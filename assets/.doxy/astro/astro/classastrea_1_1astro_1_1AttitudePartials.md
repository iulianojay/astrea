

# Class astrea::astro::AttitudePartials



[**ClassList**](annotated.md) **>** [**astrea**](namespaceastrea.md) **>** [**astro**](namespaceastrea_1_1astro.md) **>** [**AttitudePartials**](classastrea_1_1astro_1_1AttitudePartials.md)



_Class representing partial derivatives of orientation._ [More...](#detailed-description)

* `#include <Attitude.hpp>`





































## Public Functions

| Type | Name |
| ---: | :--- |
|   | [**AttitudePartials**](#function-attitudepartials-12) () = default<br>_Default constructor initializing to_ [_**CartesianPartial**_](classastrea_1_1astro_1_1CartesianPartial.md) _orientation._ |
|   | [**AttitudePartials**](#function-attitudepartials-22) (const [**BodyQuaternionRate**](namespaceastrea_1_1astro.md#typedef-bodyquaternionrate) & orientationRate, const [**BodyAngularAcceleration**](namespaceastrea_1_1astro.md#typedef-bodyangularacceleration) & angularAcceleration) <br>_Constructor initializing with_ [_**CartesianPartial**_](classastrea_1_1astro_1_1CartesianPartial.md) _orientation._ |
|  std::vector&lt; double &gt; | [**force\_to\_double\_vector**](#function-force_to_double_vector) () const<br>_Converts the_ [_**AttitudePartials**_](classastrea_1_1astro_1_1AttitudePartials.md) _to a vector of Unitless values._ |
|  [**Attitude**](classastrea_1_1astro_1_1Attitude.md) | [**operator\***](#function-operator) (const Time & time) const<br>_Multiplies the_ [_**AttitudePartials**_](classastrea_1_1astro_1_1AttitudePartials.md) _by a time to get an_[_**Attitude**_](classastrea_1_1astro_1_1Attitude.md) _._ |




























## Detailed Description


This class encapsulates the partial derivatives of orientation, allowing for operations such as multiplication by time to obtain Cartesian&lt;frames::earth::icrf&gt; state vectors. 


    
## Public Functions Documentation




### function AttitudePartials [1/2]

_Default constructor initializing to_ [_**CartesianPartial**_](classastrea_1_1astro_1_1CartesianPartial.md) _orientation._
```C++
astrea::astro::AttitudePartials::AttitudePartials () = default
```




<hr>



### function AttitudePartials [2/2]

_Constructor initializing with_ [_**CartesianPartial**_](classastrea_1_1astro_1_1CartesianPartial.md) _orientation._
```C++
astrea::astro::AttitudePartials::AttitudePartials (
    const BodyQuaternionRate & orientationRate,
    const BodyAngularAcceleration & angularAcceleration
) 
```





**Parameters:**


* `orientationRate` The orbital element partials to initialize with. 
* `angularAcceleration` The angular acceleration to initialize with. 




        

<hr>



### function force\_to\_double\_vector 

_Converts the_ [_**AttitudePartials**_](classastrea_1_1astro_1_1AttitudePartials.md) _to a vector of Unitless values._
```C++
std::vector< double > astrea::astro::AttitudePartials::force_to_double_vector () const
```





**Returns:**

std::vector&lt;Unitless&gt; Vector containing the orientation as unitless values. 





        

<hr>



### function operator\* 

_Multiplies the_ [_**AttitudePartials**_](classastrea_1_1astro_1_1AttitudePartials.md) _by a time to get an_[_**Attitude**_](classastrea_1_1astro_1_1Attitude.md) _._
```C++
Attitude astrea::astro::AttitudePartials::operator* (
    const Time & time
) const
```





**Parameters:**


* `time` The time to multiply the partials with. 



**Returns:**

A reference to the current attitude partials after conversion. 





        

<hr>

------------------------------
The documentation for this class was generated from the following file `astrea/astro/astro/state/attitude/Attitude.hpp`

