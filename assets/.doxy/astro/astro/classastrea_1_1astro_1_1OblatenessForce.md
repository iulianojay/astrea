

# Class astrea::astro::OblatenessForce



[**ClassList**](annotated.md) **>** [**astrea**](namespaceastrea.md) **>** [**astro**](namespaceastrea_1_1astro.md) **>** [**OblatenessForce**](classastrea_1_1astro_1_1OblatenessForce.md)



_Class to compute the gravitational force due to the oblateness of a celestial body._ 

* `#include <OblatenessForce.hpp>`



Inherits the following classes: [astrea::astro::Force](classastrea_1_1astro_1_1Force.md)






















































## Public Functions

| Type | Name |
| ---: | :--- |
|   | [**OblatenessForce**](#function-oblatenessforce) ([**const**](classastrea_1_1astro_1_1CartesianVector.md) [**AstrodynamicsSystem**](classastrea_1_1astro_1_1AstrodynamicsSystem.md) & sys, [**const**](classastrea_1_1astro_1_1CartesianVector.md) std::size\_t & N=2, [**const**](classastrea_1_1astro_1_1CartesianVector.md) std::size\_t & M=0) <br>_Constructor for_ [_**OblatenessForce**_](classastrea_1_1astro_1_1OblatenessForce.md) _._ |
| virtual [**CartesianVector**](classastrea_1_1astro_1_1CartesianVector.md)&lt; [**Acceleration**](classastrea_1_1astro_1_1CartesianVector.md), [**frames::earth::icrf**](structastrea_1_1astro_1_1InertialFrame.md) &gt; | [**compute\_force**](#function-compute_force) ([**const**](classastrea_1_1astro_1_1CartesianVector.md) [**State**](classastrea_1_1astro_1_1State.md) & state, [**const**](classastrea_1_1astro_1_1CartesianVector.md) [**Vehicle**](classastrea_1_1astro_1_1Vehicle.md) & vehicle) const<br>_Computes the gravitational force using Montenbruck & Gill (2000) V and W recurrence relations._  |
|   | [**~OblatenessForce**](#function-oblatenessforce) () = default<br>_Default destructor for_ [_**OblatenessForce**_](classastrea_1_1astro_1_1OblatenessForce.md) _._ |


## Public Functions inherited from astrea::astro::Force

See [astrea::astro::Force](classastrea_1_1astro_1_1Force.md)

| Type | Name |
| ---: | :--- |
|   | [**Force**](classastrea_1_1astro_1_1Force.md#function-force) () = default<br>_Default constructor for_ [_**Force**_](classastrea_1_1astro_1_1Force.md) _._ |
| virtual [**CartesianVector**](classastrea_1_1astro_1_1CartesianVector.md)&lt; [**Acceleration**](classastrea_1_1astro_1_1CartesianVector.md), [**frames::earth::icrf**](structastrea_1_1astro_1_1InertialFrame.md) &gt; | [**compute\_force**](classastrea_1_1astro_1_1Force.md#function-compute_force) ([**const**](classastrea_1_1astro_1_1CartesianVector.md) [**State**](classastrea_1_1astro_1_1State.md) & state, [**const**](classastrea_1_1astro_1_1CartesianVector.md) [**Vehicle**](classastrea_1_1astro_1_1Vehicle.md) & vehicle) const = 0<br>_Computes the force acting on a vehicle at a given date and state._  |
| virtual  | [**~Force**](classastrea_1_1astro_1_1Force.md#function-force) () = default<br>_Default destructor for_ [_**Force**_](classastrea_1_1astro_1_1Force.md) _._ |






















































## Public Functions Documentation




### function OblatenessForce 

_Constructor for_ [_**OblatenessForce**_](classastrea_1_1astro_1_1OblatenessForce.md) _._
```C++
astrea::astro::OblatenessForce::OblatenessForce (
    const  AstrodynamicsSystem & sys,
    const std::size_t & N=2,
    const std::size_t & M=0
) 
```





**Parameters:**


* `sys` Astrodynamics system containing celestial body data 
* `N` Degree of the spherical harmonics (default is 2) 
* `M` Order of the spherical harmonics (default is 0) 
* `findExactLegendre` Whether to find exact Legendre values (default is false) 
* `useFastLegendre` Whether to use fast lookup for Legendre polynomials without interpolation (default is true) 




        

<hr>



### function compute\_force 

_Computes the gravitational force using Montenbruck & Gill (2000) V and W recurrence relations._ 
```C++
virtual CartesianVector < Acceleration , frames::earth::icrf > astrea::astro::OblatenessForce::compute_force (
    const  State & state,
    const  Vehicle & vehicle
) const
```



This method implements the algorithm from "Satellite Orbits: Models, Methods and Applications" by O. Montenbruck and E. Gill (Springer, 2000), which uses V and W auxiliary functions with recurrence relations for more efficient and numerically stable computation.




**Parameters:**


* `state` [**Cartesian**](classastrea_1_1astro_1_1Cartesian.md) state vector of the vehicle 
* `vehicle` [**Vehicle**](classastrea_1_1astro_1_1Vehicle.md) object representing the spacecraft 



**Returns:**

[**AccelerationVector&lt;frames::earth::icrf&gt;**](namespaceastrea_1_1astro.md#typedef-accelerationvector) The computed acceleration vector due to oblateness. 





        
Implements [*astrea::astro::Force::compute\_force*](classastrea_1_1astro_1_1Force.md#function-compute_force)


<hr>



### function ~OblatenessForce 

_Default destructor for_ [_**OblatenessForce**_](classastrea_1_1astro_1_1OblatenessForce.md) _._
```C++
astrea::astro::OblatenessForce::~OblatenessForce () = default
```




<hr>

------------------------------
The documentation for this class was generated from the following file `astrea/astro/astro/propagation/force_models/OblatenessForce.hpp`

