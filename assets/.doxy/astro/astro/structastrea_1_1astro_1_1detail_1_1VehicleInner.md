

# Struct astrea::astro::detail::VehicleInner

**template &lt;[**typename**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) [**T**](classastrea_1_1astro_1_1DirectionCosineMatrix.md)&gt;**



[**ClassList**](annotated.md) **>** [**astrea**](namespaceastrea.md) **>** [**astro**](namespaceastrea_1_1astro.md) **>** [**detail**](namespaceastrea_1_1astro_1_1detail.md) **>** [**VehicleInner**](structastrea_1_1astro_1_1detail_1_1VehicleInner.md)



_A template class for vehicle inner implementations._ [More...](#detailed-description)

* `#include <Vehicle.hpp>`



Inherits the following classes: [astrea::astro::detail::VehicleInnerBase](structastrea_1_1astro_1_1detail_1_1VehicleInnerBase.md)






















## Public Attributes

| Type | Name |
| ---: | :--- |
|  [**T**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) | [**\_value**](#variable-_value)  <br>_The value of the vehicle inner implementation, which is the user-defined vehicle type._  |
































## Public Functions

| Type | Name |
| ---: | :--- |
|   | [**VehicleInner**](#function-vehicleinner-15) () = default<br>_Default constructor for_ [_**VehicleInner**_](structastrea_1_1astro_1_1detail_1_1VehicleInner.md) _._ |
|   | [**VehicleInner**](#function-vehicleinner-25) ([**const**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) [**VehicleInner**](structastrea_1_1astro_1_1detail_1_1VehicleInner.md) &) = delete<br>_Deleted copy assignment operator._  |
|   | [**VehicleInner**](#function-vehicleinner-35) ([**VehicleInner**](structastrea_1_1astro_1_1detail_1_1VehicleInner.md) &&) = delete<br>_Deleted move assignment operator._  |
|   | [**VehicleInner**](#function-vehicleinner-45) ([**const**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) [**T**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) & x) <br>_Constructs a_ [_**VehicleInner**_](structastrea_1_1astro_1_1detail_1_1VehicleInner.md) _with a given value._ |
|   | [**VehicleInner**](#function-vehicleinner-55) ([**T**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) && x) <br>_Constructs a_ [_**VehicleInner**_](structastrea_1_1astro_1_1detail_1_1VehicleInner.md) _with a given value._ |
| virtual std::unique\_ptr&lt; [**VehicleInnerBase**](structastrea_1_1astro_1_1detail_1_1VehicleInnerBase.md) &gt; | [**clone**](#function-clone) () const<br>_Clones the vehicle inner implementation._  |
| virtual [**Unitless**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) | [**get\_coefficient\_of\_drag**](#function-get_coefficient_of_drag) () const<br>_Gets the coefficient of drag of the vehicle or a default value._  |
| virtual [**Unitless**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) | [**get\_coefficient\_of\_lift**](#function-get_coefficient_of_lift) () const<br>_Gets the coefficient of lift of the vehicle or a default value._  |
| virtual [**Unitless**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) | [**get\_coefficient\_of\_reflectivity**](#function-get_coefficient_of_reflectivity) () const<br>_Gets the coefficient of reflectivity of the vehicle or a default value._  |
| virtual [**Perturbation**](structastrea_1_1astro_1_1Perturbation.md) | [**get\_control\_authority**](#function-get_control_authority) ([**const**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) [**State**](classastrea_1_1astro_1_1State.md) & state) const<br>_Gets the control authority of the vehicle or a default value._  |
|  [**Perturbation**](structastrea_1_1astro_1_1Perturbation.md) | [**get\_control\_authority\_impl**](#function-get_control_authority_impl-12) ([**const**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) [**U**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) &, [**const**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) [**State**](classastrea_1_1astro_1_1State.md) &) const<br>_Gets the default thrust of the vehicle._  |
|  [**Perturbation**](structastrea_1_1astro_1_1Perturbation.md) | [**get\_control\_authority\_impl**](#function-get_control_authority_impl-22) ([**const**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) [**U**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) & value, [**const**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) [**State**](classastrea_1_1astro_1_1State.md) & state) const<br>_Gets the thrust and torque of the vehicle._  |
| virtual [**InertiaTensor**](classastrea_1_1astro_1_1InertiaTensor.md)&lt; [**frames::dynamic::body**](structastrea_1_1astro_1_1frames_1_1dynamic_1_1body.md) &gt; | [**get\_inertia\_tensor**](#function-get_inertia_tensor) () const<br>_Gets the inertia tensor of the vehicle._  |
| virtual [**SurfaceArea**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) | [**get\_lift\_area**](#function-get_lift_area) () const<br>_Gets the lift area of the vehicle or a default value._  |
| virtual [**Mass**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) | [**get\_mass**](#function-get_mass) () const<br>_Gets the mass of the vehicle._  |
| virtual std::string | [**get\_name**](#function-get_name) () override const<br>_Gets the name of the vehicle._  |
|  std::string | [**get\_name\_impl**](#function-get_name_impl-12) ([**const**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) [**U**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) &) const<br>_Gets the default name of the vehicle._  |
|  std::string | [**get\_name\_impl**](#function-get_name_impl-22) ([**const**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) [**U**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) & value) const<br>_Gets the name of the vehicle._  |
| virtual [**const**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) [**void**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) \* | [**get\_ptr**](#function-get_ptr-12) () const<br>_Gets a pointer to the internal vehicle instance._  |
| virtual [**void**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) \* | [**get\_ptr**](#function-get_ptr-22) () <br>_Gets a pointer to the internal vehicle instance._  |
| virtual [**SurfaceArea**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) | [**get\_ram\_area**](#function-get_ram_area) () const<br>_Gets the ram area of the vehicle or a default value._  |
| virtual [**SurfaceArea**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) | [**get\_solar\_area**](#function-get_solar_area) () const<br>_Gets the solar area of the vehicle or a default value._  |
|  [**VehicleInner**](structastrea_1_1astro_1_1detail_1_1VehicleInner.md) & | [**operator=**](#function-operator) ([**const**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) [**VehicleInner**](structastrea_1_1astro_1_1detail_1_1VehicleInner.md) &) = delete<br>_Deleted copy assignment operator._  |
|  [**VehicleInner**](structastrea_1_1astro_1_1detail_1_1VehicleInner.md) & | [**operator=**](#function-operator_1) ([**VehicleInner**](structastrea_1_1astro_1_1detail_1_1VehicleInner.md) &&) = delete<br>_Deleted move assignment operator._  |
| virtual [**const**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) std::type\_info & | [**type**](#function-type) () const<br>_Gets the type information of the internal vehicle instance._  |


## Public Functions inherited from astrea::astro::detail::VehicleInnerBase

See [astrea::astro::detail::VehicleInnerBase](structastrea_1_1astro_1_1detail_1_1VehicleInnerBase.md)

| Type | Name |
| ---: | :--- |
| virtual std::unique\_ptr&lt; [**VehicleInnerBase**](structastrea_1_1astro_1_1detail_1_1VehicleInnerBase.md) &gt; | [**clone**](structastrea_1_1astro_1_1detail_1_1VehicleInnerBase.md#function-clone) () const = 0<br>_Clones the vehicle inner implementation._  |
| virtual [**Unitless**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) | [**get\_coefficient\_of\_drag**](structastrea_1_1astro_1_1detail_1_1VehicleInnerBase.md#function-get_coefficient_of_drag) () const = 0<br>_Gets the coefficient of drag of the vehicle._  |
| virtual [**Unitless**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) | [**get\_coefficient\_of\_lift**](structastrea_1_1astro_1_1detail_1_1VehicleInnerBase.md#function-get_coefficient_of_lift) () const = 0<br>_Gets the coefficient of lift of the vehicle._  |
| virtual [**Unitless**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) | [**get\_coefficient\_of\_reflectivity**](structastrea_1_1astro_1_1detail_1_1VehicleInnerBase.md#function-get_coefficient_of_reflectivity) () const = 0<br>_Gets the coefficient of reflectivity of the vehicle._  |
| virtual [**Perturbation**](structastrea_1_1astro_1_1Perturbation.md) | [**get\_control\_authority**](structastrea_1_1astro_1_1detail_1_1VehicleInnerBase.md#function-get_control_authority) ([**const**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) [**State**](classastrea_1_1astro_1_1State.md) & state) const = 0<br>_Gets the control authority of the vehicle._  |
| virtual [**InertiaTensor**](classastrea_1_1astro_1_1InertiaTensor.md)&lt; [**frames::dynamic::body**](structastrea_1_1astro_1_1frames_1_1dynamic_1_1body.md) &gt; | [**get\_inertia\_tensor**](structastrea_1_1astro_1_1detail_1_1VehicleInnerBase.md#function-get_inertia_tensor) () const<br>_Gets the inertia tensor of the vehicle._  |
| virtual [**SurfaceArea**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) | [**get\_lift\_area**](structastrea_1_1astro_1_1detail_1_1VehicleInnerBase.md#function-get_lift_area) () const = 0<br>_Gets the lift area of the vehicle._  |
| virtual [**Mass**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) | [**get\_mass**](structastrea_1_1astro_1_1detail_1_1VehicleInnerBase.md#function-get_mass) () const = 0<br>_Gets the mass of the vehicle._  |
| virtual std::string | [**get\_name**](structastrea_1_1astro_1_1detail_1_1VehicleInnerBase.md#function-get_name) () const = 0<br>_Gets the name of the vehicle._  |
| virtual [**const**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) [**void**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) \* | [**get\_ptr**](structastrea_1_1astro_1_1detail_1_1VehicleInnerBase.md#function-get_ptr-12) () const = 0<br>_Gets a pointer to the internal vehicle instance._  |
| virtual [**void**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) \* | [**get\_ptr**](structastrea_1_1astro_1_1detail_1_1VehicleInnerBase.md#function-get_ptr-22) () = 0<br>_Gets a pointer to the internal vehicle instance._  |
| virtual [**SurfaceArea**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) | [**get\_ram\_area**](structastrea_1_1astro_1_1detail_1_1VehicleInnerBase.md#function-get_ram_area) () const = 0<br>_Gets the ram area of the vehicle._  |
| virtual [**SurfaceArea**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) | [**get\_solar\_area**](structastrea_1_1astro_1_1detail_1_1VehicleInnerBase.md#function-get_solar_area) () const = 0<br>_Gets the solar area of the vehicle._  |
| virtual [**const**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) std::type\_info & | [**type**](structastrea_1_1astro_1_1detail_1_1VehicleInnerBase.md#function-type) () const = 0<br>_Gets the type information of the internal vehicle instance._  |
| virtual  | [**~VehicleInnerBase**](structastrea_1_1astro_1_1detail_1_1VehicleInnerBase.md#function-vehicleinnerbase) () <br>_Destructor for_ [_**VehicleInnerBase**_](structastrea_1_1astro_1_1detail_1_1VehicleInnerBase.md) _._ |


## Public Static Functions

| Type | Name |
| ---: | :--- |
|  [**Unitless**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) | [**get\_coefficient\_of\_drag\_impl**](#function-get_coefficient_of_drag_impl-12) ([**const**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) [**U**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) &) <br>_Gets the default coefficient of drag of the vehicle._  |
|  [**Unitless**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) | [**get\_coefficient\_of\_drag\_impl**](#function-get_coefficient_of_drag_impl-22) ([**const**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) [**U**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) & value) <br>_Gets the coefficient of drag of the vehicle._  |
|  [**Unitless**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) | [**get\_coefficient\_of\_lift\_impl**](#function-get_coefficient_of_lift_impl-12) ([**const**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) [**U**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) &) <br>_Gets the default coefficient of lift of the vehicle._  |
|  [**Unitless**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) | [**get\_coefficient\_of\_lift\_impl**](#function-get_coefficient_of_lift_impl-22) ([**const**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) [**U**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) & value) <br>_Gets the coefficient of lift of the vehicle._  |
|  [**Unitless**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) | [**get\_coefficient\_of\_reflectivity\_impl**](#function-get_coefficient_of_reflectivity_impl-12) ([**const**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) [**U**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) &) <br>_Gets the default coefficient of reflectivity of the vehicle._  |
|  [**Unitless**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) | [**get\_coefficient\_of\_reflectivity\_impl**](#function-get_coefficient_of_reflectivity_impl-22) ([**const**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) [**U**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) & value) <br>_Gets the coefficient of reflectivity of the vehicle._  |
|  [**InertiaTensor**](classastrea_1_1astro_1_1InertiaTensor.md)&lt; [**frames::dynamic::body**](structastrea_1_1astro_1_1frames_1_1dynamic_1_1body.md) &gt; | [**get\_inertia\_tensor\_impl**](#function-get_inertia_tensor_impl-12) ([**const**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) [**U**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) &) <br>_Gets the default inertia tensor of the vehicle._  |
|  [**InertiaTensor**](classastrea_1_1astro_1_1InertiaTensor.md)&lt; [**frames::dynamic::body**](structastrea_1_1astro_1_1frames_1_1dynamic_1_1body.md) &gt; | [**get\_inertia\_tensor\_impl**](#function-get_inertia_tensor_impl-22) ([**const**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) [**U**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) & value) <br>_Gets the inertia tensor of the vehicle._  |
|  [**SurfaceArea**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) | [**get\_lift\_area\_impl**](#function-get_lift_area_impl-12) ([**const**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) [**U**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) &) <br>_Gets the default lift area of the vehicle._  |
|  [**SurfaceArea**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) | [**get\_lift\_area\_impl**](#function-get_lift_area_impl-22) ([**const**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) [**U**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) & value) <br>_Gets the lift area of the vehicle._  |
|  [**SurfaceArea**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) | [**get\_ram\_area\_impl**](#function-get_ram_area_impl-12) ([**const**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) [**U**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) &) <br>_Gets the default ram area of the vehicle._  |
|  [**SurfaceArea**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) | [**get\_ram\_area\_impl**](#function-get_ram_area_impl-22) ([**const**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) [**U**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) & value) <br>_Gets the ram area of the vehicle._  |
|  [**SurfaceArea**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) | [**get\_solar\_area\_impl**](#function-get_solar_area_impl-12) ([**const**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) [**U**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) &) <br>_Gets the default solar area of the vehicle._  |
|  [**SurfaceArea**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) | [**get\_solar\_area\_impl**](#function-get_solar_area_impl-22) ([**const**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) [**U**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) & value) <br>_Gets the solar area of the vehicle._  |




















































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
    const  VehicleInner &
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
    const  T & x
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



### function get\_control\_authority 

_Gets the control authority of the vehicle or a default value._ 
```C++
inline virtual Perturbation astrea::astro::detail::VehicleInner::get_control_authority (
    const  State & state
) const
```





**Parameters:**


* `state` The state of the vehicle for which to get the control authority. 



**Returns:**

[**Perturbation**](structastrea_1_1astro_1_1Perturbation.md) The control authority of the vehicle. 





        
Implements [*astrea::astro::detail::VehicleInnerBase::get\_control\_authority*](structastrea_1_1astro_1_1detail_1_1VehicleInnerBase.md#function-get_control_authority)


<hr>



### function get\_control\_authority\_impl [1/2]

_Gets the default thrust of the vehicle._ 
```C++
template<typename  U>
inline Perturbation astrea::astro::detail::VehicleInner::get_control_authority_impl (
    const  U &,
    const  State &
) const
```





**Template parameters:**


* `U` The type of the vehicle implementation. 



**Parameters:**


* `value` The vehicle instance to get the control authority from. 
* `state` The state of the vehicle for which to get the control authority. 



**Returns:**

[**Perturbation**](structastrea_1_1astro_1_1Perturbation.md) The control authority of the vehicle. 





        

<hr>



### function get\_control\_authority\_impl [2/2]

_Gets the thrust and torque of the vehicle._ 
```C++
template<typename  U>
inline Perturbation astrea::astro::detail::VehicleInner::get_control_authority_impl (
    const  U & value,
    const  State & state
) const
```





**Template parameters:**


* `U` The type of the vehicle implementation. 



**Parameters:**


* `value` The vehicle instance to get the thrust from. 
* `state` The state of the vehicle for which to get the thrust. 



**Returns:**

[**Perturbation**](structastrea_1_1astro_1_1Perturbation.md) The thrust and torque of the vehicle. 





        

<hr>



### function get\_inertia\_tensor 

_Gets the inertia tensor of the vehicle._ 
```C++
inline virtual InertiaTensor < frames::dynamic::body > astrea::astro::detail::VehicleInner::get_inertia_tensor () const
```





**Returns:**

InertiaTensor&lt;frames::dynamic::body&gt; The inertia tensor of the vehicle. 





        
Implements [*astrea::astro::detail::VehicleInnerBase::get\_inertia\_tensor*](structastrea_1_1astro_1_1detail_1_1VehicleInnerBase.md#function-get_inertia_tensor)


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





        
Implements [*astrea::astro::detail::VehicleInnerBase::get\_name*](structastrea_1_1astro_1_1detail_1_1VehicleInnerBase.md#function-get_name)


<hr>



### function get\_name\_impl [1/2]

_Gets the default name of the vehicle._ 
```C++
template<typename  U>
inline std::string astrea::astro::detail::VehicleInner::get_name_impl (
    const  U &
) const
```





**Returns:**

std::string The name of the vehicle. 





        

<hr>



### function get\_name\_impl [2/2]

_Gets the name of the vehicle._ 
```C++
template<typename  U>
inline std::string astrea::astro::detail::VehicleInner::get_name_impl (
    const  U & value
) const
```





**Template parameters:**


* `U` The type of the vehicle implementation. 



**Parameters:**


* `value` The vehicle instance to get the name from. 



**Returns:**

std::string The name of the vehicle. 





        

<hr>



### function get\_ptr [1/2]

_Gets a pointer to the internal vehicle instance._ 
```C++
inline virtual const  void * astrea::astro::detail::VehicleInner::get_ptr () const
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
    const  VehicleInner &
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



### function type 

_Gets the type information of the internal vehicle instance._ 
```C++
inline virtual const std::type_info & astrea::astro::detail::VehicleInner::type () const
```





**Returns:**

const std::type\_info& The type information of the internal vehicle instance. 





        
Implements [*astrea::astro::detail::VehicleInnerBase::type*](structastrea_1_1astro_1_1detail_1_1VehicleInnerBase.md#function-type)


<hr>
## Public Static Functions Documentation




### function get\_coefficient\_of\_drag\_impl [1/2]

_Gets the default coefficient of drag of the vehicle._ 
```C++
template<typename  U>
static inline Unitless astrea::astro::detail::VehicleInner::get_coefficient_of_drag_impl (
    const  U &
) 
```





**Template parameters:**


* `U` The type of the vehicle implementation. 



**Parameters:**


* `value` The vehicle instance to get the coefficient of drag from. 



**Returns:**

Unitless The coefficient of drag of the vehicle. 





        

<hr>



### function get\_coefficient\_of\_drag\_impl [2/2]

_Gets the coefficient of drag of the vehicle._ 
```C++
template<typename  U>
static inline Unitless astrea::astro::detail::VehicleInner::get_coefficient_of_drag_impl (
    const  U & value
) 
```





**Template parameters:**


* `U` The type of the vehicle implementation. 



**Parameters:**


* `value` The vehicle instance to get the coefficient of drag from. 



**Returns:**

Unitless The coefficient of drag of the vehicle. 





        

<hr>



### function get\_coefficient\_of\_lift\_impl [1/2]

_Gets the default coefficient of lift of the vehicle._ 
```C++
template<typename  U>
static inline Unitless astrea::astro::detail::VehicleInner::get_coefficient_of_lift_impl (
    const  U &
) 
```





**Template parameters:**


* `U` The type of the vehicle implementation. 



**Parameters:**


* `value` The vehicle instance to get the coefficient of lift from. 



**Returns:**

Unitless The coefficient of lift of the vehicle. 





        

<hr>



### function get\_coefficient\_of\_lift\_impl [2/2]

_Gets the coefficient of lift of the vehicle._ 
```C++
template<typename  U>
static inline Unitless astrea::astro::detail::VehicleInner::get_coefficient_of_lift_impl (
    const  U & value
) 
```





**Template parameters:**


* `U` The type of the vehicle implementation. 



**Parameters:**


* `value` The vehicle instance to get the coefficient of lift from. 



**Returns:**

Unitless The coefficient of lift of the vehicle. 





        

<hr>



### function get\_coefficient\_of\_reflectivity\_impl [1/2]

_Gets the default coefficient of reflectivity of the vehicle._ 
```C++
template<typename  U>
static inline Unitless astrea::astro::detail::VehicleInner::get_coefficient_of_reflectivity_impl (
    const  U &
) 
```





**Template parameters:**


* `U` The type of the vehicle implementation. 



**Parameters:**


* `value` The vehicle instance to get the coefficient of reflectivity from. 



**Returns:**

Unitless The coefficient of reflectivity of the vehicle. 





        

<hr>



### function get\_coefficient\_of\_reflectivity\_impl [2/2]

_Gets the coefficient of reflectivity of the vehicle._ 
```C++
template<typename  U>
static inline Unitless astrea::astro::detail::VehicleInner::get_coefficient_of_reflectivity_impl (
    const  U & value
) 
```





**Template parameters:**


* `U` The type of the vehicle implementation. 



**Parameters:**


* `value` The vehicle instance to get the coefficient of reflectivity from. 



**Returns:**

Unitless The coefficient of reflectivity of the vehicle. 





        

<hr>



### function get\_inertia\_tensor\_impl [1/2]

_Gets the default inertia tensor of the vehicle._ 
```C++
template<typename  U>
static inline InertiaTensor < frames::dynamic::body > astrea::astro::detail::VehicleInner::get_inertia_tensor_impl (
    const  U &
) 
```





**Template parameters:**


* `U` The type of the vehicle implementation. 



**Parameters:**


* `value` The vehicle instance to get the inertia tensor from. 



**Returns:**

InertiaTensor&lt;frames::dynamic::body&gt; The inertia tensor of the vehicle. 





        

<hr>



### function get\_inertia\_tensor\_impl [2/2]

_Gets the inertia tensor of the vehicle._ 
```C++
template<typename  U>
static inline InertiaTensor < frames::dynamic::body > astrea::astro::detail::VehicleInner::get_inertia_tensor_impl (
    const  U & value
) 
```





**Template parameters:**


* `U` The type of the vehicle implementation. 



**Parameters:**


* `value` The vehicle instance to get the inertia tensor from. 



**Returns:**

InertiaTensor&lt;frames::dynamic::body&gt; The inertia tensor of the vehicle. 





        

<hr>



### function get\_lift\_area\_impl [1/2]

_Gets the default lift area of the vehicle._ 
```C++
template<typename  U>
static inline SurfaceArea astrea::astro::detail::VehicleInner::get_lift_area_impl (
    const  U &
) 
```





**Template parameters:**


* `U` The type of the vehicle implementation. 



**Parameters:**


* `value` The vehicle instance to get the lift area from. 



**Returns:**

SurfaceArea The lift area of the vehicle. 





        

<hr>



### function get\_lift\_area\_impl [2/2]

_Gets the lift area of the vehicle._ 
```C++
template<typename  U>
static inline SurfaceArea astrea::astro::detail::VehicleInner::get_lift_area_impl (
    const  U & value
) 
```





**Template parameters:**


* `U` The type of the vehicle implementation. 



**Parameters:**


* `value` The vehicle instance to get the lift area from. 



**Returns:**

SurfaceArea The lift area of the vehicle. 





        

<hr>



### function get\_ram\_area\_impl [1/2]

_Gets the default ram area of the vehicle._ 
```C++
template<typename  U>
static inline SurfaceArea astrea::astro::detail::VehicleInner::get_ram_area_impl (
    const  U &
) 
```





**Template parameters:**


* `U` The type of the vehicle implementation. 



**Parameters:**


* `value` The vehicle instance to get the ram area from. 



**Returns:**

SurfaceArea The ram area of the vehicle. 





        

<hr>



### function get\_ram\_area\_impl [2/2]

_Gets the ram area of the vehicle._ 
```C++
template<typename  U>
static inline SurfaceArea astrea::astro::detail::VehicleInner::get_ram_area_impl (
    const  U & value
) 
```





**Template parameters:**


* `U` The type of the vehicle implementation. 



**Parameters:**


* `value` The vehicle instance to get the ram area from. 



**Returns:**

SurfaceArea The ram area of the vehicle. 





        

<hr>



### function get\_solar\_area\_impl [1/2]

_Gets the default solar area of the vehicle._ 
```C++
template<typename  U>
static inline SurfaceArea astrea::astro::detail::VehicleInner::get_solar_area_impl (
    const  U &
) 
```





**Template parameters:**


* `U` The type of the vehicle implementation. 



**Parameters:**


* `value` The vehicle instance to get the solar area from. 



**Returns:**

SurfaceArea The solar area of the vehicle. 





        

<hr>



### function get\_solar\_area\_impl [2/2]

_Gets the solar area of the vehicle._ 
```C++
template<typename  U>
static inline SurfaceArea astrea::astro::detail::VehicleInner::get_solar_area_impl (
    const  U & value
) 
```





**Template parameters:**


* `U` The type of the vehicle implementation. 



**Parameters:**


* `value` The vehicle instance to get the solar area from. 



**Returns:**

SurfaceArea The solar area of the vehicle. 





        

<hr>

------------------------------
The documentation for this class was generated from the following file `astrea/astro/astro/platforms/Vehicle.hpp`

