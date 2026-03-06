

# Class astrea::astro::LambertSolver



[**ClassList**](annotated.md) **>** [**astrea**](namespaceastrea.md) **>** [**astro**](namespaceastrea_1_1astro.md) **>** [**LambertSolver**](classastrea_1_1astro_1_1LambertSolver.md)



_Class for solving Lambert's problem._ [More...](#detailed-description)

* `#include <LambertSolver.hpp>`

















## Public Types

| Type | Name |
| ---: | :--- |
| enum [**EnumType**](namespaceastrea_1_1astro.md#typedef-enumtype) | [**OrbitDirection**](#enum-orbitdirection)  <br>_Enum class for orbit direction._  |




















## Public Functions

| Type | Name |
| ---: | :--- |
|   | [**LambertSolver**](#function-lambertsolver) () = delete<br>_Deleted constructor for_ [_**LambertSolver**_](classastrea_1_1astro_1_1LambertSolver.md) _._ |
|   | [**~LambertSolver**](#function-lambertsolver) () = delete<br>_Deleted destructor for_ [_**LambertSolver**_](classastrea_1_1astro_1_1LambertSolver.md) _._ |


## Public Static Functions

| Type | Name |
| ---: | :--- |
|  [**Cartesian**](classastrea_1_1astro_1_1Cartesian.md) | [**solve**](#function-solve-12) ([**const**](classastrea_1_1astro_1_1CartesianVector.md) [**Cartesian**](classastrea_1_1astro_1_1Cartesian.md) & state0, [**const**](classastrea_1_1astro_1_1CartesianVector.md) [**Time**](classastrea_1_1astro_1_1CartesianVector.md) & dt, [**const**](classastrea_1_1astro_1_1CartesianVector.md) [**GravParam**](classastrea_1_1astro_1_1CartesianVector.md) & mu) <br>_Solve Lambert's problem for a given initial and final state. Returns the minimum energy solution._  |
|  std::pair&lt; [**VelocityVector**](namespaceastrea_1_1astro.md#typedef-velocityvector)&lt; [**frames::earth::icrf**](structastrea_1_1astro_1_1InertialFrame.md) &gt;, [**VelocityVector**](namespaceastrea_1_1astro.md#typedef-velocityvector)&lt; [**frames::earth::icrf**](structastrea_1_1astro_1_1InertialFrame.md) &gt; &gt; | [**solve**](#function-solve-22) ([**const**](classastrea_1_1astro_1_1CartesianVector.md) [**RadiusVector**](namespaceastrea_1_1astro.md#typedef-radiusvector)&lt; [**frames::earth::icrf**](structastrea_1_1astro_1_1InertialFrame.md) &gt; & r0, [**const**](classastrea_1_1astro_1_1CartesianVector.md) [**RadiusVector**](namespaceastrea_1_1astro.md#typedef-radiusvector)&lt; [**frames::earth::icrf**](structastrea_1_1astro_1_1InertialFrame.md) &gt; & rf, [**const**](classastrea_1_1astro_1_1CartesianVector.md) [**Time**](classastrea_1_1astro_1_1CartesianVector.md) & dt, [**const**](classastrea_1_1astro_1_1CartesianVector.md) [**GravParam**](classastrea_1_1astro_1_1CartesianVector.md) & mu, [**const**](classastrea_1_1astro_1_1CartesianVector.md) [**OrbitDirection**](classastrea_1_1astro_1_1LambertSolver.md#enum-orbitdirection) & direction) <br>_Solve Lambert's problem for a given initial and final state. Returns the minimum energy solution._  |


























## Detailed Description


This class provides methods for solving Lambert's problem, which involves finding the orbital trajectory between two points in space given certain initial conditions. 


    
## Public Types Documentation




### enum OrbitDirection 

_Enum class for orbit direction._ 
```C++
enum astrea::astro::LambertSolver::OrbitDirection {
    PROGRADE,
    RETROGRADE
};
```




<hr>
## Public Functions Documentation




### function LambertSolver 

_Deleted constructor for_ [_**LambertSolver**_](classastrea_1_1astro_1_1LambertSolver.md) _._
```C++
astrea::astro::LambertSolver::LambertSolver () = delete
```



This constructor is deleted to prevent instantiation of the [**LambertSolver**](classastrea_1_1astro_1_1LambertSolver.md) class. 


        

<hr>



### function ~LambertSolver 

_Deleted destructor for_ [_**LambertSolver**_](classastrea_1_1astro_1_1LambertSolver.md) _._
```C++
astrea::astro::LambertSolver::~LambertSolver () = delete
```



This destructor is deleted to prevent destruction of the [**LambertSolver**](classastrea_1_1astro_1_1LambertSolver.md) class. 


        

<hr>
## Public Static Functions Documentation




### function solve [1/2]

_Solve Lambert's problem for a given initial and final state. Returns the minimum energy solution._ 
```C++
static Cartesian astrea::astro::LambertSolver::solve (
    const  Cartesian & state0,
    const  Time & dt,
    const  GravParam & mu
) 
```





**Parameters:**


* `state0` The initial state (position and velocity) of the spacecraft. 
* `dt` The time of flight. 
* `mu` The gravitational parameter of the central body. 



**Returns:**

The final state (position and velocity) of the spacecraft. 





        

<hr>



### function solve [2/2]

_Solve Lambert's problem for a given initial and final state. Returns the minimum energy solution._ 
```C++
static std::pair< VelocityVector < frames::earth::icrf >, VelocityVector < frames::earth::icrf > > astrea::astro::LambertSolver::solve (
    const  RadiusVector < frames::earth::icrf > & r0,
    const  RadiusVector < frames::earth::icrf > & rf,
    const  Time & dt,
    const  GravParam & mu,
    const  OrbitDirection & direction
) 
```





**Parameters:**


* `r0` The initial position of the spacecraft. 
* `rf` The final position of the spacecraft. 
* `dt` The time of flight. 
* `mu` The gravitational parameter of the central body. 
* `direction` The direction of the orbit (prograde or retrograde). 



**Returns:**

A pair of velocity vectors (initial and final) for the spacecraft. 





        

<hr>

------------------------------
The documentation for this class was generated from the following file `astrea/astro/astro/propagation/analytic/LambertSolver.hpp`

