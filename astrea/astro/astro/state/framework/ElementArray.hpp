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

#include <tuple>
#include <type_traits>
#include <utility>
#include <variant>

namespace astrea {
namespace astro {

template <typename... elements, typename... elements_u>
concept IsSameElementArray = (std::is_same_v<elements, elements_u> && ...);

// Forward declaration needed for IsCompatibleElementArrayImpl
template <std::size_t n_row, std::size_t n_col, typename... elements>
struct ElementArray;

template <typename T1, typename T2>
struct IsCompatibleElementArrayImpl : std::false_type {};

template <std::size_t n_row, std::size_t n_col, std::size_t n_row_u, std::size_t n_col_u, typename... elements, typename... elements_u>
    requires(sizeof...(elements) == sizeof...(elements_u) || n_col == n_row_u)
struct IsCompatibleElementArrayImpl<ElementArray<n_row, n_col, elements...>, ElementArray<n_row_u, n_col_u, elements_u...>>
    : std::bool_constant<(std::is_convertible_v<elements, elements_u> && ...)> {};

template <typename T1, typename T2>
concept IsCompatibleElementArray = IsCompatibleElementArrayImpl<T1, T2>::value;

template <typename T>
struct IsElementArrayT : std::false_type {};

template <std::size_t R, std::size_t C, typename... Es>
struct IsElementArrayT<ElementArray<R, C, Es...>> : std::true_type {};

template <typename T>
concept NotElementArray = !IsElementArrayT<T>::value;

template <typename T, typename... elements>
concept IsScalarThatCanMultiply =
    NotElementArray<T> &&
    (std::is_arithmetic_v<T> || ((requires { elements{} * T{}; } || requires { T{} * elements{}; }) && ...));

template <typename T, typename... elements>
concept IsScalarThatCanDivide =
    NotElementArray<T> &&
    (std::is_arithmetic_v<T> || ((requires { elements{} / T{}; } || requires { T{} / elements{}; }) && ...));

template <typename first, typename... rest>
concept IsUniform = std::is_same_v<std::tuple<first, rest...>, std::tuple<rest..., first>>;

template <std::size_t _n_row_, std::size_t _n_col_, typename... _elements_>
struct ElementArray {

    std::tuple<_elements_...> elements;

    using base_type                    = ElementArray<_n_row_, _n_col_, _elements_...>;
    static constexpr std::size_t size  = std::tuple_size_v<std::tuple<_elements_...>>;
    static constexpr std::size_t n_row = _n_row_;
    static constexpr std::size_t n_col = _n_col_;

    static_assert(size == n_row * n_col, "The number of elements must equal n_row * n_col");

    ElementArray() = default;

    ElementArray(const _elements_&... elements) :
        elements(elements...)
    {
    }

    ElementArray(const ElementArray& other) = default;

    ElementArray(ElementArray&& other) noexcept = default;

    ~ElementArray() = default;

    ElementArray& operator=(const ElementArray& other) = default;

    ElementArray& operator=(ElementArray&& other) noexcept = default;

    //----------------------------------------------------
    // Access operators
    //----------------------------------------------------
    template <std::size_t idx>
    constexpr inline auto get() const
    {
        return std::get<idx>(elements);
    }

    template <std::size_t row, std::size_t col>
    constexpr inline auto get() const
    {
        static_assert(row < n_row, "Row index out of bounds");
        static_assert(col < n_col, "Column index out of bounds");
        return std::get<row * n_col + col>(elements);
    }

    template <std::size_t row>
    constexpr inline auto get_row() const
    {
        static_assert(row < n_row, "Row index out of bounds");
        const auto& [... a] = elements;
        return [&]<std::size_t... Cs>(std::index_sequence<Cs...>) {
            return ElementArray<1, _n_col_, decltype(a...[row * _n_col_ + Cs])...>{ a...[row * _n_col_ + Cs]... };
        }(std::make_index_sequence<_n_col_>{});
    }

    template <std::size_t col>
    constexpr inline auto get_col() const
    {
        static_assert(col < n_col, "Column index out of bounds");
        const auto& [... a] = elements;
        return [&]<std::size_t... Rs>(std::index_sequence<Rs...>) {
            return ElementArray<_n_row_, 1, decltype(a...[Rs * _n_col_ + col])...>{ a...[Rs * _n_col_ + col]... };
        }(std::make_index_sequence<_n_row_>{});
    }

    //----------------------------------------------------
    // Addition subtraction between equivalent ElementArrays
    //----------------------------------------------------
    template <typename... elements_u>
        requires IsCompatibleElementArray<base_type, ElementArray<_n_row_, _n_col_, elements_u...>>
    constexpr inline ElementArray operator+(const ElementArray<_n_row_, _n_col_, elements_u...>& other) const
    {
        const auto& [... a] = elements;
        const auto& [... b] = other.elements;
        return ElementArray{ (a + b)... };
    }

    template <typename... elements_u>
        requires IsCompatibleElementArray<base_type, ElementArray<_n_row_, _n_col_, elements_u...>>
    constexpr inline ElementArray& operator+=(const ElementArray<_n_row_, _n_col_, elements_u...>& other)
    {
        return *this = *this + other;
    }

    constexpr inline ElementArray operator-() const
    {
        const auto& [... a] = elements;
        return ElementArray{ (-a)... };
    }

