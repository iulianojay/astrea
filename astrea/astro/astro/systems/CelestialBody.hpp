/**
 * @file CelestialBody.hpp
 * @author Jay Iuliano (iuliano.jay@gmail.com)
 * @brief Header file for the CelestialBody class, which represents a celestial body in an astrodynamics system.
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

#include <math/chebyshev_util.hpp>
#include <units/units.hpp>

#include <astro/astro.fwd.hpp>
#include <astro/frames/Axis.hpp>
#include <astro/frames/Frame.hpp>
#include <astro/frames/Origin.hpp>
#include <astro/state/orbital_elements/instances/Keplerian.hpp>
#include <astro/systems/CelestialBodyParameters.hpp>
#include <astro/time/Date.hpp>
#include <astro/types/enums.hpp>
#include <astro/utilities/conversions.hpp>

namespace astrea {
namespace astro {

template <auto...>
struct Barycenter;

template <mp_units::basic_fixed_string _name_>
struct Barycenter<_name_> : Origin<_name_> {};

template <mp_units::basic_fixed_string _name_, IsOrigin auto _parent_>
struct Barycenter<_name_, _parent_> : Origin<_name_, _parent_> {
    using ParentIcrf = Frame<_name_ + "_icrf", _parent_, axes::icrf>; //!< The inertial frame centered on the parent body, used for ephemeris data.
    using ParentJ2000 = Frame<_name_ + "_j2000", _parent_, axes::j2000>; //!< The inertial frame centered on the parent body, used for ephemeris data.
};


/**
 * @brief CelestialBody class represents a celestial body in an astrodynamics system.
 */
template <mp_units::basic_fixed_string _name_, IsOrigin auto _parent_>
struct CelestialBody : Origin<_name_, _parent_> {
    using ParentIcrf = Frame<_name_ + "_icrf", _parent_, axes::icrf>; //!< The inertial frame centered on the parent body, used for ephemeris data.
    using ParentJ2000 = Frame<_name_ + "_j2000", _parent_, axes::j2000>; //!< The inertial frame centered on the parent body, used for ephemeris data.
};

template <CelestialBody _body_>
constexpr auto get_celestial_body_parameters() = delete; // Force specialization for each body

/**
 * @brief Get the type of the celestial body.
 *
 * @return const CelestialBodyType& Reference to the type of the celestial body.
 */
template <CelestialBody _body_>
constexpr const CelestialBodyType& get_type()
{
    return get_celestial_body_parameters<_body_>().type;
};

/**
 * @brief Get the gravitational parameter (mu) of the celestial body.
 *
 * @return const GravParam& Reference to the gravitational parameter of the celestial body.
 */
template <CelestialBody _body_>
constexpr const GravParam& get_mu()
{
    return get_celestial_body_parameters<_body_>().mu;
};

/**
 * @brief Get the mass of the celestial body.
 *
 * @return const Mass& Reference to the mass of the celestial body.
 */
template <CelestialBody _body_>
constexpr const Mass& get_mass()
{
    return get_celestial_body_parameters<_body_>().mass;
};

/**
 * @brief Get the equatorial radius of the celestial body.
 *
 * @return const Distance& Reference to the equatorial radius of the celestial body.
 */
template <CelestialBody _body_>
constexpr const Distance& get_equitorial_radius()
{
    return get_celestial_body_parameters<_body_>().equitorialRadius;
};

/**
 * @brief Get the polar radius of the celestial body.
 *
 * @return const Distance& Reference to the polar radius of the celestial body.
 */
template <CelestialBody _body_>
constexpr const Distance& get_polar_radius()
{
    return get_celestial_body_parameters<_body_>().polarRadius;
};

/**
 * @brief Get the crash radius of the celestial body.
 *
 * @return const Distance& Reference to the crash radius of the celestial body.
 */
template <CelestialBody _body_>
constexpr const Distance& get_crash_radius()
{
    return get_celestial_body_parameters<_body_>().crashRadius;
};

/**
 * @brief Get the sphere of influence of the celestial body.
 *
 * @return const Distance& Reference to the sphere of influence of the celestial body.
 */
template <CelestialBody _body_>
constexpr const Distance& get_sphere_of_influence()
{
    return get_celestial_body_parameters<_body_>().sphereOfInfluence;
};

/**
 * @brief Get the J2 gravitational coefficient of the celestial body.
 *
 * @return const Unitless& Reference to the J2 coefficient of the celestial body.
 */
