

# Class astrea::astro::Quaternion

**template &lt;IsFrame [**auto**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) \_in\_frame\_, IsFrame [**auto**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) \_out\_frame\_&gt;**



[**ClassList**](annotated.md) **>** [**astrea**](namespaceastrea.md) **>** [**astro**](namespaceastrea_1_1astro.md) **>** [**Quaternion**](classastrea_1_1astro_1_1Quaternion.md)



_Class representing a quaternion for attitude rotations between frames._ [More...](#detailed-description)

* `#include <Quaternion.hpp>`























## Public Static Attributes

| Type | Name |
| ---: | :--- |
|  [**constexpr**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) [**auto**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) | [**in\_frame**](#variable-in_frame)   = `[**\_in\_frame\_**](classastrea_1_1astro_1_1DirectionCosineMatrix.md)`<br> |
|  [**constexpr**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) [**auto**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) | [**out\_frame**](#variable-out_frame)   = `[**\_out\_frame\_**](classastrea_1_1astro_1_1DirectionCosineMatrix.md)`<br> |














## Public Functions

| Type | Name |
| ---: | :--- |
|   | [**Quaternion**](#function-quaternion-19) () <br>_Default constructor for the_ [_**Quaternion**_](classastrea_1_1astro_1_1Quaternion.md) _class. Initializes to the identity quaternion (no rotation)._ |
|   | [**Quaternion**](#function-quaternion-29) ([**const**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) [**CartesianVector**](structastrea_1_1astro_1_1CartesianVector.md)&lt; [**Unitless**](classastrea_1_1astro_1_1DirectionCosineMatrix.md), in\_frame &gt; & vec) <br>_Constructor for the_ [_**Quaternion**_](classastrea_1_1astro_1_1Quaternion.md) _class from a_[_**CartesianVector**_](structastrea_1_1astro_1_1CartesianVector.md) _._ |
|   | [**Quaternion**](#function-quaternion-39) ([**const**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) [**Unitless**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) & s, [**const**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) [**CartesianVector**](structastrea_1_1astro_1_1CartesianVector.md)&lt; [**Unitless**](classastrea_1_1astro_1_1DirectionCosineMatrix.md), in\_frame &gt; & vec) <br>_Constructor for the_ [_**Quaternion**_](classastrea_1_1astro_1_1Quaternion.md) _class from a scalar and a_[_**CartesianVector**_](structastrea_1_1astro_1_1CartesianVector.md) _._ |
|   | [**Quaternion**](#function-quaternion-49) ([**const**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) [**Unitless**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) & s, [**const**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) [**Unitless**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) & x, [**const**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) [**Unitless**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) & y, [**const**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) [**Unitless**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) & z) <br>_Constructor for the_ [_**Quaternion**_](classastrea_1_1astro_1_1Quaternion.md) _class from individual components._ |
|   | [**Quaternion**](#function-quaternion-59) ([**const**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) [**Quaternion**](classastrea_1_1astro_1_1Quaternion.md) & other) = default<br>_Default copy constructor._  |
|   | [**Quaternion**](#function-quaternion-69) ([**Quaternion**](classastrea_1_1astro_1_1Quaternion.md) && other) = default<br>_Default move constructor._  |
|   | [**Quaternion**](#function-quaternion-79) ([**const**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) [**DirectionCosineMatrix**](classastrea_1_1astro_1_1DirectionCosineMatrix.md)&lt; in\_frame, out\_frame &gt; & dcm) <br>_Constructor for the_ [_**Quaternion**_](classastrea_1_1astro_1_1Quaternion.md) _class from a Direction Cosine Matrix (DCM)._ |
|   | [**Quaternion**](#function-quaternion-89) ([**const**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) [**EulerAngles**](classastrea_1_1astro_1_1EulerAngles.md)&lt; sequence, [**rotation\_type**](classastrea_1_1astro_1_1DirectionCosineMatrix.md), in\_frame, out\_frame &gt; & angleSequence) <br>_Constructor for the_ [_**Quaternion**_](classastrea_1_1astro_1_1Quaternion.md) _class from an Euler angle sequence._ |
|   | [**Quaternion**](#function-quaternion-99) ([**const**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) [**Angle**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) & angle, [**const**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) [**CartesianVector**](structastrea_1_1astro_1_1CartesianVector.md)&lt; [**Unitless**](classastrea_1_1astro_1_1DirectionCosineMatrix.md), in\_frame &gt; & axis) <br>_Constructor for the_ [_**Quaternion**_](classastrea_1_1astro_1_1Quaternion.md) _class from an angle and rotation axis._ |
|  [**Quaternion**](classastrea_1_1astro_1_1Quaternion.md)&lt; out\_frame, in\_frame &gt; | [**conjugate**](#function-conjugate) () const<br>_Computes the conjugate of the quaternion._  |
|  [**Unitless**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) | [**dot**](#function-dot) ([**const**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) [**Quaternion**](classastrea_1_1astro_1_1Quaternion.md)&lt; in\_frame, out\_frame &gt; & other) const<br>_Computes the dot product between this quaternion and another quaternion._  |
|  std::vector&lt; [**Unitless**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) &gt; | [**force\_to\_vector**](#function-force_to_vector) () const<br>_Converts the quaternion to a vector form for use in numerical integration._  |
|  [**const**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) [**Unitless**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) & | [**get\_scalar\_part**](#function-get_scalar_part) () const<br>_Gets the scalar part of the quaternion._  |
|  [**const**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) [**CartesianVector**](structastrea_1_1astro_1_1CartesianVector.md)&lt; [**Unitless**](classastrea_1_1astro_1_1DirectionCosineMatrix.md), in\_frame &gt; & | [**get\_vector\_part**](#function-get_vector_part) () const<br>_Gets the vector part of the quaternion as a_ [_**CartesianVector**_](structastrea_1_1astro_1_1CartesianVector.md) _._ |
|  [**Quaternion**](classastrea_1_1astro_1_1Quaternion.md)&lt; in\_frame, out\_frame &gt; | [**interpolate**](#function-interpolate) ([**const**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) [**Time**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) & thisTime, [**const**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) [**Time**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) & otherTime, [**const**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) [**Quaternion**](classastrea_1_1astro_1_1Quaternion.md)&lt; in\_frame, out\_frame &gt; & other, [**const**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) [**Time**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) & targetTime) const<br>_Interpolates between this quaternion and another quaternion at a target time using SLERP._  |
|  [**Quaternion**](classastrea_1_1astro_1_1Quaternion.md)&lt; out\_frame, in\_frame &gt; | [**inverse**](#function-inverse) () const<br>_Computes the inverse of the quaternion._  |
|  [**Unitless**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) | [**norm**](#function-norm) () const<br>_Computes the norm of the quaternion._  |
|  [**Unitless**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) | [**norm\_squared**](#function-norm_squared) () const<br>_Computes the square of the magnitude of the quaternion (s^2 + u^2)._  |
|  [**void**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) | [**normalize**](#function-normalize) () <br>_Normalizes the quaternion to ensure it represents a valid rotation._  |
|  [**Quaternion**](classastrea_1_1astro_1_1Quaternion.md)&lt; in\_frame, out\_frame &gt; | [**operator\***](#function-operator) ([**const**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) [**Unitless**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) & scalar) const<br>_Multiplication operator for the_ [_**Quaternion**_](classastrea_1_1astro_1_1Quaternion.md) _class by a scalar unitless quantity._ |
|  [**Quaternion**](classastrea_1_1astro_1_1Quaternion.md)&lt; in\_frame, [**out\_frameu\_**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) &gt; | [**operator\***](#function-operator_1) ([**const**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) [**Quaternion**](classastrea_1_1astro_1_1Quaternion.md)&lt; out\_frame, [**out\_frameu\_**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) &gt; & other) const<br>_Multiplication operator for the_ [_**Quaternion**_](classastrea_1_1astro_1_1Quaternion.md) _class._ |
|  [**Quaternion**](classastrea_1_1astro_1_1Quaternion.md)&lt; in\_frame, out\_frame &gt; & | [**operator\*=**](#function-operator_2) ([**const**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) [**Unitless**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) & scalar) <br>_Multiplication operator for the_ [_**Quaternion**_](classastrea_1_1astro_1_1Quaternion.md) _class by a scalar unitless quantity._ |
|  [**Quaternion**](classastrea_1_1astro_1_1Quaternion.md)&lt; in\_frame, out\_frame &gt; | [**operator+**](#function-operator_3) ([**const**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) [**Quaternion**](classastrea_1_1astro_1_1Quaternion.md)&lt; in\_frame, out\_frame &gt; & other) const<br>_Addition operator for the_ [_**Quaternion**_](classastrea_1_1astro_1_1Quaternion.md) _class._ |
|  [**Quaternion**](classastrea_1_1astro_1_1Quaternion.md)&lt; in\_frame, out\_frame &gt; & | [**operator+=**](#function-operator_4) ([**const**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) [**Quaternion**](classastrea_1_1astro_1_1Quaternion.md)&lt; in\_frame, out\_frame &gt; & other) <br>_In-place addition operator for the_ [_**Quaternion**_](classastrea_1_1astro_1_1Quaternion.md) _class._ |
|  [**Quaternion**](classastrea_1_1astro_1_1Quaternion.md)&lt; in\_frame, out\_frame &gt; | [**operator-**](#function-operator-) () const<br>_Unary negation operator for the_ [_**Quaternion**_](classastrea_1_1astro_1_1Quaternion.md) _class._ |
|  [**Quaternion**](classastrea_1_1astro_1_1Quaternion.md)&lt; in\_frame, out\_frame &gt; | [**operator-**](#function-operator-_1) ([**const**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) [**Quaternion**](classastrea_1_1astro_1_1Quaternion.md)&lt; in\_frame, out\_frame &gt; & other) const<br>_Subtraction operator for the_ [_**Quaternion**_](classastrea_1_1astro_1_1Quaternion.md) _class._ |
|  [**Quaternion**](classastrea_1_1astro_1_1Quaternion.md)&lt; in\_frame, out\_frame &gt; & | [**operator-=**](#function-operator-_2) ([**const**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) [**Quaternion**](classastrea_1_1astro_1_1Quaternion.md)&lt; in\_frame, out\_frame &gt; & other) <br>_In-place subtraction operator for the_ [_**Quaternion**_](classastrea_1_1astro_1_1Quaternion.md) _class._ |
|  [**Quaternion**](classastrea_1_1astro_1_1Quaternion.md)&lt; in\_frame, out\_frame &gt; | [**operator/**](#function-operator_5) ([**const**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) [**Unitless**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) & scalar) const<br>_Division operator for the_ [_**Quaternion**_](classastrea_1_1astro_1_1Quaternion.md) _class by a scalar unitless quantity._ |
|  [**QuaternionPartial**](classastrea_1_1astro_1_1QuaternionPartial.md)&lt; in\_frame, out\_frame &gt; | [**operator/**](#function-operator_6) ([**const**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) [**Time**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) & dt) const<br>_Division operator for the_ [_**Quaternion**_](classastrea_1_1astro_1_1Quaternion.md) _class by a scalar time quantity, resulting in a_[_**QuaternionPartial**_](classastrea_1_1astro_1_1QuaternionPartial.md) _._ |
|  [**Quaternion**](classastrea_1_1astro_1_1Quaternion.md)&lt; in\_frame, out\_frame &gt; & | [**operator/=**](#function-operator_7) ([**const**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) [**Unitless**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) & scalar) <br>_Division operator for the_ [_**Quaternion**_](classastrea_1_1astro_1_1Quaternion.md) _class by a scalar unitless quantity._ |
|  [**Quaternion**](classastrea_1_1astro_1_1Quaternion.md) & | [**operator=**](#function-operator_8) ([**const**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) [**Quaternion**](classastrea_1_1astro_1_1Quaternion.md) & other) = default<br>_Default copy assignment operator._  |
|  [**Quaternion**](classastrea_1_1astro_1_1Quaternion.md) & | [**operator=**](#function-operator_9) ([**Quaternion**](classastrea_1_1astro_1_1Quaternion.md) && other) = default<br>_Default move assignment operator._  |
|  [**bool**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) | [**operator==**](#function-operator_10) ([**const**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) [**Quaternion**](classastrea_1_1astro_1_1Quaternion.md) & other) const<br>_Equality operator for_ [_**Quaternion**_](classastrea_1_1astro_1_1Quaternion.md) _._ |
|  [**CartesianVector**](structastrea_1_1astro_1_1CartesianVector.md)&lt; [**Value\_T**](classastrea_1_1astro_1_1DirectionCosineMatrix.md), out\_frame &gt; | [**rotate\_vector**](#function-rotate_vector) ([**const**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) [**CartesianVector**](structastrea_1_1astro_1_1CartesianVector.md)&lt; [**Value\_T**](classastrea_1_1astro_1_1DirectionCosineMatrix.md), in\_frame &gt; & vec) const<br>_Rotates a vector from the input frame to the output frame using this quaternion._  |
|  [**DirectionCosineMatrix**](classastrea_1_1astro_1_1DirectionCosineMatrix.md)&lt; in\_frame, out\_frame &gt; | [**to\_dcm**](#function-to_dcm) () const<br>_Get the scalar part of the quaternion._  |
|  [**EulerAngles**](classastrea_1_1astro_1_1EulerAngles.md)&lt; sequence, [**rotation\_type**](classastrea_1_1astro_1_1DirectionCosineMatrix.md), in\_frame, out\_frame &gt; | [**to\_euler\_angles**](#function-to_euler_angles) () const<br>_Convert the quaternion to an Euler angle sequence._  |




























## Detailed Description




**Template parameters:**


* `in_frame` The input frame type (e.g., ECI, ECEF). 
* `out_frame` The output frame type (e.g., ECI, ECEF).



**Note:**

: These are not real quaternions and are not setup to behave properly as quaternions might. These Quaternions are specifically meant to represent frame rotations and are not meant to be used for general quaternion math. They are automatically normalized on construction to avoid tracking the magnitude and to avoid expensive sqrt as much as possible. 





    
## Public Static Attributes Documentation




### variable in\_frame 

```C++
constexpr auto astrea::astro::Quaternion< _in_frame_, _out_frame_ >::in_frame;
```




<hr>



### variable out\_frame 

```C++
constexpr auto astrea::astro::Quaternion< _in_frame_, _out_frame_ >::out_frame;
```




<hr>
## Public Functions Documentation




### function Quaternion [1/9]

_Default constructor for the_ [_**Quaternion**_](classastrea_1_1astro_1_1Quaternion.md) _class. Initializes to the identity quaternion (no rotation)._
```C++
inline astrea::astro::Quaternion::Quaternion () 
```




<hr>



### function Quaternion [2/9]

_Constructor for the_ [_**Quaternion**_](classastrea_1_1astro_1_1Quaternion.md) _class from a_[_**CartesianVector**_](structastrea_1_1astro_1_1CartesianVector.md) _._
```C++
inline astrea::astro::Quaternion::Quaternion (
    const  CartesianVector < Unitless , in_frame > & vec
) 
```





**Parameters:**


* `vec` The [**CartesianVector**](structastrea_1_1astro_1_1CartesianVector.md) representing the vector part of the quaternion. The scalar part is set to 0. 




        

<hr>



### function Quaternion [3/9]

_Constructor for the_ [_**Quaternion**_](classastrea_1_1astro_1_1Quaternion.md) _class from a scalar and a_[_**CartesianVector**_](structastrea_1_1astro_1_1CartesianVector.md) _._
```C++
inline astrea::astro::Quaternion::Quaternion (
    const  Unitless & s,
    const  CartesianVector < Unitless , in_frame > & vec
) 
```





**Parameters:**


* `s` The scalar part of the quaternion. 
* `vec` The [**CartesianVector**](structastrea_1_1astro_1_1CartesianVector.md) representing the vector part of the quaternion. 




        

<hr>



### function Quaternion [4/9]

_Constructor for the_ [_**Quaternion**_](classastrea_1_1astro_1_1Quaternion.md) _class from individual components._
```C++
inline astrea::astro::Quaternion::Quaternion (
    const  Unitless & s,
    const  Unitless & x,
    const  Unitless & y,
    const  Unitless & z
) 
```





**Parameters:**


* `s` Scalar part of the quaternion (must be between -1 and 1). 
* `x` X component of the vector part of the quaternion (must be between -1 and 1). 
* `y` Y component of the vector part of the quaternion (must be between -1 and 1). 
* `z` Z component of the vector part of the quaternion (must be between -1 and 1).



**Exception:**


* `std::invalid_argument` if any of the components are outside the range [-1, 1]. 




        

<hr>



### function Quaternion [5/9]

_Default copy constructor._ 
```C++
astrea::astro::Quaternion::Quaternion (
    const  Quaternion & other
) = default
```




<hr>



### function Quaternion [6/9]

_Default move constructor._ 
```C++
astrea::astro::Quaternion::Quaternion (
    Quaternion && other
) = default
```




<hr>



### function Quaternion [7/9]

_Constructor for the_ [_**Quaternion**_](classastrea_1_1astro_1_1Quaternion.md) _class from a Direction Cosine Matrix (DCM)._
```C++
inline astrea::astro::Quaternion::Quaternion (
    const  DirectionCosineMatrix < in_frame, out_frame > & dcm
) 
```





**Parameters:**


* `dcm` The direction cosine matrix to convert to a quaternion.



**Note:**

Uses Shepperd's method for numerical stability. Algorithm branches based on which element provides the most numerically stable computation.


Shepperd, S.W. "Quaternion from rotation matrix." Journal of Guidance and Control, Vol. 1, No. 3, May-June 1978, pp. 223-224. Wertz, J.R. (ed.), "Spacecraft Attitude Determination and Control," Kluwer Academic Publishers, 1978, pp. 414-416. 


        

<hr>



### function Quaternion [8/9]

_Constructor for the_ [_**Quaternion**_](classastrea_1_1astro_1_1Quaternion.md) _class from an Euler angle sequence._
```C++
template<RotationSequence sequence, RotationType rotation_type>
inline astrea::astro::Quaternion::Quaternion (
    const  EulerAngles < sequence, rotation_type , in_frame, out_frame > & angleSequence
) 
```





**Template parameters:**


* `sequence` The rotation sequence of the Euler angles (e.g., XYZ, ZYX). 
* `rotationType` The type of rotation (extrinsic or intrinsic). 



**Parameters:**


* `angleSequence` The Euler angle sequence to convert to a quaternion.



**Note:**

This constructor converts the Euler angles to a DCM and { uses the DCM constructor to create the quaternion. 





        

<hr>



### function Quaternion [9/9]

_Constructor for the_ [_**Quaternion**_](classastrea_1_1astro_1_1Quaternion.md) _class from an angle and rotation axis._
```C++
inline astrea::astro::Quaternion::Quaternion (
    const  Angle & angle,
    const  CartesianVector < Unitless , in_frame > & axis
) 
```





**Parameters:**


* `angle` The angle of rotation. 
* `axis` The axis of rotation represented as a [**CartesianVector**](structastrea_1_1astro_1_1CartesianVector.md). Must be a unit vector.



**Note:**

This constructor creates a quaternion representing a rotation of "angle" around the "axis" using the formula: q = [cos(angle/2), axis \* sin(angle/2)] 





        

<hr>



### function conjugate 

_Computes the conjugate of the quaternion._ 
```C++
inline Quaternion < out_frame, in_frame > astrea::astro::Quaternion::conjugate () const
```





**Returns:**

The conjugate of the quaternion. 





        

<hr>



### function dot 

_Computes the dot product between this quaternion and another quaternion._ 
```C++
inline Unitless astrea::astro::Quaternion::dot (
    const  Quaternion < in_frame, out_frame > & other
) const
```





**Parameters:**


* `other` The other quaternion to compute the dot product with. 



**Returns:**

Unitless The dot product of this quaternion and the other quaternion, computed as s1\*s2 + u1 ⋅ u2. 





        

<hr>



### function force\_to\_vector 

_Converts the quaternion to a vector form for use in numerical integration._ 
```C++
inline std::vector< Unitless > astrea::astro::Quaternion::force_to_vector () const
```





**Returns:**

A std::vector of Unitless quantities representing the components of the quaternion, in the order [s, u\_x, u\_y, u\_z]. 





        

<hr>



### function get\_scalar\_part 

_Gets the scalar part of the quaternion._ 
```C++
inline const  Unitless & astrea::astro::Quaternion::get_scalar_part () const
```





**Returns:**

const Unitless& The scalar part of the quaternion. 





        

<hr>



### function get\_vector\_part 

_Gets the vector part of the quaternion as a_ [_**CartesianVector**_](structastrea_1_1astro_1_1CartesianVector.md) _._
```C++
inline const  CartesianVector < Unitless , in_frame > & astrea::astro::Quaternion::get_vector_part () const
```





**Returns:**

const [**CartesianVector&lt;Unitless, in\_frame&gt;**](structastrea_1_1astro_1_1CartesianVector.md)& The vector part of the quaternion. 





        

<hr>



### function interpolate 

_Interpolates between this quaternion and another quaternion at a target time using SLERP._ 
```C++
inline Quaternion < in_frame, out_frame > astrea::astro::Quaternion::interpolate (
    const  Time & thisTime,
    const  Time & otherTime,
    const  Quaternion < in_frame, out_frame > & other,
    const  Time & targetTime
) const
```





**Parameters:**


* `thisTime` The time corresponding to this quaternion. 
* `otherTime` The time corresponding to the other quaternion. 
* `other` The other quaternion to interpolate with. 
* `targetTime` The time at which to interpolate the quaternion. 



**Returns:**

Quaternion&lt;in\_frame, out\_frame&gt; A new [**Quaternion**](classastrea_1_1astro_1_1Quaternion.md) that is the interpolation of this quaternion and the other at the target time.




**Note:**

: [https://www.euclideanspace.com/maths/algebra/realNormedAlgebra/quaternions/slerp/index.htm](https://www.euclideanspace.com/maths/algebra/realNormedAlgebra/quaternions/slerp/index.htm) 





        

<hr>



### function inverse 

_Computes the inverse of the quaternion._ 
```C++
inline Quaternion < out_frame, in_frame > astrea::astro::Quaternion::inverse () const
```





**Returns:**

The inverse of the quaternion.




**Exception:**


* `std::runtime_error` if the norm of the quaternion is zero (cannot compute inverse of a zero quaternion). 




        

<hr>



### function norm 

_Computes the norm of the quaternion._ 
```C++
inline Unitless astrea::astro::Quaternion::norm () const
```





**Returns:**

The norm of the quaternion as a unitless quantity. 





        

<hr>



### function norm\_squared 

_Computes the square of the magnitude of the quaternion (s^2 + u^2)._ 
```C++
inline Unitless astrea::astro::Quaternion::norm_squared () const
```





**Returns:**

The square of the magnitude of the quaternion as a unitless quantity. 





        

<hr>



### function normalize 

_Normalizes the quaternion to ensure it represents a valid rotation._ 
```C++
inline void astrea::astro::Quaternion::normalize () 
```




<hr>



### function operator\* 

_Multiplication operator for the_ [_**Quaternion**_](classastrea_1_1astro_1_1Quaternion.md) _class by a scalar unitless quantity._
```C++
inline Quaternion < in_frame, out_frame > astrea::astro::Quaternion::operator* (
    const  Unitless & scalar
) const
```





**Parameters:**


* `scalar` The scalar unitless quantity to multiply the quaternion by. 



**Returns:**

The original quaternion. NO scaling is applied to the quaternion. 





        

<hr>



### function operator\* 

_Multiplication operator for the_ [_**Quaternion**_](classastrea_1_1astro_1_1Quaternion.md) _class._
```C++
template<IsFrame auto out_frameu_>
inline Quaternion < in_frame, out_frameu_ > astrea::astro::Quaternion::operator* (
    const  Quaternion < out_frame, out_frameu_ > & other
) const
```





**Template parameters:**


* `out_frameu_` The output frame type of the other quaternion. 



**Parameters:**


* `other` The quaternion to multiply with this quaternion. 



**Returns:**

A new quaternion that is the product of this quaternion and the other quaternion. 





        

<hr>



### function operator\*= 

_Multiplication operator for the_ [_**Quaternion**_](classastrea_1_1astro_1_1Quaternion.md) _class by a scalar unitless quantity._
```C++
inline Quaternion < in_frame, out_frame > & astrea::astro::Quaternion::operator*= (
    const  Unitless & scalar
) 
```





**Parameters:**


* `scalar` The scalar unitless quantity to multiply the quaternion by. 



**Returns:**

The original quaternion. NO scaling is applied to the quaternion. 





        

<hr>



### function operator+ 

_Addition operator for the_ [_**Quaternion**_](classastrea_1_1astro_1_1Quaternion.md) _class._
```C++
inline Quaternion < in_frame, out_frame > astrea::astro::Quaternion::operator+ (
    const  Quaternion < in_frame, out_frame > & other
) const
```





**Parameters:**


* `other` The quaternion to add to this quaternion. 



**Returns:**

A new quaternion that is the sum of this quaternion and the other quaternion. 





        

<hr>



### function operator+= 

_In-place addition operator for the_ [_**Quaternion**_](classastrea_1_1astro_1_1Quaternion.md) _class._
```C++
inline Quaternion < in_frame, out_frame > & astrea::astro::Quaternion::operator+= (
    const  Quaternion < in_frame, out_frame > & other
) 
```





**Parameters:**


* `other` The quaternion to add to this quaternion. 



**Returns:**

[**Quaternion**](classastrea_1_1astro_1_1Quaternion.md)& A reference to this quaternion after addition. 





        

<hr>



### function operator- 

_Unary negation operator for the_ [_**Quaternion**_](classastrea_1_1astro_1_1Quaternion.md) _class._
```C++
inline Quaternion < in_frame, out_frame > astrea::astro::Quaternion::operator- () const
```





**Returns:**

A new quaternion that is the negation of this quaternion. 





        

<hr>



### function operator- 

_Subtraction operator for the_ [_**Quaternion**_](classastrea_1_1astro_1_1Quaternion.md) _class._
```C++
inline Quaternion < in_frame, out_frame > astrea::astro::Quaternion::operator- (
    const  Quaternion < in_frame, out_frame > & other
) const
```





**Parameters:**


* `other` The quaternion to subtract from this quaternion. 



**Returns:**

A new quaternion that is the difference between this quaternion and the other quaternion. 





        

<hr>



### function operator-= 

_In-place subtraction operator for the_ [_**Quaternion**_](classastrea_1_1astro_1_1Quaternion.md) _class._
```C++
inline Quaternion < in_frame, out_frame > & astrea::astro::Quaternion::operator-= (
    const  Quaternion < in_frame, out_frame > & other
) 
```





**Parameters:**


* `other` The quaternion to subtract from this quaternion. 



**Returns:**

[**Quaternion**](classastrea_1_1astro_1_1Quaternion.md)& A reference to this quaternion after subtraction. 





        

<hr>



### function operator/ 

_Division operator for the_ [_**Quaternion**_](classastrea_1_1astro_1_1Quaternion.md) _class by a scalar unitless quantity._
```C++
inline Quaternion < in_frame, out_frame > astrea::astro::Quaternion::operator/ (
    const  Unitless & scalar
) const
```





**Parameters:**


* `scalar` The scalar unitless quantity to divide the quaternion by. 



**Returns:**

The original quaternion. NO scaling is applied to the quaternion. 





        

<hr>



### function operator/ 

_Division operator for the_ [_**Quaternion**_](classastrea_1_1astro_1_1Quaternion.md) _class by a scalar time quantity, resulting in a_[_**QuaternionPartial**_](classastrea_1_1astro_1_1QuaternionPartial.md) _._
```C++
inline QuaternionPartial < in_frame, out_frame > astrea::astro::Quaternion::operator/ (
    const  Time & dt
) const
```





**Parameters:**


* `dt` The time quantity to divide the quaternion by, representing the rate of change of the quaternion. 



**Returns:**

A new [**QuaternionPartial**](classastrea_1_1astro_1_1QuaternionPartial.md) that represents the rate of change of the quaternion with respect to time. 





        

<hr>



### function operator/= 

_Division operator for the_ [_**Quaternion**_](classastrea_1_1astro_1_1Quaternion.md) _class by a scalar unitless quantity._
```C++
inline Quaternion < in_frame, out_frame > & astrea::astro::Quaternion::operator/= (
    const  Unitless & scalar
) 
```





**Parameters:**


* `scalar` The scalar unitless quantity to divide the quaternion by. 



**Returns:**

The original quaternion. NO scaling is applied to the quaternion. 





        

<hr>



### function operator= 

_Default copy assignment operator._ 
```C++
Quaternion & astrea::astro::Quaternion::operator= (
    const  Quaternion & other
) = default
```




<hr>



### function operator= 

_Default move assignment operator._ 
```C++
Quaternion & astrea::astro::Quaternion::operator= (
    Quaternion && other
) = default
```




<hr>



### function operator== 

_Equality operator for_ [_**Quaternion**_](classastrea_1_1astro_1_1Quaternion.md) _._
```C++
inline bool astrea::astro::Quaternion::operator== (
    const  Quaternion & other
) const
```





**Parameters:**


* `other` The other [**Quaternion**](classastrea_1_1astro_1_1Quaternion.md) to compare with. 



**Returns:**

true If the two quaternions are equal. 




**Returns:**

false If the two quaternions are not equal. 





        

<hr>



### function rotate\_vector 

_Rotates a vector from the input frame to the output frame using this quaternion._ 
```C++
template<typename  Value_T>
inline CartesianVector < Value_T , out_frame > astrea::astro::Quaternion::rotate_vector (
    const  CartesianVector < Value_T , in_frame > & vec
) const
```





**Template parameters:**


* `Value_T` The type of the vector components (e.g., double, quantity). 



**Parameters:**


* `vec` The vector to rotate, expressed in the input frame. 



**Returns:**

A new vector that is the result of rotating the input vector by this quaternion, expressed in the output frame. 





        

<hr>



### function to\_dcm 

_Get the scalar part of the quaternion._ 
```C++
inline DirectionCosineMatrix < in_frame, out_frame > astrea::astro::Quaternion::to_dcm () const
```





**Returns:**

Unitless The scalar part of the quaternion. 





        

<hr>



### function to\_euler\_angles 

_Convert the quaternion to an Euler angle sequence._ 
```C++
template<RotationSequence sequence, RotationType rotation_type>
inline EulerAngles < sequence, rotation_type , in_frame, out_frame > astrea::astro::Quaternion::to_euler_angles () const
```





**Template parameters:**


* `sequence` The rotation sequence of the Euler angles (e.g., XYZ, ZYX). 
* `rotationType` The type of rotation (extrinsic or intrinsic). 



**Returns:**

EulerAngles&lt;sequence, rotation\_type, in\_frame, out\_frame&gt; The resulting Euler angle sequence.




**Note:**

This method converts the quaternion to a DCM and then extracts the Euler angles based on the specified sequence and rotation type. It uses this method: [https://pmc.ncbi.nlm.nih.gov/articles/PMC9648712/](https://pmc.ncbi.nlm.nih.gov/articles/PMC9648712/) 





        

<hr>

------------------------------
The documentation for this class was generated from the following file `astrea/astro/astro/state/attitude/Quaternion.hpp`

