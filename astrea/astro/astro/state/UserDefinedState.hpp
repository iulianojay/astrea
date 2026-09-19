/**
 * @file UserDefinedState.hpp
 * @author Jay Iuliano (iuliano.jay@gmail.com)
 * @brief Type-erased wrapper for user-defined state extensions.
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

#include <astro/types/concepts.hpp>
#include <astro/types/type_traits.hpp>

namespace astrea {
namespace astro {

class UserDefinedStatePartial;

/**
 * @brief Concept to check if a type has a static from_double_vector method.
 *
 * @tparam T The type to check.
 */
template <typename T>
concept HasStaticFromDoubleVector = requires(const std::vector<double>& vec) {
    { T::from_double_vector(vec) } -> std::same_as<T>;
};

/**
 * @brief Concept to check if a type has a mutating from_double_vector method.
 *
 * @tparam T The type to check.
 */
template <typename T>
concept HasMutatingFromDoubleVector = requires(T value, const std::vector<double>& vec) {
    requires std::is_member_function_pointer_v<decltype(&T::from_double_vector)>;
    { value.from_double_vector(vec) };
};

/**
 * @brief Concept to check if a type is streamable to std::ostream.
 *
 * @tparam T The type to check.
 */
template <typename T>
concept HasOutputStreamOperator = requires(std::ostream& os, const T& value) {
    { os << value } -> std::same_as<std::ostream&>;
};

/**
 * @brief Concept to check if a type is a valid user-defined state type.
 *
 * @tparam T The type to check.
 */
template <typename T>
concept IsUserDefinedStateType = requires(T) {
    std::is_same<T, remove_cv_ref<T>>::value;
    std::is_default_constructible<T>::value;
    std::is_copy_constructible<T>::value;
    std::is_move_constructible<T>::value;
    std::is_destructible<T>::value;
    requires std::equality_comparable<T>;
    requires HasForceToDoubleVector<T>;
    requires HasMathOperators<T>;
    requires HasInPlaceMathOperators<T>;
    requires HasOutputStreamOperator<T>;
    requires HasStaticFromDoubleVector<T> || HasMutatingFromDoubleVector<T>;
};

namespace detail {

/**
 * @brief Base class for type-erased user-defined state implementations.
 */
struct UserDefinedStateInnerBase {
    virtual ~UserDefinedStateInnerBase() {}

    virtual std::vector<double> force_to_double_vector() const                                                = 0;
    virtual void from_double_vector(const std::vector<double>& vec)                                           = 0;
    virtual std::unique_ptr<UserDefinedStateInnerBase> add(const UserDefinedStateInnerBase& other) const      = 0;
    virtual std::unique_ptr<UserDefinedStateInnerBase> subtract(const UserDefinedStateInnerBase& other) const = 0;
    virtual std::unique_ptr<UserDefinedStateInnerBase> multiply(const Unitless& scalar) const                 = 0;
    virtual std::unique_ptr<UserDefinedStateInnerBase> divide(const Unitless& scalar) const                   = 0;
    virtual void inplace_add(const UserDefinedStateInnerBase& other)                                          = 0;
    virtual void inplace_subtract(const UserDefinedStateInnerBase& other)                                     = 0;
    virtual void inplace_multiply(const Unitless& scalar)                                                     = 0;
    virtual void inplace_divide(const Unitless& scalar)                                                       = 0;
    virtual bool equals(const UserDefinedStateInnerBase& other) const                                         = 0;
    virtual std::unique_ptr<UserDefinedStateInnerBase> clone() const                                          = 0;
    virtual const void* get_ptr() const                                                                       = 0;
    virtual void* get_ptr()                                                                                   = 0;
    virtual const std::type_info& type() const                                                                = 0;
    virtual std::string get_name() const                                                                      = 0;
    virtual std::ostream& stream(std::ostream& os) const                                                      = 0;
    virtual UserDefinedStatePartial divide_by_time(const Time& divisor) const                                 = 0;
};

/**
 * @brief Template class for type-erased user-defined state implementations.
 *
 * @tparam T The concrete type of the user-defined state.
 */
template <typename T>
struct UserDefinedStateInner final : public UserDefinedStateInnerBase {

    UserDefinedStateInner()                                        = default;
    UserDefinedStateInner(const UserDefinedStateInner&)            = delete;
    UserDefinedStateInner(UserDefinedStateInner&&)                 = delete;
    UserDefinedStateInner& operator=(const UserDefinedStateInner&) = delete;
    UserDefinedStateInner& operator=(UserDefinedStateInner&&)      = delete;

    explicit UserDefinedStateInner(const T& x) :
        _value(x)
    {
    }

    explicit UserDefinedStateInner(T&& x) :
        _value(std::move(x))
    {
    }

    std::vector<double> force_to_double_vector() const final { return _value.force_to_double_vector(); }

