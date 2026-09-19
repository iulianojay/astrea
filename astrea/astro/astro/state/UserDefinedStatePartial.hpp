/**
 * @file UserDefinedStatePartial.hpp
 * @author Jay Iuliano (iuliano.jay@gmail.com)
 * @brief Type-erased wrapper for user-defined state partial extensions.
 * @date 2026-09-19
 *
 * @copyright Copyright (c) 2025-2026 Jay Iuliano
 *
 * The GNU Lesser General Public License (LGPL)
 *
 * This file is part of Astrea.
 * Astrea is free software: you can redistribute it and/or modify it under the terms of the GNU Lesser General Public License
 * as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
 * Astrea is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty
 * of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU Lesser General Public License for more details. You should
 * have received a copy of the GNU General Public License along with Astrea. If not, see <https://www.gnu.org/licenses/>.
 *
 */
#pragma once

#include <cassert>
#include <concepts>
#include <iosfwd>
#include <memory>
#include <stdexcept>
#include <string>
#include <type_traits>
#include <typeinfo>
#include <utility>
#include <vector>

#include <astro/state/UserDefinedState.hpp>
#include <astro/types/concepts.hpp>
#include <astro/types/type_traits.hpp>

namespace astrea {
namespace astro {

/**
 * @brief Concept to check if a type has a static from_double_vector method.
 *
 * @tparam T The type to check.
 */
template <typename T>
concept HasStaticFromDoubleVectorPartial = requires(const std::vector<double>& vec) {
    { T::from_double_vector(vec) } -> std::same_as<T>;
};

/**
 * @brief Concept to check if a type has a mutating from_double_vector method.
 *
 * @tparam T The type to check.
 */
template <typename T>
concept HasMutatingFromDoubleVectorPartial = requires(T value, const std::vector<double>& vec) {
    requires std::is_member_function_pointer_v<decltype(&T::from_double_vector)>;
    { value.from_double_vector(vec) };
};

/**
 * @brief Concept to check if a type is streamable to std::ostream.
 *
 * @tparam T The type to check.
 */
template <typename T>
concept HasOutputStreamOperatorPartial = requires(std::ostream& os, const T& value) {
    { os << value } -> std::same_as<std::ostream&>;
};

/**
 * @brief Concept to check if a type is a valid user-defined state partial type.
 *
 * @tparam T The type to check.
 */
template <typename T>
concept IsUserDefinedStatePartialType = requires(T) {
    std::is_same<T, remove_cv_ref<T>>::value;
    std::is_default_constructible<T>::value;
    std::is_copy_constructible<T>::value;
    std::is_move_constructible<T>::value;
    std::is_destructible<T>::value;
    requires std::equality_comparable<T>;
    requires HasForceToDoubleVector<T>;
    requires HasMathOperators<T>;
    requires HasInPlaceMathOperators<T>;
    requires HasOutputStreamOperatorPartial<T>;
    requires HasStaticFromDoubleVectorPartial<T> || HasMutatingFromDoubleVectorPartial<T>;
};

namespace detail {

/**
 * @brief Base class for type-erased user-defined state partial implementations.
 */
struct UserDefinedStatePartialInnerBase {
    virtual ~UserDefinedStatePartialInnerBase() {}

    virtual std::vector<double> force_to_double_vector() const      = 0;
    virtual void from_double_vector(const std::vector<double>& vec) = 0;
    virtual std::unique_ptr<UserDefinedStatePartialInnerBase> add(const UserDefinedStatePartialInnerBase& other) const = 0;
    virtual std::unique_ptr<UserDefinedStatePartialInnerBase> subtract(const UserDefinedStatePartialInnerBase& other) const = 0;
    virtual std::unique_ptr<UserDefinedStatePartialInnerBase> multiply(const Unitless& scalar) const = 0;
    virtual std::unique_ptr<UserDefinedStatePartialInnerBase> divide(const Unitless& scalar) const   = 0;
    virtual void inplace_add(const UserDefinedStatePartialInnerBase& other)                          = 0;
    virtual void inplace_subtract(const UserDefinedStatePartialInnerBase& other)                     = 0;
    virtual void inplace_multiply(const Unitless& scalar)                                            = 0;
    virtual void inplace_divide(const Unitless& scalar)                                              = 0;
    virtual bool equals(const UserDefinedStatePartialInnerBase& other) const                         = 0;
    virtual std::unique_ptr<UserDefinedStatePartialInnerBase> clone() const                          = 0;
    virtual const void* get_ptr() const                                                              = 0;
    virtual void* get_ptr()                                                                          = 0;
    virtual const std::type_info& type() const                                                       = 0;
    virtual std::string get_name() const                                                             = 0;
    virtual std::ostream& stream(std::ostream& os) const                                             = 0;
    virtual UserDefinedState multiply_by_time(const Time& time) const                                = 0;
};

/**
 * @brief Template class for type-erased user-defined state partial implementations.
 *
 * @tparam T The concrete type of the user-defined state partial.
 */
template <typename T>
struct UserDefinedStatePartialInner final : public UserDefinedStatePartialInnerBase {

