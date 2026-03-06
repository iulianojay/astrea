

# Class astrea::astro::Spherical



[**ClassList**](annotated.md) **>** [**astrea**](namespaceastrea.md) **>** [**astro**](namespaceastrea_1_1astro.md) **>** [**Spherical**](classastrea_1_1astro_1_1Spherical.md)



_Class representing a_ [_**Spherical**_](classastrea_1_1astro_1_1Spherical.md) _state vector in astrodynamics._[More...](#detailed-description)

* `#include <Spherical.hpp>`





































## Public Functions

| Type | Name |
| ---: | :--- |
|   | [**Spherical**](#function-spherical-17) ([**Unitless**](classastrea_1_1astro_1_1CartesianVector.md) scale=0.0 \*astrea::detail::unitless) <br>_Default constructor for_ [_**Spherical**_](classastrea_1_1astro_1_1Spherical.md) _._ |
|   | [**Spherical**](#function-spherical-27) ([**const**](classastrea_1_1astro_1_1CartesianVector.md) [**Distance**](classastrea_1_1astro_1_1CartesianVector.md) & range, [**const**](classastrea_1_1astro_1_1CartesianVector.md) [**Angle**](classastrea_1_1astro_1_1CartesianVector.md) & inclination, [**const**](classastrea_1_1astro_1_1CartesianVector.md) [**Angle**](classastrea_1_1astro_1_1CartesianVector.md) & azimuth) <br>_Constructor for_ [_**Spherical**_](classastrea_1_1astro_1_1Spherical.md) _with azimuth, inclination, and range._ |
|   | [**Spherical**](#function-spherical-37) ([**const**](classastrea_1_1astro_1_1CartesianVector.md) [**RadiusVector**](namespaceastrea_1_1astro.md#typedef-radiusvector)&lt; [**frames::earth::icrf**](structastrea_1_1astro_1_1InertialFrame.md) &gt; & r, [**const**](classastrea_1_1astro_1_1CartesianVector.md) [**Date**](classastrea_1_1astro_1_1Date.md) & date, [**const**](classastrea_1_1astro_1_1CartesianVector.md) [**CelestialBody**](classastrea_1_1astro_1_1CelestialBody.md) \* parent) <br>_Constructor for_ [_**Spherical**_](classastrea_1_1astro_1_1Spherical.md) _with position and velocity vectors._ |
|   | [**Spherical**](#function-spherical-47) ([**const**](classastrea_1_1astro_1_1CartesianVector.md) [**RadiusVector**](namespaceastrea_1_1astro.md#typedef-radiusvector)&lt; [**frames::earth::earth\_fixed**](structastrea_1_1astro_1_1BodyFixedFrame.md) &gt; & r, [**const**](classastrea_1_1astro_1_1CartesianVector.md) [**CelestialBody**](classastrea_1_1astro_1_1CelestialBody.md) \* parent) <br>_Constructor for_ [_**Spherical**_](classastrea_1_1astro_1_1Spherical.md) _with position and velocity vectors._ |
|   | [**Spherical**](#function-spherical-57) ([**const**](classastrea_1_1astro_1_1CartesianVector.md) [**T**](classastrea_1_1astro_1_1CartesianVector.md) & elements, [**const**](classastrea_1_1astro_1_1CartesianVector.md) [**AstrodynamicsSystem**](classastrea_1_1astro_1_1AstrodynamicsSystem.md) & sys, [**const**](classastrea_1_1astro_1_1CartesianVector.md) [**Date**](classastrea_1_1astro_1_1Date.md) & date) <br>_Constructor for_ [_**Spherical**_](classastrea_1_1astro_1_1Spherical.md) _from orbital elements._ |
|   | [**Spherical**](#function-spherical-67) ([**const**](classastrea_1_1astro_1_1CartesianVector.md) [**Spherical**](classastrea_1_1astro_1_1Spherical.md) & other) <br>_Copy constructor for_ [_**Spherical**_](classastrea_1_1astro_1_1Spherical.md) _._ |
|   | [**Spherical**](#function-spherical-77) ([**Spherical**](classastrea_1_1astro_1_1Spherical.md) && other) noexcept<br>_Move constructor for_ [_**Spherical**_](classastrea_1_1astro_1_1Spherical.md) _._ |
|  [**const**](classastrea_1_1astro_1_1CartesianVector.md) [**Angle**](classastrea_1_1astro_1_1CartesianVector.md) & | [**get\_azimuth**](#function-get_azimuth) () const<br>_Get the azimuth of the_ [_**Spherical**_](classastrea_1_1astro_1_1Spherical.md) _state vector._ |
|  [**const**](classastrea_1_1astro_1_1CartesianVector.md) [**Angle**](classastrea_1_1astro_1_1CartesianVector.md) & | [**get\_inclination**](#function-get_inclination) () const<br>_Get the inclination of the_ [_**Spherical**_](classastrea_1_1astro_1_1Spherical.md) _state vector._ |
|  [**RadiusVector**](namespaceastrea_1_1astro.md#typedef-radiusvector)&lt; [**frames::earth::earth\_fixed**](structastrea_1_1astro_1_1BodyFixedFrame.md) &gt; | [**get\_position**](#function-get_position-12) ([**const**](classastrea_1_1astro_1_1CartesianVector.md) [**CelestialBody**](classastrea_1_1astro_1_1CelestialBody.md) \* parent) const<br>_Converts the_ [_**Spherical**_](classastrea_1_1astro_1_1Spherical.md) _state vector to a_[_**RadiusVector&lt;frames::earth::earth\_fixed&gt;**_](namespaceastrea_1_1astro.md#typedef-radiusvector) _._ |
|  [**RadiusVector**](namespaceastrea_1_1astro.md#typedef-radiusvector)&lt; [**frames::earth::icrf**](structastrea_1_1astro_1_1InertialFrame.md) &gt; | [**get\_position**](#function-get_position-22) ([**const**](classastrea_1_1astro_1_1CartesianVector.md) [**Date**](classastrea_1_1astro_1_1Date.md) & date, [**const**](classastrea_1_1astro_1_1CartesianVector.md) [**CelestialBody**](classastrea_1_1astro_1_1CelestialBody.md) \* parent) const<br>_Converts the_ [_**Spherical**_](classastrea_1_1astro_1_1Spherical.md) _state vector to a_[_**RadiusVector&lt;frames::earth::icrf&gt;**_](namespaceastrea_1_1astro.md#typedef-radiusvector) _._ |
|  [**const**](classastrea_1_1astro_1_1CartesianVector.md) [**Distance**](classastrea_1_1astro_1_1CartesianVector.md) & | [**get\_range**](#function-get_range) () const<br>_Get the range of the_ [_**Spherical**_](classastrea_1_1astro_1_1Spherical.md) _state vector._ |
|  [**Spherical**](classastrea_1_1astro_1_1Spherical.md) | [**interpolate**](#function-interpolate) ([**const**](classastrea_1_1astro_1_1CartesianVector.md) [**Time**](classastrea_1_1astro_1_1CartesianVector.md) & thisTime, [**const**](classastrea_1_1astro_1_1CartesianVector.md) [**Time**](classastrea_1_1astro_1_1CartesianVector.md) & otherTime, [**const**](classastrea_1_1astro_1_1CartesianVector.md) [**Spherical**](classastrea_1_1astro_1_1Spherical.md) & other, [**const**](classastrea_1_1astro_1_1CartesianVector.md) [**Time**](classastrea_1_1astro_1_1CartesianVector.md) & targetTime) const<br>_Interpolates between two_ [_**Spherical**_](classastrea_1_1astro_1_1Spherical.md) _states at a given time._ |
|  [**bool**](classastrea_1_1astro_1_1CartesianVector.md) | [**operator!=**](#function-operator) ([**const**](classastrea_1_1astro_1_1CartesianVector.md) [**Spherical**](classastrea_1_1astro_1_1Spherical.md) & other) const<br>_Compares two_ [_**Spherical**_](classastrea_1_1astro_1_1Spherical.md) _objects for inequality._ |
|  [**Spherical**](classastrea_1_1astro_1_1Spherical.md) | [**operator\***](#function-operator_1) ([**const**](classastrea_1_1astro_1_1CartesianVector.md) [**Unitless**](classastrea_1_1astro_1_1CartesianVector.md) & multiplier) const<br>_Multiplies the_ [_**Spherical**_](classastrea_1_1astro_1_1Spherical.md) _state vector by a scalar._ |
|  [**Spherical**](classastrea_1_1astro_1_1Spherical.md) & | [**operator\*=**](#function-operator_2) ([**const**](classastrea_1_1astro_1_1CartesianVector.md) [**Unitless**](classastrea_1_1astro_1_1CartesianVector.md) & multiplier) <br>_Multiplies the_ [_**Spherical**_](classastrea_1_1astro_1_1Spherical.md) _state vector by a scalar._ |
|  [**Spherical**](classastrea_1_1astro_1_1Spherical.md) | [**operator+**](#function-operator_3) ([**const**](classastrea_1_1astro_1_1CartesianVector.md) [**Spherical**](classastrea_1_1astro_1_1Spherical.md) & other) const<br>_Adds two_ [_**Spherical**_](classastrea_1_1astro_1_1Spherical.md) _objects._ |
|  [**Spherical**](classastrea_1_1astro_1_1Spherical.md) & | [**operator+=**](#function-operator_4) ([**const**](classastrea_1_1astro_1_1CartesianVector.md) [**Spherical**](classastrea_1_1astro_1_1Spherical.md) & other) <br>_Adds another_ [_**Spherical**_](classastrea_1_1astro_1_1Spherical.md) _object to the current one._ |
|  [**Spherical**](classastrea_1_1astro_1_1Spherical.md) | [**operator-**](#function-operator-) ([**const**](classastrea_1_1astro_1_1CartesianVector.md) [**Spherical**](classastrea_1_1astro_1_1Spherical.md) & other) const<br>_Subtracts another_ [_**Spherical**_](classastrea_1_1astro_1_1Spherical.md) _object from the current one._ |
|  [**Spherical**](classastrea_1_1astro_1_1Spherical.md) & | [**operator-=**](#function-operator-_1) ([**const**](classastrea_1_1astro_1_1CartesianVector.md) [**Spherical**](classastrea_1_1astro_1_1Spherical.md) & other) <br>_Subtracts another_ [_**Spherical**_](classastrea_1_1astro_1_1Spherical.md) _object from the current one._ |
|  std::vector&lt; [**Unitless**](classastrea_1_1astro_1_1CartesianVector.md) &gt; | [**operator/**](#function-operator_5) ([**const**](classastrea_1_1astro_1_1CartesianVector.md) [**Spherical**](classastrea_1_1astro_1_1Spherical.md) & other) const<br>_Divides the_ [_**Spherical**_](classastrea_1_1astro_1_1Spherical.md) _state vector by another_[_**Spherical**_](classastrea_1_1astro_1_1Spherical.md) _object._ |
|  [**Spherical**](classastrea_1_1astro_1_1Spherical.md) | [**operator/**](#function-operator_6) ([**const**](classastrea_1_1astro_1_1CartesianVector.md) [**Unitless**](classastrea_1_1astro_1_1CartesianVector.md) & divisor) const<br>_Divides the_ [_**Spherical**_](classastrea_1_1astro_1_1Spherical.md) _state vector by a scalar._ |
|  [**Spherical**](classastrea_1_1astro_1_1Spherical.md) & | [**operator/=**](#function-operator_7) ([**const**](classastrea_1_1astro_1_1CartesianVector.md) [**Unitless**](classastrea_1_1astro_1_1CartesianVector.md) & divisor) <br>_Divides the_ [_**Spherical**_](classastrea_1_1astro_1_1Spherical.md) _state vector by a scalar._ |
|  [**Spherical**](classastrea_1_1astro_1_1Spherical.md) & | [**operator=**](#function-operator_8) ([**Spherical**](classastrea_1_1astro_1_1Spherical.md) && other) noexcept<br>_Move assignment operator for_ [_**Spherical**_](classastrea_1_1astro_1_1Spherical.md) _._ |
|  [**Spherical**](classastrea_1_1astro_1_1Spherical.md) & | [**operator=**](#function-operator_9) ([**const**](classastrea_1_1astro_1_1CartesianVector.md) [**Spherical**](classastrea_1_1astro_1_1Spherical.md) & other) <br>_Copy assignment operator for_ [_**Spherical**_](classastrea_1_1astro_1_1Spherical.md) _._ |
|  [**bool**](classastrea_1_1astro_1_1CartesianVector.md) | [**operator==**](#function-operator_10) ([**const**](classastrea_1_1astro_1_1CartesianVector.md) [**Spherical**](classastrea_1_1astro_1_1Spherical.md) & other) const<br>_Compares two_ [_**Spherical**_](classastrea_1_1astro_1_1Spherical.md) _objects for equality._ |
|   | [**~Spherical**](#function-spherical) () = default<br>_Default destructor for_ [_**Spherical**_](classastrea_1_1astro_1_1Spherical.md) _._ |




























## Detailed Description


This class encapsulates the position and velocity of a vehicle in [**Spherical**](classastrea_1_1astro_1_1Spherical.md) coordinates. 


    
## Public Functions Documentation




### function Spherical [1/7]

_Default constructor for_ [_**Spherical**_](classastrea_1_1astro_1_1Spherical.md) _._
```C++
inline astrea::astro::Spherical::Spherical (
    Unitless scale=0.0 *astrea::detail::unitless
) 
```



Initializes the [**Spherical**](classastrea_1_1astro_1_1Spherical.md) state vector with zero values. 


        

<hr>



### function Spherical [2/7]

_Constructor for_ [_**Spherical**_](classastrea_1_1astro_1_1Spherical.md) _with azimuth, inclination, and range._
```C++
inline astrea::astro::Spherical::Spherical (
    const  Distance & range,
    const  Angle & inclination,
    const  Angle & azimuth
) 
```





**Parameters:**


* `azimuth` [**Spherical**](classastrea_1_1astro_1_1Spherical.md) azimuth 
* `inclination` Inclination 
* `range` Range 




        

<hr>



### function Spherical [3/7]

_Constructor for_ [_**Spherical**_](classastrea_1_1astro_1_1Spherical.md) _with position and velocity vectors._
```C++
astrea::astro::Spherical::Spherical (
    const  RadiusVector < frames::earth::icrf > & r,
    const  Date & date,
    const  CelestialBody * parent
) 
```





**Parameters:**


* `r` Radius vector in ECI (position) 




        

<hr>



### function Spherical [4/7]

_Constructor for_ [_**Spherical**_](classastrea_1_1astro_1_1Spherical.md) _with position and velocity vectors._
```C++
astrea::astro::Spherical::Spherical (
    const  RadiusVector < frames::earth::earth_fixed > & r,
    const  CelestialBody * parent
) 
```





**Parameters:**


* `r` Radius vector in ECEF (position) 




        

<hr>



### function Spherical [5/7]

_Constructor for_ [_**Spherical**_](classastrea_1_1astro_1_1Spherical.md) _from orbital elements._
```C++
template<IsOrbitalElements T>
inline astrea::astro::Spherical::Spherical (
    const  T & elements,
    const  AstrodynamicsSystem & sys,
    const  Date & date
) 
```





**Parameters:**


* `elements` Orbital elements 
* `sys` Astrodynamics system containing celestial body data 




        

<hr>



### function Spherical [6/7]

_Copy constructor for_ [_**Spherical**_](classastrea_1_1astro_1_1Spherical.md) _._
```C++
astrea::astro::Spherical::Spherical (
    const  Spherical & other
) 
```





**Parameters:**


* `other` Another [**Spherical**](classastrea_1_1astro_1_1Spherical.md) object 




        

<hr>



### function Spherical [7/7]

_Move constructor for_ [_**Spherical**_](classastrea_1_1astro_1_1Spherical.md) _._
```C++
astrea::astro::Spherical::Spherical (
    Spherical && other
) noexcept
```





**Parameters:**


* `other` Another [**Spherical**](classastrea_1_1astro_1_1Spherical.md) object 




        

<hr>



### function get\_azimuth 

_Get the azimuth of the_ [_**Spherical**_](classastrea_1_1astro_1_1Spherical.md) _state vector._
```C++
inline const  Angle & astrea::astro::Spherical::get_azimuth () const
```





**Returns:**

const Angle& Reference to the azimuth component of the [**Spherical**](classastrea_1_1astro_1_1Spherical.md) state vector. 





        

<hr>



### function get\_inclination 

_Get the inclination of the_ [_**Spherical**_](classastrea_1_1astro_1_1Spherical.md) _state vector._
```C++
inline const  Angle & astrea::astro::Spherical::get_inclination () const
```





**Returns:**

const Angle& Reference to the inclination component of the [**Spherical**](classastrea_1_1astro_1_1Spherical.md) state vector. 





        

<hr>



### function get\_position [1/2]

_Converts the_ [_**Spherical**_](classastrea_1_1astro_1_1Spherical.md) _state vector to a_[_**RadiusVector&lt;frames::earth::earth\_fixed&gt;**_](namespaceastrea_1_1astro.md#typedef-radiusvector) _._
```C++
RadiusVector < frames::earth::earth_fixed > astrea::astro::Spherical::get_position (
    const  CelestialBody * parent
) const
```





**Returns:**

[**RadiusVector&lt;frames::earth::earth\_fixed&gt;**](namespaceastrea_1_1astro.md#typedef-radiusvector) The position vector in [**Spherical**](classastrea_1_1astro_1_1Spherical.md) coordinates. 





        

<hr>



### function get\_position [2/2]

_Converts the_ [_**Spherical**_](classastrea_1_1astro_1_1Spherical.md) _state vector to a_[_**RadiusVector&lt;frames::earth::icrf&gt;**_](namespaceastrea_1_1astro.md#typedef-radiusvector) _._
```C++
RadiusVector < frames::earth::icrf > astrea::astro::Spherical::get_position (
    const  Date & date,
    const  CelestialBody * parent
) const
```





**Returns:**

[**RadiusVector&lt;frames::earth::icrf&gt;**](namespaceastrea_1_1astro.md#typedef-radiusvector) The position vector in [**Spherical**](classastrea_1_1astro_1_1Spherical.md) coordinates. 





        

<hr>



### function get\_range 

_Get the range of the_ [_**Spherical**_](classastrea_1_1astro_1_1Spherical.md) _state vector._
```C++
inline const  Distance & astrea::astro::Spherical::get_range () const
```





**Returns:**

const Distance& Reference to the range component of the [**Spherical**](classastrea_1_1astro_1_1Spherical.md) state vector. 





        

<hr>



### function interpolate 

_Interpolates between two_ [_**Spherical**_](classastrea_1_1astro_1_1Spherical.md) _states at a given time._
```C++
Spherical astrea::astro::Spherical::interpolate (
    const  Time & thisTime,
    const  Time & otherTime,
    const  Spherical & other,
    const  Time & targetTime
) const
```





**Parameters:**


* `thisTime` Time of the current state 
* `otherTime` Time of the other state 
* `other` Other [**Spherical**](classastrea_1_1astro_1_1Spherical.md) state to interpolate with 
* `sys` Astrodynamics system containing celestial body data 
* `targetTime` Target time for interpolation 



**Returns:**

[**Spherical**](classastrea_1_1astro_1_1Spherical.md) Interpolated [**Spherical**](classastrea_1_1astro_1_1Spherical.md) state at the target time. 





        

<hr>



### function operator!= 

_Compares two_ [_**Spherical**_](classastrea_1_1astro_1_1Spherical.md) _objects for inequality._
```C++
bool astrea::astro::Spherical::operator!= (
    const  Spherical & other
) const
```





**Parameters:**


* `other` Another [**Spherical**](classastrea_1_1astro_1_1Spherical.md) object 



**Returns:**

true if the two [**Spherical**](classastrea_1_1astro_1_1Spherical.md) objects are not equal 




**Returns:**

false if the two [**Spherical**](classastrea_1_1astro_1_1Spherical.md) objects are equal 





        

<hr>



### function operator\* 

_Multiplies the_ [_**Spherical**_](classastrea_1_1astro_1_1Spherical.md) _state vector by a scalar._
```C++
Spherical astrea::astro::Spherical::operator* (
    const  Unitless & multiplier
) const
```





**Parameters:**


* `multiplier` Scalar value to multiply with 



**Returns:**

Resultant [**Spherical**](classastrea_1_1astro_1_1Spherical.md) after multiplication. 





        

<hr>



### function operator\*= 

_Multiplies the_ [_**Spherical**_](classastrea_1_1astro_1_1Spherical.md) _state vector by a scalar._
```C++
Spherical & astrea::astro::Spherical::operator*= (
    const  Unitless & multiplier
) 
```





**Parameters:**


* `multiplier` Scalar value to multiply with 



**Returns:**

Reference to the current [**Spherical**](classastrea_1_1astro_1_1Spherical.md) object after multiplication. 





        

<hr>



### function operator+ 

_Adds two_ [_**Spherical**_](classastrea_1_1astro_1_1Spherical.md) _objects._
```C++
Spherical astrea::astro::Spherical::operator+ (
    const  Spherical & other
) const
```





**Parameters:**


* `other` Another [**Spherical**](classastrea_1_1astro_1_1Spherical.md) object 



**Returns:**

Resultant [**Spherical**](classastrea_1_1astro_1_1Spherical.md) sum. 





        

<hr>



### function operator+= 

_Adds another_ [_**Spherical**_](classastrea_1_1astro_1_1Spherical.md) _object to the current one._
```C++
Spherical & astrea::astro::Spherical::operator+= (
    const  Spherical & other
) 
```





**Parameters:**


* `other` Another [**Spherical**](classastrea_1_1astro_1_1Spherical.md) object 



**Returns:**

Reference to the current [**Spherical**](classastrea_1_1astro_1_1Spherical.md) object after addition. 





        

<hr>



### function operator- 

_Subtracts another_ [_**Spherical**_](classastrea_1_1astro_1_1Spherical.md) _object from the current one._
```C++
Spherical astrea::astro::Spherical::operator- (
    const  Spherical & other
) const
```





**Parameters:**


* `other` Another [**Spherical**](classastrea_1_1astro_1_1Spherical.md) object 



**Returns:**

Resultant [**Spherical**](classastrea_1_1astro_1_1Spherical.md) difference. 





        

<hr>



### function operator-= 

_Subtracts another_ [_**Spherical**_](classastrea_1_1astro_1_1Spherical.md) _object from the current one._
```C++
Spherical & astrea::astro::Spherical::operator-= (
    const  Spherical & other
) 
```





**Parameters:**


* `other` Another [**Spherical**](classastrea_1_1astro_1_1Spherical.md) object 



**Returns:**

Reference to the current [**Spherical**](classastrea_1_1astro_1_1Spherical.md) object after subtraction. 





        

<hr>



### function operator/ 

_Divides the_ [_**Spherical**_](classastrea_1_1astro_1_1Spherical.md) _state vector by another_[_**Spherical**_](classastrea_1_1astro_1_1Spherical.md) _object._
```C++
std::vector< Unitless > astrea::astro::Spherical::operator/ (
    const  Spherical & other
) const
```





**Parameters:**


* `other` Another [**Spherical**](classastrea_1_1astro_1_1Spherical.md) object 



**Returns:**

Resultant vector of unitless values after division. 





        

<hr>



### function operator/ 

_Divides the_ [_**Spherical**_](classastrea_1_1astro_1_1Spherical.md) _state vector by a scalar._
```C++
Spherical astrea::astro::Spherical::operator/ (
    const  Unitless & divisor
) const
```





**Parameters:**


* `divisor` Scalar value to divide with 



**Returns:**

Resultant [**Spherical**](classastrea_1_1astro_1_1Spherical.md) after division. 





        

<hr>



### function operator/= 

_Divides the_ [_**Spherical**_](classastrea_1_1astro_1_1Spherical.md) _state vector by a scalar._
```C++
Spherical & astrea::astro::Spherical::operator/= (
    const  Unitless & divisor
) 
```





**Parameters:**


* `divisor` Scalar value to divide with 



**Returns:**

Reference to the current [**Spherical**](classastrea_1_1astro_1_1Spherical.md) object after division. 





        

<hr>



### function operator= 

_Move assignment operator for_ [_**Spherical**_](classastrea_1_1astro_1_1Spherical.md) _._
```C++
Spherical & astrea::astro::Spherical::operator= (
    Spherical && other
) noexcept
```





**Parameters:**


* `other` Another [**Spherical**](classastrea_1_1astro_1_1Spherical.md) object 



**Returns:**

[**Spherical**](classastrea_1_1astro_1_1Spherical.md)& Reference to the current object 





        

<hr>



### function operator= 

_Copy assignment operator for_ [_**Spherical**_](classastrea_1_1astro_1_1Spherical.md) _._
```C++
Spherical & astrea::astro::Spherical::operator= (
    const  Spherical & other
) 
```





**Parameters:**


* `other` Another [**Spherical**](classastrea_1_1astro_1_1Spherical.md) object 



**Returns:**

[**Spherical**](classastrea_1_1astro_1_1Spherical.md)& Reference to the current object 





        

<hr>



### function operator== 

_Compares two_ [_**Spherical**_](classastrea_1_1astro_1_1Spherical.md) _objects for equality._
```C++
bool astrea::astro::Spherical::operator== (
    const  Spherical & other
) const
```





**Parameters:**


* `other` Another [**Spherical**](classastrea_1_1astro_1_1Spherical.md) object 



**Returns:**

true if the two [**Spherical**](classastrea_1_1astro_1_1Spherical.md) objects are equal 




**Returns:**

false if the two [**Spherical**](classastrea_1_1astro_1_1Spherical.md) objects are not equal 





        

<hr>



### function ~Spherical 

_Default destructor for_ [_**Spherical**_](classastrea_1_1astro_1_1Spherical.md) _._
```C++
astrea::astro::Spherical::~Spherical () = default
```




<hr>

------------------------------
The documentation for this class was generated from the following file `astrea/astro/astro/state/angular_elements/instances/Spherical.hpp`

