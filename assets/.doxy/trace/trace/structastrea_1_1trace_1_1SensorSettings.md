

# Struct astrea::trace::SensorSettings



[**ClassList**](annotated.md) **>** [**astrea**](namespaceastrea.md) **>** [**trace**](namespaceastrea_1_1trace.md) **>** [**SensorSettings**](structastrea_1_1trace_1_1SensorSettings.md)


























## Public Attributes

| Type | Name |
| ---: | :--- |
|  astro::Direction&lt; astro::frames::dynamic::ric &gt; | [**boresight**](#variable-boresight)  <br>_Boresight direction of the sensor in RIC._  |
|  Angle | [**halfConeAngle**](#variable-halfconeangle)  <br>_Half-angle of the sensor's field of view._  |
|  std::string | [**name**](#variable-name)  <br>_Name of the sensor._  |
|  std::string | [**type**](#variable-type)  <br>_Type of sensor (e.g., "circular")_  |
















## Public Functions

| Type | Name |
| ---: | :--- |
|   | [**SensorSettings**](#function-sensorsettings-12) () = default<br> |
|   | [**SensorSettings**](#function-sensorsettings-22) (const nlohmann::json & json) <br> |




























## Public Attributes Documentation




### variable boresight 

_Boresight direction of the sensor in RIC._ 
```C++
astro::Direction<astro::frames::dynamic::ric> astrea::trace::SensorSettings::boresight;
```




<hr>



### variable halfConeAngle 

_Half-angle of the sensor's field of view._ 
```C++
Angle astrea::trace::SensorSettings::halfConeAngle;
```




<hr>



### variable name 

_Name of the sensor._ 
```C++
std::string astrea::trace::SensorSettings::name;
```




<hr>



### variable type 

_Type of sensor (e.g., "circular")_ 
```C++
std::string astrea::trace::SensorSettings::type;
```




<hr>
## Public Functions Documentation




### function SensorSettings [1/2]

```C++
astrea::trace::SensorSettings::SensorSettings () = default
```




<hr>



### function SensorSettings [2/2]

```C++
inline astrea::trace::SensorSettings::SensorSettings (
    const nlohmann::json & json
) 
```




<hr>

------------------------------
The documentation for this class was generated from the following file `astrea/trace/trace/analysis/TraceConfig.hpp`

