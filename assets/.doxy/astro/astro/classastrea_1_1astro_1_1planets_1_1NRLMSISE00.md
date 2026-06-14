

# Class astrea::astro::planets::NRLMSISE00



[**ClassList**](annotated.md) **>** [**astrea**](namespaceastrea.md) **>** [**astro**](namespaceastrea_1_1astro.md) **>** [**planets**](namespaceastrea_1_1astro_1_1planets.md) **>** [**NRLMSISE00**](classastrea_1_1astro_1_1planets_1_1NRLMSISE00.md)



[More...](#detailed-description)




Inherits the following classes: AbstractSunInfluencedAtmosphere






























































## Detailed Description


This class implements the mathematical representation of the 2001 Naval Research Laboratory Mass Spectrometer and Incoherent Scatter Radar Exosphere (NRLMSISE-00) of the MSIS® class model. 


NRLMSISE-00 calculates the neutral atmosphere empirical model from the surface to lower exosphere (0 to 1000 km) and provides: 
* Exospheric Temperature above Input Position (K) 
* Local Temperature at Input Position (K) 
* Total Mass-Density at Input Position (kg/m³) 
* Partial Densities at Input Position (1/m³) for: 
  * He, 
  * H, 
  * N, 
  * O, 
  * Ar, 
  * N2, 
  * O2, 
  * anomalous oxygen. 






The model needs geographical and time information to compute general values, but also needs space weather data: 
* mean and daily solar flux, 
* geomagnetic indices. 




Switches can be used to turn on and off particular variations:
 0 is off, 1 is on, and 2 is main effects off but cross terms on.
 The standard value is 1 for all the 23 available switches.
 Function of each switch according to its number: 
* #1 - F10.7 effect on mean 
* #2 - Independent of time 
* #3 - Symmetrical annual 
* #4 - Symmetrical semiannual 
* #5 - Asymmetrical annual 
* #6 - Asymmetrical semiannual 
* #7 - Diurnal 
* #8 - Semidiurnal 
* #9 - Daily Ap [\*\*] 
* #10 - All UT, longitudinal effects 
* #11 - Longitudinal 
* #12 - UT and mixed UT, longitudinal 
* #13 - Mixed AP, UT, longitudinal 
* #14 - Terdiurnal 
* #15 - Departures from diffusive equilibrium 
* #16 - All exospheric temperature variations 
* #17 - All variations from 120 km temperature (TLB) 
* #18 - All lower thermosphere (TN1) temperature variations 
* #19 - All 120 km gradient (S) variations 
* #20 - All upper stratosphere (TN2) temperature variations 
* #21 - All variations from 120 km values (ZLB) 
* #22 - All lower mesosphere temperature (TN3) variations 
* #23 - Turbopause scale height variations 

[\*\*] Switch #9 is a bit specific: 
* set to 1, the daily Ap only is used (first element of ap array), 
* set to -1, the entire array of ap is used, including 3 hr ap indices. 




The NRLMSISE-00 model was developed by Mike Picone, Alan Hedin, and Doug Drob.
 They also wrote a NRLMSISE-00 distribution package in FORTRAN available at:
 [ftp://hanna.ccmc.gsfc.nasa.gov/pub/modelweb/atmospheric/msis/nrlmsise00/](ftp://hanna.ccmc.gsfc.nasa.gov/pub/modelweb/atmospheric/msis/nrlmsise00/)
 
 Dominik Brodowski implemented a C version of the NRLMSISE-00 model available at:
 [https://www.brodo.de/space/nrlmsise/index.html](https://www.brodo.de/space/nrlmsise/index.html) 


Instances of this class are immutable. 




**Author:**

Mike Picone & al (Naval Research Laboratory), 2001: FORTRAN routine 




**Author:**

Dominik Brodowski, 2004: C routine 




**Author:**

Pascal Parraud, 2016: Java translation 




**Since:**

8.1 





    

------------------------------
The documentation for this class was generated from the following file `astrea/astro/astro/systems/celestial_bodies/Earth/atmosphere/NRLMSISE00.cpp`

