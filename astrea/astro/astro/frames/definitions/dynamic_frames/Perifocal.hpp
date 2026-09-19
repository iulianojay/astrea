/**
 * @file Perifocal.hpp
 * @author Jay Iuliano (iuliano.jay@gmail.com)
 * @brief Header file for the Perifocal class in the astro namespace
 * @date 2025-08-05
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

#include <astro/astro.fwd.hpp>
#include <astro/frames/definitions/body_centered_inertial_frames.hpp>
#include <astro/frames/framework/CartesianVector.hpp>
#include <astro/frames/framework/DirectionCosineMatrix.hpp>
#include <astro/frames/framework/DynamicFrame.hpp>
#include <astro/time/Date.hpp>
#include <astro/types/typedefs.hpp>

namespace astrea {
namespace astro {
namespace frames {

/**
 * @brief Frame tag type for Perifocal, defined outside the class to allow use as a DynamicFrame NTTP.
 */
template <IsFrame auto _parent_>
struct PerifocalTag final : Frame<"Perifocal", DynamicOrigin{}, DynamicAxis{}, _parent_> {
    Perifocal<_parent_> instantaneous(const RadiusVector<_parent_>& r, const VelocityVector<_parent_>& v) const
    {
        return Perifocal<_parent_>(r, v);
    }
};

template <IsFrame auto _parent_>
inline constexpr PerifocalTag<_parent_> perifocal_tag{};

/**
 * @brief Class representing the Perifocal (PQW) frame: P towards periapsis, W along the angular momentum vector,
 * and Q completing the right-handed triad in the orbital plane.
 *
 * Unlike VNB/RIC/LVLH, the perifocal frame's orientation is fixed for a given (unperturbed) orbit -- it depends
 * only on the orbital plane and the location of periapsis, not on where the satellite currently is along the orbit.
 */
template <IsFrame auto _parent_>
struct Perifocal : public DynamicFrame<Perifocal<_parent_>, _parent_, perifocal_tag<_parent_>> {

    using tag_type = PerifocalTag<_parent_>; //!< Tag type for this frame.
    static inline constexpr tag_type tag{};  //!< Empty frame tag satisfying IsFrame.
    static constexpr auto parent = _parent_; //!< The reference frame of the Perifocal frame.

    /**
     * @brief Constructor for the Perifocal frame from position, velocity, and gravitational parameter.
     *
     * @param position The position vector in the parent frame.
     * @param velocity The velocity vector in the parent frame.
     */
    Perifocal(const RadiusVector<parent>& position, const VelocityVector<parent>& velocity) :
        DynamicFrame<Perifocal<_parent_>, parent, perifocal_tag<_parent_>>(position, velocity)
    {
    }

    Perifocal() = delete; //!< Default constructor is deleted to prevent instantiation without a parent frame

    /**
     * @brief Gets the Direction Cosine Matrix (DCM) for the Perifocal frame at a given date.
     *
     * Computes the specific angular momentum vector (h = r x v, giving the W axis) and the eccentricity
     * vector (e = (v x h) / mu - r_hat, giving the P axis, i.e. the direction to periapsis), then completes
     * the right-handed triad with Q = W x P.
     *
     * @param date The date for which the DCM is requested. Unused: the perifocal frame's orientation only
     * depends on the (unperturbed) orbital plane and periapsis location, not on the current date.
     * @return DirectionCosineMatrix<parent, Perifocal> The DCM from parent to Perifocal.
     */
    DirectionCosineMatrix<parent, tag> get_dcm(const Date& date) const
    {
        static constexpr auto MU = get_mu<parent.origin>(); // Gravitational parameter of the parent frame's origin

        const auto r = this->get_position(date);
        const auto v = this->get_velocity(date);

        const auto h = r.cross(v);
        const auto p = ((v.cross(h) / MU) - r.direction()).direction();
        const auto w = h.direction();
        const auto q = w.cross(p);

        return DirectionCosineMatrix<parent, tag>::from_vectors(p, q, w);
    }
};


} // namespace frames
} // namespace astro
} // namespace astrea