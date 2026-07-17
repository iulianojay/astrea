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

#include <astro/propagation/equations_of_motion/J2MeanVop.hpp>

#include <algorithm>
#include <cmath>
#include <exception>

#include <mp-units/math.h>
#include <mp-units/systems/angular/math.h>
#include <mp-units/systems/si/math.h>

#include <astro/propagation/equations_of_motion/EquationsOfMotion.hpp>
#include <astro/propagation/force_models/ForceModel.hpp>
#include <astro/state/State.hpp>
#include <astro/state/orbital_elements/Cartesian.hpp>
#include <astro/state/orbital_elements/Keplerian.hpp>
#include <astro/systems/CelestialBody.hpp>
#include <astro/systems/system_utilities.hpp>


namespace astrea {
namespace astro {

using namespace mp_units;
using namespace mp_units::angular;
using mp_units::angular::unit_symbols::deg;
using mp_units::angular::unit_symbols::rad;
using mp_units::si::unit_symbols::km;
using mp_units::si::unit_symbols::s;


OrbitalElementPartials J2MeanVop::compute_dynamics(
    const State& state,
    const Vehicle& vehicle,
    const ForceVector<frames::earth::icrf>& perts,
    const ForceVector<frames::earth::icrf>& control
) const
{
    // Extract
    const GravParam mu     = get_mu<frames::earth::icrf.origin>();
    const auto J2          = get_j2<frames::earth::icrf.origin>();
    const auto equitorialR = get_equitorial_radius<frames::earth::icrf.origin>();

    const Keplerian<frames::earth::icrf> elements = state.in_element_set<Keplerian<frames::earth::icrf>>();
    const Distance& a                             = elements.get_semimajor();
    // const Angle& raan = elements.get_right_ascension();
    const Angle& w     = elements.get_argument_of_perigee();
    const Angle& theta = elements.get_true_anomaly();

    // Prevents singularities from occuring in the propagation. Will cause inaccuracies.
    const Unitless& ecc = (elements.get_eccentricity() < eccTol) ? eccTol : elements.get_eccentricity();
    const Angle& inc    = (elements.get_inclination() < incTol) ? incTol : elements.get_inclination();

    // conversions Keplerian elements to r and v
    const RadiusVector<frames::earth::icrf> r   = state.get_position();
    const VelocityVector<frames::earth::icrf> v = state.get_velocity();

    const Distance& x = r.get_x();
    const Distance& y = r.get_y();
    const Distance& z = r.get_z();
    const Distance R  = r.norm();

    // Variables to reduce calculations
    const auto termA = -1.5 * J2 * mu * pow<2>(equitorialR) / pow<5>(R);
    const auto termB = pow<2>(z / R);

    // TODO: Do we want to add vehicle acceleration here? It basically invalidates these equations since you'd need the
    // entire keplerian VoP form, in which case you should just use the KeplerianVoP class.

    // accel due to oblateness
    AccelerationVector<frames::earth::icrf> accelOblateness = { termA * (1.0 - 5.0 * termB) * x,
                                                                termA * (1.0 - 5.0 * termB) * y,
                                                                termA * (3.0 - 5.0 * termB) * z };

    // Only normal pert required
    const Direction Nhat          = r.cross(v).direction();
    const Acceleration normalPert = accelOblateness.dot(Nhat);

    // Precompute
    const Angle u                   = w + theta;
    const SpecificAngularMomentum h = sqrt(mu * a * (1 - ecc * ecc));

    // Calculate the derivatives of the Keplerian elements - only raan and w considered
    static const Velocity dadt          = 0.0 * km / s;
    static const UnitlessPerTime deccdt = 0.0 * one / s;
    const AngularVelocity _dincdt       = R / h * cos(u) * normalPert * rad;
    const AngularVelocity dthetadt      = h / (R * R) * rad;
    const AngularVelocity draandt       = R * sin(u) / (h * sin(inc)) * normalPert * rad;
    const AngularVelocity dwdt          = -draandt * cos(inc);

    // Loop to prevent crashes due to circular and zero inclination orbits.
    // Will cause an error
    AngularVelocity dincdt = _dincdt;
    if (inc == incTol && dincdt <= incTol * one / s) { dincdt = 0.0 * rad / s; }

    return KeplerianPartial<frames::earth::icrf>(dadt, deccdt, dincdt, draandt, dwdt, dthetadt);
}

} // namespace astro
} // namespace astrea