

# Class astrea::astro::frames::EastNorthUp



[**ClassList**](annotated.md) **>** [**astrea**](namespaceastrea.md) **>** [**astro**](namespaceastrea_1_1astro.md) **>** [**frames**](namespaceastrea_1_1astro_1_1frames.md) **>** [**EastNorthUp**](classastrea_1_1astro_1_1frames_1_1EastNorthUp.md)



_Class representing the East, North, Up (ENU) frame._ 

* `#include <EastNorthUp.hpp>`



Inherits the following classes: DynamicFrame< EastNorthUp, FrameAxis::ENU >


































## Public Functions

| Type | Name |
| ---: | :--- |
|   | [**EastNorthUp**](#function-eastnorthup-12) (const [**FrameReference**](classastrea_1_1astro_1_1FrameReference.md) \* parent) <br>_Default constructor for_ [_**EastNorthUp**_](classastrea_1_1astro_1_1frames_1_1EastNorthUp.md) _._ |
|  [**DirectionCosineMatrix**](classastrea_1_1astro_1_1DirectionCosineMatrix.md)&lt; frames::earth::icrf, [**EastNorthUp**](classastrea_1_1astro_1_1frames_1_1EastNorthUp.md) &gt; | [**get\_dcm**](#function-get_dcm) (const [**Date**](classastrea_1_1astro_1_1Date.md) & date) const<br>_Gets the Direction Cosine Matrix (DCM) for the ENU frame at a given date._  |
|   | [**~EastNorthUp**](#function-eastnorthup) () = default<br>_Default destructor for_ [_**EastNorthUp**_](classastrea_1_1astro_1_1frames_1_1EastNorthUp.md) _._ |




























## Public Functions Documentation




### function EastNorthUp [1/2]

_Default constructor for_ [_**EastNorthUp**_](classastrea_1_1astro_1_1frames_1_1EastNorthUp.md) _._
```C++
inline astrea::astro::frames::EastNorthUp::EastNorthUp (
    const FrameReference * parent
) 
```



Initializes the ENU frame with a name and origin. 


        

<hr>



### function get\_dcm 

_Gets the Direction Cosine Matrix (DCM) for the ENU frame at a given date._ 
```C++
inline DirectionCosineMatrix < frames::earth::icrf, EastNorthUp > astrea::astro::frames::EastNorthUp::get_dcm (
    const Date & date
) const
```





**Parameters:**


* `date` The date for which the DCM is requested. 



**Returns:**

DirectionCosineMatrix&lt;frames::earth::icrf, EastNorthUp&gt; The DCM from ECI to ENU. 





        

<hr>



### function ~EastNorthUp 

_Default destructor for_ [_**EastNorthUp**_](classastrea_1_1astro_1_1frames_1_1EastNorthUp.md) _._
```C++
astrea::astro::frames::EastNorthUp::~EastNorthUp () = default
```




<hr>

------------------------------
The documentation for this class was generated from the following file `astrea/astro/astro/frames/instances/EastNorthUp.hpp`

