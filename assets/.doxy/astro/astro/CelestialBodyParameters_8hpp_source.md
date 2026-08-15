

# File CelestialBodyParameters.hpp

[**File List**](files.md) **>** [**astrea**](dir_b5324400686b7cece921533bb760c87a.md) **>** [**astro**](dir_1d4dcf10fc541574a93624f5c09a3d6f.md) **>** [**astro**](dir_84db6e3c60e44147f5214c05dc45afc2.md) **>** [**systems**](dir_a5d35e082abd602943cf6d70fa2a6872.md) **>** [**CelestialBodyParameters.hpp**](CelestialBodyParameters_8hpp.md)

[Go to the documentation of this file](CelestialBodyParameters_8hpp.md)


```C++

#pragma once

#include <units/units.hpp>

#include <astro/time/Date.hpp>

namespace astrea {
namespace astro {

struct CelestialBodyParameters {
    CelestialBodyType type;                     
    Date referenceDate;                         
    GravParam mu;                               
    Mass mass;                                  
    Distance equitorialRadius;                  
    Distance polarRadius;                       
    Distance crashRadius;                       
    Distance sphereOfInfluence;                 
    Unitless j2;                                
    Unitless j3;                                
    Angle axialTilt;                            
    AngularVelocity rotationRate;               
    Time siderealPeriod;                        
    Distance semimajorAxis;                     
    Unitless eccentricity;                      
    Angle inclination;                          
    Angle rightAscension;                       
    Angle longitudeOfPerigee;                   
    Angle meanLongitude;                        
    InterplanetaryVelocity semimajorAxisRate;   
    BodyUnitlessPerTime eccentricityRate;       
    BodyAngularVelocity inclinationRate;        
    BodyAngularVelocity rightAscensionRate;     
    BodyAngularVelocity longitudeOfPerigeeRate; 
    BodyAngularVelocity meanLongitudeRate;      
    const char* gravityCoefficientFile = "";    
};

} // namespace astro
} // namespace astrea
```


