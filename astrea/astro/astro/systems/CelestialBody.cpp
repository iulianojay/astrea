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
using mp_units::si::unit_symbols::kg;
using mp_units::si::unit_symbols::m;

OrbitalElements CelestialBody::get_elements_at(const Date& date) const
{
    // Loop over each day in the epoch range
    const quantity<JulianCentury> timeSinceReferenceEpoch = date.jd() - _referenceDate.jd();

    // KEPLERIANs
    const Distance at   = _semimajorAxis + _semimajorAxisRate * timeSinceReferenceEpoch;
    const Unitless ecct = _eccentricity + _eccentricityRate * timeSinceReferenceEpoch;
    const Angle inct    = _inclination + _inclinationRate * timeSinceReferenceEpoch;
    const Angle raant   = _rightAscension + _rightAscensionRate * timeSinceReferenceEpoch;
    const Angle wt      = _argumentOfPerigee + _argumentOfPerigeeRate * timeSinceReferenceEpoch - raant;
    const Angle Lt      = _trueLatitude + _trueLatitudeRate * timeSinceReferenceEpoch;

    // Calculations
    const Angle Met = (Lt - wt);

    // This approximation has error on the order of ecc^6
    const Angle thetat = convert_mean_anomaly_to_true_anomaly(_meanAnomaly, _eccentricity);

    // Store
    return OrbitalElements(Keplerian(at, ecct, inct, raant, wt, thetat));
}

Density CelestialBody::find_atmospheric_density(const Date& date, const Distance& altitude) const
{
    return 0.0 * kg / (m * m * m);
}

} // namespace astro
} // namespace astrea