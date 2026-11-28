/**
 * @file primary_frame.hpp
 * @author Jay Iuliano (iuliano.jay@gmail.com)
 * @brief Registration point for the primary frame used across astrea.
 * @date 2025-04-22
 *
 * @copyright Copyright (c) 2025-2026 Jay Iuliano
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

#include <astro/frames/definitions/body_centered_inertial_frames.hpp>
#include <astro/frames/definitions/body_fixed_frames.hpp>
#include <astro/frames/definitions/frame_registry.fwd.hpp>

#include <type_traits>

namespace astrea {
namespace astro {

namespace detail {

template <typename>
inline constexpr bool always_false_type_v = false;

/**
 * @brief Compile-time selection of astrea's primary inertial frame
 */
template <IsCelestialBody Body_T, IsAxis Axis_T>
inline consteval auto select_primary_inertial_frame(Body_T body, Axis_T axis)
{
    if constexpr (axis != axes::icrf && axis != axes::j2000) {
        static_assert(always_false_type_v<Axis_T>, "Unsupported primary inertial axis. Must be icrf or j2000 axis.");
    }
    if constexpr (body == star::Sun) {
        if constexpr (axis == axes::icrf) { return frames::sun::icrf; }
        else if constexpr (axis == axes::j2000) {
            return frames::sun::j2000;
        }
    }
    else if constexpr (body == planets::Mercury) {
        if constexpr (axis == axes::icrf) { return frames::mercury::icrf; }
        else if constexpr (axis == axes::j2000) {
            return frames::mercury::j2000;
        }
    }
    else if constexpr (body == planets::Venus) {
        if constexpr (axis == axes::icrf) { return frames::venus::icrf; }
        else if constexpr (axis == axes::j2000) {
            return frames::venus::j2000;
        }
    }
    else if constexpr (body == planets::Earth) {
        if constexpr (axis == axes::icrf) { return frames::earth::icrf; }
        else if constexpr (axis == axes::j2000) {
            return frames::earth::j2000;
        }
    }
    else if constexpr (body == moons::Moon) {
        if constexpr (axis == axes::icrf) { return frames::moon::icrf; }
        else if constexpr (axis == axes::j2000) {
            return frames::moon::j2000;
        }
    }
    else if constexpr (body == planets::Mars) {
        if constexpr (axis == axes::icrf) { return frames::mars::icrf; }
        else if constexpr (axis == axes::j2000) {
            return frames::mars::j2000;
        }
    }
    else if constexpr (body == moons::Phobos) {
        if constexpr (axis == axes::icrf) { return frames::phobos::icrf; }
        else if constexpr (axis == axes::j2000) {
            return frames::phobos::j2000;
        }
    }
    else if constexpr (body == moons::Deimos) {
        if constexpr (axis == axes::icrf) { return frames::deimos::icrf; }
        else if constexpr (axis == axes::j2000) {
            return frames::deimos::j2000;
        }
    }
    else if constexpr (body == planets::Jupiter) {
        if constexpr (axis == axes::icrf) { return frames::jupiter::icrf; }
        else if constexpr (axis == axes::j2000) {
            return frames::jupiter::j2000;
        }
    }
    else if constexpr (body == moons::Ganymede) {
        if constexpr (axis == axes::icrf) { return frames::ganymede::icrf; }
        else if constexpr (axis == axes::j2000) {
            return frames::ganymede::j2000;
        }
    }
    else if constexpr (body == moons::Callisto) {
        if constexpr (axis == axes::icrf) { return frames::callisto::icrf; }
        else if constexpr (axis == axes::j2000) {
            return frames::callisto::j2000;
        }
    }
    else if constexpr (body == moons::Io) {
        if constexpr (axis == axes::icrf) { return frames::io::icrf; }
        else if constexpr (axis == axes::j2000) {
            return frames::io::j2000;
        }
    }
    else if constexpr (body == moons::Europa) {
        if constexpr (axis == axes::icrf) { return frames::europa::icrf; }
        else if constexpr (axis == axes::j2000) {
            return frames::europa::j2000;
        }
    }
    else if constexpr (body == planets::Saturn) {
        if constexpr (axis == axes::icrf) { return frames::saturn::icrf; }
        else if constexpr (axis == axes::j2000) {
            return frames::saturn::j2000;
        }
    }
    else if constexpr (body == moons::Titan) {
        if constexpr (axis == axes::icrf) { return frames::titan::icrf; }
        else if constexpr (axis == axes::j2000) {
            return frames::titan::j2000;
        }
    }
    else if constexpr (body == moons::Rhea) {
        if constexpr (axis == axes::icrf) { return frames::rhea::icrf; }
        else if constexpr (axis == axes::j2000) {
            return frames::rhea::j2000;
        }
    }
    else if constexpr (body == moons::Iapetus) {
        if constexpr (axis == axes::icrf) { return frames::iapetus::icrf; }
        else if constexpr (axis == axes::j2000) {
            return frames::iapetus::j2000;
        }
    }
    else if constexpr (body == planets::Uranus) {
        if constexpr (axis == axes::icrf) { return frames::uranus::icrf; }
        else if constexpr (axis == axes::j2000) {
            return frames::uranus::j2000;
        }
    }
    else if constexpr (body == moons::Titania) {
        if constexpr (axis == axes::icrf) { return frames::titania::icrf; }
        else if constexpr (axis == axes::j2000) {
            return frames::titania::j2000;
        }
    }
    else if constexpr (body == moons::Oberon) {
        if constexpr (axis == axes::icrf) { return frames::oberon::icrf; }
        else if constexpr (axis == axes::j2000) {
            return frames::oberon::j2000;
        }
    }
    else if constexpr (body == planets::Neptune) {
        if constexpr (axis == axes::icrf) { return frames::neptune::icrf; }
        else if constexpr (axis == axes::j2000) {
            return frames::neptune::j2000;
        }
    }
    else if constexpr (body == moons::Triton) {
        if constexpr (axis == axes::icrf) { return frames::triton::icrf; }
        else if constexpr (axis == axes::j2000) {
            return frames::triton::j2000;
        }
    }
    else {
        static_assert(always_false_type_v<Body_T>, "Unsupported primary body for inertial frame selection. Must be a celestial body defined in Astrea.");
    }
}

