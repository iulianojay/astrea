

# Struct astrea::astro::DynamicFrame

**template &lt;[**class**](classastrea_1_1astro_1_1CartesianVector.md) [**Frame\_T**](classastrea_1_1astro_1_1CartesianVector.md), [**FrameAxis**](namespaceastrea_1_1astro.md#enum-frameaxis) axis&gt;**



[**ClassList**](annotated.md) **>** [**astrea**](namespaceastrea.md) **>** [**astro**](namespaceastrea_1_1astro.md) **>** [**DynamicFrame**](classastrea_1_1astro_1_1DynamicFrame.md)



_Base class for all dynamic state/frames._ 

* `#include <DynamicFrame.hpp>`



Inherits the following classes: [astrea::astro::Frame](structastrea_1_1astro_1_1Frame.md)






















































## Public Functions

| Type | Name |
| ---: | :--- |
|  [**RadiusVector**](namespaceastrea_1_1astro.md#typedef-radiusvector)&lt; [**frames::earth::icrf**](structastrea_1_1astro_1_1InertialFrame.md) &gt; | [**convert\_from\_this\_frame**](#function-convert_from_this_frame) ([**const**](classastrea_1_1astro_1_1CartesianVector.md) [**RadiusVector**](namespaceastrea_1_1astro.md#typedef-radiusvector)&lt; [**Frame\_T**](classastrea_1_1astro_1_1CartesianVector.md) &gt; & vec, [**const**](classastrea_1_1astro_1_1CartesianVector.md) [**Date**](classastrea_1_1astro_1_1Date.md) & date) const<br>_Converts a_ [_**CartesianVector**_](classastrea_1_1astro_1_1CartesianVector.md) _from Frame\_T coordinates to Earth-Centered Inertial (ECI) coordinates._ |
|  [**RadiusVector**](namespaceastrea_1_1astro.md#typedef-radiusvector)&lt; [**Frame\_T**](classastrea_1_1astro_1_1CartesianVector.md) &gt; | [**convert\_to\_this\_frame**](#function-convert_to_this_frame) ([**const**](classastrea_1_1astro_1_1CartesianVector.md) [**RadiusVector**](namespaceastrea_1_1astro.md#typedef-radiusvector)&lt; [**frames::earth::icrf**](structastrea_1_1astro_1_1InertialFrame.md) &gt; & vec, [**const**](classastrea_1_1astro_1_1CartesianVector.md) [**Date**](classastrea_1_1astro_1_1Date.md) & date) const<br>_Converts a_ [_**CartesianVector**_](classastrea_1_1astro_1_1CartesianVector.md) _from Earth-Centered Inertial (ECI) to Frame\_T coordinates._ |
|  [**CartesianVector**](classastrea_1_1astro_1_1CartesianVector.md)&lt; [**Value\_T**](classastrea_1_1astro_1_1CartesianVector.md), [**Frame\_T**](classastrea_1_1astro_1_1CartesianVector.md) &gt; | [**rotate\_into\_this\_frame**](#function-rotate_into_this_frame) ([**const**](classastrea_1_1astro_1_1CartesianVector.md) [**CartesianVector**](classastrea_1_1astro_1_1CartesianVector.md)&lt; [**Value\_T**](classastrea_1_1astro_1_1CartesianVector.md), [**frames::earth::icrf**](structastrea_1_1astro_1_1InertialFrame.md) &gt; & vec, [**const**](classastrea_1_1astro_1_1CartesianVector.md) [**Date**](classastrea_1_1astro_1_1Date.md) & date) const<br>_Rotates a_ [_**CartesianVector**_](classastrea_1_1astro_1_1CartesianVector.md) _from Earth-Centered Inertial (ECI) to Frame\_T coordinates._ |
|  [**CartesianVector**](classastrea_1_1astro_1_1CartesianVector.md)&lt; [**Value\_T**](classastrea_1_1astro_1_1CartesianVector.md), [**frames::earth::icrf**](structastrea_1_1astro_1_1InertialFrame.md) &gt; | [**rotate\_out\_of\_this\_frame**](#function-rotate_out_of_this_frame) ([**const**](classastrea_1_1astro_1_1CartesianVector.md) [**CartesianVector**](classastrea_1_1astro_1_1CartesianVector.md)&lt; [**Value\_T**](classastrea_1_1astro_1_1CartesianVector.md), [**Frame\_T**](classastrea_1_1astro_1_1CartesianVector.md) &gt; & vec, [**const**](classastrea_1_1astro_1_1CartesianVector.md) [**Date**](classastrea_1_1astro_1_1Date.md) & date) const<br>_Rotates a_ [_**CartesianVector**_](classastrea_1_1astro_1_1CartesianVector.md) _from Frame\_T coordinates to Earth-Centered Inertial (ECI) coordinates._ |




## Public Static Functions

| Type | Name |
| ---: | :--- |
|  [**constexpr**](classastrea_1_1astro_1_1CartesianVector.md) [**FrameAxis**](namespaceastrea_1_1astro.md#enum-frameaxis) | [**get\_axis**](#function-get_axis) () <br>_Get the origin of the frame._  |
|  [**constexpr**](classastrea_1_1astro_1_1CartesianVector.md) [**CelestialBodyId**](namespaceastrea_1_1astro.md#enum-celestialbodyid) | [**get\_origin**](#function-get_origin) () <br>_Get the origin of the frame._  |
|  [**Frame\_T**](classastrea_1_1astro_1_1CartesianVector.md) | [**instantaneous**](#function-instantaneous) ([**const**](classastrea_1_1astro_1_1CartesianVector.md) [**RadiusVector**](namespaceastrea_1_1astro.md#typedef-radiusvector)&lt; [**frames::earth::icrf**](structastrea_1_1astro_1_1InertialFrame.md) &gt; & position, [**const**](classastrea_1_1astro_1_1CartesianVector.md) [**VelocityVector**](namespaceastrea_1_1astro.md#typedef-velocityvector)&lt; [**frames::earth::icrf**](structastrea_1_1astro_1_1InertialFrame.md) &gt; & velocity) <br>_Creates an instantaneous Frame\_T frame._  |


## Public Static Functions inherited from astrea::astro::Frame

See [astrea::astro::Frame](structastrea_1_1astro_1_1Frame.md)

| Type | Name |
| ---: | :--- |
|  [**constexpr**](classastrea_1_1astro_1_1CartesianVector.md) [**FrameAxis**](namespaceastrea_1_1astro.md#enum-frameaxis) | [**get\_axis**](structastrea_1_1astro_1_1Frame.md#function-get_axis) () <br>_Get the origin of the frame._  |
|  [**constexpr**](classastrea_1_1astro_1_1CartesianVector.md) [**CelestialBodyId**](namespaceastrea_1_1astro.md#enum-celestialbodyid) | [**get\_origin**](structastrea_1_1astro_1_1Frame.md#function-get_origin) () <br>_Get the origin of the frame._  |










## Protected Attributes

| Type | Name |
| ---: | :--- |
|  [**bool**](classastrea_1_1astro_1_1CartesianVector.md) | [**\_isInstantaneous**](#variable-_isinstantaneous)  <br>_Flag indicating if the frame is instantaneous._  |
|  [**const**](classastrea_1_1astro_1_1CartesianVector.md) [**FrameReference**](classastrea_1_1astro_1_1FrameReference.md) \* | [**\_parent**](#variable-_parent)  <br>_The parent object this frame is attached to._  |
|  [**RadiusVector**](namespaceastrea_1_1astro.md#typedef-radiusvector)&lt; [**frames::earth::icrf**](structastrea_1_1astro_1_1InertialFrame.md) &gt; | [**\_position**](#variable-_position)  <br>_The position vector in the ECI frame._  |
|  [**VelocityVector**](namespaceastrea_1_1astro.md#typedef-velocityvector)&lt; [**frames::earth::icrf**](structastrea_1_1astro_1_1InertialFrame.md) &gt; | [**\_velocity**](#variable-_velocity)  <br>_The velocity vector in the ECI frame._  |






## Protected Static Attributes inherited from astrea::astro::Frame

See [astrea::astro::Frame](structastrea_1_1astro_1_1Frame.md)

| Type | Name |
| ---: | :--- |
|  [**constexpr**](classastrea_1_1astro_1_1CartesianVector.md) [**FrameAxis**](namespaceastrea_1_1astro.md#enum-frameaxis) | [**\_axis**](structastrea_1_1astro_1_1Frame.md#variable-_axis)   = `[**axis**](classastrea_1_1astro_1_1CartesianVector.md)`<br>_The axis type of the inertial frame._  |
|  [**constexpr**](classastrea_1_1astro_1_1CartesianVector.md) [**CelestialBodyId**](namespaceastrea_1_1astro.md#enum-celestialbodyid) | [**\_origin**](structastrea_1_1astro_1_1Frame.md#variable-_origin)   = `[**origin**](classastrea_1_1astro_1_1CartesianVector.md)`<br>_The central body associated with the inertial frame._  |


























## Protected Functions

| Type | Name |
| ---: | :--- |
|   | [**DynamicFrame**](#function-dynamicframe-12) ([**const**](classastrea_1_1astro_1_1CartesianVector.md) [**FrameReference**](classastrea_1_1astro_1_1FrameReference.md) \* parent) <br>_Constructor for_ [_**DynamicFrame**_](classastrea_1_1astro_1_1DynamicFrame.md) _._ |
|   | [**DynamicFrame**](#function-dynamicframe-22) ([**const**](classastrea_1_1astro_1_1CartesianVector.md) [**RadiusVector**](namespaceastrea_1_1astro.md#typedef-radiusvector)&lt; [**frames::earth::icrf**](structastrea_1_1astro_1_1InertialFrame.md) &gt; & position, [**const**](classastrea_1_1astro_1_1CartesianVector.md) [**VelocityVector**](namespaceastrea_1_1astro.md#typedef-velocityvector)&lt; [**frames::earth::icrf**](structastrea_1_1astro_1_1InertialFrame.md) &gt; & velocity) <br>_Constructor for instantaneous dynamic state/frames._  |
|  [**RadiusVector**](namespaceastrea_1_1astro.md#typedef-radiusvector)&lt; [**frames::earth::icrf**](structastrea_1_1astro_1_1InertialFrame.md) &gt; | [**get\_inertial\_position**](#function-get_inertial_position) ([**const**](classastrea_1_1astro_1_1CartesianVector.md) [**Date**](classastrea_1_1astro_1_1Date.md) & date) const<br>_Gets the inertial position vector at a given date._  |
|  [**VelocityVector**](namespaceastrea_1_1astro.md#typedef-velocityvector)&lt; [**frames::earth::icrf**](structastrea_1_1astro_1_1InertialFrame.md) &gt; | [**get\_inertial\_velocity**](#function-get_inertial_velocity) ([**const**](classastrea_1_1astro_1_1CartesianVector.md) [**Date**](classastrea_1_1astro_1_1Date.md) & date) const<br>_Gets the inertial velocity vector at a given date._  |


## Protected Functions inherited from astrea::astro::Frame

See [astrea::astro::Frame](structastrea_1_1astro_1_1Frame.md)

| Type | Name |
| ---: | :--- |
| virtual  | [**~Frame**](structastrea_1_1astro_1_1Frame.md#function-frame) () = default<br>_Default destructor for_ [_**Frame**_](structastrea_1_1astro_1_1Frame.md) _._ |






## Public Functions Documentation




### function convert\_from\_this\_frame 

_Converts a_ [_**CartesianVector**_](classastrea_1_1astro_1_1CartesianVector.md) _from Frame\_T coordinates to Earth-Centered Inertial (ECI) coordinates._
```C++
inline RadiusVector < frames::earth::icrf > astrea::astro::DynamicFrame::convert_from_this_frame (
    const  RadiusVector < Frame_T > & vec,
    const  Date & date
) const
```





**Template parameters:**


* `Value_T` The type of the vector components. 



**Parameters:**


* `vec` The [**CartesianVector**](classastrea_1_1astro_1_1CartesianVector.md) in Frame\_T coordinates. 
* `date` The date for which the conversion is performed. 



**Returns:**

[**RadiusVector&lt;frames::earth::icrf&gt;**](namespaceastrea_1_1astro.md#typedef-radiusvector) The converted [**CartesianVector**](classastrea_1_1astro_1_1CartesianVector.md) in ECI coordinates. 





        

<hr>



### function convert\_to\_this\_frame 

_Converts a_ [_**CartesianVector**_](classastrea_1_1astro_1_1CartesianVector.md) _from Earth-Centered Inertial (ECI) to Frame\_T coordinates._
```C++
inline RadiusVector < Frame_T > astrea::astro::DynamicFrame::convert_to_this_frame (
    const  RadiusVector < frames::earth::icrf > & vec,
    const  Date & date
) const
```





**Template parameters:**


* `Value_T` The type of the vector components. 



**Parameters:**


* `vec` The [**CartesianVector**](classastrea_1_1astro_1_1CartesianVector.md) in ECI coordinates. 
* `date` The date for which the conversion is performed. 



**Returns:**

RadiusVector&lt;Frame\_T&gt; The converted [**CartesianVector**](classastrea_1_1astro_1_1CartesianVector.md) in Frame\_T coordinates. 





        

<hr>



### function rotate\_into\_this\_frame 

_Rotates a_ [_**CartesianVector**_](classastrea_1_1astro_1_1CartesianVector.md) _from Earth-Centered Inertial (ECI) to Frame\_T coordinates._
```C++
template<typename  Value_T>
inline CartesianVector < Value_T , Frame_T > astrea::astro::DynamicFrame::rotate_into_this_frame (
    const  CartesianVector < Value_T , frames::earth::icrf > & vec,
    const  Date & date
) const
```





**Template parameters:**


* `Value_T` The type of the vector components. 



**Parameters:**


* `vec` The [**CartesianVector**](classastrea_1_1astro_1_1CartesianVector.md) in ECI coordinates. 
* `date` The date for which the conversion is performed. 



**Returns:**

CartesianVector&lt;Value\_T, Frame\_T&gt; The rotated [**CartesianVector**](classastrea_1_1astro_1_1CartesianVector.md) in Frame\_T coordinates. 





        

<hr>



### function rotate\_out\_of\_this\_frame 

_Rotates a_ [_**CartesianVector**_](classastrea_1_1astro_1_1CartesianVector.md) _from Frame\_T coordinates to Earth-Centered Inertial (ECI) coordinates._
```C++
template<typename  Value_T>
inline CartesianVector < Value_T , frames::earth::icrf > astrea::astro::DynamicFrame::rotate_out_of_this_frame (
    const  CartesianVector < Value_T , Frame_T > & vec,
    const  Date & date
) const
```





**Template parameters:**


* `Value_T` The type of the vector components. 



**Parameters:**


* `vec` The [**CartesianVector**](classastrea_1_1astro_1_1CartesianVector.md) in Frame\_T coordinates. 
* `date` The date for which the conversion is performed. 



**Returns:**

CartesianVector&lt;Value\_T, frames::earth::icrf&gt; The rotated [**CartesianVector**](classastrea_1_1astro_1_1CartesianVector.md) in ECI coordinates. 





        

<hr>
## Public Static Functions Documentation




### function get\_axis 

_Get the origin of the frame._ 
```C++
static inline constexpr  FrameAxis astrea::astro::DynamicFrame::get_axis () 
```





**Returns:**

The origin of the frame. 





        

<hr>



### function get\_origin 

_Get the origin of the frame._ 
```C++
static inline constexpr  CelestialBodyId astrea::astro::DynamicFrame::get_origin () 
```





**Returns:**

The origin of the frame. 





        

<hr>



### function instantaneous 

_Creates an instantaneous Frame\_T frame._ 
```C++
static inline Frame_T astrea::astro::DynamicFrame::instantaneous (
    const  RadiusVector < frames::earth::icrf > & position,
    const  VelocityVector < frames::earth::icrf > & velocity
) 
```





**Parameters:**


* `position` The position vector in the ECI frame. 
* `velocity` The velocity vector in the ECI frame. 



**Returns:**

Frame\_T The instantaneous frame. 





        

<hr>
## Protected Attributes Documentation




### variable \_isInstantaneous 

_Flag indicating if the frame is instantaneous._ 
```C++
bool astrea::astro::DynamicFrame< Frame_T, axis >::_isInstantaneous;
```




<hr>



### variable \_parent 

_The parent object this frame is attached to._ 
```C++
const FrameReference* astrea::astro::DynamicFrame< Frame_T, axis >::_parent;
```




<hr>



### variable \_position 

_The position vector in the ECI frame._ 
```C++
RadiusVector<frames::earth::icrf> astrea::astro::DynamicFrame< Frame_T, axis >::_position;
```




<hr>



### variable \_velocity 

_The velocity vector in the ECI frame._ 
```C++
VelocityVector<frames::earth::icrf> astrea::astro::DynamicFrame< Frame_T, axis >::_velocity;
```




<hr>
## Protected Functions Documentation




### function DynamicFrame [1/2]

_Constructor for_ [_**DynamicFrame**_](classastrea_1_1astro_1_1DynamicFrame.md) _._
```C++
inline astrea::astro::DynamicFrame::DynamicFrame (
    const  FrameReference * parent
) 
```





**Parameters:**


* `name` The name of the dynamic frame. 
* `origin` The origin of the dynamic frame. 
* `parent` The parent inertial frame that this dynamic frame is based on. 




        

<hr>



### function DynamicFrame [2/2]

_Constructor for instantaneous dynamic state/frames._ 
```C++
inline astrea::astro::DynamicFrame::DynamicFrame (
    const  RadiusVector < frames::earth::icrf > & position,
    const  VelocityVector < frames::earth::icrf > & velocity
) 
```





**Parameters:**


* `name` The name of the dynamic frame. 
* `position` The position vector in the ECI frame. 
* `velocity` The velocity vector in the ECI frame. 




        

<hr>



### function get\_inertial\_position 

_Gets the inertial position vector at a given date._ 
```C++
inline RadiusVector < frames::earth::icrf > astrea::astro::DynamicFrame::get_inertial_position (
    const  Date & date
) const
```





**Parameters:**


* `date` The date for which the position is requested. 



**Returns:**

[**RadiusVector&lt;frames::earth::icrf&gt;**](namespaceastrea_1_1astro.md#typedef-radiusvector) The inertial position vector. 





        

<hr>



### function get\_inertial\_velocity 

_Gets the inertial velocity vector at a given date._ 
```C++
inline VelocityVector < frames::earth::icrf > astrea::astro::DynamicFrame::get_inertial_velocity (
    const  Date & date
) const
```





**Parameters:**


* `date` The date for which the velocity is requested. 



**Returns:**

[**VelocityVector&lt;frames::earth::icrf&gt;**](namespaceastrea_1_1astro.md#typedef-velocityvector) The inertial velocity vector. 





        

<hr>

------------------------------
The documentation for this class was generated from the following file `astrea/astro/astro/frames/types/DynamicFrame.hpp`

