

# Struct astrea::astro::detail::VehicleInnerBase



[**ClassList**](annotated.md) **>** [**astrea**](namespaceastrea.md) **>** [**astro**](namespaceastrea_1_1astro.md) **>** [**detail**](namespaceastrea_1_1astro_1_1detail.md) **>** [**VehicleInnerBase**](structastrea_1_1astro_1_1detail_1_1VehicleInnerBase.md)



_Pure virtual base class for vehicle inner implementations._ 

* `#include <Vehicle.hpp>`





Inherited by the following classes: [astrea::astro::detail::VehicleInner](structastrea_1_1astro_1_1detail_1_1VehicleInner.md)
































## Public Functions

| Type | Name |
| ---: | :--- |
| virtual std::unique\_ptr&lt; [**VehicleInnerBase**](structastrea_1_1astro_1_1detail_1_1VehicleInnerBase.md) &gt; | [**clone**](#function-clone) () const = 0<br>_Clones the vehicle inner implementation._  |
| virtual Unitless | [**get\_coefficient\_of\_drag**](#function-get_coefficient_of_drag) (const [**State**](classastrea_1_1astro_1_1State.md) & state) const = 0<br>_Gets the coefficient of drag of the vehicle._  |
| virtual Unitless | [**get\_coefficient\_of\_lift**](#function-get_coefficient_of_lift) (const [**State**](classastrea_1_1astro_1_1State.md) & state) const = 0<br>_Gets the coefficient of lift of the vehicle._  |
| virtual Unitless | [**get\_coefficient\_of\_reflectivity**](#function-get_coefficient_of_reflectivity) (const [**State**](classastrea_1_1astro_1_1State.md) & state) const = 0<br>_Gets the coefficient of reflectivity of the vehicle._  |
| virtual [**Perturbation**](structastrea_1_1astro_1_1Perturbation.md) | [**get\_control\_authority**](#function-get_control_authority) (const [**State**](classastrea_1_1astro_1_1State.md) & state) const = 0<br>_Gets the control authority of the vehicle._  |
| virtual [**InertiaTensor**](classastrea_1_1astro_1_1InertiaTensor.md)&lt; [**frames::dynamic::body**](structastrea_1_1astro_1_1frames_1_1dynamic_1_1body.md) &gt; | [**get\_inertia\_tensor**](#function-get_inertia_tensor) (const [**State**](classastrea_1_1astro_1_1State.md) & state) const<br>_Gets the inertia tensor of the vehicle._  |
| virtual SurfaceArea | [**get\_lift\_area**](#function-get_lift_area) (const [**State**](classastrea_1_1astro_1_1State.md) & state) const = 0<br>_Gets the lift area of the vehicle._  |
| virtual Mass | [**get\_mass**](#function-get_mass) (const [**State**](classastrea_1_1astro_1_1State.md) & state) const = 0<br>_Gets the mass of the vehicle._  |
| virtual std::string | [**get\_name**](#function-get_name) () const = 0<br>_Gets the name of the vehicle._  |
| virtual const void \* | [**get\_ptr**](#function-get_ptr-12) () const = 0<br>_Gets a pointer to the internal vehicle instance._  |
| virtual void \* | [**get\_ptr**](#function-get_ptr-22) () = 0<br>_Gets a pointer to the internal vehicle instance._  |
| virtual SurfaceArea | [**get\_ram\_area**](#function-get_ram_area) (const [**State**](classastrea_1_1astro_1_1State.md) & state) const = 0<br>_Gets the ram area of the vehicle._  |
| virtual SurfaceArea | [**get\_solar\_area**](#function-get_solar_area) (const [**State**](classastrea_1_1astro_1_1State.md) & state) const = 0<br>_Gets the solar area of the vehicle._  |
| virtual const std::type\_info & | [**type**](#function-type) () const = 0<br>_Gets the type information of the internal vehicle instance._  |
| virtual  | [**~VehicleInnerBase**](#function-vehicleinnerbase) () <br>_Destructor for_ [_**VehicleInnerBase**_](structastrea_1_1astro_1_1detail_1_1VehicleInnerBase.md) _._ |




























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
virtual Unitless astrea::astro::detail::VehicleInnerBase::get_coefficient_of_drag (
    const State & state
) const = 0
```





**Parameters:**


* `state` The state of the vehicle for which to get the coefficient of drag. 



**Returns:**

Unitless The coefficient of drag of the vehicle. 





        

<hr>



### function get\_coefficient\_of\_lift 

_Gets the coefficient of lift of the vehicle._ 
```C++
virtual Unitless astrea::astro::detail::VehicleInnerBase::get_coefficient_of_lift (
    const State & state
) const = 0
```





**Parameters:**


* `state` The state of the vehicle for which to get the coefficient of lift. 



**Returns:**

Unitless The coefficient of lift of the vehicle. 





        

<hr>



### function get\_coefficient\_of\_reflectivity 

_Gets the coefficient of reflectivity of the vehicle._ 
```C++
virtual Unitless astrea::astro::detail::VehicleInnerBase::get_coefficient_of_reflectivity (
    const State & state
) const = 0
```





**Parameters:**


* `state` The state of the vehicle for which to get the coefficient of reflectivity. 



**Returns:**

Unitless The coefficient of reflectivity of the vehicle. 





        

<hr>



### function get\_control\_authority 

_Gets the control authority of the vehicle._ 
```C++
virtual Perturbation astrea::astro::detail::VehicleInnerBase::get_control_authority (
    const State & state
) const = 0
```





**Parameters:**


* `state` The state of the vehicle for which to get the control authority. 



**Returns:**

[**Perturbation**](structastrea_1_1astro_1_1Perturbation.md) The control force and torque of the vehicle. 





        

<hr>



### function get\_inertia\_tensor 

_Gets the inertia tensor of the vehicle._ 
```C++
inline virtual InertiaTensor < frames::dynamic::body > astrea::astro::detail::VehicleInnerBase::get_inertia_tensor (
    const State & state
) const
```





**Parameters:**


* `state` The state of the vehicle for which to get the inertia tensor. 



**Returns:**

InertiaTensor&lt;frames::dynamic::body&gt; The inertia tensor of the vehicle. 





        

<hr>



### function get\_lift\_area 

_Gets the lift area of the vehicle._ 
```C++
virtual SurfaceArea astrea::astro::detail::VehicleInnerBase::get_lift_area (
    const State & state
) const = 0
```





**Parameters:**


* `state` The state of the vehicle for which to get the lift area. 



**Returns:**

SurfaceArea The lift area of the vehicle. 





        

<hr>



### function get\_mass 

_Gets the mass of the vehicle._ 
```C++
virtual Mass astrea::astro::detail::VehicleInnerBase::get_mass (
    const State & state
) const = 0
```





**Parameters:**


* `state` The state of the vehicle for which to get the mass. 



**Returns:**

Mass The mass of the vehicle. 





        

<hr>



### function get\_name 

_Gets the name of the vehicle._ 
```C++
virtual std::string astrea::astro::detail::VehicleInnerBase::get_name () const = 0
```





**Returns:**

std::string The name of the vehicle. 





        

<hr>



### function get\_ptr [1/2]

_Gets a pointer to the internal vehicle instance._ 
```C++
virtual const void * astrea::astro::detail::VehicleInnerBase::get_ptr () const = 0
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
virtual SurfaceArea astrea::astro::detail::VehicleInnerBase::get_ram_area (
    const State & state
) const = 0
```





**Parameters:**


* `state` The state of the vehicle for which to get the ram area. 



**Returns:**

SurfaceArea The ram area of the vehicle. 





        

<hr>



### function get\_solar\_area 

_Gets the solar area of the vehicle._ 
```C++
virtual SurfaceArea astrea::astro::detail::VehicleInnerBase::get_solar_area (
    const State & state
) const = 0
```





**Parameters:**


* `state` The state of the vehicle for which to get the solar area. 



**Returns:**

SurfaceArea The solar area of the vehicle. 





        

<hr>



### function type 

_Gets the type information of the internal vehicle instance._ 
```C++
virtual const std::type_info & astrea::astro::detail::VehicleInnerBase::type () const = 0
```





**Returns:**

const std::type\_info& The type information of the internal vehicle instance. 





        

<hr>



### function ~VehicleInnerBase 

_Destructor for_ [_**VehicleInnerBase**_](structastrea_1_1astro_1_1detail_1_1VehicleInnerBase.md) _._
```C++
inline virtual astrea::astro::detail::VehicleInnerBase::~VehicleInnerBase () 
```




<hr>

------------------------------
The documentation for this class was generated from the following file `astrea/astro/astro/platforms/Vehicle.hpp`

