

# Struct astrea::astro::IntegratorSettings



[**ClassList**](annotated.md) **>** [**astrea**](namespaceastrea.md) **>** [**astro**](namespaceastrea_1_1astro.md) **>** [**IntegratorSettings**](structastrea_1_1astro_1_1IntegratorSettings.md)


























## Public Attributes

| Type | Name |
| ---: | :--- |
|  [**Unitless**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) | [**absTol**](#variable-abstol)   = `1.0e-13`<br>_Absolute tolerance for the integrator._  |
|  [**Time**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) | [**fixedTimeStep**](#variable-fixedtimestep)   = `30.0 \* mp\_units::si::unit\_symbols::s`<br>_Fixed timestep to use if useFixedStep is true._  |
|  [**Time**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) | [**initialTimeStep**](#variable-initialtimestep)   = `1.0 \* mp\_units::si::unit\_symbols::s`<br>_Initial timestep for the integrator._  |
|  [**int**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) | [**itMax**](#variable-itmax)   = `10000`<br>_Maximum number of iterations for the integrator._  |
|  [**Unitless**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) | [**relTol**](#variable-reltol)   = `1.0e-13`<br>_Relative tolerance for the integrator._  |
|  [**StepMethod**](namespaceastrea_1_1astro.md#enum-stepmethod) | [**stepMethod**](#variable-stepmethod)   = `StepMethod::RKF78`<br>_Step method for the integrator._  |
|  [**bool**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) | [**useFixedStep**](#variable-usefixedstep)   = `[**false**](classastrea_1_1astro_1_1DirectionCosineMatrix.md)`<br>_Flag to indicate whether to use a fixed timestep._  |












































## Public Attributes Documentation




### variable absTol 

_Absolute tolerance for the integrator._ 
```C++
Unitless astrea::astro::IntegratorSettings::absTol;
```




<hr>



### variable fixedTimeStep 

_Fixed timestep to use if useFixedStep is true._ 
```C++
Time astrea::astro::IntegratorSettings::fixedTimeStep;
```




<hr>



### variable initialTimeStep 

_Initial timestep for the integrator._ 
```C++
Time astrea::astro::IntegratorSettings::initialTimeStep;
```




<hr>



### variable itMax 

_Maximum number of iterations for the integrator._ 
```C++
int astrea::astro::IntegratorSettings::itMax;
```




<hr>



### variable relTol 

_Relative tolerance for the integrator._ 
```C++
Unitless astrea::astro::IntegratorSettings::relTol;
```




<hr>



### variable stepMethod 

_Step method for the integrator._ 
```C++
StepMethod astrea::astro::IntegratorSettings::stepMethod;
```




<hr>



### variable useFixedStep 

_Flag to indicate whether to use a fixed timestep._ 
```C++
bool astrea::astro::IntegratorSettings::useFixedStep;
```




<hr>

------------------------------
The documentation for this class was generated from the following file `astrea/astro/astro/propagation/numerical/Integrator.hpp`

