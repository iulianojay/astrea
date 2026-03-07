

# Class astrea::astro::EquinoctialPartial



[**ClassList**](annotated.md) **>** [**astrea**](namespaceastrea.md) **>** [**astro**](namespaceastrea_1_1astro.md) **>** [**EquinoctialPartial**](classastrea_1_1astro_1_1EquinoctialPartial.md)



_Class representing a partial derivative of an_ [_**Equinoctial**_](classastrea_1_1astro_1_1Equinoctial.md) _state vector._

* `#include <Equinoctial.hpp>`





































## Public Functions

| Type | Name |
| ---: | :--- |
|   | [**EquinoctialPartial**](#function-equinoctialpartial-12) () = default<br>_Default constructor for_ [_**EquinoctialPartial**_](classastrea_1_1astro_1_1EquinoctialPartial.md) _._ |
|   | [**EquinoctialPartial**](#function-equinoctialpartial-22) (const Velocity & semilatusPartial, const UnitlessPerTime & fPartial, const UnitlessPerTime & gPartial, const UnitlessPerTime & hPartial, const UnitlessPerTime & kPartial, const AngularRate & trueLongitudePartial) <br>_Constructor for_ [_**EquinoctialPartial**_](classastrea_1_1astro_1_1EquinoctialPartial.md) _with velocity and acceleration components._ |
|  std::vector&lt; Unitless &gt; | [**force\_to\_vector**](#function-force_to_vector) () const<br>_Converts the_ [_**EquinoctialPartial**_](classastrea_1_1astro_1_1EquinoctialPartial.md) _state vector to a vector of unitless values._ |
|  [**Equinoctial**](classastrea_1_1astro_1_1Equinoctial.md) | [**operator\***](#function-operator) (const Time & time) const<br>_Multiplication operator for_ [_**EquinoctialPartial**_](classastrea_1_1astro_1_1EquinoctialPartial.md) _._ |




























## Public Functions Documentation




### function EquinoctialPartial [1/2]

_Default constructor for_ [_**EquinoctialPartial**_](classastrea_1_1astro_1_1EquinoctialPartial.md) _._
```C++
astrea::astro::EquinoctialPartial::EquinoctialPartial () = default
```



Initializes the [**EquinoctialPartial**](classastrea_1_1astro_1_1EquinoctialPartial.md) with zero values. 


        

<hr>



### function EquinoctialPartial [2/2]

_Constructor for_ [_**EquinoctialPartial**_](classastrea_1_1astro_1_1EquinoctialPartial.md) _with velocity and acceleration components._
```C++
inline astrea::astro::EquinoctialPartial::EquinoctialPartial (
    const Velocity & semilatusPartial,
    const UnitlessPerTime & fPartial,
    const UnitlessPerTime & gPartial,
    const UnitlessPerTime & hPartial,
    const UnitlessPerTime & kPartial,
    const AngularRate & trueLongitudePartial
) 
```





**Parameters:**


* `semilatusPartial` Semilatus rectum partial derivative 
* `fPartial` First component of the eccentricity vector partial derivative 
* `gPartial` Second component of the eccentricity vector partial derivative 
* `hPartial` First component of the planar vector partial derivative 
* `kPartial` Second component of the planar vector partial derivative 
* `trueLongitudePartial` True longitude partial derivative 




        

<hr>



### function force\_to\_vector 

_Converts the_ [_**EquinoctialPartial**_](classastrea_1_1astro_1_1EquinoctialPartial.md) _state vector to a vector of unitless values._
```C++
std::vector< Unitless > astrea::astro::EquinoctialPartial::force_to_vector () const
```





**Returns:**

std::vector&lt;Unitless&gt; Vector containing the components of the [**EquinoctialPartial**](classastrea_1_1astro_1_1EquinoctialPartial.md) state vector. 





        

<hr>



### function operator\* 

_Multiplication operator for_ [_**EquinoctialPartial**_](classastrea_1_1astro_1_1EquinoctialPartial.md) _._
```C++
Equinoctial astrea::astro::EquinoctialPartial::operator* (
    const Time & time
) const
```





**Parameters:**


* `time` Time to multiply the [**EquinoctialPartial**](classastrea_1_1astro_1_1EquinoctialPartial.md) by 



**Returns:**

[**Equinoctial**](classastrea_1_1astro_1_1Equinoctial.md) Resulting [**Equinoctial**](classastrea_1_1astro_1_1Equinoctial.md) state vector after multiplication. 





        

<hr>

------------------------------
The documentation for this class was generated from the following file `astrea/astro/astro/state/orbital_elements/instances/Equinoctial.hpp`

