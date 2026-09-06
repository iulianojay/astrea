

# Namespace astrea::astro::planets



[**Namespace List**](namespaces.md) **>** [**astrea**](namespaceastrea.md) **>** [**astro**](namespaceastrea_1_1astro.md) **>** [**planets**](namespaceastrea_1_1astro_1_1planets.md)




















## Classes

| Type | Name |
| ---: | :--- |
| struct | [**BatesProfileParams**](structastrea_1_1astro_1_1planets_1_1BatesProfileParams.md) <br> |
| class | [**Earth**](structastrea_1_1astro_1_1planets_1_1Earth.md) <br>_Represents the_ [_**Earth**_](structastrea_1_1astro_1_1planets_1_1Earth.md) _celestial body._ |
| class | [**Jupiter**](structastrea_1_1astro_1_1planets_1_1Jupiter.md) <br>_Represents the_ [_**Jupiter**_](structastrea_1_1astro_1_1planets_1_1Jupiter.md) _celestial body._ |
| class | [**Mars**](structastrea_1_1astro_1_1planets_1_1Mars.md) <br>_Represents the_ [_**Mars**_](structastrea_1_1astro_1_1planets_1_1Mars.md) _celestial body._ |
| class | [**Mercury**](structastrea_1_1astro_1_1planets_1_1Mercury.md) <br>_Represents the_ [_**Mercury**_](structastrea_1_1astro_1_1planets_1_1Mercury.md) _celestial body._ |
| class | [**Neptune**](structastrea_1_1astro_1_1planets_1_1Neptune.md) <br>_Represents the_ [_**Neptune**_](structastrea_1_1astro_1_1planets_1_1Neptune.md) _celestial body._ |
| class | [**Nrlmsise00Atmosphere**](classastrea_1_1astro_1_1planets_1_1Nrlmsise00Atmosphere.md) <br>_The NRLMSISE-00 atmospheric model for_ [_**Earth**_](structastrea_1_1astro_1_1planets_1_1Earth.md) _._ |
| class | [**Output**](classastrea_1_1astro_1_1planets_1_1Output.md) <br> |
| class | [**Saturn**](structastrea_1_1astro_1_1planets_1_1Saturn.md) <br>_Represents the_ [_**Saturn**_](structastrea_1_1astro_1_1planets_1_1Saturn.md) _celestial body._ |
| struct | [**SpeciesModelParams**](structastrea_1_1astro_1_1planets_1_1SpeciesModelParams.md) <br>_Per-species empirical parameters for NRLMSISE-00 diffusive and mixed-region density calculations._  |
| struct | [**Switch**](structastrea_1_1astro_1_1planets_1_1Switch.md) <br> |
| class | [**Uranus**](structastrea_1_1astro_1_1planets_1_1Uranus.md) <br>_Represents the_ [_**Uranus**_](structastrea_1_1astro_1_1planets_1_1Uranus.md) _celestial body._ |
| class | [**Venus**](structastrea_1_1astro_1_1planets_1_1Venus.md) <br>_Represents the_ [_**Venus**_](structastrea_1_1astro_1_1planets_1_1Venus.md) _celestial body._ |


## Public Types

