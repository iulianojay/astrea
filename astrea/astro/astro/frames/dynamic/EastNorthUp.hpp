/**
 * @file EastNorthUp.hpp
 * @author Jay Iuliano (iuliano.jay@gmail.com)
 * @brief Header file for the EastNorthUp class in the astro namespace
 * @date 2025-08-05
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

#include <mp-units/systems/angular/math.h>
#include <mp-units/systems/si/math.h>

#include <units/units.hpp>

#include <astro/astro.fwd.hpp>
#include <astro/frames/CartesianVector.hpp>
#include <astro/frames/DirectionCosineMatrix.hpp>
#include <astro/frames/DynamicFrame.hpp>
#include <astro/frames/Frame.hpp>
#include <astro/frames/transformations.hpp>
#include <astro/state/angular_elements/instances/Geodetic.hpp>
#include <astro/systems/planets.hpp>
#include <astro/time/Date.hpp>

namespace astrea {
namespace astro {
namespace frames {

/**
 * @brief Class representing the East, North, Up (ENU) frame.
 */
template <IsFrame auto _frame_>
struct EastNorthUp : public DynamicFrame<EastNorthUp<_frame_>, _frame_> {

    struct SelfTag : Frame<"enu", DynamicOrigin{}, DynamicAxis{}, _frame_> {}; //!< Empty frame tag satisfying IsFrame.

    static constexpr auto frame = _frame_; //!< The reference frame of the ENU frame.

    /**
     * @brief Constructor for instantaneous dynamic state/frames.
     *
     * @param position The position vector in the ECI frame.
     * @param velocity The velocity vector in the ECI frame.
     */
    EastNorthUp(const RadiusVector<frame>& position, const VelocityVector<frame>& velocity) :
        DynamicFrame<EastNorthUp<_frame_>, frame>(position, velocity)
    {
    }

    EastNorthUp() = delete; //!< Default constructor is deleted to prevent instantiation without a parent

    /**
     * @brief Gets the Direction Cosine Matrix (DCM) for the ENU frame at a given date.
     *
     * @param date The date for which the DCM is requested.
     * @return DirectionCosineMatrix<frame, EastNorthUp> The DCM from ECI to ENU.
     */
    DirectionCosineMatrix<frame, SelfTag{}> get_dcm(const Date& date) const
    {
        // TODO: This assumes we're using "default" Earth. REALLY don't want to pass a system
        // to this object
        static const planets::Earth earth;
        static const Distance& rEquitorial = earth.get_equitorial_radius();
        static const Distance& rPolar      = earth.get_polar_radius();

        // eci -> ecef -> lat/lon -> n/e/u
        const RadiusVector<frame> r            = this->get_position(date);
        const RadiusVector<frame_fixed> rFixed = r.in_frame<frame_fixed>(date);
        const auto [lat, lon, alt]             = convert_body_fixed_to_geodetic(rFixed, rEquitorial, rPolar);

        using mp_units::one;
        using mp_units::angular::cos;
        using mp_units::angular::sin;
        const Unitless sinLat = sin(lat);
        const Unitless cosLat = cos(lat);
        const Unitless sinLon = sin(lon);
        const Unitless cosLon = cos(lon);

        return DirectionCosineMatrix<frame, SelfTag{}>(
            { -sinLat, cosLat, 0.0 * one }, { -cosLat * sinLon, -sinLat * sinLon, cosLon }, { cosLat * cosLon, sinLat * cosLon, sinLon }
        );
    }
};

} // namespace frames
} // namespace astro
} // namespace astrea