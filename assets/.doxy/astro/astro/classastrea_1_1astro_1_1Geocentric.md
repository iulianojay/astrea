

# Class astrea::astro::Geocentric

**template &lt;IsCelestialBody [**auto**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) \_body\_&gt;**



[**ClassList**](annotated.md) **>** [**astrea**](namespaceastrea.md) **>** [**astro**](namespaceastrea_1_1astro.md) **>** [**Geocentric**](classastrea_1_1astro_1_1Geocentric.md)



_Class representing a_ [_**Geocentric**_](classastrea_1_1astro_1_1Geocentric.md) _state vector in astrodynamics._[More...](#detailed-description)

* `#include <Geocentric.hpp>`























## Public Static Attributes

| Type | Name |
| ---: | :--- |
|  [**constexpr**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) [**auto**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) | [**\_fixed\_frame\_**](#variable-_fixed_frame_)   = `get\_body\_fixed\_frame&lt;[**\_body\_**](classastrea_1_1astro_1_1DirectionCosineMatrix.md)&gt;()`<br>_Body-fixed rotating frame._  |
|  [**constexpr**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) [**auto**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) | [**\_icrf\_frame\_**](#variable-_icrf_frame_)   = `make\_frame([**\_body\_**](classastrea_1_1astro_1_1DirectionCosineMatrix.md), [**axes::icrf**](structastrea_1_1astro_1_1axes_1_1icrf.md))`<br>_Inertial frame for the body._  |
|  [**constexpr**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) [**auto**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) | [**body**](#variable-body)   = `[**\_body\_**](classastrea_1_1astro_1_1DirectionCosineMatrix.md)`<br>_The celestial body of this_ [_**Geocentric**_](classastrea_1_1astro_1_1Geocentric.md) _state._ |














## Public Functions

| Type | Name |
| ---: | :--- |
|   | [**Geocentric**](#function-geocentric-17) ([**Unitless**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) scale=0.0 \*astrea::detail::unitless) <br>_Default constructor for_ [_**Geocentric**_](classastrea_1_1astro_1_1Geocentric.md) _._ |
|   | [**Geocentric**](#function-geocentric-27) ([**const**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) [**Angle**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) & latitude, [**const**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) [**Angle**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) & longitude, [**const**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) [**Distance**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) & altitude) <br>_Constructor for_ [_**Geocentric**_](classastrea_1_1astro_1_1Geocentric.md) _with latitude, longitude, and altitude._ |
|   | [**Geocentric**](#function-geocentric-37) ([**const**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) [**RadiusVector**](namespaceastrea_1_1astro.md#typedef-radiusvector)&lt; \_frame\_ &gt; & r, [**const**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) [**Date**](classastrea_1_1astro_1_1Date.md) & date) <br>_Constructor for_ [_**Geocentric**_](classastrea_1_1astro_1_1Geocentric.md) _from any inertial radius vector centred on the same body._ |
|   | [**Geocentric**](#function-geocentric-47) ([**const**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) [**RadiusVector**](namespaceastrea_1_1astro.md#typedef-radiusvector)&lt; [**\_fixed\_frame\_**](classastrea_1_1astro_1_1Geocentric.md#variable-_fixed_frame_) &gt; & r) <br>_Constructor for_ [_**Geocentric**_](classastrea_1_1astro_1_1Geocentric.md) _from a body-fixed radius vector._ |
|   | [**Geocentric**](#function-geocentric-57) ([**const**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) [**T**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) & elements, [**const**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) [**Date**](classastrea_1_1astro_1_1Date.md) & date) <br>_Constructor for_ [_**Geocentric**_](classastrea_1_1astro_1_1Geocentric.md) _from orbital elements._ |
|   | [**Geocentric**](#function-geocentric-67) ([**const**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) [**Geocentric**](classastrea_1_1astro_1_1Geocentric.md)&lt; [**\_body\_**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) &gt; & other) <br>_Copy constructor for_ [_**Geocentric**_](classastrea_1_1astro_1_1Geocentric.md) _._ |
|   | [**Geocentric**](#function-geocentric-77) ([**Geocentric**](classastrea_1_1astro_1_1Geocentric.md)&lt; [**\_body\_**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) &gt; && other) noexcept<br>_Move constructor for_ [_**Geocentric**_](classastrea_1_1astro_1_1Geocentric.md) _._ |
|  [**const**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) [**Distance**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) & | [**get\_altitude**](#function-get_altitude) () const<br>_Get the altitude of the_ [_**Geocentric**_](classastrea_1_1astro_1_1Geocentric.md) _state vector._ |
|  [**const**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) [**Angle**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) & | [**get\_latitude**](#function-get_latitude) () const<br>_Get the latitude of the_ [_**Geocentric**_](classastrea_1_1astro_1_1Geocentric.md) _state vector._ |
|  [**const**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) [**Angle**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) & | [**get\_longitude**](#function-get_longitude) () const<br>_Get the longitude of the_ [_**Geocentric**_](classastrea_1_1astro_1_1Geocentric.md) _state vector._ |
|  [**RadiusVector**](namespaceastrea_1_1astro.md#typedef-radiusvector)&lt; [**\_fixed\_frame\_**](classastrea_1_1astro_1_1Geocentric.md#variable-_fixed_frame_) &gt; | [**get\_position**](#function-get_position-12) () const<br>_Converts the_ [_**Geocentric**_](classastrea_1_1astro_1_1Geocentric.md) _state vector to a body-fixed radius vector._ |
|  [**RadiusVector**](namespaceastrea_1_1astro.md#typedef-radiusvector)&lt; [**\_icrf\_frame\_**](classastrea_1_1astro_1_1Geocentric.md#variable-_icrf_frame_) &gt; | [**get\_position**](#function-get_position-22) ([**const**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) [**Date**](classastrea_1_1astro_1_1Date.md) & date) const<br>_Converts the_ [_**Geocentric**_](classastrea_1_1astro_1_1Geocentric.md) _state vector to an inertial radius vector._ |
|  [**Geocentric**](classastrea_1_1astro_1_1Geocentric.md)&lt; [**\_body\_**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) &gt; | [**interpolate**](#function-interpolate) ([**const**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) [**Time**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) & thisTime, [**const**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) [**Time**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) & otherTime, [**const**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) [**Geocentric**](classastrea_1_1astro_1_1Geocentric.md)&lt; [**\_body\_**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) &gt; & other, [**const**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) [**Time**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) & targetTime) const<br>_Interpolates between two_ [_**Geocentric**_](classastrea_1_1astro_1_1Geocentric.md) _states at a given time._ |
|  [**bool**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) | [**operator!=**](#function-operator) ([**const**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) [**Geocentric**](classastrea_1_1astro_1_1Geocentric.md)&lt; [**\_body\_**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) &gt; & other) const<br>_Compares two_ [_**Geocentric**_](classastrea_1_1astro_1_1Geocentric.md) _objects for inequality._ |
|  [**Geocentric**](classastrea_1_1astro_1_1Geocentric.md)&lt; [**\_body\_**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) &gt; | [**operator\***](#function-operator_1) ([**const**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) [**Unitless**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) & multiplier) const<br>_Multiplies the_ [_**Geocentric**_](classastrea_1_1astro_1_1Geocentric.md) _state vector by a scalar._ |
|  [**Geocentric**](classastrea_1_1astro_1_1Geocentric.md)&lt; [**\_body\_**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) &gt; & | [**operator\*=**](#function-operator_2) ([**const**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) [**Unitless**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) & multiplier) <br>_Multiplies the_ [_**Geocentric**_](classastrea_1_1astro_1_1Geocentric.md) _state vector by a scalar._ |
|  [**Geocentric**](classastrea_1_1astro_1_1Geocentric.md)&lt; [**\_body\_**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) &gt; | [**operator+**](#function-operator_3) ([**const**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) [**Geocentric**](classastrea_1_1astro_1_1Geocentric.md)&lt; [**\_body\_**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) &gt; & other) const<br>_Adds two_ [_**Geocentric**_](classastrea_1_1astro_1_1Geocentric.md) _objects._ |
|  [**Geocentric**](classastrea_1_1astro_1_1Geocentric.md)&lt; [**\_body\_**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) &gt; & | [**operator+=**](#function-operator_4) ([**const**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) [**Geocentric**](classastrea_1_1astro_1_1Geocentric.md)&lt; [**\_body\_**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) &gt; & other) <br>_Adds another_ [_**Geocentric**_](classastrea_1_1astro_1_1Geocentric.md) _object to the current one._ |
|  [**Geocentric**](classastrea_1_1astro_1_1Geocentric.md)&lt; [**\_body\_**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) &gt; | [**operator-**](#function-operator-) ([**const**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) [**Geocentric**](classastrea_1_1astro_1_1Geocentric.md)&lt; [**\_body\_**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) &gt; & other) const<br>_Subtracts another_ [_**Geocentric**_](classastrea_1_1astro_1_1Geocentric.md) _object from the current one._ |
|  [**Geocentric**](classastrea_1_1astro_1_1Geocentric.md)&lt; [**\_body\_**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) &gt; & | [**operator-=**](#function-operator-_1) ([**const**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) [**Geocentric**](classastrea_1_1astro_1_1Geocentric.md)&lt; [**\_body\_**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) &gt; & other) <br>_Subtracts another_ [_**Geocentric**_](classastrea_1_1astro_1_1Geocentric.md) _object from the current one._ |
|  std::vector&lt; [**Unitless**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) &gt; | [**operator/**](#function-operator_5) ([**const**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) [**Geocentric**](classastrea_1_1astro_1_1Geocentric.md)&lt; [**\_body\_**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) &gt; & other) const<br>_Divides the_ [_**Geocentric**_](classastrea_1_1astro_1_1Geocentric.md) _state vector by another_[_**Geocentric**_](classastrea_1_1astro_1_1Geocentric.md) _object._ |
|  [**Geocentric**](classastrea_1_1astro_1_1Geocentric.md)&lt; [**\_body\_**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) &gt; | [**operator/**](#function-operator_6) ([**const**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) [**Unitless**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) & divisor) const<br>_Divides the_ [_**Geocentric**_](classastrea_1_1astro_1_1Geocentric.md) _state vector by a scalar._ |
|  [**Geocentric**](classastrea_1_1astro_1_1Geocentric.md)&lt; [**\_body\_**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) &gt; & | [**operator/=**](#function-operator_7) ([**const**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) [**Unitless**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) & divisor) <br>_Divides the_ [_**Geocentric**_](classastrea_1_1astro_1_1Geocentric.md) _state vector by a scalar._ |
|  [**Geocentric**](classastrea_1_1astro_1_1Geocentric.md)&lt; [**\_body\_**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) &gt; & | [**operator=**](#function-operator_8) ([**Geocentric**](classastrea_1_1astro_1_1Geocentric.md)&lt; [**\_body\_**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) &gt; && other) noexcept<br>_Move assignment operator for_ [_**Geocentric**_](classastrea_1_1astro_1_1Geocentric.md) _._ |
|  [**Geocentric**](classastrea_1_1astro_1_1Geocentric.md)&lt; [**\_body\_**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) &gt; & | [**operator=**](#function-operator_9) ([**const**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) [**Geocentric**](classastrea_1_1astro_1_1Geocentric.md)&lt; [**\_body\_**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) &gt; & other) <br>_Copy assignment operator for_ [_**Geocentric**_](classastrea_1_1astro_1_1Geocentric.md) _._ |
|  [**bool**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) | [**operator==**](#function-operator_10) ([**const**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) [**Geocentric**](classastrea_1_1astro_1_1Geocentric.md)&lt; [**\_body\_**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) &gt; & other) const<br>_Compares two_ [_**Geocentric**_](classastrea_1_1astro_1_1Geocentric.md) _objects for equality._ |
|   | [**~Geocentric**](#function-geocentric) () = default<br>_Default destructor for_ [_**Geocentric**_](classastrea_1_1astro_1_1Geocentric.md) _._ |




























## Detailed Description


This class encapsulates the position and velocity of a vehicle in [**Geocentric**](classastrea_1_1astro_1_1Geocentric.md) coordinates.




**Template parameters:**


* `_body_` The celestial body NTTP that defines the reference ellipsoid and frames. 




    
## Public Static Attributes Documentation




### variable \_fixed\_frame\_ 

_Body-fixed rotating frame._ 
```C++
constexpr auto astrea::astro::Geocentric< _body_ >::_fixed_frame_;
```




<hr>



### variable \_icrf\_frame\_ 

_Inertial frame for the body._ 
```C++
constexpr auto astrea::astro::Geocentric< _body_ >::_icrf_frame_;
```




<hr>



### variable body 

_The celestial body of this_ [_**Geocentric**_](classastrea_1_1astro_1_1Geocentric.md) _state._
```C++
constexpr auto astrea::astro::Geocentric< _body_ >::body;
```




<hr>
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
    const  Angle & latitude,
    const  Angle & longitude,
    const  Distance & altitude
) 
```





**Parameters:**


* `latitude` [**Geocentric**](classastrea_1_1astro_1_1Geocentric.md) latitude 
* `longitude` Longitude 
* `altitude` Altitude 




        

<hr>



### function Geocentric [3/7]

_Constructor for_ [_**Geocentric**_](classastrea_1_1astro_1_1Geocentric.md) _from any inertial radius vector centred on the same body._
```C++
template<auto _frame_>
astrea::astro::Geocentric::Geocentric (
    const  RadiusVector < _frame_ > & r,
    const  Date & date
) 
```



Accepts any frame whose origin matches _body_ and whose axis is the ICRF axis.




**Template parameters:**


* `_frame_` The inertial frame of the radius vector. 



**Parameters:**


* `r` Radius vector in an ICRF-axis frame centred on the body. 
* `date` [**Date**](classastrea_1_1astro_1_1Date.md) for the frame transformation. 




        

<hr>



### function Geocentric [4/7]

_Constructor for_ [_**Geocentric**_](classastrea_1_1astro_1_1Geocentric.md) _from a body-fixed radius vector._
```C++
astrea::astro::Geocentric::Geocentric (
    const  RadiusVector < _fixed_frame_ > & r
) 
```





**Parameters:**


* `r` Radius vector in the body-fixed frame (position) 




        

<hr>



### function Geocentric [5/7]

_Constructor for_ [_**Geocentric**_](classastrea_1_1astro_1_1Geocentric.md) _from orbital elements._
```C++
template<IsOrbitalElements T>
inline astrea::astro::Geocentric::Geocentric (
    const  T & elements,
    const  Date & date
) 
```





**Parameters:**


* `elements` Orbital elements 
* `date` [**Date**](classastrea_1_1astro_1_1Date.md) for the frame transformation 




        

<hr>



### function Geocentric [6/7]

_Copy constructor for_ [_**Geocentric**_](classastrea_1_1astro_1_1Geocentric.md) _._
```C++
astrea::astro::Geocentric::Geocentric (
    const  Geocentric < _body_ > & other
) 
```





**Parameters:**


* `other` Another [**Geocentric**](classastrea_1_1astro_1_1Geocentric.md) object 




        

<hr>



### function Geocentric [7/7]

_Move constructor for_ [_**Geocentric**_](classastrea_1_1astro_1_1Geocentric.md) _._
```C++
astrea::astro::Geocentric::Geocentric (
    Geocentric < _body_ > && other
) noexcept
```





**Parameters:**


* `other` Another [**Geocentric**](classastrea_1_1astro_1_1Geocentric.md) object 




        

<hr>



### function get\_altitude 

_Get the altitude of the_ [_**Geocentric**_](classastrea_1_1astro_1_1Geocentric.md) _state vector._
```C++
inline const  Distance & astrea::astro::Geocentric::get_altitude () const
```





**Returns:**

const Distance& Reference to the altitude component of the [**Geocentric**](classastrea_1_1astro_1_1Geocentric.md) state vector. 





        

<hr>



### function get\_latitude 

_Get the latitude of the_ [_**Geocentric**_](classastrea_1_1astro_1_1Geocentric.md) _state vector._
```C++
inline const  Angle & astrea::astro::Geocentric::get_latitude () const
```





**Returns:**

const Angle& Reference to the latitude component of the [**Geocentric**](classastrea_1_1astro_1_1Geocentric.md) state vector. 





        

<hr>



### function get\_longitude 

_Get the longitude of the_ [_**Geocentric**_](classastrea_1_1astro_1_1Geocentric.md) _state vector._
```C++
inline const  Angle & astrea::astro::Geocentric::get_longitude () const
```





**Returns:**

const Angle& Reference to the longitude component of the [**Geocentric**](classastrea_1_1astro_1_1Geocentric.md) state vector. 





        

<hr>



### function get\_position [1/2]

_Converts the_ [_**Geocentric**_](classastrea_1_1astro_1_1Geocentric.md) _state vector to a body-fixed radius vector._
```C++
RadiusVector < _fixed_frame_ > astrea::astro::Geocentric::get_position () const
```





**Returns:**

RadiusVector in the body-fixed frame. 





        

<hr>



### function get\_position [2/2]

_Converts the_ [_**Geocentric**_](classastrea_1_1astro_1_1Geocentric.md) _state vector to an inertial radius vector._
```C++
RadiusVector < _icrf_frame_ > astrea::astro::Geocentric::get_position (
    const  Date & date
) const
```





**Parameters:**


* `date` [**Date**](classastrea_1_1astro_1_1Date.md) for the frame transformation 



**Returns:**

RadiusVector in the body's inertial frame. 





        

<hr>



### function interpolate 

_Interpolates between two_ [_**Geocentric**_](classastrea_1_1astro_1_1Geocentric.md) _states at a given time._
```C++
Geocentric < _body_ > astrea::astro::Geocentric::interpolate (
    const  Time & thisTime,
    const  Time & otherTime,
    const  Geocentric < _body_ > & other,
    const  Time & targetTime
) const
```





**Parameters:**


* `thisTime` Time of the current state 
* `otherTime` Time of the other state 
* `other` Other [**Geocentric**](classastrea_1_1astro_1_1Geocentric.md) state to interpolate with 
* `targetTime` Target time for interpolation 



**Returns:**

[**Geocentric**](classastrea_1_1astro_1_1Geocentric.md) Interpolated [**Geocentric**](classastrea_1_1astro_1_1Geocentric.md) state at the target time. 





        

<hr>



### function operator!= 

_Compares two_ [_**Geocentric**_](classastrea_1_1astro_1_1Geocentric.md) _objects for inequality._
```C++
bool astrea::astro::Geocentric::operator!= (
    const  Geocentric < _body_ > & other
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
Geocentric < _body_ > astrea::astro::Geocentric::operator* (
    const  Unitless & multiplier
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
Geocentric < _body_ > & astrea::astro::Geocentric::operator*= (
    const  Unitless & multiplier
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
Geocentric < _body_ > astrea::astro::Geocentric::operator+ (
    const  Geocentric < _body_ > & other
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
Geocentric < _body_ > & astrea::astro::Geocentric::operator+= (
    const  Geocentric < _body_ > & other
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
Geocentric < _body_ > astrea::astro::Geocentric::operator- (
    const  Geocentric < _body_ > & other
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
Geocentric < _body_ > & astrea::astro::Geocentric::operator-= (
    const  Geocentric < _body_ > & other
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
    const  Geocentric < _body_ > & other
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
Geocentric < _body_ > astrea::astro::Geocentric::operator/ (
    const  Unitless & divisor
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
Geocentric < _body_ > & astrea::astro::Geocentric::operator/= (
    const  Unitless & divisor
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
Geocentric < _body_ > & astrea::astro::Geocentric::operator= (
    Geocentric < _body_ > && other
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
Geocentric < _body_ > & astrea::astro::Geocentric::operator= (
    const  Geocentric < _body_ > & other
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
    const  Geocentric < _body_ > & other
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
The documentation for this class was generated from the following file `astrea/astro/astro/state/angular_elements/Geocentric.hpp`

