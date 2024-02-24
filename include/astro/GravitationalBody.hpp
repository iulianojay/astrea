#pragma once

#include <iostream>
#include <cmath>
#include <cfloat>
#include <string>
#include <vector>
#include <unordered_map>

#include "astronomical_constants.h"
#include "gravitational_bodies.hpp"

class GravitationalBody
{
private:
    //----------------------------------------------- Variables -----------------------------------------------//

    // Properties
    bodyName _name, _parent;
    bodyType _type;

    int _planetId, _moonId, _lengthJulianDate;

    double _gravitationalParameter, _mass, _equitorialRadius, _polarRadius, _crashRadius, _sphereOfInfluence,
        _j2, _j3, _axialTilt, _rotationRate, _siderealPeroid , _semimajorAxis, _eccentricity, _inclination, 
        _rightAscension, _argumentOfPerigee, _trueLatitude, _trueAnomaly, _meanAnomaly , _semimajorAxisRate, 
        _eccentricityRate, _inclinationRate, _rightAscensionRate, _argumentOfPerigeeRate, _trueLatitudeRate;

    double *_julianDate, **_radiusParentToBody, **_velocityParentToBody, **_radiusSunToBody, **_velocitySunToBody;

    //------------------------------------------------ Methods ------------------------------------------------//
    void find_radius_to_parent();
    void find_radius_to_sun();
public:
    //----------------------------------------------- Variables -----------------------------------------------//
    int numberOfNBodies = 0;
    std::string nBodyNames[30] = {};

    //------------------------------------------------ Methods ------------------------------------------------//
    // Constructor/destructor
    GravitationalBody();
    GravitationalBody(std::string nameString);
    ~GravitationalBody();

    // Property assignment
    void assign_properties(std::string nameString);
    void set_dates(double* inputJulianDate, int inputLengthJulianDate);

	// Property getters
    std::string name()   { return _mapName.at(_name); };
    std::string type()   { return _mapType.at(_type); };
    std::string parent() { return _mapName.at(_parent); };

    int planetId() { return _planetId; };
    int moonId()   { return _moonId; };

    double mu()     { return _gravitationalParameter; };
    double m()      { return _mass; };
    double eqR()    { return _equitorialRadius; };
    double polR()   { return _polarRadius; };
    double crashR() { return _crashRadius; };
    double SOI()    { return _sphereOfInfluence; };

    double j2() { return _j2; };
    double j3() { return _j3; };

    double tilt()    { return _axialTilt; };
    double rotRate() { return _rotationRate; };
    double sidP()    { return _siderealPeroid; };

    double a()     { return _semimajorAxis; };
    double ecc()   { return _eccentricity; };
    double inc()   { return _inclination; };
    double raan()  { return _rightAscension; };
    double w()     { return _argumentOfPerigee; };
    double L()     { return _trueLatitude; };
    double theta() { return _trueAnomaly; };
    double Me()    { return _meanAnomaly; };

    double adot()    { return _semimajorAxisRate; };
    double eccdot()  { return _eccentricityRate; };
    double incdot()  { return _inclinationRate; };
    double raandot() { return _rightAscensionRate; };
    double wdot()    { return _argumentOfPerigeeRate; };
    double Ldot()    { return _trueLatitudeRate; };

    int lengthOfJulianDate() { return _lengthJulianDate; };

    double*  getJulianDate()        { return _julianDate; };
    double** radiusParentToBody()   { return _radiusParentToBody; };
    double** velocityParentToBody() { return _velocityParentToBody; };
    double** radiusSunToBody()      { return _radiusSunToBody; };
    double** velocitySunToBody()    { return _velocitySunToBody; };
};


