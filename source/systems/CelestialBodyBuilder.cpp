#include "CelestialBodyBuilder.hpp"

#include "State.hpp"


CelestialBody CelestialBodyBuilder::build(SolarBody name) {
    // Build object
    CelestialBody body;

    // Assign properties
    assign_properties(body, name);

    return body;
}


// Barycenter build(std::vector<CelestialBody> names) {

// }


// Separate function to assign values so the class isn"t created twice
void CelestialBodyBuilder::assign_properties(CelestialBody& body, SolarBody name) {

    body._name = name;
    body._nameString = _mapName.at(name);

    // Identify object
    body._planetId = _idMap.at(name).first;
    body._moonId = _idMap.at(name).second;

    // Assign body class and parent
    body._type = _typeMap.at(name);
    body._parent = _parentMap.at(name);

    // Assign physical properties
    // Assign all properties from the astronomical_constants header
    int moonId = body.moonId();
    int planetId = body.planetId();
    body._gravitationalParameter = gravitataionalParameter [moonId][planetId];
    body._mass                   = mass [moonId][planetId];
    body._equitorialRadius       = equatorialRadius [moonId][planetId];
    body._polarRadius            = polarRadius [moonId][planetId];
    body._crashRadius            = crashRadius [moonId][planetId];
    body._sphereOfInfluence      = sphereOfInfluence [moonId][planetId];

    body._j2 = j2Oblateness[moonId][planetId];
    body._j3 = j3Oblateness[moonId][planetId];

    body._axialTilt      = axisTilt[moonId][planetId];
    body._rotationRate   = rotationalRate[moonId][planetId];
    body._siderealPeroid = siderealPeriod[moonId][planetId];

    // Assign orbital properties
    body._semimajorAxis      = semimajorAxis[moonId][planetId];
    body._eccentricity       = eccentricity[moonId][planetId];
    body._inclination        = inclination[moonId][planetId];
    body._rightAscension     = rightAscension[moonId][planetId];
    body._argumentOfPerigee  = argumentOfPerigee[moonId][planetId];
    body._trueLatitude       = trueLatitude[moonId][planetId];

    if (moonId == 0) {
        body._semimajorAxisRate      = semimajorAxisRate[moonId][planetId];
        body._eccentricityRate       = eccentricityRate[moonId][planetId];
        body._inclinationRate        = inclinationRate[moonId][planetId];
        body._rightAscensionRate     = rightAscensionRate[moonId][planetId];
        body._argumentOfPerigeeRate  = argumentOfPerigeeRate[moonId][planetId];
        body._trueLatitudeRate       = trueLatitudeRate[moonId][planetId];
    }
    else {
        body._semimajorAxisRate = 0.0;
        body._eccentricityRate = 0.0;
        body._inclinationRate = 0.0;
        body._rightAscensionRate = 0.0;
        body._argumentOfPerigeeRate = 0.0;
        body._trueLatitudeRate = 0.0;
    }
}
