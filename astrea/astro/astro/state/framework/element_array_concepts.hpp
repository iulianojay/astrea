/**
 * @file element_array_concepts.hpp
 * @author Jay Iuliano (iuliano.jay@gmail.com)
 * @brief Header file for the ElementArray concepts
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

namespace astrea {
namespace astro {

/**
 * @brief Concept to check if two ElementArrays have the same element types.
 *
 * @tparam elements The types of the elements in the first ElementArray.
 * @tparam elements_u The types of the elements in the second ElementArray.
 */
template <typename... elements, typename... elements_u>
concept IsSameElementArray = (std::is_same_v<elements, elements_u> && ...);

/**
 * @brief Forward declaration of the ElementArray class template.
 */
template <std::size_t n_row, std::size_t n_col, typename... elements>
struct ElementArray;

/**
 * @brief Helper struct to determine if two ElementArrays are compatible for operations.
 *
 * @tparam T1 The first ElementArray type.
 * @tparam T2 The second ElementArray type.
 */
template <typename T1, typename T2>
struct IsCompatibleElementArrayImpl : std::false_type {};

/**
 * @brief Specialization of IsCompatibleElementArrayImpl for two ElementArrays.
 *
 * @tparam n_row The number of rows in the first ElementArray.
 * @tparam n_col The number of columns in the first ElementArray.
 * @tparam n_row_u The number of rows in the second ElementArray.
 * @tparam n_col_u The number of columns in the second ElementArray.
 * @tparam elements The types of the elements in the first ElementArray.
 * @tparam elements_u The types of the elements in the second ElementArray.
 */
template <std::size_t n_row, std::size_t n_col, std::size_t n_row_u, std::size_t n_col_u, typename... elements, typename... elements_u>
    requires(sizeof...(elements) == sizeof...(elements_u) || n_col == n_row_u)
struct IsCompatibleElementArrayImpl<ElementArray<n_row, n_col, elements...>, ElementArray<n_row_u, n_col_u, elements_u...>>
    : std::bool_constant<(std::is_convertible_v<elements, elements_u> && ...)> {};

/**
 * @brief Concept to check if two ElementArrays are compatible for operations.
 *
 * @tparam T1 The first ElementArray type.
 * @tparam T2 The second ElementArray type.
 */
template <typename T1, typename T2>
concept IsCompatibleElementArray = IsCompatibleElementArrayImpl<T1, T2>::value;

/**
 * @brief Helper struct to check if a type is an ElementArray.
 *
 * @tparam T The type to check.
 */
template <typename T>
struct IsElementArrayT : std::false_type {};

/**
 * @brief Specialization of IsElementArrayT for ElementArray types.
 *
 * @tparam R The number of rows in the ElementArray.
 * @tparam C The number of columns in the ElementArray.
 * @tparam Es The types of the elements in the ElementArray.
 */
template <std::size_t R, std::size_t C, typename... Es>
struct IsElementArrayT<ElementArray<R, C, Es...>> : std::true_type {};

/**
 * @brief Concept to check if a type is not an ElementArray.
 *
 * @tparam T The type to check.
 */
template <typename T>
concept NotElementArray = !IsElementArrayT<T>::value;

/**
 * @brief Concept to check if a scalar can multiply with the elements of an ElementArray.
 *
 * @tparam T The type of the scalar.
 * @tparam elements The types of the elements in the ElementArray.
 */
template <typename T, typename... elements>
concept IsScalarThatCanMultiply =
    NotElementArray<T> &&
    (std::is_arithmetic_v<T> || ((requires { elements{} * T{}; } || requires { T{} * elements{}; }) && ...));

/**
 * @brief Concept to check if a scalar can divide the elements of an ElementArray.
 *
 * @tparam T The type of the scalar.
 * @tparam elements The types of the elements in the ElementArray.
 */
template <typename T, typename... elements>
concept IsScalarThatCanDivide =
    NotElementArray<T> &&
    (std::is_arithmetic_v<T> || ((requires { elements{} / T{}; } || requires { T{} / elements{}; }) && ...));

/**
 * @brief Concept to check if all types in a parameter pack are the same.
 *
 * @tparam first The first type in the parameter pack.
 * @tparam rest The remaining types in the parameter pack.
 */
template <typename first, typename... rest>
concept IsUniform = std::is_same_v<std::tuple<first, rest...>, std::tuple<rest..., first>>;

/**
 * @brief Concept to check if an ElementArray is a vector (either a row or column vector).
 *
 * @tparam n_row The number of rows in the ElementArray.
 * @tparam n_col The number of columns in the ElementArray.
 */
template <std::size_t n_row, std::size_t n_col>
concept IsElementVector = (n_row == 1 || n_col == 1);

} // namespace astro
} // namespace astrea