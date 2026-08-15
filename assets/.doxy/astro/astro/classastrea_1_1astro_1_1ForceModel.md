

# Class astrea::astro::ForceModel



[**ClassList**](annotated.md) **>** [**astrea**](namespaceastrea.md) **>** [**astro**](namespaceastrea_1_1astro.md) **>** [**ForceModel**](classastrea_1_1astro_1_1ForceModel.md)



_Class to manage multiple force models and compute the total force on a vehicle._ [More...](#detailed-description)

* `#include <ForceModel.hpp>`





































## Public Functions

| Type | Name |
| ---: | :--- |
|   | [**ForceModel**](#function-forcemodel-13) () = default<br>_Default constructor for_ [_**ForceModel**_](classastrea_1_1astro_1_1ForceModel.md) _._ |
|   | [**ForceModel**](#function-forcemodel-23) (const [**ForceModel**](classastrea_1_1astro_1_1ForceModel.md) & other) <br>_Copy constructor for_ [_**ForceModel**_](classastrea_1_1astro_1_1ForceModel.md) _._ |
|   | [**ForceModel**](#function-forcemodel-33) ([**ForceModel**](classastrea_1_1astro_1_1ForceModel.md) &&) noexcept<br>_Move constructor for_ [_**ForceModel**_](classastrea_1_1astro_1_1ForceModel.md) _._ |
|  const std::unique\_ptr&lt; [**PerturbingForce**](classastrea_1_1astro_1_1PerturbingForce.md) &gt; & | [**add**](#function-add-12) (Args &&... args) <br>_Adds a force model of type T with the given constructor arguments._  |
|  const std::unique\_ptr&lt; [**PerturbingForce**](classastrea_1_1astro_1_1PerturbingForce.md) &gt; & | [**add**](#function-add-22) (Args &&... args) <br>_Adds a force model of the form Force&lt;Params...&gt; with the given constructor arguments._  |
|  const std::unique\_ptr&lt; [**PerturbingForce**](classastrea_1_1astro_1_1PerturbingForce.md) &gt; & | [**at**](#function-at) (const std::string & name) const<br>_Retrieves a force model by name._  |
|  [**Perturbation**](structastrea_1_1astro_1_1Perturbation.md) | [**compute\_perturbations**](#function-compute_perturbations) (const [**State**](classastrea_1_1astro_1_1State.md) & state, const [**Vehicle**](classastrea_1_1astro_1_1Vehicle.md) & vehicle) const<br>_Computes the total force on a vehicle by summing the forces from all added force models._  |
|  const std::unique\_ptr&lt; [**PerturbingForce**](classastrea_1_1astro_1_1PerturbingForce.md) &gt; & | [**get**](#function-get) () const<br>_Retrieves a force model by type._  |
|  [**ForceModel**](classastrea_1_1astro_1_1ForceModel.md) & | [**operator=**](#function-operator) (const [**ForceModel**](classastrea_1_1astro_1_1ForceModel.md) & other) <br>_Copy assignment operator for_ [_**ForceModel**_](classastrea_1_1astro_1_1ForceModel.md) _._ |
|  [**ForceModel**](classastrea_1_1astro_1_1ForceModel.md) & | [**operator=**](#function-operator_1) ([**ForceModel**](classastrea_1_1astro_1_1ForceModel.md) &&) noexcept<br>_Move assignment operator for_ [_**ForceModel**_](classastrea_1_1astro_1_1ForceModel.md) _._ |
|  std::size\_t | [**size**](#function-size) () const<br>_Returns the number of forces added to the_ [_**ForceModel**_](classastrea_1_1astro_1_1ForceModel.md) _._ |
|   | [**~ForceModel**](#function-forcemodel) () = default<br>_Default destructor for_ [_**ForceModel**_](classastrea_1_1astro_1_1ForceModel.md) _._ |




























## Detailed Description


This class allows adding different force models, computing the total force on a vehicle, and retrieving specific force models by name or type. 


    
## Public Functions Documentation




### function ForceModel [1/3]

_Default constructor for_ [_**ForceModel**_](classastrea_1_1astro_1_1ForceModel.md) _._
```C++
astrea::astro::ForceModel::ForceModel () = default
```




<hr>



### function ForceModel [2/3]

_Copy constructor for_ [_**ForceModel**_](classastrea_1_1astro_1_1ForceModel.md) _._
```C++
astrea::astro::ForceModel::ForceModel (
    const ForceModel & other
) 
```





**Parameters:**


* `other` The [**ForceModel**](classastrea_1_1astro_1_1ForceModel.md) object to copy from. 




        

<hr>



### function ForceModel [3/3]

_Move constructor for_ [_**ForceModel**_](classastrea_1_1astro_1_1ForceModel.md) _._
```C++
astrea::astro::ForceModel::ForceModel (
    ForceModel &&
) noexcept
```





**Parameters:**


* `other` The [**ForceModel**](classastrea_1_1astro_1_1ForceModel.md) object to move from. 




        

<hr>



### function add [1/2]

_Adds a force model of type T with the given constructor arguments._ 
```C++
template<typename T, typename... Args>
inline const std::unique_ptr< PerturbingForce > & astrea::astro::ForceModel::add (
    Args &&... args
) 
```





**Template parameters:**


* `T` Type of the force model to add (no template parameters) 
* `Args` Types of the constructor arguments 



**Parameters:**


* `args` Arguments to pass to the constructor of T 



**Returns:**

const std::unique\_ptr&lt;PerturbingForce&gt;& Reference to the added force model 





        

<hr>



### function add [2/2]

_Adds a force model of the form Force&lt;Params...&gt; with the given constructor arguments._ 
```C++
template<template< auto... > class Pert, auto... Params, typename... Args>
inline const std::unique_ptr< PerturbingForce > & astrea::astro::ForceModel::add (
    Args &&... args
) 
```



Enables the syntax: model.add&lt;Pert, param1, param2&gt;(ctor\_arg1, ctor\_arg2) which constructs Pert&lt;param1, param2&gt;(ctor\_arg1, ctor\_arg2).




**Template parameters:**


* `Pert` Template template parameter taking auto... NTTPs 
* `Params` Non-type template arguments forwarded to Pert 
* `Args` Types of the constructor arguments 



**Parameters:**


* `args` Arguments to pass to the constructor of Pert&lt;Params...&gt; 



**Returns:**

const std::unique\_ptr&lt;PerturbingForce&gt;& Reference to the added force model 





        

<hr>



### function at 

_Retrieves a force model by name._ 
```C++
const std::unique_ptr< PerturbingForce > & astrea::astro::ForceModel::at (
    const std::string & name
) const
```





**Parameters:**


* `name` Name of the force model to retrieve 



**Returns:**

const std::unique\_ptr&lt;PerturbingForce&gt;& Reference to the force model with the given name. 





        

<hr>



### function compute\_perturbations 

_Computes the total force on a vehicle by summing the forces from all added force models._ 
```C++
Perturbation astrea::astro::ForceModel::compute_perturbations (
    const State & state,
    const Vehicle & vehicle
) const
```





**Parameters:**


* `state` Cartesian&lt;frames::primary&gt; state vector of the vehicle 
* `vehicle` [**Vehicle**](classastrea_1_1astro_1_1Vehicle.md) object representing the spacecraft 



**Returns:**

[**Perturbation**](structastrea_1_1astro_1_1Perturbation.md) The total computed perturbation from all force models. 





        

<hr>



### function get 

_Retrieves a force model by type._ 
```C++
template<typename T>
inline const std::unique_ptr< PerturbingForce > & astrea::astro::ForceModel::get () const
```





**Template parameters:**


* `T` Type of the force model to retrieve 



**Returns:**

const std::unique\_ptr&lt;PerturbingForce&gt;& Reference to the force model of type T. 





        

<hr>



### function operator= 

_Copy assignment operator for_ [_**ForceModel**_](classastrea_1_1astro_1_1ForceModel.md) _._
```C++
ForceModel & astrea::astro::ForceModel::operator= (
    const ForceModel & other
) 
```





**Parameters:**


* `other` The [**ForceModel**](classastrea_1_1astro_1_1ForceModel.md) object to copy from. 



**Returns:**

[**ForceModel**](classastrea_1_1astro_1_1ForceModel.md)& Reference to the assigned [**ForceModel**](classastrea_1_1astro_1_1ForceModel.md) object. 





        

<hr>



### function operator= 

_Move assignment operator for_ [_**ForceModel**_](classastrea_1_1astro_1_1ForceModel.md) _._
```C++
ForceModel & astrea::astro::ForceModel::operator= (
    ForceModel &&
) noexcept
```





**Parameters:**


* `other` The [**ForceModel**](classastrea_1_1astro_1_1ForceModel.md) object to move from. 



**Returns:**

[**ForceModel**](classastrea_1_1astro_1_1ForceModel.md)& Reference to the assigned [**ForceModel**](classastrea_1_1astro_1_1ForceModel.md) object. 





        

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