    UserDefinedStatePartialInner()                                               = default;
    UserDefinedStatePartialInner(const UserDefinedStatePartialInner&)            = delete;
    UserDefinedStatePartialInner(UserDefinedStatePartialInner&&)                 = delete;
    UserDefinedStatePartialInner& operator=(const UserDefinedStatePartialInner&) = delete;
    UserDefinedStatePartialInner& operator=(UserDefinedStatePartialInner&&)      = delete;

    explicit UserDefinedStatePartialInner(const T& x) :
        _value(x)
    {
    }

    explicit UserDefinedStatePartialInner(T&& x) :
        _value(std::move(x))
    {
    }

    std::vector<double> force_to_double_vector() const final { return _value.force_to_double_vector(); }

    void from_double_vector(const std::vector<double>& vec) final { from_double_vector_impl(_value, vec); }

    std::unique_ptr<UserDefinedStatePartialInnerBase> add(const UserDefinedStatePartialInnerBase& other) const final
    {
        const auto& rhs = cast_other(other);
        return std::make_unique<UserDefinedStatePartialInner>(_value + rhs);
    }

    std::unique_ptr<UserDefinedStatePartialInnerBase> subtract(const UserDefinedStatePartialInnerBase& other) const final
    {
        const auto& rhs = cast_other(other);
        return std::make_unique<UserDefinedStatePartialInner>(_value - rhs);
    }

    std::unique_ptr<UserDefinedStatePartialInnerBase> multiply(const Unitless& scalar) const final
    {
        return std::make_unique<UserDefinedStatePartialInner>(_value * scalar);
    }

    std::unique_ptr<UserDefinedStatePartialInnerBase> divide(const Unitless& scalar) const final
    {
        return std::make_unique<UserDefinedStatePartialInner>(_value / scalar);
    }

    void inplace_add(const UserDefinedStatePartialInnerBase& other) final { _value += cast_other(other); }
    void inplace_subtract(const UserDefinedStatePartialInnerBase& other) final { _value -= cast_other(other); }
    void inplace_multiply(const Unitless& scalar) final { _value *= scalar; }
    void inplace_divide(const Unitless& scalar) final { _value /= scalar; }

    bool equals(const UserDefinedStatePartialInnerBase& other) const final
    {
        if (other.type() != typeid(T)) { return false; }
        return _value == cast_other(other);
    }

    std::unique_ptr<UserDefinedStatePartialInnerBase> clone() const final
    {
        return std::make_unique<UserDefinedStatePartialInner>(_value);
    }

    const void* get_ptr() const final { return &_value; }
    void* get_ptr() final { return &_value; }

    const std::type_info& type() const final { return typeid(T); }

    std::string get_name() const final { return get_name_impl(_value); }

    std::ostream& stream(std::ostream& os) const final
    {
        os << _value;
        return os;
    }

    UserDefinedState multiply_by_time(const Time& time) const final { return multiply_by_time_impl(_value, time); }

    template <typename U>
        requires(HasMutatingFromDoubleVectorPartial<U>)
    static void from_double_vector_impl(U& value, const std::vector<double>& vec)
    {
        value.from_double_vector(vec);
    }

    template <typename U>
        requires(!HasMutatingFromDoubleVectorPartial<U> && HasStaticFromDoubleVectorPartial<U>)
    static void from_double_vector_impl(U& value, const std::vector<double>& vec)
    {
        value = U::from_double_vector(vec);
    }

    template <typename U>
        requires(!HasGetName<U>)
    static std::string get_name_impl(const U&)
    {
        return "UserDefinedStatePartial";
    }

    template <typename U>
        requires(HasGetName<U>)
    static std::string get_name_impl(const U& value)
    {
        return value.get_name();
    }

    template <typename U>
    static UserDefinedState multiply_by_time_impl(const U& value, const Time& time)
        requires requires { value * time; }
    {
        return UserDefinedState(value * time);
    }

    template <typename U>
    static UserDefinedState multiply_by_time_impl(const U&, const Time&)
    {
        throw std::runtime_error("Concrete user-defined state partial type does not support multiplication by Time.");
    }

