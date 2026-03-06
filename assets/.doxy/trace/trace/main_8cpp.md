

# File main.cpp



[**FileList**](files.md) **>** [**astrea**](dir_b5324400686b7cece921533bb760c87a.md) **>** [**trace**](dir_e30098dbada9bbfb44888190c04e2af0.md) **>** [**trace**](dir_f04035ba8afac2675c737f654641e7b5.md) **>** [**drivers**](dir_ede4f445fc3b272c23592e211659caf8.md) **>** [**main.cpp**](main_8cpp.md)

[Go to the source code of this file](main_8cpp_source.md)



* `#include <cstdlib>`
* `#include <filesystem>`
* `#include <fstream>`
* `#include <iostream>`
* `#include <ranges>`
* `#include <set>`
* `#include <stdio.h>`
* `#include <sqlite3.h>`
* `#include <csv.hpp>`
* `#include <nlohmann/json.hpp>`
* `#include <sqlite_orm/sqlite_orm.h>`
* `#include <mp-units/systems/angular.h>`
* `#include <mp-units/systems/international.h>`
* `#include <mp-units/systems/isq.h>`
* `#include <mp-units/systems/si.h>`
* `#include <astro/astro.hpp>`
* `#include <snapshot/snapshot.hpp>`
* `#include <trace/trace.hpp>`
* `#include <trace/trace.macros.hpp>`













## Namespaces

| Type | Name |
| ---: | :--- |
| namespace | [**astro**](namespaceastro.md) <br> |
| namespace | [**snapshot**](namespacesnapshot.md) <br> |
| namespace | [**sqlite\_orm**](namespacesqlite__orm.md) <br> |










## Public Static Attributes

| Type | Name |
| ---: | :--- |
|  const Time | [**ACCESS\_RESOLUTION**](#variable-access_resolution)   = `minutes(5.0)`<br> |
|  const Angle | [**GRID\_SPACING**](#variable-grid_spacing)   = `5.0 \* deg`<br> |
|  const bool | [**PRINT\_PROGRESS**](#variable-print_progress)   = `true`<br> |
|  const Time | [**PROP\_TIME**](#variable-prop_time)   = `months(1.0)`<br> |














## Public Functions

| Type | Name |
| ---: | :--- |
|  int | [**arcturus\_starlink\_interference\_test**](#function-arcturus_starlink_interference_test) () <br> |
|  int | [**iceye\_test**](#function-iceye_test) () <br> |
|  int | [**main**](#function-main) () <br> |
|  [**AccessArray**](classastrea_1_1trace_1_1AccessArray.md) | [**propagate\_and\_run\_access\_analysis**](#function-propagate_and_run_access_analysis) (astro::Constellation&lt; T &gt; & constellation, U & grounds, const Date & startDate, const AstrodynamicsSystem & sys, const Time propTime, const Time accessResolution) <br> |




























## Public Static Attributes Documentation




### variable ACCESS\_RESOLUTION 

```C++
const Time ACCESS_RESOLUTION;
```




<hr>



### variable GRID\_SPACING 

```C++
const Angle GRID_SPACING;
```




<hr>



### variable PRINT\_PROGRESS 

```C++
const bool PRINT_PROGRESS;
```




<hr>



### variable PROP\_TIME 

```C++
const Time PROP_TIME;
```




<hr>
## Public Functions Documentation




### function arcturus\_starlink\_interference\_test 

```C++
int arcturus_starlink_interference_test () 
```




<hr>



### function iceye\_test 

```C++
int iceye_test () 
```




<hr>



### function main 

```C++
int main () 
```




<hr>



### function propagate\_and\_run\_access\_analysis 

```C++
template<typename T, typename U>
AccessArray propagate_and_run_access_analysis (
    astro::Constellation< T > & constellation,
    U & grounds,
    const Date & startDate,
    const AstrodynamicsSystem & sys,
    const Time propTime,
    const Time accessResolution
) 
```




<hr>

------------------------------
The documentation for this class was generated from the following file `astrea/trace/trace/drivers/main.cpp`

