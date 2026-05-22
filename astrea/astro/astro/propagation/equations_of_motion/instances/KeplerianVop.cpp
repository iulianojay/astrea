/*
 * The GNU Lesser General Public License (LGPL)
 *
 * Copyright (c) 2025 Jay Iuliano
 *
 * This file is part of Astrea.
 * Astrea is free software: you can redistribute it and/or modify it under the terms of the GNU Lesser General Public License
 * as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
 * Astrea is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty
 * of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU Lesser General Public License for more details. You should
 * have received a copy of the GNU General Public License along with Astrea. If not, see <https://www.gnu.org/licenses/>.
 */

#include <astro/propagation/equations_of_motion/instances/KeplerianVop.hpp>

#include <iostream>

#include <mp-units/math.h>
#include <mp-units/systems/angular/math.h>
#include <mp-units/systems/isq_angle.h>
#include <mp-units/systems/si/math.h>

#include <astro/frames/dynamic_frames.hpp>
#include <astro/frames/frames.hpp>
#include <astro/platforms/Vehicle.hpp>
#include <astro/state/State.hpp>
#include <astro/state/orbital_elements/instances/Cartesian.hpp>
#include <astro/state/orbital_elements/instances/Keplerian.hpp>

namespace astrea {
namespace astro {

using namespace mp_units;
using namespace mp_units::angular;
using mp_units::angular::unit_symbols::deg;
using mp_units::angular::unit_symbols::rad;
using mp_units::si::unit_symbols::km;
using mp_units::si::unit_symbols::s;

KeplerianVop::KeplerianVop(const ForceModel& forces, const bool doWarn) :
    EquationsOfMotion(forces),
    doWarn(doWarn)
{
}

OrbitalElementPartials KeplerianVop::compute_dynamics(
    const State& state,
    const Vehicle& vehicle,
    const ForceVector<frames::primary>& perts,
    const ForceVector<frames::primary>& control
) const
{
    // Extract
    const auto mu    = get_mu<decltype(frames::primary)::origin>();
    const Date& date = state.get_epoch();

    const Keplerian<frames::primary> elements = state.in_element_set<Keplerian<frames::primary>>();
    const Distance& a                         = elements.get_semimajor();
    // const Angle& raan = elements.get_right_ascension();
    const Angle& w     = elements.get_argument_of_perigee();
    const Angle& theta = elements.get_true_anomaly();

    // Prevents singularities from occuring in the propagation. Will cause
    // inaccuracies.
    const Unitless& ecc = (elements.get_eccentricity() < checkTol * one) ? checkTol * one : elements.get_eccentricity();
    const Angle& inc    = (elements.get_inclination() < checkTol * rad) ? checkTol * rad : elements.get_inclination();

    if (doWarn) { check_degenerate(ecc, inc); }

    // conversions KEPLERIANs to r and v
    const VelocityVector<frames::primary> v = state.get_velocity();
    const RadiusVector<frames::primary> r   = state.get_position();

    // Calculate R, N, and T
    const auto ricFrame = frames::dynamic::ric.instantaneous(r, v);
    const AccelerationVector<frames::dynamic::ric> accelRic =
        ricFrame.rotate_into_this_frame((perts + control) / vehicle.get_mass(), date);

    const Acceleration& radialPert     = accelRic.get_x();
    const Acceleration& tangentialPert = accelRic.get_y();
    const Acceleration& normalPert     = accelRic.get_z();

    // Argument of latitude
    const Angle u = w + theta;

    // Precalculate
    const Unitless cosTA = cos(theta);
    const Unitless sinTA = sin(theta);
    const Unitless cosU  = cos(u);
    const Unitless sinU  = sin(u);

    const Distance R                    = r.norm();
    const SpecificAngularMomentum h     = sqrt(mu * a * (1 - ecc * ecc));
    const quantity hSquared             = h * h;
    const UnitlessPerTime hOverRSquared = h / (R * R);

    // Calculate the derivatives of the Keplerian elements
    const quantity dhdt = R * tangentialPert;
    const UnitlessPerTime deccdt =
        h / mu * sinTA * radialPert + 1.0 / (mu * h) * ((hSquared + mu * R) * cosTA + mu * ecc * R) * tangentialPert;
    const Velocity dadt = 2.0 * a * (1.0 / h * dhdt + ecc / (1 - ecc * ecc) * deccdt); // TODO: Someone check this. It's my derivation from h = sqrt(mu*a(1-ecc^2))
    const AngularVelocity dincdt = R / h * cosU * normalPert * (isq_angle::cotes_angle);
    const AngularVelocity dthetadt =
        (hOverRSquared + (1 / (ecc * h)) * ((hSquared / mu) * cosTA * radialPert - (hSquared / mu + R) * sinTA * tangentialPert)) *
        (isq_angle::cotes_angle);
    const AngularVelocity draandt = R * sinU / (h * sin(inc)) * normalPert * (isq_angle::cotes_angle);
    const AngularVelocity dwdt    = (-dthetadt + (hOverRSquared * isq_angle::cotes_angle - draandt * cos(inc)));

    return KeplerianPartial<frames::primary>(dadt, deccdt, dincdt, draandt, dwdt, dthetadt);
}

void KeplerianVop::check_degenerate(const Unitless& ecc, const Angle& inc) const
{
    if (ecc <= checkTol * one || inc <= checkTol * rad) {
        std::string title;
        if (ecc <= checkTol * one && inc <= checkTol * rad) { title = "Eccentricity and inclination"; }
        else if (ecc <= checkTol * one) {
            title = "Eccentricity";
        }
        else {
            title = "Inclination";
        }
        std::cout << "WARNING: Degenerate case. " << title << " smaller than acceptable tolerance (" << checkTol
                  << "). Results may be inaccurate." << std::endl
                  << std::endl;
    }
}

} // namespace astro
} // namespace astrea