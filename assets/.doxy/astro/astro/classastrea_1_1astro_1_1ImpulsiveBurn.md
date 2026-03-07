

# Class astrea::astro::ImpulsiveBurn



[**ClassList**](annotated.md) **>** [**astrea**](namespaceastrea.md) **>** [**astro**](namespaceastrea_1_1astro.md) **>** [**ImpulsiveBurn**](classastrea_1_1astro_1_1ImpulsiveBurn.md)



_A class representing an impulsive burn_ [_**Event**_](classastrea_1_1astro_1_1Event.md) _. It triggers when the true anomaly wraps around (i.e. at perigee), and applies the total impulsive delta-v from all thrusters to the vehicle in the velocity direction. TODO: Generalize to a scheduler of some sort and other burn triggers. TODO: Generalize burn direction. TODO: Generalize which thrusters burn._

* `#include <ImpulsiveBurn.hpp>`





































## Public Functions

| Type | Name |
| ---: | :--- |
|  std::string | [**get\_name**](#function-get_name) () const<br>_Gets the name of the_ [_**Event**_](classastrea_1_1astro_1_1Event.md) _._ |
|  bool | [**is\_terminal**](#function-is_terminal) () const<br>_Checks if the_ [_**Event**_](classastrea_1_1astro_1_1Event.md) _is a terminal_[_**Event**_](classastrea_1_1astro_1_1Event.md) _._ |
|  Unitless | [**measure\_event**](#function-measure_event) (const Time & time, const [**State**](classastrea_1_1astro_1_1State.md) & state, const [**Vehicle**](classastrea_1_1astro_1_1Vehicle.md) & vehicle) const<br>_Measures the anomaly as a trigger._  |
|  void | [**trigger\_action**](#function-trigger_action) (const Time & time, [**State**](classastrea_1_1astro_1_1State.md) & state, [**Vehicle**](classastrea_1_1astro_1_1Vehicle.md) & vehicle) const<br>_Triggers an impulsive burn._  |




























## Public Functions Documentation




### function get\_name 

_Gets the name of the_ [_**Event**_](classastrea_1_1astro_1_1Event.md) _._
```C++
std::string astrea::astro::ImpulsiveBurn::get_name () const
```





**Returns:**

std::string The name of the [**Event**](classastrea_1_1astro_1_1Event.md). 





        

<hr>



### function is\_terminal 

_Checks if the_ [_**Event**_](classastrea_1_1astro_1_1Event.md) _is a terminal_[_**Event**_](classastrea_1_1astro_1_1Event.md) _._
```C++
bool astrea::astro::ImpulsiveBurn::is_terminal () const
```





**Returns:**

true If the [**Event**](classastrea_1_1astro_1_1Event.md) is a terminal [**Event**](classastrea_1_1astro_1_1Event.md). 




**Returns:**

false If the [**Event**](classastrea_1_1astro_1_1Event.md) is not a terminal [**Event**](classastrea_1_1astro_1_1Event.md). 





        

<hr>



### function measure\_event 

_Measures the anomaly as a trigger._ 
```C++
Unitless astrea::astro::ImpulsiveBurn::measure_event (
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

_Triggers an impulsive burn._ 
```C++
void astrea::astro::ImpulsiveBurn::trigger_action (
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
The documentation for this class was generated from the following file `astrea/astro/astro/propagation/event_detection/events/ImpulsiveBurn.hpp`

