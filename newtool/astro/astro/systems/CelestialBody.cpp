#include <astro/systems/CelestialBody.hpp>

#include <filesystem>
#include <fstream>

#include <mp-units/math.h>
#include <mp-units/systems/angular/math.h>
#include <mp-units/systems/iau.h>
#include <mp-units/systems/si/math.h>

#include <nlohmann/json.hpp>

#include <astro/element_sets/OrbitalElements.hpp>
#include <math/utils.hpp>


using namespace mp_units;
using namespace mp_units::si;
using namespace mp_units::si::unit_symbols;
using namespace mp_units::iau::unit_symbols;


CelestialBody::CelestialBody(const std::string& file)
{

    using json = nlohmann::json;
    using jc   = 36525 * day;

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

    _mu                = planetaryData["Gravitational Parameter"]["magnitude"] * (km * pow<3>) / (s * pow<2>);
    _mass              = planetaryData["Mass"]["magnitude"] * kg * mag_power<10, 24>;
    _equitorialRadius  = planetaryData["Equitorial Radius"]["magnitude"] * km;
    _polarRadius       = planetaryData["Polar Radius"]["magnitude"] * km;
    _crashRadius       = planetaryData["Crash Radius"]["magnitude"] * km;
    _sphereOfInfluence = planetaryData["Sphere Of Influence"]["magnitude"] * au;
    _j2                = planetaryData["J2"]["magnitude"] * one;
    _j3                = planetaryData["J3"]["magnitude"] * one;
    _axialTilt         = planetaryData["Axial Tilt"]["magnitude"] * deg;
    _rotationRate      = planetaryData["Rotation Rate"]["magnitude"] * deg / day;
    _siderialPeroid    = planetaryData["Sidereal Peroid"]["magnitude"] * day;

    _referenceDate = Date(state["Epoch"].template get<std::string>());

    _semimajorAxis     = state["Semimajor Axis"]["value"]["magnitude"] * km;
    _eccentricity      = state["Eccentricity"]["value"]["magnitude"] * one;
    _inclination       = state["Inclination"]["value"]["magnitude"] * deg;
    _rightAscension    = state["Right Ascension"]["value"]["magnitude"] * deg;
    _argumentOfPerigee = state["Argument Of Perigee"]["value"]["magnitude"] * deg;
    _trueLatitude      = state["True Latitude"]["value"]["magnitude"] * deg;

    _semimajorAxisRate     = state["Semimajor Axis"]["rate"]["magnitude"] * km / jc;
    _eccentricityRate      = state["Eccentricity"]["rate"]["magnitude"] * one / jc;
    _inclinationRate       = state["Inclination"]["rate"]["magnitude"] * deg / jc;
    _rightAscensionRate    = state["Right Ascension"]["rate"]["magnitude"] * deg / jc;
    _argumentOfPerigeeRate = state["Argument Of Perigee"]["rate"]["magnitude"] * deg / jc;
    _trueLatitudeRate      = state["True Latitude"]["rate"]["magnitude"] * deg / jc;

    // TODO: Add checks to validate this object
}


void CelestialBody::propagate(const Date& epoch, const Time& propTime, const double parentMu)
{
    Date endEpoch = epoch + propTime;
    _propagate(epoch, endEpoch, parentMu);
}
void CelestialBody::propagate(const Date& epoch, const Date& endEpoch, const double parentMu)
{
    _propagate(epoch, endEpoch, parentMu);
}