template <CelestialBody _body_>
constexpr const Unitless& get_j2()
{
    return get_celestial_body_parameters<_body_>().j2;
};

/**
 * @brief Get the J3 gravitational coefficient of the celestial body.
 *
 * @return const Unitless& Reference to the J3 coefficient of the celestial body.
 */
template <CelestialBody _body_>
constexpr const Unitless& get_j3()
{
    return get_celestial_body_parameters<_body_>().j3;
};

/**
 * @brief Get the axial tilt of the celestial body.
 *
 * @return const Angle& Reference to the axial tilt of the celestial body.
 */
template <CelestialBody _body_>
constexpr const Angle& get_axial_tilt()
{
    return get_celestial_body_parameters<_body_>().axialTilt;
};

/**
 * @brief Get the rotation rate of the celestial body.
 *
 * @return const AngularVelocity& Reference to the rotation rate of the celestial body.
 */
template <CelestialBody _body_>
constexpr const AngularVelocity& get_rotation_rate()
{
    return get_celestial_body_parameters<_body_>().rotationRate;
};

/**
 * @brief Get the sidereal period of the celestial body.
 *
 * @return const Time& Reference to the sidereal period of the celestial body.
 */
template <CelestialBody _body_>
constexpr const Time& get_sidereal_period()
{
    return get_celestial_body_parameters<_body_>().siderealPeriod;
};

/**
 * @brief Get the semimajor axis of the celestial body.
 *
 * @return const Distance& Reference to the semimajor axis of the celestial body.
 */
template <CelestialBody _body_>
constexpr Distance get_semimajor(const Date& date)
{
    const mp_units::quantity<JulianCentury> T = get_time_since_reference_epoch<_body_>(date);
    return get_celestial_body_parameters<_body_>().semimajorAxis + get_celestial_body_parameters<_body_>().semimajorAxisRate * T;
};

/**
 * @brief Get the eccentricity of the celestial body.
 *
 * @return const Unitless& Reference to the eccentricity of the celestial body.
 */
template <CelestialBody _body_>
constexpr Unitless get_eccentricity(const Date& date)
{
    const mp_units::quantity<JulianCentury> T = get_time_since_reference_epoch<_body_>(date);
    return get_celestial_body_parameters<_body_>().eccentricity + get_celestial_body_parameters<_body_>().eccentricityRate * T;
};

/**
 * @brief Get the inclination of the celestial body.
 *
 * @return const Angle& Reference to the inclination of the celestial body.
 */
template <CelestialBody _body_>
constexpr Angle get_inclination(const Date& date)
{
    const mp_units::quantity<JulianCentury> T = get_time_since_reference_epoch<_body_>(date);
    return get_celestial_body_parameters<_body_>().inclination + get_celestial_body_parameters<_body_>().inclinationRate * T;
};

/**
 * @brief Get the right ascension of the celestial body.
 *
 * @return const Angle& Reference to the right ascension of the celestial body.
 */
template <CelestialBody _body_>
constexpr Angle get_right_ascension(const Date& date)
{
    const mp_units::quantity<JulianCentury> T = get_time_since_reference_epoch<_body_>(date);
    return get_celestial_body_parameters<_body_>().rightAscension + get_celestial_body_parameters<_body_>().rightAscensionRate * T;
};

/**
 * @brief Get the longitude of perigee of the celestial body.
 *
 * @return const Angle& Reference to the longitude of perigee of the celestial body.
 */
template <CelestialBody _body_>
constexpr Angle get_longitude_of_perigee(const Date& date)
{
    const mp_units::quantity<JulianCentury> T = get_time_since_reference_epoch<_body_>(date);
    return get_celestial_body_parameters<_body_>().longitudeOfPerigee +
           get_celestial_body_parameters<_body_>().longitudeOfPerigeeRate * T;
};

/**
 * @brief Get the mean longitude of the celestial body.
 *
 * @return const Angle& Reference to the mean longitude of the celestial body.
 */
template <CelestialBody _body_>
constexpr Angle get_mean_longitude(const Date& date)
{
    const mp_units::quantity<JulianCentury> T = get_time_since_reference_epoch<_body_>(date);
    return get_celestial_body_parameters<_body_>().meanLongitude + get_celestial_body_parameters<_body_>().meanLongitudeRate * T;
};

