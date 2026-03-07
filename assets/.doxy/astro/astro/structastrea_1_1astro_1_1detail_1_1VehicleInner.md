

# Struct astrea::astro::detail::VehicleInner

**template &lt;typename T&gt;**



[**ClassList**](annotated.md) **>** [**astrea**](namespaceastrea.md) **>** [**astro**](namespaceastrea_1_1astro.md) **>** [**detail**](namespaceastrea_1_1astro_1_1detail.md) **>** [**VehicleInner**](structastrea_1_1astro_1_1detail_1_1VehicleInner.md)



_A template class for vehicle inner implementations._ [More...](#detailed-description)

* `#include <Vehicle.hpp>`



Inherits the following classes: [astrea::astro::detail::VehicleInnerBase](structastrea_1_1astro_1_1detail_1_1VehicleInnerBase.md)


























## Public Attributes

| Type | Name |
| ---: | :--- |
|  T | [**\_value**](#variable-_value)  <br>_The value of the vehicle inner implementation, which is the user-defined vehicle type._  |
















































## Public Functions

| Type | Name |
| ---: | :--- |
|   | [**VehicleInner**](#function-vehicleinner-15) () = default<br>_Default constructor for_ [_**VehicleInner**_](structastrea_1_1astro_1_1detail_1_1VehicleInner.md) _._ |
|   | [**VehicleInner**](#function-vehicleinner-25) (const [**VehicleInner**](structastrea_1_1astro_1_1detail_1_1VehicleInner.md) &) = delete<br>_Deleted copy assignment operator._  |
|   | [**VehicleInner**](#function-vehicleinner-35) ([**VehicleInner**](structastrea_1_1astro_1_1detail_1_1VehicleInner.md) &&) = delete<br>_Deleted move assignment operator._  |
|   | [**VehicleInner**](#function-vehicleinner-45) (const T & x) <br>_Constructs a_ [_**VehicleInner**_](structastrea_1_1astro_1_1detail_1_1VehicleInner.md) _with a given value._ |
|   | [**VehicleInner**](#function-vehicleinner-55) (T && x) <br>_Constructs a_ [_**VehicleInner**_](structastrea_1_1astro_1_1detail_1_1VehicleInner.md) _with a given value._ |
| virtual std::unique\_ptr&lt; [**VehicleInnerBase**](structastrea_1_1astro_1_1detail_1_1VehicleInnerBase.md) &gt; | [**clone**](#function-clone) () const<br>_Clones the vehicle inner implementation._  |
| virtual Unitless | [**get\_coefficient\_of\_drag**](#function-get_coefficient_of_drag) () const<br>_Gets the coefficient of drag of the vehicle or a default value._  |
| virtual Unitless | [**get\_coefficient\_of\_lift**](#function-get_coefficient_of_lift) () const<br>_Gets the coefficient of lift of the vehicle or a default value._  |
| virtual Unitless | [**get\_coefficient\_of\_reflectivity**](#function-get_coefficient_of_reflectivity) () const<br>_Gets the coefficient of reflectivity of the vehicle or a default value._  |
| virtual [**AccelerationVector**](namespaceastrea_1_1astro.md#typedef-accelerationvector)&lt; frames::earth::icrf &gt; | [**get\_inertial\_acceleration**](#function-get_inertial_acceleration) (const [**Date**](classastrea_1_1astro_1_1Date.md) & date) override const<br>_Get the acceleration of the frame in Earth-Centered Inertial coordinates._  |
| virtual [**RadiusVector**](namespaceastrea_1_1astro.md#typedef-radiusvector)&lt; frames::earth::icrf &gt; | [**get\_inertial\_position**](#function-get_inertial_position) (const [**Date**](classastrea_1_1astro_1_1Date.md) & date) override const<br>_Get the position of the frame in Earth-Centered Inertial coordinates._  |
| virtual [**VelocityVector**](namespaceastrea_1_1astro.md#typedef-velocityvector)&lt; frames::earth::icrf &gt; | [**get\_inertial\_velocity**](#function-get_inertial_velocity) (const [**Date**](classastrea_1_1astro_1_1Date.md) & date) override const<br>_Get the velocity of the frame in Earth-Centered Inertial coordinates._  |
| virtual SurfaceArea | [**get\_lift\_area**](#function-get_lift_area) () const<br>_Gets the lift area of the vehicle or a default value._  |
| virtual Mass | [**get\_mass**](#function-get_mass) () const<br>_Gets the mass of the vehicle._  |
| virtual std::string | [**get\_name**](#function-get_name) () override const<br>_Gets the name of the vehicle._  |
| virtual const void \* | [**get\_ptr**](#function-get_ptr-12) () const<br>_Gets a pointer to the internal vehicle instance._  |
| virtual void \* | [**get\_ptr**](#function-get_ptr-22) () <br>_Gets a pointer to the internal vehicle instance._  |
| virtual SurfaceArea | [**get\_ram\_area**](#function-get_ram_area) () const<br>_Gets the ram area of the vehicle or a default value._  |
| virtual SurfaceArea | [**get\_solar\_area**](#function-get_solar_area) () const<br>_Gets the solar area of the vehicle or a default value._  |
|  [**VehicleInner**](structastrea_1_1astro_1_1detail_1_1VehicleInner.md) & | [**operator=**](#function-operator) (const [**VehicleInner**](structastrea_1_1astro_1_1detail_1_1VehicleInner.md) &) = delete<br>_Deleted copy assignment operator._  |
|  [**VehicleInner**](structastrea_1_1astro_1_1detail_1_1VehicleInner.md) & | [**operator=**](#function-operator_1) ([**VehicleInner**](structastrea_1_1astro_1_1detail_1_1VehicleInner.md) &&) = delete<br>_Deleted move assignment operator._  |
|   | [**requires**](#function-requires-112) (!HasGetRamArea&lt; U &gt;) const<br>_Gets the default ram area of the vehicle._  |
|   | [**requires**](#function-requires-212) (HasGetRamArea&lt; U &gt;) const<br>_Gets the ram area of the vehicle._  |
|   | [**requires**](#function-requires-312) (!HasGetLiftArea&lt; U &gt;) const<br>_Gets the default lift area of the vehicle._  |
|   | [**requires**](#function-requires-412) (HasGetLiftArea&lt; U &gt;) const<br>_Gets the lift area of the vehicle._  |
|   | [**requires**](#function-requires-512) (!HasGetSolarArea&lt; U &gt;) const<br>_Gets the default solar area of the vehicle._  |
|   | [**requires**](#function-requires-612) (HasGetSolarArea&lt; U &gt;) const<br>_Gets the solar area of the vehicle._  |
|   | [**requires**](#function-requires-712) (!HasGetCoefficientOfDrag&lt; U &gt;) const<br>_Gets the default coefficient of drag of the vehicle._  |
|   | [**requires**](#function-requires-812) (HasGetCoefficientOfDrag&lt; U &gt;) const<br>_Gets the coefficient of drag of the vehicle._  |
|   | [**requires**](#function-requires-912) (!HasGetCoefficientOfLift&lt; U &gt;) const<br>_Gets the default coefficient of lift of the vehicle._  |
|   | [**requires**](#function-requires-1012) (HasGetCoefficientOfLift&lt; U &gt;) const<br>_Gets the coefficient of lift of the vehicle._  |
|   | [**requires**](#function-requires-1112) (!HasGetCoefficientOfReflectivity&lt; U &gt;) const<br>_Gets the default coefficient of reflectivity of the vehicle._  |
|   | [**requires**](#function-requires-1212) (HasGetCoefficientOfReflectivity&lt; U &gt;) const<br>_Gets the coefficient of reflectivity of the vehicle._  |


## Public Functions inherited from astrea::astro::detail::VehicleInnerBase

See [astrea::astro::detail::VehicleInnerBase](structastrea_1_1astro_1_1detail_1_1VehicleInnerBase.md)

| Type | Name |
| ---: | :--- |
| virtual std::unique\_ptr&lt; [**VehicleInnerBase**](structastrea_1_1astro_1_1detail_1_1VehicleInnerBase.md) &gt; | [**clone**](structastrea_1_1astro_1_1detail_1_1VehicleInnerBase.md#function-clone) () const = 0<br>_Clones the vehicle inner implementation._  |
| virtual Unitless | [**get\_coefficient\_of\_drag**](structastrea_1_1astro_1_1detail_1_1VehicleInnerBase.md#function-get_coefficient_of_drag) () const = 0<br>_Gets the coefficient of drag of the vehicle._  |
| virtual Unitless | [**get\_coefficient\_of\_lift**](structastrea_1_1astro_1_1detail_1_1VehicleInnerBase.md#function-get_coefficient_of_lift) () const = 0<br>_Gets the coefficient of lift of the vehicle._  |
| virtual Unitless | [**get\_coefficient\_of\_reflectivity**](structastrea_1_1astro_1_1detail_1_1VehicleInnerBase.md#function-get_coefficient_of_reflectivity) () const = 0<br>_Gets the coefficient of reflectivity of the vehicle._  |
| virtual SurfaceArea | [**get\_lift\_area**](structastrea_1_1astro_1_1detail_1_1VehicleInnerBase.md#function-get_lift_area) () const = 0<br>_Gets the lift area of the vehicle._  |
| virtual Mass | [**get\_mass**](structastrea_1_1astro_1_1detail_1_1VehicleInnerBase.md#function-get_mass) () const = 0<br>_Gets the mass of the vehicle._  |
| virtual const void \* | [**get\_ptr**](structastrea_1_1astro_1_1detail_1_1VehicleInnerBase.md#function-get_ptr-12) () const = 0<br>_Gets a pointer to the internal vehicle instance._  |
| virtual void \* | [**get\_ptr**](structastrea_1_1astro_1_1detail_1_1VehicleInnerBase.md#function-get_ptr-22) () = 0<br>_Gets a pointer to the internal vehicle instance._  |
| virtual SurfaceArea | [**get\_ram\_area**](structastrea_1_1astro_1_1detail_1_1VehicleInnerBase.md#function-get_ram_area) () const = 0<br>_Gets the ram area of the vehicle._  |
| virtual SurfaceArea | [**get\_solar\_area**](structastrea_1_1astro_1_1detail_1_1VehicleInnerBase.md#function-get_solar_area) () const = 0<br>_Gets the solar area of the vehicle._  |
| virtual  | [**~VehicleInnerBase**](structastrea_1_1astro_1_1detail_1_1VehicleInnerBase.md#function-vehicleinnerbase) () <br>_Destructor for_ [_**VehicleInnerBase**_](structastrea_1_1astro_1_1detail_1_1VehicleInnerBase.md) _._ |


## Public Functions inherited from astrea::astro::FrameReference

See [astrea::astro::FrameReference](classastrea_1_1astro_1_1FrameReference.md)

| Type | Name |
| ---: | :--- |
|   | [**FrameReference**](classastrea_1_1astro_1_1FrameReference.md#function-framereference) () = default<br>_Default constructor for_ [_**FrameReference**_](classastrea_1_1astro_1_1FrameReference.md) _._ |
| virtual [**CartesianVector**](classastrea_1_1astro_1_1CartesianVector.md)&lt; Acceleration, frames::earth::icrf &gt; | [**get\_inertial\_acceleration**](classastrea_1_1astro_1_1FrameReference.md#function-get_inertial_acceleration) (const [**Date**](classastrea_1_1astro_1_1Date.md) & date) const<br>_Get the acceleration of the frame in Earth-Centered Inertial coordinates._  |
| virtual [**CartesianVector**](classastrea_1_1astro_1_1CartesianVector.md)&lt; Distance, frames::earth::icrf &gt; | [**get\_inertial\_position**](classastrea_1_1astro_1_1FrameReference.md#function-get_inertial_position) (const [**Date**](classastrea_1_1astro_1_1Date.md) & date) const = 0<br>_Get the position of the frame in Earth-Centered Inertial coordinates._  |
| virtual [**CartesianVector**](classastrea_1_1astro_1_1CartesianVector.md)&lt; Velocity, frames::earth::icrf &gt; | [**get\_inertial\_velocity**](classastrea_1_1astro_1_1FrameReference.md#function-get_inertial_velocity) (const [**Date**](classastrea_1_1astro_1_1Date.md) & date) const = 0<br>_Get the velocity of the frame in Earth-Centered Inertial coordinates._  |
| virtual std::string | [**get\_name**](classastrea_1_1astro_1_1FrameReference.md#function-get_name) () const = 0<br>_Get the name of the frame reference._  |
| virtual  | [**~FrameReference**](classastrea_1_1astro_1_1FrameReference.md#function-framereference) () = default<br>_Default destructor for_ [_**FrameReference**_](classastrea_1_1astro_1_1FrameReference.md) _._ |
















































































## Detailed Description




**Template parameters:**


* `T` The type of the vehicle implementation. 




    
## Public Attributes Documentation




### variable \_value 

_The value of the vehicle inner implementation, which is the user-defined vehicle type._ 
```C++
T astrea::astro::detail::VehicleInner< T >::_value;
```




<hr>
## Public Functions Documentation




### function VehicleInner [1/5]

_Default constructor for_ [_**VehicleInner**_](structastrea_1_1astro_1_1detail_1_1VehicleInner.md) _._
```C++
astrea::astro::detail::VehicleInner::VehicleInner () = default
```




<hr>



### function VehicleInner [2/5]

_Deleted copy assignment operator._ 
```C++
astrea::astro::detail::VehicleInner::VehicleInner (
    const VehicleInner &
) = delete
```




<hr>



### function VehicleInner [3/5]

_Deleted move assignment operator._ 
```C++
astrea::astro::detail::VehicleInner::VehicleInner (
    VehicleInner &&
) = delete
```




<hr>



### function VehicleInner [4/5]

_Constructs a_ [_**VehicleInner**_](structastrea_1_1astro_1_1detail_1_1VehicleInner.md) _with a given value._
```C++
inline explicit astrea::astro::detail::VehicleInner::VehicleInner (
    const T & x
) 
```





**Parameters:**


* `x` The value to initialize the vehicle inner implementation. 




        

<hr>



### function VehicleInner [5/5]

_Constructs a_ [_**VehicleInner**_](structastrea_1_1astro_1_1detail_1_1VehicleInner.md) _with a given value._
```C++
inline explicit astrea::astro::detail::VehicleInner::VehicleInner (
    T && x
) 
```





**Parameters:**


* `x` The value to initialize the vehicle inner implementation. 




        

<hr>



### function clone 

_Clones the vehicle inner implementation._ 
```C++
inline virtual std::unique_ptr< VehicleInnerBase > astrea::astro::detail::VehicleInner::clone () const
```





**Returns:**

std::unique\_ptr&lt;VehicleInnerBase&gt; A unique pointer to the cloned vehicle inner implementation. 





        
Implements [*astrea::astro::detail::VehicleInnerBase::clone*](structastrea_1_1astro_1_1detail_1_1VehicleInnerBase.md#function-clone)


<hr>



### function get\_coefficient\_of\_drag 

_Gets the coefficient of drag of the vehicle or a default value._ 
```C++
inline virtual Unitless astrea::astro::detail::VehicleInner::get_coefficient_of_drag () const
```





**Returns:**

Unitless The coefficient of drag of the vehicle. 





        
Implements [*astrea::astro::detail::VehicleInnerBase::get\_coefficient\_of\_drag*](structastrea_1_1astro_1_1detail_1_1VehicleInnerBase.md#function-get_coefficient_of_drag)


<hr>



### function get\_coefficient\_of\_lift 

_Gets the coefficient of lift of the vehicle or a default value._ 
```C++
inline virtual Unitless astrea::astro::detail::VehicleInner::get_coefficient_of_lift () const
```





**Returns:**

Unitless The coefficient of lift of the vehicle. 





        
Implements [*astrea::astro::detail::VehicleInnerBase::get\_coefficient\_of\_lift*](structastrea_1_1astro_1_1detail_1_1VehicleInnerBase.md#function-get_coefficient_of_lift)


<hr>



### function get\_coefficient\_of\_reflectivity 

_Gets the coefficient of reflectivity of the vehicle or a default value._ 
```C++
inline virtual Unitless astrea::astro::detail::VehicleInner::get_coefficient_of_reflectivity () const
```





**Returns:**

Unitless The coefficient of reflectivity of the vehicle. 





        
Implements [*astrea::astro::detail::VehicleInnerBase::get\_coefficient\_of\_reflectivity*](structastrea_1_1astro_1_1detail_1_1VehicleInnerBase.md#function-get_coefficient_of_reflectivity)


<hr>



### function get\_inertial\_acceleration 

_Get the acceleration of the frame in Earth-Centered Inertial coordinates._ 
```C++
inline virtual AccelerationVector < frames::earth::icrf > astrea::astro::detail::VehicleInner::get_inertial_acceleration (
    const Date & date
) override const
```





**Parameters:**


* `date` The date for which to get the acceleration. 



**Returns:**

AccelerationVector&lt;frames::earth::icrf&gt; 





        
Implements [*astrea::astro::FrameReference::get\_inertial\_acceleration*](classastrea_1_1astro_1_1FrameReference.md#function-get_inertial_acceleration)


<hr>



### function get\_inertial\_position 

_Get the position of the frame in Earth-Centered Inertial coordinates._ 
```C++
inline virtual RadiusVector < frames::earth::icrf > astrea::astro::detail::VehicleInner::get_inertial_position (
    const Date & date
) override const
```





**Parameters:**


* `date` The date for which to get the position. 



**Returns:**

RadiusVector&lt;frames::earth::icrf&gt; 





        
Implements [*astrea::astro::FrameReference::get\_inertial\_position*](classastrea_1_1astro_1_1FrameReference.md#function-get_inertial_position)


<hr>



### function get\_inertial\_velocity 

_Get the velocity of the frame in Earth-Centered Inertial coordinates._ 
```C++
inline virtual VelocityVector < frames::earth::icrf > astrea::astro::detail::VehicleInner::get_inertial_velocity (
    const Date & date
) override const
```





**Parameters:**


* `date` The date for which to get the velocity. 



**Returns:**

VelocityVector&lt;frames::earth::icrf&gt; 





        
Implements [*astrea::astro::FrameReference::get\_inertial\_velocity*](classastrea_1_1astro_1_1FrameReference.md#function-get_inertial_velocity)


<hr>



### function get\_lift\_area 

_Gets the lift area of the vehicle or a default value._ 
```C++
inline virtual SurfaceArea astrea::astro::detail::VehicleInner::get_lift_area () const
```





**Returns:**

SurfaceArea The lift area of the vehicle. 





        
Implements [*astrea::astro::detail::VehicleInnerBase::get\_lift\_area*](structastrea_1_1astro_1_1detail_1_1VehicleInnerBase.md#function-get_lift_area)


<hr>



### function get\_mass 

_Gets the mass of the vehicle._ 
```C++
inline virtual Mass astrea::astro::detail::VehicleInner::get_mass () const
```





**Returns:**

Mass The mass of the vehicle. 





        
Implements [*astrea::astro::detail::VehicleInnerBase::get\_mass*](structastrea_1_1astro_1_1detail_1_1VehicleInnerBase.md#function-get_mass)


<hr>



### function get\_name 

_Gets the name of the vehicle._ 
```C++
inline virtual std::string astrea::astro::detail::VehicleInner::get_name () override const
```





**Returns:**

std::string The name of the vehicle. 





        
Implements [*astrea::astro::FrameReference::get\_name*](classastrea_1_1astro_1_1FrameReference.md#function-get_name)


<hr>



### function get\_ptr [1/2]

_Gets a pointer to the internal vehicle instance._ 
```C++
inline virtual const void * astrea::astro::detail::VehicleInner::get_ptr () const
```





**Returns:**

const void\* A pointer to the internal vehicle instance. 





        
Implements [*astrea::astro::detail::VehicleInnerBase::get\_ptr*](structastrea_1_1astro_1_1detail_1_1VehicleInnerBase.md#function-get_ptr-12)


<hr>



### function get\_ptr [2/2]

_Gets a pointer to the internal vehicle instance._ 
```C++
inline virtual void * astrea::astro::detail::VehicleInner::get_ptr () 
```





**Returns:**

void\* A pointer to the internal vehicle instance. 





        
Implements [*astrea::astro::detail::VehicleInnerBase::get\_ptr*](structastrea_1_1astro_1_1detail_1_1VehicleInnerBase.md#function-get_ptr-22)


<hr>



### function get\_ram\_area 

_Gets the ram area of the vehicle or a default value._ 
```C++
inline virtual SurfaceArea astrea::astro::detail::VehicleInner::get_ram_area () const
```





**Returns:**

SurfaceArea The ram area of the vehicle. 





        
Implements [*astrea::astro::detail::VehicleInnerBase::get\_ram\_area*](structastrea_1_1astro_1_1detail_1_1VehicleInnerBase.md#function-get_ram_area)


<hr>



### function get\_solar\_area 

_Gets the solar area of the vehicle or a default value._ 
```C++
inline virtual SurfaceArea astrea::astro::detail::VehicleInner::get_solar_area () const
```





**Returns:**

SurfaceArea The solar area of the vehicle. 





        
Implements [*astrea::astro::detail::VehicleInnerBase::get\_solar\_area*](structastrea_1_1astro_1_1detail_1_1VehicleInnerBase.md#function-get_solar_area)


<hr>



### function operator= 

_Deleted copy assignment operator._ 
```C++
VehicleInner & astrea::astro::detail::VehicleInner::operator= (
    const VehicleInner &
) = delete
```




<hr>



### function operator= 

_Deleted move assignment operator._ 
```C++
VehicleInner & astrea::astro::detail::VehicleInner::operator= (
    VehicleInner &&
) = delete
```




<hr>



### function requires [1/12]

_Gets the default ram area of the vehicle._ 
```C++
template<typename U>
inline astrea::astro::detail::VehicleInner::requires (
    !HasGetRamArea< U >
) const
```





**Template parameters:**


* `U` The type of the vehicle implementation. 



**Parameters:**


* `value` The vehicle instance to get the ram area from. 



**Returns:**

SurfaceArea The ram area of the vehicle. 





        

<hr>



### function requires [2/12]

_Gets the ram area of the vehicle._ 
```C++
template<typename U>
inline astrea::astro::detail::VehicleInner::requires (
    HasGetRamArea< U >
) const
```





**Template parameters:**


* `U` The type of the vehicle implementation. 



**Parameters:**


* `value` The vehicle instance to get the ram area from. 



**Returns:**

SurfaceArea The ram area of the vehicle. 





        

<hr>



### function requires [3/12]

_Gets the default lift area of the vehicle._ 
```C++
template<typename U>
inline astrea::astro::detail::VehicleInner::requires (
    !HasGetLiftArea< U >
) const
```





**Template parameters:**


* `U` The type of the vehicle implementation. 



**Parameters:**


* `value` The vehicle instance to get the lift area from. 



**Returns:**

SurfaceArea The lift area of the vehicle. 





        

<hr>



### function requires [4/12]

_Gets the lift area of the vehicle._ 
```C++
template<typename U>
inline astrea::astro::detail::VehicleInner::requires (
    HasGetLiftArea< U >
) const
```





**Template parameters:**


* `U` The type of the vehicle implementation. 



**Parameters:**


* `value` The vehicle instance to get the lift area from. 



**Returns:**

SurfaceArea The lift area of the vehicle. 





        

<hr>



### function requires [5/12]

_Gets the default solar area of the vehicle._ 
```C++
template<typename U>
inline astrea::astro::detail::VehicleInner::requires (
    !HasGetSolarArea< U >
) const
```





**Template parameters:**


* `U` The type of the vehicle implementation. 



**Parameters:**


* `value` The vehicle instance to get the solar area from. 



**Returns:**

SurfaceArea The solar area of the vehicle. 





        

<hr>



### function requires [6/12]

_Gets the solar area of the vehicle._ 
```C++
template<typename U>
inline astrea::astro::detail::VehicleInner::requires (
    HasGetSolarArea< U >
) const
```





**Template parameters:**


* `U` The type of the vehicle implementation. 



**Parameters:**


* `value` The vehicle instance to get the solar area from. 



**Returns:**

SurfaceArea The solar area of the vehicle. 





        

<hr>



### function requires [7/12]

_Gets the default coefficient of drag of the vehicle._ 
```C++
template<typename U>
inline astrea::astro::detail::VehicleInner::requires (
    !HasGetCoefficientOfDrag< U >
) const
```





**Template parameters:**


* `U` The type of the vehicle implementation. 



**Parameters:**


* `value` The vehicle instance to get the coefficient of drag from. 



**Returns:**

Unitless The coefficient of drag of the vehicle. 





        

<hr>



### function requires [8/12]

_Gets the coefficient of drag of the vehicle._ 
```C++
template<typename U>
inline astrea::astro::detail::VehicleInner::requires (
    HasGetCoefficientOfDrag< U >
) const
```





**Template parameters:**


* `U` The type of the vehicle implementation. 



**Parameters:**


* `value` The vehicle instance to get the coefficient of drag from. 



**Returns:**

Unitless The coefficient of drag of the vehicle. 





        

<hr>



### function requires [9/12]

_Gets the default coefficient of lift of the vehicle._ 
```C++
template<typename U>
inline astrea::astro::detail::VehicleInner::requires (
    !HasGetCoefficientOfLift< U >
) const
```





**Template parameters:**


* `U` The type of the vehicle implementation. 



**Parameters:**


* `value` The vehicle instance to get the coefficient of lift from. 



**Returns:**

Unitless The coefficient of lift of the vehicle. 





        

<hr>



### function requires [10/12]

_Gets the coefficient of lift of the vehicle._ 
```C++
template<typename U>
inline astrea::astro::detail::VehicleInner::requires (
    HasGetCoefficientOfLift< U >
) const
```





**Template parameters:**


* `U` The type of the vehicle implementation. 



**Parameters:**


* `value` The vehicle instance to get the coefficient of lift from. 



**Returns:**

Unitless The coefficient of lift of the vehicle. 





        

<hr>



### function requires [11/12]

_Gets the default coefficient of reflectivity of the vehicle._ 
```C++
template<typename U>
inline astrea::astro::detail::VehicleInner::requires (
    !HasGetCoefficientOfReflectivity< U >
) const
```





**Template parameters:**


* `U` The type of the vehicle implementation. 



**Parameters:**


* `value` The vehicle instance to get the coefficient of reflectivity from. 



**Returns:**

Unitless The coefficient of reflectivity of the vehicle. 





        

<hr>



### function requires [12/12]

_Gets the coefficient of reflectivity of the vehicle._ 
```C++
template<typename U>
inline astrea::astro::detail::VehicleInner::requires (
    HasGetCoefficientOfReflectivity< U >
) const
```





**Template parameters:**


* `U` The type of the vehicle implementation. 



**Parameters:**


* `value` The vehicle instance to get the coefficient of reflectivity from. 



**Returns:**

Unitless The coefficient of reflectivity of the vehicle. 





        

<hr>

------------------------------
The documentation for this class was generated from the following file `astrea/astro/astro/platforms/Vehicle.hpp`

