

# Struct std::hash&lt; astrea::astro::CelestialBody &gt;

**template &lt;&gt;**



[**ClassList**](annotated.md) **>** [**std**](namespacestd.md) **>** [**hash&lt; astrea::astro::CelestialBody &gt;**](structstd_1_1hash_3_01astrea_1_1astro_1_1CelestialBody_01_4.md)



_Hash function for CelestialBody._ 

* `#include <CelestialBody.hpp>`





































## Public Functions

| Type | Name |
| ---: | :--- |
|  std::size\_t | [**operator()**](#function-operator) ([**astrea::astro::CelestialBody**](classastrea_1_1astro_1_1CelestialBody.md) const & body) noexcept const<br>_Computes a hash value for a CelestialBody object._  |




























## Public Functions Documentation




### function operator() 

_Computes a hash value for a CelestialBody object._ 
```C++
inline std::size_t std::hash< astrea::astro::CelestialBody >::operator() (
    astrea::astro::CelestialBody const & body
) noexcept const
```





**Parameters:**


* `body` The CelestialBody object to hash. 



**Returns:**

std::size\_t The computed hash value. 





        

<hr>

------------------------------
The documentation for this class was generated from the following file `astrea/astro/astro/systems/CelestialBody.hpp`

