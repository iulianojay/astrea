

# Class astrea::astro::planets::Output



[**ClassList**](annotated.md) **>** [**astrea**](namespaceastrea.md) **>** [**astro**](namespaceastrea_1_1astro.md) **>** [**planets**](namespaceastrea_1_1astro_1_1planets.md) **>** [**Output**](classastrea_1_1astro_1_1planets_1_1Output.md)



[More...](#detailed-description)


































































## Detailed Description


This class is a placeholder for the computed densities and temperatures. 


Densities are provided as an array d such as: 
* d[0] = He number density (1/m³) 
* d[1] = O number density (1/m³) 
* d[2] = N2 number density (1/m³) 
* d[3] = O2 number density (1/m³) 
* d[4] = Ar number density (1/m³) 
* d[5] = total mass density (kg/m³) (\*) 
* d[6] = H number density (1/m³) 
* d[7] = N number density (1/m³) 
* d[8] = anomalous oxygen number density (1/m³) 

Total mass density, d[5], is NOT the same for methods gtd7 and gtd7d: 
* For gtd7: d[5] is the sum of the mass densities of the species He, O, N2, O2, Ar, H and N but does NOT include anomalous oxygen. 
* For gtd7d: d[5] is the "effective total mass density for drag" and is the sum of the mass densities of all species in this model, INCLUDING anomalous oxygen. 

O, H, and N are set to zero below 72.5 km. 


Temperatures are provided as an array t such as: 
* t[0] = exospheric temperature (K) 
* t[1] = temperature at altitude (K) 

t[0] is set to global average for altitudes below 120 km.
 The 120 km gradient is left at global average value for altitudes below 72 km. 


    

------------------------------
The documentation for this class was generated from the following file `astrea/astro/astro/propagation/force_models/space_weather/atmosphere/experimental/NRLMSISE00.cpp`

