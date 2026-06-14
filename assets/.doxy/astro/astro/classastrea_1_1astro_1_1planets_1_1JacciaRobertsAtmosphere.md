

# Class astrea::astro::planets::JacciaRobertsAtmosphere



[**ClassList**](annotated.md) **>** [**astrea**](namespaceastrea.md) **>** [**astro**](namespaceastrea_1_1astro.md) **>** [**planets**](namespaceastrea_1_1astro_1_1planets.md) **>** [**JacciaRobertsAtmosphere**](classastrea_1_1astro_1_1planets_1_1JacciaRobertsAtmosphere.md)



_The Jaccia-Roberts atmospheric model for_ [_**Earth**_](structastrea_1_1astro_1_1planets_1_1Earth.md) _._

* `#include <JacciaRoberts.hpp>`





































## Public Functions

| Type | Name |
| ---: | :--- |
|   | [**JacciaRobertsAtmosphere**](#function-jacciarobertsatmosphere) () = delete<br>_Deleted constructor._  |


## Public Static Functions

| Type | Name |
| ---: | :--- |
|  [**Density**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) | [**find\_atmospheric\_density**](#function-find_atmospheric_density) ([**const**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) [**State**](classastrea_1_1astro_1_1State.md) & state, [**const**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) [**Distance**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) equitorialRadius, [**const**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) [**Distance**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) polarRadius) <br>_Find the atmospheric density at a given state using the Jaccia-Roberts atmospheric model._  |


























## Public Functions Documentation




### function JacciaRobertsAtmosphere 

_Deleted constructor._ 
```C++
astrea::astro::planets::JacciaRobertsAtmosphere::JacciaRobertsAtmosphere () = delete
```




<hr>
## Public Static Functions Documentation




### function find\_atmospheric\_density 

_Find the atmospheric density at a given state using the Jaccia-Roberts atmospheric model._ 
```C++
static Density astrea::astro::planets::JacciaRobertsAtmosphere::find_atmospheric_density (
    const  State & state,
    const  Distance equitorialRadius,
    const  Distance polarRadius
) 
```





**Returns:**

Density The atmospheric density at the given state. 





        

<hr>

------------------------------
The documentation for this class was generated from the following file `astrea/astro/astro/systems/celestial_bodies/Earth/atmosphere/JacciaRoberts.hpp`

