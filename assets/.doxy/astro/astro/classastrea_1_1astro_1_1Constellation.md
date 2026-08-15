

# Class astrea::astro::Constellation

**template &lt;class Spacecraft\_T&gt;**



[**ClassList**](annotated.md) **>** [**astrea**](namespaceastrea.md) **>** [**astro**](namespaceastrea_1_1astro.md) **>** [**Constellation**](classastrea_1_1astro_1_1Constellation.md)



_A_ [_**Constellation**_](classastrea_1_1astro_1_1Constellation.md) _is a collection of_[_**Spacecraft**_](classastrea_1_1astro_1_1Spacecraft.md) _, organized into Shells and/or Planes._[More...](#detailed-description)

* `#include <Constellation.hpp>`















## Classes

| Type | Name |
| ---: | :--- |
| class | [**sat\_iterator**](classastrea_1_1astro_1_1Constellation_1_1sat__iterator.md) <br>_Iterator class for iterating over all_ [_**Spacecraft**_](classastrea_1_1astro_1_1Spacecraft.md) _in the_[_**Constellation**_](classastrea_1_1astro_1_1Constellation.md) _._ |


## Public Types

| Type | Name |
| ---: | :--- |
| typedef const [**sat\_iterator**](classastrea_1_1astro_1_1Constellation_1_1sat__iterator.md) | [**const\_iterator**](#typedef-const_iterator)  <br>_Const iterator for iterating over all_ [_**Spacecraft**_](classastrea_1_1astro_1_1Spacecraft.md) _in the_[_**Constellation**_](classastrea_1_1astro_1_1Constellation.md) _._ |
| typedef [**sat\_iterator**](classastrea_1_1astro_1_1Constellation_1_1sat__iterator.md) | [**iterator**](#typedef-iterator)  <br>_Iterator for iterating over all_ [_**Spacecraft**_](classastrea_1_1astro_1_1Spacecraft.md) _in the_[_**Constellation**_](classastrea_1_1astro_1_1Constellation.md) _._ |




















## Public Functions

| Type | Name |
| ---: | :--- |
|   | [**Constellation**](#function-constellation-16) () <br>_Default constructor for_ [_**Constellation**_](classastrea_1_1astro_1_1Constellation.md) _._ |
|   | [**Constellation**](#function-constellation-26) (std::vector&lt; [**Shell**](classastrea_1_1astro_1_1Shell.md)&lt; Spacecraft\_T &gt; &gt; shells) <br>_Construct a_ [_**Constellation**_](classastrea_1_1astro_1_1Constellation.md) _from a vector of Shells._ |
|   | [**Constellation**](#function-constellation-36) (std::vector&lt; [**Plane**](classastrea_1_1astro_1_1Plane.md)&lt; Spacecraft\_T &gt; &gt; planes) <br>_Construct a_ [_**Constellation**_](classastrea_1_1astro_1_1Constellation.md) _from a vector of Planes._ |
|   | [**Constellation**](#function-constellation-46) (std::vector&lt; Spacecraft\_T &gt; satellites) <br>_Construct a_ [_**Constellation**_](classastrea_1_1astro_1_1Constellation.md) _from a vector of_[_**Spacecraft**_](classastrea_1_1astro_1_1Spacecraft.md) _._ |
|   | [**Constellation**](#function-constellation-56) (const std::vector&lt; [**GeneralPerturbations**](structastrea_1_1astro_1_1GeneralPerturbations.md) &gt; & gp) <br>_Construct a_ [_**Constellation**_](classastrea_1_1astro_1_1Constellation.md) _from a vector of_[_**GeneralPerturbations**_](structastrea_1_1astro_1_1GeneralPerturbations.md) _objects._ |
|   | [**Constellation**](#function-constellation-66) (const [**Date**](classastrea_1_1astro_1_1Date.md) & epoch, const Distance & semimajor, const Angle & inclination, const std::size\_t & T, const std::size\_t & P, const Unitless & F, const Angle & anchorRAAN=0.0 \*mp\_units::si::unit\_symbols::rad, const Angle & anchorAnomaly=0.0 \*mp\_units::si::unit\_symbols::rad) <br>_Construct a_ [_**Constellation**_](classastrea_1_1astro_1_1Constellation.md) _with a specific configuration._ |
|  void | [**add\_plane**](#function-add_plane-12) (const [**Plane**](classastrea_1_1astro_1_1Plane.md)&lt; Spacecraft\_T &gt; & plane, const std::size\_t & shellId) <br>_Add a_ [_**Plane**_](classastrea_1_1astro_1_1Plane.md) _to the_[_**Constellation**_](classastrea_1_1astro_1_1Constellation.md) _with a specific shell ID._ |
|  void | [**add\_plane**](#function-add_plane-22) (const [**Plane**](classastrea_1_1astro_1_1Plane.md)&lt; Spacecraft\_T &gt; & plane) <br>_Add a_ [_**Plane**_](classastrea_1_1astro_1_1Plane.md) _to the_[_**Constellation**_](classastrea_1_1astro_1_1Constellation.md) _without specifying a shell ID._ |
|  void | [**add\_shell**](#function-add_shell) (const [**Shell**](classastrea_1_1astro_1_1Shell.md)&lt; Spacecraft\_T &gt; & shell) <br>_Add a_ [_**Shell**_](classastrea_1_1astro_1_1Shell.md) _to the_[_**Constellation**_](classastrea_1_1astro_1_1Constellation.md) _._ |
|  void | [**add\_spacecraft**](#function-add_spacecraft-12) (const Spacecraft\_T & spacecraft, const std::size\_t & planeId) <br>_Add a_ [_**Spacecraft**_](classastrea_1_1astro_1_1Spacecraft.md) _to a specific_[_**Plane**_](classastrea_1_1astro_1_1Plane.md) _in the_[_**Constellation**_](classastrea_1_1astro_1_1Constellation.md) _._ |
|  void | [**add\_spacecraft**](#function-add_spacecraft-22) (const Spacecraft\_T & spacecraft) <br>_Add a_ [_**Spacecraft**_](classastrea_1_1astro_1_1Spacecraft.md) _to the_[_**Constellation**_](classastrea_1_1astro_1_1Constellation.md) _without specifying a_[_**Plane**_](classastrea_1_1astro_1_1Plane.md) _ID._ |
|  [**iterator**](classastrea_1_1astro_1_1Constellation.md#typedef-iterator) | [**begin**](#function-begin-12) () <br>_Get an iterator to the beginning of the_ [_**Constellation**_](classastrea_1_1astro_1_1Constellation.md) _._ |
|  [**const\_iterator**](classastrea_1_1astro_1_1Constellation.md#typedef-const_iterator) | [**begin**](#function-begin-22) () const<br>_Get a const iterator to the beginning of the_ [_**Constellation**_](classastrea_1_1astro_1_1Constellation.md) _._ |
|  [**const\_iterator**](classastrea_1_1astro_1_1Constellation.md#typedef-const_iterator) | [**cbegin**](#function-cbegin) () const<br>_Get a const iterator to the beginning of the_ [_**Constellation**_](classastrea_1_1astro_1_1Constellation.md) _._ |
|  [**const\_iterator**](classastrea_1_1astro_1_1Constellation.md#typedef-const_iterator) | [**cend**](#function-cend) () const<br>_Get a const iterator to the end of the_ [_**Constellation**_](classastrea_1_1astro_1_1Constellation.md) _._ |
|  [**iterator**](classastrea_1_1astro_1_1Constellation.md#typedef-iterator) | [**end**](#function-end-12) () <br>_Get an iterator to the end of the_ [_**Constellation**_](classastrea_1_1astro_1_1Constellation.md) _._ |
|  [**const\_iterator**](classastrea_1_1astro_1_1Constellation.md#typedef-const_iterator) | [**end**](#function-end-22) () const<br>_Get a const iterator to the end of the_ [_**Constellation**_](classastrea_1_1astro_1_1Constellation.md) _._ |
|  const std::vector&lt; Spacecraft\_T &gt; | [**get\_all\_spacecraft**](#function-get_all_spacecraft) () const<br>_Get all_ [_**Spacecraft**_](classastrea_1_1astro_1_1Spacecraft.md) _in the_[_**Constellation**_](classastrea_1_1astro_1_1Constellation.md) _._ |
|  const [**Plane**](classastrea_1_1astro_1_1Plane.md)&lt; Spacecraft\_T &gt; & | [**get\_plane**](#function-get_plane) (const std::size\_t & planeId) const<br>_Get a specific_ [_**Plane**_](classastrea_1_1astro_1_1Plane.md) _by its ID._ |
|  const std::vector&lt; [**Plane**](classastrea_1_1astro_1_1Plane.md)&lt; Spacecraft\_T &gt; &gt; | [**get\_planes**](#function-get_planes) () const<br>_Get all Planes in the_ [_**Constellation**_](classastrea_1_1astro_1_1Constellation.md) _._ |
|  const [**Shell**](classastrea_1_1astro_1_1Shell.md)&lt; Spacecraft\_T &gt; & | [**get\_shell**](#function-get_shell) (const std::size\_t & shellId) const<br>_Get a specific_ [_**Shell**_](classastrea_1_1astro_1_1Shell.md) _by its ID._ |
|  std::vector&lt; [**Shell**](classastrea_1_1astro_1_1Shell.md)&lt; Spacecraft\_T &gt; &gt; & | [**get\_shells**](#function-get_shells-12) () <br>_Get all Shells in the_ [_**Constellation**_](classastrea_1_1astro_1_1Constellation.md) _._ |
|  const std::vector&lt; [**Shell**](classastrea_1_1astro_1_1Shell.md)&lt; Spacecraft\_T &gt; &gt; & | [**get\_shells**](#function-get_shells-22) () const<br>_Get all Shells in the_ [_**Constellation**_](classastrea_1_1astro_1_1Constellation.md) _._ |
|  const Spacecraft\_T & | [**get\_spacecraft**](#function-get_spacecraft) (const std::size\_t & spacecraftId) const<br>_Get a specific_ [_**Spacecraft**_](classastrea_1_1astro_1_1Spacecraft.md) _by its ID._ |
|  const std::size\_t | [**n\_planes**](#function-n_planes) () const<br>_Get the number of planes in the_ [_**Constellation**_](classastrea_1_1astro_1_1Constellation.md) _._ |
|  const std::size\_t | [**n\_shells**](#function-n_shells) () const<br>_Get the number of shells in the_ [_**Constellation**_](classastrea_1_1astro_1_1Constellation.md) _._ |
|  Spacecraft\_T & | [**operator[]**](#function-operator) (const std::size\_t idx) <br>_Access the_ [_**Spacecraft**_](classastrea_1_1astro_1_1Spacecraft.md) _at a specific index in the_[_**Constellation**_](classastrea_1_1astro_1_1Constellation.md) _._ |
|  const Spacecraft\_T & | [**operator[]**](#function-operator_1) (const std::size\_t idx) const<br>_Access the_ [_**Spacecraft**_](classastrea_1_1astro_1_1Spacecraft.md) _at a specific index in the_[_**Constellation**_](classastrea_1_1astro_1_1Constellation.md) _._ |
|  void | [**propagate**](#function-propagate-12) (const Time & propTime, [**Integrator**](classastrea_1_1astro_1_1Integrator.md) & integrator) <br>_Propagate the_ [_**Constellation**_](classastrea_1_1astro_1_1Constellation.md) _using the provided epoch, Equations of Motion, and_[_**Integrator**_](classastrea_1_1astro_1_1Integrator.md) _._ |
|  void | [**propagate**](#function-propagate-22) (const [**Date**](classastrea_1_1astro_1_1Date.md) & endEpoch, [**Integrator**](classastrea_1_1astro_1_1Integrator.md) & integrator) <br>_Propagate the_ [_**Constellation**_](classastrea_1_1astro_1_1Constellation.md) _using the provided epoch, Equations of Motion, and_[_**Integrator**_](classastrea_1_1astro_1_1Integrator.md) _._ |
|  const std::size\_t | [**size**](#function-size) () const<br>_Get the size of the_ [_**Constellation**_](classastrea_1_1astro_1_1Constellation.md) _._ |
|   | [**~Constellation**](#function-constellation) () = default<br>_Default destructor for_ [_**Constellation**_](classastrea_1_1astro_1_1Constellation.md) _._ |




























## Detailed Description




**Template parameters:**


* `Spacecraft_T` The type of [**Spacecraft**](classastrea_1_1astro_1_1Spacecraft.md) that this [**Constellation**](classastrea_1_1astro_1_1Constellation.md) will contain. Must be derived from [**Spacecraft**](classastrea_1_1astro_1_1Spacecraft.md).
  * 





**Note:**

: Defaults to [**Spacecraft**](classastrea_1_1astro_1_1Spacecraft.md), but can be any class that inherits from [**Spacecraft**](classastrea_1_1astro_1_1Spacecraft.md). 





    
## Public Types Documentation




### typedef const\_iterator 

_Const iterator for iterating over all_ [_**Spacecraft**_](classastrea_1_1astro_1_1Spacecraft.md) _in the_[_**Constellation**_](classastrea_1_1astro_1_1Constellation.md) _._
```C++
using astrea::astro::Constellation< Spacecraft_T >::const_iterator =  const sat_iterator;
```



This const iterator allows iteration over all [**Spacecraft**](classastrea_1_1astro_1_1Spacecraft.md) in the [**Constellation**](classastrea_1_1astro_1_1Constellation.md), regardless of their [**Shell**](classastrea_1_1astro_1_1Shell.md) or [**Plane**](classastrea_1_1astro_1_1Plane.md). 


        

<hr>



### typedef iterator 

_Iterator for iterating over all_ [_**Spacecraft**_](classastrea_1_1astro_1_1Spacecraft.md) _in the_[_**Constellation**_](classastrea_1_1astro_1_1Constellation.md) _._
```C++
using astrea::astro::Constellation< Spacecraft_T >::iterator =  sat_iterator;
```



This iterator allows iteration over all [**Spacecraft**](classastrea_1_1astro_1_1Spacecraft.md) in the [**Constellation**](classastrea_1_1astro_1_1Constellation.md), regardless of their [**Shell**](classastrea_1_1astro_1_1Shell.md) or [**Plane**](classastrea_1_1astro_1_1Plane.md). 


        

<hr>
## Public Functions Documentation




### function Constellation [1/6]

_Default constructor for_ [_**Constellation**_](classastrea_1_1astro_1_1Constellation.md) _._
```C++
inline astrea::astro::Constellation::Constellation () 
```




<hr>



### function Constellation [2/6]

_Construct a_ [_**Constellation**_](classastrea_1_1astro_1_1Constellation.md) _from a vector of Shells._
```C++
astrea::astro::Constellation::Constellation (
    std::vector< Shell < Spacecraft_T > > shells
) 
```





**Parameters:**


* `shells` A vector of Shells to initialize the [**Constellation**](classastrea_1_1astro_1_1Constellation.md). 




        

<hr>



### function Constellation [3/6]

_Construct a_ [_**Constellation**_](classastrea_1_1astro_1_1Constellation.md) _from a vector of Planes._
```C++
astrea::astro::Constellation::Constellation (
    std::vector< Plane < Spacecraft_T > > planes
) 
```





**Parameters:**


* `planes` A vector of Planes to initialize the [**Constellation**](classastrea_1_1astro_1_1Constellation.md). 




        

<hr>



### function Constellation [4/6]

_Construct a_ [_**Constellation**_](classastrea_1_1astro_1_1Constellation.md) _from a vector of_[_**Spacecraft**_](classastrea_1_1astro_1_1Spacecraft.md) _._
```C++
astrea::astro::Constellation::Constellation (
    std::vector< Spacecraft_T > satellites
) 
```





**Parameters:**


* `satellites` A vector of [**Spacecraft**](classastrea_1_1astro_1_1Spacecraft.md) to initialize the [**Constellation**](classastrea_1_1astro_1_1Constellation.md). 




        

<hr>



### function Constellation [5/6]

_Construct a_ [_**Constellation**_](classastrea_1_1astro_1_1Constellation.md) _from a vector of_[_**GeneralPerturbations**_](structastrea_1_1astro_1_1GeneralPerturbations.md) _objects._
```C++
astrea::astro::Constellation::Constellation (
    const std::vector< GeneralPerturbations > & gp
) 
```





**Parameters:**


* `gp` A vector of [**GeneralPerturbations**](structastrea_1_1astro_1_1GeneralPerturbations.md) objects to initialize the [**Constellation**](classastrea_1_1astro_1_1Constellation.md). 




        

<hr>



### function Constellation [6/6]

_Construct a_ [_**Constellation**_](classastrea_1_1astro_1_1Constellation.md) _with a specific configuration._
```C++
astrea::astro::Constellation::Constellation (
    const Date & epoch,
    const Distance & semimajor,
    const Angle & inclination,
    const std::size_t & T,
    const std::size_t & P,
    const Unitless & F,
    const Angle & anchorRAAN=0.0 *mp_units::si::unit_symbols::rad,
    const Angle & anchorAnomaly=0.0 *mp_units::si::unit_symbols::rad
) 
```





**Parameters:**


* `epoch` The epoch of the [**Constellation**](classastrea_1_1astro_1_1Constellation.md). 
* `semimajor` The semimajor axis of the orbit. 
* `inclination` The inclination of the orbit. 
* `T` The number of shells in the [**Constellation**](classastrea_1_1astro_1_1Constellation.md). 
* `P` The number of planes in each shell. 
* `F` The number of spacecraft in each plane. 
* `anchorRAAN` The right ascension of ascending node (RAAN) for the first shell. 
* `anchorAnomaly` The argument of perigee for the first shell. 




        

<hr>



### function add\_plane [1/2]

_Add a_ [_**Plane**_](classastrea_1_1astro_1_1Plane.md) _to the_[_**Constellation**_](classastrea_1_1astro_1_1Constellation.md) _with a specific shell ID._
```C++
void astrea::astro::Constellation::add_plane (
    const Plane < Spacecraft_T > & plane,
    const std::size_t & shellId
) 
```





**Parameters:**


* `plane` The [**Plane**](classastrea_1_1astro_1_1Plane.md) to add to the [**Constellation**](classastrea_1_1astro_1_1Constellation.md). 
* `shellId` The ID of the shell to which the [**Plane**](classastrea_1_1astro_1_1Plane.md) belongs. 




        

<hr>



### function add\_plane [2/2]

_Add a_ [_**Plane**_](classastrea_1_1astro_1_1Plane.md) _to the_[_**Constellation**_](classastrea_1_1astro_1_1Constellation.md) _without specifying a shell ID._
```C++
void astrea::astro::Constellation::add_plane (
    const Plane < Spacecraft_T > & plane
) 
```





**Parameters:**


* `plane` The [**Plane**](classastrea_1_1astro_1_1Plane.md) to add to the [**Constellation**](classastrea_1_1astro_1_1Constellation.md). 




        

<hr>



### function add\_shell 

_Add a_ [_**Shell**_](classastrea_1_1astro_1_1Shell.md) _to the_[_**Constellation**_](classastrea_1_1astro_1_1Constellation.md) _._
```C++
void astrea::astro::Constellation::add_shell (
    const Shell < Spacecraft_T > & shell
) 
```





**Parameters:**


* `shell` The [**Shell**](classastrea_1_1astro_1_1Shell.md) to add to the [**Constellation**](classastrea_1_1astro_1_1Constellation.md). 




        

<hr>



### function add\_spacecraft [1/2]

_Add a_ [_**Spacecraft**_](classastrea_1_1astro_1_1Spacecraft.md) _to a specific_[_**Plane**_](classastrea_1_1astro_1_1Plane.md) _in the_[_**Constellation**_](classastrea_1_1astro_1_1Constellation.md) _._
```C++
void astrea::astro::Constellation::add_spacecraft (
    const Spacecraft_T & spacecraft,
    const std::size_t & planeId
) 
```





**Parameters:**


* `spacecraft` The [**Spacecraft**](classastrea_1_1astro_1_1Spacecraft.md) to add to the [**Constellation**](classastrea_1_1astro_1_1Constellation.md). 
* `planeId` The ID of the [**Plane**](classastrea_1_1astro_1_1Plane.md) to which the [**Spacecraft**](classastrea_1_1astro_1_1Spacecraft.md) belongs. 




        

<hr>



### function add\_spacecraft [2/2]

_Add a_ [_**Spacecraft**_](classastrea_1_1astro_1_1Spacecraft.md) _to the_[_**Constellation**_](classastrea_1_1astro_1_1Constellation.md) _without specifying a_[_**Plane**_](classastrea_1_1astro_1_1Plane.md) _ID._
```C++
void astrea::astro::Constellation::add_spacecraft (
    const Spacecraft_T & spacecraft
) 
```





**Parameters:**


* `spacecraft` The [**Spacecraft**](classastrea_1_1astro_1_1Spacecraft.md) to add to the [**Constellation**](classastrea_1_1astro_1_1Constellation.md). 




        

<hr>



### function begin [1/2]

_Get an iterator to the beginning of the_ [_**Constellation**_](classastrea_1_1astro_1_1Constellation.md) _._
```C++
inline iterator astrea::astro::Constellation::begin () 
```





**Returns:**

iterator An iterator pointing to the first [**Spacecraft**](classastrea_1_1astro_1_1Spacecraft.md) in the [**Constellation**](classastrea_1_1astro_1_1Constellation.md). 





        

<hr>



### function begin [2/2]

_Get a const iterator to the beginning of the_ [_**Constellation**_](classastrea_1_1astro_1_1Constellation.md) _._
```C++
inline const_iterator astrea::astro::Constellation::begin () const
```





**Returns:**

const\_iterator A const iterator pointing to the first [**Spacecraft**](classastrea_1_1astro_1_1Spacecraft.md) in the [**Constellation**](classastrea_1_1astro_1_1Constellation.md). 





        

<hr>



### function cbegin 

_Get a const iterator to the beginning of the_ [_**Constellation**_](classastrea_1_1astro_1_1Constellation.md) _._
```C++
inline const_iterator astrea::astro::Constellation::cbegin () const
```





**Returns:**

const\_iterator A const iterator pointing to the first [**Spacecraft**](classastrea_1_1astro_1_1Spacecraft.md) in the [**Constellation**](classastrea_1_1astro_1_1Constellation.md). 





        

<hr>



### function cend 

_Get a const iterator to the end of the_ [_**Constellation**_](classastrea_1_1astro_1_1Constellation.md) _._
```C++
inline const_iterator astrea::astro::Constellation::cend () const
```





**Returns:**

const\_iterator A const iterator pointing to one past the last [**Spacecraft**](classastrea_1_1astro_1_1Spacecraft.md) in the [**Constellation**](classastrea_1_1astro_1_1Constellation.md). 





        

<hr>



### function end [1/2]

_Get an iterator to the end of the_ [_**Constellation**_](classastrea_1_1astro_1_1Constellation.md) _._
```C++
inline iterator astrea::astro::Constellation::end () 
```





**Returns:**

iterator An iterator pointing to one past the last [**Spacecraft**](classastrea_1_1astro_1_1Spacecraft.md) in the [**Constellation**](classastrea_1_1astro_1_1Constellation.md). 





        

<hr>



### function end [2/2]

_Get a const iterator to the end of the_ [_**Constellation**_](classastrea_1_1astro_1_1Constellation.md) _._
```C++
inline const_iterator astrea::astro::Constellation::end () const
```





**Returns:**

const\_iterator A const iterator pointing to one past the last [**Spacecraft**](classastrea_1_1astro_1_1Spacecraft.md) in the [**Constellation**](classastrea_1_1astro_1_1Constellation.md). 





        

<hr>



### function get\_all\_spacecraft 

_Get all_ [_**Spacecraft**_](classastrea_1_1astro_1_1Spacecraft.md) _in the_[_**Constellation**_](classastrea_1_1astro_1_1Constellation.md) _._
```C++
const std::vector< Spacecraft_T > astrea::astro::Constellation::get_all_spacecraft () const
```





**Returns:**

std::vector&lt;Spacecraft\_T&gt; A vector of all [**Spacecraft**](classastrea_1_1astro_1_1Spacecraft.md) in the [**Constellation**](classastrea_1_1astro_1_1Constellation.md). 





        

<hr>



### function get\_plane 

_Get a specific_ [_**Plane**_](classastrea_1_1astro_1_1Plane.md) _by its ID._
```C++
const Plane < Spacecraft_T > & astrea::astro::Constellation::get_plane (
    const std::size_t & planeId
) const
```





**Parameters:**


* `planeId` The ID of the [**Plane**](classastrea_1_1astro_1_1Plane.md) to retrieve. 



**Returns:**

const [**Plane&lt;Spacecraft\_T&gt;**](classastrea_1_1astro_1_1Plane.md)& A const reference to the [**Plane**](classastrea_1_1astro_1_1Plane.md) with the specified ID. 





        

<hr>



### function get\_planes 

_Get all Planes in the_ [_**Constellation**_](classastrea_1_1astro_1_1Constellation.md) _._
```C++
const std::vector< Plane < Spacecraft_T > > astrea::astro::Constellation::get_planes () const
```





**Returns:**

std::vector&lt;Plane&lt;Spacecraft\_T&gt;&gt;& A reference to the vector of Planes in the [**Constellation**](classastrea_1_1astro_1_1Constellation.md). 





        

<hr>



### function get\_shell 

_Get a specific_ [_**Shell**_](classastrea_1_1astro_1_1Shell.md) _by its ID._
```C++
const Shell < Spacecraft_T > & astrea::astro::Constellation::get_shell (
    const std::size_t & shellId
) const
```





**Parameters:**


* `shellId` The ID of the [**Shell**](classastrea_1_1astro_1_1Shell.md) to retrieve. 



**Returns:**

const [**Shell&lt;Spacecraft\_T&gt;**](classastrea_1_1astro_1_1Shell.md)& A const reference to the [**Shell**](classastrea_1_1astro_1_1Shell.md) with the specified ID. 





        

<hr>



### function get\_shells [1/2]

_Get all Shells in the_ [_**Constellation**_](classastrea_1_1astro_1_1Constellation.md) _._
```C++
std::vector< Shell < Spacecraft_T > > & astrea::astro::Constellation::get_shells () 
```





**Returns:**

std::vector&lt;Shell&lt;Spacecraft\_T&gt;&gt;& A reference to the vector of Shells in the [**Constellation**](classastrea_1_1astro_1_1Constellation.md). 





        

<hr>



### function get\_shells [2/2]

_Get all Shells in the_ [_**Constellation**_](classastrea_1_1astro_1_1Constellation.md) _._
```C++
const std::vector< Shell < Spacecraft_T > > & astrea::astro::Constellation::get_shells () const
```





**Returns:**

const std::vector&lt;Shell&lt;Spacecraft\_T&gt;&gt;& A const reference to the vector of Shells in the [**Constellation**](classastrea_1_1astro_1_1Constellation.md). 





        

<hr>



### function get\_spacecraft 

_Get a specific_ [_**Spacecraft**_](classastrea_1_1astro_1_1Spacecraft.md) _by its ID._
```C++
const Spacecraft_T & astrea::astro::Constellation::get_spacecraft (
    const std::size_t & spacecraftId
) const
```





**Parameters:**


* `spacecraftId` The ID of the [**Spacecraft**](classastrea_1_1astro_1_1Spacecraft.md) to retrieve. 



**Returns:**

const Spacecraft\_T& A const reference to the [**Spacecraft**](classastrea_1_1astro_1_1Spacecraft.md) with the specified ID. 





        

<hr>



### function n\_planes 

_Get the number of planes in the_ [_**Constellation**_](classastrea_1_1astro_1_1Constellation.md) _._
```C++
const std::size_t astrea::astro::Constellation::n_planes () const
```





**Returns:**

const std::size\_t The number of planes in the [**Constellation**](classastrea_1_1astro_1_1Constellation.md). 





        

<hr>



### function n\_shells 

_Get the number of shells in the_ [_**Constellation**_](classastrea_1_1astro_1_1Constellation.md) _._
```C++
const std::size_t astrea::astro::Constellation::n_shells () const
```





**Returns:**

const std::size\_t The number of shells in the [**Constellation**](classastrea_1_1astro_1_1Constellation.md). 





        

<hr>



### function operator[] 

_Access the_ [_**Spacecraft**_](classastrea_1_1astro_1_1Spacecraft.md) _at a specific index in the_[_**Constellation**_](classastrea_1_1astro_1_1Constellation.md) _._
```C++
Spacecraft_T & astrea::astro::Constellation::operator[] (
    const std::size_t idx
) 
```





**Parameters:**


* `idx` The index of the [**Spacecraft**](classastrea_1_1astro_1_1Spacecraft.md) to access. 



**Returns:**

Spacecraft\_T& A reference to the [**Spacecraft**](classastrea_1_1astro_1_1Spacecraft.md) at the specified index. 





        

<hr>



### function operator[] 

_Access the_ [_**Spacecraft**_](classastrea_1_1astro_1_1Spacecraft.md) _at a specific index in the_[_**Constellation**_](classastrea_1_1astro_1_1Constellation.md) _._
```C++
const Spacecraft_T & astrea::astro::Constellation::operator[] (
    const std::size_t idx
) const
```





**Parameters:**


* `idx` The index of the [**Spacecraft**](classastrea_1_1astro_1_1Spacecraft.md) to access. 



**Returns:**

const Spacecraft\_T& A const reference to the [**Spacecraft**](classastrea_1_1astro_1_1Spacecraft.md) at the specified index. 





        

<hr>



### function propagate [1/2]

_Propagate the_ [_**Constellation**_](classastrea_1_1astro_1_1Constellation.md) _using the provided epoch, Equations of Motion, and_[_**Integrator**_](classastrea_1_1astro_1_1Integrator.md) _._
```C++
void astrea::astro::Constellation::propagate (
    const Time & propTime,
    Integrator & integrator
) 
```





**Parameters:**


* `propTime` The total propagation time after the initial state epoch. 
* `integrator` The [**Integrator**](classastrea_1_1astro_1_1Integrator.md) to use for propagation. 




        

<hr>



### function propagate [2/2]

_Propagate the_ [_**Constellation**_](classastrea_1_1astro_1_1Constellation.md) _using the provided epoch, Equations of Motion, and_[_**Integrator**_](classastrea_1_1astro_1_1Integrator.md) _._
```C++
void astrea::astro::Constellation::propagate (
    const Date & endEpoch,
    Integrator & integrator
) 
```





**Parameters:**


* `endEpoch` The total propagation time after the initial state epoch. 
* `integrator` The [**Integrator**](classastrea_1_1astro_1_1Integrator.md) to use for propagation. 




        

<hr>



### function size 

_Get the size of the_ [_**Constellation**_](classastrea_1_1astro_1_1Constellation.md) _._
```C++
const std::size_t astrea::astro::Constellation::size () const
```





**Returns:**

const std::size\_t The number of [**Spacecraft**](classastrea_1_1astro_1_1Spacecraft.md) in the [**Constellation**](classastrea_1_1astro_1_1Constellation.md). 





        

<hr>



### function ~Constellation 

_Default destructor for_ [_**Constellation**_](classastrea_1_1astro_1_1Constellation.md) _._
```C++
astrea::astro::Constellation::~Constellation () = default
```




<hr>

------------------------------
The documentation for this class was generated from the following file `astrea/astro/astro/platforms/space/Constellation.hpp`

