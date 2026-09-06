

# Struct astrea::astro::planets::SpeciesModelParams



[**ClassList**](annotated.md) **>** [**astrea**](namespaceastrea.md) **>** [**astro**](namespaceastrea_1_1astro.md) **>** [**planets**](namespaceastrea_1_1astro_1_1planets.md) **>** [**SpeciesModelParams**](structastrea_1_1astro_1_1planets_1_1SpeciesModelParams.md)



_Per-species empirical parameters for NRLMSISE-00 diffusive and mixed-region density calculations._ 






















## Public Attributes

| Type | Name |
| ---: | :--- |
|  Unitless | [**c3**](#variable-c3)  <br>_species-specific: zhm scale height (N2) or rc correction ratio (O, O2, H, N)_  |
|  Unitless | [**c9**](#variable-c9)  <br>_anomalous O only: secondary thermal reference parameter_  |
|  Distance | [**ha**](#variable-ha)  <br>_primary ccor correction scale height_  |
|  Distance | [**hb**](#variable-hb)  <br>_secondary ccor correction scale height_  |
|  Unitless | [**mixRatio**](#variable-mixratio)  <br>_dimensionless: mixing ratio / density correction factor_  |
|  NumberDensity | [**nRef**](#variable-nref)  <br>_cm⁻³: reference number density at lower boundary_  |
|  Distance | [**za**](#variable-za)  <br>_primary ccor correction centre altitude (N2: unused, set to 0)_  |
|  Distance | [**zb**](#variable-zb)  <br>_secondary ccor correction centre altitude_  |
|  Distance | [**zh**](#variable-zh)  <br>_turbopause altitude_  |












































## Public Attributes Documentation




### variable c3 

_species-specific: zhm scale height (N2) or rc correction ratio (O, O2, H, N)_ 
```C++
Unitless astrea::astro::planets::SpeciesModelParams::c3;
```




<hr>



### variable c9 

_anomalous O only: secondary thermal reference parameter_ 
```C++
Unitless astrea::astro::planets::SpeciesModelParams::c9;
```




<hr>



### variable ha 

_primary ccor correction scale height_ 
```C++
Distance astrea::astro::planets::SpeciesModelParams::ha;
```




<hr>



### variable hb 

_secondary ccor correction scale height_ 
```C++
Distance astrea::astro::planets::SpeciesModelParams::hb;
```




<hr>



### variable mixRatio 

_dimensionless: mixing ratio / density correction factor_ 
```C++
Unitless astrea::astro::planets::SpeciesModelParams::mixRatio;
```




<hr>



### variable nRef 

_cm⁻³: reference number density at lower boundary_ 
```C++
NumberDensity astrea::astro::planets::SpeciesModelParams::nRef;
```




<hr>



### variable za 

_primary ccor correction centre altitude (N2: unused, set to 0)_ 
```C++
Distance astrea::astro::planets::SpeciesModelParams::za;
```




<hr>



### variable zb 

_secondary ccor correction centre altitude_ 
```C++
Distance astrea::astro::planets::SpeciesModelParams::zb;
```




<hr>



### variable zh 

_turbopause altitude_ 
```C++
Distance astrea::astro::planets::SpeciesModelParams::zh;
```




<hr>

------------------------------
The documentation for this class was generated from the following file `astrea/astro/astro/propagation/force_models/space_weather/atmosphere/experimental/NRLMSISE00.cpp`

