

# Class astrea::astro::OblatenessForce

**template &lt;IsCelestialBody auto \_body\_, std::size\_t \_degree\_, std::size\_t \_order\_&gt;**



[**ClassList**](annotated.md) **>** [**astrea**](namespaceastrea.md) **>** [**astro**](namespaceastrea_1_1astro.md) **>** [**OblatenessForce**](classastrea_1_1astro_1_1OblatenessForce.md)



_Class to compute the gravitational force due to the oblateness of a celestial_ _body_ _._

* `#include <OblatenessForce.hpp>`



Inherits the following classes: [astrea::astro::PerturbingForce](classastrea_1_1astro_1_1PerturbingForce.md)






















































## Public Functions

| Type | Name |
| ---: | :--- |
|   | [**OblatenessForce**](#function-oblatenessforce) () = default<br>_Constructor for_ [_**OblatenessForce**_](classastrea_1_1astro_1_1OblatenessForce.md) _._ |
| virtual std::unique\_ptr&lt; [**PerturbingForce**](classastrea_1_1astro_1_1PerturbingForce.md) &gt; | [**clone**](#function-clone) () override const<br>_Creates a clone of the current_ [_**OblatenessForce**_](classastrea_1_1astro_1_1OblatenessForce.md) _object._ |
| virtual [**Perturbation**](structastrea_1_1astro_1_1Perturbation.md) | [**compute\_perturbation**](#function-compute_perturbation) (const [**State**](classastrea_1_1astro_1_1State.md) & state, const [**Vehicle**](classastrea_1_1astro_1_1Vehicle.md) & vehicle) const<br>_Computes the gravitational force using Montenbruck & Gill (2000) V and W recurrence relations._  |
|   | [**~OblatenessForce**](#function-oblatenessforce) () = default<br>_Default destructor for_ [_**OblatenessForce**_](classastrea_1_1astro_1_1OblatenessForce.md) _._ |


## Public Functions inherited from astrea::astro::PerturbingForce

See [astrea::astro::PerturbingForce](classastrea_1_1astro_1_1PerturbingForce.md)

| Type | Name |
| ---: | :--- |
|   | [**PerturbingForce**](classastrea_1_1astro_1_1PerturbingForce.md#function-perturbingforce) () = default<br>_Default constructor for_ [_**PerturbingForce**_](classastrea_1_1astro_1_1PerturbingForce.md) _._ |
| virtual std::unique\_ptr&lt; [**PerturbingForce**](classastrea_1_1astro_1_1PerturbingForce.md) &gt; | [**clone**](classastrea_1_1astro_1_1PerturbingForce.md#function-clone) () const = 0<br>_Creates a clone of the current_ [_**PerturbingForce**_](classastrea_1_1astro_1_1PerturbingForce.md) _object._ |
| virtual [**Perturbation**](structastrea_1_1astro_1_1Perturbation.md) | [**compute\_perturbation**](classastrea_1_1astro_1_1PerturbingForce.md#function-compute_perturbation) (const [**State**](classastrea_1_1astro_1_1State.md) & state, const [**Vehicle**](classastrea_1_1astro_1_1Vehicle.md) & vehicle) const = 0<br>_Computes the force acting on a vehicle at a given date and state._  |
| virtual  | [**~PerturbingForce**](classastrea_1_1astro_1_1PerturbingForce.md#function-perturbingforce) () = default<br>_Default destructor for_ [_**PerturbingForce**_](classastrea_1_1astro_1_1PerturbingForce.md) _._ |






















































## Public Functions Documentation




### function OblatenessForce 

_Constructor for_ [_**OblatenessForce**_](classastrea_1_1astro_1_1OblatenessForce.md) _._
```C++
astrea::astro::OblatenessForce::OblatenessForce () = default
```




<hr>



### function clone 

_Creates a clone of the current_ [_**OblatenessForce**_](classastrea_1_1astro_1_1OblatenessForce.md) _object._
```C++
inline virtual std::unique_ptr< PerturbingForce > astrea::astro::OblatenessForce::clone () override const
```





**Returns:**

std::unique\_ptr&lt;PerturbingForce&gt; A unique pointer to the cloned [**OblatenessForce**](classastrea_1_1astro_1_1OblatenessForce.md) object. 





        
Implements [*astrea::astro::PerturbingForce::clone*](classastrea_1_1astro_1_1PerturbingForce.md#function-clone)


<hr>



### function compute\_perturbation 

_Computes the gravitational force using Montenbruck & Gill (2000) V and W recurrence relations._ 
```C++
virtual Perturbation astrea::astro::OblatenessForce::compute_perturbation (
    const State & state,
    const Vehicle & vehicle
) const
```



This method implements the algorithm from "Satellite Orbits: Models, Methods and Applications" by O. Montenbruck and E. Gill (Springer, 2000), which uses V and W auxiliary functions with recurrence relations for more efficient and numerically stable computation.




**Parameters:**


* `state` Cartesian&lt;frames::primary&gt; state vector of the vehicle 
* `vehicle` [**Vehicle**](classastrea_1_1astro_1_1Vehicle.md) object representing the spacecraft 



**Returns:**

[**Perturbation**](structastrea_1_1astro_1_1Perturbation.md) The computed force and torque due to oblateness. 





        
Implements [*astrea::astro::PerturbingForce::compute\_perturbation*](classastrea_1_1astro_1_1PerturbingForce.md#function-compute_perturbation)


<hr>



### function ~OblatenessForce 

_Default destructor for_ [_**OblatenessForce**_](classastrea_1_1astro_1_1OblatenessForce.md) _._
```C++
astrea::astro::OblatenessForce::~OblatenessForce () = default
```




<hr>

------------------------------
The documentation for this class was generated from the following file `astrea/astro/astro/propagation/force_models/OblatenessForce.hpp`

