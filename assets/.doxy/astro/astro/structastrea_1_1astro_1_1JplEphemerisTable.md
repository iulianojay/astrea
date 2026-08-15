

# Struct astrea::astro::JplEphemerisTable



[**ClassList**](annotated.md) **>** [**astrea**](namespaceastrea.md) **>** [**astro**](namespaceastrea_1_1astro.md) **>** [**JplEphemerisTable**](structastrea_1_1astro_1_1JplEphemerisTable.md)



_Base class for any JPL_ [_**CelestialBody**_](structastrea_1_1astro_1_1CelestialBody.md) _table._

* `#include <JplEphemerisTable.hpp>`















































## Protected Static Attributes

| Type | Name |
| ---: | :--- |
|  const [**Date**](classastrea_1_1astro_1_1Date.md) | [**START\_DATE**](#variable-start_date)   = `[**Date**](classastrea_1_1astro_1_1Date.md)("1999-12-24 00:00:00")`<br>_Lower bound on MJD J2K in the TDB time system._  |
|  const [**Date**](classastrea_1_1astro_1_1Date.md) | [**STOP\_DATE**](#variable-stop_date)   = `[**Date**](classastrea_1_1astro_1_1Date.md)("2100-01-12 00:00:00")`<br>_Upper bound on MJD J2K in the TDB time system._  |














## Protected Functions

| Type | Name |
| ---: | :--- |
|   | [**JplEphemerisTable**](#function-jplephemeristable) () = delete<br> |
|   | [**~JplEphemerisTable**](#function-jplephemeristable) () = delete<br> |


## Protected Static Functions

| Type | Name |
| ---: | :--- |
|  std::size\_t | [**get\_index**](#function-get_index) (const [**Date**](classastrea_1_1astro_1_1Date.md) & date, const Time & timePerPoly) <br>_Get the index corresponding to the Chebyshev polynomial coefficients._  |


## Protected Static Attributes Documentation




### variable START\_DATE 

_Lower bound on MJD J2K in the TDB time system._ 
```C++
const Date astrea::astro::JplEphemerisTable::START_DATE;
```




<hr>



### variable STOP\_DATE 

_Upper bound on MJD J2K in the TDB time system._ 
```C++
const Date astrea::astro::JplEphemerisTable::STOP_DATE;
```




<hr>
## Protected Functions Documentation




### function JplEphemerisTable 

```C++
astrea::astro::JplEphemerisTable::JplEphemerisTable () = delete
```




<hr>



### function ~JplEphemerisTable 

```C++
astrea::astro::JplEphemerisTable::~JplEphemerisTable () = delete
```




<hr>
## Protected Static Functions Documentation




### function get\_index 

_Get the index corresponding to the Chebyshev polynomial coefficients._ 
```C++
static std::size_t astrea::astro::JplEphemerisTable::get_index (
    const Date & date,
    const Time & timePerPoly
) 
```





**Parameters:**


* `date` [**Date**](classastrea_1_1astro_1_1Date.md) for which the index is to be computed 
* `timePerPoly` Amount of time each set of polynomial coefficients covers



**Returns:**

Table lookup index 





        

<hr>

------------------------------
The documentation for this class was generated from the following file `astrea/astro/astro/systems/celestial_bodies/JplEphemerisTable.hpp`

