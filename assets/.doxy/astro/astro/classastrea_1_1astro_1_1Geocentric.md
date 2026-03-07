

# Class astrea::astro::Geocentric



[**ClassList**](annotated.md) **>** [**astrea**](namespaceastrea.md) **>** [**astro**](namespaceastrea_1_1astro.md) **>** [**Geocentric**](classastrea_1_1astro_1_1Geocentric.md)



_Class representing a_ [_**Geocentric**_](classastrea_1_1astro_1_1Geocentric.md) _state vector in astrodynamics._[More...](#detailed-description)

* `#include <Geocentric.hpp>`





































## Public Functions

| Type | Name |
| ---: | :--- |
|   | [**Geocentric**](#function-geocentric-17) (Unitless scale=0.0 \*astrea::detail::unitless) <br>_Default constructor for_ [_**Geocentric**_](classastrea_1_1astro_1_1Geocentric.md) _._ |
|   | [**Geocentric**](#function-geocentric-27) (const Angle & latitude, const Angle & longitude, const Distance & altitude) <br>_Constructor for_ [_**Geocentric**_](classastrea_1_1astro_1_1Geocentric.md) _with latitude, longitude, and altitude._ |
|   | [**Geocentric**](#function-geocentric-37) (const [**RadiusVector**](namespaceastrea_1_1astro.md#typedef-radiusvector)&lt; frames::earth::icrf &gt; & r, const [**Date**](classastrea_1_1astro_1_1Date.md) & date, const [**CelestialBody**](classastrea_1_1astro_1_1CelestialBody.md) \* parent) <br>_Constructor for_ [_**Geocentric**_](classastrea_1_1astro_1_1Geocentric.md) _with position and velocity vectors._ |
|   | [**Geocentric**](#function-geocentric-47) (const [**RadiusVector**](namespaceastrea_1_1astro.md#typedef-radiusvector)&lt; frames::earth::earth\_fixed &gt; & r, const [**CelestialBody**](classastrea_1_1astro_1_1CelestialBody.md) \* parent) <br>_Constructor for_ [_**Geocentric**_](classastrea_1_1astro_1_1Geocentric.md) _with position and velocity vectors._ |
|   | [**Geocentric**](#function-geocentric-57) (const T & elements, const [**AstrodynamicsSystem**](classastrea_1_1astro_1_1AstrodynamicsSystem.md) & sys, const [**Date**](classastrea_1_1astro_1_1Date.md) & date) <br>_Constructor for_ [_**Geocentric**_](classastrea_1_1astro_1_1Geocentric.md) _from orbital elements._ |
|   | [**Geocentric**](#function-geocentric-67) (const [**Geocentric**](classastrea_1_1astro_1_1Geocentric.md) & other) <br>_Copy constructor for_ [_**Geocentric**_](classastrea_1_1astro_1_1Geocentric.md) _._ |
|   | [**Geocentric**](#function-geocentric-77) ([**Geocentric**](classastrea_1_1astro_1_1Geocentric.md) && other) noexcept<br>_Move constructor for_ [_**Geocentric**_](classastrea_1_1astro_1_1Geocentric.md) _._ |
|  const Distance & | [**get\_altitude**](#function-get_altitude) () const<br>_Get the altitude of the_ [_**Geocentric**_](classastrea_1_1astro_1_1Geocentric.md) _state vector._ |
|  const Angle & | [**get\_latitude**](#function-get_latitude) () const<br>_Get the latitude of the_ [_**Geocentric**_](classastrea_1_1astro_1_1Geocentric.md) _state vector._ |
|  const Angle & | [**get\_longitude**](#function-get_longitude) () const<br>_Get the longitude of the_ [_**Geocentric**_](classastrea_1_1astro_1_1Geocentric.md) _state vector._ |
|  [**RadiusVector**](namespaceastrea_1_1astro.md#typedef-radiusvector)&lt; frames::earth::earth\_fixed &gt; | [**get\_position**](#function-get_position-12) (const [**CelestialBody**](classastrea_1_1astro_1_1CelestialBody.md) \* parent) const<br>_Converts the_ [_**Geocentric**_](classastrea_1_1astro_1_1Geocentric.md) _state vector to a RadiusVector&lt;frames::earth::earth\_fixed&gt;._ |
|  [**RadiusVector**](namespaceastrea_1_1astro.md#typedef-radiusvector)&lt; frames::earth::icrf &gt; | [**get\_position**](#function-get_position-22) (const [**Date**](classastrea_1_1astro_1_1Date.md) & date, const [**CelestialBody**](classastrea_1_1astro_1_1CelestialBody.md) \* parent) const<br>_Converts the_ [_**Geocentric**_](classastrea_1_1astro_1_1Geocentric.md) _state vector to a RadiusVector&lt;frames::earth::icrf&gt;._ |
|  [**Geocentric**](classastrea_1_1astro_1_1Geocentric.md) | [**interpolate**](#function-interpolate) (const Time & thisTime, const Time & otherTime, const [**Geocentric**](classastrea_1_1astro_1_1Geocentric.md) & other, const Time & targetTime) const<br>_Interpolates between two_ [_**Geocentric**_](classastrea_1_1astro_1_1Geocentric.md) _states at a given time._ |
|  bool | [**operator!=**](#function-operator) (const [**Geocentric**](classastrea_1_1astro_1_1Geocentric.md) & other) const<br>_Compares two_ [_**Geocentric**_](classastrea_1_1astro_1_1Geocentric.md) _objects for inequality._ |
|  [**Geocentric**](classastrea_1_1astro_1_1Geocentric.md) | [**operator\***](#function-operator_1) (const Unitless & multiplier) const<br>_Multiplies the_ [_**Geocentric**_](classastrea_1_1astro_1_1Geocentric.md) _state vector by a scalar._ |
|  [**Geocentric**](classastrea_1_1astro_1_1Geocentric.md) & | [**operator\*=**](#function-operator_2) (const Unitless & multiplier) <br>_Multiplies the_ [_**Geocentric**_](classastrea_1_1astro_1_1Geocentric.md) _state vector by a scalar._ |
|  [**Geocentric**](classastrea_1_1astro_1_1Geocentric.md) | [**operator+**](#function-operator_3) (const [**Geocentric**](classastrea_1_1astro_1_1Geocentric.md) & other) const<br>_Adds two_ [_**Geocentric**_](classastrea_1_1astro_1_1Geocentric.md) _objects._ |
|  [**Geocentric**](classastrea_1_1astro_1_1Geocentric.md) & | [**operator+=**](#function-operator_4) (const [**Geocentric**](classastrea_1_1astro_1_1Geocentric.md) & other) <br>_Adds another_ [_**Geocentric**_](classastrea_1_1astro_1_1Geocentric.md) _object to the current one._ |
|  [**Geocentric**](classastrea_1_1astro_1_1Geocentric.md) | [**operator-**](#function-operator-) (const [**Geocentric**](classastrea_1_1astro_1_1Geocentric.md) & other) const<br>_Subtracts another_ [_**Geocentric**_](classastrea_1_1astro_1_1Geocentric.md) _object from the current one._ |
|  [**Geocentric**](classastrea_1_1astro_1_1Geocentric.md) & | [**operator-=**](#function-operator-_1) (const [**Geocentric**](classastrea_1_1astro_1_1Geocentric.md) & other) <br>_Subtracts another_ [_**Geocentric**_](classastrea_1_1astro_1_1Geocentric.md) _object from the current one._ |
|  std::vector&lt; Unitless &gt; | [**operator/**](#function-operator_5) (const [**Geocentric**](classastrea_1_1astro_1_1Geocentric.md) & other) const<br>_Divides the_ [_**Geocentric**_](classastrea_1_1astro_1_1Geocentric.md) _state vector by another_[_**Geocentric**_](classastrea_1_1astro_1_1Geocentric.md) _object._ |
|  [**Geocentric**](classastrea_1_1astro_1_1Geocentric.md) | [**operator/**](#function-operator_6) (const Unitless & divisor) const<br>_Divides the_ [_**Geocentric**_](classastrea_1_1astro_1_1Geocentric.md) _state vector by a scalar._ |
|  [**Geocentric**](classastrea_1_1astro_1_1Geocentric.md) & | [**operator/=**](#function-operator_7) (const Unitless & divisor) <br>_Divides the_ [_**Geocentric**_](classastrea_1_1astro_1_1Geocentric.md) _state vector by a scalar._ |
|  [**Geocentric**](classastrea_1_1astro_1_1Geocentric.md) & | [**operator=**](#function-operator_8) ([**Geocentric**](classastrea_1_1astro_1_1Geocentric.md) && other) noexcept<br>_Move assignment operator for_ [_**Geocentric**_](classastrea_1_1astro_1_1Geocentric.md) _._ |
|  [**Geocentric**](classastrea_1_1astro_1_1Geocentric.md) & | [**operator=**](#function-operator_9) (const [**Geocentric**](classastrea_1_1astro_1_1Geocentric.md) & other) <br>_Copy assignment operator for_ [_**Geocentric**_](classastrea_1_1astro_1_1Geocentric.md) _._ |
|  bool | [**operator==**](#function-operator_10) (const [**Geocentric**](classastrea_1_1astro_1_1Geocentric.md) & other) const<br>_Compares two_ [_**Geocentric**_](classastrea_1_1astro_1_1Geocentric.md) _objects for equality._ |
|   | [**~Geocentric**](#function-geocentric) () = default<br>_Default destructor for_ [_**Geocentric**_](classastrea_1_1astro_1_1Geocentric.md) _._ |




























## Detailed Description


This class encapsulates the position and velocity of a vehicle in [**Geocentric**](classastrea_1_1astro_1_1Geocentric.md) coordinates. 


    
## Public Functions Documentation




### function Geocentric [1/7]

_Default constructor for_ [_**Geocentric**_](classastrea_1_1astro_1_1Geocentric.md) _._
```C++
inline astrea::astro::Geocentric::Geocentric (
    Unitless scale=0.0 *astrea::detail::unitless
) 
```



Initializes the [**Geocentric**](classastrea_1_1astro_1_1Geocentric.md) state vector with zero values. 


        

<hr>



### function Geocentric [2/7]

_Constructor for_ [_**Geocentric**_](classastrea_1_1astro_1_1Geocentric.md) _with latitude, longitude, and altitude._
```C++
inline astrea::astro::Geocentric::Geocentric (
    const Angle & latitude,
    const Angle & longitude,
    const Distance & altitude
) 
```





**Parameters:**


* `latitude` [**Geocentric**](classastrea_1_1astro_1_1Geocentric.md) latitude 
* `longitude` Longitude 
* `altitude` Altitude 




        

<hr>



### function Geocentric [3/7]

_Constructor for_ [_**Geocentric**_](classastrea_1_1astro_1_1Geocentric.md) _with position and velocity vectors._
```C++
astrea::astro::Geocentric::Geocentric (
    const RadiusVector < frames::earth::icrf > & r,
    const Date & date,
    const CelestialBody * parent
) 
```





**Parameters:**


* `r` Radius vector in ECI (position) 




        

<hr>



### function Geocentric [4/7]

_Constructor for_ [_**Geocentric**_](classastrea_1_1astro_1_1Geocentric.md) _with position and velocity vectors._
```C++
astrea::astro::Geocentric::Geocentric (
    const RadiusVector < frames::earth::earth_fixed > & r,
    const CelestialBody * parent
) 
```





**Parameters:**


* `r` Radius vector in ECEF (position) 




        

<hr>



### function Geocentric [5/7]

_Constructor for_ [_**Geocentric**_](classastrea_1_1astro_1_1Geocentric.md) _from orbital elements._
```C++
template<IsOrbitalElements T>
inline astrea::astro::Geocentric::Geocentric (
    const T & elements,
    const AstrodynamicsSystem & sys,
    const Date & date
) 
```





**Parameters:**


* `elements` Orbital elements 
* `sys` Astrodynamics system containing celestial body data 




        

<hr>



### function Geocentric [6/7]

_Copy constructor for_ [_**Geocentric**_](classastrea_1_1astro_1_1Geocentric.md) _._
```C++
astrea::astro::Geocentric::Geocentric (
    const Geocentric & other
) 
```





**Parameters:**


* `other` Another [**Geocentric**](classastrea_1_1astro_1_1Geocentric.md) object 




        

<hr>



### function Geocentric [7/7]

_Move constructor for_ [_**Geocentric**_](classastrea_1_1astro_1_1Geocentric.md) _._
```C++
astrea::astro::Geocentric::Geocentric (
    Geocentric && other
) noexcept
```





**Parameters:**


* `other` Another [**Geocentric**](classastrea_1_1astro_1_1Geocentric.md) object 




        

<hr>



### function get\_altitude 

_Get the altitude of the_ [_**Geocentric**_](classastrea_1_1astro_1_1Geocentric.md) _state vector._
```C++
inline const Distance & astrea::astro::Geocentric::get_altitude () const
```





**Returns:**

const Distance& Reference to the altitude component of the [**Geocentric**](classastrea_1_1astro_1_1Geocentric.md) state vector. 





        

<hr>



### function get\_latitude 

_Get the latitude of the_ [_**Geocentric**_](classastrea_1_1astro_1_1Geocentric.md) _state vector._
```C++
inline const Angle & astrea::astro::Geocentric::get_latitude () const
```





**Returns:**

const Angle& Reference to the latitude component of the [**Geocentric**](classastrea_1_1astro_1_1Geocentric.md) state vector. 





        

<hr>



### function get\_longitude 

_Get the longitude of the_ [_**Geocentric**_](classastrea_1_1astro_1_1Geocentric.md) _state vector._
```C++
inline const Angle & astrea::astro::Geocentric::get_longitude () const
```





**Returns:**

const Angle& Reference to the longitude component of the [**Geocentric**](classastrea_1_1astro_1_1Geocentric.md) state vector. 





        

<hr>



### function get\_position [1/2]

_Converts the_ [_**Geocentric**_](classastrea_1_1astro_1_1Geocentric.md) _state vector to a RadiusVector&lt;frames::earth::earth\_fixed&gt;._
```C++
RadiusVector < frames::earth::earth_fixed > astrea::astro::Geocentric::get_position (
    const CelestialBody * parent
) const
```





**Returns:**

RadiusVector&lt;frames::earth::earth\_fixed&gt; The position vector in [**Geocentric**](classastrea_1_1astro_1_1Geocentric.md) coordinates. 





        

<hr>



### function get\_position [2/2]

_Converts the_ [_**Geocentric**_](classastrea_1_1astro_1_1Geocentric.md) _state vector to a RadiusVector&lt;frames::earth::icrf&gt;._
```C++
RadiusVector < frames::earth::icrf > astrea::astro::Geocentric::get_position (
    const Date & date,
    const CelestialBody * parent
) const
```





**Returns:**

RadiusVector&lt;frames::earth::icrf&gt; The position vector in [**Geocentric**](classastrea_1_1astro_1_1Geocentric.md) coordinates. 





        

<hr>



### function interpolate 

_Interpolates between two_ [_**Geocentric**_](classastrea_1_1astro_1_1Geocentric.md) _states at a given time._
```C++
Geocentric astrea::astro::Geocentric::interpolate (
    const Time & thisTime,
    const Time & otherTime,
    const Geocentric & other,
    const Time & targetTime
) const
```





**Parameters:**


* `thisTime` Time of the current state 
* `otherTime` Time of the other state 
* `other` Other [**Geocentric**](classastrea_1_1astro_1_1Geocentric.md) state to interpolate with 
* `sys` Astrodynamics system containing celestial body data 
* `targetTime` Target time for interpolation 



**Returns:**

[**Geocentric**](classastrea_1_1astro_1_1Geocentric.md) Interpolated [**Geocentric**](classastrea_1_1astro_1_1Geocentric.md) state at the target time. 





        

<hr>



### function operator!= 

_Compares two_ [_**Geocentric**_](classastrea_1_1astro_1_1Geocentric.md) _objects for inequality._
```C++
bool astrea::astro::Geocentric::operator!= (
    const Geocentric & other
) const
```





**Parameters:**


* `other` Another [**Geocentric**](classastrea_1_1astro_1_1Geocentric.md) object 



**Returns:**

true if the two [**Geocentric**](classastrea_1_1astro_1_1Geocentric.md) objects are not equal 




**Returns:**

false if the two [**Geocentric**](classastrea_1_1astro_1_1Geocentric.md) objects are equal 





        

<hr>



### function operator\* 

_Multiplies the_ [_**Geocentric**_](classastrea_1_1astro_1_1Geocentric.md) _state vector by a scalar._
```C++
Geocentric astrea::astro::Geocentric::operator* (
    const Unitless & multiplier
) const
```





**Parameters:**


* `multiplier` Scalar value to multiply with 



**Returns:**

Resultant [**Geocentric**](classastrea_1_1astro_1_1Geocentric.md) after multiplication. 





        

<hr>



### function operator\*= 

_Multiplies the_ [_**Geocentric**_](classastrea_1_1astro_1_1Geocentric.md) _state vector by a scalar._
```C++
Geocentric & astrea::astro::Geocentric::operator*= (
    const Unitless & multiplier
) 
```





**Parameters:**


* `multiplier` Scalar value to multiply with 



**Returns:**

Reference to the current [**Geocentric**](classastrea_1_1astro_1_1Geocentric.md) object after multiplication. 





        

<hr>



### function operator+ 

_Adds two_ [_**Geocentric**_](classastrea_1_1astro_1_1Geocentric.md) _objects._
```C++
Geocentric astrea::astro::Geocentric::operator+ (
    const Geocentric & other
) const
```





**Parameters:**


* `other` Another [**Geocentric**](classastrea_1_1astro_1_1Geocentric.md) object 



**Returns:**

Resultant [**Geocentric**](classastrea_1_1astro_1_1Geocentric.md) sum. 





        

<hr>



### function operator+= 

_Adds another_ [_**Geocentric**_](classastrea_1_1astro_1_1Geocentric.md) _object to the current one._
```C++
Geocentric & astrea::astro::Geocentric::operator+= (
    const Geocentric & other
) 
```





**Parameters:**


* `other` Another [**Geocentric**](classastrea_1_1astro_1_1Geocentric.md) object 



**Returns:**

Reference to the current [**Geocentric**](classastrea_1_1astro_1_1Geocentric.md) object after addition. 





        

<hr>



### function operator- 

_Subtracts another_ [_**Geocentric**_](classastrea_1_1astro_1_1Geocentric.md) _object from the current one._
```C++
Geocentric astrea::astro::Geocentric::operator- (
    const Geocentric & other
) const
```





**Parameters:**


* `other` Another [**Geocentric**](classastrea_1_1astro_1_1Geocentric.md) object 



**Returns:**

Resultant [**Geocentric**](classastrea_1_1astro_1_1Geocentric.md) difference. 





        

<hr>



### function operator-= 

_Subtracts another_ [_**Geocentric**_](classastrea_1_1astro_1_1Geocentric.md) _object from the current one._
```C++
Geocentric & astrea::astro::Geocentric::operator-= (
    const Geocentric & other
) 
```





**Parameters:**


* `other` Another [**Geocentric**](classastrea_1_1astro_1_1Geocentric.md) object 



**Returns:**

Reference to the current [**Geocentric**](classastrea_1_1astro_1_1Geocentric.md) object after subtraction. 





        

<hr>



### function operator/ 

_Divides the_ [_**Geocentric**_](classastrea_1_1astro_1_1Geocentric.md) _state vector by another_[_**Geocentric**_](classastrea_1_1astro_1_1Geocentric.md) _object._
```C++
std::vector< Unitless > astrea::astro::Geocentric::operator/ (
    const Geocentric & other
) const
```





**Parameters:**


* `other` Another [**Geocentric**](classastrea_1_1astro_1_1Geocentric.md) object 



**Returns:**

Resultant vector of unitless values after division. 





        

<hr>



### function operator/ 

_Divides the_ [_**Geocentric**_](classastrea_1_1astro_1_1Geocentric.md) _state vector by a scalar._
```C++
Geocentric astrea::astro::Geocentric::operator/ (
    const Unitless & divisor
) const
```





**Parameters:**


* `divisor` Scalar value to divide with 



**Returns:**

Resultant [**Geocentric**](classastrea_1_1astro_1_1Geocentric.md) after division. 





        

<hr>



### function operator/= 

_Divides the_ [_**Geocentric**_](classastrea_1_1astro_1_1Geocentric.md) _state vector by a scalar._
```C++
Geocentric & astrea::astro::Geocentric::operator/= (
    const Unitless & divisor
) 
```





**Parameters:**


* `divisor` Scalar value to divide with 



**Returns:**

Reference to the current [**Geocentric**](classastrea_1_1astro_1_1Geocentric.md) object after division. 





        

<hr>



### function operator= 

_Move assignment operator for_ [_**Geocentric**_](classastrea_1_1astro_1_1Geocentric.md) _._
```C++
Geocentric & astrea::astro::Geocentric::operator= (
    Geocentric && other
) noexcept
```





**Parameters:**


* `other` Another [**Geocentric**](classastrea_1_1astro_1_1Geocentric.md) object 



**Returns:**

[**Geocentric**](classastrea_1_1astro_1_1Geocentric.md)& Reference to the current object 





        

<hr>



### function operator= 

_Copy assignment operator for_ [_**Geocentric**_](classastrea_1_1astro_1_1Geocentric.md) _._
```C++
Geocentric & astrea::astro::Geocentric::operator= (
    const Geocentric & other
) 
```





**Parameters:**


* `other` Another [**Geocentric**](classastrea_1_1astro_1_1Geocentric.md) object 



**Returns:**

[**Geocentric**](classastrea_1_1astro_1_1Geocentric.md)& Reference to the current object 





        

<hr>



### function operator== 

_Compares two_ [_**Geocentric**_](classastrea_1_1astro_1_1Geocentric.md) _objects for equality._
```C++
bool astrea::astro::Geocentric::operator== (
    const Geocentric & other
) const
```





**Parameters:**


* `other` Another [**Geocentric**](classastrea_1_1astro_1_1Geocentric.md) object 



**Returns:**

true if the two [**Geocentric**](classastrea_1_1astro_1_1Geocentric.md) objects are equal 




**Returns:**

false if the two [**Geocentric**](classastrea_1_1astro_1_1Geocentric.md) objects are not equal 





        

<hr>



### function ~Geocentric 

_Default destructor for_ [_**Geocentric**_](classastrea_1_1astro_1_1Geocentric.md) _._
```C++
astrea::astro::Geocentric::~Geocentric () = default
```




<hr>

------------------------------
The documentation for this class was generated from the following file `astrea/astro/astro/state/angular_elements/instances/Geocentric.hpp`

