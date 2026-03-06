

# Struct astrea::astro::detail::VehicleInnerBase



[**ClassList**](annotated.md) **>** [**astrea**](namespaceastrea.md) **>** [**astro**](namespaceastrea_1_1astro.md) **>** [**detail**](namespaceastrea_1_1astro_1_1detail.md) **>** [**VehicleInnerBase**](structastrea_1_1astro_1_1detail_1_1VehicleInnerBase.md)



_Pure virtual base class for vehicle inner implementations._ 

* `#include <Vehicle.hpp>`



Inherits the following classes: [astrea::astro::FrameReference](classastrea_1_1astro_1_1FrameReference.md)


Inherited by the following classes: [astrea::astro::detail::VehicleInner](structastrea_1_1astro_1_1detail_1_1VehicleInner.md)




















































## Public Functions

| Type | Name |
| ---: | :--- |
| virtual std::unique\_ptr&lt; [**VehicleInnerBase**](structastrea_1_1astro_1_1detail_1_1VehicleInnerBase.md) &gt; | [**clone**](#function-clone) () const = 0<br>_Clones the vehicle inner implementation._  |
| virtual [**Unitless**](classastrea_1_1astro_1_1CartesianVector.md) | [**get\_coefficient\_of\_drag**](#function-get_coefficient_of_drag) () const = 0<br>_Gets the coefficient of drag of the vehicle._  |
| virtual [**Unitless**](classastrea_1_1astro_1_1CartesianVector.md) | [**get\_coefficient\_of\_lift**](#function-get_coefficient_of_lift) () const = 0<br>_Gets the coefficient of lift of the vehicle._  |
| virtual [**Unitless**](classastrea_1_1astro_1_1CartesianVector.md) | [**get\_coefficient\_of\_reflectivity**](#function-get_coefficient_of_reflectivity) () const = 0<br>_Gets the coefficient of reflectivity of the vehicle._  |
| virtual [**SurfaceArea**](classastrea_1_1astro_1_1CartesianVector.md) | [**get\_lift\_area**](#function-get_lift_area) () const = 0<br>_Gets the lift area of the vehicle._  |
| virtual [**Mass**](classastrea_1_1astro_1_1CartesianVector.md) | [**get\_mass**](#function-get_mass) () const = 0<br>_Gets the mass of the vehicle._  |
| virtual [**const**](classastrea_1_1astro_1_1CartesianVector.md) [**void**](classastrea_1_1astro_1_1CartesianVector.md) \* | [**get\_ptr**](#function-get_ptr-12) () const = 0<br>_Gets a pointer to the internal vehicle instance._  |
| virtual [**void**](classastrea_1_1astro_1_1CartesianVector.md) \* | [**get\_ptr**](#function-get_ptr-22) () = 0<br>_Gets a pointer to the internal vehicle instance._  |
| virtual [**SurfaceArea**](classastrea_1_1astro_1_1CartesianVector.md) | [**get\_ram\_area**](#function-get_ram_area) () const = 0<br>_Gets the ram area of the vehicle._  |
| virtual [**SurfaceArea**](classastrea_1_1astro_1_1CartesianVector.md) | [**get\_solar\_area**](#function-get_solar_area) () const = 0<br>_Gets the solar area of the vehicle._  |
| virtual  | [**~VehicleInnerBase**](#function-vehicleinnerbase) () <br>_Destructor for_ [_**VehicleInnerBase**_](structastrea_1_1astro_1_1detail_1_1VehicleInnerBase.md) _._ |


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




### function clone 

_Clones the vehicle inner implementation._ 
```C++
virtual std::unique_ptr< VehicleInnerBase > astrea::astro::detail::VehicleInnerBase::clone () const = 0
```





**Returns:**

std::unique\_ptr&lt;VehicleInnerBase&gt; A unique pointer to the cloned vehicle inner implementation. 





        

<hr>



### function get\_coefficient\_of\_drag 

_Gets the coefficient of drag of the vehicle._ 
```C++
virtual Unitless astrea::astro::detail::VehicleInnerBase::get_coefficient_of_drag () const = 0
```





**Returns:**

Unitless The coefficient of drag of the vehicle. 





        

<hr>



### function get\_coefficient\_of\_lift 

_Gets the coefficient of lift of the vehicle._ 
```C++
virtual Unitless astrea::astro::detail::VehicleInnerBase::get_coefficient_of_lift () const = 0
```





**Returns:**

Unitless The coefficient of lift of the vehicle. 





        

<hr>



### function get\_coefficient\_of\_reflectivity 

_Gets the coefficient of reflectivity of the vehicle._ 
```C++
virtual Unitless astrea::astro::detail::VehicleInnerBase::get_coefficient_of_reflectivity () const = 0
```





**Returns:**

Unitless The coefficient of reflectivity of the vehicle. 





        

<hr>



### function get\_lift\_area 

_Gets the lift area of the vehicle._ 
```C++
virtual SurfaceArea astrea::astro::detail::VehicleInnerBase::get_lift_area () const = 0
```





**Returns:**

SurfaceArea The lift area of the vehicle. 





        

<hr>



### function get\_mass 

_Gets the mass of the vehicle._ 
```C++
virtual Mass astrea::astro::detail::VehicleInnerBase::get_mass () const = 0
```





**Returns:**

Mass The mass of the vehicle. 





        

<hr>



### function get\_ptr [1/2]

_Gets a pointer to the internal vehicle instance._ 
```C++
virtual const  void * astrea::astro::detail::VehicleInnerBase::get_ptr () const = 0
```





**Returns:**

const void\* A pointer to the internal vehicle instance. 





        

<hr>



### function get\_ptr [2/2]

_Gets a pointer to the internal vehicle instance._ 
```C++
virtual void * astrea::astro::detail::VehicleInnerBase::get_ptr () = 0
```





**Returns:**

void\* A pointer to the internal vehicle instance. 





        

<hr>



### function get\_ram\_area 

_Gets the ram area of the vehicle._ 
```C++
virtual SurfaceArea astrea::astro::detail::VehicleInnerBase::get_ram_area () const = 0
```





**Returns:**

SurfaceArea The ram area of the vehicle. 





        

<hr>



### function get\_solar\_area 

_Gets the solar area of the vehicle._ 
```C++
virtual SurfaceArea astrea::astro::detail::VehicleInnerBase::get_solar_area () const = 0
```





**Returns:**

SurfaceArea The solar area of the vehicle. 





        

<hr>



### function ~VehicleInnerBase 

_Destructor for_ [_**VehicleInnerBase**_](structastrea_1_1astro_1_1detail_1_1VehicleInnerBase.md) _._
```C++
inline virtual astrea::astro::detail::VehicleInnerBase::~VehicleInnerBase () 
```




<hr>

------------------------------
The documentation for this class was generated from the following file `astrea/astro/astro/platforms/Vehicle.hpp`

