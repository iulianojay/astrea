

# Class astrea::astro::planets::NRLMSISE00Atmosphere



[**ClassList**](annotated.md) **>** [**astrea**](namespaceastrea.md) **>** [**astro**](namespaceastrea_1_1astro.md) **>** [**planets**](namespaceastrea_1_1astro_1_1planets.md) **>** [**NRLMSISE00Atmosphere**](classastrea_1_1astro_1_1planets_1_1NRLMSISE00Atmosphere.md)



_The NRLMSISE-00 atmospheric model for_ [_**Earth**_](structastrea_1_1astro_1_1planets_1_1Earth.md) _._[More...](#detailed-description)

* `#include <NRLMSISE00.hpp>`





































## Public Functions

| Type | Name |
| ---: | :--- |
|   | [**NRLMSISE00Atmosphere**](#function-nrlmsise00atmosphere) () = delete<br>_Deleted constructor — use static factory or find\_atmospheric\_density directly._  |


## Public Static Functions

| Type | Name |
| ---: | :--- |
|  [**Density**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) | [**find\_atmospheric\_density**](#function-find_atmospheric_density) ([**const**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) [**State**](classastrea_1_1astro_1_1State.md) & state, [**double**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) f107a, [**double**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) f107, [**const**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) std::array&lt; [**double**](classastrea_1_1astro_1_1DirectionCosineMatrix.md), 7 &gt; & ap) <br>_Find the atmospheric density at a given state using the NRLMSISE-00 model._  |


























## Detailed Description


Implements the 2001 Naval Research Laboratory Mass Spectrometer and Incoherent Scatter Radar Exosphere (NRLMSISE-00) model. Provides density from the surface to lower exosphere (0 to 1000 km).


Space weather inputs required:
* f107a: 81-day average of F10.7 solar flux (centered on day)
* f107: daily F10.7 solar flux for previous day
* ap[7]: geomagnetic Ap array: [0] daily Ap [1] 3-hr ap for current time [2] 3-hr ap for 3 hrs before current time [3] 3-hr ap for 6 hrs before current time [4] 3-hr ap for 9 hrs before current time [5] average of eight 3-hr ap indices from 12 to 33 hrs prior [6] average of eight 3-hr ap indices from 36 to 57 hrs prior




Switches (indices 1–23, all default to 1): 0 = off, 1 = on, 2 = main effects off but cross terms on. Switch 9: set to 1 for daily Ap only, -1 to use full ap array.




**Authors:**

Mike Picone & al (Naval Research Laboratory), 2001: original FORTRAN 




**Authors:**

Dominik Brodowski, 2004: C translation 




**Authors:**

Pascal Parraud, 2016: Java translation (Orekit) 




**Authors:**

Jay Iuliano, 2026: C++ translation (Astrea) 





    
## Public Functions Documentation




### function NRLMSISE00Atmosphere 

_Deleted constructor — use static factory or find\_atmospheric\_density directly._ 
```C++
astrea::astro::planets::NRLMSISE00Atmosphere::NRLMSISE00Atmosphere () = delete
```




<hr>
## Public Static Functions Documentation




### function find\_atmospheric\_density 

_Find the atmospheric density at a given state using the NRLMSISE-00 model._ 
```C++
static Density astrea::astro::planets::NRLMSISE00Atmosphere::find_atmospheric_density (
    const  State & state,
    double f107a,
    double f107,
    const std::array< double , 7 > & ap
) 
```



Uses all 23 switches set to 1 (standard configuration).




**Parameters:**


* `state` The current spacecraft state. 
* `f107a` 81-day average F10.7 solar flux. 
* `f107` Daily F10.7 solar flux for previous day. 
* `ap` Array of 7 geomagnetic Ap values (see class documentation). 



**Returns:**

Density Total mass density (kg/m³) including anomalous oxygen. 





        

<hr>

------------------------------
The documentation for this class was generated from the following file `astrea/astro/astro/systems/celestial_bodies/Earth/atmosphere/NRLMSISE00.hpp`

