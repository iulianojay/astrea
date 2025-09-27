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
#include <astro/systems/AstrodynamicsSystem.hpp>

namespace astrea {
namespace astro {

using namespace mp_units;
using namespace mp_units::angular;
using mp_units::angular::unit_symbols::deg;
using mp_units::si::unit_symbols::kg;
using mp_units::si::unit_symbols::m;
using mp_units::si::unit_symbols::s;

OrbitalElements CelestialBody::get_elements_at(const Date& date) const
{
    // Time since reference epoch in Julian centuries
    const quantity<JulianCentury> T = date.jd() - _referenceDate.jd();

    // Keplerian element approximation pulled from here: https://ssd.jpl.nasa.gov/planets/approx_pos.html
    const Distance at   = _semimajorAxis + _semimajorAxisRate * T;
    const Unitless ecct = _eccentricity + _eccentricityRate * T;
    const Angle inct    = _inclination + _inclinationRate * T;
    const Angle raant   = _rightAscension + _rightAscensionRate * T;
    const Angle wt      = _longitudeOfPerigee + _longitudeOfPerigeeRate * T;
    const Angle Lt      = _meanLongitude + _meanLongitudeRate * T;

    const auto [B, C, S, F] = get_linear_expansion_coefficients();
    const Angle Met         = wrap_angle(Lt - wt + B * T * T + C * cos(F * T) + S * sin(F * T));
    const Angle argPert     = wrap_angle(wt - raant);

    // This approximation has error on the order of ecc^6
    const Angle thetat           = convert_mean_anomaly_to_true_anomaly(_meanAnomaly, _eccentricity);
    const Angle eccentricAnomaly = convert_mean_anomaly_to_eccentric_anomaly(Met, ecct);


    // This approximation is in the perifocal frame
    const RadiusVector<frames::dynamic::perifocal> rPerifocal{ at * (cos(eccentricAnomaly) - ecct),
                                                               at * sqrt(1 - ecct * ecct) * sin(eccentricAnomaly),
                                                               0.0 * m };

    // Rotate to the J2000 frame
    const DCM<frames::dynamic::perifocal, frames::solar_system_barycenter::j2000> dcmPeri2J2000{
        // TODO: Figure this out
        { CartesianVector<Unitless, frames::dynamic::perifocal>(
              cos(argPert) * cos(raant) - sin(argPert) * sin(raant) * cos(inct),
              -sin(argPert) * cos(raant) - cos(argPert) * sin(raant) * cos(inct),
              0.0 * one
          ),
          CartesianVector<Unitless, frames::dynamic::perifocal>(
              cos(argPert) * sin(raant) + sin(argPert) * cos(raant) * cos(inct),
              -sin(argPert) * sin(raant) + cos(argPert) * cos(raant) * cos(inct),
              0.0 * one
          ),
          CartesianVector<Unitless, frames::dynamic::perifocal>(sin(argPert) * sin(inct), cos(argPert) * sin(inct), 0.0 * one) }
    };

    const RadiusVector<frames::solar_system_barycenter::j2000> rJ2000 = dcmPeri2J2000 * rPerifocal;

    // Rotate to the ICRF frame
    static const Angle obliquity     = Angle(23.43928 * deg); // obliquity at J2000
    static const auto dcmJ2000ToICRF = DCM<frames::solar_system_barycenter::j2000, frames::earth::icrf>::X(obliquity);

    const RadiusVector<frames::solar_system_barycenter::icrf> rICRF = dcmJ2000ToICRF * rJ2000;
    const VelocityVector<frames::solar_system_barycenter::icrf> vICRF(0.0 * m / s, 0.0 * m / s, 0.0 * m / s); // TODO: Fix this

    return OrbitalElements(Cartesian(rICRF, vICRF));
}

Density CelestialBody::find_atmospheric_density(const Date& date, const Distance& altitude) const
{
    return 0.0 * kg / (m * m * m);
}

} // namespace astro
} // namespace astrea