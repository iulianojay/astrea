

# Class astrea::astro::EquationsOfMotion



[**ClassList**](annotated.md) **>** [**astrea**](namespaceastrea.md) **>** [**astro**](namespaceastrea_1_1astro.md) **>** [**EquationsOfMotion**](classastrea_1_1astro_1_1EquationsOfMotion.md)



_Base class for equations of motion in astrodynamics._ 

* `#include <EquationsOfMotion.hpp>`





Inherited by the following classes: [astrea::astro::CowellsMethod](classastrea_1_1astro_1_1CowellsMethod.md),  [astrea::astro::EquinoctialVop](classastrea_1_1astro_1_1EquinoctialVop.md),  [astrea::astro::J2MeanVop](classastrea_1_1astro_1_1J2MeanVop.md),  [astrea::astro::KeplerianVop](classastrea_1_1astro_1_1KeplerianVop.md),  [astrea::astro::TwoBody](classastrea_1_1astro_1_1TwoBody.md)
































## Public Functions

| Type | Name |
| ---: | :--- |
|   | [**EquationsOfMotion**](#function-equationsofmotion) () = default<br>_Default constructor for the Equations of Motion class._  |
| virtual [**StateTransitionMatrix**](classastrea_1_1astro_1_1StateTransitionMatrix.md) | [**compute\_stm**](#function-compute_stm) (const [**State**](classastrea_1_1astro_1_1State.md) & state, const [**Vehicle**](classastrea_1_1astro_1_1Vehicle.md) & vehicle) const = 0<br>_Computes the state transition matrix (STM)._  |
| virtual constexpr std::size\_t | [**get\_expected\_set\_id**](#function-get_expected_set_id) () const = 0<br>_Returns the expected set of orbital elements for this method._  |
| virtual [**OrbitalElementPartials**](classastrea_1_1astro_1_1OrbitalElementPartials.md) | [**operator()**](#function-operator) (const [**State**](classastrea_1_1astro_1_1State.md) & state, const [**Vehicle**](classastrea_1_1astro_1_1Vehicle.md) & vehicle) const = 0<br>_Computes the partial derivatives of the orbital elements._  |
| virtual  | [**~EquationsOfMotion**](#function-equationsofmotion) () = default<br>_Destructor for the Equations of Motion class._  |




























## Public Functions Documentation




### function EquationsOfMotion 

_Default constructor for the Equations of Motion class._ 
```C++
astrea::astro::EquationsOfMotion::EquationsOfMotion () = default
```




<hr>



### function compute\_stm 

_Computes the state transition matrix (STM)._ 
```C++
virtual StateTransitionMatrix astrea::astro::EquationsOfMotion::compute_stm (
    const State & state,
    const Vehicle & vehicle
) const = 0
```





**Parameters:**


* `date` The current date for which the STM is being computed. 
* `state` The current state of the vehicle. 
* `vehicle` The vehicle for which the STM is being computed. 



**Returns:**

[**StateTransitionMatrix**](classastrea_1_1astro_1_1StateTransitionMatrix.md) The computed state transition matrix. 





        

<hr>



### function get\_expected\_set\_id 

_Returns the expected set of orbital elements for this method._ 
```C++
virtual constexpr std::size_t astrea::astro::EquationsOfMotion::get_expected_set_id () const = 0
```





**Returns:**

std::size\_t The expected set id of orbital elements. 





        

<hr>



### function operator() 

_Computes the partial derivatives of the orbital elements._ 
```C++
virtual OrbitalElementPartials astrea::astro::EquationsOfMotion::operator() (
    const State & state,
    const Vehicle & vehicle
) const = 0
```





**Parameters:**


* `date` The current date for which the equations of motion are being computed. 
* `state` The current state of the vehicle. 
* `vehicle` The vehicle for which the equations of motion are being computed. 



**Returns:**

[**OrbitalElementPartials**](classastrea_1_1astro_1_1OrbitalElementPartials.md) The computed partial derivatives of the orbital elements. 





        

<hr>



### function ~EquationsOfMotion 

_Destructor for the Equations of Motion class._ 
```C++
virtual astrea::astro::EquationsOfMotion::~EquationsOfMotion () = default
```




<hr>

------------------------------
The documentation for this class was generated from the following file `astrea/astro/astro/propagation/equations_of_motion/EquationsOfMotion.hpp`

