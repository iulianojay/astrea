

# Class astrea::astro::TwoBody



[**ClassList**](annotated.md) **>** [**astrea**](namespaceastrea.md) **>** [**astro**](namespaceastrea_1_1astro.md) **>** [**TwoBody**](classastrea_1_1astro_1_1TwoBody.md)



_Class implementing the Two Body equations of motion._ 

* `#include <TwoBody.hpp>`



Inherits the following classes: [astrea::astro::EquationsOfMotion](classastrea_1_1astro_1_1EquationsOfMotion.md)






















































## Public Functions

| Type | Name |
| ---: | :--- |
|   | [**TwoBody**](#function-twobody) () = default<br>_Default constructor for the Two Body equations of motion class._  |
| virtual [**OrbitalElementPartials**](classastrea_1_1astro_1_1OrbitalElementPartials.md) | [**compute\_dynamics**](#function-compute_dynamics) ([**const**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) [**State**](classastrea_1_1astro_1_1State.md) & state, [**const**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) [**Vehicle**](classastrea_1_1astro_1_1Vehicle.md) & vehicle, [**const**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) [**ForceVector**](namespaceastrea_1_1astro.md#typedef-forcevector)&lt; frames::primary &gt; & perts, [**const**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) [**ForceVector**](namespaceastrea_1_1astro.md#typedef-forcevector)&lt; frames::primary &gt; & control) override const<br>_Computes the partial derivatives of the orbital elements using the Two Body method._  |
| virtual [**StateTransitionMatrix**](classastrea_1_1astro_1_1StateTransitionMatrix.md) | [**compute\_stm**](#function-compute_stm) ([**const**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) [**State**](classastrea_1_1astro_1_1State.md) & state, [**const**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) [**Vehicle**](classastrea_1_1astro_1_1Vehicle.md) & vehicle) override const<br>_Computes the state transition matrix (STM) using the Two Body method._  |
| virtual [**constexpr**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) std::size\_t | [**get\_expected\_set\_id**](#function-get_expected_set_id) () override const<br>_Returns the expected set of orbital elements for this equations of motion class._  |
|   | [**~TwoBody**](#function-twobody) () = default<br>_Destructor for the Two Body equations of motion class._  |


## Public Functions inherited from astrea::astro::EquationsOfMotion

See [astrea::astro::EquationsOfMotion](classastrea_1_1astro_1_1EquationsOfMotion.md)

| Type | Name |
| ---: | :--- |
|   | [**EquationsOfMotion**](classastrea_1_1astro_1_1EquationsOfMotion.md#function-equationsofmotion-12) () = default<br>_Default constructor for the Equations of Motion class._  |
|   | [**EquationsOfMotion**](classastrea_1_1astro_1_1EquationsOfMotion.md#function-equationsofmotion-22) ([**const**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) [**ForceModel**](classastrea_1_1astro_1_1ForceModel.md) & forces) <br>_Constructor for the Equations of Motion class that takes a_ [_**ForceModel**_](classastrea_1_1astro_1_1ForceModel.md) _._ |
| virtual [**OrbitalElementPartials**](classastrea_1_1astro_1_1OrbitalElementPartials.md) | [**compute\_dynamics**](classastrea_1_1astro_1_1EquationsOfMotion.md#function-compute_dynamics) ([**const**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) [**State**](classastrea_1_1astro_1_1State.md) & state, [**const**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) [**Vehicle**](classastrea_1_1astro_1_1Vehicle.md) & vehicle, [**const**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) [**ForceVector**](namespaceastrea_1_1astro.md#typedef-forcevector)&lt; frames::primary &gt; & perts, [**const**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) [**ForceVector**](namespaceastrea_1_1astro.md#typedef-forcevector)&lt; frames::primary &gt; & control) const = 0<br>_Computes the partial derivatives of the orbital elements._  |
| virtual [**AttitudePartials**](classastrea_1_1astro_1_1AttitudePartials.md) | [**compute\_kinematics**](classastrea_1_1astro_1_1EquationsOfMotion.md#function-compute_kinematics) ([**const**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) [**State**](classastrea_1_1astro_1_1State.md) & state, [**const**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) [**Vehicle**](classastrea_1_1astro_1_1Vehicle.md) & vehicle, [**const**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) [**TorqueVector**](namespaceastrea_1_1astro.md#typedef-torquevector)&lt; frames::primary &gt; & perts, [**const**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) [**TorqueVector**](namespaceastrea_1_1astro.md#typedef-torquevector)&lt; frames::primary &gt; & control) const<br>_Computes the kinematic partial derivatives of the attitude._  |
| virtual [**StateTransitionMatrix**](classastrea_1_1astro_1_1StateTransitionMatrix.md) | [**compute\_stm**](classastrea_1_1astro_1_1EquationsOfMotion.md#function-compute_stm) ([**const**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) [**State**](classastrea_1_1astro_1_1State.md) & state, [**const**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) [**Vehicle**](classastrea_1_1astro_1_1Vehicle.md) & vehicle) const<br>_Computes the state transition matrix (STM)._  |
| virtual [**constexpr**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) std::size\_t | [**get\_expected\_set\_id**](classastrea_1_1astro_1_1EquationsOfMotion.md#function-get_expected_set_id) () const = 0<br>_Returns the expected set of orbital elements for this method._  |
|  [**StatePartial**](classastrea_1_1astro_1_1StatePartial.md) | [**operator()**](classastrea_1_1astro_1_1EquationsOfMotion.md#function-operator) ([**const**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) [**State**](classastrea_1_1astro_1_1State.md) & state, [**const**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) [**Vehicle**](classastrea_1_1astro_1_1Vehicle.md) & vehicle) const<br>_Computes the partial derivatives of the state._  |
| virtual  | [**~EquationsOfMotion**](classastrea_1_1astro_1_1EquationsOfMotion.md#function-equationsofmotion) () = default<br>_Destructor for the Equations of Motion class._  |
















## Protected Attributes inherited from astrea::astro::EquationsOfMotion

See [astrea::astro::EquationsOfMotion](classastrea_1_1astro_1_1EquationsOfMotion.md)

| Type | Name |
| ---: | :--- |
|  [**const**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) [**ForceModel**](classastrea_1_1astro_1_1ForceModel.md) \* | [**forces**](classastrea_1_1astro_1_1EquationsOfMotion.md#variable-forces)   = `[**nullptr**](classastrea_1_1astro_1_1DirectionCosineMatrix.md)`<br>_The force model used in the equations of motion._  |






































## Public Functions Documentation




### function TwoBody 

_Default constructor for the Two Body equations of motion class._ 
```C++
astrea::astro::TwoBody::TwoBody () = default
```




<hr>



### function compute\_dynamics 

_Computes the partial derivatives of the orbital elements using the Two Body method._ 
```C++
virtual OrbitalElementPartials astrea::astro::TwoBody::compute_dynamics (
    const  State & state,
    const  Vehicle & vehicle,
    const  ForceVector < frames::primary > & perts,
    const  ForceVector < frames::primary > & control
) override const
```





**Parameters:**


* `state` The current state of the vehicle. 
* `vehicle` The vehicle for which the equations of motion are being computed. 
* `perts` The perturbations acting on the vehicle. 
* `control` The control forces produced by the vehicle. 



**Returns:**

[**OrbitalElementPartials**](classastrea_1_1astro_1_1OrbitalElementPartials.md) The computed partial derivatives of the orbital elements. 





        
Implements [*astrea::astro::EquationsOfMotion::compute\_dynamics*](classastrea_1_1astro_1_1EquationsOfMotion.md#function-compute_dynamics)


<hr>



### function compute\_stm 

_Computes the state transition matrix (STM) using the Two Body method._ 
```C++
virtual StateTransitionMatrix astrea::astro::TwoBody::compute_stm (
    const  State & state,
    const  Vehicle & vehicle
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
inline virtual constexpr std::size_t astrea::astro::TwoBody::get_expected_set_id () override const
```





**Returns:**

std::size\_t The expected set id of orbital elements. 





        
Implements [*astrea::astro::EquationsOfMotion::get\_expected\_set\_id*](classastrea_1_1astro_1_1EquationsOfMotion.md#function-get_expected_set_id)


<hr>



### function ~TwoBody 

_Destructor for the Two Body equations of motion class._ 
```C++
astrea::astro::TwoBody::~TwoBody () = default
```




<hr>

------------------------------
The documentation for this class was generated from the following file `astrea/astro/astro/propagation/equations_of_motion/TwoBody.hpp`

