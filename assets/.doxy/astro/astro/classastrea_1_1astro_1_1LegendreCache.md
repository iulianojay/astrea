

# Class astrea::astro::LegendreCache



[**ClassList**](annotated.md) **>** [**astrea**](namespaceastrea.md) **>** [**astro**](namespaceastrea_1_1astro.md) **>** [**LegendreCache**](classastrea_1_1astro_1_1LegendreCache.md)










































## Public Functions

| Type | Name |
| ---: | :--- |
|   | [**LegendreCache**](#function-legendrecache-12) () = default<br>_Default constructor for_ [_**LegendreCache**_](classastrea_1_1astro_1_1LegendreCache.md) _._ |
|   | [**LegendreCache**](#function-legendrecache-22) (const [**AstrodynamicsSystem**](classastrea_1_1astro_1_1AstrodynamicsSystem.md) & sys, const std::size\_t & degree, const std::size\_t & order) <br>_Builds the cache for Legendre polynomials and coefficients._  |
|  Unitless | [**get\_cosine\_coefficient**](#function-get_cosine_coefficient) (const std::size\_t & n, const std::size\_t & m) const<br>_Gets the cosine coefficient for given n and m._  |
|  Unitless | [**get\_normalizing\_coefficient**](#function-get_normalizing_coefficient) (const std::size\_t & n, const std::size\_t & m) const<br>_Gets the normalizing coefficient for given n and m._  |
|  Unitless | [**get\_sine\_coefficient**](#function-get_sine_coefficient) (const std::size\_t & n, const std::size\_t & m) const<br>_Gets the sine coefficient for given n and m._  |
|   | [**~LegendreCache**](#function-legendrecache) () = default<br>_Default destructor for_ [_**LegendreCache**_](classastrea_1_1astro_1_1LegendreCache.md) _._ |




























## Public Functions Documentation




### function LegendreCache [1/2]

_Default constructor for_ [_**LegendreCache**_](classastrea_1_1astro_1_1LegendreCache.md) _._
```C++
astrea::astro::LegendreCache::LegendreCache () = default
```




<hr>



### function LegendreCache [2/2]

_Builds the cache for Legendre polynomials and coefficients._ 
```C++
astrea::astro::LegendreCache::LegendreCache (
    const AstrodynamicsSystem & sys,
    const std::size_t & degree,
    const std::size_t & order
) 
```





**Parameters:**


* `sys` Astrodynamics system containing celestial body data 
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



### function get\_normalizing\_coefficient 

_Gets the normalizing coefficient for given n and m._ 
```C++
Unitless astrea::astro::LegendreCache::get_normalizing_coefficient (
    const std::size_t & n,
    const std::size_t & m
) const
```





**Parameters:**


* `n` Degree of the polynomial 
* `m` Order of the polynomial 



**Returns:**

Unitless The value of the normalizing coefficient Nnm 





        

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

