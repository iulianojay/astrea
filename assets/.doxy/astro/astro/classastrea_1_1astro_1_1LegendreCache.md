

# Class astrea::astro::LegendreCache

**template &lt;IsCelestialBody auto \_body\_, std::size\_t \_degree\_, std::size\_t \_order\_&gt;**



[**ClassList**](annotated.md) **>** [**astrea**](namespaceastrea.md) **>** [**astro**](namespaceastrea_1_1astro.md) **>** [**LegendreCache**](classastrea_1_1astro_1_1LegendreCache.md)



_Class to cache Legendre polynomial coefficients for a given celestial_ _body_ _, degree, and order._[More...](#detailed-description)

* `#include <LegendreCache.hpp>`





































## Public Functions

| Type | Name |
| ---: | :--- |
|   | [**LegendreCache**](#function-legendrecache) () <br>_Builds the cache for Legendre polynomials and coefficients._  |
|  const Unitless & | [**get\_cosine\_coefficient**](#function-get_cosine_coefficient) (const std::size\_t & n, const std::size\_t & m) const<br>_Gets the cosine coefficient for given n and m._  |
|  const Unitless & | [**get\_sine\_coefficient**](#function-get_sine_coefficient) (const std::size\_t & n, const std::size\_t & m) const<br>_Gets the sine coefficient for given n and m._  |
|   | [**~LegendreCache**](#function-legendrecache) () = default<br>_Default destructor for_ [_**LegendreCache**_](classastrea_1_1astro_1_1LegendreCache.md) _._ |




























## Detailed Description




**Template parameters:**


* `_body_` The celestial _body_ for which the Legendre coefficients are cached 
* `_degree_` The maximum degree of the spherical harmonics 
* `_order_` The maximum order of the spherical harmonics 




    
## Public Functions Documentation




### function LegendreCache 

_Builds the cache for Legendre polynomials and coefficients._ 
```C++
astrea::astro::LegendreCache::LegendreCache () 
```





**Parameters:**


* `degree` Degree of the spherical harmonics 
* `order` Order of the spherical harmonics 




        

<hr>



### function get\_cosine\_coefficient 

_Gets the cosine coefficient for given n and m._ 
```C++
const Unitless & astrea::astro::LegendreCache::get_cosine_coefficient (
    const std::size_t & n,
    const std::size_t & m
) const
```





**Parameters:**


* `n` Degree of the polynomial 
* `m` Order of the polynomial 



**Returns:**

Unitless The value of the cosine coefficient Cnm 





        

<hr>



### function get\_sine\_coefficient 

_Gets the sine coefficient for given n and m._ 
```C++
const Unitless & astrea::astro::LegendreCache::get_sine_coefficient (
    const std::size_t & n,
    const std::size_t & m
) const
```





**Parameters:**


* `n` Degree of the polynomial 
* `m` Order of the polynomial 



**Returns:**

Unitless The value of the sine coefficient Snm 





        

<hr>



### function ~LegendreCache 

_Default destructor for_ [_**LegendreCache**_](classastrea_1_1astro_1_1LegendreCache.md) _._
```C++
astrea::astro::LegendreCache::~LegendreCache () = default
```




<hr>

------------------------------
The documentation for this class was generated from the following file `astrea/astro/astro/propagation/force_models/LegendreCache.hpp`

