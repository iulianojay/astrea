

# Class astrea::astro::SolarRadiationPressure



[**ClassList**](annotated.md) **>** [**astrea**](namespaceastrea.md) **>** [**astro**](namespaceastrea_1_1astro.md) **>** [**SolarRadiationPressure**](classastrea_1_1astro_1_1SolarRadiationPressure.md)



_Class to compute the solar radiation pressure force on a spacecraft._ 

* `#include <SolarRadiationPressure.hpp>`



Inherits the following classes: [astrea::astro::Force](classastrea_1_1astro_1_1Force.md)






















































## Public Functions

| Type | Name |
| ---: | :--- |
|   | [**SolarRadiationPressure**](#function-solarradiationpressure) () = default<br>_Default constructor for_ [_**SolarRadiationPressure**_](classastrea_1_1astro_1_1SolarRadiationPressure.md) _._ |
| virtual [**CartesianVector**](classastrea_1_1astro_1_1CartesianVector.md)&lt; [**Acceleration**](classastrea_1_1astro_1_1CartesianVector.md), [**frames::earth::icrf**](structastrea_1_1astro_1_1InertialFrame.md) &gt; | [**compute\_force**](#function-compute_force) ([**const**](classastrea_1_1astro_1_1CartesianVector.md) [**State**](classastrea_1_1astro_1_1State.md) & state, [**const**](classastrea_1_1astro_1_1CartesianVector.md) [**Vehicle**](classastrea_1_1astro_1_1Vehicle.md) & vehicle) override const<br>_Computes the solar radiation pressure force on a spacecraft._  |
|   | [**~SolarRadiationPressure**](#function-solarradiationpressure) () = default<br>_Default destructor for_ [_**SolarRadiationPressure**_](classastrea_1_1astro_1_1SolarRadiationPressure.md) _._ |


## Public Functions inherited from astrea::astro::Force

See [astrea::astro::Force](classastrea_1_1astro_1_1Force.md)

| Type | Name |
| ---: | :--- |
|   | [**Force**](classastrea_1_1astro_1_1Force.md#function-force) () = default<br>_Default constructor for_ [_**Force**_](classastrea_1_1astro_1_1Force.md) _._ |
| virtual [**CartesianVector**](classastrea_1_1astro_1_1CartesianVector.md)&lt; [**Acceleration**](classastrea_1_1astro_1_1CartesianVector.md), [**frames::earth::icrf**](structastrea_1_1astro_1_1InertialFrame.md) &gt; | [**compute\_force**](classastrea_1_1astro_1_1Force.md#function-compute_force) ([**const**](classastrea_1_1astro_1_1CartesianVector.md) [**State**](classastrea_1_1astro_1_1State.md) & state, [**const**](classastrea_1_1astro_1_1CartesianVector.md) [**Vehicle**](classastrea_1_1astro_1_1Vehicle.md) & vehicle) const = 0<br>_Computes the force acting on a vehicle at a given date and state._  |
| virtual  | [**~Force**](classastrea_1_1astro_1_1Force.md#function-force) () = default<br>_Default destructor for_ [_**Force**_](classastrea_1_1astro_1_1Force.md) _._ |






















































## Public Functions Documentation




### function SolarRadiationPressure 

_Default constructor for_ [_**SolarRadiationPressure**_](classastrea_1_1astro_1_1SolarRadiationPressure.md) _._
```C++
astrea::astro::SolarRadiationPressure::SolarRadiationPressure () = default
```




<hr>



### function compute\_force 

_Computes the solar radiation pressure force on a spacecraft._ 
```C++
virtual CartesianVector < Acceleration , frames::earth::icrf > astrea::astro::SolarRadiationPressure::compute_force (
    const  State & state,
    const  Vehicle & vehicle
) override const
```





**Parameters:**


* `state` [**Cartesian**](classastrea_1_1astro_1_1Cartesian.md) state vector of the vehicle 
* `vehicle` [**Vehicle**](classastrea_1_1astro_1_1Vehicle.md) object representing the spacecraft 



**Returns:**

[**AccelerationVector&lt;frames::earth::icrf&gt;**](namespaceastrea_1_1astro.md#typedef-accelerationvector) The computed acceleration vector due to solar radiation pressure. 





        
Implements [*astrea::astro::Force::compute\_force*](classastrea_1_1astro_1_1Force.md#function-compute_force)


<hr>



### function ~SolarRadiationPressure 

_Default destructor for_ [_**SolarRadiationPressure**_](classastrea_1_1astro_1_1SolarRadiationPressure.md) _._
```C++
astrea::astro::SolarRadiationPressure::~SolarRadiationPressure () = default
```




<hr>

------------------------------
The documentation for this class was generated from the following file `astrea/astro/astro/propagation/force_models/SolarRadiationPressure.hpp`

