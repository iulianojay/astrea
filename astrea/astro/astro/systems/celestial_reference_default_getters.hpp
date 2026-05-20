/**
 * @file celestial_reference_default_getters.hpp
 * @author Jay Iuliano (iuliano.jay@gmail.com)
 * @brief Keplerian-approximation fallback implementations for get_position_at / get_velocity_at.
 *
 * @details This header provides:
 *   - get_keplerian_elements_at<_body_>  — JPL linear-approximation Keplerian elements.
 *   - get_position_at<_body_>  (primary template definition) — Keplerian fallback used for
 *     bodies that have no Chebyshev ephemeris specialisation (e.g. Phobos, Deimos).
 *   - get_velocity_at<_body_>  (primary template definition) — same fallback for velocity.
 *
 * Include order matters:
 *   CelestialBody.hpp already declares the primary templates (without a body) for
 *   get_position_at / get_velocity_at.  The planet specialisations (e.g. Earth, Jupiter)
 *   are compiled when their individual planet headers are included.  This file provides
 *   the fall-through primary-template body for any remaining bodies.
 *
 *   This file MUST be included AFTER all planet headers (and therefore after all
 *   get_position_at explicit specialisations) so that the linker can select the correct
 *   overload.  planets.hpp includes it automatically at the bottom.
 *
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

#include <astro/frames/frame_utilities.hpp>
#include <astro/state/orbital_elements/instances/Cartesian.hpp>
#include <astro/state/orbital_elements/instances/Keplerian.hpp>
#include <astro/systems/celestial_reference_getters.hpp>

namespace astrea {
namespace astro {

/**
 * @brief Get the Keplerian elements of a celestial body at a specific date using a linear approximation.
 *
 * This uses the JPL approximate-positions algorithm:
 * https://ssd.jpl.nasa.gov/planets/approx_pos.html
 *
 * Bodies that have get_linear_expansion_coefficients specialised use the full
 * perturbation-corrected mean anomaly.  All other bodies fall back to the default
 * zero-coefficient implementation (Me = L - w).
 *
 * @param date The date at which to compute the elements.
 * @return Keplerian The approximate Keplerian elements at the given date.
 */
template <auto _body_, IsFrame auto _frame_>
inline Keplerian<_frame_> get_keplerian_elements_at(Date date)
{
    using namespace mp_units;
    using namespace mp_units::angular;
    using Body_T = std::remove_cvref_t<decltype(_body_)>;

    const Distance a   = get_semimajor<Body_T>(date);
    const Unitless ecc = get_eccentricity<Body_T>(date);
    const Angle inc    = get_inclination<Body_T>(date);
    const Angle raan   = get_right_ascension<Body_T>(date);
    const Angle w      = get_longitude_of_perigee<Body_T>(date);
    const Angle L      = get_mean_longitude<Body_T>(date);

    const mp_units::quantity<JulianCentury> T = get_time_since_reference_epoch<Body_T>(date);
    const auto [B, C, S, F]                   = get_linear_expansion_coefficients<_body_>();
    const Angle Me                            = wrap_angle(L - w + B * T * T + C * cos(F * T) + S * sin(F * T));
    const Angle argPer                        = wrap_angle(w - raan);

    const Angle thetat = convert_mean_anomaly_to_true_anomaly(Me, ecc);
    return Keplerian<_frame_>(a, ecc, inc, raan, argPer, thetat);
}

/**
 * @brief Keplerian fallback for get_position_at.
 *
 * Used for bodies that have orbital element parameters but no Chebyshev ephemeris
 * specialisation (e.g. Phobos, Deimos, small moons).  The result is expressed in
 * the parent-body ICRF frame derived from the body's parent origin.
 *
 * Bodies WITH an explicit get_position_at specialisation (e.g. Earth, Jupiter when
 * ephemeris is enabled) use that specialisation in preference to this primary template.
 */
template <auto _body_>
inline auto get_position_at(const Date& date)
{
    constexpr auto frame        = get_parent_frame(_body_, axes::icrf);
    const Keplerian<frame> coes = get_keplerian_elements_at<_body_, frame>(date);
    constexpr auto parent       = get_parent(_body_);
    const GravParam mu          = get_mu<decltype(parent)>();
    return Cartesian<frame>(coes, mu).get_position();
}

/**
 * @brief Keplerian fallback for get_velocity_at.
 *
 * See get_position_at for usage notes.
 */
template <auto _body_>
inline auto get_velocity_at(const Date& date)
{
    constexpr auto frame        = get_parent_frame(_body_, axes::icrf);
    const Keplerian<frame> coes = get_keplerian_elements_at<_body_, frame>(date);
    constexpr auto parent       = get_parent(_body_);
    const GravParam mu          = get_mu<decltype(parent)>();
    return Cartesian<frame>(coes, mu).get_velocity();
}

} // namespace astro
} // namespace astrea
