

# Class astrea::astro::Equinoctial

**template &lt;IsFrame [**auto**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) \_frame\_&gt;**



[**ClassList**](annotated.md) **>** [**astrea**](namespaceastrea.md) **>** [**astro**](namespaceastrea_1_1astro.md) **>** [**Equinoctial**](classastrea_1_1astro_1_1Equinoctial.md)



_The_ [_**Equinoctial**_](classastrea_1_1astro_1_1Equinoctial.md) _class represents the equinoctial orbital elements._[More...](#detailed-description)

* `#include <Equinoctial.hpp>`























## Public Static Attributes

| Type | Name |
| ---: | :--- |
|  [**constexpr**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) [**auto**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) | [**frame**](#variable-frame)   = `\_frame\_`<br>_The reference frame of the_ [_**Equinoctial**_](classastrea_1_1astro_1_1Equinoctial.md) _state vector._ |














## Public Functions

| Type | Name |
| ---: | :--- |
|   | [**Equinoctial**](#function-equinoctial-17) ([**Unitless**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) scale=0.0 \*astrea::detail::unitless) <br>_Constructs an_ [_**Equinoctial**_](classastrea_1_1astro_1_1Equinoctial.md) _object with default values._ |
|   | [**Equinoctial**](#function-equinoctial-27) ([**const**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) [**Distance**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) & semilatus, [**const**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) [**Unitless**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) & f, [**const**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) [**Unitless**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) & g, [**const**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) [**Unitless**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) & h, [**const**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) [**Unitless**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) & k, [**const**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) [**Angle**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) & trueLongitude) <br>_Constructs an_ [_**Equinoctial**_](classastrea_1_1astro_1_1Equinoctial.md) _object with specified values._ |
|   | [**Equinoctial**](#function-equinoctial-37) ([**const**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) [**Equinoctial**](classastrea_1_1astro_1_1Equinoctial.md)&lt; \_frame\_ &gt; & elements, [**const**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) [**GravParam**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) & mu) <br>_Constructs an_ [_**Equinoctial**_](classastrea_1_1astro_1_1Equinoctial.md) _object from another_[_**Equinoctial**_](classastrea_1_1astro_1_1Equinoctial.md) _object._ |
|   | [**Equinoctial**](#function-equinoctial-47) ([**const**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) [**Keplerian**](classastrea_1_1astro_1_1Keplerian.md)&lt; \_frame\_ &gt; & elements, [**const**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) [**GravParam**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) & mu) <br>_Constructs an_ [_**Equinoctial**_](classastrea_1_1astro_1_1Equinoctial.md) _object from_[_**Keplerian**_](classastrea_1_1astro_1_1Keplerian.md) _elements._ |
|   | [**Equinoctial**](#function-equinoctial-57) ([**const**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) [**Cartesian**](classastrea_1_1astro_1_1Cartesian.md)&lt; \_frame\_ &gt; & elements, [**const**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) [**GravParam**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) & mu) <br>_Constructs an_ [_**Equinoctial**_](classastrea_1_1astro_1_1Equinoctial.md) _object from_[_**Cartesian**_](classastrea_1_1astro_1_1Cartesian.md) _elements._ |
|   | [**Equinoctial**](#function-equinoctial-67) ([**const**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) [**Equinoctial**](classastrea_1_1astro_1_1Equinoctial.md)&lt; \_frame\_ &gt; & other) <br>_Copy constructor for_ [_**Equinoctial**_](classastrea_1_1astro_1_1Equinoctial.md) _._ |
|   | [**Equinoctial**](#function-equinoctial-77) ([**Equinoctial**](classastrea_1_1astro_1_1Equinoctial.md)&lt; \_frame\_ &gt; && other) noexcept<br>_Move constructor for_ [_**Equinoctial**_](classastrea_1_1astro_1_1Equinoctial.md) _._ |
|  std::vector&lt; [**Unitless**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) &gt; | [**force\_to\_vector**](#function-force_to_vector) () const<br>_Converts the_ [_**Equinoctial**_](classastrea_1_1astro_1_1Equinoctial.md) _state vector to a vector of unitless values._ |
|  [**const**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) [**Unitless**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) & | [**get\_f**](#function-get_f) () const<br>_Get the f value of the_ [_**Equinoctial**_](classastrea_1_1astro_1_1Equinoctial.md) _state vector._ |
|  [**const**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) [**Unitless**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) & | [**get\_g**](#function-get_g) () const<br>_Get the g value of the_ [_**Equinoctial**_](classastrea_1_1astro_1_1Equinoctial.md) _state vector._ |
|  [**const**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) [**Unitless**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) & | [**get\_h**](#function-get_h) () const<br>_Get the h value of the_ [_**Equinoctial**_](classastrea_1_1astro_1_1Equinoctial.md) _state vector._ |
|  [**const**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) [**Unitless**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) & | [**get\_k**](#function-get_k) () const<br>_Get the k value of the_ [_**Equinoctial**_](classastrea_1_1astro_1_1Equinoctial.md) _state vector._ |
|  [**const**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) [**Distance**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) & | [**get\_semilatus**](#function-get_semilatus) () const<br>_Get the semilatus value of the_ [_**Equinoctial**_](classastrea_1_1astro_1_1Equinoctial.md) _state vector._ |
|  [**const**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) [**Angle**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) & | [**get\_true\_longitude**](#function-get_true_longitude) () const<br>_Get the true longitude value of the_ [_**Equinoctial**_](classastrea_1_1astro_1_1Equinoctial.md) _state vector._ |
|  [**Equinoctial**](classastrea_1_1astro_1_1Equinoctial.md)&lt; [**target\_frame**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) &gt; | [**in\_frame**](#function-in_frame) ([**const**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) [**Date**](classastrea_1_1astro_1_1Date.md) & epoch, [**const**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) [**GravParam**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) & mu) const<br>_Converts this_ [_**Equinoctial**_](classastrea_1_1astro_1_1Equinoctial.md) _state to_[_**Equinoctial**_](classastrea_1_1astro_1_1Equinoctial.md) _elements expressed in a different frame._ |
|  [**Equinoctial**](classastrea_1_1astro_1_1Equinoctial.md) | [**interpolate**](#function-interpolate) ([**const**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) [**Time**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) & thisTime, [**const**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) [**Time**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) & otherTime, [**const**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) [**Equinoctial**](classastrea_1_1astro_1_1Equinoctial.md)&lt; \_frame\_ &gt; & other, [**const**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) [**GravParam**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) & mu, [**const**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) [**Time**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) & targetTime) const<br>_Interpolates the_ [_**Equinoctial**_](classastrea_1_1astro_1_1Equinoctial.md) _state vector between two time instances._ |
|  [**bool**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) | [**operator!=**](#function-operator) ([**const**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) [**Equinoctial**](classastrea_1_1astro_1_1Equinoctial.md)&lt; \_frame\_ &gt; & other) const<br>_Checks if two_ [_**Equinoctial**_](classastrea_1_1astro_1_1Equinoctial.md) _objects are not equal._ |
|  [**Equinoctial**](classastrea_1_1astro_1_1Equinoctial.md) | [**operator\***](#function-operator_1) ([**const**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) [**Unitless**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) & multiplier) const<br>_Multiplies the_ [_**Equinoctial**_](classastrea_1_1astro_1_1Equinoctial.md) _state vector by a scalar._ |
|  [**Equinoctial**](classastrea_1_1astro_1_1Equinoctial.md) & | [**operator\*=**](#function-operator_2) ([**const**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) [**Unitless**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) & multiplier) <br>_Multiplies the_ [_**Equinoctial**_](classastrea_1_1astro_1_1Equinoctial.md) _state vector by a scalar._ |
|  [**Equinoctial**](classastrea_1_1astro_1_1Equinoctial.md) | [**operator+**](#function-operator_3) ([**const**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) [**Equinoctial**](classastrea_1_1astro_1_1Equinoctial.md)&lt; \_frame\_ &gt; & other) const<br>_Adds two_ [_**Equinoctial**_](classastrea_1_1astro_1_1Equinoctial.md) _objects._ |
|  [**Equinoctial**](classastrea_1_1astro_1_1Equinoctial.md) & | [**operator+=**](#function-operator_4) ([**const**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) [**Equinoctial**](classastrea_1_1astro_1_1Equinoctial.md)&lt; \_frame\_ &gt; & other) <br>_Adds another_ [_**Equinoctial**_](classastrea_1_1astro_1_1Equinoctial.md) _object to the current one._ |
|  [**Equinoctial**](classastrea_1_1astro_1_1Equinoctial.md) | [**operator-**](#function-operator-) ([**const**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) [**Equinoctial**](classastrea_1_1astro_1_1Equinoctial.md)&lt; \_frame\_ &gt; & other) const<br>_Subtracts another_ [_**Equinoctial**_](classastrea_1_1astro_1_1Equinoctial.md) _object from the current one._ |
|  [**Equinoctial**](classastrea_1_1astro_1_1Equinoctial.md) & | [**operator-=**](#function-operator-_1) ([**const**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) [**Equinoctial**](classastrea_1_1astro_1_1Equinoctial.md)&lt; \_frame\_ &gt; & other) <br>_Subtracts another_ [_**Equinoctial**_](classastrea_1_1astro_1_1Equinoctial.md) _object from the current one._ |
|  [**EquinoctialPartial**](classastrea_1_1astro_1_1EquinoctialPartial.md)&lt; \_frame\_ &gt; | [**operator/**](#function-operator_5) ([**const**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) [**Time**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) & time) const<br>_Divides the_ [_**Equinoctial**_](classastrea_1_1astro_1_1Equinoctial.md) _state vector by a time._ |
|  [**Equinoctial**](classastrea_1_1astro_1_1Equinoctial.md) | [**operator/**](#function-operator_6) ([**const**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) [**Unitless**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) & divisor) const<br>_Divides the_ [_**Equinoctial**_](classastrea_1_1astro_1_1Equinoctial.md) _state vector by a scalar._ |
|  [**Equinoctial**](classastrea_1_1astro_1_1Equinoctial.md) & | [**operator/=**](#function-operator_7) ([**const**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) [**Unitless**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) & divisor) <br>_Divides the_ [_**Equinoctial**_](classastrea_1_1astro_1_1Equinoctial.md) _state vector by a scalar._ |
|  [**Equinoctial**](classastrea_1_1astro_1_1Equinoctial.md) & | [**operator=**](#function-operator_8) ([**Equinoctial**](classastrea_1_1astro_1_1Equinoctial.md)&lt; \_frame\_ &gt; && other) noexcept<br>_Move assignment operator for_ [_**Equinoctial**_](classastrea_1_1astro_1_1Equinoctial.md) _._ |
|  [**Equinoctial**](classastrea_1_1astro_1_1Equinoctial.md) & | [**operator=**](#function-operator_9) ([**const**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) [**Equinoctial**](classastrea_1_1astro_1_1Equinoctial.md)&lt; \_frame\_ &gt; & other) <br>_Copy assignment operator for_ [_**Equinoctial**_](classastrea_1_1astro_1_1Equinoctial.md) _._ |
|  [**bool**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) | [**operator==**](#function-operator_10) ([**const**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) [**Equinoctial**](classastrea_1_1astro_1_1Equinoctial.md)&lt; \_frame\_ &gt; & other) const<br>_Checks if two_ [_**Equinoctial**_](classastrea_1_1astro_1_1Equinoctial.md) _objects are equal._ |
|   | [**~Equinoctial**](#function-equinoctial) () = default<br>_Default destructor for_ [_**Equinoctial**_](classastrea_1_1astro_1_1Equinoctial.md) _._ |


## Public Static Functions

| Type | Name |
| ---: | :--- |
|  [**Equinoctial**](classastrea_1_1astro_1_1Equinoctial.md) | [**GEO**](#function-geo) ([**const**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) [**GravParam**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) & mu) <br>_A static method to create_ [_**Equinoctial**_](classastrea_1_1astro_1_1Equinoctial.md) _state vectors for a GEO orbit._ |
|  [**Equinoctial**](classastrea_1_1astro_1_1Equinoctial.md) | [**GPS**](#function-gps) ([**const**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) [**GravParam**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) & mu) <br>_A static method to create_ [_**Equinoctial**_](classastrea_1_1astro_1_1Equinoctial.md) _state vectors for a GPS orbit._ |
|  [**Equinoctial**](classastrea_1_1astro_1_1Equinoctial.md) | [**HMEO**](#function-hmeo) ([**const**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) [**GravParam**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) & mu) <br>_A static method to create_ [_**Equinoctial**_](classastrea_1_1astro_1_1Equinoctial.md) _state vectors for a HMEO orbit._ |
|  [**Equinoctial**](classastrea_1_1astro_1_1Equinoctial.md) | [**LEO**](#function-leo) ([**const**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) [**GravParam**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) & mu) <br>_A static method to create_ [_**Equinoctial**_](classastrea_1_1astro_1_1Equinoctial.md) _state vectors for a LEO orbit._ |
|  [**Equinoctial**](classastrea_1_1astro_1_1Equinoctial.md) | [**LMEO**](#function-lmeo) ([**const**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) [**GravParam**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) & mu) <br>_A static method to create_ [_**Equinoctial**_](classastrea_1_1astro_1_1Equinoctial.md) _state vectors for a LMEO orbit._ |


























## Detailed Description


The equinoctial elements are a set of orbital elements that are particularly useful for describing orbits in a way that avoids singularities, especially for near-circular orbits. They are defined in terms of the semilatus rectum and the components of the eccentricity vector. 


    
## Public Static Attributes Documentation




### variable frame 

_The reference frame of the_ [_**Equinoctial**_](classastrea_1_1astro_1_1Equinoctial.md) _state vector._
```C++
constexpr auto astrea::astro::Equinoctial< _frame_ >::frame;
```




<hr>
## Public Functions Documentation




### function Equinoctial [1/7]

_Constructs an_ [_**Equinoctial**_](classastrea_1_1astro_1_1Equinoctial.md) _object with default values._
```C++
inline astrea::astro::Equinoctial::Equinoctial (
    Unitless scale=0.0 *astrea::detail::unitless
) 
```





**Parameters:**


* `scale` A scaling factor to initialize the elements, typically used for unit conversion. 




        

<hr>



### function Equinoctial [2/7]

_Constructs an_ [_**Equinoctial**_](classastrea_1_1astro_1_1Equinoctial.md) _object with specified values._
```C++
inline astrea::astro::Equinoctial::Equinoctial (
    const  Distance & semilatus,
    const  Unitless & f,
    const  Unitless & g,
    const  Unitless & h,
    const  Unitless & k,
    const  Angle & trueLongitude
) 
```





**Parameters:**


* `semilatus` The semilatus rectum of the orbit. 
* `f` The first component of the eccentricity vector. 
* `g` The second component of the eccentricity vector. 
* `h` The the first component of the planar vector. 
* `k` The the second component of the planar vector. 
* `trueLongitude` The true longitude of the orbit. 




        

<hr>



### function Equinoctial [3/7]

_Constructs an_ [_**Equinoctial**_](classastrea_1_1astro_1_1Equinoctial.md) _object from another_[_**Equinoctial**_](classastrea_1_1astro_1_1Equinoctial.md) _object._
```C++
inline astrea::astro::Equinoctial::Equinoctial (
    const  Equinoctial < _frame_ > & elements,
    const  GravParam & mu
) 
```





**Parameters:**


* `elements` The [**Equinoctial**](classastrea_1_1astro_1_1Equinoctial.md) object to copy. 
* `sys` The astrodynamics system context for conversion. 




        

<hr>



### function Equinoctial [4/7]

_Constructs an_ [_**Equinoctial**_](classastrea_1_1astro_1_1Equinoctial.md) _object from_[_**Keplerian**_](classastrea_1_1astro_1_1Keplerian.md) _elements._
```C++
astrea::astro::Equinoctial::Equinoctial (
    const  Keplerian < _frame_ > & elements,
    const  GravParam & mu
) 
```





**Parameters:**


* `elements` The [**Keplerian**](classastrea_1_1astro_1_1Keplerian.md) elements to convert. 
* `sys` The astrodynamics system context for conversion. 




        

<hr>



### function Equinoctial [5/7]

_Constructs an_ [_**Equinoctial**_](classastrea_1_1astro_1_1Equinoctial.md) _object from_[_**Cartesian**_](classastrea_1_1astro_1_1Cartesian.md) _elements._
```C++
inline astrea::astro::Equinoctial::Equinoctial (
    const  Cartesian < _frame_ > & elements,
    const  GravParam & mu
) 
```





**Parameters:**


* `elements` The [**Cartesian**](classastrea_1_1astro_1_1Cartesian.md) elements to convert. 
* `sys` The astrodynamics system context for conversion. 




        

<hr>



### function Equinoctial [6/7]

_Copy constructor for_ [_**Equinoctial**_](classastrea_1_1astro_1_1Equinoctial.md) _._
```C++
astrea::astro::Equinoctial::Equinoctial (
    const  Equinoctial < _frame_ > & other
) 
```




<hr>



### function Equinoctial [7/7]

_Move constructor for_ [_**Equinoctial**_](classastrea_1_1astro_1_1Equinoctial.md) _._
```C++
astrea::astro::Equinoctial::Equinoctial (
    Equinoctial < _frame_ > && other
) noexcept
```





**Parameters:**


* `other` Another [**Equinoctial**](classastrea_1_1astro_1_1Equinoctial.md) object 




        

<hr>



### function force\_to\_vector 

_Converts the_ [_**Equinoctial**_](classastrea_1_1astro_1_1Equinoctial.md) _state vector to a vector of unitless values._
```C++
std::vector< Unitless > astrea::astro::Equinoctial::force_to_vector () const
```





**Returns:**

std::vector&lt;Unitless&gt; Vector containing the semilatus, f, g, h, k, and true longitude components of the [**Equinoctial**](classastrea_1_1astro_1_1Equinoctial.md) state vector. 





        

<hr>



### function get\_f 

_Get the f value of the_ [_**Equinoctial**_](classastrea_1_1astro_1_1Equinoctial.md) _state vector._
```C++
inline const  Unitless & astrea::astro::Equinoctial::get_f () const
```





**Returns:**

const Unitless& Reference to the f component of the [**Equinoctial**](classastrea_1_1astro_1_1Equinoctial.md) state vector. 





        

<hr>



### function get\_g 

_Get the g value of the_ [_**Equinoctial**_](classastrea_1_1astro_1_1Equinoctial.md) _state vector._
```C++
inline const  Unitless & astrea::astro::Equinoctial::get_g () const
```





**Returns:**

const Unitless& Reference to the g component of the [**Equinoctial**](classastrea_1_1astro_1_1Equinoctial.md) state vector. 





        

<hr>



### function get\_h 

_Get the h value of the_ [_**Equinoctial**_](classastrea_1_1astro_1_1Equinoctial.md) _state vector._
```C++
inline const  Unitless & astrea::astro::Equinoctial::get_h () const
```





**Returns:**

const Unitless& Reference to the h component of the [**Equinoctial**](classastrea_1_1astro_1_1Equinoctial.md) state vector. 





        

<hr>



### function get\_k 

_Get the k value of the_ [_**Equinoctial**_](classastrea_1_1astro_1_1Equinoctial.md) _state vector._
```C++
inline const  Unitless & astrea::astro::Equinoctial::get_k () const
```





**Returns:**

const Unitless& Reference to the k component of the [**Equinoctial**](classastrea_1_1astro_1_1Equinoctial.md) state vector. 





        

<hr>



### function get\_semilatus 

_Get the semilatus value of the_ [_**Equinoctial**_](classastrea_1_1astro_1_1Equinoctial.md) _state vector._
```C++
inline const  Distance & astrea::astro::Equinoctial::get_semilatus () const
```





**Returns:**

const Distance& Reference to the semilatus component of the [**Equinoctial**](classastrea_1_1astro_1_1Equinoctial.md) state vector. 





        

<hr>



### function get\_true\_longitude 

_Get the true longitude value of the_ [_**Equinoctial**_](classastrea_1_1astro_1_1Equinoctial.md) _state vector._
```C++
inline const  Angle & astrea::astro::Equinoctial::get_true_longitude () const
```





**Returns:**

const Angle& Reference to the true longitude component of the [**Equinoctial**](classastrea_1_1astro_1_1Equinoctial.md) state vector. 





        

<hr>



### function in\_frame 

_Converts this_ [_**Equinoctial**_](classastrea_1_1astro_1_1Equinoctial.md) _state to_[_**Equinoctial**_](classastrea_1_1astro_1_1Equinoctial.md) _elements expressed in a different frame._
```C++
template<IsFrame auto target_frame>
Equinoctial < target_frame > astrea::astro::Equinoctial::in_frame (
    const  Date & epoch,
    const  GravParam & mu
) const
```



First converts to [**Cartesian**](classastrea_1_1astro_1_1Cartesian.md) in the native frame, applies the physical frame transformation, then converts the result back to [**Equinoctial**](classastrea_1_1astro_1_1Equinoctial.md) elements.




**Template parameters:**


* `target_frame` The target frame. 



**Parameters:**


* `epoch` The epoch at which to evaluate the frame transformation. 
* `mu` The gravitational parameter of the central body. 



**Returns:**

Equinoctial&lt;target\_frame&gt; This state expressed in the target frame. 





        

<hr>



### function interpolate 

_Interpolates the_ [_**Equinoctial**_](classastrea_1_1astro_1_1Equinoctial.md) _state vector between two time instances._
```C++
Equinoctial astrea::astro::Equinoctial::interpolate (
    const  Time & thisTime,
    const  Time & otherTime,
    const  Equinoctial < _frame_ > & other,
    const  GravParam & mu,
    const  Time & targetTime
) const
```





**Parameters:**


* `thisTime` Time of the current state 
* `otherTime` Time of the other state 
* `other` Another [**Equinoctial**](classastrea_1_1astro_1_1Equinoctial.md) object to interpolate with 
* `mu` The gravitational parameter to use for the interpolation 
* `targetTime` Time of the target state 



**Returns:**

[**Equinoctial**](classastrea_1_1astro_1_1Equinoctial.md) Interpolated [**Equinoctial**](classastrea_1_1astro_1_1Equinoctial.md) state vector. 





        

<hr>



### function operator!= 

_Checks if two_ [_**Equinoctial**_](classastrea_1_1astro_1_1Equinoctial.md) _objects are not equal._
```C++
bool astrea::astro::Equinoctial::operator!= (
    const  Equinoctial < _frame_ > & other
) const
```





**Parameters:**


* `other` Another [**Equinoctial**](classastrea_1_1astro_1_1Equinoctial.md) object 



**Returns:**

true if the two [**Equinoctial**](classastrea_1_1astro_1_1Equinoctial.md) objects are not equal, false otherwise. 





        

<hr>



### function operator\* 

_Multiplies the_ [_**Equinoctial**_](classastrea_1_1astro_1_1Equinoctial.md) _state vector by a scalar._
```C++
Equinoctial astrea::astro::Equinoctial::operator* (
    const  Unitless & multiplier
) const
```





**Parameters:**


* `multiplier` Scalar value to multiply with 



**Returns:**

Resultant [**Equinoctial**](classastrea_1_1astro_1_1Equinoctial.md) after multiplication. 





        

<hr>



### function operator\*= 

_Multiplies the_ [_**Equinoctial**_](classastrea_1_1astro_1_1Equinoctial.md) _state vector by a scalar._
```C++
Equinoctial & astrea::astro::Equinoctial::operator*= (
    const  Unitless & multiplier
) 
```





**Parameters:**


* `multiplier` Scalar value to multiply with 



**Returns:**

Reference to the current [**Equinoctial**](classastrea_1_1astro_1_1Equinoctial.md) object after multiplication. 





        

<hr>



### function operator+ 

_Adds two_ [_**Equinoctial**_](classastrea_1_1astro_1_1Equinoctial.md) _objects._
```C++
Equinoctial astrea::astro::Equinoctial::operator+ (
    const  Equinoctial < _frame_ > & other
) const
```





**Parameters:**


* `other` Another [**Equinoctial**](classastrea_1_1astro_1_1Equinoctial.md) object 



**Returns:**

Resultant [**Equinoctial**](classastrea_1_1astro_1_1Equinoctial.md) sum. 





        

<hr>



### function operator+= 

_Adds another_ [_**Equinoctial**_](classastrea_1_1astro_1_1Equinoctial.md) _object to the current one._
```C++
Equinoctial & astrea::astro::Equinoctial::operator+= (
    const  Equinoctial < _frame_ > & other
) 
```





**Parameters:**


* `other` Another [**Equinoctial**](classastrea_1_1astro_1_1Equinoctial.md) object 



**Returns:**

Reference to the current [**Equinoctial**](classastrea_1_1astro_1_1Equinoctial.md) object after addition. 





        

<hr>



### function operator- 

_Subtracts another_ [_**Equinoctial**_](classastrea_1_1astro_1_1Equinoctial.md) _object from the current one._
```C++
Equinoctial astrea::astro::Equinoctial::operator- (
    const  Equinoctial < _frame_ > & other
) const
```





**Parameters:**


* `other` Another [**Equinoctial**](classastrea_1_1astro_1_1Equinoctial.md) object 



**Returns:**

Resultant [**Equinoctial**](classastrea_1_1astro_1_1Equinoctial.md) after subtraction. 





        

<hr>



### function operator-= 

_Subtracts another_ [_**Equinoctial**_](classastrea_1_1astro_1_1Equinoctial.md) _object from the current one._
```C++
Equinoctial & astrea::astro::Equinoctial::operator-= (
    const  Equinoctial < _frame_ > & other
) 
```





**Parameters:**


* `other` Another [**Equinoctial**](classastrea_1_1astro_1_1Equinoctial.md) object 



**Returns:**

Reference to the current [**Equinoctial**](classastrea_1_1astro_1_1Equinoctial.md) object after subtraction. 





        

<hr>



### function operator/ 

_Divides the_ [_**Equinoctial**_](classastrea_1_1astro_1_1Equinoctial.md) _state vector by a time._
```C++
EquinoctialPartial < _frame_ > astrea::astro::Equinoctial::operator/ (
    const  Time & time
) const
```





**Parameters:**


* `time` Time value to divide by 



**Returns:**

Resultant [**EquinoctialPartial**](classastrea_1_1astro_1_1EquinoctialPartial.md) after division. 





        

<hr>



### function operator/ 

_Divides the_ [_**Equinoctial**_](classastrea_1_1astro_1_1Equinoctial.md) _state vector by a scalar._
```C++
Equinoctial astrea::astro::Equinoctial::operator/ (
    const  Unitless & divisor
) const
```





**Parameters:**


* `divisor` Scalar value to divide with 



**Returns:**

Resultant [**Equinoctial**](classastrea_1_1astro_1_1Equinoctial.md) after division. 





        

<hr>



### function operator/= 

_Divides the_ [_**Equinoctial**_](classastrea_1_1astro_1_1Equinoctial.md) _state vector by a scalar._
```C++
Equinoctial & astrea::astro::Equinoctial::operator/= (
    const  Unitless & divisor
) 
```





**Parameters:**


* `divisor` Scalar value to divide with 



**Returns:**

Reference to the current [**Equinoctial**](classastrea_1_1astro_1_1Equinoctial.md) object after division. 





        

<hr>



### function operator= 

_Move assignment operator for_ [_**Equinoctial**_](classastrea_1_1astro_1_1Equinoctial.md) _._
```C++
Equinoctial & astrea::astro::Equinoctial::operator= (
    Equinoctial < _frame_ > && other
) noexcept
```





**Parameters:**


* `other` Another [**Equinoctial**](classastrea_1_1astro_1_1Equinoctial.md) object 



**Returns:**

[**Equinoctial**](classastrea_1_1astro_1_1Equinoctial.md)&lt;_frame_&gt;& Reference to the current object 





        

<hr>



### function operator= 

_Copy assignment operator for_ [_**Equinoctial**_](classastrea_1_1astro_1_1Equinoctial.md) _._
```C++
Equinoctial & astrea::astro::Equinoctial::operator= (
    const  Equinoctial < _frame_ > & other
) 
```





**Parameters:**


* `other` Another [**Equinoctial**](classastrea_1_1astro_1_1Equinoctial.md) object 



**Returns:**

[**Equinoctial**](classastrea_1_1astro_1_1Equinoctial.md)& Reference to the current object 





        

<hr>



### function operator== 

_Checks if two_ [_**Equinoctial**_](classastrea_1_1astro_1_1Equinoctial.md) _objects are equal._
```C++
bool astrea::astro::Equinoctial::operator== (
    const  Equinoctial < _frame_ > & other
) const
```





**Parameters:**


* `other` Another [**Equinoctial**](classastrea_1_1astro_1_1Equinoctial.md) object 



**Returns:**

true if the two [**Equinoctial**](classastrea_1_1astro_1_1Equinoctial.md) objects are equal, false otherwise. 





        

<hr>



### function ~Equinoctial 

_Default destructor for_ [_**Equinoctial**_](classastrea_1_1astro_1_1Equinoctial.md) _._
```C++
astrea::astro::Equinoctial::~Equinoctial () = default
```




<hr>
## Public Static Functions Documentation




### function GEO 

_A static method to create_ [_**Equinoctial**_](classastrea_1_1astro_1_1Equinoctial.md) _state vectors for a GEO orbit._
```C++
static Equinoctial astrea::astro::Equinoctial::GEO (
    const  GravParam & mu
) 
```



This method return predefined [**Equinoctial**](classastrea_1_1astro_1_1Equinoctial.md) state vectors for various types of orbits.




**Parameters:**


* `mu` Gravitational parameter of the central body 



**Returns:**

[**Equinoctial**](classastrea_1_1astro_1_1Equinoctial.md) Predefined [**Equinoctial**](classastrea_1_1astro_1_1Equinoctial.md) state vector for a GEO orbit. 





        

<hr>



### function GPS 

_A static method to create_ [_**Equinoctial**_](classastrea_1_1astro_1_1Equinoctial.md) _state vectors for a GPS orbit._
```C++
static Equinoctial astrea::astro::Equinoctial::GPS (
    const  GravParam & mu
) 
```



This method return predefined [**Equinoctial**](classastrea_1_1astro_1_1Equinoctial.md) state vectors for various types of orbits.




**Parameters:**


* `mu` Gravitational parameter of the central body 



**Returns:**

[**Equinoctial**](classastrea_1_1astro_1_1Equinoctial.md) Predefined [**Equinoctial**](classastrea_1_1astro_1_1Equinoctial.md) state vector for a GPS orbit. 





        

<hr>



### function HMEO 

_A static method to create_ [_**Equinoctial**_](classastrea_1_1astro_1_1Equinoctial.md) _state vectors for a HMEO orbit._
```C++
static Equinoctial astrea::astro::Equinoctial::HMEO (
    const  GravParam & mu
) 
```



This method return predefined [**Equinoctial**](classastrea_1_1astro_1_1Equinoctial.md) state vectors for various types of orbits.




**Parameters:**


* `mu` Gravitational parameter of the central body 



**Returns:**

[**Equinoctial**](classastrea_1_1astro_1_1Equinoctial.md) Predefined [**Equinoctial**](classastrea_1_1astro_1_1Equinoctial.md) state vector for a HMEO orbit. 





        

<hr>



### function LEO 

_A static method to create_ [_**Equinoctial**_](classastrea_1_1astro_1_1Equinoctial.md) _state vectors for a LEO orbit._
```C++
static Equinoctial astrea::astro::Equinoctial::LEO (
    const  GravParam & mu
) 
```



This method return predefined [**Equinoctial**](classastrea_1_1astro_1_1Equinoctial.md) state vectors for various types of orbits.




**Parameters:**


* `mu` Gravitational parameter of the central body 



**Returns:**

[**Equinoctial**](classastrea_1_1astro_1_1Equinoctial.md) Predefined [**Equinoctial**](classastrea_1_1astro_1_1Equinoctial.md) state vector for a LEO orbit. 





        

<hr>



### function LMEO 

_A static method to create_ [_**Equinoctial**_](classastrea_1_1astro_1_1Equinoctial.md) _state vectors for a LMEO orbit._
```C++
static Equinoctial astrea::astro::Equinoctial::LMEO (
    const  GravParam & mu
) 
```



This method return predefined [**Equinoctial**](classastrea_1_1astro_1_1Equinoctial.md) state vectors for various types of orbits.




**Parameters:**


* `mu` Gravitational parameter of the central body 



**Returns:**

[**Equinoctial**](classastrea_1_1astro_1_1Equinoctial.md) Predefined [**Equinoctial**](classastrea_1_1astro_1_1Equinoctial.md) state vector for a LMEO orbit. 





        

<hr>

------------------------------
The documentation for this class was generated from the following file `astrea/astro/astro/state/orbital_elements/Equinoctial.hpp`

