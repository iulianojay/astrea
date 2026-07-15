/**
 * @file element_matrix_concepts.hpp
 * @author Jay Iuliano (iuliano.jay@gmail.com)
 * @brief Header file for the ElementMatrix concepts
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
 * @brief Concept to check if two ElementMatrixs have the same element types.
 *
 * @tparam elements The types of the elements in the first ElementMatrix.
 * @tparam elements_u The types of the elements in the second ElementMatrix.
 */
template <typename... elements, typename... elements_u>
concept IsSameElementMatrix = (std::is_same_v<elements, elements_u> && ...);

/**
 * @brief Forward declaration of the ElementMatrix class template.
 */
template <std::size_t n_row, std::size_t n_col, typename... elements>
struct ElementMatrix;

/**
 * @brief Helper struct to determine if two ElementMatrixs are compatible for operations.
 *
 * @tparam T1 The first ElementMatrix type.
 * @tparam T2 The second ElementMatrix type.
 */
template <typename T1, typename T2>
struct IsCompatibleElementMatrixImpl : std::false_type {};

/**
 * @brief Specialization of IsCompatibleElementMatrixImpl for two ElementMatrixs.
 *
 * @tparam n_row The number of rows in the first ElementMatrix.
 * @tparam n_col The number of columns in the first ElementMatrix.
 * @tparam n_row_u The number of rows in the second ElementMatrix.
 * @tparam n_col_u The number of columns in the second ElementMatrix.
 * @tparam elements The types of the elements in the first ElementMatrix.
 * @tparam elements_u The types of the elements in the second ElementMatrix.
 */
template <std::size_t n_row, std::size_t n_col, std::size_t n_row_u, std::size_t n_col_u, typename... elements, typename... elements_u>
    requires(sizeof...(elements) == sizeof...(elements_u) || n_col == n_row_u)
struct IsCompatibleElementMatrixImpl<ElementMatrix<n_row, n_col, elements...>, ElementMatrix<n_row_u, n_col_u, elements_u...>>
    : std::bool_constant<(std::is_convertible_v<elements, elements_u> && ...)> {};

/**
 * @brief Concept to check if two ElementMatrixs are compatible for operations.
 *
 * @tparam T1 The first ElementMatrix type.
 * @tparam T2 The second ElementMatrix type.
 */
template <typename T1, typename T2>
concept IsCompatibleElementMatrix = IsCompatibleElementMatrixImpl<T1, T2>::value;

/**
 * @brief Helper struct to check if a type is an ElementMatrix.
 *
 * @tparam T The type to check.
 */
template <typename T>
struct IsElementMatrixT : std::false_type {};

/**
 * @brief Specialization of IsElementMatrixT for ElementMatrix types.
 *
 * @tparam R The number of rows in the ElementMatrix.
 * @tparam C The number of columns in the ElementMatrix.
 * @tparam Es The types of the elements in the ElementMatrix.
 */
template <std::size_t R, std::size_t C, typename... Es>
struct IsElementMatrixT<ElementMatrix<R, C, Es...>> : std::true_type {};

/**
 * @brief Concept to check if a type is not an ElementMatrix.
 *
 * @tparam T The type to check.
 */
template <typename T>
concept NotElementMatrix = !IsElementMatrixT<T>::value;

/**
 * @brief Concept to check if a scalar can multiply with the elements of an ElementMatrix.
 *
 * @tparam T The type of the scalar.
 * @tparam elements The types of the elements in the ElementMatrix.
 */
template <typename T, typename... elements>
concept IsScalarThatCanMultiply =
    NotElementMatrix<T> &&
    (std::is_arithmetic_v<T> || ((requires { elements{} * T{}; } || requires { T{} * elements{}; }) && ...));

/**
 * @brief Concept to check if a scalar can divide the elements of an ElementMatrix.
 *
 * @tparam T The type of the scalar.
 * @tparam elements The types of the elements in the ElementMatrix.
 */
template <typename T, typename... elements>
concept IsScalarThatCanDivide =
    NotElementMatrix<T> &&
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
 * @brief Concept to check if an ElementMatrix is a vector (either a row or column vector).
 *
 * @tparam n_row The number of rows in the ElementMatrix.
 * @tparam n_col The number of columns in the ElementMatrix.
 */
template <std::size_t n_row, std::size_t n_col>
concept IsElementVector = (n_row == 1 || n_col == 1);

} // namespace astro
} // namespace astrea