/**
 * @brief Get the true anomaly of the celestial body.
 *
 * @return const Angle& Reference to the true anomaly of the celestial body.
 */
template <CelestialBody _body_>
Angle get_true_anomaly(const Date& date)
{
    return wrap_angle(convert_mean_anomaly_to_true_anomaly(get_mean_anomaly<_body_>(date), get_eccentricity<_body_>(date)));
};

/**
 * @brief Get the mean anomaly of the celestial body.
 *
 * @return const Angle& Reference to the mean anomaly of the celestial body.
 */
template <CelestialBody _body_>
constexpr Angle get_mean_anomaly(const Date& date)
{
    const mp_units::quantity<JulianCentury> T = get_time_since_reference_epoch<_body_>(date);
    return get_celestial_body_parameters<_body_>().meanAnomaly + get_celestial_body_parameters<_body_>().meanAnomalyRate * T;
};

/**
 * @brief Get the semimajor axis rate of the celestial body.
 *
 * @return const InterplanetaryVelocity& Reference to the semimajor axis rate of the celestial body.
 */
template <CelestialBody _body_>
constexpr const InterplanetaryVelocity& get_semimajor_rate()
{
    return get_celestial_body_parameters<_body_>().semimajorAxisRate;
};

/**
 * @brief Get the eccentricity rate of the celestial body.
 *
 * @return const BodyUnitlessPerTime& Reference to the eccentricity rate of the celestial body.
 */
template <CelestialBody _body_>
constexpr const BodyUnitlessPerTime& get_eccentricity_rate()
{
    return get_celestial_body_parameters<_body_>().eccentricityRate;
};

/**
 * @brief Get the inclination rate of the celestial body.
 *
 * @return const BodyAngularVelocity& Reference to the inclination rate of the celestial body.
 */
template <CelestialBody _body_>
constexpr const BodyAngularVelocity& get_inclination_rate()
{
    return get_celestial_body_parameters<_body_>().inclinationRate;
};

/**
 * @brief Get the right ascension rate of the celestial body.
 *
 * @return const BodyAngularVelocity& Reference to the right ascension rate of the celestial body.
 */
template <CelestialBody _body_>
constexpr const BodyAngularVelocity& get_right_ascension_rate()
{
    return get_celestial_body_parameters<_body_>().rightAscensionRate;
};

template <CelestialBody _body_>
constexpr auto get_time_since_reference_epoch(const Date& date)
{
    return date - get_celestial_body_parameters<_body_>().referenceDate;
};

/**
 * @brief Get the longitude of perigee rate of the celestial body.
 *
 * @return const BodyAngularVelocity& Reference to the longitude of perigee rate of the celestial body.
 */
template <CelestialBody _body_>
constexpr const BodyAngularVelocity& get_longitude_of_perigee_rate()
{
    return get_celestial_body_parameters<_body_>().longitudeOfPerigeeRate;
};

/**
 * @brief Get the mean longitude rate of the celestial body.
 *
 * @return const BodyAngularVelocity& Reference to the mean longitude rate of the celestial body.
 */
template <CelestialBody _body_>
constexpr const BodyAngularVelocity& get_mean_longitude_rate()
{
    return get_celestial_body_parameters<_body_>().meanLongitudeRate;
};


/**
 * @brief Finds the atmospheric density at a given date and state.
 *
 * @param date The date at which to find the atmospheric density.
 * @param state The Cartesian state vector at which to find the atmospheric density.
 * @return Density The atmospheric density at the specified date and state.
 *
 * @note Assume that most bodies have no significant atmosphere. Assume that
 * the atmosphere of the gas giants is defined by their radii, e.g.
 * outside of their equitorial radius, they have no noticible atmosphere
 * and inside that radius, the object will crash.
 */
template <CelestialBody _body_>
inline constexpr Density find_atmospheric_density(const State& state)
{
    return Density::zero();
}

/**
 * @brief Get the keplerian elements of the celestial body at a specific date using a linear approximation.
 *
 * @param date The date at which to get the state of the celestial body.
 * @return Keplerian The approximate Keplerian elements of the celestial body at the specified date.
 */
