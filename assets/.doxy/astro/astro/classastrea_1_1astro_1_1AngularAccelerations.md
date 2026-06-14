

# Class astrea::astro::AngularAccelerations

**template &lt;IsFrame [**auto**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) \_in\_frame\_, IsFrame [**auto**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) \_ref\_frame\_&gt;**



[**ClassList**](annotated.md) **>** [**astrea**](namespaceastrea.md) **>** [**astro**](namespaceastrea_1_1astro.md) **>** [**AngularAccelerations**](classastrea_1_1astro_1_1AngularAccelerations.md)



_Class representing the angular sequence acceleration, which is the time derivative of the angular sequence velocity._ [More...](#detailed-description)

* `#include <AngularVelocities.hpp>`























## Public Static Attributes

| Type | Name |
| ---: | :--- |
|  [**constexpr**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) [**auto**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) | [**in\_frame**](#variable-in_frame)   = `[**\_in\_frame\_**](classastrea_1_1astro_1_1DirectionCosineMatrix.md)`<br> |
|  [**constexpr**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) [**auto**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) | [**ref\_frame**](#variable-ref_frame)   = `[**\_ref\_frame\_**](classastrea_1_1astro_1_1DirectionCosineMatrix.md)`<br> |














## Public Functions

| Type | Name |
| ---: | :--- |
|   | [**AngularAccelerations**](#function-angularaccelerations-13) () = default<br>_Default constructor for the_ [_**AngularAccelerations**_](classastrea_1_1astro_1_1AngularAccelerations.md) _class. Initializes all angular accelerations to zero._ |
|   | [**AngularAccelerations**](#function-angularaccelerations-23) ([**const**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) [**AngularAcceleration**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) & accel1, [**const**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) [**AngularAcceleration**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) & accel2, [**const**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) [**AngularAcceleration**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) & accel3) <br>_Constructor for the_ [_**AngularAccelerations**_](classastrea_1_1astro_1_1AngularAccelerations.md) _class from three angular accelerations._ |
|   | [**AngularAccelerations**](#function-angularaccelerations-33) ([**const**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) [**CartesianVector**](structastrea_1_1astro_1_1CartesianVector.md)&lt; [**AngularAcceleration**](classastrea_1_1astro_1_1DirectionCosineMatrix.md), in\_frame &gt; & accels) <br>_Constructor for the_ [_**AngularAccelerations**_](classastrea_1_1astro_1_1AngularAccelerations.md) _class from a_[_**CartesianVector**_](structastrea_1_1astro_1_1CartesianVector.md) _of angular accelerations._ |
|  [**CartesianVector**](structastrea_1_1astro_1_1CartesianVector.md)&lt; [**decltype**](classastrea_1_1astro_1_1DirectionCosineMatrix.md)([**AngularAcceleration**](classastrea_1_1astro_1_1DirectionCosineMatrix.md){} \*[**Value\_U**](classastrea_1_1astro_1_1DirectionCosineMatrix.md){}), in\_frame &gt; | [**cross**](#function-cross-12) ([**const**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) [**CartesianVector**](structastrea_1_1astro_1_1CartesianVector.md)&lt; [**Value\_U**](classastrea_1_1astro_1_1DirectionCosineMatrix.md), in\_frame &gt; & other) const<br>_Cross product of this angular acceleration vector with a_ [_**CartesianVector**_](structastrea_1_1astro_1_1CartesianVector.md) _._ |
|  [**CartesianVector**](structastrea_1_1astro_1_1CartesianVector.md)&lt; [**decltype**](classastrea_1_1astro_1_1DirectionCosineMatrix.md)([**AngularAcceleration**](classastrea_1_1astro_1_1DirectionCosineMatrix.md){} \*[**AngularAcceleration**](classastrea_1_1astro_1_1DirectionCosineMatrix.md){}), in\_frame &gt; | [**cross**](#function-cross-22) ([**const**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) [**AngularAccelerations**](classastrea_1_1astro_1_1AngularAccelerations.md)&lt; in\_frame, ref\_frame &gt; & other) const<br>_Cross product of this angle vector with another_ [_**AngularAccelerations**_](classastrea_1_1astro_1_1AngularAccelerations.md) _._ |
|  [**auto**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) | [**dot**](#function-dot-12) ([**const**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) [**CartesianVector**](structastrea_1_1astro_1_1CartesianVector.md)&lt; [**Value\_U**](classastrea_1_1astro_1_1DirectionCosineMatrix.md), in\_frame &gt; & other) const<br>_Dot product of this angular acceleration vector with a_ [_**CartesianVector**_](structastrea_1_1astro_1_1CartesianVector.md) _._ |
|  [**auto**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) | [**dot**](#function-dot-22) ([**const**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) [**AngularAccelerations**](classastrea_1_1astro_1_1AngularAccelerations.md)&lt; in\_frame, ref\_frame &gt; & other) const<br>_Dot product of this angle vector with another_ [_**AngularAccelerations**_](classastrea_1_1astro_1_1AngularAccelerations.md) _._ |
|  std::vector&lt; [**Unitless**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) &gt; | [**force\_to\_vector**](#function-force_to_vector) () const<br>_Converts the angular sequence acceleration to a vector form for use in numerical integration._  |
|  [**CartesianVector**](structastrea_1_1astro_1_1CartesianVector.md)&lt; [**AngularAcceleration**](classastrea_1_1astro_1_1DirectionCosineMatrix.md), in\_frame &gt; & | [**get\_angularAccels**](#function-get_angularaccels-12) () <br>_Get access to the underlying_ [_**CartesianVector**_](structastrea_1_1astro_1_1CartesianVector.md) _._ |
|  [**const**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) [**CartesianVector**](structastrea_1_1astro_1_1CartesianVector.md)&lt; [**AngularAcceleration**](classastrea_1_1astro_1_1DirectionCosineMatrix.md), in\_frame &gt; & | [**get\_angularAccels**](#function-get_angularaccels-22) () const<br>_Get const access to the underlying_ [_**CartesianVector**_](structastrea_1_1astro_1_1CartesianVector.md) _._ |
|  [**CartesianVector**](structastrea_1_1astro_1_1CartesianVector.md)&lt; [**decltype**](classastrea_1_1astro_1_1DirectionCosineMatrix.md)([**AngularAcceleration**](classastrea_1_1astro_1_1DirectionCosineMatrix.md){} \*[**Value\_U**](classastrea_1_1astro_1_1DirectionCosineMatrix.md){}), in\_frame &gt; | [**operator\***](#function-operator) ([**const**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) [**Value\_U**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) & scalar) const<br>_Scalar multiplication operator for_ [_**AngularAccelerations**_](classastrea_1_1astro_1_1AngularAccelerations.md) _by a quantity, resulting in a_[_**CartesianVector**_](structastrea_1_1astro_1_1CartesianVector.md) _._ |
|  [**AngularVelocities**](classastrea_1_1astro_1_1AngularVelocities.md)&lt; in\_frame, ref\_frame &gt; | [**operator\***](#function-operator_1) ([**const**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) [**Time**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) & time) const<br>_Scalar multiplication operator for_ [_**AngularAccelerations**_](classastrea_1_1astro_1_1AngularAccelerations.md) _._ |
|  [**AngularAccelerations**](classastrea_1_1astro_1_1AngularAccelerations.md)&lt; in\_frame, ref\_frame &gt; | [**operator+**](#function-operator_2) ([**const**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) [**AngularAccelerations**](classastrea_1_1astro_1_1AngularAccelerations.md)&lt; in\_frame, ref\_frame &gt; & other) const<br>_Addition operator for_ [_**AngularAccelerations**_](classastrea_1_1astro_1_1AngularAccelerations.md) _._ |
|  [**AngularAccelerations**](classastrea_1_1astro_1_1AngularAccelerations.md)&lt; in\_frame, ref\_frame &gt; & | [**operator+=**](#function-operator_3) ([**const**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) [**AngularAccelerations**](classastrea_1_1astro_1_1AngularAccelerations.md)&lt; in\_frame, ref\_frame &gt; & other) <br>_Addition assignment operator for_ [_**AngularAccelerations**_](classastrea_1_1astro_1_1AngularAccelerations.md) _._ |
|  [**AngularAccelerations**](classastrea_1_1astro_1_1AngularAccelerations.md)&lt; in\_frame, ref\_frame &gt; | [**operator-**](#function-operator-) ([**const**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) [**AngularAccelerations**](classastrea_1_1astro_1_1AngularAccelerations.md)&lt; in\_frame, ref\_frame &gt; & other) const<br>_Subtraction operator for_ [_**AngularAccelerations**_](classastrea_1_1astro_1_1AngularAccelerations.md) _._ |
|  [**AngularAccelerations**](classastrea_1_1astro_1_1AngularAccelerations.md)&lt; in\_frame, ref\_frame &gt; & | [**operator-=**](#function-operator-_1) ([**const**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) [**AngularAccelerations**](classastrea_1_1astro_1_1AngularAccelerations.md)&lt; in\_frame, ref\_frame &gt; & other) <br>_Subtraction assignment operator for_ [_**AngularAccelerations**_](classastrea_1_1astro_1_1AngularAccelerations.md) _._ |
|  [**CartesianVector**](structastrea_1_1astro_1_1CartesianVector.md)&lt; [**decltype**](classastrea_1_1astro_1_1DirectionCosineMatrix.md)([**AngularAcceleration**](classastrea_1_1astro_1_1DirectionCosineMatrix.md){}/[**Value\_U**](classastrea_1_1astro_1_1DirectionCosineMatrix.md){}), in\_frame &gt; | [**operator/**](#function-operator_4) ([**const**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) [**Value\_U**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) & scalar) const<br>_Scalar division operator for_ [_**AngularAccelerations**_](classastrea_1_1astro_1_1AngularAccelerations.md) _by a quantity, resulting in a_[_**CartesianVector**_](structastrea_1_1astro_1_1CartesianVector.md) _._ |
|  [**AngularAcceleration**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) & | [**operator[]**](#function-operator_5) (std::size\_t index) <br>_Array access operator for accessing individual angular acceleration components._  |
|  [**const**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) [**AngularAcceleration**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) & | [**operator[]**](#function-operator_6) (std::size\_t index) const<br>_Const array access operator for accessing individual angular acceleration components._  |




























## Detailed Description




**Template parameters:**


* `in_frame` The input frame type (e.g., ECI, ECEF). 
* `ref_frame` The output frame type (e.g., ECI, ECEF). 




    
## Public Static Attributes Documentation




### variable in\_frame 

```C++
constexpr auto astrea::astro::AngularAccelerations< _in_frame_, _ref_frame_ >::in_frame;
```




<hr>



### variable ref\_frame 

```C++
constexpr auto astrea::astro::AngularAccelerations< _in_frame_, _ref_frame_ >::ref_frame;
```




<hr>
## Public Functions Documentation




### function AngularAccelerations [1/3]

_Default constructor for the_ [_**AngularAccelerations**_](classastrea_1_1astro_1_1AngularAccelerations.md) _class. Initializes all angular accelerations to zero._
```C++
astrea::astro::AngularAccelerations::AngularAccelerations () = default
```




<hr>



### function AngularAccelerations [2/3]

_Constructor for the_ [_**AngularAccelerations**_](classastrea_1_1astro_1_1AngularAccelerations.md) _class from three angular accelerations._
```C++
inline astrea::astro::AngularAccelerations::AngularAccelerations (
    const  AngularAcceleration & accel1,
    const  AngularAcceleration & accel2,
    const  AngularAcceleration & accel3
) 
```





**Parameters:**


* `accel1` The first angular acceleration in the sequence. 
* `accel2` The second angular acceleration in the sequence. 
* `accel3` The third angular acceleration in the sequence. 




        

<hr>



### function AngularAccelerations [3/3]

_Constructor for the_ [_**AngularAccelerations**_](classastrea_1_1astro_1_1AngularAccelerations.md) _class from a_[_**CartesianVector**_](structastrea_1_1astro_1_1CartesianVector.md) _of angular accelerations._
```C++
inline astrea::astro::AngularAccelerations::AngularAccelerations (
    const  CartesianVector < AngularAcceleration , in_frame > & accels
) 
```





**Parameters:**


* `accels` A [**CartesianVector**](structastrea_1_1astro_1_1CartesianVector.md) containing the three angular accelerations in the sequence. 




        

<hr>



### function cross [1/2]

_Cross product of this angular acceleration vector with a_ [_**CartesianVector**_](structastrea_1_1astro_1_1CartesianVector.md) _._
```C++
template<typename  Value_U>
inline CartesianVector < decltype ( AngularAcceleration {} * Value_U {}), in_frame > astrea::astro::AngularAccelerations::cross (
    const  CartesianVector < Value_U , in_frame > & other
) const
```





**Template parameters:**


* `Value_U` The type of the [**CartesianVector**](structastrea_1_1astro_1_1CartesianVector.md)'s components. 



**Parameters:**


* `other` The [**CartesianVector**](structastrea_1_1astro_1_1CartesianVector.md) to take the cross product with. 



**Returns:**

[**CartesianVector**](structastrea_1_1astro_1_1CartesianVector.md)&lt;decltype(AngularAcceleration{} \* Value\_U{}), in\_frame&gt; The resulting [**CartesianVector**](structastrea_1_1astro_1_1CartesianVector.md) from the cross product. 





        

<hr>



### function cross [2/2]

_Cross product of this angle vector with another_ [_**AngularAccelerations**_](classastrea_1_1astro_1_1AngularAccelerations.md) _._
```C++
inline CartesianVector < decltype ( AngularAcceleration {} * AngularAcceleration {}), in_frame > astrea::astro::AngularAccelerations::cross (
    const  AngularAccelerations < in_frame, ref_frame > & other
) const
```





**Parameters:**


* `other` The other [**AngularAccelerations**](classastrea_1_1astro_1_1AngularAccelerations.md) to take the cross product with. 



**Returns:**

[**CartesianVector**](structastrea_1_1astro_1_1CartesianVector.md)&lt;decltype(AngularAcceleration{} \* AngularAcceleration{}), in\_frame&gt; The resulting [**CartesianVector**](structastrea_1_1astro_1_1CartesianVector.md) from the cross product. 





        

<hr>



### function dot [1/2]

_Dot product of this angular acceleration vector with a_ [_**CartesianVector**_](structastrea_1_1astro_1_1CartesianVector.md) _._
```C++
template<typename  Value_U>
inline auto astrea::astro::AngularAccelerations::dot (
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

_Dot product of this angle vector with another_ [_**AngularAccelerations**_](classastrea_1_1astro_1_1AngularAccelerations.md) _._
```C++
inline auto astrea::astro::AngularAccelerations::dot (
    const  AngularAccelerations < in_frame, ref_frame > & other
) const
```





**Parameters:**


* `other` The other [**AngularAccelerations**](classastrea_1_1astro_1_1AngularAccelerations.md) to take the dot product with. 



**Returns:**

auto The resulting scalar from the dot product. 





        

<hr>



### function force\_to\_vector 

_Converts the angular sequence acceleration to a vector form for use in numerical integration._ 
```C++
inline std::vector< Unitless > astrea::astro::AngularAccelerations::force_to_vector () const
```





**Returns:**

A std::vector of Unitless quantities representing the components of the angular sequence acceleration, in the order [first, second, third]. 





        

<hr>



### function get\_angularAccels [1/2]

_Get access to the underlying_ [_**CartesianVector**_](structastrea_1_1astro_1_1CartesianVector.md) _._
```C++
inline CartesianVector < AngularAcceleration , in_frame > & astrea::astro::AngularAccelerations::get_angularAccels () 
```





**Returns:**

[**CartesianVector&lt;AngularAcceleration, in\_frame&gt;**](structastrea_1_1astro_1_1CartesianVector.md)& Reference to the internal [**CartesianVector**](structastrea_1_1astro_1_1CartesianVector.md). 





        

<hr>



### function get\_angularAccels [2/2]

_Get const access to the underlying_ [_**CartesianVector**_](structastrea_1_1astro_1_1CartesianVector.md) _._
```C++
inline const  CartesianVector < AngularAcceleration , in_frame > & astrea::astro::AngularAccelerations::get_angularAccels () const
```





**Returns:**

const [**CartesianVector&lt;AngularAcceleration, in\_frame&gt;**](structastrea_1_1astro_1_1CartesianVector.md)& Const reference to the internal [**CartesianVector**](structastrea_1_1astro_1_1CartesianVector.md). 





        

<hr>



### function operator\* 

_Scalar multiplication operator for_ [_**AngularAccelerations**_](classastrea_1_1astro_1_1AngularAccelerations.md) _by a quantity, resulting in a_[_**CartesianVector**_](structastrea_1_1astro_1_1CartesianVector.md) _._
```C++
template<typename  Value_U>
inline CartesianVector < decltype ( AngularAcceleration {} * Value_U {}), in_frame > astrea::astro::AngularAccelerations::operator* (
    const  Value_U & scalar
) const
```





**Parameters:**


* `scalar` The quantity to multiply by. 



**Returns:**

[**CartesianVector**](structastrea_1_1astro_1_1CartesianVector.md)&lt;decltype(AngularAcceleration{} \* Value\_U{}), in\_frame&gt; A new [**CartesianVector**](structastrea_1_1astro_1_1CartesianVector.md) that is the product of this sequence and the quantity. 





        

<hr>



### function operator\* 

_Scalar multiplication operator for_ [_**AngularAccelerations**_](classastrea_1_1astro_1_1AngularAccelerations.md) _._
```C++
inline AngularVelocities < in_frame, ref_frame > astrea::astro::AngularAccelerations::operator* (
    const  Time & time
) const
```





**Parameters:**


* `time` The time value to multiply with. 



**Returns:**

AngularVelocities&lt;in\_frame, ref\_frame&gt; A new [**AngularVelocities**](classastrea_1_1astro_1_1AngularVelocities.md) that is the product of this sequence and the time 





        

<hr>



### function operator+ 

_Addition operator for_ [_**AngularAccelerations**_](classastrea_1_1astro_1_1AngularAccelerations.md) _._
```C++
inline AngularAccelerations < in_frame, ref_frame > astrea::astro::AngularAccelerations::operator+ (
    const  AngularAccelerations < in_frame, ref_frame > & other
) const
```





**Parameters:**


* `other` The other [**AngularAccelerations**](classastrea_1_1astro_1_1AngularAccelerations.md) to add. 



**Returns:**

AngularAccelerations&lt;in\_frame, ref\_frame&gt; A new [**AngularAccelerations**](classastrea_1_1astro_1_1AngularAccelerations.md) that is the sum of this and other. 





        

<hr>



### function operator+= 

_Addition assignment operator for_ [_**AngularAccelerations**_](classastrea_1_1astro_1_1AngularAccelerations.md) _._
```C++
inline AngularAccelerations < in_frame, ref_frame > & astrea::astro::AngularAccelerations::operator+= (
    const  AngularAccelerations < in_frame, ref_frame > & other
) 
```





**Parameters:**


* `other` The other [**AngularAccelerations**](classastrea_1_1astro_1_1AngularAccelerations.md) to add. 



**Returns:**

AngularAccelerations&lt;in\_frame, ref\_frame&gt;& Reference to the current object after addition. 





        

<hr>



### function operator- 

_Subtraction operator for_ [_**AngularAccelerations**_](classastrea_1_1astro_1_1AngularAccelerations.md) _._
```C++
inline AngularAccelerations < in_frame, ref_frame > astrea::astro::AngularAccelerations::operator- (
    const  AngularAccelerations < in_frame, ref_frame > & other
) const
```





**Parameters:**


* `other` The other [**AngularAccelerations**](classastrea_1_1astro_1_1AngularAccelerations.md) to subtract. 



**Returns:**

AngularAccelerations&lt;in\_frame, ref\_frame&gt; A new [**AngularAccelerations**](classastrea_1_1astro_1_1AngularAccelerations.md) that is the difference of this and other. 





        

<hr>



### function operator-= 

_Subtraction assignment operator for_ [_**AngularAccelerations**_](classastrea_1_1astro_1_1AngularAccelerations.md) _._
```C++
inline AngularAccelerations < in_frame, ref_frame > & astrea::astro::AngularAccelerations::operator-= (
    const  AngularAccelerations < in_frame, ref_frame > & other
) 
```





**Parameters:**


* `other` The other [**AngularAccelerations**](classastrea_1_1astro_1_1AngularAccelerations.md) to subtract. 



**Returns:**

AngularAccelerations&lt;in\_frame, ref\_frame&gt;& Reference to the current object after subtraction. 





        

<hr>



### function operator/ 

_Scalar division operator for_ [_**AngularAccelerations**_](classastrea_1_1astro_1_1AngularAccelerations.md) _by a quantity, resulting in a_[_**CartesianVector**_](structastrea_1_1astro_1_1CartesianVector.md) _._
```C++
template<typename  Value_U>
inline CartesianVector < decltype ( AngularAcceleration {}/ Value_U {}), in_frame > astrea::astro::AngularAccelerations::operator/ (
    const  Value_U & scalar
) const
```





**Parameters:**


* `scalar` The quantity to divide by. 



**Returns:**

[**CartesianVector**](structastrea_1_1astro_1_1CartesianVector.md)&lt;decltype(AngularAcceleration{} / Value\_U{}), in\_frame&gt; A new [**CartesianVector**](structastrea_1_1astro_1_1CartesianVector.md) that is the quotient of this sequence and the quantity. 





        

<hr>



### function operator[] 

_Array access operator for accessing individual angular acceleration components._ 
```C++
inline AngularAcceleration & astrea::astro::AngularAccelerations::operator[] (
    std::size_t index
) 
```





**Parameters:**


* `index` The index of the angular acceleration component (0, 1, or 2). 



**Returns:**

AngularAcceleration& Reference to the angular acceleration component. 





        

<hr>



### function operator[] 

_Const array access operator for accessing individual angular acceleration components._ 
```C++
inline const  AngularAcceleration & astrea::astro::AngularAccelerations::operator[] (
    std::size_t index
) const
```





**Parameters:**


* `index` The index of the angular acceleration component (0, 1, or 2). 



**Returns:**

const AngularAcceleration& Const reference to the angular acceleration component. 





        

<hr>

------------------------------
The documentation for this class was generated from the following file `astrea/astro/astro/state/attitude/AngularVelocities.hpp`

