

# Class astrea::astro::NBodyForce

**template &lt;IsCelestialBody auto... bodies&gt;**



[**ClassList**](annotated.md) **>** [**astrea**](namespaceastrea.md) **>** [**astro**](namespaceastrea_1_1astro.md) **>** [**NBodyForce**](classastrea_1_1astro_1_1NBodyForce.md)



_Class to compute the gravitational force due to multiple celestial bodies._ 

* `#include <NBodyForce.hpp>`



Inherits the following classes: [astrea::astro::PerturbingForce](classastrea_1_1astro_1_1PerturbingForce.md)






















































## Public Functions

| Type | Name |
| ---: | :--- |
|   | [**NBodyForce**](#function-nbodyforce) () = default<br>_Default constructor for_ [_**NBodyForce**_](classastrea_1_1astro_1_1NBodyForce.md) _._ |
| virtual std::unique\_ptr&lt; [**PerturbingForce**](classastrea_1_1astro_1_1PerturbingForce.md) &gt; | [**clone**](#function-clone) () override const<br>_Creates a clone of the current_ [_**NBodyForce**_](classastrea_1_1astro_1_1NBodyForce.md) _object._ |
| virtual [**Perturbation**](structastrea_1_1astro_1_1Perturbation.md) | [**compute\_perturbation**](#function-compute_perturbation) (const [**State**](classastrea_1_1astro_1_1State.md) & state, const [**Vehicle**](classastrea_1_1astro_1_1Vehicle.md) & vehicle) override const<br>_Computes the gravitational force due to multiple celestial bodies._  |
|   | [**~NBodyForce**](#function-nbodyforce) () = default<br>_Default destructor for_ [_**NBodyForce**_](classastrea_1_1astro_1_1NBodyForce.md) _._ |


## Public Functions inherited from astrea::astro::PerturbingForce

See [astrea::astro::PerturbingForce](classastrea_1_1astro_1_1PerturbingForce.md)

| Type | Name |
| ---: | :--- |
|   | [**PerturbingForce**](classastrea_1_1astro_1_1PerturbingForce.md#function-perturbingforce) () = default<br>_Default constructor for_ [_**PerturbingForce**_](classastrea_1_1astro_1_1PerturbingForce.md) _._ |
| virtual std::unique\_ptr&lt; [**PerturbingForce**](classastrea_1_1astro_1_1PerturbingForce.md) &gt; | [**clone**](classastrea_1_1astro_1_1PerturbingForce.md#function-clone) () const = 0<br>_Creates a clone of the current_ [_**PerturbingForce**_](classastrea_1_1astro_1_1PerturbingForce.md) _object._ |
| virtual [**Perturbation**](structastrea_1_1astro_1_1Perturbation.md) | [**compute\_perturbation**](classastrea_1_1astro_1_1PerturbingForce.md#function-compute_perturbation) (const [**State**](classastrea_1_1astro_1_1State.md) & state, const [**Vehicle**](classastrea_1_1astro_1_1Vehicle.md) & vehicle) const = 0<br>_Computes the force acting on a vehicle at a given date and state._  |
| virtual  | [**~PerturbingForce**](classastrea_1_1astro_1_1PerturbingForce.md#function-perturbingforce) () = default<br>_Default destructor for_ [_**PerturbingForce**_](classastrea_1_1astro_1_1PerturbingForce.md) _._ |






















































## Public Functions Documentation




### function NBodyForce 

_Default constructor for_ [_**NBodyForce**_](classastrea_1_1astro_1_1NBodyForce.md) _._
```C++
astrea::astro::NBodyForce::NBodyForce () = default
```




<hr>



### function clone 

_Creates a clone of the current_ [_**NBodyForce**_](classastrea_1_1astro_1_1NBodyForce.md) _object._
```C++
inline virtual std::unique_ptr< PerturbingForce > astrea::astro::NBodyForce::clone () override const
```





**Returns:**

std::unique\_ptr&lt;PerturbingForce&gt; A unique pointer to the cloned [**NBodyForce**](classastrea_1_1astro_1_1NBodyForce.md) object. 





        
Implements [*astrea::astro::PerturbingForce::clone*](classastrea_1_1astro_1_1PerturbingForce.md#function-clone)


<hr>



### function compute\_perturbation 

_Computes the gravitational force due to multiple celestial bodies._ 
```C++
inline virtual Perturbation astrea::astro::NBodyForce::compute_perturbation (
    const State & state,
    const Vehicle & vehicle
) override const
```





**Parameters:**


* `state` Cartesian&lt;frames::primary&gt; state vector of the vehicle 
* `vehicle` [**Vehicle**](classastrea_1_1astro_1_1Vehicle.md) object representing the spacecraft 



**Returns:**

[**Perturbation**](structastrea_1_1astro_1_1Perturbation.md) The computed force and torque due to multiple bodies. 





        
Implements [*astrea::astro::PerturbingForce::compute\_perturbation*](classastrea_1_1astro_1_1PerturbingForce.md#function-compute_perturbation)


<hr>



### function ~NBodyForce 

_Default destructor for_ [_**NBodyForce**_](classastrea_1_1astro_1_1NBodyForce.md) _._
```C++
astrea::astro::NBodyForce::~NBodyForce () = default
```




<hr>

------------------------------
The documentation for this class was generated from the following file `astrea/astro/astro/propagation/force_models/NBodyForce.hpp`

