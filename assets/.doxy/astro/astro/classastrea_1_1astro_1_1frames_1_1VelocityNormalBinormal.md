

# Class astrea::astro::frames::VelocityNormalBinormal



[**ClassList**](annotated.md) **>** [**astrea**](namespaceastrea.md) **>** [**astro**](namespaceastrea_1_1astro.md) **>** [**frames**](namespaceastrea_1_1astro_1_1frames.md) **>** [**VelocityNormalBinormal**](classastrea_1_1astro_1_1frames_1_1VelocityNormalBinormal.md)



_Class representing the Velocity, Normal, Binormal (VNB) frame._ 

* `#include <VelocityNormalBinormal.hpp>`



Inherits the following classes: [astrea::astro::DynamicFrame](classastrea_1_1astro_1_1DynamicFrame.md)










































































## Public Functions

| Type | Name |
| ---: | :--- |
|   | [**VelocityNormalBinormal**](#function-velocitynormalbinormal-12) ([**const**](classastrea_1_1astro_1_1CartesianVector.md) [**FrameReference**](classastrea_1_1astro_1_1FrameReference.md) \* parent) <br>_Default constructor for_ [_**VelocityNormalBinormal**_](classastrea_1_1astro_1_1frames_1_1VelocityNormalBinormal.md) _._ |
|  [**DirectionCosineMatrix**](classastrea_1_1astro_1_1DirectionCosineMatrix.md)&lt; [**frames::earth::icrf**](structastrea_1_1astro_1_1InertialFrame.md), [**VelocityNormalBinormal**](classastrea_1_1astro_1_1frames_1_1VelocityNormalBinormal.md) &gt; | [**get\_dcm**](#function-get_dcm) ([**const**](classastrea_1_1astro_1_1CartesianVector.md) [**Date**](classastrea_1_1astro_1_1Date.md) & date) const<br>_Gets the Direction Cosine Matrix (DCM) for the VNB frame at a given date._  |
|   | [**~VelocityNormalBinormal**](#function-velocitynormalbinormal) () = default<br>_Default destructor for_ [_**VelocityNormalBinormal**_](classastrea_1_1astro_1_1frames_1_1VelocityNormalBinormal.md) _._ |


## Public Functions inherited from astrea::astro::DynamicFrame

See [astrea::astro::DynamicFrame](classastrea_1_1astro_1_1DynamicFrame.md)

| Type | Name |
| ---: | :--- |
|  [**RadiusVector**](namespaceastrea_1_1astro.md#typedef-radiusvector)&lt; [**frames::earth::icrf**](structastrea_1_1astro_1_1InertialFrame.md) &gt; | [**convert\_from\_this\_frame**](classastrea_1_1astro_1_1DynamicFrame.md#function-convert_from_this_frame) ([**const**](classastrea_1_1astro_1_1CartesianVector.md) [**RadiusVector**](namespaceastrea_1_1astro.md#typedef-radiusvector)&lt; [**Frame\_T**](classastrea_1_1astro_1_1CartesianVector.md) &gt; & vec, [**const**](classastrea_1_1astro_1_1CartesianVector.md) [**Date**](classastrea_1_1astro_1_1Date.md) & date) const<br>_Converts a_ [_**CartesianVector**_](classastrea_1_1astro_1_1CartesianVector.md) _from Frame\_T coordinates to Earth-Centered Inertial (ECI) coordinates._ |
|  [**RadiusVector**](namespaceastrea_1_1astro.md#typedef-radiusvector)&lt; [**Frame\_T**](classastrea_1_1astro_1_1CartesianVector.md) &gt; | [**convert\_to\_this\_frame**](classastrea_1_1astro_1_1DynamicFrame.md#function-convert_to_this_frame) ([**const**](classastrea_1_1astro_1_1CartesianVector.md) [**RadiusVector**](namespaceastrea_1_1astro.md#typedef-radiusvector)&lt; [**frames::earth::icrf**](structastrea_1_1astro_1_1InertialFrame.md) &gt; & vec, [**const**](classastrea_1_1astro_1_1CartesianVector.md) [**Date**](classastrea_1_1astro_1_1Date.md) & date) const<br>_Converts a_ [_**CartesianVector**_](classastrea_1_1astro_1_1CartesianVector.md) _from Earth-Centered Inertial (ECI) to Frame\_T coordinates._ |
|  [**CartesianVector**](classastrea_1_1astro_1_1CartesianVector.md)&lt; [**Value\_T**](classastrea_1_1astro_1_1CartesianVector.md), [**Frame\_T**](classastrea_1_1astro_1_1CartesianVector.md) &gt; | [**rotate\_into\_this\_frame**](classastrea_1_1astro_1_1DynamicFrame.md#function-rotate_into_this_frame) ([**const**](classastrea_1_1astro_1_1CartesianVector.md) [**CartesianVector**](classastrea_1_1astro_1_1CartesianVector.md)&lt; [**Value\_T**](classastrea_1_1astro_1_1CartesianVector.md), [**frames::earth::icrf**](structastrea_1_1astro_1_1InertialFrame.md) &gt; & vec, [**const**](classastrea_1_1astro_1_1CartesianVector.md) [**Date**](classastrea_1_1astro_1_1Date.md) & date) const<br>_Rotates a_ [_**CartesianVector**_](classastrea_1_1astro_1_1CartesianVector.md) _from Earth-Centered Inertial (ECI) to Frame\_T coordinates._ |
|  [**CartesianVector**](classastrea_1_1astro_1_1CartesianVector.md)&lt; [**Value\_T**](classastrea_1_1astro_1_1CartesianVector.md), [**frames::earth::icrf**](structastrea_1_1astro_1_1InertialFrame.md) &gt; | [**rotate\_out\_of\_this\_frame**](classastrea_1_1astro_1_1DynamicFrame.md#function-rotate_out_of_this_frame) ([**const**](classastrea_1_1astro_1_1CartesianVector.md) [**CartesianVector**](classastrea_1_1astro_1_1CartesianVector.md)&lt; [**Value\_T**](classastrea_1_1astro_1_1CartesianVector.md), [**Frame\_T**](classastrea_1_1astro_1_1CartesianVector.md) &gt; & vec, [**const**](classastrea_1_1astro_1_1CartesianVector.md) [**Date**](classastrea_1_1astro_1_1Date.md) & date) const<br>_Rotates a_ [_**CartesianVector**_](classastrea_1_1astro_1_1CartesianVector.md) _from Frame\_T coordinates to Earth-Centered Inertial (ECI) coordinates._ |






## Public Static Functions inherited from astrea::astro::DynamicFrame

See [astrea::astro::DynamicFrame](classastrea_1_1astro_1_1DynamicFrame.md)

| Type | Name |
| ---: | :--- |
|  [**constexpr**](classastrea_1_1astro_1_1CartesianVector.md) [**FrameAxis**](namespaceastrea_1_1astro.md#enum-frameaxis) | [**get\_axis**](classastrea_1_1astro_1_1DynamicFrame.md#function-get_axis) () <br>_Get the origin of the frame._  |
|  [**constexpr**](classastrea_1_1astro_1_1CartesianVector.md) [**CelestialBodyId**](namespaceastrea_1_1astro.md#enum-celestialbodyid) | [**get\_origin**](classastrea_1_1astro_1_1DynamicFrame.md#function-get_origin) () <br>_Get the origin of the frame._  |
|  [**Frame\_T**](classastrea_1_1astro_1_1CartesianVector.md) | [**instantaneous**](classastrea_1_1astro_1_1DynamicFrame.md#function-instantaneous) ([**const**](classastrea_1_1astro_1_1CartesianVector.md) [**RadiusVector**](namespaceastrea_1_1astro.md#typedef-radiusvector)&lt; [**frames::earth::icrf**](structastrea_1_1astro_1_1InertialFrame.md) &gt; & position, [**const**](classastrea_1_1astro_1_1CartesianVector.md) [**VelocityVector**](namespaceastrea_1_1astro.md#typedef-velocityvector)&lt; [**frames::earth::icrf**](structastrea_1_1astro_1_1InertialFrame.md) &gt; & velocity) <br>_Creates an instantaneous Frame\_T frame._  |


## Public Static Functions inherited from astrea::astro::Frame

See [astrea::astro::Frame](structastrea_1_1astro_1_1Frame.md)

| Type | Name |
| ---: | :--- |
|  [**constexpr**](classastrea_1_1astro_1_1CartesianVector.md) [**FrameAxis**](namespaceastrea_1_1astro.md#enum-frameaxis) | [**get\_axis**](structastrea_1_1astro_1_1Frame.md#function-get_axis) () <br>_Get the origin of the frame._  |
|  [**constexpr**](classastrea_1_1astro_1_1CartesianVector.md) [**CelestialBodyId**](namespaceastrea_1_1astro.md#enum-celestialbodyid) | [**get\_origin**](structastrea_1_1astro_1_1Frame.md#function-get_origin) () <br>_Get the origin of the frame._  |
















## Protected Attributes inherited from astrea::astro::DynamicFrame

See [astrea::astro::DynamicFrame](classastrea_1_1astro_1_1DynamicFrame.md)

| Type | Name |
| ---: | :--- |
|  [**bool**](classastrea_1_1astro_1_1CartesianVector.md) | [**\_isInstantaneous**](classastrea_1_1astro_1_1DynamicFrame.md#variable-_isinstantaneous)  <br>_Flag indicating if the frame is instantaneous._  |
|  [**const**](classastrea_1_1astro_1_1CartesianVector.md) [**FrameReference**](classastrea_1_1astro_1_1FrameReference.md) \* | [**\_parent**](classastrea_1_1astro_1_1DynamicFrame.md#variable-_parent)  <br>_The parent object this frame is attached to._  |
|  [**RadiusVector**](namespaceastrea_1_1astro.md#typedef-radiusvector)&lt; [**frames::earth::icrf**](structastrea_1_1astro_1_1InertialFrame.md) &gt; | [**\_position**](classastrea_1_1astro_1_1DynamicFrame.md#variable-_position)  <br>_The position vector in the ECI frame._  |
|  [**VelocityVector**](namespaceastrea_1_1astro.md#typedef-velocityvector)&lt; [**frames::earth::icrf**](structastrea_1_1astro_1_1InertialFrame.md) &gt; | [**\_velocity**](classastrea_1_1astro_1_1DynamicFrame.md#variable-_velocity)  <br>_The velocity vector in the ECI frame._  |








## Protected Static Attributes inherited from astrea::astro::Frame

See [astrea::astro::Frame](structastrea_1_1astro_1_1Frame.md)

| Type | Name |
| ---: | :--- |
|  [**constexpr**](classastrea_1_1astro_1_1CartesianVector.md) [**FrameAxis**](namespaceastrea_1_1astro.md#enum-frameaxis) | [**\_axis**](structastrea_1_1astro_1_1Frame.md#variable-_axis)   = `[**axis**](classastrea_1_1astro_1_1CartesianVector.md)`<br>_The axis type of the inertial frame._  |
|  [**constexpr**](classastrea_1_1astro_1_1CartesianVector.md) [**CelestialBodyId**](namespaceastrea_1_1astro.md#enum-celestialbodyid) | [**\_origin**](structastrea_1_1astro_1_1Frame.md#variable-_origin)   = `[**origin**](classastrea_1_1astro_1_1CartesianVector.md)`<br>_The central body associated with the inertial frame._  |








































## Protected Functions inherited from astrea::astro::DynamicFrame

See [astrea::astro::DynamicFrame](classastrea_1_1astro_1_1DynamicFrame.md)

| Type | Name |
| ---: | :--- |
|   | [**DynamicFrame**](classastrea_1_1astro_1_1DynamicFrame.md#function-dynamicframe-12) ([**const**](classastrea_1_1astro_1_1CartesianVector.md) [**FrameReference**](classastrea_1_1astro_1_1FrameReference.md) \* parent) <br>_Constructor for_ [_**DynamicFrame**_](classastrea_1_1astro_1_1DynamicFrame.md) _._ |
|   | [**DynamicFrame**](classastrea_1_1astro_1_1DynamicFrame.md#function-dynamicframe-22) ([**const**](classastrea_1_1astro_1_1CartesianVector.md) [**RadiusVector**](namespaceastrea_1_1astro.md#typedef-radiusvector)&lt; [**frames::earth::icrf**](structastrea_1_1astro_1_1InertialFrame.md) &gt; & position, [**const**](classastrea_1_1astro_1_1CartesianVector.md) [**VelocityVector**](namespaceastrea_1_1astro.md#typedef-velocityvector)&lt; [**frames::earth::icrf**](structastrea_1_1astro_1_1InertialFrame.md) &gt; & velocity) <br>_Constructor for instantaneous dynamic state/frames._  |
|  [**RadiusVector**](namespaceastrea_1_1astro.md#typedef-radiusvector)&lt; [**frames::earth::icrf**](structastrea_1_1astro_1_1InertialFrame.md) &gt; | [**get\_inertial\_position**](classastrea_1_1astro_1_1DynamicFrame.md#function-get_inertial_position) ([**const**](classastrea_1_1astro_1_1CartesianVector.md) [**Date**](classastrea_1_1astro_1_1Date.md) & date) const<br>_Gets the inertial position vector at a given date._  |
|  [**VelocityVector**](namespaceastrea_1_1astro.md#typedef-velocityvector)&lt; [**frames::earth::icrf**](structastrea_1_1astro_1_1InertialFrame.md) &gt; | [**get\_inertial\_velocity**](classastrea_1_1astro_1_1DynamicFrame.md#function-get_inertial_velocity) ([**const**](classastrea_1_1astro_1_1CartesianVector.md) [**Date**](classastrea_1_1astro_1_1Date.md) & date) const<br>_Gets the inertial velocity vector at a given date._  |


## Protected Functions inherited from astrea::astro::Frame

See [astrea::astro::Frame](structastrea_1_1astro_1_1Frame.md)

| Type | Name |
| ---: | :--- |
| virtual  | [**~Frame**](structastrea_1_1astro_1_1Frame.md#function-frame) () = default<br>_Default destructor for_ [_**Frame**_](structastrea_1_1astro_1_1Frame.md) _._ |








## Public Functions Documentation




### function VelocityNormalBinormal [1/2]

_Default constructor for_ [_**VelocityNormalBinormal**_](classastrea_1_1astro_1_1frames_1_1VelocityNormalBinormal.md) _._
```C++
inline astrea::astro::frames::VelocityNormalBinormal::VelocityNormalBinormal (
    const  FrameReference * parent
) 
```



Initializes the ECEF frame with a name and origin. 


        

<hr>



### function get\_dcm 

_Gets the Direction Cosine Matrix (DCM) for the VNB frame at a given date._ 
```C++
inline DirectionCosineMatrix < frames::earth::icrf , VelocityNormalBinormal > astrea::astro::frames::VelocityNormalBinormal::get_dcm (
    const  Date & date
) const
```





**Parameters:**


* `date` The date for which the DCM is requested. 



**Returns:**

DirectionCosineMatrix&lt;frames::earth::icrf, VelocityNormalBinormal&gt; The DCM from ECI to VNB. 





        

<hr>



### function ~VelocityNormalBinormal 

_Default destructor for_ [_**VelocityNormalBinormal**_](classastrea_1_1astro_1_1frames_1_1VelocityNormalBinormal.md) _._
```C++
astrea::astro::frames::VelocityNormalBinormal::~VelocityNormalBinormal () = default
```




<hr>

------------------------------
The documentation for this class was generated from the following file `astrea/astro/astro/frames/instances/VelocityNormalBinormal.hpp`

