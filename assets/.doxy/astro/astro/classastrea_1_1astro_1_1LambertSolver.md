

# Class astrea::astro::LambertSolver



[**ClassList**](annotated.md) **>** [**astrea**](namespaceastrea.md) **>** [**astro**](namespaceastrea_1_1astro.md) **>** [**LambertSolver**](classastrea_1_1astro_1_1LambertSolver.md)



_Class for solving Lambert's problem._ [More...](#detailed-description)

* `#include <LambertSolver.hpp>`















## Classes

| Type | Name |
| ---: | :--- |
| struct | [**Solution**](structastrea_1_1astro_1_1LambertSolver_1_1Solution.md) &lt;\_frame\_&gt;<br>_Result structure for optimal Lambert solutions._  |


## Public Types

| Type | Name |
| ---: | :--- |
| enum [**EnumType**](namespaceastrea_1_1astro.md#typedef-enumtype) | [**MultiRevBranch**](#enum-multirevbranch)  <br>_Enum class for the branch of a multi-revolution Lambert solution._  |
| enum [**EnumType**](namespaceastrea_1_1astro.md#typedef-enumtype) | [**OrbitDirection**](#enum-orbitdirection)  <br>_Enum class for orbit direction._  |
| enum [**EnumType**](namespaceastrea_1_1astro.md#typedef-enumtype) | [**SolutionType**](#enum-solutiontype)  <br>_Enum class for the type of optimal Lambert solution._  |




















## Public Functions

| Type | Name |
| ---: | :--- |
|   | [**LambertSolver**](#function-lambertsolver) () = delete<br>_Deleted constructor for_ [_**LambertSolver**_](classastrea_1_1astro_1_1LambertSolver.md) _._ |
|   | [**~LambertSolver**](#function-lambertsolver) () = delete<br>_Deleted destructor for_ [_**LambertSolver**_](classastrea_1_1astro_1_1LambertSolver.md) _._ |


## Public Static Functions

| Type | Name |
| ---: | :--- |
|  [**Cartesian**](classastrea_1_1astro_1_1Cartesian.md)&lt; \_frame\_ &gt; | [**solve**](#function-solve-14) ([**const**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) [**Cartesian**](classastrea_1_1astro_1_1Cartesian.md)&lt; \_frame\_ &gt; & state0, [**const**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) [**Time**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) & dt, [**const**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) [**GravParam**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) & mu) <br>_Solve Lambert's problem for a given initial and final state. Returns the minimum energy solution._  |
|  std::pair&lt; [**VelocityVector**](namespaceastrea_1_1astro.md#typedef-velocityvector)&lt; \_frame\_ &gt;, [**VelocityVector**](namespaceastrea_1_1astro.md#typedef-velocityvector)&lt; \_frame\_ &gt; &gt; | [**solve**](#function-solve-24) ([**const**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) [**RadiusVector**](namespaceastrea_1_1astro.md#typedef-radiusvector)&lt; \_frame\_ &gt; & r0, [**const**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) [**RadiusVector**](namespaceastrea_1_1astro.md#typedef-radiusvector)&lt; \_frame\_ &gt; & rf, [**const**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) [**Time**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) & dt, [**const**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) [**GravParam**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) & mu, [**const**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) [**OrbitDirection**](classastrea_1_1astro_1_1LambertSolver.md#enum-orbitdirection) & direction) <br>_Solve Lambert's problem for a given initial and final state. Returns the minimum energy solution._  |
|  [**Solution**](structastrea_1_1astro_1_1LambertSolver_1_1Solution.md)&lt; \_frame\_ &gt; | [**solve**](#function-solve-34) ([**const**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) [**RadiusVector**](namespaceastrea_1_1astro.md#typedef-radiusvector)&lt; \_frame\_ &gt; & r0, [**const**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) [**RadiusVector**](namespaceastrea_1_1astro.md#typedef-radiusvector)&lt; \_frame\_ &gt; & rf, [**const**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) [**GravParam**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) & mu, [**const**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) [**OrbitDirection**](classastrea_1_1astro_1_1LambertSolver.md#enum-orbitdirection) & direction, [**const**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) [**SolutionType**](classastrea_1_1astro_1_1LambertSolver.md#enum-solutiontype) & solutionType) <br>_Solve Lambert's problem for an optimal trajectory without a fixed time of flight._  |
|  std::pair&lt; [**VelocityVector**](namespaceastrea_1_1astro.md#typedef-velocityvector)&lt; \_frame\_ &gt;, [**VelocityVector**](namespaceastrea_1_1astro.md#typedef-velocityvector)&lt; \_frame\_ &gt; &gt; | [**solve**](#function-solve-44) ([**const**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) [**RadiusVector**](namespaceastrea_1_1astro.md#typedef-radiusvector)&lt; \_frame\_ &gt; & r0, [**const**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) [**RadiusVector**](namespaceastrea_1_1astro.md#typedef-radiusvector)&lt; \_frame\_ &gt; & rf, [**const**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) [**Time**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) & dt, [**const**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) [**GravParam**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) & mu, [**const**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) [**OrbitDirection**](classastrea_1_1astro_1_1LambertSolver.md#enum-orbitdirection) & direction, [**unsigned**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) N, [**const**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) [**MultiRevBranch**](classastrea_1_1astro_1_1LambertSolver.md#enum-multirevbranch) & branch) <br>_Solve Lambert's problem for a multi-revolution transfer with a fixed time of flight._  |


























## Detailed Description


This class provides methods for solving Lambert's problem, which involves finding the orbital trajectory between two points in space given certain initial conditions. 


    
## Public Types Documentation




### enum MultiRevBranch 

_Enum class for the branch of a multi-revolution Lambert solution._ 
```C++
enum astrea::astro::LambertSolver::MultiRevBranch {
    LEFT,
    RIGHT
};
```



For N &gt; 0 revolutions two solutions exist on either side of the minimum-time orbit. LEFT (low-energy) has a longer time of flight; RIGHT (high-energy) has a shorter one. 


        

<hr>



### enum OrbitDirection 

_Enum class for orbit direction._ 
```C++
enum astrea::astro::LambertSolver::OrbitDirection {
    PROGRADE,
    RETROGRADE
};
```




<hr>



### enum SolutionType 

_Enum class for the type of optimal Lambert solution._ 
```C++
enum astrea::astro::LambertSolver::SolutionType {
    MINIMUM_ENERGY,
    MINIMUM_TIME
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




### function solve [1/4]

_Solve Lambert's problem for a given initial and final state. Returns the minimum energy solution._ 
```C++
template<IsFrame auto _frame_>
static inline Cartesian < _frame_ > astrea::astro::LambertSolver::solve (
    const  Cartesian < _frame_ > & state0,
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



### function solve [2/4]

_Solve Lambert's problem for a given initial and final state. Returns the minimum energy solution._ 
```C++
template<IsFrame auto _frame_>
static inline std::pair< VelocityVector < _frame_ >, VelocityVector < _frame_ > > astrea::astro::LambertSolver::solve (
    const  RadiusVector < _frame_ > & r0,
    const  RadiusVector < _frame_ > & rf,
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



### function solve [3/4]

_Solve Lambert's problem for an optimal trajectory without a fixed time of flight._ 
```C++
template<IsFrame auto _frame_>
static inline Solution < _frame_ > astrea::astro::LambertSolver::solve (
    const  RadiusVector < _frame_ > & r0,
    const  RadiusVector < _frame_ > & rf,
    const  GravParam & mu,
    const  OrbitDirection & direction,
    const  SolutionType & solutionType
) 
```





**Parameters:**


* `r0` The initial position of the spacecraft. 
* `rf` The final position of the spacecraft. 
* `mu` The gravitational parameter of the central body. 
* `direction` The direction of the orbit (prograde or retrograde). 
* `solutionType` MINIMUM\_ENERGY returns the minimum delta-v (minimum semi-major axis) transfer; MINIMUM\_TIME returns the minimum time of flight (parabolic) transfer. 



**Returns:**

A [**Solution**](structastrea_1_1astro_1_1LambertSolver_1_1Solution.md) containing the time of flight and the initial/final velocity vectors. 





        

<hr>



### function solve [4/4]

_Solve Lambert's problem for a multi-revolution transfer with a fixed time of flight._ 
```C++
template<IsFrame auto _frame_>
static inline std::pair< VelocityVector < _frame_ >, VelocityVector < _frame_ > > astrea::astro::LambertSolver::solve (
    const  RadiusVector < _frame_ > & r0,
    const  RadiusVector < _frame_ > & rf,
    const  Time & dt,
    const  GravParam & mu,
    const  OrbitDirection & direction,
    unsigned N,
    const  MultiRevBranch & branch
) 
```



For N &gt; 0 complete revolutions two solutions exist (LEFT and RIGHT branches); this overload returns the requested branch. The caller must supply a time of flight that exceeds the minimum possible multi-rev TOF (i.e. dt &gt; T\_min(N)), otherwise a std::runtime\_error is thrown.




**Parameters:**


* `r0` The initial position of the spacecraft. 
* `rf` The final position of the spacecraft. 
* `dt` The desired time of flight. 
* `mu` The gravitational parameter of the central body. 
* `direction` The direction of the orbit (prograde or retrograde). 
* `N` The number of complete revolutions (must be ≥ 1). 
* `branch` Which of the two solutions to return (LEFT or RIGHT). 



**Returns:**

A pair of velocity vectors (initial and final) for the spacecraft.




**Note:**

: Multi-revolution Lambert solver (Gooding 1990 / Lancaster-Blanchard x-parameter)


Normalisation (Gooding 1990): n = (R0 + Rf) / 2 [km] λ = √(R0·Rf) · cos(Δθ/2) / n [−] (λ ∈ [0,1]) τ = √(2μ/n³) · dt / 2 [−] (normalised half-TOF)


TOF equation (Eq. 16): T(x) = [N·π + atan2(σ, x) − λ·x·σ] / (1 − x²) where σ = √(1 − λ²x²), x ∈ (−1, 1)


For N ≥ 1 there are two solutions separated by x\* (argmin of T): LEFT branch (x &lt; x\*): lower-energy, longer TOF RIGHT branch (x &gt; x\*): higher-energy, shorter TOF


After finding x, the semi-latus rectum is: p = n · (1−λ²) · (1−x²) / σ² and the f-and-g functions give the velocities. 


        

<hr>

------------------------------
The documentation for this class was generated from the following file `astrea/astro/astro/propagation/analytic/LambertSolver.hpp`

