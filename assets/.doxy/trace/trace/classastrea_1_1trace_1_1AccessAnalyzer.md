

# Class astrea::trace::AccessAnalyzer



[**ClassList**](annotated.md) **>** [**astrea**](namespaceastrea.md) **>** [**trace**](namespaceastrea_1_1trace.md) **>** [**AccessAnalyzer**](classastrea_1_1trace_1_1AccessAnalyzer.md)










































## Public Functions

| Type | Name |
| ---: | :--- |
|   | [**AccessAnalyzer**](#function-accessanalyzer) (const Time & resolution, const astro::Date & startDate, const astro::Date & endDate, const astro::AstrodynamicsSystem & sys, const bool printProgress=false) <br>_Constructor for_ [_**AccessAnalyzer**_](classastrea_1_1trace_1_1AccessAnalyzer.md) _with specified resolution and date range._ |
|  [**AccessArray**](classastrea_1_1trace_1_1AccessArray.md) | [**find\_accesses**](#function-find_accesses-12) ([**ViewerConstellation**](namespaceastrea_1_1trace.md#typedef-viewerconstellation) & constel, [**GroundArchitecture**](classastrea_1_1trace_1_1GroundArchitecture.md) & grounds, const bool includeInternalAccesses=false) <br>_Find accesses between a constellation of viewers and a ground architecture._  |
|  [**AccessArray**](classastrea_1_1trace_1_1AccessArray.md) | [**find\_accesses**](#function-find_accesses-22) ([**ViewerConstellation**](namespaceastrea_1_1trace.md#typedef-viewerconstellation) & constel, [**Grid**](classastrea_1_1trace_1_1Grid.md) & grid, const bool includeInternalAccesses=false) <br>_Find accesses between a constellation of viewers and a ground architecture._  |
|  [**AccessArray**](classastrea_1_1trace_1_1AccessArray.md) | [**find\_internal\_accesses**](#function-find_internal_accesses) ([**ViewerConstellation**](namespaceastrea_1_1trace.md#typedef-viewerconstellation) & constel, const bool clearPositionCache=true) <br>_Find accesses between a constellation of viewers._  |
|   | [**~AccessAnalyzer**](#function-accessanalyzer) () = default<br>_Destructor for_ [_**AccessAnalyzer**_](classastrea_1_1trace_1_1AccessAnalyzer.md) _._ |




























## Public Functions Documentation




### function AccessAnalyzer 

_Constructor for_ [_**AccessAnalyzer**_](classastrea_1_1trace_1_1AccessAnalyzer.md) _with specified resolution and date range._
```C++
inline astrea::trace::AccessAnalyzer::AccessAnalyzer (
    const Time & resolution,
    const astro::Date & startDate,
    const astro::Date & endDate,
    const astro::AstrodynamicsSystem & sys,
    const bool printProgress=false
) 
```





**Parameters:**


* `resolution` The time resolution for access calculations. 
* `startDate` The start date for the analysis. 
* `endDate` The end date for the analysis. 
* `sys` The astrodynamics system used for calculations. 
* `printProgress` Flag indicating whether to print progress during calculations. 




        

<hr>



### function find\_accesses [1/2]

_Find accesses between a constellation of viewers and a ground architecture._ 
```C++
AccessArray astrea::trace::AccessAnalyzer::find_accesses (
    ViewerConstellation & constel,
    GroundArchitecture & grounds,
    const bool includeInternalAccesses=false
) 
```





**Parameters:**


* `constel` The constellation of viewers. 
* `grounds` The ground architecture containing ground stations. 
* `resolution` The time resolution for access calculations. 
* `startDate` The start date for the analysis. 
* `endDate` The end date for the analysis. 
* `sys` The astrodynamics system used for calculations. 



**Returns:**

[**AccessArray**](classastrea_1_1trace_1_1AccessArray.md) A collection of accesses between viewers and ground stations. 





        

<hr>



### function find\_accesses [2/2]

_Find accesses between a constellation of viewers and a ground architecture._ 
```C++
AccessArray astrea::trace::AccessAnalyzer::find_accesses (
    ViewerConstellation & constel,
    Grid & grid,
    const bool includeInternalAccesses=false
) 
```





**Parameters:**


* `constel` The constellation of viewers. 
* `grid` The grid containing ground points. 



**Returns:**

[**AccessArray**](classastrea_1_1trace_1_1AccessArray.md) A collection of accesses between viewers and ground stations. 





        

<hr>



### function find\_internal\_accesses 

_Find accesses between a constellation of viewers._ 
```C++
AccessArray astrea::trace::AccessAnalyzer::find_internal_accesses (
    ViewerConstellation & constel,
    const bool clearPositionCache=true
) 
```





**Parameters:**


* `constel` The constellation of viewers. 
* `sys` The astrodynamics system used for calculations. 



**Returns:**

[**AccessArray**](classastrea_1_1trace_1_1AccessArray.md) A collection of accesses between viewers. 





        

<hr>



### function ~AccessAnalyzer 

_Destructor for_ [_**AccessAnalyzer**_](classastrea_1_1trace_1_1AccessAnalyzer.md) _._
```C++
astrea::trace::AccessAnalyzer::~AccessAnalyzer () = default
```




<hr>

------------------------------
The documentation for this class was generated from the following file `astrea/trace/trace/analysis/AccessAnalyzer.hpp`

