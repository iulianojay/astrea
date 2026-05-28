/**
 * @file CelestialBodyFunctions.hpp
 * @author Jay Iuliano (iuliano.jay@gmail.com)
 * @brief Template function definitions for celestial body property accessors and orbital computations.
 * @details Separated from CelestialBody.hpp to break the circular include chain:
 *          CelestialBody.hpp -> CelestialBodyParameters.hpp -> Date.hpp -> CelestialBody.hpp
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

#include <string>

#include <mp-units/systems/angular.h>
#include <mp-units/systems/si.h>

#include <astro/utilities/conversions.hpp>
#include <math/chebyshev_util.hpp>
#include <units/units.hpp>

// CelestialBody.hpp provides the primary template declarations AND includes this file.
// Include it again here to be self-contained; the guard will prevent re-processing.
#include <astro/frames/framework/CartesianVector.hpp>
#include <astro/systems/Barycenter.hpp>
#include <astro/systems/CelestialBody.hpp>
#include <astro/systems/CelestialBodyParameters.hpp>
#include <astro/systems/system_concepts.hpp>
#include <astro/time/Date.hpp>
#include <astro/types/enums.hpp>

// NOTE: CoefficientPack and get_linear_expansion_coefficients must be declared BEFORE
// including any header that pulls in celestial_bodies.hpp, because planet headers specialise
// get_linear_expansion_coefficients.  The primary template must be visible first.
namespace astrea {
namespace astro {

/**
 * @brief Type alias for a tuple of linear expansion coefficients.
 *
 * The four fields are (B, C, S, F):
 *   Me = L - w + B*T^2 + C*cos(F*T) + S*sin(F*T)
 * where T is time since reference epoch in Julian centuries.
 */
using CoefficientPack = std::tuple<
    mp_units::quantity<mp_units::angular::unit_symbols::rad / (JulianCentury * JulianCentury)>,
    mp_units::quantity<mp_units::angular::unit_symbols::rad>,
    mp_units::quantity<mp_units::angular::unit_symbols::rad>,
    mp_units::quantity<mp_units::angular::unit_symbols::rad / JulianCentury>>;

/**
 * @brief Get the linear expansion coefficients for the celestial body's mean anomaly correction.
 *
 * Default implementation returns zero coefficients (no perturbation terms),
 * which reduces to Me = L - w.  Specialise for bodies that need it (e.g. outer planets).
 *
 * @return CoefficientPack A tuple containing (B, C, S, F) coefficients.
 */
template <IsCelestialReference auto body>
inline constexpr CoefficientPack get_linear_expansion_coefficients()
{
    using namespace mp_units::angular::unit_symbols;
    return std::make_tuple(0.0 * rad / (JulianCentury * JulianCentury), 0.0 * rad, 0.0 * rad, 0.0 * rad / JulianCentury);
}

/**
 * @brief Get the type of the celestial body.
 *
 * @return CelestialBodyType Reference to the type of the celestial body.
 */
template <IsCelestialBody auto body>
inline consteval CelestialBodyType get_body_type()
{
    return get_celestial_body_parameters<body>().type;
};

/**
 * @brief Get the gravitational parameter (mu) of the celestial body or barycenter.
 *
 * For a CelestialBody, returns its intrinsic mu from CelestialBodyParameters.
 * For a Barycenter, returns the sum of mu over all member bodies.
 *
 * @return GravParam The gravitational parameter.
 */
template <IsCelestialReference auto body>
inline constexpr GravParam get_mu()
{
    if constexpr (IsBarycenter<decltype(body)>) {
        return [&]<typename... Bs>(const CelestialBodyTypePack<Bs...>&) { return (get_mu<Bs{}>() + ...); }(body);
    }
    else {
        return get_celestial_body_parameters<body>().mu;
    }
};

/**
 * @brief Get the mass of the celestial body.
 *
 * @return Mass Reference to the mass of the celestial body.
 */
template <IsCelestialBody auto body>
inline constexpr Mass get_mass()
{
    return get_celestial_body_parameters<body>().mass;
};

/**
 * @brief Get the equatorial radius of the celestial body.
 *
 * @return Distance Reference to the equatorial radius of the celestial body.
 */
template <IsCelestialBody auto body>
inline constexpr Distance get_equitorial_radius()
{
    return get_celestial_body_parameters<body>().equitorialRadius;
};

/**
 * @brief Get the polar radius of the celestial body.
 *
 * @return Distance Reference to the polar radius of the celestial body.
 */
