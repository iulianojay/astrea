

# Struct astrea::astro::planets::SpeciesModelParams



[**ClassList**](annotated.md) **>** [**astrea**](namespaceastrea.md) **>** [**astro**](namespaceastrea_1_1astro.md) **>** [**planets**](namespaceastrea_1_1astro_1_1planets.md) **>** [**SpeciesModelParams**](structastrea_1_1astro_1_1planets_1_1SpeciesModelParams.md)



_Per-species empirical parameters for NRLMSISE-00 diffusive and mixed-region density calculations._ 






















## Public Attributes

| Type | Name |
| ---: | :--- |
|  [**Unitless**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) | [**c3**](#variable-c3)  <br>_species-specific: zhm scale height (N2) or rc correction ratio (O, O2, H, N)_  |
|  [**Unitless**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) | [**c9**](#variable-c9)  <br>_anomalous O only: secondary thermal reference parameter_  |
|  [**Distance**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) | [**ha**](#variable-ha)  <br>_primary ccor correction scale height_  |
|  [**Distance**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) | [**hb**](#variable-hb)  <br>_secondary ccor correction scale height_  |
|  [**Unitless**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) | [**mix\_ratio**](#variable-mix_ratio)  <br>_dimensionless: mixing ratio / density correction factor_  |
|  NumberDensity | [**n\_ref**](#variable-n_ref)  <br>_cm⁻³: reference number density at lower boundary_  |
|  [**Distance**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) | [**za**](#variable-za)  <br>_primary ccor correction centre altitude (N2: unused, set to 0)_  |
|  [**Distance**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) | [**zb**](#variable-zb)  <br>_secondary ccor correction centre altitude_  |
|  [**Distance**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) | [**zh**](#variable-zh)  <br>_turbopause altitude_  |












































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



### variable mix\_ratio 

_dimensionless: mixing ratio / density correction factor_ 
```C++
Unitless astrea::astro::planets::SpeciesModelParams::mix_ratio;
```




<hr>



### variable n\_ref 

_cm⁻³: reference number density at lower boundary_ 
```C++
NumberDensity astrea::astro::planets::SpeciesModelParams::n_ref;
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
The documentation for this class was generated from the following file `astrea/astro/astro/systems/celestial_bodies/Earth/atmosphere/NRLMSISE00.cpp`

