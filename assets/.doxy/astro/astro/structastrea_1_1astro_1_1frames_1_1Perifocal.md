

# Struct astrea::astro::frames::Perifocal

**template &lt;IsFrame auto \_parent\_&gt;**



[**ClassList**](annotated.md) **>** [**astrea**](namespaceastrea.md) **>** [**astro**](namespaceastrea_1_1astro.md) **>** [**frames**](namespaceastrea_1_1astro_1_1frames.md) **>** [**Perifocal**](structastrea_1_1astro_1_1frames_1_1Perifocal.md)



_Class representing the_ [_**Perifocal**_](structastrea_1_1astro_1_1frames_1_1Perifocal.md) _(PQW) frame: P towards periapsis, W along the angular momentum vector, and Q completing the right-handed triad in the orbital plane._[More...](#detailed-description)

* `#include <Perifocal.hpp>`



Inherits the following classes: [astrea::astro::DynamicFrame](structastrea_1_1astro_1_1DynamicFrame.md)














## Public Types

| Type | Name |
| ---: | :--- |
| typedef [**PerifocalTag**](structastrea_1_1astro_1_1frames_1_1PerifocalTag.md)&lt; \_parent\_ &gt; | [**tag\_type**](#typedef-tag_type)  <br>_Tag type for this frame._  |












## Public Static Attributes

| Type | Name |
| ---: | :--- |
|  constexpr auto | [**parent**](#variable-parent)   = `\_parent\_`<br>_The reference frame of the_ [_**Perifocal**_](structastrea_1_1astro_1_1frames_1_1Perifocal.md) _frame._ |
|  constexpr [**tag\_type**](structastrea_1_1astro_1_1frames_1_1Perifocal.md#typedef-tag_type) | [**tag**](#variable-tag)   = `{}`<br>_Empty frame tag satisfying IsFrame._  |


## Public Static Attributes inherited from astrea::astro::DynamicFrame

See [astrea::astro::DynamicFrame](structastrea_1_1astro_1_1DynamicFrame.md)

| Type | Name |
| ---: | :--- |
|  constexpr auto | [**parent**](structastrea_1_1astro_1_1DynamicFrame.md#variable-parent)   = `\_parent\_`<br>_The reference frame of the dynamic frame._  |


























## Public Functions

| Type | Name |
| ---: | :--- |
|   | [**Perifocal**](#function-perifocal-12) (const [**RadiusVector**](namespaceastrea_1_1astro.md#typedef-radiusvector)&lt; [**parent**](structastrea_1_1astro_1_1frames_1_1Perifocal.md#variable-parent) &gt; & position, const [**VelocityVector**](namespaceastrea_1_1astro.md#typedef-velocityvector)&lt; [**parent**](structastrea_1_1astro_1_1frames_1_1Perifocal.md#variable-parent) &gt; & velocity) <br>_Constructor for the_ [_**Perifocal**_](structastrea_1_1astro_1_1frames_1_1Perifocal.md) _frame from position, velocity, and gravitational parameter._ |
|   | [**Perifocal**](#function-perifocal-22) () = delete<br>_Default constructor is deleted to prevent instantiation without a parent frame._  |
|  [**DirectionCosineMatrix**](classastrea_1_1astro_1_1DirectionCosineMatrix.md)&lt; [**parent**](structastrea_1_1astro_1_1frames_1_1Perifocal.md#variable-parent), [**tag**](structastrea_1_1astro_1_1frames_1_1Perifocal.md#variable-tag) &gt; | [**get\_dcm**](#function-get_dcm) (const [**Date**](classastrea_1_1astro_1_1Date.md) & date) const<br>_Gets the Direction Cosine Matrix (DCM) for the_ [_**Perifocal**_](structastrea_1_1astro_1_1frames_1_1Perifocal.md) _frame at a given date._ |


## Public Functions inherited from astrea::astro::DynamicFrame

See [astrea::astro::DynamicFrame](structastrea_1_1astro_1_1DynamicFrame.md)

| Type | Name |
| ---: | :--- |
|  [**CartesianVector**](structastrea_1_1astro_1_1CartesianVector.md)&lt; Value\_T, \_self\_ &gt; | [**rotate\_into\_this\_frame**](structastrea_1_1astro_1_1DynamicFrame.md#function-rotate_into_this_frame) (const [**CartesianVector**](structastrea_1_1astro_1_1CartesianVector.md)&lt; Value\_T, [**parent**](structastrea_1_1astro_1_1DynamicFrame.md#variable-parent) &gt; & vec, const [**Date**](classastrea_1_1astro_1_1Date.md) & date) const<br>_Rotates a_ [_**CartesianVector**_](structastrea_1_1astro_1_1CartesianVector.md) _from the parent frame to this frame's coordinates._ |
|  [**CartesianVector**](structastrea_1_1astro_1_1CartesianVector.md)&lt; Value\_T, [**parent**](structastrea_1_1astro_1_1DynamicFrame.md#variable-parent) &gt; | [**rotate\_out\_of\_this\_frame**](structastrea_1_1astro_1_1DynamicFrame.md#function-rotate_out_of_this_frame) (const [**CartesianVector**](structastrea_1_1astro_1_1CartesianVector.md)&lt; Value\_T, \_self\_ &gt; & vec, const [**Date**](classastrea_1_1astro_1_1Date.md) & date) const<br>_Rotates a_ [_**CartesianVector**_](structastrea_1_1astro_1_1CartesianVector.md) _from this frame's coordinates to the parent frame coordinates._ |
|  [**RadiusVector**](namespaceastrea_1_1astro.md#typedef-radiusvector)&lt; [**parent**](structastrea_1_1astro_1_1DynamicFrame.md#variable-parent) &gt; | [**transform\_from\_this\_frame**](structastrea_1_1astro_1_1DynamicFrame.md#function-transform_from_this_frame) (const [**RadiusVector**](namespaceastrea_1_1astro.md#typedef-radiusvector)&lt; \_self\_ &gt; & vec, const [**Date**](classastrea_1_1astro_1_1Date.md) & date) const<br>_Converts a_ [_**CartesianVector**_](structastrea_1_1astro_1_1CartesianVector.md) _from this frame's coordinates to the parent frame coordinates._ |
|  [**RadiusVector**](namespaceastrea_1_1astro.md#typedef-radiusvector)&lt; \_self\_ &gt; | [**transform\_to\_this\_frame**](structastrea_1_1astro_1_1DynamicFrame.md#function-transform_to_this_frame) (const [**RadiusVector**](namespaceastrea_1_1astro.md#typedef-radiusvector)&lt; [**parent**](structastrea_1_1astro_1_1DynamicFrame.md#variable-parent) &gt; & vec, const [**Date**](classastrea_1_1astro_1_1Date.md) & date) const<br>_Converts a_ [_**CartesianVector**_](structastrea_1_1astro_1_1CartesianVector.md) _from the parent frame to this frame's coordinates._ |
















## Protected Attributes inherited from astrea::astro::DynamicFrame

See [astrea::astro::DynamicFrame](structastrea_1_1astro_1_1DynamicFrame.md)

| Type | Name |
| ---: | :--- |
|  [**RadiusVector**](namespaceastrea_1_1astro.md#typedef-radiusvector)&lt; [**parent**](structastrea_1_1astro_1_1DynamicFrame.md#variable-parent) &gt; | [**\_position**](structastrea_1_1astro_1_1DynamicFrame.md#variable-_position)  <br>_The position vector._  |
|  [**VelocityVector**](namespaceastrea_1_1astro.md#typedef-velocityvector)&lt; [**parent**](structastrea_1_1astro_1_1DynamicFrame.md#variable-parent) &gt; | [**\_velocity**](structastrea_1_1astro_1_1DynamicFrame.md#variable-_velocity)  <br>_The velocity vector._  |
































## Protected Functions inherited from astrea::astro::DynamicFrame

See [astrea::astro::DynamicFrame](structastrea_1_1astro_1_1DynamicFrame.md)

| Type | Name |
| ---: | :--- |
|   | [**DynamicFrame**](structastrea_1_1astro_1_1DynamicFrame.md#function-dynamicframe) (const [**RadiusVector**](namespaceastrea_1_1astro.md#typedef-radiusvector)&lt; \_parent\_ &gt; & position, const [**VelocityVector**](namespaceastrea_1_1astro.md#typedef-velocityvector)&lt; \_parent\_ &gt; & velocity) <br>_Constructor for instantaneous dynamic state/frames._  |
|  [**RadiusVector**](namespaceastrea_1_1astro.md#typedef-radiusvector)&lt; [**parent**](structastrea_1_1astro_1_1DynamicFrame.md#variable-parent) &gt; | [**get\_position**](structastrea_1_1astro_1_1DynamicFrame.md#function-get_position) (const [**Date**](classastrea_1_1astro_1_1Date.md) & date) const<br>_Gets the inertial position vector at a given date._  |
|  [**VelocityVector**](namespaceastrea_1_1astro.md#typedef-velocityvector)&lt; [**parent**](structastrea_1_1astro_1_1DynamicFrame.md#variable-parent) &gt; | [**get\_velocity**](structastrea_1_1astro_1_1DynamicFrame.md#function-get_velocity) (const [**Date**](classastrea_1_1astro_1_1Date.md) & date) const<br>_Gets the inertial velocity vector at a given date._  |






## Detailed Description


Unlike VNB/RIC/LVLH, the perifocal frame's orientation is fixed for a given (unperturbed) orbit  it depends only on the orbital plane and the location of periapsis, not on where the satellite currently is along the orbit. 


    
## Public Types Documentation




### typedef tag\_type 

_Tag type for this frame._ 
```C++
using astrea::astro::frames::Perifocal< _parent_ >::tag_type =  PerifocalTag<_parent_>;
```




<hr>
## Public Static Attributes Documentation




### variable parent 

_The reference frame of the_ [_**Perifocal**_](structastrea_1_1astro_1_1frames_1_1Perifocal.md) _frame._
```C++
constexpr auto astrea::astro::frames::Perifocal< _parent_ >::parent;
```




<hr>



### variable tag 

_Empty frame tag satisfying IsFrame._ 
```C++
constexpr tag_type astrea::astro::frames::Perifocal< _parent_ >::tag;
```




<hr>
## Public Functions Documentation




### function Perifocal [1/2]

_Constructor for the_ [_**Perifocal**_](structastrea_1_1astro_1_1frames_1_1Perifocal.md) _frame from position, velocity, and gravitational parameter._
```C++
inline astrea::astro::frames::Perifocal::Perifocal (
    const RadiusVector < parent > & position,
    const VelocityVector < parent > & velocity
) 
```





**Parameters:**


* `position` The position vector in the parent frame. 
* `velocity` The velocity vector in the parent frame. 




        

<hr>



### function Perifocal [2/2]

_Default constructor is deleted to prevent instantiation without a parent frame._ 
```C++
astrea::astro::frames::Perifocal::Perifocal () = delete
```




<hr>



### function get\_dcm 

_Gets the Direction Cosine Matrix (DCM) for the_ [_**Perifocal**_](structastrea_1_1astro_1_1frames_1_1Perifocal.md) _frame at a given date._
```C++
inline DirectionCosineMatrix < parent , tag > astrea::astro::frames::Perifocal::get_dcm (
    const Date & date
) const
```



Computes the specific angular momentum vector (h = r x v, giving the W axis) and the eccentricity vector (e = (v x h) / mu - r\_hat, giving the P axis, i.e. the direction to periapsis), then completes the right-handed triad with Q = W x P.




**Parameters:**


* `date` The date for which the DCM is requested. Unused: the perifocal frame's orientation only depends on the (unperturbed) orbital plane and periapsis location, not on the current date. 



**Returns:**

DirectionCosineMatrix&lt;parent, Perifocal&gt; The DCM from parent to [**Perifocal**](structastrea_1_1astro_1_1frames_1_1Perifocal.md). 





        

<hr>

------------------------------
The documentation for this class was generated from the following file `astrea/astro/astro/frames/definitions/dynamic_frames/Perifocal.hpp`

