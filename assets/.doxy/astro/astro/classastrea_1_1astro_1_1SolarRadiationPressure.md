

# Class astrea::astro::SolarRadiationPressure



[**ClassList**](annotated.md) **>** [**astrea**](namespaceastrea.md) **>** [**astro**](namespaceastrea_1_1astro.md) **>** [**SolarRadiationPressure**](classastrea_1_1astro_1_1SolarRadiationPressure.md)



_Class to compute the solar radiation pressure force on a spacecraft._ 

* `#include <SolarRadiationPressure.hpp>`



Inherits the following classes: [astrea::astro::PerturbingForce](classastrea_1_1astro_1_1PerturbingForce.md)






















































## Public Functions

| Type | Name |
| ---: | :--- |
|   | [**SolarRadiationPressure**](#function-solarradiationpressure) () = default<br>_Default constructor for_ [_**SolarRadiationPressure**_](classastrea_1_1astro_1_1SolarRadiationPressure.md) _._ |
| virtual std::unique\_ptr&lt; [**PerturbingForce**](classastrea_1_1astro_1_1PerturbingForce.md) &gt; | [**clone**](#function-clone) () override const<br>_Creates a clone of the current_ [_**SolarRadiationPressure**_](classastrea_1_1astro_1_1SolarRadiationPressure.md) _object._ |
| virtual [**Perturbation**](structastrea_1_1astro_1_1Perturbation.md) | [**compute\_perturbation**](#function-compute_perturbation) (const [**State**](classastrea_1_1astro_1_1State.md) & state, const [**Vehicle**](classastrea_1_1astro_1_1Vehicle.md) & vehicle) override const<br>_Computes the solar radiation pressure force on a spacecraft._  |
|   | [**~SolarRadiationPressure**](#function-solarradiationpressure) () = default<br>_Default destructor for_ [_**SolarRadiationPressure**_](classastrea_1_1astro_1_1SolarRadiationPressure.md) _._ |


## Public Functions inherited from astrea::astro::PerturbingForce

See [astrea::astro::PerturbingForce](classastrea_1_1astro_1_1PerturbingForce.md)

| Type | Name |
| ---: | :--- |
|   | [**PerturbingForce**](classastrea_1_1astro_1_1PerturbingForce.md#function-perturbingforce) () = default<br>_Default constructor for_ [_**PerturbingForce**_](classastrea_1_1astro_1_1PerturbingForce.md) _._ |
|  void | [**bind\_space\_weather\_provider**](classastrea_1_1astro_1_1PerturbingForce.md#function-bind_space_weather_provider) (std::shared\_ptr&lt; const [**SpaceWeatherProvider**](classastrea_1_1astro_1_1SpaceWeatherProvider.md) &gt; provider) <br>_Binds shared immutable space weather data to this force._  |
| virtual std::unique\_ptr&lt; [**PerturbingForce**](classastrea_1_1astro_1_1PerturbingForce.md) &gt; | [**clone**](classastrea_1_1astro_1_1PerturbingForce.md#function-clone) () const = 0<br>_Creates a clone of the current_ [_**PerturbingForce**_](classastrea_1_1astro_1_1PerturbingForce.md) _object._ |
| virtual [**Perturbation**](structastrea_1_1astro_1_1Perturbation.md) | [**compute\_perturbation**](classastrea_1_1astro_1_1PerturbingForce.md#function-compute_perturbation) (const [**State**](classastrea_1_1astro_1_1State.md) & state, const [**Vehicle**](classastrea_1_1astro_1_1Vehicle.md) & vehicle) const = 0<br>_Computes the force acting on a vehicle at a given date and state._  |
|  std::shared\_ptr&lt; const [**SpaceWeatherData**](classastrea_1_1astro_1_1SpaceWeatherData.md) &gt; | [**get\_space\_weather\_data**](classastrea_1_1astro_1_1PerturbingForce.md#function-get_space_weather_data) () noexcept const<br> |
|  const std::shared\_ptr&lt; const [**SpaceWeatherProvider**](classastrea_1_1astro_1_1SpaceWeatherProvider.md) &gt; & | [**get\_space\_weather\_provider**](classastrea_1_1astro_1_1PerturbingForce.md#function-get_space_weather_provider) () noexcept const<br> |
| virtual  | [**~PerturbingForce**](classastrea_1_1astro_1_1PerturbingForce.md#function-perturbingforce) () = default<br>_Default destructor for_ [_**PerturbingForce**_](classastrea_1_1astro_1_1PerturbingForce.md) _._ |






















































## Public Functions Documentation




### function SolarRadiationPressure 

_Default constructor for_ [_**SolarRadiationPressure**_](classastrea_1_1astro_1_1SolarRadiationPressure.md) _._
```C++
astrea::astro::SolarRadiationPressure::SolarRadiationPressure () = default
```




<hr>



### function clone 

_Creates a clone of the current_ [_**SolarRadiationPressure**_](classastrea_1_1astro_1_1SolarRadiationPressure.md) _object._
```C++
inline virtual std::unique_ptr< PerturbingForce > astrea::astro::SolarRadiationPressure::clone () override const
```





**Returns:**

std::unique\_ptr&lt;PerturbingForce&gt; A unique pointer to the cloned [**SolarRadiationPressure**](classastrea_1_1astro_1_1SolarRadiationPressure.md) object. 





        
Implements [*astrea::astro::PerturbingForce::clone*](classastrea_1_1astro_1_1PerturbingForce.md#function-clone)


<hr>



### function compute\_perturbation 

_Computes the solar radiation pressure force on a spacecraft._ 
```C++
virtual Perturbation astrea::astro::SolarRadiationPressure::compute_perturbation (
    const State & state,
    const Vehicle & vehicle
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

