

# Class astrea::astro::CartesianPartial

**template &lt;IsFrame auto \_frame\_&gt;**



[**ClassList**](annotated.md) **>** [**astrea**](namespaceastrea.md) **>** [**astro**](namespaceastrea_1_1astro.md) **>** [**CartesianPartial**](classastrea_1_1astro_1_1CartesianPartial.md)



_Class representing a partial derivative of a_ [_**Cartesian**_](classastrea_1_1astro_1_1Cartesian.md) _state vector._[More...](#detailed-description)

* `#include <Cartesian.hpp>`























## Public Static Attributes

| Type | Name |
| ---: | :--- |
|  constexpr auto | [**frame**](#variable-frame)   = `\_frame\_`<br>_The reference frame of the_ [_**Cartesian**_](classastrea_1_1astro_1_1Cartesian.md) _state vector._ |














## Public Functions

| Type | Name |
| ---: | :--- |
|   | [**CartesianPartial**](#function-cartesianpartial-13) () = default<br>_Default constructor for_ [_**CartesianPartial**_](classastrea_1_1astro_1_1CartesianPartial.md) _._ |
|   | [**CartesianPartial**](#function-cartesianpartial-23) (const Velocity & vx, const Velocity & vy, const Velocity & vz, const Acceleration & ax, const Acceleration & ay, const Acceleration & az) <br>_Constructor for_ [_**CartesianPartial**_](classastrea_1_1astro_1_1CartesianPartial.md) _with velocity and acceleration components._ |
|   | [**CartesianPartial**](#function-cartesianpartial-33) (const [**VelocityVector**](namespaceastrea_1_1astro.md#typedef-velocityvector)&lt; \_frame\_ &gt; & v, const [**AccelerationVector**](namespaceastrea_1_1astro.md#typedef-accelerationvector)&lt; \_frame\_ &gt; & a) <br>_Constructor for_ [_**CartesianPartial**_](classastrea_1_1astro_1_1CartesianPartial.md) _with velocity and acceleration vectors._ |
|  std::vector&lt; double &gt; | [**force\_to\_double\_vector**](#function-force_to_double_vector) () const<br>_Converts the_ [_**CartesianPartial**_](classastrea_1_1astro_1_1CartesianPartial.md) _state vector to a vector of unitless values._ |
|  Acceleration | [**get\_ax**](#function-get_ax) () const<br>_Get the ax value of the_ [_**CartesianPartial**_](classastrea_1_1astro_1_1CartesianPartial.md) _state vector._ |
|  Acceleration | [**get\_ay**](#function-get_ay) () const<br>_Get the ay value of the_ [_**CartesianPartial**_](classastrea_1_1astro_1_1CartesianPartial.md) _state vector._ |
|  Acceleration | [**get\_az**](#function-get_az) () const<br>_Get the az value of the_ [_**CartesianPartial**_](classastrea_1_1astro_1_1CartesianPartial.md) _state vector._ |
|  Velocity | [**get\_vx**](#function-get_vx) () const<br>_Get the vx value of the_ [_**CartesianPartial**_](classastrea_1_1astro_1_1CartesianPartial.md) _state vector._ |
|  Velocity | [**get\_vy**](#function-get_vy) () const<br>_Get the vy value of the_ [_**CartesianPartial**_](classastrea_1_1astro_1_1CartesianPartial.md) _state vector._ |
|  Velocity | [**get\_vz**](#function-get_vz) () const<br>_Get the vz value of the_ [_**CartesianPartial**_](classastrea_1_1astro_1_1CartesianPartial.md) _state vector._ |
|  [**Cartesian**](classastrea_1_1astro_1_1Cartesian.md)&lt; \_frame\_ &gt; | [**operator\***](#function-operator) (const Time & time) const<br>_Multiplication operator for_ [_**CartesianPartial**_](classastrea_1_1astro_1_1CartesianPartial.md) _._ |




























## Detailed Description


This class encapsulates the velocity and acceleration components of a vehicle in [**Cartesian**](classastrea_1_1astro_1_1Cartesian.md) coordinates. 


    
## Public Static Attributes Documentation




### variable frame 

_The reference frame of the_ [_**Cartesian**_](classastrea_1_1astro_1_1Cartesian.md) _state vector._
```C++
constexpr auto astrea::astro::CartesianPartial< _frame_ >::frame;
```




<hr>
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
    const Velocity & vx,
    const Velocity & vy,
    const Velocity & vz,
    const Acceleration & ax,
    const Acceleration & ay,
    const Acceleration & az
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
    const VelocityVector < _frame_ > & v,
    const AccelerationVector < _frame_ > & a
) 
```





**Parameters:**


* `v` Velocity vector 
* `a` Acceleration vector 




        

<hr>



### function force\_to\_double\_vector 

_Converts the_ [_**CartesianPartial**_](classastrea_1_1astro_1_1CartesianPartial.md) _state vector to a vector of unitless values._
```C++
std::vector< double > astrea::astro::CartesianPartial::force_to_double_vector () const
```





**Returns:**

std::vector&lt;Unitless&gt; Vector containing the components of the [**CartesianPartial**](classastrea_1_1astro_1_1CartesianPartial.md) state vector. 





        

<hr>



### function get\_ax 

_Get the ax value of the_ [_**CartesianPartial**_](classastrea_1_1astro_1_1CartesianPartial.md) _state vector._
```C++
inline Acceleration astrea::astro::CartesianPartial::get_ax () const
```





**Returns:**

Acceleration The ax component of the [**CartesianPartial**](classastrea_1_1astro_1_1CartesianPartial.md) state vector. 





        

<hr>



### function get\_ay 

_Get the ay value of the_ [_**CartesianPartial**_](classastrea_1_1astro_1_1CartesianPartial.md) _state vector._
```C++
inline Acceleration astrea::astro::CartesianPartial::get_ay () const
```





**Returns:**

Acceleration The ay component of the [**CartesianPartial**](classastrea_1_1astro_1_1CartesianPartial.md) state vector. 





        

<hr>



### function get\_az 

_Get the az value of the_ [_**CartesianPartial**_](classastrea_1_1astro_1_1CartesianPartial.md) _state vector._
```C++
inline Acceleration astrea::astro::CartesianPartial::get_az () const
```





**Returns:**

Acceleration The az component of the [**CartesianPartial**](classastrea_1_1astro_1_1CartesianPartial.md) state vector. 





        

<hr>



### function get\_vx 

_Get the vx value of the_ [_**CartesianPartial**_](classastrea_1_1astro_1_1CartesianPartial.md) _state vector._
```C++
inline Velocity astrea::astro::CartesianPartial::get_vx () const
```





**Returns:**

Velocity The vx component of the [**CartesianPartial**](classastrea_1_1astro_1_1CartesianPartial.md) state vector. 





        

<hr>



### function get\_vy 

_Get the vy value of the_ [_**CartesianPartial**_](classastrea_1_1astro_1_1CartesianPartial.md) _state vector._
```C++
inline Velocity astrea::astro::CartesianPartial::get_vy () const
```





**Returns:**

Velocity The vy component of the [**CartesianPartial**](classastrea_1_1astro_1_1CartesianPartial.md) state vector. 





        

<hr>



### function get\_vz 

_Get the vz value of the_ [_**CartesianPartial**_](classastrea_1_1astro_1_1CartesianPartial.md) _state vector._
```C++
inline Velocity astrea::astro::CartesianPartial::get_vz () const
```





**Returns:**

Velocity The vz component of the [**CartesianPartial**](classastrea_1_1astro_1_1CartesianPartial.md) state vector. 





        

<hr>



### function operator\* 

_Multiplication operator for_ [_**CartesianPartial**_](classastrea_1_1astro_1_1CartesianPartial.md) _._
```C++
Cartesian < _frame_ > astrea::astro::CartesianPartial::operator* (
    const Time & time
) const
```





**Parameters:**


* `time` Time to multiply the [**CartesianPartial**](classastrea_1_1astro_1_1CartesianPartial.md) by 



**Returns:**

[**Cartesian**](classastrea_1_1astro_1_1Cartesian.md) Resulting [**Cartesian**](classastrea_1_1astro_1_1Cartesian.md) state vector after multiplication. 





        

<hr>

------------------------------
The documentation for this class was generated from the following file `astrea/astro/astro/state/orbital_elements/Cartesian.hpp`

