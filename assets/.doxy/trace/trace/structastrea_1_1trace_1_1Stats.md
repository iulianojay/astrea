

# Struct astrea::trace::Stats

**template &lt;class T&gt;**



[**ClassList**](annotated.md) **>** [**astrea**](namespaceastrea.md) **>** [**trace**](namespaceastrea_1_1trace.md) **>** [**Stats**](structastrea_1_1trace_1_1Stats.md)



_The_ [_**Stats**_](structastrea_1_1trace_1_1Stats.md) _struct represents basic statistics (min, max, average, and percentiles) for a vector of values of type T._

* `#include <Stats.hpp>`





















## Public Attributes

| Type | Name |
| ---: | :--- |
|  T | [**avg**](#variable-avg)  <br>_The average value in the vector._  |
|  T | [**max**](#variable-max)  <br>_The maximum value in the vector._  |
|  T | [**min**](#variable-min)  <br>_The minimum value in the vector._  |
|  std::vector&lt; T &gt; | [**percentiles**](#variable-percentiles)  <br>_A vector of percentiles corresponding to the DEFAULT\_PERCENTILES._  |
















## Public Functions

| Type | Name |
| ---: | :--- |
|   | [**Stats**](#function-stats-14) () = default<br>_Default constructor for_ [_**Stats**_](structastrea_1_1trace_1_1Stats.md) _._ |
|   | [**Stats**](#function-stats-24) (const [**RiseSetArray**](classastrea_1_1trace_1_1RiseSetArray.md) & risesets, const [**RiseSetMetric**](namespaceastrea_1_1trace.md#enum-risesetmetric) & metric) = delete<br>_Constructs a_ [_**Stats**_](structastrea_1_1trace_1_1Stats.md) _object from a vector of values of type T. Deleted for non-Time types._ |
|   | [**Stats**](#function-stats-34) (std::vector&lt; T &gt; values) <br>_Constructs a_ [_**Stats**_](structastrea_1_1trace_1_1Stats.md) _object from a vector of values of type T._ |
|   | [**Stats**](#function-stats-44) (const [**RiseSetArray**](classastrea_1_1trace_1_1RiseSetArray.md) & risesets, const [**RiseSetMetric**](namespaceastrea_1_1trace.md#enum-risesetmetric) & metric) <br>_Specialization of the_ [_**Stats**_](structastrea_1_1trace_1_1Stats.md) _struct for Time type, which can be constructed from a_[_**RiseSetArray**_](classastrea_1_1trace_1_1RiseSetArray.md) _and a RiseSetMetric._ |
|  std::vector&lt; std::string &gt; | [**to\_string\_vector**](#function-to_string_vector-12) () const<br>_Converts the statistics to a vector of strings for output._  |
|  std::vector&lt; std::string &gt; | [**to\_string\_vector**](#function-to_string_vector-22) () const<br>_Specialization of the to\_string\_vector method for Time type, which formats the Time values as strings._  |


## Public Static Functions

| Type | Name |
| ---: | :--- |
|  constexpr std::size\_t | [**size**](#function-size) () <br> |


























## Public Attributes Documentation




### variable avg 

_The average value in the vector._ 
```C++
T astrea::trace::Stats< T >::avg;
```




<hr>



### variable max 

_The maximum value in the vector._ 
```C++
T astrea::trace::Stats< T >::max;
```




<hr>



### variable min 

_The minimum value in the vector._ 
```C++
T astrea::trace::Stats< T >::min;
```




<hr>



### variable percentiles 

_A vector of percentiles corresponding to the DEFAULT\_PERCENTILES._ 
```C++
std::vector<T> astrea::trace::Stats< T >::percentiles;
```




<hr>
## Public Functions Documentation




### function Stats [1/4]

_Default constructor for_ [_**Stats**_](structastrea_1_1trace_1_1Stats.md) _._
```C++
astrea::trace::Stats::Stats () = default
```




<hr>



### function Stats [2/4]

_Constructs a_ [_**Stats**_](structastrea_1_1trace_1_1Stats.md) _object from a vector of values of type T. Deleted for non-Time types._
```C++
astrea::trace::Stats::Stats (
    const RiseSetArray & risesets,
    const RiseSetMetric & metric
) = delete
```





**Parameters:**


* `values` A vector of values to calculate statistics for. 



**Exception:**


* `std::runtime_error` If the input vector is empty. 




        

<hr>



### function Stats [3/4]

_Constructs a_ [_**Stats**_](structastrea_1_1trace_1_1Stats.md) _object from a vector of values of type T._
```C++
inline astrea::trace::Stats::Stats (
    std::vector< T > values
) 
```





**Parameters:**


* `values` A vector of values to calculate statistics for. 



**Exception:**


* `std::runtime_error` If the input vector is empty. 




        

<hr>



### function Stats [4/4]

_Specialization of the_ [_**Stats**_](structastrea_1_1trace_1_1Stats.md) _struct for Time type, which can be constructed from a_[_**RiseSetArray**_](classastrea_1_1trace_1_1RiseSetArray.md) _and a RiseSetMetric._
```C++
inline astrea::trace::Stats::Stats (
    const RiseSetArray & risesets,
    const RiseSetMetric & metric
) 
```





**Template parameters:**


* `T` The type of the statistics, specialized for Time. 



**Parameters:**


* `risesets` The [**RiseSetArray**](classastrea_1_1trace_1_1RiseSetArray.md) containing the rise and set times to calculate statistics for. 
* `metric` The RiseSetMetric indicating which metric to calculate statistics for (ACCESS\_TIME or GAP). 



**Exception:**


* `std::runtime_error` If the RiseSetMetric is unrecognized. 




        

<hr>



### function to\_string\_vector [1/2]

_Converts the statistics to a vector of strings for output._ 
```C++
inline std::vector< std::string > astrea::trace::Stats::to_string_vector () const
```





**Returns:**

std::vector&lt;std::string&gt; A vector of strings representing the statistics. 





        

<hr>



### function to\_string\_vector [2/2]

_Specialization of the to\_string\_vector method for Time type, which formats the Time values as strings._ 
```C++
inline std::vector< std::string > astrea::trace::Stats::to_string_vector () const
```





**Returns:**

std::vector&lt;std::string&gt; A vector of strings representing the statistics, formatted as time strings. 





        

<hr>
## Public Static Functions Documentation




### function size 

```C++
static inline constexpr std::size_t astrea::trace::Stats::size () 
```




<hr>

------------------------------
The documentation for this class was generated from the following file `astrea/trace/trace/analysis/stats/Stats.hpp`

