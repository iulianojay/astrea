/**
 * @file concepts.hpp
 * @author Jay Iuliano (iuliano.jay@gmail.com)
 * @brief Concept definitions for astrodynamics.
 * @date 2025-10-09
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

#include <concepts>

#include <astro/types/enums.hpp>
#include <astro/types/type_traits.hpp>
#include <astro/types/typedefs.hpp>

namespace astrea {
namespace astro {

/**
 * @brief Concept to check if a type can be constructed from a set of orbital elements.
 *
 * @tparam T The type to check.
 * @tparam U The type to construct from.
 */
template <typename T, typename U>
concept IsConstructableTo = requires(T elements, const GravParam& mu) {
    { U(elements, mu) };
};

/**
 * @brief Concept to check if a type can be converted to Cartesian elements.
 *
 * @tparam T The type to check.
 * @tparam Frame_T The frame type to check.
 */
template <typename T, typename Frame_T>
concept HasDirectCartesianConversion = requires(const T elements, const GravParam& mu) {
    { elements.to_cartesian(mu) } -> std::same_as<Cartesian<Frame_T>>;
};

/**
 * @brief Concept to check if a type can be converted to Keplerian elements.
 *
 * @tparam T The type to check.
 */
template <typename T>
concept HasDirectKeplerianConversion = requires(const T elements, const GravParam& mu) {
    { elements.to_keplerian(mu) } -> std::same_as<Keplerian>;
};

/**
 * @brief Concept to check if a type can be converted to Equinoctial elements.
 *
 * @tparam T The type to check.
 */
template <typename T>
concept HasDirectEquinoctialConversion = requires(const T elements, const GravParam& mu) {
    { elements.to_equinoctial(mu) } -> std::same_as<Equinoctial>;
};

/**
 * @brief Concept to check if a type can be converted to Cartesian elements.
 *
 * @tparam T The type to check.
 */
template <typename T>
concept HasIterpolate =
    requires(const T elements, const Time& thisTime, const Time& otherTime, const T& other, const GravParam& mu, const Time& targetTime) {
        { elements.interpolate(thisTime, otherTime, other, mu, targetTime) } -> std::same_as<T>;
    };

/**
 * @brief Concept to check if a type can be converted to a vector of Unitless.
 *
 * @tparam T The type to check.
 */
template <typename T>
concept HasToVector = requires(const T elements) {
    { elements.force_to_vector() } -> std::same_as<std::vector<Unitless>>;
};

/**
 * @brief Concept to check if a type has mathematical operators defined.
 *
 * @tparam T The type to check.
 */
template <typename T>
concept HasMathOperators = requires(const T elements, const T other, const Unitless scalar) {
    { elements + other } -> std::same_as<T>;
    { elements - other } -> std::same_as<T>;
    { elements * scalar } -> std::same_as<T>;
    { elements / scalar } -> std::same_as<T>;
};

/**
 * @brief Concept to check if a type has in-place mathematical operators defined.
 *
 * @tparam T The type to check.
 */
template <typename T>
concept HasInPlaceMathOperators = requires(T elements, const T other, const Unitless scalar) {
    { elements += other };
    { elements -= other };
    { elements *= scalar };
    { elements /= scalar };
};


/**
 * @brief Concept to check if a type has a method to get the event name.
 *
 * @tparam T The type to check.
 */
template <typename T>
concept HasGetName = requires(const T event) {
    { event.get_name() } -> std::same_as<std::string>;
};

} // namespace astro
} // namespace astrea