    template <typename... elements_u>
        requires IsCompatibleElementArray<base_type, ElementArray<_n_row_, _n_col_, elements_u...>>
    constexpr inline ElementArray operator-(const ElementArray<_n_row_, _n_col_, elements_u...>& other) const
    {
        const auto& [... a] = elements;
        const auto& [... b] = other.elements;
        return ElementArray{ (a - b)... };
    }

    template <typename... elements_u>
        requires IsCompatibleElementArray<base_type, ElementArray<_n_row_, _n_col_, elements_u...>>
    constexpr inline ElementArray& operator-=(const ElementArray<_n_row_, _n_col_, elements_u...>& other)
    {
        return *this = *this - other;
    }

    //----------------------------------------------------
    // Comparison between equivalent ElementArrays
    //----------------------------------------------------
    template <typename... elements_u>
        requires IsCompatibleElementArray<base_type, ElementArray<_n_row_, _n_col_, elements_u...>>
    constexpr inline bool operator==(const ElementArray<_n_row_, _n_col_, elements_u...>& other) const
    {
        const auto& [... a] = elements;
        const auto& [... b] = other.elements;
        return ((a == b) && ...);
    }

    //----------------------------------------------------
    // Multiplication and division by scalars
    //----------------------------------------------------
    template <typename T>
        requires IsScalarThatCanMultiply<T, _elements_...>
    constexpr inline auto operator*(const T& scalar) const
    {
        const auto& [... a] = elements;
        return ElementArray<_n_row_, _n_col_, decltype(a * scalar)...>{ (a * scalar)... };
    }

    template <typename T>
        requires IsScalarThatCanMultiply<T, _elements_...> && (std::is_arithmetic_v<T> || std::is_same_v<T, Unitless>)
    constexpr inline ElementArray& operator*=(const T& scalar)
    {
        return *this = *this * scalar;
    }

    template <typename T>
        requires IsScalarThatCanDivide<T, _elements_...>
    constexpr inline auto operator/(const T& scalar) const
    {
        const auto& [... a] = elements;
        return ElementArray<_n_row_, _n_col_, decltype(a / scalar)...>{ (a / scalar)... };
    }

    template <typename T>
        requires IsScalarThatCanDivide<T, _elements_...> && (std::is_arithmetic_v<T> || std::is_same_v<T, Unitless>)
    constexpr inline ElementArray& operator/=(const T& scalar)
    {
        return *this = *this / scalar;
    }

    //----------------------------------------------------
    // Matrix multiplication: (n_row x n_col) * (n_col x n_col_u) -> (n_row x n_col_u)
    // Uses C++26 pack indexing to address elements by compile-time row/col arithmetic.
    //----------------------------------------------------
    template <std::size_t n_row_u, std::size_t n_col_u, typename... elements_u>
        requires(_n_col_ == n_row_u)
    constexpr inline auto operator*(const ElementArray<n_row_u, n_col_u, elements_u...>& other) const
    {
        const auto& [... a] = elements;
        const auto& [... b] = other.elements;

        // Compute one result element at flat index ri (= row * n_col_u + col)
        // by summing over the k inner-dimension index Ps.
        auto dot = [&]<std::size_t ri>(std::integral_constant<std::size_t, ri>) {
            return [&]<std::size_t... Ps>(std::index_sequence<Ps...>) {
                return ((a...[ri / n_col_u * _n_col_ + Ps] * b...[Ps * n_col_u + ri % n_col_u]) + ...);
            }(std::make_index_sequence<_n_col_>{});
        };

        return [&]<std::size_t... ResultIs>(std::index_sequence<ResultIs...>) {
            using result_type =
                ElementArray<_n_row_, n_col_u, decltype(dot(std::integral_constant<std::size_t, ResultIs>{}))...>;
            return result_type{ dot(std::integral_constant<std::size_t, ResultIs>{})... };
        }(std::make_index_sequence<_n_row_ * n_col_u>{});
    }
};

template <typename T, std::size_t _n_row_, std::size_t _n_col_, typename... _elements_>
    requires IsScalarThatCanMultiply<T, _elements_...>
constexpr inline auto operator*(const T& scalar, const astrea::astro::ElementArray<_n_row_, _n_col_, _elements_...>& arr)
{
    return arr * scalar;
}

template <typename T, std::size_t _n_row_, std::size_t _n_col_, typename... _elements_>
    requires IsScalarThatCanDivide<T, _elements_...>
constexpr inline auto operator/(const T& scalar, const astrea::astro::ElementArray<_n_row_, _n_col_, _elements_...>& arr)
{
    return arr / scalar;
}

} // namespace astro
} // namespace astrea

namespace std {

template <std::size_t _n_row_, std::size_t _n_col_, typename... _elements_>
struct tuple_size<astrea::astro::ElementArray<_n_row_, _n_col_, _elements_...>>
    : std::integral_constant<std::size_t, sizeof...(_elements_)> {};

template <std::size_t I, std::size_t _n_row_, std::size_t _n_col_, typename... _elements_>
struct tuple_element<I, astrea::astro::ElementArray<_n_row_, _n_col_, _elements_...>>
    : std::tuple_element<I, std::tuple<_elements_...>> {};

} // namespace std