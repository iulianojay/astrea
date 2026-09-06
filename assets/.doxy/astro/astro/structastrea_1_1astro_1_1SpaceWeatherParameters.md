

# Struct astrea::astro::SpaceWeatherParameters



[**ClassList**](annotated.md) **>** [**astrea**](namespaceastrea.md) **>** [**astro**](namespaceastrea_1_1astro.md) **>** [**SpaceWeatherParameters**](structastrea_1_1astro_1_1SpaceWeatherParameters.md)



_Struct to hold space weather parameters for a specific date._ [More...](#detailed-description)

* `#include <SpaceWeatherData.hpp>`





















## Public Attributes

| Type | Name |
| ---: | :--- |
|  std::array&lt; Unitless, 8 &gt; | [**ap**](#variable-ap)  <br>_Planetary Equivalent Amplitude with each index corresponding to the ith 3-hour interval of the day (00-03, 03-06, 06-09, 09-12, 12-15, 15-18, 18-21, 21-24)._  |
|  Unitless | [**avgAp**](#variable-avgap)  <br>_Daily Average of the 8 Ap indices._  |
|  std::uint8\_t | [**bsrn**](#variable-bsrn)  <br>_Bartels Solar Rotation Number. A sequence of 27-day intervals counted continuously from 1832 Feb 8._  |
|  std::uint8\_t | [**c9**](#variable-c9)  <br>_C9. A conversion of the 0-to-2.5 range of the Cp index to one digit between 0 and 9._  |
|  Unitless | [**cp**](#variable-cp)  <br>_magnetic activity for the day determined from the sum of the 8 Ap indices. Cp ranges, in steps of one-tenth, from 0 (quiet) to 2.5 (highly disturbed)._  |
|  [**Date**](classastrea_1_1astro_1_1Date.md) | [**date**](#variable-date)  <br> |
|  [**SolarFluxData**](structastrea_1_1astro_1_1SolarFluxData.md) | [**f107Adj**](#variable-f107adj)  <br>_Adjusted 10.7 cm Solar Radio Flux adjusted to 1 AU._  |
|  [**SolarFluxData**](structastrea_1_1astro_1_1SolarFluxData.md) | [**f107Obs**](#variable-f107obs)  <br>_Observed 10.7 cm Solar Radio Flux._  |
|  unsigned | [**isn**](#variable-isn)  <br>_International Sunspot Number. Records contain the Zurich number through 1980 Dec 31 and the International Brussels number thereafter._  |
|  std::array&lt; Unitless, 8 &gt; | [**kp**](#variable-kp)  <br>_Planetary 3-hour Range Index with each index corresponding to the ith 3-hour interval of the day (00-03, 03-06, 06-09, 09-12, 12-15, 15-18, 18-21, 21-24)._  |
|  [**MeasurementType**](namespaceastrea_1_1astro.md#enum-measurementtype) | [**measurement**](#variable-measurement)  <br> |
|  std::uint8\_t | [**nd**](#variable-nd)  <br>_Number of Day within the Bartels 27-day cycle (01-27)._  |
|  Unitless | [**sumKp**](#variable-sumkp)  <br>_Daily Sum of the 8 Kp indices._  |












































## Detailed Description


This struct contains various space weather parameters, including the Bartels Solar Rotation Number, Kp indices, Ap indices, Cp index, International Sunspot Number, and 10.7 cm Solar Radio Flux data.




**Note:**

Format from [https://celestrak.org/SpaceData/SpaceWx-format.php](https://celestrak.org/SpaceData/SpaceWx-format.php) 





    
## Public Attributes Documentation




### variable ap 

_Planetary Equivalent Amplitude with each index corresponding to the ith 3-hour interval of the day (00-03, 03-06, 06-09, 09-12, 12-15, 15-18, 18-21, 21-24)._ 
```C++
std::array<Unitless, 8> astrea::astro::SpaceWeatherParameters::ap;
```




<hr>



### variable avgAp 

_Daily Average of the 8 Ap indices._ 
```C++
Unitless astrea::astro::SpaceWeatherParameters::avgAp;
```




<hr>



### variable bsrn 

_Bartels Solar Rotation Number. A sequence of 27-day intervals counted continuously from 1832 Feb 8._ 
```C++
std::uint8_t astrea::astro::SpaceWeatherParameters::bsrn;
```




<hr>



### variable c9 

_C9. A conversion of the 0-to-2.5 range of the Cp index to one digit between 0 and 9._ 
```C++
std::uint8_t astrea::astro::SpaceWeatherParameters::c9;
```




<hr>



### variable cp 

_magnetic activity for the day determined from the sum of the 8 Ap indices. Cp ranges, in steps of one-tenth, from 0 (quiet) to 2.5 (highly disturbed)._ 
```C++
Unitless astrea::astro::SpaceWeatherParameters::cp;
```



Cp or Planetary Daily Character Figure. A qualitative estimate of overall level of 


        

<hr>



### variable date 

```C++
Date astrea::astro::SpaceWeatherParameters::date;
```




<hr>



### variable f107Adj 

_Adjusted 10.7 cm Solar Radio Flux adjusted to 1 AU._ 
```C++
SolarFluxData astrea::astro::SpaceWeatherParameters::f107Adj;
```




<hr>



### variable f107Obs 

_Observed 10.7 cm Solar Radio Flux._ 
```C++
SolarFluxData astrea::astro::SpaceWeatherParameters::f107Obs;
```




<hr>



### variable isn 

_International Sunspot Number. Records contain the Zurich number through 1980 Dec 31 and the International Brussels number thereafter._ 
```C++
unsigned astrea::astro::SpaceWeatherParameters::isn;
```




<hr>



### variable kp 

_Planetary 3-hour Range Index with each index corresponding to the ith 3-hour interval of the day (00-03, 03-06, 06-09, 09-12, 12-15, 15-18, 18-21, 21-24)._ 
```C++
std::array<Unitless, 8> astrea::astro::SpaceWeatherParameters::kp;
```




<hr>



### variable measurement 

```C++
MeasurementType astrea::astro::SpaceWeatherParameters::measurement;
```




<hr>



### variable nd 

_Number of Day within the Bartels 27-day cycle (01-27)._ 
```C++
std::uint8_t astrea::astro::SpaceWeatherParameters::nd;
```




<hr>



### variable sumKp 

_Daily Sum of the 8 Kp indices._ 
```C++
Unitless astrea::astro::SpaceWeatherParameters::sumKp;
```




<hr>

------------------------------
The documentation for this class was generated from the following file `astrea/astro/astro/propagation/force_models/space_weather/SpaceWeatherData.hpp`

