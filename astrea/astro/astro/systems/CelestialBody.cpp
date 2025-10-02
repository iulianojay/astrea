#include <astro/systems/CelestialBody.hpp>

#include <cfloat>
#include <cmath>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <string>

#include <mp-units/math.h>
#include <mp-units/systems/angular.h>
#include <mp-units/systems/angular/math.h>
#include <mp-units/systems/iau.h>
#include <mp-units/systems/isq_angle.h>
#include <mp-units/systems/si.h>
#include <mp-units/systems/si/math.h>
#include <nlohmann/json.hpp>

#include <astro/state/State.hpp>
#include <astro/state/StateHistory.hpp>
#include <astro/state/orbital_elements/OrbitalElements.hpp>
#include <astro/state/orbital_elements/instances/Keplerian.hpp>
#include <astro/systems/AstrodynamicsSystem.hpp>

namespace astrea {
namespace astro {

using namespace mp_units;
using namespace mp_units::angular;
using mp_units::angular::unit_symbols::deg;
using mp_units::si::unit_symbols::kg;
using mp_units::si::unit_symbols::m;
using mp_units::si::unit_symbols::s;

Keplerian CelestialBody::get_keplerian_elements_at(const Date& date) const
{
    // Time since reference epoch in Julian centuries
    const quantity<JulianCentury> T = date.jd() - _referenceDate.jd();

    // Keplerian element approximation pulled from here: https://ssd.jpl.nasa.gov/planets/approx_pos.html
    const Distance a   = _semimajorAxis + _semimajorAxisRate * T;
    const Unitless ecc = _eccentricity + _eccentricityRate * T;
    const Angle inc    = _inclination + _inclinationRate * T;
    const Angle raan   = _rightAscension + _rightAscensionRate * T;
    const Angle w      = _longitudeOfPerigee + _longitudeOfPerigeeRate * T;
    const Angle L      = _meanLongitude + _meanLongitudeRate * T;

    const auto [B, C, S, F] = get_linear_expansion_coefficients();
    const Angle Me          = wrap_angle(L - w + B * T * T + C * cos(F * T) + S * sin(F * T));
    const Angle argPer      = wrap_angle(w - raan);

    // This approximation has error on the order of ecc^6
    const Angle thetat = convert_mean_anomaly_to_true_anomaly(Me, ecc);

    return Keplerian(a, ecc, inc, raan, argPer, thetat);
}

RadiusVector<frames::solar_system_barycenter::icrf> CelestialBody::get_position_at(const Date& date) const
{
    // This approximation is in the perifocal frame
    const Keplerian coes         = get_keplerian_elements_at(date);
    const Distance a             = coes.get_semimajor();
    const Unitless ecc           = coes.get_eccentricity();
    const Angle inc              = coes.get_inclination();
    const Angle raan             = coes.get_right_ascension();
    const Angle argPer           = coes.get_argument_of_perigee();
    const Angle theta            = coes.get_true_anomaly();
    const Angle Me               = convert_true_anomaly_to_mean_anomaly(theta, ecc);
    const Angle eccentricAnomaly = convert_mean_anomaly_to_eccentric_anomaly(Me, ecc);

    // Position in perifocal frame
    const RadiusVector<frames::dynamic::perifocal> rPerifocal{ a * (cos(eccentricAnomaly) - ecc),
                                                               a * sqrt(1 - ecc * ecc) * sin(eccentricAnomaly),
                                                               0.0 * m };

    // Rotate to the J2000 frame
    const DCM<frames::dynamic::perifocal, frames::solar_system_barycenter::j2000> dcmPeri2J2000(
        { // TODO: Figure this out
          std::array<Unitless, 3>{ cos(argPer) * cos(raan) - sin(argPer) * sin(raan) * cos(inc),
                                   -sin(argPer) * cos(raan) - cos(argPer) * sin(raan) * cos(inc),
                                   0.0 * one },
          std::array<Unitless, 3>{ cos(argPer) * sin(raan) + sin(argPer) * cos(raan) * cos(inc),
                                   -sin(argPer) * sin(raan) + cos(argPer) * cos(raan) * cos(inc),
                                   0.0 * one },
          std::array<Unitless, 3>{ sin(argPer) * sin(inc), cos(argPer) * sin(inc), 0.0 * one } }
    );
    const RadiusVector<frames::solar_system_barycenter::j2000> rJ2000 = dcmPeri2J2000 * rPerifocal;

    // Rotate to the ICRF frame
    static const Angle obliquity = Angle(23.43928 * deg); // obliquity at J2000
    static const auto dcmJ2000ToICRF =
        DCM<frames::solar_system_barycenter::j2000, frames::solar_system_barycenter::icrf>::X(obliquity);

    const RadiusVector<frames::solar_system_barycenter::icrf> rICRF = dcmJ2000ToICRF * rJ2000;
    return rICRF;
}

Density CelestialBody::find_atmospheric_density(const Date& date, const Distance& altitude) const
{
    return 0.0 * kg / (m * m * m);
}

} // namespace astro
} // namespace astrea