

# Class astrea::astro::Cartesian

**template &lt;IsFrame auto \_frame\_&gt;**



[**ClassList**](annotated.md) **>** [**astrea**](namespaceastrea.md) **>** [**astro**](namespaceastrea_1_1astro.md) **>** [**Cartesian**](classastrea_1_1astro_1_1Cartesian.md)



_Class representing a_ [_**Cartesian**_](classastrea_1_1astro_1_1Cartesian.md) _state vector in astrodynamics._[More...](#detailed-description)

* `#include <Cartesian.hpp>`

















## Public Types

| Type | Name |
| ---: | :--- |
| typedef [**Cartesian**](classastrea_1_1astro_1_1Cartesian.md)&lt; F &gt; | [**BaseType**](#typedef-basetype)  <br> |






## Public Static Attributes

| Type | Name |
| ---: | :--- |
|  constexpr auto | [**frame**](#variable-frame)   = `\_frame\_`<br>_The reference frame of the_ [_**Cartesian**_](classastrea_1_1astro_1_1Cartesian.md) _state vector._ |














## Public Functions

| Type | Name |
| ---: | :--- |
|   | [**Cartesian**](#function-cartesian-18) (Unitless scale=0.0 \*astrea::detail::unitless) <br>_Default constructor for_ [_**Cartesian**_](classastrea_1_1astro_1_1Cartesian.md) _._ |
|   | [**Cartesian**](#function-cartesian-28) (const [**RadiusVector**](namespaceastrea_1_1astro.md#typedef-radiusvector)&lt; \_frame\_ &gt; & r, const [**VelocityVector**](namespaceastrea_1_1astro.md#typedef-velocityvector)&lt; \_frame\_ &gt; & v) <br>_Constructor for_ [_**Cartesian**_](classastrea_1_1astro_1_1Cartesian.md) _with position and velocity vectors._ |
|   | [**Cartesian**](#function-cartesian-38) (const Distance & x, const Distance & y, const Distance & z, const Velocity & vx, const Velocity & vy, const Velocity & vz) <br>_Constructor for_ [_**Cartesian**_](classastrea_1_1astro_1_1Cartesian.md) _with individual position and velocity components._ |
|   | [**Cartesian**](#function-cartesian-48) (const [**Cartesian**](classastrea_1_1astro_1_1Cartesian.md) & elements, const GravParam & mu) <br>_Constructor for_ [_**Cartesian**_](classastrea_1_1astro_1_1Cartesian.md) _from another_[_**Cartesian**_](classastrea_1_1astro_1_1Cartesian.md) _object._ |
|   | [**Cartesian**](#function-cartesian-58) (const [**Keplerian**](classastrea_1_1astro_1_1Keplerian.md)&lt; \_frame\_ &gt; & elements, const GravParam & mu) <br>_Constructor for_ [_**Cartesian**_](classastrea_1_1astro_1_1Cartesian.md) _from_[_**Keplerian**_](classastrea_1_1astro_1_1Keplerian.md) _elements._ |
|   | [**Cartesian**](#function-cartesian-68) (const [**Equinoctial**](classastrea_1_1astro_1_1Equinoctial.md)&lt; \_frame\_ &gt; & elements, const GravParam & mu) <br>_Constructor for_ [_**Cartesian**_](classastrea_1_1astro_1_1Cartesian.md) _from_[_**Equinoctial**_](classastrea_1_1astro_1_1Equinoctial.md) _elements._ |
|   | [**Cartesian**](#function-cartesian-78) (const [**Cartesian**](classastrea_1_1astro_1_1Cartesian.md)&lt; \_frame\_ &gt; & other) <br>_Copy constructor for_ [_**Cartesian**_](classastrea_1_1astro_1_1Cartesian.md) _._ |
|   | [**Cartesian**](#function-cartesian-88) ([**Cartesian**](classastrea_1_1astro_1_1Cartesian.md)&lt; \_frame\_ &gt; &&) noexcept<br>_Move constructor for_ [_**Cartesian**_](classastrea_1_1astro_1_1Cartesian.md) _._ |
|  std::vector&lt; double &gt; | [**force\_to\_double\_vector**](#function-force_to_double_vector) () const<br>_Converts the_ [_**Cartesian**_](classastrea_1_1astro_1_1Cartesian.md) _state vector to a vector of unitless values._ |
|  const [**RadiusVector**](namespaceastrea_1_1astro.md#typedef-radiusvector)&lt; \_frame\_ &gt; & | [**get\_position**](#function-get_position) () const<br>_Converts the_ [_**Cartesian**_](classastrea_1_1astro_1_1Cartesian.md) _state vector to a RadiusVector&lt;__frame_ _&gt;._ |
|  const [**VelocityVector**](namespaceastrea_1_1astro.md#typedef-velocityvector)&lt; \_frame\_ &gt; & | [**get\_velocity**](#function-get_velocity) () const<br>_Converts the_ [_**Cartesian**_](classastrea_1_1astro_1_1Cartesian.md) _state vector to a VelocityVector&lt;__frame_ _&gt;._ |
|  const Velocity & | [**get\_vx**](#function-get_vx) () const<br>_Get the vx value of the_ [_**Cartesian**_](classastrea_1_1astro_1_1Cartesian.md) _state vector._ |
|  const Velocity & | [**get\_vy**](#function-get_vy) () const<br>_Get the vy value of the_ [_**Cartesian**_](classastrea_1_1astro_1_1Cartesian.md) _state vector._ |
|  const Velocity & | [**get\_vz**](#function-get_vz) () const<br>_Get the vz value of the_ [_**Cartesian**_](classastrea_1_1astro_1_1Cartesian.md) _state vector._ |
|  const Distance & | [**get\_x**](#function-get_x) () const<br>_Get the x value of the_ [_**Cartesian**_](classastrea_1_1astro_1_1Cartesian.md) _state vector._ |
|  const Distance & | [**get\_y**](#function-get_y) () const<br>_Get the y value of the_ [_**Cartesian**_](classastrea_1_1astro_1_1Cartesian.md) _state vector._ |
|  const Distance & | [**get\_z**](#function-get_z) () const<br>_Get the z value of the_ [_**Cartesian**_](classastrea_1_1astro_1_1Cartesian.md) _state vector._ |
|  [**Cartesian**](classastrea_1_1astro_1_1Cartesian.md)&lt; target\_frame &gt; | [**in\_frame**](#function-in_frame-12) (const [**Date**](classastrea_1_1astro_1_1Date.md) & epoch) const<br>_Converts this_ [_**Cartesian**_](classastrea_1_1astro_1_1Cartesian.md) _state to an equivalent_[_**Cartesian**_](classastrea_1_1astro_1_1Cartesian.md) _state in a different frame._ |
|  [**Cartesian**](classastrea_1_1astro_1_1Cartesian.md)&lt; target\_frame &gt; | [**in\_frame**](#function-in_frame-22) (const [**Date**](classastrea_1_1astro_1_1Date.md) & epoch, const GravParam &) const<br> |
|  [**Cartesian**](classastrea_1_1astro_1_1Cartesian.md) | [**interpolate**](#function-interpolate) (const Time & thisTime, const Time & otherTime, const [**Cartesian**](classastrea_1_1astro_1_1Cartesian.md)&lt; \_frame\_ &gt; & other, const GravParam & mu, const Time & targetTime) const<br>_Interpolates between two_ [_**Cartesian**_](classastrea_1_1astro_1_1Cartesian.md) _states at a given time._ |
|  bool | [**operator!=**](#function-operator) (const [**Cartesian**](classastrea_1_1astro_1_1Cartesian.md)&lt; \_frame\_ &gt; & other) const<br>_Compares two_ [_**Cartesian**_](classastrea_1_1astro_1_1Cartesian.md) _objects for inequality._ |
|  [**Cartesian**](classastrea_1_1astro_1_1Cartesian.md) | [**operator\***](#function-operator_1) (const Unitless & multiplier) const<br>_Multiplies the_ [_**Cartesian**_](classastrea_1_1astro_1_1Cartesian.md) _state vector by a scalar._ |
|  [**Cartesian**](classastrea_1_1astro_1_1Cartesian.md) & | [**operator\*=**](#function-operator_2) (const Unitless & multiplier) <br>_Multiplies the_ [_**Cartesian**_](classastrea_1_1astro_1_1Cartesian.md) _state vector by a scalar._ |
|  [**Cartesian**](classastrea_1_1astro_1_1Cartesian.md) | [**operator+**](#function-operator_3) (const [**Cartesian**](classastrea_1_1astro_1_1Cartesian.md)&lt; \_frame\_ &gt; & other) const<br>_Adds two_ [_**Cartesian**_](classastrea_1_1astro_1_1Cartesian.md) _objects._ |
|  [**Cartesian**](classastrea_1_1astro_1_1Cartesian.md) | [**operator+**](#function-operator_4) (const [**RadiusVector**](namespaceastrea_1_1astro.md#typedef-radiusvector)&lt; \_frame\_ &gt; & r) const<br> |
|  [**Cartesian**](classastrea_1_1astro_1_1Cartesian.md) | [**operator+**](#function-operator_5) (const [**VelocityVector**](namespaceastrea_1_1astro.md#typedef-velocityvector)&lt; \_frame\_ &gt; & v) const<br> |
|  [**Cartesian**](classastrea_1_1astro_1_1Cartesian.md) & | [**operator+=**](#function-operator_6) (const [**Cartesian**](classastrea_1_1astro_1_1Cartesian.md)&lt; \_frame\_ &gt; & other) <br>_Adds another_ [_**Cartesian**_](classastrea_1_1astro_1_1Cartesian.md) _object to the current one._ |
|  [**Cartesian**](classastrea_1_1astro_1_1Cartesian.md) & | [**operator+=**](#function-operator_7) (const [**RadiusVector**](namespaceastrea_1_1astro.md#typedef-radiusvector)&lt; \_frame\_ &gt; & r) <br> |
|  [**Cartesian**](classastrea_1_1astro_1_1Cartesian.md) & | [**operator+=**](#function-operator_8) (const [**VelocityVector**](namespaceastrea_1_1astro.md#typedef-velocityvector)&lt; \_frame\_ &gt; & v) <br> |
|  [**Cartesian**](classastrea_1_1astro_1_1Cartesian.md) | [**operator-**](#function-operator-) (const [**Cartesian**](classastrea_1_1astro_1_1Cartesian.md)&lt; \_frame\_ &gt; & other) const<br>_Subtracts another_ [_**Cartesian**_](classastrea_1_1astro_1_1Cartesian.md) _object from the current one._ |
|  [**Cartesian**](classastrea_1_1astro_1_1Cartesian.md) | [**operator-**](#function-operator-_1) (const [**RadiusVector**](namespaceastrea_1_1astro.md#typedef-radiusvector)&lt; \_frame\_ &gt; & r) const<br> |
|  [**Cartesian**](classastrea_1_1astro_1_1Cartesian.md) | [**operator-**](#function-operator-_2) (const [**VelocityVector**](namespaceastrea_1_1astro.md#typedef-velocityvector)&lt; \_frame\_ &gt; & v) const<br> |
|  [**Cartesian**](classastrea_1_1astro_1_1Cartesian.md) & | [**operator-=**](#function-operator-_3) (const [**Cartesian**](classastrea_1_1astro_1_1Cartesian.md)&lt; \_frame\_ &gt; & other) <br>_Subtracts another_ [_**Cartesian**_](classastrea_1_1astro_1_1Cartesian.md) _object from the current one._ |
|  [**Cartesian**](classastrea_1_1astro_1_1Cartesian.md) & | [**operator-=**](#function-operator-_4) (const [**RadiusVector**](namespaceastrea_1_1astro.md#typedef-radiusvector)&lt; \_frame\_ &gt; & r) <br> |
|  [**Cartesian**](classastrea_1_1astro_1_1Cartesian.md) & | [**operator-=**](#function-operator-_5) (const [**VelocityVector**](namespaceastrea_1_1astro.md#typedef-velocityvector)&lt; \_frame\_ &gt; & v) <br> |
|  [**CartesianPartial**](classastrea_1_1astro_1_1CartesianPartial.md)&lt; \_frame\_ &gt; | [**operator/**](#function-operator_9) (const Time & time) const<br>_Divides the_ [_**Cartesian**_](classastrea_1_1astro_1_1Cartesian.md) _state vector by a time._ |
|  std::vector&lt; Unitless &gt; | [**operator/**](#function-operator_10) (const [**Cartesian**](classastrea_1_1astro_1_1Cartesian.md)&lt; \_frame\_ &gt; & other) const<br>_Divides the_ [_**Cartesian**_](classastrea_1_1astro_1_1Cartesian.md) _state vector by another_[_**Cartesian**_](classastrea_1_1astro_1_1Cartesian.md) _object._ |
|  [**Cartesian**](classastrea_1_1astro_1_1Cartesian.md) | [**operator/**](#function-operator_11) (const Unitless & divisor) const<br>_Divides the_ [_**Cartesian**_](classastrea_1_1astro_1_1Cartesian.md) _state vector by a scalar._ |
|  [**Cartesian**](classastrea_1_1astro_1_1Cartesian.md) & | [**operator/=**](#function-operator_12) (const Unitless & divisor) <br>_Divides the_ [_**Cartesian**_](classastrea_1_1astro_1_1Cartesian.md) _state vector by a scalar._ |
|  [**Cartesian**](classastrea_1_1astro_1_1Cartesian.md) & | [**operator=**](#function-operator_13) ([**Cartesian**](classastrea_1_1astro_1_1Cartesian.md)&lt; \_frame\_ &gt; && other) noexcept<br>_Move assignment operator for_ [_**Cartesian**_](classastrea_1_1astro_1_1Cartesian.md) _._ |
|  [**Cartesian**](classastrea_1_1astro_1_1Cartesian.md) & | [**operator=**](#function-operator_14) (const [**Cartesian**](classastrea_1_1astro_1_1Cartesian.md)&lt; \_frame\_ &gt; & other) <br>_Copy assignment operator for_ [_**Cartesian**_](classastrea_1_1astro_1_1Cartesian.md) _._ |
|  bool | [**operator==**](#function-operator_15) (const [**Cartesian**](classastrea_1_1astro_1_1Cartesian.md)&lt; \_frame\_ &gt; & other) const<br>_Compares two_ [_**Cartesian**_](classastrea_1_1astro_1_1Cartesian.md) _objects for equality._ |
|   | [**~Cartesian**](#function-cartesian) () = default<br>_Default destructor for_ [_**Cartesian**_](classastrea_1_1astro_1_1Cartesian.md) _._ |


## Public Static Functions

| Type | Name |
| ---: | :--- |
|  [**Cartesian**](classastrea_1_1astro_1_1Cartesian.md) | [**GEO**](#function-geo) (const GravParam & mu) <br>_A static method to create_ [_**Cartesian**_](classastrea_1_1astro_1_1Cartesian.md) _state vectors for a GEO orbit._ |
|  [**Cartesian**](classastrea_1_1astro_1_1Cartesian.md) | [**GPS**](#function-gps) (const GravParam & mu) <br>_A static method to create_ [_**Cartesian**_](classastrea_1_1astro_1_1Cartesian.md) _state vectors for a GPS orbit._ |
|  [**Cartesian**](classastrea_1_1astro_1_1Cartesian.md) | [**HMEO**](#function-hmeo) (const GravParam & mu) <br>_A static method to create_ [_**Cartesian**_](classastrea_1_1astro_1_1Cartesian.md) _state vectors for a HMEO orbit._ |
|  [**Cartesian**](classastrea_1_1astro_1_1Cartesian.md) | [**LEO**](#function-leo) (const GravParam & mu) <br>_A static method to create_ [_**Cartesian**_](classastrea_1_1astro_1_1Cartesian.md) _state vectors for a LEO orbit._ |
|  [**Cartesian**](classastrea_1_1astro_1_1Cartesian.md) | [**LMEO**](#function-lmeo) (const GravParam & mu) <br>_A static method to create_ [_**Cartesian**_](classastrea_1_1astro_1_1Cartesian.md) _state vectors for a LMEO orbit._ |


























## Detailed Description


This class encapsulates the position and velocity of a vehicle in [**Cartesian**](classastrea_1_1astro_1_1Cartesian.md) coordinates. 


    
## Public Types Documentation




### typedef BaseType 

```C++
using astrea::astro::Cartesian< _frame_ >::BaseType =  Cartesian<F>;
```




<hr>
## Public Static Attributes Documentation




### variable frame 

_The reference frame of the_ [_**Cartesian**_](classastrea_1_1astro_1_1Cartesian.md) _state vector._
```C++
constexpr auto astrea::astro::Cartesian< _frame_ >::frame;
```




<hr>
## Public Functions Documentation




### function Cartesian [1/8]

_Default constructor for_ [_**Cartesian**_](classastrea_1_1astro_1_1Cartesian.md) _._
```C++
inline astrea::astro::Cartesian::Cartesian (
    Unitless scale=0.0 *astrea::detail::unitless
) 
```



Initializes the [**Cartesian**](classastrea_1_1astro_1_1Cartesian.md) state vector with zero values. 


        

<hr>



### function Cartesian [2/8]

_Constructor for_ [_**Cartesian**_](classastrea_1_1astro_1_1Cartesian.md) _with position and velocity vectors._
```C++
inline astrea::astro::Cartesian::Cartesian (
    const RadiusVector < _frame_ > & r,
    const VelocityVector < _frame_ > & v
) 
```





**Parameters:**


* `r` Radius vector (position) 
* `v` Velocity vector 




        

<hr>



### function Cartesian [3/8]

_Constructor for_ [_**Cartesian**_](classastrea_1_1astro_1_1Cartesian.md) _with individual position and velocity components._
```C++
inline astrea::astro::Cartesian::Cartesian (
    const Distance & x,
    const Distance & y,
    const Distance & z,
    const Velocity & vx,
    const Velocity & vy,
    const Velocity & vz
) 
```





**Parameters:**


* `x` X component of position 
* `y` Y component of position 
* `z` Z component of position 
* `vx` X component of velocity 
* `vy` Y component of velocity 
* `vz` Z component of velocity 




        

<hr>



### function Cartesian [4/8]

_Constructor for_ [_**Cartesian**_](classastrea_1_1astro_1_1Cartesian.md) _from another_[_**Cartesian**_](classastrea_1_1astro_1_1Cartesian.md) _object._
```C++
inline astrea::astro::Cartesian::Cartesian (
    const Cartesian & elements,
    const GravParam & mu
) 
```





**Parameters:**


* `elements` Another [**Cartesian**](classastrea_1_1astro_1_1Cartesian.md) object 
* `sys` Astrodynamics system containing celestial body data 




        

<hr>



### function Cartesian [5/8]

_Constructor for_ [_**Cartesian**_](classastrea_1_1astro_1_1Cartesian.md) _from_[_**Keplerian**_](classastrea_1_1astro_1_1Keplerian.md) _elements._
```C++
astrea::astro::Cartesian::Cartesian (
    const Keplerian < _frame_ > & elements,
    const GravParam & mu
) 
```





**Parameters:**


* `elements` [**Keplerian**](classastrea_1_1astro_1_1Keplerian.md) elements 
* `sys` Astrodynamics system containing celestial body data 




        

<hr>



### function Cartesian [6/8]

_Constructor for_ [_**Cartesian**_](classastrea_1_1astro_1_1Cartesian.md) _from_[_**Equinoctial**_](classastrea_1_1astro_1_1Equinoctial.md) _elements._
```C++
astrea::astro::Cartesian::Cartesian (
    const Equinoctial < _frame_ > & elements,
    const GravParam & mu
) 
```





**Parameters:**


* `elements` [**Equinoctial**](classastrea_1_1astro_1_1Equinoctial.md) elements 
* `sys` Astrodynamics system containing celestial body data 




        

<hr>



### function Cartesian [7/8]

_Copy constructor for_ [_**Cartesian**_](classastrea_1_1astro_1_1Cartesian.md) _._
```C++
astrea::astro::Cartesian::Cartesian (
    const Cartesian < _frame_ > & other
) 
```





**Parameters:**


* `other` Another [**Cartesian**](classastrea_1_1astro_1_1Cartesian.md) object 




        

<hr>



### function Cartesian [8/8]

_Move constructor for_ [_**Cartesian**_](classastrea_1_1astro_1_1Cartesian.md) _._
```C++
astrea::astro::Cartesian::Cartesian (
    Cartesian < _frame_ > &&
) noexcept
```





**Parameters:**


* `other` Another [**Cartesian**](classastrea_1_1astro_1_1Cartesian.md) object 




        

<hr>



### function force\_to\_double\_vector 

_Converts the_ [_**Cartesian**_](classastrea_1_1astro_1_1Cartesian.md) _state vector to a vector of unitless values._
```C++
std::vector< double > astrea::astro::Cartesian::force_to_double_vector () const
```





**Returns:**

std::vector&lt;Unitless&gt; Vector containing the x, y, z, vx, vy, and vz components of the [**Cartesian**](classastrea_1_1astro_1_1Cartesian.md) state vector. 





        

<hr>



### function get\_position 

_Converts the_ [_**Cartesian**_](classastrea_1_1astro_1_1Cartesian.md) _state vector to a RadiusVector&lt;__frame_ _&gt;._
```C++
inline const RadiusVector < _frame_ > & astrea::astro::Cartesian::get_position () const
```





**Returns:**

RadiusVector&lt;_frame_&gt; The position vector in [**Cartesian**](classastrea_1_1astro_1_1Cartesian.md) coordinates. 





        

<hr>



### function get\_velocity 

_Converts the_ [_**Cartesian**_](classastrea_1_1astro_1_1Cartesian.md) _state vector to a VelocityVector&lt;__frame_ _&gt;._
```C++
inline const VelocityVector < _frame_ > & astrea::astro::Cartesian::get_velocity () const
```





**Returns:**

VelocityVector&lt;_frame_&gt; The velocity vector in [**Cartesian**](classastrea_1_1astro_1_1Cartesian.md) coordinates. 





        

<hr>



### function get\_vx 

_Get the vx value of the_ [_**Cartesian**_](classastrea_1_1astro_1_1Cartesian.md) _state vector._
```C++
inline const Velocity & astrea::astro::Cartesian::get_vx () const
```





**Returns:**

const Velocity& Reference to the vx component of the [**Cartesian**](classastrea_1_1astro_1_1Cartesian.md) state vector. 





        

<hr>



### function get\_vy 

_Get the vy value of the_ [_**Cartesian**_](classastrea_1_1astro_1_1Cartesian.md) _state vector._
```C++
inline const Velocity & astrea::astro::Cartesian::get_vy () const
```





**Returns:**

const Velocity& Reference to the vy component of the [**Cartesian**](classastrea_1_1astro_1_1Cartesian.md) state vector. 





        

<hr>



### function get\_vz 

_Get the vz value of the_ [_**Cartesian**_](classastrea_1_1astro_1_1Cartesian.md) _state vector._
```C++
inline const Velocity & astrea::astro::Cartesian::get_vz () const
```





**Returns:**

const Velocity& Reference to the vz component of the [**Cartesian**](classastrea_1_1astro_1_1Cartesian.md) state vector. 





        

<hr>



### function get\_x 

_Get the x value of the_ [_**Cartesian**_](classastrea_1_1astro_1_1Cartesian.md) _state vector._
```C++
inline const Distance & astrea::astro::Cartesian::get_x () const
```





**Returns:**

const Distance& Reference to the x component of the [**Cartesian**](classastrea_1_1astro_1_1Cartesian.md) state vector. 





        

<hr>



### function get\_y 

_Get the y value of the_ [_**Cartesian**_](classastrea_1_1astro_1_1Cartesian.md) _state vector._
```C++
inline const Distance & astrea::astro::Cartesian::get_y () const
```





**Returns:**

const Distance& Reference to the y component of the [**Cartesian**](classastrea_1_1astro_1_1Cartesian.md) state vector. 





        

<hr>



### function get\_z 

_Get the z value of the_ [_**Cartesian**_](classastrea_1_1astro_1_1Cartesian.md) _state vector._
```C++
inline const Distance & astrea::astro::Cartesian::get_z () const
```





**Returns:**

const Distance& Reference to the z component of the [**Cartesian**](classastrea_1_1astro_1_1Cartesian.md) state vector. 





        

<hr>



### function in\_frame [1/2]

_Converts this_ [_**Cartesian**_](classastrea_1_1astro_1_1Cartesian.md) _state to an equivalent_[_**Cartesian**_](classastrea_1_1astro_1_1Cartesian.md) _state in a different frame._
```C++
template<IsFrame auto target_frame>
inline Cartesian < target_frame > astrea::astro::Cartesian::in_frame (
    const Date & epoch
) const
```



Uses proper physical frame transformation (translation and rotation) via in\_frame on each component vector. The gravitational parameter is accepted but not used; it exists so that [**Cartesian**](classastrea_1_1astro_1_1Cartesian.md) shares a uniform in\_frame(epoch, mu) signature with [**Keplerian**](classastrea_1_1astro_1_1Keplerian.md) and [**Equinoctial**](classastrea_1_1astro_1_1Equinoctial.md).




**Template parameters:**


* `target_frame` The target frame. 



**Parameters:**


* `epoch` The epoch at which to evaluate the frame transformation. 



**Returns:**

Cartesian&lt;target\_frame&gt; This state expressed in the target frame. 





        

<hr>



### function in\_frame [2/2]

```C++
template<IsFrame auto target_frame>
inline Cartesian < target_frame > astrea::astro::Cartesian::in_frame (
    const Date & epoch,
    const GravParam &
) const
```




<hr>



### function interpolate 

_Interpolates between two_ [_**Cartesian**_](classastrea_1_1astro_1_1Cartesian.md) _states at a given time._
```C++
Cartesian astrea::astro::Cartesian::interpolate (
    const Time & thisTime,
    const Time & otherTime,
    const Cartesian < _frame_ > & other,
    const GravParam & mu,
    const Time & targetTime
) const
```





**Parameters:**


* `thisTime` Time of the current state 
* `otherTime` Time of the other state 
* `other` Other [**Cartesian**](classastrea_1_1astro_1_1Cartesian.md) state to interpolate with 
* `mu` Gravitational parameter of the central body 
* `targetTime` Target time for interpolation 



**Returns:**

[**Cartesian**](classastrea_1_1astro_1_1Cartesian.md) Interpolated [**Cartesian**](classastrea_1_1astro_1_1Cartesian.md) state at the target time. 





        

<hr>



### function operator!= 

_Compares two_ [_**Cartesian**_](classastrea_1_1astro_1_1Cartesian.md) _objects for inequality._
```C++
bool astrea::astro::Cartesian::operator!= (
    const Cartesian < _frame_ > & other
) const
```





**Parameters:**


* `other` Another [**Cartesian**](classastrea_1_1astro_1_1Cartesian.md) object 



**Returns:**

true if the two [**Cartesian**](classastrea_1_1astro_1_1Cartesian.md) objects are not equal 




**Returns:**

false if the two [**Cartesian**](classastrea_1_1astro_1_1Cartesian.md) objects are equal 





        

<hr>



### function operator\* 

_Multiplies the_ [_**Cartesian**_](classastrea_1_1astro_1_1Cartesian.md) _state vector by a scalar._
```C++
Cartesian astrea::astro::Cartesian::operator* (
    const Unitless & multiplier
) const
```





**Parameters:**


* `multiplier` Scalar value to multiply with 



**Returns:**

Resultant [**Cartesian**](classastrea_1_1astro_1_1Cartesian.md) after multiplication. 





        

<hr>



### function operator\*= 

_Multiplies the_ [_**Cartesian**_](classastrea_1_1astro_1_1Cartesian.md) _state vector by a scalar._
```C++
Cartesian & astrea::astro::Cartesian::operator*= (
    const Unitless & multiplier
) 
```





**Parameters:**


* `multiplier` Scalar value to multiply with 



**Returns:**

Reference to the current [**Cartesian**](classastrea_1_1astro_1_1Cartesian.md) object after multiplication. 





        

<hr>



### function operator+ 

_Adds two_ [_**Cartesian**_](classastrea_1_1astro_1_1Cartesian.md) _objects._
```C++
Cartesian astrea::astro::Cartesian::operator+ (
    const Cartesian < _frame_ > & other
) const
```





**Parameters:**


* `other` Another [**Cartesian**](classastrea_1_1astro_1_1Cartesian.md) object 



**Returns:**

Resultant [**Cartesian**](classastrea_1_1astro_1_1Cartesian.md) sum. 





        

<hr>



### function operator+ 

```C++
Cartesian astrea::astro::Cartesian::operator+ (
    const RadiusVector < _frame_ > & r
) const
```




<hr>



### function operator+ 

```C++
Cartesian astrea::astro::Cartesian::operator+ (
    const VelocityVector < _frame_ > & v
) const
```




<hr>



### function operator+= 

_Adds another_ [_**Cartesian**_](classastrea_1_1astro_1_1Cartesian.md) _object to the current one._
```C++
Cartesian & astrea::astro::Cartesian::operator+= (
    const Cartesian < _frame_ > & other
) 
```





**Parameters:**


* `other` Another [**Cartesian**](classastrea_1_1astro_1_1Cartesian.md) object 



**Returns:**

Reference to the current [**Cartesian**](classastrea_1_1astro_1_1Cartesian.md) object after addition. 





        

<hr>



### function operator+= 

```C++
Cartesian & astrea::astro::Cartesian::operator+= (
    const RadiusVector < _frame_ > & r
) 
```




<hr>



### function operator+= 

```C++
Cartesian & astrea::astro::Cartesian::operator+= (
    const VelocityVector < _frame_ > & v
) 
```




<hr>



### function operator- 

_Subtracts another_ [_**Cartesian**_](classastrea_1_1astro_1_1Cartesian.md) _object from the current one._
```C++
Cartesian astrea::astro::Cartesian::operator- (
    const Cartesian < _frame_ > & other
) const
```





**Parameters:**


* `other` Another [**Cartesian**](classastrea_1_1astro_1_1Cartesian.md) object 



**Returns:**

Resultant [**Cartesian**](classastrea_1_1astro_1_1Cartesian.md) difference. 





        

<hr>



### function operator- 

```C++
Cartesian astrea::astro::Cartesian::operator- (
    const RadiusVector < _frame_ > & r
) const
```




<hr>



### function operator- 

```C++
Cartesian astrea::astro::Cartesian::operator- (
    const VelocityVector < _frame_ > & v
) const
```




<hr>



### function operator-= 

_Subtracts another_ [_**Cartesian**_](classastrea_1_1astro_1_1Cartesian.md) _object from the current one._
```C++
Cartesian & astrea::astro::Cartesian::operator-= (
    const Cartesian < _frame_ > & other
) 
```





**Parameters:**


* `other` Another [**Cartesian**](classastrea_1_1astro_1_1Cartesian.md) object 



**Returns:**

Reference to the current [**Cartesian**](classastrea_1_1astro_1_1Cartesian.md) object after subtraction. 





        

<hr>



### function operator-= 

```C++
Cartesian & astrea::astro::Cartesian::operator-= (
    const RadiusVector < _frame_ > & r
) 
```




<hr>



### function operator-= 

```C++
Cartesian & astrea::astro::Cartesian::operator-= (
    const VelocityVector < _frame_ > & v
) 
```




<hr>



### function operator/ 

_Divides the_ [_**Cartesian**_](classastrea_1_1astro_1_1Cartesian.md) _state vector by a time._
```C++
CartesianPartial < _frame_ > astrea::astro::Cartesian::operator/ (
    const Time & time
) const
```





**Parameters:**


* `time` Time value to divide by 



**Returns:**

Resultant [**CartesianPartial**](classastrea_1_1astro_1_1CartesianPartial.md) after division. 





        

<hr>



### function operator/ 

_Divides the_ [_**Cartesian**_](classastrea_1_1astro_1_1Cartesian.md) _state vector by another_[_**Cartesian**_](classastrea_1_1astro_1_1Cartesian.md) _object._
```C++
std::vector< Unitless > astrea::astro::Cartesian::operator/ (
    const Cartesian < _frame_ > & other
) const
```





**Parameters:**


* `other` Another [**Cartesian**](classastrea_1_1astro_1_1Cartesian.md) object 



**Returns:**

Resultant vector of unitless values after division. 





        

<hr>



### function operator/ 

_Divides the_ [_**Cartesian**_](classastrea_1_1astro_1_1Cartesian.md) _state vector by a scalar._
```C++
Cartesian astrea::astro::Cartesian::operator/ (
    const Unitless & divisor
) const
```





**Parameters:**


* `divisor` Scalar value to divide with 



**Returns:**

Resultant [**Cartesian**](classastrea_1_1astro_1_1Cartesian.md) after division. 





        

<hr>



### function operator/= 

_Divides the_ [_**Cartesian**_](classastrea_1_1astro_1_1Cartesian.md) _state vector by a scalar._
```C++
Cartesian & astrea::astro::Cartesian::operator/= (
    const Unitless & divisor
) 
```





**Parameters:**


* `divisor` Scalar value to divide with 



**Returns:**

Reference to the current [**Cartesian**](classastrea_1_1astro_1_1Cartesian.md) object after division. 





        

<hr>



### function operator= 

_Move assignment operator for_ [_**Cartesian**_](classastrea_1_1astro_1_1Cartesian.md) _._
```C++
Cartesian & astrea::astro::Cartesian::operator= (
    Cartesian < _frame_ > && other
) noexcept
```





**Parameters:**


* `other` Another [**Cartesian**](classastrea_1_1astro_1_1Cartesian.md) object 



**Returns:**

[**Cartesian**](classastrea_1_1astro_1_1Cartesian.md)& Reference to the current object 





        

<hr>



### function operator= 

_Copy assignment operator for_ [_**Cartesian**_](classastrea_1_1astro_1_1Cartesian.md) _._
```C++
Cartesian & astrea::astro::Cartesian::operator= (
    const Cartesian < _frame_ > & other
) 
```





**Parameters:**


* `other` Another [**Cartesian**](classastrea_1_1astro_1_1Cartesian.md) object 



**Returns:**

[**Cartesian**](classastrea_1_1astro_1_1Cartesian.md)& Reference to the current object 





        

<hr>



### function operator== 

_Compares two_ [_**Cartesian**_](classastrea_1_1astro_1_1Cartesian.md) _objects for equality._
```C++
bool astrea::astro::Cartesian::operator== (
    const Cartesian < _frame_ > & other
) const
```





**Parameters:**


* `other` Another [**Cartesian**](classastrea_1_1astro_1_1Cartesian.md) object 



**Returns:**

true if the two [**Cartesian**](classastrea_1_1astro_1_1Cartesian.md) objects are equal 




**Returns:**

false if the two [**Cartesian**](classastrea_1_1astro_1_1Cartesian.md) objects are not equal 





        

<hr>



### function ~Cartesian 

_Default destructor for_ [_**Cartesian**_](classastrea_1_1astro_1_1Cartesian.md) _._
```C++
astrea::astro::Cartesian::~Cartesian () = default
```




<hr>
## Public Static Functions Documentation




### function GEO 

_A static method to create_ [_**Cartesian**_](classastrea_1_1astro_1_1Cartesian.md) _state vectors for a GEO orbit._
```C++
static Cartesian astrea::astro::Cartesian::GEO (
    const GravParam & mu
) 
```



This method return predefined [**Cartesian**](classastrea_1_1astro_1_1Cartesian.md) state vectors for various types of orbits.




**Parameters:**


* `mu` Gravitational parameter of the central body 



**Returns:**

[**Cartesian**](classastrea_1_1astro_1_1Cartesian.md) Predefined [**Cartesian**](classastrea_1_1astro_1_1Cartesian.md) state vector for a GEO orbit. 





        

<hr>



### function GPS 

_A static method to create_ [_**Cartesian**_](classastrea_1_1astro_1_1Cartesian.md) _state vectors for a GPS orbit._
```C++
static Cartesian astrea::astro::Cartesian::GPS (
    const GravParam & mu
) 
```



This method return predefined [**Cartesian**](classastrea_1_1astro_1_1Cartesian.md) state vectors for various types of orbits.




**Parameters:**


* `mu` Gravitational parameter of the central body 



**Returns:**

[**Cartesian**](classastrea_1_1astro_1_1Cartesian.md) Predefined [**Cartesian**](classastrea_1_1astro_1_1Cartesian.md) state vector for a GPS orbit. 





        

<hr>



### function HMEO 

_A static method to create_ [_**Cartesian**_](classastrea_1_1astro_1_1Cartesian.md) _state vectors for a HMEO orbit._
```C++
static Cartesian astrea::astro::Cartesian::HMEO (
    const GravParam & mu
) 
```



This method return predefined [**Cartesian**](classastrea_1_1astro_1_1Cartesian.md) state vectors for various types of orbits.




**Parameters:**


* `mu` Gravitational parameter of the central body 



**Returns:**

[**Cartesian**](classastrea_1_1astro_1_1Cartesian.md) Predefined [**Cartesian**](classastrea_1_1astro_1_1Cartesian.md) state vector for a HMEO orbit. 





        

<hr>



### function LEO 

_A static method to create_ [_**Cartesian**_](classastrea_1_1astro_1_1Cartesian.md) _state vectors for a LEO orbit._
```C++
static Cartesian astrea::astro::Cartesian::LEO (
    const GravParam & mu
) 
```



This method return predefined [**Cartesian**](classastrea_1_1astro_1_1Cartesian.md) state vectors for various types of orbits.




**Parameters:**


* `mu` Gravitational parameter of the central body 



**Returns:**

[**Cartesian**](classastrea_1_1astro_1_1Cartesian.md) Predefined [**Cartesian**](classastrea_1_1astro_1_1Cartesian.md) state vector for a LEO orbit. 





        

<hr>



### function LMEO 

_A static method to create_ [_**Cartesian**_](classastrea_1_1astro_1_1Cartesian.md) _state vectors for a LMEO orbit._
```C++
static Cartesian astrea::astro::Cartesian::LMEO (
    const GravParam & mu
) 
```



This method return predefined [**Cartesian**](classastrea_1_1astro_1_1Cartesian.md) state vectors for various types of orbits.




**Parameters:**


* `mu` Gravitational parameter of the central body 



**Returns:**

[**Cartesian**](classastrea_1_1astro_1_1Cartesian.md) Predefined [**Cartesian**](classastrea_1_1astro_1_1Cartesian.md) state vector for a LMEO orbit. 





        

<hr>

------------------------------
The documentation for this class was generated from the following file `astrea/astro/astro/state/orbital_elements/Cartesian.hpp`

