

# Class astrea::astro::NullVehicle



[**ClassList**](annotated.md) **>** [**astrea**](namespaceastrea.md) **>** [**astro**](namespaceastrea_1_1astro.md) **>** [**NullVehicle**](classastrea_1_1astro_1_1NullVehicle.md)



_A class representing a null vehicle in the astrea astro platform. This class is used as a placeholder for vehicles that do not have a defined state or mass._ 

* `#include <NullVehicle.hpp>`



Inherits the following classes: [astrea::astro::FrameReference](classastrea_1_1astro_1_1FrameReference.md)






















































## Public Functions

| Type | Name |
| ---: | :--- |
|   | [**NullVehicle**](#function-nullvehicle) ([**const**](classastrea_1_1astro_1_1CartesianVector.md) [**Mass**](classastrea_1_1astro_1_1CartesianVector.md) & mass=0.0 \*mp\_units::si::unit\_symbols::kg) <br>_Constructs a_ [_**NullVehicle**_](classastrea_1_1astro_1_1NullVehicle.md) _with an initial state and mass._ |
|  [**NullVehicle**](classastrea_1_1astro_1_1NullVehicle.md) \* | [**clone**](#function-clone) () const<br>_Clone the_ [_**NullVehicle**_](classastrea_1_1astro_1_1NullVehicle.md) _object._ |
| virtual [**CartesianVector**](classastrea_1_1astro_1_1CartesianVector.md)&lt; [**Acceleration**](classastrea_1_1astro_1_1CartesianVector.md), [**frames::earth::icrf**](structastrea_1_1astro_1_1InertialFrame.md) &gt; | [**get\_inertial\_acceleration**](#function-get_inertial_acceleration) ([**const**](classastrea_1_1astro_1_1CartesianVector.md) [**Date**](classastrea_1_1astro_1_1Date.md) & date) const<br>_Get the acceleration of the frame in Earth-Centered Inertial coordinates._  |
| virtual [**CartesianVector**](classastrea_1_1astro_1_1CartesianVector.md)&lt; [**Distance**](classastrea_1_1astro_1_1CartesianVector.md), [**frames::earth::icrf**](structastrea_1_1astro_1_1InertialFrame.md) &gt; | [**get\_inertial\_position**](#function-get_inertial_position) ([**const**](classastrea_1_1astro_1_1CartesianVector.md) [**Date**](classastrea_1_1astro_1_1Date.md) & date) const<br>_Get the position of the frame in Earth-Centered Inertial coordinates._  |
| virtual [**CartesianVector**](classastrea_1_1astro_1_1CartesianVector.md)&lt; [**Velocity**](classastrea_1_1astro_1_1CartesianVector.md), [**frames::earth::icrf**](structastrea_1_1astro_1_1InertialFrame.md) &gt; | [**get\_inertial\_velocity**](#function-get_inertial_velocity) ([**const**](classastrea_1_1astro_1_1CartesianVector.md) [**Date**](classastrea_1_1astro_1_1Date.md) & date) const<br>_Get the velocity of the frame in Earth-Centered Inertial coordinates._  |
|  [**Mass**](classastrea_1_1astro_1_1CartesianVector.md) | [**get\_mass**](#function-get_mass) () const<br>_Gets the mass of the vehicle._  |
| virtual std::string | [**get\_name**](#function-get_name) () const<br>_Gets the name of the vehicle._  |


## Public Functions inherited from astrea::astro::FrameReference

See [astrea::astro::FrameReference](classastrea_1_1astro_1_1FrameReference.md)

| Type | Name |
| ---: | :--- |
|   | [**FrameReference**](classastrea_1_1astro_1_1FrameReference.md#function-framereference) () = default<br>_Default constructor for_ [_**FrameReference**_](classastrea_1_1astro_1_1FrameReference.md) _._ |
| virtual [**CartesianVector**](classastrea_1_1astro_1_1CartesianVector.md)&lt; [**Acceleration**](classastrea_1_1astro_1_1CartesianVector.md), [**frames::earth::icrf**](structastrea_1_1astro_1_1InertialFrame.md) &gt; | [**get\_inertial\_acceleration**](classastrea_1_1astro_1_1FrameReference.md#function-get_inertial_acceleration) ([**const**](classastrea_1_1astro_1_1CartesianVector.md) [**Date**](classastrea_1_1astro_1_1Date.md) & date) const<br>_Get the acceleration of the frame in Earth-Centered Inertial coordinates._  |
| virtual [**CartesianVector**](classastrea_1_1astro_1_1CartesianVector.md)&lt; [**Distance**](classastrea_1_1astro_1_1CartesianVector.md), [**frames::earth::icrf**](structastrea_1_1astro_1_1InertialFrame.md) &gt; | [**get\_inertial\_position**](classastrea_1_1astro_1_1FrameReference.md#function-get_inertial_position) ([**const**](classastrea_1_1astro_1_1CartesianVector.md) [**Date**](classastrea_1_1astro_1_1Date.md) & date) const = 0<br>_Get the position of the frame in Earth-Centered Inertial coordinates._  |
| virtual [**CartesianVector**](classastrea_1_1astro_1_1CartesianVector.md)&lt; [**Velocity**](classastrea_1_1astro_1_1CartesianVector.md), [**frames::earth::icrf**](structastrea_1_1astro_1_1InertialFrame.md) &gt; | [**get\_inertial\_velocity**](classastrea_1_1astro_1_1FrameReference.md#function-get_inertial_velocity) ([**const**](classastrea_1_1astro_1_1CartesianVector.md) [**Date**](classastrea_1_1astro_1_1Date.md) & date) const = 0<br>_Get the velocity of the frame in Earth-Centered Inertial coordinates._  |
| virtual std::string | [**get\_name**](classastrea_1_1astro_1_1FrameReference.md#function-get_name) () const = 0<br>_Get the name of the frame reference._  |
| virtual  | [**~FrameReference**](classastrea_1_1astro_1_1FrameReference.md#function-framereference) () = default<br>_Default destructor for_ [_**FrameReference**_](classastrea_1_1astro_1_1FrameReference.md) _._ |






















































## Public Functions Documentation




### function NullVehicle 

_Constructs a_ [_**NullVehicle**_](classastrea_1_1astro_1_1NullVehicle.md) _with an initial state and mass._
```C++
astrea::astro::NullVehicle::NullVehicle (
    const  Mass & mass=0.0 *mp_units::si::unit_symbols::kg
) 
```





**Parameters:**


* `mass` The mass of the vehicle, defaulting to zero kilograms. 




        

<hr>



### function clone 

_Clone the_ [_**NullVehicle**_](classastrea_1_1astro_1_1NullVehicle.md) _object._
```C++
NullVehicle * astrea::astro::NullVehicle::clone () const
```





**Returns:**

NullVehicle\* A pointer to a new [**NullVehicle**](classastrea_1_1astro_1_1NullVehicle.md) object that is a copy of this one. 





        

<hr>



### function get\_inertial\_acceleration 

_Get the acceleration of the frame in Earth-Centered Inertial coordinates._ 
```C++
virtual CartesianVector < Acceleration , frames::earth::icrf > astrea::astro::NullVehicle::get_inertial_acceleration (
    const  Date & date
) const
```





**Parameters:**


* `date` The date for which to get the acceleration. 



**Returns:**

CartesianVector&lt;Acceleration, frames::earth::icrf&gt; 





        
Implements [*astrea::astro::FrameReference::get\_inertial\_acceleration*](classastrea_1_1astro_1_1FrameReference.md#function-get_inertial_acceleration)


<hr>



### function get\_inertial\_position 

_Get the position of the frame in Earth-Centered Inertial coordinates._ 
```C++
virtual CartesianVector < Distance , frames::earth::icrf > astrea::astro::NullVehicle::get_inertial_position (
    const  Date & date
) const
```





**Parameters:**


* `date` The date for which to get the position. 



**Returns:**

CartesianVector&lt;Distance, frames::earth::icrf&gt; 





        
Implements [*astrea::astro::FrameReference::get\_inertial\_position*](classastrea_1_1astro_1_1FrameReference.md#function-get_inertial_position)


<hr>



### function get\_inertial\_velocity 

_Get the velocity of the frame in Earth-Centered Inertial coordinates._ 
```C++
virtual CartesianVector < Velocity , frames::earth::icrf > astrea::astro::NullVehicle::get_inertial_velocity (
    const  Date & date
) const
```





**Parameters:**


* `date` The date for which to get the velocity. 



**Returns:**

CartesianVector&lt;Velocity, frames::earth::icrf&gt; 





        
Implements [*astrea::astro::FrameReference::get\_inertial\_velocity*](classastrea_1_1astro_1_1FrameReference.md#function-get_inertial_velocity)


<hr>



### function get\_mass 

_Gets the mass of the vehicle._ 
```C++
Mass astrea::astro::NullVehicle::get_mass () const
```





**Returns:**

Mass The mass of the vehicle. 





        

<hr>



### function get\_name 

_Gets the name of the vehicle._ 
```C++
virtual std::string astrea::astro::NullVehicle::get_name () const
```





**Returns:**

std::string The name of the vehicle. 





        
Implements [*astrea::astro::FrameReference::get\_name*](classastrea_1_1astro_1_1FrameReference.md#function-get_name)


<hr>

------------------------------
The documentation for this class was generated from the following file `astrea/astro/astro/platforms/vehicles/NullVehicle.hpp`

