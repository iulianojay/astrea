

# Class astrea::astro::EventDetector



[**ClassList**](annotated.md) **>** [**astrea**](namespaceastrea.md) **>** [**astro**](namespaceastrea_1_1astro.md) **>** [**EventDetector**](classastrea_1_1astro_1_1EventDetector.md)



_A class for detecting events in the astrea astro platform._ 

* `#include <EventDetector.hpp>`





































## Public Functions

| Type | Name |
| ---: | :--- |
|   | [**EventDetector**](#function-eventdetector-12) () = default<br>_Default constructor for_ [_**EventDetector**_](classastrea_1_1astro_1_1EventDetector.md) _._ |
|   | [**EventDetector**](#function-eventdetector-22) ([**const**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) std::vector&lt; [**Event**](classastrea_1_1astro_1_1Event.md) &gt; & events) <br>_Constructs an_ [_**EventDetector**_](classastrea_1_1astro_1_1EventDetector.md) _with a given list of Events._ |
|  [**void**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) | [**add\_event**](#function-add_event) ([**const**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) [**Event**](classastrea_1_1astro_1_1Event.md) & event) <br>_Adds an_ [_**Event**_](classastrea_1_1astro_1_1Event.md) _to the list of Events to track._ |
|  [**void**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) | [**add\_events**](#function-add_events) ([**const**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) std::vector&lt; [**Event**](classastrea_1_1astro_1_1Event.md) &gt; & events) <br>_Sets the list of Events to track._  |
|  [**void**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) | [**clear\_events**](#function-clear_events) () <br>_Clears all Events from the list of Events to track._  |
|  [**bool**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) | [**detect\_events**](#function-detect_events) ([**const**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) [**Time**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) & time, [**State**](classastrea_1_1astro_1_1State.md) & state, [**Vehicle**](classastrea_1_1astro_1_1Vehicle.md) & vehicle) <br>_Detects events for a given time and vehicle._  |
|  gtl::btree\_map&lt; std::string, std::vector&lt; [**Date**](classastrea_1_1astro_1_1Date.md) &gt; &gt; | [**get\_event\_times**](#function-get_event_times) ([**const**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) [**Date**](classastrea_1_1astro_1_1Date.md) & epoch) const<br>_Retrieves the event times recorded during propagation._  |
|  std::vector&lt; [**Event**](classastrea_1_1astro_1_1Event.md) &gt; | [**get\_events**](#function-get_events) () const<br>_Get events being tracked._  |
|   | [**~EventDetector**](#function-eventdetector) () = default<br>_Destructor for_ [_**EventDetector**_](classastrea_1_1astro_1_1EventDetector.md) _._ |




























## Public Functions Documentation




### function EventDetector [1/2]

_Default constructor for_ [_**EventDetector**_](classastrea_1_1astro_1_1EventDetector.md) _._
```C++
astrea::astro::EventDetector::EventDetector () = default
```




<hr>



### function EventDetector [2/2]

_Constructs an_ [_**EventDetector**_](classastrea_1_1astro_1_1EventDetector.md) _with a given list of Events._
```C++
astrea::astro::EventDetector::EventDetector (
    const std::vector< Event > & events
) 
```





**Parameters:**


* `events` The list of Events to track. 




        

<hr>



### function add\_event 

_Adds an_ [_**Event**_](classastrea_1_1astro_1_1Event.md) _to the list of Events to track._
```C++
void astrea::astro::EventDetector::add_event (
    const  Event & event
) 
```





**Parameters:**


* `event` The [**Event**](classastrea_1_1astro_1_1Event.md) to add. 




        

<hr>



### function add\_events 

_Sets the list of Events to track._ 
```C++
void astrea::astro::EventDetector::add_events (
    const std::vector< Event > & events
) 
```





**Parameters:**


* `events` The list of Events to track. 




        

<hr>



### function clear\_events 

_Clears all Events from the list of Events to track._ 
```C++
void astrea::astro::EventDetector::clear_events () 
```




<hr>



### function detect\_events 

_Detects events for a given time and vehicle._ 
```C++
bool astrea::astro::EventDetector::detect_events (
    const  Time & time,
    State & state,
    Vehicle & vehicle
) 
```





**Parameters:**


* `time` The current time. 
* `state` The current state. 
* `vehicle` The [**Vehicle**](classastrea_1_1astro_1_1Vehicle.md) to check for events. 



**Returns:**

true If a terminal event was detected. 




**Returns:**

false If no terminal event was detected. 





        

<hr>



### function get\_event\_times 

_Retrieves the event times recorded during propagation._ 
```C++
gtl::btree_map< std::string, std::vector< Date > > astrea::astro::EventDetector::get_event_times (
    const  Date & epoch
) const
```





**Parameters:**


* `epoch` The epoch to which the event times are relative. 



**Returns:**

const std::vector&lt;Date&gt;& A vector of dates representing the event times. 





        

<hr>



### function get\_events 

_Get events being tracked._ 
```C++
std::vector< Event > astrea::astro::EventDetector::get_events () const
```





**Returns:**

const std::vector&lt;Event&gt;& A const reference to the list of Events being tracked. 





        

<hr>



### function ~EventDetector 

_Destructor for_ [_**EventDetector**_](classastrea_1_1astro_1_1EventDetector.md) _._
```C++
astrea::astro::EventDetector::~EventDetector () = default
```




<hr>

------------------------------
The documentation for this class was generated from the following file `astrea/astro/astro/propagation/event_detection/EventDetector.hpp`

