

# Class astrea::astro::SolarRadiationPressure



[**ClassList**](annotated.md) **>** [**astrea**](namespaceastrea.md) **>** [**astro**](namespaceastrea_1_1astro.md) **>** [**SolarRadiationPressure**](classastrea_1_1astro_1_1SolarRadiationPressure.md)



_Class to compute the solar radiation pressure force on a spacecraft._ 

* `#include <SolarRadiationPressure.hpp>`



Inherits the following classes: [astrea::astro::PerturbingForce](classastrea_1_1astro_1_1PerturbingForce.md)






















































## Public Functions

| Type | Name |
| ---: | :--- |
|   | [**SolarRadiationPressure**](#function-solarradiationpressure) () = default<br>_Default constructor for_ [_**SolarRadiationPressure**_](classastrea_1_1astro_1_1SolarRadiationPressure.md) _._ |
| virtual [**Perturbation**](structastrea_1_1astro_1_1Perturbation.md) | [**compute\_perturbation**](#function-compute_perturbation) ([**const**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) [**State**](classastrea_1_1astro_1_1State.md) & state, [**const**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) [**Vehicle**](classastrea_1_1astro_1_1Vehicle.md) & vehicle) override const<br>_Computes the solar radiation pressure force on a spacecraft._  |
|   | [**~SolarRadiationPressure**](#function-solarradiationpressure) () = default<br>_Default destructor for_ [_**SolarRadiationPressure**_](classastrea_1_1astro_1_1SolarRadiationPressure.md) _._ |


## Public Functions inherited from astrea::astro::PerturbingForce

See [astrea::astro::PerturbingForce](classastrea_1_1astro_1_1PerturbingForce.md)

| Type | Name |
| ---: | :--- |
|   | [**PerturbingForce**](classastrea_1_1astro_1_1PerturbingForce.md#function-perturbingforce) () = default<br>_Default constructor for_ [_**PerturbingForce**_](classastrea_1_1astro_1_1PerturbingForce.md) _._ |
| virtual [**Perturbation**](structastrea_1_1astro_1_1Perturbation.md) | [**compute\_perturbation**](classastrea_1_1astro_1_1PerturbingForce.md#function-compute_perturbation) ([**const**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) [**State**](classastrea_1_1astro_1_1State.md) & state, [**const**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) [**Vehicle**](classastrea_1_1astro_1_1Vehicle.md) & vehicle) const = 0<br>_Computes the force acting on a vehicle at a given date and state._  |
| virtual  | [**~PerturbingForce**](classastrea_1_1astro_1_1PerturbingForce.md#function-perturbingforce) () = default<br>_Default destructor for_ [_**PerturbingForce**_](classastrea_1_1astro_1_1PerturbingForce.md) _._ |






















































## Public Functions Documentation




### function SolarRadiationPressure 

_Default constructor for_ [_**SolarRadiationPressure**_](classastrea_1_1astro_1_1SolarRadiationPressure.md) _._
```C++
astrea::astro::SolarRadiationPressure::SolarRadiationPressure () = default
```




<hr>



### function compute\_perturbation 

_Computes the solar radiation pressure force on a spacecraft._ 
```C++
virtual Perturbation astrea::astro::SolarRadiationPressure::compute_perturbation (
    const  State & state,
    const  Vehicle & vehicle
) override const
```





**Parameters:**


* `state` Cartesian&lt;frames::primary&gt; state vector of the vehicle 
* `vehicle` [**Vehicle**](classastrea_1_1astro_1_1Vehicle.md) object representing the spacecraft 



**Returns:**

[**Perturbation**](structastrea_1_1astro_1_1Perturbation.md) The computed force and torque due to solar radiation pressure. 





        
Implements [*astrea::astro::PerturbingForce::compute\_perturbation*](classastrea_1_1astro_1_1PerturbingForce.md#function-compute_perturbation)


<hr>



### function ~SolarRadiationPressure 

_Default destructor for_ [_**SolarRadiationPressure**_](classastrea_1_1astro_1_1SolarRadiationPressure.md) _._
```C++
astrea::astro::SolarRadiationPressure::~SolarRadiationPressure () = default
```




<hr>

------------------------------
The documentation for this class was generated from the following file `astrea/astro/astro/propagation/force_models/SolarRadiationPressure.hpp`

