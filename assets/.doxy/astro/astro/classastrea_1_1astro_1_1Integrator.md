

# Class astrea::astro::Integrator



[**ClassList**](annotated.md) **>** [**astrea**](namespaceastrea.md) **>** [**astro**](namespaceastrea_1_1astro.md) **>** [**Integrator**](classastrea_1_1astro_1_1Integrator.md)



[_**Integrator**_](classastrea_1_1astro_1_1Integrator.md) _class for numerical propagation of orbital mechanics problems._[More...](#detailed-description)

* `#include <Integrator.hpp>`

















## Public Types

| Type | Name |
| ---: | :--- |
| enum [**EnumType**](namespaceastrea_1_1astro.md#typedef-enumtype) | [**StepMethod**](#enum-stepmethod)  <br>_Enumeration for different Runge-Kutta stepper methods._  |






## Public Static Attributes

| Type | Name |
| ---: | :--- |
|  [**Interval**](classastrea_1_1astro_1_1Interval.md) | [**defaultInterval**](#variable-defaultinterval)   = `{ 0.0 \* astrea::detail::time\_unit, 86400.0 \* astrea::detail::time\_unit }`<br>_Default time interval for propagation._  |














## Public Functions

| Type | Name |
| ---: | :--- |
|   | [**Integrator**](#function-integrator) () = default<br>_Default constructor for the_ [_**Integrator**_](classastrea_1_1astro_1_1Integrator.md) _class._ |
|  int | [**n\_func\_evals**](#function-n_func_evals) () <br>_Get the current timestep used by the integrator._  |
|  [**StateHistory**](classastrea_1_1astro_1_1StateHistory.md) | [**propagate**](#function-propagate-12) (const [**State**](classastrea_1_1astro_1_1State.md) & state0, const Time & propTime, const [**EquationsOfMotion**](classastrea_1_1astro_1_1EquationsOfMotion.md) & eom, [**Vehicle**](classastrea_1_1astro_1_1Vehicle.md) vehicle, bool store=false, std::vector&lt; [**Event**](classastrea_1_1astro_1_1Event.md) &gt; events={}) <br>_Propagate the state of a vehicle over a specified time interval using the given equations of motion._  |
|  [**StateHistory**](classastrea_1_1astro_1_1StateHistory.md) | [**propagate**](#function-propagate-22) (const [**State**](classastrea_1_1astro_1_1State.md) & state0, const [**Date**](classastrea_1_1astro_1_1Date.md) & endEpoch, const [**EquationsOfMotion**](classastrea_1_1astro_1_1EquationsOfMotion.md) & eom, [**Vehicle**](classastrea_1_1astro_1_1Vehicle.md) vehicle, bool store=false, std::vector&lt; [**Event**](classastrea_1_1astro_1_1Event.md) &gt; events={}) <br>_Propagate the state of a vehicle from its current epoch to a specified end epoch using the given equations of motion._  |
|  void | [**set\_abs\_tol**](#function-set_abs_tol) (const Unitless & absTol) <br>_Set the absolute tolerance for the integrator._  |
|  void | [**set\_initial\_timestep**](#function-set_initial_timestep) (const Time & dt0) <br>_Set the initial timestep for the integrator._  |
|  void | [**set\_max\_iter**](#function-set_max_iter) (const int & itMax) <br>_Set the maximum number of iterations for the integrator._  |
|  void | [**set\_rel\_tol**](#function-set_rel_tol) (const Unitless & relTol) <br>_Set the relative tolerance for the integrator._  |
|  void | [**set\_step\_method**](#function-set_step_method) (const [**StepMethod**](classastrea_1_1astro_1_1Integrator.md#enum-stepmethod) & stepMethod) <br>_Set the step method for the integrator._  |
|  void | [**set\_timestep**](#function-set_timestep) (const Time & fixedTimeStep) <br>_Set the fixed timestep for the integrator._  |
|  void | [**switch\_fixed\_timestep**](#function-switch_fixed_timestep-12) (const bool & onOff) <br>_Switch the fixed timestep mode on or off._  |
|  void | [**switch\_fixed\_timestep**](#function-switch_fixed_timestep-22) (const bool & onOff, const Time & fixedTimeStep) <br>_Set the fixed timestep for the integrator._  |
|  void | [**switch\_print**](#function-switch_print) (const bool & onOff) <br>_Switch the printing of integration details on or off._  |
|  void | [**switch\_timer**](#function-switch_timer) (const bool & onOff) <br>_Switch the timer for measuring integration performance on or off._  |
|   | [**~Integrator**](#function-integrator) () = default<br>_Default destructor for the_ [_**Integrator**_](classastrea_1_1astro_1_1Integrator.md) _class._ |




























## Detailed Description


This class implements various Runge-Kutta methods for integrating the equations of motion of a vehicle in space. It allows for variable step sizes, error control, and event handling. 


    
## Public Types Documentation




### enum StepMethod 

_Enumeration for different Runge-Kutta stepper methods._ 
```C++
enum astrea::astro::Integrator::StepMethod {
    RK45,
    RKF45,
    RKF78,
    DOP45,
    DOP78
};
```




<hr>
## Public Static Attributes Documentation




### variable defaultInterval 

_Default time interval for propagation._ 
```C++
Interval astrea::astro::Integrator::defaultInterval;
```




<hr>
## Public Functions Documentation




### function Integrator 

_Default constructor for the_ [_**Integrator**_](classastrea_1_1astro_1_1Integrator.md) _class._
```C++
astrea::astro::Integrator::Integrator () = default
```




<hr>



### function n\_func\_evals 

_Get the current timestep used by the integrator._ 
```C++
inline int astrea::astro::Integrator::n_func_evals () 
```





**Returns:**

Time The current timestep. 





        

<hr>



### function propagate [1/2]

_Propagate the state of a vehicle over a specified time interval using the given equations of motion._ 
```C++
StateHistory astrea::astro::Integrator::propagate (
    const State & state0,
    const Time & propTime,
    const EquationsOfMotion & eom,
    Vehicle vehicle,
    bool store=false,
    std::vector< Event > events={}
) 
```





**Parameters:**


* `state0` The initial state from which to start propagation. 
* `propTime` The total propagation time after the initial state epoch. 
* `eom` The equations of motion to use for the propagation. 
* `vehicle` The vehicle whose state is to be propagated. 
* `store` Whether to store the state history during propagation. Default is false. 



**Returns:**

[**StateHistory**](classastrea_1_1astro_1_1StateHistory.md) The history of the vehicle's state over the propagated interval. 





        

<hr>



### function propagate [2/2]

_Propagate the state of a vehicle from its current epoch to a specified end epoch using the given equations of motion._ 
```C++
StateHistory astrea::astro::Integrator::propagate (
    const State & state0,
    const Date & endEpoch,
    const EquationsOfMotion & eom,
    Vehicle vehicle,
    bool store=false,
    std::vector< Event > events={}
) 
```





**Parameters:**


* `state0` The initial state from which to start propagation. 
* `endEpoch` The final epoch (end time) for the propagation. 
* `eom` The equations of motion to use for the propagation. 
* `vehicle` The vehicle whose state is to be propagated. 
* `store` Whether to store the state history during propagation. Default is false. 



**Returns:**

[**StateHistory**](classastrea_1_1astro_1_1StateHistory.md) The history of the vehicle's state over the propagated interval. 





        

<hr>



### function set\_abs\_tol 

_Set the absolute tolerance for the integrator._ 
```C++
void astrea::astro::Integrator::set_abs_tol (
    const Unitless & absTol
) 
```





**Parameters:**


* `absTol` The absolute tolerance value to set. 




        

<hr>



### function set\_initial\_timestep 

_Set the initial timestep for the integrator._ 
```C++
void astrea::astro::Integrator::set_initial_timestep (
    const Time & dt0
) 
```





**Parameters:**


* `dt0` The initial timestep to set. 




        

<hr>



### function set\_max\_iter 

_Set the maximum number of iterations for the integrator._ 
```C++
void astrea::astro::Integrator::set_max_iter (
    const int & itMax
) 
```





**Parameters:**


* `itMax` The maximum number of iterations to set. 




        

<hr>



### function set\_rel\_tol 

_Set the relative tolerance for the integrator._ 
```C++
void astrea::astro::Integrator::set_rel_tol (
    const Unitless & relTol
) 
```





**Parameters:**


* `relTol` The relative tolerance value to set. 




        

<hr>



### function set\_step\_method 

_Set the step method for the integrator._ 
```C++
void astrea::astro::Integrator::set_step_method (
    const StepMethod & stepMethod
) 
```





**Parameters:**


* `stepMethod` The name of the step method to use (e.g., "RK45", "RKF45", etc.). 




        

<hr>



### function set\_timestep 

_Set the fixed timestep for the integrator._ 
```C++
void astrea::astro::Integrator::set_timestep (
    const Time & fixedTimeStep
) 
```





**Parameters:**


* `fixedTimeStep` The fixed timestep to set. 




        

<hr>



### function switch\_fixed\_timestep [1/2]

_Switch the fixed timestep mode on or off._ 
```C++
void astrea::astro::Integrator::switch_fixed_timestep (
    const bool & onOff
) 
```





**Parameters:**


* `onOff` Boolean flag to turn fixed timestep mode on (true) or off (false). 




        

<hr>



### function switch\_fixed\_timestep [2/2]

_Set the fixed timestep for the integrator._ 
```C++
void astrea::astro::Integrator::switch_fixed_timestep (
    const bool & onOff,
    const Time & fixedTimeStep
) 
```





**Parameters:**


* `fixedTimeStep` The fixed timestep to set. 




        

<hr>



### function switch\_print 

_Switch the printing of integration details on or off._ 
```C++
void astrea::astro::Integrator::switch_print (
    const bool & onOff
) 
```





**Parameters:**


* `onOff` Boolean flag to turn printing on (true) or off (false). 




        

<hr>



### function switch\_timer 

_Switch the timer for measuring integration performance on or off._ 
```C++
void astrea::astro::Integrator::switch_timer (
    const bool & onOff
) 
```





**Parameters:**


* `onOff` Boolean flag to turn the timer on (true) or off (false). 




        

<hr>



### function ~Integrator 

_Default destructor for the_ [_**Integrator**_](classastrea_1_1astro_1_1Integrator.md) _class._
```C++
astrea::astro::Integrator::~Integrator () = default
```




<hr>

------------------------------
The documentation for this class was generated from the following file `astrea/astro/astro/propagation/numerical/Integrator.hpp`

