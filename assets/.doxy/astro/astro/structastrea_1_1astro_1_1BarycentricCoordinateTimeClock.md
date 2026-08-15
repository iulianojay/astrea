

# Struct astrea::astro::BarycentricCoordinateTimeClock



[**ClassList**](annotated.md) **>** [**astrea**](namespaceastrea.md) **>** [**astro**](namespaceastrea_1_1astro.md) **>** [**BarycentricCoordinateTimeClock**](structastrea_1_1astro_1_1BarycentricCoordinateTimeClock.md)



_A clock implementation for Barycentric Coordinate Time (TCB)._ [More...](#detailed-description)

* `#include <BarycentricCoordinateTimeClock.hpp>`

















## Public Types

| Type | Name |
| ---: | :--- |
| typedef std::chrono::duration&lt; [**rep**](structastrea_1_1astro_1_1BarycentricCoordinateTimeClock.md#typedef-rep), [**period**](structastrea_1_1astro_1_1BarycentricCoordinateTimeClock.md#typedef-period) &gt; | [**duration**](#typedef-duration)  <br>_The duration type, representing time in seconds._  |
| typedef std::ratio&lt; 1 &gt; | [**period**](#typedef-period)  <br>_The period type, seconds._  |
| typedef double | [**rep**](#typedef-rep)  <br>_The representation type, a double for sub-second precision._  |
| typedef std::chrono::time\_point&lt; [**BarycentricCoordinateTimeClock**](structastrea_1_1astro_1_1BarycentricCoordinateTimeClock.md) &gt; | [**time\_point**](#typedef-time_point)  <br>_The time point type for TCB, using_ [_**BarycentricCoordinateTimeClock**_](structastrea_1_1astro_1_1BarycentricCoordinateTimeClock.md) _._ |






## Public Static Attributes

| Type | Name |
| ---: | :--- |
|  constexpr [**rep**](structastrea_1_1astro_1_1BarycentricCoordinateTimeClock.md#typedef-rep) | [**Lb**](#variable-lb)   = `1.550519768e-8`<br>_The rate difference between TCB and TT, defined by the IAU._  |
|  constexpr auto | [**P0**](#variable-p0)   = `[**duration**](structastrea_1_1astro_1_1BarycentricCoordinateTimeClock.md#typedef-duration){ 6.55e-5 }`<br> |
|  constexpr bool | [**is\_steady**](#variable-is_steady)   = `false`<br>_TCB is not a steady clock; it is anchored to TAI._  |
|  constexpr auto | [**jdRef**](#variable-jdref)   = `[**JulianDateClock::duration**](structastrea_1_1astro_1_1JulianDateClock.md#typedef-duration){ 2443144.5 }`<br> |
















## Public Static Functions

| Type | Name |
| ---: | :--- |
|  auto | [**from\_sys**](#function-from_sys) (std::chrono::sys\_time&lt; Duration &gt; const & timePoint) noexcept<br>_Converts a system time point to a Barycentric Coordinate Time time point._  |
|  [**time\_point**](structastrea_1_1astro_1_1BarycentricCoordinateTimeClock.md#typedef-time_point) | [**now**](#function-now) () noexcept<br>_Gets the current time point in Barycentric Coordinate Time format._  |
|  auto | [**to\_sys**](#function-to_sys) ([**BarycentricCoordinateTimePoint**](namespaceastrea_1_1astro.md#typedef-barycentriccoordinatetimepoint)&lt; Duration &gt; const & timePoint) noexcept<br>_Converts a Barycentric Coordinate Time time point to a system time point._  |


























## Detailed Description


[**Geocentric**](classastrea_1_1astro_1_1Geocentric.md) Coordinate Time is a continuous time scale defined by the IAU. It is related to Terrestrial Time (TT) by a linear transformation that accounts for the relativistic effects of Earth's gravitational potential. TCG is commonly used in astrodynamics for high-precision timekeeping in the vicinity of Earth. 


    
## Public Types Documentation




### typedef duration 

_The duration type, representing time in seconds._ 
```C++
using astrea::astro::BarycentricCoordinateTimeClock::duration =  std::chrono::duration<rep, period>;
```




<hr>



### typedef period 

_The period type, seconds._ 
```C++
using astrea::astro::BarycentricCoordinateTimeClock::period =  std::ratio<1>;
```




<hr>



### typedef rep 

_The representation type, a double for sub-second precision._ 
```C++
using astrea::astro::BarycentricCoordinateTimeClock::rep =  double;
```




<hr>



### typedef time\_point 

_The time point type for TCB, using_ [_**BarycentricCoordinateTimeClock**_](structastrea_1_1astro_1_1BarycentricCoordinateTimeClock.md) _._
```C++
using astrea::astro::BarycentricCoordinateTimeClock::time_point =  std::chrono::time_point<BarycentricCoordinateTimeClock>;
```




<hr>
## Public Static Attributes Documentation




### variable Lb 

_The rate difference between TCB and TT, defined by the IAU._ 
```C++
constexpr rep astrea::astro::BarycentricCoordinateTimeClock::Lb;
```




<hr>



### variable P0 

```C++
constexpr auto astrea::astro::BarycentricCoordinateTimeClock::P0;
```




<hr>



### variable is\_steady 

_TCB is not a steady clock; it is anchored to TAI._ 
```C++
constexpr bool astrea::astro::BarycentricCoordinateTimeClock::is_steady;
```




<hr>



### variable jdRef 

```C++
constexpr auto astrea::astro::BarycentricCoordinateTimeClock::jdRef;
```




<hr>
## Public Static Functions Documentation




### function from\_sys 

_Converts a system time point to a Barycentric Coordinate Time time point._ 
```C++
template<class Duration>
static inline auto astrea::astro::BarycentricCoordinateTimeClock::from_sys (
    std::chrono::sys_time< Duration > const & timePoint
) noexcept
```



The conversion route is: UTC → TT → TCB




**Template parameters:**


* `Duration` The duration type of the system time point. 



**Parameters:**


* `timePoint` The system time point to convert. 



**Returns:**

BarycentricCoordinateTimePoint The converted TCB time point.


[https://ntrs.nasa.gov/api/citations/20220014814/downloads/NASA](https://ntrs.nasa.gov/api/citations/20220014814/downloads/NASA)%20TP%2020220014814%20final.pdf 


        

<hr>



### function now 

_Gets the current time point in Barycentric Coordinate Time format._ 
```C++
static inline time_point astrea::astro::BarycentricCoordinateTimeClock::now () noexcept
```





**Returns:**

[**BarycentricCoordinateTimeClock::time\_point**](structastrea_1_1astro_1_1BarycentricCoordinateTimeClock.md#typedef-time_point) The current time point in TCB format. 





        

<hr>



### function to\_sys 

_Converts a Barycentric Coordinate Time time point to a system time point._ 
```C++
template<class Duration>
static inline auto astrea::astro::BarycentricCoordinateTimeClock::to_sys (
    BarycentricCoordinateTimePoint < Duration > const & timePoint
) noexcept
```



The conversion route is: TCB → TAI (- 32.184 s) → UTC (via clock\_cast, handling leap seconds).




**Template parameters:**


* `Duration` The duration type of the TCB time point. 



**Parameters:**


* `timePoint` The TCB time point to convert. 



**Returns:**

std::chrono::sys\_time&lt;std::chrono::tai\_clock::duration&gt; The converted system time point.


[https://ntrs.nasa.gov/api/citations/20220014814/downloads/NASA](https://ntrs.nasa.gov/api/citations/20220014814/downloads/NASA)%20TP%2020220014814%20final.pdf 


        

<hr>

------------------------------
The documentation for this class was generated from the following file `astrea/astro/astro/time/clocks/BarycentricCoordinateTimeClock.hpp`