| Type | Name |
| ---: | :--- |
| enum  | [**Option**](#enum-option)  <br> |
| enum  | [**Species**](#enum-species)  <br> |
| enum  | [**TemperatureType**](#enum-temperaturetype)  <br> |




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
|  std::unordered\_map&lt; Option, [**Switch**](structastrea_1_1astro_1_1planets_1_1Switch.md) &gt; | [**options**](#variable-options)   = `/* multi line expression */`<br> |


## Public Static Attributes

| Type | Name |
| ---: | :--- |
|  const AtomicMass | [**AR\_MASS**](#variable-ar_mass)   = `40.0 \* u`<br> |
|  const SolarFlux | [**FLUX\_REF**](#variable-flux_ref)   = `150.0`<br> |
|  const Acceleration | [**G\_REF**](#variable-g_ref)   = `980.616 \* cm / (s \* s)`<br> |
|  const AtomicMass | [**HE\_MASS**](#variable-he_mass)   = `4.0 \* u`<br> |
|  const AtomicMass | [**H\_MASS**](#variable-h_mass)   = `1.0 \* u`<br> |
|  const Angle | [**LAT\_REF**](#variable-lat_ref)   = `45.0 \* deg`<br> |
|  const Temperature | [**MIN\_TEMP**](#variable-min_temp)   = `50.0 \* K`<br> |
|  const AtomicMass | [**N2\_MASS**](#variable-n2_mass)   = `2.0 \* N\_MASS`<br> |
|  const AtomicMass | [**N\_MASS**](#variable-n_mass)   = `14.0 \* u`<br> |
|  const AtomicMass | [**O2\_MASS**](#variable-o2_mass)   = `2.0 \* O\_MASS`<br> |
|  const AtomicMass | [**O\_MASS**](#variable-o_mass)   = `16.0 \* u`<br> |
|  const std::array&lt; quantity, 10 &gt; | [**PAVGM**](#variable-pavgm)   = `/* multi line expression */`<br> |
|  const std::array&lt; std::array&lt; NumberDensity, 150 &gt;, 9 &gt; | [**PD**](#variable-pd)  <br> |
|  const quantity[][] | [**PDL**](#variable-pdl)   = `/* multi line expression */`<br> |
|  const quantity[][] | [**PMA**](#variable-pma)  <br> |
|  const quantity[] | [**PS**](#variable-ps)   = `/* multi line expression */`<br> |
|  const std::array&lt; Temperature, 150 &gt; | [**PT**](#variable-pt)  <br> |
|  const quantity[][] | [**PTL**](#variable-ptl)  <br> |
|  const [**BatesProfileParams**](structastrea_1_1astro_1_1planets_1_1BatesProfileParams.md) | [**PTM**](#variable-ptm)   = `/* multi line expression */`<br> |
|  const auto | [**R\_GAS**](#variable-r_gas)   = `831.4 \* J / (mol \* K)`<br> |
|  const std::unordered\_map&lt; Species, [**SpeciesModelParams**](structastrea_1_1astro_1_1planets_1_1SpeciesModelParams.md) &gt; | [**SpeciesModelData**](#variable-speciesmodeldata)   = `/* multi line expression */`<br> |
|  const AtomicMass | [**XMM**](#variable-xmm)   = `28.9500 \* u`<br>_Mean molecular mass of the well-mixed lower atmosphere (amu), corresponding to SpeciesModelData[N2][4] in the Fortran source._  |
|  const Distance | [**ZMIX**](#variable-zmix)   = `62.5 \* km`<br> |
|  const std::array&lt; Distance, 5 &gt; | [**ZN1**](#variable-zn1)   = `{ 123.435 \* km, 110.0 \* km, 100.0 \* km, 90.0 \* km, 72.5 \* km }`<br> |
|  const std::array&lt; Distance, 4 &gt; | [**ZN2**](#variable-zn2)   = `{ 72.5 \* km, 55.0 \* km, 45.0 \* km, 32.5 \* km }`<br> |
|  const std::array&lt; Distance, 5 &gt; | [**ZN3**](#variable-zn3)   = `{ 32.5 \* km, 20.0 \* km, 15.0 \* km, 10.0 \* km, 0.0 \* km }`<br> |














## Public Functions

| Type | Name |
| ---: | :--- |
|  Time | [**calculate\_local\_solar\_time**](#function-calculate_local_solar_time) (const [**State**](classastrea_1_1astro_1_1State.md) & state) <br> |
|  Density | [**find\_atmospheric\_density**](#function-find_atmospheric_density) (const [**State**](classastrea_1_1astro_1_1State.md) & state) <br> |




























## Public Types Documentation




### enum Option 

```C++
enum astrea::astro::planets::Option {
    F107_EFFECT_ON_MEAN = 0,
    INDEPENDENT_OF_TIME = 1,
    SYMMETRICAL_ANNUAL = 2,
    SYMMETRICAL_SEMIANNUAL = 3,
    ASYMMETRICAL_ANNUAL = 4,
    ASYMMETRICAL_SEMIANNUAL = 5,
    DIURNAL = 6,
    SEMIDIURNAL = 7,
    DAILY_AP = 8,
    ALL_UT_LONGITUDINAL_EFFECTS = 9,
    LONGITUDINAL_EFFECTS = 10,
    UT_AND_MIXED_UT_LONGITUDINAL_EFFECTS = 11,
    MIXED_AP_UT_LONGITUDINAL_EFFECTS = 12,
    TERDIURNAL = 13,
    DEPARTURES_FROM_DIFFUSIVE_EQUILIBRIUM = 14,
    ALL_EXOSPHERIC_TEMPERATURE_VARIATIONS = 15,
    ALL_VARIATIONS_FROM_120KM_TEMPERATURE_TLB = 16,
    ALL_LOWER_THERMOSPHERE_TEMPERATURE_TN1_VARIATIONS = 17,
    ALL_120KM_GRADIENT_S_VARIATIONS = 18,
    ALL_UPPER_STRATOSPHERE_TEMPERATURE_TN2_VARIATIONS = 19,
    ALL_VARIATIONS_FROM_120KM_VALUES_ZLB = 20,
    ALL_LOWER_MESOSPHERE_TEMPERATURE_TN3_VARIATIONS = 21,
    TURBOPAUSE_SCALE_HEIGHT_VARIATIONS = 22
};
```



Switches for main effects. 


        

<hr>



### enum Species 

```C++
enum astrea::astro::planets::Species {
    HELIUM = 0,
    ATOMIC_OXYGEN = 1,
    MOLECULAR_NITROGEN = 2,
    MOLECULAR_OXYGEN = 3,
    ARGON = 4,
    TOTAL_MASS = 5,
    HYDROGEN = 6,
    ATOMIC_NITROGEN = 7,
    ANOMALOUS_OXYGEN = 8
};
```




<hr>



### enum TemperatureType 

```C++
enum astrea::astro::planets::TemperatureType {
    EXOSPHERIC = 0,
    ALTITUDE = 1
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



### variable options 

```C++
std::unordered_map<Option, Switch> astrea::astro::planets::options;
```




<hr>
## Public Static Attributes Documentation




### variable AR\_MASS 

```C++
const AtomicMass astrea::astro::planets::AR_MASS;
```



Argon atomic mass. 


        

<hr>



### variable FLUX\_REF 

```C++
const SolarFlux astrea::astro::planets::FLUX_REF;
```



Reference average flux. 


        

<hr>



### variable G\_REF 

```C++
const Acceleration astrea::astro::planets::G_REF;
```



Reference gravity on [**Earth**](structastrea_1_1astro_1_1planets_1_1Earth.md) surface at reference latitude (cm/s2). 


        

<hr>



### variable HE\_MASS 

```C++
const AtomicMass astrea::astro::planets::HE_MASS;
```



Helium atomic mass. 


        

<hr>



### variable H\_MASS 

```C++
const AtomicMass astrea::astro::planets::H_MASS;
```



Hydrogen atomic mass. 


        

<hr>



### variable LAT\_REF 

```C++
const Angle astrea::astro::planets::LAT_REF;
```



Reference latitude (°). 


        

<hr>



### variable MIN\_TEMP 

```C++
const Temperature astrea::astro::planets::MIN_TEMP;
```



NRLMSISE-00 minimum temperature, used in many cases in density computation. 


        

<hr>



### variable N2\_MASS 

```C++
const AtomicMass astrea::astro::planets::N2_MASS;
```



N2 molecular mass. 


        

<hr>



### variable N\_MASS 

```C++
const AtomicMass astrea::astro::planets::N_MASS;
```



Nitrogen atomic mass. 


        

<hr>



### variable O2\_MASS 

```C++
const AtomicMass astrea::astro::planets::O2_MASS;
```



O2 molecular mass. 


        

<hr>



### variable O\_MASS 

```C++
const AtomicMass astrea::astro::planets::O_MASS;
```



Oxygen atomic mass. 


        

<hr>



### variable PAVGM 

```C++
const std::array<quantity, 10> astrea::astro::planets::PAVGM;
```



NRLMSISE-00 data: MIDDLE ATMOSPHERE AVERAGES pavgm[10]. 


        

<hr>



### variable PD 

```C++
const std::array<std::array<NumberDensity, 150>, 9> astrea::astro::planets::PD;
```



NRLMSISE-00 data: density pd[9][150]. 


        

<hr>



### variable PDL 

```C++
const quantity [][] astrea::astro::planets::PDL;
```



NRLMSISE-00 data: TURBO pdl[2][25]. 


        

<hr>



### variable PMA 

```C++
const quantity [][] astrea::astro::planets::PMA;
```



NRLMSISE-00 data: pma[10][100]. 


        

<hr>



### variable PS 

```C++
const quantity [] astrea::astro::planets::PS;
```



NRLMSISE-00 data: ps[150]. 


        

<hr>



### variable PT 

```C++
const std::array<Temperature, 150> astrea::astro::planets::PT;
```



NRLMSISE-00 data: temperature pt[150]. 


        

<hr>



### variable PTL 

```C++
const quantity [][] astrea::astro::planets::PTL;
```



NRLMSISE-00 data: ptl[4][100]. 


        

<hr>



### variable PTM 

```C++
const BatesProfileParams astrea::astro::planets::PTM;
```




<hr>



### variable R\_GAS 

```C++
const auto astrea::astro::planets::R_GAS;
```



Gas constant (inverse of). 


        

<hr>



### variable SpeciesModelData 

```C++
const std::unordered_map<Species, SpeciesModelParams> astrea::astro::planets::SpeciesModelData;
```



NRLMSISE-00 data: pdm[8][10]. 


        

<hr>



### variable XMM 

_Mean molecular mass of the well-mixed lower atmosphere (amu), corresponding to SpeciesModelData[N2][4] in the Fortran source._ 
```C++
const AtomicMass astrea::astro::planets::XMM;
```




<hr>



### variable ZMIX 

```C++
const Distance astrea::astro::planets::ZMIX;
```



Mix altitude (km). 


        

<hr>



### variable ZN1 

```C++
const std::array<Distance, 5> astrea::astro::planets::ZN1;
```



Array of altitudes #1. 


        

<hr>



### variable ZN2 

```C++
const std::array<Distance, 4> astrea::astro::planets::ZN2;
```



Array of altitudes #2. 


        

<hr>



### variable ZN3 

```C++
const std::array<Distance, 5> astrea::astro::planets::ZN3;
```



Array of altitudes #3. 


        

<hr>
## Public Functions Documentation




### function calculate\_local\_solar\_time 

```C++
Time astrea::astro::planets::calculate_local_solar_time (
    const State & state
) 
```




<hr>



### function find\_atmospheric\_density 

```C++
Density astrea::astro::planets::find_atmospheric_density (
    const State & state
) 
```




<hr>

------------------------------
The documentation for this class was generated from the following file `astrea/astro/astro/propagation/force_models/space_weather/atmosphere/experimental/NRLMSISE00.cpp`

