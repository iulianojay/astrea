

# Class astrea::astro::LegendreCache

**template &lt;IsCelestialBody [**auto**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) \_body\_, std::size\_t \_degree\_, std::size\_t \_order\_&gt;**



[**ClassList**](annotated.md) **>** [**astrea**](namespaceastrea.md) **>** [**astro**](namespaceastrea_1_1astro.md) **>** [**LegendreCache**](classastrea_1_1astro_1_1LegendreCache.md)










































## Public Functions

| Type | Name |
| ---: | :--- |
|   | [**LegendreCache**](#function-legendrecache) () <br>_Builds the cache for Legendre polynomials and coefficients._  |
|  [**Unitless**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) | [**get\_cosine\_coefficient**](#function-get_cosine_coefficient) ([**const**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) std::size\_t & n, [**const**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) std::size\_t & m) const<br>_Gets the cosine coefficient for given n and m._  |
|  [**Unitless**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) | [**get\_sine\_coefficient**](#function-get_sine_coefficient) ([**const**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) std::size\_t & n, [**const**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) std::size\_t & m) const<br>_Gets the sine coefficient for given n and m._  |
|   | [**~LegendreCache**](#function-legendrecache) () = default<br>_Default destructor for_ [_**LegendreCache**_](classastrea_1_1astro_1_1LegendreCache.md) _._ |




























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
Unitless astrea::astro::LegendreCache::get_cosine_coefficient (
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
Unitless astrea::astro::LegendreCache::get_sine_coefficient (
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
The documentation for this class was generated from the following file `astrea/astro/astro/propagation/force_models/OblatenessForce.hpp`

