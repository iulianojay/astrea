

# Class astrea::astro::ForceModel



[**ClassList**](annotated.md) **>** [**astrea**](namespaceastrea.md) **>** [**astro**](namespaceastrea_1_1astro.md) **>** [**ForceModel**](classastrea_1_1astro_1_1ForceModel.md)



_Class to manage multiple force models and compute the total force on a vehicle._ [More...](#detailed-description)

* `#include <ForceModel.hpp>`





































## Public Functions

| Type | Name |
| ---: | :--- |
|   | [**ForceModel**](#function-forcemodel) () = default<br>_Default constructor for_ [_**ForceModel**_](classastrea_1_1astro_1_1ForceModel.md) _._ |
|  const std::unique\_ptr&lt; [**Force**](classastrea_1_1astro_1_1Force.md) &gt; & | [**add**](#function-add) (Args &&... args) <br>_Adds a force model of type T with the given arguments._  |
|  const std::unique\_ptr&lt; [**Force**](classastrea_1_1astro_1_1Force.md) &gt; & | [**at**](#function-at) (const std::string & name) const<br>_Retrieves a force model by name._  |
|  [**CartesianVector**](classastrea_1_1astro_1_1CartesianVector.md)&lt; Acceleration, frames::earth::icrf &gt; | [**compute\_forces**](#function-compute_forces) (const [**State**](classastrea_1_1astro_1_1State.md) & state, const [**Vehicle**](classastrea_1_1astro_1_1Vehicle.md) & vehicle) const<br>_Computes the total force on a vehicle by summing the forces from all added force models._  |
|  const std::unique\_ptr&lt; [**Force**](classastrea_1_1astro_1_1Force.md) &gt; & | [**get**](#function-get) () const<br>_Retrieves a force model by type._  |
|  std::size\_t | [**size**](#function-size) () const<br>_Returns the number of forces added to the_ [_**ForceModel**_](classastrea_1_1astro_1_1ForceModel.md) _._ |
|   | [**~ForceModel**](#function-forcemodel) () = default<br>_Default destructor for_ [_**ForceModel**_](classastrea_1_1astro_1_1ForceModel.md) _._ |




























## Detailed Description


This class allows adding different force models, computing the total force on a vehicle, and retrieving specific force models by name or type. 


    
## Public Functions Documentation




### function ForceModel 

_Default constructor for_ [_**ForceModel**_](classastrea_1_1astro_1_1ForceModel.md) _._
```C++
astrea::astro::ForceModel::ForceModel () = default
```




<hr>



### function add 

_Adds a force model of type T with the given arguments._ 
```C++
template<typename T, typename... Args>
inline const std::unique_ptr< Force > & astrea::astro::ForceModel::add (
    Args &&... args
) 
```





**Template parameters:**


* `T` Type of the force model to add 
* `Args` Types of the arguments for the constructor of T 



**Parameters:**


* `args` Arguments to pass to the constructor of T 



**Returns:**

const std::unique\_ptr&lt;Force&gt;& Reference to the added force model 





        

<hr>



### function at 

_Retrieves a force model by name._ 
```C++
const std::unique_ptr< Force > & astrea::astro::ForceModel::at (
    const std::string & name
) const
```





**Parameters:**


* `name` Name of the force model to retrieve 



**Returns:**

const std::unique\_ptr&lt;Force&gt;& Reference to the force model with the given name. 





        

<hr>



### function compute\_forces 

_Computes the total force on a vehicle by summing the forces from all added force models._ 
```C++
CartesianVector < Acceleration, frames::earth::icrf > astrea::astro::ForceModel::compute_forces (
    const State & state,
    const Vehicle & vehicle
) const
```





**Parameters:**


* `state` [**Cartesian**](classastrea_1_1astro_1_1Cartesian.md) state vector of the vehicle 
* `vehicle` [**Vehicle**](classastrea_1_1astro_1_1Vehicle.md) object representing the spacecraft 



**Returns:**

AccelerationVector&lt;frames::earth::icrf&gt; The total computed acceleration vector from all force models. 





        

<hr>



### function get 

_Retrieves a force model by type._ 
```C++
template<typename T>
inline const std::unique_ptr< Force > & astrea::astro::ForceModel::get () const
```





**Template parameters:**


* `T` Type of the force model to retrieve 



**Returns:**

const std::unique\_ptr&lt;Force&gt;& Reference to the force model of type T. 





        

<hr>



### function size 

_Returns the number of forces added to the_ [_**ForceModel**_](classastrea_1_1astro_1_1ForceModel.md) _._
```C++
inline std::size_t astrea::astro::ForceModel::size () const
```





**Returns:**

std::size\_t Number of forces. 





        

<hr>



### function ~ForceModel 

_Default destructor for_ [_**ForceModel**_](classastrea_1_1astro_1_1ForceModel.md) _._
```C++
astrea::astro::ForceModel::~ForceModel () = default
```




<hr>

------------------------------
The documentation for this class was generated from the following file `astrea/astro/astro/propagation/force_models/ForceModel.hpp`

