

# Class astrea::astro::CartesianVector

**template &lt;[**class**](classastrea_1_1astro_1_1CartesianVector.md) [**Value\_T**](classastrea_1_1astro_1_1CartesianVector.md), [**class**](classastrea_1_1astro_1_1CartesianVector.md) [**Frame\_T**](classastrea_1_1astro_1_1CartesianVector.md)&gt;**



[**ClassList**](annotated.md) **>** [**astrea**](namespaceastrea.md) **>** [**astro**](namespaceastrea_1_1astro.md) **>** [**CartesianVector**](classastrea_1_1astro_1_1CartesianVector.md)



_Class representing a 3D vector in_ [_**Cartesian**_](classastrea_1_1astro_1_1Cartesian.md) _coordinates._[More...](#detailed-description)

* `#include <CartesianVector.hpp>`





















## Public Attributes

| Type | Name |
| ---: | :--- |
|  [**decltype**](classastrea_1_1astro_1_1CartesianVector.md)([**Value\_T**](classastrea_1_1astro_1_1CartesianVector.md){} \*[**Value\_U**](classastrea_1_1astro_1_1CartesianVector.md){} | [**dot**](#variable-dot)  <br>_Dot product of this vector with another_ [_**CartesianVector**_](classastrea_1_1astro_1_1CartesianVector.md) _._ |
















## Public Functions

| Type | Name |
| ---: | :--- |
|   | [**CartesianVector**](#function-cartesianvector-13) ([**const**](classastrea_1_1astro_1_1CartesianVector.md) [**Value\_T**](classastrea_1_1astro_1_1CartesianVector.md) & x=[**Value\_T**](classastrea_1_1astro_1_1CartesianVector.md)(), [**const**](classastrea_1_1astro_1_1CartesianVector.md) [**Value\_T**](classastrea_1_1astro_1_1CartesianVector.md) & y=[**Value\_T**](classastrea_1_1astro_1_1CartesianVector.md)(), [**const**](classastrea_1_1astro_1_1CartesianVector.md) [**Value\_T**](classastrea_1_1astro_1_1CartesianVector.md) & z=[**Value\_T**](classastrea_1_1astro_1_1CartesianVector.md)()) <br>_Default constructor for_ [_**CartesianVector**_](classastrea_1_1astro_1_1CartesianVector.md) _._ |
|   | [**CartesianVector**](#function-cartesianvector-23) ([**const**](classastrea_1_1astro_1_1CartesianVector.md) [**CartesianVector**](classastrea_1_1astro_1_1CartesianVector.md)&lt; [**Value\_T**](classastrea_1_1astro_1_1CartesianVector.md), [**Frame\_U**](classastrea_1_1astro_1_1CartesianVector.md) &gt; & other) = delete<br> |
|   | [**CartesianVector**](#function-cartesianvector-33) ([**CartesianVector**](classastrea_1_1astro_1_1CartesianVector.md)&lt; [**Value\_T**](classastrea_1_1astro_1_1CartesianVector.md), [**Frame\_U**](classastrea_1_1astro_1_1CartesianVector.md) &gt; && other) = delete<br> |
|  [**CartesianVector**](classastrea_1_1astro_1_1CartesianVector.md)&lt; [**decltype**](classastrea_1_1astro_1_1CartesianVector.md)([**Value\_T**](classastrea_1_1astro_1_1CartesianVector.md){} \*[**Value\_U**](classastrea_1_1astro_1_1CartesianVector.md){}), [**Frame\_T**](classastrea_1_1astro_1_1CartesianVector.md) &gt; | [**cross**](#function-cross) ([**const**](classastrea_1_1astro_1_1CartesianVector.md) [**CartesianVector**](classastrea_1_1astro_1_1CartesianVector.md)&lt; [**Value\_U**](classastrea_1_1astro_1_1CartesianVector.md), [**Frame\_T**](classastrea_1_1astro_1_1CartesianVector.md) &gt; & other) const<br>_Cross product of this vector with another_ [_**CartesianVector**_](classastrea_1_1astro_1_1CartesianVector.md) _._ |
|  [**CartesianVector**](classastrea_1_1astro_1_1CartesianVector.md)&lt; [**Value\_T**](classastrea_1_1astro_1_1CartesianVector.md), [**Frame\_U**](classastrea_1_1astro_1_1CartesianVector.md) &gt; | [**force\_frame\_conversion**](#function-force_frame_conversion) () const<br>_Copy constructor for_ [_**CartesianVector**_](classastrea_1_1astro_1_1CartesianVector.md) _that implicitly converts the frame._ |
|  [**Value\_T**](classastrea_1_1astro_1_1CartesianVector.md) & | [**get\_x**](#function-get_x-12) () <br>_Get the x value of the_ [_**Cartesian**_](classastrea_1_1astro_1_1Cartesian.md) _vector._ |
|  [**const**](classastrea_1_1astro_1_1CartesianVector.md) [**Value\_T**](classastrea_1_1astro_1_1CartesianVector.md) & | [**get\_x**](#function-get_x-22) () const<br>_Get the x value of the_ [_**Cartesian**_](classastrea_1_1astro_1_1Cartesian.md) _vector._ |
|  [**Value\_T**](classastrea_1_1astro_1_1CartesianVector.md) & | [**get\_y**](#function-get_y-12) () <br>_Get the y value of the_ [_**Cartesian**_](classastrea_1_1astro_1_1Cartesian.md) _vector._ |
|  [**const**](classastrea_1_1astro_1_1CartesianVector.md) [**Value\_T**](classastrea_1_1astro_1_1CartesianVector.md) & | [**get\_y**](#function-get_y-22) () const<br>_Get the y value of the_ [_**Cartesian**_](classastrea_1_1astro_1_1Cartesian.md) _vector._ |
|  [**Value\_T**](classastrea_1_1astro_1_1CartesianVector.md) & | [**get\_z**](#function-get_z-12) () <br>_Get the z value of the_ [_**Cartesian**_](classastrea_1_1astro_1_1Cartesian.md) _vector._ |
|  [**const**](classastrea_1_1astro_1_1CartesianVector.md) [**Value\_T**](classastrea_1_1astro_1_1CartesianVector.md) & | [**get\_z**](#function-get_z-22) () const<br>_Get the z value of the_ [_**Cartesian**_](classastrea_1_1astro_1_1Cartesian.md) _vector._ |
|  [**CartesianVector**](classastrea_1_1astro_1_1CartesianVector.md)&lt; [**Value\_T**](classastrea_1_1astro_1_1CartesianVector.md), [**Frame\_U**](classastrea_1_1astro_1_1CartesianVector.md) &gt; | [**in\_frame**](#function-in_frame) ([**const**](classastrea_1_1astro_1_1CartesianVector.md) [**Date**](classastrea_1_1astro_1_1Date.md) & date) const<br>_Rotate this vector into another frame at a given date._  |
|  [**Value\_T**](classastrea_1_1astro_1_1CartesianVector.md) | [**norm**](#function-norm) () const<br>_Calculate the norm (magnitude) of the vector._  |
|  [**CartesianVector**](classastrea_1_1astro_1_1CartesianVector.md)&lt; [**Value\_T**](classastrea_1_1astro_1_1CartesianVector.md), [**Frame\_V**](classastrea_1_1astro_1_1CartesianVector.md) &gt; | [**offset**](#function-offset) ([**const**](classastrea_1_1astro_1_1CartesianVector.md) [**CartesianVector**](classastrea_1_1astro_1_1CartesianVector.md)&lt; [**Value\_T**](classastrea_1_1astro_1_1CartesianVector.md), [**Frame\_U**](classastrea_1_1astro_1_1CartesianVector.md) &gt; & other) const<br>_Calculate the offset vector from another vector in a different frame, resulting in a vector in a third frame._  |
|  [**Angle**](classastrea_1_1astro_1_1CartesianVector.md) | [**offset\_angle**](#function-offset_angle) ([**const**](classastrea_1_1astro_1_1CartesianVector.md) [**CartesianVector**](classastrea_1_1astro_1_1CartesianVector.md)&lt; [**Value\_T**](classastrea_1_1astro_1_1CartesianVector.md), [**Frame\_T**](classastrea_1_1astro_1_1CartesianVector.md) &gt; & other) const<br>_Calculate the angle between this vector and another_ [_**CartesianVector**_](classastrea_1_1astro_1_1CartesianVector.md) _._ |
|  [**CartesianVector**](classastrea_1_1astro_1_1CartesianVector.md)&lt; [**decltype**](classastrea_1_1astro_1_1CartesianVector.md)([**Value\_T**](classastrea_1_1astro_1_1CartesianVector.md){} \*[**Value\_U**](classastrea_1_1astro_1_1CartesianVector.md){}), [**Frame\_T**](classastrea_1_1astro_1_1CartesianVector.md) &gt; | [**operator\***](#function-operator) ([**const**](classastrea_1_1astro_1_1CartesianVector.md) [**Value\_U**](classastrea_1_1astro_1_1CartesianVector.md) & scalar) const<br>_Scalar multiplication operator for_ [_**CartesianVector**_](classastrea_1_1astro_1_1CartesianVector.md) _._ |
|  [**CartesianVector**](classastrea_1_1astro_1_1CartesianVector.md)&lt; [**Value\_T**](classastrea_1_1astro_1_1CartesianVector.md), [**Frame\_T**](classastrea_1_1astro_1_1CartesianVector.md) &gt; & | [**operator\*=**](#function-operator_1) ([**const**](classastrea_1_1astro_1_1CartesianVector.md) [**Unitless**](classastrea_1_1astro_1_1CartesianVector.md) & scalar) <br>_Scalar multiplication assignment operator for_ [_**CartesianVector**_](classastrea_1_1astro_1_1CartesianVector.md) _._ |
|  [**CartesianVector**](classastrea_1_1astro_1_1CartesianVector.md)&lt; [**Value\_T**](classastrea_1_1astro_1_1CartesianVector.md), [**Frame\_T**](classastrea_1_1astro_1_1CartesianVector.md) &gt; | [**operator+**](#function-operator_2) ([**const**](classastrea_1_1astro_1_1CartesianVector.md) [**CartesianVector**](classastrea_1_1astro_1_1CartesianVector.md)&lt; [**Value\_T**](classastrea_1_1astro_1_1CartesianVector.md), [**Frame\_T**](classastrea_1_1astro_1_1CartesianVector.md) &gt; & other) const<br>_Addition operator for_ [_**CartesianVector**_](classastrea_1_1astro_1_1CartesianVector.md) _._ |
|  [**CartesianVector**](classastrea_1_1astro_1_1CartesianVector.md)&lt; [**Value\_T**](classastrea_1_1astro_1_1CartesianVector.md), [**Frame\_T**](classastrea_1_1astro_1_1CartesianVector.md) &gt; & | [**operator+=**](#function-operator_3) ([**const**](classastrea_1_1astro_1_1CartesianVector.md) [**CartesianVector**](classastrea_1_1astro_1_1CartesianVector.md)&lt; [**Value\_T**](classastrea_1_1astro_1_1CartesianVector.md), [**Frame\_T**](classastrea_1_1astro_1_1CartesianVector.md) &gt; & other) <br>_Addition assignment operator for_ [_**CartesianVector**_](classastrea_1_1astro_1_1CartesianVector.md) _._ |
|  [**CartesianVector**](classastrea_1_1astro_1_1CartesianVector.md)&lt; [**Value\_T**](classastrea_1_1astro_1_1CartesianVector.md), [**Frame\_T**](classastrea_1_1astro_1_1CartesianVector.md) &gt; | [**operator-**](#function-operator-) ([**const**](classastrea_1_1astro_1_1CartesianVector.md) [**CartesianVector**](classastrea_1_1astro_1_1CartesianVector.md)&lt; [**Value\_T**](classastrea_1_1astro_1_1CartesianVector.md), [**Frame\_T**](classastrea_1_1astro_1_1CartesianVector.md) &gt; & other) const<br>_Subtraction operator for_ [_**CartesianVector**_](classastrea_1_1astro_1_1CartesianVector.md) _._ |
|  [**CartesianVector**](classastrea_1_1astro_1_1CartesianVector.md)&lt; [**Value\_T**](classastrea_1_1astro_1_1CartesianVector.md), [**Frame\_T**](classastrea_1_1astro_1_1CartesianVector.md) &gt; | [**operator-**](#function-operator-_1) () const<br>_Negation operator for_ [_**CartesianVector**_](classastrea_1_1astro_1_1CartesianVector.md) _._ |
|  [**CartesianVector**](classastrea_1_1astro_1_1CartesianVector.md)&lt; [**Value\_T**](classastrea_1_1astro_1_1CartesianVector.md), [**Frame\_T**](classastrea_1_1astro_1_1CartesianVector.md) &gt; & | [**operator-=**](#function-operator-_2) ([**const**](classastrea_1_1astro_1_1CartesianVector.md) [**CartesianVector**](classastrea_1_1astro_1_1CartesianVector.md)&lt; [**Value\_T**](classastrea_1_1astro_1_1CartesianVector.md), [**Frame\_T**](classastrea_1_1astro_1_1CartesianVector.md) &gt; & other) <br>_Subtraction assignment operator for_ [_**CartesianVector**_](classastrea_1_1astro_1_1CartesianVector.md) _._ |
|  [**CartesianVector**](classastrea_1_1astro_1_1CartesianVector.md)&lt; [**decltype**](classastrea_1_1astro_1_1CartesianVector.md)([**Value\_T**](classastrea_1_1astro_1_1CartesianVector.md){}/[**Value\_U**](classastrea_1_1astro_1_1CartesianVector.md){}), [**Frame\_T**](classastrea_1_1astro_1_1CartesianVector.md) &gt; | [**operator/**](#function-operator_4) ([**const**](classastrea_1_1astro_1_1CartesianVector.md) [**Value\_U**](classastrea_1_1astro_1_1CartesianVector.md) & scalar) const<br>_Scalar division operator for_ [_**CartesianVector**_](classastrea_1_1astro_1_1CartesianVector.md) _._ |
|  [**CartesianVector**](classastrea_1_1astro_1_1CartesianVector.md)&lt; [**Value\_T**](classastrea_1_1astro_1_1CartesianVector.md), [**Frame\_T**](classastrea_1_1astro_1_1CartesianVector.md) &gt; & | [**operator/=**](#function-operator_5) ([**const**](classastrea_1_1astro_1_1CartesianVector.md) [**Unitless**](classastrea_1_1astro_1_1CartesianVector.md) & scalar) <br>_Scalar division assignment operator for_ [_**CartesianVector**_](classastrea_1_1astro_1_1CartesianVector.md) _._ |
|  [**CartesianVector**](classastrea_1_1astro_1_1CartesianVector.md)&lt; [**Value\_T**](classastrea_1_1astro_1_1CartesianVector.md), [**Frame\_T**](classastrea_1_1astro_1_1CartesianVector.md) &gt; | [**operator=**](#function-operator_6) ([**const**](classastrea_1_1astro_1_1CartesianVector.md) [**CartesianVector**](classastrea_1_1astro_1_1CartesianVector.md)&lt; [**Value\_T**](classastrea_1_1astro_1_1CartesianVector.md), [**Frame\_U**](classastrea_1_1astro_1_1CartesianVector.md) &gt; & other) = delete<br> |
|  [**CartesianVector**](classastrea_1_1astro_1_1CartesianVector.md)&lt; [**Value\_T**](classastrea_1_1astro_1_1CartesianVector.md), [**Frame\_T**](classastrea_1_1astro_1_1CartesianVector.md) &gt; | [**operator=**](#function-operator_7) ([**CartesianVector**](classastrea_1_1astro_1_1CartesianVector.md)&lt; [**Value\_T**](classastrea_1_1astro_1_1CartesianVector.md), [**Frame\_U**](classastrea_1_1astro_1_1CartesianVector.md) &gt; && other) = delete<br> |
|  [**bool**](classastrea_1_1astro_1_1CartesianVector.md) | [**operator==**](#function-operator_8) ([**const**](classastrea_1_1astro_1_1CartesianVector.md) [**CartesianVector**](classastrea_1_1astro_1_1CartesianVector.md)&lt; [**Value\_U**](classastrea_1_1astro_1_1CartesianVector.md), [**Frame\_T**](classastrea_1_1astro_1_1CartesianVector.md) &gt; & other) const<br>_Equality operator for_ [_**CartesianVector**_](classastrea_1_1astro_1_1CartesianVector.md) _._ |
|  [**bool**](classastrea_1_1astro_1_1CartesianVector.md) | [**operator==**](#function-operator_9) ([**const**](classastrea_1_1astro_1_1CartesianVector.md) [**CartesianVector**](classastrea_1_1astro_1_1CartesianVector.md)&lt; [**Value\_T**](classastrea_1_1astro_1_1CartesianVector.md), [**Frame\_U**](classastrea_1_1astro_1_1CartesianVector.md) &gt; & other) const<br>_Inequality operator for_ [_**CartesianVector**_](classastrea_1_1astro_1_1CartesianVector.md) _in a different frame. Always false._ |
|  [**Value\_T**](classastrea_1_1astro_1_1CartesianVector.md) & | [**operator[]**](#function-operator_10) ([**size\_t**](classastrea_1_1astro_1_1CartesianVector.md) index) <br>_Access operator for vector components._  |
|  [**const**](classastrea_1_1astro_1_1CartesianVector.md) [**Value\_T**](classastrea_1_1astro_1_1CartesianVector.md) & | [**operator[]**](#function-operator_11) ([**size\_t**](classastrea_1_1astro_1_1CartesianVector.md) index) const<br>_Const access operator for vector components._  |
|  [**CartesianVector**](classastrea_1_1astro_1_1CartesianVector.md)&lt; [**Value\_T**](classastrea_1_1astro_1_1CartesianVector.md), [**Frame\_V**](classastrea_1_1astro_1_1CartesianVector.md) &gt; | [**translate**](#function-translate) ([**const**](classastrea_1_1astro_1_1CartesianVector.md) [**CartesianVector**](classastrea_1_1astro_1_1CartesianVector.md)&lt; [**Value\_T**](classastrea_1_1astro_1_1CartesianVector.md), [**Frame\_U**](classastrea_1_1astro_1_1CartesianVector.md) &gt; & other) const<br>_Translate this vector by another vector in a different frame, resulting in a vector in a third frame._  |
|  [**CartesianVector**](classastrea_1_1astro_1_1CartesianVector.md)&lt; [**Unitless**](classastrea_1_1astro_1_1CartesianVector.md), [**Frame\_T**](classastrea_1_1astro_1_1CartesianVector.md) &gt; | [**unit**](#function-unit) () const<br>_Normalize the vector to create a unit vector._  |




























## Detailed Description


This class encapsulates a vector with three components (x, y, z) and provides various operations such as addition, subtraction, scalar multiplication, and dot/cross products.




**Template parameters:**


* `T` The type of the vector components (e.g., Distance, Velocity). 




    
## Public Attributes Documentation




### variable dot 

_Dot product of this vector with another_ [_**CartesianVector**_](classastrea_1_1astro_1_1CartesianVector.md) _._
```C++
decltype(Value_T{} *Value_U{} astrea::astro::CartesianVector< Value_T, Frame_T >::dot) (const CartesianVector< Value_U, Frame_T > &other) const;
```





**Template parameters:**


* `U` The type of the other [**CartesianVector**](classastrea_1_1astro_1_1CartesianVector.md). 



**Parameters:**


* `other` The other [**CartesianVector**](classastrea_1_1astro_1_1CartesianVector.md) to compute the dot product with. 



**Returns:**

decltype(Value\_T{} \* Value\_U{}) The result of the dot product. 





        

<hr>
## Public Functions Documentation




### function CartesianVector [1/3]

_Default constructor for_ [_**CartesianVector**_](classastrea_1_1astro_1_1CartesianVector.md) _._
```C++
inline astrea::astro::CartesianVector::CartesianVector (
    const  Value_T & x=Value_T (),
    const  Value_T & y=Value_T (),
    const  Value_T & z=Value_T ()
) 
```



Initializes the vector components to zero. 

**Parameters:**


* `x` The x component of the vector (default is 0). 
* `y` The y component of the vector (default is 0). 
* `z` The z component of the vector (default is 0). 




        

<hr>



### function CartesianVector [2/3]

```C++
template<typename  Frame_U>
astrea::astro::CartesianVector::CartesianVector (
    const  CartesianVector < Value_T , Frame_U > & other
) = delete
```




<hr>



### function CartesianVector [3/3]

```C++
template<typename  Frame_U>
astrea::astro::CartesianVector::CartesianVector (
    CartesianVector < Value_T , Frame_U > && other
) = delete
```




<hr>



### function cross 

_Cross product of this vector with another_ [_**CartesianVector**_](classastrea_1_1astro_1_1CartesianVector.md) _._
```C++
template<typename  Value_U>
inline CartesianVector < decltype ( Value_T {} * Value_U {}), Frame_T > astrea::astro::CartesianVector::cross (
    const  CartesianVector < Value_U , Frame_T > & other
) const
```





**Template parameters:**


* `U` The type of the other [**CartesianVector**](classastrea_1_1astro_1_1CartesianVector.md). 



**Parameters:**


* `other` The other [**CartesianVector**](classastrea_1_1astro_1_1CartesianVector.md) to compute the cross product with. 



**Returns:**

[**CartesianVector**](classastrea_1_1astro_1_1CartesianVector.md)&lt;decltype(Value\_T{} \* Value\_U{})&gt; The result of the cross product. 





        

<hr>



### function force\_frame\_conversion 

_Copy constructor for_ [_**CartesianVector**_](classastrea_1_1astro_1_1CartesianVector.md) _that implicitly converts the frame._
```C++
template<typename  Frame_U>
inline CartesianVector < Value_T , Frame_U > astrea::astro::CartesianVector::force_frame_conversion () const
```





**Parameters:**


* `other` The other [**CartesianVector**](classastrea_1_1astro_1_1CartesianVector.md) to copy from. 




        

<hr>



### function get\_x [1/2]

_Get the x value of the_ [_**Cartesian**_](classastrea_1_1astro_1_1Cartesian.md) _vector._
```C++
inline Value_T & astrea::astro::CartesianVector::get_x () 
```





**Returns:**

Value\_T& Reference to the x component of the [**Cartesian**](classastrea_1_1astro_1_1Cartesian.md) vector. 





        

<hr>



### function get\_x [2/2]

_Get the x value of the_ [_**Cartesian**_](classastrea_1_1astro_1_1Cartesian.md) _vector._
```C++
inline const  Value_T & astrea::astro::CartesianVector::get_x () const
```





**Returns:**

const Value\_T& Reference to the x component of the [**Cartesian**](classastrea_1_1astro_1_1Cartesian.md) vector. 





        

<hr>



### function get\_y [1/2]

_Get the y value of the_ [_**Cartesian**_](classastrea_1_1astro_1_1Cartesian.md) _vector._
```C++
inline Value_T & astrea::astro::CartesianVector::get_y () 
```





**Returns:**

Value\_T& Reference to the y component of the [**Cartesian**](classastrea_1_1astro_1_1Cartesian.md) vector. 





        

<hr>



### function get\_y [2/2]

_Get the y value of the_ [_**Cartesian**_](classastrea_1_1astro_1_1Cartesian.md) _vector._
```C++
inline const  Value_T & astrea::astro::CartesianVector::get_y () const
```





**Returns:**

const Value\_T& Reference to the y component of the [**Cartesian**](classastrea_1_1astro_1_1Cartesian.md) vector. 





        

<hr>



### function get\_z [1/2]

_Get the z value of the_ [_**Cartesian**_](classastrea_1_1astro_1_1Cartesian.md) _vector._
```C++
inline Value_T & astrea::astro::CartesianVector::get_z () 
```





**Returns:**

Value\_T& Reference to the z component of the [**Cartesian**](classastrea_1_1astro_1_1Cartesian.md) vector. 





        

<hr>



### function get\_z [2/2]

_Get the z value of the_ [_**Cartesian**_](classastrea_1_1astro_1_1Cartesian.md) _vector._
```C++
inline const  Value_T & astrea::astro::CartesianVector::get_z () const
```





**Returns:**

const Value\_T& Reference to the z component of the [**Cartesian**](classastrea_1_1astro_1_1Cartesian.md) vector. 





        

<hr>



### function in\_frame 

_Rotate this vector into another frame at a given date._ 
```C++
template<IsStaticFrame Frame_U>
inline CartesianVector < Value_T , Frame_U > astrea::astro::CartesianVector::in_frame (
    const  Date & date
) const
```





**Template parameters:**


* `Frame_U` The target frame type to rotate into. 



**Parameters:**


* `date` The date at which to perform the rotation. 



**Returns:**

CartesianVector&lt;Value\_T, Frame\_U&gt; A new [**CartesianVector**](classastrea_1_1astro_1_1CartesianVector.md) in the target frame. 




**Exception:**


* `std::runtime_error` If the frames do not share the same origin or if the DCM cannot be obtained. 




        

<hr>



### function norm 

_Calculate the norm (magnitude) of the vector._ 
```C++
inline Value_T astrea::astro::CartesianVector::norm () const
```





**Returns:**

T The norm of the vector. 





        

<hr>



### function offset 

_Calculate the offset vector from another vector in a different frame, resulting in a vector in a third frame._ 
```C++
template<typename  Frame_U, typename  Frame_V>
inline CartesianVector < Value_T , Frame_V > astrea::astro::CartesianVector::offset (
    const  CartesianVector < Value_T , Frame_U > & other
) const
```





**Template parameters:**


* `Frame_U` The frame type of the vector to calculate the offset from. 
* `Frame_V` The frame type of the resulting vector. 



**Parameters:**


* `other` The [**CartesianVector**](classastrea_1_1astro_1_1CartesianVector.md) to calculate the offset from. 



**Returns:**

CartesianVector&lt;Value\_T, Frame\_V&gt; A new [**CartesianVector**](classastrea_1_1astro_1_1CartesianVector.md) in the resulting frame. 




**Note:**

It is the user's responsibility to ensure that this operation makes sense in the context of the frames involved. 





        

<hr>



### function offset\_angle 

_Calculate the angle between this vector and another_ [_**CartesianVector**_](classastrea_1_1astro_1_1CartesianVector.md) _._
```C++
inline Angle astrea::astro::CartesianVector::offset_angle (
    const  CartesianVector < Value_T , Frame_T > & other
) const
```





**Parameters:**


* `other` The other [**CartesianVector**](classastrea_1_1astro_1_1CartesianVector.md) to calculate the angle with. 



**Returns:**

Angle The angle between the two vectors. 




**Exception:**


* `std::runtime_error` If either vector has zero magnitude. 




        

<hr>



### function operator\* 

_Scalar multiplication operator for_ [_**CartesianVector**_](classastrea_1_1astro_1_1CartesianVector.md) _._
```C++
template<typename  Value_U>
inline CartesianVector < decltype ( Value_T {} * Value_U {}), Frame_T > astrea::astro::CartesianVector::operator* (
    const  Value_U & scalar
) const
```





**Template parameters:**


* `U` The type of the scalar to multiply with. 



**Parameters:**


* `scalar` The scalar value to multiply with. 



**Returns:**

CartesianVector&lt;Value\_T \* Value\_U, Frame\_T&gt; A new [**CartesianVector**](classastrea_1_1astro_1_1CartesianVector.md) that is the product of this vector and the scalar. 





        

<hr>



### function operator\*= 

_Scalar multiplication assignment operator for_ [_**CartesianVector**_](classastrea_1_1astro_1_1CartesianVector.md) _._
```C++
inline CartesianVector < Value_T , Frame_T > & astrea::astro::CartesianVector::operator*= (
    const  Unitless & scalar
) 
```





**Parameters:**


* `scalar` The scalar value to multiply with. 



**Returns:**

CartesianVector&lt;Value\_T, Frame\_T&gt;& Reference to the current object after multiplication. 





        

<hr>



### function operator+ 

_Addition operator for_ [_**CartesianVector**_](classastrea_1_1astro_1_1CartesianVector.md) _._
```C++
inline CartesianVector < Value_T , Frame_T > astrea::astro::CartesianVector::operator+ (
    const  CartesianVector < Value_T , Frame_T > & other
) const
```





**Parameters:**


* `other` The other [**CartesianVector**](classastrea_1_1astro_1_1CartesianVector.md) to add. 



**Returns:**

CartesianVector&lt;Value\_T, Frame\_T&gt; A new [**CartesianVector**](classastrea_1_1astro_1_1CartesianVector.md) that is the sum of this vector and the other. 





        

<hr>



### function operator+= 

_Addition assignment operator for_ [_**CartesianVector**_](classastrea_1_1astro_1_1CartesianVector.md) _._
```C++
inline CartesianVector < Value_T , Frame_T > & astrea::astro::CartesianVector::operator+= (
    const  CartesianVector < Value_T , Frame_T > & other
) 
```





**Parameters:**


* `other` The other [**CartesianVector**](classastrea_1_1astro_1_1CartesianVector.md) to add. 



**Returns:**

CartesianVector&lt;Value\_T, Frame\_T&gt;& Reference to the current object after addition. 





        

<hr>



### function operator- 

_Subtraction operator for_ [_**CartesianVector**_](classastrea_1_1astro_1_1CartesianVector.md) _._
```C++
inline CartesianVector < Value_T , Frame_T > astrea::astro::CartesianVector::operator- (
    const  CartesianVector < Value_T , Frame_T > & other
) const
```





**Parameters:**


* `other` The other [**CartesianVector**](classastrea_1_1astro_1_1CartesianVector.md) to subtract. 



**Returns:**

CartesianVector&lt;Value\_T, Frame\_T&gt; A new [**CartesianVector**](classastrea_1_1astro_1_1CartesianVector.md) that is the difference of this vector and the other. 





        

<hr>



### function operator- 

_Negation operator for_ [_**CartesianVector**_](classastrea_1_1astro_1_1CartesianVector.md) _._
```C++
inline CartesianVector < Value_T , Frame_T > astrea::astro::CartesianVector::operator- () const
```





**Returns:**

CartesianVector&lt;T&gt; A new [**CartesianVector**](classastrea_1_1astro_1_1CartesianVector.md) that is the negation of this vector. 





        

<hr>



### function operator-= 

_Subtraction assignment operator for_ [_**CartesianVector**_](classastrea_1_1astro_1_1CartesianVector.md) _._
```C++
inline CartesianVector < Value_T , Frame_T > & astrea::astro::CartesianVector::operator-= (
    const  CartesianVector < Value_T , Frame_T > & other
) 
```





**Parameters:**


* `other` The other [**CartesianVector**](classastrea_1_1astro_1_1CartesianVector.md) to subtract. 



**Returns:**

CartesianVector&lt;Value\_T, Frame\_T&gt;& Reference to the current object after subtraction. 





        

<hr>



### function operator/ 

_Scalar division operator for_ [_**CartesianVector**_](classastrea_1_1astro_1_1CartesianVector.md) _._
```C++
template<typename  Value_U>
inline CartesianVector < decltype ( Value_T {}/ Value_U {}), Frame_T > astrea::astro::CartesianVector::operator/ (
    const  Value_U & scalar
) const
```





**Template parameters:**


* `U` The type of the scalar to divide by. 



**Parameters:**


* `scalar` The scalar value to divide by. 



**Returns:**

[**CartesianVector**](classastrea_1_1astro_1_1CartesianVector.md)&lt;decltype(Value\_T{} / U{})&gt; A new [**CartesianVector**](classastrea_1_1astro_1_1CartesianVector.md) that is the quotient of this vector and the scalar. 





        

<hr>



### function operator/= 

_Scalar division assignment operator for_ [_**CartesianVector**_](classastrea_1_1astro_1_1CartesianVector.md) _._
```C++
inline CartesianVector < Value_T , Frame_T > & astrea::astro::CartesianVector::operator/= (
    const  Unitless & scalar
) 
```





**Parameters:**


* `scalar` The scalar value to divide by. 



**Returns:**

CartesianVector&lt;Value\_T, Frame\_T&gt;& Reference to the current object after division. 





        

<hr>



### function operator= 

```C++
template<typename  Frame_U>
CartesianVector < Value_T , Frame_T > astrea::astro::CartesianVector::operator= (
    const  CartesianVector < Value_T , Frame_U > & other
) = delete
```




<hr>



### function operator= 

```C++
template<typename  Frame_U>
CartesianVector < Value_T , Frame_T > astrea::astro::CartesianVector::operator= (
    CartesianVector < Value_T , Frame_U > && other
) = delete
```




<hr>



### function operator== 

_Equality operator for_ [_**CartesianVector**_](classastrea_1_1astro_1_1CartesianVector.md) _._
```C++
template<typename  Value_U>
inline bool astrea::astro::CartesianVector::operator== (
    const  CartesianVector < Value_U , Frame_T > & other
) const
```





**Parameters:**


* `other` The other [**CartesianVector**](classastrea_1_1astro_1_1CartesianVector.md) to compare with. 



**Returns:**

true If the two vectors are equal. 




**Returns:**

false If the two vectors are not equal. 





        

<hr>



### function operator== 

_Inequality operator for_ [_**CartesianVector**_](classastrea_1_1astro_1_1CartesianVector.md) _in a different frame. Always false._
```C++
template<typename  Frame_U>
inline bool astrea::astro::CartesianVector::operator== (
    const  CartesianVector < Value_T , Frame_U > & other
) const
```





**Parameters:**


* `other` The other [**CartesianVector**](classastrea_1_1astro_1_1CartesianVector.md) to compare with. 



**Returns:**

true If the two vectors are not equal. 




**Returns:**

false If the two vectors are equal. 





        

<hr>



### function operator[] 

_Access operator for vector components._ 
```C++
inline Value_T & astrea::astro::CartesianVector::operator[] (
    size_t index
) 
```





**Parameters:**


* `index` The index of the component to access (0 for x, 1 for y, 2 for z). 



**Returns:**

Value\_T& Reference to the component at the specified index. 





        

<hr>



### function operator[] 

_Const access operator for vector components._ 
```C++
inline const  Value_T & astrea::astro::CartesianVector::operator[] (
    size_t index
) const
```





**Parameters:**


* `index` The index of the component to access (0 for x, 1 for y, 2 for z). 



**Returns:**

const Value\_T& Reference to the component at the specified index. 





        

<hr>



### function translate 

_Translate this vector by another vector in a different frame, resulting in a vector in a third frame._ 
```C++
template<typename  Frame_U, typename  Frame_V>
inline CartesianVector < Value_T , Frame_V > astrea::astro::CartesianVector::translate (
    const  CartesianVector < Value_T , Frame_U > & other
) const
```



This operation is valid when the two frames share the same axis but have different origins. For example, translating a position vector of the Moon relative to the Earth by the position vector of the Earth relative to the Solar System Barycenter results in the position vector of the Moon relative to the Solar System Barycenter.




**Template parameters:**


* `Frame_U` The frame type of the vector to translate by. 
* `Frame_V` The frame type of the resulting vector. 



**Parameters:**


* `other` The [**CartesianVector**](classastrea_1_1astro_1_1CartesianVector.md) to translate by. 



**Returns:**

CartesianVector&lt;Value\_T, Frame\_V&gt; A new [**CartesianVector**](classastrea_1_1astro_1_1CartesianVector.md) in the resulting frame. 




**Note:**

It is the user's responsibility to ensure that this operation makes sense in the context of the frames involved. r&lt;Frame\_T&gt; + r&lt;Frame\_U&gt; = r&lt;Frame\_V&gt; [**rEarth&lt;ssb::icrf&gt;**](classastrea_1_1astro_1_1CartesianVector.md#function-cartesianvector-13) + [**rMoon&lt;earth::icrf&gt;**](classastrea_1_1astro_1_1CartesianVector.md#function-cartesianvector-13) = [**rMoon&lt;ssb::icrf&gt;**](classastrea_1_1astro_1_1CartesianVector.md#function-cartesianvector-13) [**rEarth&lt;ssb::icrf&gt;**](classastrea_1_1astro_1_1CartesianVector.md#function-cartesianvector-13) + [**rMoon&lt;ssb::icrf&gt;**](classastrea_1_1astro_1_1CartesianVector.md#function-cartesianvector-13) = (rEarth + rMoon)&lt;ssb::icrf&gt; [**rEarth&lt;ssb::icrf&gt;**](classastrea_1_1astro_1_1CartesianVector.md#function-cartesianvector-13) + [**rMoon&lt;jupiter::icrf&gt;**](classastrea_1_1astro_1_1CartesianVector.md#function-cartesianvector-13) = (???)&lt;???&gt; there's no way to enforce this makes sense at compile time without explicitly knowing where the vectors start and end, so it has to be left to the user to use it correctly 





        

<hr>



### function unit 

_Normalize the vector to create a unit vector._ 
```C++
inline CartesianVector < Unitless , Frame_T > astrea::astro::CartesianVector::unit () const
```





**Returns:**

CartesianVector&lt;Unitless&gt; A unit vector in the same direction as this vector. 




**Note:**

If the norm is zero, returns a zero vector. 





        

<hr>

------------------------------
The documentation for this class was generated from the following file `astrea/astro/astro/frames/CartesianVector.hpp`

