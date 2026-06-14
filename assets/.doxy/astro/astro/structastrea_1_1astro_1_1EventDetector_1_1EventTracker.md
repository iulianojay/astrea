

# Struct astrea::astro::EventDetector::EventTracker



[**ClassList**](annotated.md) **>** [**EventTracker**](structastrea_1_1astro_1_1EventDetector_1_1EventTracker.md)



_A struct for tracking events._ 






















## Public Attributes

| Type | Name |
| ---: | :--- |
|  std::set&lt; [**Time**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) &gt; | [**detectionTimes**](#variable-detectiontimes)  <br>_The times at which the_ [_**Event**_](classastrea_1_1astro_1_1Event.md) _was detected._ |
|  [**Event**](classastrea_1_1astro_1_1Event.md) | [**event**](#variable-event)  <br>_The_ [_**Event**_](classastrea_1_1astro_1_1Event.md) _being tracked._ |
|  [**bool**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) | [**firstMeasurement**](#variable-firstmeasurement)  <br>_Whether this is the first measurement for the_ [_**Event**_](classastrea_1_1astro_1_1Event.md) _._ |
|  [**Time**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) | [**previousTime**](#variable-previoustime)  <br>_The previous time the_ [_**Event**_](classastrea_1_1astro_1_1Event.md) _was measured._ |
|  [**Unitless**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) | [**previousValue**](#variable-previousvalue)  <br>_The previous value the_ [_**Event**_](classastrea_1_1astro_1_1Event.md) _was measured at._ |












































## Public Attributes Documentation




### variable detectionTimes 

_The times at which the_ [_**Event**_](classastrea_1_1astro_1_1Event.md) _was detected._
```C++
std::set<Time> astrea::astro::EventDetector::EventTracker::detectionTimes;
```




<hr>



### variable event 

_The_ [_**Event**_](classastrea_1_1astro_1_1Event.md) _being tracked._
```C++
Event astrea::astro::EventDetector::EventTracker::event;
```




<hr>



### variable firstMeasurement 

_Whether this is the first measurement for the_ [_**Event**_](classastrea_1_1astro_1_1Event.md) _._
```C++
bool astrea::astro::EventDetector::EventTracker::firstMeasurement;
```




<hr>



### variable previousTime 

_The previous time the_ [_**Event**_](classastrea_1_1astro_1_1Event.md) _was measured._
```C++
Time astrea::astro::EventDetector::EventTracker::previousTime;
```




<hr>



### variable previousValue 

_The previous value the_ [_**Event**_](classastrea_1_1astro_1_1Event.md) _was measured at._
```C++
Unitless astrea::astro::EventDetector::EventTracker::previousValue;
```




<hr>

------------------------------
The documentation for this class was generated from the following file `astrea/astro/astro/propagation/event_detection/EventDetector.hpp`

