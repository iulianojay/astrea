/**
 * @file Earth.hpp
 * @author Jay Iuliano (iuliano.jay@gmail.com)
 * @brief Header file for the Earth class.
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

#include <mp-units/systems/angular.h>
#include <mp-units/systems/iau.h>
#include <mp-units/systems/si.h>

#include <units/units.hpp>

#include <astro/astro.fwd.hpp>
#include <astro/systems/CelestialBody.hpp>
#include <astro/types/typedefs.hpp>

namespace astrea {
namespace astro {
namespace planetary_bodies {

enum class EarthAtmosphereModel { JACHIA_ROBERTS, NRLMSISE00, DTM2000, HARRIS_PRIESTER };

struct EarthParameters {
    EarthAtmosphereModel atmosphereModel = EarthAtmosphereModel::JACHIA_ROBERTS; //!< The atmospheric model to use for Earth.
};

static const CelestialBodyParameters DEFAULT_EARTH_PARAMS{
    .name          = "Earth",
    .parent        = CelestialBodyId::SUN,
    .type          = CelestialBodyType::PLANET,
    .referenceDate = Date("2000-01-01 12:00:00"),
    .mu = GravParam(398600.44189 * mp_units::pow<3>(mp_units::si::unit_symbols::km) / mp_units::pow<2>(mp_units::si::unit_symbols::s)),
    .mass              = Mass(5.97 * (mp_units::mag_power<10, 24> * mp_units::si::unit_symbols::kg)),
    .equitorialRadius  = Distance(6378.137 * mp_units::si::unit_symbols::km),
    .polarRadius       = Distance(6356.75538082 * mp_units::si::unit_symbols::km),
    .crashRadius       = Distance(6478.1 * mp_units::si::unit_symbols::km),
    .sphereOfInfluence = Distance(0.092449582665046 * mp_units::iau::unit_symbols::au),
    .j2                = Unitless(0.00108262982 * mp_units::one),
    .j3                = Unitless(-0.0000025323 * mp_units::one),
    .axialTilt         = Angle(23.439292 * mp_units::angular::unit_symbols::deg),
    .rotationRate = AngularVelocity(7.29211514670638e-5 * mp_units::angular::unit_symbols::rad / mp_units::si::unit_symbols::s),
    .siderealPeriod         = Time(365.256 * mp_units::non_si::day),
    .semimajorAxis          = Distance(1.00000261 * mp_units::iau::unit_symbols::au),
    .eccentricity           = Unitless(0.01671123 * mp_units::one),
    .inclination            = Angle(-0.00001531 * mp_units::angular::unit_symbols::deg),
    .rightAscension         = Angle(0.0 * mp_units::angular::unit_symbols::deg),
    .longitudeOfPerigee     = Angle(102.93768193 * mp_units::angular::unit_symbols::deg),
    .meanLongitude          = Angle(100.46457166 * mp_units::angular::unit_symbols::deg),
    .semimajorAxisRate      = InterplanetaryVelocity(0.00000562 * mp_units::iau::unit_symbols::au / JulianCentury),
    .eccentricityRate       = BodyUnitlessPerTime(-0.00004392 * mp_units::one / JulianCentury),
    .inclinationRate        = BodyAngularVelocity(-0.01294668 * mp_units::angular::unit_symbols::deg / JulianCentury),
    .rightAscensionRate     = BodyAngularVelocity(0.0 * mp_units::angular::unit_symbols::deg / JulianCentury),
    .longitudeOfPerigeeRate = BodyAngularVelocity(0.32327364 * mp_units::angular::unit_symbols::deg / JulianCentury),
    .meanLongitudeRate      = BodyAngularVelocity(35999.37244981 * mp_units::angular::unit_symbols::deg / JulianCentury)
};

/**
 * @class Earth
 * @brief Represents the Earth celestial body.
 *
 * This class provides properties and methods specific to Earth, including its physical and orbital parameters.
 */
class Earth : public CelestialBody {

  public:
    using CelestialBody::CelestialBody;

    /**
     * @brief Default constructor for the Earth class.
     *
     * Initializes the Earth object with predefined physical and orbital parameters.
     */
    constexpr Earth() :
        CelestialBody(DEFAULT_EARTH_PARAMS),
        _atmosphereModel(EarthAtmosphereModel::JACHIA_ROBERTS)
    {
    }

    /**
     * @brief Constructor for the Earth class with custom parameters.
     * @param params The EarthParameters struct containing custom parameters for the Earth object.
     */
    constexpr Earth(const CelestialBodyParameters& params, const EarthParameters& earthParams) :
        CelestialBody(params),
        _atmosphereModel(earthParams.atmosphereModel)
    {
    }

    /**
     * @brief Default destructor for the Earth class.
     */
    ~Earth() = default;

    /**
     * @brief Find the atmospheric density at a given date and altitude using the US Standard Atmosphere 1976 model.
     *
     * @param date The date for which to find the atmospheric density.
     * @param altitude The altitude at which to find the atmospheric density.
     * @return Density The atmospheric density at the given date and altitude.
     * @note Numbers for this model are pulled from Vallado, 5th ed.
     */
    Density find_atmospheric_density(const State& state) const override;

    /**
     * @brief Get the unique identifier for the Earth celestial body.
     *
     * @return CelestialBodyId The unique identifier for Earth.
     */
    static constexpr CelestialBodyId get_id() { return CelestialBodyId::EARTH; };

#ifdef ASTREA_BUILD_EARTH_EPHEMERIS

    /**
     * @brief Get the position of the Earth at a specific date in the ICRF frame using JPL DE430 ephemeris data.
     *
     * @param date The date for which to find the position of the Earth.
     * @return RadiusVector<frames::solar_system_barycenter::icrf> The position of the Earth at the given date.
     */
    RadiusVector<frames::solar_system_barycenter::icrf> get_position_at(const Date& date) const;

    /**
     * @brief Get the velocity of the Earth at a specific date in the ICRF frame using JPL DE430 ephemeris data.
     *
     * @param date The date for which to find the velocity of the Earth.
     * @return VelocityVector<frames::solar_system_barycenter::icrf> The velocity of the Earth at the given date.
     */
    VelocityVector<frames::solar_system_barycenter::icrf> get_velocity_at(const Date& date) const;

#endif // ASTREA_BUILD_EARTH_EPHEMERIS

    /**
     * @brief Find the atmospheric density at a given state using the Jachia-Roberts atmospheric model.
     *
     * @param state The state for which to find the atmospheric density.
     * @return Density The atmospheric density at the given state.
     */
    Density find_jachia_roberts_atmospheric_density(const State& state) const;

    /**
     * @brief Find the atmospheric density at a given state using the Harris-Priester atmospheric model.
     *
     * @param state The state for which to find the atmospheric density.
     * @return Density The atmospheric density at the given state.
     */
    Density find_harris_priester_atmospheric_density(const State& state) const;

  private:
    EarthAtmosphereModel _atmosphereModel; //!< The atmospheric model to use for Earth.
};

} // namespace planetary_bodies
} // namespace astro
} // namespace astrea