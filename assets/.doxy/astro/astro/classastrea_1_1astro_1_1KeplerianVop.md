

# Class astrea::astro::KeplerianVop



[**ClassList**](annotated.md) **>** [**astrea**](namespaceastrea.md) **>** [**astro**](namespaceastrea_1_1astro.md) **>** [**KeplerianVop**](classastrea_1_1astro_1_1KeplerianVop.md)



_Class implementing the_ [_**Keplerian**_](classastrea_1_1astro_1_1Keplerian.md) _VOP equations of motion._

* `#include <KeplerianVop.hpp>`



Inherits the following classes: [astrea::astro::EquationsOfMotion](classastrea_1_1astro_1_1EquationsOfMotion.md)






















































## Public Functions

| Type | Name |
| ---: | :--- |
|   | [**KeplerianVop**](#function-keplerianvop) (const [**ForceModel**](classastrea_1_1astro_1_1ForceModel.md) & forces, const bool doWarn=true) <br>_Constructor for the_ [_**Keplerian**_](classastrea_1_1astro_1_1Keplerian.md) _VOP class._ |
| virtual [**StateTransitionMatrix**](classastrea_1_1astro_1_1StateTransitionMatrix.md) | [**compute\_stm**](#function-compute_stm) (const [**State**](classastrea_1_1astro_1_1State.md) & state, const [**Vehicle**](classastrea_1_1astro_1_1Vehicle.md) & vehicle) override const<br>_Computes the state transition matrix (STM) using Cowell's method._  |
| virtual constexpr std::size\_t | [**get\_expected\_set\_id**](#function-get_expected_set_id) () override const<br>_Returns the expected set of orbital elements for this equations of motion class._  |
| virtual [**OrbitalElementPartials**](classastrea_1_1astro_1_1OrbitalElementPartials.md) | [**operator()**](#function-operator) (const [**State**](classastrea_1_1astro_1_1State.md) & state, const [**Vehicle**](classastrea_1_1astro_1_1Vehicle.md) & vehicle) override const<br>_Computes the partial derivatives of the orbital elements using the_ [_**Keplerian**_](classastrea_1_1astro_1_1Keplerian.md) _VOP method._ |
|   | [**~KeplerianVop**](#function-keplerianvop) () = default<br>_Destructor for the_ [_**Keplerian**_](classastrea_1_1astro_1_1Keplerian.md) _VOP class._ |


## Public Functions inherited from astrea::astro::EquationsOfMotion

See [astrea::astro::EquationsOfMotion](classastrea_1_1astro_1_1EquationsOfMotion.md)

| Type | Name |
| ---: | :--- |
|   | [**EquationsOfMotion**](classastrea_1_1astro_1_1EquationsOfMotion.md#function-equationsofmotion) () = default<br>_Default constructor for the Equations of Motion class._  |
| virtual [**StateTransitionMatrix**](classastrea_1_1astro_1_1StateTransitionMatrix.md) | [**compute\_stm**](classastrea_1_1astro_1_1EquationsOfMotion.md#function-compute_stm) (const [**State**](classastrea_1_1astro_1_1State.md) & state, const [**Vehicle**](classastrea_1_1astro_1_1Vehicle.md) & vehicle) const = 0<br>_Computes the state transition matrix (STM)._  |
| virtual constexpr std::size\_t | [**get\_expected\_set\_id**](classastrea_1_1astro_1_1EquationsOfMotion.md#function-get_expected_set_id) () const = 0<br>_Returns the expected set of orbital elements for this method._  |
| virtual [**OrbitalElementPartials**](classastrea_1_1astro_1_1OrbitalElementPartials.md) | [**operator()**](classastrea_1_1astro_1_1EquationsOfMotion.md#function-operator) (const [**State**](classastrea_1_1astro_1_1State.md) & state, const [**Vehicle**](classastrea_1_1astro_1_1Vehicle.md) & vehicle) const = 0<br>_Computes the partial derivatives of the orbital elements._  |
| virtual  | [**~EquationsOfMotion**](classastrea_1_1astro_1_1EquationsOfMotion.md#function-equationsofmotion) () = default<br>_Destructor for the Equations of Motion class._  |






















































## Public Functions Documentation




### function KeplerianVop 

_Constructor for the_ [_**Keplerian**_](classastrea_1_1astro_1_1Keplerian.md) _VOP class._
```C++
astrea::astro::KeplerianVop::KeplerianVop (
    const ForceModel & forces,
    const bool doWarn=true
) 
```





**Parameters:**


* `forces` The force model to be used in the equations of motion. 
* `doWarn` Flag to indicate whether to warn about degenerate cases. 




        

<hr>



### function compute\_stm 

_Computes the state transition matrix (STM) using Cowell's method._ 
```C++
virtual StateTransitionMatrix astrea::astro::KeplerianVop::compute_stm (
    const State & state,
    const Vehicle & vehicle
) override const
```





**Parameters:**


* `state` The current state of the vehicle. 
* `vehicle` The vehicle for which the STM is being computed. 



**Returns:**

[**StateTransitionMatrix**](classastrea_1_1astro_1_1StateTransitionMatrix.md) The computed state transition matrix. 





        
Implements [*astrea::astro::EquationsOfMotion::compute\_stm*](classastrea_1_1astro_1_1EquationsOfMotion.md#function-compute_stm)


<hr>



### function get\_expected\_set\_id 

_Returns the expected set of orbital elements for this equations of motion class._ 
```C++
inline virtual constexpr std::size_t astrea::astro::KeplerianVop::get_expected_set_id () override const
```





**Returns:**

std::size\_t The expected set id of orbital elements. 





        
Implements [*astrea::astro::EquationsOfMotion::get\_expected\_set\_id*](classastrea_1_1astro_1_1EquationsOfMotion.md#function-get_expected_set_id)


<hr>



### function operator() 

_Computes the partial derivatives of the orbital elements using the_ [_**Keplerian**_](classastrea_1_1astro_1_1Keplerian.md) _VOP method._
```C++
virtual OrbitalElementPartials astrea::astro::KeplerianVop::operator() (
    const State & state,
    const Vehicle & vehicle
) override const
```





**Parameters:**


* `date` The current date for which the equations of motion are being computed. 
* `state` The current state of the vehicle. 
* `vehicle` The vehicle for which the equations of motion are being computed. 



**Returns:**

[**OrbitalElementPartials**](classastrea_1_1astro_1_1OrbitalElementPartials.md) The computed partial derivatives of the orbital elements.


Dr. Kira Abercromby, Orbits 351: Advanced Orbital Mechanics, Lecture 2: Variation of Parameters 


        
Implements [*astrea::astro::EquationsOfMotion::operator()*](classastrea_1_1astro_1_1EquationsOfMotion.md#function-operator)


<hr>



### function ~KeplerianVop 

_Destructor for the_ [_**Keplerian**_](classastrea_1_1astro_1_1Keplerian.md) _VOP class._
```C++
astrea::astro::KeplerianVop::~KeplerianVop () = default
```




<hr>

------------------------------
The documentation for this class was generated from the following file `astrea/astro/astro/propagation/equations_of_motion/KeplerianVop.hpp`

