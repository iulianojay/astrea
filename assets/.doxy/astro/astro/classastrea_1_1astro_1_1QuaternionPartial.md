

# Class astrea::astro::QuaternionPartial

**template &lt;IsFrame [**auto**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) \_in\_frame\_, IsFrame [**auto**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) \_out\_frame\_&gt;**



[**ClassList**](annotated.md) **>** [**astrea**](namespaceastrea.md) **>** [**astro**](namespaceastrea_1_1astro.md) **>** [**QuaternionPartial**](classastrea_1_1astro_1_1QuaternionPartial.md)



_Class representing the partial derivative of a quaternion with respect to time, used for integration._ [More...](#detailed-description)

* `#include <Quaternion.hpp>`























## Public Static Attributes

| Type | Name |
| ---: | :--- |
|  [**constexpr**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) [**auto**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) | [**in\_frame**](#variable-in_frame)   = `[**\_in\_frame\_**](classastrea_1_1astro_1_1DirectionCosineMatrix.md)`<br> |
|  [**constexpr**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) [**auto**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) | [**out\_frame**](#variable-out_frame)   = `[**\_out\_frame\_**](classastrea_1_1astro_1_1DirectionCosineMatrix.md)`<br> |














## Public Functions

| Type | Name |
| ---: | :--- |
|   | [**QuaternionPartial**](#function-quaternionpartial-12) () = default<br>_Default constructor for the_ [_**QuaternionPartial**_](classastrea_1_1astro_1_1QuaternionPartial.md) _class. Initializes to zero rates of change._ |
|   | [**QuaternionPartial**](#function-quaternionpartial-22) ([**const**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) [**UnitlessPerTime**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) & sDot, [**const**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) [**CartesianVector**](structastrea_1_1astro_1_1CartesianVector.md)&lt; [**UnitlessPerTime**](classastrea_1_1astro_1_1DirectionCosineMatrix.md), in\_frame &gt; & uDot) <br>_Constructor for the_ [_**QuaternionPartial**_](classastrea_1_1astro_1_1QuaternionPartial.md) _class from a scalar and a_[_**CartesianVector**_](structastrea_1_1astro_1_1CartesianVector.md) _._ |
|  std::vector&lt; [**Unitless**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) &gt; | [**force\_to\_vector**](#function-force_to_vector) () const<br>_Converts the quaternion derivative to a vector form for use in numerical integration._  |
|  [**const**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) [**UnitlessPerTime**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) & | [**get\_scalar\_part**](#function-get_scalar_part) () const<br>_Gets the scalar part of the quaternion._  |
|  [**const**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) [**CartesianVector**](structastrea_1_1astro_1_1CartesianVector.md)&lt; [**UnitlessPerTime**](classastrea_1_1astro_1_1DirectionCosineMatrix.md), in\_frame &gt; & | [**get\_vector\_part**](#function-get_vector_part) () const<br>_Gets the vector part of the quaternion as a_ [_**CartesianVector**_](structastrea_1_1astro_1_1CartesianVector.md) _._ |
|  [**Quaternion**](classastrea_1_1astro_1_1Quaternion.md)&lt; in\_frame, out\_frame &gt; | [**operator\***](#function-operator) ([**const**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) [**Time**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) & dt) const<br>_Multiplies the quaternion derivative by a time quantity to get a quaternion representing the change in attitude over that time interval._  |




























## Detailed Description




**Template parameters:**


* `in_frame` The input frame type (e.g., ECI, ECEF). 
* `out_frame` The output frame type (e.g., ECI, ECEF). 




    
## Public Static Attributes Documentation




### variable in\_frame 

```C++
constexpr auto astrea::astro::QuaternionPartial< _in_frame_, _out_frame_ >::in_frame;
```




<hr>



### variable out\_frame 

```C++
constexpr auto astrea::astro::QuaternionPartial< _in_frame_, _out_frame_ >::out_frame;
```




<hr>
## Public Functions Documentation




### function QuaternionPartial [1/2]

_Default constructor for the_ [_**QuaternionPartial**_](classastrea_1_1astro_1_1QuaternionPartial.md) _class. Initializes to zero rates of change._
```C++
astrea::astro::QuaternionPartial::QuaternionPartial () = default
```




<hr>



### function QuaternionPartial [2/2]

_Constructor for the_ [_**QuaternionPartial**_](classastrea_1_1astro_1_1QuaternionPartial.md) _class from a scalar and a_[_**CartesianVector**_](structastrea_1_1astro_1_1CartesianVector.md) _._
```C++
inline astrea::astro::QuaternionPartial::QuaternionPartial (
    const  UnitlessPerTime & sDot,
    const  CartesianVector < UnitlessPerTime , in_frame > & uDot
) 
```





**Parameters:**


* `sDot` The scalar part of the quaternion derivative. 
* `uDot` The vector part of the quaternion derivative, representing the rate of change of the vector part of the quaternion. 




        

<hr>



### function force\_to\_vector 

_Converts the quaternion derivative to a vector form for use in numerical integration._ 
```C++
inline std::vector< Unitless > astrea::astro::QuaternionPartial::force_to_vector () const
```





**Returns:**

A std::vector of Unitless quantities representing the components of the quaternion derivative, in the order [sDot, uDot\_x, uDot\_y, uDot\_z]. 





        

<hr>



### function get\_scalar\_part 

_Gets the scalar part of the quaternion._ 
```C++
inline const  UnitlessPerTime & astrea::astro::QuaternionPartial::get_scalar_part () const
```





**Returns:**

const UnitlessPerTime& The scalar part of the quaternion. 





        

<hr>



### function get\_vector\_part 

_Gets the vector part of the quaternion as a_ [_**CartesianVector**_](structastrea_1_1astro_1_1CartesianVector.md) _._
```C++
inline const  CartesianVector < UnitlessPerTime , in_frame > & astrea::astro::QuaternionPartial::get_vector_part () const
```





**Returns:**

const [**CartesianVector&lt;UnitlessPerTime, in\_frame&gt;**](structastrea_1_1astro_1_1CartesianVector.md)& The vector part of the quaternion. 





        

<hr>



### function operator\* 

_Multiplies the quaternion derivative by a time quantity to get a quaternion representing the change in attitude over that time interval._ 
```C++
inline Quaternion < in_frame, out_frame > astrea::astro::QuaternionPartial::operator* (
    const  Time & dt
) const
```





**Parameters:**


* `dt` The time quantity to multiply the quaternion derivative by, representing the time interval over which to apply the change in attitude. 



**Returns:**

A new [**Quaternion**](classastrea_1_1astro_1_1Quaternion.md) that represents the change in attitude over the given time interval. 





        

<hr>

------------------------------
The documentation for this class was generated from the following file `astrea/astro/astro/state/attitude/Quaternion.hpp`

