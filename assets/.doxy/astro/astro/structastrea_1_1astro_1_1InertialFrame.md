

# Struct astrea::astro::InertialFrame

**template &lt;[**CelestialBodyId**](namespaceastrea_1_1astro.md#enum-celestialbodyid) origin, [**FrameAxis**](namespaceastrea_1_1astro.md#enum-frameaxis) axis&gt;**



[**ClassList**](annotated.md) **>** [**astrea**](namespaceastrea.md) **>** [**astro**](namespaceastrea_1_1astro.md) **>** [**InertialFrame**](structastrea_1_1astro_1_1InertialFrame.md)



_Base class for all inertial state/frames._ 

* `#include <InertialFrame.hpp>`



Inherits the following classes: [astrea::astro::Frame](structastrea_1_1astro_1_1Frame.md)






















































## Public Functions

| Type | Name |
| ---: | :--- |
| virtual  | [**~InertialFrame**](#function-inertialframe) () = default<br> |




## Public Static Functions

| Type | Name |
| ---: | :--- |
|  [**constexpr**](classastrea_1_1astro_1_1CartesianVector.md) [**FrameAxis**](namespaceastrea_1_1astro.md#enum-frameaxis) | [**get\_axis**](#function-get_axis) () <br>_Get the origin of the frame._  |
|  [**constexpr**](classastrea_1_1astro_1_1CartesianVector.md) [**CelestialBodyId**](namespaceastrea_1_1astro.md#enum-celestialbodyid) | [**get\_origin**](#function-get_origin) () <br>_Get the origin of the frame._  |


## Public Static Functions inherited from astrea::astro::Frame

See [astrea::astro::Frame](structastrea_1_1astro_1_1Frame.md)

| Type | Name |
| ---: | :--- |
|  [**constexpr**](classastrea_1_1astro_1_1CartesianVector.md) [**FrameAxis**](namespaceastrea_1_1astro.md#enum-frameaxis) | [**get\_axis**](structastrea_1_1astro_1_1Frame.md#function-get_axis) () <br>_Get the origin of the frame._  |
|  [**constexpr**](classastrea_1_1astro_1_1CartesianVector.md) [**CelestialBodyId**](namespaceastrea_1_1astro.md#enum-celestialbodyid) | [**get\_origin**](structastrea_1_1astro_1_1Frame.md#function-get_origin) () <br>_Get the origin of the frame._  |
















## Protected Static Attributes inherited from astrea::astro::Frame

See [astrea::astro::Frame](structastrea_1_1astro_1_1Frame.md)

| Type | Name |
| ---: | :--- |
|  [**constexpr**](classastrea_1_1astro_1_1CartesianVector.md) [**FrameAxis**](namespaceastrea_1_1astro.md#enum-frameaxis) | [**\_axis**](structastrea_1_1astro_1_1Frame.md#variable-_axis)   = `[**axis**](classastrea_1_1astro_1_1CartesianVector.md)`<br>_The axis type of the inertial frame._  |
|  [**constexpr**](classastrea_1_1astro_1_1CartesianVector.md) [**CelestialBodyId**](namespaceastrea_1_1astro.md#enum-celestialbodyid) | [**\_origin**](structastrea_1_1astro_1_1Frame.md#variable-_origin)   = `[**origin**](classastrea_1_1astro_1_1CartesianVector.md)`<br>_The central body associated with the inertial frame._  |




























## Protected Functions inherited from astrea::astro::Frame

See [astrea::astro::Frame](structastrea_1_1astro_1_1Frame.md)

| Type | Name |
| ---: | :--- |
| virtual  | [**~Frame**](structastrea_1_1astro_1_1Frame.md#function-frame) () = default<br>_Default destructor for_ [_**Frame**_](structastrea_1_1astro_1_1Frame.md) _._ |






## Public Functions Documentation




### function ~InertialFrame 

```C++
virtual astrea::astro::InertialFrame::~InertialFrame () = default
```




<hr>
## Public Static Functions Documentation




### function get\_axis 

_Get the origin of the frame._ 
```C++
static inline constexpr  FrameAxis astrea::astro::InertialFrame::get_axis () 
```





**Returns:**

The origin of the frame. 





        

<hr>



### function get\_origin 

_Get the origin of the frame._ 
```C++
static inline constexpr  CelestialBodyId astrea::astro::InertialFrame::get_origin () 
```





**Returns:**

The origin of the frame. 





        

<hr>

------------------------------
The documentation for this class was generated from the following file `astrea/astro/astro/frames/types/InertialFrame.hpp`