// Find position of body relative to parent and relative to the sun
void CelestialBody::_propagate(const Date& epoch, const Date& endEpoch, const double parentMu)
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
    const int nDays                      = (endEpoch - epoch).count<days>();
    const double daysSinceReferenceEpoch = epoch.julian_day() - _referenceDate.julian_day();
    for (int iDay = 0; iDay < nDays; ++iDay) {
        // Time since reference date
        const double julianCenturies = (static_cast<double>(iDay) + daysSinceReferenceEpoch) / 36525.0; // time in Julian Centuries

        // KEPLERIANs
        const quantity at    = _semimajorAxis + _semimajorAxisRate * julianCenturies;
        const quantity ecct  = _eccentricity + _eccentricityRate * julianCenturies;
        const quantity inct  = _inclination + _inclinationRate * julianCenturies;
        const quantity raant = _rightAscension + _rightAscensionRate * julianCenturies;
        const quantity wt    = _argumentOfPerigee + _argumentOfPerigeeRate * julianCenturies - raant;
        const quantity Lt    = _trueLatitude + _trueLatitudeRate * julianCenturies;

        // Calculations
        const quantity ht  = pow(parentMu * at * (1 - ecct * ecct), 0.5);
        const quantity Met = (Lt - wt);

        // This approximation has error on the order of ecc^6. It is
        // assumed to be good for this calc since all these bodies are
        // nearly circular. Solving Kepler"s equations takes a very long
        // time
        const quantity ecct_2 = ecct * ecct;
        const quantity ecct_3 = ecct_2 * ecct;
        const quantity ecct_4 = ecct_3 * ecct;
        const quantity ecct_5 = ecct_4 * ecct;

        const quantity thetat =
            (Met + (2.0 * ecct - 0.25 * ecct_3 + 5.0 / 96.0 * ecct_5) * math_c::sin(Met) +
             (1.25 * ecct_2 - 11.0 / 24.0 * ecct_4) * math_c::sin(2.0 * Met) +
             (13.0 / 12.0 * ecct_3 - 43.0 / 64.0 * ecct_5) * math_c::sin(3.0 * Met) +
             103.0 / 96.0 * ecct_4 * math_c::sin(4 * Met) + 1097.0 / 960.0 * ecct_5 * math_c::sin(5 * Met));

        // Store mean and true anomaly
        _meanAnomaly = Met;
        _trueAnomaly = thetat;

        // Calculate once for speed
        const quantity ct = cos(thetat);
        const quantity st = sin(thetat);
        const quantity cw = cos(wt);
        const quantity sw = sin(wt);
        const quantity cr = cos(raant);
        const quantity sr = sin(raant);
        const quantity ci = cos(inct);
        const quantity si = sin(inct);

        const quantity coes2perir = ht * ht / parentMu / (1 + ecct * ct);
        const quantity coes2periv = parentMu / ht;

        // Perifocal frame
        // z_peri is 0 by definition
        const quantity xPerifocal = coes2perir * ct;
        const quantity yPerifocal = coes2perir * st;

        const quantity vxPerifocal = -coes2periv * st;
        const quantity vyPerifocal = coes2periv * (ecct + ct);

        // Translate to inertial frame
        /*
                     | cw sw 0| |1   0  0| | cr sr 0|
          peri2ECI = |-sw cw 0|*|0  ci si|*|-sr cr 0|
                     |  0  0 1| |0 -si ci| |  0  0 1|
        */
        const quantity DCM_xx = cw * cr - ci * sw * sr;
        const quantity DCM_xy = -sw * cr - ci * cw * sr;
        const quantity DCM_yx = cw * sr + ci * sw * cr;
        const quantity DCM_yy = -sw * sr + ci * cw * cr;
        const quantity DCM_zx = si * sw;
        const quantity DCM_zy = si * cw;

        // Find radius and velocity vector
        const Cartesian bciState{ { DCM_xx * xPerifocal + DCM_xy * yPerifocal,
                                    DCM_yx * xPerifocal + DCM_yy * yPerifocal,
                                    DCM_zx * xPerifocal + DCM_zy * yPerifocal },
                                  { DCM_xx * vxPerifocal + DCM_xy * vyPerifocal,
                                    DCM_yx * vxPerifocal + DCM_yy * vyPerifocal,
                                    DCM_zx * vxPerifocal + DCM_zy * vyPerifocal } };

        // Store
        State state(days(iDay), bciState, ElementSet::CARTESIAN);
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