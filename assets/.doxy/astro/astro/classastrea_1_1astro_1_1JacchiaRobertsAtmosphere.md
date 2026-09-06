

# Class astrea::astro::JacchiaRobertsAtmosphere



[**ClassList**](annotated.md) **>** [**astrea**](namespaceastrea.md) **>** [**astro**](namespaceastrea_1_1astro.md) **>** [**JacchiaRobertsAtmosphere**](classastrea_1_1astro_1_1JacchiaRobertsAtmosphere.md)



_The Jaccia-Roberts atmospheric model for Earth._ 

* `#include <JacchiaRoberts.hpp>`





































## Public Functions

| Type | Name |
| ---: | :--- |
|   | [**JacchiaRobertsAtmosphere**](#function-jacchiarobertsatmosphere) () = delete<br>_Deleted constructor._  |


## Public Static Functions

| Type | Name |
| ---: | :--- |
|  Density | [**find\_atmospheric\_density**](#function-find_atmospheric_density) (const [**State**](classastrea_1_1astro_1_1State.md) & state, const Distance equitorialRadius, const Distance polarRadius) <br>_Find the atmospheric density at a given state using the Jaccia-Roberts atmospheric model._  |


























## Public Functions Documentation




### function JacchiaRobertsAtmosphere 

_Deleted constructor._ 
```C++
astrea::astro::JacchiaRobertsAtmosphere::JacchiaRobertsAtmosphere () = delete
```




<hr>
## Public Static Functions Documentation




### function find\_atmospheric\_density 

_Find the atmospheric density at a given state using the Jaccia-Roberts atmospheric model._ 
```C++
static Density astrea::astro::JacchiaRobertsAtmosphere::find_atmospheric_density (
    const State & state,
    const Distance equitorialRadius,
    const Distance polarRadius
) 
```





**Returns:**

Density The atmospheric density at the given state. 





        

<hr>

------------------------------
The documentation for this class was generated from the following file `astrea/astro/astro/propagation/force_models/space_weather/atmosphere/JacchiaRoberts.hpp`

