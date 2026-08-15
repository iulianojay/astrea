

# Class astrea::astro::planets::HarrisPriesterAtmosphere



[**ClassList**](annotated.md) **>** [**astrea**](namespaceastrea.md) **>** [**astro**](namespaceastrea_1_1astro.md) **>** [**planets**](namespaceastrea_1_1astro_1_1planets.md) **>** [**HarrisPriesterAtmosphere**](classastrea_1_1astro_1_1planets_1_1HarrisPriesterAtmosphere.md)



_The Harris-Priester atmospheric model for_ [_**Earth**_](structastrea_1_1astro_1_1planets_1_1Earth.md) _._

* `#include <HarrisPriester.hpp>`





































## Public Functions

| Type | Name |
| ---: | :--- |
|   | [**HarrisPriesterAtmosphere**](#function-harrispriesteratmosphere) () = delete<br>_Deleted constructor._  |


## Public Static Functions

| Type | Name |
| ---: | :--- |
|  Density | [**find\_atmospheric\_density**](#function-find_atmospheric_density) (const [**State**](classastrea_1_1astro_1_1State.md) & state) <br>_Find the atmospheric density at a given state using the Harris-Priester atmospheric model._  |


























## Public Functions Documentation




### function HarrisPriesterAtmosphere 

_Deleted constructor._ 
```C++
astrea::astro::planets::HarrisPriesterAtmosphere::HarrisPriesterAtmosphere () = delete
```




<hr>
## Public Static Functions Documentation




### function find\_atmospheric\_density 

_Find the atmospheric density at a given state using the Harris-Priester atmospheric model._ 
```C++
static Density astrea::astro::planets::HarrisPriesterAtmosphere::find_atmospheric_density (
    const State & state
) 
```





**Returns:**

Density The atmospheric density at the given state. 





        

<hr>

------------------------------
The documentation for this class was generated from the following file `astrea/astro/astro/systems/celestial_bodies/Earth/atmosphere/HarrisPriester.hpp`