    void from_double_vector(const std::vector<double>& vec) final { from_double_vector_impl(_value, vec); }

    std::unique_ptr<UserDefinedStateInnerBase> add(const UserDefinedStateInnerBase& other) const final
    {
        const auto& rhs = cast_other(other);
        return std::make_unique<UserDefinedStateInner>(_value + rhs);
    }

    std::unique_ptr<UserDefinedStateInnerBase> subtract(const UserDefinedStateInnerBase& other) const final
    {
        const auto& rhs = cast_other(other);
        return std::make_unique<UserDefinedStateInner>(_value - rhs);
    }

    std::unique_ptr<UserDefinedStateInnerBase> multiply(const Unitless& scalar) const final
    {
        return std::make_unique<UserDefinedStateInner>(_value * scalar);
    }

    std::unique_ptr<UserDefinedStateInnerBase> divide(const Unitless& scalar) const final
    {
        return std::make_unique<UserDefinedStateInner>(_value / scalar);
    }

    void inplace_add(const UserDefinedStateInnerBase& other) final { _value += cast_other(other); }
    void inplace_subtract(const UserDefinedStateInnerBase& other) final { _value -= cast_other(other); }
    void inplace_multiply(const Unitless& scalar) final { _value *= scalar; }
    void inplace_divide(const Unitless& scalar) final { _value /= scalar; }

    bool equals(const UserDefinedStateInnerBase& other) const final
    {
        if (other.type() != typeid(T)) { return false; }
        return _value == cast_other(other);
    }

    std::unique_ptr<UserDefinedStateInnerBase> clone() const final
    {
        return std::make_unique<UserDefinedStateInner>(_value);
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

    UserDefinedStatePartial divide_by_time(const Time& divisor) const final;

    template <typename U>
    static UserDefinedStatePartial divide_by_time_impl(const U& value, const Time& divisor)
        requires requires { value / divisor; };

    template <typename U>
    static UserDefinedStatePartial divide_by_time_impl(const U& value, const Time& divisor);

    template <typename U>
        requires(HasMutatingFromDoubleVector<U>)
    static void from_double_vector_impl(U& value, const std::vector<double>& vec)
    {
        value.from_double_vector(vec);
    }

    template <typename U>
        requires(!HasMutatingFromDoubleVector<U> && HasStaticFromDoubleVector<U>)
    static void from_double_vector_impl(U& value, const std::vector<double>& vec)
    {
        value = U::from_double_vector(vec);
    }

    template <typename U>
        requires(!HasGetName<U>)
    static std::string get_name_impl(const U&)
    {
        return "UserDefinedState";
    }

    template <typename U>
        requires(HasGetName<U>)
    static std::string get_name_impl(const U& value)
    {
        return value.get_name();
    }

    const T& cast_other(const UserDefinedStateInnerBase& other) const
    {
        if (other.type() != typeid(T)) {
            throw std::runtime_error("Cannot operate on UserDefinedState instances of different concrete types.");
        }
        return static_cast<const UserDefinedStateInner<T>&>(other)._value;
    }

    T _value;
};

/**
 * @brief A null implementation of a user-defined state, used as a default.
 */
struct NullUserDefinedState {
    std::vector<double> force_to_double_vector() const { return {}; }
    void from_double_vector(const std::vector<double>&) {}
    NullUserDefinedState operator+(const NullUserDefinedState&) const { return {}; }
    NullUserDefinedState& operator+=(const NullUserDefinedState&) { return *this; }
    NullUserDefinedState operator-(const NullUserDefinedState&) const { return {}; }
    NullUserDefinedState& operator-=(const NullUserDefinedState&) { return *this; }
    NullUserDefinedState operator*(const Unitless&) const { return {}; }
    NullUserDefinedState& operator*=(const Unitless&) { return *this; }
    NullUserDefinedState operator/(const Unitless&) const { return {}; }
    NullUserDefinedState& operator/=(const Unitless&) { return *this; }
    bool operator==(const NullUserDefinedState&) const { return true; }
    std::string get_name() const { return "NullUserDefinedState"; }
    friend std::ostream& operator<<(std::ostream& os, const NullUserDefinedState&)
    {
        os << "NullUserDefinedState";
        return os;
    }
};

} // namespace detail

class UserDefinedState;

/**
 * @brief Concept to check if a type is generically constructable as a UserDefinedState.
 *
 * @tparam T The type to check.
 */
template <typename T>
concept IsGenericallyConstructableUserDefinedState = requires(T) {
    requires !std::is_same<UserDefinedState, remove_cv_ref<T>>::value;
    requires IsUserDefinedStateType<remove_cv_ref<T>>;
};

/**
 * @brief Type-erased wrapper for user-defined state extensions.
 *
 * This class allows users to define their own state extensions while providing a consistent interface for operations
 * such as addition, subtraction, multiplication, and division. It uses type erasure to store any user-defined state
 * type that satisfies the IsUserDefinedStateType concept.
 */
class UserDefinedState {

