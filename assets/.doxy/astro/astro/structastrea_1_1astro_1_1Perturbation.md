

# Struct astrea::astro::Perturbation



[**ClassList**](annotated.md) **>** [**astrea**](namespaceastrea.md) **>** [**astro**](namespaceastrea_1_1astro.md) **>** [**Perturbation**](structastrea_1_1astro_1_1Perturbation.md)



_Struct to hold the results of a perturbation force computation, including both acceleration and torque._ 

* `#include <Perturbation.hpp>`





















## Public Attributes

| Type | Name |
| ---: | :--- |
|  [**ForceVector**](namespaceastrea_1_1astro.md#typedef-forcevector)&lt; frames::primary &gt; | [**force**](#variable-force)   = `{ 0.0 \* mp\_units::si::unit\_symbols::N }`<br>_The computed force vector due to the perturbing force._  |
|  [**TorqueVector**](namespaceastrea_1_1astro.md#typedef-torquevector)&lt; frames::primary &gt; | [**torque**](#variable-torque)   = `{ 0.0 \* mp\_units::si::unit\_symbols::N \* mp\_units::si::unit\_symbols::m }`<br>_The computed torque vector due to the perturbing force._  |












































## Public Attributes Documentation




### variable force 

_The computed force vector due to the perturbing force._ 
```C++
ForceVector<frames::primary> astrea::astro::Perturbation::force;
```




<hr>



### variable torque 

_The computed torque vector due to the perturbing force._ 
```C++
TorqueVector<frames::primary> astrea::astro::Perturbation::torque;
```




<hr>

------------------------------
The documentation for this class was generated from the following file `astrea/astro/astro/propagation/force_models/Perturbation.hpp`

