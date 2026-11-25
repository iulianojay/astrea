/**
 * @file AngularElementsInterface.hpp
 * @author Jay Iuliano (iuliano.jay@gmail.com)
 * @brief This file defines the AngularElementsInterface class and its associated methods.
 * @date 2025-08-02
 *
 * @copyright Copyright (c) 2025 Jay Iuliano
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

#include <math/interpolation.hpp>

#include <astro/frames/definitions.hpp>
#include <astro/frames/framework/CartesianVector.hpp>
#include <astro/frames/framework/frame_concepts.hpp>
#include <astro/state/framework/ElementMatrix.hpp>
#include <astro/state/orbital_elements.hpp>
#include <astro/systems.hpp>
#include <astro/types/concepts.hpp>

namespace astrea {
namespace astro {

template <typename T>
concept IsAngularElementsImpl = requires {
    typename T::ArrayType;
    typename T::AngularElementsTag;
    requires IsCelestialBody<std::remove_cvref_t<decltype(T::body)>>;
};

template <typename Derived_T, typename Derived_U>
concept IsCompatibleAngularElements = IsAngularElementsImpl<Derived_U> && IsAngularElementsImpl<Derived_T> &&
                                      IsCompatibleElementMatrix<typename Derived_T::ArrayType, typename Derived_U::ArrayType> &&
                                      equivalent(Derived_T::body, Derived_U::body);

template <typename Derived_T, IsCelestialBody auto _body_, typename... Elements_T>
class AngularElementsInterface {
  public:
    using AngularElementsTag = void; //!< Tag type used by IsAngularElementsImpl concept detection.
    using ArrayType = ElementMatrix<sizeof...(Elements_T), 1, Elements_T...>; //!< The underlying array type representing the orbital elements.

    static constexpr auto body          = _body_; //!< The central body of this angular element set
    static constexpr auto _icrf_frame_  = make_frame(_body_, axes::icrf); //!< Inertial frame for the body.
    static constexpr auto _fixed_frame_ = get_body_fixed_frame<_body_>(); //!< Body-fixed rotating frame.

    /**
     * @brief Default constructor for AngularElements.
     *
     * Initializes the AngularElements with default values.
     */
    inline constexpr AngularElementsInterface() = default;

    /**
     * @brief Constructor for AngularElements with specified elements.
     *
     * @param elements The elements to initialize the AngularElements with.
     */
    inline constexpr AngularElementsInterface(const Elements_T&... elements) :
        _elements(elements...)
    {
    }

    /**
     * @brief Constructor for AngularElements with an existing array of elements.
     *
     * @param elements The array of elements to initialize the AngularElements with.
     */
    inline constexpr AngularElementsInterface(const ArrayType& elements) :
        _elements(elements)
    {
    }

    /**
     * @brief Constructor for AngularElements by moving an existing array of elements.
     *
     * @param elements The array of elements to move into the AngularElements.
     */
    inline constexpr AngularElementsInterface(ArrayType&& elements) :
        _elements(std::move(elements))
    {
    }

    /**
     * @brief Constructor for Derived_T from any inertial radius vector centred on the same body.
     *
     * Accepts any frame whose origin matches _body_ and whose axis is the ICRF axis.
     *
     * @tparam _frame_ The inertial frame of the radius vector.
     * @param r Radius vector in an ICRF-axis frame centred on the body.
     * @param date Date for the frame transformation.
     */
    template <auto _frame_>
        requires(equivalent(_frame_, _icrf_frame_))
    AngularElementsInterface(const RadiusVector<_frame_>& r, const Date& date)
    {
        *this = Derived_T(r.template in_frame<_fixed_frame_>(date));
    }

    /**
     * @brief Constructor for Derived_T from a body-fixed radius vector.
     *
     * @param r Radius vector in the body-fixed frame
     */
    AngularElementsInterface(const RadiusVector<_fixed_frame_>& r)
    {
        std::tie(get<0>(), get<1>(), get<2>()) = Derived_T::from_body_fixed(r);
    }

    /**
     * @brief Constructor for Derived_T from orbital elements.
     *
     * @param elements Orbital elements
     * @param date Date for the frame transformation
     */
    template <IsOrbitalElements T>
    AngularElementsInterface(const T& elements, const Date& date)
    {
        static const GravParam mu = get_mu<Derived_T::body>();
        *this = Derived_T(Cartesian<T::frame>(elements, mu).get_position().template in_frame<_fixed_frame_>(date));
    }

    /**
     * @brief Converts the Derived_T state to a body-fixed radius vector.
     */
    RadiusVector<_fixed_frame_> get_position() const
    {
        return Derived_T::template to_body_fixed<_fixed_frame_>(get<0>(), get<1>(), get<2>());
    }

    /**
     * @brief Converts the Derived_T state to an inertial radius vector.
     *
     * @param date Date for the frame transformation
     */
    RadiusVector<_icrf_frame_> get_position(const Date& date) const
    {
        return get_position().template in_frame<_icrf_frame_>(date);
    }

    /**
     * @brief Virtual destructor for AngularElements.
     */
    virtual inline constexpr ~AngularElementsInterface() = default;

    /**
     * @brief Copy assignment operator for the Derived_T.
     *
     * @param other The Derived_T to copy from.
     * @return A reference to the assigned Derived_T.
     */
    inline constexpr Derived_T& operator=(const Derived_T& other)
    {
        _elements = other._elements;
        return static_cast<Derived_T&>(*this);
    }

    /**
     * @brief Move assignment operator for the Derived_T.
     *
     * @param other The Derived_T to move from.
     * @return A reference to the assigned Derived_T.
     */
    inline constexpr Derived_T& operator=(Derived_T&& other) noexcept
    {
        _elements = std::move(other._elements);
        return static_cast<Derived_T&>(*this);
    }

    /**
     * @brief Copy assignment operator for compatible Derived_Ts.
     *
     * @tparam elements_u The types of the elements in the other Derived_T.
     * @param other The Derived_T to copy from.
     * @return A reference to the assigned Derived_T.
     */
    template <typename Derived_U>
        requires(!std::is_same_v<std::remove_cvref_t<Derived_U>, AngularElementsInterface> && IsCompatibleAngularElements<Derived_T, Derived_U>)
    inline constexpr Derived_T& operator=(const Derived_U& other)
    {
        _elements = other._elements;
        return static_cast<Derived_T&>(*this);
    }

    /**
     * @brief Move assignment operator for compatible Derived_Ts.
     *
     * @tparam elements_u The types of the elements in the other Derived_T.
     * @param other The Derived_T to move from.
     * @return A reference to the assigned Derived_T.
     */
    template <typename Derived_U>
        requires(!std::is_same_v<std::remove_cvref_t<Derived_U>, AngularElementsInterface> && IsCompatibleAngularElements<Derived_T, Derived_U>)
    inline constexpr Derived_T& operator=(Derived_U&& other) noexcept
    {
        _elements = std::move(other._elements);
        return static_cast<Derived_T&>(*this);
    }

    /**
     * @brief Access an element of the array by its flat index.
     *
     * @tparam idx The flat index of the element to access.
     * @return The element at the specified index.
     */
    template <std::size_t idx>
    inline constexpr auto& get()
    {
        return _elements.template get<idx>();
    }

    /**
     * @brief Access an element of the array by its flat index (const version).
     *
     * @tparam idx The flat index of the element to access.
     * @return The element at the specified index.
     */
    template <std::size_t idx>
    inline constexpr const auto& get() const
    {
        return _elements.template get<idx>();
    }

    /**
     * @brief Addition between equivalent Derived_Ts.
     *
     * @tparam elements_u The types of the elements in the other array.
     * @param other The other Derived_T to add.
     * @return A new Derived_T representing the sum of the two arrays.
     */
    template <typename Derived_U>
        requires(IsCompatibleAngularElements<Derived_T, Derived_U>)
    inline constexpr Derived_T operator+(const Derived_U& other) const
    {
        return { _elements + other._elements };
    }

    /**
     * @brief Addition assignment between equivalent Derived_Ts.
     *
     * @tparam elements_u The types of the elements in the other array.
     * @param other The other Derived_T to add.
     * @return A reference to the modified Derived_T after addition.
     */
    template <typename Derived_U>
        requires(IsCompatibleAngularElements<Derived_T, Derived_U>)
    inline constexpr Derived_T& operator+=(const Derived_U& other)
    {
        _elements += other._elements;
        return static_cast<Derived_T&>(*this);
    }

    /**
     * @brief Unary negation of the Derived_T.
     *
     * @return A new Derived_T with all elements negated.
     */
    inline constexpr Derived_T operator-() const { return { -_elements }; }

    /**
     * @brief Subtraction between equivalent Derived_Ts.
     *
     * @tparam elements_u The types of the elements in the other array.
     * @param other The other Derived_T to subtract.
     * @return A new Derived_T representing the difference of the two arrays.
     */
    template <typename Derived_U>
        requires(IsCompatibleAngularElements<Derived_T, Derived_U>)
    inline constexpr Derived_T operator-(const Derived_U& other) const
    {
        return { _elements - other._elements };
    }

    /**
     * @brief Subtraction assignment between equivalent Derived_Ts.
     *
     * @tparam elements_u The types of the elements in the other array.
     * @param other The other Derived_T to subtract.
     * @return A reference to the modified Derived_T after subtraction.
     */
    template <typename Derived_U>
        requires(IsCompatibleAngularElements<Derived_T, Derived_U>)
    inline constexpr Derived_T& operator-=(const Derived_U& other)
    {
        _elements -= other._elements;
        return static_cast<Derived_T&>(*this);
    }

    /**
     * @brief Equality comparison between equal Derived_Ts.
     *
     * Use a hidden-friend non-member to avoid C++20 rewritten-member ambiguity warnings with `x == y`.
     */
    friend inline constexpr bool operator==(const Derived_T& lhs, const Derived_T& rhs)
    {
        return lhs._elements == rhs._elements;
    }

    /**
     * @brief Equality comparison between equivalent orbital element types.
     *
     * Use a hidden-friend non-member to keep direct comparability without member-operator rewrite ambiguity.
     */
    template <typename Derived_U>
        requires(IsCompatibleAngularElements<Derived_T, Derived_U> && !IsSameUnderlyingType<Derived_T, Derived_U>)
    friend inline constexpr bool operator==(const Derived_T& lhs, const Derived_U& rhs)
    {
        return lhs._elements == rhs._elements;
    }

    /**
     * @brief Inequality comparison between equivalent Derived_Ts.
     *
     * @tparam elements_u The types of the elements in the other array.
     * @param other The other Derived_T to compare.
     * @return True if any corresponding elements are not equal, false otherwise.
     */
    template <typename T>
        requires(IsScalarThatCanMultiply<T, Elements_T...> && (std::is_arithmetic_v<T> || std::is_same_v<T, Unitless>))
    inline constexpr Derived_T operator*(const T& scalar) const
    {
        return Derived_T{ _elements * scalar };
    }

    template <typename T>
        requires(IsScalarThatCanMultiply<T, Elements_T...> && !std::is_arithmetic_v<T> && !std::is_same_v<T, Unitless>)
    inline constexpr auto operator*(const T& scalar) const
    {
        return _elements * scalar;
    }

    /**
     * @brief Multiplication assignment by a scalar.
     *
     * @tparam T The type of the scalar.
     * @param scalar The scalar to multiply by.
     * @return A reference to the modified Derived_T after multiplication.
     */
    template <typename T>
        requires(IsScalarThatCanMultiply<T, Elements_T...> && (std::is_arithmetic_v<T> || std::is_same_v<T, Unitless>))
    inline constexpr Derived_T& operator*=(const T& scalar)
    {
        _elements *= scalar;
        return static_cast<Derived_T&>(*this);
    }

    /**
     * @brief Division by a scalar.
     *
     * @tparam T The type of the scalar.
     * @param scalar The scalar to divide by.
     * @return A new Derived_T representing the result of the division.
     */
    template <typename T>
        requires(IsScalarThatCanDivide<T, Elements_T...> && (std::is_arithmetic_v<T> || std::is_same_v<T, Unitless>))
    inline constexpr Derived_T operator/(const T& scalar) const
    {
        return Derived_T{ _elements / scalar };
    }

    template <typename T>
        requires(IsScalarThatCanDivide<T, Elements_T...> && !std::is_arithmetic_v<T> && !std::is_same_v<T, Unitless>)
    inline constexpr auto operator/(const T& scalar) const
    {
        return _elements / scalar;
    }

    /**
     * @brief Division assignment by a scalar.
     *
     * @tparam T The type of the scalar.
     * @param scalar The scalar to divide by.
     * @return A reference to the modified Derived_T after division.
     */
    template <typename T>
        requires(IsScalarThatCanDivide<T, Elements_T...> && (std::is_arithmetic_v<T> || std::is_same_v<T, Unitless>))
    inline constexpr Derived_T& operator/=(const T& scalar)
    {
        _elements /= scalar;
        return static_cast<Derived_T&>(*this);
    }

    /**
     * @brief Dot product between compatible Derived_Ts.
     *
     * @tparam n_row_u The number of rows in the other array.
     * @tparam n_col_u The number of columns in the other array.
     * @tparam elements_u The types of the elements in the other array.
     * @param other The other Derived_T to compute the dot product with.
     * @return The result of the dot product.
     */
    template <typename Derived_U>
    inline constexpr auto dot(const Derived_U& other) const
    {
        return _elements.dot(other._elements);
    }

    /**
     * @brief Transpose of the Derived_T.
     *
     * @return A new Derived_T representing the transpose of the original array.
     */
    inline constexpr auto transpose() const { return _elements.transpose(); }

    /**
     * @brief Convert the Derived_T to a raw ElementMatrix.
     *
     * @return An ElementMatrix containing the elements of the array.
     */
    inline constexpr auto force_to_element_array() const { return _elements; }

    /**
     * @brief Convert the Derived_T to a raw tuple.
     *
     * @return A tuple containing the elements of the array.
     */
    inline constexpr typename ArrayType::TupleType force_to_tuple() const { return _elements.to_tuple(); }

    /**
     * @brief Flatten the Derived_T to a 1D vector of doubles.
     *
     * @return A std::vector<double> representing the flattened version of the original array.
     */
    inline constexpr auto force_to_double_vector() const { return _elements.force_to_double_vector(); }

    /**
     * @brief Create a Derived_T from a std::vector of doubles.
     *
     * @param vec The std::vector<double> to convert.
     * @return A new Derived_T representing the elements in the vector.
     */
    inline constexpr static Derived_T from_double_vector(const std::vector<double>& vec)
    {
        return Derived_T{ ArrayType::from_double_vector(vec) };
    }

    /**
     * @brief Interpolates between two AngularElementsInterface states at a given time.
     *
     * @param thisTime Time of the current state
     * @param otherTime Time of the other state
     * @param other Other AngularElementsInterface state to interpolate with
     * @param targetTime Target time for interpolation
     * @return AngularElementsInterface Interpolated AngularElementsInterface state at the target time.
     */
    inline constexpr Derived_T interpolate(const Time& thisTime, const Time& otherTime, const Derived_T& other, const Time& targetTime) const
    {
        const std::array<Time, 2> times = { thisTime, otherTime };

        using Type0 = std::remove_cvref_t<decltype(get<0>())>;
        using Type1 = std::remove_cvref_t<decltype(get<1>())>;
        using Type2 = std::remove_cvref_t<decltype(get<2>())>;

        auto retval = Derived_T{};
        retval.template get<0>() = math::fast_interpolate<Time, Type0>(times, { get<0>(), other.template get<0>() }, targetTime);
        retval.template get<1>() = math::fast_interpolate<Time, Type1>(times, { get<1>(), other.template get<1>() }, targetTime);
        retval.template get<2>() = math::fast_interpolate<Time, Type2>(times, { get<2>(), other.template get<2>() }, targetTime);
        return retval;
    }

  protected:
    ArrayType _elements; //!< The underlying Derived_T representing the orbital elements.
};

} // namespace astro
} // namespace astrea
