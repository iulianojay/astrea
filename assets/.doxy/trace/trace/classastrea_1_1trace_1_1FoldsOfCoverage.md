

# Class astrea::trace::FoldsOfCoverage



[**ClassList**](annotated.md) **>** [**astrea**](namespaceastrea.md) **>** [**trace**](namespaceastrea_1_1trace.md) **>** [**FoldsOfCoverage**](classastrea_1_1trace_1_1FoldsOfCoverage.md)



_The_ [_**FoldsOfCoverage**_](classastrea_1_1trace_1_1FoldsOfCoverage.md) _class represents the folds of coverage (simultaneous accesses) for each receiver ID over time._[More...](#detailed-description)

* `#include <FoldsOfCoverage.hpp>`

















## Public Types

| Type | Name |
| ---: | :--- |
| typedef gtl::flat\_hash\_map&lt; std::size\_t, std::vector&lt; double &gt; &gt;::const\_iterator | [**const\_iterator**](#typedef-const_iterator)  <br>_Constant iterator type for the_ [_**FoldsOfCoverage**_](classastrea_1_1trace_1_1FoldsOfCoverage.md) _._ |
| typedef gtl::flat\_hash\_map&lt; std::size\_t, std::vector&lt; double &gt; &gt;::iterator | [**iterator**](#typedef-iterator)  <br>_Iterator type for the_ [_**FoldsOfCoverage**_](classastrea_1_1trace_1_1FoldsOfCoverage.md) _._ |




















## Public Functions

| Type | Name |
| ---: | :--- |
|   | [**FoldsOfCoverage**](#function-foldsofcoverage-12) () = default<br>_Default constructor for_ [_**FoldsOfCoverage**_](classastrea_1_1trace_1_1FoldsOfCoverage.md) _._ |
|   | [**FoldsOfCoverage**](#function-foldsofcoverage-22) (const [**AccessArray**](classastrea_1_1trace_1_1AccessArray.md) & access, const Time & resolution, const Time & end) <br>_Constructs a_ [_**FoldsOfCoverage**_](classastrea_1_1trace_1_1FoldsOfCoverage.md) _object from an_[_**AccessArray**_](classastrea_1_1trace_1_1AccessArray.md) _and time parameters._ |
|  [**iterator**](classastrea_1_1trace_1_1FoldsOfCoverage.md#typedef-iterator) | [**begin**](#function-begin-12) () <br>_Returns an iterator to the beginning of the_ [_**FoldsOfCoverage**_](classastrea_1_1trace_1_1FoldsOfCoverage.md) _._ |
|  [**const\_iterator**](classastrea_1_1trace_1_1FoldsOfCoverage.md#typedef-const_iterator) | [**begin**](#function-begin-22) () const<br>_Returns a constant iterator to the beginning of the_ [_**FoldsOfCoverage**_](classastrea_1_1trace_1_1FoldsOfCoverage.md) _._ |
|  [**const\_iterator**](classastrea_1_1trace_1_1FoldsOfCoverage.md#typedef-const_iterator) | [**cbegin**](#function-cbegin) () const<br>_Returns a constant iterator to the beginning of the_ [_**FoldsOfCoverage**_](classastrea_1_1trace_1_1FoldsOfCoverage.md) _._ |
|  [**const\_iterator**](classastrea_1_1trace_1_1FoldsOfCoverage.md#typedef-const_iterator) | [**cend**](#function-cend) () const<br>_Returns a constant iterator to the end of the_ [_**FoldsOfCoverage**_](classastrea_1_1trace_1_1FoldsOfCoverage.md) _._ |
|  [**iterator**](classastrea_1_1trace_1_1FoldsOfCoverage.md#typedef-iterator) | [**end**](#function-end-12) () <br>_Returns an iterator to the end of the_ [_**FoldsOfCoverage**_](classastrea_1_1trace_1_1FoldsOfCoverage.md) _._ |
|  [**const\_iterator**](classastrea_1_1trace_1_1FoldsOfCoverage.md#typedef-const_iterator) | [**end**](#function-end-22) () const<br>_Returns a constant iterator to the end of the_ [_**FoldsOfCoverage**_](classastrea_1_1trace_1_1FoldsOfCoverage.md) _._ |
|  const [**Stats**](structastrea_1_1trace_1_1Stats.md)&lt; double &gt; & | [**get\_stats**](#function-get_stats) (const std::size\_t & id) const<br>_Returns the statistics for a given ID._  |




























## Detailed Description


It calculates the number of accesses (folds) for each receiver ID at each time point based on the provided [**AccessArray**](classastrea_1_1trace_1_1AccessArray.md) and time parameters. It also computes statistics for the folds of coverage for each receiver ID. 


    
## Public Types Documentation




### typedef const\_iterator 

_Constant iterator type for the_ [_**FoldsOfCoverage**_](classastrea_1_1trace_1_1FoldsOfCoverage.md) _._
```C++
using astrea::trace::FoldsOfCoverage::const_iterator =  gtl::flat_hash_map<std::size_t, std::vector<double> >::const_iterator;
```




<hr>



### typedef iterator 

_Iterator type for the_ [_**FoldsOfCoverage**_](classastrea_1_1trace_1_1FoldsOfCoverage.md) _._
```C++
using astrea::trace::FoldsOfCoverage::iterator =  gtl::flat_hash_map<std::size_t, std::vector<double> >::iterator;
```




<hr>
## Public Functions Documentation




### function FoldsOfCoverage [1/2]

_Default constructor for_ [_**FoldsOfCoverage**_](classastrea_1_1trace_1_1FoldsOfCoverage.md) _._
```C++
astrea::trace::FoldsOfCoverage::FoldsOfCoverage () = default
```




<hr>



### function FoldsOfCoverage [2/2]

_Constructs a_ [_**FoldsOfCoverage**_](classastrea_1_1trace_1_1FoldsOfCoverage.md) _object from an_[_**AccessArray**_](classastrea_1_1trace_1_1AccessArray.md) _and time parameters._
```C++
astrea::trace::FoldsOfCoverage::FoldsOfCoverage (
    const AccessArray & access,
    const Time & resolution,
    const Time & end
) 
```





**Parameters:**


* `access` The [**AccessArray**](classastrea_1_1trace_1_1AccessArray.md) containing the rise sets for each sender-receiver pair. 
* `resolution` The time resolution for calculating folds of coverage. 
* `end` The end time for calculating folds of coverage. 




        

<hr>



### function begin [1/2]

_Returns an iterator to the beginning of the_ [_**FoldsOfCoverage**_](classastrea_1_1trace_1_1FoldsOfCoverage.md) _._
```C++
inline iterator astrea::trace::FoldsOfCoverage::begin () 
```





**Returns:**

iterator An iterator to the beginning of the [**FoldsOfCoverage**](classastrea_1_1trace_1_1FoldsOfCoverage.md). 





        

<hr>



### function begin [2/2]

_Returns a constant iterator to the beginning of the_ [_**FoldsOfCoverage**_](classastrea_1_1trace_1_1FoldsOfCoverage.md) _._
```C++
inline const_iterator astrea::trace::FoldsOfCoverage::begin () const
```





**Returns:**

const\_iterator A constant iterator to the beginning of the [**FoldsOfCoverage**](classastrea_1_1trace_1_1FoldsOfCoverage.md). 





        

<hr>



### function cbegin 

_Returns a constant iterator to the beginning of the_ [_**FoldsOfCoverage**_](classastrea_1_1trace_1_1FoldsOfCoverage.md) _._
```C++
inline const_iterator astrea::trace::FoldsOfCoverage::cbegin () const
```





**Returns:**

const\_iterator A constant iterator to the beginning of the [**FoldsOfCoverage**](classastrea_1_1trace_1_1FoldsOfCoverage.md). 





        

<hr>



### function cend 

_Returns a constant iterator to the end of the_ [_**FoldsOfCoverage**_](classastrea_1_1trace_1_1FoldsOfCoverage.md) _._
```C++
inline const_iterator astrea::trace::FoldsOfCoverage::cend () const
```





**Returns:**

const\_iterator A constant iterator to the end of the [**FoldsOfCoverage**](classastrea_1_1trace_1_1FoldsOfCoverage.md). 





        

<hr>



### function end [1/2]

_Returns an iterator to the end of the_ [_**FoldsOfCoverage**_](classastrea_1_1trace_1_1FoldsOfCoverage.md) _._
```C++
inline iterator astrea::trace::FoldsOfCoverage::end () 
```





**Returns:**

iterator An iterator to the end of the [**FoldsOfCoverage**](classastrea_1_1trace_1_1FoldsOfCoverage.md). 





        

<hr>



### function end [2/2]

_Returns a constant iterator to the end of the_ [_**FoldsOfCoverage**_](classastrea_1_1trace_1_1FoldsOfCoverage.md) _._
```C++
inline const_iterator astrea::trace::FoldsOfCoverage::end () const
```





**Returns:**

const\_iterator A constant iterator to the end of the [**FoldsOfCoverage**](classastrea_1_1trace_1_1FoldsOfCoverage.md). 





        

<hr>



### function get\_stats 

_Returns the statistics for a given ID._ 
```C++
inline const Stats < double > & astrea::trace::FoldsOfCoverage::get_stats (
    const std::size_t & id
) const
```





**Parameters:**


* `id` The ID to get the statistics for. 



**Returns:**

Stats&lt;std::size\_t&gt; The statistics for the given ID. 





        

<hr>

------------------------------
The documentation for this class was generated from the following file `astrea/trace/trace/analysis/stats/FoldsOfCoverage.hpp`

