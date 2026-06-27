

# Class astrea::astro::Shell

**template &lt;[**class**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) [**Spacecraft\_T**](classastrea_1_1astro_1_1DirectionCosineMatrix.md)&gt;**



[**ClassList**](annotated.md) **>** [**astrea**](namespaceastrea.md) **>** [**astro**](namespaceastrea_1_1astro.md) **>** [**Shell**](classastrea_1_1astro_1_1Shell.md)



_A_ [_**Shell**_](classastrea_1_1astro_1_1Shell.md) _is a collection of planes, each containing a set of_[_**Spacecraft**_](classastrea_1_1astro_1_1Spacecraft.md) _. It is used to represent sub-constellations of satellites in orbit._[More...](#detailed-description)

* `#include <Shell.hpp>`















## Classes

| Type | Name |
| ---: | :--- |
| class | [**sat\_iterator**](classastrea_1_1astro_1_1Shell_1_1sat__iterator.md) <br>_Iterator for iterating over all_ [_**Spacecraft**_](classastrea_1_1astro_1_1Spacecraft.md) _in the_[_**Shell**_](classastrea_1_1astro_1_1Shell.md) _._ |


## Public Types

| Type | Name |
| ---: | :--- |
| typedef [**const**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) [**sat\_iterator**](classastrea_1_1astro_1_1Shell_1_1sat__iterator.md) | [**const\_iterator**](#typedef-const_iterator)  <br>_Const iterator for iterating over all Planes in the_ [_**Shell**_](classastrea_1_1astro_1_1Shell.md) _._ |
| typedef [**sat\_iterator**](classastrea_1_1astro_1_1Shell_1_1sat__iterator.md) | [**iterator**](#typedef-iterator)  <br>_Iterator for iterating over all Planes in the_ [_**Shell**_](classastrea_1_1astro_1_1Shell.md) _._ |




















## Public Functions

| Type | Name |
| ---: | :--- |
|   | [**Shell**](#function-shell-14) () = default<br>_Default constructor for_ [_**Shell**_](classastrea_1_1astro_1_1Shell.md) _. Initializes an empty shell with no planes or spacecraft._ |
|   | [**Shell**](#function-shell-24) (std::vector&lt; [**Plane**](classastrea_1_1astro_1_1Plane.md)&lt; [**Spacecraft\_T**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) &gt; &gt; planes) <br>_Constructor for_ [_**Shell**_](classastrea_1_1astro_1_1Shell.md) _with a vector of planes._ |
|   | [**Shell**](#function-shell-34) (std::vector&lt; [**Spacecraft\_T**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) &gt; satellites) <br>_Constructor for_ [_**Shell**_](classastrea_1_1astro_1_1Shell.md) _with a vector of satellites._ |
|   | [**Shell**](#function-shell-44) ([**const**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) [**Date**](classastrea_1_1astro_1_1Date.md) & epoch, [**const**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) [**Distance**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) & semimajor, [**const**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) [**Angle**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) & inclination, [**const**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) std::size\_t & T, [**const**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) std::size\_t & P, [**const**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) [**Unitless**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) & F, [**const**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) [**Angle**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) & anchorRAAN=0.0 \*mp\_units::angular::unit\_symbols::rad, [**const**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) [**Angle**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) & anchorAnomaly=0.0 \*mp\_units::angular::unit\_symbols::rad) <br>_Constructor for_ [_**Shell**_](classastrea_1_1astro_1_1Shell.md) _with a Walker parameters._ |
|  [**void**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) | [**add\_plane**](#function-add_plane) ([**const**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) [**Plane**](classastrea_1_1astro_1_1Plane.md)&lt; [**Spacecraft\_T**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) &gt; & plane) <br>_Adds a plane to the shell._  |
|  [**void**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) | [**add\_spacecraft**](#function-add_spacecraft-12) ([**const**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) [**Spacecraft\_T**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) & spacecraft, [**const**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) std::size\_t & planeId) <br>_Adds a spacecraft to a specific plane in the shell._  |
|  [**void**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) | [**add\_spacecraft**](#function-add_spacecraft-22) ([**const**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) [**Spacecraft\_T**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) & spacecraft) <br>_Adds a spacecraft to the shell._  |
|  [**iterator**](classastrea_1_1astro_1_1Shell.md#typedef-iterator) | [**begin**](#function-begin-12) () <br>_Get an iterator to the beginning of the_ [_**Shell**_](classastrea_1_1astro_1_1Shell.md) _._ |
|  [**const\_iterator**](classastrea_1_1astro_1_1Shell.md#typedef-const_iterator) | [**begin**](#function-begin-22) () const<br>_Get a const iterator to the beginning of the_ [_**Shell**_](classastrea_1_1astro_1_1Shell.md) _._ |
|  [**const\_iterator**](classastrea_1_1astro_1_1Shell.md#typedef-const_iterator) | [**cbegin**](#function-cbegin) () const<br>_Get a const iterator to the beginning of the_ [_**Shell**_](classastrea_1_1astro_1_1Shell.md) _._ |
|  [**const\_iterator**](classastrea_1_1astro_1_1Shell.md#typedef-const_iterator) | [**cend**](#function-cend) () const<br>_Get a const iterator to the end of the_ [_**Shell**_](classastrea_1_1astro_1_1Shell.md) _._ |
|  [**iterator**](classastrea_1_1astro_1_1Shell.md#typedef-iterator) | [**end**](#function-end-12) () <br>_Get an iterator to the end of the_ [_**Shell**_](classastrea_1_1astro_1_1Shell.md) _._ |
|  [**const\_iterator**](classastrea_1_1astro_1_1Shell.md#typedef-const_iterator) | [**end**](#function-end-22) () const<br>_Get a const iterator to the end of the_ [_**Shell**_](classastrea_1_1astro_1_1Shell.md) _._ |
|  [**const**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) std::vector&lt; [**Spacecraft\_T**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) &gt; | [**get\_all\_spacecraft**](#function-get_all_spacecraft) () const<br>_Returns a vector of all spacecraft in the shell._  |
|  [**const**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) std::size\_t | [**get\_id**](#function-get_id) () const<br> |
|  [**const**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) [**Plane**](classastrea_1_1astro_1_1Plane.md)&lt; [**Spacecraft\_T**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) &gt; & | [**get\_plane**](#function-get_plane) ([**const**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) std::size\_t & planeId) const<br>_Returns a reference to a specific plane in the shell by its ID._  |
|  std::vector&lt; [**Plane**](classastrea_1_1astro_1_1Plane.md)&lt; [**Spacecraft\_T**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) &gt; &gt; & | [**get\_planes**](#function-get_planes-12) () <br>_Returns a reference to the vector of planes in the shell._  |
|  [**const**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) std::vector&lt; [**Plane**](classastrea_1_1astro_1_1Plane.md)&lt; [**Spacecraft\_T**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) &gt; &gt; & | [**get\_planes**](#function-get_planes-22) () const<br>_Returns a constant reference to the vector of planes in the shell._  |
|  [**const**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) [**Spacecraft\_T**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) & | [**get\_spacecraft**](#function-get_spacecraft) ([**const**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) std::size\_t & spacecraftId) const<br>_Returns a reference to a specific spacecraft in the shell by its ID._  |
|  [**const**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) std::size\_t | [**n\_planes**](#function-n_planes) () const<br>_Returns the number of planes in the shell._  |
|  [**void**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) | [**propagate**](#function-propagate-12) ([**const**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) [**Time**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) & propTime, [**Integrator**](classastrea_1_1astro_1_1Integrator.md) & integrator) <br>_Propagates the shell's spacecraft using the provided equations of motion and integrator._  |
|  [**void**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) | [**propagate**](#function-propagate-22) ([**const**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) [**Date**](classastrea_1_1astro_1_1Date.md) & endEpoch, [**Integrator**](classastrea_1_1astro_1_1Integrator.md) & integrator) <br>_Propagates the shell's spacecraft using the provided equations of motion and integrator._  |
|  [**const**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) std::size\_t | [**size**](#function-size) () const<br>_Returns the size of the shell, which is the number of spacecraft it contains._  |
|   | [**~Shell**](#function-shell) () <br>_Destructor for_ [_**Shell**_](classastrea_1_1astro_1_1Shell.md) _. Cleans up the shell and its planes._ |




























## Detailed Description




**Template parameters:**


* `Spacecraft_T` The type of spacecraft contained in the shell, must derive from [**Spacecraft**](classastrea_1_1astro_1_1Spacecraft.md).
  * 





**Note:**

This class is templated to allow for different types of spacecraft, but it must be derived from the [**Spacecraft**](classastrea_1_1astro_1_1Spacecraft.md) base class. 





    
## Public Types Documentation




### typedef const\_iterator 

_Const iterator for iterating over all Planes in the_ [_**Shell**_](classastrea_1_1astro_1_1Shell.md) _._
```C++
using astrea::astro::Shell< Spacecraft_T >::const_iterator =  const sat_iterator;
```




<hr>



### typedef iterator 

_Iterator for iterating over all Planes in the_ [_**Shell**_](classastrea_1_1astro_1_1Shell.md) _._
```C++
using astrea::astro::Shell< Spacecraft_T >::iterator =  sat_iterator;
```




<hr>
## Public Functions Documentation




### function Shell [1/4]

_Default constructor for_ [_**Shell**_](classastrea_1_1astro_1_1Shell.md) _. Initializes an empty shell with no planes or spacecraft._
```C++
astrea::astro::Shell::Shell () = default
```




<hr>



### function Shell [2/4]

_Constructor for_ [_**Shell**_](classastrea_1_1astro_1_1Shell.md) _with a vector of planes._
```C++
astrea::astro::Shell::Shell (
    std::vector< Plane < Spacecraft_T > > planes
) 
```





**Parameters:**


* `planes` A vector of [**Plane**](classastrea_1_1astro_1_1Plane.md) objects containing Spacecraft\_T. 




        

<hr>



### function Shell [3/4]

_Constructor for_ [_**Shell**_](classastrea_1_1astro_1_1Shell.md) _with a vector of satellites._
```C++
astrea::astro::Shell::Shell (
    std::vector< Spacecraft_T > satellites
) 
```





**Parameters:**


* `satellites` A vector of Spacecraft\_T objects to be added to the shell. 




        

<hr>



### function Shell [4/4]

_Constructor for_ [_**Shell**_](classastrea_1_1astro_1_1Shell.md) _with a Walker parameters._
```C++
astrea::astro::Shell::Shell (
    const  Date & epoch,
    const  Distance & semimajor,
    const  Angle & inclination,
    const std::size_t & T,
    const std::size_t & P,
    const  Unitless & F,
    const  Angle & anchorRAAN=0.0 *mp_units::angular::unit_symbols::rad,
    const  Angle & anchorAnomaly=0.0 *mp_units::angular::unit_symbols::rad
) 
```





**Parameters:**


* `epoch` The epoch date for the shell's orbit. 
* `semimajor` The semimajor axis of the shell's orbit. 
* `inclination` The inclination of the shell's orbit. 
* `T` The number of planes in the shell. 
* `P` The number of spacecraft per plane. 
* `F` The spacing factor between spacecraft in the same plane. 
* `anchorRAAN` The right ascension of ascending node for the shell's orbit (default is 0). 
* `anchorAnomaly` The argument of perigee for the shell's orbit (default is 0). 




        

<hr>



### function add\_plane 

_Adds a plane to the shell._ 
```C++
void astrea::astro::Shell::add_plane (
    const  Plane < Spacecraft_T > & plane
) 
```





**Parameters:**


* `plane` The [**Plane**](classastrea_1_1astro_1_1Plane.md) object to be added to the shell. 




        

<hr>



### function add\_spacecraft [1/2]

_Adds a spacecraft to a specific plane in the shell._ 
```C++
void astrea::astro::Shell::add_spacecraft (
    const  Spacecraft_T & spacecraft,
    const std::size_t & planeId
) 
```





**Parameters:**


* `spacecraft` The Spacecraft\_T object to be added. 
* `planeId` The ID of the plane to which the spacecraft will be added. 




        

<hr>



### function add\_spacecraft [2/2]

_Adds a spacecraft to the shell._ 
```C++
void astrea::astro::Shell::add_spacecraft (
    const  Spacecraft_T & spacecraft
) 
```





**Parameters:**


* `spacecraft` The Spacecraft\_T object to be added. 




        

<hr>



### function begin [1/2]

_Get an iterator to the beginning of the_ [_**Shell**_](classastrea_1_1astro_1_1Shell.md) _._
```C++
inline iterator astrea::astro::Shell::begin () 
```





**Returns:**

iterator An iterator pointing to the first [**Plane**](classastrea_1_1astro_1_1Plane.md) in the [**Shell**](classastrea_1_1astro_1_1Shell.md). 





        

<hr>



### function begin [2/2]

_Get a const iterator to the beginning of the_ [_**Shell**_](classastrea_1_1astro_1_1Shell.md) _._
```C++
inline const_iterator astrea::astro::Shell::begin () const
```





**Returns:**

const\_iterator A const iterator pointing to the first [**Plane**](classastrea_1_1astro_1_1Plane.md) in the [**Shell**](classastrea_1_1astro_1_1Shell.md). 





        

<hr>



### function cbegin 

_Get a const iterator to the beginning of the_ [_**Shell**_](classastrea_1_1astro_1_1Shell.md) _._
```C++
inline const_iterator astrea::astro::Shell::cbegin () const
```





**Returns:**

const\_iterator A const iterator pointing to the first [**Plane**](classastrea_1_1astro_1_1Plane.md) in the [**Shell**](classastrea_1_1astro_1_1Shell.md). 





        

<hr>



### function cend 

_Get a const iterator to the end of the_ [_**Shell**_](classastrea_1_1astro_1_1Shell.md) _._
```C++
inline const_iterator astrea::astro::Shell::cend () const
```





**Returns:**

const\_iterator A const iterator pointing to one past the last [**Plane**](classastrea_1_1astro_1_1Plane.md) in the [**Shell**](classastrea_1_1astro_1_1Shell.md). 





        

<hr>



### function end [1/2]

_Get an iterator to the end of the_ [_**Shell**_](classastrea_1_1astro_1_1Shell.md) _._
```C++
inline iterator astrea::astro::Shell::end () 
```





**Returns:**

iterator An iterator pointing to one past the last [**Plane**](classastrea_1_1astro_1_1Plane.md) in the [**Shell**](classastrea_1_1astro_1_1Shell.md). 





        

<hr>



### function end [2/2]

_Get a const iterator to the end of the_ [_**Shell**_](classastrea_1_1astro_1_1Shell.md) _._
```C++
inline const_iterator astrea::astro::Shell::end () const
```





**Returns:**

const\_iterator A const iterator pointing to one past the last [**Plane**](classastrea_1_1astro_1_1Plane.md) in the [**Shell**](classastrea_1_1astro_1_1Shell.md). 





        

<hr>



### function get\_all\_spacecraft 

_Returns a vector of all spacecraft in the shell._ 
```C++
const std::vector< Spacecraft_T > astrea::astro::Shell::get_all_spacecraft () const
```





**Returns:**

const std::vector&lt;Spacecraft\_T&gt; A vector containing all spacecraft in the shell. 





        

<hr>



### function get\_id 

```C++
inline const std::size_t astrea::astro::Shell::get_id () const
```




<hr>



### function get\_plane 

_Returns a reference to a specific plane in the shell by its ID._ 
```C++
const  Plane < Spacecraft_T > & astrea::astro::Shell::get_plane (
    const std::size_t & planeId
) const
```





**Parameters:**


* `planeId` The ID of the plane to retrieve. 



**Returns:**

const [**Plane&lt;Spacecraft\_T&gt;**](classastrea_1_1astro_1_1Plane.md)& A constant reference to the specified plane. 





        

<hr>



### function get\_planes [1/2]

_Returns a reference to the vector of planes in the shell._ 
```C++
std::vector< Plane < Spacecraft_T > > & astrea::astro::Shell::get_planes () 
```





**Returns:**

std::vector&lt;Plane&lt;Spacecraft\_T&gt;&gt;& A reference to the vector of planes in the shell. 





        

<hr>



### function get\_planes [2/2]

_Returns a constant reference to the vector of planes in the shell._ 
```C++
const std::vector< Plane < Spacecraft_T > > & astrea::astro::Shell::get_planes () const
```





**Returns:**

const std::vector&lt;Plane&lt;Spacecraft\_T&gt;&gt;& A constant reference to the vector of planes in the shell. 





        

<hr>



### function get\_spacecraft 

_Returns a reference to a specific spacecraft in the shell by its ID._ 
```C++
const  Spacecraft_T & astrea::astro::Shell::get_spacecraft (
    const std::size_t & spacecraftId
) const
```





**Parameters:**


* `spacecraftId` The ID of the spacecraft to retrieve. 



**Returns:**

const Spacecraft\_T& A constant reference to the specified spacecraft. 





        

<hr>



### function n\_planes 

_Returns the number of planes in the shell._ 
```C++
const std::size_t astrea::astro::Shell::n_planes () const
```





**Returns:**

const std::size\_t The number of planes in the shell. 





        

<hr>



### function propagate [1/2]

_Propagates the shell's spacecraft using the provided equations of motion and integrator._ 
```C++
void astrea::astro::Shell::propagate (
    const  Time & propTime,
    Integrator & integrator
) 
```





**Parameters:**


* `propTime` The total propagation time after the initial state epoch. 
* `integrator` The integrator to be used for numerical integration. 




        

<hr>



### function propagate [2/2]

_Propagates the shell's spacecraft using the provided equations of motion and integrator._ 
```C++
void astrea::astro::Shell::propagate (
    const  Date & endEpoch,
    Integrator & integrator
) 
```





**Parameters:**


* `endEpoch` The end epoch for propagation. 
* `integrator` The integrator to be used for numerical integration. 




        

<hr>



### function size 

_Returns the size of the shell, which is the number of spacecraft it contains._ 
```C++
const std::size_t astrea::astro::Shell::size () const
```





**Returns:**

const std::size\_t The number of spacecraft in the shell. 





        

<hr>



### function ~Shell 

_Destructor for_ [_**Shell**_](classastrea_1_1astro_1_1Shell.md) _. Cleans up the shell and its planes._
```C++
inline astrea::astro::Shell::~Shell () 
```




<hr>

------------------------------
The documentation for this class was generated from the following file `astrea/astro/astro/platforms/space/Shell.hpp`

