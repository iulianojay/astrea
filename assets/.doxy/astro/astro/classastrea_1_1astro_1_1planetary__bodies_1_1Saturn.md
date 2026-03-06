

# Class astrea::astro::planetary\_bodies::Saturn



[**ClassList**](annotated.md) **>** [**astrea**](namespaceastrea.md) **>** [**astro**](namespaceastrea_1_1astro.md) **>** [**planetary\_bodies**](namespaceastrea_1_1astro_1_1planetary__bodies.md) **>** [**Saturn**](classastrea_1_1astro_1_1planetary__bodies_1_1Saturn.md)



_Represents the_ [_**Saturn**_](classastrea_1_1astro_1_1planetary__bodies_1_1Saturn.md) _celestial body._[More...](#detailed-description)

* `#include <Saturn.hpp>`



Inherits the following classes: [astrea::astro::CelestialBody](classastrea_1_1astro_1_1CelestialBody.md)






















































## Public Functions

| Type | Name |
| ---: | :--- |
|  [**constexpr**](classastrea_1_1astro_1_1CartesianVector.md) | [**Saturn**](#function-saturn) () <br>_Default constructor for the_ [_**Saturn**_](classastrea_1_1astro_1_1planetary__bodies_1_1Saturn.md) _class._ |
|   | [**~Saturn**](#function-saturn) () = default<br>_Default destructor for the_ [_**Saturn**_](classastrea_1_1astro_1_1planetary__bodies_1_1Saturn.md) _class._ |


## Public Functions inherited from astrea::astro::CelestialBody

See [astrea::astro::CelestialBody](classastrea_1_1astro_1_1CelestialBody.md)

| Type | Name |
| ---: | :--- |
|   | [**CelestialBody**](classastrea_1_1astro_1_1CelestialBody.md#function-celestialbody-13) () = default<br>_Default constructor for_ [_**CelestialBody**_](classastrea_1_1astro_1_1CelestialBody.md) _._ |
|  [**constexpr**](classastrea_1_1astro_1_1CartesianVector.md) | [**CelestialBody**](classastrea_1_1astro_1_1CelestialBody.md#function-celestialbody-23) ([**const**](classastrea_1_1astro_1_1CartesianVector.md) [**CelestialBodyParameters**](structastrea_1_1astro_1_1CelestialBodyParameters.md) & data) <br>_Constructs a_ [_**CelestialBody**_](classastrea_1_1astro_1_1CelestialBody.md) _from individual parameters._ |
|   | [**CelestialBody**](classastrea_1_1astro_1_1CelestialBody.md#function-celestialbody-33) ([**const**](classastrea_1_1astro_1_1CartesianVector.md) [**CelestialBody**](classastrea_1_1astro_1_1CelestialBody.md) & other) = default<br>_Copy constructor for_ [_**CelestialBody**_](classastrea_1_1astro_1_1CelestialBody.md) _._ |
| virtual [**Density**](classastrea_1_1astro_1_1CartesianVector.md) | [**find\_atmospheric\_density**](classastrea_1_1astro_1_1CelestialBody.md#function-find_atmospheric_density) ([**const**](classastrea_1_1astro_1_1CartesianVector.md) [**Date**](classastrea_1_1astro_1_1Date.md) & date, [**const**](classastrea_1_1astro_1_1CartesianVector.md) [**Distance**](classastrea_1_1astro_1_1CartesianVector.md) & altitude) const<br>_Finds the atmospheric density at a given date and state._  |
|  [**constexpr**](classastrea_1_1astro_1_1CartesianVector.md) [**const**](classastrea_1_1astro_1_1CartesianVector.md) [**Angle**](classastrea_1_1astro_1_1CartesianVector.md) & | [**get\_axial\_tilt**](classastrea_1_1astro_1_1CelestialBody.md#function-get_axial_tilt) () const<br>_Get the axial tilt of the celestial body._  |
|  [**constexpr**](classastrea_1_1astro_1_1CartesianVector.md) [**const**](classastrea_1_1astro_1_1CartesianVector.md) [**Distance**](classastrea_1_1astro_1_1CartesianVector.md) & | [**get\_crash\_radius**](classastrea_1_1astro_1_1CelestialBody.md#function-get_crash_radius) () const<br>_Get the crash radius of the celestial body._  |
|  [**constexpr**](classastrea_1_1astro_1_1CartesianVector.md) [**const**](classastrea_1_1astro_1_1CartesianVector.md) [**Unitless**](classastrea_1_1astro_1_1CartesianVector.md) & | [**get\_eccentricity**](classastrea_1_1astro_1_1CelestialBody.md#function-get_eccentricity) () const<br>_Get the eccentricity of the celestial body._  |
|  [**constexpr**](classastrea_1_1astro_1_1CartesianVector.md) [**const**](classastrea_1_1astro_1_1CartesianVector.md) [**BodyUnitlessPerTime**](classastrea_1_1astro_1_1CartesianVector.md) & | [**get\_eccentricity\_rate**](classastrea_1_1astro_1_1CelestialBody.md#function-get_eccentricity_rate) () const<br>_Get the eccentricity rate of the celestial body._  |
|  [**constexpr**](classastrea_1_1astro_1_1CartesianVector.md) [**const**](classastrea_1_1astro_1_1CartesianVector.md) [**Distance**](classastrea_1_1astro_1_1CartesianVector.md) & | [**get\_equitorial\_radius**](classastrea_1_1astro_1_1CelestialBody.md#function-get_equitorial_radius) () const<br>_Get the equatorial radius of the celestial body._  |
|  [**constexpr**](classastrea_1_1astro_1_1CartesianVector.md) [**const**](classastrea_1_1astro_1_1CartesianVector.md) [**Angle**](classastrea_1_1astro_1_1CartesianVector.md) & | [**get\_inclination**](classastrea_1_1astro_1_1CelestialBody.md#function-get_inclination) () const<br>_Get the inclination of the celestial body._  |
|  [**constexpr**](classastrea_1_1astro_1_1CartesianVector.md) [**const**](classastrea_1_1astro_1_1CartesianVector.md) [**BodyAngularRate**](classastrea_1_1astro_1_1CartesianVector.md) & | [**get\_inclination\_rate**](classastrea_1_1astro_1_1CelestialBody.md#function-get_inclination_rate) () const<br>_Get the inclination rate of the celestial body._  |
|  [**constexpr**](classastrea_1_1astro_1_1CartesianVector.md) [**const**](classastrea_1_1astro_1_1CartesianVector.md) [**Unitless**](classastrea_1_1astro_1_1CartesianVector.md) & | [**get\_j2**](classastrea_1_1astro_1_1CelestialBody.md#function-get_j2) () const<br>_Get the J2 gravitational coefficient of the celestial body._  |
|  [**constexpr**](classastrea_1_1astro_1_1CartesianVector.md) [**const**](classastrea_1_1astro_1_1CartesianVector.md) [**Unitless**](classastrea_1_1astro_1_1CartesianVector.md) & | [**get\_j3**](classastrea_1_1astro_1_1CelestialBody.md#function-get_j3) () const<br>_Get the J3 gravitational coefficient of the celestial body._  |
|  [**Keplerian**](classastrea_1_1astro_1_1Keplerian.md) | [**get\_keplerian\_elements\_at**](classastrea_1_1astro_1_1CelestialBody.md#function-get_keplerian_elements_at) ([**const**](classastrea_1_1astro_1_1CartesianVector.md) [**Date**](classastrea_1_1astro_1_1Date.md) & date) const<br>_Get the keplerian elements of the celestial body at a specific date using a linear approximation._  |
|  [**constexpr**](classastrea_1_1astro_1_1CartesianVector.md) [**const**](classastrea_1_1astro_1_1CartesianVector.md) [**Angle**](classastrea_1_1astro_1_1CartesianVector.md) & | [**get\_longitude\_of\_perigee**](classastrea_1_1astro_1_1CelestialBody.md#function-get_longitude_of_perigee) () const<br>_Get the longitude of perigee of the celestial body._  |
|  [**constexpr**](classastrea_1_1astro_1_1CartesianVector.md) [**const**](classastrea_1_1astro_1_1CartesianVector.md) [**BodyAngularRate**](classastrea_1_1astro_1_1CartesianVector.md) & | [**get\_longitude\_of\_perigee\_rate**](classastrea_1_1astro_1_1CelestialBody.md#function-get_longitude_of_perigee_rate) () const<br>_Get the longitude of perigee rate of the celestial body._  |
|  [**constexpr**](classastrea_1_1astro_1_1CartesianVector.md) [**const**](classastrea_1_1astro_1_1CartesianVector.md) [**Mass**](classastrea_1_1astro_1_1CartesianVector.md) & | [**get\_mass**](classastrea_1_1astro_1_1CelestialBody.md#function-get_mass) () const<br>_Get the mass of the celestial body._  |
|  [**constexpr**](classastrea_1_1astro_1_1CartesianVector.md) [**const**](classastrea_1_1astro_1_1CartesianVector.md) [**Angle**](classastrea_1_1astro_1_1CartesianVector.md) & | [**get\_mean\_anomaly**](classastrea_1_1astro_1_1CelestialBody.md#function-get_mean_anomaly) () const<br>_Get the mean anomaly of the celestial body._  |
|  [**constexpr**](classastrea_1_1astro_1_1CartesianVector.md) [**const**](classastrea_1_1astro_1_1CartesianVector.md) [**Angle**](classastrea_1_1astro_1_1CartesianVector.md) & | [**get\_mean\_longitude**](classastrea_1_1astro_1_1CelestialBody.md#function-get_mean_longitude) () const<br>_Get the mean longitude of the celestial body._  |
|  [**constexpr**](classastrea_1_1astro_1_1CartesianVector.md) [**const**](classastrea_1_1astro_1_1CartesianVector.md) [**BodyAngularRate**](classastrea_1_1astro_1_1CartesianVector.md) & | [**get\_mean\_longitude\_rate**](classastrea_1_1astro_1_1CelestialBody.md#function-get_mean_longitude_rate) () const<br>_Get the mean longitude rate of the celestial body._  |
|  [**constexpr**](classastrea_1_1astro_1_1CartesianVector.md) [**const**](classastrea_1_1astro_1_1CartesianVector.md) [**GravParam**](classastrea_1_1astro_1_1CartesianVector.md) & | [**get\_mu**](classastrea_1_1astro_1_1CelestialBody.md#function-get_mu) () const<br>_Get the gravitational parameter (mu) of the celestial body._  |
|  [**constexpr**](classastrea_1_1astro_1_1CartesianVector.md) [**const**](classastrea_1_1astro_1_1CartesianVector.md) std::string & | [**get\_name**](classastrea_1_1astro_1_1CelestialBody.md#function-get_name) () const<br>_Get the name of the celestial body._  |
|  [**constexpr**](classastrea_1_1astro_1_1CartesianVector.md) [**const**](classastrea_1_1astro_1_1CartesianVector.md) [**CelestialBodyId**](namespaceastrea_1_1astro.md#enum-celestialbodyid) & | [**get\_parent**](classastrea_1_1astro_1_1CelestialBody.md#function-get_parent) () const<br>_Get the parent celestial body._  |
|  [**constexpr**](classastrea_1_1astro_1_1CartesianVector.md) [**const**](classastrea_1_1astro_1_1CartesianVector.md) [**Distance**](classastrea_1_1astro_1_1CartesianVector.md) & | [**get\_polar\_radius**](classastrea_1_1astro_1_1CelestialBody.md#function-get_polar_radius) () const<br>_Get the polar radius of the celestial body._  |
| virtual [**CartesianVector**](classastrea_1_1astro_1_1CartesianVector.md)&lt; [**Distance**](classastrea_1_1astro_1_1CartesianVector.md), [**frames::solar\_system\_barycenter::icrf**](classastrea_1_1astro_1_1CartesianVector.md) &gt; | [**get\_position\_at**](classastrea_1_1astro_1_1CelestialBody.md#function-get_position_at) ([**const**](classastrea_1_1astro_1_1CartesianVector.md) [**Date**](classastrea_1_1astro_1_1Date.md) & date) const<br>_Get the position of the celestial body at a specific date in the ICRF frame._  |
|  [**constexpr**](classastrea_1_1astro_1_1CartesianVector.md) [**const**](classastrea_1_1astro_1_1CartesianVector.md) [**Angle**](classastrea_1_1astro_1_1CartesianVector.md) & | [**get\_right\_ascension**](classastrea_1_1astro_1_1CelestialBody.md#function-get_right_ascension) () const<br>_Get the right ascension of the celestial body._  |
|  [**constexpr**](classastrea_1_1astro_1_1CartesianVector.md) [**const**](classastrea_1_1astro_1_1CartesianVector.md) [**BodyAngularRate**](classastrea_1_1astro_1_1CartesianVector.md) & | [**get\_right\_ascension\_rate**](classastrea_1_1astro_1_1CelestialBody.md#function-get_right_ascension_rate) () const<br>_Get the right ascension rate of the celestial body._  |
|  [**constexpr**](classastrea_1_1astro_1_1CartesianVector.md) [**const**](classastrea_1_1astro_1_1CartesianVector.md) [**AngularRate**](classastrea_1_1astro_1_1CartesianVector.md) & | [**get\_rotation\_rate**](classastrea_1_1astro_1_1CelestialBody.md#function-get_rotation_rate) () const<br>_Get the rotation rate of the celestial body._  |
|  [**constexpr**](classastrea_1_1astro_1_1CartesianVector.md) [**const**](classastrea_1_1astro_1_1CartesianVector.md) [**Distance**](classastrea_1_1astro_1_1CartesianVector.md) & | [**get\_semimajor**](classastrea_1_1astro_1_1CelestialBody.md#function-get_semimajor) () const<br>_Get the semimajor axis of the celestial body._  |
|  [**constexpr**](classastrea_1_1astro_1_1CartesianVector.md) [**const**](classastrea_1_1astro_1_1CartesianVector.md) [**InterplanetaryVelocity**](classastrea_1_1astro_1_1CartesianVector.md) & | [**get\_semimajor\_rate**](classastrea_1_1astro_1_1CelestialBody.md#function-get_semimajor_rate) () const<br>_Get the semimajor axis rate of the celestial body._  |
|  [**constexpr**](classastrea_1_1astro_1_1CartesianVector.md) [**const**](classastrea_1_1astro_1_1CartesianVector.md) [**Time**](classastrea_1_1astro_1_1CartesianVector.md) & | [**get\_sidereal\_period**](classastrea_1_1astro_1_1CelestialBody.md#function-get_sidereal_period) () const<br>_Get the sidereal period of the celestial body._  |
|  [**constexpr**](classastrea_1_1astro_1_1CartesianVector.md) [**const**](classastrea_1_1astro_1_1CartesianVector.md) [**Distance**](classastrea_1_1astro_1_1CartesianVector.md) & | [**get\_sphere\_of\_influence**](classastrea_1_1astro_1_1CelestialBody.md#function-get_sphere_of_influence) () const<br>_Get the sphere of influence of the celestial body._  |
|  [**Angle**](classastrea_1_1astro_1_1CartesianVector.md) | [**get\_true\_anomaly**](classastrea_1_1astro_1_1CelestialBody.md#function-get_true_anomaly) () const<br>_Get the true anomaly of the celestial body._  |
|  [**constexpr**](classastrea_1_1astro_1_1CartesianVector.md) [**const**](classastrea_1_1astro_1_1CartesianVector.md) [**CelestialBodyType**](namespaceastrea_1_1astro.md#enum-celestialbodytype) & | [**get\_type**](classastrea_1_1astro_1_1CelestialBody.md#function-get_type) () const<br>_Get the type of the celestial body._  |
|  [**constexpr**](classastrea_1_1astro_1_1CartesianVector.md) [**bool**](classastrea_1_1astro_1_1CartesianVector.md) | [**operator==**](classastrea_1_1astro_1_1CelestialBody.md#function-operator) ([**const**](classastrea_1_1astro_1_1CartesianVector.md) [**CelestialBody**](classastrea_1_1astro_1_1CelestialBody.md) & other) const<br>_Equality operator for_ [_**CelestialBody**_](classastrea_1_1astro_1_1CelestialBody.md) _._ |
| virtual  | [**~CelestialBody**](classastrea_1_1astro_1_1CelestialBody.md#function-celestialbody) () = default<br>_Default destructor for_ [_**CelestialBody**_](classastrea_1_1astro_1_1CelestialBody.md) _._ |


## Public Static Functions

| Type | Name |
| ---: | :--- |
|  [**constexpr**](classastrea_1_1astro_1_1CartesianVector.md) [**CelestialBodyId**](namespaceastrea_1_1astro.md#enum-celestialbodyid) | [**get\_id**](#function-get_id) () <br>_Get the unique identifier for the_ [_**Saturn**_](classastrea_1_1astro_1_1planetary__bodies_1_1Saturn.md) _celestial body._ |


## Public Static Functions inherited from astrea::astro::CelestialBody

See [astrea::astro::CelestialBody](classastrea_1_1astro_1_1CelestialBody.md)

| Type | Name |
| ---: | :--- |
|  [**constexpr**](classastrea_1_1astro_1_1CartesianVector.md) [**CelestialBodyId**](namespaceastrea_1_1astro.md#enum-celestialbodyid) | [**get\_id**](classastrea_1_1astro_1_1CelestialBody.md#function-get_id) () <br>_Get the parent celestial body._  |




## Protected Types inherited from astrea::astro::CelestialBody

See [astrea::astro::CelestialBody](classastrea_1_1astro_1_1CelestialBody.md)

| Type | Name |
| ---: | :--- |
| typedef std::tuple&lt; mp\_units::quantity&lt; mp\_units::angular::unit\_symbols::rad/([**JulianCentury**](classastrea_1_1astro_1_1CartesianVector.md) \*[**JulianCentury**](classastrea_1_1astro_1_1CartesianVector.md))&gt;, mp\_units::quantity&lt; mp\_units::angular::unit\_symbols::rad &gt;, mp\_units::quantity&lt; mp\_units::angular::unit\_symbols::rad &gt;, mp\_units::quantity&lt; mp\_units::angular::unit\_symbols::rad/[**JulianCentury**](classastrea_1_1astro_1_1CartesianVector.md) &gt; &gt; | [**CoefficientPack**](classastrea_1_1astro_1_1CelestialBody.md#typedef-coefficientpack)  <br>_Type alias for a tuple of linear expansion coefficients._  |








## Protected Attributes inherited from astrea::astro::CelestialBody

See [astrea::astro::CelestialBody](classastrea_1_1astro_1_1CelestialBody.md)

| Type | Name |
| ---: | :--- |
|  [**Angle**](classastrea_1_1astro_1_1CartesianVector.md) | [**\_axialTilt**](classastrea_1_1astro_1_1CelestialBody.md#variable-_axialtilt)  <br>_Axial tilt of the celestial body._  |
|  [**Distance**](classastrea_1_1astro_1_1CartesianVector.md) | [**\_crashRadius**](classastrea_1_1astro_1_1CelestialBody.md#variable-_crashradius)  <br>_Crash radius of the celestial body._  |
|  [**Unitless**](classastrea_1_1astro_1_1CartesianVector.md) | [**\_eccentricity**](classastrea_1_1astro_1_1CelestialBody.md#variable-_eccentricity)  <br>_Eccentricity._  |
|  [**BodyUnitlessPerTime**](classastrea_1_1astro_1_1CartesianVector.md) | [**\_eccentricityRate**](classastrea_1_1astro_1_1CelestialBody.md#variable-_eccentricityrate)  <br>_Rate of change of the eccentricity._  |
|  [**Distance**](classastrea_1_1astro_1_1CartesianVector.md) | [**\_equitorialRadius**](classastrea_1_1astro_1_1CelestialBody.md#variable-_equitorialradius)  <br>_Equatorial radius of the celestial body._  |
|  [**Angle**](classastrea_1_1astro_1_1CartesianVector.md) | [**\_inclination**](classastrea_1_1astro_1_1CelestialBody.md#variable-_inclination)  <br>_Inclination._  |
|  [**BodyAngularRate**](classastrea_1_1astro_1_1CartesianVector.md) | [**\_inclinationRate**](classastrea_1_1astro_1_1CelestialBody.md#variable-_inclinationrate)  <br>_Rate of change of the inclination._  |
|  [**Unitless**](classastrea_1_1astro_1_1CartesianVector.md) | [**\_j2**](classastrea_1_1astro_1_1CelestialBody.md#variable-_j2)  <br>_J2 gravitational coefficient of the celestial body._  |
|  [**Unitless**](classastrea_1_1astro_1_1CartesianVector.md) | [**\_j3**](classastrea_1_1astro_1_1CelestialBody.md#variable-_j3)  <br>_J3 gravitational coefficient of the celestial body._  |
|  [**Angle**](classastrea_1_1astro_1_1CartesianVector.md) | [**\_longitudeOfPerigee**](classastrea_1_1astro_1_1CelestialBody.md#variable-_longitudeofperigee)  <br>_Argument of perigee._  |
|  [**BodyAngularRate**](classastrea_1_1astro_1_1CartesianVector.md) | [**\_longitudeOfPerigeeRate**](classastrea_1_1astro_1_1CelestialBody.md#variable-_longitudeofperigeerate)  <br>_Rate of change of the longitude of perigee._  |
|  [**Mass**](classastrea_1_1astro_1_1CartesianVector.md) | [**\_mass**](classastrea_1_1astro_1_1CelestialBody.md#variable-_mass)  <br>_Mass of the celestial body._  |
|  [**Angle**](classastrea_1_1astro_1_1CartesianVector.md) | [**\_meanAnomaly**](classastrea_1_1astro_1_1CelestialBody.md#variable-_meananomaly)  <br>_Mean anomaly._  |
|  [**Angle**](classastrea_1_1astro_1_1CartesianVector.md) | [**\_meanLongitude**](classastrea_1_1astro_1_1CelestialBody.md#variable-_meanlongitude)  <br>_Mean longitude._  |
|  [**BodyAngularRate**](classastrea_1_1astro_1_1CartesianVector.md) | [**\_meanLongitudeRate**](classastrea_1_1astro_1_1CelestialBody.md#variable-_meanlongituderate)  <br>_Rate of change of the mean longitude._  |
|  [**GravParam**](classastrea_1_1astro_1_1CartesianVector.md) | [**\_mu**](classastrea_1_1astro_1_1CelestialBody.md#variable-_mu)  <br>_Gravitational parameter (mu) of the celestial body._  |
|  std::string | [**\_name**](classastrea_1_1astro_1_1CelestialBody.md#variable-_name)  <br>_Name of the celestial body._  |
|  [**CelestialBodyId**](namespaceastrea_1_1astro.md#enum-celestialbodyid) | [**\_parent**](classastrea_1_1astro_1_1CelestialBody.md#variable-_parent)  <br>_Parent celestial body._  |
|  [**GravParam**](classastrea_1_1astro_1_1CartesianVector.md) | [**\_parentMu**](classastrea_1_1astro_1_1CelestialBody.md#variable-_parentmu)  <br>_Gravitational parameter of the parent celestial body, if any._  |
|  [**Distance**](classastrea_1_1astro_1_1CartesianVector.md) | [**\_polarRadius**](classastrea_1_1astro_1_1CelestialBody.md#variable-_polarradius)  <br>_Polar radius of the celestial body._  |
|  [**Date**](classastrea_1_1astro_1_1Date.md) | [**\_referenceDate**](classastrea_1_1astro_1_1CelestialBody.md#variable-_referencedate)  <br>_Reference date for the celestial body data._  |
|  [**Angle**](classastrea_1_1astro_1_1CartesianVector.md) | [**\_rightAscension**](classastrea_1_1astro_1_1CelestialBody.md#variable-_rightascension)  <br>_Right ascension._  |
|  [**BodyAngularRate**](classastrea_1_1astro_1_1CartesianVector.md) | [**\_rightAscensionRate**](classastrea_1_1astro_1_1CelestialBody.md#variable-_rightascensionrate)  <br>_Rate of change of the right ascension._  |
|  [**AngularRate**](classastrea_1_1astro_1_1CartesianVector.md) | [**\_rotationRate**](classastrea_1_1astro_1_1CelestialBody.md#variable-_rotationrate)  <br>_Rotation rate of the celestial body._  |
|  [**Distance**](classastrea_1_1astro_1_1CartesianVector.md) | [**\_semimajorAxis**](classastrea_1_1astro_1_1CelestialBody.md#variable-_semimajoraxis)  <br>_Semimajor axis._  |
|  [**InterplanetaryVelocity**](classastrea_1_1astro_1_1CartesianVector.md) | [**\_semimajorAxisRate**](classastrea_1_1astro_1_1CelestialBody.md#variable-_semimajoraxisrate)  <br>_Rate of change of the semimajor axis._  |
|  [**Time**](classastrea_1_1astro_1_1CartesianVector.md) | [**\_siderealPeriod**](classastrea_1_1astro_1_1CelestialBody.md#variable-_siderealperiod)  <br>_Sidereal period of the celestial body._  |
|  [**Distance**](classastrea_1_1astro_1_1CartesianVector.md) | [**\_sphereOfInfluence**](classastrea_1_1astro_1_1CelestialBody.md#variable-_sphereofinfluence)  <br>_Crash radius of the celestial body._  |
|  [**Angle**](classastrea_1_1astro_1_1CartesianVector.md) | [**\_trueAnomaly**](classastrea_1_1astro_1_1CelestialBody.md#variable-_trueanomaly)  <br>_True anomaly._  |
|  [**CelestialBodyType**](namespaceastrea_1_1astro.md#enum-celestialbodytype) | [**\_type**](classastrea_1_1astro_1_1CelestialBody.md#variable-_type)  <br>_Type of the celestial body._  |




## Protected Static Attributes inherited from astrea::astro::CelestialBody

See [astrea::astro::CelestialBody](classastrea_1_1astro_1_1CelestialBody.md)

| Type | Name |
| ---: | :--- |
|  [**constexpr**](classastrea_1_1astro_1_1CartesianVector.md) [**double**](classastrea_1_1astro_1_1CartesianVector.md) | [**\_COEFF\_ZERO\_FACTOR**](classastrea_1_1astro_1_1CelestialBody.md#variable-_coeff_zero_factor)   = `1.0`<br> |




























## Protected Functions inherited from astrea::astro::CelestialBody

See [astrea::astro::CelestialBody](classastrea_1_1astro_1_1CelestialBody.md)

| Type | Name |
| ---: | :--- |
|  [**const**](classastrea_1_1astro_1_1CartesianVector.md) [**auto**](classastrea_1_1astro_1_1CartesianVector.md) | [**get\_chebyshev\_table\_coefficients**](classastrea_1_1astro_1_1CelestialBody.md#function-get_chebyshev_table_coefficients) ([**const**](classastrea_1_1astro_1_1CartesianVector.md) [**Date**](classastrea_1_1astro_1_1Date.md) & date) const<br>_Get the Chebyshev polynomial coefficients for the celestial body at a specific date._  |
| virtual [**constexpr**](classastrea_1_1astro_1_1CartesianVector.md) [**CoefficientPack**](classastrea_1_1astro_1_1CelestialBody.md#typedef-coefficientpack) | [**get\_linear\_expansion\_coefficients**](classastrea_1_1astro_1_1CelestialBody.md#function-get_linear_expansion_coefficients) () const<br>_Get the linear expansion coefficients for the celestial body's orbital elements._  |
|  [**CartesianVector**](classastrea_1_1astro_1_1CartesianVector.md)&lt; [**Distance**](classastrea_1_1astro_1_1CartesianVector.md), [**Frame\_T**](classastrea_1_1astro_1_1CartesianVector.md) &gt; | [**get\_position\_at\_impl**](classastrea_1_1astro_1_1CelestialBody.md#function-get_position_at_impl) ([**const**](classastrea_1_1astro_1_1CartesianVector.md) [**Date**](classastrea_1_1astro_1_1Date.md) & date) const<br>_Get the position of the celestial body at a specific date in a specified frame using Chebyshev polynomials._  |
|  [**CartesianVector**](classastrea_1_1astro_1_1CartesianVector.md)&lt; [**Velocity**](classastrea_1_1astro_1_1CartesianVector.md), [**Frame\_T**](classastrea_1_1astro_1_1CartesianVector.md) &gt; | [**get\_velocity\_at\_impl**](classastrea_1_1astro_1_1CelestialBody.md#function-get_velocity_at_impl) ([**const**](classastrea_1_1astro_1_1CartesianVector.md) [**Date**](classastrea_1_1astro_1_1Date.md) & date) const<br>_Get the velocity of the celestial body at a specific date in a specified frame using Chebyshev polynomials._  |






## Detailed Description


This class provides properties and methods specific to [**Saturn**](classastrea_1_1astro_1_1planetary__bodies_1_1Saturn.md), including its physical and orbital parameters. 


    
## Public Functions Documentation




### function Saturn 

_Default constructor for the_ [_**Saturn**_](classastrea_1_1astro_1_1planetary__bodies_1_1Saturn.md) _class._
```C++
inline constexpr astrea::astro::planetary_bodies::Saturn::Saturn () 
```



Initializes the [**Saturn**](classastrea_1_1astro_1_1planetary__bodies_1_1Saturn.md) object with predefined physical and orbital parameters. 


        

<hr>



### function ~Saturn 

_Default destructor for the_ [_**Saturn**_](classastrea_1_1astro_1_1planetary__bodies_1_1Saturn.md) _class._
```C++
astrea::astro::planetary_bodies::Saturn::~Saturn () = default
```




<hr>
## Public Static Functions Documentation




### function get\_id 

_Get the unique identifier for the_ [_**Saturn**_](classastrea_1_1astro_1_1planetary__bodies_1_1Saturn.md) _celestial body._
```C++
static inline constexpr  CelestialBodyId astrea::astro::planetary_bodies::Saturn::get_id () 
```





**Returns:**

CelestialBodyId The unique identifier for [**Saturn**](classastrea_1_1astro_1_1planetary__bodies_1_1Saturn.md). 





        

<hr>

------------------------------
The documentation for this class was generated from the following file `astrea/astro/astro/systems/planetary_bodies/Saturn/Saturn.hpp`

