

# Class astrea::astro::ImpulsiveBurn



[**ClassList**](annotated.md) **>** [**astrea**](namespaceastrea.md) **>** [**astro**](namespaceastrea_1_1astro.md) **>** [**ImpulsiveBurn**](classastrea_1_1astro_1_1ImpulsiveBurn.md)



_A class representing an impulsive burn_ [_**Event**_](classastrea_1_1astro_1_1Event.md) _. It triggers when the true anomaly wraps around (i.e. at perigee), and applies the total impulsive delta-v from all thrusters to the vehicle in the velocity direction._

* `#include <ImpulsiveBurn.hpp>`





































## Public Functions

| Type | Name |
| ---: | :--- |
|   | [**ImpulsiveBurn**](#function-impulsiveburn-14) () <br> |
|  std::string | [**get\_name**](#function-get_name) () const<br>_Gets the name of the_ [_**Event**_](classastrea_1_1astro_1_1Event.md) _._ |
|  [**bool**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) | [**is\_terminal**](#function-is_terminal) () const<br>_Checks if the_ [_**Event**_](classastrea_1_1astro_1_1Event.md) _is a terminal_[_**Event**_](classastrea_1_1astro_1_1Event.md) _._ |
|  [**Unitless**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) | [**measure\_event**](#function-measure_event) ([**const**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) [**Time**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) & time, [**const**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) [**State**](classastrea_1_1astro_1_1State.md) & state, [**const**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) [**Vehicle**](classastrea_1_1astro_1_1Vehicle.md) & vehicle) const<br>_Measures the anomaly as a trigger._  |
|  [**void**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) | [**trigger\_action**](#function-trigger_action) ([**const**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) [**Time**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) & time, [**State**](classastrea_1_1astro_1_1State.md) & state, [**Vehicle**](classastrea_1_1astro_1_1Vehicle.md) & vehicle) const<br>_Triggers an impulsive burn._  |


## Public Static Functions

| Type | Name |
| ---: | :--- |
|  [**ImpulsiveBurn**](classastrea_1_1astro_1_1ImpulsiveBurn.md) | [**trigger\_at\_altitude**](#function-trigger_at_altitude) ([**const**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) [**Distance**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) & triggerAltitude, [**const**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) [**Direction**](namespaceastrea_1_1astro.md#typedef-direction)&lt; frames::dynamic::ric &gt; burnDirection, [**const**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) [**unsigned**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) nMaxTriggers=0) <br>_Constructs an_ [_**ImpulsiveBurn**_](classastrea_1_1astro_1_1ImpulsiveBurn.md) __[_**Event**_](classastrea_1_1astro_1_1Event.md) _that triggers at a specific altitude._ |
|  [**ImpulsiveBurn**](classastrea_1_1astro_1_1ImpulsiveBurn.md) | [**trigger\_at\_epoch**](#function-trigger_at_epoch) ([**const**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) [**Date**](classastrea_1_1astro_1_1Date.md) & triggerEpoch, [**const**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) [**Direction**](namespaceastrea_1_1astro.md#typedef-direction)&lt; frames::dynamic::ric &gt; burnDirection, [**const**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) [**unsigned**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) nMaxTriggers=0) <br>_Constructs an_ [_**ImpulsiveBurn**_](classastrea_1_1astro_1_1ImpulsiveBurn.md) __[_**Event**_](classastrea_1_1astro_1_1Event.md) _that triggers at a specific epoch._ |
|  [**ImpulsiveBurn**](classastrea_1_1astro_1_1ImpulsiveBurn.md) | [**trigger\_at\_mean\_anomaly**](#function-trigger_at_mean_anomaly) ([**const**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) [**Angle**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) & triggerAnomaly, [**const**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) [**Direction**](namespaceastrea_1_1astro.md#typedef-direction)&lt; frames::dynamic::ric &gt; burnDirection, [**const**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) [**unsigned**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) nMaxTriggers=0) <br>_Constructs an_ [_**ImpulsiveBurn**_](classastrea_1_1astro_1_1ImpulsiveBurn.md) __[_**Event**_](classastrea_1_1astro_1_1Event.md) _that triggers at a specific mean anomaly._ |
|  [**ImpulsiveBurn**](classastrea_1_1astro_1_1ImpulsiveBurn.md) | [**trigger\_at\_true\_anomaly**](#function-trigger_at_true_anomaly) ([**const**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) [**Angle**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) & triggerAnomaly, [**const**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) [**Direction**](namespaceastrea_1_1astro.md#typedef-direction)&lt; frames::dynamic::ric &gt; burnDirection, [**const**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) [**unsigned**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) nMaxTriggers=0) <br>_Constructs an_ [_**ImpulsiveBurn**_](classastrea_1_1astro_1_1ImpulsiveBurn.md) __[_**Event**_](classastrea_1_1astro_1_1Event.md) _that triggers at a specific true anomaly._ |


























## Public Functions Documentation




### function ImpulsiveBurn [1/4]

```C++
inline astrea::astro::ImpulsiveBurn::ImpulsiveBurn () 
```




<hr>



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
    const  Time & time,
    const  State & state,
    const  Vehicle & vehicle
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
    const  Time & time,
    State & state,
    Vehicle & vehicle
) const
```





**Parameters:**


* `time` The current time in the integration. 
* `state` The current state of the vehicle represented as orbital elements. 
* `vehicle` The [**Vehicle**](classastrea_1_1astro_1_1Vehicle.md) to trigger the action on. 




        

<hr>
## Public Static Functions Documentation




### function trigger\_at\_altitude 

_Constructs an_ [_**ImpulsiveBurn**_](classastrea_1_1astro_1_1ImpulsiveBurn.md) __[_**Event**_](classastrea_1_1astro_1_1Event.md) _that triggers at a specific altitude._
```C++
static inline ImpulsiveBurn astrea::astro::ImpulsiveBurn::trigger_at_altitude (
    const  Distance & triggerAltitude,
    const  Direction < frames::dynamic::ric > burnDirection,
    const  unsigned nMaxTriggers=0
) 
```





**Parameters:**


* `triggerAltitude` The altitude at which the burn should trigger. 
* `burnDirection` The direction of the burn in the ICRF frame. 
* `nMaxTriggers` The maximum number of times the [**Event**](classastrea_1_1astro_1_1Event.md) can trigger before it is disabled. Zero means it can trigger infinitely. Default is zero. 



**Returns:**

[**ImpulsiveBurn**](classastrea_1_1astro_1_1ImpulsiveBurn.md) An [**ImpulsiveBurn**](classastrea_1_1astro_1_1ImpulsiveBurn.md) [**Event**](classastrea_1_1astro_1_1Event.md) that triggers at the specified altitude. 





        

<hr>



### function trigger\_at\_epoch 

_Constructs an_ [_**ImpulsiveBurn**_](classastrea_1_1astro_1_1ImpulsiveBurn.md) __[_**Event**_](classastrea_1_1astro_1_1Event.md) _that triggers at a specific epoch._
```C++
static inline ImpulsiveBurn astrea::astro::ImpulsiveBurn::trigger_at_epoch (
    const  Date & triggerEpoch,
    const  Direction < frames::dynamic::ric > burnDirection,
    const  unsigned nMaxTriggers=0
) 
```





**Parameters:**


* `triggerEpoch` The epoch at which the burn should trigger. 
* `burnDirection` The direction of the burn in the ICRF frame. 
* `nMaxTriggers` The maximum number of times the [**Event**](classastrea_1_1astro_1_1Event.md) can trigger before it is disabled. Zero means it can trigger infinitely. Default is zero. 



**Returns:**

[**ImpulsiveBurn**](classastrea_1_1astro_1_1ImpulsiveBurn.md) An [**ImpulsiveBurn**](classastrea_1_1astro_1_1ImpulsiveBurn.md) [**Event**](classastrea_1_1astro_1_1Event.md) that triggers at the specified epoch. 





        

<hr>



### function trigger\_at\_mean\_anomaly 

_Constructs an_ [_**ImpulsiveBurn**_](classastrea_1_1astro_1_1ImpulsiveBurn.md) __[_**Event**_](classastrea_1_1astro_1_1Event.md) _that triggers at a specific mean anomaly._
```C++
static inline ImpulsiveBurn astrea::astro::ImpulsiveBurn::trigger_at_mean_anomaly (
    const  Angle & triggerAnomaly,
    const  Direction < frames::dynamic::ric > burnDirection,
    const  unsigned nMaxTriggers=0
) 
```





**Parameters:**


* `triggerAnomaly` The mean anomaly at which the burn should trigger. 
* `burnDirection` The direction of the burn in the ICRF frame. 
* `nMaxTriggers` The maximum number of times the [**Event**](classastrea_1_1astro_1_1Event.md) can trigger before it is disabled. Zero means it can trigger infinitely. Default is zero. 



**Returns:**

[**ImpulsiveBurn**](classastrea_1_1astro_1_1ImpulsiveBurn.md) An [**ImpulsiveBurn**](classastrea_1_1astro_1_1ImpulsiveBurn.md) [**Event**](classastrea_1_1astro_1_1Event.md) that triggers at the specified mean anomaly. 





        

<hr>



### function trigger\_at\_true\_anomaly 

_Constructs an_ [_**ImpulsiveBurn**_](classastrea_1_1astro_1_1ImpulsiveBurn.md) __[_**Event**_](classastrea_1_1astro_1_1Event.md) _that triggers at a specific true anomaly._
```C++
static inline ImpulsiveBurn astrea::astro::ImpulsiveBurn::trigger_at_true_anomaly (
    const  Angle & triggerAnomaly,
    const  Direction < frames::dynamic::ric > burnDirection,
    const  unsigned nMaxTriggers=0
) 
```





**Parameters:**


* `triggerAnomaly` The true anomaly at which the burn should trigger. 
* `burnDirection` The direction of the burn in the ICRF frame. 
* `nMaxTriggers` The maximum number of times the [**Event**](classastrea_1_1astro_1_1Event.md) can trigger before it is disabled. Zero means it can trigger infinitely. Default is zero. 



**Returns:**

[**ImpulsiveBurn**](classastrea_1_1astro_1_1ImpulsiveBurn.md) An [**ImpulsiveBurn**](classastrea_1_1astro_1_1ImpulsiveBurn.md) [**Event**](classastrea_1_1astro_1_1Event.md) that triggers at the specified true anomaly. 





        

<hr>

------------------------------
The documentation for this class was generated from the following file `astrea/astro/astro/propagation/event_detection/events/ImpulsiveBurn.hpp`

