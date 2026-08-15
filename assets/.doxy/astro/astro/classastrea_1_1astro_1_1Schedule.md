

# Class astrea::astro::Schedule



[**ClassList**](annotated.md) **>** [**astrea**](namespaceastrea.md) **>** [**astro**](namespaceastrea_1_1astro.md) **>** [**Schedule**](classastrea_1_1astro_1_1Schedule.md)



_A class representing a_ [_**Schedule**_](classastrea_1_1astro_1_1Schedule.md) _in the astrea astro library. The_[_**Schedule**_](classastrea_1_1astro_1_1Schedule.md) _is responsible for scheduling and managing Events that are set to trigger at specific Dates during propagation._

* `#include <Schedule.hpp>`





































## Public Functions

| Type | Name |
| ---: | :--- |
|   | [**Schedule**](#function-schedule) () = default<br>_Default constructor for the_ [_**Schedule**_](classastrea_1_1astro_1_1Schedule.md) _class._ |
|  void | [**clear**](#function-clear) () <br>_Clears all scheduled Events and their associated Dates from the_ [_**Schedule**_](classastrea_1_1astro_1_1Schedule.md) _._ |
|  std::vector&lt; [**Event**](classastrea_1_1astro_1_1Event.md) &gt; | [**get\_events\_at**](#function-get_events_at) (const [**Date**](classastrea_1_1astro_1_1Date.md) & date) const<br>_Retrieves the Events scheduled to trigger at a specific_ [_**Date**_](classastrea_1_1astro_1_1Date.md) _._ |
|  std::vector&lt; [**Date**](classastrea_1_1astro_1_1Date.md) &gt; | [**get\_scheduled\_dates**](#function-get_scheduled_dates) () const<br>_Retrieves all the Dates that have Events scheduled._  |
|  void | [**remove\_events\_at**](#function-remove_events_at) (const [**Date**](classastrea_1_1astro_1_1Date.md) & date) <br>_Removes all Events scheduled to trigger at a specific_ [_**Date**_](classastrea_1_1astro_1_1Date.md) _._ |
|  void | [**remove\_events\_between**](#function-remove_events_between) (const [**Date**](classastrea_1_1astro_1_1Date.md) & startDate, const [**Date**](classastrea_1_1astro_1_1Date.md) & endDate) <br>_Removes all Events scheduled to trigger between two Dates (inclusive)._  |
|  void | [**schedule\_event**](#function-schedule_event-12) (const [**Date**](classastrea_1_1astro_1_1Date.md) & date, const [**Event**](classastrea_1_1astro_1_1Event.md) & event) <br>_Schedules an_ [_**Event**_](classastrea_1_1astro_1_1Event.md) _to trigger at a specific_[_**Date**_](classastrea_1_1astro_1_1Date.md) _._ |
|  void | [**schedule\_event**](#function-schedule_event-22) (const std::vector&lt; [**Date**](classastrea_1_1astro_1_1Date.md) &gt; & dates, const [**Event**](classastrea_1_1astro_1_1Event.md) & event) <br>_Schedules an_ [_**Event**_](classastrea_1_1astro_1_1Event.md) _to trigger at multiple Dates._ |
|  void | [**trigger\_scheduled\_events**](#function-trigger_scheduled_events) (const [**Date**](classastrea_1_1astro_1_1Date.md) & date, const Time & time, [**State**](classastrea_1_1astro_1_1State.md) & state, [**Vehicle**](classastrea_1_1astro_1_1Vehicle.md) & vehicle) const<br>_Triggers all Events scheduled to trigger at a specific_ [_**Date**_](classastrea_1_1astro_1_1Date.md) _._ |




























## Public Functions Documentation




### function Schedule 

_Default constructor for the_ [_**Schedule**_](classastrea_1_1astro_1_1Schedule.md) _class._
```C++
astrea::astro::Schedule::Schedule () = default
```




<hr>



### function clear 

_Clears all scheduled Events and their associated Dates from the_ [_**Schedule**_](classastrea_1_1astro_1_1Schedule.md) _._
```C++
void astrea::astro::Schedule::clear () 
```




<hr>



### function get\_events\_at 

_Retrieves the Events scheduled to trigger at a specific_ [_**Date**_](classastrea_1_1astro_1_1Date.md) _._
```C++
std::vector< Event > astrea::astro::Schedule::get_events_at (
    const Date & date
) const
```





**Parameters:**


* `date` The [**Date**](classastrea_1_1astro_1_1Date.md) for which to retrieve the scheduled Events. 



**Returns:**

std::vector&lt;Event&gt; A vector of Events scheduled to trigger at the specified [**Date**](classastrea_1_1astro_1_1Date.md). 





        

<hr>



### function get\_scheduled\_dates 

_Retrieves all the Dates that have Events scheduled._ 
```C++
std::vector< Date > astrea::astro::Schedule::get_scheduled_dates () const
```





**Returns:**

std::vector&lt;Date&gt; A vector of Dates that have Events scheduled. 





        

<hr>



### function remove\_events\_at 

_Removes all Events scheduled to trigger at a specific_ [_**Date**_](classastrea_1_1astro_1_1Date.md) _._
```C++
void astrea::astro::Schedule::remove_events_at (
    const Date & date
) 
```





**Parameters:**


* `date` The [**Date**](classastrea_1_1astro_1_1Date.md) for which to remove the scheduled Events. 




        

<hr>



### function remove\_events\_between 

_Removes all Events scheduled to trigger between two Dates (inclusive)._ 
```C++
void astrea::astro::Schedule::remove_events_between (
    const Date & startDate,
    const Date & endDate
) 
```





**Parameters:**


* `startDate` The start [**Date**](classastrea_1_1astro_1_1Date.md) of the range for which to remove the scheduled Events. 
* `endDate` The end [**Date**](classastrea_1_1astro_1_1Date.md) of the range for which to remove the scheduled Events. 




        

<hr>



### function schedule\_event [1/2]

_Schedules an_ [_**Event**_](classastrea_1_1astro_1_1Event.md) _to trigger at a specific_[_**Date**_](classastrea_1_1astro_1_1Date.md) _._
```C++
void astrea::astro::Schedule::schedule_event (
    const Date & date,
    const Event & event
) 
```





**Parameters:**


* `date` The [**Date**](classastrea_1_1astro_1_1Date.md) at which the [**Event**](classastrea_1_1astro_1_1Event.md) should trigger. 
* `event` The [**Event**](classastrea_1_1astro_1_1Event.md) to be scheduled. 




        

<hr>



### function schedule\_event [2/2]

_Schedules an_ [_**Event**_](classastrea_1_1astro_1_1Event.md) _to trigger at multiple Dates._
```C++
void astrea::astro::Schedule::schedule_event (
    const std::vector< Date > & dates,
    const Event & event
) 
```





**Parameters:**


* `dates` A vector of Dates at which the [**Event**](classastrea_1_1astro_1_1Event.md) should trigger. 
* `event` The [**Event**](classastrea_1_1astro_1_1Event.md) to be scheduled. 




        

<hr>



### function trigger\_scheduled\_events 

_Triggers all Events scheduled to trigger at a specific_ [_**Date**_](classastrea_1_1astro_1_1Date.md) _._
```C++
void astrea::astro::Schedule::trigger_scheduled_events (
    const Date & date,
    const Time & time,
    State & state,
    Vehicle & vehicle
) const
```





**Parameters:**


* `date` The [**Date**](classastrea_1_1astro_1_1Date.md) at which to trigger the scheduled Events. 
* `time` The current time in the integration. 
* `state` The current state of the vehicle represented as orbital elements. 
* `vehicle` The [**Vehicle**](classastrea_1_1astro_1_1Vehicle.md) to trigger the Events on. 




        

<hr>

------------------------------
The documentation for this class was generated from the following file `astrea/astro/astro/propagation/event_detection/Schedule.hpp`

