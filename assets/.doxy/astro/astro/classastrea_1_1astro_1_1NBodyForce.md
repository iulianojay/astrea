

# Class astrea::astro::NBodyForce



[**ClassList**](annotated.md) **>** [**astrea**](namespaceastrea.md) **>** [**astro**](namespaceastrea_1_1astro.md) **>** [**NBodyForce**](classastrea_1_1astro_1_1NBodyForce.md)



_Class to compute the gravitational force due to multiple celestial bodies._ 

* `#include <NBodyForce.hpp>`



Inherits the following classes: [astrea::astro::Force](classastrea_1_1astro_1_1Force.md)






















































## Public Functions

| Type | Name |
| ---: | :--- |
|   | [**NBodyForce**](#function-nbodyforce) () = default<br>_Default constructor for_ [_**NBodyForce**_](classastrea_1_1astro_1_1NBodyForce.md) _._ |
| virtual [**CartesianVector**](classastrea_1_1astro_1_1CartesianVector.md)&lt; [**Acceleration**](classastrea_1_1astro_1_1CartesianVector.md), [**frames::earth::icrf**](structastrea_1_1astro_1_1InertialFrame.md) &gt; | [**compute\_force**](#function-compute_force) ([**const**](classastrea_1_1astro_1_1CartesianVector.md) [**State**](classastrea_1_1astro_1_1State.md) & state, [**const**](classastrea_1_1astro_1_1CartesianVector.md) [**Vehicle**](classastrea_1_1astro_1_1Vehicle.md) & vehicle) override const<br>_Computes the gravitational force due to multiple celestial bodies._  |
|   | [**~NBodyForce**](#function-nbodyforce) () = default<br>_Default destructor for_ [_**NBodyForce**_](classastrea_1_1astro_1_1NBodyForce.md) _._ |


## Public Functions inherited from astrea::astro::Force

See [astrea::astro::Force](classastrea_1_1astro_1_1Force.md)

| Type | Name |
| ---: | :--- |
|   | [**Force**](classastrea_1_1astro_1_1Force.md#function-force) () = default<br>_Default constructor for_ [_**Force**_](classastrea_1_1astro_1_1Force.md) _._ |
| virtual [**CartesianVector**](classastrea_1_1astro_1_1CartesianVector.md)&lt; [**Acceleration**](classastrea_1_1astro_1_1CartesianVector.md), [**frames::earth::icrf**](structastrea_1_1astro_1_1InertialFrame.md) &gt; | [**compute\_force**](classastrea_1_1astro_1_1Force.md#function-compute_force) ([**const**](classastrea_1_1astro_1_1CartesianVector.md) [**State**](classastrea_1_1astro_1_1State.md) & state, [**const**](classastrea_1_1astro_1_1CartesianVector.md) [**Vehicle**](classastrea_1_1astro_1_1Vehicle.md) & vehicle) const = 0<br>_Computes the force acting on a vehicle at a given date and state._  |
| virtual  | [**~Force**](classastrea_1_1astro_1_1Force.md#function-force) () = default<br>_Default destructor for_ [_**Force**_](classastrea_1_1astro_1_1Force.md) _._ |






















































## Public Functions Documentation




### function NBodyForce 

_Default constructor for_ [_**NBodyForce**_](classastrea_1_1astro_1_1NBodyForce.md) _._
```C++
astrea::astro::NBodyForce::NBodyForce () = default
```




<hr>



### function compute\_force 

_Computes the gravitational force due to multiple celestial bodies._ 
```C++
virtual CartesianVector < Acceleration , frames::earth::icrf > astrea::astro::NBodyForce::compute_force (
    const  State & state,
    const  Vehicle & vehicle
) override const
```





**Parameters:**


* `state` [**Cartesian**](classastrea_1_1astro_1_1Cartesian.md) state vector of the vehicle 
* `vehicle` [**Vehicle**](classastrea_1_1astro_1_1Vehicle.md) object representing the spacecraft 



**Returns:**

[**AccelerationVector&lt;frames::earth::icrf&gt;**](namespaceastrea_1_1astro.md#typedef-accelerationvector) The computed acceleration vector due to multiple bodies. 





        
Implements [*astrea::astro::Force::compute\_force*](classastrea_1_1astro_1_1Force.md#function-compute_force)


<hr>



### function ~NBodyForce 

_Default destructor for_ [_**NBodyForce**_](classastrea_1_1astro_1_1NBodyForce.md) _._
```C++
astrea::astro::NBodyForce::~NBodyForce () = default
```




<hr>

------------------------------
The documentation for this class was generated from the following file `astrea/astro/astro/propagation/force_models/NBodyForce.hpp`