template <CelestialBody _body_>
inline constexpr Keplerian get_keplerian_elements_at(const Date& date)
{
    // Keplerian element approximation pulled from here: https://ssd.jpl.nasa.gov/planets/approx_pos.html
    const Distance a   = get_semimajor<_body_>(date);
    const Unitless ecc = get_eccentricity<_body_>(date);
    const Angle inc    = get_inclination<_body_>(date);
    const Angle raan   = get_right_ascension<_body_>(date);
    const Angle w      = get_longitude_of_perigee<_body_>(date);
    const Angle L      = get_mean_longitude<_body_>(date);

    // Time since reference epoch in Julian centuries
    const mp_units::quantity<JulianCentury> T = get_time_since_reference_epoch<_body_>(date);
    const auto [B, C, S, F]                   = get_linear_expansion_coefficients<_body_>();
    const Angle Me                            = wrap_angle(L - w + B * T * T + C * cos(F * T) + S * sin(F * T));
    const Angle argPer                        = wrap_angle(w - raan);

    // This approximation has error on the order of ecc^6
    const Angle thetat = convert_mean_anomaly_to_true_anomaly(Me, ecc);

    return Keplerian(a, ecc, inc, raan, argPer, thetat);
}

/**
 * @brief Get the position of a barycenter at a specific date in its parent ICRF frame. Must be specialized.
 */
template <Barycenter _body_>
inline constexpr CartesianVector<Distance, _body_::ParentIcrf> get_position_at(const Date& date) = delete;

/**
 * @brief Get the velocity of a barycenter at a specific date in its parent ICRF frame. Must be specialized.
 */
template <Barycenter _body_>
inline constexpr CartesianVector<Velocity, _body_::ParentIcrf> get_velocity_at(const Date& date) = delete;

/**
 * @brief Get the position of the celestial body at a specific date in the ICRF frame.
 *
 * @param date The date at which to get the position of the celestial body.
 * @return CartesianVector<Distance, ParentFrame> The position of the celestial body at the specified date.
 *
 * @note This function is wrong. It actually returns the position in the ICRF frame, centered on the object's
 * parent. Need to figure out how to make dynamic centers work with frames.
 */
template <CelestialBody _body_>
inline constexpr CartesianVector<Distance, _body_::ParentIcrf> get_position_at(const Date& date)
{
    // This approximation is in the perifocal frame
    const Keplerian coes         = get_keplerian_elements_at<_body_>(date);
    const Distance a             = coes.get_semimajor();
    const Unitless ecc           = coes.get_eccentricity();
    const Angle inc              = coes.get_inclination();
    const Angle raan             = coes.get_right_ascension();
    const Angle argPer           = coes.get_argument_of_perigee();
    const Angle theta            = coes.get_true_anomaly();
    const Angle Me               = convert_true_anomaly_to_mean_anomaly(theta, ecc);
    const Angle eccentricAnomaly = convert_mean_anomaly_to_eccentric_anomaly(Me, ecc);

    // Position in perifocal frame
    class perifocal;
    const RadiusVector<perifocal> rPerifocal{ a * (cos(eccentricAnomaly) - ecc),
                                              a * sqrt(1 - ecc * ecc) * sin(eccentricAnomaly),
                                              0.0 * m };

    // Perifocal to J2000 transformation: R3(-RAAN) * R1(-inc) * R3(-argPer)
    const DCM<perifocal, ParentJ2000> dcmPeriToJ2000(
        { { cos(argPer) * cos(raan) - sin(argPer) * sin(raan) * cos(inc),
            -sin(argPer) * cos(raan) - cos(argPer) * sin(raan) * cos(inc),
            sin(inc) * sin(raan) },
          { cos(argPer) * sin(raan) + sin(argPer) * cos(raan) * cos(inc),
            -sin(argPer) * sin(raan) + cos(argPer) * cos(raan) * cos(inc),
            -sin(inc) * cos(raan) },
          { sin(argPer) * sin(inc), cos(argPer) * sin(inc), cos(inc) } }
    );
    const RadiusVector<ParentJ2000> rJ2000 = dcmPeriToJ2000 * rPerifocal;

    // Rotate to the ICRF frame
    return rJ2000.in_frame<ParentIcrf>();
}

/**
 * @brief Get the velocity of the celestial body at a specific date in the ICRF frame.
 *
 * @param date The date at which to get the velocity of the celestial body.
 * @return CartesianVector<Velocity, ParentFrame> The velocity of the celestial body at the specified date.
 *
 * @note This function is wrong. It actually returns the velocity in the ICRF frame, centered on the object's
 * parent. Need to figure out how to make dynamic centers work with frames.
 */
