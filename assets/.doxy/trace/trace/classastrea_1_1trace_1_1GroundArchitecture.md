

# Class astrea::trace::GroundArchitecture



[**ClassList**](annotated.md) **>** [**astrea**](namespaceastrea.md) **>** [**trace**](namespaceastrea_1_1trace.md) **>** [**GroundArchitecture**](classastrea_1_1trace_1_1GroundArchitecture.md)



[_**GroundArchitecture**_](classastrea_1_1trace_1_1GroundArchitecture.md) _class represents a collection of ground stations._[More...](#detailed-description)

* `#include <GroundArchitecture.hpp>`

















## Public Types

| Type | Name |
| ---: | :--- |
| typedef std::vector&lt; [**GroundStation**](classastrea_1_1trace_1_1GroundStation.md) &gt;::const\_iterator | [**const\_iterator**](#typedef-const_iterator)  <br>_Constant iterator type for the_ [_**GroundArchitecture**_](classastrea_1_1trace_1_1GroundArchitecture.md) _class._ |
| typedef std::vector&lt; [**GroundStation**](classastrea_1_1trace_1_1GroundStation.md) &gt;::iterator | [**iterator**](#typedef-iterator)  <br>_Iterator type for the_ [_**GroundArchitecture**_](classastrea_1_1trace_1_1GroundArchitecture.md) _class._ |




















## Public Functions

| Type | Name |
| ---: | :--- |
|   | [**GroundArchitecture**](#function-groundarchitecture) (const std::vector&lt; [**GroundStation**](classastrea_1_1trace_1_1GroundStation.md) &gt; & groundStations) <br>_Constructs a_ [_**GroundArchitecture**_](classastrea_1_1trace_1_1GroundArchitecture.md) _with a list of ground stations._ |
|  [**iterator**](classastrea_1_1trace_1_1GroundArchitecture.md#typedef-iterator) | [**begin**](#function-begin-12) () <br>_Returns an iterator to the beginning of the ground stations._  |
|  [**const\_iterator**](classastrea_1_1trace_1_1GroundArchitecture.md#typedef-const_iterator) | [**begin**](#function-begin-22) () const<br>_Returns a constant iterator to the beginning of the ground stations._  |
|  [**const\_iterator**](classastrea_1_1trace_1_1GroundArchitecture.md#typedef-const_iterator) | [**cbegin**](#function-cbegin) () const<br>_Returns a constant iterator to the beginning of the ground stations._  |
|  [**const\_iterator**](classastrea_1_1trace_1_1GroundArchitecture.md#typedef-const_iterator) | [**cend**](#function-cend) () const<br>_Returns a constant iterator to the end of the ground stations._  |
|  [**iterator**](classastrea_1_1trace_1_1GroundArchitecture.md#typedef-iterator) | [**end**](#function-end-12) () <br>_Returns an iterator to the end of the ground stations._  |
|  [**const\_iterator**](classastrea_1_1trace_1_1GroundArchitecture.md#typedef-const_iterator) | [**end**](#function-end-22) () const<br>_Returns a constant iterator to the end of the ground stations._  |
|  [**GroundStation**](classastrea_1_1trace_1_1GroundStation.md) & | [**operator[]**](#function-operator) (const std::size\_t & idx) <br>_Access operator for_ [_**GroundStation**_](classastrea_1_1trace_1_1GroundStation.md) _._ |
|  const [**GroundStation**](classastrea_1_1trace_1_1GroundStation.md) & | [**operator[]**](#function-operator_1) (const std::size\_t & idx) const<br>_Access operator for_ [_**GroundStation**_](classastrea_1_1trace_1_1GroundStation.md) _(const)._ |
|  std::size\_t | [**size**](#function-size) () const<br>_Returns the number of ground stations in the architecture._  |
|   | [**~GroundArchitecture**](#function-groundarchitecture) () = default<br>_Default destructor for_ [_**GroundArchitecture**_](classastrea_1_1trace_1_1GroundArchitecture.md) _._ |




























## Detailed Description


This class is used to manage and access a set of ground stations, which can be used for various purposes such as communication, observation, or data collection. 


    
## Public Types Documentation




### typedef const\_iterator 

_Constant iterator type for the_ [_**GroundArchitecture**_](classastrea_1_1trace_1_1GroundArchitecture.md) _class._
```C++
using astrea::trace::GroundArchitecture::const_iterator =  std::vector<GroundStation>::const_iterator;
```




<hr>



### typedef iterator 

_Iterator type for the_ [_**GroundArchitecture**_](classastrea_1_1trace_1_1GroundArchitecture.md) _class._
```C++
using astrea::trace::GroundArchitecture::iterator =  std::vector<GroundStation>::iterator;
```




<hr>
## Public Functions Documentation




### function GroundArchitecture 

_Constructs a_ [_**GroundArchitecture**_](classastrea_1_1trace_1_1GroundArchitecture.md) _with a list of ground stations._
```C++
inline astrea::trace::GroundArchitecture::GroundArchitecture (
    const std::vector< GroundStation > & groundStations
) 
```





**Parameters:**


* `groundStations` A vector of [**GroundStation**](classastrea_1_1trace_1_1GroundStation.md) objects representing the ground stations. 




        

<hr>



### function begin [1/2]

_Returns an iterator to the beginning of the ground stations._ 
```C++
inline iterator astrea::trace::GroundArchitecture::begin () 
```





**Returns:**

An iterator to the first ground station. 





        

<hr>



### function begin [2/2]

_Returns a constant iterator to the beginning of the ground stations._ 
```C++
inline const_iterator astrea::trace::GroundArchitecture::begin () const
```





**Returns:**

A constant iterator to the first ground station. 





        

<hr>



### function cbegin 

_Returns a constant iterator to the beginning of the ground stations._ 
```C++
inline const_iterator astrea::trace::GroundArchitecture::cbegin () const
```





**Returns:**

A constant iterator to the first ground station. 





        

<hr>



### function cend 

_Returns a constant iterator to the end of the ground stations._ 
```C++
inline const_iterator astrea::trace::GroundArchitecture::cend () const
```





**Returns:**

A constant iterator to one past the last ground station. 





        

<hr>



### function end [1/2]

_Returns an iterator to the end of the ground stations._ 
```C++
inline iterator astrea::trace::GroundArchitecture::end () 
```





**Returns:**

An iterator to one past the last ground station. 





        

<hr>



### function end [2/2]

_Returns a constant iterator to the end of the ground stations._ 
```C++
inline const_iterator astrea::trace::GroundArchitecture::end () const
```





**Returns:**

A constant iterator to one past the last ground station. 





        

<hr>



### function operator[] 

_Access operator for_ [_**GroundStation**_](classastrea_1_1trace_1_1GroundStation.md) _._
```C++
inline GroundStation & astrea::trace::GroundArchitecture::operator[] (
    const std::size_t & idx
) 
```





**Parameters:**


* `idx` The index of the ground station to access. 



**Returns:**

[**GroundStation**](classastrea_1_1trace_1_1GroundStation.md)& Ground station at the specified index. 





        

<hr>



### function operator[] 

_Access operator for_ [_**GroundStation**_](classastrea_1_1trace_1_1GroundStation.md) _(const)._
```C++
inline const GroundStation & astrea::trace::GroundArchitecture::operator[] (
    const std::size_t & idx
) const
```





**Parameters:**


* `idx` The index of the ground station to access. 



**Returns:**

const [**GroundStation**](classastrea_1_1trace_1_1GroundStation.md)& Ground station at the specified index. 





        

<hr>



### function size 

_Returns the number of ground stations in the architecture._ 
```C++
inline std::size_t astrea::trace::GroundArchitecture::size () const
```





**Returns:**

std::size\_t The number of ground stations. 





        

<hr>



### function ~GroundArchitecture 

_Default destructor for_ [_**GroundArchitecture**_](classastrea_1_1trace_1_1GroundArchitecture.md) _._
```C++
astrea::trace::GroundArchitecture::~GroundArchitecture () = default
```




<hr>

------------------------------
The documentation for this class was generated from the following file `astrea/trace/trace/platforms/ground/GroundArchitecture.hpp`

