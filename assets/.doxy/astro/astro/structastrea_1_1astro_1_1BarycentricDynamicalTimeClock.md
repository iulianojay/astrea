

# Struct astrea::astro::BarycentricDynamicalTimeClock



[**ClassList**](annotated.md) **>** [**astrea**](namespaceastrea.md) **>** [**astro**](namespaceastrea_1_1astro.md) **>** [**BarycentricDynamicalTimeClock**](structastrea_1_1astro_1_1BarycentricDynamicalTimeClock.md)



_A clock implementation for Barycentric Dynamical Time (TDB)._ [More...](#detailed-description)

* `#include <BarycentricDynamicalTimeClock.hpp>`

















## Public Types

| Type | Name |
| ---: | :--- |
| typedef std::chrono::duration&lt; [**rep**](structastrea_1_1astro_1_1BarycentricDynamicalTimeClock.md#typedef-rep), [**period**](structastrea_1_1astro_1_1BarycentricDynamicalTimeClock.md#typedef-period) &gt; | [**duration**](#typedef-duration)  <br>_The duration type, representing time in seconds._  |
| typedef std::ratio&lt; 1 &gt; | [**period**](#typedef-period)  <br>_The period type, seconds._  |
| typedef [**double**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) | [**rep**](#typedef-rep)  <br>_The representation type, a double for sub-second precision._  |
| typedef std::chrono::time\_point&lt; [**BarycentricDynamicalTimeClock**](structastrea_1_1astro_1_1BarycentricDynamicalTimeClock.md) &gt; | [**time\_point**](#typedef-time_point)  <br>_The time point type for TDB, using_ [_**BarycentricDynamicalTimeClock**_](structastrea_1_1astro_1_1BarycentricDynamicalTimeClock.md) _._ |






## Public Static Attributes

| Type | Name |
| ---: | :--- |
|  [**constexpr**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) [**bool**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) | [**is\_steady**](#variable-is_steady)   = `[**false**](classastrea_1_1astro_1_1DirectionCosineMatrix.md)`<br>_TDB is not a steady clock; it is anchored to TAI._  |
|  [**constexpr**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) [**auto**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) | [**jdRef**](#variable-jdref)   = `[**JulianDateClock::duration**](structastrea_1_1astro_1_1JulianDateClock.md#typedef-duration){ 2451545.0 }`<br> |
















## Public Static Functions

| Type | Name |
| ---: | :--- |
|  [**auto**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) | [**from\_sys**](#function-from_sys) (std::chrono::sys\_time&lt; [**Duration**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) &gt; [**const**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) & timePoint) noexcept<br>_Converts a system time point to a Barycentric Dynamical Time time point._  |
|  [**time\_point**](structastrea_1_1astro_1_1BarycentricDynamicalTimeClock.md#typedef-time_point) | [**now**](#function-now) () noexcept<br>_Gets the current time point in Barycentric Dynamical Time format._  |
|  [**auto**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) | [**to\_sys**](#function-to_sys) ([**BarycentricDynamicalTimePoint**](namespaceastrea_1_1astro.md#typedef-barycentricdynamicaltimepoint)&lt; [**Duration**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) &gt; [**const**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) & timePoint) noexcept<br>_Converts a Barycentric Dynamical Time time point to a system time point._  |


























## Detailed Description


[**Geocentric**](classastrea_1_1astro_1_1Geocentric.md) Coordinate Time is a continuous time scale defined by the IAU. It is related to Terrestrial Time (TT) by a linear transformation that accounts for the relativistic effects of Earth's gravitational potential. TCG is commonly used in astrodynamics for high-precision timekeeping in the vicinity of Earth. 


    
## Public Types Documentation




### typedef duration 

_The duration type, representing time in seconds._ 
```C++
using astrea::astro::BarycentricDynamicalTimeClock::duration =  std::chrono::duration<rep, period>;
```




<hr>



### typedef period 

_The period type, seconds._ 
```C++
using astrea::astro::BarycentricDynamicalTimeClock::period =  std::ratio<1>;
```




<hr>



### typedef rep 

_The representation type, a double for sub-second precision._ 
```C++
using astrea::astro::BarycentricDynamicalTimeClock::rep =  double;
```




<hr>



### typedef time\_point 

_The time point type for TDB, using_ [_**BarycentricDynamicalTimeClock**_](structastrea_1_1astro_1_1BarycentricDynamicalTimeClock.md) _._
```C++
using astrea::astro::BarycentricDynamicalTimeClock::time_point =  std::chrono::time_point<BarycentricDynamicalTimeClock>;
```




<hr>
## Public Static Attributes Documentation




### variable is\_steady 

_TDB is not a steady clock; it is anchored to TAI._ 
```C++
constexpr bool astrea::astro::BarycentricDynamicalTimeClock::is_steady;
```




<hr>



### variable jdRef 

```C++
constexpr auto astrea::astro::BarycentricDynamicalTimeClock::jdRef;
```




<hr>
## Public Static Functions Documentation




### function from\_sys 

_Converts a system time point to a Barycentric Dynamical Time time point._ 
```C++
template<class  Duration>
static inline auto astrea::astro::BarycentricDynamicalTimeClock::from_sys (
    std::chrono::sys_time< Duration > const & timePoint
) noexcept
```



The conversion route is: UTC → TT → TDB




**Template parameters:**


* `Duration` The duration type of the system time point. 



**Parameters:**


* `timePoint` The system time point to convert. 



**Returns:**

BarycentricDynamicalTimePoint The converted TDB time point.


[https://ntrs.nasa.gov/api/citations/20220014814/downloads/NASA](https://ntrs.nasa.gov/api/citations/20220014814/downloads/NASA)%20TP%2020220014814%20final.pdf 


        

<hr>



### function now 

_Gets the current time point in Barycentric Dynamical Time format._ 
```C++
static inline time_point astrea::astro::BarycentricDynamicalTimeClock::now () noexcept
```





**Returns:**

[**BarycentricDynamicalTimeClock::time\_point**](structastrea_1_1astro_1_1BarycentricDynamicalTimeClock.md#typedef-time_point) The current time point in TDB format. 





        

<hr>



### function to\_sys 

_Converts a Barycentric Dynamical Time time point to a system time point._ 
```C++
template<class  Duration>
static inline auto astrea::astro::BarycentricDynamicalTimeClock::to_sys (
    BarycentricDynamicalTimePoint < Duration > const & timePoint
) noexcept
```



The conversion route is: TDB → TAI (- 32.184 s) → UTC (via clock\_cast, handling leap seconds).




**Template parameters:**


* `Duration` The duration type of the TDB time point. 



**Parameters:**


* `timePoint` The TDB time point to convert. 



**Returns:**

std::chrono::sys\_time&lt;std::chrono::tai\_clock::duration&gt; The converted system time point.


[https://ntrs.nasa.gov/api/citations/20220014814/downloads/NASA](https://ntrs.nasa.gov/api/citations/20220014814/downloads/NASA)%20TP%2020220014814%20final.pdf 


        

<hr>

------------------------------
The documentation for this class was generated from the following file `astrea/astro/astro/time/clocks/BarycentricDynamicalTimeClock.hpp`