    const T& cast_other(const UserDefinedStatePartialInnerBase& other) const
    {
        if (other.type() != typeid(T)) {
            throw std::runtime_error("Cannot operate on UserDefinedStatePartial instances of different concrete types.");
        }
        return static_cast<const UserDefinedStatePartialInner<T>&>(other)._value;
    }

    T _value;
};

/**
 * @brief A null implementation of a user-defined state partial, used as a default.
 */
struct NullUserDefinedStatePartial {
    std::vector<double> force_to_double_vector() const { return {}; }
    void from_double_vector(const std::vector<double>&) {}
    NullUserDefinedStatePartial operator+(const NullUserDefinedStatePartial&) const { return {}; }
    NullUserDefinedStatePartial& operator+=(const NullUserDefinedStatePartial&) { return *this; }
    NullUserDefinedStatePartial operator-(const NullUserDefinedStatePartial&) const { return {}; }
    NullUserDefinedStatePartial& operator-=(const NullUserDefinedStatePartial&) { return *this; }
    NullUserDefinedStatePartial operator*(const Unitless&) const { return {}; }
    NullUserDefinedStatePartial& operator*=(const Unitless&) { return *this; }
    NullUserDefinedStatePartial operator/(const Unitless&) const { return {}; }
    NullUserDefinedStatePartial& operator/=(const Unitless&) { return *this; }
    bool operator==(const NullUserDefinedStatePartial&) const { return true; }
    std::string get_name() const { return "NullUserDefinedStatePartial"; }
    friend std::ostream& operator<<(std::ostream& os, const NullUserDefinedStatePartial&)
    {
        os << "NullUserDefinedStatePartial";
        return os;
    }
};

} // namespace detail

class UserDefinedStatePartial;

/**
 * @brief Concept to check if a type is generically constructable as a UserDefinedStatePartial.
 *
 * @tparam T The type to check.
 */
template <typename T>
concept IsGenericallyConstructableUserDefinedStatePartial = requires(T) {
    requires !std::is_same<UserDefinedStatePartial, remove_cv_ref<T>>::value;
    requires IsUserDefinedStatePartialType<remove_cv_ref<T>>;
};

/**
 * @brief Type-erased wrapper for user-defined state partial extensions.
 */
class UserDefinedStatePartial {

    friend std::ostream& operator<<(std::ostream& os, const UserDefinedStatePartial& state)
    {
        return state.ptr()->stream(os);
    }

  public:
    /**
     * @brief Default constructor that initializes with a NullUserDefinedStatePartial.
     */
    UserDefinedStatePartial() :
        UserDefinedStatePartial(detail::NullUserDefinedStatePartial{})
    {
    }

  private:
    /**
     * @brief Helper function to handle generic construction of UserDefinedStatePartial.
     */
    void generic_ctor_impl() {}

  public:
    /**
     * @brief Constructs a UserDefinedStatePartial from a user-defined partial type.
     *
     * @tparam T The type of the user-defined state partial.
     * @param x The user-defined state partial instance to wrap.
     */
    template <IsGenericallyConstructableUserDefinedStatePartial T>
    explicit UserDefinedStatePartial(T&& x) :
        _ptr(std::make_unique<detail::UserDefinedStatePartialInner<remove_cv_ref<T>>>(std::forward<T>(x)))
    {
        generic_ctor_impl();
    }

    /**
     * @brief Copy constructor for UserDefinedStatePartial.
     *
     * @param other The UserDefinedStatePartial instance to copy from.
     */
    UserDefinedStatePartial(const UserDefinedStatePartial& other) :
        _ptr(other._ptr->clone())
    {
    }

    /**
     * @brief Move constructor for UserDefinedStatePartial.
     *
     * @param other The UserDefinedStatePartial instance to move from.
     */
    UserDefinedStatePartial(UserDefinedStatePartial&& other) noexcept = default;

    /**
     * @brief Move assignment operator for UserDefinedStatePartial.
     *
     * @param other The UserDefinedStatePartial instance to move from.
     * @return UserDefinedStatePartial& Reference to the current instance after assignment.
     */
    UserDefinedStatePartial& operator=(UserDefinedStatePartial&& other) noexcept = default;

    /**
     * @brief Copy assignment operator for UserDefinedStatePartial.
     *
     * @param other The UserDefinedStatePartial instance to copy from.
     * @return UserDefinedStatePartial& Reference to the current instance after assignment.
     */
    UserDefinedStatePartial& operator=(const UserDefinedStatePartial& other)
    {
        if (this != &other) { _ptr = other._ptr->clone(); }
        return *this;
    }

