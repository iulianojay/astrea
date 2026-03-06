

# Class astrea::astro::CelestialBody



[**ClassList**](annotated.md) **>** [**astrea**](namespaceastrea.md) **>** [**astro**](namespaceastrea_1_1astro.md) **>** [**CelestialBody**](classastrea_1_1astro_1_1CelestialBody.md)



[_**CelestialBody**_](classastrea_1_1astro_1_1CelestialBody.md) _class represents a celestial body in an astrodynamics system._

* `#include <CelestialBody.hpp>`





Inherited by the following classes: [astrea::astro::planetary\_bodies::Callisto](classastrea_1_1astro_1_1planetary__bodies_1_1Callisto.md),  [astrea::astro::planetary\_bodies::Deimos](classastrea_1_1astro_1_1planetary__bodies_1_1Deimos.md),  [astrea::astro::planetary\_bodies::Earth](classastrea_1_1astro_1_1planetary__bodies_1_1Earth.md),  [astrea::astro::planetary\_bodies::Europa](classastrea_1_1astro_1_1planetary__bodies_1_1Europa.md),  [astrea::astro::planetary\_bodies::Ganymede](classastrea_1_1astro_1_1planetary__bodies_1_1Ganymede.md),  [astrea::astro::planetary\_bodies::Iapetus](classastrea_1_1astro_1_1planetary__bodies_1_1Iapetus.md),  [astrea::astro::planetary\_bodies::Io](classastrea_1_1astro_1_1planetary__bodies_1_1Io.md),  [astrea::astro::planetary\_bodies::Jupiter](classastrea_1_1astro_1_1planetary__bodies_1_1Jupiter.md),  [astrea::astro::planetary\_bodies::Mars](classastrea_1_1astro_1_1planetary__bodies_1_1Mars.md),  [astrea::astro::planetary\_bodies::Mercury](classastrea_1_1astro_1_1planetary__bodies_1_1Mercury.md),  [astrea::astro::planetary\_bodies::Moon](classastrea_1_1astro_1_1planetary__bodies_1_1Moon.md),  [astrea::astro::planetary\_bodies::Neptune](classastrea_1_1astro_1_1planetary__bodies_1_1Neptune.md),  [astrea::astro::planetary\_bodies::Oberon](classastrea_1_1astro_1_1planetary__bodies_1_1Oberon.md),  [astrea::astro::planetary\_bodies::Phobos](classastrea_1_1astro_1_1planetary__bodies_1_1Phobos.md),  [astrea::astro::planetary\_bodies::Rhea](classastrea_1_1astro_1_1planetary__bodies_1_1Rhea.md),  [astrea::astro::planetary\_bodies::Saturn](classastrea_1_1astro_1_1planetary__bodies_1_1Saturn.md),  [astrea::astro::planetary\_bodies::Sun](classastrea_1_1astro_1_1planetary__bodies_1_1Sun.md),  [astrea::astro::planetary\_bodies::Titan](classastrea_1_1astro_1_1planetary__bodies_1_1Titan.md),  [astrea::astro::planetary\_bodies::Titania](classastrea_1_1astro_1_1planetary__bodies_1_1Titania.md),  [astrea::astro::planetary\_bodies::Triton](classastrea_1_1astro_1_1planetary__bodies_1_1Triton.md),  [astrea::astro::planetary\_bodies::Uranus](classastrea_1_1astro_1_1planetary__bodies_1_1Uranus.md),  [astrea::astro::planetary\_bodies::Venus](classastrea_1_1astro_1_1planetary__bodies_1_1Venus.md)
































## Public Functions

