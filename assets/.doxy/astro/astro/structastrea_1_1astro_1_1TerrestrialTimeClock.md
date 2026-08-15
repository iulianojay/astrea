

# Struct astrea::astro::TerrestrialTimeClock



[**ClassList**](annotated.md) **>** [**astrea**](namespaceastrea.md) **>** [**astro**](namespaceastrea_1_1astro.md) **>** [**TerrestrialTimeClock**](structastrea_1_1astro_1_1TerrestrialTimeClock.md)



_A clock implementation for Terrestrial Time (TT)._ [More...](#detailed-description)

* `#include <TerrestrialTimeClock.hpp>`

















## Public Types

| Type | Name |
| ---: | :--- |
| typedef std::chrono::duration&lt; [**rep**](structastrea_1_1astro_1_1TerrestrialTimeClock.md#typedef-rep), [**period**](structastrea_1_1astro_1_1TerrestrialTimeClock.md#typedef-period) &gt; | [**duration**](#typedef-duration)  <br>_The duration type, representing time in seconds._  |
| typedef std::ratio&lt; 1 &gt; | [**period**](#typedef-period)  <br>_The period type, seconds._  |
| typedef double | [**rep**](#typedef-rep)  <br>_The representation type, a double for sub-second precision._  |
| typedef std::chrono::time\_point&lt; [**TerrestrialTimeClock**](structastrea_1_1astro_1_1TerrestrialTimeClock.md) &gt; | [**time\_point**](#typedef-time_point)  <br>_The time point type for TT, using_ [_**TerrestrialTimeClock**_](structastrea_1_1astro_1_1TerrestrialTimeClock.md) _._ |






## Public Static Attributes

| Type | Name |
| ---: | :--- |
|  constexpr bool | [**is\_steady**](#variable-is_steady)   = `false`<br>_TT is not a steady clock; it is anchored to TAI._  |
|  constexpr [**duration**](structastrea_1_1astro_1_1TerrestrialTimeClock.md#typedef-duration) | [**tt\_tai\_offset**](#variable-tt_tai_offset)   = `{ 32.184 }`<br>_The fixed offset between Terrestrial Time and International Atomic Time._  |
















## Public Static Functions

| Type | Name |
| ---: | :--- |
|  auto | [**from\_sys**](#function-from_sys) (std::chrono::sys\_time&lt; Duration &gt; const & timePoint) noexcept<br>_Converts a system time point to a Terrestrial Time time point._  |
|  [**time\_point**](structastrea_1_1astro_1_1TerrestrialTimeClock.md#typedef-time_point) | [**now**](#function-now) () noexcept<br>_Gets the current time point in Terrestrial Time format._  |
|  auto | [**to\_sys**](#function-to_sys) ([**TerrestrialDateTime**](namespaceastrea_1_1astro.md#typedef-terrestrialdatetime)&lt; Duration &gt; const & timePoint) noexcept<br>_Converts a Terrestrial Time time point to a system time point._  |


























## Detailed Description


Terrestrial Time is a continuous time scale defined by the IAU. It is related to International Atomic Time (TAI) by a fixed offset: TT = TAI + 32.184 seconds. TT is commonly used in astrodynamics as the independent variable for planetary motion equations.


This clock provides conversions to and from the system clock via the TAI clock, accounting for the fixed TT-TAI offset. Leap seconds are handled transparently through std::chrono::tai\_clock. 


    
## Public Types Documentation




### typedef duration 

_The duration type, representing time in seconds._ 
```C++
using astrea::astro::TerrestrialTimeClock::duration =  std::chrono::duration<rep, period>;
```




<hr>



### typedef period 

_The period type, seconds._ 
```C++
using astrea::astro::TerrestrialTimeClock::period =  std::ratio<1>;
```




<hr>



### typedef rep 

_The representation type, a double for sub-second precision._ 
```C++
using astrea::astro::TerrestrialTimeClock::rep =  double;
```




<hr>



### typedef time\_point 

_The time point type for TT, using_ [_**TerrestrialTimeClock**_](structastrea_1_1astro_1_1TerrestrialTimeClock.md) _._
```C++
using astrea::astro::TerrestrialTimeClock::time_point =  std::chrono::time_point<TerrestrialTimeClock>;
```




<hr>
## Public Static Attributes Documentation




### variable is\_steady 

_TT is not a steady clock; it is anchored to TAI._ 
```C++
constexpr bool astrea::astro::TerrestrialTimeClock::is_steady;
```




<hr>



### variable tt\_tai\_offset 

_The fixed offset between Terrestrial Time and International Atomic Time._ 
```C++
constexpr duration astrea::astro::TerrestrialTimeClock::tt_tai_offset;
```



TT = TAI + 32.184 s (as defined by the IAU). 


        

<hr>
## Public Static Functions Documentation




### function from\_sys 

_Converts a system time point to a Terrestrial Time time point._ 
```C++
template<class Duration>
static inline auto astrea::astro::TerrestrialTimeClock::from_sys (
    std::chrono::sys_time< Duration > const & timePoint
) noexcept
```



The conversion route is: UTC (sys) → TAI (via clock\_cast, handling leap seconds) → TT (+ 32.184 s).




**Template parameters:**


* `Duration` The duration type of the system time point. 



**Parameters:**


* `timePoint` The system time point to convert. 



**Returns:**

TerrestrialDateTime&lt;TerrestrialTimeClock::duration&gt; The converted TT time point. 





        

<hr>



### function now 

_Gets the current time point in Terrestrial Time format._ 
```C++
static inline time_point astrea::astro::TerrestrialTimeClock::now () noexcept
```





**Returns:**

[**TerrestrialTimeClock::time\_point**](structastrea_1_1astro_1_1TerrestrialTimeClock.md#typedef-time_point) The current time point in TT format. 





        

<hr>



### function to\_sys 

_Converts a Terrestrial Time time point to a system time point._ 
```C++
template<class Duration>
static inline auto astrea::astro::TerrestrialTimeClock::to_sys (
    TerrestrialDateTime < Duration > const & timePoint
) noexcept
```



The conversion route is: TT → TAI (- 32.184 s) → UTC (via clock\_cast, handling leap seconds).




**Template parameters:**


* `Duration` The duration type of the TT time point. 



**Parameters:**


* `timePoint` The TT time point to convert. 



**Returns:**

std::chrono::sys\_time&lt;std::chrono::tai\_clock::duration&gt; The converted system time point. 





        

<hr>

------------------------------
The documentation for this class was generated from the following file `astrea/astro/astro/time/clocks/TerrestrialTimeClock.hpp`

