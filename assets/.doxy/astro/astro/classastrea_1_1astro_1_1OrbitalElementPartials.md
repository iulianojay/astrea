

# Class astrea::astro::OrbitalElementPartials



[**ClassList**](annotated.md) **>** [**astrea**](namespaceastrea.md) **>** [**astro**](namespaceastrea_1_1astro.md) **>** [**OrbitalElementPartials**](classastrea_1_1astro_1_1OrbitalElementPartials.md)



_Class representing partial derivatives of orbital elements._ [More...](#detailed-description)

* `#include <OrbitalElements.hpp>`





































## Public Functions

| Type | Name |
| ---: | :--- |
|   | [**OrbitalElementPartials**](#function-orbitalelementpartials-14) () <br>_Default constructor initializing to_ [_**CartesianPartial**_](classastrea_1_1astro_1_1CartesianPartial.md) _elements._ |
|   | [**OrbitalElementPartials**](#function-orbitalelementpartials-24) ([**CartesianPartial**](classastrea_1_1astro_1_1CartesianPartial.md)&lt; frame &gt; elements) <br>_Constructor initializing with_ [_**CartesianPartial**_](classastrea_1_1astro_1_1CartesianPartial.md) _elements._ |
|   | [**OrbitalElementPartials**](#function-orbitalelementpartials-34) ([**KeplerianPartial**](classastrea_1_1astro_1_1KeplerianPartial.md)&lt; frame &gt; elements) <br>_Constructor initializing with_ [_**KeplerianPartial**_](classastrea_1_1astro_1_1KeplerianPartial.md) _elements._ |
|   | [**OrbitalElementPartials**](#function-orbitalelementpartials-44) ([**EquinoctialPartial**](classastrea_1_1astro_1_1EquinoctialPartial.md)&lt; frame &gt; elements) <br>_Constructor initializing with_ [_**EquinoctialPartial**_](classastrea_1_1astro_1_1EquinoctialPartial.md) _elements._ |
|  const PartialVariant & | [**extract**](#function-extract-12) () const<br>_Extracts the underlying orbital element partials as a variant._  |
|  PartialVariant & | [**extract**](#function-extract-22) () <br>_Extracts the underlying orbital element partials as a variant._  |
|  std::vector&lt; double &gt; | [**force\_to\_double\_vector**](#function-force_to_double_vector) () const<br>_Converts the_ [_**OrbitalElementPartials**_](classastrea_1_1astro_1_1OrbitalElementPartials.md) _to a vector of Unitless values._ |
|  constexpr std::size\_t | [**index**](#function-index) () const<br>_Returns the index of the current orbital element partials in the variant._  |
|  [**OrbitalElements**](classastrea_1_1astro_1_1OrbitalElements.md) | [**operator\***](#function-operator) (const Time & time) const<br>_Converts the current orbital element partials to a specific type._  |




























## Detailed Description


This class encapsulates the partial derivatives of orbital elements, allowing for operations such as multiplication by time to obtain Cartesian&lt;frames::primary&gt; state vectors. 


    
## Public Functions Documentation




### function OrbitalElementPartials [1/4]

_Default constructor initializing to_ [_**CartesianPartial**_](classastrea_1_1astro_1_1CartesianPartial.md) _elements._
```C++
inline astrea::astro::OrbitalElementPartials::OrbitalElementPartials () 
```




<hr>



### function OrbitalElementPartials [2/4]

_Constructor initializing with_ [_**CartesianPartial**_](classastrea_1_1astro_1_1CartesianPartial.md) _elements._
```C++
template<IsFrame auto frame>
inline astrea::astro::OrbitalElementPartials::OrbitalElementPartials (
    CartesianPartial < frame > elements
) 
```





**Parameters:**


* `elements` The orbital element partials to initialize with. 




        

<hr>



### function OrbitalElementPartials [3/4]

_Constructor initializing with_ [_**KeplerianPartial**_](classastrea_1_1astro_1_1KeplerianPartial.md) _elements._
```C++
template<IsFrame auto frame>
inline astrea::astro::OrbitalElementPartials::OrbitalElementPartials (
    KeplerianPartial < frame > elements
) 
```





**Parameters:**


* `elements` The orbital element partials to initialize with. 




        

<hr>



### function OrbitalElementPartials [4/4]

_Constructor initializing with_ [_**EquinoctialPartial**_](classastrea_1_1astro_1_1EquinoctialPartial.md) _elements._
```C++
template<IsFrame auto frame>
inline astrea::astro::OrbitalElementPartials::OrbitalElementPartials (
    EquinoctialPartial < frame > elements
) 
```





**Parameters:**


* `elements` The orbital element partials to initialize with. 




        

<hr>



### function extract [1/2]

_Extracts the underlying orbital element partials as a variant._ 
```C++
const PartialVariant & astrea::astro::OrbitalElementPartials::extract () const
```





**Returns:**

const PartialVariant& Reference to the underlying orbital element partials variant. 





        

<hr>



### function extract [2/2]

_Extracts the underlying orbital element partials as a variant._ 
```C++
PartialVariant & astrea::astro::OrbitalElementPartials::extract () 
```





**Returns:**

PartialVariant& Reference to the underlying orbital element partials variant. 





        

<hr>



### function force\_to\_double\_vector 

_Converts the_ [_**OrbitalElementPartials**_](classastrea_1_1astro_1_1OrbitalElementPartials.md) _to a vector of Unitless values._
```C++
std::vector< double > astrea::astro::OrbitalElementPartials::force_to_double_vector () const
```





**Returns:**

std::vector&lt;Unitless&gt; Vector containing the orbital elements as unitless values. 





        

<hr>



### function index 

_Returns the index of the current orbital element partials in the variant._ 
```C++
inline constexpr std::size_t astrea::astro::OrbitalElementPartials::index () const
```





**Returns:**

std::size\_t The index of the current orbital element partials in the variant. 





        

<hr>



### function operator\* 

_Converts the current orbital element partials to a specific type._ 
```C++
OrbitalElements astrea::astro::OrbitalElementPartials::operator* (
    const Time & time
) const
```





**Template parameters:**


* `T` The type to convert to. 



**Parameters:**


* `mu` The gravitational parameter to use for the conversion. 



**Returns:**

A reference to the current orbital element partials after conversion. 





        

<hr>

------------------------------
The documentation for this class was generated from the following file `astrea/astro/astro/state/orbital_elements/OrbitalElements.hpp`