    friend std::ostream& operator<<(std::ostream& os, const UserDefinedState& state) { return state.ptr()->stream(os); }

  public:
    /**
     * @brief Default constructor that initializes the UserDefinedState with a NullUserDefinedState.
     */
    UserDefinedState() :
        UserDefinedState(detail::NullUserDefinedState{})
    {
    }

  private:
    /**
     * @brief Helper function to handle generic construction of UserDefinedState.
     */
    void generic_ctor_impl() {}

  public:
    /**
     * @brief Constructs a UserDefinedState from a user-defined state type that satisfies the IsGenericallyConstructableUserDefinedState concept.
     *
     * @tparam T The type of the user-defined state.
     * @param x The user-defined state instance to wrap.
     */
    template <IsGenericallyConstructableUserDefinedState T>
    explicit UserDefinedState(T&& x) :
        _ptr(std::make_unique<detail::UserDefinedStateInner<remove_cv_ref<T>>>(std::forward<T>(x)))
    {
        generic_ctor_impl();
    }

    /**
     * @brief Copy constructor for UserDefinedState.
     *
     * @param other The UserDefinedState instance to copy from.
     */
    UserDefinedState(const UserDefinedState& other) :
        _ptr(other._ptr->clone())
    {
    }

    /**
     * @brief Move constructor for UserDefinedState.
     *
     * @param other The UserDefinedState instance to move from.
     */
    UserDefinedState(UserDefinedState&& other) noexcept = default;

    /**
     * @brief Copy assignment operator for UserDefinedState.
     *
     * @param other The UserDefinedState instance to copy from.
     * @return UserDefinedState& Reference to the current instance after assignment.
     */
    UserDefinedState& operator=(UserDefinedState&& other) noexcept = default;

    /**
     * @brief Copy assignment operator for UserDefinedState.
     *
     * @param other The UserDefinedState instance to copy from.
     * @return UserDefinedState& Reference to the current instance after assignment.
     */
    UserDefinedState& operator=(const UserDefinedState& other)
    {
        if (this != &other) { _ptr = other._ptr->clone(); }
        return *this;
    }

    /**
     * @brief Assignment operator for user-defined state types that satisfy the IsGenericallyConstructableUserDefinedState concept.
     *
     * @tparam T The type of the user-defined state.
     * @param x The user-defined state instance to assign from.
     * @return UserDefinedState& Reference to the current instance after assignment.
     */
    template <IsGenericallyConstructableUserDefinedState T>
    UserDefinedState& operator=(T&& x)
    {
        return (*this) = UserDefinedState(std::forward<T>(x));
    }

    /**
     * @brief Extracts a pointer to the underlying user-defined state of type T.
     *
     * @tparam T The type of the user-defined state to extract.
     * @return const T* Pointer to the underlying user-defined state if it matches type T, otherwise nullptr.
     */
    template <IsGenericallyConstructableUserDefinedState T>
    const T* extract() const noexcept
    {
        auto p = static_cast<const detail::UserDefinedStateInner<T>*>(ptr());
        return ptr()->type() == typeid(T) ? &(p->_value) : nullptr;
    }

    /**
     * @brief Extracts a mutable pointer to the underlying user-defined state of type T.
     *
     * @tparam T The type of the user-defined state to extract.
     * @return T* Pointer to the underlying user-defined state if it matches type T, otherwise nullptr.
     */
    template <IsGenericallyConstructableUserDefinedState T>
    T* extract_mutable_reference() noexcept
    {
        auto p = static_cast<detail::UserDefinedStateInner<T>*>(ptr());
        return ptr()->type() == typeid(T) ? &(p->_value) : nullptr;
    }

    /**
     * @brief Forces the user-defined state to a vector of double values.
     *
     * @return std::vector<double> Vector containing the user-defined state as double values.
     */
    std::vector<double> force_to_double_vector() const { return ptr()->force_to_double_vector(); }

    /**
     * @brief Mutates the user-defined state from a vector of double values.
     *
     * @param vec The vector of double values to set the user-defined state from.
     * @return UserDefinedState& Reference to the current instance after mutation.
     */
    UserDefinedState& from_double_vector(const std::vector<double>& vec)
    {
        ptr()->from_double_vector(vec);
        return *this;
    }

    /**
     * @brief Gets the name of the user-defined state type.
     *
     * @return std::string The name of the user-defined state type.
     */
    UserDefinedState operator+(const UserDefinedState& other) const
    {
        return UserDefinedState(ptr()->add(*other.ptr()));
    }

