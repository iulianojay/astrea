/**
 * @file OrbitalElementsTemp.hpp
 * @author Jay Iuliano (iuliano.jay@gmail.com)
 * @brief This file defines the OrbitalElementsTemp class and its associated methods.
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

#include <astro/frames.hpp>
#include <astro/state/framework/ElementArray.hpp>

namespace astrea {
namespace astro {

template <typename T>
concept IsOrbitalElementsTemp = requires {
    typename T::ArrayType;
    typename T::orbital_elements_temp_tag;
};

template <typename Derived_T, typename Derived_U>
concept IsCompatibleOrbitalElementsTemp =
    IsOrbitalElementsTemp<Derived_T> && IsOrbitalElementsTemp<Derived_U> &&
    IsCompatibleElementArray<typename Derived_T::ArrayType, typename Derived_U::ArrayType> &&
    equivalent(Derived_T::frame, Derived_U::frame);

template <typename Derived_T, IsFrame auto _frame_, typename... Elements_T>
class OrbitalElementsTemp {
  public:
    using orbital_elements_temp_tag = void; //!< Tag type used by IsOrbitalElementsTemp concept detection.
    using ArrayType = ElementArray<sizeof...(Elements_T), 1, Elements_T...>; //!< The underlying array type representing the orbital elements.

    static constexpr auto frame = _frame_; //!< The reference frame of the OrbitalElementsTemp.

    /**
     * @brief Default constructor for OrbitalElementsTemp.
     *
     * Initializes the OrbitalElementsTemp with default values.
     */
    OrbitalElementsTemp() = default;

    /**
     * @brief Constructor for OrbitalElementsTemp with specified elements.
     *
     * @param elements The elements to initialize the OrbitalElementsTemp with.
     */
    OrbitalElementsTemp(const Elements_T&... elements) :
        elements(elements...)
    {
    }

    /**
     * @brief Constructor for OrbitalElementsTemp with an existing array of elements.
     *
     * @param elements The array of elements to initialize the OrbitalElementsTemp with.
     */
    OrbitalElementsTemp(const ArrayType& elements) :
        elements(elements)
    {
    }

    /**
     * @brief Constructor for OrbitalElementsTemp by moving an existing array of elements.
     *
     * @param elements The array of elements to move into the OrbitalElementsTemp.
     */
    OrbitalElementsTemp(ArrayType&& elements) :
        elements(std::move(elements))
    {
    }

    /**
     * @brief Virtual destructor for OrbitalElementsTemp.
     */
    virtual ~OrbitalElementsTemp() = default;

    /**
     * @brief Copy assignment operator for the Derived_T.
     *
     * @param other The Derived_T to copy from.
     * @return A reference to the assigned Derived_T.
     */
    Derived_T& operator=(const Derived_T& other)
    {
        elements = other.elements;
        return static_cast<Derived_T&>(*this);
    }

    /**
     * @brief Move assignment operator for the Derived_T.
     *
     * @param other The Derived_T to move from.
     * @return A reference to the assigned Derived_T.
     */
    Derived_T& operator=(Derived_T&& other) noexcept
    {
        elements = std::move(other.elements);
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
        requires(IsCompatibleOrbitalElementsTemp<Derived_T, Derived_U>)
    Derived_T& operator=(const Derived_U& other)
    {
        elements = other.elements;
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
        requires(IsCompatibleOrbitalElementsTemp<Derived_T, Derived_U>)
    Derived_T& operator=(Derived_U&& other) noexcept
    {
        elements = std::move(other.elements);
        return static_cast<Derived_T&>(*this);
    }

    /**
     * @brief Access an element of the array by its flat index.
     *
     * @tparam idx The flat index of the element to access.
     * @return The element at the specified index.
     */
    template <std::size_t idx>
    inline constexpr auto get() const
    {
        return elements.template get<idx>();
    }

    /**
     * @brief Addition between equivalent Derived_Ts.
     *
     * @tparam elements_u The types of the elements in the other array.
     * @param other The other Derived_T to add.
     * @return A new Derived_T representing the sum of the two arrays.
     */
    template <typename Derived_U>
        requires(IsCompatibleOrbitalElementsTemp<Derived_T, Derived_U>)
    inline constexpr Derived_T operator+(const Derived_U& other) const
    {
        return { elements + other.elements };
    }

    /**
     * @brief Addition assignment between equivalent Derived_Ts.
     *
     * @tparam elements_u The types of the elements in the other array.
     * @param other The other Derived_T to add.
     * @return A reference to the modified Derived_T after addition.
     */
    template <typename Derived_U>
        requires(IsCompatibleOrbitalElementsTemp<Derived_T, Derived_U>)
    inline constexpr Derived_T& operator+=(const Derived_U& other)
    {
        elements += other.elements;
        return static_cast<Derived_T&>(*this);
    }

    /**
     * @brief Unary negation of the Derived_T.
     *
     * @return A new Derived_T with all elements negated.
     */
    inline constexpr Derived_T operator-() const { return { -elements }; }

    /**
     * @brief Subtraction between equivalent Derived_Ts.
     *
     * @tparam elements_u The types of the elements in the other array.
     * @param other The other Derived_T to subtract.
     * @return A new Derived_T representing the difference of the two arrays.
     */
    template <typename Derived_U>
        requires(IsCompatibleOrbitalElementsTemp<Derived_T, Derived_U>)
    inline constexpr Derived_T operator-(const Derived_U& other) const
    {
        return { elements - other.elements };
    }

    /**
     * @brief Subtraction assignment between equivalent Derived_Ts.
     *
     * @tparam elements_u The types of the elements in the other array.
     * @param other The other Derived_T to subtract.
     * @return A reference to the modified Derived_T after subtraction.
     */
    template <typename Derived_U>
        requires(IsCompatibleOrbitalElementsTemp<Derived_T, Derived_U>)
    inline constexpr Derived_T& operator-=(const Derived_U& other)
    {
        elements -= other.elements;
        return static_cast<Derived_T&>(*this);
    }

    /**
     * @brief Equality comparison between equivalent Derived_Ts.
     *
     * @tparam elements_u The types of the elements in the other array.
     * @param other The other Derived_T to compare.
     * @return True if all corresponding elements are equal, false otherwise.
     */
    template <typename Derived_U>
        requires(IsCompatibleOrbitalElementsTemp<Derived_T, Derived_U>)
    inline constexpr bool operator==(const Derived_U& other) const
    {
        return elements == other.elements;
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
        return Derived_T{ elements * scalar };
    }

    template <typename T>
        requires(IsScalarThatCanMultiply<T, Elements_T...> && !std::is_arithmetic_v<T> && !std::is_same_v<T, Unitless>)
    inline constexpr auto operator*(const T& scalar) const
    {
        return elements * scalar;
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
        elements *= scalar;
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
        return Derived_T{ elements / scalar };
    }

    template <typename T>
        requires(IsScalarThatCanDivide<T, Elements_T...> && !std::is_arithmetic_v<T> && !std::is_same_v<T, Unitless>)
    inline constexpr auto operator/(const T& scalar) const
    {
        return elements / scalar;
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
        elements /= scalar;
        return static_cast<Derived_T&>(*this);
    }

    /**
     * @brief Matrix multiplication between compatible Derived_Ts.
     *
     * @tparam n_row_u The number of rows in the other array.
     * @tparam n_col_u The number of columns in the other array.
     * @tparam elements_u The types of the elements in the other array.
     * @param other The other Derived_T to multiply with.
     * @return A new Derived_T representing the result of the matrix multiplication.
     */
    template <typename Derived_U>
    inline constexpr auto operator*(const Derived_U& other) const
    {
        return elements * other.elements;
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
        return elements.dot(other.elements);
    }

    /**
     * @brief Transpose of the Derived_T.
     *
     * @return A new Derived_T representing the transpose of the original array.
     */
    inline constexpr auto transpose() const { return elements.transpose(); }

    /**
     * @brief Convert the Derived_T to a tuple.
     *
     * @return A tuple containing the elements of the array.
     */
    inline constexpr typename ArrayType::tuple_type to_tuple() const { return elements.to_tuple(); }

    /**
     * @brief Force the Derived_T to a std::array of doubles.
     *
     * @return A std::array containing the numerical values of the elements in the array.
     *
     * @note This function is only defined for uniform element arrays.
     */
    inline constexpr auto force_to_double_array() const { return elements.force_to_double_array(); }

  protected:
    ArrayType elements; //!< The underlying Derived_T representing the orbital elements.
};

template <IsFrame auto _frame_>
class KeplerianTemp
    : public OrbitalElementsTemp<KeplerianTemp<_frame_>, _frame_, Distance, Unitless, Angle, Angle, Angle, Angle> {};

} // namespace astro
} // namespace astrea