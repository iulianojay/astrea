

# Class astrea::astro::CartesianPartial



[**ClassList**](annotated.md) **>** [**astrea**](namespaceastrea.md) **>** [**astro**](namespaceastrea_1_1astro.md) **>** [**CartesianPartial**](classastrea_1_1astro_1_1CartesianPartial.md)



_Class representing a partial derivative of a_ [_**Cartesian**_](classastrea_1_1astro_1_1Cartesian.md) _state vector._[More...](#detailed-description)

* `#include <Cartesian.hpp>`





































## Public Functions

| Type | Name |
| ---: | :--- |
|   | [**CartesianPartial**](#function-cartesianpartial-13) () = default<br>_Default constructor for_ [_**CartesianPartial**_](classastrea_1_1astro_1_1CartesianPartial.md) _._ |
|   | [**CartesianPartial**](#function-cartesianpartial-23) ([**const**](classastrea_1_1astro_1_1CartesianVector.md) [**Velocity**](classastrea_1_1astro_1_1CartesianVector.md) & vx, [**const**](classastrea_1_1astro_1_1CartesianVector.md) [**Velocity**](classastrea_1_1astro_1_1CartesianVector.md) & vy, [**const**](classastrea_1_1astro_1_1CartesianVector.md) [**Velocity**](classastrea_1_1astro_1_1CartesianVector.md) & vz, [**const**](classastrea_1_1astro_1_1CartesianVector.md) [**Acceleration**](classastrea_1_1astro_1_1CartesianVector.md) & ax, [**const**](classastrea_1_1astro_1_1CartesianVector.md) [**Acceleration**](classastrea_1_1astro_1_1CartesianVector.md) & ay, [**const**](classastrea_1_1astro_1_1CartesianVector.md) [**Acceleration**](classastrea_1_1astro_1_1CartesianVector.md) & az) <br>_Constructor for_ [_**CartesianPartial**_](classastrea_1_1astro_1_1CartesianPartial.md) _with velocity and acceleration components._ |
|   | [**CartesianPartial**](#function-cartesianpartial-33) ([**const**](classastrea_1_1astro_1_1CartesianVector.md) [**VelocityVector**](namespaceastrea_1_1astro.md#typedef-velocityvector)&lt; [**frames::earth::icrf**](structastrea_1_1astro_1_1InertialFrame.md) &gt; & v, [**const**](classastrea_1_1astro_1_1CartesianVector.md) [**AccelerationVector**](namespaceastrea_1_1astro.md#typedef-accelerationvector)&lt; [**frames::earth::icrf**](structastrea_1_1astro_1_1InertialFrame.md) &gt; & a) <br>_Constructor for_ [_**CartesianPartial**_](classastrea_1_1astro_1_1CartesianPartial.md) _with velocity and acceleration vectors._ |
|  std::vector&lt; [**Unitless**](classastrea_1_1astro_1_1CartesianVector.md) &gt; | [**force\_to\_vector**](#function-force_to_vector) () const<br>_Converts the_ [_**CartesianPartial**_](classastrea_1_1astro_1_1CartesianPartial.md) _state vector to a vector of unitless values._ |
|  [**Cartesian**](classastrea_1_1astro_1_1Cartesian.md) | [**operator\***](#function-operator) ([**const**](classastrea_1_1astro_1_1CartesianVector.md) [**Time**](classastrea_1_1astro_1_1CartesianVector.md) & time) const<br>_Multiplication operator for_ [_**CartesianPartial**_](classastrea_1_1astro_1_1CartesianPartial.md) _._ |




























## Detailed Description


This class encapsulates the velocity and acceleration components of a vehicle in [**Cartesian**](classastrea_1_1astro_1_1Cartesian.md) coordinates. 


    
## Public Functions Documentation




### function CartesianPartial [1/3]

_Default constructor for_ [_**CartesianPartial**_](classastrea_1_1astro_1_1CartesianPartial.md) _._
```C++
astrea::astro::CartesianPartial::CartesianPartial () = default
```




<hr>



### function CartesianPartial [2/3]

_Constructor for_ [_**CartesianPartial**_](classastrea_1_1astro_1_1CartesianPartial.md) _with velocity and acceleration components._
```C++
inline astrea::astro::CartesianPartial::CartesianPartial (
    const  Velocity & vx,
    const  Velocity & vy,
    const  Velocity & vz,
    const  Acceleration & ax,
    const  Acceleration & ay,
    const  Acceleration & az
) 
```





**Parameters:**


* `vx` X component of velocity 
* `vy` Y component of velocity 
* `vz` Z component of velocity 
* `ax` X component of acceleration 
* `ay` Y component of acceleration 
* `az` Z component of acceleration 




        

<hr>



### function CartesianPartial [3/3]

_Constructor for_ [_**CartesianPartial**_](classastrea_1_1astro_1_1CartesianPartial.md) _with velocity and acceleration vectors._
```C++
inline astrea::astro::CartesianPartial::CartesianPartial (
    const  VelocityVector < frames::earth::icrf > & v,
    const  AccelerationVector < frames::earth::icrf > & a
) 
```





**Parameters:**


* `v` Velocity vector 
* `a` Acceleration vector 




        

<hr>



### function force\_to\_vector 

_Converts the_ [_**CartesianPartial**_](classastrea_1_1astro_1_1CartesianPartial.md) _state vector to a vector of unitless values._
```C++
std::vector< Unitless > astrea::astro::CartesianPartial::force_to_vector () const
```





**Returns:**

std::vector&lt;Unitless&gt; Vector containing the components of the [**CartesianPartial**](classastrea_1_1astro_1_1CartesianPartial.md) state vector. 





        

<hr>



### function operator\* 

_Multiplication operator for_ [_**CartesianPartial**_](classastrea_1_1astro_1_1CartesianPartial.md) _._
```C++
Cartesian astrea::astro::CartesianPartial::operator* (
    const  Time & time
) const
```





**Parameters:**


* `time` Time to multiply the [**CartesianPartial**](classastrea_1_1astro_1_1CartesianPartial.md) by 



**Returns:**

[**Cartesian**](classastrea_1_1astro_1_1Cartesian.md) Resulting [**Cartesian**](classastrea_1_1astro_1_1Cartesian.md) state vector after multiplication. 





        

<hr>

------------------------------
The documentation for this class was generated from the following file `astrea/astro/astro/state/orbital_elements/instances/Cartesian.hpp`

