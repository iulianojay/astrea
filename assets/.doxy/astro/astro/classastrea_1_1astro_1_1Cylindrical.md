

# Class astrea::astro::Cylindrical



[**ClassList**](annotated.md) **>** [**astrea**](namespaceastrea.md) **>** [**astro**](namespaceastrea_1_1astro.md) **>** [**Cylindrical**](classastrea_1_1astro_1_1Cylindrical.md)



_Class representing a_ [_**Cylindrical**_](classastrea_1_1astro_1_1Cylindrical.md) _state vector in astrodynamics._[More...](#detailed-description)

* `#include <Cylindrical.hpp>`





































## Public Functions

| Type | Name |
| ---: | :--- |
|   | [**Cylindrical**](#function-cylindrical-17) ([**Unitless**](classastrea_1_1astro_1_1CartesianVector.md) scale=0.0 \*astrea::detail::unitless) <br>_Default constructor for_ [_**Cylindrical**_](classastrea_1_1astro_1_1Cylindrical.md) _._ |
|   | [**Cylindrical**](#function-cylindrical-27) ([**const**](classastrea_1_1astro_1_1CartesianVector.md) [**Distance**](classastrea_1_1astro_1_1CartesianVector.md) & range, [**const**](classastrea_1_1astro_1_1CartesianVector.md) [**Angle**](classastrea_1_1astro_1_1CartesianVector.md) & azimuth, [**const**](classastrea_1_1astro_1_1CartesianVector.md) [**Distance**](classastrea_1_1astro_1_1CartesianVector.md) & elevation) <br>_Constructor for_ [_**Cylindrical**_](classastrea_1_1astro_1_1Cylindrical.md) _with azimuth, elevation, and range._ |
|   | [**Cylindrical**](#function-cylindrical-37) ([**const**](classastrea_1_1astro_1_1CartesianVector.md) [**RadiusVector**](namespaceastrea_1_1astro.md#typedef-radiusvector)&lt; [**frames::earth::icrf**](structastrea_1_1astro_1_1InertialFrame.md) &gt; & r, [**const**](classastrea_1_1astro_1_1CartesianVector.md) [**Date**](classastrea_1_1astro_1_1Date.md) & date, [**const**](classastrea_1_1astro_1_1CartesianVector.md) [**CelestialBody**](classastrea_1_1astro_1_1CelestialBody.md) \* parent) <br>_Constructor for_ [_**Cylindrical**_](classastrea_1_1astro_1_1Cylindrical.md) _with position and velocity vectors._ |
|   | [**Cylindrical**](#function-cylindrical-47) ([**const**](classastrea_1_1astro_1_1CartesianVector.md) [**RadiusVector**](namespaceastrea_1_1astro.md#typedef-radiusvector)&lt; [**frames::earth::earth\_fixed**](structastrea_1_1astro_1_1BodyFixedFrame.md) &gt; & r, [**const**](classastrea_1_1astro_1_1CartesianVector.md) [**CelestialBody**](classastrea_1_1astro_1_1CelestialBody.md) \* parent) <br>_Constructor for_ [_**Cylindrical**_](classastrea_1_1astro_1_1Cylindrical.md) _with position and velocity vectors._ |
|   | [**Cylindrical**](#function-cylindrical-57) ([**const**](classastrea_1_1astro_1_1CartesianVector.md) [**T**](classastrea_1_1astro_1_1CartesianVector.md) & elements, [**const**](classastrea_1_1astro_1_1CartesianVector.md) [**AstrodynamicsSystem**](classastrea_1_1astro_1_1AstrodynamicsSystem.md) & sys, [**const**](classastrea_1_1astro_1_1CartesianVector.md) [**Date**](classastrea_1_1astro_1_1Date.md) & date) <br>_Constructor for_ [_**Cylindrical**_](classastrea_1_1astro_1_1Cylindrical.md) _from orbital elements._ |
|   | [**Cylindrical**](#function-cylindrical-67) ([**const**](classastrea_1_1astro_1_1CartesianVector.md) [**Cylindrical**](classastrea_1_1astro_1_1Cylindrical.md) & other) <br>_Copy constructor for_ [_**Cylindrical**_](classastrea_1_1astro_1_1Cylindrical.md) _._ |
|   | [**Cylindrical**](#function-cylindrical-77) ([**Cylindrical**](classastrea_1_1astro_1_1Cylindrical.md) && other) noexcept<br>_Move constructor for_ [_**Cylindrical**_](classastrea_1_1astro_1_1Cylindrical.md) _._ |
|  [**const**](classastrea_1_1astro_1_1CartesianVector.md) [**Angle**](classastrea_1_1astro_1_1CartesianVector.md) & | [**get\_azimuth**](#function-get_azimuth) () const<br>_Get the azimuth of the_ [_**Cylindrical**_](classastrea_1_1astro_1_1Cylindrical.md) _state vector._ |
|  [**const**](classastrea_1_1astro_1_1CartesianVector.md) [**Distance**](classastrea_1_1astro_1_1CartesianVector.md) & | [**get\_elevation**](#function-get_elevation) () const<br>_Get the elevation of the_ [_**Cylindrical**_](classastrea_1_1astro_1_1Cylindrical.md) _state vector._ |
|  [**RadiusVector**](namespaceastrea_1_1astro.md#typedef-radiusvector)&lt; [**frames::earth::earth\_fixed**](structastrea_1_1astro_1_1BodyFixedFrame.md) &gt; | [**get\_position**](#function-get_position-12) ([**const**](classastrea_1_1astro_1_1CartesianVector.md) [**CelestialBody**](classastrea_1_1astro_1_1CelestialBody.md) \* parent) const<br>_Converts the_ [_**Cylindrical**_](classastrea_1_1astro_1_1Cylindrical.md) _state vector to a_[_**RadiusVector&lt;frames::earth::earth\_fixed&gt;**_](namespaceastrea_1_1astro.md#typedef-radiusvector) _._ |
|  [**RadiusVector**](namespaceastrea_1_1astro.md#typedef-radiusvector)&lt; [**frames::earth::icrf**](structastrea_1_1astro_1_1InertialFrame.md) &gt; | [**get\_position**](#function-get_position-22) ([**const**](classastrea_1_1astro_1_1CartesianVector.md) [**Date**](classastrea_1_1astro_1_1Date.md) & date, [**const**](classastrea_1_1astro_1_1CartesianVector.md) [**CelestialBody**](classastrea_1_1astro_1_1CelestialBody.md) \* parent) const<br>_Converts the_ [_**Cylindrical**_](classastrea_1_1astro_1_1Cylindrical.md) _state vector to a_[_**RadiusVector&lt;frames::earth::icrf&gt;**_](namespaceastrea_1_1astro.md#typedef-radiusvector) _._ |
|  [**const**](classastrea_1_1astro_1_1CartesianVector.md) [**Distance**](classastrea_1_1astro_1_1CartesianVector.md) & | [**get\_range**](#function-get_range) () const<br>_Get the range of the_ [_**Cylindrical**_](classastrea_1_1astro_1_1Cylindrical.md) _state vector._ |
|  [**Cylindrical**](classastrea_1_1astro_1_1Cylindrical.md) | [**interpolate**](#function-interpolate) ([**const**](classastrea_1_1astro_1_1CartesianVector.md) [**Time**](classastrea_1_1astro_1_1CartesianVector.md) & thisTime, [**const**](classastrea_1_1astro_1_1CartesianVector.md) [**Time**](classastrea_1_1astro_1_1CartesianVector.md) & otherTime, [**const**](classastrea_1_1astro_1_1CartesianVector.md) [**Cylindrical**](classastrea_1_1astro_1_1Cylindrical.md) & other, [**const**](classastrea_1_1astro_1_1CartesianVector.md) [**Time**](classastrea_1_1astro_1_1CartesianVector.md) & targetTime) const<br>_Interpolates between two_ [_**Cylindrical**_](classastrea_1_1astro_1_1Cylindrical.md) _states at a given time._ |
|  [**bool**](classastrea_1_1astro_1_1CartesianVector.md) | [**operator!=**](#function-operator) ([**const**](classastrea_1_1astro_1_1CartesianVector.md) [**Cylindrical**](classastrea_1_1astro_1_1Cylindrical.md) & other) const<br>_Compares two_ [_**Cylindrical**_](classastrea_1_1astro_1_1Cylindrical.md) _objects for inequality._ |
|  [**Cylindrical**](classastrea_1_1astro_1_1Cylindrical.md) | [**operator\***](#function-operator_1) ([**const**](classastrea_1_1astro_1_1CartesianVector.md) [**Unitless**](classastrea_1_1astro_1_1CartesianVector.md) & multiplier) const<br>_Multiplies the_ [_**Cylindrical**_](classastrea_1_1astro_1_1Cylindrical.md) _state vector by a scalar._ |
|  [**Cylindrical**](classastrea_1_1astro_1_1Cylindrical.md) & | [**operator\*=**](#function-operator_2) ([**const**](classastrea_1_1astro_1_1CartesianVector.md) [**Unitless**](classastrea_1_1astro_1_1CartesianVector.md) & multiplier) <br>_Multiplies the_ [_**Cylindrical**_](classastrea_1_1astro_1_1Cylindrical.md) _state vector by a scalar._ |
|  [**Cylindrical**](classastrea_1_1astro_1_1Cylindrical.md) | [**operator+**](#function-operator_3) ([**const**](classastrea_1_1astro_1_1CartesianVector.md) [**Cylindrical**](classastrea_1_1astro_1_1Cylindrical.md) & other) const<br>_Adds two_ [_**Cylindrical**_](classastrea_1_1astro_1_1Cylindrical.md) _objects._ |
|  [**Cylindrical**](classastrea_1_1astro_1_1Cylindrical.md) & | [**operator+=**](#function-operator_4) ([**const**](classastrea_1_1astro_1_1CartesianVector.md) [**Cylindrical**](classastrea_1_1astro_1_1Cylindrical.md) & other) <br>_Adds another_ [_**Cylindrical**_](classastrea_1_1astro_1_1Cylindrical.md) _object to the current one._ |
|  [**Cylindrical**](classastrea_1_1astro_1_1Cylindrical.md) | [**operator-**](#function-operator-) ([**const**](classastrea_1_1astro_1_1CartesianVector.md) [**Cylindrical**](classastrea_1_1astro_1_1Cylindrical.md) & other) const<br>_Subtracts another_ [_**Cylindrical**_](classastrea_1_1astro_1_1Cylindrical.md) _object from the current one._ |
|  [**Cylindrical**](classastrea_1_1astro_1_1Cylindrical.md) & | [**operator-=**](#function-operator-_1) ([**const**](classastrea_1_1astro_1_1CartesianVector.md) [**Cylindrical**](classastrea_1_1astro_1_1Cylindrical.md) & other) <br>_Subtracts another_ [_**Cylindrical**_](classastrea_1_1astro_1_1Cylindrical.md) _object from the current one._ |
|  std::vector&lt; [**Unitless**](classastrea_1_1astro_1_1CartesianVector.md) &gt; | [**operator/**](#function-operator_5) ([**const**](classastrea_1_1astro_1_1CartesianVector.md) [**Cylindrical**](classastrea_1_1astro_1_1Cylindrical.md) & other) const<br>_Divides the_ [_**Cylindrical**_](classastrea_1_1astro_1_1Cylindrical.md) _state vector by another_[_**Cylindrical**_](classastrea_1_1astro_1_1Cylindrical.md) _object._ |
|  [**Cylindrical**](classastrea_1_1astro_1_1Cylindrical.md) | [**operator/**](#function-operator_6) ([**const**](classastrea_1_1astro_1_1CartesianVector.md) [**Unitless**](classastrea_1_1astro_1_1CartesianVector.md) & divisor) const<br>_Divides the_ [_**Cylindrical**_](classastrea_1_1astro_1_1Cylindrical.md) _state vector by a scalar._ |
|  [**Cylindrical**](classastrea_1_1astro_1_1Cylindrical.md) & | [**operator/=**](#function-operator_7) ([**const**](classastrea_1_1astro_1_1CartesianVector.md) [**Unitless**](classastrea_1_1astro_1_1CartesianVector.md) & divisor) <br>_Divides the_ [_**Cylindrical**_](classastrea_1_1astro_1_1Cylindrical.md) _state vector by a scalar._ |
|  [**Cylindrical**](classastrea_1_1astro_1_1Cylindrical.md) & | [**operator=**](#function-operator_8) ([**Cylindrical**](classastrea_1_1astro_1_1Cylindrical.md) && other) noexcept<br>_Move assignment operator for_ [_**Cylindrical**_](classastrea_1_1astro_1_1Cylindrical.md) _._ |
|  [**Cylindrical**](classastrea_1_1astro_1_1Cylindrical.md) & | [**operator=**](#function-operator_9) ([**const**](classastrea_1_1astro_1_1CartesianVector.md) [**Cylindrical**](classastrea_1_1astro_1_1Cylindrical.md) & other) <br>_Copy assignment operator for_ [_**Cylindrical**_](classastrea_1_1astro_1_1Cylindrical.md) _._ |
|  [**bool**](classastrea_1_1astro_1_1CartesianVector.md) | [**operator==**](#function-operator_10) ([**const**](classastrea_1_1astro_1_1CartesianVector.md) [**Cylindrical**](classastrea_1_1astro_1_1Cylindrical.md) & other) const<br>_Compares two_ [_**Cylindrical**_](classastrea_1_1astro_1_1Cylindrical.md) _objects for equality._ |
|   | [**~Cylindrical**](#function-cylindrical) () = default<br>_Default destructor for_ [_**Cylindrical**_](classastrea_1_1astro_1_1Cylindrical.md) _._ |




























## Detailed Description


This class encapsulates the position and velocity of a vehicle in [**Cylindrical**](classastrea_1_1astro_1_1Cylindrical.md) coordinates. 


    
## Public Functions Documentation




### function Cylindrical [1/7]

_Default constructor for_ [_**Cylindrical**_](classastrea_1_1astro_1_1Cylindrical.md) _._
```C++
inline astrea::astro::Cylindrical::Cylindrical (
    Unitless scale=0.0 *astrea::detail::unitless
) 
```



Initializes the [**Cylindrical**](classastrea_1_1astro_1_1Cylindrical.md) state vector with zero values. 


        

<hr>



### function Cylindrical [2/7]

_Constructor for_ [_**Cylindrical**_](classastrea_1_1astro_1_1Cylindrical.md) _with azimuth, elevation, and range._
```C++
inline astrea::astro::Cylindrical::Cylindrical (
    const  Distance & range,
    const  Angle & azimuth,
    const  Distance & elevation
) 
```





**Parameters:**


* `azimuth` [**Cylindrical**](classastrea_1_1astro_1_1Cylindrical.md) azimuth 
* `elevation` Elevation 
* `range` Range 




        

<hr>



### function Cylindrical [3/7]

_Constructor for_ [_**Cylindrical**_](classastrea_1_1astro_1_1Cylindrical.md) _with position and velocity vectors._
```C++
astrea::astro::Cylindrical::Cylindrical (
    const  RadiusVector < frames::earth::icrf > & r,
    const  Date & date,
    const  CelestialBody * parent
) 
```





**Parameters:**


* `r` Radius vector in ECI (position) 




        

<hr>



### function Cylindrical [4/7]

_Constructor for_ [_**Cylindrical**_](classastrea_1_1astro_1_1Cylindrical.md) _with position and velocity vectors._
```C++
astrea::astro::Cylindrical::Cylindrical (
    const  RadiusVector < frames::earth::earth_fixed > & r,
    const  CelestialBody * parent
) 
```





**Parameters:**


* `r` Radius vector in ECEF (position) 




        

<hr>



### function Cylindrical [5/7]

_Constructor for_ [_**Cylindrical**_](classastrea_1_1astro_1_1Cylindrical.md) _from orbital elements._
```C++
template<IsOrbitalElements T>
inline astrea::astro::Cylindrical::Cylindrical (
    const  T & elements,
    const  AstrodynamicsSystem & sys,
    const  Date & date
) 
```





**Parameters:**


* `elements` Orbital elements 
* `sys` Astrodynamics system containing celestial body data 




        

<hr>



### function Cylindrical [6/7]

_Copy constructor for_ [_**Cylindrical**_](classastrea_1_1astro_1_1Cylindrical.md) _._
```C++
astrea::astro::Cylindrical::Cylindrical (
    const  Cylindrical & other
) 
```





**Parameters:**


* `other` Another [**Cylindrical**](classastrea_1_1astro_1_1Cylindrical.md) object 




        

<hr>



### function Cylindrical [7/7]

_Move constructor for_ [_**Cylindrical**_](classastrea_1_1astro_1_1Cylindrical.md) _._
```C++
astrea::astro::Cylindrical::Cylindrical (
    Cylindrical && other
) noexcept
```





**Parameters:**


* `other` Another [**Cylindrical**](classastrea_1_1astro_1_1Cylindrical.md) object 




        

<hr>



### function get\_azimuth 

_Get the azimuth of the_ [_**Cylindrical**_](classastrea_1_1astro_1_1Cylindrical.md) _state vector._
```C++
inline const  Angle & astrea::astro::Cylindrical::get_azimuth () const
```





**Returns:**

const Angle& Reference to the azimuth component of the [**Cylindrical**](classastrea_1_1astro_1_1Cylindrical.md) state vector. 





        

<hr>



### function get\_elevation 

_Get the elevation of the_ [_**Cylindrical**_](classastrea_1_1astro_1_1Cylindrical.md) _state vector._
```C++
inline const  Distance & astrea::astro::Cylindrical::get_elevation () const
```





**Returns:**

const Distance& Reference to the elevation component of the [**Cylindrical**](classastrea_1_1astro_1_1Cylindrical.md) state vector. 





        

<hr>



### function get\_position [1/2]

_Converts the_ [_**Cylindrical**_](classastrea_1_1astro_1_1Cylindrical.md) _state vector to a_[_**RadiusVector&lt;frames::earth::earth\_fixed&gt;**_](namespaceastrea_1_1astro.md#typedef-radiusvector) _._
```C++
RadiusVector < frames::earth::earth_fixed > astrea::astro::Cylindrical::get_position (
    const  CelestialBody * parent
) const
```





**Returns:**

[**RadiusVector&lt;frames::earth::earth\_fixed&gt;**](namespaceastrea_1_1astro.md#typedef-radiusvector) The position vector in [**Cylindrical**](classastrea_1_1astro_1_1Cylindrical.md) coordinates. 





        

<hr>



### function get\_position [2/2]

_Converts the_ [_**Cylindrical**_](classastrea_1_1astro_1_1Cylindrical.md) _state vector to a_[_**RadiusVector&lt;frames::earth::icrf&gt;**_](namespaceastrea_1_1astro.md#typedef-radiusvector) _._
```C++
RadiusVector < frames::earth::icrf > astrea::astro::Cylindrical::get_position (
    const  Date & date,
    const  CelestialBody * parent
) const
```





**Returns:**

[**RadiusVector&lt;frames::earth::icrf&gt;**](namespaceastrea_1_1astro.md#typedef-radiusvector) The position vector in [**Cylindrical**](classastrea_1_1astro_1_1Cylindrical.md) coordinates. 





        

<hr>



### function get\_range 

_Get the range of the_ [_**Cylindrical**_](classastrea_1_1astro_1_1Cylindrical.md) _state vector._
```C++
inline const  Distance & astrea::astro::Cylindrical::get_range () const
```





**Returns:**

const Distance& Reference to the range component of the [**Cylindrical**](classastrea_1_1astro_1_1Cylindrical.md) state vector. 





        

<hr>



### function interpolate 

_Interpolates between two_ [_**Cylindrical**_](classastrea_1_1astro_1_1Cylindrical.md) _states at a given time._
```C++
Cylindrical astrea::astro::Cylindrical::interpolate (
    const  Time & thisTime,
    const  Time & otherTime,
    const  Cylindrical & other,
    const  Time & targetTime
) const
```





**Parameters:**


* `thisTime` Time of the current state 
* `otherTime` Time of the other state 
* `other` Other [**Cylindrical**](classastrea_1_1astro_1_1Cylindrical.md) state to interpolate with 
* `sys` Astrodynamics system containing celestial body data 
* `targetTime` Target time for interpolation 



**Returns:**

[**Cylindrical**](classastrea_1_1astro_1_1Cylindrical.md) Interpolated [**Cylindrical**](classastrea_1_1astro_1_1Cylindrical.md) state at the target time. 





        

<hr>



### function operator!= 

_Compares two_ [_**Cylindrical**_](classastrea_1_1astro_1_1Cylindrical.md) _objects for inequality._
```C++
bool astrea::astro::Cylindrical::operator!= (
    const  Cylindrical & other
) const
```





**Parameters:**


* `other` Another [**Cylindrical**](classastrea_1_1astro_1_1Cylindrical.md) object 



**Returns:**

true if the two [**Cylindrical**](classastrea_1_1astro_1_1Cylindrical.md) objects are not equal 




**Returns:**

false if the two [**Cylindrical**](classastrea_1_1astro_1_1Cylindrical.md) objects are equal 





        

<hr>



### function operator\* 

_Multiplies the_ [_**Cylindrical**_](classastrea_1_1astro_1_1Cylindrical.md) _state vector by a scalar._
```C++
Cylindrical astrea::astro::Cylindrical::operator* (
    const  Unitless & multiplier
) const
```





**Parameters:**


* `multiplier` Scalar value to multiply with 



**Returns:**

Resultant [**Cylindrical**](classastrea_1_1astro_1_1Cylindrical.md) after multiplication. 





        

<hr>



### function operator\*= 

_Multiplies the_ [_**Cylindrical**_](classastrea_1_1astro_1_1Cylindrical.md) _state vector by a scalar._
```C++
Cylindrical & astrea::astro::Cylindrical::operator*= (
    const  Unitless & multiplier
) 
```





**Parameters:**


* `multiplier` Scalar value to multiply with 



**Returns:**

Reference to the current [**Cylindrical**](classastrea_1_1astro_1_1Cylindrical.md) object after multiplication. 





        

<hr>



### function operator+ 

_Adds two_ [_**Cylindrical**_](classastrea_1_1astro_1_1Cylindrical.md) _objects._
```C++
Cylindrical astrea::astro::Cylindrical::operator+ (
    const  Cylindrical & other
) const
```





**Parameters:**


* `other` Another [**Cylindrical**](classastrea_1_1astro_1_1Cylindrical.md) object 



**Returns:**

Resultant [**Cylindrical**](classastrea_1_1astro_1_1Cylindrical.md) sum. 





        

<hr>



### function operator+= 

_Adds another_ [_**Cylindrical**_](classastrea_1_1astro_1_1Cylindrical.md) _object to the current one._
```C++
Cylindrical & astrea::astro::Cylindrical::operator+= (
    const  Cylindrical & other
) 
```





**Parameters:**


* `other` Another [**Cylindrical**](classastrea_1_1astro_1_1Cylindrical.md) object 



**Returns:**

Reference to the current [**Cylindrical**](classastrea_1_1astro_1_1Cylindrical.md) object after addition. 





        

<hr>



### function operator- 

_Subtracts another_ [_**Cylindrical**_](classastrea_1_1astro_1_1Cylindrical.md) _object from the current one._
```C++
Cylindrical astrea::astro::Cylindrical::operator- (
    const  Cylindrical & other
) const
```





**Parameters:**


* `other` Another [**Cylindrical**](classastrea_1_1astro_1_1Cylindrical.md) object 



**Returns:**

Resultant [**Cylindrical**](classastrea_1_1astro_1_1Cylindrical.md) difference. 





        

<hr>



### function operator-= 

_Subtracts another_ [_**Cylindrical**_](classastrea_1_1astro_1_1Cylindrical.md) _object from the current one._
```C++
Cylindrical & astrea::astro::Cylindrical::operator-= (
    const  Cylindrical & other
) 
```





**Parameters:**


* `other` Another [**Cylindrical**](classastrea_1_1astro_1_1Cylindrical.md) object 



**Returns:**

Reference to the current [**Cylindrical**](classastrea_1_1astro_1_1Cylindrical.md) object after subtraction. 





        

<hr>



### function operator/ 

_Divides the_ [_**Cylindrical**_](classastrea_1_1astro_1_1Cylindrical.md) _state vector by another_[_**Cylindrical**_](classastrea_1_1astro_1_1Cylindrical.md) _object._
```C++
std::vector< Unitless > astrea::astro::Cylindrical::operator/ (
    const  Cylindrical & other
) const
```





**Parameters:**


* `other` Another [**Cylindrical**](classastrea_1_1astro_1_1Cylindrical.md) object 



**Returns:**

Resultant vector of unitless values after division. 





        

<hr>



### function operator/ 

_Divides the_ [_**Cylindrical**_](classastrea_1_1astro_1_1Cylindrical.md) _state vector by a scalar._
```C++
Cylindrical astrea::astro::Cylindrical::operator/ (
    const  Unitless & divisor
) const
```





**Parameters:**


* `divisor` Scalar value to divide with 



**Returns:**

Resultant [**Cylindrical**](classastrea_1_1astro_1_1Cylindrical.md) after division. 





        

<hr>



### function operator/= 

_Divides the_ [_**Cylindrical**_](classastrea_1_1astro_1_1Cylindrical.md) _state vector by a scalar._
```C++
Cylindrical & astrea::astro::Cylindrical::operator/= (
    const  Unitless & divisor
) 
```





**Parameters:**


* `divisor` Scalar value to divide with 



**Returns:**

Reference to the current [**Cylindrical**](classastrea_1_1astro_1_1Cylindrical.md) object after division. 





        

<hr>



### function operator= 

_Move assignment operator for_ [_**Cylindrical**_](classastrea_1_1astro_1_1Cylindrical.md) _._
```C++
Cylindrical & astrea::astro::Cylindrical::operator= (
    Cylindrical && other
) noexcept
```





**Parameters:**


* `other` Another [**Cylindrical**](classastrea_1_1astro_1_1Cylindrical.md) object 



**Returns:**

[**Cylindrical**](classastrea_1_1astro_1_1Cylindrical.md)& Reference to the current object 





        

<hr>



### function operator= 

_Copy assignment operator for_ [_**Cylindrical**_](classastrea_1_1astro_1_1Cylindrical.md) _._
```C++
Cylindrical & astrea::astro::Cylindrical::operator= (
    const  Cylindrical & other
) 
```





**Parameters:**


* `other` Another [**Cylindrical**](classastrea_1_1astro_1_1Cylindrical.md) object 



**Returns:**

[**Cylindrical**](classastrea_1_1astro_1_1Cylindrical.md)& Reference to the current object 





        

<hr>



### function operator== 

_Compares two_ [_**Cylindrical**_](classastrea_1_1astro_1_1Cylindrical.md) _objects for equality._
```C++
bool astrea::astro::Cylindrical::operator== (
    const  Cylindrical & other
) const
```





**Parameters:**


* `other` Another [**Cylindrical**](classastrea_1_1astro_1_1Cylindrical.md) object 



**Returns:**

true if the two [**Cylindrical**](classastrea_1_1astro_1_1Cylindrical.md) objects are equal 




**Returns:**

false if the two [**Cylindrical**](classastrea_1_1astro_1_1Cylindrical.md) objects are not equal 





        

<hr>



### function ~Cylindrical 

_Default destructor for_ [_**Cylindrical**_](classastrea_1_1astro_1_1Cylindrical.md) _._
```C++
astrea::astro::Cylindrical::~Cylindrical () = default
```




<hr>

------------------------------
The documentation for this class was generated from the following file `astrea/astro/astro/state/angular_elements/instances/Cylindrical.hpp`

