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
#include <astro/state/orbital_elements/instances/Cartesian.hpp>
#include <astro/state/orbital_elements/instances/Keplerian.hpp>
#include <astro/systems/AstrodynamicsSystem.hpp>
#include <astro/systems/CelestialBody.hpp>


namespace astrea {
namespace astro {

using namespace mp_units;
using namespace mp_units::angular;
using mp_units::angular::unit_symbols::deg;
using mp_units::angular::unit_symbols::rad;
using mp_units::si::unit_symbols::km;
using mp_units::si::unit_symbols::s;


OrbitalElementPartials J2MeanVop::operator()(const State& state, const Vehicle& vehicle) const
{
    const auto mu             = state.get_system().get_mu();
    const auto J2             = state.get_system().get_central_body()->get_j2();
    const auto equitorialR    = state.get_system().get_central_body()->get_equitorial_radius();
    const Keplerian elements  = state.in_element_set<Keplerian>();
    const Cartesian cartesian = state.in_element_set<Cartesian>();

    // Extract
    const Distance& a = elements.get_semimajor();
    // const Angle& raan = elements.get_right_ascension();
    const Angle& w     = elements.get_argument_of_perigee();
    const Angle& theta = elements.get_true_anomaly();

    // Prevents singularities from occuring in the propagation. Will cause inaccuracies.
    const Unitless& ecc = (elements.get_eccentricity() < eccTol) ? eccTol : elements.get_eccentricity();
    const Angle& inc    = (elements.get_inclination() < incTol) ? incTol : elements.get_inclination();

    // conversions Keplerian elements to r and v
    const VelocityVector<frames::earth::icrf> v = cartesian.get_velocity();
    const RadiusVector<frames::earth::icrf> r   = cartesian.get_position();

    const Distance x = cartesian.get_x();
    const Distance y = cartesian.get_y();
    const Distance z = cartesian.get_z();
    const Distance R = r.norm();

    // Variables to reduce calculations
    const auto termA = -1.5 * J2 * mu * equitorialR * equitorialR / (R * R * R * R * R);
    const auto termB = z * z / (R * R);

    // accel due to oblateness
    AccelerationVector<frames::earth::icrf> accelOblateness = { termA * (1.0 - 5.0 * termB) * x,
                                                                termA * (1.0 - 5.0 * termB) * y,
                                                                termA * (3.0 - 5.0 * termB) * z };

    // Only normal pert required
    const UnitVector Nhat         = r.cross(v).unit();
    const Acceleration normalPert = accelOblateness.dot(Nhat);

    // Precompute
    const Angle u                   = w + theta;
    const SpecificAngularMomentum h = sqrt(mu * a * (1 - ecc * ecc));

    // Calculate the derivatives of the Keplerian elements - only raan and w considered
    static const Velocity dadt          = 0.0 * km / s;
    static const UnitlessPerTime deccdt = 0.0 * one / s;
    const AngularRate _dincdt           = R / h * cos(u) * normalPert * rad;
    const AngularRate dthetadt          = h / (R * R) * rad;
    const AngularRate draandt           = R * sin(u) / (h * sin(inc)) * normalPert * rad;
    const AngularRate dwdt              = -draandt * cos(inc);

    // Loop to prevent crashes due to circular and zero inclination orbits.
    // Will cause an error
    AngularRate dincdt = _dincdt;
    if (inc == incTol && dincdt <= incTol * one / s) { dincdt = 0.0 * rad / s; }

    return KeplerianPartial(dadt, deccdt, dincdt, draandt, dwdt, dthetadt);
}


StateTransitionMatrix J2MeanVop::compute_stm(const State& state, const Vehicle& vehicle) const
{
    return StateTransitionMatrix(*this, state, vehicle);
}

} // namespace astro
} // namespace astrea