template <CelestialBody _body_>
inline constexpr CartesianVector<Velocity, _body_::ParentIcrf> get_velocity_at(const Date& date)
{
    // This approximation is in the perifocal frame
    const Keplerian coes         = get_keplerian_elements_at<_body_>(date);
    const Distance a             = coes.get_semimajor();
    const Unitless ecc           = coes.get_eccentricity();
    const Angle inc              = coes.get_inclination();
    const Angle raan             = coes.get_right_ascension();
    const Angle argPer           = coes.get_argument_of_perigee();
    const Angle theta            = coes.get_true_anomaly();
    const Angle Me               = convert_true_anomaly_to_mean_anomaly(theta, ecc);
    const Angle eccentricAnomaly = convert_mean_anomaly_to_eccentric_anomaly(Me, ecc);

    // Velocity in perifocal frame
    class perifocal;
    const VelocityVector<perifocal> vPerifocal{ -sqrt(get_mu<_body_::Parent>() / (a * (1 - ecc * ecc))) * sin(eccentricAnomaly),
                                                sqrt(get_mu<_body_::Parent>() / (a * (1 - ecc * ecc))) *
                                                    sqrt(1 - ecc * ecc) * cos(eccentricAnomaly),
                                                0.0 * m / s };

    // Perifocal to J2000 transformation: R3(-RAAN) * R1(-inc) * R3(-argPer)
    const DCM<perifocal, _body_::ParentJ2000> dcmPeriToJ2000(
        { { cos(argPer) * cos(raan) - sin(argPer) * sin(raan) * cos(inc),
            -sin(argPer) * cos(raan) - cos(argPer) * sin(raan) * cos(inc),
            sin(inc) * sin(raan) },
          { cos(argPer) * sin(raan) + sin(argPer) * cos(raan) * cos(inc),
            -sin(argPer) * sin(raan) + cos(argPer) * cos(raan) * cos(inc),
            -sin(inc) * cos(raan) },
          { sin(argPer) * sin(inc), cos(argPer) * sin(inc), cos(inc) } }
    );
    const VelocityVector<_body_::ParentJ2000> vJ2000 = dcmPeriToJ2000 * vPerifocal;

    // Rotate to the ICRF frame
    return vJ2000.in_frame<_body_::ParentIcrf>();
}

/**
 * @brief Get the position of the celestial body at a specific date in a specified frame using Chebyshev polynomials.
 *
 * @tparam Table_T The Chebyshev table type to use for interpolation.
 * @tparam frame The frame type in which to return the position.
 * @param date The date at which to get the position of the celestial body.
 * @return CartesianVector<Distance, frame> The position of the celestial body at the specified date in the specified frame.
 */
template <typename Table_T, IsFrame auto frame>
inline constexpr CartesianVector<Distance, frame> get_position_at_impl(const Date& date)
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
inline constexpr CartesianVector<Velocity, frame> get_velocity_at_impl(const Date& date)
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
inline constexpr auto get_chebyshev_table_coefficients(const Date& date)
{
    //! Number of days covered by each set of polynomial coefficients
    static constexpr Time timePerCoefficient = Table_T::TIME_PER_COEFFICIENT;

    // Extract components
    const std::size_t ind = Table_T::get_index(date, timePerCoefficient);
    const auto& xInterp   = Table_T::X_INTERP[ind];
    const auto& yInterp   = Table_T::Y_INTERP[ind];
    const auto& zInterp   = Table_T::Z_INTERP[ind];

    return std::make_tuple(xInterp, yInterp, zInterp);
}

/**
 * @brief Type alias for a tuple of linear expansion coefficients.
 */
using CoefficientPack = std::tuple<
    mp_units::quantity<mp_units::angular::unit_symbols::rad / (JulianCentury * JulianCentury)>,
    mp_units::quantity<mp_units::angular::unit_symbols::rad>,
    mp_units::quantity<mp_units::angular::unit_symbols::rad>,
    mp_units::quantity<mp_units::angular::unit_symbols::rad / JulianCentury>>;

/**
 * @brief Get the linear expansion coefficients for the celestial body's orbital elements.
 *
 * @return CoefficientPack A tuple containing the linear expansion coefficients.
 *
 * @note The default implementation returns zero coefficients, indicating no perturbations.
 *       Derived classes should override this method to provide actual coefficients.
 */
template <CelestialBody _body_>
inline constexpr CoefficientPack get_linear_expansion_coefficients() = delete; // Force specialization for each body

} // namespace astro
} // namespace astrea