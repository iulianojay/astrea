

# File NRLMSISE00.cpp



[**FileList**](files.md) **>** [**astrea**](dir_b5324400686b7cece921533bb760c87a.md) **>** [**astro**](dir_1d4dcf10fc541574a93624f5c09a3d6f.md) **>** [**astro**](dir_84db6e3c60e44147f5214c05dc45afc2.md) **>** [**systems**](dir_a5d35e082abd602943cf6d70fa2a6872.md) **>** [**celestial\_bodies**](dir_b988f8927672605e377af1c3b431ef9b.md) **>** [**Earth**](dir_0d926747df7aa4605536658442a7f1d2.md) **>** [**atmosphere**](dir_52ad4357f9588f54fe1e3d5cf2b75c1b.md) **>** [**NRLMSISE00.cpp**](NRLMSISE00_8cpp.md)

[Go to the source code of this file](NRLMSISE00_8cpp_source.md)



* `#include <astro/systems/celestial_bodies/Earth/atmosphere/JacciaRoberts.hpp>`
* `#include <mp-units/core.h>`
* `#include <mp-units/systems/angular.h>`
* `#include <mp-units/systems/hep.h>`
* `#include <mp-units/systems/si.h>`













## Namespaces

| Type | Name |
| ---: | :--- |
| namespace | [**astrea**](namespaceastrea.md) <br> |
| namespace | [**astro**](namespaceastrea_1_1astro.md) <br> |
| namespace | [**planets**](namespaceastrea_1_1astro_1_1planets.md) <br> |


## Classes

| Type | Name |
| ---: | :--- |
| struct | [**BatesProfileParams**](structastrea_1_1astro_1_1planets_1_1BatesProfileParams.md) <br> |
| class | [**NRLMSISE00**](classastrea_1_1astro_1_1planets_1_1NRLMSISE00.md) <br> |
| struct | [**SpeciesModelParams**](structastrea_1_1astro_1_1planets_1_1SpeciesModelParams.md) <br>_Per-species empirical parameters for NRLMSISE-00 diffusive and mixed-region density calculations._  |


## Public Types

| Type | Name |
| ---: | :--- |
| typedef quantity&lt; u &gt; | [**AtomicMass**](#typedef-atomicmass)  <br> |
| typedef quantity&lt; one/pow&lt; 3 &gt;(m)&gt; | [**NumberDensity**](#typedef-numberdensity)  <br> |
















































## Public Types Documentation




### typedef AtomicMass 

```C++
using AtomicMass =  quantity<u>;
```




<hr>



### typedef NumberDensity 

```C++
using NumberDensity =  quantity<one / pow<3>(m)>;
```




<hr>

------------------------------
The documentation for this class was generated from the following file `astrea/astro/astro/systems/celestial_bodies/Earth/atmosphere/NRLMSISE00.cpp`

