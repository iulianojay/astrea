

# Class astrea::astro::KeplerianPartial

**template &lt;IsFrame [**auto**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) \_frame\_&gt;**



[**ClassList**](annotated.md) **>** [**astrea**](namespaceastrea.md) **>** [**astro**](namespaceastrea_1_1astro.md) **>** [**KeplerianPartial**](classastrea_1_1astro_1_1KeplerianPartial.md)



_Class representing a partial derivative of a_ [_**Keplerian**_](classastrea_1_1astro_1_1Keplerian.md) _state vector._[More...](#detailed-description)

* `#include <Keplerian.hpp>`























## Public Static Attributes

| Type | Name |
| ---: | :--- |
|  [**constexpr**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) [**auto**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) | [**frame**](#variable-frame)   = `\_frame\_`<br>_The reference frame of the_ [_**Keplerian**_](classastrea_1_1astro_1_1Keplerian.md) _partial derivatives._ |














## Public Functions

| Type | Name |
| ---: | :--- |
|   | [**KeplerianPartial**](#function-keplerianpartial-12) () = default<br>_Default constructor for_ [_**KeplerianPartial**_](classastrea_1_1astro_1_1KeplerianPartial.md) _._ |
|   | [**KeplerianPartial**](#function-keplerianpartial-22) ([**const**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) [**Velocity**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) & semimajorPartial, [**const**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) [**UnitlessPerTime**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) & eccentricityPartial, [**const**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) [**AngularVelocity**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) & inclinationPartial, [**const**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) [**AngularVelocity**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) & rightAscensionPartial, [**const**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) [**AngularVelocity**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) & argPerigeePartial, [**const**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) [**AngularVelocity**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) & trueAnomalyPartial) <br>_Constructor for_ [_**KeplerianPartial**_](classastrea_1_1astro_1_1KeplerianPartial.md) _with velocity and acceleration components._ |
|  std::vector&lt; [**Unitless**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) &gt; | [**force\_to\_vector**](#function-force_to_vector) () const<br>_Converts the_ [_**KeplerianPartial**_](classastrea_1_1astro_1_1KeplerianPartial.md) _state vector to a vector of unitless values._ |
|  [**Keplerian**](classastrea_1_1astro_1_1Keplerian.md)&lt; \_frame\_ &gt; | [**operator\***](#function-operator) ([**const**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) [**Time**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) & time) const<br>_Multiplication operator for_ [_**KeplerianPartial**_](classastrea_1_1astro_1_1KeplerianPartial.md) _._ |




























## Detailed Description


This class encapsulates the velocity and acceleration components of a vehicle in [**Keplerian**](classastrea_1_1astro_1_1Keplerian.md) coordinates. It is used to represent the rate of change of the [**Keplerian**](classastrea_1_1astro_1_1Keplerian.md) elements with respect to time.




**Note:**

The [**KeplerianPartial**](classastrea_1_1astro_1_1KeplerianPartial.md) class is typically used in astrodynamics calculations involving orbital mechanics. 





    
## Public Static Attributes Documentation




### variable frame 

_The reference frame of the_ [_**Keplerian**_](classastrea_1_1astro_1_1Keplerian.md) _partial derivatives._
```C++
constexpr auto astrea::astro::KeplerianPartial< _frame_ >::frame;
```




<hr>
## Public Functions Documentation




### function KeplerianPartial [1/2]

_Default constructor for_ [_**KeplerianPartial**_](classastrea_1_1astro_1_1KeplerianPartial.md) _._
```C++
astrea::astro::KeplerianPartial::KeplerianPartial () = default
```



Initializes the [**KeplerianPartial**](classastrea_1_1astro_1_1KeplerianPartial.md) with zero values. 


        

<hr>



### function KeplerianPartial [2/2]

_Constructor for_ [_**KeplerianPartial**_](classastrea_1_1astro_1_1KeplerianPartial.md) _with velocity and acceleration components._
```C++
inline astrea::astro::KeplerianPartial::KeplerianPartial (
    const  Velocity & semimajorPartial,
    const  UnitlessPerTime & eccentricityPartial,
    const  AngularVelocity & inclinationPartial,
    const  AngularVelocity & rightAscensionPartial,
    const  AngularVelocity & argPerigeePartial,
    const  AngularVelocity & trueAnomalyPartial
) 
```





**Parameters:**


* `semimajorPartial` Semimajor axis partial derivative 
* `eccentricityPartial` Eccentricity partial derivative 
* `inclinationPartial` Inclination partial derivative 
* `rightAscensionPartial` Right ascension partial derivative 
* `argPerigeePartial` Argument of perigee partial derivative 
* `trueAnomalyPartial` True anomaly partial derivative 




        

<hr>



### function force\_to\_vector 

_Converts the_ [_**KeplerianPartial**_](classastrea_1_1astro_1_1KeplerianPartial.md) _state vector to a vector of unitless values._
```C++
std::vector< Unitless > astrea::astro::KeplerianPartial::force_to_vector () const
```





**Returns:**

std::vector&lt;Unitless&gt; Vector containing the components of the [**KeplerianPartial**](classastrea_1_1astro_1_1KeplerianPartial.md) state vector. 





        

<hr>



### function operator\* 

_Multiplication operator for_ [_**KeplerianPartial**_](classastrea_1_1astro_1_1KeplerianPartial.md) _._
```C++
Keplerian < _frame_ > astrea::astro::KeplerianPartial::operator* (
    const  Time & time
) const
```



This method multiplies the [**KeplerianPartial**](classastrea_1_1astro_1_1KeplerianPartial.md) by a time value to obtain a [**Keplerian**](classastrea_1_1astro_1_1Keplerian.md) state vector.




**Parameters:**


* `time` Time to multiply the [**KeplerianPartial**](classastrea_1_1astro_1_1KeplerianPartial.md) by 



**Returns:**

[**Keplerian**](classastrea_1_1astro_1_1Keplerian.md) Resulting [**Keplerian**](classastrea_1_1astro_1_1Keplerian.md) state vector after multiplication. 





        

<hr>

------------------------------
The documentation for this class was generated from the following file `astrea/astro/astro/state/orbital_elements/Keplerian.hpp`

