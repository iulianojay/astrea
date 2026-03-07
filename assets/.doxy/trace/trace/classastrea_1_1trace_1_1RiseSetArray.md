

# Class astrea::trace::RiseSetArray



[**ClassList**](annotated.md) **>** [**astrea**](namespaceastrea.md) **>** [**trace**](namespaceastrea_1_1trace.md) **>** [**RiseSetArray**](classastrea_1_1trace_1_1RiseSetArray.md)



_Represents an array of rise and set times._ [More...](#detailed-description)

* `#include <RiseSetArray.hpp>`

















## Public Types

| Type | Name |
| ---: | :--- |
| typedef std::vector&lt; Time &gt;::[**const\_iterator**](classastrea_1_1trace_1_1RiseSetArray.md#typedef-const_iterator) | [**const\_iterator**](#typedef-const_iterator)  <br>_Constant iterator type for the_ [_**RiseSetArray**_](classastrea_1_1trace_1_1RiseSetArray.md) _._ |
| typedef std::vector&lt; Time &gt;::[**iterator**](classastrea_1_1trace_1_1RiseSetArray.md#typedef-iterator) | [**iterator**](#typedef-iterator)  <br>_Iterator type for the_ [_**RiseSetArray**_](classastrea_1_1trace_1_1RiseSetArray.md) _._ |




















## Public Functions

| Type | Name |
| ---: | :--- |
|   | [**RiseSetArray**](#function-risesetarray-14) () = default<br>_Default constructor for_ [_**RiseSetArray**_](classastrea_1_1trace_1_1RiseSetArray.md) _._ |
|   | [**RiseSetArray**](#function-risesetarray-24) (const std::vector&lt; Time &gt; & risesets) <br>_Constructs a_ [_**RiseSetArray**_](classastrea_1_1trace_1_1RiseSetArray.md) _from a vector of Time objects._ |
|   | [**RiseSetArray**](#function-risesetarray-34) (const [**RiseSetArray**](classastrea_1_1trace_1_1RiseSetArray.md) & other) <br>_Copy constructor for_ [_**RiseSetArray**_](classastrea_1_1trace_1_1RiseSetArray.md) _._ |
|   | [**RiseSetArray**](#function-risesetarray-44) ([**RiseSetArray**](classastrea_1_1trace_1_1RiseSetArray.md) && other) noexcept<br>_Move constructor for_ [_**RiseSetArray**_](classastrea_1_1trace_1_1RiseSetArray.md) _._ |
|  Time | [**access\_time**](#function-access_time) (const [**StatType**](namespaceastrea_1_1trace.md#enum-stattype) & stat=StatType::AVG, const Unitless percentile=0.5) const<br>_Calculates the access time based on rise and set times._  |
|  void | [**append**](#function-append) (const Time & rise, const Time & set) <br>_Appends a rise and set time to the array._  |
|  Time | [**average\_daily\_vis\_time**](#function-average_daily_vis_time) () const<br>_Calculates the average daily visibility time based on the rise and set times._  |
|  [**iterator**](classastrea_1_1trace_1_1RiseSetArray.md#typedef-iterator) | [**begin**](#function-begin-12) () <br>_Returns an iterator to the beginning of the_ [_**RiseSetArray**_](classastrea_1_1trace_1_1RiseSetArray.md) _._ |
|  [**const\_iterator**](classastrea_1_1trace_1_1RiseSetArray.md#typedef-const_iterator) | [**begin**](#function-begin-22) () const<br>_Returns a constant iterator to the beginning of the_ [_**RiseSetArray**_](classastrea_1_1trace_1_1RiseSetArray.md) _._ |
|  [**const\_iterator**](classastrea_1_1trace_1_1RiseSetArray.md#typedef-const_iterator) | [**cbegin**](#function-cbegin) () const<br>_Returns a constant iterator to the beginning of the_ [_**RiseSetArray**_](classastrea_1_1trace_1_1RiseSetArray.md) _._ |
|  [**const\_iterator**](classastrea_1_1trace_1_1RiseSetArray.md#typedef-const_iterator) | [**cend**](#function-cend) () const<br>_Returns a constant iterator to the end of the_ [_**RiseSetArray**_](classastrea_1_1trace_1_1RiseSetArray.md) _._ |
|  [**iterator**](classastrea_1_1trace_1_1RiseSetArray.md#typedef-iterator) | [**end**](#function-end-12) () <br>_Returns an iterator to the end of the_ [_**RiseSetArray**_](classastrea_1_1trace_1_1RiseSetArray.md) _._ |
|  [**const\_iterator**](classastrea_1_1trace_1_1RiseSetArray.md#typedef-const_iterator) | [**end**](#function-end-22) () const<br>_Returns a constant iterator to the end of the_ [_**RiseSetArray**_](classastrea_1_1trace_1_1RiseSetArray.md) _._ |
|  Time | [**gap**](#function-gap) (const [**StatType**](namespaceastrea_1_1trace.md#enum-stattype) & stat=StatType::AVG, const Unitless percentile=0.5) const<br>_Calculates the gap between rise and set times._  |
|  std::vector&lt; Time &gt; | [**get\_access\_times**](#function-get_access_times) () const<br>_Get a vector of access durations for this rise-set array._  |
|  std::vector&lt; Time &gt; | [**get\_gap\_times**](#function-get_gap_times) () const<br>_Get a vector of gap durations for this rise-set array._  |
|  bool | [**has\_access**](#function-has_access) (const Time & time) const<br>_Checks if the given time occurs during an access window._  |
|  void | [**insert**](#function-insert) (const Time & rise, const Time & set) <br>_Inserts a rise and set time at the end of the array._  |
|  Time | [**mean\_time\_to\_access**](#function-mean_time_to_access) () const<br>_Calculates the mean time to access (MTTA) for this_ [_**RiseSetArray**_](classastrea_1_1trace_1_1RiseSetArray.md) _._ |
|  [**RiseSetArray**](classastrea_1_1trace_1_1RiseSetArray.md) | [**operator&**](#function-operator) (const [**RiseSetArray**](classastrea_1_1trace_1_1RiseSetArray.md) & other) const<br>_Intersection operator to find common rise/set pairs between two_ [_**RiseSetArray**_](classastrea_1_1trace_1_1RiseSetArray.md) _objects._ |
|  [**RiseSetArray**](classastrea_1_1trace_1_1RiseSetArray.md) & | [**operator&=**](#function-operator_1) (const [**RiseSetArray**](classastrea_1_1trace_1_1RiseSetArray.md) & other) <br>_In-place intersection operator to find common rise/set pairs between two_ [_**RiseSetArray**_](classastrea_1_1trace_1_1RiseSetArray.md) _objects._ |
|  [**RiseSetArray**](classastrea_1_1trace_1_1RiseSetArray.md) | [**operator-**](#function-operator-) (const [**RiseSetArray**](classastrea_1_1trace_1_1RiseSetArray.md) & other) const<br>_Difference operator to subtract one_ [_**RiseSetArray**_](classastrea_1_1trace_1_1RiseSetArray.md) _from another._ |
|  [**RiseSetArray**](classastrea_1_1trace_1_1RiseSetArray.md) & | [**operator-=**](#function-operator-_1) (const [**RiseSetArray**](classastrea_1_1trace_1_1RiseSetArray.md) & other) <br>_In-place difference operator to subtract one_ [_**RiseSetArray**_](classastrea_1_1trace_1_1RiseSetArray.md) _from another._ |
|  [**RiseSetArray**](classastrea_1_1trace_1_1RiseSetArray.md) & | [**operator=**](#function-operator_2) ([**RiseSetArray**](classastrea_1_1trace_1_1RiseSetArray.md) && other) noexcept<br>_Move assignment operator for_ [_**RiseSetArray**_](classastrea_1_1trace_1_1RiseSetArray.md) _._ |
|  [**RiseSetArray**](classastrea_1_1trace_1_1RiseSetArray.md) & | [**operator=**](#function-operator_3) (const [**RiseSetArray**](classastrea_1_1trace_1_1RiseSetArray.md) & other) <br>_Copy assignment operator for_ [_**RiseSetArray**_](classastrea_1_1trace_1_1RiseSetArray.md) _._ |
|  bool | [**operator==**](#function-operator_4) (const [**RiseSetArray**](classastrea_1_1trace_1_1RiseSetArray.md) & other) const<br>_Equality operator to compare two_ [_**RiseSetArray**_](classastrea_1_1trace_1_1RiseSetArray.md) _objects._ |
|  Time & | [**operator[]**](#function-operator_5) (const std::size\_t & ind) <br>_Returns a reference to the rise/set pair at the specified index._  |
|  const Time & | [**operator[]**](#function-operator_6) (const std::size\_t & ind) const<br>_Returns a const reference to the rise/set pair at the specified index._  |
|  [**RiseSetArray**](classastrea_1_1trace_1_1RiseSetArray.md) | [**operator\|**](#function-operator_7) (const [**RiseSetArray**](classastrea_1_1trace_1_1RiseSetArray.md) & other) const<br>_Union operator to combine two_ [_**RiseSetArray**_](classastrea_1_1trace_1_1RiseSetArray.md) _objects._ |
|  [**RiseSetArray**](classastrea_1_1trace_1_1RiseSetArray.md) & | [**operator\|=**](#function-operator_8) (const [**RiseSetArray**](classastrea_1_1trace_1_1RiseSetArray.md) & other) <br>_In-place union operator to combine two_ [_**RiseSetArray**_](classastrea_1_1trace_1_1RiseSetArray.md) _objects._ |
|  void | [**prepend**](#function-prepend) (const Time & rise, const Time & set) <br>_Prepends a rise and set time to the array._  |
|  std::size\_t | [**size**](#function-size) () const<br>_Returns the number of rise/set pairs in the array._  |
|  std::vector&lt; std::string &gt; | [**to\_string\_vector**](#function-to_string_vector) () const<br>_Converts the_ [_**RiseSetArray**_](classastrea_1_1trace_1_1RiseSetArray.md) _to a vector of formatted strings._ |
|   | [**~RiseSetArray**](#function-risesetarray) () = default<br>_Destructor for_ [_**RiseSetArray**_](classastrea_1_1trace_1_1RiseSetArray.md) _._ |




























## Detailed Description


This class provides functionality to manage and manipulate an array of rise and set times, including operations like addition, subtraction, intersection, and union of rise/set pairs. 


    
## Public Types Documentation




### typedef const\_iterator 

_Constant iterator type for the_ [_**RiseSetArray**_](classastrea_1_1trace_1_1RiseSetArray.md) _._
```C++
using astrea::trace::RiseSetArray::const_iterator =  std::vector<Time>::const_iterator;
```




<hr>



### typedef iterator 

_Iterator type for the_ [_**RiseSetArray**_](classastrea_1_1trace_1_1RiseSetArray.md) _._
```C++
using astrea::trace::RiseSetArray::iterator =  std::vector<Time>::iterator;
```




<hr>
## Public Functions Documentation




### function RiseSetArray [1/4]

_Default constructor for_ [_**RiseSetArray**_](classastrea_1_1trace_1_1RiseSetArray.md) _._
```C++
astrea::trace::RiseSetArray::RiseSetArray () = default
```



Initializes an empty [**RiseSetArray**](classastrea_1_1trace_1_1RiseSetArray.md). 


        

<hr>



### function RiseSetArray [2/4]

_Constructs a_ [_**RiseSetArray**_](classastrea_1_1trace_1_1RiseSetArray.md) _from a vector of Time objects._
```C++
astrea::trace::RiseSetArray::RiseSetArray (
    const std::vector< Time > & risesets
) 
```





**Parameters:**


* `risesets` A vector of Time objects representing rise and set times. 




        

<hr>



### function RiseSetArray [3/4]

_Copy constructor for_ [_**RiseSetArray**_](classastrea_1_1trace_1_1RiseSetArray.md) _._
```C++
astrea::trace::RiseSetArray::RiseSetArray (
    const RiseSetArray & other
) 
```





**Parameters:**


* `other` The other [**RiseSetArray**](classastrea_1_1trace_1_1RiseSetArray.md) to copy from. 




        

<hr>



### function RiseSetArray [4/4]

_Move constructor for_ [_**RiseSetArray**_](classastrea_1_1trace_1_1RiseSetArray.md) _._
```C++
astrea::trace::RiseSetArray::RiseSetArray (
    RiseSetArray && other
) noexcept
```





**Parameters:**


* `other` The other [**RiseSetArray**](classastrea_1_1trace_1_1RiseSetArray.md) to move from. 




        

<hr>



### function access\_time 

_Calculates the access time based on rise and set times._ 
```C++
Time astrea::trace::RiseSetArray::access_time (
    const StatType & stat=StatType::AVG,
    const Unitless percentile=0.5
) const
```





**Parameters:**


* `stat` The statistical measure to calculate (MIN, MEAN, MAX, PCT). 
* `percentile` The percentile to calculate if stat is PCT (between 0 and 1). 



**Returns:**

Time The calculated access time based on the specified statistic. 





        

<hr>



### function append 

_Appends a rise and set time to the array._ 
```C++
void astrea::trace::RiseSetArray::append (
    const Time & rise,
    const Time & set
) 
```





**Parameters:**


* `rise` The rise time to append. 
* `set` The set time to append. 



**Exception:**


* `std::invalid_argument` If the rise time is not before the set time. 
* `std::invalid_argument` If the rise and set times are not in chronological order. 
* `std::invalid_argument` If the rise and set times are not valid. 




        

<hr>



### function average\_daily\_vis\_time 

_Calculates the average daily visibility time based on the rise and set times._ 
```C++
Time astrea::trace::RiseSetArray::average_daily_vis_time () const
```





**Returns:**

Time The calculated average daily visibility time. 





        

<hr>



### function begin [1/2]

_Returns an iterator to the beginning of the_ [_**RiseSetArray**_](classastrea_1_1trace_1_1RiseSetArray.md) _._
```C++
iterator astrea::trace::RiseSetArray::begin () 
```





**Returns:**

iterator An iterator to the beginning of the [**RiseSetArray**](classastrea_1_1trace_1_1RiseSetArray.md). 





        

<hr>



### function begin [2/2]

_Returns a constant iterator to the beginning of the_ [_**RiseSetArray**_](classastrea_1_1trace_1_1RiseSetArray.md) _._
```C++
const_iterator astrea::trace::RiseSetArray::begin () const
```





**Returns:**

const\_iterator A constant iterator to the beginning of the [**RiseSetArray**](classastrea_1_1trace_1_1RiseSetArray.md). 





        

<hr>



### function cbegin 

_Returns a constant iterator to the beginning of the_ [_**RiseSetArray**_](classastrea_1_1trace_1_1RiseSetArray.md) _._
```C++
const_iterator astrea::trace::RiseSetArray::cbegin () const
```





**Returns:**

const\_iterator A constant iterator to the beginning of the [**RiseSetArray**](classastrea_1_1trace_1_1RiseSetArray.md). 





        

<hr>



### function cend 

_Returns a constant iterator to the end of the_ [_**RiseSetArray**_](classastrea_1_1trace_1_1RiseSetArray.md) _._
```C++
const_iterator astrea::trace::RiseSetArray::cend () const
```





**Returns:**

const\_iterator A constant iterator to the end of the [**RiseSetArray**](classastrea_1_1trace_1_1RiseSetArray.md). 





        

<hr>



### function end [1/2]

_Returns an iterator to the end of the_ [_**RiseSetArray**_](classastrea_1_1trace_1_1RiseSetArray.md) _._
```C++
iterator astrea::trace::RiseSetArray::end () 
```





**Returns:**

iterator An iterator to the end of the [**RiseSetArray**](classastrea_1_1trace_1_1RiseSetArray.md). 





        

<hr>



### function end [2/2]

_Returns a constant iterator to the end of the_ [_**RiseSetArray**_](classastrea_1_1trace_1_1RiseSetArray.md) _._
```C++
const_iterator astrea::trace::RiseSetArray::end () const
```





**Returns:**

const\_iterator A constant iterator to the end of the [**RiseSetArray**](classastrea_1_1trace_1_1RiseSetArray.md). 





        

<hr>



### function gap 

_Calculates the gap between rise and set times._ 
```C++
Time astrea::trace::RiseSetArray::gap (
    const StatType & stat=StatType::AVG,
    const Unitless percentile=0.5
) const
```





**Parameters:**


* `stat` The statistical measure to calculate (MIN, MEAN, MAX, PCT). 
* `percentile` The percentile to calculate if stat is PCT (between 0 and 1). 



**Returns:**

Time The calculated gap based on the specified statistic. 





        

<hr>



### function get\_access\_times 

_Get a vector of access durations for this rise-set array._ 
```C++
std::vector< Time > astrea::trace::RiseSetArray::get_access_times () const
```





**Returns:**

std::vector&lt;Time&gt; Vector of access durations in the order that they appear 





        

<hr>



### function get\_gap\_times 

_Get a vector of gap durations for this rise-set array._ 
```C++
std::vector< Time > astrea::trace::RiseSetArray::get_gap_times () const
```





**Returns:**

std::vector&lt;Time&gt; Vector of gap durations in the order that they appear 





        

<hr>



### function has\_access 

_Checks if the given time occurs during an access window._ 
```C++
bool astrea::trace::RiseSetArray::has_access (
    const Time & time
) const
```





**Parameters:**


* `time` Time to check for access 



**Returns:**

true if time occurs during an access windows 




**Returns:**

false if time occurs during a gap 





        

<hr>



### function insert 

_Inserts a rise and set time at the end of the array._ 
```C++
void astrea::trace::RiseSetArray::insert (
    const Time & rise,
    const Time & set
) 
```





**Parameters:**


* `rise` The rise time to insert. 
* `set` The set time to insert. 



**Exception:**


* `std::invalid_argument` If the rise time is not before the set time. 
* `std::invalid_argument` If the rise and set times are not in chronological order. 
* `std::invalid_argument` If the rise and set times are not valid. 




        

<hr>



### function mean\_time\_to\_access 

_Calculates the mean time to access (MTTA) for this_ [_**RiseSetArray**_](classastrea_1_1trace_1_1RiseSetArray.md) _._
```C++
Time astrea::trace::RiseSetArray::mean_time_to_access () const
```





**Returns:**

Time The calculated mean time to access based on the rise and set times.




**Note:**

access: \|&lt;gap--&gt;\|&lt;access--&gt;\|&lt;-gap-&gt;\|&lt;access--&gt;\|... \| \| \| \| \|... tta: \|\ \| \| \| \|... \|+\ \| \| \| \|... \|++\ \| \|\ \| \|... \|+++\ \| \|+\ \| \|... \|++++\ \| \|++\ \| \|... \|+++++\ \| \|+++\ \| \|... \|++++++\ \| \|++++\ \| \|... \|+++++++\ \| \|+++++\ \| \|... \|++++++++\|\_\_\_\_\_\_\_\_\_\_\_\_\|++++++\|\_\_\_\_\_\_\_\_\_\_\_\_\|...


MMTA is the mean time to access, or the mean height of the shaded regions MMTA = 0.5 \* sqrt(gap0^2 + gap1^2 + ...) 


        

<hr>



### function operator& 

_Intersection operator to find common rise/set pairs between two_ [_**RiseSetArray**_](classastrea_1_1trace_1_1RiseSetArray.md) _objects._
```C++
RiseSetArray astrea::trace::RiseSetArray::operator& (
    const RiseSetArray & other
) const
```





**Parameters:**


* `other` The other [**RiseSetArray**](classastrea_1_1trace_1_1RiseSetArray.md) to intersect with this one. 



**Returns:**

[**RiseSetArray**](classastrea_1_1trace_1_1RiseSetArray.md) A new [**RiseSetArray**](classastrea_1_1trace_1_1RiseSetArray.md) containing the intersection of the two. 





        

<hr>



### function operator&= 

_In-place intersection operator to find common rise/set pairs between two_ [_**RiseSetArray**_](classastrea_1_1trace_1_1RiseSetArray.md) _objects._
```C++
RiseSetArray & astrea::trace::RiseSetArray::operator&= (
    const RiseSetArray & other
) 
```





**Parameters:**


* `other` The other [**RiseSetArray**](classastrea_1_1trace_1_1RiseSetArray.md) to intersect with this one. 



**Returns:**

[**RiseSetArray**](classastrea_1_1trace_1_1RiseSetArray.md)& Reference to this [**RiseSetArray**](classastrea_1_1trace_1_1RiseSetArray.md) after the intersection. 





        

<hr>



### function operator- 

_Difference operator to subtract one_ [_**RiseSetArray**_](classastrea_1_1trace_1_1RiseSetArray.md) _from another._
```C++
RiseSetArray astrea::trace::RiseSetArray::operator- (
    const RiseSetArray & other
) const
```





**Parameters:**


* `other` The [**RiseSetArray**](classastrea_1_1trace_1_1RiseSetArray.md) to subtract from this one. 



**Returns:**

[**RiseSetArray**](classastrea_1_1trace_1_1RiseSetArray.md) A new [**RiseSetArray**](classastrea_1_1trace_1_1RiseSetArray.md) containing the result of the subtraction. 





        

<hr>



### function operator-= 

_In-place difference operator to subtract one_ [_**RiseSetArray**_](classastrea_1_1trace_1_1RiseSetArray.md) _from another._
```C++
RiseSetArray & astrea::trace::RiseSetArray::operator-= (
    const RiseSetArray & other
) 
```





**Parameters:**


* `other` The [**RiseSetArray**](classastrea_1_1trace_1_1RiseSetArray.md) to subtract from this one. 



**Returns:**

[**RiseSetArray**](classastrea_1_1trace_1_1RiseSetArray.md)& Reference to this [**RiseSetArray**](classastrea_1_1trace_1_1RiseSetArray.md) after the subtraction. 





        

<hr>



### function operator= 

_Move assignment operator for_ [_**RiseSetArray**_](classastrea_1_1trace_1_1RiseSetArray.md) _._
```C++
RiseSetArray & astrea::trace::RiseSetArray::operator= (
    RiseSetArray && other
) noexcept
```





**Parameters:**


* `other` The other [**RiseSetArray**](classastrea_1_1trace_1_1RiseSetArray.md) to move from. 



**Returns:**

[**RiseSetArray**](classastrea_1_1trace_1_1RiseSetArray.md)& Reference to this [**RiseSetArray**](classastrea_1_1trace_1_1RiseSetArray.md) after the move. 





        

<hr>



### function operator= 

_Copy assignment operator for_ [_**RiseSetArray**_](classastrea_1_1trace_1_1RiseSetArray.md) _._
```C++
RiseSetArray & astrea::trace::RiseSetArray::operator= (
    const RiseSetArray & other
) 
```





**Parameters:**


* `other` The other [**RiseSetArray**](classastrea_1_1trace_1_1RiseSetArray.md) to copy from. 



**Returns:**

[**RiseSetArray**](classastrea_1_1trace_1_1RiseSetArray.md)& Reference to this [**RiseSetArray**](classastrea_1_1trace_1_1RiseSetArray.md) after the copy. 





        

<hr>



### function operator== 

_Equality operator to compare two_ [_**RiseSetArray**_](classastrea_1_1trace_1_1RiseSetArray.md) _objects._
```C++
bool astrea::trace::RiseSetArray::operator== (
    const RiseSetArray & other
) const
```





**Parameters:**


* `other` The other [**RiseSetArray**](classastrea_1_1trace_1_1RiseSetArray.md) to compare against. 



**Returns:**

true If the two [**RiseSetArray**](classastrea_1_1trace_1_1RiseSetArray.md) objects are equal. 




**Returns:**

false If the two [**RiseSetArray**](classastrea_1_1trace_1_1RiseSetArray.md) objects are not equal. 





        

<hr>



### function operator[] 

_Returns a reference to the rise/set pair at the specified index._ 
```C++
Time & astrea::trace::RiseSetArray::operator[] (
    const std::size_t & ind
) 
```





**Parameters:**


* `ind` The index of the rise/set pair to access. 



**Returns:**

Time& A reference to the rise/set pair at the specified index. 





        

<hr>



### function operator[] 

_Returns a const reference to the rise/set pair at the specified index._ 
```C++
const Time & astrea::trace::RiseSetArray::operator[] (
    const std::size_t & ind
) const
```





**Parameters:**


* `ind` The index of the rise/set pair to access. 



**Returns:**

const Time& A const reference to the rise/set pair at the specified index. 





        

<hr>



### function operator\| 

_Union operator to combine two_ [_**RiseSetArray**_](classastrea_1_1trace_1_1RiseSetArray.md) _objects._
```C++
RiseSetArray astrea::trace::RiseSetArray::operator| (
    const RiseSetArray & other
) const
```





**Parameters:**


* `other` The other [**RiseSetArray**](classastrea_1_1trace_1_1RiseSetArray.md) to combine with this one. 



**Returns:**

[**RiseSetArray**](classastrea_1_1trace_1_1RiseSetArray.md) A new [**RiseSetArray**](classastrea_1_1trace_1_1RiseSetArray.md) containing the union of the two. 





        

<hr>



### function operator\|= 

_In-place union operator to combine two_ [_**RiseSetArray**_](classastrea_1_1trace_1_1RiseSetArray.md) _objects._
```C++
RiseSetArray & astrea::trace::RiseSetArray::operator|= (
    const RiseSetArray & other
) 
```





**Parameters:**


* `other` The other [**RiseSetArray**](classastrea_1_1trace_1_1RiseSetArray.md) to combine with this one. 



**Returns:**

[**RiseSetArray**](classastrea_1_1trace_1_1RiseSetArray.md)& Reference to this [**RiseSetArray**](classastrea_1_1trace_1_1RiseSetArray.md) after the union. 





        

<hr>



### function prepend 

_Prepends a rise and set time to the array._ 
```C++
void astrea::trace::RiseSetArray::prepend (
    const Time & rise,
    const Time & set
) 
```





**Parameters:**


* `rise` The rise time to prepend. 
* `set` The set time to prepend. 



**Exception:**


* `std::invalid_argument` If the rise time is not before the set time. 
* `std::invalid_argument` If the rise and set times are not in chronological order. 
* `std::invalid_argument` If the rise and set times are not valid. 




        

<hr>



### function size 

_Returns the number of rise/set pairs in the array._ 
```C++
std::size_t astrea::trace::RiseSetArray::size () const
```





**Returns:**

std::size\_t The number of rise/set pairs. 





        

<hr>



### function to\_string\_vector 

_Converts the_ [_**RiseSetArray**_](classastrea_1_1trace_1_1RiseSetArray.md) _to a vector of formatted strings._
```C++
std::vector< std::string > astrea::trace::RiseSetArray::to_string_vector () const
```





**Returns:**

std::vector&lt;std::string&gt; A vector of formatted strings representing the rise and set times. 





        

<hr>



### function ~RiseSetArray 

_Destructor for_ [_**RiseSetArray**_](classastrea_1_1trace_1_1RiseSetArray.md) _._
```C++
astrea::trace::RiseSetArray::~RiseSetArray () = default
```




<hr>

------------------------------
The documentation for this class was generated from the following file `astrea/trace/trace/risesets/RiseSetArray.hpp`

