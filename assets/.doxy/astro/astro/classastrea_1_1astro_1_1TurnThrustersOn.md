

# Class astrea::astro::TurnThrustersOn



[**ClassList**](annotated.md) **>** [**astrea**](namespaceastrea.md) **>** [**astro**](namespaceastrea_1_1astro.md) **>** [**TurnThrustersOn**](classastrea_1_1astro_1_1TurnThrustersOn.md)



_A class representing a_ [_**TurnThrustersOn**_](classastrea_1_1astro_1_1TurnThrustersOn.md) __[_**Event**_](classastrea_1_1astro_1_1Event.md) _in the astrea astro platform. This class is used as a placeholder for Events that do not have a defined state or mass._

* `#include <TurnThrustersOn.hpp>`





































## Public Functions

| Type | Name |
| ---: | :--- |
|   | [**TurnThrustersOn**](#function-turnthrusterson) () <br>_Constructs a_ [_**TurnThrustersOn**_](classastrea_1_1astro_1_1TurnThrustersOn.md) __[_**Event**_](classastrea_1_1astro_1_1Event.md) _that triggers at a specific altitude._ |
|  std::string | [**get\_name**](#function-get_name) () const<br>_Gets the name of the_ [_**Event**_](classastrea_1_1astro_1_1Event.md) _._ |
|  bool | [**is\_terminal**](#function-is_terminal) () const<br>_Checks if the_ [_**Event**_](classastrea_1_1astro_1_1Event.md) _is a terminal_[_**Event**_](classastrea_1_1astro_1_1Event.md) _._ |
|  Unitless | [**measure\_event**](#function-measure_event) (const Time & time, const [**State**](classastrea_1_1astro_1_1State.md) & state, const [**Vehicle**](classastrea_1_1astro_1_1Vehicle.md) & vehicle) const<br>_Detects if the_ [_**Event**_](classastrea_1_1astro_1_1Event.md) _is triggered by a_[_**Vehicle**_](classastrea_1_1astro_1_1Vehicle.md) _._ |
|  void | [**trigger\_action**](#function-trigger_action) (const Time & time, [**State**](classastrea_1_1astro_1_1State.md) & state, [**Vehicle**](classastrea_1_1astro_1_1Vehicle.md) & vehicle) const<br>_Turns on the thrusters of the_ [_**Vehicle**_](classastrea_1_1astro_1_1Vehicle.md) _._ |




























## Public Functions Documentation




### function TurnThrustersOn 

_Constructs a_ [_**TurnThrustersOn**_](classastrea_1_1astro_1_1TurnThrustersOn.md) __[_**Event**_](classastrea_1_1astro_1_1Event.md) _that triggers at a specific altitude._
```C++
astrea::astro::TurnThrustersOn::TurnThrustersOn () 
```





**Parameters:**


* `triggerAltitude` The altitude at which the [**TurnThrustersOn**](classastrea_1_1astro_1_1TurnThrustersOn.md) should trigger. Default is 0 km, which means it will trigger when the vehicle reaches the default crash radius of the central body. 



**Returns:**

[**TurnThrustersOn**](classastrea_1_1astro_1_1TurnThrustersOn.md) A [**TurnThrustersOn**](classastrea_1_1astro_1_1TurnThrustersOn.md) [**Event**](classastrea_1_1astro_1_1Event.md) that triggers at the specified altitude. 





        

<hr>



### function get\_name 

_Gets the name of the_ [_**Event**_](classastrea_1_1astro_1_1Event.md) _._
```C++
std::string astrea::astro::TurnThrustersOn::get_name () const
```





**Returns:**

std::string The name of the [**Event**](classastrea_1_1astro_1_1Event.md). 





        

<hr>



### function is\_terminal 

_Checks if the_ [_**Event**_](classastrea_1_1astro_1_1Event.md) _is a terminal_[_**Event**_](classastrea_1_1astro_1_1Event.md) _._
```C++
bool astrea::astro::TurnThrustersOn::is_terminal () const
```





**Returns:**

true If the [**Event**](classastrea_1_1astro_1_1Event.md) is a terminal [**Event**](classastrea_1_1astro_1_1Event.md). 




**Returns:**

false If the [**Event**](classastrea_1_1astro_1_1Event.md) is not a terminal [**Event**](classastrea_1_1astro_1_1Event.md). 





        

<hr>



### function measure\_event 

_Detects if the_ [_**Event**_](classastrea_1_1astro_1_1Event.md) _is triggered by a_[_**Vehicle**_](classastrea_1_1astro_1_1Vehicle.md) _._
```C++
Unitless astrea::astro::TurnThrustersOn::measure_event (
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



### function trigger\_action 

_Turns on the thrusters of the_ [_**Vehicle**_](classastrea_1_1astro_1_1Vehicle.md) _._
```C++
void astrea::astro::TurnThrustersOn::trigger_action (
    const Time & time,
    State & state,
    Vehicle & vehicle
) const
```





**Parameters:**


* `time` The current time in the integration. 
* `state` The current state of the vehicle represented as orbital elements. 
* `vehicle` The [**Vehicle**](classastrea_1_1astro_1_1Vehicle.md) to trigger the action on. 




        

<hr>

------------------------------
The documentation for this class was generated from the following file `astrea/astro/astro/propagation/event_detection/events/TurnThrustersOn.hpp`

