

# Struct astrea::trace::AnalysisSettings



[**ClassList**](annotated.md) **>** [**astrea**](namespaceastrea.md) **>** [**trace**](namespaceastrea_1_1trace.md) **>** [**AnalysisSettings**](structastrea_1_1trace_1_1AnalysisSettings.md)


























## Public Attributes

| Type | Name |
| ---: | :--- |
|  astro::Date | [**epoch**](#variable-epoch)  <br>_Epoch of the simulation._  |
|  Time | [**resolution**](#variable-resolution)  <br>_Time resolution of the simulation._  |
|  Time | [**simTime**](#variable-simtime)  <br>_Total simulation time._  |
















## Public Functions

| Type | Name |
| ---: | :--- |
|   | [**AnalysisSettings**](#function-analysissettings-12) () = default<br> |
|   | [**AnalysisSettings**](#function-analysissettings-22) (const nlohmann::json & json) <br> |




























## Public Attributes Documentation




### variable epoch 

_Epoch of the simulation._ 
```C++
astro::Date astrea::trace::AnalysisSettings::epoch;
```




<hr>



### variable resolution 

_Time resolution of the simulation._ 
```C++
Time astrea::trace::AnalysisSettings::resolution;
```




<hr>



### variable simTime 

_Total simulation time._ 
```C++
Time astrea::trace::AnalysisSettings::simTime;
```




<hr>
## Public Functions Documentation




### function AnalysisSettings [1/2]

```C++
astrea::trace::AnalysisSettings::AnalysisSettings () = default
```




<hr>



### function AnalysisSettings [2/2]

```C++
inline astrea::trace::AnalysisSettings::AnalysisSettings (
    const nlohmann::json & json
) 
```




<hr>

------------------------------
The documentation for this class was generated from the following file `astrea/trace/trace/analysis/TraceConfig.hpp`

