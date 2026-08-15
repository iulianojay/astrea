

# Struct astrea::astro::CartesianVector

**template &lt;class Value\_T, IsFrame auto \_frame\_&gt;**



[**ClassList**](annotated.md) **>** [**astrea**](namespaceastrea.md) **>** [**astro**](namespaceastrea_1_1astro.md) **>** [**CartesianVector**](structastrea_1_1astro_1_1CartesianVector.md)



_Class representing a 3D vector in_ [_**Cartesian**_](classastrea_1_1astro_1_1Cartesian.md) _coordinates._[More...](#detailed-description)

* `#include <CartesianVector.hpp>`





















## Public Attributes

| Type | Name |
| ---: | :--- |
|  std::array&lt; Value\_T, 3 &gt; | [**\_vector**](#variable-_vector)  <br>_Array to hold the x, y, and z components of the vector._  |
|  constexpr decltype(Value\_T{} \*Value\_U{} | [**dot**](#variable-dot)  <br>_Dot product of this vector with another_ [_**CartesianVector**_](structastrea_1_1astro_1_1CartesianVector.md) _._ |


## Public Static Attributes

| Type | Name |
| ---: | :--- |
|  constexpr auto | [**frame**](#variable-frame)   = `\_frame\_`<br>_The reference frame of the vector._  |














## Public Functions

| Type | Name |
| ---: | :--- |
|  constexpr | [**CartesianVector**](#function-cartesianvector-16) (const Value\_T & x=Value\_T::zero(), const Value\_T & y=Value\_T::zero(), const Value\_T & z=Value\_T::zero()) <br>_Default constructor for_ [_**CartesianVector**_](structastrea_1_1astro_1_1CartesianVector.md) _._ |
|  constexpr | [**CartesianVector**](#function-cartesianvector-26) (const std::array&lt; Value\_T, 3 &gt; & vec) <br>_Constructor for_ [_**CartesianVector**_](structastrea_1_1astro_1_1CartesianVector.md) _from an array of components._ |
|  constexpr | [**CartesianVector**](#function-cartesianvector-36) (const [**CartesianVector**](structastrea_1_1astro_1_1CartesianVector.md) &) = default<br> |
|  constexpr | [**CartesianVector**](#function-cartesianvector-46) ([**CartesianVector**](structastrea_1_1astro_1_1CartesianVector.md) &&) = default<br> |
|  constexpr | [**CartesianVector**](#function-cartesianvector-56) (const [**CartesianVector**](structastrea_1_1astro_1_1CartesianVector.md)&lt; Value\_U, frame\_u &gt; & other) <br> |
|  constexpr | [**CartesianVector**](#function-cartesianvector-66) ([**CartesianVector**](structastrea_1_1astro_1_1CartesianVector.md)&lt; Value\_U, frame\_u &gt; && other) <br> |
|  constexpr [**CartesianVector**](structastrea_1_1astro_1_1CartesianVector.md)&lt; decltype(Value\_T{} \*Value\_U{}), [**frame**](structastrea_1_1astro_1_1CartesianVector.md#variable-frame) &gt; | [**cross**](#function-cross) (const [**CartesianVector**](structastrea_1_1astro_1_1CartesianVector.md)&lt; Value\_U, [**frame**](structastrea_1_1astro_1_1CartesianVector.md#variable-frame) &gt; & other) const<br>_Cross product of this vector with another_ [_**CartesianVector**_](structastrea_1_1astro_1_1CartesianVector.md) _._ |
|  constexpr [**CartesianVector**](structastrea_1_1astro_1_1CartesianVector.md)&lt; Unitless, [**frame**](structastrea_1_1astro_1_1CartesianVector.md#variable-frame) &gt; | [**direction**](#function-direction) () const<br>_Normalize the vector to create a unit vector._  |
|  constexpr [**CartesianVector**](structastrea_1_1astro_1_1CartesianVector.md)&lt; Value\_T, frame\_u &gt; | [**force\_frame\_conversion**](#function-force_frame_conversion) () const<br>_Copy constructor for_ [_**CartesianVector**_](structastrea_1_1astro_1_1CartesianVector.md) _that implicitly converts the frame._ |
|  constexpr Value\_T & | [**get\_x**](#function-get_x-12) () <br>_Get the x value of the_ [_**Cartesian**_](classastrea_1_1astro_1_1Cartesian.md) _vector._ |
|  constexpr const Value\_T & | [**get\_x**](#function-get_x-22) () const<br>_Get the x value of the_ [_**Cartesian**_](classastrea_1_1astro_1_1Cartesian.md) _vector._ |
|  constexpr Value\_T & | [**get\_y**](#function-get_y-12) () <br>_Get the y value of the_ [_**Cartesian**_](classastrea_1_1astro_1_1Cartesian.md) _vector._ |
|  constexpr const Value\_T & | [**get\_y**](#function-get_y-22) () const<br>_Get the y value of the_ [_**Cartesian**_](classastrea_1_1astro_1_1Cartesian.md) _vector._ |
|  constexpr Value\_T & | [**get\_z**](#function-get_z-12) () <br>_Get the z value of the_ [_**Cartesian**_](classastrea_1_1astro_1_1Cartesian.md) _vector._ |
|  constexpr const Value\_T & | [**get\_z**](#function-get_z-22) () const<br>_Get the z value of the_ [_**Cartesian**_](classastrea_1_1astro_1_1Cartesian.md) _vector._ |
|  constexpr [**CartesianVector**](structastrea_1_1astro_1_1CartesianVector.md)&lt; Value\_T, frame\_u &gt; | [**in\_frame**](#function-in_frame-16) (const [**Date**](classastrea_1_1astro_1_1Date.md) & date) const<br>_No-op overload when calling in\_frame with the same frame._  |
|  constexpr [**CartesianVector**](structastrea_1_1astro_1_1CartesianVector.md)&lt; Value\_T, frame\_u &gt; | [**in\_frame**](#function-in_frame-26) (const [**Date**](classastrea_1_1astro_1_1Date.md) &, const [**CartesianVector**](structastrea_1_1astro_1_1CartesianVector.md)&lt; Distance, \_frame\_ &gt; &) const<br>_No-op overload when calling in\_frame with the same frame._  |
|  constexpr [**CartesianVector**](structastrea_1_1astro_1_1CartesianVector.md)&lt; Value\_T, frame\_u &gt; | [**in\_frame**](#function-in_frame-36) (const [**Date**](classastrea_1_1astro_1_1Date.md) &, const [**CartesianVector**](structastrea_1_1astro_1_1CartesianVector.md)&lt; Distance, \_frame\_ &gt; &, const [**CartesianVector**](structastrea_1_1astro_1_1CartesianVector.md)&lt; Velocity, \_frame\_ &gt; &) const<br>_No-op overload when calling in\_frame with the same frame._  |
|  constexpr [**CartesianVector**](structastrea_1_1astro_1_1CartesianVector.md)&lt; Value\_T, frame\_u &gt; | [**in\_frame**](#function-in_frame-46) (const [**Date**](classastrea_1_1astro_1_1Date.md) & date) const<br>_Rotate this vector into another frame at a given date._  |
|  constexpr [**CartesianVector**](structastrea_1_1astro_1_1CartesianVector.md)&lt; Velocity, frame\_u &gt; | [**in\_frame**](#function-in_frame-56) (const [**Date**](classastrea_1_1astro_1_1Date.md) & date, const [**CartesianVector**](structastrea_1_1astro_1_1CartesianVector.md)&lt; Distance, \_frame\_ &gt; & position) const<br>_Rotate this vector into another frame at a given date, accounting for velocity aberration._  |
|  constexpr [**CartesianVector**](structastrea_1_1astro_1_1CartesianVector.md)&lt; Acceleration, frame\_u &gt; | [**in\_frame**](#function-in_frame-66) (const [**Date**](classastrea_1_1astro_1_1Date.md) & date, const [**CartesianVector**](structastrea_1_1astro_1_1CartesianVector.md)&lt; Distance, \_frame\_ &gt; & position, const [**CartesianVector**](structastrea_1_1astro_1_1CartesianVector.md)&lt; Velocity, \_frame\_ &gt; & velocity) const<br>_Rotate this vector into another frame at a given date, accounting for velocity and acceleration aberration._  |
|  constexpr Value\_T | [**norm**](#function-norm) () const<br>_Calculate the norm (magnitude) of the vector._  |
|  constexpr [**CartesianVector**](structastrea_1_1astro_1_1CartesianVector.md)&lt; Value\_T, frame\_v &gt; | [**offset**](#function-offset) (const [**CartesianVector**](structastrea_1_1astro_1_1CartesianVector.md)&lt; Value\_T, frame\_u &gt; & other) const<br>_Calculate the offset vector from another vector in a different frame, resulting in a vector in a third frame._  |
|  constexpr Angle | [**offset\_angle**](#function-offset_angle) (const [**CartesianVector**](structastrea_1_1astro_1_1CartesianVector.md)&lt; Value\_U, [**frame**](structastrea_1_1astro_1_1CartesianVector.md#variable-frame) &gt; & other) const<br>_Calculate the angle between this vector and another_ [_**CartesianVector**_](structastrea_1_1astro_1_1CartesianVector.md) _._ |
|  constexpr [**CartesianVector**](structastrea_1_1astro_1_1CartesianVector.md)&lt; decltype(Value\_T{} \*Value\_U{}), [**frame**](structastrea_1_1astro_1_1CartesianVector.md#variable-frame) &gt; | [**operator\***](#function-operator) (const Value\_U & scalar) const<br>_Scalar multiplication operator for_ [_**CartesianVector**_](structastrea_1_1astro_1_1CartesianVector.md) _._ |
|  constexpr [**CartesianVector**](structastrea_1_1astro_1_1CartesianVector.md) & | [**operator\*=**](#function-operator_1) (const Unitless & scalar) <br>_Scalar multiplication assignment operator for_ [_**CartesianVector**_](structastrea_1_1astro_1_1CartesianVector.md) _._ |
|  constexpr [**CartesianVector**](structastrea_1_1astro_1_1CartesianVector.md) | [**operator+**](#function-operator_2) (const [**CartesianVector**](structastrea_1_1astro_1_1CartesianVector.md) & other) const<br>_Addition operator for_ [_**CartesianVector**_](structastrea_1_1astro_1_1CartesianVector.md) _._ |
|  constexpr [**CartesianVector**](structastrea_1_1astro_1_1CartesianVector.md) & | [**operator+=**](#function-operator_3) (const [**CartesianVector**](structastrea_1_1astro_1_1CartesianVector.md) & other) <br>_Addition assignment operator for_ [_**CartesianVector**_](structastrea_1_1astro_1_1CartesianVector.md) _._ |
|  constexpr [**CartesianVector**](structastrea_1_1astro_1_1CartesianVector.md) | [**operator-**](#function-operator-) (const [**CartesianVector**](structastrea_1_1astro_1_1CartesianVector.md) & other) const<br>_Subtraction operator for_ [_**CartesianVector**_](structastrea_1_1astro_1_1CartesianVector.md) _._ |
|  constexpr [**CartesianVector**](structastrea_1_1astro_1_1CartesianVector.md) | [**operator-**](#function-operator-_1) () const<br>_Negation operator for_ [_**CartesianVector**_](structastrea_1_1astro_1_1CartesianVector.md) _._ |
|  constexpr [**CartesianVector**](structastrea_1_1astro_1_1CartesianVector.md) & | [**operator-=**](#function-operator-_2) (const [**CartesianVector**](structastrea_1_1astro_1_1CartesianVector.md) & other) <br>_Subtraction assignment operator for_ [_**CartesianVector**_](structastrea_1_1astro_1_1CartesianVector.md) _._ |
|  constexpr [**CartesianVector**](structastrea_1_1astro_1_1CartesianVector.md)&lt; decltype(Value\_T{}/Value\_U{}), [**frame**](structastrea_1_1astro_1_1CartesianVector.md#variable-frame) &gt; | [**operator/**](#function-operator_4) (const Value\_U & scalar) const<br>_Scalar division operator for_ [_**CartesianVector**_](structastrea_1_1astro_1_1CartesianVector.md) _._ |
|  constexpr [**CartesianVector**](structastrea_1_1astro_1_1CartesianVector.md) & | [**operator/=**](#function-operator_5) (const Unitless & scalar) <br>_Scalar division assignment operator for_ [_**CartesianVector**_](structastrea_1_1astro_1_1CartesianVector.md) _._ |
|  constexpr [**CartesianVector**](structastrea_1_1astro_1_1CartesianVector.md) & | [**operator=**](#function-operator_6) (const [**CartesianVector**](structastrea_1_1astro_1_1CartesianVector.md) &) = default<br> |
|  constexpr [**CartesianVector**](structastrea_1_1astro_1_1CartesianVector.md) & | [**operator=**](#function-operator_7) ([**CartesianVector**](structastrea_1_1astro_1_1CartesianVector.md) &&) = default<br> |
|  constexpr [**CartesianVector**](structastrea_1_1astro_1_1CartesianVector.md) | [**operator=**](#function-operator_8) (const [**CartesianVector**](structastrea_1_1astro_1_1CartesianVector.md)&lt; Value\_U, [**frame**](structastrea_1_1astro_1_1CartesianVector.md#variable-frame) &gt; & other) const<br>_Copy constructor for_ [_**CartesianVector**_](structastrea_1_1astro_1_1CartesianVector.md) _that implicitly converts the unit._ |
|  constexpr bool | [**operator==**](#function-operator_9) (const [**CartesianVector**](structastrea_1_1astro_1_1CartesianVector.md) & other) const<br>_Equality operator for_ [_**CartesianVector**_](structastrea_1_1astro_1_1CartesianVector.md) _(same type and frame)._ |
|  constexpr bool | [**operator==**](#function-operator_10) (const OtherCart & other) const<br>_Equality operator for_ [_**CartesianVector**_](structastrea_1_1astro_1_1CartesianVector.md) _in a different frame or with an incompatible value type. Always returns false._ |
|  constexpr Value\_T & | [**operator[]**](#function-operator_11) (size\_t index) <br>_Access operator for vector components._  |
|  constexpr const Value\_T & | [**operator[]**](#function-operator_12) (size\_t index) const<br>_Const access operator for vector components._  |
|  constexpr Value\_T | [**p\_norm**](#function-p_norm) () const<br>_Calculate the p-norm of the vector._  |
|  constexpr [**CartesianVector**](structastrea_1_1astro_1_1CartesianVector.md) | [**reverse**](#function-reverse) () const<br>_Return the reverse of the vector, which switches the x and z components. This is useful for converting between different rotation sequences._  |
|  constexpr [**CartesianVector**](structastrea_1_1astro_1_1CartesianVector.md)&lt; Value\_T, frame\_v &gt; | [**translate**](#function-translate) (const [**CartesianVector**](structastrea_1_1astro_1_1CartesianVector.md)&lt; Value\_T, frame\_u &gt; & other) const<br>_Translate this vector by another vector in a different frame, resulting in a vector in a third frame._  |
|  constexpr | [**~CartesianVector**](#function-cartesianvector) () = default<br>_Destructor for_ [_**CartesianVector**_](structastrea_1_1astro_1_1CartesianVector.md) _._ |




























## Detailed Description


This class encapsulates a vector with three components (x, y, z) and provides various operations such as addition, subtraction, scalar multiplication, and dot/cross products.




**Template parameters:**


* `T` The type of the vector components (e.g., Distance, Velocity). 




    
## Public Attributes Documentation




### variable \_vector 

_Array to hold the x, y, and z components of the vector._ 
```C++
std::array<Value_T, 3> astrea::astro::CartesianVector< Value_T, _frame_ >::_vector;
```




<hr>



### variable dot 

_Dot product of this vector with another_ [_**CartesianVector**_](structastrea_1_1astro_1_1CartesianVector.md) _._
```C++
constexpr decltype(Value_T{} *Value_U{} astrea::astro::CartesianVector< Value_T, _frame_ >::dot) (const CartesianVector< Value_U, frame > &other) const;
```





**Template parameters:**


* `U` The type of the other [**CartesianVector**](structastrea_1_1astro_1_1CartesianVector.md). 



**Parameters:**


* `other` The other [**CartesianVector**](structastrea_1_1astro_1_1CartesianVector.md) to compute the dot product with. 



**Returns:**

decltype(Value\_T{} \* Value\_U{}) The result of the dot product. 





        

<hr>
## Public Static Attributes Documentation




### variable frame 

_The reference frame of the vector._ 
```C++
constexpr auto astrea::astro::CartesianVector< Value_T, _frame_ >::frame;
```




<hr>
## Public Functions Documentation




### function CartesianVector [1/6]

_Default constructor for_ [_**CartesianVector**_](structastrea_1_1astro_1_1CartesianVector.md) _._
```C++
inline constexpr astrea::astro::CartesianVector::CartesianVector (
    const Value_T & x=Value_T::zero(),
    const Value_T & y=Value_T::zero(),
    const Value_T & z=Value_T::zero()
) 
```



Initializes the vector components to zero. 

**Parameters:**


* `x` The x component of the vector (default is 0). 
* `y` The y component of the vector (default is 0). 
* `z` The z component of the vector (default is 0). 




        

<hr>



### function CartesianVector [2/6]

_Constructor for_ [_**CartesianVector**_](structastrea_1_1astro_1_1CartesianVector.md) _from an array of components._
```C++
inline constexpr astrea::astro::CartesianVector::CartesianVector (
    const std::array< Value_T, 3 > & vec
) 
```





**Parameters:**


* `vec` An array containing the three components of the vector (x, y, z). 




        

<hr>



### function CartesianVector [3/6]

```C++
inline constexpr astrea::astro::CartesianVector::CartesianVector (
    const CartesianVector &
) = default
```




<hr>



### function CartesianVector [4/6]

```C++
inline constexpr astrea::astro::CartesianVector::CartesianVector (
    CartesianVector &&
) = default
```




<hr>



### function CartesianVector [5/6]

```C++
template<typename Value_U, auto frame_u>
inline constexpr astrea::astro::CartesianVector::CartesianVector (
    const CartesianVector < Value_U, frame_u > & other
) 
```




<hr>



### function CartesianVector [6/6]

```C++
template<typename Value_U, auto frame_u>
inline constexpr astrea::astro::CartesianVector::CartesianVector (
    CartesianVector < Value_U, frame_u > && other
) 
```




<hr>



### function cross 

_Cross product of this vector with another_ [_**CartesianVector**_](structastrea_1_1astro_1_1CartesianVector.md) _._
```C++
template<typename Value_U>
inline constexpr CartesianVector < decltype(Value_T{} *Value_U{}), frame > astrea::astro::CartesianVector::cross (
    const CartesianVector < Value_U, frame > & other
) const
```





**Template parameters:**


* `U` The type of the other [**CartesianVector**](structastrea_1_1astro_1_1CartesianVector.md). 



**Parameters:**


* `other` The other [**CartesianVector**](structastrea_1_1astro_1_1CartesianVector.md) to compute the cross product with. 



**Returns:**

[**CartesianVector**](structastrea_1_1astro_1_1CartesianVector.md)&lt;decltype(Value\_T{} \* Value\_U{})&gt; The result of the cross product. 





        

<hr>



### function direction 

_Normalize the vector to create a unit vector._ 
```C++
inline constexpr CartesianVector < Unitless, frame > astrea::astro::CartesianVector::direction () const
```





**Returns:**

CartesianVector&lt;Unitless&gt; A unit vector in the same direction as this vector. 




**Note:**

If the norm is zero, returns a zero vector. 





        

<hr>



### function force\_frame\_conversion 

_Copy constructor for_ [_**CartesianVector**_](structastrea_1_1astro_1_1CartesianVector.md) _that implicitly converts the frame._
```C++
template<IsFrame auto frame_u>
inline constexpr CartesianVector < Value_T, frame_u > astrea::astro::CartesianVector::force_frame_conversion () const
```





**Parameters:**


* `other` The other [**CartesianVector**](structastrea_1_1astro_1_1CartesianVector.md) to copy from. 




        

<hr>



### function get\_x [1/2]

_Get the x value of the_ [_**Cartesian**_](classastrea_1_1astro_1_1Cartesian.md) _vector._
```C++
inline constexpr Value_T & astrea::astro::CartesianVector::get_x () 
```





**Returns:**

Value\_T& Reference to the x component of the [**Cartesian**](classastrea_1_1astro_1_1Cartesian.md) vector. 





        

<hr>



### function get\_x [2/2]

_Get the x value of the_ [_**Cartesian**_](classastrea_1_1astro_1_1Cartesian.md) _vector._
```C++
inline constexpr const Value_T & astrea::astro::CartesianVector::get_x () const
```





**Returns:**

const Value\_T& Reference to the x component of the [**Cartesian**](classastrea_1_1astro_1_1Cartesian.md) vector. 





        

<hr>



### function get\_y [1/2]

_Get the y value of the_ [_**Cartesian**_](classastrea_1_1astro_1_1Cartesian.md) _vector._
```C++
inline constexpr Value_T & astrea::astro::CartesianVector::get_y () 
```





**Returns:**

Value\_T& Reference to the y component of the [**Cartesian**](classastrea_1_1astro_1_1Cartesian.md) vector. 





        

<hr>



### function get\_y [2/2]

_Get the y value of the_ [_**Cartesian**_](classastrea_1_1astro_1_1Cartesian.md) _vector._
```C++
inline constexpr const Value_T & astrea::astro::CartesianVector::get_y () const
```





**Returns:**

const Value\_T& Reference to the y component of the [**Cartesian**](classastrea_1_1astro_1_1Cartesian.md) vector. 





        

<hr>



### function get\_z [1/2]

_Get the z value of the_ [_**Cartesian**_](classastrea_1_1astro_1_1Cartesian.md) _vector._
```C++
inline constexpr Value_T & astrea::astro::CartesianVector::get_z () 
```





**Returns:**

Value\_T& Reference to the z component of the [**Cartesian**](classastrea_1_1astro_1_1Cartesian.md) vector. 





        

<hr>



### function get\_z [2/2]

_Get the z value of the_ [_**Cartesian**_](classastrea_1_1astro_1_1Cartesian.md) _vector._
```C++
inline constexpr const Value_T & astrea::astro::CartesianVector::get_z () const
```





**Returns:**

const Value\_T& Reference to the z component of the [**Cartesian**](classastrea_1_1astro_1_1Cartesian.md) vector. 





        

<hr>



### function in\_frame [1/6]

_No-op overload when calling in\_frame with the same frame._ 
```C++
template<IsFrame auto frame_u>
inline constexpr CartesianVector < Value_T, frame_u > astrea::astro::CartesianVector::in_frame (
    const Date & date
) const
```





**Template parameters:**


* `frame_u` The target frame type to get the vector in. 



**Returns:**

CartesianVector&lt;Value\_T, frame\_u&gt; A new [**CartesianVector**](structastrea_1_1astro_1_1CartesianVector.md) in the target frame. 




**Exception:**


* `std::runtime_error` If the frames do not share the same origin or if the DCM cannot be obtained. 




        

<hr>



### function in\_frame [2/6]

_No-op overload when calling in\_frame with the same frame._ 
```C++
template<IsFrame auto frame_u>
inline constexpr CartesianVector < Value_T, frame_u > astrea::astro::CartesianVector::in_frame (
    const Date &,
    const CartesianVector < Distance, _frame_ > &
) const
```





**Template parameters:**


* `frame_u` The target frame type to get the vector in. 



**Returns:**

CartesianVector&lt;Value\_T, frame\_u&gt; A new [**CartesianVector**](structastrea_1_1astro_1_1CartesianVector.md) in the target frame. 




**Exception:**


* `std::runtime_error` If the frames do not share the same origin or if the DCM cannot be obtained. 




        

<hr>



### function in\_frame [3/6]

_No-op overload when calling in\_frame with the same frame._ 
```C++
template<IsFrame auto frame_u>
inline constexpr CartesianVector < Value_T, frame_u > astrea::astro::CartesianVector::in_frame (
    const Date &,
    const CartesianVector < Distance, _frame_ > &,
    const CartesianVector < Velocity, _frame_ > &
) const
```





**Template parameters:**


* `frame_u` The target frame type to get the vector in. 



**Returns:**

CartesianVector&lt;Value\_T, frame\_u&gt; A new [**CartesianVector**](structastrea_1_1astro_1_1CartesianVector.md) in the target frame. 




**Exception:**


* `std::runtime_error` If the frames do not share the same origin or if the DCM cannot be obtained. 




        

<hr>



### function in\_frame [4/6]

_Rotate this vector into another frame at a given date._ 
```C++
template<IsFrame auto frame_u>
inline constexpr CartesianVector < Value_T, frame_u > astrea::astro::CartesianVector::in_frame (
    const Date & date
) const
```





**Template parameters:**


* `frame_u` The target frame type to rotate into. 



**Parameters:**


* `date` The date at which to perform the rotation. 



**Returns:**

CartesianVector&lt;Value\_T, frame\_u&gt; A new [**CartesianVector**](structastrea_1_1astro_1_1CartesianVector.md) in the target frame. 




**Exception:**


* `std::runtime_error` If the frames do not share the same origin or if the DCM cannot be obtained. 




        

<hr>



### function in\_frame [5/6]

_Rotate this vector into another frame at a given date, accounting for velocity aberration._ 
```C++
template<IsFrame auto frame_u>
inline constexpr CartesianVector < Velocity, frame_u > astrea::astro::CartesianVector::in_frame (
    const Date & date,
    const CartesianVector < Distance, _frame_ > & position
) const
```





**Template parameters:**


* `frame_u` The target frame type to rotate into. 



**Parameters:**


* `date` The date at which to perform the rotation. 
* `position` The position vector in the original frame, used for calculating velocity aberration effects. 



**Returns:**

CartesianVector&lt;Value\_T, frame\_u&gt; A new [**CartesianVector**](structastrea_1_1astro_1_1CartesianVector.md) in the target frame. 




**Exception:**


* `std::runtime_error` If the frames do not share the same origin or if the DCM cannot be obtained. 



**Note:**

This is only valid for velocity vectors since velocity aberration is a function of the position and velocity of the object. 





        

<hr>



### function in\_frame [6/6]

_Rotate this vector into another frame at a given date, accounting for velocity and acceleration aberration._ 
```C++
template<IsFrame auto frame_u>
inline constexpr CartesianVector < Acceleration, frame_u > astrea::astro::CartesianVector::in_frame (
    const Date & date,
    const CartesianVector < Distance, _frame_ > & position,
    const CartesianVector < Velocity, _frame_ > & velocity
) const
```





**Template parameters:**


* `frame_u` The target frame type to rotate into. 



**Parameters:**


* `date` The date at which to perform the rotation. 
* `position` The position vector in the original frame, used for calculating aberration effects. 
* `velocity` The velocity vector in the original frame, used for calculating aberration effects. 



**Returns:**

CartesianVector&lt;Value\_T, frame\_u&gt; A new [**CartesianVector**](structastrea_1_1astro_1_1CartesianVector.md) in the target frame. 




**Exception:**


* `std::runtime_error` If the frames do not share the same origin or if the DCM cannot be obtained. 



**Note:**

This is only valid for acceleration vectors since velocity and acceleration aberration are functions of the position, velocity, and acceleration of the object. 





        

<hr>



### function norm 

_Calculate the norm (magnitude) of the vector._ 
```C++
inline constexpr Value_T astrea::astro::CartesianVector::norm () const
```





**Returns:**

T The norm of the vector.




**Note:**

: This can't be called "magnitude" due to an mp-units type resolution bug 





        

<hr>



### function offset 

_Calculate the offset vector from another vector in a different frame, resulting in a vector in a third frame._ 
```C++
template<IsFrame auto frame_u, IsFrame auto frame_v>
inline constexpr CartesianVector < Value_T, frame_v > astrea::astro::CartesianVector::offset (
    const CartesianVector < Value_T, frame_u > & other
) const
```





**Template parameters:**


* `frame_u` The frame type of the vector to calculate the offset from. 
* `frame_v` The frame type of the resulting vector. 



**Parameters:**


* `other` The [**CartesianVector**](structastrea_1_1astro_1_1CartesianVector.md) to calculate the offset from. 



**Returns:**

CartesianVector&lt;Value\_T, frame\_v&gt; A new [**CartesianVector**](structastrea_1_1astro_1_1CartesianVector.md) in the resulting frame. 




**Note:**

It is the user's responsibility to ensure that this operation makes sense in the context of the frames involved. 





        

<hr>



### function offset\_angle 

_Calculate the angle between this vector and another_ [_**CartesianVector**_](structastrea_1_1astro_1_1CartesianVector.md) _._
```C++
template<typename Value_U>
inline constexpr Angle astrea::astro::CartesianVector::offset_angle (
    const CartesianVector < Value_U, frame > & other
) const
```





**Template parameters:**


* `U` The type of the other [**CartesianVector**](structastrea_1_1astro_1_1CartesianVector.md). 



**Parameters:**


* `other` The other [**CartesianVector**](structastrea_1_1astro_1_1CartesianVector.md) to calculate the angle with. 



**Returns:**

Angle The angle between the two vectors. 




**Exception:**


* `std::runtime_error` If either vector has zero magnitude. 




        

<hr>



### function operator\* 

_Scalar multiplication operator for_ [_**CartesianVector**_](structastrea_1_1astro_1_1CartesianVector.md) _._
```C++
template<typename Value_U>
inline constexpr CartesianVector < decltype(Value_T{} *Value_U{}), frame > astrea::astro::CartesianVector::operator* (
    const Value_U & scalar
) const
```





**Template parameters:**


* `U` The type of the scalar to multiply with. 



**Parameters:**


* `scalar` The scalar value to multiply with. 



**Returns:**

CartesianVector&lt;Value\_T \* Value\_U, frame&gt; A new [**CartesianVector**](structastrea_1_1astro_1_1CartesianVector.md) that is the product of this vector and the scalar. 





        

<hr>



### function operator\*= 

_Scalar multiplication assignment operator for_ [_**CartesianVector**_](structastrea_1_1astro_1_1CartesianVector.md) _._
```C++
inline constexpr CartesianVector & astrea::astro::CartesianVector::operator*= (
    const Unitless & scalar
) 
```





**Parameters:**


* `scalar` The scalar value to multiply with. 



**Returns:**

[**CartesianVector**](structastrea_1_1astro_1_1CartesianVector.md)& Reference to the current object after multiplication. 





        

<hr>



### function operator+ 

_Addition operator for_ [_**CartesianVector**_](structastrea_1_1astro_1_1CartesianVector.md) _._
```C++
inline constexpr CartesianVector astrea::astro::CartesianVector::operator+ (
    const CartesianVector & other
) const
```





**Parameters:**


* `other` The other [**CartesianVector**](structastrea_1_1astro_1_1CartesianVector.md) to add. 



**Returns:**

[**CartesianVector**](structastrea_1_1astro_1_1CartesianVector.md) A new [**CartesianVector**](structastrea_1_1astro_1_1CartesianVector.md) that is the sum of this vector and the other. 





        

<hr>



### function operator+= 

_Addition assignment operator for_ [_**CartesianVector**_](structastrea_1_1astro_1_1CartesianVector.md) _._
```C++
inline constexpr CartesianVector & astrea::astro::CartesianVector::operator+= (
    const CartesianVector & other
) 
```





**Parameters:**


* `other` The other [**CartesianVector**](structastrea_1_1astro_1_1CartesianVector.md) to add. 



**Returns:**

[**CartesianVector**](structastrea_1_1astro_1_1CartesianVector.md)& Reference to the current object after addition. 





        

<hr>



### function operator- 

_Subtraction operator for_ [_**CartesianVector**_](structastrea_1_1astro_1_1CartesianVector.md) _._
```C++
inline constexpr CartesianVector astrea::astro::CartesianVector::operator- (
    const CartesianVector & other
) const
```





**Parameters:**


* `other` The other [**CartesianVector**](structastrea_1_1astro_1_1CartesianVector.md) to subtract. 



**Returns:**

[**CartesianVector**](structastrea_1_1astro_1_1CartesianVector.md) A new [**CartesianVector**](structastrea_1_1astro_1_1CartesianVector.md) that is the difference of this vector and the other. 





        

<hr>



### function operator- 

_Negation operator for_ [_**CartesianVector**_](structastrea_1_1astro_1_1CartesianVector.md) _._
```C++
inline constexpr CartesianVector astrea::astro::CartesianVector::operator- () const
```





**Returns:**

CartesianVector&lt;T&gt; A new [**CartesianVector**](structastrea_1_1astro_1_1CartesianVector.md) that is the negation of this vector. 





        

<hr>



### function operator-= 

_Subtraction assignment operator for_ [_**CartesianVector**_](structastrea_1_1astro_1_1CartesianVector.md) _._
```C++
inline constexpr CartesianVector & astrea::astro::CartesianVector::operator-= (
    const CartesianVector & other
) 
```





**Parameters:**


* `other` The other [**CartesianVector**](structastrea_1_1astro_1_1CartesianVector.md) to subtract. 



**Returns:**

[**CartesianVector**](structastrea_1_1astro_1_1CartesianVector.md)& Reference to the current object after subtraction. 





        

<hr>



### function operator/ 

_Scalar division operator for_ [_**CartesianVector**_](structastrea_1_1astro_1_1CartesianVector.md) _._
```C++
template<typename Value_U>
inline constexpr CartesianVector < decltype(Value_T{}/Value_U{}), frame > astrea::astro::CartesianVector::operator/ (
    const Value_U & scalar
) const
```





**Template parameters:**


* `U` The type of the scalar to divide by. 



**Parameters:**


* `scalar` The scalar value to divide by. 



**Returns:**

[**CartesianVector**](structastrea_1_1astro_1_1CartesianVector.md)&lt;decltype(Value\_T{} / U{})&gt; A new [**CartesianVector**](structastrea_1_1astro_1_1CartesianVector.md) that is the quotient of this vector and the scalar. 





        

<hr>



### function operator/= 

_Scalar division assignment operator for_ [_**CartesianVector**_](structastrea_1_1astro_1_1CartesianVector.md) _._
```C++
inline constexpr CartesianVector & astrea::astro::CartesianVector::operator/= (
    const Unitless & scalar
) 
```





**Parameters:**


* `scalar` The scalar value to divide by. 



**Returns:**

[**CartesianVector**](structastrea_1_1astro_1_1CartesianVector.md)& Reference to the current object after division. 





        

<hr>



### function operator= 

```C++
inline constexpr CartesianVector & astrea::astro::CartesianVector::operator= (
    const CartesianVector &
) = default
```




<hr>



### function operator= 

```C++
inline constexpr CartesianVector & astrea::astro::CartesianVector::operator= (
    CartesianVector &&
) = default
```




<hr>



### function operator= 

_Copy constructor for_ [_**CartesianVector**_](structastrea_1_1astro_1_1CartesianVector.md) _that implicitly converts the unit._
```C++
template<typename Value_U>
inline constexpr CartesianVector astrea::astro::CartesianVector::operator= (
    const CartesianVector < Value_U, frame > & other
) const
```





**Returns:**

[**CartesianVector**](structastrea_1_1astro_1_1CartesianVector.md) A new [**CartesianVector**](structastrea_1_1astro_1_1CartesianVector.md) with the same components but potentially different unit. 





        

<hr>



### function operator== 

_Equality operator for_ [_**CartesianVector**_](structastrea_1_1astro_1_1CartesianVector.md) _(same type and frame)._
```C++
inline constexpr bool astrea::astro::CartesianVector::operator== (
    const CartesianVector & other
) const
```





**Parameters:**


* `other` The other [**CartesianVector**](structastrea_1_1astro_1_1CartesianVector.md) to compare with. 



**Returns:**

true If the two vectors are equal. 




**Returns:**

false If the two vectors are not equal. 





        

<hr>



### function operator== 

_Equality operator for_ [_**CartesianVector**_](structastrea_1_1astro_1_1CartesianVector.md) _in a different frame or with an incompatible value type. Always returns false._
```C++
template<class OtherCart>
inline constexpr bool astrea::astro::CartesianVector::operator== (
    const OtherCart & other
) const
```



Uses a type-parameter approach to avoid GCC 15's constrained auto NTTP deduction bug (which incorrectly deduces `frame_u = Value_U` for `IsFrame auto frame_u` in both direct and reversed lookup).




**Parameters:**


* `other` The other [**CartesianVector**](structastrea_1_1astro_1_1CartesianVector.md) to compare with. 



**Returns:**

false Always, since vectors in different frames or with incompatible types cannot be equal. 





        

<hr>



### function operator[] 

_Access operator for vector components._ 
```C++
inline constexpr Value_T & astrea::astro::CartesianVector::operator[] (
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
inline constexpr const Value_T & astrea::astro::CartesianVector::operator[] (
    size_t index
) const
```





**Parameters:**


* `index` The index of the component to access (0 for x, 1 for y, 2 for z). 



**Returns:**

const Value\_T& Reference to the component at the specified index. 





        

<hr>



### function p\_norm 

_Calculate the p-norm of the vector._ 
```C++
template<unsigned N>
inline constexpr Value_T astrea::astro::CartesianVector::p_norm () const
```





**Template parameters:**


* `N` The order of the norm to calculate (default is 2 for Euclidean norm). 



**Returns:**

T The p-norm of the vector. 





        

<hr>



### function reverse 

_Return the reverse of the vector, which switches the x and z components. This is useful for converting between different rotation sequences._ 
```C++
inline constexpr CartesianVector astrea::astro::CartesianVector::reverse () const
```




<hr>



### function translate 

_Translate this vector by another vector in a different frame, resulting in a vector in a third frame._ 
```C++
template<IsFrame auto frame_u, IsFrame auto frame_v>
inline constexpr CartesianVector < Value_T, frame_v > astrea::astro::CartesianVector::translate (
    const CartesianVector < Value_T, frame_u > & other
) const
```



This operation is valid when the two frames share the same axis but have different origins. For example, translating a position vector of the Moon relative to the Earth by the position vector of the Earth relative to the Solar System [**Barycenter**](structastrea_1_1astro_1_1Barycenter.md) results in the position vector of the Moon relative to the Solar System [**Barycenter**](structastrea_1_1astro_1_1Barycenter.md).




**Template parameters:**


* `frame_u` The frame type of the vector to translate by. 
* `frame_v` The frame type of the resulting vector. 



**Parameters:**


* `other` The [**CartesianVector**](structastrea_1_1astro_1_1CartesianVector.md) to translate by. 



**Returns:**

CartesianVector&lt;Value\_T, frame\_v&gt; A new [**CartesianVector**](structastrea_1_1astro_1_1CartesianVector.md) in the resulting frame. 




**Note:**

It is the user's responsibility to ensure that this operation makes sense in the context of the frames involved. r&lt;frame&gt; + r&lt;frame\_u&gt; = r&lt;frame\_v&gt; rEarth&lt;ssb::icrf&gt; + rMoon&lt;earth::icrf&gt; = rMoon&lt;ssb::icrf&gt; rEarth&lt;ssb::icrf&gt; + rMoon&lt;ssb::icrf&gt; = (rEarth + rMoon)&lt;ssb::icrf&gt; rEarth&lt;ssb::icrf&gt; + rMoon&lt;jupiter::icrf&gt; = (???)&lt;???&gt; there's no way to enforce this makes sense at compile time without explicitly knowing where the vectors start and end, so it has to be left to the user to use it correctly 





        

<hr>



### function ~CartesianVector 

_Destructor for_ [_**CartesianVector**_](structastrea_1_1astro_1_1CartesianVector.md) _._
```C++
inline constexpr astrea::astro::CartesianVector::~CartesianVector () = default
```




<hr>

------------------------------
The documentation for this class was generated from the following file `astrea/astro/astro/frames/framework/CartesianVector.hpp`

