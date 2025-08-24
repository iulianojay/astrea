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
#include <astro/state/State.hpp>
#include <astro/state/StateHistory.hpp>
#include <astro/systems/AstrodynamicsSystem.hpp>


using namespace mp_units;
using namespace mp_units::angular;

using mp_units::angular::unit_symbols::deg;
using mp_units::angular::unit_symbols::rad;
using mp_units::iau::unit_symbols::au;
using mp_units::non_si::day;
using mp_units::si::unit_symbols::kg;
using mp_units::si::unit_symbols::km;
using mp_units::si::unit_symbols::s;

namespace astrea {
namespace astro {


CelestialBody::CelestialBody(const std::string& file, const AstrodynamicsSystem& system) :
    _systemPtr(&system)
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

State CelestialBody::get_state_at(const Date& date) const
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
    static const GravParam parentMu = _systemPtr->get(_parent)->get_mu();
    const quantity ht               = sqrt(parentMu * at * (1 - ecct * ecct));
    const Angle Met                 = (Lt - wt);

    // This approximation has error on the order of ecc^6. It is
    // assumed to be good for this calc since all these bodies are
    // nearly circular. Solving Kepler"s equations takes a very long
    // time
    const Unitless ecct_2 = ecct * ecct;
    const Unitless ecct_3 = ecct_2 * ecct;
    const Unitless ecct_4 = ecct_3 * ecct;
    const Unitless ecct_5 = ecct_4 * ecct;

    const Angle thetat = Met + ((2.0 * ecct - 0.25 * ecct_3 + 5.0 / 96.0 * ecct_5) * sin(Met) +
                                (1.25 * ecct_2 - 11.0 / 24.0 * ecct_4) * sin(2.0 * Met) +
                                (13.0 / 12.0 * ecct_3 - 43.0 / 64.0 * ecct_5) * sin(3.0 * Met) +
                                103.0 / 96.0 * ecct_4 * sin(4 * Met) + 1097.0 / 960.0 * ecct_5 * sin(5 * Met)) *
                                   isq_angle::cotes_angle;

    // Store
    return State(OrbitalElements(Keplerian(at, ecct, inct, raant, wt, thetat)), date, *_systemPtr);
}

} // namespace astro
} // namespace astrea