| Type | Name |
| ---: | :--- |
|   | [**CelestialBody**](#function-celestialbody-13) () = default<br>_Default constructor for_ [_**CelestialBody**_](classastrea_1_1astro_1_1CelestialBody.md) _._ |
|  [**constexpr**](classastrea_1_1astro_1_1CartesianVector.md) | [**CelestialBody**](#function-celestialbody-23) ([**const**](classastrea_1_1astro_1_1CartesianVector.md) [**CelestialBodyParameters**](structastrea_1_1astro_1_1CelestialBodyParameters.md) & data) <br>_Constructs a_ [_**CelestialBody**_](classastrea_1_1astro_1_1CelestialBody.md) _from individual parameters._ |
|   | [**CelestialBody**](#function-celestialbody-33) ([**const**](classastrea_1_1astro_1_1CartesianVector.md) [**CelestialBody**](classastrea_1_1astro_1_1CelestialBody.md) & other) = default<br>_Copy constructor for_ [_**CelestialBody**_](classastrea_1_1astro_1_1CelestialBody.md) _._ |
| virtual [**Density**](classastrea_1_1astro_1_1CartesianVector.md) | [**find\_atmospheric\_density**](#function-find_atmospheric_density) ([**const**](classastrea_1_1astro_1_1CartesianVector.md) [**Date**](classastrea_1_1astro_1_1Date.md) & date, [**const**](classastrea_1_1astro_1_1CartesianVector.md) [**Distance**](classastrea_1_1astro_1_1CartesianVector.md) & altitude) const<br>_Finds the atmospheric density at a given date and state._  |
|  [**constexpr**](classastrea_1_1astro_1_1CartesianVector.md) [**const**](classastrea_1_1astro_1_1CartesianVector.md) [**Angle**](classastrea_1_1astro_1_1CartesianVector.md) & | [**get\_axial\_tilt**](#function-get_axial_tilt) () const<br>_Get the axial tilt of the celestial body._  |
|  [**constexpr**](classastrea_1_1astro_1_1CartesianVector.md) [**const**](classastrea_1_1astro_1_1CartesianVector.md) [**Distance**](classastrea_1_1astro_1_1CartesianVector.md) & | [**get\_crash\_radius**](#function-get_crash_radius) () const<br>_Get the crash radius of the celestial body._  |
|  [**constexpr**](classastrea_1_1astro_1_1CartesianVector.md) [**const**](classastrea_1_1astro_1_1CartesianVector.md) [**Unitless**](classastrea_1_1astro_1_1CartesianVector.md) & | [**get\_eccentricity**](#function-get_eccentricity) () const<br>_Get the eccentricity of the celestial body._  |
|  [**constexpr**](classastrea_1_1astro_1_1CartesianVector.md) [**const**](classastrea_1_1astro_1_1CartesianVector.md) [**BodyUnitlessPerTime**](classastrea_1_1astro_1_1CartesianVector.md) & | [**get\_eccentricity\_rate**](#function-get_eccentricity_rate) () const<br>_Get the eccentricity rate of the celestial body._  |
|  [**constexpr**](classastrea_1_1astro_1_1CartesianVector.md) [**const**](classastrea_1_1astro_1_1CartesianVector.md) [**Distance**](classastrea_1_1astro_1_1CartesianVector.md) & | [**get\_equitorial\_radius**](#function-get_equitorial_radius) () const<br>_Get the equatorial radius of the celestial body._  |
|  [**constexpr**](classastrea_1_1astro_1_1CartesianVector.md) [**const**](classastrea_1_1astro_1_1CartesianVector.md) [**Angle**](classastrea_1_1astro_1_1CartesianVector.md) & | [**get\_inclination**](#function-get_inclination) () const<br>_Get the inclination of the celestial body._  |
|  [**constexpr**](classastrea_1_1astro_1_1CartesianVector.md) [**const**](classastrea_1_1astro_1_1CartesianVector.md) [**BodyAngularRate**](classastrea_1_1astro_1_1CartesianVector.md) & | [**get\_inclination\_rate**](#function-get_inclination_rate) () const<br>_Get the inclination rate of the celestial body._  |
|  [**constexpr**](classastrea_1_1astro_1_1CartesianVector.md) [**const**](classastrea_1_1astro_1_1CartesianVector.md) [**Unitless**](classastrea_1_1astro_1_1CartesianVector.md) & | [**get\_j2**](#function-get_j2) () const<br>_Get the J2 gravitational coefficient of the celestial body._  |
|  [**constexpr**](classastrea_1_1astro_1_1CartesianVector.md) [**const**](classastrea_1_1astro_1_1CartesianVector.md) [**Unitless**](classastrea_1_1astro_1_1CartesianVector.md) & | [**get\_j3**](#function-get_j3) () const<br>_Get the J3 gravitational coefficient of the celestial body._  |
|  [**Keplerian**](classastrea_1_1astro_1_1Keplerian.md) | [**get\_keplerian\_elements\_at**](#function-get_keplerian_elements_at) ([**const**](classastrea_1_1astro_1_1CartesianVector.md) [**Date**](classastrea_1_1astro_1_1Date.md) & date) const<br>_Get the keplerian elements of the celestial body at a specific date using a linear approximation._  |
|  [**constexpr**](classastrea_1_1astro_1_1CartesianVector.md) [**const**](classastrea_1_1astro_1_1CartesianVector.md) [**Angle**](classastrea_1_1astro_1_1CartesianVector.md) & | [**get\_longitude\_of\_perigee**](#function-get_longitude_of_perigee) () const<br>_Get the longitude of perigee of the celestial body._  |
|  [**constexpr**](classastrea_1_1astro_1_1CartesianVector.md) [**const**](classastrea_1_1astro_1_1CartesianVector.md) [**BodyAngularRate**](classastrea_1_1astro_1_1CartesianVector.md) & | [**get\_longitude\_of\_perigee\_rate**](#function-get_longitude_of_perigee_rate) () const<br>_Get the longitude of perigee rate of the celestial body._  |
|  [**constexpr**](classastrea_1_1astro_1_1CartesianVector.md) [**const**](classastrea_1_1astro_1_1CartesianVector.md) [**Mass**](classastrea_1_1astro_1_1CartesianVector.md) & | [**get\_mass**](#function-get_mass) () const<br>_Get the mass of the celestial body._  |
|  [**constexpr**](classastrea_1_1astro_1_1CartesianVector.md) [**const**](classastrea_1_1astro_1_1CartesianVector.md) [**Angle**](classastrea_1_1astro_1_1CartesianVector.md) & | [**get\_mean\_anomaly**](#function-get_mean_anomaly) () const<br>_Get the mean anomaly of the celestial body._  |
|  [**constexpr**](classastrea_1_1astro_1_1CartesianVector.md) [**const**](classastrea_1_1astro_1_1CartesianVector.md) [**Angle**](classastrea_1_1astro_1_1CartesianVector.md) & | [**get\_mean\_longitude**](#function-get_mean_longitude) () const<br>_Get the mean longitude of the celestial body._  |
|  [**constexpr**](classastrea_1_1astro_1_1CartesianVector.md) [**const**](classastrea_1_1astro_1_1CartesianVector.md) [**BodyAngularRate**](classastrea_1_1astro_1_1CartesianVector.md) & | [**get\_mean\_longitude\_rate**](#function-get_mean_longitude_rate) () const<br>_Get the mean longitude rate of the celestial body._  |
|  [**constexpr**](classastrea_1_1astro_1_1CartesianVector.md) [**const**](classastrea_1_1astro_1_1CartesianVector.md) [**GravParam**](classastrea_1_1astro_1_1CartesianVector.md) & | [**get\_mu**](#function-get_mu) () const<br>_Get the gravitational parameter (mu) of the celestial body._  |
|  [**constexpr**](classastrea_1_1astro_1_1CartesianVector.md) [**const**](classastrea_1_1astro_1_1CartesianVector.md) std::string & | [**get\_name**](#function-get_name) () const<br>_Get the name of the celestial body._  |
|  [**constexpr**](classastrea_1_1astro_1_1CartesianVector.md) [**const**](classastrea_1_1astro_1_1CartesianVector.md) [**CelestialBodyId**](namespaceastrea_1_1astro.md#enum-celestialbodyid) & | [**get\_parent**](#function-get_parent) () const<br>_Get the parent celestial body._  |
|  [**constexpr**](classastrea_1_1astro_1_1CartesianVector.md) [**const**](classastrea_1_1astro_1_1CartesianVector.md) [**Distance**](classastrea_1_1astro_1_1CartesianVector.md) & | [**get\_polar\_radius**](#function-get_polar_radius) () const<br>_Get the polar radius of the celestial body._  |
| virtual [**CartesianVector**](classastrea_1_1astro_1_1CartesianVector.md)&lt; [**Distance**](classastrea_1_1astro_1_1CartesianVector.md), [**frames::solar\_system\_barycenter::icrf**](classastrea_1_1astro_1_1CartesianVector.md) &gt; | [**get\_position\_at**](#function-get_position_at) ([**const**](classastrea_1_1astro_1_1CartesianVector.md) [**Date**](classastrea_1_1astro_1_1Date.md) & date) const<br>_Get the position of the celestial body at a specific date in the ICRF frame._  |
|  [**constexpr**](classastrea_1_1astro_1_1CartesianVector.md) [**const**](classastrea_1_1astro_1_1CartesianVector.md) [**Angle**](classastrea_1_1astro_1_1CartesianVector.md) & | [**get\_right\_ascension**](#function-get_right_ascension) () const<br>_Get the right ascension of the celestial body._  |
|  [**constexpr**](classastrea_1_1astro_1_1CartesianVector.md) [**const**](classastrea_1_1astro_1_1CartesianVector.md) [**BodyAngularRate**](classastrea_1_1astro_1_1CartesianVector.md) & | [**get\_right\_ascension\_rate**](#function-get_right_ascension_rate) () const<br>_Get the right ascension rate of the celestial body._  |
|  [**constexpr**](classastrea_1_1astro_1_1CartesianVector.md) [**const**](classastrea_1_1astro_1_1CartesianVector.md) [**AngularRate**](classastrea_1_1astro_1_1CartesianVector.md) & | [**get\_rotation\_rate**](#function-get_rotation_rate) () const<br>_Get the rotation rate of the celestial body._  |
|  [**constexpr**](classastrea_1_1astro_1_1CartesianVector.md) [**const**](classastrea_1_1astro_1_1CartesianVector.md) [**Distance**](classastrea_1_1astro_1_1CartesianVector.md) & | [**get\_semimajor**](#function-get_semimajor) () const<br>_Get the semimajor axis of the celestial body._  |
|  [**constexpr**](classastrea_1_1astro_1_1CartesianVector.md) [**const**](classastrea_1_1astro_1_1CartesianVector.md) [**InterplanetaryVelocity**](classastrea_1_1astro_1_1CartesianVector.md) & | [**get\_semimajor\_rate**](#function-get_semimajor_rate) () const<br>_Get the semimajor axis rate of the celestial body._  |
|  [**constexpr**](classastrea_1_1astro_1_1CartesianVector.md) [**const**](classastrea_1_1astro_1_1CartesianVector.md) [**Time**](classastrea_1_1astro_1_1CartesianVector.md) & | [**get\_sidereal\_period**](#function-get_sidereal_period) () const<br>_Get the sidereal period of the celestial body._  |
|  [**constexpr**](classastrea_1_1astro_1_1CartesianVector.md) [**const**](classastrea_1_1astro_1_1CartesianVector.md) [**Distance**](classastrea_1_1astro_1_1CartesianVector.md) & | [**get\_sphere\_of\_influence**](#function-get_sphere_of_influence) () const<br>_Get the sphere of influence of the celestial body._  |
|  [**Angle**](classastrea_1_1astro_1_1CartesianVector.md) | [**get\_true\_anomaly**](#function-get_true_anomaly) () const<br>_Get the true anomaly of the celestial body._  |
|  [**constexpr**](classastrea_1_1astro_1_1CartesianVector.md) [**const**](classastrea_1_1astro_1_1CartesianVector.md) [**CelestialBodyType**](namespaceastrea_1_1astro.md#enum-celestialbodytype) & | [**get\_type**](#function-get_type) () const<br>_Get the type of the celestial body._  |
|  [**constexpr**](classastrea_1_1astro_1_1CartesianVector.md) [**bool**](classastrea_1_1astro_1_1CartesianVector.md) | [**operator==**](#function-operator) ([**const**](classastrea_1_1astro_1_1CartesianVector.md) [**CelestialBody**](classastrea_1_1astro_1_1CelestialBody.md) & other) const<br>_Equality operator for_ [_**CelestialBody**_](classastrea_1_1astro_1_1CelestialBody.md) _._ |
| virtual  | [**~CelestialBody**](#function-celestialbody) () = default<br>_Default destructor for_ [_**CelestialBody**_](classastrea_1_1astro_1_1CelestialBody.md) _._ |


## Public Static Functions

| Type | Name |
| ---: | :--- |
|  [**constexpr**](classastrea_1_1astro_1_1CartesianVector.md) [**CelestialBodyId**](namespaceastrea_1_1astro.md#enum-celestialbodyid) | [**get\_id**](#function-get_id) () <br>_Get the parent celestial body._  |


## Protected Types

| Type | Name |
| ---: | :--- |
| typedef std::tuple&lt; mp\_units::quantity&lt; mp\_units::angular::unit\_symbols::rad/([**JulianCentury**](classastrea_1_1astro_1_1CartesianVector.md) \*[**JulianCentury**](classastrea_1_1astro_1_1CartesianVector.md))&gt;, mp\_units::quantity&lt; mp\_units::angular::unit\_symbols::rad &gt;, mp\_units::quantity&lt; mp\_units::angular::unit\_symbols::rad &gt;, mp\_units::quantity&lt; mp\_units::angular::unit\_symbols::rad/[**JulianCentury**](classastrea_1_1astro_1_1CartesianVector.md) &gt; &gt; | [**CoefficientPack**](#typedef-coefficientpack)  <br>_Type alias for a tuple of linear expansion coefficients._  |




## Protected Attributes

| Type | Name |
| ---: | :--- |
|  [**Angle**](classastrea_1_1astro_1_1CartesianVector.md) | [**\_axialTilt**](#variable-_axialtilt)  <br>_Axial tilt of the celestial body._  |
|  [**Distance**](classastrea_1_1astro_1_1CartesianVector.md) | [**\_crashRadius**](#variable-_crashradius)  <br>_Crash radius of the celestial body._  |
|  [**Unitless**](classastrea_1_1astro_1_1CartesianVector.md) | [**\_eccentricity**](#variable-_eccentricity)  <br>_Eccentricity._  |
|  [**BodyUnitlessPerTime**](classastrea_1_1astro_1_1CartesianVector.md) | [**\_eccentricityRate**](#variable-_eccentricityrate)  <br>_Rate of change of the eccentricity._  |
|  [**Distance**](classastrea_1_1astro_1_1CartesianVector.md) | [**\_equitorialRadius**](#variable-_equitorialradius)  <br>_Equatorial radius of the celestial body._  |
|  [**Angle**](classastrea_1_1astro_1_1CartesianVector.md) | [**\_inclination**](#variable-_inclination)  <br>_Inclination._  |
|  [**BodyAngularRate**](classastrea_1_1astro_1_1CartesianVector.md) | [**\_inclinationRate**](#variable-_inclinationrate)  <br>_Rate of change of the inclination._  |
|  [**Unitless**](classastrea_1_1astro_1_1CartesianVector.md) | [**\_j2**](#variable-_j2)  <br>_J2 gravitational coefficient of the celestial body._  |
|  [**Unitless**](classastrea_1_1astro_1_1CartesianVector.md) | [**\_j3**](#variable-_j3)  <br>_J3 gravitational coefficient of the celestial body._  |
|  [**Angle**](classastrea_1_1astro_1_1CartesianVector.md) | [**\_longitudeOfPerigee**](#variable-_longitudeofperigee)  <br>_Argument of perigee._  |
|  [**BodyAngularRate**](classastrea_1_1astro_1_1CartesianVector.md) | [**\_longitudeOfPerigeeRate**](#variable-_longitudeofperigeerate)  <br>_Rate of change of the longitude of perigee._  |
|  [**Mass**](classastrea_1_1astro_1_1CartesianVector.md) | [**\_mass**](#variable-_mass)  <br>_Mass of the celestial body._  |
|  [**Angle**](classastrea_1_1astro_1_1CartesianVector.md) | [**\_meanAnomaly**](#variable-_meananomaly)  <br>_Mean anomaly._  |
|  [**Angle**](classastrea_1_1astro_1_1CartesianVector.md) | [**\_meanLongitude**](#variable-_meanlongitude)  <br>_Mean longitude._  |
|  [**BodyAngularRate**](classastrea_1_1astro_1_1CartesianVector.md) | [**\_meanLongitudeRate**](#variable-_meanlongituderate)  <br>_Rate of change of the mean longitude._  |
|  [**GravParam**](classastrea_1_1astro_1_1CartesianVector.md) | [**\_mu**](#variable-_mu)  <br>_Gravitational parameter (mu) of the celestial body._  |
|  std::string | [**\_name**](#variable-_name)  <br>_Name of the celestial body._  |
|  [**CelestialBodyId**](namespaceastrea_1_1astro.md#enum-celestialbodyid) | [**\_parent**](#variable-_parent)  <br>_Parent celestial body._  |
|  [**GravParam**](classastrea_1_1astro_1_1CartesianVector.md) | [**\_parentMu**](#variable-_parentmu)  <br>_Gravitational parameter of the parent celestial body, if any._  |
|  [**Distance**](classastrea_1_1astro_1_1CartesianVector.md) | [**\_polarRadius**](#variable-_polarradius)  <br>_Polar radius of the celestial body._  |
|  [**Date**](classastrea_1_1astro_1_1Date.md) | [**\_referenceDate**](#variable-_referencedate)  <br>_Reference date for the celestial body data._  |
|  [**Angle**](classastrea_1_1astro_1_1CartesianVector.md) | [**\_rightAscension**](#variable-_rightascension)  <br>_Right ascension._  |
|  [**BodyAngularRate**](classastrea_1_1astro_1_1CartesianVector.md) | [**\_rightAscensionRate**](#variable-_rightascensionrate)  <br>_Rate of change of the right ascension._  |
|  [**AngularRate**](classastrea_1_1astro_1_1CartesianVector.md) | [**\_rotationRate**](#variable-_rotationrate)  <br>_Rotation rate of the celestial body._  |
|  [**Distance**](classastrea_1_1astro_1_1CartesianVector.md) | [**\_semimajorAxis**](#variable-_semimajoraxis)  <br>_Semimajor axis._  |
|  [**InterplanetaryVelocity**](classastrea_1_1astro_1_1CartesianVector.md) | [**\_semimajorAxisRate**](#variable-_semimajoraxisrate)  <br>_Rate of change of the semimajor axis._  |
|  [**Time**](classastrea_1_1astro_1_1CartesianVector.md) | [**\_siderealPeriod**](#variable-_siderealperiod)  <br>_Sidereal period of the celestial body._  |
|  [**Distance**](classastrea_1_1astro_1_1CartesianVector.md) | [**\_sphereOfInfluence**](#variable-_sphereofinfluence)  <br>_Crash radius of the celestial body._  |
|  [**Angle**](classastrea_1_1astro_1_1CartesianVector.md) | [**\_trueAnomaly**](#variable-_trueanomaly)  <br>_True anomaly._  |
|  [**CelestialBodyType**](namespaceastrea_1_1astro.md#enum-celestialbodytype) | [**\_type**](#variable-_type)  <br>_Type of the celestial body._  |


## Protected Static Attributes

| Type | Name |
| ---: | :--- |
|  [**constexpr**](classastrea_1_1astro_1_1CartesianVector.md) [**double**](classastrea_1_1astro_1_1CartesianVector.md) | [**\_COEFF\_ZERO\_FACTOR**](#variable-_coeff_zero_factor)   = `1.0`<br> |














## Protected Functions

| Type | Name |
| ---: | :--- |
|  [**const**](classastrea_1_1astro_1_1CartesianVector.md) [**auto**](classastrea_1_1astro_1_1CartesianVector.md) | [**get\_chebyshev\_table\_coefficients**](#function-get_chebyshev_table_coefficients) ([**const**](classastrea_1_1astro_1_1CartesianVector.md) [**Date**](classastrea_1_1astro_1_1Date.md) & date) const<br>_Get the Chebyshev polynomial coefficients for the celestial body at a specific date._  |
| virtual [**constexpr**](classastrea_1_1astro_1_1CartesianVector.md) [**CoefficientPack**](classastrea_1_1astro_1_1CelestialBody.md#typedef-coefficientpack) | [**get\_linear\_expansion\_coefficients**](#function-get_linear_expansion_coefficients) () const<br>_Get the linear expansion coefficients for the celestial body's orbital elements._  |
|  [**CartesianVector**](classastrea_1_1astro_1_1CartesianVector.md)&lt; [**Distance**](classastrea_1_1astro_1_1CartesianVector.md), [**Frame\_T**](classastrea_1_1astro_1_1CartesianVector.md) &gt; | [**get\_position\_at\_impl**](#function-get_position_at_impl) ([**const**](classastrea_1_1astro_1_1CartesianVector.md) [**Date**](classastrea_1_1astro_1_1Date.md) & date) const<br>_Get the position of the celestial body at a specific date in a specified frame using Chebyshev polynomials._  |
|  [**CartesianVector**](classastrea_1_1astro_1_1CartesianVector.md)&lt; [**Velocity**](classastrea_1_1astro_1_1CartesianVector.md), [**Frame\_T**](classastrea_1_1astro_1_1CartesianVector.md) &gt; | [**get\_velocity\_at\_impl**](#function-get_velocity_at_impl) ([**const**](classastrea_1_1astro_1_1CartesianVector.md) [**Date**](classastrea_1_1astro_1_1Date.md) & date) const<br>_Get the velocity of the celestial body at a specific date in a specified frame using Chebyshev polynomials._  |




## Public Functions Documentation




### function CelestialBody [1/3]

_Default constructor for_ [_**CelestialBody**_](classastrea_1_1astro_1_1CelestialBody.md) _._
```C++
astrea::astro::CelestialBody::CelestialBody () = default
```




<hr>



### function CelestialBody [2/3]

_Constructs a_ [_**CelestialBody**_](classastrea_1_1astro_1_1CelestialBody.md) _from individual parameters._
```C++
inline constexpr astrea::astro::CelestialBody::CelestialBody (
    const  CelestialBodyParameters & data
) 
```





**Parameters:**


* `data` The [**CelestialBodyParameters**](structastrea_1_1astro_1_1CelestialBodyParameters.md) struct containing all the necessary parameters to construct a [**CelestialBody**](classastrea_1_1astro_1_1CelestialBody.md). 




        

<hr>



### function CelestialBody [3/3]

_Copy constructor for_ [_**CelestialBody**_](classastrea_1_1astro_1_1CelestialBody.md) _._
```C++
astrea::astro::CelestialBody::CelestialBody (
    const  CelestialBody & other
) = default
```





**Parameters:**


* `other` The [**CelestialBody**](classastrea_1_1astro_1_1CelestialBody.md) to copy from. 




        

<hr>



### function find\_atmospheric\_density 

_Finds the atmospheric density at a given date and state._ 
```C++
virtual Density astrea::astro::CelestialBody::find_atmospheric_density (
    const  Date & date,
    const  Distance & altitude
) const
```





**Parameters:**


* `date` The date at which to find the atmospheric density. 
* `state` The [**Cartesian**](classastrea_1_1astro_1_1Cartesian.md) state vector at which to find the atmospheric density. 



**Returns:**

Density The atmospheric density at the specified date and state.




**Note:**

Assume that most bodies have no significant atmosphere. Assume that the atmosphere of the gas giants is defined by their radii, e.g. outside of their equitorial radius, they have no noticible atmosphere and inside that radius, the object will crash. 





        

<hr>



### function get\_axial\_tilt 

_Get the axial tilt of the celestial body._ 
```C++
inline constexpr  const  Angle & astrea::astro::CelestialBody::get_axial_tilt () const
```





**Returns:**

const Angle& Reference to the axial tilt of the celestial body. 





        

<hr>



### function get\_crash\_radius 

_Get the crash radius of the celestial body._ 
```C++
inline constexpr  const  Distance & astrea::astro::CelestialBody::get_crash_radius () const
```





**Returns:**

const Distance& Reference to the crash radius of the celestial body. 





        

<hr>



### function get\_eccentricity 

_Get the eccentricity of the celestial body._ 
```C++
inline constexpr  const  Unitless & astrea::astro::CelestialBody::get_eccentricity () const
```





**Returns:**

const Unitless& Reference to the eccentricity of the celestial body. 





        

<hr>



### function get\_eccentricity\_rate 

_Get the eccentricity rate of the celestial body._ 
```C++
inline constexpr  const  BodyUnitlessPerTime & astrea::astro::CelestialBody::get_eccentricity_rate () const
```





**Returns:**

const BodyUnitlessPerTime& Reference to the eccentricity rate of the celestial body. 





        

<hr>



### function get\_equitorial\_radius 

_Get the equatorial radius of the celestial body._ 
```C++
inline constexpr  const  Distance & astrea::astro::CelestialBody::get_equitorial_radius () const
```





**Returns:**

const Distance& Reference to the equatorial radius of the celestial body. 





        

<hr>



### function get\_inclination 

_Get the inclination of the celestial body._ 
```C++
inline constexpr  const  Angle & astrea::astro::CelestialBody::get_inclination () const
```





**Returns:**

const Angle& Reference to the inclination of the celestial body. 





        

<hr>



### function get\_inclination\_rate 

_Get the inclination rate of the celestial body._ 
```C++
inline constexpr  const  BodyAngularRate & astrea::astro::CelestialBody::get_inclination_rate () const
```





**Returns:**

const BodyAngularRate& Reference to the inclination rate of the celestial body. 





        

<hr>



### function get\_j2 

_Get the J2 gravitational coefficient of the celestial body._ 
```C++
inline constexpr  const  Unitless & astrea::astro::CelestialBody::get_j2 () const
```





**Returns:**

const Unitless& Reference to the J2 coefficient of the celestial body. 





        

<hr>



### function get\_j3 

_Get the J3 gravitational coefficient of the celestial body._ 
```C++
inline constexpr  const  Unitless & astrea::astro::CelestialBody::get_j3 () const
```





**Returns:**

const Unitless& Reference to the J3 coefficient of the celestial body. 





        

<hr>



### function get\_keplerian\_elements\_at 

_Get the keplerian elements of the celestial body at a specific date using a linear approximation._ 
```C++
Keplerian astrea::astro::CelestialBody::get_keplerian_elements_at (
    const  Date & date
) const
```





**Parameters:**


* `date` The date at which to get the state of the celestial body. 



**Returns:**

[**Keplerian**](classastrea_1_1astro_1_1Keplerian.md) The approximate [**Keplerian**](classastrea_1_1astro_1_1Keplerian.md) elements of the celestial body at the specified date. 





        

<hr>



### function get\_longitude\_of\_perigee 

_Get the longitude of perigee of the celestial body._ 
```C++
inline constexpr  const  Angle & astrea::astro::CelestialBody::get_longitude_of_perigee () const
```





**Returns:**

const Angle& Reference to the longitude of perigee of the celestial body. 





        

<hr>



### function get\_longitude\_of\_perigee\_rate 

_Get the longitude of perigee rate of the celestial body._ 
```C++
inline constexpr  const  BodyAngularRate & astrea::astro::CelestialBody::get_longitude_of_perigee_rate () const
```





**Returns:**

const BodyAngularRate& Reference to the longitude of perigee rate of the celestial body. 





        

<hr>



### function get\_mass 

_Get the mass of the celestial body._ 
```C++
inline constexpr  const  Mass & astrea::astro::CelestialBody::get_mass () const
```





**Returns:**

const Mass& Reference to the mass of the celestial body. 





        

<hr>



### function get\_mean\_anomaly 

_Get the mean anomaly of the celestial body._ 
```C++
inline constexpr  const  Angle & astrea::astro::CelestialBody::get_mean_anomaly () const
```





**Returns:**

const Angle& Reference to the mean anomaly of the celestial body. 





        

<hr>



### function get\_mean\_longitude 

_Get the mean longitude of the celestial body._ 
```C++
inline constexpr  const  Angle & astrea::astro::CelestialBody::get_mean_longitude () const
```





**Returns:**

const Angle& Reference to the mean longitude of the celestial body. 





        

<hr>



### function get\_mean\_longitude\_rate 

_Get the mean longitude rate of the celestial body._ 
```C++
inline constexpr  const  BodyAngularRate & astrea::astro::CelestialBody::get_mean_longitude_rate () const
```





**Returns:**

const BodyAngularRate& Reference to the mean longitude rate of the celestial body. 





        

<hr>



### function get\_mu 

_Get the gravitational parameter (mu) of the celestial body._ 
```C++
inline constexpr  const  GravParam & astrea::astro::CelestialBody::get_mu () const
```





**Returns:**

const GravParam& Reference to the gravitational parameter of the celestial body. 





        

<hr>



### function get\_name 

_Get the name of the celestial body._ 
```C++
inline constexpr  const std::string & astrea::astro::CelestialBody::get_name () const
```





**Returns:**

const std::string& Reference to the name of the celestial body. 





        

<hr>



### function get\_parent 

_Get the parent celestial body._ 
```C++
inline constexpr  const  CelestialBodyId & astrea::astro::CelestialBody::get_parent () const
```





**Returns:**

const std::string& Reference to the name of the parent celestial body. 





        

<hr>



### function get\_polar\_radius 

_Get the polar radius of the celestial body._ 
```C++
inline constexpr  const  Distance & astrea::astro::CelestialBody::get_polar_radius () const
```





**Returns:**

const Distance& Reference to the polar radius of the celestial body. 





        

<hr>



### function get\_position\_at 

_Get the position of the celestial body at a specific date in the ICRF frame._ 
```C++
virtual CartesianVector < Distance , frames::solar_system_barycenter::icrf > astrea::astro::CelestialBody::get_position_at (
    const  Date & date
) const
```





**Parameters:**


* `date` The date at which to get the position of the celestial body. 



**Returns:**

CartesianVector&lt;Distance,  frames::solar\_system\_barycenter::icrf&gt; The position of the celestial body at the specified date.




**Note:**

This function is wrong. It actually returns the position in the ICRF frame, centered on the object's parent. Need to figure out how to make dynamic centers work with frames. 





        

<hr>



### function get\_right\_ascension 

_Get the right ascension of the celestial body._ 
```C++
inline constexpr  const  Angle & astrea::astro::CelestialBody::get_right_ascension () const
```





**Returns:**

const Angle& Reference to the right ascension of the celestial body. 





        

<hr>



### function get\_right\_ascension\_rate 

_Get the right ascension rate of the celestial body._ 
```C++
inline constexpr  const  BodyAngularRate & astrea::astro::CelestialBody::get_right_ascension_rate () const
```





**Returns:**

const BodyAngularRate& Reference to the right ascension rate of the celestial body. 





        

<hr>



### function get\_rotation\_rate 

_Get the rotation rate of the celestial body._ 
```C++
inline constexpr  const  AngularRate & astrea::astro::CelestialBody::get_rotation_rate () const
```





**Returns:**

const AngularRate& Reference to the rotation rate of the celestial body. 





        

<hr>



### function get\_semimajor 

_Get the semimajor axis of the celestial body._ 
```C++
inline constexpr  const  Distance & astrea::astro::CelestialBody::get_semimajor () const
```





**Returns:**

const Distance& Reference to the semimajor axis of the celestial body. 





        

<hr>



### function get\_semimajor\_rate 

_Get the semimajor axis rate of the celestial body._ 
```C++
inline constexpr  const  InterplanetaryVelocity & astrea::astro::CelestialBody::get_semimajor_rate () const
```





**Returns:**

const InterplanetaryVelocity& Reference to the semimajor axis rate of the celestial body. 





        

<hr>



### function get\_sidereal\_period 

_Get the sidereal period of the celestial body._ 
```C++
inline constexpr  const  Time & astrea::astro::CelestialBody::get_sidereal_period () const
```





**Returns:**

const Time& Reference to the sidereal period of the celestial body. 





        

<hr>



### function get\_sphere\_of\_influence 

_Get the sphere of influence of the celestial body._ 
```C++
inline constexpr  const  Distance & astrea::astro::CelestialBody::get_sphere_of_influence () const
```





**Returns:**

const Distance& Reference to the sphere of influence of the celestial body. 





        

<hr>



### function get\_true\_anomaly 

_Get the true anomaly of the celestial body._ 
```C++
inline Angle astrea::astro::CelestialBody::get_true_anomaly () const
```





**Returns:**

const Angle& Reference to the true anomaly of the celestial body. 





        

<hr>



### function get\_type 

_Get the type of the celestial body._ 
```C++
inline constexpr  const  CelestialBodyType & astrea::astro::CelestialBody::get_type () const
```





**Returns:**

const CelestialBodyType& Reference to the type of the celestial body. 





        

<hr>



### function operator== 

_Equality operator for_ [_**CelestialBody**_](classastrea_1_1astro_1_1CelestialBody.md) _._
```C++
inline constexpr  bool astrea::astro::CelestialBody::operator== (
    const  CelestialBody & other
) const
```





**Parameters:**


* `other` The [**CelestialBody**](classastrea_1_1astro_1_1CelestialBody.md) to compare with. 



**Returns:**

true if the celestial bodies are equal, false otherwise. 





        

<hr>



### function ~CelestialBody 

_Default destructor for_ [_**CelestialBody**_](classastrea_1_1astro_1_1CelestialBody.md) _._
```C++
virtual astrea::astro::CelestialBody::~CelestialBody () = default
```




<hr>
## Public Static Functions Documentation




### function get\_id 

_Get the parent celestial body._ 
```C++
static inline constexpr  CelestialBodyId astrea::astro::CelestialBody::get_id () 
```





**Returns:**

const std::string& Reference to the name of the parent celestial body. 





        

<hr>
## Protected Types Documentation




### typedef CoefficientPack 

_Type alias for a tuple of linear expansion coefficients._ 
```C++
using astrea::astro::CelestialBody::CoefficientPack =  std::tuple< mp_units::quantity<mp_units::angular::unit_symbols::rad / (JulianCentury * JulianCentury)>, mp_units::quantity<mp_units::angular::unit_symbols::rad>, mp_units::quantity<mp_units::angular::unit_symbols::rad>, mp_units::quantity<mp_units::angular::unit_symbols::rad / JulianCentury> >;
```




<hr>
## Protected Attributes Documentation




### variable \_axialTilt 

_Axial tilt of the celestial body._ 
```C++
Angle astrea::astro::CelestialBody::_axialTilt;
```




<hr>



### variable \_crashRadius 

_Crash radius of the celestial body._ 
```C++
Distance astrea::astro::CelestialBody::_crashRadius;
```




<hr>



### variable \_eccentricity 

_Eccentricity._ 
```C++
Unitless astrea::astro::CelestialBody::_eccentricity;
```




<hr>



### variable \_eccentricityRate 

_Rate of change of the eccentricity._ 
```C++
BodyUnitlessPerTime astrea::astro::CelestialBody::_eccentricityRate;
```




<hr>



### variable \_equitorialRadius 

_Equatorial radius of the celestial body._ 
```C++
Distance astrea::astro::CelestialBody::_equitorialRadius;
```




<hr>



### variable \_inclination 

_Inclination._ 
```C++
Angle astrea::astro::CelestialBody::_inclination;
```




<hr>



### variable \_inclinationRate 

_Rate of change of the inclination._ 
```C++
BodyAngularRate astrea::astro::CelestialBody::_inclinationRate;
```




<hr>



### variable \_j2 

_J2 gravitational coefficient of the celestial body._ 
```C++
Unitless astrea::astro::CelestialBody::_j2;
```




<hr>



### variable \_j3 

_J3 gravitational coefficient of the celestial body._ 
```C++
Unitless astrea::astro::CelestialBody::_j3;
```




<hr>



### variable \_longitudeOfPerigee 

_Argument of perigee._ 
```C++
Angle astrea::astro::CelestialBody::_longitudeOfPerigee;
```




<hr>



### variable \_longitudeOfPerigeeRate 

_Rate of change of the longitude of perigee._ 
```C++
BodyAngularRate astrea::astro::CelestialBody::_longitudeOfPerigeeRate;
```




<hr>



### variable \_mass 

_Mass of the celestial body._ 
```C++
Mass astrea::astro::CelestialBody::_mass;
```




<hr>



### variable \_meanAnomaly 

_Mean anomaly._ 
```C++
Angle astrea::astro::CelestialBody::_meanAnomaly;
```




<hr>



### variable \_meanLongitude 

_Mean longitude._ 
```C++
Angle astrea::astro::CelestialBody::_meanLongitude;
```




<hr>



### variable \_meanLongitudeRate 

_Rate of change of the mean longitude._ 
```C++
BodyAngularRate astrea::astro::CelestialBody::_meanLongitudeRate;
```




<hr>



### variable \_mu 

_Gravitational parameter (mu) of the celestial body._ 
```C++
GravParam astrea::astro::CelestialBody::_mu;
```




<hr>



### variable \_name 

_Name of the celestial body._ 
```C++
std::string astrea::astro::CelestialBody::_name;
```




<hr>



### variable \_parent 

_Parent celestial body._ 
```C++
CelestialBodyId astrea::astro::CelestialBody::_parent;
```




<hr>



### variable \_parentMu 

_Gravitational parameter of the parent celestial body, if any._ 
```C++
GravParam astrea::astro::CelestialBody::_parentMu;
```




<hr>



### variable \_polarRadius 

_Polar radius of the celestial body._ 
```C++
Distance astrea::astro::CelestialBody::_polarRadius;
```




<hr>



### variable \_referenceDate 

_Reference date for the celestial body data._ 
```C++
Date astrea::astro::CelestialBody::_referenceDate;
```




<hr>



### variable \_rightAscension 

_Right ascension._ 
```C++
Angle astrea::astro::CelestialBody::_rightAscension;
```




<hr>



### variable \_rightAscensionRate 

_Rate of change of the right ascension._ 
```C++
BodyAngularRate astrea::astro::CelestialBody::_rightAscensionRate;
```




<hr>



### variable \_rotationRate 

_Rotation rate of the celestial body._ 
```C++
AngularRate astrea::astro::CelestialBody::_rotationRate;
```




<hr>



### variable \_semimajorAxis 

_Semimajor axis._ 
```C++
Distance astrea::astro::CelestialBody::_semimajorAxis;
```




<hr>



### variable \_semimajorAxisRate 

_Rate of change of the semimajor axis._ 
```C++
InterplanetaryVelocity astrea::astro::CelestialBody::_semimajorAxisRate;
```




<hr>



### variable \_siderealPeriod 

_Sidereal period of the celestial body._ 
```C++
Time astrea::astro::CelestialBody::_siderealPeriod;
```




<hr>



### variable \_sphereOfInfluence 

_Crash radius of the celestial body._ 
```C++
Distance astrea::astro::CelestialBody::_sphereOfInfluence;
```




<hr>



### variable \_trueAnomaly 

_True anomaly._ 
```C++
Angle astrea::astro::CelestialBody::_trueAnomaly;
```




<hr>



### variable \_type 

_Type of the celestial body._ 
```C++
CelestialBodyType astrea::astro::CelestialBody::_type;
```




<hr>
## Protected Static Attributes Documentation




### variable \_COEFF\_ZERO\_FACTOR 

```C++
constexpr double astrea::astro::CelestialBody::_COEFF_ZERO_FACTOR;
```




<hr>
## Protected Functions Documentation




### function get\_chebyshev\_table\_coefficients 

_Get the Chebyshev polynomial coefficients for the celestial body at a specific date._ 
```C++
template<typename  Table_T>
inline const  auto astrea::astro::CelestialBody::get_chebyshev_table_coefficients (
    const  Date & date
) const
```





**Template parameters:**


* `Table_T` The Chebyshev table type to use for interpolation. 



**Parameters:**


* `date` The date at which to get the Chebyshev coefficients. 



**Returns:**

A tuple containing references to the x, y, and z Chebyshev coefficient vectors. 





        

<hr>



### function get\_linear\_expansion\_coefficients 

_Get the linear expansion coefficients for the celestial body's orbital elements._ 
```C++
inline virtual constexpr  CoefficientPack astrea::astro::CelestialBody::get_linear_expansion_coefficients () const
```





**Returns:**

CoefficientPack A tuple containing the linear expansion coefficients.




**Note:**

The default implementation returns zero coefficients, indicating no perturbations. Derived classes should override this method to provide actual coefficients. 





        

<hr>



### function get\_position\_at\_impl 

_Get the position of the celestial body at a specific date in a specified frame using Chebyshev polynomials._ 
```C++
template<typename  Table_T, typename  Frame_T>
inline CartesianVector < Distance , Frame_T > astrea::astro::CelestialBody::get_position_at_impl (
    const  Date & date
) const
```





**Template parameters:**


* `Table_T` The Chebyshev table type to use for interpolation. 
* `Frame_T` The frame type in which to return the position. 



**Parameters:**


* `date` The date at which to get the position of the celestial body. 



**Returns:**

CartesianVector&lt;Distance, Frame\_T&gt; The position of the celestial body at the specified date in the specified frame. 





        

<hr>



### function get\_velocity\_at\_impl 

_Get the velocity of the celestial body at a specific date in a specified frame using Chebyshev polynomials._ 
```C++
template<typename  Table_T, typename  Frame_T>
inline CartesianVector < Velocity , Frame_T > astrea::astro::CelestialBody::get_velocity_at_impl (
    const  Date & date
) const
```





**Template parameters:**


* `Table_T` The Chebyshev table type to use for interpolation. 
* `Frame_T` The frame type in which to return the velocity. 



**Parameters:**


* `date` The date at which to get the velocity of the celestial body. 



**Returns:**

CartesianVector&lt;Velocity, Frame\_T&gt; The velocity of the celestial body at the specified date in the specified frame. 





        

<hr>

------------------------------
The documentation for this class was generated from the following file `astrea/astro/astro/systems/CelestialBody.hpp`

