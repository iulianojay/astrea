

# Class astrea::astro::PerturbingForce



[**ClassList**](annotated.md) **>** [**astrea**](namespaceastrea.md) **>** [**astro**](namespaceastrea_1_1astro.md) **>** [**PerturbingForce**](classastrea_1_1astro_1_1PerturbingForce.md)



_Abstract base class for force models in astrodynamics._ [More...](#detailed-description)

* `#include <PerturbingForce.hpp>`





Inherited by the following classes: [astrea::astro::AtmosphericForce](classastrea_1_1astro_1_1AtmosphericForce.md),  [astrea::astro::NBodyForce](classastrea_1_1astro_1_1NBodyForce.md),  [astrea::astro::OblatenessForce](classastrea_1_1astro_1_1OblatenessForce.md),  [astrea::astro::SolarRadiationPressure](classastrea_1_1astro_1_1SolarRadiationPressure.md)
































## Public Functions

| Type | Name |
| ---: | :--- |
|   | [**PerturbingForce**](#function-perturbingforce) () = default<br>_Default constructor for_ [_**PerturbingForce**_](classastrea_1_1astro_1_1PerturbingForce.md) _._ |
|  void | [**bind\_space\_weather\_provider**](#function-bind_space_weather_provider) (std::shared\_ptr&lt; const [**SpaceWeatherProvider**](classastrea_1_1astro_1_1SpaceWeatherProvider.md) &gt; provider) <br>_Binds shared immutable space weather data to this force._  |
| virtual std::unique\_ptr&lt; [**PerturbingForce**](classastrea_1_1astro_1_1PerturbingForce.md) &gt; | [**clone**](#function-clone) () const = 0<br>_Creates a clone of the current_ [_**PerturbingForce**_](classastrea_1_1astro_1_1PerturbingForce.md) _object._ |
| virtual [**Perturbation**](structastrea_1_1astro_1_1Perturbation.md) | [**compute\_perturbation**](#function-compute_perturbation) (const [**State**](classastrea_1_1astro_1_1State.md) & state, const [**Vehicle**](classastrea_1_1astro_1_1Vehicle.md) & vehicle) const = 0<br>_Computes the force acting on a vehicle at a given date and state._  |
|  std::shared\_ptr&lt; const [**SpaceWeatherData**](classastrea_1_1astro_1_1SpaceWeatherData.md) &gt; | [**get\_space\_weather\_data**](#function-get_space_weather_data) () noexcept const<br> |
|  const std::shared\_ptr&lt; const [**SpaceWeatherProvider**](classastrea_1_1astro_1_1SpaceWeatherProvider.md) &gt; & | [**get\_space\_weather\_provider**](#function-get_space_weather_provider) () noexcept const<br> |
| virtual  | [**~PerturbingForce**](#function-perturbingforce) () = default<br>_Default destructor for_ [_**PerturbingForce**_](classastrea_1_1astro_1_1PerturbingForce.md) _._ |




























## Detailed Description


This class defines the interface for computing forces acting on a vehicle in space. 


    
## Public Functions Documentation




### function PerturbingForce 

_Default constructor for_ [_**PerturbingForce**_](classastrea_1_1astro_1_1PerturbingForce.md) _._
```C++
astrea::astro::PerturbingForce::PerturbingForce () = default
```




<hr>



### function bind\_space\_weather\_provider 

_Binds shared immutable space weather data to this force._ 
```C++
inline void astrea::astro::PerturbingForce::bind_space_weather_provider (
    std::shared_ptr< const SpaceWeatherProvider > provider
) 
```




<hr>



### function clone 

_Creates a clone of the current_ [_**PerturbingForce**_](classastrea_1_1astro_1_1PerturbingForce.md) _object._
```C++
virtual std::unique_ptr< PerturbingForce > astrea::astro::PerturbingForce::clone () const = 0
```





**Returns:**

std::unique\_ptr&lt;PerturbingForce&gt; A unique pointer to the cloned [**PerturbingForce**](classastrea_1_1astro_1_1PerturbingForce.md) object. 





        

<hr>



### function compute\_perturbation 

_Computes the force acting on a vehicle at a given date and state._ 
```C++
virtual Perturbation astrea::astro::PerturbingForce::compute_perturbation (
    const State & state,
    const Vehicle & vehicle
) const = 0
```





**Parameters:**


* `state` [**State**](classastrea_1_1astro_1_1State.md) of the vehicle 
* `vehicle` [**Vehicle**](classastrea_1_1astro_1_1Vehicle.md) object representing the spacecraft 



**Returns:**

[**Perturbation**](structastrea_1_1astro_1_1Perturbation.md) The computed acceleration and torque vectors due to the force. 





        

<hr>



### function get\_space\_weather\_data 

```C++
inline std::shared_ptr< const SpaceWeatherData > astrea::astro::PerturbingForce::get_space_weather_data () noexcept const
```




<hr>



### function get\_space\_weather\_provider 

```C++
inline const std::shared_ptr< const SpaceWeatherProvider > & astrea::astro::PerturbingForce::get_space_weather_provider () noexcept const
```




<hr>



### function ~PerturbingForce 

_Default destructor for_ [_**PerturbingForce**_](classastrea_1_1astro_1_1PerturbingForce.md) _._
```C++
virtual astrea::astro::PerturbingForce::~PerturbingForce () = default
```




<hr>

------------------------------
The documentation for this class was generated from the following file `astrea/astro/astro/propagation/force_models/PerturbingForce.hpp`

