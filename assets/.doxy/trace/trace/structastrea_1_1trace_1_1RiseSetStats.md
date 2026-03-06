

# Struct astrea::trace::RiseSetStats



[**ClassList**](annotated.md) **>** [**astrea**](namespaceastrea.md) **>** [**trace**](namespaceastrea_1_1trace.md) **>** [**RiseSetStats**](structastrea_1_1trace_1_1RiseSetStats.md)



_The_ [_**RiseSetStats**_](structastrea_1_1trace_1_1RiseSetStats.md) _struct represents statistics for rise and set times based on a_[_**RiseSetArray**_](classastrea_1_1trace_1_1RiseSetArray.md) _and a RiseSetMetric._[More...](#detailed-description)

* `#include <RiseSetStats.hpp>`





































## Public Functions

| Type | Name |
| ---: | :--- |
|   | [**RiseSetStats**](#function-risesetstats-12) () = default<br>_Default constructor for_ [_**RiseSetStats**_](structastrea_1_1trace_1_1RiseSetStats.md) _._ |
|   | [**RiseSetStats**](#function-risesetstats-22) (const [**RiseSetArray**](classastrea_1_1trace_1_1RiseSetArray.md) & risesets) <br>_Constructs a_ [_**RiseSetStats**_](structastrea_1_1trace_1_1RiseSetStats.md) _object from a_[_**RiseSetArray**_](classastrea_1_1trace_1_1RiseSetArray.md) _and a RiseSetMetric._ |
|  const auto & | [**at**](#function-at) (const [**RiseSetMetric**](namespaceastrea_1_1trace.md#enum-risesetmetric) & metric) const<br>_Accesses the statistics for a given RiseSetMetric._  |
|  auto & | [**operator[]**](#function-operator) (const [**RiseSetMetric**](namespaceastrea_1_1trace.md#enum-risesetmetric) & metric) <br>_Accesses the statistics for a given RiseSetMetric._  |
|  std::vector&lt; std::string &gt; | [**to\_string\_vector**](#function-to_string_vector) () const<br>_Converts the statistics to a vector of strings for output._  |




























## Detailed Description


It contains a map of RiseSetMetric to [**Stats&lt;Time&gt;**](structastrea_1_1trace_1_1Stats.md), which holds the calculated statistics for each metric (GAP and ACCESS\_TIME). 


    
## Public Functions Documentation




### function RiseSetStats [1/2]

_Default constructor for_ [_**RiseSetStats**_](structastrea_1_1trace_1_1RiseSetStats.md) _._
```C++
astrea::trace::RiseSetStats::RiseSetStats () = default
```




<hr>



### function RiseSetStats [2/2]

_Constructs a_ [_**RiseSetStats**_](structastrea_1_1trace_1_1RiseSetStats.md) _object from a_[_**RiseSetArray**_](classastrea_1_1trace_1_1RiseSetArray.md) _and a RiseSetMetric._
```C++
astrea::trace::RiseSetStats::RiseSetStats (
    const RiseSetArray & risesets
) 
```





**Parameters:**


* `risesets` The [**RiseSetArray**](classastrea_1_1trace_1_1RiseSetArray.md) containing the rise and set times to calculate statistics for. 



**Exception:**


* `std::runtime_error` If the RiseSetMetric is unrecognized. 




        

<hr>



### function at 

_Accesses the statistics for a given RiseSetMetric._ 
```C++
inline const auto & astrea::trace::RiseSetStats::at (
    const RiseSetMetric & metric
) const
```





**Parameters:**


* `metric` The RiseSetMetric to access statistics for. 



**Returns:**

const [**Stats&lt;Time&gt;**](structastrea_1_1trace_1_1Stats.md)& A reference to the [**Stats&lt;Time&gt;**](structastrea_1_1trace_1_1Stats.md) object containing the statistics for the given metric. 





        

<hr>



### function operator[] 

_Accesses the statistics for a given RiseSetMetric._ 
```C++
inline auto & astrea::trace::RiseSetStats::operator[] (
    const RiseSetMetric & metric
) 
```





**Parameters:**


* `metric` The RiseSetMetric to access statistics for. 



**Returns:**

[**Stats&lt;Time&gt;**](structastrea_1_1trace_1_1Stats.md)& A reference to the [**Stats&lt;Time&gt;**](structastrea_1_1trace_1_1Stats.md) object containing the statistics for the given metric. 





        

<hr>



### function to\_string\_vector 

_Converts the statistics to a vector of strings for output._ 
```C++
std::vector< std::string > astrea::trace::RiseSetStats::to_string_vector () const
```





**Returns:**

std::vector&lt;std::string&gt; A vector of strings representing the statistics for each metric. 





        

<hr>

------------------------------
The documentation for this class was generated from the following file `astrea/trace/trace/analysis/stats/RiseSetStats.hpp`

