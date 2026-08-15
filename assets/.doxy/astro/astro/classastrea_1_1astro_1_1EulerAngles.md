

# Class astrea::astro::EulerAngles

**template &lt;[**RotationSequence**](namespaceastrea_1_1astro.md#enum-rotationsequence) sequence, [**RotationType**](namespaceastrea_1_1astro.md#enum-rotationtype) rotation\_type, IsFrame auto \_in\_frame\_, IsFrame auto \_out\_frame\_&gt;**



[**ClassList**](annotated.md) **>** [**astrea**](namespaceastrea.md) **>** [**astro**](namespaceastrea_1_1astro.md) **>** [**EulerAngles**](classastrea_1_1astro_1_1EulerAngles.md)



_Class representing a sequence of angles (either Euler or Tait-Bryan) for attitude transformations between frames._ [More...](#detailed-description)

* `#include <EulerAngles.hpp>`























## Public Static Attributes

| Type | Name |
| ---: | :--- |
|  constexpr auto | [**in\_frame**](#variable-in_frame)   = `\_in\_frame\_`<br> |
|  constexpr auto | [**out\_frame**](#variable-out_frame)   = `\_out\_frame\_`<br> |














## Public Functions

| Type | Name |
| ---: | :--- |
|   | [**EulerAngles**](#function-eulerangles-110) () = default<br>_Default constructor for the_ [_**EulerAngles**_](classastrea_1_1astro_1_1EulerAngles.md) _class. Initializes all angles to zero._ |
|   | [**EulerAngles**](#function-eulerangles-210) (const Angle & angle1, const Angle & angle2, const Angle & angle3) <br>_Constructor for the_ [_**EulerAngles**_](classastrea_1_1astro_1_1EulerAngles.md) _class from three angles._ |
|   | [**EulerAngles**](#function-eulerangles-310) (const [**CartesianVector**](structastrea_1_1astro_1_1CartesianVector.md)&lt; Angle, \_in\_frame\_ &gt; & angles) <br>_Constructor for the_ [_**EulerAngles**_](classastrea_1_1astro_1_1EulerAngles.md) _class from a_[_**CartesianVector**_](structastrea_1_1astro_1_1CartesianVector.md) _of angles._ |
|   | [**EulerAngles**](#function-eulerangles-410) (const [**EulerAngles**](classastrea_1_1astro_1_1EulerAngles.md) & other) = default<br> |
|   | [**EulerAngles**](#function-eulerangles-510) ([**EulerAngles**](classastrea_1_1astro_1_1EulerAngles.md) && other) = default<br> |
|   | [**EulerAngles**](#function-eulerangles-610) (const [**EulerAngles**](classastrea_1_1astro_1_1EulerAngles.md)&lt; sequence\_u, rotation\_type\_u, \_in\_frame\_u\_, \_out\_frame\_u\_ &gt; & other) <br> |
|   | [**EulerAngles**](#function-eulerangles-710) ([**EulerAngles**](classastrea_1_1astro_1_1EulerAngles.md)&lt; sequence\_u, rotation\_type\_u, \_in\_frame\_u\_, \_out\_frame\_u\_ &gt; && other) <br> |
|   | [**EulerAngles**](#function-eulerangles-810) (const [**EulerAngles**](classastrea_1_1astro_1_1EulerAngles.md)&lt; sequence\_u, rotation\_type\_u, \_in\_frame\_, \_out\_frame\_ &gt; & other) <br>_Explicit copy constructor for incompatible sequences (different specific sequence, different rotation type, or different frames). Converts through the DCM to ensure correct transformations between frames and proper handling of singularities._  |
|   | [**EulerAngles**](#function-eulerangles-910) (const [**EulerAngles**](classastrea_1_1astro_1_1EulerAngles.md)&lt; sequence\_u, rotation\_type\_u, \_in\_frame\_u\_, \_out\_frame\_u\_ &gt; & other) = delete<br> |
|   | [**EulerAngles**](#function-eulerangles-1010) ([**EulerAngles**](classastrea_1_1astro_1_1EulerAngles.md)&lt; sequence\_u, rotation\_type\_u, \_in\_frame\_u\_, \_out\_frame\_u\_ &gt; && other) = delete<br> |
|  auto | [**cross**](#function-cross-12) (const [**EulerAngles**](classastrea_1_1astro_1_1EulerAngles.md)&lt; sequence, rotation\_type, \_in\_frame\_, \_out\_frame\_ &gt; & other) const<br>_Cross product of this angle vector with another_ [_**EulerAngles**_](classastrea_1_1astro_1_1EulerAngles.md) _._ |
|  auto | [**cross**](#function-cross-22) (const [**CartesianVector**](structastrea_1_1astro_1_1CartesianVector.md)&lt; Value\_U, \_in\_frame\_ &gt; & other) const<br>_Cross product of this angle vector with a generic_ [_**CartesianVector**_](structastrea_1_1astro_1_1CartesianVector.md) _._ |
|  auto | [**dot**](#function-dot-12) (const [**EulerAngles**](classastrea_1_1astro_1_1EulerAngles.md)&lt; sequence, rotation\_type, \_in\_frame\_, \_out\_frame\_ &gt; & other) const<br>_Dot product of this angle vector with another_ [_**EulerAngles**_](classastrea_1_1astro_1_1EulerAngles.md) _._ |
|  auto | [**dot**](#function-dot-22) (const [**CartesianVector**](structastrea_1_1astro_1_1CartesianVector.md)&lt; Value\_U, \_in\_frame\_ &gt; & other) const<br>_Dot product of this angle vector with a generic_ [_**CartesianVector**_](structastrea_1_1astro_1_1CartesianVector.md) _._ |
|  std::vector&lt; double &gt; | [**force\_to\_double\_vector**](#function-force_to_double_vector) () const<br>_Converts the angle sequence to a vector form for use in numerical integration._  |
|  [**CartesianVector**](structastrea_1_1astro_1_1CartesianVector.md)&lt; Angle, \_in\_frame\_ &gt; & | [**get\_angles**](#function-get_angles-12) () <br>_Get access to the underlying_ [_**CartesianVector**_](structastrea_1_1astro_1_1CartesianVector.md) _._ |
|  const [**CartesianVector**](structastrea_1_1astro_1_1CartesianVector.md)&lt; Angle, \_in\_frame\_ &gt; & | [**get\_angles**](#function-get_angles-22) () const<br>_Get const access to the underlying_ [_**CartesianVector**_](structastrea_1_1astro_1_1CartesianVector.md) _._ |
|  [**EulerAngles**](classastrea_1_1astro_1_1EulerAngles.md)&lt; [**get\_reverse\_sequence**](namespaceastrea_1_1astro.md#function-get_reverse_sequence)(sequence), rotation\_type, \_out\_frame\_, \_in\_frame\_ &gt; | [**get\_inverse\_sequence**](#function-get_inverse_sequence) () const<br>_Constructs the inverse sequence with the same rotation type._  |
|  [**EulerAngles**](classastrea_1_1astro_1_1EulerAngles.md)&lt; sequence, rotation\_type, \_in\_frame\_, \_out\_frame\_ &gt; | [**interpolate**](#function-interpolate) (const Time & thisTime, const Time & otherTime, const [**EulerAngles**](classastrea_1_1astro_1_1EulerAngles.md)&lt; sequence, rotation\_type, \_in\_frame\_, \_out\_frame\_ &gt; & other, const Time & targetTime) const<br>_Interpolates between this angle sequence and another angle sequence at a target time._  |
|  Angle | [**norm**](#function-norm) () const<br>_Norm of the angle vector._  |
|  [**EulerAngles**](classastrea_1_1astro_1_1EulerAngles.md)&lt; sequence, rotation\_type, \_in\_frame\_, \_out\_frame\_ &gt; | [**operator\***](#function-operator) (const Unitless & scalar) const<br>_Scalar multiplication operator for_ [_**EulerAngles**_](classastrea_1_1astro_1_1EulerAngles.md) _._ |
|  [**EulerAngles**](classastrea_1_1astro_1_1EulerAngles.md)&lt; sequence, rotation\_type, \_in\_frame\_, \_out\_frame\_ &gt; & | [**operator\*=**](#function-operator_1) (const Unitless & scalar) <br>_Scalar multiplication assignment operator for_ [_**EulerAngles**_](classastrea_1_1astro_1_1EulerAngles.md) _._ |
|  [**EulerAngles**](classastrea_1_1astro_1_1EulerAngles.md)&lt; sequence, rotation\_type, \_in\_frame\_, \_out\_frame\_ &gt; | [**operator+**](#function-operator_2) (const [**EulerAngles**](classastrea_1_1astro_1_1EulerAngles.md)&lt; sequence, rotation\_type, \_in\_frame\_, \_out\_frame\_ &gt; & other) const<br>_Addition operator for_ [_**CartesianVector**_](structastrea_1_1astro_1_1CartesianVector.md) _._ |
|  [**EulerAngles**](classastrea_1_1astro_1_1EulerAngles.md)&lt; sequence, rotation\_type, \_in\_frame\_, \_out\_frame\_ &gt; & | [**operator+=**](#function-operator_3) (const [**EulerAngles**](classastrea_1_1astro_1_1EulerAngles.md)&lt; sequence, rotation\_type, \_in\_frame\_, \_out\_frame\_ &gt; & other) <br>_Addition assignment operator for_ [_**EulerAngles**_](classastrea_1_1astro_1_1EulerAngles.md) _._ |
|  [**EulerAngles**](classastrea_1_1astro_1_1EulerAngles.md)&lt; sequence, rotation\_type, \_in\_frame\_, \_out\_frame\_ &gt; | [**operator-**](#function-operator-) (const [**EulerAngles**](classastrea_1_1astro_1_1EulerAngles.md)&lt; sequence, rotation\_type, \_in\_frame\_, \_out\_frame\_ &gt; & other) const<br>_Subtraction operator for_ [_**EulerAngles**_](classastrea_1_1astro_1_1EulerAngles.md) _._ |
|  [**EulerAngles**](classastrea_1_1astro_1_1EulerAngles.md)&lt; sequence, rotation\_type, \_in\_frame\_, \_out\_frame\_ &gt; | [**operator-**](#function-operator-_1) () const<br>_Negation operator for_ [_**EulerAngles**_](classastrea_1_1astro_1_1EulerAngles.md) _._ |
|  [**EulerAngles**](classastrea_1_1astro_1_1EulerAngles.md)&lt; sequence, rotation\_type, \_in\_frame\_, \_out\_frame\_ &gt; & | [**operator-=**](#function-operator-_2) (const [**EulerAngles**](classastrea_1_1astro_1_1EulerAngles.md)&lt; sequence, rotation\_type, \_in\_frame\_, \_out\_frame\_ &gt; & other) <br>_Subtraction assignment operator for_ [_**EulerAngles**_](classastrea_1_1astro_1_1EulerAngles.md) _._ |
|  [**AngularVelocities**](classastrea_1_1astro_1_1AngularVelocities.md)&lt; \_in\_frame\_, \_out\_frame\_ &gt; | [**operator/**](#function-operator_4) (const Time & time) const<br>_Scalar division operator for_ [_**EulerAngles**_](classastrea_1_1astro_1_1EulerAngles.md) _by a Time quantity, resulting in an EulerAnglesRate._ |
|  [**EulerAngles**](classastrea_1_1astro_1_1EulerAngles.md)&lt; sequence, rotation\_type, \_in\_frame\_, \_out\_frame\_ &gt; | [**operator/**](#function-operator_5) (const Unitless & scalar) const<br>_Scalar division operator for_ [_**EulerAngles**_](classastrea_1_1astro_1_1EulerAngles.md) _._ |
|  [**EulerAngles**](classastrea_1_1astro_1_1EulerAngles.md)&lt; sequence, rotation\_type, \_in\_frame\_, \_out\_frame\_ &gt; & | [**operator/=**](#function-operator_6) (const Unitless & scalar) <br>_Scalar division assignment operator for_ [_**EulerAngles**_](classastrea_1_1astro_1_1EulerAngles.md) _._ |
|  [**EulerAngles**](classastrea_1_1astro_1_1EulerAngles.md) & | [**operator=**](#function-operator_7) (const [**EulerAngles**](classastrea_1_1astro_1_1EulerAngles.md) & other) = default<br> |
|  [**EulerAngles**](classastrea_1_1astro_1_1EulerAngles.md) & | [**operator=**](#function-operator_8) ([**EulerAngles**](classastrea_1_1astro_1_1EulerAngles.md) && other) = default<br> |
|  [**EulerAngles**](classastrea_1_1astro_1_1EulerAngles.md) & | [**operator=**](#function-operator_9) (const [**EulerAngles**](classastrea_1_1astro_1_1EulerAngles.md)&lt; sequence\_u, rotation\_type\_u, \_in\_frame\_u\_, \_out\_frame\_u\_ &gt; & other) <br> |
|  [**EulerAngles**](classastrea_1_1astro_1_1EulerAngles.md) & | [**operator=**](#function-operator_10) ([**EulerAngles**](classastrea_1_1astro_1_1EulerAngles.md)&lt; sequence\_u, rotation\_type\_u, \_in\_frame\_u\_, \_out\_frame\_u\_ &gt; && other) <br> |
|  [**EulerAngles**](classastrea_1_1astro_1_1EulerAngles.md)&lt; sequence, rotation\_type, \_in\_frame\_, \_out\_frame\_ &gt; & | [**operator=**](#function-operator_11) (const [**EulerAngles**](classastrea_1_1astro_1_1EulerAngles.md)&lt; sequence\_u, rotation\_type\_u, \_in\_frame\_u\_, \_out\_frame\_u\_ &gt; & other) = delete<br> |
|  [**EulerAngles**](classastrea_1_1astro_1_1EulerAngles.md)&lt; sequence, rotation\_type, \_in\_frame\_, \_out\_frame\_ &gt; & | [**operator=**](#function-operator_12) ([**EulerAngles**](classastrea_1_1astro_1_1EulerAngles.md)&lt; sequence\_u, rotation\_type\_u, \_in\_frame\_u\_, \_out\_frame\_u\_ &gt; && other) = delete<br> |
|  bool | [**operator==**](#function-operator_13) (const [**EulerAngles**](classastrea_1_1astro_1_1EulerAngles.md)&lt; sequence, rotation\_type, \_in\_frame\_, \_out\_frame\_ &gt; & other) const<br>_Equality operator for_ [_**CartesianVector**_](structastrea_1_1astro_1_1CartesianVector.md) _._ |
|  bool | [**operator==**](#function-operator_14) (const [**EulerAngles**](classastrea_1_1astro_1_1EulerAngles.md)&lt; sequence\_u, rotation\_type\_u, \_in\_frame\_u\_, \_out\_frame\_u\_ &gt; & other) const<br> |
|  bool | [**operator==**](#function-operator_15) (const [**EulerAngles**](classastrea_1_1astro_1_1EulerAngles.md)&lt; sequence\_u, rotation\_type\_u, \_in\_frame\_u\_, \_out\_frame\_u\_ &gt; & other) const<br>_Inequality operator for_ [_**CartesianVector**_](structastrea_1_1astro_1_1CartesianVector.md) _in a different frame. Always false._ |
|  Angle & | [**operator[]**](#function-operator_16) (std::size\_t index) <br>_Array access operator for accessing individual angle components._  |
|  const Angle & | [**operator[]**](#function-operator_17) (std::size\_t index) const<br>_Const array access operator for accessing individual angle components._  |
|  [**DirectionCosineMatrix**](classastrea_1_1astro_1_1DirectionCosineMatrix.md)&lt; \_in\_frame\_, \_out\_frame\_ &gt; | [**to\_dcm**](#function-to_dcm) () const<br>_Converts the angle sequence to a direction cosine matrix (DCM) for transforming vectors between frames._  |
|  [**EulerAngles**](classastrea_1_1astro_1_1EulerAngles.md)&lt; [**get\_reverse\_sequence**](namespaceastrea_1_1astro.md#function-get_reverse_sequence)(sequence), rotation\_u, \_in\_frame\_, \_out\_frame\_ &gt; | [**to\_rotation\_type**](#function-to_rotation_type-12) () const<br>_Converts the angle sequence to the opposite rotation type (intrinsic to extrinsic or vice versa) by reversing the order of the angles._  |
|  [**EulerAngles**](classastrea_1_1astro_1_1EulerAngles.md)&lt; sequence, rotation\_type, \_in\_frame\_, \_out\_frame\_ &gt; | [**to\_rotation\_type**](#function-to_rotation_type-22) () const<br>_Converts the angle sequence to the same rotation type (intrinsic to intrinsic or extrinsic to extrinsic). This is a no-op but allows for explicit conversions between different sequences of the same rotation type._  |




























## Detailed Description




**Template parameters:**


* `sequence` The specific sequence of rotations (e.g., RotationSequence::ZXZ). 
* `type` Whether the sequence is intrinsic or extrinsic. 
* `_in_frame_` The input frame type (e.g., ECI, ECEF). 
* `_out_frame_` The output frame type (e.g., ECI, ECEF).



**Note:**

: welcome to templating hell 





    
## Public Static Attributes Documentation




### variable in\_frame 

```C++
constexpr auto astrea::astro::EulerAngles< sequence, rotation_type, _in_frame_, _out_frame_ >::in_frame;
```




<hr>



### variable out\_frame 

```C++
constexpr auto astrea::astro::EulerAngles< sequence, rotation_type, _in_frame_, _out_frame_ >::out_frame;
```




<hr>
## Public Functions Documentation




### function EulerAngles [1/10]

_Default constructor for the_ [_**EulerAngles**_](classastrea_1_1astro_1_1EulerAngles.md) _class. Initializes all angles to zero._
```C++
astrea::astro::EulerAngles::EulerAngles () = default
```




<hr>



### function EulerAngles [2/10]

_Constructor for the_ [_**EulerAngles**_](classastrea_1_1astro_1_1EulerAngles.md) _class from three angles._
```C++
inline astrea::astro::EulerAngles::EulerAngles (
    const Angle & angle1,
    const Angle & angle2,
    const Angle & angle3
) 
```





**Parameters:**


* `angle1` The first angle in the sequence. 
* `angle2` The second angle in the sequence. 
* `angle3` The third angle in the sequence. 




        

<hr>



### function EulerAngles [3/10]

_Constructor for the_ [_**EulerAngles**_](classastrea_1_1astro_1_1EulerAngles.md) _class from a_[_**CartesianVector**_](structastrea_1_1astro_1_1CartesianVector.md) _of angles._
```C++
inline astrea::astro::EulerAngles::EulerAngles (
    const CartesianVector < Angle, _in_frame_ > & angles
) 
```





**Parameters:**


* `angles` A [**CartesianVector**](structastrea_1_1astro_1_1CartesianVector.md) containing the three angles in the sequence. 




        

<hr>



### function EulerAngles [4/10]

```C++
explicit astrea::astro::EulerAngles::EulerAngles (
    const EulerAngles & other
) = default
```



Default copy and move constructors and assignment operators for the same sequence, rotation type, and frames. 


        

<hr>



### function EulerAngles [5/10]

```C++
explicit astrea::astro::EulerAngles::EulerAngles (
    EulerAngles && other
) = default
```




<hr>



### function EulerAngles [6/10]

```C++
template<RotationSequence sequence_u, RotationType rotation_type_u, auto _in_frame_u_, auto _out_frame_u_>
inline astrea::astro::EulerAngles::EulerAngles (
    const EulerAngles < sequence_u, rotation_type_u, _in_frame_u_, _out_frame_u_ > & other
) 
```



Copy and move constructors and assignment operators for equivalent sequences (reverse sequence and opposite rotation type). These allow for implicit conversions between equivalent sequences (e.g., ZXZ extrinsic with angles [x, y, z] to ZXZ intrinsic with angles [z, y, x]). 


        

<hr>



### function EulerAngles [7/10]

```C++
template<RotationSequence sequence_u, RotationType rotation_type_u, auto _in_frame_u_, auto _out_frame_u_>
inline astrea::astro::EulerAngles::EulerAngles (
    EulerAngles < sequence_u, rotation_type_u, _in_frame_u_, _out_frame_u_ > && other
) 
```




<hr>



### function EulerAngles [8/10]

_Explicit copy constructor for incompatible sequences (different specific sequence, different rotation type, or different frames). Converts through the DCM to ensure correct transformations between frames and proper handling of singularities._ 
```C++
template<RotationSequence sequence_u, RotationType rotation_type_u>
astrea::astro::EulerAngles::EulerAngles (
    const EulerAngles < sequence_u, rotation_type_u, _in_frame_, _out_frame_ > & other
) 
```





**Parameters:**


* `other` The other [**EulerAngles**](classastrea_1_1astro_1_1EulerAngles.md) to copy from, which must be incompatible with this sequence. 



**Returns:**

[**EulerAngles**](classastrea_1_1astro_1_1EulerAngles.md)&lt;sequence, rotation\_type, _in\_frame_, _out\_frame_&gt; A new [**EulerAngles**](classastrea_1_1astro_1_1EulerAngles.md) object that is the result of converting the other sequence to this sequence. 





        

<hr>



### function EulerAngles [9/10]

```C++
template<RotationSequence sequence_u, RotationType rotation_type_u, auto _in_frame_u_, auto _out_frame_u_>
astrea::astro::EulerAngles::EulerAngles (
    const EulerAngles < sequence_u, rotation_type_u, _in_frame_u_, _out_frame_u_ > & other
) = delete
```




<hr>



### function EulerAngles [10/10]

```C++
template<RotationSequence sequence_u, RotationType rotation_type_u, auto _in_frame_u_, auto _out_frame_u_>
astrea::astro::EulerAngles::EulerAngles (
    EulerAngles < sequence_u, rotation_type_u, _in_frame_u_, _out_frame_u_ > && other
) = delete
```




<hr>



### function cross [1/2]

_Cross product of this angle vector with another_ [_**EulerAngles**_](classastrea_1_1astro_1_1EulerAngles.md) _._
```C++
inline auto astrea::astro::EulerAngles::cross (
    const EulerAngles < sequence, rotation_type, _in_frame_, _out_frame_ > & other
) const
```





**Parameters:**


* `other` The other [**EulerAngles**](classastrea_1_1astro_1_1EulerAngles.md) to take the cross product with. 



**Returns:**

auto The resulting [**CartesianVector**](structastrea_1_1astro_1_1CartesianVector.md) from the cross product. 





        

<hr>



### function cross [2/2]

_Cross product of this angle vector with a generic_ [_**CartesianVector**_](structastrea_1_1astro_1_1CartesianVector.md) _._
```C++
template<typename Value_U>
inline auto astrea::astro::EulerAngles::cross (
    const CartesianVector < Value_U, _in_frame_ > & other
) const
```





**Template parameters:**


* `Value_U` The value type of the [**CartesianVector**](structastrea_1_1astro_1_1CartesianVector.md). 



**Parameters:**


* `other` The [**CartesianVector**](structastrea_1_1astro_1_1CartesianVector.md) to take the cross product with. 



**Returns:**

auto The resulting [**CartesianVector**](structastrea_1_1astro_1_1CartesianVector.md) from the cross product. 





        

<hr>



### function dot [1/2]

_Dot product of this angle vector with another_ [_**EulerAngles**_](classastrea_1_1astro_1_1EulerAngles.md) _._
```C++
inline auto astrea::astro::EulerAngles::dot (
    const EulerAngles < sequence, rotation_type, _in_frame_, _out_frame_ > & other
) const
```





**Parameters:**


* `other` The other [**EulerAngles**](classastrea_1_1astro_1_1EulerAngles.md) to take the dot product with. 



**Returns:**

auto The resulting scalar from the dot product. 





        

<hr>



### function dot [2/2]

_Dot product of this angle vector with a generic_ [_**CartesianVector**_](structastrea_1_1astro_1_1CartesianVector.md) _._
```C++
template<typename Value_U>
inline auto astrea::astro::EulerAngles::dot (
    const CartesianVector < Value_U, _in_frame_ > & other
) const
```





**Template parameters:**


* `Value_U` The value type of the [**CartesianVector**](structastrea_1_1astro_1_1CartesianVector.md). 



**Parameters:**


* `other` The [**CartesianVector**](structastrea_1_1astro_1_1CartesianVector.md) to take the dot product with. 



**Returns:**

auto The resulting scalar from the dot product. 





        

<hr>



### function force\_to\_double\_vector 

_Converts the angle sequence to a vector form for use in numerical integration._ 
```C++
inline std::vector< double > astrea::astro::EulerAngles::force_to_double_vector () const
```





**Returns:**

A std::vector of Unitless quantities representing the components of the angle sequence, in the order [first, second, third]. 





        

<hr>



### function get\_angles [1/2]

_Get access to the underlying_ [_**CartesianVector**_](structastrea_1_1astro_1_1CartesianVector.md) _._
```C++
inline CartesianVector < Angle, _in_frame_ > & astrea::astro::EulerAngles::get_angles () 
```





**Returns:**

[**CartesianVector**](structastrea_1_1astro_1_1CartesianVector.md)&lt;Angle, _in\_frame_&gt;& Reference to the internal [**CartesianVector**](structastrea_1_1astro_1_1CartesianVector.md). 





        

<hr>



### function get\_angles [2/2]

_Get const access to the underlying_ [_**CartesianVector**_](structastrea_1_1astro_1_1CartesianVector.md) _._
```C++
inline const CartesianVector < Angle, _in_frame_ > & astrea::astro::EulerAngles::get_angles () const
```





**Returns:**

const [**CartesianVector**](structastrea_1_1astro_1_1CartesianVector.md)&lt;Angle, _in\_frame_&gt;& Const reference to the internal [**CartesianVector**](structastrea_1_1astro_1_1CartesianVector.md). 





        

<hr>



### function get\_inverse\_sequence 

_Constructs the inverse sequence with the same rotation type._ 
```C++
inline EulerAngles < get_reverse_sequence (sequence), rotation_type, _out_frame_, _in_frame_ > astrea::astro::EulerAngles::get_inverse_sequence () const
```





**Returns:**

[**EulerAngles**](classastrea_1_1astro_1_1EulerAngles.md)&lt;get\_reverse\_sequence(sequence), rotation\_type, _out\_frame_, _in\_frame_&gt; A new [**EulerAngles**](classastrea_1_1astro_1_1EulerAngles.md) object that is the inverse sequence with the same rotation type and reversed angles. object that is the inverse sequence with the same rotation type and reversed angles. 





        

<hr>



### function interpolate 

_Interpolates between this angle sequence and another angle sequence at a target time._ 
```C++
inline EulerAngles < sequence, rotation_type, _in_frame_, _out_frame_ > astrea::astro::EulerAngles::interpolate (
    const Time & thisTime,
    const Time & otherTime,
    const EulerAngles < sequence, rotation_type, _in_frame_, _out_frame_ > & other,
    const Time & targetTime
) const
```





**Parameters:**


* `thisTime` The time corresponding to this angle sequence. 
* `otherTime` The time corresponding to the other angle sequence. 
* `other` The other angle sequence to interpolate with. 
* `targetTime` The time at which to interpolate the angle sequence. 



**Returns:**

[**EulerAngles**](classastrea_1_1astro_1_1EulerAngles.md)&lt;sequence, rotation\_type, _in\_frame_, _out\_frame_&gt; A new [**EulerAngles**](classastrea_1_1astro_1_1EulerAngles.md) that is the interpolation of this sequence and the other at the target time. 





        

<hr>



### function norm 

_Norm of the angle vector._ 
```C++
inline Angle astrea::astro::EulerAngles::norm () const
```





**Returns:**

Angle The resulting norm of the angle vector. 





        

<hr>



### function operator\* 

_Scalar multiplication operator for_ [_**EulerAngles**_](classastrea_1_1astro_1_1EulerAngles.md) _._
```C++
inline EulerAngles < sequence, rotation_type, _in_frame_, _out_frame_ > astrea::astro::EulerAngles::operator* (
    const Unitless & scalar
) const
```





**Parameters:**


* `scalar` The scalar value to multiply with. 



**Returns:**

[**EulerAngles**](classastrea_1_1astro_1_1EulerAngles.md)&lt;sequence, rotation\_type, _in\_frame_, _out\_frame_&gt; A new [**EulerAngles**](classastrea_1_1astro_1_1EulerAngles.md) that is the product of this sequence and the scalar. 





        

<hr>



### function operator\*= 

_Scalar multiplication assignment operator for_ [_**EulerAngles**_](classastrea_1_1astro_1_1EulerAngles.md) _._
```C++
inline EulerAngles < sequence, rotation_type, _in_frame_, _out_frame_ > & astrea::astro::EulerAngles::operator*= (
    const Unitless & scalar
) 
```





**Parameters:**


* `scalar` The scalar value to multiply with. 



**Returns:**

[**EulerAngles**](classastrea_1_1astro_1_1EulerAngles.md)&lt;sequence, rotation\_type, _in\_frame_, _out\_frame_&gt;& Reference to the current object after multiplication. 





        

<hr>



### function operator+ 

_Addition operator for_ [_**CartesianVector**_](structastrea_1_1astro_1_1CartesianVector.md) _._
```C++
inline EulerAngles < sequence, rotation_type, _in_frame_, _out_frame_ > astrea::astro::EulerAngles::operator+ (
    const EulerAngles < sequence, rotation_type, _in_frame_, _out_frame_ > & other
) const
```





**Parameters:**


* `other` The other [**EulerAngles**](classastrea_1_1astro_1_1EulerAngles.md) to add. 



**Returns:**

[**EulerAngles**](classastrea_1_1astro_1_1EulerAngles.md)&lt;sequence, rotation\_type, _in\_frame_, _out\_frame_&gt; A new [**EulerAngles**](classastrea_1_1astro_1_1EulerAngles.md) that is the sum of this sequence and the other. 





        

<hr>



### function operator+= 

_Addition assignment operator for_ [_**EulerAngles**_](classastrea_1_1astro_1_1EulerAngles.md) _._
```C++
inline EulerAngles < sequence, rotation_type, _in_frame_, _out_frame_ > & astrea::astro::EulerAngles::operator+= (
    const EulerAngles < sequence, rotation_type, _in_frame_, _out_frame_ > & other
) 
```





**Parameters:**


* `other` The other [**EulerAngles**](classastrea_1_1astro_1_1EulerAngles.md) to add. 



**Returns:**

[**EulerAngles**](classastrea_1_1astro_1_1EulerAngles.md)&lt;sequence, rotation\_type, _in\_frame_, _out\_frame_&gt;& Reference to the current object after addition. 





        

<hr>



### function operator- 

_Subtraction operator for_ [_**EulerAngles**_](classastrea_1_1astro_1_1EulerAngles.md) _._
```C++
inline EulerAngles < sequence, rotation_type, _in_frame_, _out_frame_ > astrea::astro::EulerAngles::operator- (
    const EulerAngles < sequence, rotation_type, _in_frame_, _out_frame_ > & other
) const
```





**Parameters:**


* `other` The other [**EulerAngles**](classastrea_1_1astro_1_1EulerAngles.md) to subtract. 



**Returns:**

[**EulerAngles**](classastrea_1_1astro_1_1EulerAngles.md)&lt;sequence, rotation\_type, _in\_frame_, _out\_frame_&gt; A new [**EulerAngles**](classastrea_1_1astro_1_1EulerAngles.md) that is the difference of this sequence and the other. 





        

<hr>



### function operator- 

_Negation operator for_ [_**EulerAngles**_](classastrea_1_1astro_1_1EulerAngles.md) _._
```C++
inline EulerAngles < sequence, rotation_type, _in_frame_, _out_frame_ > astrea::astro::EulerAngles::operator- () const
```





**Returns:**

[**EulerAngles**](classastrea_1_1astro_1_1EulerAngles.md)&lt;sequence, rotation\_type, _in\_frame_, _out\_frame_&gt; A new [**EulerAngles**](classastrea_1_1astro_1_1EulerAngles.md) that is the negation of this sequence. 





        

<hr>



### function operator-= 

_Subtraction assignment operator for_ [_**EulerAngles**_](classastrea_1_1astro_1_1EulerAngles.md) _._
```C++
inline EulerAngles < sequence, rotation_type, _in_frame_, _out_frame_ > & astrea::astro::EulerAngles::operator-= (
    const EulerAngles < sequence, rotation_type, _in_frame_, _out_frame_ > & other
) 
```





**Parameters:**


* `other` The other [**EulerAngles**](classastrea_1_1astro_1_1EulerAngles.md) to subtract. 



**Returns:**

[**EulerAngles**](classastrea_1_1astro_1_1EulerAngles.md)&lt;sequence, rotation\_type, _in\_frame_, _out\_frame_&gt;& Reference to the current object after subtraction. 





        

<hr>



### function operator/ 

_Scalar division operator for_ [_**EulerAngles**_](classastrea_1_1astro_1_1EulerAngles.md) _by a Time quantity, resulting in an EulerAnglesRate._
```C++
inline AngularVelocities < _in_frame_, _out_frame_ > astrea::astro::EulerAngles::operator/ (
    const Time & time
) const
```





**Parameters:**


* `time` The time quantity to divide by. 



**Returns:**

[**AngularVelocities**](classastrea_1_1astro_1_1AngularVelocities.md)&lt;_in\_frame_, _out\_frame_&gt; A new [**AngularVelocities**](classastrea_1_1astro_1_1AngularVelocities.md) that is the quotient of this sequence and the time. 





        

<hr>



### function operator/ 

_Scalar division operator for_ [_**EulerAngles**_](classastrea_1_1astro_1_1EulerAngles.md) _._
```C++
inline EulerAngles < sequence, rotation_type, _in_frame_, _out_frame_ > astrea::astro::EulerAngles::operator/ (
    const Unitless & scalar
) const
```





**Parameters:**


* `scalar` The scalar value to divide by. 



**Returns:**

[**EulerAngles**](classastrea_1_1astro_1_1EulerAngles.md)&lt;sequence, rotation\_type, _in\_frame_, _out\_frame_&gt; A new [**EulerAngles**](classastrea_1_1astro_1_1EulerAngles.md) that is the quotient of this sequence and the scalar. 





        

<hr>



### function operator/= 

_Scalar division assignment operator for_ [_**EulerAngles**_](classastrea_1_1astro_1_1EulerAngles.md) _._
```C++
inline EulerAngles < sequence, rotation_type, _in_frame_, _out_frame_ > & astrea::astro::EulerAngles::operator/= (
    const Unitless & scalar
) 
```





**Parameters:**


* `scalar` The scalar value to divide by. 



**Returns:**

[**EulerAngles**](classastrea_1_1astro_1_1EulerAngles.md)&lt;sequence, rotation\_type, _in\_frame_, _out\_frame_&gt;& Reference to the current object after division. 





        

<hr>



### function operator= 

```C++
EulerAngles & astrea::astro::EulerAngles::operator= (
    const EulerAngles & other
) = default
```




<hr>



### function operator= 

```C++
EulerAngles & astrea::astro::EulerAngles::operator= (
    EulerAngles && other
) = default
```




<hr>



### function operator= 

```C++
template<RotationSequence sequence_u, RotationType rotation_type_u, auto _in_frame_u_, auto _out_frame_u_>
inline EulerAngles & astrea::astro::EulerAngles::operator= (
    const EulerAngles < sequence_u, rotation_type_u, _in_frame_u_, _out_frame_u_ > & other
) 
```




<hr>



### function operator= 

```C++
template<RotationSequence sequence_u, RotationType rotation_type_u, auto _in_frame_u_, auto _out_frame_u_>
inline EulerAngles & astrea::astro::EulerAngles::operator= (
    EulerAngles < sequence_u, rotation_type_u, _in_frame_u_, _out_frame_u_ > && other
) 
```




<hr>



### function operator= 

```C++
template<RotationSequence sequence_u, RotationType rotation_type_u, auto _in_frame_u_, auto _out_frame_u_>
EulerAngles < sequence, rotation_type, _in_frame_, _out_frame_ > & astrea::astro::EulerAngles::operator= (
    const EulerAngles < sequence_u, rotation_type_u, _in_frame_u_, _out_frame_u_ > & other
) = delete
```




<hr>



### function operator= 

```C++
template<RotationSequence sequence_u, RotationType rotation_type_u, auto _in_frame_u_, auto _out_frame_u_>
EulerAngles < sequence, rotation_type, _in_frame_, _out_frame_ > & astrea::astro::EulerAngles::operator= (
    EulerAngles < sequence_u, rotation_type_u, _in_frame_u_, _out_frame_u_ > && other
) = delete
```




<hr>



### function operator== 

_Equality operator for_ [_**CartesianVector**_](structastrea_1_1astro_1_1CartesianVector.md) _._
```C++
inline bool astrea::astro::EulerAngles::operator== (
    const EulerAngles < sequence, rotation_type, _in_frame_, _out_frame_ > & other
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

```C++
template<RotationSequence sequence_u, RotationType rotation_type_u, auto _in_frame_u_, auto _out_frame_u_>
inline bool astrea::astro::EulerAngles::operator== (
    const EulerAngles < sequence_u, rotation_type_u, _in_frame_u_, _out_frame_u_ > & other
) const
```




<hr>



### function operator== 

_Inequality operator for_ [_**CartesianVector**_](structastrea_1_1astro_1_1CartesianVector.md) _in a different frame. Always false._
```C++
template<RotationSequence sequence_u, RotationType rotation_type_u, auto _in_frame_u_, auto _out_frame_u_>
inline bool astrea::astro::EulerAngles::operator== (
    const EulerAngles < sequence_u, rotation_type_u, _in_frame_u_, _out_frame_u_ > & other
) const
```





**Parameters:**


* `other` The other [**CartesianVector**](structastrea_1_1astro_1_1CartesianVector.md) to compare with. 



**Returns:**

true If the two vectors are not equal. 




**Returns:**

false If the two vectors are equal. 





        

<hr>



### function operator[] 

_Array access operator for accessing individual angle components._ 
```C++
inline Angle & astrea::astro::EulerAngles::operator[] (
    std::size_t index
) 
```





**Parameters:**


* `index` The index of the angle component (0, 1, or 2). 



**Returns:**

Angle& Reference to the angle component. 





        

<hr>



### function operator[] 

_Const array access operator for accessing individual angle components._ 
```C++
inline const Angle & astrea::astro::EulerAngles::operator[] (
    std::size_t index
) const
```





**Parameters:**


* `index` The index of the angle component (0, 1, or 2). 



**Returns:**

const Angle& Const reference to the angle component. 





        

<hr>



### function to\_dcm 

_Converts the angle sequence to a direction cosine matrix (DCM) for transforming vectors between frames._ 
```C++
inline DirectionCosineMatrix < _in_frame_, _out_frame_ > astrea::astro::EulerAngles::to_dcm () const
```





**Returns:**

[**DirectionCosineMatrix**](classastrea_1_1astro_1_1DirectionCosineMatrix.md)&lt;_in\_frame_, _out\_frame_&gt; The resulting direction cosine matrix. 





        

<hr>



### function to\_rotation\_type [1/2]

_Converts the angle sequence to the opposite rotation type (intrinsic to extrinsic or vice versa) by reversing the order of the angles._ 
```C++
template<RotationType rotation_u>
inline EulerAngles < get_reverse_sequence (sequence), rotation_u, _in_frame_, _out_frame_ > astrea::astro::EulerAngles::to_rotation_type () const
```




<hr>



### function to\_rotation\_type [2/2]

_Converts the angle sequence to the same rotation type (intrinsic to intrinsic or extrinsic to extrinsic). This is a no-op but allows for explicit conversions between different sequences of the same rotation type._ 
```C++
template<RotationType rotation_u>
inline EulerAngles < sequence, rotation_type, _in_frame_, _out_frame_ > astrea::astro::EulerAngles::to_rotation_type () const
```




<hr>

------------------------------
The documentation for this class was generated from the following file `astrea/astro/astro/state/attitude/EulerAngles.hpp`