template <IsCelestialBody auto body>
inline constexpr Distance get_polar_radius()
{
    return get_celestial_body_parameters<body>().polarRadius;
};

/**
 * @brief Get the crash radius of the celestial body.
 *
 * @return Distance Reference to the crash radius of the celestial body.
 */
template <IsCelestialBody auto body>
inline constexpr Distance get_crash_radius()
{
    return get_celestial_body_parameters<body>().crashRadius;
};

/**
 * @brief Get the sphere of influence of the celestial body.
 *
 * @return Distance Reference to the sphere of influence of the celestial body.
 */
template <IsCelestialBody auto body>
inline constexpr Distance get_sphere_of_influence()
{
    return get_celestial_body_parameters<body>().sphereOfInfluence;
};

/**
 * @brief Get the J2 gravitational coefficient of the celestial body.
 *
 * @return Unitless Reference to the J2 coefficient of the celestial body.
 */
template <IsCelestialBody auto body>
inline constexpr Unitless get_j2()
{
    return get_celestial_body_parameters<body>().j2;
};

/**
 * @brief Get the J3 gravitational coefficient of the celestial body.
 *
 * @return Unitless Reference to the J3 coefficient of the celestial body.
 */
template <IsCelestialBody auto body>
inline constexpr Unitless get_j3()
{
    return get_celestial_body_parameters<body>().j3;
};

/**
 * @brief Get the axial tilt of the celestial body.
 *
 * @return Angle Reference to the axial tilt of the celestial body.
 */
template <IsCelestialBody auto body>
inline constexpr Angle get_axial_tilt()
{
    return get_celestial_body_parameters<body>().axialTilt;
};

/**
 * @brief Get the rotation rate of the celestial body.
 *
 * @return AngularVelocity Reference to the rotation rate of the celestial body.
 */
template <IsCelestialBody auto body>
inline constexpr AngularVelocity get_rotation_rate()
{
    return get_celestial_body_parameters<body>().rotationRate;
};

/**
 * @brief Get the sidereal period of the celestial body.
 *
 * @return Time Reference to the sidereal period of the celestial body.
 */
template <IsCelestialBody auto body>
inline constexpr Time get_sidereal_period()
{
    return get_celestial_body_parameters<body>().siderealPeriod;
};

/**
 * @brief Get the semimajor axis of the celestial body.
 *
 * @return Distance Reference to the semimajor axis of the celestial body.
 */
template <IsCelestialBody auto body>
inline constexpr Distance get_semimajor(Date date)
{
    const mp_units::quantity<JulianCentury> T = get_time_since_reference_epoch<body>(date);
    return get_celestial_body_parameters<body>().semimajorAxis + get_celestial_body_parameters<body>().semimajorAxisRate * T;
};

/**
 * @brief Get the eccentricity of the celestial body.
 *
 * @return Unitless Reference to the eccentricity of the celestial body.
 */
template <IsCelestialBody auto body>
inline constexpr Unitless get_eccentricity(Date date)
{
    const mp_units::quantity<JulianCentury> T = get_time_since_reference_epoch<body>(date);
    return get_celestial_body_parameters<body>().eccentricity + get_celestial_body_parameters<body>().eccentricityRate * T;
};

/**
 * @brief Get the inclination of the celestial body.
 *
 * @return Angle Reference to the inclination of the celestial body.
 */
template <IsCelestialBody auto body>
inline constexpr Angle get_inclination(Date date)
{
    const mp_units::quantity<JulianCentury> T = get_time_since_reference_epoch<body>(date);
    return get_celestial_body_parameters<body>().inclination + get_celestial_body_parameters<body>().inclinationRate * T;
};

/**
 * @brief Get the right ascension of the celestial body.
 *
 * @return Angle Reference to the right ascension of the celestial body.
 */
template <IsCelestialBody auto body>
inline constexpr Angle get_right_ascension(Date date)
{
    const mp_units::quantity<JulianCentury> T = get_time_since_reference_epoch<body>(date);
    return get_celestial_body_parameters<body>().rightAscension + get_celestial_body_parameters<body>().rightAscensionRate * T;
};

/**
 * @brief Get the longitude of perigee of the celestial body.
 *
 * @return Angle Reference to the longitude of perigee of the celestial body.
 */
template <IsCelestialBody auto body>
inline constexpr Angle get_longitude_of_perigee(Date date)
{
    const mp_units::quantity<JulianCentury> T = get_time_since_reference_epoch<body>(date);
    return get_celestial_body_parameters<body>().longitudeOfPerigee +
           get_celestial_body_parameters<body>().longitudeOfPerigeeRate * T;
};

