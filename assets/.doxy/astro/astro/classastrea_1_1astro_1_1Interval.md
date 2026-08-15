

# Class astrea::astro::Interval



[**ClassList**](annotated.md) **>** [**astrea**](namespaceastrea.md) **>** [**astro**](namespaceastrea_1_1astro.md) **>** [**Interval**](classastrea_1_1astro_1_1Interval.md)



_Represents a time interval with a start and end time._ [More...](#detailed-description)

* `#include <Interval.hpp>`





















## Public Attributes

| Type | Name |
| ---: | :--- |
|  Time | [**propTime**](#variable-proptime)  <br>_The end time of the interval._  |
|  Time | [**start**](#variable-start)  <br>_The start time of the interval._  |
















## Public Functions

| Type | Name |
| ---: | :--- |
|   | [**Interval**](#function-interval) (const Time & start, const Time & end) <br>_Constructs an_ [_**Interval**_](classastrea_1_1astro_1_1Interval.md) _object with the specified start and end times._ |
|   | [**~Interval**](#function-interval) () = default<br>_Default destructor for_ [_**Interval**_](classastrea_1_1astro_1_1Interval.md) _._ |




























## Detailed Description


This class is used to define a time interval in the context of astrodynamics. It contains two Time objects: one for the start of the interval and one for the end. 


    
## Public Attributes Documentation




### variable propTime 

_The end time of the interval._ 
```C++
Time astrea::astro::Interval::propTime;
```




<hr>



### variable start 

_The start time of the interval._ 
```C++
Time astrea::astro::Interval::start;
```




<hr>
## Public Functions Documentation




### function Interval 

_Constructs an_ [_**Interval**_](classastrea_1_1astro_1_1Interval.md) _object with the specified start and end times._
```C++
inline astrea::astro::Interval::Interval (
    const Time & start,
    const Time & end
) 
```





**Parameters:**


* `start` The start time of the interval. 
* `end` The end time of the interval. 




        

<hr>



### function ~Interval 

_Default destructor for_ [_**Interval**_](classastrea_1_1astro_1_1Interval.md) _._
```C++
astrea::astro::Interval::~Interval () = default
```




<hr>

------------------------------
The documentation for this class was generated from the following file `astrea/astro/astro/time/Interval.hpp`