    /**
     * @brief Adds another UserDefinedState to this UserDefinedState in place.
     *
     * @param other The other UserDefinedState to add.
     * @return Reference to the current UserDefinedState after addition.
     */
    UserDefinedState& operator+=(const UserDefinedState& other)
    {
        ptr()->inplace_add(*other.ptr());
        return *this;
    }

    /**
     * @brief Subtracts another UserDefinedState from this UserDefinedState.
     *
     * @param other The other UserDefinedState to subtract.
     * @return UserDefinedState The resulting UserDefinedState after subtraction.
     */
    UserDefinedState operator-(const UserDefinedState& other) const
    {
        return UserDefinedState(ptr()->subtract(*other.ptr()));
    }

    /**
     * @brief Subtracts another UserDefinedState from this UserDefinedState in place.
     *
     * @param other The other UserDefinedState to subtract.
     * @return Reference to the current UserDefinedState after subtraction.
     */
    UserDefinedState& operator-=(const UserDefinedState& other)
    {
        ptr()->inplace_subtract(*other.ptr());
        return *this;
    }

    /**
     * @brief Multiplies the UserDefinedState by a scalar.
     *
     * @param scalar The scalar to multiply with.
     * @return UserDefinedState The resulting UserDefinedState after multiplication.
     */
    UserDefinedState operator*(const Unitless& scalar) const { return UserDefinedState(ptr()->multiply(scalar)); }

    /**
     * @brief Multiplies the UserDefinedState by a scalar in place.
     *
     * @param scalar The scalar to multiply with.
     * @return Reference to the current UserDefinedState after multiplication.
     */
    UserDefinedState& operator*=(const Unitless& scalar)
    {
        ptr()->inplace_multiply(scalar);
        return *this;
    }

    /**
     * @brief Divides the UserDefinedState by a scalar.
     *
     * @param scalar The scalar to divide by.
     * @return UserDefinedState The resulting UserDefinedState after division.
     */
    UserDefinedState operator/(const Unitless& scalar) const { return UserDefinedState(ptr()->divide(scalar)); }

    /**
     * @brief Divides the UserDefinedState by Time to produce a UserDefinedStatePartial.
     *
     * @param divisor The time divisor.
     * @return UserDefinedStatePartial The resulting user-defined state partial.
     */
    UserDefinedStatePartial operator/(const Time& divisor) const;

    /**
     * @brief Divides the UserDefinedState by a scalar in place.
     *
     * @param scalar The scalar to divide by.
     * @return Reference to the current UserDefinedState after division.
     */
    UserDefinedState& operator/=(const Unitless& scalar)
    {
        ptr()->inplace_divide(scalar);
        return *this;
    }

    /**
     * @brief Checks if two UserDefinedState instances are equal.
     *
     * @param other The other UserDefinedState to compare with.
     * @return true if the two instances are equal, false otherwise.
     */
    bool operator==(const UserDefinedState& other) const { return ptr()->equals(*other.ptr()); }

    /**
     * @brief Gets the name of the user-defined state type.
     *
     * @return std::string The name of the user-defined state type.
     */
    std::string get_name() const { return ptr()->get_name(); }

    /**
     * @brief Gets a pointer to the underlying user-defined state.
     *
     * @return const void* Pointer to the underlying user-defined state.
     */
    const void* get_ptr() const { return ptr()->get_ptr(); }

    /**
     * @brief Gets a mutable pointer to the underlying user-defined state.
     *
     * @return void* Mutable pointer to the underlying user-defined state.
     */
    void* get_ptr() { return ptr()->get_ptr(); }

  private:
    /**
     * @brief Constructs a UserDefinedState from a unique pointer to a UserDefinedStateInnerBase.
     *
     * @param ptr The unique pointer to the UserDefinedStateInnerBase.
     */
    explicit UserDefinedState(std::unique_ptr<detail::UserDefinedStateInnerBase>&& ptr) :
        _ptr(std::move(ptr))
    {
    }

    std::unique_ptr<detail::UserDefinedStateInnerBase> _ptr; //!< Unique pointer to the type-erased user-defined state implementation.

    /**
     * @brief Gets a pointer to the underlying UserDefinedStateInnerBase.
     *
     * @return detail::UserDefinedStateInnerBase const* Pointer to the underlying UserDefinedStateInnerBase.
     */
    detail::UserDefinedStateInnerBase const* ptr() const
    {
        assert(_ptr.get() != nullptr);
        return _ptr.get();
    }

    /**
     * @brief Gets a mutable pointer to the underlying UserDefinedStateInnerBase.
     *
     * @return detail::UserDefinedStateInnerBase* Mutable pointer to the underlying UserDefinedStateInnerBase.
     */
    detail::UserDefinedStateInnerBase* ptr()
    {
        assert(_ptr.get() != nullptr);
        return _ptr.get();
    }
};

} // namespace astro
} // namespace astrea

#include <astro/state/UserDefinedStatePartial.hpp>
