#include <astro/systems/CelestialBody.hpp>

#include <filesystem>
#include <fstream>

#include <mp-units/math.h>
#include <mp-units/systems/angular/math.h>
#include <mp-units/systems/iau.h>
#include <mp-units/systems/isq_angle.h>
#include <mp-units/systems/si/math.h>

#include <nlohmann/json.hpp>

#include <astro/element_sets/OrbitalElements.hpp>
#include <math/utils.hpp>


using namespace mp_units;
using namespace mp_units::angular;

using mp_units::angular::unit_symbols::deg;
using mp_units::angular::unit_symbols::rad;
using mp_units::iau::unit_symbols::au;
using mp_units::non_si::day;
using mp_units::si::unit_symbols::kg;
using mp_units::si::unit_symbols::km;
using mp_units::si::unit_symbols::s;

namespace astro {


CelestialBody::CelestialBody(const std::string& file)
{

    using json = nlohmann::json;

    // Read file into JSON
    // TODO: Add checks to make sure its a valid JSON
    std::ifstream fileStream(file);

    // Parse
    const json planetaryData = json::parse(fileStream);
    const json state         = planetaryData["State"];

    // Store
    _name   = planetaryData["Name"].template get<std::string>();
    _parent = planetaryData["Parent"].template get<std::string>();
    _type   = planetaryData["Type"].template get<std::string>();

    _mu                = planetaryData["Gravitational Parameter"]["magnitude"].get<double>() * (pow<3>(km) / pow<2>(s));
    _mass              = planetaryData["Mass"]["magnitude"].get<double>() * (mag_power<10, 24> * kg);
    _equitorialRadius  = planetaryData["Equitorial Radius"]["magnitude"].get<double>() * km;
    _polarRadius       = planetaryData["Polar Radius"]["magnitude"].get<double>() * km;
    _crashRadius       = planetaryData["Crash Radius"]["magnitude"].get<double>() * km;
    _sphereOfInfluence = planetaryData["Sphere Of Influence"]["magnitude"].get<double>() * au;
    _j2                = planetaryData["J2"]["magnitude"].get<double>() * one;
    _j3                = planetaryData["J3"]["magnitude"].get<double>() * one;
    _axialTilt         = planetaryData["Axial Tilt"]["magnitude"].get<double>() * deg;
    _rotationRate      = planetaryData["Rotation Rate"]["magnitude"].get<double>() * deg / day;
    _siderialPeroid    = planetaryData["Sidereal Peroid"]["magnitude"].get<double>() * day;

    _referenceDate = Date(state["Epoch"].template get<std::string>());

    _semimajorAxis     = state["Semimajor Axis"]["value"]["magnitude"].get<double>() * km;
    _eccentricity      = state["Eccentricity"]["value"]["magnitude"].get<double>() * one;
    _inclination       = state["Inclination"]["value"]["magnitude"].get<double>() * deg;
    _rightAscension    = state["Right Ascension"]["value"]["magnitude"].get<double>() * deg;
    _argumentOfPerigee = state["Argument Of Perigee"]["value"]["magnitude"].get<double>() * deg;
    _trueLatitude      = state["True Latitude"]["value"]["magnitude"].get<double>() * deg;

    _semimajorAxisRate     = state["Semimajor Axis"]["rate"]["magnitude"].get<double>() * km / JulianCentury;
    _eccentricityRate      = state["Eccentricity"]["rate"]["magnitude"].get<double>() * one / JulianCentury;
    _inclinationRate       = state["Inclination"]["rate"]["magnitude"].get<double>() * deg / JulianCentury;
    _rightAscensionRate    = state["Right Ascension"]["rate"]["magnitude"].get<double>() * deg / JulianCentury;
    _argumentOfPerigeeRate = state["Argument Of Perigee"]["rate"]["magnitude"].get<double>() * deg / JulianCentury;
    _trueLatitudeRate      = state["True Latitude"]["rate"]["magnitude"].get<double>() * deg / JulianCentury;

    // TODO: Add checks to validate this object
}


void CelestialBody::propagate(const Date& epoch, const Time& propTime, const GravParam& parentMu)
{
    Date endEpoch = epoch + propTime;
    _propagate(epoch, endEpoch, parentMu);
}

void CelestialBody::propagate(const Date& epoch, const Date& endEpoch, const GravParam& parentMu)
{
    _propagate(epoch, endEpoch, parentMu);
}

// Find position of body relative to parent and relative to the sun
void CelestialBody::_propagate(const Date& epoch, const Date& endEpoch, const GravParam& parentMu)
{

    // Get reference date
    /*
    phobos/deimos   Epoch: 1950, Jan. 1.00 , TT -> julianDate = 2433282.5
    jupiter         Epoch: 1997, Jan. 16.00, TT -> julianDate = 2450465
    uranus          Epoch: 1980, Jan. 1.0  , TT -> julianDate = 2444240
    moon            Epoch: 2000, Jan. 1.50 , TT -> julianDate = 2451545.5
    saturn          Epoch: 2000, Jan. 1.50 , TT -> julianDate = 2451545.5
    neptune         Epoch: 2000, Jan. 1.50 , TT -> julianDate = 2451545.5

    UTC = TT - 64 seconds
    */

    // Loop over each day in the epoch range
    const quantity<day> nDays                   = endEpoch - epoch;
    const quantity<day> daysSinceReferenceEpoch = epoch.jd() - _referenceDate.jd();
    for (quantity<day> iDay = 0 * day; iDay < nDays; iDay += 1 * day) {
        // Time since reference date
        const quantity<JulianCentury> julianCenturies = (iDay + daysSinceReferenceEpoch); // time in Julian Centuries

        // KEPLERIANs
        const Distance at   = _semimajorAxis + _semimajorAxisRate * julianCenturies;
        const Unitless ecct = _eccentricity + _eccentricityRate * julianCenturies;
        const Angle inct    = _inclination + _inclinationRate * julianCenturies;
        const Angle raant   = _rightAscension + _rightAscensionRate * julianCenturies;
        const Angle wt      = _argumentOfPerigee + _argumentOfPerigeeRate * julianCenturies - raant;
        const Angle Lt      = _trueLatitude + _trueLatitudeRate * julianCenturies;

        // Calculations
        const quantity ht = sqrt(parentMu * at * (1 - ecct * ecct));
        const Angle Met   = (Lt - wt);

        // This approximation has error on the order of ecc^6. It is
        // assumed to be good for this calc since all these bodies are
        // nearly circular. Solving Kepler"s equations takes a very long
        // time
        const Unitless ecct_2 = ecct * ecct;
        const Unitless ecct_3 = ecct_2 * ecct;
        const Unitless ecct_4 = ecct_3 * ecct;
        const Unitless ecct_5 = ecct_4 * ecct;

        const Angle thetat =
            (Met + (2.0 * ecct - 0.25 * ecct_3 + 5.0 / 96.0 * ecct_5) * sin(Met) * isq_angle::cotes_angle +
             (1.25 * ecct_2 - 11.0 / 24.0 * ecct_4) * sin(2.0 * Met) * isq_angle::cotes_angle +
             (13.0 / 12.0 * ecct_3 - 43.0 / 64.0 * ecct_5) * sin(3.0 * Met) * isq_angle::cotes_angle +
             103.0 / 96.0 * ecct_4 * sin(4 * Met) * isq_angle::cotes_angle +
             1097.0 / 960.0 * ecct_5 * sin(5 * Met) * isq_angle::cotes_angle);

        // Store mean and true anomaly
        _meanAnomaly = Met;
        _trueAnomaly = thetat;

        // Store
        State state(iDay, Keplerian(at, ecct, inct, raant, wt, thetat));
        _states.push_back(state);
    }
}

const State& CelestialBody::get_closest_state(const Time& time) const
{

    // Check if input time is out of bounds
    if (time <= _states[0].time) { return _states[0]; }
    else if (time >= _states[_states.size() - 1].time) {
        return _states[_states.size() - 1];
    }

    // Get index of lower bound closest to input time
    const auto id = std::distance(_states.begin(), std::lower_bound(_states.begin(), _states.end(), time, state_time_comparitor));

    // Compare time before and after index
    const Time lowerDiff = (_states[id].time - time);
    const Time upperDiff = (_states[id + 1].time - time);

    // Return closest
    if (lowerDiff < upperDiff) { return _states[id]; }
    else {
        return _states[id + 1];
    }
}

} // namespace astro