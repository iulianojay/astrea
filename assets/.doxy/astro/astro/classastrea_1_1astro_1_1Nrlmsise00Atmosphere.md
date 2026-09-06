

# Class astrea::astro::Nrlmsise00Atmosphere



[**ClassList**](annotated.md) **>** [**astrea**](namespaceastrea.md) **>** [**astro**](namespaceastrea_1_1astro.md) **>** [**Nrlmsise00Atmosphere**](classastrea_1_1astro_1_1Nrlmsise00Atmosphere.md)










































## Public Functions

| Type | Name |
| ---: | :--- |
|   | [**Nrlmsise00Atmosphere**](#function-nrlmsise00atmosphere) () = delete<br>_Deleted constructor — use static factory or find\_atmospheric\_density directly._  |


## Public Static Functions

| Type | Name |
| ---: | :--- |
|  Density | [**find\_atmospheric\_density**](#function-find_atmospheric_density) (const [**State**](classastrea_1_1astro_1_1State.md) & state, const SolarFlux & f107a, const SolarFlux & f107, const std::array&lt; Unitless, 8 &gt; & ap, const std::array&lt; int, 24 &gt; & flags=get\_default\_flags(), const bool ignoreLowAltitudes=true) <br>_Find the atmospheric density at a given state and solar/geomagnetic conditions._  |


























## Public Functions Documentation




### function Nrlmsise00Atmosphere 

_Deleted constructor — use static factory or find\_atmospheric\_density directly._ 
```C++
astrea::astro::Nrlmsise00Atmosphere::Nrlmsise00Atmosphere () = delete
```




<hr>
## Public Static Functions Documentation




### function find\_atmospheric\_density 

_Find the atmospheric density at a given state and solar/geomagnetic conditions._ 
```C++
static Density astrea::astro::Nrlmsise00Atmosphere::find_atmospheric_density (
    const State & state,
    const SolarFlux & f107a,
    const SolarFlux & f107,
    const std::array< Unitless, 8 > & ap,
    const std::array< int, 24 > & flags=get_default_flags(),
    const bool ignoreLowAltitudes=true
) 
```





**Parameters:**


* `state` The current state of the satellite. 
* `f107a` The 81-day average of the F10.7 solar flux. 
* `f107` The daily F10.7 solar flux. 
* `ap` The array of geomagnetic indices. 
* `flags` The array of flags to set the model switches. 
* `ignoreLowAltitudes` If true, the model will ignore low altitudes and return a density of 0.0 for altitudes below 80 km. 



**Returns:**

The atmospheric density.











        

<hr>

------------------------------
The documentation for this class was generated from the following file `astrea/astro/astro/propagation/force_models/space_weather/atmosphere/Nrlmsise00.hpp`

