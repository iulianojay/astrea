

# Class astrea::astro::FrameReference



[**ClassList**](annotated.md) **>** [**astrea**](namespaceastrea.md) **>** [**astro**](namespaceastrea_1_1astro.md) **>** [**FrameReference**](classastrea_1_1astro_1_1FrameReference.md)



_Base class for all frame references._ [More...](#detailed-description)

* `#include <FrameReference.hpp>`





Inherited by the following classes: [astrea::astro::NullVehicle](classastrea_1_1astro_1_1NullVehicle.md),  [astrea::astro::PayloadPlatform](classastrea_1_1astro_1_1PayloadPlatform.md),  [astrea::astro::Vehicle](classastrea_1_1astro_1_1Vehicle.md),  [astrea::astro::detail::VehicleInnerBase](structastrea_1_1astro_1_1detail_1_1VehicleInnerBase.md)
































## Public Functions

| Type | Name |
| ---: | :--- |
|   | [**FrameReference**](#function-framereference) () = default<br>_Default constructor for_ [_**FrameReference**_](classastrea_1_1astro_1_1FrameReference.md) _._ |
| virtual [**CartesianVector**](classastrea_1_1astro_1_1CartesianVector.md)&lt; Acceleration, frames::earth::icrf &gt; | [**get\_inertial\_acceleration**](#function-get_inertial_acceleration) (const [**Date**](classastrea_1_1astro_1_1Date.md) & date) const<br>_Get the acceleration of the frame in Earth-Centered Inertial coordinates._  |
| virtual [**CartesianVector**](classastrea_1_1astro_1_1CartesianVector.md)&lt; Distance, frames::earth::icrf &gt; | [**get\_inertial\_position**](#function-get_inertial_position) (const [**Date**](classastrea_1_1astro_1_1Date.md) & date) const = 0<br>_Get the position of the frame in Earth-Centered Inertial coordinates._  |
| virtual [**CartesianVector**](classastrea_1_1astro_1_1CartesianVector.md)&lt; Velocity, frames::earth::icrf &gt; | [**get\_inertial\_velocity**](#function-get_inertial_velocity) (const [**Date**](classastrea_1_1astro_1_1Date.md) & date) const = 0<br>_Get the velocity of the frame in Earth-Centered Inertial coordinates._  |
| virtual std::string | [**get\_name**](#function-get_name) () const = 0<br>_Get the name of the frame reference._  |
| virtual  | [**~FrameReference**](#function-framereference) () = default<br>_Default destructor for_ [_**FrameReference**_](classastrea_1_1astro_1_1FrameReference.md) _._ |




























## Detailed Description


This class provides a common interface for all frame references used in the astrodynamics library. It allows for easy conversion between different coordinate state/frames. 


    
## Public Functions Documentation




### function FrameReference 

_Default constructor for_ [_**FrameReference**_](classastrea_1_1astro_1_1FrameReference.md) _._
```C++
astrea::astro::FrameReference::FrameReference () = default
```



Initializes the frame reference with default values. 


        

<hr>



### function get\_inertial\_acceleration 

_Get the acceleration of the frame in Earth-Centered Inertial coordinates._ 
```C++
virtual CartesianVector < Acceleration, frames::earth::icrf > astrea::astro::FrameReference::get_inertial_acceleration (
    const Date & date
) const
```





**Parameters:**


* `date` The date for which to get the acceleration. 



**Returns:**

CartesianVector&lt;Acceleration, frames::earth::icrf&gt; 





        

<hr>



### function get\_inertial\_position 

_Get the position of the frame in Earth-Centered Inertial coordinates._ 
```C++
virtual CartesianVector < Distance, frames::earth::icrf > astrea::astro::FrameReference::get_inertial_position (
    const Date & date
) const = 0
```





**Parameters:**


* `date` The date for which to get the position. 



**Returns:**

CartesianVector&lt;Distance, frames::earth::icrf&gt; 





        

<hr>



### function get\_inertial\_velocity 

_Get the velocity of the frame in Earth-Centered Inertial coordinates._ 
```C++
virtual CartesianVector < Velocity, frames::earth::icrf > astrea::astro::FrameReference::get_inertial_velocity (
    const Date & date
) const = 0
```





**Parameters:**


* `date` The date for which to get the velocity. 



**Returns:**

CartesianVector&lt;Velocity, frames::earth::icrf&gt; 





        

<hr>



### function get\_name 

_Get the name of the frame reference._ 
```C++
virtual std::string astrea::astro::FrameReference::get_name () const = 0
```





**Returns:**

std::string The name of the frame reference. Get the name of the frame reference. 





        

<hr>



### function ~FrameReference 

_Default destructor for_ [_**FrameReference**_](classastrea_1_1astro_1_1FrameReference.md) _._
```C++
virtual astrea::astro::FrameReference::~FrameReference () = default
```




<hr>

------------------------------
The documentation for this class was generated from the following file `astrea/astro/astro/frames/FrameReference.hpp`

