/**
 * @file ElementArray.hpp
 * @author Jay Iuliano (iuliano.jay@gmail.com)
 * @brief Header file for the ElementArray module
 * @date 2026-06-01
 *
 * @copyright Copyright (c) 2026 Jay Iuliano
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

#include <cmath>
#include <tuple>
#include <type_traits>
#include <utility>

#include <mp-units/framework/quantity_concepts.h>
#include <mp-units/math.h>

#include <astro/state/framework/element_array_concepts.hpp>

namespace astrea {
namespace astro {

/**
 * @brief A class representing a heterogeneous array of elements, which can be used to represent various state vectors in astrodynamics.
 *
 * @tparam _n_row_ The number of rows in the array.
 * @tparam _n_col_ The number of columns in the array.
 * @tparam Elements_T The types of the elements in the array.
 *
 * @note This is frame unaware and meant to be used as a base class for frame aware state vectors.
 */
template <std::size_t _n_row_, std::size_t _n_col_, typename... Elements_T>
struct ElementArray {

    using base_type = ElementArray<_n_row_, _n_col_, Elements_T...>; //!< The base type of the ElementArray for introspection
    using tuple_type = std::tuple<Elements_T...>;                    //!< The underlying tuple type of the ElementArray

    template <mp_units::Quantity Partial_T>
    using partial_in =
        ElementArray<_n_row_, _n_col_, decltype(Elements_T{} / Partial_T{})...>; //!< Partial of array w.r.t input quantity

    static constexpr std::size_t n_row = _n_row_;               //!< The number of rows in the array
    static constexpr std::size_t n_col = _n_col_;               //!< The number of columns in the array
    static constexpr std::size_t size  = sizeof...(Elements_T); //!< The total number of elements in the array
    static constexpr std::pair<std::size_t, std::size_t> shape{ n_row, n_col }; //!< The shape of the array as a pair of (n_row, n_col)

    static constexpr bool _is_quantity_array = mp_units::Quantity<std::tuple_element_t<0, std::tuple<Elements_T...>>>; //!< Whether the array is a quantity array (all elements are quantities)

    static_assert(size == n_row * n_col, "The number of elements must equal n_row * n_col");

    std::tuple<Elements_T...> elements; //!< The underlying tuple of elements in the array

    /**
     * @brief Default constructor for the ElementArray.
     */
    ElementArray() = default;

    /**
     * @brief Constructor for the ElementArray that takes individual elements as arguments.
     *
     * @param elements The individual elements to initialize the array with.
     */
    ElementArray(const Elements_T&... elements) :
        elements(elements...)
    {
    }

    /**
     * @brief Copy constructor for the ElementArray.
     *
     * @param other The ElementArray to copy from.
     */
    ElementArray(const ElementArray& other) = default;

    /**
     * @brief Move constructor for the ElementArray.
     *
     * @param other The ElementArray to move from.
     */
    ElementArray(ElementArray&& other) noexcept = default;

    /**
     * @brief Virtual destructor for the ElementArray.
     */
    ~ElementArray() = default;

    /**
     * @brief Copy assignment operator for the ElementArray.
     *
     * @param other The ElementArray to copy from.
     * @return A reference to the assigned ElementArray.
     */
    ElementArray& operator=(const ElementArray& other) = default;

    /**
     * @brief Move assignment operator for the ElementArray.
     *
     * @param other The ElementArray to move from.
     * @return A reference to the assigned ElementArray.
     */
    ElementArray& operator=(ElementArray&& other) noexcept = default;

    /**
     * @brief Copy constructor for compatible ElementArrays.
     *
     * @tparam elements_u The types of the elements in the other ElementArray.
     * @param other The ElementArray to copy from.
     */
    template <typename... elements_u>
        requires(IsCompatibleElementArray<base_type, ElementArray<_n_row_, _n_col_, elements_u...>>)
    ElementArray(const ElementArray<_n_row_, _n_col_, elements_u...>& other) :
        elements(other.elements)
    {
    }

