#include <astro/systems/CelestialBody.hpp>

#include <filesystem>
#include <fstream>

#include <nlohmann/json.hpp>

#include <astro/element_sets/OrbitalElements.hpp>
#include <math/utils.hpp>


CelestialBody::CelestialBody(const std::string& file)
{

    using nlohmann::json;

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

    _mu                = planetaryData["Gravitational Parameter"]["magnitude"];
    _mass              = planetaryData["Mass"]["magnitude"];
    _equitorialRadius  = planetaryData["Equitorial Radius"]["magnitude"];
    _polarRadius       = planetaryData["Polar Radius"]["magnitude"];
    _crashRadius       = planetaryData["Crash Radius"]["magnitude"];
    _sphereOfInfluence = planetaryData["Sphere Of Influence"]["magnitude"];
    _j2                = planetaryData["J2"]["magnitude"];
    _j3                = planetaryData["J3"]["magnitude"];
    _axialTilt         = planetaryData["Axial Tilt"]["magnitude"];
    _rotationRate      = planetaryData["Rotation Rate"]["magnitude"];
    _siderialPeroid    = planetaryData["Sidereal Peroid"]["magnitude"];

    _referenceDate = Date(state["Epoch"].template get<std::string>());

    _semimajorAxis     = state["Semimajor Axis"]["value"]["magnitude"];
    _eccentricity      = state["Eccentricity"]["value"]["magnitude"];
    _inclination       = state["Inclination"]["value"]["magnitude"];
    _rightAscension    = state["Right Ascension"]["value"]["magnitude"];
    _argumentOfPerigee = state["Argument Of Perigee"]["value"]["magnitude"];
    _trueLatitude      = state["True Latitude"]["value"]["magnitude"];

    _semimajorAxisRate     = state["Semimajor Axis"]["rate"]["magnitude"];
    _eccentricityRate      = state["Eccentricity"]["rate"]["magnitude"];
    _inclinationRate       = state["Inclination"]["rate"]["magnitude"];
    _rightAscensionRate    = state["Right Ascension"]["rate"]["magnitude"];
    _argumentOfPerigeeRate = state["Argument Of Perigee"]["rate"]["magnitude"];
    _trueLatitudeRate      = state["True Latitude"]["rate"]["magnitude"];

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

    // Variables for loop
    const double rad2deg = 180.0 / M_PI;
    const double deg2rad = M_PI / 180.0;

    // Loop over each day in the epoch range
    const int nDays                      = (endEpoch - epoch).count<days>();
    const double daysSinceReferenceEpoch = epoch.julian_day() - _referenceDate.julian_day();
    for (int iDay = 0; iDay < nDays; ++iDay) {
        // Time since reference date
        const double julianCenturies = (static_cast<double>(iDay) + daysSinceReferenceEpoch) / 36525.0; // time in Julian Centuries

        // KEPLERIANs
        const double at    = _semimajorAxis + _semimajorAxisRate * julianCenturies;
        const double ecct  = _eccentricity + _eccentricityRate * julianCenturies;
        const double inct  = _inclination + _inclinationRate * julianCenturies;
        const double raant = _rightAscension + _rightAscensionRate * julianCenturies;
        const double wt    = _argumentOfPerigee + _argumentOfPerigeeRate * julianCenturies - raant;
        const double Lt    = _trueLatitude + _trueLatitudeRate * julianCenturies;

        // Calculations
        const double ht  = std::pow(parentMu * at * (1 - ecct * ecct), 0.5);
        const double Met = (Lt - wt) * deg2rad;

        // This approximation has error on the order of ecc^6. It is
        // assumed to be good for this calc since all these bodies are
        // nearly circular. Solving Kepler"s equations takes a very long
        // time
        const double ecct_2 = ecct * ecct;
        const double ecct_3 = ecct_2 * ecct;
        const double ecct_4 = ecct_3 * ecct;
        const double ecct_5 = ecct_4 * ecct;

        const double thetat = (Met + (2.0 * ecct - 0.25 * ecct_3 + 5.0 / 96.0 * ecct_5) * std::sin(Met) +
                               (1.25 * ecct_2 - 11.0 / 24.0 * ecct_4) * std::sin(2.0 * Met) +
                               (13.0 / 12.0 * ecct_3 - 43.0 / 64.0 * ecct_5) * std::sin(3.0 * Met) +
                               103.0 / 96.0 * ecct_4 * std::sin(4 * Met) + 1097.0 / 960.0 * ecct_5 * std::sin(5 * Met)) *
                              rad2deg;

        // Store mean and true anomaly
        _meanAnomaly = Met;
        _trueAnomaly = thetat;

        // Calculate once for speed
        const double ct = std::cos(thetat * deg2rad);
        const double st = std::sin(thetat * deg2rad);
        const double cw = std::cos(wt * deg2rad);
        const double sw = std::sin(wt * deg2rad);
        const double cr = std::cos(raant * deg2rad);
        const double sr = std::sin(raant * deg2rad);
        const double ci = std::cos(inct * deg2rad);
        const double si = std::sin(inct * deg2rad);

        const double coes2perir = ht * ht / parentMu / (1 + ecct * ct);
        const double coes2periv = parentMu / ht;

        // Perifocal frame
        // z_peri is 0 by definition
        const double xPerifocal = coes2perir * ct;
        const double yPerifocal = coes2perir * st;

        const double vxPerifocal = -coes2periv * st;
        const double vyPerifocal = coes2periv * (ecct + ct);

        // Translate to inertial frame
        /*
         DCM_peri2ECI = | cw sw 0|*|1   0  0|*| cr sr 0|
                        |-sw cw 0| |0  ci si| |-sr cr 0|
                        |  0  0 1| |0 -si ci| |  0  0 1|
        */
        const double DCM_xx = cw * cr - ci * sw * sr;
        const double DCM_xy = -sw * cr - ci * cw * sr;
        const double DCM_yx = cw * sr + ci * sw * cr;
        const double DCM_yy = -sw * sr + ci * cw * cr;
        const double DCM_zx = si * sw;
        const double DCM_zy = si * cw;

        // Find radius and velocity vector
        ElementArray bciState;
        bciState[0] = DCM_xx * xPerifocal + DCM_xy * yPerifocal;
        bciState[1] = DCM_yx * xPerifocal + DCM_yy * yPerifocal;
        bciState[2] = DCM_zx * xPerifocal + DCM_zy * yPerifocal;

        bciState[3] = DCM_xx * vxPerifocal + DCM_xy * vyPerifocal;
        bciState[4] = DCM_yx * vxPerifocal + DCM_yy * vyPerifocal;
        bciState[5] = DCM_zx * vxPerifocal + DCM_zy * vyPerifocal;

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