

# Struct astrea::trace::ConstellationSettings



[**ClassList**](annotated.md) **>** [**astrea**](namespaceastrea.md) **>** [**trace**](namespaceastrea_1_1trace.md) **>** [**ConstellationSettings**](structastrea_1_1trace_1_1ConstellationSettings.md)


























## Public Attributes

| Type | Name |
| ---: | :--- |
|  Distance | [**altitude**](#variable-altitude)  <br>_Altitude of the constellation._  |
|  Angle | [**anchorRaan**](#variable-anchorraan)  <br>_Right ascension of the ascending node for the anchor satellite._  |
|  Angle | [**anchorTrueAnomaly**](#variable-anchortrueanomaly)  <br>_True anomaly of the anchor satellite._  |
|  Angle | [**inclination**](#variable-inclination)  <br>_Inclination of the constellation._  |
|  std::size\_t | [**nPlanes**](#variable-nplanes)  <br>_Number of planes in the constellation._  |
|  std::size\_t | [**nSats**](#variable-nsats)  <br>_Number of satellites per plane._  |
|  Unitless | [**phasing**](#variable-phasing)  <br>_Phasing parameter for walkers._  |
















## Public Functions

| Type | Name |
| ---: | :--- |
|   | [**ConstellationSettings**](#function-constellationsettings-12) () = default<br> |
|   | [**ConstellationSettings**](#function-constellationsettings-22) (const nlohmann::json & json) <br> |




























## Public Attributes Documentation




### variable altitude 

_Altitude of the constellation._ 
```C++
Distance astrea::trace::ConstellationSettings::altitude;
```




<hr>



### variable anchorRaan 

_Right ascension of the ascending node for the anchor satellite._ 
```C++
Angle astrea::trace::ConstellationSettings::anchorRaan;
```




<hr>



### variable anchorTrueAnomaly 

_True anomaly of the anchor satellite._ 
```C++
Angle astrea::trace::ConstellationSettings::anchorTrueAnomaly;
```




<hr>



### variable inclination 

_Inclination of the constellation._ 
```C++
Angle astrea::trace::ConstellationSettings::inclination;
```




<hr>



### variable nPlanes 

_Number of planes in the constellation._ 
```C++
std::size_t astrea::trace::ConstellationSettings::nPlanes;
```




<hr>



### variable nSats 

_Number of satellites per plane._ 
```C++
std::size_t astrea::trace::ConstellationSettings::nSats;
```




<hr>



### variable phasing 

_Phasing parameter for walkers._ 
```C++
Unitless astrea::trace::ConstellationSettings::phasing;
```




<hr>
## Public Functions Documentation




### function ConstellationSettings [1/2]

```C++
astrea::trace::ConstellationSettings::ConstellationSettings () = default
```




<hr>



### function ConstellationSettings [2/2]

```C++
inline astrea::trace::ConstellationSettings::ConstellationSettings (
    const nlohmann::json & json
) 
```




<hr>

------------------------------
The documentation for this class was generated from the following file `astrea/trace/trace/analysis/TraceConfig.hpp`

