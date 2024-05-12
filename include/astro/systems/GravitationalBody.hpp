#pragma once

#include <iostream>
#include <cmath>
#include <cfloat>
#include <string>
#include <vector>
#include <unordered_map>

#include "astronomical_constants.h"
#include "solar_system.hpp"
#include "Time.hpp"
#include "Date.hpp"
#include "State.hpp"

// Forward declaration
namespace solar_system {
    class SolarObjectBuilder;
}

class GravitationalBody {

    friend class solar_system::SolarObjectBuilder;

public:

    //----------------------------------------------- Variables -----------------------------------------------//
    int numberOfNBodies = 0;
    std::string nBodyNames[30] = {};

    //------------------------------------------------ Methods ------------------------------------------------//
    // Constructor/destructor
    GravitationalBody() {}
    ~GravitationalBody() {}

    // Property assignment
    void propagate(Date epoch, double propTime);
    void propagate(Date epoch, Time propTime);
    void propagate(Date epoch, Date endEpoch);

	// Property getters
    const std::string name()     const { return _nameString; };
    const solar_system::SolarObjectType type() const { return _type; };
    const solar_system::SolarObject parent()   const { return _parent; };

    const int planetId() const { return _planetId; };
    const int moonId()   const { return _moonId; };

    const double mu()     const { return _gravitationalParameter; };
    const double m()      const { return _mass; };
    const double eqR()    const { return _equitorialRadius; };
    const double polR()   const { return _polarRadius; };
    const double crashR() const { return _crashRadius; };
    const double SOI()    const { return _sphereOfInfluence; };

    const double j2() const { return _j2; };
    const double j3() const { return _j3; };

    const double tilt()    const { return _axialTilt; };
    const double rotRate() const { return _rotationRate; };
    const double sidP()    const { return _siderealPeroid; };

    const double a()     const { return _semimajorAxis; };
    const double ecc()   const { return _eccentricity; };
    const double inc()   const { return _inclination; };
    const double raan()  const { return _rightAscension; };
    const double w()     const { return _argumentOfPerigee; };
    const double L()     const { return _trueLatitude; };
    const double theta() const { return _trueAnomaly; };
    const double Me()    const { return _meanAnomaly; };

    const double adot()    const { return _semimajorAxisRate; };
    const double eccdot()  const { return _eccentricityRate; };
    const double incdot()  const { return _inclinationRate; };
    const double raandot() const { return _rightAscensionRate; };
    const double wdot()    const { return _argumentOfPerigeeRate; };
    const double Ldot()    const { return _trueLatitudeRate; };

    int nDays() { return _nDays; };
    std::vector<State> get_states()   { return _states; };

private:
    //----------------------------------------------- Variables -----------------------------------------------//

    // Properties
    solar_system::SolarObject _name, _parent;
    solar_system::SolarObjectType _type;

    std::string _nameString;

    int _planetId = -1, _moonId = -1, _nDays = 0;

    double _gravitationalParameter, _mass, _equitorialRadius, _polarRadius, _crashRadius, _sphereOfInfluence,
        _j2, _j3, _axialTilt, _rotationRate, _siderealPeroid , _semimajorAxis, _eccentricity, _inclination, 
        _rightAscension, _argumentOfPerigee, _trueLatitude, _trueAnomaly, _meanAnomaly , _semimajorAxisRate, 
        _eccentricityRate, _inclinationRate, _rightAscensionRate, _argumentOfPerigeeRate, _trueLatitudeRate;

    std::vector<State> _states;

    //------------------------------------------------ Methods ------------------------------------------------//
    void find_state_relative_to_parent(Date epoch, Date endEpoch);
    void _propagate(Date epoch, Date endEpoch);
};
