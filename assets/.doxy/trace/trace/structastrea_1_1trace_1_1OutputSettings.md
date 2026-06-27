

# Struct astrea::trace::OutputSettings



[**ClassList**](annotated.md) **>** [**astrea**](namespaceastrea.md) **>** [**trace**](namespaceastrea_1_1trace.md) **>** [**OutputSettings**](structastrea_1_1trace_1_1OutputSettings.md)


























## Public Attributes

| Type | Name |
| ---: | :--- |
|  std::string | [**dbName**](#variable-dbname)  <br>_Name of the output database._  |
|  std::string | [**outdir**](#variable-outdir)  <br>_Output directory for results._  |
|  bool | [**printProgress**](#variable-printprogress)  <br>_Flag to print progress during analysis._  |
|  bool | [**runPlotter**](#variable-runplotter)  <br>_Flag to run the plotter after analysis._  |
|  bool | [**saveResults**](#variable-saveresults)  <br>_Flag to save results to the database._  |
















## Public Functions

| Type | Name |
| ---: | :--- |
|   | [**OutputSettings**](#function-outputsettings-12) () = default<br> |
|   | [**OutputSettings**](#function-outputsettings-22) (const nlohmann::json & json) <br> |




























## Public Attributes Documentation




### variable dbName 

_Name of the output database._ 
```C++
std::string astrea::trace::OutputSettings::dbName;
```




<hr>



### variable outdir 

_Output directory for results._ 
```C++
std::string astrea::trace::OutputSettings::outdir;
```




<hr>



### variable printProgress 

_Flag to print progress during analysis._ 
```C++
bool astrea::trace::OutputSettings::printProgress;
```




<hr>



### variable runPlotter 

_Flag to run the plotter after analysis._ 
```C++
bool astrea::trace::OutputSettings::runPlotter;
```




<hr>



### variable saveResults 

_Flag to save results to the database._ 
```C++
bool astrea::trace::OutputSettings::saveResults;
```




<hr>
## Public Functions Documentation




### function OutputSettings [1/2]

```C++
astrea::trace::OutputSettings::OutputSettings () = default
```




<hr>



### function OutputSettings [2/2]

```C++
inline astrea::trace::OutputSettings::OutputSettings (
    const nlohmann::json & json
) 
```




<hr>

------------------------------
The documentation for this class was generated from the following file `astrea/trace/trace/analysis/TraceConfig.hpp`

