

# File NRLMSISE00.cpp



[**FileList**](files.md) **>** [**astrea**](dir_b5324400686b7cece921533bb760c87a.md) **>** [**astro**](dir_1d4dcf10fc541574a93624f5c09a3d6f.md) **>** [**astro**](dir_84db6e3c60e44147f5214c05dc45afc2.md) **>** [**propagation**](dir_55ae0edd352c6621ebfa1115f28a0fff.md) **>** [**force\_models**](dir_0ce51a85166db93c377c5b7f000b236c.md) **>** [**space\_weather**](dir_ba92a5bb4647772267966b3cef944594.md) **>** [**atmosphere**](dir_3bfcc16c8bbdb2d74b81ce33c082ff6e.md) **>** [**experimental**](dir_c9cd73a564506b77e0cd8e52337735df.md) **>** [**NRLMSISE00.cpp**](NRLMSISE00_8cpp.md)

[Go to the source code of this file](NRLMSISE00_8cpp_source.md)



* `#include <astro/propagation/force_models/space_weather/atmosphere/Nrlmsise00.hpp>`
* `#include <mp-units/math.h>`
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
| class | [**Output**](classastrea_1_1astro_1_1planets_1_1Output.md) <br> |
| struct | [**SpeciesModelParams**](structastrea_1_1astro_1_1planets_1_1SpeciesModelParams.md) <br>_Per-species empirical parameters for NRLMSISE-00 diffusive and mixed-region density calculations._  |
| struct | [**Switch**](structastrea_1_1astro_1_1planets_1_1Switch.md) <br> |


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
The documentation for this class was generated from the following file `astrea/astro/astro/propagation/force_models/space_weather/atmosphere/experimental/NRLMSISE00.cpp`

