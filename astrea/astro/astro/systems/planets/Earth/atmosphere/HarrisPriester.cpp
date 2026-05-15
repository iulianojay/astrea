/*
 * The GNU Lesser General Public License (LGPL)
 *
 * Copyright (c) 2026 Jay Iuliano
 *
 * This file is part of Astrea.
 * Astrea is free software: you can redistribute it and/or modify it under the terms of the GNU Lesser General Public License
 * as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
 * Astrea is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty
 * of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU Lesser General Public License for more details. You should
 * have received a copy of the GNU General Public License along with Astrea. If not, see <https://www.gnu.org/licenses/>.
 */

#include <astro/systems/planets/Earth/atmosphere/HarrisPriester.hpp>

#include <map>

#include <math/operations.hpp>

#include <astro/frames/frames.hpp>
#include <astro/state/State.hpp>
#include <astro/state/angular_elements/instances/Geodetic.hpp>

namespace astrea {
namespace astro {
namespace planets {

using namespace mp_units;
using mp_units::angular::unit_symbols::deg;
using mp_units::angular::unit_symbols::rad;
using mp_units::non_si::day;
using mp_units::si::unit_symbols::kg;
using mp_units::si::unit_symbols::km;
using mp_units::si::unit_symbols::m;
using mp_units::si::unit_symbols::s;


/** Default cosine exponent value. */
static const int cosineExponent = 4;

/** Lag angle for diurnal bulge. */
static const Angle LAG = 30.0 * deg;

/** Harris-Priester min-max density (kg/m3) vs. altitude (km) table.
 *  These data are valid for a mean solar activity. */
static const std::map<Altitude, std::tuple<Density, Density>> HARRIS_PRIESTER_ATMOSPHERE = {
    { 100.0 * km, { 4.974e-07 * kg / (pow<3>(m)), 4.974e-07 * kg / (pow<3>(m)) } },
    { 120.0 * km, { 2.490e-08 * kg / (pow<3>(m)), 2.490e-08 * kg / (pow<3>(m)) } },
    { 130.0 * km, { 8.377e-09 * kg / (pow<3>(m)), 8.710e-09 * kg / (pow<3>(m)) } },
    { 140.0 * km, { 3.899e-09 * kg / (pow<3>(m)), 4.059e-09 * kg / (pow<3>(m)) } },
    { 150.0 * km, { 2.122e-09 * kg / (pow<3>(m)), 2.215e-09 * kg / (pow<3>(m)) } },
    { 160.0 * km, { 1.263e-09 * kg / (pow<3>(m)), 1.344e-09 * kg / (pow<3>(m)) } },
    { 170.0 * km, { 8.008e-10 * kg / (pow<3>(m)), 8.758e-10 * kg / (pow<3>(m)) } },
    { 180.0 * km, { 5.283e-10 * kg / (pow<3>(m)), 6.010e-10 * kg / (pow<3>(m)) } },
    { 190.0 * km, { 3.617e-10 * kg / (pow<3>(m)), 4.297e-10 * kg / (pow<3>(m)) } },
    { 200.0 * km, { 2.557e-10 * kg / (pow<3>(m)), 3.162e-10 * kg / (pow<3>(m)) } },
    { 210.0 * km, { 1.839e-10 * kg / (pow<3>(m)), 2.396e-10 * kg / (pow<3>(m)) } },
    { 220.0 * km, { 1.341e-10 * kg / (pow<3>(m)), 1.853e-10 * kg / (pow<3>(m)) } },
    { 230.0 * km, { 9.949e-11 * kg / (pow<3>(m)), 1.455e-10 * kg / (pow<3>(m)) } },
    { 240.0 * km, { 7.488e-11 * kg / (pow<3>(m)), 1.157e-10 * kg / (pow<3>(m)) } },
    { 250.0 * km, { 5.709e-11 * kg / (pow<3>(m)), 9.308e-11 * kg / (pow<3>(m)) } },
    { 260.0 * km, { 4.403e-11 * kg / (pow<3>(m)), 7.555e-11 * kg / (pow<3>(m)) } },
    { 270.0 * km, { 3.430e-11 * kg / (pow<3>(m)), 6.182e-11 * kg / (pow<3>(m)) } },
    { 280.0 * km, { 2.697e-11 * kg / (pow<3>(m)), 5.095e-11 * kg / (pow<3>(m)) } },
    { 290.0 * km, { 2.139e-11 * kg / (pow<3>(m)), 4.226e-11 * kg / (pow<3>(m)) } },
    { 300.0 * km, { 1.708e-11 * kg / (pow<3>(m)), 3.526e-11 * kg / (pow<3>(m)) } },
    { 320.0 * km, { 1.099e-11 * kg / (pow<3>(m)), 2.511e-11 * kg / (pow<3>(m)) } },
    { 340.0 * km, { 7.214e-12 * kg / (pow<3>(m)), 1.819e-11 * kg / (pow<3>(m)) } },
    { 360.0 * km, { 4.824e-12 * kg / (pow<3>(m)), 1.337e-11 * kg / (pow<3>(m)) } },
    { 380.0 * km, { 3.274e-12 * kg / (pow<3>(m)), 9.955e-12 * kg / (pow<3>(m)) } },
    { 400.0 * km, { 2.249e-12 * kg / (pow<3>(m)), 7.492e-12 * kg / (pow<3>(m)) } },
    { 420.0 * km, { 1.558e-12 * kg / (pow<3>(m)), 5.684e-12 * kg / (pow<3>(m)) } },
    { 440.0 * km, { 1.091e-12 * kg / (pow<3>(m)), 4.355e-12 * kg / (pow<3>(m)) } },
    { 460.0 * km, { 7.701e-13 * kg / (pow<3>(m)), 3.362e-12 * kg / (pow<3>(m)) } },
    { 480.0 * km, { 5.474e-13 * kg / (pow<3>(m)), 2.612e-12 * kg / (pow<3>(m)) } },
    { 500.0 * km, { 3.916e-13 * kg / (pow<3>(m)), 2.042e-12 * kg / (pow<3>(m)) } },
    { 520.0 * km, { 2.819e-13 * kg / (pow<3>(m)), 1.605e-12 * kg / (pow<3>(m)) } },
    { 540.0 * km, { 2.042e-13 * kg / (pow<3>(m)), 1.267e-12 * kg / (pow<3>(m)) } },
    { 560.0 * km, { 1.488e-13 * kg / (pow<3>(m)), 1.005e-12 * kg / (pow<3>(m)) } },
    { 580.0 * km, { 1.092e-13 * kg / (pow<3>(m)), 7.997e-13 * kg / (pow<3>(m)) } },
    { 600.0 * km, { 8.070e-14 * kg / (pow<3>(m)), 6.390e-13 * kg / (pow<3>(m)) } },
    { 620.0 * km, { 6.012e-14 * kg / (pow<3>(m)), 5.123e-13 * kg / (pow<3>(m)) } },
    { 640.0 * km, { 4.519e-14 * kg / (pow<3>(m)), 4.121e-13 * kg / (pow<3>(m)) } },
    { 660.0 * km, { 3.430e-14 * kg / (pow<3>(m)), 3.325e-13 * kg / (pow<3>(m)) } },
    { 680.0 * km, { 2.632e-14 * kg / (pow<3>(m)), 2.691e-13 * kg / (pow<3>(m)) } },
    { 700.0 * km, { 2.043e-14 * kg / (pow<3>(m)), 2.185e-13 * kg / (pow<3>(m)) } },
    { 720.0 * km, { 1.607e-14 * kg / (pow<3>(m)), 1.779e-13 * kg / (pow<3>(m)) } },
    { 740.0 * km, { 1.281e-14 * kg / (pow<3>(m)), 1.452e-13 * kg / (pow<3>(m)) } },
    { 760.0 * km, { 1.036e-14 * kg / (pow<3>(m)), 1.190e-13 * kg / (pow<3>(m)) } },
    { 780.0 * km, { 8.496e-15 * kg / (pow<3>(m)), 9.776e-14 * kg / (pow<3>(m)) } },
    { 800.0 * km, { 7.069e-15 * kg / (pow<3>(m)), 8.059e-14 * kg / (pow<3>(m)) } },
    { 840.0 * km, { 4.680e-15 * kg / (pow<3>(m)), 5.741e-14 * kg / (pow<3>(m)) } },
    { 880.0 * km, { 3.200e-15 * kg / (pow<3>(m)), 4.210e-14 * kg / (pow<3>(m)) } },
    { 920.0 * km, { 2.210e-15 * kg / (pow<3>(m)), 3.130e-14 * kg / (pow<3>(m)) } },
    { 960.0 * km, { 1.560e-15 * kg / (pow<3>(m)), 2.360e-14 * kg / (pow<3>(m)) } },
    { 1000.0 * km, { 1.150e-15 * kg / (pow<3>(m)), 1.810e-14 * kg / (pow<3>(m)) } }
};


Density HarrisPriesterAtmosphere::find_atmospheric_density(const State& state, const Distance equitorialRadius, const Distance polarRadius)
{
    const auto& position     = state.get_position();
    const auto& positionEcef = state.get_position_in_frame<frames::earth::earth_fixed>();
    const auto [latitude, longitude, altitude] = convert_body_fixed_to_geodetic(positionEcef, equitorialRadius, polarRadius);

    // Diurnal bulge apex direction
    const RadiusVector<frames::solar_system_barycenter::icrf> sun2Earth = get_relative_position<Earth, Sun>(state.get_epoch());
    const UnitVector<frames::earth::icrf> sunDirection = -sun2Earth.unit().force_frame_conversion<frames::earth::icrf>();
    const UnitVector<frames::earth::icrf> bulgeDirection = DCM<frames::earth::icrf, frames::earth::icrf>::Z(LAG) * sunDirection;

    // Cosine of angle Psi between the diurnal bulge apex and the satellite
    const Unitless cosPsi = bulgeDirection.unit().dot(position.unit());
    // (1 + cos(Psi))/2 = cos²(Psi/2)
    const Unitless c2Psi2 = (1.0 * one + cosPsi) / 2.0;
    const Unitless cPsi2  = sqrt(c2Psi2);
    const Unitless cosPow = (cPsi2 > 1.0e-12 * one) ? c2Psi2 * math::pow(cPsi2, (cosineExponent - 2) * one) : Unitless::zero();

    // Search altitude index in density table
    auto iter = HARRIS_PRIESTER_ATMOSPHERE.upper_bound(altitude);
    if (iter != HARRIS_PRIESTER_ATMOSPHERE.end()) {
        // Ensure we can call next safely
        if (iter == std::prev(HARRIS_PRIESTER_ATMOSPHERE.end())) { iter = std::prev(iter); }
        const Distance referenceAltitude = iter->first;
        const auto atmo                  = iter->second;
        const Density minDensity         = std::get<0>(atmo);
        const Density maxDensity         = std::get<1>(atmo);

        const Distance nextReferenceAltitude = std::next(iter)->first;
        const Density nextMinDensity         = std::get<0>(std::next(iter)->second);
        const Density nextMaxDensity         = std::get<1>(std::next(iter)->second);

        // Fractional satellite height
        const Unitless dH = (referenceAltitude - altitude) / (referenceAltitude - nextReferenceAltitude);

        // Min exponential density interpolation
        const Density rhoMin = minDensity * math::pow(nextMinDensity / minDensity, dH);
        if (is_eq_zero(cosPow)) { return rhoMin; }
        else {
            // Max exponential density interpolation
            const Density rhoMax = maxDensity * math::pow(nextMaxDensity / maxDensity, dH);
            return rhoMin + (rhoMax - rhoMin) * cosPow;
        }
    }
    // Beyond the last altitude in the table, the density is negligible
    return Density::zero();
}

} // namespace planets
} // namespace astro
} // namespace astrea