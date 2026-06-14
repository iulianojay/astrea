

# Struct astrea::astro::frames::RadialInTrackCrossTrack

**template &lt;IsFrame [**auto**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) \_parent\_&gt;**



[**ClassList**](annotated.md) **>** [**astrea**](namespaceastrea.md) **>** [**astro**](namespaceastrea_1_1astro.md) **>** [**frames**](namespaceastrea_1_1astro_1_1frames.md) **>** [**RadialInTrackCrossTrack**](structastrea_1_1astro_1_1frames_1_1RadialInTrackCrossTrack.md)



_Class representing the Radial, In-Track, Cross-Track (RIC) frame._ 

* `#include <RadialInTrackCrossTrack.hpp>`



Inherits the following classes: [astrea::astro::DynamicFrame](structastrea_1_1astro_1_1DynamicFrame.md)














## Public Types

| Type | Name |
| ---: | :--- |
| typedef [**RicTag**](structastrea_1_1astro_1_1frames_1_1RicTag.md)&lt; [**\_parent\_**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) &gt; | [**tag\_type**](#typedef-tag_type)  <br>_Tag type for this frame._  |












## Public Static Attributes

| Type | Name |
| ---: | :--- |
|  [**constexpr**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) [**auto**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) | [**parent**](#variable-parent)   = `[**\_parent\_**](classastrea_1_1astro_1_1DirectionCosineMatrix.md)`<br>_The reference frame of the RIC frame._  |
|  [**constexpr**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) [**tag\_type**](structastrea_1_1astro_1_1frames_1_1RadialInTrackCrossTrack.md#typedef-tag_type) | [**tag**](#variable-tag)   = `{}`<br>_Empty frame tag satisfying IsFrame._  |


## Public Static Attributes inherited from astrea::astro::DynamicFrame

See [astrea::astro::DynamicFrame](structastrea_1_1astro_1_1DynamicFrame.md)

| Type | Name |
| ---: | :--- |
|  [**constexpr**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) [**auto**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) | [**parent**](structastrea_1_1astro_1_1DynamicFrame.md#variable-parent)   = `[**\_parent\_**](classastrea_1_1astro_1_1DirectionCosineMatrix.md)`<br>_The reference frame of the dynamic frame._  |


























## Public Functions

| Type | Name |
| ---: | :--- |
|   | [**RadialInTrackCrossTrack**](#function-radialintrackcrosstrack-12) ([**const**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) [**RadiusVector**](namespaceastrea_1_1astro.md#typedef-radiusvector)&lt; [**parent**](structastrea_1_1astro_1_1frames_1_1RadialInTrackCrossTrack.md#variable-parent) &gt; & position, [**const**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) [**VelocityVector**](namespaceastrea_1_1astro.md#typedef-velocityvector)&lt; [**parent**](structastrea_1_1astro_1_1frames_1_1RadialInTrackCrossTrack.md#variable-parent) &gt; & velocity) <br>_Constructor for instantaneous dynamic state/frames._  |
|   | [**RadialInTrackCrossTrack**](#function-radialintrackcrosstrack-22) () = delete<br>_Default constructor is deleted to prevent instantiation without a parent frame._  |
|  [**DirectionCosineMatrix**](classastrea_1_1astro_1_1DirectionCosineMatrix.md)&lt; [**parent**](structastrea_1_1astro_1_1frames_1_1RadialInTrackCrossTrack.md#variable-parent), [**tag**](structastrea_1_1astro_1_1frames_1_1RadialInTrackCrossTrack.md#variable-tag) &gt; | [**get\_dcm**](#function-get_dcm) ([**const**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) [**Date**](classastrea_1_1astro_1_1Date.md) & date) const<br>_Gets the Direction Cosine Matrix (DCM) for the RIC frame at a given date._  |


## Public Functions inherited from astrea::astro::DynamicFrame

See [astrea::astro::DynamicFrame](structastrea_1_1astro_1_1DynamicFrame.md)

| Type | Name |
| ---: | :--- |
|  [**CartesianVector**](structastrea_1_1astro_1_1CartesianVector.md)&lt; [**Value\_T**](classastrea_1_1astro_1_1DirectionCosineMatrix.md), [**\_self\_**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) &gt; | [**rotate\_into\_this\_frame**](structastrea_1_1astro_1_1DynamicFrame.md#function-rotate_into_this_frame) ([**const**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) [**CartesianVector**](structastrea_1_1astro_1_1CartesianVector.md)&lt; [**Value\_T**](classastrea_1_1astro_1_1DirectionCosineMatrix.md), [**parent**](structastrea_1_1astro_1_1DynamicFrame.md#variable-parent) &gt; & vec, [**const**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) [**Date**](classastrea_1_1astro_1_1Date.md) & date) const<br>_Rotates a_ [_**CartesianVector**_](structastrea_1_1astro_1_1CartesianVector.md) _from the parent frame to this frame's coordinates._ |
|  [**CartesianVector**](structastrea_1_1astro_1_1CartesianVector.md)&lt; [**Value\_T**](classastrea_1_1astro_1_1DirectionCosineMatrix.md), [**parent**](structastrea_1_1astro_1_1DynamicFrame.md#variable-parent) &gt; | [**rotate\_out\_of\_this\_frame**](structastrea_1_1astro_1_1DynamicFrame.md#function-rotate_out_of_this_frame) ([**const**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) [**CartesianVector**](structastrea_1_1astro_1_1CartesianVector.md)&lt; [**Value\_T**](classastrea_1_1astro_1_1DirectionCosineMatrix.md), [**\_self\_**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) &gt; & vec, [**const**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) [**Date**](classastrea_1_1astro_1_1Date.md) & date) const<br>_Rotates a_ [_**CartesianVector**_](structastrea_1_1astro_1_1CartesianVector.md) _from this frame's coordinates to the parent frame coordinates._ |
|  [**RadiusVector**](namespaceastrea_1_1astro.md#typedef-radiusvector)&lt; [**parent**](structastrea_1_1astro_1_1DynamicFrame.md#variable-parent) &gt; | [**transform\_from\_this\_frame**](structastrea_1_1astro_1_1DynamicFrame.md#function-transform_from_this_frame) ([**const**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) [**RadiusVector**](namespaceastrea_1_1astro.md#typedef-radiusvector)&lt; [**\_self\_**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) &gt; & vec, [**const**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) [**Date**](classastrea_1_1astro_1_1Date.md) & date) const<br>_Converts a_ [_**CartesianVector**_](structastrea_1_1astro_1_1CartesianVector.md) _from this frame's coordinates to the parent frame coordinates._ |
|  [**RadiusVector**](namespaceastrea_1_1astro.md#typedef-radiusvector)&lt; [**\_self\_**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) &gt; | [**transform\_to\_this\_frame**](structastrea_1_1astro_1_1DynamicFrame.md#function-transform_to_this_frame) ([**const**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) [**RadiusVector**](namespaceastrea_1_1astro.md#typedef-radiusvector)&lt; [**parent**](structastrea_1_1astro_1_1DynamicFrame.md#variable-parent) &gt; & vec, [**const**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) [**Date**](classastrea_1_1astro_1_1Date.md) & date) const<br>_Converts a_ [_**CartesianVector**_](structastrea_1_1astro_1_1CartesianVector.md) _from the parent frame to this frame's coordinates._ |
















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
|   | [**DynamicFrame**](structastrea_1_1astro_1_1DynamicFrame.md#function-dynamicframe) ([**const**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) [**RadiusVector**](namespaceastrea_1_1astro.md#typedef-radiusvector)&lt; [**\_parent\_**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) &gt; & position, [**const**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) [**VelocityVector**](namespaceastrea_1_1astro.md#typedef-velocityvector)&lt; [**\_parent\_**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) &gt; & velocity) <br>_Constructor for instantaneous dynamic state/frames._  |
|  [**RadiusVector**](namespaceastrea_1_1astro.md#typedef-radiusvector)&lt; [**parent**](structastrea_1_1astro_1_1DynamicFrame.md#variable-parent) &gt; | [**get\_position**](structastrea_1_1astro_1_1DynamicFrame.md#function-get_position) ([**const**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) [**Date**](classastrea_1_1astro_1_1Date.md) & date) const<br>_Gets the inertial position vector at a given date._  |
|  [**VelocityVector**](namespaceastrea_1_1astro.md#typedef-velocityvector)&lt; [**parent**](structastrea_1_1astro_1_1DynamicFrame.md#variable-parent) &gt; | [**get\_velocity**](structastrea_1_1astro_1_1DynamicFrame.md#function-get_velocity) ([**const**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) [**Date**](classastrea_1_1astro_1_1Date.md) & date) const<br>_Gets the inertial velocity vector at a given date._  |






## Public Types Documentation




### typedef tag\_type 

_Tag type for this frame._ 
```C++
using astrea::astro::frames::RadialInTrackCrossTrack< _parent_ >::tag_type =  RicTag<_parent_>;
```




<hr>
## Public Static Attributes Documentation




### variable parent 

_The reference frame of the RIC frame._ 
```C++
constexpr auto astrea::astro::frames::RadialInTrackCrossTrack< _parent_ >::parent;
```




<hr>



### variable tag 

_Empty frame tag satisfying IsFrame._ 
```C++
constexpr tag_type astrea::astro::frames::RadialInTrackCrossTrack< _parent_ >::tag;
```




<hr>
## Public Functions Documentation




### function RadialInTrackCrossTrack [1/2]

_Constructor for instantaneous dynamic state/frames._ 
```C++
inline astrea::astro::frames::RadialInTrackCrossTrack::RadialInTrackCrossTrack (
    const  RadiusVector < parent > & position,
    const  VelocityVector < parent > & velocity
) 
```





**Parameters:**


* `position` The position vector in the parent frame. 
* `velocity` The velocity vector in the parent frame. 




        

<hr>



### function RadialInTrackCrossTrack [2/2]

_Default constructor is deleted to prevent instantiation without a parent frame._ 
```C++
astrea::astro::frames::RadialInTrackCrossTrack::RadialInTrackCrossTrack () = delete
```




<hr>



### function get\_dcm 

_Gets the Direction Cosine Matrix (DCM) for the RIC frame at a given date._ 
```C++
inline DirectionCosineMatrix < parent , tag > astrea::astro::frames::RadialInTrackCrossTrack::get_dcm (
    const  Date & date
) const
```





**Parameters:**


* `date` The date for which the DCM is requested. 



**Returns:**

DirectionCosineMatrix&lt;parent, RadialInTrackCrossTrack&gt; The DCM from parent to RIC. 





        

<hr>

------------------------------
The documentation for this class was generated from the following file `astrea/astro/astro/frames/definitions/RadialInTrackCrossTrack.hpp`

