

# Class astrea::astro::Spherical

**template &lt;IsCelestialBody [**auto**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) \_body\_&gt;**



[**ClassList**](annotated.md) **>** [**astrea**](namespaceastrea.md) **>** [**astro**](namespaceastrea_1_1astro.md) **>** [**Spherical**](classastrea_1_1astro_1_1Spherical.md)



_Class representing a_ [_**Spherical**_](classastrea_1_1astro_1_1Spherical.md) _state vector in astrodynamics._[More...](#detailed-description)

* `#include <Spherical.hpp>`























## Public Static Attributes

| Type | Name |
| ---: | :--- |
|  [**constexpr**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) [**auto**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) | [**\_fixed\_frame\_**](#variable-_fixed_frame_)   = `get\_body\_fixed\_frame&lt;[**\_body\_**](classastrea_1_1astro_1_1DirectionCosineMatrix.md)&gt;()`<br>_Body-fixed rotating frame._  |
|  [**constexpr**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) [**auto**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) | [**\_icrf\_frame\_**](#variable-_icrf_frame_)   = `make\_frame([**\_body\_**](classastrea_1_1astro_1_1DirectionCosineMatrix.md), [**axes::icrf**](structastrea_1_1astro_1_1axes_1_1icrf.md))`<br>_Inertial frame for the body._  |
|  [**constexpr**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) [**auto**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) | [**body**](#variable-body)   = `[**\_body\_**](classastrea_1_1astro_1_1DirectionCosineMatrix.md)`<br>_The celestial body of this_ [_**Spherical**_](classastrea_1_1astro_1_1Spherical.md) _state._ |














## Public Functions

| Type | Name |
| ---: | :--- |
|   | [**Spherical**](#function-spherical-17) ([**Unitless**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) scale=0.0 \*astrea::detail::unitless) <br>_Default constructor for_ [_**Spherical**_](classastrea_1_1astro_1_1Spherical.md) _._ |
|   | [**Spherical**](#function-spherical-27) ([**const**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) [**Distance**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) & range, [**const**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) [**Angle**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) & inclination, [**const**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) [**Angle**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) & azimuth) <br>_Constructor for_ [_**Spherical**_](classastrea_1_1astro_1_1Spherical.md) _with range, inclination, and azimuth._ |
|   | [**Spherical**](#function-spherical-37) ([**const**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) [**RadiusVector**](namespaceastrea_1_1astro.md#typedef-radiusvector)&lt; \_frame\_ &gt; & r, [**const**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) [**Date**](classastrea_1_1astro_1_1Date.md) & date) <br>_Constructor for_ [_**Spherical**_](classastrea_1_1astro_1_1Spherical.md) _from any inertial radius vector centred on the same body._ |
|   | [**Spherical**](#function-spherical-47) ([**const**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) [**RadiusVector**](namespaceastrea_1_1astro.md#typedef-radiusvector)&lt; [**\_fixed\_frame\_**](classastrea_1_1astro_1_1Spherical.md#variable-_fixed_frame_) &gt; & r) <br>_Constructor for_ [_**Spherical**_](classastrea_1_1astro_1_1Spherical.md) _from a body-fixed radius vector._ |
|   | [**Spherical**](#function-spherical-57) ([**const**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) [**T**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) & elements, [**const**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) [**Date**](classastrea_1_1astro_1_1Date.md) & date) <br>_Constructor for_ [_**Spherical**_](classastrea_1_1astro_1_1Spherical.md) _from orbital elements._ |
|   | [**Spherical**](#function-spherical-67) ([**const**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) [**Spherical**](classastrea_1_1astro_1_1Spherical.md)&lt; [**\_body\_**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) &gt; & other) <br>_Copy constructor for_ [_**Spherical**_](classastrea_1_1astro_1_1Spherical.md) _._ |
|   | [**Spherical**](#function-spherical-77) ([**Spherical**](classastrea_1_1astro_1_1Spherical.md)&lt; [**\_body\_**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) &gt; && other) noexcept<br>_Move constructor for_ [_**Spherical**_](classastrea_1_1astro_1_1Spherical.md) _._ |
|  [**const**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) [**Angle**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) & | [**get\_azimuth**](#function-get_azimuth) () const<br> |
|  [**const**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) [**Angle**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) & | [**get\_inclination**](#function-get_inclination) () const<br> |
|  [**RadiusVector**](namespaceastrea_1_1astro.md#typedef-radiusvector)&lt; [**\_fixed\_frame\_**](classastrea_1_1astro_1_1Spherical.md#variable-_fixed_frame_) &gt; | [**get\_position**](#function-get_position-12) () const<br>_Converts the_ [_**Spherical**_](classastrea_1_1astro_1_1Spherical.md) _state to a body-fixed radius vector._ |
|  [**RadiusVector**](namespaceastrea_1_1astro.md#typedef-radiusvector)&lt; [**\_icrf\_frame\_**](classastrea_1_1astro_1_1Spherical.md#variable-_icrf_frame_) &gt; | [**get\_position**](#function-get_position-22) ([**const**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) [**Date**](classastrea_1_1astro_1_1Date.md) & date) const<br>_Converts the_ [_**Spherical**_](classastrea_1_1astro_1_1Spherical.md) _state to an inertial radius vector._ |
|  [**const**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) [**Distance**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) & | [**get\_range**](#function-get_range) () const<br> |
|  [**Spherical**](classastrea_1_1astro_1_1Spherical.md)&lt; [**\_body\_**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) &gt; | [**interpolate**](#function-interpolate) ([**const**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) [**Time**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) & thisTime, [**const**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) [**Time**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) & otherTime, [**const**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) [**Spherical**](classastrea_1_1astro_1_1Spherical.md)&lt; [**\_body\_**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) &gt; & other, [**const**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) [**Time**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) & targetTime) const<br> |
|  [**bool**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) | [**operator!=**](#function-operator) ([**const**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) [**Spherical**](classastrea_1_1astro_1_1Spherical.md)&lt; [**\_body\_**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) &gt; & other) const<br> |
|  [**Spherical**](classastrea_1_1astro_1_1Spherical.md)&lt; [**\_body\_**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) &gt; | [**operator\***](#function-operator_1) ([**const**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) [**Unitless**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) & multiplier) const<br> |
|  [**Spherical**](classastrea_1_1astro_1_1Spherical.md)&lt; [**\_body\_**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) &gt; & | [**operator\*=**](#function-operator_2) ([**const**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) [**Unitless**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) & multiplier) <br> |
|  [**Spherical**](classastrea_1_1astro_1_1Spherical.md)&lt; [**\_body\_**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) &gt; | [**operator+**](#function-operator_3) ([**const**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) [**Spherical**](classastrea_1_1astro_1_1Spherical.md)&lt; [**\_body\_**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) &gt; & other) const<br> |
|  [**Spherical**](classastrea_1_1astro_1_1Spherical.md)&lt; [**\_body\_**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) &gt; & | [**operator+=**](#function-operator_4) ([**const**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) [**Spherical**](classastrea_1_1astro_1_1Spherical.md)&lt; [**\_body\_**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) &gt; & other) <br> |
|  [**Spherical**](classastrea_1_1astro_1_1Spherical.md)&lt; [**\_body\_**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) &gt; | [**operator-**](#function-operator-) ([**const**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) [**Spherical**](classastrea_1_1astro_1_1Spherical.md)&lt; [**\_body\_**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) &gt; & other) const<br> |
|  [**Spherical**](classastrea_1_1astro_1_1Spherical.md)&lt; [**\_body\_**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) &gt; & | [**operator-=**](#function-operator-_1) ([**const**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) [**Spherical**](classastrea_1_1astro_1_1Spherical.md)&lt; [**\_body\_**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) &gt; & other) <br> |
|  std::vector&lt; [**Unitless**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) &gt; | [**operator/**](#function-operator_5) ([**const**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) [**Spherical**](classastrea_1_1astro_1_1Spherical.md)&lt; [**\_body\_**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) &gt; & other) const<br> |
|  [**Spherical**](classastrea_1_1astro_1_1Spherical.md)&lt; [**\_body\_**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) &gt; | [**operator/**](#function-operator_6) ([**const**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) [**Unitless**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) & divisor) const<br> |
|  [**Spherical**](classastrea_1_1astro_1_1Spherical.md)&lt; [**\_body\_**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) &gt; & | [**operator/=**](#function-operator_7) ([**const**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) [**Unitless**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) & divisor) <br> |
|  [**Spherical**](classastrea_1_1astro_1_1Spherical.md)&lt; [**\_body\_**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) &gt; & | [**operator=**](#function-operator_8) ([**Spherical**](classastrea_1_1astro_1_1Spherical.md)&lt; [**\_body\_**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) &gt; && other) noexcept<br>_Move assignment operator for_ [_**Spherical**_](classastrea_1_1astro_1_1Spherical.md) _._ |
|  [**Spherical**](classastrea_1_1astro_1_1Spherical.md)&lt; [**\_body\_**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) &gt; & | [**operator=**](#function-operator_9) ([**const**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) [**Spherical**](classastrea_1_1astro_1_1Spherical.md)&lt; [**\_body\_**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) &gt; & other) <br>_Copy assignment operator for_ [_**Spherical**_](classastrea_1_1astro_1_1Spherical.md) _._ |
|  [**bool**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) | [**operator==**](#function-operator_10) ([**const**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) [**Spherical**](classastrea_1_1astro_1_1Spherical.md)&lt; [**\_body\_**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) &gt; & other) const<br> |
|   | [**~Spherical**](#function-spherical) () = default<br>_Default destructor for_ [_**Spherical**_](classastrea_1_1astro_1_1Spherical.md) _._ |




























## Detailed Description


This class encapsulates the position and velocity of a vehicle in [**Spherical**](classastrea_1_1astro_1_1Spherical.md) coordinates.




**Template parameters:**


* `_body_` The celestial body NTTP that defines the reference frames. 




    
## Public Static Attributes Documentation




### variable \_fixed\_frame\_ 

_Body-fixed rotating frame._ 
```C++
constexpr auto astrea::astro::Spherical< _body_ >::_fixed_frame_;
```




<hr>



### variable \_icrf\_frame\_ 

_Inertial frame for the body._ 
```C++
constexpr auto astrea::astro::Spherical< _body_ >::_icrf_frame_;
```




<hr>



### variable body 

_The celestial body of this_ [_**Spherical**_](classastrea_1_1astro_1_1Spherical.md) _state._
```C++
constexpr auto astrea::astro::Spherical< _body_ >::body;
```




<hr>
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

_Constructor for_ [_**Spherical**_](classastrea_1_1astro_1_1Spherical.md) _with range, inclination, and azimuth._
```C++
inline astrea::astro::Spherical::Spherical (
    const  Distance & range,
    const  Angle & inclination,
    const  Angle & azimuth
) 
```





**Parameters:**


* `range` Range 
* `inclination` Inclination 
* `azimuth` Azimuth 




        

<hr>



### function Spherical [3/7]

_Constructor for_ [_**Spherical**_](classastrea_1_1astro_1_1Spherical.md) _from any inertial radius vector centred on the same body._
```C++
template<auto _frame_>
astrea::astro::Spherical::Spherical (
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



### function Spherical [4/7]

_Constructor for_ [_**Spherical**_](classastrea_1_1astro_1_1Spherical.md) _from a body-fixed radius vector._
```C++
astrea::astro::Spherical::Spherical (
    const  RadiusVector < _fixed_frame_ > & r
) 
```





**Parameters:**


* `r` Radius vector in the body-fixed frame 




        

<hr>



### function Spherical [5/7]

_Constructor for_ [_**Spherical**_](classastrea_1_1astro_1_1Spherical.md) _from orbital elements._
```C++
template<IsOrbitalElements T>
inline astrea::astro::Spherical::Spherical (
    const  T & elements,
    const  Date & date
) 
```





**Parameters:**


* `elements` Orbital elements 
* `date` [**Date**](classastrea_1_1astro_1_1Date.md) for the frame transformation 




        

<hr>



### function Spherical [6/7]

_Copy constructor for_ [_**Spherical**_](classastrea_1_1astro_1_1Spherical.md) _._
```C++
astrea::astro::Spherical::Spherical (
    const  Spherical < _body_ > & other
) 
```




<hr>



### function Spherical [7/7]

_Move constructor for_ [_**Spherical**_](classastrea_1_1astro_1_1Spherical.md) _._
```C++
astrea::astro::Spherical::Spherical (
    Spherical < _body_ > && other
) noexcept
```




<hr>



### function get\_azimuth 

```C++
inline const  Angle & astrea::astro::Spherical::get_azimuth () const
```




<hr>



### function get\_inclination 

```C++
inline const  Angle & astrea::astro::Spherical::get_inclination () const
```




<hr>



### function get\_position [1/2]

_Converts the_ [_**Spherical**_](classastrea_1_1astro_1_1Spherical.md) _state to a body-fixed radius vector._
```C++
RadiusVector < _fixed_frame_ > astrea::astro::Spherical::get_position () const
```




<hr>



### function get\_position [2/2]

_Converts the_ [_**Spherical**_](classastrea_1_1astro_1_1Spherical.md) _state to an inertial radius vector._
```C++
RadiusVector < _icrf_frame_ > astrea::astro::Spherical::get_position (
    const  Date & date
) const
```





**Parameters:**


* `date` [**Date**](classastrea_1_1astro_1_1Date.md) for the frame transformation 




        

<hr>



### function get\_range 

```C++
inline const  Distance & astrea::astro::Spherical::get_range () const
```




<hr>



### function interpolate 

```C++
Spherical < _body_ > astrea::astro::Spherical::interpolate (
    const  Time & thisTime,
    const  Time & otherTime,
    const  Spherical < _body_ > & other,
    const  Time & targetTime
) const
```




<hr>



### function operator!= 

```C++
bool astrea::astro::Spherical::operator!= (
    const  Spherical < _body_ > & other
) const
```




<hr>



### function operator\* 

```C++
Spherical < _body_ > astrea::astro::Spherical::operator* (
    const  Unitless & multiplier
) const
```




<hr>



### function operator\*= 

```C++
Spherical < _body_ > & astrea::astro::Spherical::operator*= (
    const  Unitless & multiplier
) 
```




<hr>



### function operator+ 

```C++
Spherical < _body_ > astrea::astro::Spherical::operator+ (
    const  Spherical < _body_ > & other
) const
```




<hr>



### function operator+= 

```C++
Spherical < _body_ > & astrea::astro::Spherical::operator+= (
    const  Spherical < _body_ > & other
) 
```




<hr>



### function operator- 

```C++
Spherical < _body_ > astrea::astro::Spherical::operator- (
    const  Spherical < _body_ > & other
) const
```




<hr>



### function operator-= 

```C++
Spherical < _body_ > & astrea::astro::Spherical::operator-= (
    const  Spherical < _body_ > & other
) 
```




<hr>



### function operator/ 

```C++
std::vector< Unitless > astrea::astro::Spherical::operator/ (
    const  Spherical < _body_ > & other
) const
```




<hr>



### function operator/ 

```C++
Spherical < _body_ > astrea::astro::Spherical::operator/ (
    const  Unitless & divisor
) const
```




<hr>



### function operator/= 

```C++
Spherical < _body_ > & astrea::astro::Spherical::operator/= (
    const  Unitless & divisor
) 
```




<hr>



### function operator= 

_Move assignment operator for_ [_**Spherical**_](classastrea_1_1astro_1_1Spherical.md) _._
```C++
Spherical < _body_ > & astrea::astro::Spherical::operator= (
    Spherical < _body_ > && other
) noexcept
```




<hr>



### function operator= 

_Copy assignment operator for_ [_**Spherical**_](classastrea_1_1astro_1_1Spherical.md) _._
```C++
Spherical < _body_ > & astrea::astro::Spherical::operator= (
    const  Spherical < _body_ > & other
) 
```




<hr>



### function operator== 

```C++
bool astrea::astro::Spherical::operator== (
    const  Spherical < _body_ > & other
) const
```




<hr>



### function ~Spherical 

_Default destructor for_ [_**Spherical**_](classastrea_1_1astro_1_1Spherical.md) _._
```C++
astrea::astro::Spherical::~Spherical () = default
```




<hr>

------------------------------
The documentation for this class was generated from the following file `astrea/astro/astro/state/angular_elements/Spherical.hpp`

