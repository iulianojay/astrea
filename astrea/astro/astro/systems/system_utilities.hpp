/**
 * @file system_utilities
 * @author Jay Iuliano (iuliano.jay@gmail.com)
 * @brief Header file for the system utilities, which provides helper functions for celestial bodies and their interactions.
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

#include <memory>
#include <ranges>
#include <unordered_set>
#include <vector>

#include <gtl/phmap.hpp>

#include <astro/systems/CelestialBody.hpp>
#include <astro/systems/barycenters.hpp>
#include <astro/systems/celestial_reference_getters.hpp>
#include <astro/systems/planets.hpp>
#include <astro/time/Date.hpp>
#include <astro/types/enums.hpp>
#include <astro/types/type_traits.hpp>


namespace astrea {
namespace astro {

/**
 * @brief Returns true if Ancestor is Body itself or appears anywhere in Body's parent chain.
 */
template <IsOrigin auto ancestor, IsOrigin auto body>
consteval bool is_ancestor_of()
{
    if constexpr (std::is_same_v<decltype(ancestor), decltype(body)>) { return true; }
    else if constexpr (requires { decltype(body)::parent; }) {
        return is_ancestor_of<ancestor, decltype(body)::parent>();
    }
    else {
        return false;
    }
}

/**
 * @brief Returns the single PLANET in the pack (assumes exactly one exists).
 */
template <IsCelestialBody auto first, IsCelestialBody auto... rest>
consteval auto get_planet_from_pack()
{
    if constexpr (get_body_type<first>() == CelestialBodyType::PLANET) { return first; }
    else {
        static_assert(sizeof...(rest) > 0, "no PLANET found in body pack");
        return get_planet_from_pack<rest...>();
    }
}

/**
 * @brief Finds the closest common ancestor of the given celestial bodies.
 *
 * - 1 body      → that body itself.
 * - ≥ 2 planets → SolarSystemBarycenter (the only common ancestor of independent planets).
 * - 1 planet    → that planet if all other bodies are in its sub-hierarchy, else SolarSystemBarycenter.
 * - 0 planets   → SolarSystemBarycenter (conservative fall-back for pure-satellite sets).
 *
 * @tparam Bodies The celestial bodies to consider.
 * @return The common ancestor body value.
 */
template <IsCelestialBody auto... bodies>
consteval auto find_common_ancestor()
{
    if constexpr (sizeof...(bodies) == 1) { return (bodies, ...); }
    else {
        constexpr std::size_t planet_count = ((get_body_type<bodies>() == CelestialBodyType::PLANET ? 1 : 0) + ...);

        if constexpr (planet_count >= 2) { return barycenters::SolarSystemBarycenter; }
        else if constexpr (planet_count == 1) {
            constexpr auto planet = get_planet_from_pack<bodies...>();
            if constexpr ((is_ancestor_of<planet, bodies>() && ...)) { return planet; }
            else {
                return barycenters::SolarSystemBarycenter;
            }
        }
        else {
            return barycenters::SolarSystemBarycenter;
        }
    }
}

/**
 * @brief Get the relative position between two celestial bodies at a specific date.
 *
 * @param date The date at which to get the relative position.
 * @param id1 The ID of the first celestial body.
 * @param id2 The ID of the second celestial body.
 * @return CartesianVector<Distance, frames::solar_system_barycenter::icrf> The relative position vector from id2 to id1.
 */
template <IsCelestialBody auto body1, IsCelestialBody auto body2>
constexpr auto get_relative_position(const Date& date)
{
    static constexpr auto parent1 = decltype(body1)::parent;
    static constexpr auto parent2 = decltype(body2)::parent;

    if constexpr (std::is_same_v<decltype(parent1), decltype(body2)>) { return get_position_at<body1>(date); }
    else if constexpr (std::is_same_v<decltype(parent2), decltype(body1)>) {
        return -get_position_at<body2>(date);
    }
    else {
        static constexpr auto root = find_common_ancestor<body1, body2>();
        const auto pos1            = get_position_relative_to_ancestor<body1, root>(date);
        const auto pos2            = get_position_relative_to_ancestor<body2, root>(date);
        return pos1 - pos2;
    }
}

/**
 * @brief Get the relative position between two celestial bodies at a specific date.
 *
 * @param date The date at which to get the relative position.
 * @param id1 The ID of the first celestial body.
 * @param id2 The ID of the second celestial body.
 * @return CartesianVector<Velocity, frames::solar_system_barycenter::icrf> The relative velocity vector from id2 to id1.
 */
template <IsCelestialBody auto body1, IsCelestialBody auto body2>
constexpr auto get_relative_velocity(const Date& date)
{
    static constexpr auto parent1 = decltype(body1)::parent;
    static constexpr auto parent2 = decltype(body2)::parent;

    if constexpr (std::is_same_v<decltype(parent1), decltype(body2)>) { return get_velocity_at<body1>(date); }
    else if constexpr (std::is_same_v<decltype(parent2), decltype(body1)>) {
        return -get_velocity_at<body2>(date);
    }
    else {
        static constexpr auto root = find_common_ancestor<body1, body2>();
        const auto vel1            = get_velocity_relative_to_ancestor<body1, root>(date);
        const auto vel2            = get_velocity_relative_to_ancestor<body2, root>(date);
        return vel1 - vel2;
    }
}


/**
 * @brief Get the position of a celestial body relative to the root at a specific date.
 *
 * @param date The date at which to get the position.
 * @param id The ID of the celestial body.
 * @return CartesianVector<Distance, frames::solar_system_barycenter::icrf> The position vector of the celestial body relative to the root.
 */
template <IsCelestialBody auto body, IsCelestialBody auto ancestor>
constexpr auto get_position_relative_to_ancestor(const Date& date)
{
    static constexpr auto parent = decltype(body)::parent;
    if constexpr (std::is_same_v<decltype(parent), decltype(ancestor)>) { return get_position_at<body>(date); }
    else {
        return get_position_at<body>(date) + get_position_relative_to_ancestor<parent, ancestor>(date);
    }
}

/**
 * @brief Get the velocity of a celestial body relative to the root at a specific date.
 *
 * @param date The date at which to get the velocity.
 * @param id The ID of the celestial body.
 * @return CartesianVector<Velocity, frames::solar_system_barycenter::icrf> The velocity vector of the celestial body relative to the root.
 */
template <IsCelestialBody auto body, IsCelestialBody auto ancestor>
constexpr auto get_velocity_relative_to_ancestor(const Date& date)
{
    static constexpr auto parent = decltype(body)::parent;
    if constexpr (std::is_same_v<decltype(parent), decltype(ancestor)>) { return get_velocity_at<body>(date); }
    else {
        return get_velocity_at<body>(date) + get_velocity_relative_to_ancestor<parent, ancestor>(date);
    }
}

} // namespace astro
} // namespace astrea