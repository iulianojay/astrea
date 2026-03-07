

# Struct astrea::trace::HyperStats

**template &lt;class T&gt;**



[**ClassList**](annotated.md) **>** [**astrea**](namespaceastrea.md) **>** [**trace**](namespaceastrea_1_1trace.md) **>** [**HyperStats**](structastrea_1_1trace_1_1HyperStats.md)



_The_ [_**HyperStats**_](structastrea_1_1trace_1_1HyperStats.md) _struct represents statistics of statistics, allowing for the calculation of statistics on a vector of Stats&lt;T&gt;._[More...](#detailed-description)

* `#include <HyperStats.hpp>`





















## Public Attributes

| Type | Name |
| ---: | :--- |
|  [**Stats**](structastrea_1_1trace_1_1Stats.md)&lt; T &gt; | [**avg**](#variable-avg)  <br>_Statistics for the average values across the input Stats&lt;T&gt; vector._  |
|  [**Stats**](structastrea_1_1trace_1_1Stats.md)&lt; T &gt; | [**max**](#variable-max)  <br>_Statistics for the maximum values across the input Stats&lt;T&gt; vector._  |
|  [**Stats**](structastrea_1_1trace_1_1Stats.md)&lt; T &gt; | [**min**](#variable-min)  <br>_Statistics for the minimum values across the input Stats&lt;T&gt; vector._  |
|  std::vector&lt; [**Stats**](structastrea_1_1trace_1_1Stats.md)&lt; T &gt; &gt; | [**percentiles**](#variable-percentiles)  <br>_Statistics for each percentile across the input Stats&lt;T&gt; vector._  |
















## Public Functions

| Type | Name |
| ---: | :--- |
|   | [**HyperStats**](#function-hyperstats-12) () = default<br>_Default constructor for_ [_**HyperStats**_](structastrea_1_1trace_1_1HyperStats.md) _._ |
|   | [**HyperStats**](#function-hyperstats-22) (const std::vector&lt; [**Stats**](structastrea_1_1trace_1_1Stats.md)&lt; T &gt;&gt; & statsVec) <br>_Constructs a_ [_**HyperStats**_](structastrea_1_1trace_1_1HyperStats.md) _object from a vector of Stats&lt;T&gt;._ |
|  std::vector&lt; std::string &gt; | [**to\_string\_vector**](#function-to_string_vector) () const<br>_Converts the statistics of statistics to a vector of strings for output._  |


## Public Static Functions

| Type | Name |
| ---: | :--- |
|  constexpr std::size\_t | [**size**](#function-size) () <br> |


























## Detailed Description


It contains Stats&lt;T&gt; for the minimum, maximum, and average values across the input Stats&lt;T&gt; vector, as well as a vector of Stats&lt;T&gt; for each percentile. 


    
## Public Attributes Documentation




### variable avg 

_Statistics for the average values across the input Stats&lt;T&gt; vector._ 
```C++
Stats<T> astrea::trace::HyperStats< T >::avg;
```




<hr>



### variable max 

_Statistics for the maximum values across the input Stats&lt;T&gt; vector._ 
```C++
Stats<T> astrea::trace::HyperStats< T >::max;
```




<hr>



### variable min 

_Statistics for the minimum values across the input Stats&lt;T&gt; vector._ 
```C++
Stats<T> astrea::trace::HyperStats< T >::min;
```




<hr>



### variable percentiles 

_Statistics for each percentile across the input Stats&lt;T&gt; vector._ 
```C++
std::vector<Stats<T> > astrea::trace::HyperStats< T >::percentiles;
```




<hr>
## Public Functions Documentation




### function HyperStats [1/2]

_Default constructor for_ [_**HyperStats**_](structastrea_1_1trace_1_1HyperStats.md) _._
```C++
astrea::trace::HyperStats::HyperStats () = default
```




<hr>



### function HyperStats [2/2]

_Constructs a_ [_**HyperStats**_](structastrea_1_1trace_1_1HyperStats.md) _object from a vector of Stats&lt;T&gt;._
```C++
inline astrea::trace::HyperStats::HyperStats (
    const std::vector< Stats < T >> & statsVec
) 
```





**Parameters:**


* `statsVec` A vector of Stats&lt;T&gt; to calculate the statistics of. 



**Exception:**


* `std::runtime_error` If the input vector is empty. 




        

<hr>



### function to\_string\_vector 

_Converts the statistics of statistics to a vector of strings for output._ 
```C++
inline std::vector< std::string > astrea::trace::HyperStats::to_string_vector () const
```





**Returns:**

std::vector&lt;std::string&gt; A vector of strings representing the statistics of statistics. 





        

<hr>
## Public Static Functions Documentation




### function size 

```C++
static inline constexpr std::size_t astrea::trace::HyperStats::size () 
```




<hr>

------------------------------
The documentation for this class was generated from the following file `astrea/trace/trace/analysis/stats/HyperStats.hpp`

