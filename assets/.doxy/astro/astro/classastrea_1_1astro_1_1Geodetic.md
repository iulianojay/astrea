

# Class astrea::astro::Geodetic

**template &lt;IsCelestialBody auto \_body\_&gt;**



[**ClassList**](annotated.md) **>** [**astrea**](namespaceastrea.md) **>** [**astro**](namespaceastrea_1_1astro.md) **>** [**Geodetic**](classastrea_1_1astro_1_1Geodetic.md)



_Class representing a_ [_**Geodetic**_](classastrea_1_1astro_1_1Geodetic.md) _state vector in astrodynamics._[More...](#detailed-description)

* `#include <Geodetic.hpp>`























## Public Static Attributes

| Type | Name |
| ---: | :--- |
|  constexpr auto | [**\_fixed\_frame\_**](#variable-_fixed_frame_)   = `get\_body\_fixed\_frame&lt;\_body\_&gt;()`<br>_Body-fixed rotating frame._  |
|  constexpr auto | [**\_icrf\_frame\_**](#variable-_icrf_frame_)   = `make\_frame(\_body\_, [**axes::icrf**](structastrea_1_1astro_1_1axes_1_1icrf.md))`<br>_Inertial frame for the body._  |
|  constexpr auto | [**body**](#variable-body)   = `\_body\_`<br>_The celestial body of this_ [_**Geodetic**_](classastrea_1_1astro_1_1Geodetic.md) _state._ |














## Public Functions

| Type | Name |
| ---: | :--- |
|   | [**Geodetic**](#function-geodetic-17) (Unitless scale=0.0 \*astrea::detail::unitless) <br>_Default constructor for_ [_**Geodetic**_](classastrea_1_1astro_1_1Geodetic.md) _._ |
|   | [**Geodetic**](#function-geodetic-27) (const Angle & latitude, const Angle & longitude, const Distance & altitude) <br>_Constructor for_ [_**Geodetic**_](classastrea_1_1astro_1_1Geodetic.md) _with latitude, longitude, and altitude._ |
|   | [**Geodetic**](#function-geodetic-37) (const [**RadiusVector**](namespaceastrea_1_1astro.md#typedef-radiusvector)&lt; \_frame\_ &gt; & r, const [**Date**](classastrea_1_1astro_1_1Date.md) & date) <br>_Constructor for_ [_**Geodetic**_](classastrea_1_1astro_1_1Geodetic.md) _from a radius vector in any inertial frame centred on the same body._ |
|   | [**Geodetic**](#function-geodetic-47) (const [**RadiusVector**](namespaceastrea_1_1astro.md#typedef-radiusvector)&lt; [**\_fixed\_frame\_**](classastrea_1_1astro_1_1Geodetic.md#variable-_fixed_frame_) &gt; & r) <br>_Constructor for_ [_**Geodetic**_](classastrea_1_1astro_1_1Geodetic.md) _from a radius vector in the body-fixed frame._ |
|   | [**Geodetic**](#function-geodetic-57) (const T & elements, const [**Date**](classastrea_1_1astro_1_1Date.md) & date) <br>_Constructor for_ [_**Geodetic**_](classastrea_1_1astro_1_1Geodetic.md) _from orbital elements._ |
|   | [**Geodetic**](#function-geodetic-67) (const [**Geodetic**](classastrea_1_1astro_1_1Geodetic.md)&lt; \_body\_ &gt; & other) <br>_Copy constructor for_ [_**Geodetic**_](classastrea_1_1astro_1_1Geodetic.md) _._ |
|   | [**Geodetic**](#function-geodetic-77) ([**Geodetic**](classastrea_1_1astro_1_1Geodetic.md)&lt; \_body\_ &gt; && other) noexcept<br>_Move constructor for_ [_**Geodetic**_](classastrea_1_1astro_1_1Geodetic.md) _._ |
|  const Distance & | [**get\_altitude**](#function-get_altitude) () const<br>_Get the altitude of the_ [_**Geodetic**_](classastrea_1_1astro_1_1Geodetic.md) _state vector._ |
|  const Angle & | [**get\_latitude**](#function-get_latitude) () const<br>_Get the latitude of the_ [_**Geodetic**_](classastrea_1_1astro_1_1Geodetic.md) _state vector._ |
|  const Angle & | [**get\_longitude**](#function-get_longitude) () const<br>_Get the longitude of the_ [_**Geodetic**_](classastrea_1_1astro_1_1Geodetic.md) _state vector._ |
|  [**RadiusVector**](namespaceastrea_1_1astro.md#typedef-radiusvector)&lt; [**\_fixed\_frame\_**](classastrea_1_1astro_1_1Geodetic.md#variable-_fixed_frame_) &gt; | [**get\_position**](#function-get_position-12) () const<br>_Converts the_ [_**Geodetic**_](classastrea_1_1astro_1_1Geodetic.md) _state vector to a position in the body-fixed frame._ |
|  [**RadiusVector**](namespaceastrea_1_1astro.md#typedef-radiusvector)&lt; [**\_icrf\_frame\_**](classastrea_1_1astro_1_1Geodetic.md#variable-_icrf_frame_) &gt; | [**get\_position**](#function-get_position-22) (const [**Date**](classastrea_1_1astro_1_1Date.md) & date) const<br>_Converts the_ [_**Geodetic**_](classastrea_1_1astro_1_1Geodetic.md) _state vector to a position in the body's inertial frame._ |
|  [**Geodetic**](classastrea_1_1astro_1_1Geodetic.md) | [**interpolate**](#function-interpolate) (const Time & thisTime, const Time & otherTime, const [**Geodetic**](classastrea_1_1astro_1_1Geodetic.md)&lt; \_body\_ &gt; & other, const Time & targetTime) const<br>_Interpolates between two_ [_**Geodetic**_](classastrea_1_1astro_1_1Geodetic.md) _states at a given time._ |
|  bool | [**operator!=**](#function-operator) (const [**Geodetic**](classastrea_1_1astro_1_1Geodetic.md)&lt; \_body\_ &gt; & other) const<br>_Compares two_ [_**Geodetic**_](classastrea_1_1astro_1_1Geodetic.md) _objects for inequality._ |
|  [**Geodetic**](classastrea_1_1astro_1_1Geodetic.md) | [**operator\***](#function-operator_1) (const Unitless & multiplier) const<br>_Multiplies the_ [_**Geodetic**_](classastrea_1_1astro_1_1Geodetic.md) _state vector by a scalar._ |
|  [**Geodetic**](classastrea_1_1astro_1_1Geodetic.md) & | [**operator\*=**](#function-operator_2) (const Unitless & multiplier) <br>_Multiplies the_ [_**Geodetic**_](classastrea_1_1astro_1_1Geodetic.md) _state vector by a scalar._ |
|  [**Geodetic**](classastrea_1_1astro_1_1Geodetic.md) | [**operator+**](#function-operator_3) (const [**Geodetic**](classastrea_1_1astro_1_1Geodetic.md)&lt; \_body\_ &gt; & other) const<br>_Adds two_ [_**Geodetic**_](classastrea_1_1astro_1_1Geodetic.md) _objects._ |
|  [**Geodetic**](classastrea_1_1astro_1_1Geodetic.md) & | [**operator+=**](#function-operator_4) (const [**Geodetic**](classastrea_1_1astro_1_1Geodetic.md)&lt; \_body\_ &gt; & other) <br>_Adds another_ [_**Geodetic**_](classastrea_1_1astro_1_1Geodetic.md) _object to the current one._ |
|  [**Geodetic**](classastrea_1_1astro_1_1Geodetic.md) | [**operator-**](#function-operator-) (const [**Geodetic**](classastrea_1_1astro_1_1Geodetic.md)&lt; \_body\_ &gt; & other) const<br>_Subtracts another_ [_**Geodetic**_](classastrea_1_1astro_1_1Geodetic.md) _object from the current one._ |
|  [**Geodetic**](classastrea_1_1astro_1_1Geodetic.md) & | [**operator-=**](#function-operator-_1) (const [**Geodetic**](classastrea_1_1astro_1_1Geodetic.md)&lt; \_body\_ &gt; & other) <br>_Subtracts another_ [_**Geodetic**_](classastrea_1_1astro_1_1Geodetic.md) _object from the current one._ |
|  std::vector&lt; Unitless &gt; | [**operator/**](#function-operator_5) (const [**Geodetic**](classastrea_1_1astro_1_1Geodetic.md)&lt; \_body\_ &gt; & other) const<br>_Divides the_ [_**Geodetic**_](classastrea_1_1astro_1_1Geodetic.md) _state vector by another_[_**Geodetic**_](classastrea_1_1astro_1_1Geodetic.md) _object._ |
|  [**Geodetic**](classastrea_1_1astro_1_1Geodetic.md) | [**operator/**](#function-operator_6) (const Unitless & divisor) const<br>_Divides the_ [_**Geodetic**_](classastrea_1_1astro_1_1Geodetic.md) _state vector by a scalar._ |
|  [**Geodetic**](classastrea_1_1astro_1_1Geodetic.md) & | [**operator/=**](#function-operator_7) (const Unitless & divisor) <br>_Divides the_ [_**Geodetic**_](classastrea_1_1astro_1_1Geodetic.md) _state vector by a scalar._ |
|  [**Geodetic**](classastrea_1_1astro_1_1Geodetic.md) & | [**operator=**](#function-operator_8) ([**Geodetic**](classastrea_1_1astro_1_1Geodetic.md)&lt; \_body\_ &gt; && other) noexcept<br>_Move assignment operator for_ [_**Geodetic**_](classastrea_1_1astro_1_1Geodetic.md) _._ |
|  [**Geodetic**](classastrea_1_1astro_1_1Geodetic.md) & | [**operator=**](#function-operator_9) (const [**Geodetic**](classastrea_1_1astro_1_1Geodetic.md)&lt; \_body\_ &gt; & other) <br>_Copy assignment operator for_ [_**Geodetic**_](classastrea_1_1astro_1_1Geodetic.md) _._ |
|  bool | [**operator==**](#function-operator_10) (const [**Geodetic**](classastrea_1_1astro_1_1Geodetic.md)&lt; \_body\_ &gt; & other) const<br>_Compares two_ [_**Geodetic**_](classastrea_1_1astro_1_1Geodetic.md) _objects for equality._ |
|   | [**~Geodetic**](#function-geodetic) () = default<br>_Default destructor for_ [_**Geodetic**_](classastrea_1_1astro_1_1Geodetic.md) _._ |




























## Detailed Description


This class encapsulates the latitude, longitude, and altitude of a position in geodetic coordinates relative to the surface of a celestial body.




**Template parameters:**


* `_body_` The celestial body NTTP that defines the reference ellipsoid and frames. 




    
## Public Static Attributes Documentation




### variable \_fixed\_frame\_ 

_Body-fixed rotating frame._ 
```C++
constexpr auto astrea::astro::Geodetic< _body_ >::_fixed_frame_;
```




<hr>



### variable \_icrf\_frame\_ 

_Inertial frame for the body._ 
```C++
constexpr auto astrea::astro::Geodetic< _body_ >::_icrf_frame_;
```




<hr>



### variable body 

_The celestial body of this_ [_**Geodetic**_](classastrea_1_1astro_1_1Geodetic.md) _state._
```C++
constexpr auto astrea::astro::Geodetic< _body_ >::body;
```




<hr>
## Public Functions Documentation




### function Geodetic [1/7]

_Default constructor for_ [_**Geodetic**_](classastrea_1_1astro_1_1Geodetic.md) _._
```C++
inline astrea::astro::Geodetic::Geodetic (
    Unitless scale=0.0 *astrea::detail::unitless
) 
```



Initializes the [**Geodetic**](classastrea_1_1astro_1_1Geodetic.md) state vector with zero values. 


        

<hr>



### function Geodetic [2/7]

_Constructor for_ [_**Geodetic**_](classastrea_1_1astro_1_1Geodetic.md) _with latitude, longitude, and altitude._
```C++
inline astrea::astro::Geodetic::Geodetic (
    const Angle & latitude,
    const Angle & longitude,
    const Distance & altitude
) 
```





**Parameters:**


* `latitude` [**Geodetic**](classastrea_1_1astro_1_1Geodetic.md) latitude 
* `longitude` Longitude 
* `altitude` Altitude 




        

<hr>



### function Geodetic [3/7]

_Constructor for_ [_**Geodetic**_](classastrea_1_1astro_1_1Geodetic.md) _from a radius vector in any inertial frame centred on the same body._
```C++
template<auto _frame_>
astrea::astro::Geodetic::Geodetic (
    const RadiusVector < _frame_ > & r,
    const Date & date
) 
```



Accepts any frame whose origin matches _body_ and whose axis is the ICRF axis, so that both the canonical named frame (e.g. [**frames::earth::icrf**](structastrea_1_1astro_1_1frames_1_1earth_1_1icrf.md)) and the synthetic frame produced by make\_frame(_body_, [**axes::icrf**](structastrea_1_1astro_1_1axes_1_1icrf.md)) are accepted.




**Template parameters:**


* `_frame_` The inertial frame of the radius vector. 



**Parameters:**


* `r` Radius vector in an ICRF-axis frame centred on the body. 
* `date` Epoch date used to convert inertial to body-fixed. 




        

<hr>



### function Geodetic [4/7]

_Constructor for_ [_**Geodetic**_](classastrea_1_1astro_1_1Geodetic.md) _from a radius vector in the body-fixed frame._
```C++
astrea::astro::Geodetic::Geodetic (
    const RadiusVector < _fixed_frame_ > & r
) 
```





**Parameters:**


* `r` Radius vector in the body-fixed frame. 




        

<hr>



### function Geodetic [5/7]

_Constructor for_ [_**Geodetic**_](classastrea_1_1astro_1_1Geodetic.md) _from orbital elements._
```C++
template<IsOrbitalElements T>
inline astrea::astro::Geodetic::Geodetic (
    const T & elements,
    const Date & date
) 
```





**Parameters:**


* `elements` Orbital elements 
* `date` Epoch date 




        

<hr>



### function Geodetic [6/7]

_Copy constructor for_ [_**Geodetic**_](classastrea_1_1astro_1_1Geodetic.md) _._
```C++
astrea::astro::Geodetic::Geodetic (
    const Geodetic < _body_ > & other
) 
```





**Parameters:**


* `other` Another [**Geodetic**](classastrea_1_1astro_1_1Geodetic.md) object 




        

<hr>



### function Geodetic [7/7]

_Move constructor for_ [_**Geodetic**_](classastrea_1_1astro_1_1Geodetic.md) _._
```C++
astrea::astro::Geodetic::Geodetic (
    Geodetic < _body_ > && other
) noexcept
```





**Parameters:**


* `other` Another [**Geodetic**](classastrea_1_1astro_1_1Geodetic.md) object 




        

<hr>



### function get\_altitude 

_Get the altitude of the_ [_**Geodetic**_](classastrea_1_1astro_1_1Geodetic.md) _state vector._
```C++
inline const Distance & astrea::astro::Geodetic::get_altitude () const
```





**Returns:**

const Distance& Reference to the altitude component of the [**Geodetic**](classastrea_1_1astro_1_1Geodetic.md) state vector. 





        

<hr>



### function get\_latitude 

_Get the latitude of the_ [_**Geodetic**_](classastrea_1_1astro_1_1Geodetic.md) _state vector._
```C++
inline const Angle & astrea::astro::Geodetic::get_latitude () const
```





**Returns:**

const Angle& Reference to the latitude component of the [**Geodetic**](classastrea_1_1astro_1_1Geodetic.md) state vector. 





        

<hr>



### function get\_longitude 

_Get the longitude of the_ [_**Geodetic**_](classastrea_1_1astro_1_1Geodetic.md) _state vector._
```C++
inline const Angle & astrea::astro::Geodetic::get_longitude () const
```





**Returns:**

const Angle& Reference to the longitude component of the [**Geodetic**](classastrea_1_1astro_1_1Geodetic.md) state vector. 





        

<hr>



### function get\_position [1/2]

_Converts the_ [_**Geodetic**_](classastrea_1_1astro_1_1Geodetic.md) _state vector to a position in the body-fixed frame._
```C++
RadiusVector < _fixed_frame_ > astrea::astro::Geodetic::get_position () const
```





**Returns:**

RadiusVector in the body-fixed frame. 





        

<hr>



### function get\_position [2/2]

_Converts the_ [_**Geodetic**_](classastrea_1_1astro_1_1Geodetic.md) _state vector to a position in the body's inertial frame._
```C++
RadiusVector < _icrf_frame_ > astrea::astro::Geodetic::get_position (
    const Date & date
) const
```





**Parameters:**


* `date` Epoch date used to convert body-fixed to inertial. 



**Returns:**

RadiusVector in the body's inertial frame. 





        

<hr>



### function interpolate 

_Interpolates between two_ [_**Geodetic**_](classastrea_1_1astro_1_1Geodetic.md) _states at a given time._
```C++
Geodetic astrea::astro::Geodetic::interpolate (
    const Time & thisTime,
    const Time & otherTime,
    const Geodetic < _body_ > & other,
    const Time & targetTime
) const
```





**Parameters:**


* `thisTime` Time of the current state 
* `otherTime` Time of the other state 
* `other` Other [**Geodetic**](classastrea_1_1astro_1_1Geodetic.md) state to interpolate with 
* `targetTime` Target time for interpolation 



**Returns:**

[**Geodetic**](classastrea_1_1astro_1_1Geodetic.md) Interpolated [**Geodetic**](classastrea_1_1astro_1_1Geodetic.md) state at the target time. 





        

<hr>



### function operator!= 

_Compares two_ [_**Geodetic**_](classastrea_1_1astro_1_1Geodetic.md) _objects for inequality._
```C++
bool astrea::astro::Geodetic::operator!= (
    const Geodetic < _body_ > & other
) const
```





**Parameters:**


* `other` Another [**Geodetic**](classastrea_1_1astro_1_1Geodetic.md) object 



**Returns:**

true if the two [**Geodetic**](classastrea_1_1astro_1_1Geodetic.md) objects are not equal 




**Returns:**

false if the two [**Geodetic**](classastrea_1_1astro_1_1Geodetic.md) objects are equal 





        

<hr>



### function operator\* 

_Multiplies the_ [_**Geodetic**_](classastrea_1_1astro_1_1Geodetic.md) _state vector by a scalar._
```C++
Geodetic astrea::astro::Geodetic::operator* (
    const Unitless & multiplier
) const
```





**Parameters:**


* `multiplier` Scalar value to multiply with 



**Returns:**

Resultant [**Geodetic**](classastrea_1_1astro_1_1Geodetic.md) after multiplication. 





        

<hr>



### function operator\*= 

_Multiplies the_ [_**Geodetic**_](classastrea_1_1astro_1_1Geodetic.md) _state vector by a scalar._
```C++
Geodetic & astrea::astro::Geodetic::operator*= (
    const Unitless & multiplier
) 
```





**Parameters:**


* `multiplier` Scalar value to multiply with 



**Returns:**

Reference to the current [**Geodetic**](classastrea_1_1astro_1_1Geodetic.md) object after multiplication. 





        

<hr>



### function operator+ 

_Adds two_ [_**Geodetic**_](classastrea_1_1astro_1_1Geodetic.md) _objects._
```C++
Geodetic astrea::astro::Geodetic::operator+ (
    const Geodetic < _body_ > & other
) const
```





**Parameters:**


* `other` Another [**Geodetic**](classastrea_1_1astro_1_1Geodetic.md) object 



**Returns:**

Resultant [**Geodetic**](classastrea_1_1astro_1_1Geodetic.md) sum. 





        

<hr>



### function operator+= 

_Adds another_ [_**Geodetic**_](classastrea_1_1astro_1_1Geodetic.md) _object to the current one._
```C++
Geodetic & astrea::astro::Geodetic::operator+= (
    const Geodetic < _body_ > & other
) 
```





**Parameters:**


* `other` Another [**Geodetic**](classastrea_1_1astro_1_1Geodetic.md) object 



**Returns:**

Reference to the current [**Geodetic**](classastrea_1_1astro_1_1Geodetic.md) object after addition. 





        

<hr>



### function operator- 

_Subtracts another_ [_**Geodetic**_](classastrea_1_1astro_1_1Geodetic.md) _object from the current one._
```C++
Geodetic astrea::astro::Geodetic::operator- (
    const Geodetic < _body_ > & other
) const
```





**Parameters:**


* `other` Another [**Geodetic**](classastrea_1_1astro_1_1Geodetic.md) object 



**Returns:**

Resultant [**Geodetic**](classastrea_1_1astro_1_1Geodetic.md) difference. 





        

<hr>



### function operator-= 

_Subtracts another_ [_**Geodetic**_](classastrea_1_1astro_1_1Geodetic.md) _object from the current one._
```C++
Geodetic & astrea::astro::Geodetic::operator-= (
    const Geodetic < _body_ > & other
) 
```





**Parameters:**


* `other` Another [**Geodetic**](classastrea_1_1astro_1_1Geodetic.md) object 



**Returns:**

Reference to the current [**Geodetic**](classastrea_1_1astro_1_1Geodetic.md) object after subtraction. 





        

<hr>



### function operator/ 

_Divides the_ [_**Geodetic**_](classastrea_1_1astro_1_1Geodetic.md) _state vector by another_[_**Geodetic**_](classastrea_1_1astro_1_1Geodetic.md) _object._
```C++
std::vector< Unitless > astrea::astro::Geodetic::operator/ (
    const Geodetic < _body_ > & other
) const
```





**Parameters:**


* `other` Another [**Geodetic**](classastrea_1_1astro_1_1Geodetic.md) object 



**Returns:**

Resultant vector of unitless values after division. 





        

<hr>



### function operator/ 

_Divides the_ [_**Geodetic**_](classastrea_1_1astro_1_1Geodetic.md) _state vector by a scalar._
```C++
Geodetic astrea::astro::Geodetic::operator/ (
    const Unitless & divisor
) const
```





**Parameters:**


* `divisor` Scalar value to divide with 



**Returns:**

Resultant [**Geodetic**](classastrea_1_1astro_1_1Geodetic.md) after division. 





        

<hr>



### function operator/= 

_Divides the_ [_**Geodetic**_](classastrea_1_1astro_1_1Geodetic.md) _state vector by a scalar._
```C++
Geodetic & astrea::astro::Geodetic::operator/= (
    const Unitless & divisor
) 
```





**Parameters:**


* `divisor` Scalar value to divide with 



**Returns:**

Reference to the current [**Geodetic**](classastrea_1_1astro_1_1Geodetic.md) object after division. 





        

<hr>



### function operator= 

_Move assignment operator for_ [_**Geodetic**_](classastrea_1_1astro_1_1Geodetic.md) _._
```C++
Geodetic & astrea::astro::Geodetic::operator= (
    Geodetic < _body_ > && other
) noexcept
```





**Parameters:**


* `other` Another [**Geodetic**](classastrea_1_1astro_1_1Geodetic.md) object 



**Returns:**

[**Geodetic**](classastrea_1_1astro_1_1Geodetic.md)& Reference to the current object 





        

<hr>



### function operator= 

_Copy assignment operator for_ [_**Geodetic**_](classastrea_1_1astro_1_1Geodetic.md) _._
```C++
Geodetic & astrea::astro::Geodetic::operator= (
    const Geodetic < _body_ > & other
) 
```





**Parameters:**


* `other` Another [**Geodetic**](classastrea_1_1astro_1_1Geodetic.md) object 



**Returns:**

[**Geodetic**](classastrea_1_1astro_1_1Geodetic.md)& Reference to the current object 





        

<hr>



### function operator== 

_Compares two_ [_**Geodetic**_](classastrea_1_1astro_1_1Geodetic.md) _objects for equality._
```C++
bool astrea::astro::Geodetic::operator== (
    const Geodetic < _body_ > & other
) const
```





**Parameters:**


* `other` Another [**Geodetic**](classastrea_1_1astro_1_1Geodetic.md) object 



**Returns:**

true if the two [**Geodetic**](classastrea_1_1astro_1_1Geodetic.md) objects are equal 




**Returns:**

false if the two [**Geodetic**](classastrea_1_1astro_1_1Geodetic.md) objects are not equal 





        

<hr>



### function ~Geodetic 

_Default destructor for_ [_**Geodetic**_](classastrea_1_1astro_1_1Geodetic.md) _._
```C++
astrea::astro::Geodetic::~Geodetic () = default
```




<hr>

------------------------------
The documentation for this class was generated from the following file `astrea/astro/astro/state/angular_elements/Geodetic.hpp`