    /**
     * @brief Move constructor for compatible ElementArrays.
     *
     * @tparam elements_u The types of the elements in the other ElementArray.
     * @param other The ElementArray to move from.
     */
    template <typename... elements_u>
        requires(IsCompatibleElementArray<base_type, ElementArray<_n_row_, _n_col_, elements_u...>>)
    ElementArray(ElementArray<_n_row_, _n_col_, elements_u...>&& other) noexcept :
        elements(std::move(other.elements))
    {
    }

    /**
     * @brief Copy assignment operator for compatible ElementArrays.
     *
     * @tparam elements_u The types of the elements in the other ElementArray.
     * @param other The ElementArray to copy from.
     * @return A reference to the assigned ElementArray.
     */
    template <typename... elements_u>
        requires(IsCompatibleElementArray<base_type, ElementArray<_n_row_, _n_col_, elements_u...>>)
    ElementArray& operator=(const ElementArray<_n_row_, _n_col_, elements_u...>& other)
    {
        elements = other.elements;
        return *this;
    }

    /**
     * @brief Move assignment operator for compatible ElementArrays.
     *
     * @tparam elements_u The types of the elements in the other ElementArray.
     * @param other The ElementArray to move from.
     * @return A reference to the assigned ElementArray.
     */
    template <typename... elements_u>
        requires(IsCompatibleElementArray<base_type, ElementArray<_n_row_, _n_col_, elements_u...>>)
    ElementArray& operator=(ElementArray<_n_row_, _n_col_, elements_u...>&& other) noexcept
    {
        elements = std::move(other.elements);
        return *this;
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
        return std::get<idx>(elements);
    }

    /**
     * @brief Access an element of the array by its row and column indices.
     *
     * @tparam row The row index of the element to access.
     * @tparam col The column index of the element to access.
     * @return The element at the specified row and column.
     */
    template <std::size_t row, std::size_t col>
    inline constexpr auto get() const
    {
        static_assert(row < n_row, "Row index out of bounds");
        static_assert(col < n_col, "Column index out of bounds");
        return std::get<row * n_col + col>(elements);
    }

    /**
     * @brief Get a specific row of the array as a new ElementArray.
     *
     * @tparam row The index of the row to retrieve.
     * @return An ElementArray representing the specified row.
     *
     * @note This returned value is NOT a reference to the original array, but a new ElementArray containing the elements of the specified row.
     */
    template <std::size_t row>
    inline constexpr auto get_row() const
    {
        static_assert(row < n_row, "Row index out of bounds");

        const auto& [... a] = elements;
        return [&]<std::size_t... colIdx>(std::index_sequence<colIdx...>) {
            return ElementArray<1, _n_col_, decltype(a...[row * _n_col_ + colIdx])...>{ a...[row * _n_col_ + colIdx]... };
        }(std::make_index_sequence<_n_col_>{});
    }

    /**
     * @brief Get a specific column of the array as a new ElementArray.
     *
     * @tparam col The index of the column to retrieve.
     * @return An ElementArray representing the specified column.
     *
     * @note This returned value is NOT a reference to the original array, but a new ElementArray containing the elements of the specified column.
     */
    template <std::size_t col>
    inline constexpr auto get_col() const
    {
        static_assert(col < n_col, "Column index out of bounds");

        const auto& [... a] = elements;
        return [&]<std::size_t... rowIdx>(std::index_sequence<rowIdx...>) {
            return ElementArray<_n_row_, 1, decltype(a...[rowIdx * _n_col_ + col])...>{ a...[rowIdx * _n_col_ + col]... };
        }(std::make_index_sequence<_n_row_>{});
    }

