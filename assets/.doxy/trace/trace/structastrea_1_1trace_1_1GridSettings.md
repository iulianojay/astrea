

# Struct astrea::trace::GridSettings



[**ClassList**](annotated.md) **>** [**astrea**](namespaceastrea.md) **>** [**trace**](namespaceastrea_1_1trace.md) **>** [**GridSettings**](structastrea_1_1trace_1_1GridSettings.md)


























## Public Attributes

| Type | Name |
| ---: | :--- |
|  [**LatRange**](namespaceastrea_1_1trace.md#typedef-latrange) | [**latRange**](#variable-latrange)  <br>_Latitude range of the grid._  |
|  [**LonRange**](namespaceastrea_1_1trace.md#typedef-lonrange) | [**lonRange**](#variable-lonrange)  <br>_Longitude range of the grid._  |
|  Angle | [**spacing**](#variable-spacing)  <br>_Spacing of the grid points._  |
|  std::string | [**type**](#variable-type)  <br>_Type of grid (e.g., "uniform")_  |
















## Public Functions

| Type | Name |
| ---: | :--- |
|   | [**GridSettings**](#function-gridsettings-12) () = default<br> |
|   | [**GridSettings**](#function-gridsettings-22) (const nlohmann::json & json) <br> |




























## Public Attributes Documentation




### variable latRange 

_Latitude range of the grid._ 
```C++
LatRange astrea::trace::GridSettings::latRange;
```




<hr>



### variable lonRange 

_Longitude range of the grid._ 
```C++
LonRange astrea::trace::GridSettings::lonRange;
```




<hr>



### variable spacing 

_Spacing of the grid points._ 
```C++
Angle astrea::trace::GridSettings::spacing;
```




<hr>



### variable type 

_Type of grid (e.g., "uniform")_ 
```C++
std::string astrea::trace::GridSettings::type;
```




<hr>
## Public Functions Documentation




### function GridSettings [1/2]

```C++
astrea::trace::GridSettings::GridSettings () = default
```




<hr>



### function GridSettings [2/2]

```C++
inline astrea::trace::GridSettings::GridSettings (
    const nlohmann::json & json
) 
```




<hr>

------------------------------
The documentation for this class was generated from the following file `astrea/trace/trace/analysis/TraceConfig.hpp`

