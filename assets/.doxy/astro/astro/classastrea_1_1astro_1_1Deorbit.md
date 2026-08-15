

# Class astrea::astro::Deorbit



[**ClassList**](annotated.md) **>** [**astrea**](namespaceastrea.md) **>** [**astro**](namespaceastrea_1_1astro.md) **>** [**Deorbit**](classastrea_1_1astro_1_1Deorbit.md)



_A class representing a deorbit_ [_**Event**_](classastrea_1_1astro_1_1Event.md) _in the astrea astro platform. This class is used as a placeholder for Events that do not have a defined state or mass._

* `#include <Deorbit.hpp>`





































## Public Functions

| Type | Name |
| ---: | :--- |
|   | [**Deorbit**](#function-deorbit) (const Distance & triggerAltitude=0.0 \*mp\_units::si::unit\_symbols::km) <br>_Constructs a_ [_**Deorbit**_](classastrea_1_1astro_1_1Deorbit.md) __[_**Event**_](classastrea_1_1astro_1_1Event.md) _that triggers at a specific altitude._ |
|  std::string | [**get\_name**](#function-get_name) () const<br>_Gets the name of the_ [_**Event**_](classastrea_1_1astro_1_1Event.md) _._ |
|  bool | [**is\_terminal**](#function-is_terminal) () const<br>_Checks if the_ [_**Event**_](classastrea_1_1astro_1_1Event.md) _is a terminal_[_**Event**_](classastrea_1_1astro_1_1Event.md) _._ |
|  Unitless | [**measure\_event**](#function-measure_event) (const Time & time, const [**State**](classastrea_1_1astro_1_1State.md) & state, const [**Vehicle**](classastrea_1_1astro_1_1Vehicle.md) & vehicle) const<br>_Detects if the_ [_**Event**_](classastrea_1_1astro_1_1Event.md) _is triggered by a_[_**Vehicle**_](classastrea_1_1astro_1_1Vehicle.md) _._ |




























## Public Functions Documentation




### function Deorbit 

_Constructs a_ [_**Deorbit**_](classastrea_1_1astro_1_1Deorbit.md) __[_**Event**_](classastrea_1_1astro_1_1Event.md) _that triggers at a specific altitude._
```C++
astrea::astro::Deorbit::Deorbit (
    const Distance & triggerAltitude=0.0 *mp_units::si::unit_symbols::km
) 
```





**Parameters:**


* `triggerAltitude` The altitude at which the deorbit should trigger. Default is 0 km, which means it will trigger when the vehicle reaches the default crash radius of the central body. 



**Returns:**

[**Deorbit**](classastrea_1_1astro_1_1Deorbit.md) A [**Deorbit**](classastrea_1_1astro_1_1Deorbit.md) [**Event**](classastrea_1_1astro_1_1Event.md) that triggers at the specified altitude. 





        

<hr>



### function get\_name 

_Gets the name of the_ [_**Event**_](classastrea_1_1astro_1_1Event.md) _._
```C++
std::string astrea::astro::Deorbit::get_name () const
```





**Returns:**

std::string The name of the [**Event**](classastrea_1_1astro_1_1Event.md). 





        

<hr>



### function is\_terminal 

_Checks if the_ [_**Event**_](classastrea_1_1astro_1_1Event.md) _is a terminal_[_**Event**_](classastrea_1_1astro_1_1Event.md) _._
```C++
bool astrea::astro::Deorbit::is_terminal () const
```





**Returns:**

true If the [**Event**](classastrea_1_1astro_1_1Event.md) is a terminal [**Event**](classastrea_1_1astro_1_1Event.md). 




**Returns:**

false If the [**Event**](classastrea_1_1astro_1_1Event.md) is not a terminal [**Event**](classastrea_1_1astro_1_1Event.md). 





        

<hr>



### function measure\_event 

_Detects if the_ [_**Event**_](classastrea_1_1astro_1_1Event.md) _is triggered by a_[_**Vehicle**_](classastrea_1_1astro_1_1Vehicle.md) _._
```C++
Unitless astrea::astro::Deorbit::measure_event (
    const Time & time,
    const State & state,
    const Vehicle & vehicle
) const
```





**Parameters:**


* `vehicle` The [**Vehicle**](classastrea_1_1astro_1_1Vehicle.md) to check. 



**Returns:**

true If the [**Event**](classastrea_1_1astro_1_1Event.md) is triggered by the [**Vehicle**](classastrea_1_1astro_1_1Vehicle.md). 




**Returns:**

false If the [**Event**](classastrea_1_1astro_1_1Event.md) is not triggered by the [**Vehicle**](classastrea_1_1astro_1_1Vehicle.md). 





        

<hr>

------------------------------
The documentation for this class was generated from the following file `astrea/astro/astro/propagation/event_detection/events/Deorbit.hpp`

