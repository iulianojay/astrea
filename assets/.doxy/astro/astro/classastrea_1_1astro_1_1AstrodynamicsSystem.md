

# Class astrea::astro::AstrodynamicsSystem



[**ClassList**](annotated.md) **>** [**astrea**](namespaceastrea.md) **>** [**astro**](namespaceastrea_1_1astro.md) **>** [**AstrodynamicsSystem**](classastrea_1_1astro_1_1AstrodynamicsSystem.md)



_Represents a system of celestial bodies and their interactions._ [More...](#detailed-description)

* `#include <AstrodynamicsSystem.hpp>`

















## Public Types

| Type | Name |
| ---: | :--- |
| typedef std::unordered\_map&lt; [**CelestialBodyId**](namespaceastrea_1_1astro.md#enum-celestialbodyid), [**CelestialBodyUniquePtr**](namespaceastrea_1_1astro.md#typedef-celestialbodyuniqueptr) &gt;::[**const\_iterator**](classastrea_1_1astro_1_1AstrodynamicsSystem.md#typedef-const_iterator) | [**const\_iterator**](#typedef-const_iterator)  <br>_Constant iterator type for iterating over celestial bodies._  |
| typedef std::unordered\_map&lt; [**CelestialBodyId**](namespaceastrea_1_1astro.md#enum-celestialbodyid), [**CelestialBodyUniquePtr**](namespaceastrea_1_1astro.md#typedef-celestialbodyuniqueptr) &gt;::[**iterator**](classastrea_1_1astro_1_1AstrodynamicsSystem.md#typedef-iterator) | [**iterator**](#typedef-iterator)  <br>_Iterator type for iterating over celestial bodies._  |




















## Public Functions

| Type | Name |
| ---: | :--- |
|  constexpr | [**AstrodynamicsSystem**](#function-astrodynamicssystem-15) (const [**CelestialBodyId**](namespaceastrea_1_1astro.md#enum-celestialbodyid) & centralBody=CelestialBodyId::EARTH, const std::unordered\_set&lt; [**CelestialBodyId**](namespaceastrea_1_1astro.md#enum-celestialbodyid) &gt; & secondaryBodies={}) <br>_Constructs an_ [_**AstrodynamicsSystem**_](classastrea_1_1astro_1_1AstrodynamicsSystem.md) _with a specified central body, and the set of all other bodies._ |
|  constexpr | [**AstrodynamicsSystem**](#function-astrodynamicssystem-25) (const [**CelestialBody**](classastrea_1_1astro_1_1CelestialBody.md) & centralBody, const std::unordered\_set&lt; [**CelestialBodyId**](namespaceastrea_1_1astro.md#enum-celestialbodyid) &gt; & secondaryBodies={}) <br>_Constructs an_ [_**AstrodynamicsSystem**_](classastrea_1_1astro_1_1AstrodynamicsSystem.md) _with a specified central body, and the set of all other bodies._ |
|  constexpr | [**AstrodynamicsSystem**](#function-astrodynamicssystem-35) (const [**CelestialBody**](classastrea_1_1astro_1_1CelestialBody.md) & centralBody, const std::unordered\_set&lt; [**CelestialBody**](classastrea_1_1astro_1_1CelestialBody.md) &gt; & secondaryBodies={}) <br>_Constructs an_ [_**AstrodynamicsSystem**_](classastrea_1_1astro_1_1AstrodynamicsSystem.md) _with a specified central body, and the set of all other bodies._ |
|   | [**AstrodynamicsSystem**](#function-astrodynamicssystem-45) (const [**AstrodynamicsSystem**](classastrea_1_1astro_1_1AstrodynamicsSystem.md) &) = delete<br>_Deleted copy constructor for the_ [_**AstrodynamicsSystem**_](classastrea_1_1astro_1_1AstrodynamicsSystem.md) _class._ |
|   | [**AstrodynamicsSystem**](#function-astrodynamicssystem-55) ([**AstrodynamicsSystem**](classastrea_1_1astro_1_1AstrodynamicsSystem.md) &&) = default<br>_Default move constructor for the_ [_**AstrodynamicsSystem**_](classastrea_1_1astro_1_1AstrodynamicsSystem.md) _class._ |
|  constexpr const [**CelestialBodyUniquePtr**](namespaceastrea_1_1astro.md#typedef-celestialbodyuniqueptr) & | [**add\_body**](#function-add_body-13) (const [**CelestialBodyId**](namespaceastrea_1_1astro.md#enum-celestialbodyid) & id) <br>_Create a celestial body by id._  |
|  constexpr const [**CelestialBodyUniquePtr**](namespaceastrea_1_1astro.md#typedef-celestialbodyuniqueptr) & | [**add\_body**](#function-add_body-23) (const [**CelestialBody**](classastrea_1_1astro_1_1CelestialBody.md) & body) <br>_Store manually generated celestial body._  |
|  constexpr [**CelestialBodyUniquePtr**](namespaceastrea_1_1astro.md#typedef-celestialbodyuniqueptr) | [**add\_body**](#function-add_body-33) (const [**CelestialBodyId**](namespaceastrea_1_1astro.md#enum-celestialbodyid) & id) const<br>_Create a celestial body by id (const version)._  |
|  constexpr auto | [**begin**](#function-begin) () const<br>_Returns an iterator to the beginning of the celestial bodies._  |
|  constexpr void | [**clear**](#function-clear) () <br>_Clears all celestial bodies managed by this factory._  |
|  constexpr auto | [**end**](#function-end) () const<br>_Returns an iterator to the end of the celestial bodies._  |
|  constexpr const auto & | [**get\_all\_bodies**](#function-get_all_bodies) () const<br>_Returns a vector of all celestial bodies in the system._  |
|  constexpr const [**CelestialBodyUniquePtr**](namespaceastrea_1_1astro.md#typedef-celestialbodyuniqueptr) & | [**get\_body**](#function-get_body) (const [**CelestialBodyId**](namespaceastrea_1_1astro.md#enum-celestialbodyid) & id) const<br>_Return a specific celestial body by ID._  |
|  constexpr const [**SystemCenter**](namespaceastrea_1_1astro.md#enum-systemcenter) & | [**get\_center\_type**](#function-get_center_type) () const<br>_Returns the central celestial body of the system._  |
|  constexpr const [**CelestialBodyUniquePtr**](namespaceastrea_1_1astro.md#typedef-celestialbodyuniqueptr) & | [**get\_central\_body**](#function-get_central_body) () const<br>_Returns the central celestial body as a CelestialBodyUniquePtr._  |
|  constexpr const [**CelestialBodyId**](namespaceastrea_1_1astro.md#enum-celestialbodyid) & | [**get\_central\_body\_id**](#function-get_central_body_id) () const<br>_Returns the central celestial body ID._  |
|  constexpr GravParam | [**get\_mu**](#function-get_mu) () const<br>_Get the gravitational parameter (mu) of the central body._  |
|  [**CartesianVector**](classastrea_1_1astro_1_1CartesianVector.md)&lt; Distance, frames::solar\_system\_barycenter::icrf &gt; | [**get\_relative\_position**](#function-get_relative_position) (const [**Date**](classastrea_1_1astro_1_1Date.md) & date, const [**CelestialBodyId**](namespaceastrea_1_1astro.md#enum-celestialbodyid) id1, const [**CelestialBodyId**](namespaceastrea_1_1astro.md#enum-celestialbodyid) id2) const<br>_Get the relative position between two celestial bodies at a specific date._  |
|  constexpr const [**CelestialBodyId**](namespaceastrea_1_1astro.md#enum-celestialbodyid) & | [**get\_system\_root**](#function-get_system_root) () const<br>_Get the root object of the celestial body hierarchy._  |
|  [**AstrodynamicsSystem**](classastrea_1_1astro_1_1AstrodynamicsSystem.md) & | [**operator=**](#function-operator) (const [**AstrodynamicsSystem**](classastrea_1_1astro_1_1AstrodynamicsSystem.md) &) = delete<br>_Deleted assignment operator for the_ [_**AstrodynamicsSystem**_](classastrea_1_1astro_1_1AstrodynamicsSystem.md) _class._ |
|  [**AstrodynamicsSystem**](classastrea_1_1astro_1_1AstrodynamicsSystem.md) & | [**operator=**](#function-operator_1) ([**AstrodynamicsSystem**](classastrea_1_1astro_1_1AstrodynamicsSystem.md) &&) = default<br>_Default move assignment operator for the_ [_**AstrodynamicsSystem**_](classastrea_1_1astro_1_1AstrodynamicsSystem.md) _class._ |
|   | [**requires**](#function-requires) (std::is\_base\_of&lt; [**CelestialBody**](classastrea_1_1astro_1_1CelestialBody.md), T &gt;::value) const<br>_Creates a celestial body of a specific type._  |
|  constexpr const std::size\_t | [**size**](#function-size) () const<br>_Returns the number of celestial bodies managed by this factory._  |
|   | [**~AstrodynamicsSystem**](#function-astrodynamicssystem) () = default<br>_Default destructor for the_ [_**AstrodynamicsSystem**_](classastrea_1_1astro_1_1AstrodynamicsSystem.md) _class._ |


## Public Static Functions

| Type | Name |
| ---: | :--- |
|  constexpr [**AstrodynamicsSystem**](classastrea_1_1astro_1_1AstrodynamicsSystem.md) | [**EarthMoon**](#function-earthmoon) () <br>_Creates a default_ [_**AstrodynamicsSystem**_](classastrea_1_1astro_1_1AstrodynamicsSystem.md) _._ |


























## Detailed Description


This class manages celestial bodies, their properties, and provides methods to access them. 


    
## Public Types Documentation




### typedef const\_iterator 

_Constant iterator type for iterating over celestial bodies._ 
```C++
using astrea::astro::AstrodynamicsSystem::const_iterator =  std::unordered_map<CelestialBodyId, CelestialBodyUniquePtr>::const_iterator;
```




<hr>



### typedef iterator 

_Iterator type for iterating over celestial bodies._ 
```C++
using astrea::astro::AstrodynamicsSystem::iterator =  std::unordered_map<CelestialBodyId, CelestialBodyUniquePtr>::iterator;
```




<hr>
## Public Functions Documentation




### function AstrodynamicsSystem [1/5]

_Constructs an_ [_**AstrodynamicsSystem**_](classastrea_1_1astro_1_1AstrodynamicsSystem.md) _with a specified central body, and the set of all other bodies._
```C++
inline constexpr astrea::astro::AstrodynamicsSystem::AstrodynamicsSystem (
    const CelestialBodyId & centralBody=CelestialBodyId::EARTH,
    const std::unordered_set< CelestialBodyId > & secondaryBodies={}
) 
```





**Parameters:**


* `centralBody` The name of the central celestial body (default is "Earth"). 
* `allBodies` A set of names of all secondary celestial bodies in the system (default is none). 




        

<hr>



### function AstrodynamicsSystem [2/5]

_Constructs an_ [_**AstrodynamicsSystem**_](classastrea_1_1astro_1_1AstrodynamicsSystem.md) _with a specified central body, and the set of all other bodies._
```C++
inline constexpr astrea::astro::AstrodynamicsSystem::AstrodynamicsSystem (
    const CelestialBody & centralBody,
    const std::unordered_set< CelestialBodyId > & secondaryBodies={}
) 
```





**Parameters:**


* `centralBody` The central celestial body. 
* `allBodies` A set of all secondary celestial bodies in the system (default is none). 




        

<hr>



### function AstrodynamicsSystem [3/5]

_Constructs an_ [_**AstrodynamicsSystem**_](classastrea_1_1astro_1_1AstrodynamicsSystem.md) _with a specified central body, and the set of all other bodies._
```C++
inline constexpr astrea::astro::AstrodynamicsSystem::AstrodynamicsSystem (
    const CelestialBody & centralBody,
    const std::unordered_set< CelestialBody > & secondaryBodies={}
) 
```





**Parameters:**


* `centralBody` The central celestial body. 
* `allBodies` A set of all secondary celestial bodies in the system (default is none). 




        

<hr>



### function AstrodynamicsSystem [4/5]

_Deleted copy constructor for the_ [_**AstrodynamicsSystem**_](classastrea_1_1astro_1_1AstrodynamicsSystem.md) _class._
```C++
astrea::astro::AstrodynamicsSystem::AstrodynamicsSystem (
    const AstrodynamicsSystem &
) = delete
```




<hr>



### function AstrodynamicsSystem [5/5]

_Default move constructor for the_ [_**AstrodynamicsSystem**_](classastrea_1_1astro_1_1AstrodynamicsSystem.md) _class._
```C++
astrea::astro::AstrodynamicsSystem::AstrodynamicsSystem (
    AstrodynamicsSystem &&
) = default
```




<hr>



### function add\_body [1/3]

_Create a celestial body by id._ 
```C++
inline constexpr const CelestialBodyUniquePtr & astrea::astro::AstrodynamicsSystem::add_body (
    const CelestialBodyId & id
) 
```





**Parameters:**


* `id` The id of the celestial body to create. 
* `system` The astrodynamics system to which the body belongs. 



**Returns:**

const CelestialBodyUniquePtr& A pointer to the created celestial body. 





        

<hr>



### function add\_body [2/3]

_Store manually generated celestial body._ 
```C++
inline constexpr const CelestialBodyUniquePtr & astrea::astro::AstrodynamicsSystem::add_body (
    const CelestialBody & body
) 
```





**Parameters:**


* `id` The id of the celestial body to create. 
* `system` The astrodynamics system to which the body belongs. 



**Returns:**

const CelestialBodyUniquePtr& A pointer to the created celestial body. 





        

<hr>



### function add\_body [3/3]

_Create a celestial body by id (const version)._ 
```C++
inline constexpr CelestialBodyUniquePtr astrea::astro::AstrodynamicsSystem::add_body (
    const CelestialBodyId & id
) const
```





**Parameters:**


* `id` The id of the celestial body to create. 



**Returns:**

const CelestialBodyUniquePtr& A pointer to the created celestial body. 





        

<hr>



### function begin 

_Returns an iterator to the beginning of the celestial bodies._ 
```C++
inline constexpr auto astrea::astro::AstrodynamicsSystem::begin () const
```





**Returns:**

iterator An iterator to the first celestial body. 





        

<hr>



### function clear 

_Clears all celestial bodies managed by this factory._ 
```C++
inline constexpr void astrea::astro::AstrodynamicsSystem::clear () 
```




<hr>



### function end 

_Returns an iterator to the end of the celestial bodies._ 
```C++
inline constexpr auto astrea::astro::AstrodynamicsSystem::end () const
```





**Returns:**

iterator An iterator to the end of the celestial bodies. 





        

<hr>



### function get\_all\_bodies 

_Returns a vector of all celestial bodies in the system._ 
```C++
inline constexpr const auto & astrea::astro::AstrodynamicsSystem::get_all_bodies () const
```





**Returns:**

const std::vector&lt;CelestialBodyUniquePtr&gt;& A vector containing pointers to all celestial bodies in the system. 





        

<hr>



### function get\_body 

_Return a specific celestial body by ID._ 
```C++
inline constexpr const CelestialBodyUniquePtr & astrea::astro::AstrodynamicsSystem::get_body (
    const CelestialBodyId & id
) const
```





**Parameters:**


* `id` The ID of the celestial body to retrieve. 



**Returns:**

const CelestialBodyUniquePtr& A pointer to the celestial body with the specified ID. 





        

<hr>



### function get\_center\_type 

_Returns the central celestial body of the system._ 
```C++
inline constexpr const SystemCenter & astrea::astro::AstrodynamicsSystem::get_center_type () const
```





**Returns:**

const SystemCenter& The name of the central celestial body. 





        

<hr>



### function get\_central\_body 

_Returns the central celestial body as a CelestialBodyUniquePtr._ 
```C++
inline constexpr const CelestialBodyUniquePtr & astrea::astro::AstrodynamicsSystem::get_central_body () const
```





**Returns:**

const CelestialBodyUniquePtr& A pointer to the central celestial body. 





        

<hr>



### function get\_central\_body\_id 

_Returns the central celestial body ID._ 
```C++
inline constexpr const CelestialBodyId & astrea::astro::AstrodynamicsSystem::get_central_body_id () const
```





**Returns:**

const CelestialBodyId& The ID of the central celestial body. 





        

<hr>



### function get\_mu 

_Get the gravitational parameter (mu) of the central body._ 
```C++
inline constexpr GravParam astrea::astro::AstrodynamicsSystem::get_mu () const
```





**Returns:**

GravParam The gravitational parameter of the central body. 





        

<hr>



### function get\_relative\_position 

_Get the relative position between two celestial bodies at a specific date._ 
```C++
CartesianVector < Distance, frames::solar_system_barycenter::icrf > astrea::astro::AstrodynamicsSystem::get_relative_position (
    const Date & date,
    const CelestialBodyId id1,
    const CelestialBodyId id2
) const
```





**Parameters:**


* `date` The date at which to get the relative position. 
* `id1` The ID of the first celestial body. 
* `id2` The ID of the second celestial body. 



**Returns:**

CartesianVector&lt;Distance, frames::solar\_system\_barycenter::icrf&gt; The relative position vector from id2 to id1. 





        

<hr>



### function get\_system\_root 

_Get the root object of the celestial body hierarchy._ 
```C++
inline constexpr const CelestialBodyId & astrea::astro::AstrodynamicsSystem::get_system_root () const
```





**Returns:**

const CelestialBodyId& The name of the root celestial body. 





        

<hr>



### function operator= 

_Deleted assignment operator for the_ [_**AstrodynamicsSystem**_](classastrea_1_1astro_1_1AstrodynamicsSystem.md) _class._
```C++
AstrodynamicsSystem & astrea::astro::AstrodynamicsSystem::operator= (
    const AstrodynamicsSystem &
) = delete
```




<hr>



### function operator= 

_Default move assignment operator for the_ [_**AstrodynamicsSystem**_](classastrea_1_1astro_1_1AstrodynamicsSystem.md) _class._
```C++
AstrodynamicsSystem & astrea::astro::AstrodynamicsSystem::operator= (
    AstrodynamicsSystem &&
) = default
```




<hr>



### function requires 

_Creates a celestial body of a specific type._ 
```C++
template<typename T, typename... Args>
inline astrea::astro::AstrodynamicsSystem::requires (
    std::is_base_of< CelestialBody , T >::value
) const
```



This method allows for the creation of celestial bodies of derived types, such as specific planets or moons. The created body is assigned to the provided astrodynamics system.




**Template parameters:**


* `T` The type of celestial body to create, must be derived from [**CelestialBody**](classastrea_1_1astro_1_1CelestialBody.md). 
* `Args` The types of arguments to pass to the constructor of T. 



**Parameters:**


* `args` The arguments to pass to the constructor of T. 
* `system` The astrodynamics system to which the body belongs. 



**Returns:**

A unique pointer to the created [**CelestialBody**](classastrea_1_1astro_1_1CelestialBody.md) of type T. 





        

<hr>



### function size 

_Returns the number of celestial bodies managed by this factory._ 
```C++
inline constexpr const std::size_t astrea::astro::AstrodynamicsSystem::size () const
```





**Returns:**

const std::size\_t The number of celestial bodies. 





        

<hr>



### function ~AstrodynamicsSystem 

_Default destructor for the_ [_**AstrodynamicsSystem**_](classastrea_1_1astro_1_1AstrodynamicsSystem.md) _class._
```C++
astrea::astro::AstrodynamicsSystem::~AstrodynamicsSystem () = default
```




<hr>
## Public Static Functions Documentation




### function EarthMoon 

_Creates a default_ [_**AstrodynamicsSystem**_](classastrea_1_1astro_1_1AstrodynamicsSystem.md) _._
```C++
static inline constexpr AstrodynamicsSystem astrea::astro::AstrodynamicsSystem::EarthMoon () 
```





**Returns:**

A default [**AstrodynamicsSystem**](classastrea_1_1astro_1_1AstrodynamicsSystem.md) instance. 





        

<hr>

------------------------------
The documentation for this class was generated from the following file `astrea/astro/astro/systems/AstrodynamicsSystem.hpp`

