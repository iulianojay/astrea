

# Struct astrea::astro::DynamicFrame

**template &lt;[**typename**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) [**Self**](classastrea_1_1astro_1_1DirectionCosineMatrix.md), IsFrame [**auto**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) \_parent\_, IsFrame [**auto**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) \_self\_&gt;**



[**ClassList**](annotated.md) **>** [**astrea**](namespaceastrea.md) **>** [**astro**](namespaceastrea_1_1astro.md) **>** [**DynamicFrame**](structastrea_1_1astro_1_1DynamicFrame.md)



_Base class for all dynamic state/frames._ 

* `#include <DynamicFrame.hpp>`























## Public Static Attributes

| Type | Name |
| ---: | :--- |
|  [**constexpr**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) [**auto**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) | [**parent**](#variable-parent)   = `[**\_parent\_**](classastrea_1_1astro_1_1DirectionCosineMatrix.md)`<br>_The reference frame of the dynamic frame._  |














## Public Functions

| Type | Name |
| ---: | :--- |
|  [**CartesianVector**](structastrea_1_1astro_1_1CartesianVector.md)&lt; [**Value\_T**](classastrea_1_1astro_1_1DirectionCosineMatrix.md), [**\_self\_**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) &gt; | [**rotate\_into\_this\_frame**](#function-rotate_into_this_frame) ([**const**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) [**CartesianVector**](structastrea_1_1astro_1_1CartesianVector.md)&lt; [**Value\_T**](classastrea_1_1astro_1_1DirectionCosineMatrix.md), [**parent**](structastrea_1_1astro_1_1DynamicFrame.md#variable-parent) &gt; & vec, [**const**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) [**Date**](classastrea_1_1astro_1_1Date.md) & date) const<br>_Rotates a_ [_**CartesianVector**_](structastrea_1_1astro_1_1CartesianVector.md) _from the parent frame to this frame's coordinates._ |
|  [**CartesianVector**](structastrea_1_1astro_1_1CartesianVector.md)&lt; [**Value\_T**](classastrea_1_1astro_1_1DirectionCosineMatrix.md), [**parent**](structastrea_1_1astro_1_1DynamicFrame.md#variable-parent) &gt; | [**rotate\_out\_of\_this\_frame**](#function-rotate_out_of_this_frame) ([**const**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) [**CartesianVector**](structastrea_1_1astro_1_1CartesianVector.md)&lt; [**Value\_T**](classastrea_1_1astro_1_1DirectionCosineMatrix.md), [**\_self\_**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) &gt; & vec, [**const**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) [**Date**](classastrea_1_1astro_1_1Date.md) & date) const<br>_Rotates a_ [_**CartesianVector**_](structastrea_1_1astro_1_1CartesianVector.md) _from this frame's coordinates to the parent frame coordinates._ |
|  [**RadiusVector**](namespaceastrea_1_1astro.md#typedef-radiusvector)&lt; [**parent**](structastrea_1_1astro_1_1DynamicFrame.md#variable-parent) &gt; | [**transform\_from\_this\_frame**](#function-transform_from_this_frame) ([**const**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) [**RadiusVector**](namespaceastrea_1_1astro.md#typedef-radiusvector)&lt; [**\_self\_**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) &gt; & vec, [**const**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) [**Date**](classastrea_1_1astro_1_1Date.md) & date) const<br>_Converts a_ [_**CartesianVector**_](structastrea_1_1astro_1_1CartesianVector.md) _from this frame's coordinates to the parent frame coordinates._ |
|  [**RadiusVector**](namespaceastrea_1_1astro.md#typedef-radiusvector)&lt; [**\_self\_**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) &gt; | [**transform\_to\_this\_frame**](#function-transform_to_this_frame) ([**const**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) [**RadiusVector**](namespaceastrea_1_1astro.md#typedef-radiusvector)&lt; [**parent**](structastrea_1_1astro_1_1DynamicFrame.md#variable-parent) &gt; & vec, [**const**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) [**Date**](classastrea_1_1astro_1_1Date.md) & date) const<br>_Converts a_ [_**CartesianVector**_](structastrea_1_1astro_1_1CartesianVector.md) _from the parent frame to this frame's coordinates._ |








## Protected Attributes

| Type | Name |
| ---: | :--- |
|  [**RadiusVector**](namespaceastrea_1_1astro.md#typedef-radiusvector)&lt; [**parent**](structastrea_1_1astro_1_1DynamicFrame.md#variable-parent) &gt; | [**\_position**](#variable-_position)  <br>_The position vector._  |
|  [**VelocityVector**](namespaceastrea_1_1astro.md#typedef-velocityvector)&lt; [**parent**](structastrea_1_1astro_1_1DynamicFrame.md#variable-parent) &gt; | [**\_velocity**](#variable-_velocity)  <br>_The velocity vector._  |
















## Protected Functions

| Type | Name |
| ---: | :--- |
|   | [**DynamicFrame**](#function-dynamicframe) ([**const**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) [**RadiusVector**](namespaceastrea_1_1astro.md#typedef-radiusvector)&lt; [**\_parent\_**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) &gt; & position, [**const**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) [**VelocityVector**](namespaceastrea_1_1astro.md#typedef-velocityvector)&lt; [**\_parent\_**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) &gt; & velocity) <br>_Constructor for instantaneous dynamic state/frames._  |
|  [**RadiusVector**](namespaceastrea_1_1astro.md#typedef-radiusvector)&lt; [**parent**](structastrea_1_1astro_1_1DynamicFrame.md#variable-parent) &gt; | [**get\_position**](#function-get_position) ([**const**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) [**Date**](classastrea_1_1astro_1_1Date.md) & date) const<br>_Gets the inertial position vector at a given date._  |
|  [**VelocityVector**](namespaceastrea_1_1astro.md#typedef-velocityvector)&lt; [**parent**](structastrea_1_1astro_1_1DynamicFrame.md#variable-parent) &gt; | [**get\_velocity**](#function-get_velocity) ([**const**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) [**Date**](classastrea_1_1astro_1_1Date.md) & date) const<br>_Gets the inertial velocity vector at a given date._  |




## Public Static Attributes Documentation




### variable parent 

_The reference frame of the dynamic frame._ 
```C++
constexpr auto astrea::astro::DynamicFrame< Self, _parent_, _self_ >::parent;
```




<hr>
## Public Functions Documentation




### function rotate\_into\_this\_frame 

_Rotates a_ [_**CartesianVector**_](structastrea_1_1astro_1_1CartesianVector.md) _from the parent frame to this frame's coordinates._
```C++
template<typename  Value_T>
inline CartesianVector < Value_T , _self_ > astrea::astro::DynamicFrame::rotate_into_this_frame (
    const  CartesianVector < Value_T , parent > & vec,
    const  Date & date
) const
```





**Template parameters:**


* `Value_T` The type of the vector components. 



**Parameters:**


* `vec` The [**CartesianVector**](structastrea_1_1astro_1_1CartesianVector.md) in parent coordinates. 
* `date` The date for which the conversion is performed. 



**Returns:**

[**CartesianVector**](structastrea_1_1astro_1_1CartesianVector.md)&lt;Value\_T, _self_&gt; The rotated [**CartesianVector**](structastrea_1_1astro_1_1CartesianVector.md) in this frame's coordinates. 





        

<hr>



### function rotate\_out\_of\_this\_frame 

_Rotates a_ [_**CartesianVector**_](structastrea_1_1astro_1_1CartesianVector.md) _from this frame's coordinates to the parent frame coordinates._
```C++
template<typename  Value_T>
inline CartesianVector < Value_T , parent > astrea::astro::DynamicFrame::rotate_out_of_this_frame (
    const  CartesianVector < Value_T , _self_ > & vec,
    const  Date & date
) const
```





**Template parameters:**


* `Value_T` The type of the vector components. 



**Parameters:**


* `vec` The [**CartesianVector**](structastrea_1_1astro_1_1CartesianVector.md) in this frame's coordinates. 
* `date` The date for which the conversion is performed. 



**Returns:**

CartesianVector&lt;Value\_T, parent&gt; The rotated [**CartesianVector**](structastrea_1_1astro_1_1CartesianVector.md) in parent coordinates. 





        

<hr>



### function transform\_from\_this\_frame 

_Converts a_ [_**CartesianVector**_](structastrea_1_1astro_1_1CartesianVector.md) _from this frame's coordinates to the parent frame coordinates._
```C++
inline RadiusVector < parent > astrea::astro::DynamicFrame::transform_from_this_frame (
    const  RadiusVector < _self_ > & vec,
    const  Date & date
) const
```





**Template parameters:**


* `Value_T` The type of the vector components. 



**Parameters:**


* `vec` The [**CartesianVector**](structastrea_1_1astro_1_1CartesianVector.md) in this frame's coordinates. 
* `date` The date for which the conversion is performed. 



**Returns:**

RadiusVector&lt;parent&gt; The converted [**CartesianVector**](structastrea_1_1astro_1_1CartesianVector.md) in parent coordinates. 





        

<hr>



### function transform\_to\_this\_frame 

_Converts a_ [_**CartesianVector**_](structastrea_1_1astro_1_1CartesianVector.md) _from the parent frame to this frame's coordinates._
```C++
inline RadiusVector < _self_ > astrea::astro::DynamicFrame::transform_to_this_frame (
    const  RadiusVector < parent > & vec,
    const  Date & date
) const
```





**Template parameters:**


* `Value_T` The type of the vector components. 



**Parameters:**


* `vec` The [**CartesianVector**](structastrea_1_1astro_1_1CartesianVector.md) in parent coordinates. 
* `date` The date for which the conversion is performed. 



**Returns:**

RadiusVector&lt;_self_&gt; The converted [**CartesianVector**](structastrea_1_1astro_1_1CartesianVector.md) in this frame's coordinates. 





        

<hr>
## Protected Attributes Documentation




### variable \_position 

_The position vector._ 
```C++
RadiusVector<parent> astrea::astro::DynamicFrame< Self, _parent_, _self_ >::_position;
```




<hr>



### variable \_velocity 

_The velocity vector._ 
```C++
VelocityVector<parent> astrea::astro::DynamicFrame< Self, _parent_, _self_ >::_velocity;
```




<hr>
## Protected Functions Documentation




### function DynamicFrame 

_Constructor for instantaneous dynamic state/frames._ 
```C++
inline astrea::astro::DynamicFrame::DynamicFrame (
    const  RadiusVector < _parent_ > & position,
    const  VelocityVector < _parent_ > & velocity
) 
```





**Parameters:**


* `name` The name of the dynamic frame. 
* `position` The position vector in the parent frame. 
* `velocity` The velocity vector in the parent frame. 




        

<hr>



### function get\_position 

_Gets the inertial position vector at a given date._ 
```C++
inline RadiusVector < parent > astrea::astro::DynamicFrame::get_position (
    const  Date & date
) const
```





**Parameters:**


* `date` The date for which the position is requested. 



**Returns:**

RadiusVector&lt;parent&gt; The inertial position vector. 





        

<hr>



### function get\_velocity 

_Gets the inertial velocity vector at a given date._ 
```C++
inline VelocityVector < parent > astrea::astro::DynamicFrame::get_velocity (
    const  Date & date
) const
```





**Parameters:**


* `date` The date for which the velocity is requested. 



**Returns:**

VelocityVector&lt;parent&gt; The inertial velocity vector. 





        

<hr>

------------------------------
The documentation for this class was generated from the following file `astrea/astro/astro/frames/framework/DynamicFrame.hpp`

