

# File property\_getters.hpp

[**File List**](files.md) **>** [**astrea**](dir_b5324400686b7cece921533bb760c87a.md) **>** [**astro**](dir_1d4dcf10fc541574a93624f5c09a3d6f.md) **>** [**astro**](dir_84db6e3c60e44147f5214c05dc45afc2.md) **>** [**systems**](dir_a5d35e082abd602943cf6d70fa2a6872.md) **>** [**property\_getters.hpp**](property__getters_8hpp.md)

[Go to the documentation of this file](property__getters_8hpp.md)


```C++

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

using CoefficientPack = std::tuple<
    mp_units::quantity<mp_units::angular::unit_symbols::rad / (JulianCentury * JulianCentury)>,
    mp_units::quantity<mp_units::angular::unit_symbols::rad>,
    mp_units::quantity<mp_units::angular::unit_symbols::rad>,
    mp_units::quantity<mp_units::angular::unit_symbols::rad / JulianCentury>>;

template <IsCelestialReference auto body>
inline constexpr CoefficientPack get_linear_expansion_coefficients()
{
    using namespace mp_units::angular::unit_symbols;
    return std::make_tuple(0.0 * rad / (JulianCentury * JulianCentury), 0.0 * rad, 0.0 * rad, 0.0 * rad / JulianCentury);
}

template <IsCelestialBody auto body>
inline consteval CelestialBodyType get_body_type()
{
    return get_celestial_body_parameters<body>().type;
};

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

template <IsCelestialBody auto body>
inline constexpr Mass get_mass()
{
    return get_celestial_body_parameters<body>().mass;
};

template <IsCelestialBody auto body>
inline constexpr Distance get_equitorial_radius()
{
    return get_celestial_body_parameters<body>().equitorialRadius;
};

template <IsCelestialBody auto body>
inline constexpr Distance get_polar_radius()
{
    return get_celestial_body_parameters<body>().polarRadius;
};

template <IsCelestialBody auto body>
inline constexpr Distance get_crash_radius()
{
    return get_celestial_body_parameters<body>().crashRadius;
};

template <IsCelestialBody auto body>
inline constexpr Distance get_sphere_of_influence()
{
    return get_celestial_body_parameters<body>().sphereOfInfluence;
};

template <IsCelestialBody auto body>
inline constexpr Unitless get_j2()
{
    return get_celestial_body_parameters<body>().j2;
};

template <IsCelestialBody auto body>
inline constexpr Unitless get_j3()
{
    return get_celestial_body_parameters<body>().j3;
};

template <IsCelestialBody auto body>
inline constexpr Angle get_axial_tilt()
{
    return get_celestial_body_parameters<body>().axialTilt;
};

template <IsCelestialBody auto body>
inline constexpr AngularVelocity get_rotation_rate()
{
    return get_celestial_body_parameters<body>().rotationRate;
};

template <IsCelestialBody auto body>
inline constexpr Time get_sidereal_period()
{
    return get_celestial_body_parameters<body>().siderealPeriod;
};

template <IsCelestialBody auto body>
inline constexpr Distance get_semimajor(Date date)
{
    const mp_units::quantity<JulianCentury> T = get_time_since_reference_epoch<body>(date);
    return get_celestial_body_parameters<body>().semimajorAxis + get_celestial_body_parameters<body>().semimajorAxisRate * T;
};

template <IsCelestialBody auto body>
inline constexpr Unitless get_eccentricity(Date date)
{
    const mp_units::quantity<JulianCentury> T = get_time_since_reference_epoch<body>(date);
    return get_celestial_body_parameters<body>().eccentricity + get_celestial_body_parameters<body>().eccentricityRate * T;
};

template <IsCelestialBody auto body>
inline constexpr Angle get_inclination(Date date)
{
    const mp_units::quantity<JulianCentury> T = get_time_since_reference_epoch<body>(date);
    return get_celestial_body_parameters<body>().inclination + get_celestial_body_parameters<body>().inclinationRate * T;
};

template <IsCelestialBody auto body>
inline constexpr Angle get_right_ascension(Date date)
{
    const mp_units::quantity<JulianCentury> T = get_time_since_reference_epoch<body>(date);
    return get_celestial_body_parameters<body>().rightAscension + get_celestial_body_parameters<body>().rightAscensionRate * T;
};

template <IsCelestialBody auto body>
inline constexpr Angle get_longitude_of_perigee(Date date)
{
    const mp_units::quantity<JulianCentury> T = get_time_since_reference_epoch<body>(date);
    return get_celestial_body_parameters<body>().longitudeOfPerigee +
           get_celestial_body_parameters<body>().longitudeOfPerigeeRate * T;
};

template <IsCelestialBody auto body>
inline constexpr Angle get_mean_longitude(Date date)
{
    const mp_units::quantity<JulianCentury> T = get_time_since_reference_epoch<body>(date);
    return get_celestial_body_parameters<body>().meanLongitude + get_celestial_body_parameters<body>().meanLongitudeRate * T;
};

template <IsCelestialBody auto body>
inline constexpr Angle get_true_anomaly(Date date)
{
    return wrap_angle(convert_mean_anomaly_to_true_anomaly(get_mean_anomaly<body>(date), get_eccentricity<body>(date)));
};

template <IsCelestialBody auto body>
inline constexpr Angle get_mean_anomaly(Date date)
{
    const auto L    = get_mean_longitude<body>(date);
    const auto w    = get_longitude_of_perigee<body>(date);
    const auto raan = get_right_ascension<body>(date);
    return wrap_angle(L - w - raan);
};

template <IsCelestialBody auto body>
inline constexpr InterplanetaryVelocity get_semimajor_rate()
{
    return get_celestial_body_parameters<body>().semimajorAxisRate;
};

template <IsCelestialBody auto body>
inline constexpr BodyUnitlessPerTime get_eccentricity_rate()
{
    return get_celestial_body_parameters<body>().eccentricityRate;
};

template <IsCelestialBody auto body>
inline constexpr BodyAngularVelocity get_inclination_rate()
{
    return get_celestial_body_parameters<body>().inclinationRate;
};

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

template <IsCelestialBody auto body>
inline constexpr BodyAngularVelocity get_longitude_of_perigee_rate()
{
    return get_celestial_body_parameters<body>().longitudeOfPerigeeRate;
};

template <IsCelestialBody auto body>
inline constexpr BodyAngularVelocity get_mean_longitude_rate()
{
    return get_celestial_body_parameters<body>().meanLongitudeRate;
};

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

template <typename Table_T, IsFrame auto frame>
inline constexpr CartesianVector<Acceleration, frame> get_acceleration_at_impl(Date date)
{
    using mp_units::non_si::day;
    using mp_units::si::unit_symbols::km;

    static constexpr Time timePerCoefficient = Table_T::TIME_PER_COEFFICIENT;
    static const double _COEFF_ZERO_FACTOR   = 1.0;

    // Evaluate Chebyshev polynomials
    const auto [xInterp, yInterp, zInterp] = get_chebyshev_table_coefficients<Table_T>(date);

    const Date date1  = date - timePerCoefficient;
    const Date date2  = date + timePerCoefficient;
    const double mjd1 = (date1.mjd() - Date(J2000).mjd()).count();
    const double mjd  = (date.mjd() - Date(J2000).mjd()).count();
    const double mjd2 = (date2.mjd() - Date(J2000).mjd()).count();

    // TODO: Just linearize around the velocity until I can figure out the 2nd chebyshev derivative properly.
    const Velocity vx1 = math::evaluate_chebyshev_derivative(mjd1, xInterp, _COEFF_ZERO_FACTOR) * km / day;
    const Velocity vy1 = math::evaluate_chebyshev_derivative(mjd1, yInterp, _COEFF_ZERO_FACTOR) * km / day;
    const Velocity vz1 = math::evaluate_chebyshev_derivative(mjd1, zInterp, _COEFF_ZERO_FACTOR) * km / day;

    const Velocity vx = math::evaluate_chebyshev_derivative(mjd, xInterp, _COEFF_ZERO_FACTOR) * km / day;
    const Velocity vy = math::evaluate_chebyshev_derivative(mjd, yInterp, _COEFF_ZERO_FACTOR) * km / day;
    const Velocity vz = math::evaluate_chebyshev_derivative(mjd, zInterp, _COEFF_ZERO_FACTOR) * km / day;

    const Velocity vx2 = math::evaluate_chebyshev_derivative(mjd2, xInterp, _COEFF_ZERO_FACTOR) * km / day;
    const Velocity vy2 = math::evaluate_chebyshev_derivative(mjd2, yInterp, _COEFF_ZERO_FACTOR) * km / day;
    const Velocity vz2 = math::evaluate_chebyshev_derivative(mjd2, zInterp, _COEFF_ZERO_FACTOR) * km / day;

    // 2nd order central difference: f''(x) ≈ (f(x+h) - 2f(x) + f(x-h)) / h^2
    // Time unit correction to account for h^2 in denominator
    static constexpr Time stepSquaredFactor =
        (timePerCoefficient * timePerCoefficient.numerical_value_in(timePerCoefficient.unit));
    const Acceleration ax = (vx1 - 2.0 * vx + vx2) / stepSquaredFactor;
    const Acceleration ay = (vy1 - 2.0 * vy + vy2) / stepSquaredFactor;
    const Acceleration az = (vz1 - 2.0 * vz + vz2) / stepSquaredFactor;

    return CartesianVector<Acceleration, frame>(ax, ay, az);
}

template <typename Table_T>
inline constexpr auto get_chebyshev_table_coefficients(Date date)
{
    static constexpr Time timePerCoefficient = Table_T::TIME_PER_COEFFICIENT;

    // Extract components
    const std::size_t ind = Table_T::get_index(date, timePerCoefficient);
    auto xInterp          = Table_T::X_INTERP[ind];
    auto yInterp          = Table_T::Y_INTERP[ind];
    auto zInterp          = Table_T::Z_INTERP[ind];

    return std::make_tuple(xInterp, yInterp, zInterp);
}

template <IsCelestialBody auto body>
inline constexpr Angle julian_date_to_body_sidereal_time(JulianDate date)
{
    using mp_units::non_si::day;

    // Elapsed time since J2000 in seconds
    const Time elapsed = (date.time_since_epoch().count() - J2000.time_since_epoch().count()) * day;

    // Accumulated rotation of the body's prime meridian since J2000
    return wrap_angle(get_rotation_rate<body>() * elapsed);
}

template <IsCelestialBody auto body>
inline consteval auto get_body_fixed_frame()
{
    return BodyFixedFrame<body.name + mp_units::symbol_text{ "_fixed" }, body>{};
}

} // namespace astro
} // namespace astrea
```