    /**
     * @brief Assignment operator for user-defined partial types.
     *
     * @tparam T The type of the user-defined partial.
     * @param x The user-defined partial instance to assign from.
     * @return UserDefinedStatePartial& Reference to the current instance after assignment.
     */
    template <IsGenericallyConstructableUserDefinedStatePartial T>
    UserDefinedStatePartial& operator=(T&& x)
    {
        return (*this) = UserDefinedStatePartial(std::forward<T>(x));
    }

    /**
     * @brief Extracts a pointer to the underlying user-defined state partial of type T.
     *
     * @tparam T The type of the user-defined state partial to extract.
     * @return const T* Pointer to the underlying user-defined state partial if it matches type T, otherwise nullptr.
     */
    template <IsGenericallyConstructableUserDefinedStatePartial T>
    const T* extract() const noexcept
    {
        auto p = static_cast<const detail::UserDefinedStatePartialInner<T>*>(ptr());
        return ptr()->type() == typeid(T) ? &(p->_value) : nullptr;
    }

    /**
     * @brief Extracts a mutable pointer to the underlying user-defined state partial of type T.
     *
     * @tparam T The type of the user-defined state partial to extract.
     * @return T* Pointer to the underlying user-defined state partial if it matches type T, otherwise nullptr.
     */
    template <IsGenericallyConstructableUserDefinedStatePartial T>
    T* extract_mutable_reference() noexcept
    {
        auto p = static_cast<detail::UserDefinedStatePartialInner<T>*>(ptr());
        return ptr()->type() == typeid(T) ? &(p->_value) : nullptr;
    }

    /**
     * @brief Forces the user-defined state partial to a vector of double values.
     *
     * @return std::vector<double> Vector containing the user-defined state partial as double values.
     */
    std::vector<double> force_to_double_vector() const { return ptr()->force_to_double_vector(); }

    /**
     * @brief Mutates the user-defined state partial from a vector of double values.
     *
     * @param vec The vector of double values to set the user-defined state partial from.
     * @return UserDefinedStatePartial& Reference to the current instance after mutation.
     */
    UserDefinedStatePartial& from_double_vector(const std::vector<double>& vec)
    {
        ptr()->from_double_vector(vec);
        return *this;
    }

    /**
     * @brief Adds another UserDefinedStatePartial to this UserDefinedStatePartial.
     *
     * @param other The other UserDefinedStatePartial to add.
     * @return UserDefinedStatePartial The resulting UserDefinedStatePartial after addition.
     */
    UserDefinedStatePartial operator+(const UserDefinedStatePartial& other) const
    {
        return UserDefinedStatePartial(ptr()->add(*other.ptr()));
    }

    /**
     * @brief Adds another UserDefinedStatePartial to this UserDefinedStatePartial in place.
     *
     * @param other The other UserDefinedStatePartial to add.
     * @return UserDefinedStatePartial& Reference to the current UserDefinedStatePartial after addition.
     */
    UserDefinedStatePartial& operator+=(const UserDefinedStatePartial& other)
    {
        ptr()->inplace_add(*other.ptr());
        return *this;
    }

    /**
     * @brief Subtracts another UserDefinedStatePartial from this UserDefinedStatePartial.
     *
     * @param other The other UserDefinedStatePartial to subtract.
     * @return UserDefinedStatePartial The resulting UserDefinedStatePartial after subtraction.
     */
    UserDefinedStatePartial operator-(const UserDefinedStatePartial& other) const
    {
        return UserDefinedStatePartial(ptr()->subtract(*other.ptr()));
    }

    /**
     * @brief Subtracts another UserDefinedStatePartial from this UserDefinedStatePartial in place.
     *
     * @param other The other UserDefinedStatePartial to subtract.
     * @return UserDefinedStatePartial& Reference to the current UserDefinedStatePartial after subtraction.
     */
    UserDefinedStatePartial& operator-=(const UserDefinedStatePartial& other)
    {
        ptr()->inplace_subtract(*other.ptr());
        return *this;
    }

    /**
     * @brief Multiplies the UserDefinedStatePartial by a scalar.
     *
     * @param scalar The scalar to multiply with.
     * @return UserDefinedStatePartial The resulting UserDefinedStatePartial after multiplication.
     */
    UserDefinedStatePartial operator*(const Unitless& scalar) const
    {
        return UserDefinedStatePartial(ptr()->multiply(scalar));
    }

