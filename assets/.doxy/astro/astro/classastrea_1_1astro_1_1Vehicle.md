

# Class astrea::astro::Vehicle



[**ClassList**](annotated.md) **>** [**astrea**](namespaceastrea.md) **>** [**astro**](namespaceastrea_1_1astro.md) **>** [**Vehicle**](classastrea_1_1astro_1_1Vehicle.md)



_A class representing a vehicle in the astrea astro platform. This class serves as a base for user-defined vehicles and provides a common interface._ 

* `#include <Vehicle.hpp>`





































## Public Functions

| Type | Name |
| ---: | :--- |
|   | [**Vehicle**](#function-vehicle-14) () <br>_Default constructor for_ [_**Vehicle**_](classastrea_1_1astro_1_1Vehicle.md) _._ |
|   | [**Vehicle**](#function-vehicle-24) (T && x) <br>_Constructs a_ [_**Vehicle**_](classastrea_1_1astro_1_1Vehicle.md) _with a user-defined type._ |
|   | [**Vehicle**](#function-vehicle-34) (const [**Vehicle**](classastrea_1_1astro_1_1Vehicle.md) & other) <br>_Copy constructor for_ [_**Vehicle**_](classastrea_1_1astro_1_1Vehicle.md) _._ |
|   | [**Vehicle**](#function-vehicle-44) ([**Vehicle**](classastrea_1_1astro_1_1Vehicle.md) && other) noexcept<br>_Move constructor for_ [_**Vehicle**_](classastrea_1_1astro_1_1Vehicle.md) _._ |
|  const T \* | [**extract**](#function-extract) () noexcept const<br>_Extracts the user-defined vehicle from the_ [_**Vehicle**_](classastrea_1_1astro_1_1Vehicle.md) _instance._ |
|  T \* | [**extract\_mutable\_reference**](#function-extract_mutable_reference) () noexcept<br>_Extracts the user-defined vehicle from the_ [_**Vehicle**_](classastrea_1_1astro_1_1Vehicle.md) _instance._ |
|  Unitless | [**get\_coefficient\_of\_drag**](#function-get_coefficient_of_drag) () const<br>_Gets the coefficient of drag._  |
|  Unitless | [**get\_coefficient\_of\_lift**](#function-get_coefficient_of_lift) () const<br>_Gets the coefficient of lift._  |
|  Unitless | [**get\_coefficient\_of\_reflectivity**](#function-get_coefficient_of_reflectivity) () const<br>_Gets the coefficient of reflectivity._  |
|  [**Perturbation**](structastrea_1_1astro_1_1Perturbation.md) | [**get\_control\_authority**](#function-get_control_authority) (const [**State**](classastrea_1_1astro_1_1State.md) & state) const<br>_Gets the control authority of the vehicle._  |
|  [**InertiaTensor**](classastrea_1_1astro_1_1InertiaTensor.md)&lt; [**frames::dynamic::body**](structastrea_1_1astro_1_1frames_1_1dynamic_1_1body.md) &gt; | [**get\_inertia\_tensor**](#function-get_inertia_tensor) () const<br>_Gets the inertia tensor of the vehicle._  |
|  SurfaceArea | [**get\_lift\_area**](#function-get_lift_area) () const<br>_Get the lift area of the vehicle._  |
|  Mass | [**get\_mass**](#function-get_mass) () const<br>_Gets the mass of the vehicle._  |
|  std::string | [**get\_name**](#function-get_name) () const<br>_Gets the name of the vehicle._  |
|  const void \* | [**get\_ptr**](#function-get_ptr-12) () const<br>_Gets a pointer to the internal vehicle instance._  |
|  void \* | [**get\_ptr**](#function-get_ptr-22) () <br>_Gets a pointer to the internal vehicle instance._  |
|  SurfaceArea | [**get\_ram\_area**](#function-get_ram_area) () const<br>_Get the ram area of the vehicle._  |
|  SurfaceArea | [**get\_solar\_area**](#function-get_solar_area) () const<br>_Get the solar area of the vehicle._  |
|  [**Vehicle**](classastrea_1_1astro_1_1Vehicle.md) & | [**operator=**](#function-operator) ([**Vehicle**](classastrea_1_1astro_1_1Vehicle.md) && other) noexcept<br>_Copy assignment operator for_ [_**Vehicle**_](classastrea_1_1astro_1_1Vehicle.md) _._ |
|  [**Vehicle**](classastrea_1_1astro_1_1Vehicle.md) & | [**operator=**](#function-operator_1) (const [**Vehicle**](classastrea_1_1astro_1_1Vehicle.md) & other) <br>_Move assignment operator for_ [_**Vehicle**_](classastrea_1_1astro_1_1Vehicle.md) _._ |
|  [**Vehicle**](classastrea_1_1astro_1_1Vehicle.md) & | [**operator=**](#function-operator_2) (T && x) <br>_Generic assignment operator for_ [_**Vehicle**_](classastrea_1_1astro_1_1Vehicle.md) _._ |




























## Public Functions Documentation




### function Vehicle [1/4]

_Default constructor for_ [_**Vehicle**_](classastrea_1_1astro_1_1Vehicle.md) _._
```C++
astrea::astro::Vehicle::Vehicle () 
```




<hr>



### function Vehicle [2/4]

_Constructs a_ [_**Vehicle**_](classastrea_1_1astro_1_1Vehicle.md) _with a user-defined type._
```C++
template<IsGenericallyConstructableVehicle T>
inline explicit astrea::astro::Vehicle::Vehicle (
    T && x
) 
```





**Template parameters:**


* `T` The type of the user-defined vehicle. 



**Parameters:**


* `x` The user-defined vehicle instance to initialize the [**Vehicle**](classastrea_1_1astro_1_1Vehicle.md). 




        

<hr>



### function Vehicle [3/4]

_Copy constructor for_ [_**Vehicle**_](classastrea_1_1astro_1_1Vehicle.md) _._
```C++
astrea::astro::Vehicle::Vehicle (
    const Vehicle & other
) 
```





**Parameters:**


* `other` The [**Vehicle**](classastrea_1_1astro_1_1Vehicle.md) instance to copy from. 




        

<hr>



### function Vehicle [4/4]

_Move constructor for_ [_**Vehicle**_](classastrea_1_1astro_1_1Vehicle.md) _._
```C++
astrea::astro::Vehicle::Vehicle (
    Vehicle && other
) noexcept
```





**Parameters:**


* `other` The [**Vehicle**](classastrea_1_1astro_1_1Vehicle.md) instance to move from. 




        

<hr>



### function extract 

_Extracts the user-defined vehicle from the_ [_**Vehicle**_](classastrea_1_1astro_1_1Vehicle.md) _instance._
```C++
template<IsGenericallyConstructableVehicle T>
inline const T * astrea::astro::Vehicle::extract () noexcept const
```





**Template parameters:**


* `T` The type of the user-defined vehicle to extract. 



**Returns:**

const T\* A pointer to the user-defined vehicle if it matches the type, otherwise nullptr. 





        

<hr>



### function extract\_mutable\_reference 

_Extracts the user-defined vehicle from the_ [_**Vehicle**_](classastrea_1_1astro_1_1Vehicle.md) _instance._
```C++
template<IsGenericallyConstructableVehicle T>
inline T * astrea::astro::Vehicle::extract_mutable_reference () noexcept
```





**Template parameters:**


* `T` The type of the user-defined vehicle to extract. 



**Returns:**

T\* A pointer to the user-defined vehicle if it matches the type, otherwise nullptr. 





        

<hr>



### function get\_coefficient\_of\_drag 

_Gets the coefficient of drag._ 
```C++
inline Unitless astrea::astro::Vehicle::get_coefficient_of_drag () const
```





**Returns:**

Unitless The coefficient of drag. 





        

<hr>



### function get\_coefficient\_of\_lift 

_Gets the coefficient of lift._ 
```C++
inline Unitless astrea::astro::Vehicle::get_coefficient_of_lift () const
```





**Returns:**

Unitless The coefficient of lift. 





        

<hr>



### function get\_coefficient\_of\_reflectivity 

_Gets the coefficient of reflectivity._ 
```C++
inline Unitless astrea::astro::Vehicle::get_coefficient_of_reflectivity () const
```





**Returns:**

Unitless The coefficient of reflectivity. 





        

<hr>



### function get\_control\_authority 

_Gets the control authority of the vehicle._ 
```C++
inline Perturbation astrea::astro::Vehicle::get_control_authority (
    const State & state
) const
```





**Parameters:**


* `state` The state of the vehicle for which to get the control authority. 



**Returns:**

[**Perturbation**](structastrea_1_1astro_1_1Perturbation.md) The control authority of the vehicle. 





        

<hr>



### function get\_inertia\_tensor 

_Gets the inertia tensor of the vehicle._ 
```C++
inline InertiaTensor < frames::dynamic::body > astrea::astro::Vehicle::get_inertia_tensor () const
```





**Returns:**

InertiaTensor&lt;frames::dynamic::body&gt; The inertia tensor of the vehicle. 





        

<hr>



### function get\_lift\_area 

_Get the lift area of the vehicle._ 
```C++
inline SurfaceArea astrea::astro::Vehicle::get_lift_area () const
```





**Returns:**

SurfaceArea The lift area of the vehicle. 





        

<hr>



### function get\_mass 

_Gets the mass of the vehicle._ 
```C++
inline Mass astrea::astro::Vehicle::get_mass () const
```





**Returns:**

Mass The mass of the vehicle. 





        

<hr>



### function get\_name 

_Gets the name of the vehicle._ 
```C++
inline std::string astrea::astro::Vehicle::get_name () const
```





**Returns:**

std::string The name of the vehicle. 





        

<hr>



### function get\_ptr [1/2]

_Gets a pointer to the internal vehicle instance._ 
```C++
const void * astrea::astro::Vehicle::get_ptr () const
```





**Returns:**

const void\* A pointer to the internal vehicle instance. 





        

<hr>



### function get\_ptr [2/2]

_Gets a pointer to the internal vehicle instance._ 
```C++
void * astrea::astro::Vehicle::get_ptr () 
```





**Returns:**

void\* A pointer to the internal vehicle instance. 





        

<hr>



### function get\_ram\_area 

_Get the ram area of the vehicle._ 
```C++
inline SurfaceArea astrea::astro::Vehicle::get_ram_area () const
```





**Returns:**

SurfaceArea The ram area of the vehicle. 





        

<hr>



### function get\_solar\_area 

_Get the solar area of the vehicle._ 
```C++
inline SurfaceArea astrea::astro::Vehicle::get_solar_area () const
```





**Returns:**

SurfaceArea The solar area of the vehicle. 





        

<hr>



### function operator= 

_Copy assignment operator for_ [_**Vehicle**_](classastrea_1_1astro_1_1Vehicle.md) _._
```C++
Vehicle & astrea::astro::Vehicle::operator= (
    Vehicle && other
) noexcept
```





**Returns:**

[**Vehicle**](classastrea_1_1astro_1_1Vehicle.md)& A reference to the current [**Vehicle**](classastrea_1_1astro_1_1Vehicle.md) instance. 





        

<hr>



### function operator= 

_Move assignment operator for_ [_**Vehicle**_](classastrea_1_1astro_1_1Vehicle.md) _._
```C++
Vehicle & astrea::astro::Vehicle::operator= (
    const Vehicle & other
) 
```





**Parameters:**


* `other` The [**Vehicle**](classastrea_1_1astro_1_1Vehicle.md) instance to move from. 



**Returns:**

[**Vehicle**](classastrea_1_1astro_1_1Vehicle.md)& A reference to the current [**Vehicle**](classastrea_1_1astro_1_1Vehicle.md) instance. 





        

<hr>



### function operator= 

_Generic assignment operator for_ [_**Vehicle**_](classastrea_1_1astro_1_1Vehicle.md) _._
```C++
template<IsGenericallyConstructableVehicle T>
inline Vehicle & astrea::astro::Vehicle::operator= (
    T && x
) 
```





**Template parameters:**


* `T` The type of the user-defined vehicle. 



**Parameters:**


* `x` The user-defined vehicle instance to assign to the [**Vehicle**](classastrea_1_1astro_1_1Vehicle.md). 



**Returns:**

[**Vehicle**](classastrea_1_1astro_1_1Vehicle.md)& A reference to the current [**Vehicle**](classastrea_1_1astro_1_1Vehicle.md) instance. 





        

<hr>

------------------------------
The documentation for this class was generated from the following file `astrea/astro/astro/platforms/Vehicle.hpp`

