

# Struct astrea::astro::JulianDateClock



[**ClassList**](annotated.md) **>** [**astrea**](namespaceastrea.md) **>** [**astro**](namespaceastrea_1_1astro.md) **>** [**JulianDateClock**](structastrea_1_1astro_1_1JulianDateClock.md)



_A clock implementation for Julian Dates._ [More...](#detailed-description)

* `#include <JulianDateClock.hpp>`

















## Public Types

| Type | Name |
| ---: | :--- |
| typedef std::chrono::duration&lt; [**rep**](structastrea_1_1astro_1_1JulianDateClock.md#typedef-rep), [**period**](structastrea_1_1astro_1_1JulianDateClock.md#typedef-period) &gt; | [**duration**](#typedef-duration)  <br>_The duration type for the Julian_ [_**Date**_](classastrea_1_1astro_1_1Date.md) _, representing the time in days._ |
| typedef std::chrono::days::period | [**period**](#typedef-period)  <br>_The period type for the Julian_ [_**Date**_](classastrea_1_1astro_1_1Date.md) _, typically days._ |
| typedef double | [**rep**](#typedef-rep)  <br>_The representation type for the Julian_ [_**Date**_](classastrea_1_1astro_1_1Date.md) _, typically a double for fractional days._ |
| typedef std::chrono::time\_point&lt; [**JulianDateClock**](structastrea_1_1astro_1_1JulianDateClock.md) &gt; | [**time\_point**](#typedef-time_point)  <br>_The time point type for the Julian_ [_**Date**_](classastrea_1_1astro_1_1Date.md) _, using the_[_**JulianDateClock**_](structastrea_1_1astro_1_1JulianDateClock.md) _._ |






## Public Static Attributes

| Type | Name |
| ---: | :--- |
|  constexpr bool | [**is\_steady**](#variable-is_steady)   = `/* multi line expression */`<br>_Indicates that the clock is not steady, meaning it can be adjusted or may have leap seconds._  |
















## Public Static Functions

| Type | Name |
| ---: | :--- |
|  auto | [**from\_sys**](#function-from_sys) (std::chrono::sys\_time&lt; Duration &gt; const & timePoint) noexcept<br>_Converts a system time point to a Julian_ [_**Date**_](classastrea_1_1astro_1_1Date.md) _time point._ |
|  [**time\_point**](structastrea_1_1astro_1_1JulianDateClock.md#typedef-time_point) | [**now**](#function-now) () noexcept<br>_Gets the current time point in Julian_ [_**Date**_](classastrea_1_1astro_1_1Date.md) _format._ |
|  auto | [**to\_sys**](#function-to_sys) ([**JulianDateTime**](namespaceastrea_1_1astro.md#typedef-juliandatetime)&lt; Duration &gt; const & timePoint) noexcept<br>_Converts a Julian_ [_**Date**_](classastrea_1_1astro_1_1Date.md) _time point to a system time point._ |


























## Detailed Description


This clock is used to represent time points in Julian [**Date**](classastrea_1_1astro_1_1Date.md) format, which is commonly used in astronomy. It provides conversions to and from system clocks and supports arithmetic operations on Julian Dates. 


    
## Public Types Documentation




### typedef duration 

_The duration type for the Julian_ [_**Date**_](classastrea_1_1astro_1_1Date.md) _, representing the time in days._
```C++
using astrea::astro::JulianDateClock::duration =  std::chrono::duration<rep, period>;
```




<hr>



### typedef period 

_The period type for the Julian_ [_**Date**_](classastrea_1_1astro_1_1Date.md) _, typically days._
```C++
using astrea::astro::JulianDateClock::period =  std::chrono::days::period;
```




<hr>



### typedef rep 

_The representation type for the Julian_ [_**Date**_](classastrea_1_1astro_1_1Date.md) _, typically a double for fractional days._
```C++
using astrea::astro::JulianDateClock::rep =  double;
```




<hr>



### typedef time\_point 

_The time point type for the Julian_ [_**Date**_](classastrea_1_1astro_1_1Date.md) _, using the_[_**JulianDateClock**_](structastrea_1_1astro_1_1JulianDateClock.md) _._
```C++
using astrea::astro::JulianDateClock::time_point =  std::chrono::time_point<JulianDateClock>;
```




<hr>
## Public Static Attributes Documentation




### variable is\_steady 

_Indicates that the clock is not steady, meaning it can be adjusted or may have leap seconds._ 
```C++
constexpr bool astrea::astro::JulianDateClock::is_steady;
```




<hr>
## Public Static Functions Documentation




### function from\_sys 

_Converts a system time point to a Julian_ [_**Date**_](classastrea_1_1astro_1_1Date.md) _time point._
```C++
template<class Duration>
static inline auto astrea::astro::JulianDateClock::from_sys (
    std::chrono::sys_time< Duration > const & timePoint
) noexcept
```





**Template parameters:**


* `Duration` The duration type of the system time point. 



**Parameters:**


* `timePoint` The system time point to convert. 



**Returns:**

JulianDateTime&lt;Duration&gt; The converted Julian [**Date**](classastrea_1_1astro_1_1Date.md) time point. 





        

<hr>



### function now 

_Gets the current time point in Julian_ [_**Date**_](classastrea_1_1astro_1_1Date.md) _format._
```C++
static inline time_point astrea::astro::JulianDateClock::now () noexcept
```





**Returns:**

[**JulianDateClock::time\_point**](structastrea_1_1astro_1_1JulianDateClock.md#typedef-time_point) The current time point in Julian [**Date**](classastrea_1_1astro_1_1Date.md) format. 





        

<hr>



### function to\_sys 

_Converts a Julian_ [_**Date**_](classastrea_1_1astro_1_1Date.md) _time point to a system time point._
```C++
template<class Duration>
static inline auto astrea::astro::JulianDateClock::to_sys (
    JulianDateTime < Duration > const & timePoint
) noexcept
```





**Template parameters:**


* `Duration` The duration type of the Julian [**Date**](classastrea_1_1astro_1_1Date.md) time point. 



**Parameters:**


* `timePoint` The Julian [**Date**](classastrea_1_1astro_1_1Date.md) time point to convert. 



**Returns:**

std::chrono::sys\_time&lt;Duration&gt; The converted system time point. 





        

<hr>

------------------------------
The documentation for this class was generated from the following file `astrea/astro/astro/time/clocks/JulianDateClock.hpp`