    /**
     * @brief Multiplies the UserDefinedStatePartial by a scalar in place.
     *
     * @param scalar The scalar to multiply with.
     * @return UserDefinedStatePartial& Reference to the current UserDefinedStatePartial after multiplication.
     */
    UserDefinedStatePartial& operator*=(const Unitless& scalar)
    {
        ptr()->inplace_multiply(scalar);
        return *this;
    }

    /**
     * @brief Divides the UserDefinedStatePartial by a scalar.
     *
     * @param scalar The scalar to divide by.
     * @return UserDefinedStatePartial The resulting UserDefinedStatePartial after division.
     */
    UserDefinedStatePartial operator/(const Unitless& scalar) const
    {
        return UserDefinedStatePartial(ptr()->divide(scalar));
    }

    /**
     * @brief Multiplies the UserDefinedStatePartial by Time to produce a UserDefinedState.
     *
     * @param time The time multiplier.
     * @return UserDefinedState The resulting user-defined state.
     */
    UserDefinedState operator*(const Time& time) const { return ptr()->multiply_by_time(time); }

    /**
     * @brief Divides the UserDefinedStatePartial by a scalar in place.
     *
     * @param scalar The scalar to divide by.
     * @return UserDefinedStatePartial& Reference to the current UserDefinedStatePartial after division.
     */
    UserDefinedStatePartial& operator/=(const Unitless& scalar)
    {
        ptr()->inplace_divide(scalar);
        return *this;
    }

    /**
     * @brief Checks if two UserDefinedStatePartial instances are equal.
     *
     * @param other The other UserDefinedStatePartial to compare with.
     * @return true if the two instances are equal, false otherwise.
     */
    bool operator==(const UserDefinedStatePartial& other) const { return ptr()->equals(*other.ptr()); }

    /**
     * @brief Gets the name of the user-defined state partial type.
     *
     * @return std::string The name of the user-defined state partial type.
     */
    std::string get_name() const { return ptr()->get_name(); }

    /**
     * @brief Gets a pointer to the underlying user-defined state partial.
     *
     * @return const void* Pointer to the underlying user-defined state partial.
     */
    const void* get_ptr() const { return ptr()->get_ptr(); }

    /**
     * @brief Gets a mutable pointer to the underlying user-defined state partial.
     *
     * @return void* Mutable pointer to the underlying user-defined state partial.
     */
    void* get_ptr() { return ptr()->get_ptr(); }

  private:
    /**
     * @brief Constructs a UserDefinedStatePartial from a unique pointer to a UserDefinedStatePartialInnerBase.
     *
     * @param ptr The unique pointer to the UserDefinedStatePartialInnerBase.
     */
    explicit UserDefinedStatePartial(std::unique_ptr<detail::UserDefinedStatePartialInnerBase>&& ptr) :
        _ptr(std::move(ptr))
    {
    }

    std::unique_ptr<detail::UserDefinedStatePartialInnerBase> _ptr; //!< Unique pointer to the type-erased user-defined state partial implementation.

    /**
     * @brief Gets a pointer to the underlying UserDefinedStatePartialInnerBase.
     *
     * @return detail::UserDefinedStatePartialInnerBase const* Pointer to the underlying UserDefinedStatePartialInnerBase.
     */
    detail::UserDefinedStatePartialInnerBase const* ptr() const
    {
        assert(_ptr.get() != nullptr);
        return _ptr.get();
    }

    /**
     * @brief Gets a mutable pointer to the underlying UserDefinedStatePartialInnerBase.
     *
     * @return detail::UserDefinedStatePartialInnerBase* Mutable pointer to the underlying UserDefinedStatePartialInnerBase.
     */
    detail::UserDefinedStatePartialInnerBase* ptr()
    {
        assert(_ptr.get() != nullptr);
        return _ptr.get();
    }
};

template <typename T>
UserDefinedStatePartial detail::UserDefinedStateInner<T>::divide_by_time(const Time& divisor) const
{
    return divide_by_time_impl(_value, divisor);
}

template <typename T>
template <typename U>
UserDefinedStatePartial detail::UserDefinedStateInner<T>::divide_by_time_impl(const U& value, const Time& divisor)
    requires requires { value / divisor; }
{
    return UserDefinedStatePartial(value / divisor);
}

template <typename T>
template <typename U>
UserDefinedStatePartial detail::UserDefinedStateInner<T>::divide_by_time_impl(const U&, const Time&)
{
    throw std::runtime_error("Concrete user-defined state type does not support division by Time.");
}

inline UserDefinedStatePartial UserDefinedState::operator/(const Time& divisor) const
{
    return ptr()->divide_by_time(divisor);
}

} // namespace astro
} // namespace astrea
