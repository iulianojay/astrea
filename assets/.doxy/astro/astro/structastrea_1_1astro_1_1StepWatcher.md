

# Struct astrea::astro::StepWatcher



[**ClassList**](annotated.md) **>** [**astrea**](namespaceastrea.md) **>** [**astro**](namespaceastrea_1_1astro.md) **>** [**StepWatcher**](structastrea_1_1astro_1_1StepWatcher.md)



_Function wrapper class for watching the state of the integrator at each step. This can be used for plotting or logging the state during propagation._ 

* `#include <StepWatcher.hpp>`





































## Public Functions

| Type | Name |
| ---: | :--- |
|   | [**StepWatcher**](#function-stepwatcher-12) () = default<br>_Default constructor for_ [_**StepWatcher**_](structastrea_1_1astro_1_1StepWatcher.md) _._ |
|   | [**StepWatcher**](#function-stepwatcher-22) ([**T**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) && func) <br>_Constructor for_ [_**StepWatcher**_](structastrea_1_1astro_1_1StepWatcher.md) _that takes a function to be called at each step of the integration._ |
|  [**void**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) | [**operator()**](#function-operator) ([**const**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) [**Time**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) & time, [**const**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) [**State**](classastrea_1_1astro_1_1State.md) & state, [**const**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) [**Vehicle**](classastrea_1_1astro_1_1Vehicle.md) & vehicle) const<br>_Call the stored function with the given time, state, and vehicle._  |




























## Public Functions Documentation




### function StepWatcher [1/2]

_Default constructor for_ [_**StepWatcher**_](structastrea_1_1astro_1_1StepWatcher.md) _._
```C++
astrea::astro::StepWatcher::StepWatcher () = default
```




<hr>



### function StepWatcher [2/2]

_Constructor for_ [_**StepWatcher**_](structastrea_1_1astro_1_1StepWatcher.md) _that takes a function to be called at each step of the integration._
```C++
template<typename  T>
inline astrea::astro::StepWatcher::StepWatcher (
    T && func
) 
```





**Parameters:**


* `func` The function to be called at each step of the integration. 




        

<hr>



### function operator() 

_Call the stored function with the given time, state, and vehicle._ 
```C++
inline void astrea::astro::StepWatcher::operator() (
    const  Time & time,
    const  State & state,
    const  Vehicle & vehicle
) const
```





**Parameters:**


* `time` The current time of the integration step. 
* `state` The current state of the vehicle at this integration step. 
* `vehicle` The vehicle being propagated. 




        

<hr>

------------------------------
The documentation for this class was generated from the following file `astrea/astro/astro/propagation/numerical/StepWatcher.hpp`

