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
#include <astro/systems/celestial_bodies.hpp>
#include <astro/systems/property_getters.hpp>
#include <astro/time/Date.hpp>
#include <astro/types/enums.hpp>
#include <astro/types/type_traits.hpp>


namespace astrea {
namespace astro {


template <IsCelestialReference auto ancestor, IsCelestialReference auto body>
consteval bool is_same_body()
{
    if constexpr (std::is_same_v<decltype(ancestor), decltype(body)>) { return true; }
    else {
        return false;
    }
}

template <IsCelestialReference auto body>
consteval bool has_parent()
{
    if constexpr (requires { decltype(body)::parent; }) { return true; }
    else {
        return false;
    }
}

template <IsCelestialReference auto body>
    requires(has_parent<body>())
consteval auto get_parent()
{
    return decltype(body)::parent;
}

/**
 * @brief Returns true if Ancestor is Body itself or appears anywhere in Body's parent chain.
 */
template <IsCelestialReference auto ancestor, IsCelestialReference auto body>
consteval bool is_ancestor_of()
{
    if constexpr (is_same_body<ancestor, body>()) { return true; }
    else if constexpr (has_parent<body>()) {
        return is_ancestor_of<ancestor, get_parent<body>()>();
    }
    else {
        return false;
    }
}

/**
 * @brief Returns the single PLANET in the pack (assumes exactly one exists).
 */
template <IsCelestialReference auto first, IsCelestialReference auto... rest>
consteval auto get_planet_from_pack()
{
    if constexpr (get_body_type<first>() == CelestialBodyType::PLANET) { return first; }
    else {
        static_assert(sizeof...(rest) > 0, "no PLANET found in body pack");
        return get_planet_from_pack<rest...>();
    }
}

/**
 * @brief Checks if all bodies in the pack share the same parent.
 */
template <IsCelestialReference auto first, IsCelestialReference auto... rest>
consteval bool check_all_bodies_share_a_parent()
{
    if constexpr (sizeof...(rest) == 0) { return true; }

    static_assert(has_parent<first>(), "body must have a parent to check if all bodies share a parent");
    constexpr auto parent = get_parent<first>();
    return ((is_same_body<parent, rest>() || (has_parent<rest>() && is_same_body<parent, get_parent<rest>()>())) && ...);
}

/**
 * @brief Finds the closest common ancestor of the given celestial bodies.
 *
 * - 1 body      → that body itself.
 * - ≥ 2 planets → SolarSystemBarycenter (the only common ancestor of independent planets).
 * - 1 planet    → that planet if all other bodies are in its system, else SolarSystemBarycenter.
 * - 0 planets   → only moons, check if they share a parent, else SolarSystemBarycenter.
 *
 * @tparam Bodies The celestial bodies to consider.
 * @return The common ancestor body value.
 */
template <IsCelestialReference auto... bodies>
consteval auto find_common_ancestor()
{
    if constexpr (sizeof...(bodies) == 1) { return (bodies, ...); }

    constexpr std::size_t planet_count = ((get_body_type<bodies>() == CelestialBodyType::PLANET ? 1 : 0) + ...);

    // 2 or more planets means the common ancestor is the Solar System Barycenter
    if constexpr (planet_count >= 2) { return barycenters::SolarSystemBarycenter; }
    else if constexpr (planet_count == 1) {
        // Exactly 1 planet, check if all other bodies are in its system
        constexpr auto planet = get_planet_from_pack<bodies...>();
        if constexpr ((is_ancestor_of<planet, bodies>() && ...)) { return planet; }
    }
    else if constexpr (planet_count == 0) {
        // No planets, check if all bodies share the same parent
        if constexpr (check_all_bodies_share_a_parent<bodies...>()) {
            constexpr auto first = (bodies, ...);
            return get_parent<first>();
        }
    }
    return barycenters::SolarSystemBarycenter;
}

/**
 * @brief Get the relative position between two celestial bodies at a specific date.
 *
 * @param date The date at which to get the relative position.
 * @param id1 The ID of the first celestial body.
 * @param id2 The ID of the second celestial body.
 * @return CartesianVector<Distance, frames::solar_system_barycenter::icrf> The relative position vector from id2 to id1.
 */
template <IsCelestialReference auto body1, IsCelestialReference auto body2>
constexpr auto get_relative_position(const Date& date)
{
    if constexpr (is_same_body<body1, body2>()) {
        return decltype(get_position_at<body1>(date))(Distance::zero(), Distance::zero(), Distance::zero());
    }
    else if constexpr (has_parent<body1>() && is_same_body<get_parent<body1>(), body2>()) {
        return get_position_at<body1>(date);
    }
    else if constexpr (has_parent<body2>() && is_same_body<get_parent<body2>(), body1>()) {
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
template <IsCelestialReference auto body1, IsCelestialReference auto body2>
constexpr auto get_relative_velocity(const Date& date)
{
    if constexpr (is_same_body<body1, body2>()) {
        return decltype(get_velocity_at<body1>(date))(Velocity::zero(), Velocity::zero(), Velocity::zero());
    }
    else if constexpr (has_parent<body1>() && is_same_body<get_parent<body1>(), body2>()) {
        return get_velocity_at<body1>(date);
    }
    else if constexpr (has_parent<body2>() && is_same_body<get_parent<body2>(), body1>()) {
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
template <IsCelestialReference auto body, IsCelestialReference auto ancestor>
constexpr auto get_position_relative_to_ancestor(const Date& date)
{
    static constexpr auto parent = get_parent<body>();
    if constexpr (is_same_body<parent, ancestor>()) { return get_position_at<body>(date); }
    else {
        // r_body/ancestor = r_body/parent + r_parent/ancestor
        return get_position_at<body>(date)
                   .template force_frame_conversion<decltype(get_position_relative_to_ancestor<parent, ancestor>(date))::frame>() +
               get_position_relative_to_ancestor<parent, ancestor>(date);
    }
}

/**
 * @brief Get the velocity of a celestial body relative to the root at a specific date.
 *
 * @param date The date at which to get the velocity.
 * @param id The ID of the celestial body.
 * @return CartesianVector<Velocity, frames::solar_system_barycenter::icrf> The velocity vector of the celestial body relative to the root.
 */
template <IsCelestialReference auto body, IsCelestialReference auto ancestor>
constexpr auto get_velocity_relative_to_ancestor(const Date& date)
{
    static constexpr auto parent = get_parent<body>();
    if constexpr (is_same_body<parent, ancestor>()) { return get_velocity_at<body>(date); }
    else {
        return get_velocity_at<body>(date)
                   .template force_frame_conversion<decltype(get_velocity_relative_to_ancestor<parent, ancestor>(date))::frame>() +
               get_velocity_relative_to_ancestor<parent, ancestor>(date);
    }
}

} // namespace astro
} // namespace astrea