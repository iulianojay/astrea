/**
 * @file TopocentricFrame.hpp
 * @author Jay Iuliano (iuliano.jay@gmail.com)
 * @brief Definition for a TopocentricFrame in astrea.
 * @date 2025-10-02
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

#include <type_traits>

#include <mp-units/core.h>
#include <mp-units/framework/symbol_text.h>

#include <units/units.hpp>
#include <utilities/string_util.hpp>

#include <astro/frames/framework/BodyFixedFrame.hpp>
#include <astro/frames/framework/FixedOffsetFrame.hpp>
#include <astro/frames/framework/Frame.hpp>
#include <astro/frames/framework/frame_concepts.hpp>
#include <astro/state/angular_elements/Geodetic.hpp>
#include <astro/types/enums.hpp>

namespace astrea {
namespace astro {

// There has to be a better way to do this
template <IsBodyFixedFrame auto _parent_, Angle _lat_, Angle _lon_, Distance _alt_>
inline consteval auto get_x_offset_from_lla()
{
    return convert_geodetic_to_body_fixed<_parent_>(_lat_, _lon_, _alt_)[0];
}

template <IsBodyFixedFrame auto _parent_, Angle _lat_, Angle _lon_, Distance _alt_>
inline consteval auto get_y_offset_from_lla()
{
    return convert_geodetic_to_body_fixed<_parent_>(_lat_, _lon_, _alt_)[1];
}

template <IsBodyFixedFrame auto _parent_, Angle _lat_, Angle _lon_, Distance _alt_>
inline consteval auto get_z_offset_from_lla()
{
    return convert_geodetic_to_body_fixed<_parent_>(_lat_, _lon_, _alt_)[2];
}

template <mp_units::symbol_text _name_, IsBodyFixedFrame auto _parent_, Angle _lat_, Angle _lon_, Distance _alt_>
struct TopocentricFrame : public FixedOffsetFrame<
                              _name_,
                              _parent_,
                              get_x_offset_from_lla<_parent_, _lat_, _lon_, _alt_>(),
                              get_y_offset_from_lla<_parent_, _lat_, _lon_, _alt_>(),
                              get_z_offset_from_lla<_parent_, _lat_, _lon_, _alt_>(),
                              Angle(90.0 * mp_units::angular::degree), // rotation z by longitude,
                              _lat_,                                   // rotation y by latitude,
                              _lon_,                   // rotation x by 90 degrees (to align with local vertical)
                              RotationSequence::ZYX> { // This gives the NWU frame
    static constexpr auto lat = _lat_;
    static constexpr auto lon = _lon_;
    static constexpr auto alt = _alt_;
};

} // namespace astro
} // namespace astrea