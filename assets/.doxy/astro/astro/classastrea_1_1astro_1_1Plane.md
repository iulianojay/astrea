

# Class astrea::astro::Plane

**template &lt;[**class**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) [**Spacecraft\_T**](classastrea_1_1astro_1_1DirectionCosineMatrix.md)&gt;**



[**ClassList**](annotated.md) **>** [**astrea**](namespaceastrea.md) **>** [**astro**](namespaceastrea_1_1astro.md) **>** [**Plane**](classastrea_1_1astro_1_1Plane.md)



_A_ [_**Plane**_](classastrea_1_1astro_1_1Plane.md) _is a collection of_[_**Spacecraft**_](classastrea_1_1astro_1_1Spacecraft.md) _that share the same orbital elements._[More...](#detailed-description)

* `#include <Plane.hpp>`

















## Public Types

| Type | Name |
| ---: | :--- |
| typedef std::vector&lt; [**Spacecraft\_T**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) &gt;::const\_iterator | [**const\_iterator**](#typedef-const_iterator)  <br>_Const iterator for iterating over all_ [_**Spacecraft**_](classastrea_1_1astro_1_1Spacecraft.md) _in the_[_**Plane**_](classastrea_1_1astro_1_1Plane.md) _._ |
| typedef std::vector&lt; [**Spacecraft\_T**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) &gt;::iterator | [**iterator**](#typedef-iterator)  <br>_Iterator for iterating over all_ [_**Spacecraft**_](classastrea_1_1astro_1_1Spacecraft.md) _in the_[_**Plane**_](classastrea_1_1astro_1_1Plane.md) _._ |




















## Public Functions

| Type | Name |
| ---: | :--- |
|   | [**Plane**](#function-plane-12) () <br>_Default constructor for_ [_**Plane**_](classastrea_1_1astro_1_1Plane.md) _._ |
|   | [**Plane**](#function-plane-22) (std::vector&lt; [**Spacecraft\_T**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) &gt; satellites) <br>_Construct a_ [_**Plane**_](classastrea_1_1astro_1_1Plane.md) _from a vector of_[_**Spacecraft**_](classastrea_1_1astro_1_1Spacecraft.md) _._ |
|  [**void**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) | [**add\_spacecraft**](#function-add_spacecraft) ([**const**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) [**Spacecraft\_T**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) & spacecraft) <br>_Add a_ [_**Spacecraft**_](classastrea_1_1astro_1_1Spacecraft.md) _to the_[_**Plane**_](classastrea_1_1astro_1_1Plane.md) _._ |
|  [**iterator**](classastrea_1_1astro_1_1Plane.md#typedef-iterator) | [**begin**](#function-begin-12) () <br>_Get an iterator to the beginning of the_ [_**Plane**_](classastrea_1_1astro_1_1Plane.md) _._ |
|  [**const\_iterator**](classastrea_1_1astro_1_1Plane.md#typedef-const_iterator) | [**begin**](#function-begin-22) () const<br>_Get a const iterator to the beginning of the_ [_**Plane**_](classastrea_1_1astro_1_1Plane.md) _._ |
|  [**const\_iterator**](classastrea_1_1astro_1_1Plane.md#typedef-const_iterator) | [**cbegin**](#function-cbegin) () const<br>_Get a const iterator to the beginning of the_ [_**Plane**_](classastrea_1_1astro_1_1Plane.md) _._ |
|  [**const\_iterator**](classastrea_1_1astro_1_1Plane.md#typedef-const_iterator) | [**cend**](#function-cend) () const<br>_Get a const iterator to the end of the_ [_**Plane**_](classastrea_1_1astro_1_1Plane.md) _._ |
|  [**iterator**](classastrea_1_1astro_1_1Plane.md#typedef-iterator) | [**end**](#function-end-12) () <br>_Get an iterator to the end of the_ [_**Plane**_](classastrea_1_1astro_1_1Plane.md) _._ |
|  [**const\_iterator**](classastrea_1_1astro_1_1Plane.md#typedef-const_iterator) | [**end**](#function-end-22) () const<br>_Get a const iterator to the end of the_ [_**Plane**_](classastrea_1_1astro_1_1Plane.md) _._ |
|  std::vector&lt; [**Spacecraft\_T**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) &gt; & | [**get\_all\_spacecraft**](#function-get_all_spacecraft-12) () <br>_Get all_ [_**Spacecraft**_](classastrea_1_1astro_1_1Spacecraft.md) _in the_[_**Plane**_](classastrea_1_1astro_1_1Plane.md) _._ |
|  [**const**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) std::vector&lt; [**Spacecraft\_T**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) &gt; & | [**get\_all\_spacecraft**](#function-get_all_spacecraft-22) () const<br>_Get all_ [_**Spacecraft**_](classastrea_1_1astro_1_1Spacecraft.md) _in the_[_**Plane**_](classastrea_1_1astro_1_1Plane.md) _._ |
|  [**const**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) [**OrbitalElements**](classastrea_1_1astro_1_1OrbitalElements.md) & | [**get\_elements**](#function-get_elements) () const<br>_Get the orbital elements shared by all_ [_**Spacecraft**_](classastrea_1_1astro_1_1Spacecraft.md) _in the_[_**Plane**_](classastrea_1_1astro_1_1Plane.md) _. The fast variable can be ignored._ |
|  [**const**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) std::size\_t | [**get\_id**](#function-get_id) () const<br>_Get the ID of the_ [_**Plane**_](classastrea_1_1astro_1_1Plane.md) _._ |
|  [**const**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) [**Spacecraft\_T**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) & | [**get\_spacecraft**](#function-get_spacecraft) ([**const**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) std::size\_t & spacecraftId) const<br>_Get a_ [_**Spacecraft**_](classastrea_1_1astro_1_1Spacecraft.md) _by its ID._ |
|  [**void**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) | [**propagate**](#function-propagate-12) ([**const**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) [**Time**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) & propTime, [**Integrator**](classastrea_1_1astro_1_1Integrator.md) & integrator) <br>_Propagate the_ [_**Plane**_](classastrea_1_1astro_1_1Plane.md) _using the provided epoch and Equations of Motion._ |
|  [**void**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) | [**propagate**](#function-propagate-22) ([**const**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) [**Date**](classastrea_1_1astro_1_1Date.md) & endEpoch, [**Integrator**](classastrea_1_1astro_1_1Integrator.md) & integrator) <br>_Propagate the_ [_**Plane**_](classastrea_1_1astro_1_1Plane.md) _using the provided epoch and Equations of Motion._ |
|  [**const**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) std::size\_t | [**size**](#function-size) () const<br>_Get the number of_ [_**Spacecraft**_](classastrea_1_1astro_1_1Spacecraft.md) _in the_[_**Plane**_](classastrea_1_1astro_1_1Plane.md) _._ |
|   | [**~Plane**](#function-plane) () = default<br>_Destructor for_ [_**Plane**_](classastrea_1_1astro_1_1Plane.md) _._ |




























## Detailed Description




**Template parameters:**


* `Spacecraft_T` The type of [**Spacecraft**](classastrea_1_1astro_1_1Spacecraft.md) that this [**Plane**](classastrea_1_1astro_1_1Plane.md) will contain. Must be derived from [**Spacecraft**](classastrea_1_1astro_1_1Spacecraft.md).
  * 





**Note:**

This class is templated to allow for different types of [**Spacecraft**](classastrea_1_1astro_1_1Spacecraft.md), but it is expected that the type will be derived from [**Spacecraft**](classastrea_1_1astro_1_1Spacecraft.md). 





    
## Public Types Documentation




### typedef const\_iterator 

_Const iterator for iterating over all_ [_**Spacecraft**_](classastrea_1_1astro_1_1Spacecraft.md) _in the_[_**Plane**_](classastrea_1_1astro_1_1Plane.md) _._
```C++
using astrea::astro::Plane< Spacecraft_T >::const_iterator =  std::vector<Spacecraft_T>::const_iterator;
```




<hr>



### typedef iterator 

_Iterator for iterating over all_ [_**Spacecraft**_](classastrea_1_1astro_1_1Spacecraft.md) _in the_[_**Plane**_](classastrea_1_1astro_1_1Plane.md) _._
```C++
using astrea::astro::Plane< Spacecraft_T >::iterator =  std::vector<Spacecraft_T>::iterator;
```




<hr>
## Public Functions Documentation




### function Plane [1/2]

_Default constructor for_ [_**Plane**_](classastrea_1_1astro_1_1Plane.md) _._
```C++
inline astrea::astro::Plane::Plane () 
```




<hr>



### function Plane [2/2]

_Construct a_ [_**Plane**_](classastrea_1_1astro_1_1Plane.md) _from a vector of_[_**Spacecraft**_](classastrea_1_1astro_1_1Spacecraft.md) _._
```C++
astrea::astro::Plane::Plane (
    std::vector< Spacecraft_T > satellites
) 
```





**Parameters:**


* `satellites` A vector of [**Spacecraft**](classastrea_1_1astro_1_1Spacecraft.md) to initialize the [**Plane**](classastrea_1_1astro_1_1Plane.md). 




        

<hr>



### function add\_spacecraft 

_Add a_ [_**Spacecraft**_](classastrea_1_1astro_1_1Spacecraft.md) _to the_[_**Plane**_](classastrea_1_1astro_1_1Plane.md) _._
```C++
void astrea::astro::Plane::add_spacecraft (
    const  Spacecraft_T & spacecraft
) 
```





**Parameters:**


* `spacecraft` The [**Spacecraft**](classastrea_1_1astro_1_1Spacecraft.md) to add to the [**Plane**](classastrea_1_1astro_1_1Plane.md). 




        

<hr>



### function begin [1/2]

_Get an iterator to the beginning of the_ [_**Plane**_](classastrea_1_1astro_1_1Plane.md) _._
```C++
inline iterator astrea::astro::Plane::begin () 
```





**Returns:**

iterator An iterator pointing to the first [**Spacecraft**](classastrea_1_1astro_1_1Spacecraft.md) in the [**Plane**](classastrea_1_1astro_1_1Plane.md). 





        

<hr>



### function begin [2/2]

_Get a const iterator to the beginning of the_ [_**Plane**_](classastrea_1_1astro_1_1Plane.md) _._
```C++
inline const_iterator astrea::astro::Plane::begin () const
```





**Returns:**

const\_iterator A const iterator pointing to the first [**Spacecraft**](classastrea_1_1astro_1_1Spacecraft.md) in the [**Plane**](classastrea_1_1astro_1_1Plane.md). 





        

<hr>



### function cbegin 

_Get a const iterator to the beginning of the_ [_**Plane**_](classastrea_1_1astro_1_1Plane.md) _._
```C++
inline const_iterator astrea::astro::Plane::cbegin () const
```





**Returns:**

const\_iterator A const iterator pointing to the first [**Spacecraft**](classastrea_1_1astro_1_1Spacecraft.md) in the [**Plane**](classastrea_1_1astro_1_1Plane.md). 





        

<hr>



### function cend 

_Get a const iterator to the end of the_ [_**Plane**_](classastrea_1_1astro_1_1Plane.md) _._
```C++
inline const_iterator astrea::astro::Plane::cend () const
```





**Returns:**

const\_iterator A const iterator pointing to one past the last [**Spacecraft**](classastrea_1_1astro_1_1Spacecraft.md) in the [**Plane**](classastrea_1_1astro_1_1Plane.md). 





        

<hr>



### function end [1/2]

_Get an iterator to the end of the_ [_**Plane**_](classastrea_1_1astro_1_1Plane.md) _._
```C++
inline iterator astrea::astro::Plane::end () 
```





**Returns:**

iterator An iterator pointing to one past the last [**Spacecraft**](classastrea_1_1astro_1_1Spacecraft.md) in the [**Plane**](classastrea_1_1astro_1_1Plane.md). 





        

<hr>



### function end [2/2]

_Get a const iterator to the end of the_ [_**Plane**_](classastrea_1_1astro_1_1Plane.md) _._
```C++
inline const_iterator astrea::astro::Plane::end () const
```





**Returns:**

const\_iterator A const iterator pointing to one past the last [**Spacecraft**](classastrea_1_1astro_1_1Spacecraft.md) in the [**Plane**](classastrea_1_1astro_1_1Plane.md). 





        

<hr>



### function get\_all\_spacecraft [1/2]

_Get all_ [_**Spacecraft**_](classastrea_1_1astro_1_1Spacecraft.md) _in the_[_**Plane**_](classastrea_1_1astro_1_1Plane.md) _._
```C++
std::vector< Spacecraft_T > & astrea::astro::Plane::get_all_spacecraft () 
```





**Returns:**

std::vector&lt;Spacecraft\_T&gt;& A reference to the vector of [**Spacecraft**](classastrea_1_1astro_1_1Spacecraft.md) in the [**Plane**](classastrea_1_1astro_1_1Plane.md). 





        

<hr>



### function get\_all\_spacecraft [2/2]

_Get all_ [_**Spacecraft**_](classastrea_1_1astro_1_1Spacecraft.md) _in the_[_**Plane**_](classastrea_1_1astro_1_1Plane.md) _._
```C++
const std::vector< Spacecraft_T > & astrea::astro::Plane::get_all_spacecraft () const
```





**Returns:**

const std::vector&lt;Spacecraft\_T&gt;& A const reference to the vector of [**Spacecraft**](classastrea_1_1astro_1_1Spacecraft.md) in the [**Plane**](classastrea_1_1astro_1_1Plane.md). 





        

<hr>



### function get\_elements 

_Get the orbital elements shared by all_ [_**Spacecraft**_](classastrea_1_1astro_1_1Spacecraft.md) _in the_[_**Plane**_](classastrea_1_1astro_1_1Plane.md) _. The fast variable can be ignored._
```C++
inline const  OrbitalElements & astrea::astro::Plane::get_elements () const
```





**Returns:**

const [**OrbitalElements**](classastrea_1_1astro_1_1OrbitalElements.md)& A const reference to the orbital elements of the [**Plane**](classastrea_1_1astro_1_1Plane.md). 





        

<hr>



### function get\_id 

_Get the ID of the_ [_**Plane**_](classastrea_1_1astro_1_1Plane.md) _._
```C++
inline const std::size_t astrea::astro::Plane::get_id () const
```





**Returns:**

const std::size\_t The unique identifier for the [**Plane**](classastrea_1_1astro_1_1Plane.md). 





        

<hr>



### function get\_spacecraft 

_Get a_ [_**Spacecraft**_](classastrea_1_1astro_1_1Spacecraft.md) _by its ID._
```C++
const  Spacecraft_T & astrea::astro::Plane::get_spacecraft (
    const std::size_t & spacecraftId
) const
```





**Parameters:**


* `spacecraftId` The ID of the [**Spacecraft**](classastrea_1_1astro_1_1Spacecraft.md) to retrieve. 



**Returns:**

Spacecraft\_T& A reference to the [**Spacecraft**](classastrea_1_1astro_1_1Spacecraft.md) with the specified ID. 





        

<hr>



### function propagate [1/2]

_Propagate the_ [_**Plane**_](classastrea_1_1astro_1_1Plane.md) _using the provided epoch and Equations of Motion._
```C++
void astrea::astro::Plane::propagate (
    const  Time & propTime,
    Integrator & integrator
) 
```





**Parameters:**


* `propTime` The total propagation time after the initial state epoch. 
* `integrator` The [**Integrator**](classastrea_1_1astro_1_1Integrator.md) to use for propagation. 




        

<hr>



### function propagate [2/2]

_Propagate the_ [_**Plane**_](classastrea_1_1astro_1_1Plane.md) _using the provided epoch and Equations of Motion._
```C++
void astrea::astro::Plane::propagate (
    const  Date & endEpoch,
    Integrator & integrator
) 
```





**Parameters:**


* `endEpoch` The end epoch for propagation. 
* `integrator` The [**Integrator**](classastrea_1_1astro_1_1Integrator.md) to use for propagation. 




        

<hr>



### function size 

_Get the number of_ [_**Spacecraft**_](classastrea_1_1astro_1_1Spacecraft.md) _in the_[_**Plane**_](classastrea_1_1astro_1_1Plane.md) _._
```C++
const std::size_t astrea::astro::Plane::size () const
```





**Returns:**

std::size\_t The number of [**Spacecraft**](classastrea_1_1astro_1_1Spacecraft.md) in the [**Plane**](classastrea_1_1astro_1_1Plane.md). 





        

<hr>



### function ~Plane 

_Destructor for_ [_**Plane**_](classastrea_1_1astro_1_1Plane.md) _._
```C++
astrea::astro::Plane::~Plane () = default
```




<hr>

------------------------------
The documentation for this class was generated from the following file `astrea/astro/astro/platforms/space/Plane.hpp`

