

# Class astrea::astro::Integrator



[**ClassList**](annotated.md) **>** [**astrea**](namespaceastrea.md) **>** [**astro**](namespaceastrea_1_1astro.md) **>** [**Integrator**](classastrea_1_1astro_1_1Integrator.md)



[_**Integrator**_](classastrea_1_1astro_1_1Integrator.md) _class for numerical propagation of orbital mechanics problems._[More...](#detailed-description)

* `#include <Integrator.hpp>`





































## Public Functions

| Type | Name |
| ---: | :--- |
|   | [**Integrator**](#function-integrator-12) () = default<br>_Default constructor for the_ [_**Integrator**_](classastrea_1_1astro_1_1Integrator.md) _class._ |
|   | [**Integrator**](#function-integrator-22) (const [**IntegratorSettings**](structastrea_1_1astro_1_1IntegratorSettings.md) & settings) <br>_Constructor for the_ [_**Integrator**_](classastrea_1_1astro_1_1Integrator.md) _class that takes an_[_**IntegratorSettings**_](structastrea_1_1astro_1_1IntegratorSettings.md) _struct._ |
|  void | [**add\_event**](#function-add_event) (const [**Event**](classastrea_1_1astro_1_1Event.md) & event) <br>_Add an event to the integrator's event detector._  |
|  void | [**add\_events**](#function-add_events) (const std::vector&lt; [**Event**](classastrea_1_1astro_1_1Event.md) &gt; & events) <br>_Add multiple events to the integrator's event detector._  |
|  void | [**add\_step\_watcher**](#function-add_step_watcher) (const [**StepWatcher**](structastrea_1_1astro_1_1StepWatcher.md) & watcher) <br>_Add a step watcher function to be called at each step of the integration._  |
|  void | [**clear**](#function-clear) () <br>_Clear the schedule of events, removing all scheduled events from the integrator._  |
|  void | [**clear\_events**](#function-clear_events) () <br>_Clear all events from the integrator's event detector._  |
|  void | [**clear\_watchers**](#function-clear_watchers) () <br>_Clear all step watchers from the integrator._  |
|  int | [**n\_func\_evals**](#function-n_func_evals) () <br>_Get the current timestep used by the integrator._  |
|  [**StateHistory**](classastrea_1_1astro_1_1StateHistory.md) | [**propagate**](#function-propagate-12) (const [**State**](classastrea_1_1astro_1_1State.md) & state0, const Time & propTime, [**Vehicle**](classastrea_1_1astro_1_1Vehicle.md) vehicle) <br>_Propagate the state of a vehicle over a specified time interval using the given equations of motion._  |
|  [**StateHistory**](classastrea_1_1astro_1_1StateHistory.md) | [**propagate**](#function-propagate-22) (const [**State**](classastrea_1_1astro_1_1State.md) & state0, const [**Date**](classastrea_1_1astro_1_1Date.md) & endEpoch, [**Vehicle**](classastrea_1_1astro_1_1Vehicle.md) vehicle) <br>_Propagate the state of a vehicle from its current epoch to a specified end epoch using the given equations of motion._  |
|  [**State**](classastrea_1_1astro_1_1State.md) | [**propagate\_no\_storage**](#function-propagate_no_storage-12) (const [**State**](classastrea_1_1astro_1_1State.md) & state0, const Time & propTime, [**Vehicle**](classastrea_1_1astro_1_1Vehicle.md) vehicle) <br>_Propagate the state of a vehicle over a specified time interval without storing the state history._  |
|  [**State**](classastrea_1_1astro_1_1State.md) | [**propagate\_no\_storage**](#function-propagate_no_storage-22) (const [**State**](classastrea_1_1astro_1_1State.md) & state0, const [**Date**](classastrea_1_1astro_1_1Date.md) & endEpoch, [**Vehicle**](classastrea_1_1astro_1_1Vehicle.md) vehicle) <br>_Propagate the state of a vehicle from its current epoch to a specified end epoch without storing the state history._  |
|  void | [**set\_abs\_tol**](#function-set_abs_tol) (const Unitless & absTol) <br>_Set the absolute tolerance for the integrator._  |
|  void | [**set\_equations\_of\_motion**](#function-set_equations_of_motion) (const T & eom) <br>_Set the equations of motion to be used for propagation._  |
|  void | [**set\_initial\_timestep**](#function-set_initial_timestep) (const Time & dt0) <br>_Set the initial timestep for the integrator._  |
|  void | [**set\_max\_iter**](#function-set_max_iter) (const int & itMax) <br>_Set the maximum number of iterations for the integrator._  |
|  void | [**set\_rel\_tol**](#function-set_rel_tol) (const Unitless & relTol) <br>_Set the relative tolerance for the integrator._  |
|  void | [**set\_schedule**](#function-set_schedule) (const [**Schedule**](classastrea_1_1astro_1_1Schedule.md) & schedule) <br>_Set the schedule of events to be tracked during propagation._  |
|  void | [**set\_step\_method**](#function-set_step_method) (const [**StepMethod**](namespaceastrea_1_1astro.md#enum-stepmethod) & stepMethod) <br>_Set the step method for the integrator._  |
|  void | [**set\_timestep**](#function-set_timestep) (const Time & fixedTimeStep) <br>_Set the fixed timestep for the integrator._  |
|  void | [**switch\_fixed\_timestep**](#function-switch_fixed_timestep-12) (const bool & onOff) <br>_Switch the fixed timestep mode on or off._  |
|  void | [**switch\_fixed\_timestep**](#function-switch_fixed_timestep-22) (const bool & onOff, const Time & fixedTimeStep) <br>_Set the fixed timestep for the integrator._  |
|   | [**~Integrator**](#function-integrator) () = default<br>_Default destructor for the_ [_**Integrator**_](classastrea_1_1astro_1_1Integrator.md) _class._ |




























## Detailed Description


This class implements various Runge-Kutta methods for integrating the equations of motion of a vehicle in space. It allows for variable step sizes, error control, and event handling. 


    
## Public Functions Documentation




### function Integrator [1/2]

_Default constructor for the_ [_**Integrator**_](classastrea_1_1astro_1_1Integrator.md) _class._
```C++
astrea::astro::Integrator::Integrator () = default
```




<hr>



### function Integrator [2/2]

_Constructor for the_ [_**Integrator**_](classastrea_1_1astro_1_1Integrator.md) _class that takes an_[_**IntegratorSettings**_](structastrea_1_1astro_1_1IntegratorSettings.md) _struct._
```C++
inline astrea::astro::Integrator::Integrator (
    const IntegratorSettings & settings
) 
```





**Parameters:**


* `settings` The settings to configure the integrator. 




        

<hr>



### function add\_event 

_Add an event to the integrator's event detector._ 
```C++
void astrea::astro::Integrator::add_event (
    const Event & event
) 
```





**Parameters:**


* `event` The [**Event**](classastrea_1_1astro_1_1Event.md) object to be added to the integrator's event detector. 




        

<hr>



### function add\_events 

_Add multiple events to the integrator's event detector._ 
```C++
void astrea::astro::Integrator::add_events (
    const std::vector< Event > & events
) 
```





**Parameters:**


* `events` A vector of [**Event**](classastrea_1_1astro_1_1Event.md) objects to be added to the integrator's event detector. 




        

<hr>



### function add\_step\_watcher 

_Add a step watcher function to be called at each step of the integration._ 
```C++
void astrea::astro::Integrator::add_step_watcher (
    const StepWatcher & watcher
) 
```





**Parameters:**


* `watcher` The [**StepWatcher**](structastrea_1_1astro_1_1StepWatcher.md) function to be added.



**Note:**

: beware - callbacks are slow 





        

<hr>



### function clear 

_Clear the schedule of events, removing all scheduled events from the integrator._ 
```C++
void astrea::astro::Integrator::clear () 
```




<hr>



### function clear\_events 

_Clear all events from the integrator's event detector._ 
```C++
void astrea::astro::Integrator::clear_events () 
```




<hr>



### function clear\_watchers 

_Clear all step watchers from the integrator._ 
```C++
void astrea::astro::Integrator::clear_watchers () 
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
    Vehicle vehicle
) 
```





**Parameters:**


* `state0` The initial state from which to start propagation. 
* `propTime` The total propagation time after the initial state epoch. 
* `vehicle` The vehicle whose state is to be propagated. 



**Returns:**

[**StateHistory**](classastrea_1_1astro_1_1StateHistory.md) The history of the vehicle's state over the propagated interval. 





        

<hr>



### function propagate [2/2]

_Propagate the state of a vehicle from its current epoch to a specified end epoch using the given equations of motion._ 
```C++
StateHistory astrea::astro::Integrator::propagate (
    const State & state0,
    const Date & endEpoch,
    Vehicle vehicle
) 
```





**Parameters:**


* `state0` The initial state from which to start propagation. 
* `endEpoch` The final epoch (end time) for the propagation. 
* `vehicle` The vehicle whose state is to be propagated. 



**Returns:**

[**StateHistory**](classastrea_1_1astro_1_1StateHistory.md) The history of the vehicle's state over the propagated interval. 





        

<hr>



### function propagate\_no\_storage [1/2]

_Propagate the state of a vehicle over a specified time interval without storing the state history._ 
```C++
State astrea::astro::Integrator::propagate_no_storage (
    const State & state0,
    const Time & propTime,
    Vehicle vehicle
) 
```





**Parameters:**


* `state0` The initial state from which to start propagation. 
* `propTime` The total propagation time after the initial state epoch. 
* `vehicle` The vehicle whose state is to be propagated. 



**Returns:**

[**State**](classastrea_1_1astro_1_1State.md) The final state of the vehicle at the end of the propagation interval. 





        

<hr>



### function propagate\_no\_storage [2/2]

_Propagate the state of a vehicle from its current epoch to a specified end epoch without storing the state history._ 
```C++
State astrea::astro::Integrator::propagate_no_storage (
    const State & state0,
    const Date & endEpoch,
    Vehicle vehicle
) 
```





**Parameters:**


* `state0` The initial state from which to start propagation. 
* `endEpoch` The final epoch (end time) for the propagation. 
* `vehicle` The vehicle whose state is to be propagated. 



**Returns:**

[**State**](classastrea_1_1astro_1_1State.md) The final state of the vehicle at the end of the propagation interval. 





        

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



### function set\_equations\_of\_motion 

_Set the equations of motion to be used for propagation._ 
```C++
template<typename T>
inline void astrea::astro::Integrator::set_equations_of_motion (
    const T & eom
) 
```





**Parameters:**


* `eom` The [**EquationsOfMotion**](classastrea_1_1astro_1_1EquationsOfMotion.md) object to be used for propagation. 




        

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



### function set\_schedule 

_Set the schedule of events to be tracked during propagation._ 
```C++
void astrea::astro::Integrator::set_schedule (
    const Schedule & schedule
) 
```





**Parameters:**


* `schedule` The [**Schedule**](classastrea_1_1astro_1_1Schedule.md) object containing the events to be tracked. 




        

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



### function ~Integrator 

_Default destructor for the_ [_**Integrator**_](classastrea_1_1astro_1_1Integrator.md) _class._
```C++
astrea::astro::Integrator::~Integrator () = default
```




<hr>

------------------------------
The documentation for this class was generated from the following file `astrea/astro/astro/propagation/numerical/Integrator.hpp`

