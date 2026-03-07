

# Struct astrea::astro::Frame

**template &lt;[**CelestialBodyId**](namespaceastrea_1_1astro.md#enum-celestialbodyid) origin, [**FrameAxis**](namespaceastrea_1_1astro.md#enum-frameaxis) axis&gt;**



[**ClassList**](annotated.md) **>** [**astrea**](namespaceastrea.md) **>** [**astro**](namespaceastrea_1_1astro.md) **>** [**Frame**](structastrea_1_1astro_1_1Frame.md)



_Base class for all state/frames._ 

* `#include <Frame.hpp>`







































## Public Static Functions

| Type | Name |
| ---: | :--- |
|  constexpr [**FrameAxis**](namespaceastrea_1_1astro.md#enum-frameaxis) | [**get\_axis**](#function-get_axis) () <br>_Get the origin of the frame._  |
|  constexpr [**CelestialBodyId**](namespaceastrea_1_1astro.md#enum-celestialbodyid) | [**get\_origin**](#function-get_origin) () <br>_Get the origin of the frame._  |








## Protected Static Attributes

| Type | Name |
| ---: | :--- |
|  constexpr [**FrameAxis**](namespaceastrea_1_1astro.md#enum-frameaxis) | [**\_axis**](#variable-_axis)   = `axis`<br>_The axis type of the inertial frame._  |
|  constexpr [**CelestialBodyId**](namespaceastrea_1_1astro.md#enum-celestialbodyid) | [**\_origin**](#variable-_origin)   = `origin`<br>_The central body associated with the inertial frame._  |














## Protected Functions

| Type | Name |
| ---: | :--- |
| virtual  | [**~Frame**](#function-frame) () = default<br>_Default destructor for_ [_**Frame**_](structastrea_1_1astro_1_1Frame.md) _._ |




## Public Static Functions Documentation




### function get\_axis 

_Get the origin of the frame._ 
```C++
static inline constexpr FrameAxis astrea::astro::Frame::get_axis () 
```





**Returns:**

The origin of the frame. 





        

<hr>



### function get\_origin 

_Get the origin of the frame._ 
```C++
static inline constexpr CelestialBodyId astrea::astro::Frame::get_origin () 
```





**Returns:**

The origin of the frame. 





        

<hr>
## Protected Static Attributes Documentation




### variable \_axis 

_The axis type of the inertial frame._ 
```C++
constexpr FrameAxis astrea::astro::Frame< origin, axis >::_axis;
```




<hr>



### variable \_origin 

_The central body associated with the inertial frame._ 
```C++
constexpr CelestialBodyId astrea::astro::Frame< origin, axis >::_origin;
```




<hr>
## Protected Functions Documentation




### function ~Frame 

_Default destructor for_ [_**Frame**_](structastrea_1_1astro_1_1Frame.md) _._
```C++
virtual astrea::astro::Frame::~Frame () = default
```




<hr>

------------------------------
The documentation for this class was generated from the following file `astrea/astro/astro/frames/Frame.hpp`

