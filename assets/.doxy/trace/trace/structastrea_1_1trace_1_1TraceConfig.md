

# Struct astrea::trace::TraceConfig



[**ClassList**](annotated.md) **>** [**astrea**](namespaceastrea.md) **>** [**trace**](namespaceastrea_1_1trace.md) **>** [**TraceConfig**](structastrea_1_1trace_1_1TraceConfig.md)



_Configuration for a trace analysis run._ [More...](#detailed-description)

* `#include <TraceConfig.hpp>`





















## Public Attributes

| Type | Name |
| ---: | :--- |
|  [**AnalysisSettings**](structastrea_1_1trace_1_1AnalysisSettings.md) | [**analysisSettings**](#variable-analysissettings)  <br> |
|  [**ConstellationSettings**](structastrea_1_1trace_1_1ConstellationSettings.md) | [**constellationSettings**](#variable-constellationsettings)  <br> |
|  [**GroundSettings**](structastrea_1_1trace_1_1GroundSettings.md) | [**groundSettings**](#variable-groundsettings)  <br> |
|  [**OutputSettings**](structastrea_1_1trace_1_1OutputSettings.md) | [**outputSettings**](#variable-outputsettings)  <br> |
|  [**SensorSettings**](structastrea_1_1trace_1_1SensorSettings.md) | [**sensorSettings**](#variable-sensorsettings)  <br> |
















## Public Functions

| Type | Name |
| ---: | :--- |
|   | [**TraceConfig**](#function-traceconfig-12) () = default<br> |
|   | [**TraceConfig**](#function-traceconfig-22) (const nlohmann::json & json) <br>_Construct a_ [_**TraceConfig**_](structastrea_1_1trace_1_1TraceConfig.md) _from a JSON object._ |




























## Detailed Description


All parameters have sensible defaults that replicate the original hard-coded behaviour. The struct can be constructed from a JSON object whose keys follow snake\_case field names (see the explicit constructor below). Any key absent from the JSON retains its default. 


    
## Public Attributes Documentation




### variable analysisSettings 

```C++
AnalysisSettings astrea::trace::TraceConfig::analysisSettings;
```




<hr>



### variable constellationSettings 

```C++
ConstellationSettings astrea::trace::TraceConfig::constellationSettings;
```




<hr>



### variable groundSettings 

```C++
GroundSettings astrea::trace::TraceConfig::groundSettings;
```




<hr>



### variable outputSettings 

```C++
OutputSettings astrea::trace::TraceConfig::outputSettings;
```




<hr>



### variable sensorSettings 

```C++
SensorSettings astrea::trace::TraceConfig::sensorSettings;
```




<hr>
## Public Functions Documentation




### function TraceConfig [1/2]

```C++
astrea::trace::TraceConfig::TraceConfig () = default
```




<hr>



### function TraceConfig [2/2]

_Construct a_ [_**TraceConfig**_](structastrea_1_1trace_1_1TraceConfig.md) _from a JSON object._
```C++
inline astrea::trace::TraceConfig::TraceConfig (
    const nlohmann::json & json
) 
```




<hr>

------------------------------
The documentation for this class was generated from the following file `astrea/trace/trace/analysis/TraceConfig.hpp`

