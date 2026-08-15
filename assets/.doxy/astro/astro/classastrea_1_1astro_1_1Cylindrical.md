

# Class astrea::astro::Cylindrical

**template &lt;IsCelestialBody auto \_body\_&gt;**



[**ClassList**](annotated.md) **>** [**astrea**](namespaceastrea.md) **>** [**astro**](namespaceastrea_1_1astro.md) **>** [**Cylindrical**](classastrea_1_1astro_1_1Cylindrical.md)



_Class representing a_ [_**Cylindrical**_](classastrea_1_1astro_1_1Cylindrical.md) _state vector in astrodynamics._[More...](#detailed-description)

* `#include <Cylindrical.hpp>`























## Public Static Attributes

| Type | Name |
| ---: | :--- |
|  constexpr auto | [**\_fixed\_frame\_**](#variable-_fixed_frame_)   = `get\_body\_fixed\_frame&lt;\_body\_&gt;()`<br>_Body-fixed rotating frame._  |
|  constexpr auto | [**\_icrf\_frame\_**](#variable-_icrf_frame_)   = `make\_frame(\_body\_, [**axes::icrf**](structastrea_1_1astro_1_1axes_1_1icrf.md))`<br>_Inertial frame for the body._  |
|  constexpr auto | [**body**](#variable-body)   = `\_body\_`<br>_The celestial body of this_ [_**Cylindrical**_](classastrea_1_1astro_1_1Cylindrical.md) _state._ |














## Public Functions

| Type | Name |
| ---: | :--- |
|   | [**Cylindrical**](#function-cylindrical-17) (Unitless scale=0.0 \*astrea::detail::unitless) <br>_Default constructor for_ [_**Cylindrical**_](classastrea_1_1astro_1_1Cylindrical.md) _._ |
|   | [**Cylindrical**](#function-cylindrical-27) (const Distance & range, const Angle & azimuth, const Distance & elevation) <br>_Constructor for_ [_**Cylindrical**_](classastrea_1_1astro_1_1Cylindrical.md) _with range, azimuth, and elevation._ |
|   | [**Cylindrical**](#function-cylindrical-37) (const [**RadiusVector**](namespaceastrea_1_1astro.md#typedef-radiusvector)&lt; \_frame\_ &gt; & r, const [**Date**](classastrea_1_1astro_1_1Date.md) & date) <br>_Constructor for_ [_**Cylindrical**_](classastrea_1_1astro_1_1Cylindrical.md) _from any inertial radius vector centred on the same body._ |
|   | [**Cylindrical**](#function-cylindrical-47) (const [**RadiusVector**](namespaceastrea_1_1astro.md#typedef-radiusvector)&lt; [**\_fixed\_frame\_**](classastrea_1_1astro_1_1Cylindrical.md#variable-_fixed_frame_) &gt; & r) <br>_Constructor for_ [_**Cylindrical**_](classastrea_1_1astro_1_1Cylindrical.md) _from a body-fixed radius vector._ |
|   | [**Cylindrical**](#function-cylindrical-57) (const T & elements, const [**Date**](classastrea_1_1astro_1_1Date.md) & date) <br>_Constructor for_ [_**Cylindrical**_](classastrea_1_1astro_1_1Cylindrical.md) _from orbital elements._ |
|   | [**Cylindrical**](#function-cylindrical-67) (const [**Cylindrical**](classastrea_1_1astro_1_1Cylindrical.md)&lt; \_body\_ &gt; & other) <br>_Copy constructor for_ [_**Cylindrical**_](classastrea_1_1astro_1_1Cylindrical.md) _._ |
|   | [**Cylindrical**](#function-cylindrical-77) ([**Cylindrical**](classastrea_1_1astro_1_1Cylindrical.md)&lt; \_body\_ &gt; && other) noexcept<br>_Move constructor for_ [_**Cylindrical**_](classastrea_1_1astro_1_1Cylindrical.md) _._ |
|  const Angle & | [**get\_azimuth**](#function-get_azimuth) () const<br> |
|  const Distance & | [**get\_elevation**](#function-get_elevation) () const<br> |
|  [**RadiusVector**](namespaceastrea_1_1astro.md#typedef-radiusvector)&lt; [**\_fixed\_frame\_**](classastrea_1_1astro_1_1Cylindrical.md#variable-_fixed_frame_) &gt; | [**get\_position**](#function-get_position-12) () const<br>_Converts the_ [_**Cylindrical**_](classastrea_1_1astro_1_1Cylindrical.md) _state to a body-fixed radius vector._ |
|  [**RadiusVector**](namespaceastrea_1_1astro.md#typedef-radiusvector)&lt; [**\_icrf\_frame\_**](classastrea_1_1astro_1_1Cylindrical.md#variable-_icrf_frame_) &gt; | [**get\_position**](#function-get_position-22) (const [**Date**](classastrea_1_1astro_1_1Date.md) & date) const<br>_Converts the_ [_**Cylindrical**_](classastrea_1_1astro_1_1Cylindrical.md) _state to an inertial radius vector._ |
|  const Distance & | [**get\_range**](#function-get_range) () const<br> |
|  [**Cylindrical**](classastrea_1_1astro_1_1Cylindrical.md)&lt; \_body\_ &gt; | [**interpolate**](#function-interpolate) (const Time & thisTime, const Time & otherTime, const [**Cylindrical**](classastrea_1_1astro_1_1Cylindrical.md)&lt; \_body\_ &gt; & other, const Time & targetTime) const<br> |
|  bool | [**operator!=**](#function-operator) (const [**Cylindrical**](classastrea_1_1astro_1_1Cylindrical.md)&lt; \_body\_ &gt; & other) const<br> |
|  [**Cylindrical**](classastrea_1_1astro_1_1Cylindrical.md)&lt; \_body\_ &gt; | [**operator\***](#function-operator_1) (const Unitless & multiplier) const<br> |
|  [**Cylindrical**](classastrea_1_1astro_1_1Cylindrical.md)&lt; \_body\_ &gt; & | [**operator\*=**](#function-operator_2) (const Unitless & multiplier) <br> |
|  [**Cylindrical**](classastrea_1_1astro_1_1Cylindrical.md)&lt; \_body\_ &gt; | [**operator+**](#function-operator_3) (const [**Cylindrical**](classastrea_1_1astro_1_1Cylindrical.md)&lt; \_body\_ &gt; & other) const<br> |
|  [**Cylindrical**](classastrea_1_1astro_1_1Cylindrical.md)&lt; \_body\_ &gt; & | [**operator+=**](#function-operator_4) (const [**Cylindrical**](classastrea_1_1astro_1_1Cylindrical.md)&lt; \_body\_ &gt; & other) <br> |
|  [**Cylindrical**](classastrea_1_1astro_1_1Cylindrical.md)&lt; \_body\_ &gt; | [**operator-**](#function-operator-) (const [**Cylindrical**](classastrea_1_1astro_1_1Cylindrical.md)&lt; \_body\_ &gt; & other) const<br> |
|  [**Cylindrical**](classastrea_1_1astro_1_1Cylindrical.md)&lt; \_body\_ &gt; & | [**operator-=**](#function-operator-_1) (const [**Cylindrical**](classastrea_1_1astro_1_1Cylindrical.md)&lt; \_body\_ &gt; & other) <br> |
|  std::vector&lt; Unitless &gt; | [**operator/**](#function-operator_5) (const [**Cylindrical**](classastrea_1_1astro_1_1Cylindrical.md)&lt; \_body\_ &gt; & other) const<br> |
|  [**Cylindrical**](classastrea_1_1astro_1_1Cylindrical.md)&lt; \_body\_ &gt; | [**operator/**](#function-operator_6) (const Unitless & divisor) const<br> |
|  [**Cylindrical**](classastrea_1_1astro_1_1Cylindrical.md)&lt; \_body\_ &gt; & | [**operator/=**](#function-operator_7) (const Unitless & divisor) <br> |
|  [**Cylindrical**](classastrea_1_1astro_1_1Cylindrical.md)&lt; \_body\_ &gt; & | [**operator=**](#function-operator_8) ([**Cylindrical**](classastrea_1_1astro_1_1Cylindrical.md)&lt; \_body\_ &gt; && other) noexcept<br>_Move assignment operator for_ [_**Cylindrical**_](classastrea_1_1astro_1_1Cylindrical.md) _._ |
|  [**Cylindrical**](classastrea_1_1astro_1_1Cylindrical.md)&lt; \_body\_ &gt; & | [**operator=**](#function-operator_9) (const [**Cylindrical**](classastrea_1_1astro_1_1Cylindrical.md)&lt; \_body\_ &gt; & other) <br>_Copy assignment operator for_ [_**Cylindrical**_](classastrea_1_1astro_1_1Cylindrical.md) _._ |
|  bool | [**operator==**](#function-operator_10) (const [**Cylindrical**](classastrea_1_1astro_1_1Cylindrical.md)&lt; \_body\_ &gt; & other) const<br> |
|   | [**~Cylindrical**](#function-cylindrical) () = default<br>_Default destructor for_ [_**Cylindrical**_](classastrea_1_1astro_1_1Cylindrical.md) _._ |




























## Detailed Description


This class encapsulates the position and velocity of a vehicle in [**Cylindrical**](classastrea_1_1astro_1_1Cylindrical.md) coordinates.




**Template parameters:**


* `_body_` The celestial body NTTP that defines the reference frames. 




    
## Public Static Attributes Documentation




### variable \_fixed\_frame\_ 

_Body-fixed rotating frame._ 
```C++
constexpr auto astrea::astro::Cylindrical< _body_ >::_fixed_frame_;
```




<hr>



### variable \_icrf\_frame\_ 

_Inertial frame for the body._ 
```C++
constexpr auto astrea::astro::Cylindrical< _body_ >::_icrf_frame_;
```




<hr>



### variable body 

_The celestial body of this_ [_**Cylindrical**_](classastrea_1_1astro_1_1Cylindrical.md) _state._
```C++
constexpr auto astrea::astro::Cylindrical< _body_ >::body;
```




<hr>
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

_Constructor for_ [_**Cylindrical**_](classastrea_1_1astro_1_1Cylindrical.md) _with range, azimuth, and elevation._
```C++
inline astrea::astro::Cylindrical::Cylindrical (
    const Distance & range,
    const Angle & azimuth,
    const Distance & elevation
) 
```





**Parameters:**


* `range` Range 
* `azimuth` [**Cylindrical**](classastrea_1_1astro_1_1Cylindrical.md) azimuth 
* `elevation` Elevation 




        

<hr>



### function Cylindrical [3/7]

_Constructor for_ [_**Cylindrical**_](classastrea_1_1astro_1_1Cylindrical.md) _from any inertial radius vector centred on the same body._
```C++
template<auto _frame_>
astrea::astro::Cylindrical::Cylindrical (
    const RadiusVector < _frame_ > & r,
    const Date & date
) 
```



Accepts any frame whose origin matches _body_ and whose axis is the ICRF axis.




**Template parameters:**


* `_frame_` The inertial frame of the radius vector. 



**Parameters:**


* `r` Radius vector in an ICRF-axis frame centred on the body. 
* `date` [**Date**](classastrea_1_1astro_1_1Date.md) for the frame transformation. 




        

<hr>



### function Cylindrical [4/7]

_Constructor for_ [_**Cylindrical**_](classastrea_1_1astro_1_1Cylindrical.md) _from a body-fixed radius vector._
```C++
astrea::astro::Cylindrical::Cylindrical (
    const RadiusVector < _fixed_frame_ > & r
) 
```





**Parameters:**


* `r` Radius vector in the body-fixed frame 




        

<hr>



### function Cylindrical [5/7]

_Constructor for_ [_**Cylindrical**_](classastrea_1_1astro_1_1Cylindrical.md) _from orbital elements._
```C++
template<IsOrbitalElements T>
inline astrea::astro::Cylindrical::Cylindrical (
    const T & elements,
    const Date & date
) 
```





**Parameters:**


* `elements` Orbital elements 
* `date` [**Date**](classastrea_1_1astro_1_1Date.md) for the frame transformation 




        

<hr>



### function Cylindrical [6/7]

_Copy constructor for_ [_**Cylindrical**_](classastrea_1_1astro_1_1Cylindrical.md) _._
```C++
astrea::astro::Cylindrical::Cylindrical (
    const Cylindrical < _body_ > & other
) 
```




<hr>



### function Cylindrical [7/7]

_Move constructor for_ [_**Cylindrical**_](classastrea_1_1astro_1_1Cylindrical.md) _._
```C++
astrea::astro::Cylindrical::Cylindrical (
    Cylindrical < _body_ > && other
) noexcept
```




<hr>



### function get\_azimuth 

```C++
inline const Angle & astrea::astro::Cylindrical::get_azimuth () const
```




<hr>



### function get\_elevation 

```C++
inline const Distance & astrea::astro::Cylindrical::get_elevation () const
```




<hr>



### function get\_position [1/2]

_Converts the_ [_**Cylindrical**_](classastrea_1_1astro_1_1Cylindrical.md) _state to a body-fixed radius vector._
```C++
RadiusVector < _fixed_frame_ > astrea::astro::Cylindrical::get_position () const
```




<hr>



### function get\_position [2/2]

_Converts the_ [_**Cylindrical**_](classastrea_1_1astro_1_1Cylindrical.md) _state to an inertial radius vector._
```C++
RadiusVector < _icrf_frame_ > astrea::astro::Cylindrical::get_position (
    const Date & date
) const
```





**Parameters:**


* `date` [**Date**](classastrea_1_1astro_1_1Date.md) for the frame transformation 




        

<hr>



### function get\_range 

```C++
inline const Distance & astrea::astro::Cylindrical::get_range () const
```




<hr>



### function interpolate 

```C++
Cylindrical < _body_ > astrea::astro::Cylindrical::interpolate (
    const Time & thisTime,
    const Time & otherTime,
    const Cylindrical < _body_ > & other,
    const Time & targetTime
) const
```




<hr>



### function operator!= 

```C++
bool astrea::astro::Cylindrical::operator!= (
    const Cylindrical < _body_ > & other
) const
```




<hr>



### function operator\* 

```C++
Cylindrical < _body_ > astrea::astro::Cylindrical::operator* (
    const Unitless & multiplier
) const
```




<hr>



### function operator\*= 

```C++
Cylindrical < _body_ > & astrea::astro::Cylindrical::operator*= (
    const Unitless & multiplier
) 
```




<hr>



### function operator+ 

```C++
Cylindrical < _body_ > astrea::astro::Cylindrical::operator+ (
    const Cylindrical < _body_ > & other
) const
```




<hr>



### function operator+= 

```C++
Cylindrical < _body_ > & astrea::astro::Cylindrical::operator+= (
    const Cylindrical < _body_ > & other
) 
```




<hr>



### function operator- 

```C++
Cylindrical < _body_ > astrea::astro::Cylindrical::operator- (
    const Cylindrical < _body_ > & other
) const
```




<hr>



### function operator-= 

```C++
Cylindrical < _body_ > & astrea::astro::Cylindrical::operator-= (
    const Cylindrical < _body_ > & other
) 
```




<hr>



### function operator/ 

```C++
std::vector< Unitless > astrea::astro::Cylindrical::operator/ (
    const Cylindrical < _body_ > & other
) const
```




<hr>



### function operator/ 

```C++
Cylindrical < _body_ > astrea::astro::Cylindrical::operator/ (
    const Unitless & divisor
) const
```




<hr>



### function operator/= 

```C++
Cylindrical < _body_ > & astrea::astro::Cylindrical::operator/= (
    const Unitless & divisor
) 
```




<hr>



### function operator= 

_Move assignment operator for_ [_**Cylindrical**_](classastrea_1_1astro_1_1Cylindrical.md) _._
```C++
Cylindrical < _body_ > & astrea::astro::Cylindrical::operator= (
    Cylindrical < _body_ > && other
) noexcept
```




<hr>



### function operator= 

_Copy assignment operator for_ [_**Cylindrical**_](classastrea_1_1astro_1_1Cylindrical.md) _._
```C++
Cylindrical < _body_ > & astrea::astro::Cylindrical::operator= (
    const Cylindrical < _body_ > & other
) 
```




<hr>



### function operator== 

```C++
bool astrea::astro::Cylindrical::operator== (
    const Cylindrical < _body_ > & other
) const
```




<hr>



### function ~Cylindrical 

_Default destructor for_ [_**Cylindrical**_](classastrea_1_1astro_1_1Cylindrical.md) _._
```C++
astrea::astro::Cylindrical::~Cylindrical () = default
```




<hr>

------------------------------
The documentation for this class was generated from the following file `astrea/astro/astro/state/angular_elements/Cylindrical.hpp`

