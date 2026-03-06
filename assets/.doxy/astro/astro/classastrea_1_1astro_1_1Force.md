

# Class astrea::astro::Force



[**ClassList**](annotated.md) **>** [**astrea**](namespaceastrea.md) **>** [**astro**](namespaceastrea_1_1astro.md) **>** [**Force**](classastrea_1_1astro_1_1Force.md)



_Abstract base class for force models in astrodynamics._ [More...](#detailed-description)

* `#include <Force.hpp>`





Inherited by the following classes: [astrea::astro::AtmosphericForce](classastrea_1_1astro_1_1AtmosphericForce.md),  [astrea::astro::NBodyForce](classastrea_1_1astro_1_1NBodyForce.md),  [astrea::astro::OblatenessForce](classastrea_1_1astro_1_1OblatenessForce.md),  [astrea::astro::SolarRadiationPressure](classastrea_1_1astro_1_1SolarRadiationPressure.md)
































## Public Functions

| Type | Name |
| ---: | :--- |
|   | [**Force**](#function-force) () = default<br>_Default constructor for_ [_**Force**_](classastrea_1_1astro_1_1Force.md) _._ |
| virtual [**CartesianVector**](classastrea_1_1astro_1_1CartesianVector.md)&lt; [**Acceleration**](classastrea_1_1astro_1_1CartesianVector.md), [**frames::earth::icrf**](structastrea_1_1astro_1_1InertialFrame.md) &gt; | [**compute\_force**](#function-compute_force) ([**const**](classastrea_1_1astro_1_1CartesianVector.md) [**State**](classastrea_1_1astro_1_1State.md) & state, [**const**](classastrea_1_1astro_1_1CartesianVector.md) [**Vehicle**](classastrea_1_1astro_1_1Vehicle.md) & vehicle) const = 0<br>_Computes the force acting on a vehicle at a given date and state._  |
| virtual  | [**~Force**](#function-force) () = default<br>_Default destructor for_ [_**Force**_](classastrea_1_1astro_1_1Force.md) _._ |




























## Detailed Description


This class defines the interface for computing forces acting on a vehicle in space. 


    
## Public Functions Documentation




### function Force 

_Default constructor for_ [_**Force**_](classastrea_1_1astro_1_1Force.md) _._
```C++
astrea::astro::Force::Force () = default
```




<hr>



### function compute\_force 

_Computes the force acting on a vehicle at a given date and state._ 
```C++
virtual CartesianVector < Acceleration , frames::earth::icrf > astrea::astro::Force::compute_force (
    const  State & state,
    const  Vehicle & vehicle
) const = 0
```





**Parameters:**


* `state` [**State**](classastrea_1_1astro_1_1State.md) of the vehicle 
* `vehicle` [**Vehicle**](classastrea_1_1astro_1_1Vehicle.md) object representing the spacecraft 



**Returns:**

[**AccelerationVector&lt;frames::earth::icrf&gt;**](namespaceastrea_1_1astro.md#typedef-accelerationvector) The computed acceleration vector due to the force. 





        

<hr>



### function ~Force 

_Default destructor for_ [_**Force**_](classastrea_1_1astro_1_1Force.md) _._
```C++
virtual astrea::astro::Force::~Force () = default
```




<hr>

------------------------------
The documentation for this class was generated from the following file `astrea/astro/astro/propagation/force_models/Force.hpp`