/**
 * @brief Get the mean longitude of the celestial body.
 *
 * @return Angle Reference to the mean longitude of the celestial body.
 */
template <IsCelestialBody auto body>
inline constexpr Angle get_mean_longitude(Date date)
{
    const mp_units::quantity<JulianCentury> T = get_time_since_reference_epoch<body>(date);
    return get_celestial_body_parameters<body>().meanLongitude + get_celestial_body_parameters<body>().meanLongitudeRate * T;
};

/**
 * @brief Get the true anomaly of the celestial body.
 *
 * @return Angle Reference to the true anomaly of the celestial body.
 */
template <IsCelestialBody auto body>
inline constexpr Angle get_true_anomaly(Date date)
{
    return wrap_angle(convert_mean_anomaly_to_true_anomaly(get_mean_anomaly<body>(date), get_eccentricity<body>(date)));
};

/**
 * @brief Get the mean anomaly of the celestial body.
 *
 * @return Angle Reference to the mean anomaly of the celestial body.
 */
template <IsCelestialBody auto body>
inline constexpr Angle get_mean_anomaly(Date date)
{
    const mp_units::quantity<JulianCentury> T = get_time_since_reference_epoch<body>(date);
    return get_celestial_body_parameters<body>().meanAnomaly + get_celestial_body_parameters<body>().meanAnomalyRate * T;
};

/**
 * @brief Get the semimajor axis rate of the celestial body.
 *
 * @return InterplanetaryVelocity Reference to the semimajor axis rate of the celestial body.
 */
template <IsCelestialBody auto body>
inline constexpr InterplanetaryVelocity get_semimajor_rate()
{
    return get_celestial_body_parameters<body>().semimajorAxisRate;
};

/**
 * @brief Get the eccentricity rate of the celestial body.
 *
 * @return BodyUnitlessPerTime Reference to the eccentricity rate of the celestial body.
 */
template <IsCelestialBody auto body>
inline constexpr BodyUnitlessPerTime get_eccentricity_rate()
{
    return get_celestial_body_parameters<body>().eccentricityRate;
};

/**
 * @brief Get the inclination rate of the celestial body.
 *
 * @return BodyAngularVelocity Reference to the inclination rate of the celestial body.
 */
template <IsCelestialBody auto body>
inline constexpr BodyAngularVelocity get_inclination_rate()
{
    return get_celestial_body_parameters<body>().inclinationRate;
};

/**
 * @brief Get the right ascension rate of the celestial body.
 *
 * @return BodyAngularVelocity Reference to the right ascension rate of the celestial body.
 */
template <IsCelestialBody auto body>
inline constexpr BodyAngularVelocity get_right_ascension_rate()
{
    return get_celestial_body_parameters<body>().rightAscensionRate;
};

template <IsCelestialBody auto body>
inline constexpr auto get_time_since_reference_epoch(Date date)
{
    return date - get_celestial_body_parameters<body>().referenceDate;
};

/**
 * @brief Get the longitude of perigee rate of the celestial body.
 *
 * @return BodyAngularVelocity Reference to the longitude of perigee rate of the celestial body.
 */
template <IsCelestialBody auto body>
inline constexpr BodyAngularVelocity get_longitude_of_perigee_rate()
{
    return get_celestial_body_parameters<body>().longitudeOfPerigeeRate;
};

/**
 * @brief Get the mean longitude rate of the celestial body.
 *
 * @return BodyAngularVelocity Reference to the mean longitude rate of the celestial body.
 */
template <IsCelestialBody auto body>
inline constexpr BodyAngularVelocity get_mean_longitude_rate()
{
    return get_celestial_body_parameters<body>().meanLongitudeRate;
};

/**
 * @brief Get the position of the celestial body at a specific date in a specified frame using Chebyshev polynomials.
 *
 * @tparam Table_T The Chebyshev table type to use for interpolation.
 * @tparam frame The frame type in which to return the position.
 * @param date The date at which to get the position of the celestial body.
 * @return CartesianVector<Distance, frame> The position of the celestial body at the specified date in the specified frame.
 */