    /**
     * @brief Get a submatrix of the array as a new ElementArray.
     *
     * @tparam row0 The starting row index (inclusive) of the submatrix.
     * @tparam rowf The ending row index (exclusive) of the submatrix.
     * @tparam col0 The starting column index (inclusive) of the submatrix.
     * @tparam colf The ending column index (exclusive) of the submatrix.
     * @return An ElementArray representing the specified submatrix.
     *
     * @note This returned value is NOT a reference to the original array, but a new ElementArray containing the elements of the specified submatrix.
     */
    template <std::size_t row0, std::size_t rowf, std::size_t col0, std::size_t colf>
    inline constexpr auto get_submatrix() const
    {
        static_assert(row0 < rowf && rowf <= n_row, "Row indices out of bounds");
        static_assert(col0 < colf && colf <= n_col, "Column indices out of bounds");

        return [&]<std::size_t... idx>(std::index_sequence<idx...>) {
            return ElementArray<rowf - row0, colf - col0, decltype(std::get<(row0 + idx / (colf - col0)) * _n_col_ + (col0 + idx % (colf - col0))>(elements))...>{
                std::get<(row0 + idx / (colf - col0)) * _n_col_ + (col0 + idx % (colf - col0))>(elements)...
            };
        }(std::make_index_sequence<(rowf - row0) * (colf - col0)>{});
    }

    /**
     * @brief Addition between equivalent ElementArrays.
     *
     * @tparam elements_u The types of the elements in the other array.
     * @param other The other ElementArray to add.
     * @return A new ElementArray representing the sum of the two arrays.
     */
    template <typename... elements_u>
        requires(IsCompatibleElementArray<base_type, ElementArray<_n_row_, _n_col_, elements_u...>>)
    inline constexpr ElementArray operator+(const ElementArray<_n_row_, _n_col_, elements_u...>& other) const
    {
        const auto& [... a] = elements;
        const auto& [... b] = other.elements;
        return ElementArray{ (a + b)... };
    }

    /**
     * @brief Addition assignment between equivalent ElementArrays.
     *
     * @tparam elements_u The types of the elements in the other array.
     * @param other The other ElementArray to add.
     * @return A reference to the modified ElementArray after addition.
     */
    template <typename... elements_u>
        requires(IsCompatibleElementArray<base_type, ElementArray<_n_row_, _n_col_, elements_u...>>)
    inline constexpr ElementArray& operator+=(const ElementArray<_n_row_, _n_col_, elements_u...>& other)
    {
        return *this = *this + other;
    }

    /**
     * @brief Unary negation of the ElementArray.
     *
     * @return A new ElementArray with all elements negated.
     */
    inline constexpr ElementArray operator-() const
    {
        const auto& [... a] = elements;
        return ElementArray{ (-a)... };
    }

    /**
     * @brief Subtraction between equivalent ElementArrays.
     *
     * @tparam elements_u The types of the elements in the other array.
     * @param other The other ElementArray to subtract.
     * @return A new ElementArray representing the difference of the two arrays.
     */
    template <typename... elements_u>
        requires(IsCompatibleElementArray<base_type, ElementArray<_n_row_, _n_col_, elements_u...>>)
    inline constexpr ElementArray operator-(const ElementArray<_n_row_, _n_col_, elements_u...>& other) const
    {
        const auto& [... a] = elements;
        const auto& [... b] = other.elements;
        return ElementArray{ (a - b)... };
    }

    /**
     * @brief Subtraction assignment between equivalent ElementArrays.
     *
     * @tparam elements_u The types of the elements in the other array.
     * @param other The other ElementArray to subtract.
     * @return A reference to the modified ElementArray after subtraction.
     */
    template <typename... elements_u>
        requires(IsCompatibleElementArray<base_type, ElementArray<_n_row_, _n_col_, elements_u...>>)
    inline constexpr ElementArray& operator-=(const ElementArray<_n_row_, _n_col_, elements_u...>& other)
    {
        return *this = *this - other;
    }

    /**
     * @brief Equality comparison between equivalent ElementArrays.
     *
     * @tparam elements_u The types of the elements in the other array.
     * @param other The other ElementArray to compare.
     * @return True if all corresponding elements are equal, false otherwise.
     */
    template <typename... elements_u>
        requires(IsCompatibleElementArray<base_type, ElementArray<_n_row_, _n_col_, elements_u...>>)
    inline constexpr bool operator==(const ElementArray<_n_row_, _n_col_, elements_u...>& other) const
    {
        const auto& [... a] = elements;
        const auto& [... b] = other.elements;
        return ((a == b) && ...);
    }