/**
 * @brief Compile-time selection of astrea's primary fixed frame
 */
template <IsCelestialBody Body_T>
inline consteval auto select_primary_fixed_frame(Body_T body)
{
    if constexpr (body == planets::Mercury) { return frames::mercury::mercury_fixed; }
    else if constexpr (body == planets::Venus) {
        return frames::venus::venus_fixed;
    }
    else if constexpr (body == planets::Earth) {
        return frames::earth::earth_fixed;
    }
    else if constexpr (body == moons::Moon) {
        return frames::moon::moon_fixed;
    }
    else if constexpr (body == planets::Mars) {
        return frames::mars::mars_fixed;
    }
    else if constexpr (body == moons::Phobos) {
        return frames::phobos::phobos_fixed;
    }
    else if constexpr (body == moons::Deimos) {
        return frames::deimos::deimos_fixed;
    }
    else if constexpr (body == planets::Jupiter) {
        return frames::jupiter::jupiter_fixed;
    }
    else if constexpr (body == moons::Ganymede) {
        return frames::ganymede::ganymede_fixed;
    }
    else if constexpr (body == moons::Callisto) {
        return frames::callisto::callisto_fixed;
    }
    else if constexpr (body == moons::Io) {
        return frames::io::io_fixed;
    }
    else if constexpr (body == moons::Europa) {
        return frames::europa::europa_fixed;
    }
    else if constexpr (body == planets::Saturn) {
        return frames::saturn::saturn_fixed;
    }
    else if constexpr (body == moons::Titan) {
        return frames::titan::titan_fixed;
    }
    else if constexpr (body == moons::Rhea) {
        return frames::rhea::rhea_fixed;
    }
    else if constexpr (body == moons::Iapetus) {
        return frames::iapetus::iapetus_fixed;
    }
    else if constexpr (body == planets::Uranus) {
        return frames::uranus::uranus_fixed;
    }
    else if constexpr (body == moons::Titania) {
        return frames::titania::titania_fixed;
    }
    else if constexpr (body == moons::Oberon) {
        return frames::oberon::oberon_fixed;
    }
    else if constexpr (body == planets::Neptune) {
        return frames::neptune::neptune_fixed;
    }
    else if constexpr (body == moons::Triton) {
        return frames::triton::triton_fixed;
    }
    else {
        static_assert(always_false_type_v<Body_T>, "Unsupported primary body for fixed-frame selection.");
    }
}

} // namespace detail

using SelectedPrimaryFrame = PrimaryFrameSelection<>;

inline constexpr auto primary_body = SelectedPrimaryFrame::body;
inline constexpr auto primary_axes = SelectedPrimaryFrame::axis;

namespace frames {

inline constexpr auto primary       = detail::select_primary_inertial_frame(primary_body, primary_axes);
inline constexpr auto primary_fixed = detail::select_primary_fixed_frame(primary_body);

} // namespace frames

static_assert(IsInertialFrame<std::decay_t<decltype(frames::primary)>>, "The primary frame must be inertial.");

} // namespace astro
} // namespace astrea
