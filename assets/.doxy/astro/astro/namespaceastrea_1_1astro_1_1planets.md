

# Namespace astrea::astro::planets



[**Namespace List**](namespaces.md) **>** [**astrea**](namespaceastrea.md) **>** [**astro**](namespaceastrea_1_1astro.md) **>** [**planets**](namespaceastrea_1_1astro_1_1planets.md)




















## Classes

| Type | Name |
| ---: | :--- |
| struct | [**BatesProfileParams**](structastrea_1_1astro_1_1planets_1_1BatesProfileParams.md) <br> |
| class | [**Earth**](structastrea_1_1astro_1_1planets_1_1Earth.md) <br>_Represents the_ [_**Earth**_](structastrea_1_1astro_1_1planets_1_1Earth.md) _celestial body._ |
| struct | [**EarthParameters**](structastrea_1_1astro_1_1planets_1_1EarthParameters.md) <br> |
| class | [**HarrisPriesterAtmosphere**](classastrea_1_1astro_1_1planets_1_1HarrisPriesterAtmosphere.md) <br>_The Harris-Priester atmospheric model for_ [_**Earth**_](structastrea_1_1astro_1_1planets_1_1Earth.md) _._ |
| class | [**JacciaRobertsAtmosphere**](classastrea_1_1astro_1_1planets_1_1JacciaRobertsAtmosphere.md) <br>_The Jaccia-Roberts atmospheric model for_ [_**Earth**_](structastrea_1_1astro_1_1planets_1_1Earth.md) _._ |
| class | [**Jupiter**](structastrea_1_1astro_1_1planets_1_1Jupiter.md) <br>_Represents the_ [_**Jupiter**_](structastrea_1_1astro_1_1planets_1_1Jupiter.md) _celestial body._ |
| class | [**Mars**](structastrea_1_1astro_1_1planets_1_1Mars.md) <br>_Represents the_ [_**Mars**_](structastrea_1_1astro_1_1planets_1_1Mars.md) _celestial body._ |
| class | [**Mercury**](structastrea_1_1astro_1_1planets_1_1Mercury.md) <br>_Represents the_ [_**Mercury**_](structastrea_1_1astro_1_1planets_1_1Mercury.md) _celestial body._ |
| class | [**NRLMSISE00**](classastrea_1_1astro_1_1planets_1_1NRLMSISE00.md) <br> |
| class | [**NRLMSISE00Atmosphere**](classastrea_1_1astro_1_1planets_1_1NRLMSISE00Atmosphere.md) <br>_The NRLMSISE-00 atmospheric model for_ [_**Earth**_](structastrea_1_1astro_1_1planets_1_1Earth.md) _._ |
| class | [**Neptune**](structastrea_1_1astro_1_1planets_1_1Neptune.md) <br>_Represents the_ [_**Neptune**_](structastrea_1_1astro_1_1planets_1_1Neptune.md) _celestial body._ |
| class | [**Saturn**](structastrea_1_1astro_1_1planets_1_1Saturn.md) <br>_Represents the_ [_**Saturn**_](structastrea_1_1astro_1_1planets_1_1Saturn.md) _celestial body._ |
| struct | [**SpeciesModelParams**](structastrea_1_1astro_1_1planets_1_1SpeciesModelParams.md) <br>_Per-species empirical parameters for NRLMSISE-00 diffusive and mixed-region density calculations._  |
| class | [**Uranus**](structastrea_1_1astro_1_1planets_1_1Uranus.md) <br>_Represents the_ [_**Uranus**_](structastrea_1_1astro_1_1planets_1_1Uranus.md) _celestial body._ |
| class | [**Venus**](structastrea_1_1astro_1_1planets_1_1Venus.md) <br>_Represents the_ [_**Venus**_](structastrea_1_1astro_1_1planets_1_1Venus.md) _celestial body._ |


## Public Types

