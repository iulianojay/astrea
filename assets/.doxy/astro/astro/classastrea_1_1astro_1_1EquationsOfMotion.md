

# Class astrea::astro::EquationsOfMotion



[**ClassList**](annotated.md) **>** [**astrea**](namespaceastrea.md) **>** [**astro**](namespaceastrea_1_1astro.md) **>** [**EquationsOfMotion**](classastrea_1_1astro_1_1EquationsOfMotion.md)



_Base class for equations of motion in astrodynamics._ 

* `#include <EquationsOfMotion.hpp>`





Inherited by the following classes: [astrea::astro::CircularRestrictedThreeBodyProblem](classastrea_1_1astro_1_1CircularRestrictedThreeBodyProblem.md),  [astrea::astro::CowellsMethod](classastrea_1_1astro_1_1CowellsMethod.md),  [astrea::astro::EquinoctialVop](classastrea_1_1astro_1_1EquinoctialVop.md),  [astrea::astro::J2MeanVop](classastrea_1_1astro_1_1J2MeanVop.md),  [astrea::astro::KeplerianVop](classastrea_1_1astro_1_1KeplerianVop.md),  [astrea::astro::TwoBody](classastrea_1_1astro_1_1TwoBody.md)
































## Public Functions

| Type | Name |
| ---: | :--- |
|   | [**EquationsOfMotion**](#function-equationsofmotion-12) () = default<br>_Default constructor for the Equations of Motion class._  |
|   | [**EquationsOfMotion**](#function-equationsofmotion-22) ([**const**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) [**ForceModel**](classastrea_1_1astro_1_1ForceModel.md) & forces) <br>_Constructor for the Equations of Motion class that takes a_ [_**ForceModel**_](classastrea_1_1astro_1_1ForceModel.md) _._ |
| virtual [**OrbitalElementPartials**](classastrea_1_1astro_1_1OrbitalElementPartials.md) | [**compute\_dynamics**](#function-compute_dynamics) ([**const**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) [**State**](classastrea_1_1astro_1_1State.md) & state, [**const**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) [**Vehicle**](classastrea_1_1astro_1_1Vehicle.md) & vehicle, [**const**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) [**ForceVector**](namespaceastrea_1_1astro.md#typedef-forcevector)&lt; frames::primary &gt; & perts, [**const**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) [**ForceVector**](namespaceastrea_1_1astro.md#typedef-forcevector)&lt; frames::primary &gt; & control) const = 0<br>_Computes the partial derivatives of the orbital elements._  |
| virtual [**AttitudePartials**](classastrea_1_1astro_1_1AttitudePartials.md) | [**compute\_kinematics**](#function-compute_kinematics) ([**const**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) [**State**](classastrea_1_1astro_1_1State.md) & state, [**const**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) [**Vehicle**](classastrea_1_1astro_1_1Vehicle.md) & vehicle, [**const**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) [**TorqueVector**](namespaceastrea_1_1astro.md#typedef-torquevector)&lt; frames::primary &gt; & perts, [**const**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) [**TorqueVector**](namespaceastrea_1_1astro.md#typedef-torquevector)&lt; frames::primary &gt; & control) const<br>_Computes the kinematic partial derivatives of the attitude._  |
| virtual [**StateTransitionMatrix**](classastrea_1_1astro_1_1StateTransitionMatrix.md) | [**compute\_stm**](#function-compute_stm) ([**const**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) [**State**](classastrea_1_1astro_1_1State.md) & state, [**const**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) [**Vehicle**](classastrea_1_1astro_1_1Vehicle.md) & vehicle) const<br>_Computes the state transition matrix (STM)._  |
| virtual [**constexpr**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) std::size\_t | [**get\_expected\_set\_id**](#function-get_expected_set_id) () const = 0<br>_Returns the expected set of orbital elements for this method._  |
|  [**StatePartial**](classastrea_1_1astro_1_1StatePartial.md) | [**operator()**](#function-operator) ([**const**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) [**State**](classastrea_1_1astro_1_1State.md) & state, [**const**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) [**Vehicle**](classastrea_1_1astro_1_1Vehicle.md) & vehicle) const<br>_Computes the partial derivatives of the state._  |
| virtual  | [**~EquationsOfMotion**](#function-equationsofmotion) () = default<br>_Destructor for the Equations of Motion class._  |








## Protected Attributes

| Type | Name |
| ---: | :--- |
|  [**const**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) [**ForceModel**](classastrea_1_1astro_1_1ForceModel.md) \* | [**forces**](#variable-forces)   = `[**nullptr**](classastrea_1_1astro_1_1DirectionCosineMatrix.md)`<br>_The force model used in the equations of motion._  |




















## Public Functions Documentation




### function EquationsOfMotion [1/2]

_Default constructor for the Equations of Motion class._ 
```C++
astrea::astro::EquationsOfMotion::EquationsOfMotion () = default
```




<hr>



### function EquationsOfMotion [2/2]

_Constructor for the Equations of Motion class that takes a_ [_**ForceModel**_](classastrea_1_1astro_1_1ForceModel.md) _._
```C++
astrea::astro::EquationsOfMotion::EquationsOfMotion (
    const  ForceModel & forces
) 
```





**Parameters:**


* `forces` The force model to be used in the equations of motion. 




        

<hr>



### function compute\_dynamics 

_Computes the partial derivatives of the orbital elements._ 
```C++
virtual OrbitalElementPartials astrea::astro::EquationsOfMotion::compute_dynamics (
    const  State & state,
    const  Vehicle & vehicle,
    const  ForceVector < frames::primary > & perts,
    const  ForceVector < frames::primary > & control
) const = 0
```





**Parameters:**


* `date` The current date for which the equations of motion are being computed. 
* `state` The current state of the vehicle. 
* `vehicle` The vehicle for which the equations of motion are being computed. 
* `perts` The perturbations acting on the vehicle. 
* `control` The control forces produced by the vehicle. 



**Returns:**

[**StatePartial**](classastrea_1_1astro_1_1StatePartial.md) The computed partial derivatives of the orbital elements. 





        

<hr>



### function compute\_kinematics 

_Computes the kinematic partial derivatives of the attitude._ 
```C++
virtual AttitudePartials astrea::astro::EquationsOfMotion::compute_kinematics (
    const  State & state,
    const  Vehicle & vehicle,
    const  TorqueVector < frames::primary > & perts,
    const  TorqueVector < frames::primary > & control
) const
```





**Parameters:**


* `state` The current state of the vehicle. 
* `vehicle` The vehicle for which the kinematic partials are being computed. 
* `perts` The perturbations acting on the vehicle. 
* `control` The control torques produced by the vehicle. 



**Returns:**

[**AttitudePartials**](classastrea_1_1astro_1_1AttitudePartials.md) The computed kinematic partial derivatives of the attitude. 





        

<hr>



### function compute\_stm 

_Computes the state transition matrix (STM)._ 
```C++
virtual StateTransitionMatrix astrea::astro::EquationsOfMotion::compute_stm (
    const  State & state,
    const  Vehicle & vehicle
) const
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

_Computes the partial derivatives of the state._ 
```C++
StatePartial astrea::astro::EquationsOfMotion::operator() (
    const  State & state,
    const  Vehicle & vehicle
) const
```





**Parameters:**


* `state` The current state of the vehicle. 
* `vehicle` The vehicle for which the equations of motion are being computed. 



**Returns:**

[**StatePartial**](classastrea_1_1astro_1_1StatePartial.md) The computed partial derivatives of the state. 





        

<hr>



### function ~EquationsOfMotion 

_Destructor for the Equations of Motion class._ 
```C++
virtual astrea::astro::EquationsOfMotion::~EquationsOfMotion () = default
```




<hr>
## Protected Attributes Documentation




### variable forces 

_The force model used in the equations of motion._ 
```C++
const ForceModel* astrea::astro::EquationsOfMotion::forces;
```




<hr>

------------------------------
The documentation for this class was generated from the following file `astrea/astro/astro/propagation/equations_of_motion/EquationsOfMotion.hpp`

