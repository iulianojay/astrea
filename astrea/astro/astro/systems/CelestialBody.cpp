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
    const Distance xPerifocal = at * (cos(eccentricAnomaly) - ecct); // TODO: Make a perifocal frame
    const Distance yPerifocal = at * sqrt(1 - ecct * ecct) * sin(eccentricAnomaly);

    // Rotate to the J2000 frame
    const Distance xJ2000 = (cos(argPert) * cos(raant) - sin(argPert) * sin(raant) * cos(inct)) * xPerifocal -
                            (sin(argPert) * cos(raant) + cos(argPert) * sin(raant) * cos(inct)) * yPerifocal;
    const Distance yJ2000 = (cos(argPert) * sin(raant) + sin(argPert) * cos(raant) * cos(inct)) * xPerifocal -
                            (sin(argPert) * sin(raant) - cos(argPert) * cos(raant) * cos(inct)) * yPerifocal;
    const Distance zJ2000 = (sin(argPert) * sin(inct)) * xPerifocal + (cos(argPert) * sin(inct)) * yPerifocal;
    const RadiusVector<frames::solar_system_barycenter::j2000> rJ2000(xJ2000, yJ2000, zJ2000);

    // Rotate to the ICRF frame
    const Angle obliquity = Angle(23.43928 * deg); // obliquity at J2000
    const RadiusVector<frames::earth::icrf> rICRF = DCM<frames::solar_system_barycenter::j2000, frames::earth::icrf>::X(obliquity) *
                                                    rJ2000; // TODO: solve this earth centered everything problem

    const VelocityVector<frames::earth::icrf> vICRF(0.0 * m / s, 0.0 * m / s, 0.0 * m / s);

    return OrbitalElements(Cartesian(rICRF, vICRF));
}

Density CelestialBody::find_atmospheric_density(const Date& date, const Distance& altitude) const
{
    return 0.0 * kg / (m * m * m);
}

} // namespace astro
} // namespace astrea