

# Class astrea::astro::AtmosphericForce



[**ClassList**](annotated.md) **>** [**astrea**](namespaceastrea.md) **>** [**astro**](namespaceastrea_1_1astro.md) **>** [**AtmosphericForce**](classastrea_1_1astro_1_1AtmosphericForce.md)



_Class to compute the atmospheric force on a vehicle._ [More...](#detailed-description)

* `#include <AtmosphericForce.hpp>`



Inherits the following classes: [astrea::astro::Force](classastrea_1_1astro_1_1Force.md)






















































## Public Functions

| Type | Name |
| ---: | :--- |
|   | [**AtmosphericForce**](#function-atmosphericforce) () = default<br>_Default constructor for_ [_**AtmosphericForce**_](classastrea_1_1astro_1_1AtmosphericForce.md) _._ |
| virtual [**CartesianVector**](classastrea_1_1astro_1_1CartesianVector.md)&lt; Acceleration, frames::earth::icrf &gt; | [**compute\_force**](#function-compute_force) (const [**State**](classastrea_1_1astro_1_1State.md) & state, const [**Vehicle**](classastrea_1_1astro_1_1Vehicle.md) & vehicle) override const<br>_Computes the atmospheric force on a vehicle._  |
|   | [**~AtmosphericForce**](#function-atmosphericforce) () = default<br>_Default destructor for_ [_**AtmosphericForce**_](classastrea_1_1astro_1_1AtmosphericForce.md) _._ |


## Public Functions inherited from astrea::astro::Force

See [astrea::astro::Force](classastrea_1_1astro_1_1Force.md)

| Type | Name |
| ---: | :--- |
|   | [**Force**](classastrea_1_1astro_1_1Force.md#function-force) () = default<br>_Default constructor for_ [_**Force**_](classastrea_1_1astro_1_1Force.md) _._ |
| virtual [**CartesianVector**](classastrea_1_1astro_1_1CartesianVector.md)&lt; Acceleration, frames::earth::icrf &gt; | [**compute\_force**](classastrea_1_1astro_1_1Force.md#function-compute_force) (const [**State**](classastrea_1_1astro_1_1State.md) & state, const [**Vehicle**](classastrea_1_1astro_1_1Vehicle.md) & vehicle) const = 0<br>_Computes the force acting on a vehicle at a given date and state._  |
| virtual  | [**~Force**](classastrea_1_1astro_1_1Force.md#function-force) () = default<br>_Default destructor for_ [_**Force**_](classastrea_1_1astro_1_1Force.md) _._ |






















































## Detailed Description


This class computes the atmospheric force on a vehicle based on its state and the celestial body's atmosphere. 


    
## Public Functions Documentation




### function AtmosphericForce 

_Default constructor for_ [_**AtmosphericForce**_](classastrea_1_1astro_1_1AtmosphericForce.md) _._
```C++
astrea::astro::AtmosphericForce::AtmosphericForce () = default
```




<hr>



### function compute\_force 

_Computes the atmospheric force on a vehicle._ 
```C++
virtual CartesianVector < Acceleration, frames::earth::icrf > astrea::astro::AtmosphericForce::compute_force (
    const State & state,
    const Vehicle & vehicle
) override const
```





**Parameters:**


* `state` [**State**](classastrea_1_1astro_1_1State.md) of the vehicle 
* `vehicle` [**Vehicle**](classastrea_1_1astro_1_1Vehicle.md) object representing the spacecraft 



**Returns:**

AccelerationVector&lt;frames::earth::icrf&gt; The computed acceleration vector due to atmospheric force. 





        
Implements [*astrea::astro::Force::compute\_force*](classastrea_1_1astro_1_1Force.md#function-compute_force)


<hr>



### function ~AtmosphericForce 

_Default destructor for_ [_**AtmosphericForce**_](classastrea_1_1astro_1_1AtmosphericForce.md) _._
```C++
astrea::astro::AtmosphericForce::~AtmosphericForce () = default
```




<hr>

------------------------------
The documentation for this class was generated from the following file `astrea/astro/astro/propagation/force_models/AtmosphericForce.hpp`

