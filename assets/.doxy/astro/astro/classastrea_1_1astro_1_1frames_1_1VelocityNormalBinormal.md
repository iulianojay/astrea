

# Class astrea::astro::frames::VelocityNormalBinormal



[**ClassList**](annotated.md) **>** [**astrea**](namespaceastrea.md) **>** [**astro**](namespaceastrea_1_1astro.md) **>** [**frames**](namespaceastrea_1_1astro_1_1frames.md) **>** [**VelocityNormalBinormal**](classastrea_1_1astro_1_1frames_1_1VelocityNormalBinormal.md)



_Class representing the Velocity, Normal, Binormal (VNB) frame._ 

* `#include <VelocityNormalBinormal.hpp>`



Inherits the following classes: DynamicFrame< VelocityNormalBinormal, FrameAxis::VNB >


































## Public Functions

| Type | Name |
| ---: | :--- |
|   | [**VelocityNormalBinormal**](#function-velocitynormalbinormal-12) (const [**FrameReference**](classastrea_1_1astro_1_1FrameReference.md) \* parent) <br>_Default constructor for_ [_**VelocityNormalBinormal**_](classastrea_1_1astro_1_1frames_1_1VelocityNormalBinormal.md) _._ |
|  [**DirectionCosineMatrix**](classastrea_1_1astro_1_1DirectionCosineMatrix.md)&lt; frames::earth::icrf, [**VelocityNormalBinormal**](classastrea_1_1astro_1_1frames_1_1VelocityNormalBinormal.md) &gt; | [**get\_dcm**](#function-get_dcm) (const [**Date**](classastrea_1_1astro_1_1Date.md) & date) const<br>_Gets the Direction Cosine Matrix (DCM) for the VNB frame at a given date._  |
|   | [**~VelocityNormalBinormal**](#function-velocitynormalbinormal) () = default<br>_Default destructor for_ [_**VelocityNormalBinormal**_](classastrea_1_1astro_1_1frames_1_1VelocityNormalBinormal.md) _._ |




























## Public Functions Documentation




### function VelocityNormalBinormal [1/2]

_Default constructor for_ [_**VelocityNormalBinormal**_](classastrea_1_1astro_1_1frames_1_1VelocityNormalBinormal.md) _._
```C++
inline astrea::astro::frames::VelocityNormalBinormal::VelocityNormalBinormal (
    const FrameReference * parent
) 
```



Initializes the ECEF frame with a name and origin. 


        

<hr>



### function get\_dcm 

_Gets the Direction Cosine Matrix (DCM) for the VNB frame at a given date._ 
```C++
inline DirectionCosineMatrix < frames::earth::icrf, VelocityNormalBinormal > astrea::astro::frames::VelocityNormalBinormal::get_dcm (
    const Date & date
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

