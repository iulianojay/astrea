

# Struct astrea::trace::AccessStats



[**ClassList**](annotated.md) **>** [**astrea**](namespaceastrea.md) **>** [**trace**](namespaceastrea_1_1trace.md) **>** [**AccessStats**](structastrea_1_1trace_1_1AccessStats.md)



_The_ [_**AccessStats**_](structastrea_1_1trace_1_1AccessStats.md) _struct represents statistics for access times based on an_[_**AccessArray**_](classastrea_1_1trace_1_1AccessArray.md) _._[More...](#detailed-description)

* `#include <AccessStats.hpp>`





































## Public Functions

| Type | Name |
| ---: | :--- |
|   | [**AccessStats**](#function-accessstats-12) () = default<br>_Default constructor for_ [_**AccessStats**_](structastrea_1_1trace_1_1AccessStats.md) _._ |
|   | [**AccessStats**](#function-accessstats-22) (const [**AccessArray**](classastrea_1_1trace_1_1AccessArray.md) & accesses) <br>_Constructs an_ [_**AccessStats**_](structastrea_1_1trace_1_1AccessStats.md) _object from an_[_**AccessArray**_](classastrea_1_1trace_1_1AccessArray.md) _._ |
|  const auto & | [**get\_access\_metric**](#function-get_access_metric) (std::size\_t receiverId, const [**AccessMetric**](namespaceastrea_1_1trace.md#enum-accessmetric) & metric) const<br>_Accesses the access statistics for a given receiver ID and AccessMetric._  |
|  const auto & | [**get\_access\_metrics**](#function-get_access_metrics) () const<br>_Accesses the access statistics for all receiver IDs and AccessMetrics._  |
|  const auto & | [**get\_access\_statistics**](#function-get_access_statistics) (const [**AccessMetric**](namespaceastrea_1_1trace.md#enum-accessmetric) & metric) const<br>_Accesses the rise/set statistics for a given receiver ID._  |
|  const auto & | [**get\_hyper\_statistics**](#function-get_hyper_statistics-12) (const [**RiseSetMetric**](namespaceastrea_1_1trace.md#enum-risesetmetric) & metric) const<br>_Accesses the statistics for a given RiseSetMetric._  |
|  auto & | [**get\_hyper\_statistics**](#function-get_hyper_statistics-22) (const [**RiseSetMetric**](namespaceastrea_1_1trace.md#enum-risesetmetric) & metric) <br>_Accesses the statistics for a given RiseSetMetric._  |
|  const auto & | [**get\_riseset\_statistics**](#function-get_riseset_statistics-12) () const<br>_Accesses the rise/set statistics for all receivers._  |
|  const auto & | [**get\_riseset\_statistics**](#function-get_riseset_statistics-22) (std::size\_t receiverId) const<br>_Accesses the rise/set statistics for a given receiver ID._  |
|  std::vector&lt; std::string &gt; | [**to\_string\_vector**](#function-to_string_vector) () const<br>_Converts the statistics to a vector of strings for output._  |




























## Detailed Description


It contains maps for aggregate rise sets and their statistics for each receiver ID, as well as individual rise set statistics for each sender-receiver pair and hyper statistics for each receiver ID. 


    
## Public Functions Documentation




### function AccessStats [1/2]

_Default constructor for_ [_**AccessStats**_](structastrea_1_1trace_1_1AccessStats.md) _._
```C++
astrea::trace::AccessStats::AccessStats () = default
```




<hr>



### function AccessStats [2/2]

_Constructs an_ [_**AccessStats**_](structastrea_1_1trace_1_1AccessStats.md) _object from an_[_**AccessArray**_](classastrea_1_1trace_1_1AccessArray.md) _._
```C++
astrea::trace::AccessStats::AccessStats (
    const AccessArray & accesses
) 
```





**Parameters:**


* `accesses` The [**AccessArray**](classastrea_1_1trace_1_1AccessArray.md) containing the access times to calculate statistics for. 




        

<hr>



### function get\_access\_metric 

_Accesses the access statistics for a given receiver ID and AccessMetric._ 
```C++
inline const auto & astrea::trace::AccessStats::get_access_metric (
    std::size_t receiverId,
    const AccessMetric & metric
) const
```





**Parameters:**


* `receiverId` The ID of the receiver to access statistics for. 
* `metric` The AccessMetric to access statistics for. 



**Returns:**

const Time& A reference to the Time object containing the statistic for the given receiver ID and metric. 





        

<hr>



### function get\_access\_metrics 

_Accesses the access statistics for all receiver IDs and AccessMetrics._ 
```C++
inline const auto & astrea::trace::AccessStats::get_access_metrics () const
```





**Returns:**

const gtl::flat\_hash\_map&lt;std::size\_t, gtl::flat\_hash\_map&lt;AccessMetric, Time&gt;&gt;& A reference to the map containing the access metrics for all receiver IDs and AccessMetrics. 





        

<hr>



### function get\_access\_statistics 

_Accesses the rise/set statistics for a given receiver ID._ 
```C++
inline const auto & astrea::trace::AccessStats::get_access_statistics (
    const AccessMetric & metric
) const
```





**Parameters:**


* `receiverId` The ID of the receiver to access statistics for. 



**Returns:**

const [**RiseSetStats**](structastrea_1_1trace_1_1RiseSetStats.md)& A reference to the [**RiseSetStats**](structastrea_1_1trace_1_1RiseSetStats.md) object containing the statistics for the given receiver ID. 





        

<hr>



### function get\_hyper\_statistics [1/2]

_Accesses the statistics for a given RiseSetMetric._ 
```C++
inline const auto & astrea::trace::AccessStats::get_hyper_statistics (
    const RiseSetMetric & metric
) const
```





**Parameters:**


* `metric` The RiseSetMetric to access statistics for. 



**Returns:**

const [**Stats&lt;Time&gt;**](structastrea_1_1trace_1_1Stats.md)& A reference to the [**Stats&lt;Time&gt;**](structastrea_1_1trace_1_1Stats.md) object containing the statistics for the given metric. 





        

<hr>



### function get\_hyper\_statistics [2/2]

_Accesses the statistics for a given RiseSetMetric._ 
```C++
inline auto & astrea::trace::AccessStats::get_hyper_statistics (
    const RiseSetMetric & metric
) 
```





**Parameters:**


* `metric` The RiseSetMetric to access statistics for. 



**Returns:**

[**Stats&lt;Time&gt;**](structastrea_1_1trace_1_1Stats.md)& A reference to the [**Stats&lt;Time&gt;**](structastrea_1_1trace_1_1Stats.md) object containing the statistics for the given metric. 





        

<hr>



### function get\_riseset\_statistics [1/2]

_Accesses the rise/set statistics for all receivers._ 
```C++
inline const auto & astrea::trace::AccessStats::get_riseset_statistics () const
```





**Returns:**

const [**RiseSetStats**](structastrea_1_1trace_1_1RiseSetStats.md)& A reference to the [**RiseSetStats**](structastrea_1_1trace_1_1RiseSetStats.md) object containing the statistics for the given receiver ID. 





        

<hr>



### function get\_riseset\_statistics [2/2]

_Accesses the rise/set statistics for a given receiver ID._ 
```C++
inline const auto & astrea::trace::AccessStats::get_riseset_statistics (
    std::size_t receiverId
) const
```





**Parameters:**


* `receiverId` The ID of the receiver to access statistics for. 



**Returns:**

const [**RiseSetStats**](structastrea_1_1trace_1_1RiseSetStats.md)& A reference to the [**RiseSetStats**](structastrea_1_1trace_1_1RiseSetStats.md) object containing the statistics for the given receiver ID. 





        

<hr>



### function to\_string\_vector 

_Converts the statistics to a vector of strings for output._ 
```C++
std::vector< std::string > astrea::trace::AccessStats::to_string_vector () const
```





**Returns:**

std::vector&lt;std::string&gt; A vector of strings representing the statistics for each receiver ID and metric. 





        

<hr>

------------------------------
The documentation for this class was generated from the following file `astrea/trace/trace/analysis/stats/AccessStats.hpp`

