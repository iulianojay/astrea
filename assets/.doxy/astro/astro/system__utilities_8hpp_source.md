

# File system\_utilities.hpp

[**File List**](files.md) **>** [**astrea**](dir_b5324400686b7cece921533bb760c87a.md) **>** [**astro**](dir_1d4dcf10fc541574a93624f5c09a3d6f.md) **>** [**astro**](dir_84db6e3c60e44147f5214c05dc45afc2.md) **>** [**systems**](dir_a5d35e082abd602943cf6d70fa2a6872.md) **>** [**system\_utilities.hpp**](system__utilities_8hpp.md)

[Go to the documentation of this file](system__utilities_8hpp.md)


```C++

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

template <IsCelestialReference auto first, IsCelestialReference auto... rest>
consteval auto get_planet_from_pack()
{
    if constexpr (get_body_type<first>() == CelestialBodyType::PLANET) { return first; }
    else {
        static_assert(sizeof...(rest) > 0, "no PLANET found in body pack");
        return get_planet_from_pack<rest...>();
    }
}

template <IsCelestialReference auto first, IsCelestialReference auto... rest>
consteval bool check_all_bodies_share_a_parent()
{
    if constexpr (sizeof...(rest) == 0) { return true; }

    static_assert(has_parent<first>(), "body must have a parent to check if all bodies share a parent");
    constexpr auto parent = get_parent<first>();
    return ((is_same_body<parent, rest>() || (has_parent<rest>() && is_same_body<parent, get_parent<rest>()>())) && ...);
}

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

template <IsCelestialReference auto body1, IsCelestialReference auto body2>
constexpr auto get_relative_acceleration(const Date& date)
{
    if constexpr (is_same_body<body1, body2>()) {
        return decltype(get_acceleration_at<body1>(date))(Acceleration::zero(), Acceleration::zero(), Acceleration::zero());
    }
    else if constexpr (has_parent<body1>() && is_same_body<get_parent<body1>(), body2>()) {
        return get_acceleration_at<body1>(date);
    }
    else if constexpr (has_parent<body2>() && is_same_body<get_parent<body2>(), body1>()) {
        return -get_acceleration_at<body2>(date);
    }
    else {
        static constexpr auto root = find_common_ancestor<body1, body2>();
        const auto acc1            = get_acceleration_relative_to_ancestor<body1, root>(date);
        const auto acc2            = get_acceleration_relative_to_ancestor<body2, root>(date);
        return acc1 - acc2;
    }
}

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

template <IsCelestialReference auto body, IsCelestialReference auto ancestor>
constexpr auto get_acceleration_relative_to_ancestor(const Date& date)
{
    static constexpr auto parent = get_parent<body>();
    if constexpr (is_same_body<parent, ancestor>()) { return get_acceleration_at<body>(date); }
    else {
        return get_acceleration_at<body>(date)
                   .template force_frame_conversion<decltype(get_acceleration_relative_to_ancestor<parent, ancestor>(date))::frame>() +
               get_acceleration_relative_to_ancestor<parent, ancestor>(date);
    }
}

} // namespace astro
} // namespace astrea
```


