

# Class astrea::astro::Keplerian

**template &lt;IsFrame [**auto**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) \_frame\_&gt;**



[**ClassList**](annotated.md) **>** [**astrea**](namespaceastrea.md) **>** [**astro**](namespaceastrea_1_1astro.md) **>** [**Keplerian**](classastrea_1_1astro_1_1Keplerian.md)



_The_ [_**Keplerian**_](classastrea_1_1astro_1_1Keplerian.md) _class represents the_[_**Keplerian**_](classastrea_1_1astro_1_1Keplerian.md) _orbital elements._[More...](#detailed-description)

* `#include <Keplerian.hpp>`























## Public Static Attributes

| Type | Name |
| ---: | :--- |
|  [**constexpr**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) [**auto**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) | [**frame**](#variable-frame)   = `\_frame\_`<br>_The reference frame of the_ [_**Keplerian**_](classastrea_1_1astro_1_1Keplerian.md) _elements._ |














## Public Functions

| Type | Name |
| ---: | :--- |
|   | [**Keplerian**](#function-keplerian-17) ([**Unitless**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) scale=0.0 \*astrea::detail::unitless) <br>_Constructs a_ [_**Keplerian**_](classastrea_1_1astro_1_1Keplerian.md) _object with default values._ |
|   | [**Keplerian**](#function-keplerian-27) ([**const**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) [**Distance**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) & semimajor, [**const**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) [**Unitless**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) & eccentricity, [**const**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) [**Angle**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) & inclination, [**const**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) [**Angle**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) & rightAscension, [**const**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) [**Angle**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) & argPerigee, [**const**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) [**Angle**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) & trueAnomaly) <br>_Constructs a_ [_**Keplerian**_](classastrea_1_1astro_1_1Keplerian.md) _object with specified values._ |
|   | [**Keplerian**](#function-keplerian-37) ([**const**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) [**Keplerian**](classastrea_1_1astro_1_1Keplerian.md)&lt; \_frame\_ &gt; & elements, [**const**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) [**GravParam**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) & mu) <br>_Constructs a_ [_**Keplerian**_](classastrea_1_1astro_1_1Keplerian.md) _object from another_[_**Keplerian**_](classastrea_1_1astro_1_1Keplerian.md) _object._ |
|   | [**Keplerian**](#function-keplerian-47) ([**const**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) [**Cartesian**](classastrea_1_1astro_1_1Cartesian.md)&lt; \_frame\_ &gt; & elements, [**const**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) [**GravParam**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) & mu) <br>_Constructs a_ [_**Keplerian**_](classastrea_1_1astro_1_1Keplerian.md) _object from_[_**Cartesian**_](classastrea_1_1astro_1_1Cartesian.md) _elements._ |
|   | [**Keplerian**](#function-keplerian-57) ([**const**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) [**Equinoctial**](classastrea_1_1astro_1_1Equinoctial.md)&lt; \_frame\_ &gt; & elements, [**const**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) [**GravParam**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) & mu) <br>_Constructs a_ [_**Keplerian**_](classastrea_1_1astro_1_1Keplerian.md) _object from_[_**Equinoctial**_](classastrea_1_1astro_1_1Equinoctial.md) _elements._ |
|   | [**Keplerian**](#function-keplerian-67) ([**const**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) [**Keplerian**](classastrea_1_1astro_1_1Keplerian.md)&lt; \_frame\_ &gt; & other) <br>_Copy constructor for_ [_**Keplerian**_](classastrea_1_1astro_1_1Keplerian.md) _._ |
|   | [**Keplerian**](#function-keplerian-77) ([**Keplerian**](classastrea_1_1astro_1_1Keplerian.md)&lt; \_frame\_ &gt; && other) noexcept<br>_Move constructor for_ [_**Keplerian**_](classastrea_1_1astro_1_1Keplerian.md) _._ |
|  std::vector&lt; [**Unitless**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) &gt; | [**force\_to\_vector**](#function-force_to_vector) () const<br>_Converts the_ [_**Keplerian**_](classastrea_1_1astro_1_1Keplerian.md) _state vector to a vector of unitless values._ |
|  [**const**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) [**Angle**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) & | [**get\_argument\_of\_perigee**](#function-get_argument_of_perigee) () const<br>_Get the argument of perigee of the_ [_**Keplerian**_](classastrea_1_1astro_1_1Keplerian.md) _state vector._ |
|  [**const**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) [**Unitless**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) & | [**get\_eccentricity**](#function-get_eccentricity) () const<br>_Get the eccentricity of the_ [_**Keplerian**_](classastrea_1_1astro_1_1Keplerian.md) _state vector._ |
|  [**const**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) [**Angle**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) & | [**get\_inclination**](#function-get_inclination) () const<br>_Get the inclination of the_ [_**Keplerian**_](classastrea_1_1astro_1_1Keplerian.md) _state vector._ |
|  [**Angle**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) | [**get\_mean\_anomaly**](#function-get_mean_anomaly) () const<br>_Get the mean anomaly of the_ [_**Keplerian**_](classastrea_1_1astro_1_1Keplerian.md) _state vector._ |
|  [**MeanMotion**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) | [**get\_mean\_motion**](#function-get_mean_motion) ([**const**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) [**GravParam**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) & mu) const<br>_Get the mean motion of the_ [_**Keplerian**_](classastrea_1_1astro_1_1Keplerian.md) _state vector._ |
|  [**Time**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) | [**get\_orbital\_period**](#function-get_orbital_period) ([**const**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) [**GravParam**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) & mu) const<br>_Get the orbital period of the_ [_**Keplerian**_](classastrea_1_1astro_1_1Keplerian.md) _state vector._ |
|  [**const**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) [**Angle**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) & | [**get\_right\_ascension**](#function-get_right_ascension) () const<br>_Get the right ascension of the ascending node of the_ [_**Keplerian**_](classastrea_1_1astro_1_1Keplerian.md) _state vector._ |
|  [**const**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) [**Distance**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) & | [**get\_semimajor**](#function-get_semimajor) () const<br>_Get the semimajor axis of the_ [_**Keplerian**_](classastrea_1_1astro_1_1Keplerian.md) _state vector._ |
|  [**const**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) [**Angle**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) & | [**get\_true\_anomaly**](#function-get_true_anomaly) () const<br>_Get the true anomaly of the_ [_**Keplerian**_](classastrea_1_1astro_1_1Keplerian.md) _state vector._ |
|  [**Keplerian**](classastrea_1_1astro_1_1Keplerian.md)&lt; [**target\_frame**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) &gt; | [**in\_frame**](#function-in_frame) ([**const**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) [**Date**](classastrea_1_1astro_1_1Date.md) & epoch, [**const**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) [**GravParam**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) & mu) const<br>_Converts this_ [_**Keplerian**_](classastrea_1_1astro_1_1Keplerian.md) _state to_[_**Keplerian**_](classastrea_1_1astro_1_1Keplerian.md) _elements expressed in a different frame._ |
|  [**Keplerian**](classastrea_1_1astro_1_1Keplerian.md) | [**interpolate**](#function-interpolate) ([**const**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) [**Time**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) & thisTime, [**const**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) [**Time**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) & otherTime, [**const**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) [**Keplerian**](classastrea_1_1astro_1_1Keplerian.md)&lt; \_frame\_ &gt; & other, [**const**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) [**GravParam**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) & mu, [**const**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) [**Time**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) & targetTime) const<br>_Interpolates between two_ [_**Keplerian**_](classastrea_1_1astro_1_1Keplerian.md) _state vectors._ |
|  [**bool**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) | [**operator!=**](#function-operator) ([**const**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) [**Keplerian**](classastrea_1_1astro_1_1Keplerian.md)&lt; \_frame\_ &gt; & other) const<br>_Checks if two_ [_**Keplerian**_](classastrea_1_1astro_1_1Keplerian.md) _objects are not equal._ |
|  [**Keplerian**](classastrea_1_1astro_1_1Keplerian.md) | [**operator\***](#function-operator_1) ([**const**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) [**Unitless**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) & multiplier) const<br>_Multiplies the_ [_**Keplerian**_](classastrea_1_1astro_1_1Keplerian.md) _state vector by a scalar._ |
|  [**Keplerian**](classastrea_1_1astro_1_1Keplerian.md) & | [**operator\*=**](#function-operator_2) ([**const**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) [**Unitless**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) & multiplier) <br>_Multiplies the_ [_**Keplerian**_](classastrea_1_1astro_1_1Keplerian.md) _state vector by a scalar._ |
|  [**Keplerian**](classastrea_1_1astro_1_1Keplerian.md) | [**operator+**](#function-operator_3) ([**const**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) [**Keplerian**](classastrea_1_1astro_1_1Keplerian.md)&lt; \_frame\_ &gt; & other) const<br>_Adds two_ [_**Keplerian**_](classastrea_1_1astro_1_1Keplerian.md) _objects._ |
|  [**Keplerian**](classastrea_1_1astro_1_1Keplerian.md) & | [**operator+=**](#function-operator_4) ([**const**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) [**Keplerian**](classastrea_1_1astro_1_1Keplerian.md)&lt; \_frame\_ &gt; & other) <br>_Adds another_ [_**Keplerian**_](classastrea_1_1astro_1_1Keplerian.md) _object to the current one._ |
|  [**Keplerian**](classastrea_1_1astro_1_1Keplerian.md) | [**operator-**](#function-operator-) ([**const**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) [**Keplerian**](classastrea_1_1astro_1_1Keplerian.md)&lt; \_frame\_ &gt; & other) const<br>_Subtracts another_ [_**Keplerian**_](classastrea_1_1astro_1_1Keplerian.md) _object from the current one._ |
|  [**Keplerian**](classastrea_1_1astro_1_1Keplerian.md) & | [**operator-=**](#function-operator-_1) ([**const**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) [**Keplerian**](classastrea_1_1astro_1_1Keplerian.md)&lt; \_frame\_ &gt; & other) <br>_Subtracts another_ [_**Keplerian**_](classastrea_1_1astro_1_1Keplerian.md) _object from the current one._ |
|  [**KeplerianPartial**](classastrea_1_1astro_1_1KeplerianPartial.md)&lt; \_frame\_ &gt; | [**operator/**](#function-operator_5) ([**const**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) [**Time**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) & time) const<br>_Divides the_ [_**Keplerian**_](classastrea_1_1astro_1_1Keplerian.md) _state vector by a time._ |
|  [**Keplerian**](classastrea_1_1astro_1_1Keplerian.md) | [**operator/**](#function-operator_6) ([**const**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) [**Unitless**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) & divisor) const<br>_Divides the_ [_**Keplerian**_](classastrea_1_1astro_1_1Keplerian.md) _state vector by another_[_**Keplerian**_](classastrea_1_1astro_1_1Keplerian.md) _object._ |
|  [**Keplerian**](classastrea_1_1astro_1_1Keplerian.md) & | [**operator/=**](#function-operator_7) ([**const**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) [**Unitless**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) & divisor) <br>_Divides the_ [_**Keplerian**_](classastrea_1_1astro_1_1Keplerian.md) _state vector by a scalar._ |
|  [**Keplerian**](classastrea_1_1astro_1_1Keplerian.md) & | [**operator=**](#function-operator_8) ([**Keplerian**](classastrea_1_1astro_1_1Keplerian.md)&lt; \_frame\_ &gt; && other) noexcept<br>_Move assignment operator for_ [_**Keplerian**_](classastrea_1_1astro_1_1Keplerian.md) _._ |
|  [**Keplerian**](classastrea_1_1astro_1_1Keplerian.md) & | [**operator=**](#function-operator_9) ([**const**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) [**Keplerian**](classastrea_1_1astro_1_1Keplerian.md)&lt; \_frame\_ &gt; & other) <br>_Copy assignment operator for_ [_**Keplerian**_](classastrea_1_1astro_1_1Keplerian.md) _._ |
|  [**bool**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) | [**operator==**](#function-operator_10) ([**const**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) [**Keplerian**](classastrea_1_1astro_1_1Keplerian.md)&lt; \_frame\_ &gt; & other) const<br>_Checks if two_ [_**Keplerian**_](classastrea_1_1astro_1_1Keplerian.md) _objects are equal._ |
|  [**void**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) | [**set\_argument\_of\_perigee**](#function-set_argument_of_perigee) ([**const**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) [**Angle**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) & argPerigee) <br>_Get the argument of perigee of the_ [_**Keplerian**_](classastrea_1_1astro_1_1Keplerian.md) _state vector._ |
|  [**void**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) | [**set\_eccentricity**](#function-set_eccentricity) ([**const**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) [**Unitless**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) & eccentricity) <br>_Set the eccentricity of the_ [_**Keplerian**_](classastrea_1_1astro_1_1Keplerian.md) _state vector._ |
|  [**void**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) | [**set\_inclination**](#function-set_inclination) ([**const**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) [**Angle**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) & inclination) <br>_Set the inclination of the_ [_**Keplerian**_](classastrea_1_1astro_1_1Keplerian.md) _state vector._ |
|  [**void**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) | [**set\_right\_ascension**](#function-set_right_ascension) ([**const**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) [**Angle**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) & rightAscension) <br>_Set the right ascension of the ascending node of the_ [_**Keplerian**_](classastrea_1_1astro_1_1Keplerian.md) _state vector._ |
|  [**void**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) | [**set\_semimajor**](#function-set_semimajor) ([**const**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) [**Distance**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) & semimajor) <br>_Set the semimajor axis of the_ [_**Keplerian**_](classastrea_1_1astro_1_1Keplerian.md) _state vector._ |
|  [**void**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) | [**set\_true\_anomaly**](#function-set_true_anomaly) ([**const**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) [**Angle**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) & trueAnomaly) <br>_Get the true anomaly of the_ [_**Keplerian**_](classastrea_1_1astro_1_1Keplerian.md) _state vector._ |
|   | [**~Keplerian**](#function-keplerian) () = default<br>_Destructor for_ [_**Keplerian**_](classastrea_1_1astro_1_1Keplerian.md) _._ |


## Public Static Functions

| Type | Name |
| ---: | :--- |
|  [**Keplerian**](classastrea_1_1astro_1_1Keplerian.md) | [**GEO**](#function-geo) () <br>_A static method to create_ [_**Keplerian**_](classastrea_1_1astro_1_1Keplerian.md) _state vectors for a GEO orbit._ |
|  [**Keplerian**](classastrea_1_1astro_1_1Keplerian.md) | [**GPS**](#function-gps) () <br>_A static method to create_ [_**Keplerian**_](classastrea_1_1astro_1_1Keplerian.md) _state vectors for a GPS orbit._ |
|  [**Keplerian**](classastrea_1_1astro_1_1Keplerian.md) | [**HMEO**](#function-hmeo) () <br>_A static method to create_ [_**Keplerian**_](classastrea_1_1astro_1_1Keplerian.md) _state vectors for a HMEO orbit._ |
|  [**Keplerian**](classastrea_1_1astro_1_1Keplerian.md) | [**LEO**](#function-leo) () <br>_A static method to create_ [_**Keplerian**_](classastrea_1_1astro_1_1Keplerian.md) _state vectors for a LEO orbit._ |
|  [**Keplerian**](classastrea_1_1astro_1_1Keplerian.md) | [**LMEO**](#function-lmeo) () <br>_A static method to create_ [_**Keplerian**_](classastrea_1_1astro_1_1Keplerian.md) _state vectors for a LMEO orbit._ |


























## Detailed Description


The [**Keplerian**](classastrea_1_1astro_1_1Keplerian.md) elements are a set of six parameters that describe the orbit of a celestial body. They include the semimajor axis, eccentricity, inclination, right ascension of the ascending node, argument of perigee, and true anomaly. 


    
## Public Static Attributes Documentation




### variable frame 

_The reference frame of the_ [_**Keplerian**_](classastrea_1_1astro_1_1Keplerian.md) _elements._
```C++
constexpr auto astrea::astro::Keplerian< _frame_ >::frame;
```




<hr>
## Public Functions Documentation




### function Keplerian [1/7]

_Constructs a_ [_**Keplerian**_](classastrea_1_1astro_1_1Keplerian.md) _object with default values._
```C++
inline astrea::astro::Keplerian::Keplerian (
    Unitless scale=0.0 *astrea::detail::unitless
) 
```





**Parameters:**


* `scale` A scaling factor to initialize the elements, typically used for unit conversion. 




        

<hr>



### function Keplerian [2/7]

_Constructs a_ [_**Keplerian**_](classastrea_1_1astro_1_1Keplerian.md) _object with specified values._
```C++
inline astrea::astro::Keplerian::Keplerian (
    const  Distance & semimajor,
    const  Unitless & eccentricity,
    const  Angle & inclination,
    const  Angle & rightAscension,
    const  Angle & argPerigee,
    const  Angle & trueAnomaly
) 
```





**Parameters:**


* `semimajor` The semimajor axis of the orbit. 
* `eccentricity` The eccentricity of the orbit. 
* `inclination` The inclination of the orbit. 
* `rightAscension` The right ascension of the ascending node. 
* `argPerigee` The argument of perigee. 
* `trueAnomaly` The true anomaly of the orbit. 




        

<hr>



### function Keplerian [3/7]

_Constructs a_ [_**Keplerian**_](classastrea_1_1astro_1_1Keplerian.md) _object from another_[_**Keplerian**_](classastrea_1_1astro_1_1Keplerian.md) _object._
```C++
inline astrea::astro::Keplerian::Keplerian (
    const  Keplerian < _frame_ > & elements,
    const  GravParam & mu
) 
```





**Parameters:**


* `elements` The [**Keplerian**](classastrea_1_1astro_1_1Keplerian.md) elements to copy. 
* `sys` The astrodynamics system context for conversion. 




        

<hr>



### function Keplerian [4/7]

_Constructs a_ [_**Keplerian**_](classastrea_1_1astro_1_1Keplerian.md) _object from_[_**Cartesian**_](classastrea_1_1astro_1_1Cartesian.md) _elements._
```C++
astrea::astro::Keplerian::Keplerian (
    const  Cartesian < _frame_ > & elements,
    const  GravParam & mu
) 
```





**Parameters:**


* `elements` The [**Cartesian**](classastrea_1_1astro_1_1Cartesian.md) elements to convert. 
* `sys` The astrodynamics system context for conversion. 




        

<hr>



### function Keplerian [5/7]

_Constructs a_ [_**Keplerian**_](classastrea_1_1astro_1_1Keplerian.md) _object from_[_**Equinoctial**_](classastrea_1_1astro_1_1Equinoctial.md) _elements._
```C++
astrea::astro::Keplerian::Keplerian (
    const  Equinoctial < _frame_ > & elements,
    const  GravParam & mu
) 
```





**Parameters:**


* `elements` The [**Equinoctial**](classastrea_1_1astro_1_1Equinoctial.md) elements to convert. 
* `sys` The astrodynamics system context for conversion. 




        

<hr>



### function Keplerian [6/7]

_Copy constructor for_ [_**Keplerian**_](classastrea_1_1astro_1_1Keplerian.md) _._
```C++
astrea::astro::Keplerian::Keplerian (
    const  Keplerian < _frame_ > & other
) 
```





**Parameters:**


* `other` Another [**Keplerian**](classastrea_1_1astro_1_1Keplerian.md) object 




        

<hr>



### function Keplerian [7/7]

_Move constructor for_ [_**Keplerian**_](classastrea_1_1astro_1_1Keplerian.md) _._
```C++
astrea::astro::Keplerian::Keplerian (
    Keplerian < _frame_ > && other
) noexcept
```





**Parameters:**


* `other` Another [**Keplerian**](classastrea_1_1astro_1_1Keplerian.md) object 




        

<hr>



### function force\_to\_vector 

_Converts the_ [_**Keplerian**_](classastrea_1_1astro_1_1Keplerian.md) _state vector to a vector of unitless values._
```C++
std::vector< Unitless > astrea::astro::Keplerian::force_to_vector () const
```





**Returns:**

std::vector&lt;Unitless&gt; Vector containing the semimajor axis, eccentricity, inclination, right ascension, argument of perigee, and true anomaly components of the [**Keplerian**](classastrea_1_1astro_1_1Keplerian.md) state vector. 





        

<hr>



### function get\_argument\_of\_perigee 

_Get the argument of perigee of the_ [_**Keplerian**_](classastrea_1_1astro_1_1Keplerian.md) _state vector._
```C++
inline const  Angle & astrea::astro::Keplerian::get_argument_of_perigee () const
```





**Returns:**

const Angle& Reference to the argument of perigee component of the [**Keplerian**](classastrea_1_1astro_1_1Keplerian.md) state vector. 





        

<hr>



### function get\_eccentricity 

_Get the eccentricity of the_ [_**Keplerian**_](classastrea_1_1astro_1_1Keplerian.md) _state vector._
```C++
inline const  Unitless & astrea::astro::Keplerian::get_eccentricity () const
```





**Returns:**

const Unitless& Reference to the eccentricity component of the [**Keplerian**](classastrea_1_1astro_1_1Keplerian.md) state vector. 





        

<hr>



### function get\_inclination 

_Get the inclination of the_ [_**Keplerian**_](classastrea_1_1astro_1_1Keplerian.md) _state vector._
```C++
inline const  Angle & astrea::astro::Keplerian::get_inclination () const
```





**Returns:**

const Angle& Reference to the inclination component of the [**Keplerian**](classastrea_1_1astro_1_1Keplerian.md) state vector. 





        

<hr>



### function get\_mean\_anomaly 

_Get the mean anomaly of the_ [_**Keplerian**_](classastrea_1_1astro_1_1Keplerian.md) _state vector._
```C++
Angle astrea::astro::Keplerian::get_mean_anomaly () const
```





**Returns:**

Angle Mean anomaly of the [**Keplerian**](classastrea_1_1astro_1_1Keplerian.md) state vector. 





        

<hr>



### function get\_mean\_motion 

_Get the mean motion of the_ [_**Keplerian**_](classastrea_1_1astro_1_1Keplerian.md) _state vector._
```C++
MeanMotion astrea::astro::Keplerian::get_mean_motion (
    const  GravParam & mu
) const
```





**Parameters:**


* `mu` Gravitational parameter of the central body 



**Returns:**

MeanMotion Mean motion of the [**Keplerian**](classastrea_1_1astro_1_1Keplerian.md) state vector. 





        

<hr>



### function get\_orbital\_period 

_Get the orbital period of the_ [_**Keplerian**_](classastrea_1_1astro_1_1Keplerian.md) _state vector._
```C++
Time astrea::astro::Keplerian::get_orbital_period (
    const  GravParam & mu
) const
```





**Parameters:**


* `mu` Gravitational parameter of the central body 



**Returns:**

Time Orbital period of the [**Keplerian**](classastrea_1_1astro_1_1Keplerian.md) state vector. 





        

<hr>



### function get\_right\_ascension 

_Get the right ascension of the ascending node of the_ [_**Keplerian**_](classastrea_1_1astro_1_1Keplerian.md) _state vector._
```C++
inline const  Angle & astrea::astro::Keplerian::get_right_ascension () const
```





**Returns:**

const Angle& Reference to the right ascension component of the [**Keplerian**](classastrea_1_1astro_1_1Keplerian.md) state vector. 





        

<hr>



### function get\_semimajor 

_Get the semimajor axis of the_ [_**Keplerian**_](classastrea_1_1astro_1_1Keplerian.md) _state vector._
```C++
inline const  Distance & astrea::astro::Keplerian::get_semimajor () const
```





**Returns:**

const Distance& Reference to the semimajor axis component of the [**Keplerian**](classastrea_1_1astro_1_1Keplerian.md) state vector. 





        

<hr>



### function get\_true\_anomaly 

_Get the true anomaly of the_ [_**Keplerian**_](classastrea_1_1astro_1_1Keplerian.md) _state vector._
```C++
inline const  Angle & astrea::astro::Keplerian::get_true_anomaly () const
```





**Returns:**

const Angle& Reference to the true anomaly component of the [**Keplerian**](classastrea_1_1astro_1_1Keplerian.md) state vector. 





        

<hr>



### function in\_frame 

_Converts this_ [_**Keplerian**_](classastrea_1_1astro_1_1Keplerian.md) _state to_[_**Keplerian**_](classastrea_1_1astro_1_1Keplerian.md) _elements expressed in a different frame._
```C++
template<IsFrame auto target_frame>
Keplerian < target_frame > astrea::astro::Keplerian::in_frame (
    const  Date & epoch,
    const  GravParam & mu
) const
```



First converts to [**Cartesian**](classastrea_1_1astro_1_1Cartesian.md) in the native frame, applies the physical frame transformation, then converts the result back to [**Keplerian**](classastrea_1_1astro_1_1Keplerian.md) elements.




**Template parameters:**


* `target_frame` The target frame. 



**Parameters:**


* `epoch` The epoch at which to evaluate the frame transformation. 
* `mu` The gravitational parameter of the central body. 



**Returns:**

Keplerian&lt;target\_frame&gt; This state expressed in the target frame. 





        

<hr>



### function interpolate 

_Interpolates between two_ [_**Keplerian**_](classastrea_1_1astro_1_1Keplerian.md) _state vectors._
```C++
Keplerian astrea::astro::Keplerian::interpolate (
    const  Time & thisTime,
    const  Time & otherTime,
    const  Keplerian < _frame_ > & other,
    const  GravParam & mu,
    const  Time & targetTime
) const
```



This method performs linear interpolation between two [**Keplerian**](classastrea_1_1astro_1_1Keplerian.md) state vectors at a specified target time.




**Parameters:**


* `thisTime` The time of the first [**Keplerian**](classastrea_1_1astro_1_1Keplerian.md) state vector. 
* `otherTime` The time of the second [**Keplerian**](classastrea_1_1astro_1_1Keplerian.md) state vector. 
* `other` The second [**Keplerian**](classastrea_1_1astro_1_1Keplerian.md) state vector to interpolate with. 
* `mu` The gravitational parameter of the central body. 
* `targetTime` The target time for interpolation. 



**Returns:**

[**Keplerian**](classastrea_1_1astro_1_1Keplerian.md) Interpolated [**Keplerian**](classastrea_1_1astro_1_1Keplerian.md) state vector at the target time. 





        

<hr>



### function operator!= 

_Checks if two_ [_**Keplerian**_](classastrea_1_1astro_1_1Keplerian.md) _objects are not equal._
```C++
bool astrea::astro::Keplerian::operator!= (
    const  Keplerian < _frame_ > & other
) const
```





**Parameters:**


* `other` Another [**Keplerian**](classastrea_1_1astro_1_1Keplerian.md) object 



**Returns:**

true if the two [**Keplerian**](classastrea_1_1astro_1_1Keplerian.md) objects are not equal, false otherwise. 





        

<hr>



### function operator\* 

_Multiplies the_ [_**Keplerian**_](classastrea_1_1astro_1_1Keplerian.md) _state vector by a scalar._
```C++
Keplerian astrea::astro::Keplerian::operator* (
    const  Unitless & multiplier
) const
```





**Parameters:**


* `multiplier` Scalar value to multiply with 



**Returns:**

Resultant [**Keplerian**](classastrea_1_1astro_1_1Keplerian.md) after multiplication. 





        

<hr>



### function operator\*= 

_Multiplies the_ [_**Keplerian**_](classastrea_1_1astro_1_1Keplerian.md) _state vector by a scalar._
```C++
Keplerian & astrea::astro::Keplerian::operator*= (
    const  Unitless & multiplier
) 
```





**Parameters:**


* `multiplier` Scalar value to multiply with 



**Returns:**

Reference to the current [**Keplerian**](classastrea_1_1astro_1_1Keplerian.md) object after multiplication. 





        

<hr>



### function operator+ 

_Adds two_ [_**Keplerian**_](classastrea_1_1astro_1_1Keplerian.md) _objects._
```C++
Keplerian astrea::astro::Keplerian::operator+ (
    const  Keplerian < _frame_ > & other
) const
```





**Parameters:**


* `other` Another [**Keplerian**](classastrea_1_1astro_1_1Keplerian.md) object 



**Returns:**

Resultant [**Keplerian**](classastrea_1_1astro_1_1Keplerian.md) sum. 





        

<hr>



### function operator+= 

_Adds another_ [_**Keplerian**_](classastrea_1_1astro_1_1Keplerian.md) _object to the current one._
```C++
Keplerian & astrea::astro::Keplerian::operator+= (
    const  Keplerian < _frame_ > & other
) 
```





**Parameters:**


* `other` Another [**Keplerian**](classastrea_1_1astro_1_1Keplerian.md) object 



**Returns:**

Reference to the current [**Keplerian**](classastrea_1_1astro_1_1Keplerian.md) object after addition. 





        

<hr>



### function operator- 

_Subtracts another_ [_**Keplerian**_](classastrea_1_1astro_1_1Keplerian.md) _object from the current one._
```C++
Keplerian astrea::astro::Keplerian::operator- (
    const  Keplerian < _frame_ > & other
) const
```





**Parameters:**


* `other` Another [**Keplerian**](classastrea_1_1astro_1_1Keplerian.md) object 



**Returns:**

Resultant [**Keplerian**](classastrea_1_1astro_1_1Keplerian.md) after subtraction. 





        

<hr>



### function operator-= 

_Subtracts another_ [_**Keplerian**_](classastrea_1_1astro_1_1Keplerian.md) _object from the current one._
```C++
Keplerian & astrea::astro::Keplerian::operator-= (
    const  Keplerian < _frame_ > & other
) 
```





**Parameters:**


* `other` Another [**Keplerian**](classastrea_1_1astro_1_1Keplerian.md) object 



**Returns:**

Reference to the current [**Keplerian**](classastrea_1_1astro_1_1Keplerian.md) object after subtraction. 





        

<hr>



### function operator/ 

_Divides the_ [_**Keplerian**_](classastrea_1_1astro_1_1Keplerian.md) _state vector by a time._
```C++
KeplerianPartial < _frame_ > astrea::astro::Keplerian::operator/ (
    const  Time & time
) const
```





**Parameters:**


* `time` Time value to divide by 



**Returns:**

Resultant [**KeplerianPartial**](classastrea_1_1astro_1_1KeplerianPartial.md) after division. 





        

<hr>



### function operator/ 

_Divides the_ [_**Keplerian**_](classastrea_1_1astro_1_1Keplerian.md) _state vector by another_[_**Keplerian**_](classastrea_1_1astro_1_1Keplerian.md) _object._
```C++
Keplerian astrea::astro::Keplerian::operator/ (
    const  Unitless & divisor
) const
```





**Parameters:**


* `other` Another [**Keplerian**](classastrea_1_1astro_1_1Keplerian.md) object 



**Returns:**

Resultant vector of unitless values after division. 





        

<hr>



### function operator/= 

_Divides the_ [_**Keplerian**_](classastrea_1_1astro_1_1Keplerian.md) _state vector by a scalar._
```C++
Keplerian & astrea::astro::Keplerian::operator/= (
    const  Unitless & divisor
) 
```





**Parameters:**


* `divisor` Scalar value to divide with 



**Returns:**

Reference to the current [**Keplerian**](classastrea_1_1astro_1_1Keplerian.md) object after division. 





        

<hr>



### function operator= 

_Move assignment operator for_ [_**Keplerian**_](classastrea_1_1astro_1_1Keplerian.md) _._
```C++
Keplerian & astrea::astro::Keplerian::operator= (
    Keplerian < _frame_ > && other
) noexcept
```





**Parameters:**


* `other` Another [**Keplerian**](classastrea_1_1astro_1_1Keplerian.md) object 



**Returns:**

[**Keplerian**](classastrea_1_1astro_1_1Keplerian.md)& Reference to the current object 





        

<hr>



### function operator= 

_Copy assignment operator for_ [_**Keplerian**_](classastrea_1_1astro_1_1Keplerian.md) _._
```C++
Keplerian & astrea::astro::Keplerian::operator= (
    const  Keplerian < _frame_ > & other
) 
```





**Parameters:**


* `other` Another [**Keplerian**](classastrea_1_1astro_1_1Keplerian.md) object 



**Returns:**

[**Keplerian**](classastrea_1_1astro_1_1Keplerian.md)& Reference to the current object 





        

<hr>



### function operator== 

_Checks if two_ [_**Keplerian**_](classastrea_1_1astro_1_1Keplerian.md) _objects are equal._
```C++
bool astrea::astro::Keplerian::operator== (
    const  Keplerian < _frame_ > & other
) const
```





**Parameters:**


* `other` Another [**Keplerian**](classastrea_1_1astro_1_1Keplerian.md) object 



**Returns:**

true if the two [**Keplerian**](classastrea_1_1astro_1_1Keplerian.md) objects are equal, false otherwise. 





        

<hr>



### function set\_argument\_of\_perigee 

_Get the argument of perigee of the_ [_**Keplerian**_](classastrea_1_1astro_1_1Keplerian.md) _state vector._
```C++
inline void astrea::astro::Keplerian::set_argument_of_perigee (
    const  Angle & argPerigee
) 
```




<hr>



### function set\_eccentricity 

_Set the eccentricity of the_ [_**Keplerian**_](classastrea_1_1astro_1_1Keplerian.md) _state vector._
```C++
inline void astrea::astro::Keplerian::set_eccentricity (
    const  Unitless & eccentricity
) 
```




<hr>



### function set\_inclination 

_Set the inclination of the_ [_**Keplerian**_](classastrea_1_1astro_1_1Keplerian.md) _state vector._
```C++
inline void astrea::astro::Keplerian::set_inclination (
    const  Angle & inclination
) 
```




<hr>



### function set\_right\_ascension 

_Set the right ascension of the ascending node of the_ [_**Keplerian**_](classastrea_1_1astro_1_1Keplerian.md) _state vector._
```C++
inline void astrea::astro::Keplerian::set_right_ascension (
    const  Angle & rightAscension
) 
```




<hr>



### function set\_semimajor 

_Set the semimajor axis of the_ [_**Keplerian**_](classastrea_1_1astro_1_1Keplerian.md) _state vector._
```C++
inline void astrea::astro::Keplerian::set_semimajor (
    const  Distance & semimajor
) 
```




<hr>



### function set\_true\_anomaly 

_Get the true anomaly of the_ [_**Keplerian**_](classastrea_1_1astro_1_1Keplerian.md) _state vector._
```C++
inline void astrea::astro::Keplerian::set_true_anomaly (
    const  Angle & trueAnomaly
) 
```




<hr>



### function ~Keplerian 

_Destructor for_ [_**Keplerian**_](classastrea_1_1astro_1_1Keplerian.md) _._
```C++
astrea::astro::Keplerian::~Keplerian () = default
```



Cleans up the [**Keplerian**](classastrea_1_1astro_1_1Keplerian.md) object. 


        

<hr>
## Public Static Functions Documentation




### function GEO 

_A static method to create_ [_**Keplerian**_](classastrea_1_1astro_1_1Keplerian.md) _state vectors for a GEO orbit._
```C++
static Keplerian astrea::astro::Keplerian::GEO () 
```



This method return predefined [**Keplerian**](classastrea_1_1astro_1_1Keplerian.md) state vectors for various types of orbits.




**Parameters:**


* `mu` Gravitational parameter of the central body 



**Returns:**

[**Keplerian**](classastrea_1_1astro_1_1Keplerian.md) Predefined [**Keplerian**](classastrea_1_1astro_1_1Keplerian.md) state vector for a GEO orbit. 





        

<hr>



### function GPS 

_A static method to create_ [_**Keplerian**_](classastrea_1_1astro_1_1Keplerian.md) _state vectors for a GPS orbit._
```C++
static Keplerian astrea::astro::Keplerian::GPS () 
```



This method return predefined [**Keplerian**](classastrea_1_1astro_1_1Keplerian.md) state vectors for various types of orbits.




**Parameters:**


* `mu` Gravitational parameter of the central body 



**Returns:**

[**Keplerian**](classastrea_1_1astro_1_1Keplerian.md) Predefined [**Keplerian**](classastrea_1_1astro_1_1Keplerian.md) state vector for a GPS orbit. 





        

<hr>



### function HMEO 

_A static method to create_ [_**Keplerian**_](classastrea_1_1astro_1_1Keplerian.md) _state vectors for a HMEO orbit._
```C++
static Keplerian astrea::astro::Keplerian::HMEO () 
```



This method return predefined [**Keplerian**](classastrea_1_1astro_1_1Keplerian.md) state vectors for various types of orbits.




**Parameters:**


* `mu` Gravitational parameter of the central body 



**Returns:**

[**Keplerian**](classastrea_1_1astro_1_1Keplerian.md) Predefined [**Keplerian**](classastrea_1_1astro_1_1Keplerian.md) state vector for a HMEO orbit. 





        

<hr>



### function LEO 

_A static method to create_ [_**Keplerian**_](classastrea_1_1astro_1_1Keplerian.md) _state vectors for a LEO orbit._
```C++
static Keplerian astrea::astro::Keplerian::LEO () 
```



This method return predefined [**Keplerian**](classastrea_1_1astro_1_1Keplerian.md) state vectors for various types of orbits.




**Parameters:**


* `mu` Gravitational parameter of the central body 



**Returns:**

[**Keplerian**](classastrea_1_1astro_1_1Keplerian.md) Predefined [**Keplerian**](classastrea_1_1astro_1_1Keplerian.md) state vector for a LEO orbit. 





        

<hr>



### function LMEO 

_A static method to create_ [_**Keplerian**_](classastrea_1_1astro_1_1Keplerian.md) _state vectors for a LMEO orbit._
```C++
static Keplerian astrea::astro::Keplerian::LMEO () 
```



This method return predefined [**Keplerian**](classastrea_1_1astro_1_1Keplerian.md) state vectors for various types of orbits.




**Parameters:**


* `mu` Gravitational parameter of the central body 



**Returns:**

[**Keplerian**](classastrea_1_1astro_1_1Keplerian.md) Predefined [**Keplerian**](classastrea_1_1astro_1_1Keplerian.md) state vector for a LMEO orbit. 





        

<hr>

------------------------------
The documentation for this class was generated from the following file `astrea/astro/astro/state/orbital_elements/Keplerian.hpp`

