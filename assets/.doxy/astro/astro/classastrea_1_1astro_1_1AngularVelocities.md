

# Class astrea::astro::AngularVelocities

**template &lt;IsFrame [**auto**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) \_in\_frame\_, IsFrame [**auto**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) \_ref\_frame\_&gt;**



[**ClassList**](annotated.md) **>** [**astrea**](namespaceastrea.md) **>** [**astro**](namespaceastrea_1_1astro.md) **>** [**AngularVelocities**](classastrea_1_1astro_1_1AngularVelocities.md)



_Class representing a sequence of angular velocities (either Euler or Tait-Bryan) for attitude transformations between frames._ [More...](#detailed-description)

* `#include <AngularVelocities.hpp>`























## Public Static Attributes

| Type | Name |
| ---: | :--- |
|  [**constexpr**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) [**auto**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) | [**in\_frame**](#variable-in_frame)   = `[**\_in\_frame\_**](classastrea_1_1astro_1_1DirectionCosineMatrix.md)`<br> |
|  [**constexpr**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) [**auto**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) | [**ref\_frame**](#variable-ref_frame)   = `[**\_ref\_frame\_**](classastrea_1_1astro_1_1DirectionCosineMatrix.md)`<br> |














## Public Functions

| Type | Name |
| ---: | :--- |
|   | [**AngularVelocities**](#function-angularvelocities-15) () = default<br>_Default constructor for the_ [_**AngularVelocities**_](classastrea_1_1astro_1_1AngularVelocities.md) _class. Initializes all angles to zero._ |
|   | [**AngularVelocities**](#function-angularvelocities-25) ([**const**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) [**AngularVelocity**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) & angle1, [**const**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) [**AngularVelocity**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) & angle2, [**const**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) [**AngularVelocity**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) & angle3) <br>_Constructor for the_ [_**AngularVelocities**_](classastrea_1_1astro_1_1AngularVelocities.md) _class from three angles._ |
|   | [**AngularVelocities**](#function-angularvelocities-35) ([**const**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) [**CartesianVector**](structastrea_1_1astro_1_1CartesianVector.md)&lt; [**AngularVelocity**](classastrea_1_1astro_1_1DirectionCosineMatrix.md), in\_frame &gt; & angles) <br>_Constructor for the_ [_**AngularVelocities**_](classastrea_1_1astro_1_1AngularVelocities.md) _class from a_[_**CartesianVector**_](structastrea_1_1astro_1_1CartesianVector.md) _of angles._ |
|   | [**AngularVelocities**](#function-angularvelocities-45) ([**const**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) [**AngularVelocities**](classastrea_1_1astro_1_1AngularVelocities.md) & other) = default<br> |
|   | [**AngularVelocities**](#function-angularvelocities-55) ([**AngularVelocities**](classastrea_1_1astro_1_1AngularVelocities.md) && other) = default<br> |
|  [**CartesianVector**](structastrea_1_1astro_1_1CartesianVector.md)&lt; [**decltype**](classastrea_1_1astro_1_1DirectionCosineMatrix.md)([**AngularVelocity**](classastrea_1_1astro_1_1DirectionCosineMatrix.md){} \*[**Value\_U**](classastrea_1_1astro_1_1DirectionCosineMatrix.md){}), in\_frame &gt; | [**cross**](#function-cross-12) ([**const**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) [**CartesianVector**](structastrea_1_1astro_1_1CartesianVector.md)&lt; [**Value\_U**](classastrea_1_1astro_1_1DirectionCosineMatrix.md), in\_frame &gt; & other) const<br>_Cross product of this angular velocity vector with a_ [_**CartesianVector**_](structastrea_1_1astro_1_1CartesianVector.md) _._ |
|  [**CartesianVector**](structastrea_1_1astro_1_1CartesianVector.md)&lt; [**decltype**](classastrea_1_1astro_1_1DirectionCosineMatrix.md)([**AngularVelocity**](classastrea_1_1astro_1_1DirectionCosineMatrix.md){} \*[**AngularVelocity**](classastrea_1_1astro_1_1DirectionCosineMatrix.md){}), in\_frame &gt; | [**cross**](#function-cross-22) ([**const**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) [**AngularVelocities**](classastrea_1_1astro_1_1AngularVelocities.md) & other) const<br>_Cross product of this angle vector with another_ [_**AngularVelocities**_](classastrea_1_1astro_1_1AngularVelocities.md) _._ |
|  [**auto**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) | [**dot**](#function-dot-12) ([**const**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) [**CartesianVector**](structastrea_1_1astro_1_1CartesianVector.md)&lt; [**Value\_U**](classastrea_1_1astro_1_1DirectionCosineMatrix.md), in\_frame &gt; & other) const<br>_Dot product of this angular velocity vector with a_ [_**CartesianVector**_](structastrea_1_1astro_1_1CartesianVector.md) _._ |
|  [**auto**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) | [**dot**](#function-dot-22) ([**const**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) [**AngularVelocities**](classastrea_1_1astro_1_1AngularVelocities.md) & other) const<br>_Dot product of this angle vector with another_ [_**AngularVelocities**_](classastrea_1_1astro_1_1AngularVelocities.md) _._ |
|  std::vector&lt; [**Unitless**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) &gt; | [**force\_to\_vector**](#function-force_to_vector) () const<br>_Converts the angle sequence velocity to a vector form for use in numerical integration._  |
|  [**CartesianVector**](structastrea_1_1astro_1_1CartesianVector.md)&lt; [**AngularVelocity**](classastrea_1_1astro_1_1DirectionCosineMatrix.md), in\_frame &gt; & | [**get\_angular\_velocities**](#function-get_angular_velocities-12) () <br>_Get access to the underlying_ [_**CartesianVector**_](structastrea_1_1astro_1_1CartesianVector.md) _._ |
|  [**const**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) [**CartesianVector**](structastrea_1_1astro_1_1CartesianVector.md)&lt; [**AngularVelocity**](classastrea_1_1astro_1_1DirectionCosineMatrix.md), in\_frame &gt; & | [**get\_angular\_velocities**](#function-get_angular_velocities-22) () const<br>_Get const access to the underlying_ [_**CartesianVector**_](structastrea_1_1astro_1_1CartesianVector.md) _._ |
|  [**AngularVelocities**](classastrea_1_1astro_1_1AngularVelocities.md) | [**interpolate**](#function-interpolate) ([**const**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) [**Time**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) & thisTime, [**const**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) [**Time**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) & otherTime, [**const**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) [**AngularVelocities**](classastrea_1_1astro_1_1AngularVelocities.md) & other, [**const**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) [**Time**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) & targetTime) const<br>_Interpolates between this angle sequence and another angle sequence at a target time._  |
|  [**CartesianVector**](structastrea_1_1astro_1_1CartesianVector.md)&lt; [**decltype**](classastrea_1_1astro_1_1DirectionCosineMatrix.md)([**AngularVelocity**](classastrea_1_1astro_1_1DirectionCosineMatrix.md){} \*[**Value\_U**](classastrea_1_1astro_1_1DirectionCosineMatrix.md){}), in\_frame &gt; | [**operator\***](#function-operator) ([**const**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) [**Value\_U**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) & scalar) const<br>_Scalar multiplication operator for_ [_**AngularVelocities**_](classastrea_1_1astro_1_1AngularVelocities.md) _by a quantity, resulting in an_[_**CartesianVector**_](structastrea_1_1astro_1_1CartesianVector.md) _._ |
|  [**EulerAngles**](classastrea_1_1astro_1_1EulerAngles.md)&lt; sequence, [**rotation\_type**](classastrea_1_1astro_1_1DirectionCosineMatrix.md), in\_frame, ref\_frame &gt; | [**operator\***](#function-operator_1) ([**const**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) [**Time**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) & time) const<br>_Scalar multiplication operator for_ [_**AngularVelocities**_](classastrea_1_1astro_1_1AngularVelocities.md) _by a Time quantity, resulting in an_[_**EulerAngles**_](classastrea_1_1astro_1_1EulerAngles.md) _._ |
|  [**AngularVelocities**](classastrea_1_1astro_1_1AngularVelocities.md) | [**operator\***](#function-operator_2) ([**const**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) [**Unitless**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) & scale) const<br>_Scalar multiplication operator for_ [_**AngularVelocities**_](classastrea_1_1astro_1_1AngularVelocities.md) _by a quantity, resulting in an_[_**AngularVelocities**_](classastrea_1_1astro_1_1AngularVelocities.md) _._ |
|  [**AngularVelocities**](classastrea_1_1astro_1_1AngularVelocities.md) & | [**operator\*=**](#function-operator_3) ([**const**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) [**Unitless**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) & scale) <br>_Scalar multiplication assignment operator for_ [_**AngularVelocities**_](classastrea_1_1astro_1_1AngularVelocities.md) _by a quantity._ |
|  [**CartesianVector**](structastrea_1_1astro_1_1CartesianVector.md)&lt; [**AngularVelocity**](classastrea_1_1astro_1_1DirectionCosineMatrix.md), in\_frame &gt; | [**operator+**](#function-operator_4) ([**const**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) [**CartesianVector**](structastrea_1_1astro_1_1CartesianVector.md)&lt; [**AngularVelocity**](classastrea_1_1astro_1_1DirectionCosineMatrix.md), in\_frame &gt; & other) const<br>_Addition operator for_ [_**CartesianVector**_](structastrea_1_1astro_1_1CartesianVector.md) _._ |
|  [**AngularVelocities**](classastrea_1_1astro_1_1AngularVelocities.md) | [**operator+**](#function-operator_5) ([**const**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) [**AngularVelocities**](classastrea_1_1astro_1_1AngularVelocities.md) & other) const<br>_Addition operator for_ [_**CartesianVector**_](structastrea_1_1astro_1_1CartesianVector.md) _._ |
|  [**AngularVelocities**](classastrea_1_1astro_1_1AngularVelocities.md) & | [**operator+=**](#function-operator_6) ([**const**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) [**AngularVelocities**](classastrea_1_1astro_1_1AngularVelocities.md) & other) <br>_Addition assignment operator for_ [_**AngularVelocities**_](classastrea_1_1astro_1_1AngularVelocities.md) _._ |
|  [**AngularVelocities**](classastrea_1_1astro_1_1AngularVelocities.md) | [**operator-**](#function-operator-) () const<br>_Unary negation operator for_ [_**AngularVelocities**_](classastrea_1_1astro_1_1AngularVelocities.md) _._ |
|  [**CartesianVector**](structastrea_1_1astro_1_1CartesianVector.md)&lt; [**AngularVelocity**](classastrea_1_1astro_1_1DirectionCosineMatrix.md), in\_frame &gt; | [**operator-**](#function-operator-_1) ([**const**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) [**CartesianVector**](structastrea_1_1astro_1_1CartesianVector.md)&lt; [**AngularVelocity**](classastrea_1_1astro_1_1DirectionCosineMatrix.md), in\_frame &gt; & other) const<br>_Subtraction operator for_ [_**CartesianVector**_](structastrea_1_1astro_1_1CartesianVector.md) _._ |
|  [**AngularVelocities**](classastrea_1_1astro_1_1AngularVelocities.md) | [**operator-**](#function-operator-_2) ([**const**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) [**AngularVelocities**](classastrea_1_1astro_1_1AngularVelocities.md) & other) const<br>_Subtraction operator for_ [_**AngularVelocities**_](classastrea_1_1astro_1_1AngularVelocities.md) _._ |
|  [**AngularVelocities**](classastrea_1_1astro_1_1AngularVelocities.md) & | [**operator-=**](#function-operator-_3) ([**const**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) [**AngularVelocities**](classastrea_1_1astro_1_1AngularVelocities.md) & other) <br>_Subtraction assignment operator for_ [_**AngularVelocities**_](classastrea_1_1astro_1_1AngularVelocities.md) _._ |
|  [**CartesianVector**](structastrea_1_1astro_1_1CartesianVector.md)&lt; [**decltype**](classastrea_1_1astro_1_1DirectionCosineMatrix.md)([**AngularVelocity**](classastrea_1_1astro_1_1DirectionCosineMatrix.md){}/[**Value\_U**](classastrea_1_1astro_1_1DirectionCosineMatrix.md){}), in\_frame &gt; | [**operator/**](#function-operator_7) ([**const**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) [**Value\_U**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) & scalar) const<br>_Scalar division operator for_ [_**AngularVelocities**_](classastrea_1_1astro_1_1AngularVelocities.md) _by a quantity, resulting in a_[_**CartesianVector**_](structastrea_1_1astro_1_1CartesianVector.md) _._ |
|  [**AngularAccelerations**](classastrea_1_1astro_1_1AngularAccelerations.md)&lt; in\_frame, ref\_frame &gt; | [**operator/**](#function-operator_8) ([**const**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) [**Time**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) & time) const<br>_Scalar division operator for_ [_**AngularVelocities**_](classastrea_1_1astro_1_1AngularVelocities.md) _by a Time quantity, resulting in an_[_**AngularAccelerations**_](classastrea_1_1astro_1_1AngularAccelerations.md) _._ |
|  [**AngularVelocities**](classastrea_1_1astro_1_1AngularVelocities.md) | [**operator/**](#function-operator_9) ([**const**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) [**Unitless**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) & scale) const<br>_Scalar division operator for_ [_**AngularVelocities**_](classastrea_1_1astro_1_1AngularVelocities.md) _by a quantity, resulting in an_[_**AngularVelocities**_](classastrea_1_1astro_1_1AngularVelocities.md) _._ |
|  [**AngularVelocities**](classastrea_1_1astro_1_1AngularVelocities.md) & | [**operator/=**](#function-operator_10) ([**const**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) [**Unitless**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) & scale) <br>_Scalar division assignment operator for_ [_**AngularVelocities**_](classastrea_1_1astro_1_1AngularVelocities.md) _by a quantity._ |
|  [**AngularVelocities**](classastrea_1_1astro_1_1AngularVelocities.md) & | [**operator=**](#function-operator_11) ([**const**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) [**AngularVelocities**](classastrea_1_1astro_1_1AngularVelocities.md) & other) = default<br> |
|  [**AngularVelocities**](classastrea_1_1astro_1_1AngularVelocities.md) & | [**operator=**](#function-operator_12) ([**AngularVelocities**](classastrea_1_1astro_1_1AngularVelocities.md) && other) = default<br> |
|  [**bool**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) | [**operator==**](#function-operator_13) ([**const**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) [**AngularVelocities**](classastrea_1_1astro_1_1AngularVelocities.md) & other) const<br> |
|  [**bool**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) | [**operator==**](#function-operator_14) ([**const**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) [**AngularVelocities**](classastrea_1_1astro_1_1AngularVelocities.md)&lt; [**in\_frame\_u**](classastrea_1_1astro_1_1DirectionCosineMatrix.md), [**ref\_frame\_u**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) &gt; &) const<br> |
|  [**AngularVelocity**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) & | [**operator[]**](#function-operator_15) (std::size\_t index) <br>_Array access operator for accessing individual angular velocity components._  |
|  [**const**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) [**AngularVelocity**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) & | [**operator[]**](#function-operator_16) (std::size\_t index) const<br>_Const array access operator for accessing individual angular velocity components._  |




























## Detailed Description




**Template parameters:**


* `in_frame` The input frame type (e.g., ECI, ECEF), defaulting to dynamic body frame. 
* `ref_frame` The reference frame type (e.g., ECI, ECEF), defaulting to Earth ICRF frame. 




    
## Public Static Attributes Documentation




### variable in\_frame 

```C++
constexpr auto astrea::astro::AngularVelocities< _in_frame_, _ref_frame_ >::in_frame;
```




<hr>



### variable ref\_frame 

```C++
constexpr auto astrea::astro::AngularVelocities< _in_frame_, _ref_frame_ >::ref_frame;
```




<hr>
## Public Functions Documentation




### function AngularVelocities [1/5]

_Default constructor for the_ [_**AngularVelocities**_](classastrea_1_1astro_1_1AngularVelocities.md) _class. Initializes all angles to zero._
```C++
astrea::astro::AngularVelocities::AngularVelocities () = default
```




<hr>



### function AngularVelocities [2/5]

_Constructor for the_ [_**AngularVelocities**_](classastrea_1_1astro_1_1AngularVelocities.md) _class from three angles._
```C++
inline astrea::astro::AngularVelocities::AngularVelocities (
    const  AngularVelocity & angle1,
    const  AngularVelocity & angle2,
    const  AngularVelocity & angle3
) 
```





**Parameters:**


* `angle1` The first angle in the sequence. 
* `angle2` The second angle in the sequence. 
* `angle3` The third angle in the sequence. 




        

<hr>



### function AngularVelocities [3/5]

_Constructor for the_ [_**AngularVelocities**_](classastrea_1_1astro_1_1AngularVelocities.md) _class from a_[_**CartesianVector**_](structastrea_1_1astro_1_1CartesianVector.md) _of angles._
```C++
inline astrea::astro::AngularVelocities::AngularVelocities (
    const  CartesianVector < AngularVelocity , in_frame > & angles
) 
```





**Parameters:**


* `angles` A [**CartesianVector**](structastrea_1_1astro_1_1CartesianVector.md) containing the three angles in the sequence. 




        

<hr>



### function AngularVelocities [4/5]

```C++
explicit astrea::astro::AngularVelocities::AngularVelocities (
    const  AngularVelocities & other
) = default
```




<hr>



### function AngularVelocities [5/5]

```C++
explicit astrea::astro::AngularVelocities::AngularVelocities (
    AngularVelocities && other
) = default
```




<hr>



### function cross [1/2]

_Cross product of this angular velocity vector with a_ [_**CartesianVector**_](structastrea_1_1astro_1_1CartesianVector.md) _._
```C++
template<typename  Value_U>
inline CartesianVector < decltype ( AngularVelocity {} * Value_U {}), in_frame > astrea::astro::AngularVelocities::cross (
    const  CartesianVector < Value_U , in_frame > & other
) const
```





**Template parameters:**


* `Value_U` The type of the [**CartesianVector**](structastrea_1_1astro_1_1CartesianVector.md)'s components. 



**Parameters:**


* `other` The [**CartesianVector**](structastrea_1_1astro_1_1CartesianVector.md) to take the cross product with. 



**Returns:**

[**CartesianVector**](structastrea_1_1astro_1_1CartesianVector.md)&lt;decltype(AngularVelocity{} \* Value\_U{}), in\_frame&gt; The resulting [**CartesianVector**](structastrea_1_1astro_1_1CartesianVector.md) from the cross product. 





        

<hr>



### function cross [2/2]

_Cross product of this angle vector with another_ [_**AngularVelocities**_](classastrea_1_1astro_1_1AngularVelocities.md) _._
```C++
inline CartesianVector < decltype ( AngularVelocity {} * AngularVelocity {}), in_frame > astrea::astro::AngularVelocities::cross (
    const  AngularVelocities & other
) const
```





**Parameters:**


* `other` The other [**AngularVelocities**](classastrea_1_1astro_1_1AngularVelocities.md) to take the cross product with. 



**Returns:**

[**CartesianVector**](structastrea_1_1astro_1_1CartesianVector.md)&lt;decltype(AngularVelocity{} \* AngularVelocity{}), in\_frame&gt; The resulting [**CartesianVector**](structastrea_1_1astro_1_1CartesianVector.md) from the cross product. 





        

<hr>



### function dot [1/2]

_Dot product of this angular velocity vector with a_ [_**CartesianVector**_](structastrea_1_1astro_1_1CartesianVector.md) _._
```C++
template<typename  Value_U>
inline auto astrea::astro::AngularVelocities::dot (
    const  CartesianVector < Value_U , in_frame > & other
) const
```





**Template parameters:**


* `Value_U` The type of the [**CartesianVector**](structastrea_1_1astro_1_1CartesianVector.md)'s components. 



**Parameters:**


* `other` The [**CartesianVector**](structastrea_1_1astro_1_1CartesianVector.md) to take the dot product with. 



**Returns:**

auto The resulting scalar from the dot product. 





        

<hr>



### function dot [2/2]

_Dot product of this angle vector with another_ [_**AngularVelocities**_](classastrea_1_1astro_1_1AngularVelocities.md) _._
```C++
inline auto astrea::astro::AngularVelocities::dot (
    const  AngularVelocities & other
) const
```





**Parameters:**


* `other` The other [**AngularVelocities**](classastrea_1_1astro_1_1AngularVelocities.md) to take the dot product with. 



**Returns:**

auto The resulting scalar from the dot product. 





        

<hr>



### function force\_to\_vector 

_Converts the angle sequence velocity to a vector form for use in numerical integration._ 
```C++
inline std::vector< Unitless > astrea::astro::AngularVelocities::force_to_vector () const
```





**Returns:**

A std::vector of Unitless quantities representing the components of the angle sequence velocity, in the order [first, second, third]. 





        

<hr>



### function get\_angular\_velocities [1/2]

_Get access to the underlying_ [_**CartesianVector**_](structastrea_1_1astro_1_1CartesianVector.md) _._
```C++
inline CartesianVector < AngularVelocity , in_frame > & astrea::astro::AngularVelocities::get_angular_velocities () 
```





**Returns:**

[**CartesianVector&lt;AngularVelocity, in\_frame&gt;**](structastrea_1_1astro_1_1CartesianVector.md)& Reference to the internal [**CartesianVector**](structastrea_1_1astro_1_1CartesianVector.md). 





        

<hr>



### function get\_angular\_velocities [2/2]

_Get const access to the underlying_ [_**CartesianVector**_](structastrea_1_1astro_1_1CartesianVector.md) _._
```C++
inline const  CartesianVector < AngularVelocity , in_frame > & astrea::astro::AngularVelocities::get_angular_velocities () const
```





**Returns:**

const [**CartesianVector&lt;AngularVelocity, in\_frame&gt;**](structastrea_1_1astro_1_1CartesianVector.md)& Const reference to the internal [**CartesianVector**](structastrea_1_1astro_1_1CartesianVector.md). 





        

<hr>



### function interpolate 

_Interpolates between this angle sequence and another angle sequence at a target time._ 
```C++
inline AngularVelocities astrea::astro::AngularVelocities::interpolate (
    const  Time & thisTime,
    const  Time & otherTime,
    const  AngularVelocities & other,
    const  Time & targetTime
) const
```





**Parameters:**


* `thisTime` The time corresponding to this angle sequence. 
* `otherTime` The time corresponding to the other angle sequence. 
* `other` The other angle sequence to interpolate with. 
* `targetTime` The time at which to interpolate the angle sequence. 



**Returns:**

[**AngularVelocities**](classastrea_1_1astro_1_1AngularVelocities.md) A new [**AngularVelocities**](classastrea_1_1astro_1_1AngularVelocities.md) that is the interpolation of this sequence and the other at the target time. 





        

<hr>



### function operator\* 

_Scalar multiplication operator for_ [_**AngularVelocities**_](classastrea_1_1astro_1_1AngularVelocities.md) _by a quantity, resulting in an_[_**CartesianVector**_](structastrea_1_1astro_1_1CartesianVector.md) _._
```C++
template<typename  Value_U>
inline CartesianVector < decltype ( AngularVelocity {} * Value_U {}), in_frame > astrea::astro::AngularVelocities::operator* (
    const  Value_U & scalar
) const
```





**Parameters:**


* `scalar` The quantity to multiply by. 



**Returns:**

[**CartesianVector**](structastrea_1_1astro_1_1CartesianVector.md)&lt;decltype(AngularVelocity{} \* Value\_U{}), in\_frame&gt; A new [**CartesianVector**](structastrea_1_1astro_1_1CartesianVector.md) that is the product of this sequence and the quantity. 





        

<hr>



### function operator\* 

_Scalar multiplication operator for_ [_**AngularVelocities**_](classastrea_1_1astro_1_1AngularVelocities.md) _by a Time quantity, resulting in an_[_**EulerAngles**_](classastrea_1_1astro_1_1EulerAngles.md) _._
```C++
template<RotationSequence sequence, RotationType rotation_type>
inline EulerAngles < sequence, rotation_type , in_frame, ref_frame > astrea::astro::AngularVelocities::operator* (
    const  Time & time
) const
```





**Parameters:**


* `time` The time quantity to multiply by. 



**Returns:**

EulerAngles&lt;sequence, rotation\_type, in\_frame, ref\_frame&gt; A new [**EulerAngles**](classastrea_1_1astro_1_1EulerAngles.md) that is the product of this sequence and the time. 





        

<hr>



### function operator\* 

_Scalar multiplication operator for_ [_**AngularVelocities**_](classastrea_1_1astro_1_1AngularVelocities.md) _by a quantity, resulting in an_[_**AngularVelocities**_](classastrea_1_1astro_1_1AngularVelocities.md) _._
```C++
inline AngularVelocities astrea::astro::AngularVelocities::operator* (
    const  Unitless & scale
) const
```





**Parameters:**


* `scale` The quantity to multiply by. 



**Returns:**

[**AngularVelocities**](classastrea_1_1astro_1_1AngularVelocities.md) A new [**AngularVelocities**](classastrea_1_1astro_1_1AngularVelocities.md) that is the product of this sequence and the quantity. 





        

<hr>



### function operator\*= 

_Scalar multiplication assignment operator for_ [_**AngularVelocities**_](classastrea_1_1astro_1_1AngularVelocities.md) _by a quantity._
```C++
inline AngularVelocities & astrea::astro::AngularVelocities::operator*= (
    const  Unitless & scale
) 
```





**Parameters:**


* `scale` The quantity to multiply by. 



**Returns:**

[**AngularVelocities**](classastrea_1_1astro_1_1AngularVelocities.md)& Reference to the current object after multiplication. 





        

<hr>



### function operator+ 

_Addition operator for_ [_**CartesianVector**_](structastrea_1_1astro_1_1CartesianVector.md) _._
```C++
inline CartesianVector < AngularVelocity , in_frame > astrea::astro::AngularVelocities::operator+ (
    const  CartesianVector < AngularVelocity , in_frame > & other
) const
```





**Parameters:**


* `other` The other [**CartesianVector**](structastrea_1_1astro_1_1CartesianVector.md) to add. 



**Returns:**

[**CartesianVector&lt;AngularVelocity, in\_frame&gt;**](structastrea_1_1astro_1_1CartesianVector.md) A new [**CartesianVector**](structastrea_1_1astro_1_1CartesianVector.md) that is the sum of this sequence and the other. 





        

<hr>



### function operator+ 

_Addition operator for_ [_**CartesianVector**_](structastrea_1_1astro_1_1CartesianVector.md) _._
```C++
inline AngularVelocities astrea::astro::AngularVelocities::operator+ (
    const  AngularVelocities & other
) const
```





**Parameters:**


* `other` The other [**AngularVelocities**](classastrea_1_1astro_1_1AngularVelocities.md) to add. 



**Returns:**

[**AngularVelocities**](classastrea_1_1astro_1_1AngularVelocities.md) A new [**AngularVelocities**](classastrea_1_1astro_1_1AngularVelocities.md) that is the sum of this sequence and the other. 





        

<hr>



### function operator+= 

_Addition assignment operator for_ [_**AngularVelocities**_](classastrea_1_1astro_1_1AngularVelocities.md) _._
```C++
inline AngularVelocities & astrea::astro::AngularVelocities::operator+= (
    const  AngularVelocities & other
) 
```





**Parameters:**


* `other` The other [**AngularVelocities**](classastrea_1_1astro_1_1AngularVelocities.md) to add. 



**Returns:**

[**AngularVelocities**](classastrea_1_1astro_1_1AngularVelocities.md)& Reference to the current object after addition. 





        

<hr>



### function operator- 

_Unary negation operator for_ [_**AngularVelocities**_](classastrea_1_1astro_1_1AngularVelocities.md) _._
```C++
inline AngularVelocities astrea::astro::AngularVelocities::operator- () const
```





**Returns:**

[**AngularVelocities**](classastrea_1_1astro_1_1AngularVelocities.md) A new [**AngularVelocities**](classastrea_1_1astro_1_1AngularVelocities.md) that is the negation of this sequence. 





        

<hr>



### function operator- 

_Subtraction operator for_ [_**CartesianVector**_](structastrea_1_1astro_1_1CartesianVector.md) _._
```C++
inline CartesianVector < AngularVelocity , in_frame > astrea::astro::AngularVelocities::operator- (
    const  CartesianVector < AngularVelocity , in_frame > & other
) const
```





**Parameters:**


* `other` The other [**CartesianVector**](structastrea_1_1astro_1_1CartesianVector.md) to subtract. 



**Returns:**

[**CartesianVector&lt;AngularVelocity, in\_frame&gt;**](structastrea_1_1astro_1_1CartesianVector.md) [**CartesianVector**](structastrea_1_1astro_1_1CartesianVector.md) result of subtraction. 





        

<hr>



### function operator- 

_Subtraction operator for_ [_**AngularVelocities**_](classastrea_1_1astro_1_1AngularVelocities.md) _._
```C++
inline AngularVelocities astrea::astro::AngularVelocities::operator- (
    const  AngularVelocities & other
) const
```





**Parameters:**


* `other` The other [**AngularVelocities**](classastrea_1_1astro_1_1AngularVelocities.md) to subtract. 



**Returns:**

[**AngularVelocities**](classastrea_1_1astro_1_1AngularVelocities.md) A new [**AngularVelocities**](classastrea_1_1astro_1_1AngularVelocities.md) that is the difference of this sequence and the other. 





        

<hr>



### function operator-= 

_Subtraction assignment operator for_ [_**AngularVelocities**_](classastrea_1_1astro_1_1AngularVelocities.md) _._
```C++
inline AngularVelocities & astrea::astro::AngularVelocities::operator-= (
    const  AngularVelocities & other
) 
```





**Parameters:**


* `other` The other [**AngularVelocities**](classastrea_1_1astro_1_1AngularVelocities.md) to subtract. 



**Returns:**

[**AngularVelocities**](classastrea_1_1astro_1_1AngularVelocities.md)& Reference to the current object after subtraction. 





        

<hr>



### function operator/ 

_Scalar division operator for_ [_**AngularVelocities**_](classastrea_1_1astro_1_1AngularVelocities.md) _by a quantity, resulting in a_[_**CartesianVector**_](structastrea_1_1astro_1_1CartesianVector.md) _._
```C++
template<typename  Value_U>
inline CartesianVector < decltype ( AngularVelocity {}/ Value_U {}), in_frame > astrea::astro::AngularVelocities::operator/ (
    const  Value_U & scalar
) const
```





**Parameters:**


* `scalar` The quantity to divide by. 



**Returns:**

[**CartesianVector**](structastrea_1_1astro_1_1CartesianVector.md)&lt;decltype(AngularVelocity{} / Value\_U{}), in\_frame&gt; A new [**CartesianVector**](structastrea_1_1astro_1_1CartesianVector.md) that is the quotient of this sequence and the quantity. 





        

<hr>



### function operator/ 

_Scalar division operator for_ [_**AngularVelocities**_](classastrea_1_1astro_1_1AngularVelocities.md) _by a Time quantity, resulting in an_[_**AngularAccelerations**_](classastrea_1_1astro_1_1AngularAccelerations.md) _._
```C++
inline AngularAccelerations < in_frame, ref_frame > astrea::astro::AngularVelocities::operator/ (
    const  Time & time
) const
```





**Parameters:**


* `time` The time quantity to divide by. 



**Returns:**

AngularAccelerations&lt;in\_frame, ref\_frame&gt; A new [**AngularAccelerations**](classastrea_1_1astro_1_1AngularAccelerations.md) that is the quotient of this sequence and the time. 





        

<hr>



### function operator/ 

_Scalar division operator for_ [_**AngularVelocities**_](classastrea_1_1astro_1_1AngularVelocities.md) _by a quantity, resulting in an_[_**AngularVelocities**_](classastrea_1_1astro_1_1AngularVelocities.md) _._
```C++
inline AngularVelocities astrea::astro::AngularVelocities::operator/ (
    const  Unitless & scale
) const
```





**Parameters:**


* `scale` The quantity to divide by. 



**Returns:**

[**AngularVelocities**](classastrea_1_1astro_1_1AngularVelocities.md) A new [**AngularVelocities**](classastrea_1_1astro_1_1AngularVelocities.md) that is the quotient of this sequence and the quantity. 





        

<hr>



### function operator/= 

_Scalar division assignment operator for_ [_**AngularVelocities**_](classastrea_1_1astro_1_1AngularVelocities.md) _by a quantity._
```C++
inline AngularVelocities & astrea::astro::AngularVelocities::operator/= (
    const  Unitless & scale
) 
```





**Parameters:**


* `scale` The quantity to divide by. 



**Returns:**

[**AngularVelocities**](classastrea_1_1astro_1_1AngularVelocities.md)& Reference to the current object after division. 





        

<hr>



### function operator= 

```C++
AngularVelocities & astrea::astro::AngularVelocities::operator= (
    const  AngularVelocities & other
) = default
```




<hr>



### function operator= 

```C++
AngularVelocities & astrea::astro::AngularVelocities::operator= (
    AngularVelocities && other
) = default
```




<hr>



### function operator== 

```C++
inline bool astrea::astro::AngularVelocities::operator== (
    const  AngularVelocities & other
) const
```




<hr>



### function operator== 

```C++
template<auto in_frame_u, auto ref_frame_u>
inline bool astrea::astro::AngularVelocities::operator== (
    const  AngularVelocities < in_frame_u , ref_frame_u > &
) const
```




<hr>



### function operator[] 

_Array access operator for accessing individual angular velocity components._ 
```C++
inline AngularVelocity & astrea::astro::AngularVelocities::operator[] (
    std::size_t index
) 
```





**Parameters:**


* `index` The index of the angular velocity component (0, 1, or 2). 



**Returns:**

AngularVelocity& Reference to the angular velocity component. 





        

<hr>



### function operator[] 

_Const array access operator for accessing individual angular velocity components._ 
```C++
inline const  AngularVelocity & astrea::astro::AngularVelocities::operator[] (
    std::size_t index
) const
```





**Parameters:**


* `index` The index of the angular velocity component (0, 1, or 2). 



**Returns:**

const AngularVelocity& Const reference to the angular velocity component. 





        

<hr>

------------------------------
The documentation for this class was generated from the following file `astrea/astro/astro/state/attitude/AngularVelocities.hpp`

