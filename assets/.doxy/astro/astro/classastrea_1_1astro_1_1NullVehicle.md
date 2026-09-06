

# Class astrea::astro::NullVehicle



[**ClassList**](annotated.md) **>** [**astrea**](namespaceastrea.md) **>** [**astro**](namespaceastrea_1_1astro.md) **>** [**NullVehicle**](classastrea_1_1astro_1_1NullVehicle.md)



_A class representing a null vehicle in the astrea astro platform. This class is used as a placeholder for vehicles that do not have a defined state or mass._ 

* `#include <NullVehicle.hpp>`





































## Public Functions

| Type | Name |
| ---: | :--- |
|   | [**NullVehicle**](#function-nullvehicle) (const Mass & mass=1.0 \*mp\_units::si::unit\_symbols::kg) <br>_Constructs a_ [_**NullVehicle**_](classastrea_1_1astro_1_1NullVehicle.md) _with an initial state and mass._ |
|  [**NullVehicle**](classastrea_1_1astro_1_1NullVehicle.md) \* | [**clone**](#function-clone) () const<br>_Clone the_ [_**NullVehicle**_](classastrea_1_1astro_1_1NullVehicle.md) _object._ |
|  Mass | [**get\_mass**](#function-get_mass) (const [**State**](classastrea_1_1astro_1_1State.md) & state) const<br>_Gets the mass of the vehicle._  |
|  std::string | [**get\_name**](#function-get_name) () const<br>_Gets the name of the vehicle._  |




























## Public Functions Documentation




### function NullVehicle 

_Constructs a_ [_**NullVehicle**_](classastrea_1_1astro_1_1NullVehicle.md) _with an initial state and mass._
```C++
astrea::astro::NullVehicle::NullVehicle (
    const Mass & mass=1.0 *mp_units::si::unit_symbols::kg
) 
```





**Parameters:**


* `mass` The mass of the vehicle, defaulting to one kilogram. 




        

<hr>



### function clone 

_Clone the_ [_**NullVehicle**_](classastrea_1_1astro_1_1NullVehicle.md) _object._
```C++
NullVehicle * astrea::astro::NullVehicle::clone () const
```





**Returns:**

NullVehicle\* A pointer to a new [**NullVehicle**](classastrea_1_1astro_1_1NullVehicle.md) object that is a copy of this one. 





        

<hr>



### function get\_mass 

_Gets the mass of the vehicle._ 
```C++
Mass astrea::astro::NullVehicle::get_mass (
    const State & state
) const
```





**Returns:**

Mass The mass of the vehicle. 





        

<hr>



### function get\_name 

_Gets the name of the vehicle._ 
```C++
std::string astrea::astro::NullVehicle::get_name () const
```





**Returns:**

std::string The name of the vehicle. 





        

<hr>

------------------------------
The documentation for this class was generated from the following file `astrea/astro/astro/platforms/vehicles/NullVehicle.hpp`

