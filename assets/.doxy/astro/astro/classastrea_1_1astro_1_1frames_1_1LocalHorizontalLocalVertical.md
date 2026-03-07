

# Class astrea::astro::frames::LocalHorizontalLocalVertical



[**ClassList**](annotated.md) **>** [**astrea**](namespaceastrea.md) **>** [**astro**](namespaceastrea_1_1astro.md) **>** [**frames**](namespaceastrea_1_1astro_1_1frames.md) **>** [**LocalHorizontalLocalVertical**](classastrea_1_1astro_1_1frames_1_1LocalHorizontalLocalVertical.md)



_Class representing the Local Horizontal, Local Vertical (LVLH) frame._ 

* `#include <LocalHorizontalLocalVertical.hpp>`



Inherits the following classes: DynamicFrame< LocalHorizontalLocalVertical, FrameAxis::LVLH >


































## Public Functions

| Type | Name |
| ---: | :--- |
|   | [**LocalHorizontalLocalVertical**](#function-localhorizontallocalvertical-13) () = delete<br>_Default constructor is deleted to prevent instantiation without a parent frame._  |
|   | [**LocalHorizontalLocalVertical**](#function-localhorizontallocalvertical-23) (const [**FrameReference**](classastrea_1_1astro_1_1FrameReference.md) \* parent) <br>_Default constructor for_ [_**LocalHorizontalLocalVertical**_](classastrea_1_1astro_1_1frames_1_1LocalHorizontalLocalVertical.md) _._ |
|  [**DirectionCosineMatrix**](classastrea_1_1astro_1_1DirectionCosineMatrix.md)&lt; frames::earth::icrf, [**LocalHorizontalLocalVertical**](classastrea_1_1astro_1_1frames_1_1LocalHorizontalLocalVertical.md) &gt; | [**get\_dcm**](#function-get_dcm) (const [**Date**](classastrea_1_1astro_1_1Date.md) & date) const<br>_Gets the Direction Cosine Matrix (DCM) for the Local Horizontal, Local Vertical frame at a given date._  |
|   | [**~LocalHorizontalLocalVertical**](#function-localhorizontallocalvertical) () = default<br>_Default destructor for_ [_**LocalHorizontalLocalVertical**_](classastrea_1_1astro_1_1frames_1_1LocalHorizontalLocalVertical.md) _._ |




























## Public Functions Documentation




### function LocalHorizontalLocalVertical [1/3]

_Default constructor is deleted to prevent instantiation without a parent frame._ 
```C++
astrea::astro::frames::LocalHorizontalLocalVertical::LocalHorizontalLocalVertical () = delete
```




<hr>



### function LocalHorizontalLocalVertical [2/3]

_Default constructor for_ [_**LocalHorizontalLocalVertical**_](classastrea_1_1astro_1_1frames_1_1LocalHorizontalLocalVertical.md) _._
```C++
inline astrea::astro::frames::LocalHorizontalLocalVertical::LocalHorizontalLocalVertical (
    const FrameReference * parent
) 
```



Initializes the ECEF frame with a name and origin. 


        

<hr>



### function get\_dcm 

_Gets the Direction Cosine Matrix (DCM) for the Local Horizontal, Local Vertical frame at a given date._ 
```C++
inline DirectionCosineMatrix < frames::earth::icrf, LocalHorizontalLocalVertical > astrea::astro::frames::LocalHorizontalLocalVertical::get_dcm (
    const Date & date
) const
```





**Parameters:**


* `date` The date for which the DCM is computed. 



**Returns:**

DirectionCosineMatrix&lt;frames::earth::icrf, LocalHorizontalLocalVertical&gt; The DCM from ECI to LVLH. 





        

<hr>



### function ~LocalHorizontalLocalVertical 

_Default destructor for_ [_**LocalHorizontalLocalVertical**_](classastrea_1_1astro_1_1frames_1_1LocalHorizontalLocalVertical.md) _._
```C++
astrea::astro::frames::LocalHorizontalLocalVertical::~LocalHorizontalLocalVertical () = default
```




<hr>

------------------------------
The documentation for this class was generated from the following file `astrea/astro/astro/frames/instances/LocalHorizontalLocalVertical.hpp`

