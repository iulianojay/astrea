

# Struct astrea::astro::CelestialBodyParameters



[**ClassList**](annotated.md) **>** [**astrea**](namespaceastrea.md) **>** [**astro**](namespaceastrea_1_1astro.md) **>** [**CelestialBodyParameters**](structastrea_1_1astro_1_1CelestialBodyParameters.md)


























## Public Attributes

| Type | Name |
| ---: | :--- |
|  [**Angle**](classastrea_1_1astro_1_1CartesianVector.md) | [**axialTilt**](#variable-axialtilt)  <br>_Axial tilt of the celestial body._  |
|  [**Distance**](classastrea_1_1astro_1_1CartesianVector.md) | [**crashRadius**](#variable-crashradius)  <br>_Crash radius of the celestial body._  |
|  [**Unitless**](classastrea_1_1astro_1_1CartesianVector.md) | [**eccentricity**](#variable-eccentricity)  <br>_Eccentricity._  |
|  [**BodyUnitlessPerTime**](classastrea_1_1astro_1_1CartesianVector.md) | [**eccentricityRate**](#variable-eccentricityrate)  <br>_Rate of change of the eccentricity._  |
|  [**Distance**](classastrea_1_1astro_1_1CartesianVector.md) | [**equitorialRadius**](#variable-equitorialradius)  <br>_Equatorial radius of the celestial body._  |
|  [**Angle**](classastrea_1_1astro_1_1CartesianVector.md) | [**inclination**](#variable-inclination)  <br>_Inclination._  |
|  [**BodyAngularRate**](classastrea_1_1astro_1_1CartesianVector.md) | [**inclinationRate**](#variable-inclinationrate)  <br>_Rate of change of the inclination._  |
|  [**Unitless**](classastrea_1_1astro_1_1CartesianVector.md) | [**j2**](#variable-j2)  <br>_J2 gravitational coefficient of the celestial body._  |
|  [**Unitless**](classastrea_1_1astro_1_1CartesianVector.md) | [**j3**](#variable-j3)  <br>_J3 gravitational coefficient of the celestial body._  |
|  [**Angle**](classastrea_1_1astro_1_1CartesianVector.md) | [**longitudeOfPerigee**](#variable-longitudeofperigee)  <br>_Longitude of perigee._  |
|  [**BodyAngularRate**](classastrea_1_1astro_1_1CartesianVector.md) | [**longitudeOfPerigeeRate**](#variable-longitudeofperigeerate)  <br>_Rate of change of the longitude of perigee._  |
|  [**Mass**](classastrea_1_1astro_1_1CartesianVector.md) | [**mass**](#variable-mass)  <br>_Mass of the celestial body._  |
|  [**Angle**](classastrea_1_1astro_1_1CartesianVector.md) | [**meanLongitude**](#variable-meanlongitude)  <br>_Mean longitude._  |
|  [**BodyAngularRate**](classastrea_1_1astro_1_1CartesianVector.md) | [**meanLongitudeRate**](#variable-meanlongituderate)  <br>_Rate of change of the mean longitude._  |
|  [**GravParam**](classastrea_1_1astro_1_1CartesianVector.md) | [**mu**](#variable-mu)  <br>_Gravitational parameter (mu) of the celestial body._  |
|  std::string | [**name**](#variable-name)  <br>_Name of the celestial body._  |
|  [**CelestialBodyId**](namespaceastrea_1_1astro.md#enum-celestialbodyid) | [**parent**](#variable-parent)  <br>_Reference to the parent planetary body._  |
|  [**Distance**](classastrea_1_1astro_1_1CartesianVector.md) | [**polarRadius**](#variable-polarradius)  <br>_Polar radius of the celestial body._  |
|  [**Date**](classastrea_1_1astro_1_1Date.md) | [**referenceDate**](#variable-referencedate)  <br>_Reference date for the celestial body data._  |
|  [**Angle**](classastrea_1_1astro_1_1CartesianVector.md) | [**rightAscension**](#variable-rightascension)  <br>_Right ascension._  |
|  [**BodyAngularRate**](classastrea_1_1astro_1_1CartesianVector.md) | [**rightAscensionRate**](#variable-rightascensionrate)  <br>_Rate of change of the right ascension._  |
|  [**AngularRate**](classastrea_1_1astro_1_1CartesianVector.md) | [**rotationRate**](#variable-rotationrate)  <br>_Rotation rate of the celestial body._  |
|  [**Distance**](classastrea_1_1astro_1_1CartesianVector.md) | [**semimajorAxis**](#variable-semimajoraxis)  <br>_Semimajor axis._  |
|  [**InterplanetaryVelocity**](classastrea_1_1astro_1_1CartesianVector.md) | [**semimajorAxisRate**](#variable-semimajoraxisrate)  <br>_Rate of change of the semimajor axis._  |
|  [**Time**](classastrea_1_1astro_1_1CartesianVector.md) | [**siderealPeriod**](#variable-siderealperiod)  <br>_Sidereal period of the celestial body._  |
|  [**Distance**](classastrea_1_1astro_1_1CartesianVector.md) | [**sphereOfInfluence**](#variable-sphereofinfluence)  <br>_Sphere of influence of the celestial body._  |
|  [**CelestialBodyType**](namespaceastrea_1_1astro.md#enum-celestialbodytype) | [**type**](#variable-type)  <br>_Type of the celestial body._  |












































## Public Attributes Documentation




### variable axialTilt 

_Axial tilt of the celestial body._ 
```C++
Angle astrea::astro::CelestialBodyParameters::axialTilt;
```




<hr>



### variable crashRadius 

_Crash radius of the celestial body._ 
```C++
Distance astrea::astro::CelestialBodyParameters::crashRadius;
```




<hr>



### variable eccentricity 

_Eccentricity._ 
```C++
Unitless astrea::astro::CelestialBodyParameters::eccentricity;
```




<hr>



### variable eccentricityRate 

_Rate of change of the eccentricity._ 
```C++
BodyUnitlessPerTime astrea::astro::CelestialBodyParameters::eccentricityRate;
```




<hr>



### variable equitorialRadius 

_Equatorial radius of the celestial body._ 
```C++
Distance astrea::astro::CelestialBodyParameters::equitorialRadius;
```




<hr>



### variable inclination 

_Inclination._ 
```C++
Angle astrea::astro::CelestialBodyParameters::inclination;
```




<hr>



### variable inclinationRate 

_Rate of change of the inclination._ 
```C++
BodyAngularRate astrea::astro::CelestialBodyParameters::inclinationRate;
```




<hr>



### variable j2 

_J2 gravitational coefficient of the celestial body._ 
```C++
Unitless astrea::astro::CelestialBodyParameters::j2;
```




<hr>



### variable j3 

_J3 gravitational coefficient of the celestial body._ 
```C++
Unitless astrea::astro::CelestialBodyParameters::j3;
```




<hr>



### variable longitudeOfPerigee 

_Longitude of perigee._ 
```C++
Angle astrea::astro::CelestialBodyParameters::longitudeOfPerigee;
```




<hr>



### variable longitudeOfPerigeeRate 

_Rate of change of the longitude of perigee._ 
```C++
BodyAngularRate astrea::astro::CelestialBodyParameters::longitudeOfPerigeeRate;
```




<hr>



### variable mass 

_Mass of the celestial body._ 
```C++
Mass astrea::astro::CelestialBodyParameters::mass;
```




<hr>



### variable meanLongitude 

_Mean longitude._ 
```C++
Angle astrea::astro::CelestialBodyParameters::meanLongitude;
```




<hr>



### variable meanLongitudeRate 

_Rate of change of the mean longitude._ 
```C++
BodyAngularRate astrea::astro::CelestialBodyParameters::meanLongitudeRate;
```




<hr>



### variable mu 

_Gravitational parameter (mu) of the celestial body._ 
```C++
GravParam astrea::astro::CelestialBodyParameters::mu;
```




<hr>



### variable name 

_Name of the celestial body._ 
```C++
std::string astrea::astro::CelestialBodyParameters::name;
```




<hr>



### variable parent 

_Reference to the parent planetary body._ 
```C++
CelestialBodyId astrea::astro::CelestialBodyParameters::parent;
```




<hr>



### variable polarRadius 

_Polar radius of the celestial body._ 
```C++
Distance astrea::astro::CelestialBodyParameters::polarRadius;
```




<hr>



### variable referenceDate 

_Reference date for the celestial body data._ 
```C++
Date astrea::astro::CelestialBodyParameters::referenceDate;
```




<hr>



### variable rightAscension 

_Right ascension._ 
```C++
Angle astrea::astro::CelestialBodyParameters::rightAscension;
```




<hr>



### variable rightAscensionRate 

_Rate of change of the right ascension._ 
```C++
BodyAngularRate astrea::astro::CelestialBodyParameters::rightAscensionRate;
```




<hr>



### variable rotationRate 

_Rotation rate of the celestial body._ 
```C++
AngularRate astrea::astro::CelestialBodyParameters::rotationRate;
```




<hr>



### variable semimajorAxis 

_Semimajor axis._ 
```C++
Distance astrea::astro::CelestialBodyParameters::semimajorAxis;
```




<hr>



### variable semimajorAxisRate 

_Rate of change of the semimajor axis._ 
```C++
InterplanetaryVelocity astrea::astro::CelestialBodyParameters::semimajorAxisRate;
```




<hr>



### variable siderealPeriod 

_Sidereal period of the celestial body._ 
```C++
Time astrea::astro::CelestialBodyParameters::siderealPeriod;
```




<hr>



### variable sphereOfInfluence 

_Sphere of influence of the celestial body._ 
```C++
Distance astrea::astro::CelestialBodyParameters::sphereOfInfluence;
```




<hr>



### variable type 

_Type of the celestial body._ 
```C++
CelestialBodyType astrea::astro::CelestialBodyParameters::type;
```




<hr>

------------------------------
The documentation for this class was generated from the following file `astrea/astro/astro/systems/CelestialBodyParameters.hpp`