template <typename Table_T, IsFrame auto frame>
inline constexpr CartesianVector<Distance, frame> get_position_at_impl(Date date)
{
    using mp_units::si::unit_symbols::km;

    static const double _COEFF_ZERO_FACTOR = 1.0;

    // Evaluate Chebyshev polynomials
    const auto [xInterp, yInterp, zInterp] = get_chebyshev_table_coefficients<Table_T>(date);
    const double mjd                       = (date.mjd() - Date(J2000).mjd()).count();

    const Distance x = math::evaluate_chebyshev_polynomial(mjd, xInterp, _COEFF_ZERO_FACTOR) * km;
    const Distance y = math::evaluate_chebyshev_polynomial(mjd, yInterp, _COEFF_ZERO_FACTOR) * km;
    const Distance z = math::evaluate_chebyshev_polynomial(mjd, zInterp, _COEFF_ZERO_FACTOR) * km;

    return CartesianVector<Distance, frame>(x, y, z);
}

/**
 * @brief Get the velocity of the celestial body at a specific date in a specified frame using Chebyshev polynomials.
 *
 * @tparam Table_T The Chebyshev table type to use for interpolation.
 * @tparam frame The frame type in which to return the velocity.
 * @param date The date at which to get the velocity of the celestial body.
 * @return CartesianVector<Velocity, frame> The velocity of the celestial body at the specified date in the specified frame.
 */
template <typename Table_T, IsFrame auto frame>
inline constexpr CartesianVector<Velocity, frame> get_velocity_at_impl(Date date)
{
    using mp_units::non_si::day;
    using mp_units::si::unit_symbols::km;

    static const double _COEFF_ZERO_FACTOR = 1.0;

    // Evaluate Chebyshev polynomials
    const auto [xInterp, yInterp, zInterp] = get_chebyshev_table_coefficients<Table_T>(date);
    const double mjd                       = (date.mjd() - Date(J2000).mjd()).count();

    const Velocity vx = math::evaluate_chebyshev_derivative(mjd, xInterp, _COEFF_ZERO_FACTOR) * km / day;
    const Velocity vy = math::evaluate_chebyshev_derivative(mjd, yInterp, _COEFF_ZERO_FACTOR) * km / day;
    const Velocity vz = math::evaluate_chebyshev_derivative(mjd, zInterp, _COEFF_ZERO_FACTOR) * km / day;

    return CartesianVector<Velocity, frame>(vx, vy, vz);
}

/**
 * @brief Get the Chebyshev polynomial coefficients for the celestial body at a specific date.
 *
 * @tparam Table_T The Chebyshev table type to use for interpolation.
 * @param date The date at which to get the Chebyshev coefficients.
 * @return A tuple containing references to the x, y, and z Chebyshev coefficient vectors.
 */
template <typename Table_T>
inline constexpr auto get_chebyshev_table_coefficients(Date date)
{
    //! Number of days covered by each set of polynomial coefficients
    static constexpr Time timePerCoefficient = Table_T::TIME_PER_COEFFICIENT;

    // Extract components
    const std::size_t ind = Table_T::get_index(date, timePerCoefficient);
    auto xInterp          = Table_T::X_INTERP[ind];
    auto yInterp          = Table_T::Y_INTERP[ind];
    auto zInterp          = Table_T::Z_INTERP[ind];

    return std::make_tuple(xInterp, yInterp, zInterp);
}

/**
 * @brief Compute the equivalent of Greenwich Sidereal Time for an arbitrary celestial body.
 *
 * Computes the accumulated rotation angle of the body's prime meridian relative to its
 * inertial reference direction since J2000, using the body's rotation rate.
 *
 * @param date The Julian date at which to evaluate the angle.
 * @return Angle The body's prime meridian rotation angle, wrapped to [0, 2π).
 */
template <IsCelestialBody auto body>
inline constexpr Angle julian_date_to_body_sidereal_time(JulianDate date)
{
    using mp_units::non_si::day;

    // Elapsed time since J2000 in seconds
    const Time elapsed = (date.time_since_epoch().count() - J2000.time_since_epoch().count()) * day;

    // Accumulated rotation of the body's prime meridian since J2000
    return wrap_angle(get_rotation_rate<body>() * elapsed);
}

/**
 * @brief Get the body-fixed rotating frame for a celestial body.
 *
 * Returns a Z-rotation body-fixed frame for @p body. For well-known bodies
 * (e.g. Earth) an explicit specialisation in the appropriate platform header
 * returns the canonical named frame instance so that existing DCM
 * specialisations are reused.
 *
 * @tparam body The celestial body NTTP.
 * @return A constexpr BodyFixedFrame value centred at body.
 */
template <IsCelestialBody auto body>
inline consteval auto get_body_fixed_frame()
{
    return BodyFixedFrame<body.name + mp_units::symbol_text{ "_fixed" }, body>{};
}

} // namespace astro
} // namespace astrea