    /**
     * @brief Inequality comparison between equivalent ElementArrays.
     *
     * @tparam elements_u The types of the elements in the other array.
     * @param other The other ElementArray to compare.
     * @return True if any corresponding elements are not equal, false otherwise.
     */
    template <typename T>
        requires(IsScalarThatCanMultiply<T, Elements_T...>)
    inline constexpr auto operator*(const T& scalar) const
    {
        const auto& [... a] = elements;
        return ElementArray<_n_row_, _n_col_, decltype(a * scalar)...>{ (a * scalar)... };
    }

    /**
     * @brief Multiplication assignment by a scalar.
     *
     * @tparam T The type of the scalar.
     * @param scalar The scalar to multiply by.
     * @return A reference to the modified ElementArray after multiplication.
     */
    template <typename T>
        requires(IsScalarThatCanMultiply<T, Elements_T...> && (std::is_arithmetic_v<T> || std::is_same_v<T, Unitless>))
    inline constexpr ElementArray& operator*=(const T& scalar)
    {
        return *this = *this * scalar;
    }

    /**
     * @brief Division by a scalar.
     *
     * @tparam T The type of the scalar.
     * @param scalar The scalar to divide by.
     * @return A new ElementArray representing the result of the division.
     */
    template <typename T>
        requires(IsScalarThatCanDivide<T, Elements_T...>)
    inline constexpr auto operator/(const T& scalar) const
    {
        const auto& [... a] = elements;
        return ElementArray<_n_row_, _n_col_, decltype(a / scalar)...>{ (a / scalar)... };
    }

    /**
     * @brief Division assignment by a scalar.
     *
     * @tparam T The type of the scalar.
     * @param scalar The scalar to divide by.
     * @return A reference to the modified ElementArray after division.
     */
    template <typename T>
        requires(IsScalarThatCanDivide<T, Elements_T...> && (std::is_arithmetic_v<T> || std::is_same_v<T, Unitless>))
    inline constexpr ElementArray& operator/=(const T& scalar)
    {
        return *this = *this / scalar;
    }

    /**
     * @brief Matrix multiplication between compatible ElementArrays.
     *
     * @tparam n_row_u The number of rows in the other array.
     * @tparam n_col_u The number of columns in the other array.
     * @tparam elements_u The types of the elements in the other array.
     * @param other The other ElementArray to multiply with.
     * @return A new ElementArray representing the result of the matrix multiplication.
     */
    template <std::size_t n_row_u, std::size_t n_col_u, typename... elements_u>
        requires(_n_col_ == n_row_u)
    inline constexpr auto operator*(const ElementArray<n_row_u, n_col_u, elements_u...>& other) const
    {
        const auto& [... a] = elements;
        const auto& [... b] = other.elements;

        // Compute one result element at flat index (= row * n_col_u + col)
        // by summing over the k inner-dimension index.
        auto dot = [&]<std::size_t flatIdx>(std::integral_constant<std::size_t, flatIdx>) {
            return [&]<std::size_t... innerDimIdx>(std::index_sequence<innerDimIdx...>) {
                return ((a...[flatIdx / n_col_u * _n_col_ + innerDimIdx] * b...[innerDimIdx * n_col_u + flatIdx % n_col_u]) + ...);
            }(std::make_index_sequence<_n_col_>{});
        };

        return [&]<std::size_t... resultIdx>(std::index_sequence<resultIdx...>) {
            using result_type =
                ElementArray<_n_row_, n_col_u, decltype(dot(std::integral_constant<std::size_t, resultIdx>{}))...>;
            return result_type{ dot(std::integral_constant<std::size_t, resultIdx>{})... };
        }(std::make_index_sequence<_n_row_ * n_col_u>{});
    }

