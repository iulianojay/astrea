

# Class astrea::astro::Attitude



[**ClassList**](annotated.md) **>** [**astrea**](namespaceastrea.md) **>** [**astro**](namespaceastrea_1_1astro.md) **>** [**Attitude**](classastrea_1_1astro_1_1Attitude.md)



_Class representing a set of orientation._ [More...](#detailed-description)

* `#include <Attitude.hpp>`





































## Public Functions

| Type | Name |
| ---: | :--- |
|   | [**Attitude**](#function-attitude-13) () = default<br>_Default constructor initializing to Cartesian&lt;frames::earth::icrf&gt; orientation._  |
|   | [**Attitude**](#function-attitude-23) ([**const**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) [**BodyQuaternion**](namespaceastrea_1_1astro.md#typedef-bodyquaternion) & orientation, [**const**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) [**BodyAngleVelocities**](namespaceastrea_1_1astro.md#typedef-bodyanglevelocities) & angularVelocity) <br>_Constructor initializing with_ [_**Quaternion**_](classastrea_1_1astro_1_1Quaternion.md) _orientation._ |
|   | [**Attitude**](#function-attitude-33) ([**const**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) [**EulerAngles**](classastrea_1_1astro_1_1EulerAngles.md)&lt; sequence, [**rotationType**](classastrea_1_1astro_1_1DirectionCosineMatrix.md), [**frames::dynamic::body**](structastrea_1_1astro_1_1frames_1_1dynamic_1_1body.md), [**frames::earth::icrf**](structastrea_1_1astro_1_1frames_1_1earth_1_1icrf.md) &gt; & angleSequence, [**const**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) [**BodyAngleVelocities**](namespaceastrea_1_1astro.md#typedef-bodyanglevelocities) & angleSequenceVelocity) <br>_Constructor initializing with_ [_**EulerAngles**_](classastrea_1_1astro_1_1EulerAngles.md) _orientation._ |
|  std::vector&lt; [**Unitless**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) &gt; | [**force\_to\_vector**](#function-force_to_vector) () const<br>_Converts the_ [_**Attitude**_](classastrea_1_1astro_1_1Attitude.md) _to a vector of Unitless values._ |
|  [**const**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) [**BodyAngleVelocities**](namespaceastrea_1_1astro.md#typedef-bodyanglevelocities) & | [**get\_angular\_velocity**](#function-get_angular_velocity) () const<br>_Gets the angular velocity as a BodyAngleVelocities._  |
|  [**const**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) [**BodyQuaternion**](namespaceastrea_1_1astro.md#typedef-bodyquaternion) & | [**get\_orientation**](#function-get_orientation) () const<br>_Gets the orientation as a BodyQuaternion._  |
|  [**Attitude**](classastrea_1_1astro_1_1Attitude.md) | [**interpolate**](#function-interpolate) ([**const**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) [**Time**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) & thisTime, [**const**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) [**Time**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) & otherTime, [**const**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) [**Attitude**](classastrea_1_1astro_1_1Attitude.md) & other, [**const**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) [**Time**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) & targetTime) const<br>_Interpolates between two_ [_**Attitude**_](classastrea_1_1astro_1_1Attitude.md) _at a given time._ |
|  [**Attitude**](classastrea_1_1astro_1_1Attitude.md) | [**operator\***](#function-operator) ([**const**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) [**Unitless**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) & multiplier) const<br>_Multiplies the_ [_**Attitude**_](classastrea_1_1astro_1_1Attitude.md) _by a scalar._ |
|  [**Attitude**](classastrea_1_1astro_1_1Attitude.md) & | [**operator\*=**](#function-operator_1) ([**const**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) [**Unitless**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) & multiplier) <br>_Multiplies the_ [_**Attitude**_](classastrea_1_1astro_1_1Attitude.md) _by a scalar._ |
|  [**Attitude**](classastrea_1_1astro_1_1Attitude.md) | [**operator+**](#function-operator_2) ([**const**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) [**Attitude**](classastrea_1_1astro_1_1Attitude.md) & other) const<br>_Adds two_ [_**Attitude**_](classastrea_1_1astro_1_1Attitude.md) _objects._ |
|  [**Attitude**](classastrea_1_1astro_1_1Attitude.md) & | [**operator+=**](#function-operator_3) ([**const**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) [**Attitude**](classastrea_1_1astro_1_1Attitude.md) & other) <br>_Adds another_ [_**Attitude**_](classastrea_1_1astro_1_1Attitude.md) _object to the current one._ |
|  [**Attitude**](classastrea_1_1astro_1_1Attitude.md) | [**operator-**](#function-operator-) ([**const**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) [**Attitude**](classastrea_1_1astro_1_1Attitude.md) & other) const<br>_Subtracts another_ [_**Attitude**_](classastrea_1_1astro_1_1Attitude.md) _object from the current one._ |
|  [**Attitude**](classastrea_1_1astro_1_1Attitude.md) & | [**operator-=**](#function-operator-_1) ([**const**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) [**Attitude**](classastrea_1_1astro_1_1Attitude.md) & other) <br>_Subtracts another_ [_**Attitude**_](classastrea_1_1astro_1_1Attitude.md) _object from the current one._ |
|  [**AttitudePartials**](classastrea_1_1astro_1_1AttitudePartials.md) | [**operator/**](#function-operator_4) ([**const**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) [**Time**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) & divisor) const<br>_Divides the_ [_**Attitude**_](classastrea_1_1astro_1_1Attitude.md) _by a time._ |
|  [**Attitude**](classastrea_1_1astro_1_1Attitude.md) | [**operator/**](#function-operator_5) ([**const**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) [**Unitless**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) & divisor) const<br>_Divides the_ [_**Attitude**_](classastrea_1_1astro_1_1Attitude.md) _by a scalar._ |
|  [**Attitude**](classastrea_1_1astro_1_1Attitude.md) & | [**operator/=**](#function-operator_6) ([**const**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) [**Unitless**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) & divisor) <br>_Divides the_ [_**Attitude**_](classastrea_1_1astro_1_1Attitude.md) _by a scalar._ |
|  [**bool**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) | [**operator==**](#function-operator_7) ([**const**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) [**Attitude**](classastrea_1_1astro_1_1Attitude.md) & other) const<br>_Compares two_ [_**Attitude**_](classastrea_1_1astro_1_1Attitude.md) _objects for equality._ |




























## Detailed Description


This class encapsulates different types of orientation ([**EulerAngles**](classastrea_1_1astro_1_1EulerAngles.md), [**EulerAngles**](classastrea_1_1astro_1_1EulerAngles.md), [**Quaternion**](classastrea_1_1astro_1_1Quaternion.md)) and provides methods for conversion, interpolation, and mathematical operations. 


    
## Public Functions Documentation




### function Attitude [1/3]

_Default constructor initializing to Cartesian&lt;frames::earth::icrf&gt; orientation._ 
```C++
astrea::astro::Attitude::Attitude () = default
```




<hr>



### function Attitude [2/3]

_Constructor initializing with_ [_**Quaternion**_](classastrea_1_1astro_1_1Quaternion.md) _orientation._
```C++
astrea::astro::Attitude::Attitude (
    const  BodyQuaternion & orientation,
    const  BodyAngleVelocities & angularVelocity
) 
```





**Parameters:**


* `orientation` The orientation to initialize with. 




        

<hr>



### function Attitude [3/3]

_Constructor initializing with_ [_**EulerAngles**_](classastrea_1_1astro_1_1EulerAngles.md) _orientation._
```C++
template<RotationSequence sequence, RotationType rotationType>
inline astrea::astro::Attitude::Attitude (
    const  EulerAngles < sequence, rotationType , frames::dynamic::body , frames::earth::icrf > & angleSequence,
    const  BodyAngleVelocities & angleSequenceVelocity
) 
```





**Parameters:**


* `orientation` The orientation to initialize with. 




        

<hr>



### function force\_to\_vector 

_Converts the_ [_**Attitude**_](classastrea_1_1astro_1_1Attitude.md) _to a vector of Unitless values._
```C++
std::vector< Unitless > astrea::astro::Attitude::force_to_vector () const
```





**Returns:**

std::vector&lt;Unitless&gt; Vector containing the orientation as unitless values. 





        

<hr>



### function get\_angular\_velocity 

_Gets the angular velocity as a BodyAngleVelocities._ 
```C++
inline const  BodyAngleVelocities & astrea::astro::Attitude::get_angular_velocity () const
```





**Returns:**

const BodyAngleVelocities& The angular velocity as a BodyAngleVelocities. 





        

<hr>



### function get\_orientation 

_Gets the orientation as a BodyQuaternion._ 
```C++
inline const  BodyQuaternion & astrea::astro::Attitude::get_orientation () const
```





**Returns:**

const BodyQuaternion& The orientation as a BodyQuaternion. 





        

<hr>



### function interpolate 

_Interpolates between two_ [_**Attitude**_](classastrea_1_1astro_1_1Attitude.md) _at a given time._
```C++
Attitude astrea::astro::Attitude::interpolate (
    const  Time & thisTime,
    const  Time & otherTime,
    const  Attitude & other,
    const  Time & targetTime
) const
```





**Parameters:**


* `thisTime` Time of the current state 
* `otherTime` Time of the other state 
* `other` Another [**Attitude**](classastrea_1_1astro_1_1Attitude.md) object to interpolate with 
* `targetTime` The target time for interpolation 



**Returns:**

Interpolated [**Attitude**](classastrea_1_1astro_1_1Attitude.md) at the target time. 





        

<hr>



### function operator\* 

_Multiplies the_ [_**Attitude**_](classastrea_1_1astro_1_1Attitude.md) _by a scalar._
```C++
Attitude astrea::astro::Attitude::operator* (
    const  Unitless & multiplier
) const
```





**Parameters:**


* `multiplier` Scalar value to multiply with 



**Returns:**

Resultant [**Attitude**](classastrea_1_1astro_1_1Attitude.md) after multiplication. 





        

<hr>



### function operator\*= 

_Multiplies the_ [_**Attitude**_](classastrea_1_1astro_1_1Attitude.md) _by a scalar._
```C++
Attitude & astrea::astro::Attitude::operator*= (
    const  Unitless & multiplier
) 
```





**Parameters:**


* `multiplier` Scalar value to multiply with 



**Returns:**

Reference to the current [**Attitude**](classastrea_1_1astro_1_1Attitude.md) object after multiplication. 





        

<hr>



### function operator+ 

_Adds two_ [_**Attitude**_](classastrea_1_1astro_1_1Attitude.md) _objects._
```C++
Attitude astrea::astro::Attitude::operator+ (
    const  Attitude & other
) const
```





**Parameters:**


* `other` Another [**Attitude**](classastrea_1_1astro_1_1Attitude.md) object 



**Returns:**

Resultant [**Attitude**](classastrea_1_1astro_1_1Attitude.md) sum. 





        

<hr>



### function operator+= 

_Adds another_ [_**Attitude**_](classastrea_1_1astro_1_1Attitude.md) _object to the current one._
```C++
Attitude & astrea::astro::Attitude::operator+= (
    const  Attitude & other
) 
```





**Parameters:**


* `other` Another [**Attitude**](classastrea_1_1astro_1_1Attitude.md) object 



**Returns:**

Reference to the current [**Attitude**](classastrea_1_1astro_1_1Attitude.md) object after addition. 





        

<hr>



### function operator- 

_Subtracts another_ [_**Attitude**_](classastrea_1_1astro_1_1Attitude.md) _object from the current one._
```C++
Attitude astrea::astro::Attitude::operator- (
    const  Attitude & other
) const
```





**Parameters:**


* `other` Another [**Attitude**](classastrea_1_1astro_1_1Attitude.md) object 



**Returns:**

Resultant [**Attitude**](classastrea_1_1astro_1_1Attitude.md) difference. 





        

<hr>



### function operator-= 

_Subtracts another_ [_**Attitude**_](classastrea_1_1astro_1_1Attitude.md) _object from the current one._
```C++
Attitude & astrea::astro::Attitude::operator-= (
    const  Attitude & other
) 
```





**Parameters:**


* `other` Another [**Attitude**](classastrea_1_1astro_1_1Attitude.md) object 



**Returns:**

Reference to the current [**Attitude**](classastrea_1_1astro_1_1Attitude.md) object after subtraction. 





        

<hr>



### function operator/ 

_Divides the_ [_**Attitude**_](classastrea_1_1astro_1_1Attitude.md) _by a time._
```C++
AttitudePartials astrea::astro::Attitude::operator/ (
    const  Time & divisor
) const
```





**Parameters:**


* `divisor` Time value to divide by 



**Returns:**

Resultant [**AttitudePartials**](classastrea_1_1astro_1_1AttitudePartials.md) after division. 





        

<hr>



### function operator/ 

_Divides the_ [_**Attitude**_](classastrea_1_1astro_1_1Attitude.md) _by a scalar._
```C++
Attitude astrea::astro::Attitude::operator/ (
    const  Unitless & divisor
) const
```





**Parameters:**


* `divisor` Scalar value to divide with 



**Returns:**

Resultant [**Attitude**](classastrea_1_1astro_1_1Attitude.md) after division. 





        

<hr>



### function operator/= 

_Divides the_ [_**Attitude**_](classastrea_1_1astro_1_1Attitude.md) _by a scalar._
```C++
Attitude & astrea::astro::Attitude::operator/= (
    const  Unitless & divisor
) 
```





**Parameters:**


* `divisor` Scalar value to divide with 



**Returns:**

Reference to the current [**Attitude**](classastrea_1_1astro_1_1Attitude.md) object after division. 





        

<hr>



### function operator== 

_Compares two_ [_**Attitude**_](classastrea_1_1astro_1_1Attitude.md) _objects for equality._
```C++
bool astrea::astro::Attitude::operator== (
    const  Attitude & other
) const
```





**Parameters:**


* `other` Another [**Attitude**](classastrea_1_1astro_1_1Attitude.md) object to compare with. 



**Returns:**

true if the two [**Attitude**](classastrea_1_1astro_1_1Attitude.md) objects are equal 




**Returns:**

false if the two [**Attitude**](classastrea_1_1astro_1_1Attitude.md) objects are not equal 





        

<hr>

------------------------------
The documentation for this class was generated from the following file `astrea/astro/astro/state/attitude/Attitude.hpp`

