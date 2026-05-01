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

#include <astro/systems/planetary_bodies/Earth/Earth.hpp>

#include <map>

#include <mp-units/math.h>
#include <mp-units/systems/angular.h>

#include <math/math.hpp>

#ifdef ASTREA_BUILD_EARTH_EPHEMERIS
#include <astro/state/orbital_elements/OrbitalElements.hpp>
#include <ephemerides/Earth/EarthFromEmbEphemerisTable.hpp>
#include <ephemerides/Earth/EmbEphemerisTable.hpp>
#endif // ASTREA_BUILD_EARTH_EPHEMERIS

#include <astro/state/State.hpp>
#include <astro/state/angular_elements/instances/Geodetic.hpp>

namespace astrea {
namespace astro {
namespace planetary_bodies {

using namespace mp_units;
using mp_units::non_si::day;
using mp_units::si::unit_symbols::kg;
using mp_units::si::unit_symbols::km;
using mp_units::si::unit_symbols::m;
using mp_units::si::unit_symbols::s;

// Altitude Conditions(TABLE 7-4, Vallado)
static const std::map<Altitude, std::tuple<Altitude, Density, Altitude>> JACHIA_ROBERTS_ATMOSPHERE = {
    { 25.0 * km, { 0.0 * km, 1.225 * kg / (pow<3>(m)), 7.249 * km } },
    { 30.0 * km, { 25.0 * km, 3.899e-2 * kg / (pow<3>(m)), 6.349 * km } },
    { 40.0 * km, { 30.0 * km, 1.774e-2 * kg / (pow<3>(m)), 6.682 * km } },
    { 50.0 * km, { 40.0 * km, 3.972e-3 * kg / (pow<3>(m)), 7.554 * km } },
    { 60.0 * km, { 50.0 * km, 1.057e-3 * kg / (pow<3>(m)), 8.382 * km } },
    { 70.0 * km, { 60.0 * km, 3.206e-4 * kg / (pow<3>(m)), 7.714 * km } },
    { 80.0 * km, { 70.0 * km, 8.770e-5 * kg / (pow<3>(m)), 6.549 * km } },
    { 90.0 * km, { 80.0 * km, 1.905e-5 * kg / (pow<3>(m)), 5.799 * km } },
    { 100.0 * km, { 90.0 * km, 3.396e-6 * kg / (pow<3>(m)), 5.382 * km } },
    { 110.0 * km, { 100.0 * km, 5.297e-7 * kg / (pow<3>(m)), 5.877 * km } },
    { 120.0 * km, { 110.0 * km, 9.661e-8 * kg / (pow<3>(m)), 7.263 * km } },
    { 130.0 * km, { 120.0 * km, 2.438e-8 * kg / (pow<3>(m)), 9.473 * km } },
    { 140.0 * km, { 130.0 * km, 8.484e-9 * kg / (pow<3>(m)), 12.636 * km } },
    { 150.0 * km, { 140.0 * km, 3.845e-9 * kg / (pow<3>(m)), 16.149 * km } },
    { 180.0 * km, { 150.0 * km, 2.070e-9 * kg / (pow<3>(m)), 22.523 * km } },
    { 200.0 * km, { 180.0 * km, 5.464e-10 * kg / (pow<3>(m)), 29.740 * km } },
    { 250.0 * km, { 200.0 * km, 2.789e-10 * kg / (pow<3>(m)), 37.105 * km } },
    { 300.0 * km, { 250.0 * km, 7.248e-11 * kg / (pow<3>(m)), 45.546 * km } },
    { 350.0 * km, { 300.0 * km, 2.418e-11 * kg / (pow<3>(m)), 53.628 * km } },
    { 400.0 * km, { 350.0 * km, 9.158e-12 * kg / (pow<3>(m)), 53.298 * km } },
    { 450.0 * km, { 400.0 * km, 3.725e-12 * kg / (pow<3>(m)), 58.515 * km } },
    { 500.0 * km, { 450.0 * km, 1.585e-12 * kg / (pow<3>(m)), 60.828 * km } },
    { 600.0 * km, { 500.0 * km, 6.967e-13 * kg / (pow<3>(m)), 63.822 * km } },
    { 700.0 * km, { 600.0 * km, 1.454e-13 * kg / (pow<3>(m)), 71.835 * km } },
    { 800.0 * km, { 700.0 * km, 3.614e-14 * kg / (pow<3>(m)), 88.667 * km } },
    { 900.0 * km, { 800.0 * km, 1.170e-14 * kg / (pow<3>(m)), 124.64 * km } },
    { 1000.0 * km, { 900.0 * km, 5.245e-15 * kg / (pow<3>(m)), 181.05 * km } },
    { 1100.0 * km, { 1000.0 * km, 2.019e-15 * kg / (pow<3>(m)), 268.00 * km } }
};

Density Earth::find_jachia_roberts_atmospheric_density(const State& state) const
{

    const auto& position = state.get_position_in_frame<frames::earth::earth_fixed>();
    const auto [latitude, longitude, altitude] =
        convert_body_fixed_to_geodetic(position, get_equitorial_radius(), get_polar_radius());

    Distance referenceAltitude;
    Density referenceDensity;
    Distance scaleHeight;

    const auto iter = JACHIA_ROBERTS_ATMOSPHERE.upper_bound(altitude);
    if (iter != JACHIA_ROBERTS_ATMOSPHERE.end()) {
        const auto atmo   = iter->second;
        referenceAltitude = std::get<0>(atmo);
        referenceDensity  = std::get<1>(atmo);
        scaleHeight       = std::get<2>(atmo);
    }
    else {
        referenceAltitude = 1100.0 * km;
        referenceDensity  = 0.0 * kg / (m * m * m);
        scaleHeight       = 1.0 * km;
    }

    return referenceDensity * exp((referenceAltitude - altitude) / scaleHeight);
}

/** Default cosine exponent value. */
static const int cosineExponent = 4;

/** Lag angle for diurnal bulge. */
static const Angle LAG = 30.0 * deg;

// CHECKSTYLE: stop NoWhitespaceAfter check
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

Density Earth::find_harris_priester_atmospheric_density(const State& state) const
{
    const auto& position     = state.get_position();
    const auto& positionEcef = state.get_position_in_frame<frames::earth::earth_fixed>();
    const auto [latitude, longitude, altitude] =
        convert_body_fixed_to_geodetic(positionEcef, get_equitorial_radius(), get_polar_radius());

    // Diurnal bulge apex direction
    const RadiusVector<frames::solar_system_barycenter::icrf> sun2Earth = get_position_at(state.get_epoch());
    const UnitVector<frames::earth::icrf> sunDirection = -sun2Earth.unit().force_frame_conversion<frames::earth::icrf>();
    const UnitVector<frames::earth::icrf> bulgeDirection = DCM<frames::earth::icrf, frames::earth::icrf>::Z(LAG) * sunDirection;

    // Cosine of angle Psi between the diurnal bulge apex and the satellite
    const Unitless cosPsi = bulgeDirection.unit().dot(position.unit());
    // (1 + cos(Psi))/2 = cos²(Psi/2)
    const Unitless c2Psi2 = (1.0 * one + cosPsi) / 2.0;
    const Unitless cPsi2  = sqrt(c2Psi2);
    const Unitless cosPow = (cPsi2 > 1.0e-12 * one) ? c2Psi2 * math::pow(cPsi2, (cosineExponent - 2) * one) : Unitless::zero();

    // Search altitude index in density table
    const auto iter = HARRIS_PRIESTER_ATMOSPHERE.upper_bound(altitude);
    if (iter != HARRIS_PRIESTER_ATMOSPHERE.end()) {
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

Density Earth::find_atmospheric_density(const State& state) const
{
    switch (_atmosphereModel) {
        case EarthAtmosphereModel::JACHIA_ROBERTS: return find_jachia_roberts_atmospheric_density(state);
        case EarthAtmosphereModel::HARRIS_PRIESTER: return find_harris_priester_atmospheric_density(state);
        case EarthAtmosphereModel::NRLMSISE00:
        case EarthAtmosphereModel::DTM2000:
        default: throw std::runtime_error("Selected atmospheric model not implemented yet");
    }
}

#ifdef ASTREA_BUILD_EARTH_EPHEMERIS

RadiusVector<frames::solar_system_barycenter::icrf> Earth::get_position_at(const Date& date) const
{
    const auto positionEmbFromSsb = get_position_at_impl<EmbEphemerisTable, frames::solar_system_barycenter::icrf>(date);
    const auto positionEarthFromEmb = get_position_at_impl<EarthFromEmbEphemerisTable, frames::earth_barycenter::icrf>(date);
    return positionEmbFromSsb + positionEarthFromEmb.force_frame_conversion<frames::solar_system_barycenter::icrf>();
}

VelocityVector<frames::solar_system_barycenter::icrf> Earth::get_velocity_at(const Date& date) const
{
    const auto velocityEarthFromEmb = get_velocity_at_impl<EarthFromEmbEphemerisTable, frames::earth_barycenter::icrf>(date);
    return velocityEarthFromEmb.force_frame_conversion<frames::solar_system_barycenter::icrf>();
}

#endif // ASTREA_BUILD_EARTH_EPHEMERIS

} // namespace planetary_bodies
} // namespace astro
} // namespace astrea