    /**
     * @brief Dot product between compatible ElementArrays.
     *
     * @tparam n_row_u The number of rows in the other array.
     * @tparam n_col_u The number of columns in the other array.
     * @tparam elements_u The types of the elements in the other array.
     * @param other The other ElementArray to compute the dot product with.
     * @return The result of the dot product.
     */
    template <std::size_t n_row_u, std::size_t n_col_u, typename... elements_u>
        requires(
            IsElementVector<_n_row_, _n_col_> &&                     // row or column vector
            IsElementVector<n_row_u, n_col_u> &&                     //
            (_n_row_ * _n_col_ == n_row_u * n_col_u) &&              // same size
            IsUniform<base_type> &&                                  // uniform element types
            IsUniform<ElementArray<n_row_u, n_col_u, elements_u...>> //
        )
    inline constexpr auto dot(const ElementArray<n_row_u, n_col_u, elements_u...>& other) const
    {
        const auto& [... a] = elements;
        const auto& [... b] = other.elements;
        return [&]<std::size_t... idx>(std::index_sequence<idx...>) {
            return ((a...[idx] * b...[idx]) + ...);
        }(std::make_index_sequence<size>{});
    }

    /**
     * @brief Transpose of the ElementArray.
     *
     * @return A new ElementArray representing the transpose of the original array.
     */
    inline constexpr auto transpose() const
    {
        const auto& [... a] = elements;
        return [&]<std::size_t... resultIdx>(std::index_sequence<resultIdx...>) {
            using result_type =
                ElementArray<_n_col_, _n_row_, decltype(a...[resultIdx % _n_row_ * _n_col_ + resultIdx / _n_row_])...>;
            return result_type{ a...[resultIdx % _n_row_ * _n_col_ + resultIdx / _n_row_]... };
        }(std::make_index_sequence<size>{});
    }

    /**
     * @brief Determinant of the ElementArray.
     *
     * @return The determinant of the array.
     *
     * @note This function is only defined for square matrices (n_row == n_col).
     */
    inline constexpr auto determinant() const
    {
        static_assert(_n_row_ == _n_col_, "Determinant is only defined for square matrices");

        if constexpr (_n_row_ == 1) { return std::get<0>(elements); }
        else if constexpr (_n_row_ == 2) {
            return std::get<0>(elements) * std::get<3>(elements) - std::get<1>(elements) * std::get<2>(elements);
        }
        else if constexpr (_n_row_ == 3) {
            return std::get<0>(elements) *
                       (std::get<4>(elements) * std::get<8>(elements) - std::get<5>(elements) * std::get<7>(elements)) -
                   std::get<1>(elements) *
                       (std::get<3>(elements) * std::get<8>(elements) - std::get<5>(elements) * std::get<6>(elements)) +
                   std::get<2>(elements) *
                       (std::get<3>(elements) * std::get<7>(elements) - std::get<4>(elements) * std::get<6>(elements));
        }
        else {
            return [&]<std::size_t... rowIdx>(std::index_sequence<rowIdx...>) {
                return (
                    (std::get<rowIdx * _n_col_>(elements) *
                     ElementArray<_n_row_ - 1, _n_col_ - 1, decltype(std::get<rowIdx * _n_col_ + 1>(elements))...>{
                         std::get<rowIdx * _n_col_ + 1>(elements)... } // minor matrix
                         .determinant() *
                     ((rowIdx % 2 == 0) ? 1 : -1)) +
                    ...
                );
            }(std::make_index_sequence<_n_row_>{});
        }
    }

    /**
     * @brief Trace of the ElementArray.
     *
     * @return The trace of the array (sum of diagonal elements).
     *
     * @note This function is only defined for square matrices (n_row == n_col).
     */
    inline constexpr auto trace() const
    {
        static_assert(_n_row_ == _n_col_, "Trace is only defined for square matrices");
        static_assert(IsUniform<base_type>, "Trace is only defined for uniform element arrays");

        const auto& [... a] = elements;
        return [&]<std::size_t... diagIdx>(std::index_sequence<diagIdx...>) {
            return (a...[diagIdx * (_n_col_ + 1)] + ...);
        }(std::make_index_sequence<_n_row_>{});
    }

