

# Struct astrea::astro::GeocentricCoordinateTimeClock



[**ClassList**](annotated.md) **>** [**astrea**](namespaceastrea.md) **>** [**astro**](namespaceastrea_1_1astro.md) **>** [**GeocentricCoordinateTimeClock**](structastrea_1_1astro_1_1GeocentricCoordinateTimeClock.md)



_A clock implementation for_ [_**Geocentric**_](classastrea_1_1astro_1_1Geocentric.md) _Coordinate Time (TCG)._[More...](#detailed-description)

* `#include <GeocentricCoordinateTimeClock.hpp>`

















## Public Types

| Type | Name |
| ---: | :--- |
| typedef std::chrono::duration&lt; [**rep**](structastrea_1_1astro_1_1GeocentricCoordinateTimeClock.md#typedef-rep), [**period**](structastrea_1_1astro_1_1GeocentricCoordinateTimeClock.md#typedef-period) &gt; | [**duration**](#typedef-duration)  <br>_The duration type, representing time in seconds._  |
| typedef std::ratio&lt; 1 &gt; | [**period**](#typedef-period)  <br>_The period type, seconds._  |
| typedef double | [**rep**](#typedef-rep)  <br>_The representation type, a double for sub-second precision._  |
| typedef std::chrono::time\_point&lt; [**GeocentricCoordinateTimeClock**](structastrea_1_1astro_1_1GeocentricCoordinateTimeClock.md) &gt; | [**time\_point**](#typedef-time_point)  <br>_The time point type for TCG, using_ [_**GeocentricCoordinateTimeClock**_](structastrea_1_1astro_1_1GeocentricCoordinateTimeClock.md) _._ |






## Public Static Attributes

| Type | Name |
| ---: | :--- |
|  constexpr [**rep**](structastrea_1_1astro_1_1GeocentricCoordinateTimeClock.md#typedef-rep) | [**Lg**](#variable-lg)   = `{ 6.969290134e-10 }`<br>_The dimensionless constant Lg, representing the rate difference between TCG and TT._  |
|  constexpr bool | [**is\_steady**](#variable-is_steady)   = `false`<br>_TCG is not a steady clock; it is anchored to TAI._  |
|  constexpr [**JulianDateClock::duration**](structastrea_1_1astro_1_1JulianDateClock.md#typedef-duration) | [**jdRef**](#variable-jdref)   = `{ 2443144.5 }`<br> |
















## Public Static Functions

| Type | Name |
| ---: | :--- |
|  auto | [**from\_sys**](#function-from_sys) (std::chrono::sys\_time&lt; Duration &gt; const & timePoint) noexcept<br>_Converts a system time point to a_ [_**Geocentric**_](classastrea_1_1astro_1_1Geocentric.md) _Coordinate Time time point._ |
|  [**time\_point**](structastrea_1_1astro_1_1GeocentricCoordinateTimeClock.md#typedef-time_point) | [**now**](#function-now) () noexcept<br>_Gets the current time point in_ [_**Geocentric**_](classastrea_1_1astro_1_1Geocentric.md) _Coordinate Time format._ |
|  auto | [**to\_sys**](#function-to_sys) ([**GeocentricCoordinateDateTime**](namespaceastrea_1_1astro.md#typedef-geocentriccoordinatedatetime)&lt; Duration &gt; const & timePoint) noexcept<br>_Converts a_ [_**Geocentric**_](classastrea_1_1astro_1_1Geocentric.md) _Coordinate Time time point to a system time point._ |


























## Detailed Description


[**Geocentric**](classastrea_1_1astro_1_1Geocentric.md) Coordinate Time is a continuous time scale defined by the IAU. It is related to Terrestrial Time (TT) by a linear transformation that accounts for the relativistic effects of Earth's gravitational potential. TCG is commonly used in astrodynamics for high-precision timekeeping in the vicinity of Earth. 


    
## Public Types Documentation




### typedef duration 

_The duration type, representing time in seconds._ 
```C++
using astrea::astro::GeocentricCoordinateTimeClock::duration =  std::chrono::duration<rep, period>;
```




<hr>



### typedef period 

_The period type, seconds._ 
```C++
using astrea::astro::GeocentricCoordinateTimeClock::period =  std::ratio<1>;
```




<hr>



### typedef rep 

_The representation type, a double for sub-second precision._ 
```C++
using astrea::astro::GeocentricCoordinateTimeClock::rep =  double;
```




<hr>



### typedef time\_point 

_The time point type for TCG, using_ [_**GeocentricCoordinateTimeClock**_](structastrea_1_1astro_1_1GeocentricCoordinateTimeClock.md) _._
```C++
using astrea::astro::GeocentricCoordinateTimeClock::time_point =  std::chrono::time_point<GeocentricCoordinateTimeClock>;
```




<hr>
## Public Static Attributes Documentation




### variable Lg 

_The dimensionless constant Lg, representing the rate difference between TCG and TT._ 
```C++
constexpr rep astrea::astro::GeocentricCoordinateTimeClock::Lg;
```




<hr>



### variable is\_steady 

_TCG is not a steady clock; it is anchored to TAI._ 
```C++
constexpr bool astrea::astro::GeocentricCoordinateTimeClock::is_steady;
```




<hr>



### variable jdRef 

```C++
constexpr JulianDateClock::duration astrea::astro::GeocentricCoordinateTimeClock::jdRef;
```




<hr>
## Public Static Functions Documentation




### function from\_sys 

_Converts a system time point to a_ [_**Geocentric**_](classastrea_1_1astro_1_1Geocentric.md) _Coordinate Time time point._
```C++
template<class Duration>
static inline auto astrea::astro::GeocentricCoordinateTimeClock::from_sys (
    std::chrono::sys_time< Duration > const & timePoint
) noexcept
```



The conversion route is: UTC → TT → TCG




**Template parameters:**


* `Duration` The duration type of the system time point. 



**Parameters:**


* `timePoint` The system time point to convert. 



**Returns:**

GeocentricCoordinateDateTime The converted TCG time point.


[https://ntrs.nasa.gov/api/citations/20220014814/downloads/NASA](https://ntrs.nasa.gov/api/citations/20220014814/downloads/NASA)%20TP%2020220014814%20final.pdf 


        

<hr>



### function now 

_Gets the current time point in_ [_**Geocentric**_](classastrea_1_1astro_1_1Geocentric.md) _Coordinate Time format._
```C++
static inline time_point astrea::astro::GeocentricCoordinateTimeClock::now () noexcept
```





**Returns:**

[**GeocentricCoordinateTimeClock::time\_point**](structastrea_1_1astro_1_1GeocentricCoordinateTimeClock.md#typedef-time_point) The current time point in TCG format. 





        

<hr>



### function to\_sys 

_Converts a_ [_**Geocentric**_](classastrea_1_1astro_1_1Geocentric.md) _Coordinate Time time point to a system time point._
```C++
template<class Duration>
static inline auto astrea::astro::GeocentricCoordinateTimeClock::to_sys (
    GeocentricCoordinateDateTime < Duration > const & timePoint
) noexcept
```



The conversion route is: TCG → TAI (- 32.184 s) → UTC (via clock\_cast, handling leap seconds).




**Template parameters:**


* `Duration` The duration type of the TCG time point. 



**Parameters:**


* `timePoint` The TCG time point to convert. 



**Returns:**

std::chrono::sys\_time&lt;std::chrono::tai\_clock::duration&gt; The converted system time point.


[https://ntrs.nasa.gov/api/citations/20220014814/downloads/NASA](https://ntrs.nasa.gov/api/citations/20220014814/downloads/NASA)%20TP%2020220014814%20final.pdf 


        

<hr>

------------------------------
The documentation for this class was generated from the following file `astrea/astro/astro/time/clocks/GeocentricCoordinateTimeClock.hpp`

