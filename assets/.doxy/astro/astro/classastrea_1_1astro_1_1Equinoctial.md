

# Class astrea::astro::Equinoctial



[**ClassList**](annotated.md) **>** [**astrea**](namespaceastrea.md) **>** [**astro**](namespaceastrea_1_1astro.md) **>** [**Equinoctial**](classastrea_1_1astro_1_1Equinoctial.md)



_The_ [_**Equinoctial**_](classastrea_1_1astro_1_1Equinoctial.md) _class represents the equinoctial orbital elements._[More...](#detailed-description)

* `#include <Equinoctial.hpp>`





































## Public Functions

| Type | Name |
| ---: | :--- |
|   | [**Equinoctial**](#function-equinoctial-18) ([**Unitless**](classastrea_1_1astro_1_1CartesianVector.md) scale=0.0 \*astrea::detail::unitless) <br>_Constructs an_ [_**Equinoctial**_](classastrea_1_1astro_1_1Equinoctial.md) _object with default values._ |
|   | [**Equinoctial**](#function-equinoctial-28) ([**const**](classastrea_1_1astro_1_1CartesianVector.md) [**Distance**](classastrea_1_1astro_1_1CartesianVector.md) & semilatus, [**const**](classastrea_1_1astro_1_1CartesianVector.md) [**Unitless**](classastrea_1_1astro_1_1CartesianVector.md) & f, [**const**](classastrea_1_1astro_1_1CartesianVector.md) [**Unitless**](classastrea_1_1astro_1_1CartesianVector.md) & g, [**const**](classastrea_1_1astro_1_1CartesianVector.md) [**Unitless**](classastrea_1_1astro_1_1CartesianVector.md) & h, [**const**](classastrea_1_1astro_1_1CartesianVector.md) [**Unitless**](classastrea_1_1astro_1_1CartesianVector.md) & k, [**const**](classastrea_1_1astro_1_1CartesianVector.md) [**Angle**](classastrea_1_1astro_1_1CartesianVector.md) & trueLongitude) <br>_Constructs an_ [_**Equinoctial**_](classastrea_1_1astro_1_1Equinoctial.md) _object with specified values._ |
|   | [**Equinoctial**](#function-equinoctial-38) ([**const**](classastrea_1_1astro_1_1CartesianVector.md) [**Equinoctial**](classastrea_1_1astro_1_1Equinoctial.md) & elements, [**const**](classastrea_1_1astro_1_1CartesianVector.md) [**GravParam**](classastrea_1_1astro_1_1CartesianVector.md) & mu) <br>_Constructs an_ [_**Equinoctial**_](classastrea_1_1astro_1_1Equinoctial.md) _object from another_[_**Equinoctial**_](classastrea_1_1astro_1_1Equinoctial.md) _object._ |
|   | [**Equinoctial**](#function-equinoctial-48) ([**const**](classastrea_1_1astro_1_1CartesianVector.md) [**Keplerian**](classastrea_1_1astro_1_1Keplerian.md) & elements, [**const**](classastrea_1_1astro_1_1CartesianVector.md) [**GravParam**](classastrea_1_1astro_1_1CartesianVector.md) & mu) <br>_Constructs an_ [_**Equinoctial**_](classastrea_1_1astro_1_1Equinoctial.md) _object from_[_**Keplerian**_](classastrea_1_1astro_1_1Keplerian.md) _elements._ |
|   | [**Equinoctial**](#function-equinoctial-58) ([**const**](classastrea_1_1astro_1_1CartesianVector.md) [**Cartesian**](classastrea_1_1astro_1_1Cartesian.md) & elements, [**const**](classastrea_1_1astro_1_1CartesianVector.md) [**GravParam**](classastrea_1_1astro_1_1CartesianVector.md) & mu) <br>_Constructs an_ [_**Equinoctial**_](classastrea_1_1astro_1_1Equinoctial.md) _object from_[_**Cartesian**_](classastrea_1_1astro_1_1Cartesian.md) _elements._ |
|   | [**Equinoctial**](#function-equinoctial-68) ([**const**](classastrea_1_1astro_1_1CartesianVector.md) [**OrbitalElements**](classastrea_1_1astro_1_1OrbitalElements.md) & elements, [**const**](classastrea_1_1astro_1_1CartesianVector.md) [**GravParam**](classastrea_1_1astro_1_1CartesianVector.md) & mu) <br>_Constructs an_ [_**Equinoctial**_](classastrea_1_1astro_1_1Equinoctial.md) _object from_[_**OrbitalElements**_](classastrea_1_1astro_1_1OrbitalElements.md) _._ |
|   | [**Equinoctial**](#function-equinoctial-78) ([**const**](classastrea_1_1astro_1_1CartesianVector.md) [**Equinoctial**](classastrea_1_1astro_1_1Equinoctial.md) & other) <br>_Copy constructor for_ [_**Equinoctial**_](classastrea_1_1astro_1_1Equinoctial.md) _._ |
|   | [**Equinoctial**](#function-equinoctial-88) ([**Equinoctial**](classastrea_1_1astro_1_1Equinoctial.md) && other) noexcept<br>_Move constructor for_ [_**Equinoctial**_](classastrea_1_1astro_1_1Equinoctial.md) _._ |
|  std::vector&lt; [**Unitless**](classastrea_1_1astro_1_1CartesianVector.md) &gt; | [**force\_to\_vector**](#function-force_to_vector) () const<br>_Converts the_ [_**Equinoctial**_](classastrea_1_1astro_1_1Equinoctial.md) _state vector to a vector of unitless values._ |
|  [**const**](classastrea_1_1astro_1_1CartesianVector.md) [**Unitless**](classastrea_1_1astro_1_1CartesianVector.md) & | [**get\_f**](#function-get_f) () const<br>_Get the f value of the_ [_**Equinoctial**_](classastrea_1_1astro_1_1Equinoctial.md) _state vector._ |
|  [**const**](classastrea_1_1astro_1_1CartesianVector.md) [**Unitless**](classastrea_1_1astro_1_1CartesianVector.md) & | [**get\_g**](#function-get_g) () const<br>_Get the g value of the_ [_**Equinoctial**_](classastrea_1_1astro_1_1Equinoctial.md) _state vector._ |
|  [**const**](classastrea_1_1astro_1_1CartesianVector.md) [**Unitless**](classastrea_1_1astro_1_1CartesianVector.md) & | [**get\_h**](#function-get_h) () const<br>_Get the h value of the_ [_**Equinoctial**_](classastrea_1_1astro_1_1Equinoctial.md) _state vector._ |
|  [**const**](classastrea_1_1astro_1_1CartesianVector.md) [**Unitless**](classastrea_1_1astro_1_1CartesianVector.md) & | [**get\_k**](#function-get_k) () const<br>_Get the k value of the_ [_**Equinoctial**_](classastrea_1_1astro_1_1Equinoctial.md) _state vector._ |
|  [**const**](classastrea_1_1astro_1_1CartesianVector.md) [**Distance**](classastrea_1_1astro_1_1CartesianVector.md) & | [**get\_semilatus**](#function-get_semilatus) () const<br>_Get the semilatus value of the_ [_**Equinoctial**_](classastrea_1_1astro_1_1Equinoctial.md) _state vector._ |
|  [**const**](classastrea_1_1astro_1_1CartesianVector.md) [**Angle**](classastrea_1_1astro_1_1CartesianVector.md) & | [**get\_true\_longitude**](#function-get_true_longitude) () const<br>_Get the true longitude value of the_ [_**Equinoctial**_](classastrea_1_1astro_1_1Equinoctial.md) _state vector._ |
|  [**Equinoctial**](classastrea_1_1astro_1_1Equinoctial.md) | [**interpolate**](#function-interpolate) ([**const**](classastrea_1_1astro_1_1CartesianVector.md) [**Time**](classastrea_1_1astro_1_1CartesianVector.md) & thisTime, [**const**](classastrea_1_1astro_1_1CartesianVector.md) [**Time**](classastrea_1_1astro_1_1CartesianVector.md) & otherTime, [**const**](classastrea_1_1astro_1_1CartesianVector.md) [**Equinoctial**](classastrea_1_1astro_1_1Equinoctial.md) & other, [**const**](classastrea_1_1astro_1_1CartesianVector.md) [**GravParam**](classastrea_1_1astro_1_1CartesianVector.md) & mu, [**const**](classastrea_1_1astro_1_1CartesianVector.md) [**Time**](classastrea_1_1astro_1_1CartesianVector.md) & targetTime) const<br>_Interpolates the_ [_**Equinoctial**_](classastrea_1_1astro_1_1Equinoctial.md) _state vector between two time instances._ |
|  [**bool**](classastrea_1_1astro_1_1CartesianVector.md) | [**operator!=**](#function-operator) ([**const**](classastrea_1_1astro_1_1CartesianVector.md) [**Equinoctial**](classastrea_1_1astro_1_1Equinoctial.md) & other) const<br>_Checks if two_ [_**Equinoctial**_](classastrea_1_1astro_1_1Equinoctial.md) _objects are not equal._ |
|  [**Equinoctial**](classastrea_1_1astro_1_1Equinoctial.md) | [**operator\***](#function-operator_1) ([**const**](classastrea_1_1astro_1_1CartesianVector.md) [**Unitless**](classastrea_1_1astro_1_1CartesianVector.md) & multiplier) const<br>_Multiplies the_ [_**Equinoctial**_](classastrea_1_1astro_1_1Equinoctial.md) _state vector by a scalar._ |
|  [**Equinoctial**](classastrea_1_1astro_1_1Equinoctial.md) & | [**operator\*=**](#function-operator_2) ([**const**](classastrea_1_1astro_1_1CartesianVector.md) [**Unitless**](classastrea_1_1astro_1_1CartesianVector.md) & multiplier) <br>_Multiplies the_ [_**Equinoctial**_](classastrea_1_1astro_1_1Equinoctial.md) _state vector by a scalar._ |
|  [**Equinoctial**](classastrea_1_1astro_1_1Equinoctial.md) | [**operator+**](#function-operator_3) ([**const**](classastrea_1_1astro_1_1CartesianVector.md) [**Equinoctial**](classastrea_1_1astro_1_1Equinoctial.md) & other) const<br>_Adds two_ [_**Equinoctial**_](classastrea_1_1astro_1_1Equinoctial.md) _objects._ |
|  [**Equinoctial**](classastrea_1_1astro_1_1Equinoctial.md) & | [**operator+=**](#function-operator_4) ([**const**](classastrea_1_1astro_1_1CartesianVector.md) [**Equinoctial**](classastrea_1_1astro_1_1Equinoctial.md) & other) <br>_Adds another_ [_**Equinoctial**_](classastrea_1_1astro_1_1Equinoctial.md) _object to the current one._ |
|  [**Equinoctial**](classastrea_1_1astro_1_1Equinoctial.md) | [**operator-**](#function-operator-) ([**const**](classastrea_1_1astro_1_1CartesianVector.md) [**Equinoctial**](classastrea_1_1astro_1_1Equinoctial.md) & other) const<br>_Subtracts another_ [_**Equinoctial**_](classastrea_1_1astro_1_1Equinoctial.md) _object from the current one._ |
|  [**Equinoctial**](classastrea_1_1astro_1_1Equinoctial.md) & | [**operator-=**](#function-operator-_1) ([**const**](classastrea_1_1astro_1_1CartesianVector.md) [**Equinoctial**](classastrea_1_1astro_1_1Equinoctial.md) & other) <br>_Subtracts another_ [_**Equinoctial**_](classastrea_1_1astro_1_1Equinoctial.md) _object from the current one._ |
|  [**EquinoctialPartial**](classastrea_1_1astro_1_1EquinoctialPartial.md) | [**operator/**](#function-operator_5) ([**const**](classastrea_1_1astro_1_1CartesianVector.md) [**Time**](classastrea_1_1astro_1_1CartesianVector.md) & time) const<br>_Divides the_ [_**Equinoctial**_](classastrea_1_1astro_1_1Equinoctial.md) _state vector by a time._ |
|  [**Equinoctial**](classastrea_1_1astro_1_1Equinoctial.md) | [**operator/**](#function-operator_6) ([**const**](classastrea_1_1astro_1_1CartesianVector.md) [**Unitless**](classastrea_1_1astro_1_1CartesianVector.md) & divisor) const<br>_Divides the_ [_**Equinoctial**_](classastrea_1_1astro_1_1Equinoctial.md) _state vector by a scalar._ |
|  [**Equinoctial**](classastrea_1_1astro_1_1Equinoctial.md) & | [**operator/=**](#function-operator_7) ([**const**](classastrea_1_1astro_1_1CartesianVector.md) [**Unitless**](classastrea_1_1astro_1_1CartesianVector.md) & divisor) <br>_Divides the_ [_**Equinoctial**_](classastrea_1_1astro_1_1Equinoctial.md) _state vector by a scalar._ |
|  [**Equinoctial**](classastrea_1_1astro_1_1Equinoctial.md) & | [**operator=**](#function-operator_8) ([**Equinoctial**](classastrea_1_1astro_1_1Equinoctial.md) && other) noexcept<br>_Move assignment operator for_ [_**Equinoctial**_](classastrea_1_1astro_1_1Equinoctial.md) _._ |
|  [**Equinoctial**](classastrea_1_1astro_1_1Equinoctial.md) & | [**operator=**](#function-operator_9) ([**const**](classastrea_1_1astro_1_1CartesianVector.md) [**Equinoctial**](classastrea_1_1astro_1_1Equinoctial.md) & other) <br>_Copy assignment operator for_ [_**Equinoctial**_](classastrea_1_1astro_1_1Equinoctial.md) _._ |
|  [**bool**](classastrea_1_1astro_1_1CartesianVector.md) | [**operator==**](#function-operator_10) ([**const**](classastrea_1_1astro_1_1CartesianVector.md) [**Equinoctial**](classastrea_1_1astro_1_1Equinoctial.md) & other) const<br>_Checks if two_ [_**Equinoctial**_](classastrea_1_1astro_1_1Equinoctial.md) _objects are equal._ |
|   | [**~Equinoctial**](#function-equinoctial) () = default<br>_Default destructor for_ [_**Equinoctial**_](classastrea_1_1astro_1_1Equinoctial.md) _._ |


## Public Static Functions

| Type | Name |
| ---: | :--- |
|  [**Equinoctial**](classastrea_1_1astro_1_1Equinoctial.md) | [**GEO**](#function-geo) ([**const**](classastrea_1_1astro_1_1CartesianVector.md) [**GravParam**](classastrea_1_1astro_1_1CartesianVector.md) & mu) <br>_A static method to create_ [_**Equinoctial**_](classastrea_1_1astro_1_1Equinoctial.md) _state vectors for a GEO orbit._ |
|  [**Equinoctial**](classastrea_1_1astro_1_1Equinoctial.md) | [**GPS**](#function-gps) ([**const**](classastrea_1_1astro_1_1CartesianVector.md) [**GravParam**](classastrea_1_1astro_1_1CartesianVector.md) & mu) <br>_A static method to create_ [_**Equinoctial**_](classastrea_1_1astro_1_1Equinoctial.md) _state vectors for a GPS orbit._ |
|  [**Equinoctial**](classastrea_1_1astro_1_1Equinoctial.md) | [**HMEO**](#function-hmeo) ([**const**](classastrea_1_1astro_1_1CartesianVector.md) [**GravParam**](classastrea_1_1astro_1_1CartesianVector.md) & mu) <br>_A static method to create_ [_**Equinoctial**_](classastrea_1_1astro_1_1Equinoctial.md) _state vectors for a HMEO orbit._ |
|  [**Equinoctial**](classastrea_1_1astro_1_1Equinoctial.md) | [**LEO**](#function-leo) ([**const**](classastrea_1_1astro_1_1CartesianVector.md) [**GravParam**](classastrea_1_1astro_1_1CartesianVector.md) & mu) <br>_A static method to create_ [_**Equinoctial**_](classastrea_1_1astro_1_1Equinoctial.md) _state vectors for a LEO orbit._ |
|  [**Equinoctial**](classastrea_1_1astro_1_1Equinoctial.md) | [**LMEO**](#function-lmeo) ([**const**](classastrea_1_1astro_1_1CartesianVector.md) [**GravParam**](classastrea_1_1astro_1_1CartesianVector.md) & mu) <br>_A static method to create_ [_**Equinoctial**_](classastrea_1_1astro_1_1Equinoctial.md) _state vectors for a LMEO orbit._ |


























## Detailed Description


The equinoctial elements are a set of orbital elements that are particularly useful for describing orbits in a way that avoids singularities, especially for near-circular orbits. They are defined in terms of the semilatus rectum and the components of the eccentricity vector. 


    
## Public Functions Documentation




### function Equinoctial [1/8]

_Constructs an_ [_**Equinoctial**_](classastrea_1_1astro_1_1Equinoctial.md) _object with default values._
```C++
inline astrea::astro::Equinoctial::Equinoctial (
    Unitless scale=0.0 *astrea::detail::unitless
) 
```





**Parameters:**


* `scale` A scaling factor to initialize the elements, typically used for unit conversion. 




        

<hr>



### function Equinoctial [2/8]

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



### function Equinoctial [3/8]

_Constructs an_ [_**Equinoctial**_](classastrea_1_1astro_1_1Equinoctial.md) _object from another_[_**Equinoctial**_](classastrea_1_1astro_1_1Equinoctial.md) _object._
```C++
inline astrea::astro::Equinoctial::Equinoctial (
    const  Equinoctial & elements,
    const  GravParam & mu
) 
```





**Parameters:**


* `elements` The [**Equinoctial**](classastrea_1_1astro_1_1Equinoctial.md) object to copy. 
* `sys` The astrodynamics system context for conversion. 




        

<hr>



### function Equinoctial [4/8]

_Constructs an_ [_**Equinoctial**_](classastrea_1_1astro_1_1Equinoctial.md) _object from_[_**Keplerian**_](classastrea_1_1astro_1_1Keplerian.md) _elements._
```C++
astrea::astro::Equinoctial::Equinoctial (
    const  Keplerian & elements,
    const  GravParam & mu
) 
```





**Parameters:**


* `elements` The [**Keplerian**](classastrea_1_1astro_1_1Keplerian.md) elements to convert. 
* `sys` The astrodynamics system context for conversion. 




        

<hr>



### function Equinoctial [5/8]

_Constructs an_ [_**Equinoctial**_](classastrea_1_1astro_1_1Equinoctial.md) _object from_[_**Cartesian**_](classastrea_1_1astro_1_1Cartesian.md) _elements._
```C++
astrea::astro::Equinoctial::Equinoctial (
    const  Cartesian & elements,
    const  GravParam & mu
) 
```





**Parameters:**


* `elements` The [**Cartesian**](classastrea_1_1astro_1_1Cartesian.md) elements to convert. 
* `sys` The astrodynamics system context for conversion. 




        

<hr>



### function Equinoctial [6/8]

_Constructs an_ [_**Equinoctial**_](classastrea_1_1astro_1_1Equinoctial.md) _object from_[_**OrbitalElements**_](classastrea_1_1astro_1_1OrbitalElements.md) _._
```C++
astrea::astro::Equinoctial::Equinoctial (
    const  OrbitalElements & elements,
    const  GravParam & mu
) 
```





**Parameters:**


* `elements` The [**OrbitalElements**](classastrea_1_1astro_1_1OrbitalElements.md) to convert. 
* `sys` The astrodynamics system context for conversion. 




        

<hr>



### function Equinoctial [7/8]

_Copy constructor for_ [_**Equinoctial**_](classastrea_1_1astro_1_1Equinoctial.md) _._
```C++
astrea::astro::Equinoctial::Equinoctial (
    const  Equinoctial & other
) 
```




<hr>



### function Equinoctial [8/8]

_Move constructor for_ [_**Equinoctial**_](classastrea_1_1astro_1_1Equinoctial.md) _._
```C++
astrea::astro::Equinoctial::Equinoctial (
    Equinoctial && other
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



### function interpolate 

_Interpolates the_ [_**Equinoctial**_](classastrea_1_1astro_1_1Equinoctial.md) _state vector between two time instances._
```C++
Equinoctial astrea::astro::Equinoctial::interpolate (
    const  Time & thisTime,
    const  Time & otherTime,
    const  Equinoctial & other,
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
    const  Equinoctial & other
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
    const  Equinoctial & other
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
    const  Equinoctial & other
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
    const  Equinoctial & other
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
    const  Equinoctial & other
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
EquinoctialPartial astrea::astro::Equinoctial::operator/ (
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
    Equinoctial && other
) noexcept
```





**Parameters:**


* `other` Another [**Equinoctial**](classastrea_1_1astro_1_1Equinoctial.md) object 



**Returns:**

[**Equinoctial**](classastrea_1_1astro_1_1Equinoctial.md)& Reference to the current object 





        

<hr>



### function operator= 

_Copy assignment operator for_ [_**Equinoctial**_](classastrea_1_1astro_1_1Equinoctial.md) _._
```C++
Equinoctial & astrea::astro::Equinoctial::operator= (
    const  Equinoctial & other
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
    const  Equinoctial & other
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
The documentation for this class was generated from the following file `astrea/astro/astro/state/orbital_elements/instances/Equinoctial.hpp`

