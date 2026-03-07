

# Class astrea::astro::frames::RadialInTrackCrossTrack



[**ClassList**](annotated.md) **>** [**astrea**](namespaceastrea.md) **>** [**astro**](namespaceastrea_1_1astro.md) **>** [**frames**](namespaceastrea_1_1astro_1_1frames.md) **>** [**RadialInTrackCrossTrack**](classastrea_1_1astro_1_1frames_1_1RadialInTrackCrossTrack.md)



_Class representing the Radial, In-Track, Cross-Track (RIC) frame._ 

* `#include <RadialInTrackCrossTrack.hpp>`



Inherits the following classes: DynamicFrame< RadialInTrackCrossTrack, FrameAxis::RIC >


































## Public Functions

| Type | Name |
| ---: | :--- |
|   | [**RadialInTrackCrossTrack**](#function-radialintrackcrosstrack-13) () = delete<br>_Default constructor is deleted to prevent instantiation without a parent frame._  |
|   | [**RadialInTrackCrossTrack**](#function-radialintrackcrosstrack-23) (const [**FrameReference**](classastrea_1_1astro_1_1FrameReference.md) \* parent) <br>_Default constructor for_ [_**RadialInTrackCrossTrack**_](classastrea_1_1astro_1_1frames_1_1RadialInTrackCrossTrack.md) _._ |
|  [**DirectionCosineMatrix**](classastrea_1_1astro_1_1DirectionCosineMatrix.md)&lt; frames::earth::icrf, [**RadialInTrackCrossTrack**](classastrea_1_1astro_1_1frames_1_1RadialInTrackCrossTrack.md) &gt; | [**get\_dcm**](#function-get_dcm) (const [**Date**](classastrea_1_1astro_1_1Date.md) & date) const<br>_Gets the Direction Cosine Matrix (DCM) for the RIC frame at a given date._  |
|   | [**~RadialInTrackCrossTrack**](#function-radialintrackcrosstrack) () = default<br>_Default destructor for_ [_**RadialInTrackCrossTrack**_](classastrea_1_1astro_1_1frames_1_1RadialInTrackCrossTrack.md) _._ |




























## Public Functions Documentation




### function RadialInTrackCrossTrack [1/3]

_Default constructor is deleted to prevent instantiation without a parent frame._ 
```C++
astrea::astro::frames::RadialInTrackCrossTrack::RadialInTrackCrossTrack () = delete
```




<hr>



### function RadialInTrackCrossTrack [2/3]

_Default constructor for_ [_**RadialInTrackCrossTrack**_](classastrea_1_1astro_1_1frames_1_1RadialInTrackCrossTrack.md) _._
```C++
inline astrea::astro::frames::RadialInTrackCrossTrack::RadialInTrackCrossTrack (
    const FrameReference * parent
) 
```



Initializes the ECEF frame with a name and origin. 


        

<hr>



### function get\_dcm 

_Gets the Direction Cosine Matrix (DCM) for the RIC frame at a given date._ 
```C++
inline DirectionCosineMatrix < frames::earth::icrf, RadialInTrackCrossTrack > astrea::astro::frames::RadialInTrackCrossTrack::get_dcm (
    const Date & date
) const
```





**Parameters:**


* `date` The date for which the DCM is requested. 



**Returns:**

DirectionCosineMatrix&lt;frames::earth::icrf, frames::dynamic::ric&gt; The DCM from ECI to RIC. 





        

<hr>



### function ~RadialInTrackCrossTrack 

_Default destructor for_ [_**RadialInTrackCrossTrack**_](classastrea_1_1astro_1_1frames_1_1RadialInTrackCrossTrack.md) _._
```C++
astrea::astro::frames::RadialInTrackCrossTrack::~RadialInTrackCrossTrack () = default
```




<hr>

------------------------------
The documentation for this class was generated from the following file `astrea/astro/astro/frames/instances/RadialInTrackCrossTrack.hpp`