| Type | Name |
| ---: | :--- |
| enum  | [**EarthAtmosphereModel**](#enum-earthatmospheremodel)  <br> |




## Public Attributes

| Type | Name |
| ---: | :--- |
|  [**astrea::astro::planets::Earth**](structastrea_1_1astro_1_1planets_1_1Earth.md) | [**Earth**](#variable-earth)  <br> |
|  [**astrea::astro::planets::Jupiter**](structastrea_1_1astro_1_1planets_1_1Jupiter.md) | [**Jupiter**](#variable-jupiter)  <br> |
|  [**astrea::astro::planets::Mars**](structastrea_1_1astro_1_1planets_1_1Mars.md) | [**Mars**](#variable-mars)  <br> |
|  [**astrea::astro::planets::Mercury**](structastrea_1_1astro_1_1planets_1_1Mercury.md) | [**Mercury**](#variable-mercury)  <br> |
|  [**astrea::astro::planets::Neptune**](structastrea_1_1astro_1_1planets_1_1Neptune.md) | [**Neptune**](#variable-neptune)  <br> |
|  [**astrea::astro::planets::Saturn**](structastrea_1_1astro_1_1planets_1_1Saturn.md) | [**Saturn**](#variable-saturn)  <br> |
|  [**astrea::astro::planets::Uranus**](structastrea_1_1astro_1_1planets_1_1Uranus.md) | [**Uranus**](#variable-uranus)  <br> |
|  [**astrea::astro::planets::Venus**](structastrea_1_1astro_1_1planets_1_1Venus.md) | [**Venus**](#variable-venus)  <br> |


## Public Static Attributes

| Type | Name |
| ---: | :--- |
|  [**const**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) std::map&lt; [**Altitude**](classastrea_1_1astro_1_1DirectionCosineMatrix.md), std::tuple&lt; [**Density**](classastrea_1_1astro_1_1DirectionCosineMatrix.md), [**Density**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) &gt; &gt; | [**HARRIS\_PRIESTER\_ATMOSPHERE**](#variable-harris_priester_atmosphere)  <br> |
|  [**const**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) std::map&lt; [**Altitude**](classastrea_1_1astro_1_1DirectionCosineMatrix.md), std::tuple&lt; [**Altitude**](classastrea_1_1astro_1_1DirectionCosineMatrix.md), [**Density**](classastrea_1_1astro_1_1DirectionCosineMatrix.md), [**Altitude**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) &gt; &gt; | [**JACHIA\_ROBERTS\_ATMOSPHERE**](#variable-jachia_roberts_atmosphere)   = `/* multi line expression */`<br> |
|  [**const**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) [**Angle**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) | [**LAG**](#variable-lag)   = `30.0 \* deg`<br> |
|  [**const**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) std::array&lt; std::array&lt; NumberDensity, 150 &gt;, 9 &gt; | [**PD**](#variable-pd)  <br> |
|  [**const**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) [**double**](classastrea_1_1astro_1_1DirectionCosineMatrix.md)[][] | [**PDL**](#variable-pdl)   = `/* multi line expression */`<br> |
|  [**const**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) std::array&lt; [**SpeciesModelParams**](structastrea_1_1astro_1_1planets_1_1SpeciesModelParams.md), 8 &gt; | [**PDM**](#variable-pdm)   = `/* multi line expression */`<br> |
|  [**const**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) [**double**](classastrea_1_1astro_1_1DirectionCosineMatrix.md)[][] | [**PMA**](#variable-pma)  <br> |
|  [**const**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) [**double**](classastrea_1_1astro_1_1DirectionCosineMatrix.md)[] | [**PS**](#variable-ps)   = `/* multi line expression */`<br> |
|  [**const**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) [**double**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) | [**PT**](#variable-pt)   = `/* multi line expression */`<br> |
|  [**const**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) [**double**](classastrea_1_1astro_1_1DirectionCosineMatrix.md)[][] | [**PTL**](#variable-ptl)  <br> |
|  [**const**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) [**BatesProfileParams**](structastrea_1_1astro_1_1planets_1_1BatesProfileParams.md) | [**PTM**](#variable-ptm)   = `/* multi line expression */`<br> |
|  [**const**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) AtomicMass | [**XMM**](#variable-xmm)   = `28.9500 \* u`<br>_Mean molecular mass of the well-mixed lower atmosphere (amu), corresponding to PDM[N2][4] in the Fortran source._  |
|  [**const**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) [**int**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) | [**cosineExponent**](#variable-cosineexponent)   = `4`<br> |










































## Public Types Documentation




### enum EarthAtmosphereModel 

```C++
enum astrea::astro::planets::EarthAtmosphereModel {
    JACHIA_ROBERTS,
    NRLMSISE00,
    DTM2000,
    HARRIS_PRIESTER
};
```




<hr>
## Public Attributes Documentation




### variable Earth 

```C++
astrea::astro::planets::Earth astrea::astro::planets::Earth;
```




<hr>



### variable Jupiter 

```C++
astrea::astro::planets::Jupiter astrea::astro::planets::Jupiter;
```




<hr>



### variable Mars 

```C++
astrea::astro::planets::Mars astrea::astro::planets::Mars;
```




<hr>



### variable Mercury 

```C++
astrea::astro::planets::Mercury astrea::astro::planets::Mercury;
```




<hr>



### variable Neptune 

```C++
astrea::astro::planets::Neptune astrea::astro::planets::Neptune;
```




<hr>



### variable Saturn 

```C++
astrea::astro::planets::Saturn astrea::astro::planets::Saturn;
```




<hr>



### variable Uranus 

```C++
astrea::astro::planets::Uranus astrea::astro::planets::Uranus;
```




<hr>



### variable Venus 

```C++
astrea::astro::planets::Venus astrea::astro::planets::Venus;
```




<hr>
## Public Static Attributes Documentation




### variable HARRIS\_PRIESTER\_ATMOSPHERE 

```C++
const std::map<Altitude, std::tuple<Density, Density> > astrea::astro::planets::HARRIS_PRIESTER_ATMOSPHERE;
```



Harris-Priester min-max density (kg/m3) vs. altitude (km) table. These data are valid for a mean solar activity. 


        

<hr>



### variable JACHIA\_ROBERTS\_ATMOSPHERE 

```C++
const std::map<Altitude, std::tuple<Altitude, Density, Altitude> > astrea::astro::planets::JACHIA_ROBERTS_ATMOSPHERE;
```




<hr>



### variable LAG 

```C++
const Angle astrea::astro::planets::LAG;
```



Lag angle for diurnal bulge. 


        

<hr>



### variable PD 

```C++
const std::array<std::array<NumberDensity, 150>, 9> astrea::astro::planets::PD;
```



NRLMSISE-00 data: density pd[9][150]. 


        

<hr>



### variable PDL 

```C++
const double [][] astrea::astro::planets::PDL;
```



NRLMSISE-00 data: TURBO pdl[2][25]. 


        

<hr>



### variable PDM 

```C++
const std::array<SpeciesModelParams, 8> astrea::astro::planets::PDM;
```



NRLMSISE-00 data: pdm[8][10]. 


        

<hr>



### variable PMA 

```C++
const double [][] astrea::astro::planets::PMA;
```



NRLMSISE-00 data: pma[10][100]. 


        

<hr>



### variable PS 

```C++
const double [] astrea::astro::planets::PS;
```



NRLMSISE-00 data: ps[150]. 


        

<hr>



### variable PT 

```C++
const double astrea::astro::planets::PT[];
```



NRLMSISE-00 data: temperature pt[150]. 


        

<hr>



### variable PTL 

```C++
const double [][] astrea::astro::planets::PTL;
```



NRLMSISE-00 data: ptl[4][100]. 


        

<hr>



### variable PTM 

```C++
const BatesProfileParams astrea::astro::planets::PTM;
```




<hr>



### variable XMM 

_Mean molecular mass of the well-mixed lower atmosphere (amu), corresponding to PDM[N2][4] in the Fortran source._ 
```C++
const AtomicMass astrea::astro::planets::XMM;
```




<hr>



### variable cosineExponent 

```C++
const int astrea::astro::planets::cosineExponent;
```



Default cosine exponent value. 


        

<hr>

------------------------------
The documentation for this class was generated from the following file `astrea/astro/astro/systems/barycenters.hpp`

