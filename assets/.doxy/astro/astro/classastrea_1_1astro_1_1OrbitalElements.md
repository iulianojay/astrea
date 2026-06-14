

# Class astrea::astro::OrbitalElements



[**ClassList**](annotated.md) **>** [**astrea**](namespaceastrea.md) **>** [**astro**](namespaceastrea_1_1astro.md) **>** [**OrbitalElements**](classastrea_1_1astro_1_1OrbitalElements.md)



_Class representing a set of orbital elements._ [More...](#detailed-description)

* `#include <OrbitalElements.hpp>`





































## Public Functions

| Type | Name |
| ---: | :--- |
|   | [**OrbitalElements**](#function-orbitalelements-14) () <br>_Default constructor initializing to Cartesian&lt;frames::primary&gt; elements._  |
|   | [**OrbitalElements**](#function-orbitalelements-24) ([**Cartesian**](classastrea_1_1astro_1_1Cartesian.md)&lt; frame &gt; elements) <br>_Constructor initializing with Cartesian&lt;frame&gt; elements._  |
|   | [**OrbitalElements**](#function-orbitalelements-34) ([**Keplerian**](classastrea_1_1astro_1_1Keplerian.md)&lt; frame &gt; elements) <br>_Constructor initializing with Keplerian&lt;frame&gt; elements._  |
|   | [**OrbitalElements**](#function-orbitalelements-44) ([**Equinoctial**](classastrea_1_1astro_1_1Equinoctial.md)&lt; frame &gt; elements) <br>_Constructor initializing with Equinoctial&lt;frame&gt; elements._  |
|  [**OrbitalElements**](classastrea_1_1astro_1_1OrbitalElements.md) & | [**convert\_to\_set**](#function-convert_to_set-14) ([**const**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) std::size\_t idx, [**const**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) [**GravParam**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) & mu) <br>_Converts the current orbital elements to a specific type._  |
|  [**OrbitalElements**](classastrea_1_1astro_1_1OrbitalElements.md) | [**convert\_to\_set**](#function-convert_to_set-24) ([**const**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) std::size\_t idx, [**const**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) [**GravParam**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) & mu) const<br>_Converts the current orbital elements to a specific type._  |
|  [**OrbitalElements**](classastrea_1_1astro_1_1OrbitalElements.md) & | [**convert\_to\_set**](#function-convert_to_set-34) ([**const**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) [**GravParam**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) & mu) <br>_Converts the current orbital elements to a specific type._  |
|  [**OrbitalElements**](classastrea_1_1astro_1_1OrbitalElements.md) | [**convert\_to\_set**](#function-convert_to_set-44) ([**const**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) [**GravParam**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) & mu) const<br>_Converts the current orbital elements to a specific type._  |
|  [**const**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) [**ElementVariant**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) & | [**extract**](#function-extract-12) () const<br>_Extracts the underlying orbital elements as a variant._  |
|  [**ElementVariant**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) & | [**extract**](#function-extract-22) () <br>_Extracts the underlying orbital elements as a variant._  |
|  std::vector&lt; [**Unitless**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) &gt; | [**force\_to\_vector**](#function-force_to_vector) () const<br>_Converts the_ [_**OrbitalElements**_](classastrea_1_1astro_1_1OrbitalElements.md) _to a vector of Unitless values._ |
|  [**T**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) | [**in\_element\_set**](#function-in_element_set) ([**const**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) [**GravParam**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) & mu) const<br>_Converts the current orbital elements to a specified type._  |
|  [**OrbitalElements**](classastrea_1_1astro_1_1OrbitalElements.md) | [**in\_frame**](#function-in_frame) ([**const**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) [**Date**](classastrea_1_1astro_1_1Date.md) & epoch, [**const**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) [**GravParam**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) & mu) const<br>_Converts all held orbital elements to the specified frame._  |
|  [**constexpr**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) std::size\_t | [**index**](#function-index) () const<br>_Returns the index of the current orbital elements in the variant._  |
|  [**OrbitalElements**](classastrea_1_1astro_1_1OrbitalElements.md) | [**interpolate**](#function-interpolate) ([**const**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) [**Time**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) & thisTime, [**const**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) [**Time**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) & otherTime, [**const**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) [**OrbitalElements**](classastrea_1_1astro_1_1OrbitalElements.md) & other, [**const**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) [**GravParam**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) & mu, [**const**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) [**Time**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) & targetTime) const<br>_Interpolates between two_ [_**OrbitalElements**_](classastrea_1_1astro_1_1OrbitalElements.md) _at a given time._ |
|  [**OrbitalElements**](classastrea_1_1astro_1_1OrbitalElements.md) | [**operator\***](#function-operator) ([**const**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) [**Unitless**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) & multiplier) const<br>_Multiplies the_ [_**OrbitalElements**_](classastrea_1_1astro_1_1OrbitalElements.md) _by a scalar._ |
|  [**OrbitalElements**](classastrea_1_1astro_1_1OrbitalElements.md) & | [**operator\*=**](#function-operator_1) ([**const**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) [**Unitless**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) & multiplier) <br>_Multiplies the_ [_**OrbitalElements**_](classastrea_1_1astro_1_1OrbitalElements.md) _by a scalar._ |
|  [**OrbitalElements**](classastrea_1_1astro_1_1OrbitalElements.md) | [**operator+**](#function-operator_2) ([**const**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) [**OrbitalElements**](classastrea_1_1astro_1_1OrbitalElements.md) & other) const<br>_Adds two_ [_**OrbitalElements**_](classastrea_1_1astro_1_1OrbitalElements.md) _objects._ |
|  [**OrbitalElements**](classastrea_1_1astro_1_1OrbitalElements.md) & | [**operator+=**](#function-operator_3) ([**const**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) [**OrbitalElements**](classastrea_1_1astro_1_1OrbitalElements.md) & other) <br>_Adds another_ [_**OrbitalElements**_](classastrea_1_1astro_1_1OrbitalElements.md) _object to the current one._ |
|  [**OrbitalElements**](classastrea_1_1astro_1_1OrbitalElements.md) | [**operator-**](#function-operator-) ([**const**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) [**OrbitalElements**](classastrea_1_1astro_1_1OrbitalElements.md) & other) const<br>_Subtracts another_ [_**OrbitalElements**_](classastrea_1_1astro_1_1OrbitalElements.md) _object from the current one._ |
|  [**OrbitalElements**](classastrea_1_1astro_1_1OrbitalElements.md) & | [**operator-=**](#function-operator-_1) ([**const**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) [**OrbitalElements**](classastrea_1_1astro_1_1OrbitalElements.md) & other) <br>_Subtracts another_ [_**OrbitalElements**_](classastrea_1_1astro_1_1OrbitalElements.md) _object from the current one._ |
|  [**OrbitalElementPartials**](classastrea_1_1astro_1_1OrbitalElementPartials.md) | [**operator/**](#function-operator_4) ([**const**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) [**Time**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) & divisor) const<br>_Divides the_ [_**OrbitalElements**_](classastrea_1_1astro_1_1OrbitalElements.md) _by a time._ |
|  [**OrbitalElements**](classastrea_1_1astro_1_1OrbitalElements.md) | [**operator/**](#function-operator_5) ([**const**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) [**Unitless**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) & divisor) const<br>_Divides the_ [_**OrbitalElements**_](classastrea_1_1astro_1_1OrbitalElements.md) _by a scalar._ |
|  [**OrbitalElements**](classastrea_1_1astro_1_1OrbitalElements.md) & | [**operator/=**](#function-operator_6) ([**const**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) [**Unitless**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) & divisor) <br>_Divides the_ [_**OrbitalElements**_](classastrea_1_1astro_1_1OrbitalElements.md) _by a scalar._ |
|  [**bool**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) | [**operator==**](#function-operator_7) ([**const**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) [**OrbitalElements**](classastrea_1_1astro_1_1OrbitalElements.md) & other) const<br>_Compares two_ [_**OrbitalElements**_](classastrea_1_1astro_1_1OrbitalElements.md) _objects for equality._ |


## Public Static Functions

| Type | Name |
| ---: | :--- |
|  [**constexpr**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) std::size\_t | [**get\_set\_id**](#function-get_set_id) () <br>_Returns the set ID for a specific type of orbital elements._  |


























## Detailed Description


This class encapsulates different types of orbital elements ([**Cartesian**](classastrea_1_1astro_1_1Cartesian.md), [**Keplerian**](classastrea_1_1astro_1_1Keplerian.md), [**Equinoctial**](classastrea_1_1astro_1_1Equinoctial.md)) and provides methods for conversion, interpolation, and mathematical operations. 


    
## Public Functions Documentation




### function OrbitalElements [1/4]

_Default constructor initializing to Cartesian&lt;frames::primary&gt; elements._ 
```C++
inline astrea::astro::OrbitalElements::OrbitalElements () 
```




<hr>



### function OrbitalElements [2/4]

_Constructor initializing with Cartesian&lt;frame&gt; elements._ 
```C++
template<IsFrame auto frame>
inline astrea::astro::OrbitalElements::OrbitalElements (
    Cartesian < frame > elements
) 
```





**Parameters:**


* `elements` The orbital elements to initialize with. 




        

<hr>



### function OrbitalElements [3/4]

_Constructor initializing with Keplerian&lt;frame&gt; elements._ 
```C++
template<IsFrame auto frame>
inline astrea::astro::OrbitalElements::OrbitalElements (
    Keplerian < frame > elements
) 
```





**Parameters:**


* `elements` The orbital elements to initialize with. 




        

<hr>



### function OrbitalElements [4/4]

_Constructor initializing with Equinoctial&lt;frame&gt; elements._ 
```C++
template<IsFrame auto frame>
inline astrea::astro::OrbitalElements::OrbitalElements (
    Equinoctial < frame > elements
) 
```





**Parameters:**


* `elements` The orbital elements to initialize with. 




        

<hr>



### function convert\_to\_set [1/4]

_Converts the current orbital elements to a specific type._ 
```C++
OrbitalElements & astrea::astro::OrbitalElements::convert_to_set (
    const std::size_t idx,
    const  GravParam & mu
) 
```





**Template parameters:**


* `index` The index of the orbital element type to convert to. 



**Parameters:**


* `mu` The gravitational parameter to use for the conversion. 



**Returns:**

[**OrbitalElements**](classastrea_1_1astro_1_1OrbitalElements.md)& Reference to the current orbital elements after conversion. 





        

<hr>



### function convert\_to\_set [2/4]

_Converts the current orbital elements to a specific type._ 
```C++
OrbitalElements astrea::astro::OrbitalElements::convert_to_set (
    const std::size_t idx,
    const  GravParam & mu
) const
```





**Template parameters:**


* `index` The index of the orbital element type to convert to. 



**Parameters:**


* `mu` The gravitational parameter to use for the conversion. 



**Returns:**

[**OrbitalElements**](classastrea_1_1astro_1_1OrbitalElements.md) Orbital elements after conversion. 





        

<hr>



### function convert\_to\_set [3/4]

_Converts the current orbital elements to a specific type._ 
```C++
template<IsOrbitalElements T>
inline OrbitalElements & astrea::astro::OrbitalElements::convert_to_set (
    const  GravParam & mu
) 
```





**Template parameters:**


* `T` The type to convert to. 



**Parameters:**


* `mu` The gravitational parameter to use for the conversion. 



**Returns:**

A reference to the current orbital elements after conversion. 





        

<hr>



### function convert\_to\_set [4/4]

_Converts the current orbital elements to a specific type._ 
```C++
template<IsOrbitalElements T>
inline OrbitalElements astrea::astro::OrbitalElements::convert_to_set (
    const  GravParam & mu
) const
```





**Template parameters:**


* `T` The type to convert to. 



**Parameters:**


* `mu` The gravitational parameter to use for the conversion. 



**Returns:**

The converted orbital elements. 





        

<hr>



### function extract [1/2]

_Extracts the underlying orbital elements as a variant._ 
```C++
const  ElementVariant & astrea::astro::OrbitalElements::extract () const
```





**Returns:**

const ElementVariant& Reference to the underlying orbital elements variant. 





        

<hr>



### function extract [2/2]

_Extracts the underlying orbital elements as a variant._ 
```C++
ElementVariant & astrea::astro::OrbitalElements::extract () 
```





**Returns:**

ElementVariant& Reference to the underlying orbital elements variant. 





        

<hr>



### function force\_to\_vector 

_Converts the_ [_**OrbitalElements**_](classastrea_1_1astro_1_1OrbitalElements.md) _to a vector of Unitless values._
```C++
std::vector< Unitless > astrea::astro::OrbitalElements::force_to_vector () const
```





**Returns:**

std::vector&lt;Unitless&gt; Vector containing the orbital elements as unitless values. 





        

<hr>



### function in\_element\_set 

_Converts the current orbital elements to a specified type._ 
```C++
template<IsOrbitalElements T>
inline T astrea::astro::OrbitalElements::in_element_set (
    const  GravParam & mu
) const
```





**Parameters:**


* `mu` The gravitational parameter to use for the conversion. 



**Returns:**

The converted orbital elements. 





        

<hr>



### function in\_frame 

_Converts all held orbital elements to the specified frame._ 
```C++
template<IsFrame auto target_frame>
inline OrbitalElements astrea::astro::OrbitalElements::in_frame (
    const  Date & epoch,
    const  GravParam & mu
) const
```



Visits the current element type and calls its in\_frame&lt;target\_frame&gt;(epoch, mu), returning a new [**OrbitalElements**](classastrea_1_1astro_1_1OrbitalElements.md) holding the converted elements.




**Template parameters:**


* `target_frame` The frame to convert into. 



**Parameters:**


* `epoch` The epoch at which to evaluate the frame transformation. 
* `mu` The gravitational parameter of the central body. 



**Returns:**

[**OrbitalElements**](classastrea_1_1astro_1_1OrbitalElements.md) Orbital elements expressed in target\_frame. 





        

<hr>



### function index 

_Returns the index of the current orbital elements in the variant._ 
```C++
inline constexpr std::size_t astrea::astro::OrbitalElements::index () const
```





**Returns:**

std::size\_t The index of the current orbital elements in the variant. 





        

<hr>



### function interpolate 

_Interpolates between two_ [_**OrbitalElements**_](classastrea_1_1astro_1_1OrbitalElements.md) _at a given time._
```C++
OrbitalElements astrea::astro::OrbitalElements::interpolate (
    const  Time & thisTime,
    const  Time & otherTime,
    const  OrbitalElements & other,
    const  GravParam & mu,
    const  Time & targetTime
) const
```





**Parameters:**


* `thisTime` Time of the current state 
* `otherTime` Time of the other state 
* `other` Another [**OrbitalElements**](classastrea_1_1astro_1_1OrbitalElements.md) object to interpolate with 
* `mu` The gravitational parameter to use for the interpolation 
* `targetTime` The target time for interpolation 



**Returns:**

Interpolated [**OrbitalElements**](classastrea_1_1astro_1_1OrbitalElements.md) at the target time. 





        

<hr>



### function operator\* 

_Multiplies the_ [_**OrbitalElements**_](classastrea_1_1astro_1_1OrbitalElements.md) _by a scalar._
```C++
OrbitalElements astrea::astro::OrbitalElements::operator* (
    const  Unitless & multiplier
) const
```





**Parameters:**


* `multiplier` Scalar value to multiply with 



**Returns:**

Resultant [**OrbitalElements**](classastrea_1_1astro_1_1OrbitalElements.md) after multiplication. 





        

<hr>



### function operator\*= 

_Multiplies the_ [_**OrbitalElements**_](classastrea_1_1astro_1_1OrbitalElements.md) _by a scalar._
```C++
OrbitalElements & astrea::astro::OrbitalElements::operator*= (
    const  Unitless & multiplier
) 
```





**Parameters:**


* `multiplier` Scalar value to multiply with 



**Returns:**

Reference to the current [**OrbitalElements**](classastrea_1_1astro_1_1OrbitalElements.md) object after multiplication. 





        

<hr>



### function operator+ 

_Adds two_ [_**OrbitalElements**_](classastrea_1_1astro_1_1OrbitalElements.md) _objects._
```C++
OrbitalElements astrea::astro::OrbitalElements::operator+ (
    const  OrbitalElements & other
) const
```





**Parameters:**


* `other` Another [**OrbitalElements**](classastrea_1_1astro_1_1OrbitalElements.md) object 



**Returns:**

Resultant [**OrbitalElements**](classastrea_1_1astro_1_1OrbitalElements.md) sum. 





        

<hr>



### function operator+= 

_Adds another_ [_**OrbitalElements**_](classastrea_1_1astro_1_1OrbitalElements.md) _object to the current one._
```C++
OrbitalElements & astrea::astro::OrbitalElements::operator+= (
    const  OrbitalElements & other
) 
```





**Parameters:**


* `other` Another [**OrbitalElements**](classastrea_1_1astro_1_1OrbitalElements.md) object 



**Returns:**

Reference to the current [**OrbitalElements**](classastrea_1_1astro_1_1OrbitalElements.md) object after addition. 





        

<hr>



### function operator- 

_Subtracts another_ [_**OrbitalElements**_](classastrea_1_1astro_1_1OrbitalElements.md) _object from the current one._
```C++
OrbitalElements astrea::astro::OrbitalElements::operator- (
    const  OrbitalElements & other
) const
```





**Parameters:**


* `other` Another [**OrbitalElements**](classastrea_1_1astro_1_1OrbitalElements.md) object 



**Returns:**

Resultant [**OrbitalElements**](classastrea_1_1astro_1_1OrbitalElements.md) difference. 





        

<hr>



### function operator-= 

_Subtracts another_ [_**OrbitalElements**_](classastrea_1_1astro_1_1OrbitalElements.md) _object from the current one._
```C++
OrbitalElements & astrea::astro::OrbitalElements::operator-= (
    const  OrbitalElements & other
) 
```





**Parameters:**


* `other` Another [**OrbitalElements**](classastrea_1_1astro_1_1OrbitalElements.md) object 



**Returns:**

Reference to the current [**OrbitalElements**](classastrea_1_1astro_1_1OrbitalElements.md) object after subtraction. 





        

<hr>



### function operator/ 

_Divides the_ [_**OrbitalElements**_](classastrea_1_1astro_1_1OrbitalElements.md) _by a time._
```C++
OrbitalElementPartials astrea::astro::OrbitalElements::operator/ (
    const  Time & divisor
) const
```





**Parameters:**


* `divisor` Time value to divide by 



**Returns:**

Resultant [**OrbitalElementPartials**](classastrea_1_1astro_1_1OrbitalElementPartials.md) after division. 





        

<hr>



### function operator/ 

_Divides the_ [_**OrbitalElements**_](classastrea_1_1astro_1_1OrbitalElements.md) _by a scalar._
```C++
OrbitalElements astrea::astro::OrbitalElements::operator/ (
    const  Unitless & divisor
) const
```





**Parameters:**


* `divisor` Scalar value to divide with 



**Returns:**

Resultant [**OrbitalElements**](classastrea_1_1astro_1_1OrbitalElements.md) after division. 





        

<hr>



### function operator/= 

_Divides the_ [_**OrbitalElements**_](classastrea_1_1astro_1_1OrbitalElements.md) _by a scalar._
```C++
OrbitalElements & astrea::astro::OrbitalElements::operator/= (
    const  Unitless & divisor
) 
```





**Parameters:**


* `divisor` Scalar value to divide with 



**Returns:**

Reference to the current [**OrbitalElements**](classastrea_1_1astro_1_1OrbitalElements.md) object after division. 





        

<hr>



### function operator== 

_Compares two_ [_**OrbitalElements**_](classastrea_1_1astro_1_1OrbitalElements.md) _objects for equality._
```C++
bool astrea::astro::OrbitalElements::operator== (
    const  OrbitalElements & other
) const
```





**Parameters:**


* `other` Another [**OrbitalElements**](classastrea_1_1astro_1_1OrbitalElements.md) object to compare with. 



**Returns:**

true if the two [**OrbitalElements**](classastrea_1_1astro_1_1OrbitalElements.md) objects are equal 




**Returns:**

false if the two [**OrbitalElements**](classastrea_1_1astro_1_1OrbitalElements.md) objects are not equal 





        

<hr>
## Public Static Functions Documentation




### function get\_set\_id 

_Returns the set ID for a specific type of orbital elements._ 
```C++
template<typename  T>
static inline constexpr std::size_t astrea::astro::OrbitalElements::get_set_id () 
```





**Template parameters:**


* `T` The type of orbital elements. 



**Returns:**

std::size\_t The set ID for the specified type. 





        

<hr>

------------------------------
The documentation for this class was generated from the following file `astrea/astro/astro/state/orbital_elements/OrbitalElements.hpp`