    /**
     * @brief Norm of the ElementArray (Euclidean norm).
     *
     * @return The Euclidean norm of the array.
     *
     * @note This function is only defined for uniform element arrays.
     */
    inline constexpr auto norm() const
    {
        static_assert(IsUniform<base_type>, "Norm is only defined for uniform element arrays");

        const auto& [... a] = elements;
        if constexpr (_is_quantity_array) { return mp_units::sqrt(((a * a) + ...)); }
        else {
            return std::sqrt(((a * a) + ...));
        }
    }

    /**
     * @brief Norm of the ElementArray raised to a power p.
     *
     * @tparam p The power to which the norm is raised.
     * @return The norm of the array raised to the power p.
     *
     * @note This function is only defined for uniform element arrays.
     */
    template <unsigned p>
    inline constexpr auto norm() const
    {
        static_assert(IsUniform<base_type>, "Norm is only defined for uniform element arrays");

        const auto& [... a] = elements;
        if constexpr (_is_quantity_array) { return mp_units::pow<1, p>((mp_units::pow<p>(a) + ...)); }
        else {
            return std::pow((std::pow(a, static_cast<double>(p)) + ...), 1.0 / static_cast<double>(p));
        }
    }

    /**
     * @brief Convert the ElementArray to a tuple.
     *
     * @return A tuple containing the elements of the array.
     */
    inline constexpr tuple_type to_tuple() const { return elements; }

    /**
     * @brief Flatten the ElementArray to a 1D array.
     *
     * @return A new ElementArray representing the flattened version of the original array.
     */
    inline constexpr auto flatten() const
    {
        const auto& [... a] = elements;
        return ElementArray<1, size, decltype(a)...>{ a... };
    }

    /**
     * @brief Force the ElementArray to a std::array of doubles.
     *
     * @return A std::array containing the numerical values of the elements in the array.
     *
     * @note This function is only defined for uniform element arrays.
     */
    inline constexpr std::array<double, size> force_to_double_array() const
    {
        const auto& [... a] = elements;
        if constexpr (_is_quantity_array) { return std::array<double, size>{ a.numerical_value_in(a.unit)... }; }
        else {
            return std::array<double, size>{ static_cast<double>(a)... };
        }
    }
};

/**
 * @brief Scalar multiplication between a scalar and an ElementArray.
 *
 * @tparam T The type of the scalar.
 * @tparam _n_row_ The number of rows in the ElementArray.
 * @tparam _n_col_ The number of columns in the ElementArray.
 * @tparam Elements_T The types of the elements in the ElementArray.
 * @param scalar The scalar to multiply with.
 * @param arr The ElementArray to multiply.
 * @return A new ElementArray representing the result of the multiplication.
 */
template <typename T, std::size_t _n_row_, std::size_t _n_col_, typename... Elements_T>
    requires(IsScalarThatCanMultiply<T, Elements_T...>)
inline constexpr auto operator*(const T& scalar, const astrea::astro::ElementArray<_n_row_, _n_col_, Elements_T...>& arr)
{
    return arr * scalar;
}

} // namespace astro
} // namespace astrea

namespace std {

/**
 * @brief Specialization of std::tuple_size for ElementArray.
 *
 * @tparam _n_row_ The number of rows in the ElementArray.
 * @tparam _n_col_ The number of columns in the ElementArray.
 * @tparam Elements_T The types of the elements in the ElementArray.
 */
template <std::size_t _n_row_, std::size_t _n_col_, typename... Elements_T>
struct tuple_size<astrea::astro::ElementArray<_n_row_, _n_col_, Elements_T...>>
    : std::integral_constant<std::size_t, sizeof...(Elements_T)> {};

/**
 * @brief Specialization of std::tuple_element for ElementArray.
 *
 * @tparam I The index of the element to access.
 * @tparam _n_row_ The number of rows in the ElementArray.
 * @tparam _n_col_ The number of columns in the ElementArray.
 * @tparam Elements_T The types of the elements in the ElementArray.
 */
template <std::size_t I, std::size_t _n_row_, std::size_t _n_col_, typename... Elements_T>
struct tuple_element<I, astrea::astro::ElementArray<_n_row_, _n_col_, Elements_T...>>
    : std::tuple_element<I, std::tuple<Elements_T...>> {};

} // namespace std