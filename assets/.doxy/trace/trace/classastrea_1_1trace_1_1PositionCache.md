

# Class astrea::trace::PositionCache



[**ClassList**](annotated.md) **>** [**astrea**](namespaceastrea.md) **>** [**trace**](namespaceastrea_1_1trace.md) **>** [**PositionCache**](classastrea_1_1trace_1_1PositionCache.md)



_Contiguous memory cache for platform positions across time._ [More...](#detailed-description)

* `#include <PositionCache.hpp>`





































## Public Functions

| Type | Name |
| ---: | :--- |
|   | [**PositionCache**](#function-positioncache) () = default<br> |
|  std::size\_t | [**add\_platform**](#function-add_platform) (std::size\_t platformId, std::size\_t nTimesteps) <br>_Add a platform to the cache._  |
|  void | [**clear**](#function-clear) () <br>_Clear all data._  |
|  std::size\_t | [**get\_index**](#function-get_index) (std::size\_t platformId) const<br>_Convert platform ID to internal index._  |
|  std::size\_t | [**get\_platform\_id**](#function-get_platform_id) (std::size\_t platformIdx) const<br>_Get platform ID from internal index._  |
|  const EcefRadiusVec & | [**get\_position\_by\_id**](#function-get_position_by_id) (std::size\_t platformId, std::size\_t timeIdx) const<br>_Get position by platform ID and time index._  |
|  const EcefRadiusVec & | [**get\_position\_by\_index**](#function-get_position_by_index) (std::size\_t platformIdx, std::size\_t timeIdx) const<br>_Get position by platform index and time index (faster)_  |
|  std::size\_t | [**n\_platforms**](#function-n_platforms) () const<br>_Get number of platforms._  |
|  std::size\_t | [**n\_timesteps**](#function-n_timesteps) () const<br>_Get number of timesteps._  |
|  void | [**reserve**](#function-reserve) (std::size\_t nPlatforms) <br>_Reserve space for platforms and timesteps._  |
|  void | [**set\_position**](#function-set_position) (std::size\_t platformIdx, std::size\_t timeIdx, const EcefRadiusVec & position) <br>_Set position for a platform at a specific timestep._  |
|   | [**~PositionCache**](#function-positioncache) () = default<br> |




























## Detailed Description


Uses structure-of-arrays layout for better cache locality and SIMD potential 


    
## Public Functions Documentation




### function PositionCache 

```C++
astrea::trace::PositionCache::PositionCache () = default
```




<hr>



### function add\_platform 

_Add a platform to the cache._ 
```C++
std::size_t astrea::trace::PositionCache::add_platform (
    std::size_t platformId,
    std::size_t nTimesteps
) 
```





**Parameters:**


* `platformId` Unique ID of the platform 
* `nTimesteps` Number of timesteps to cache for this platform 



**Returns:**

std::size\_t Index of the platform in the cache 





        

<hr>



### function clear 

_Clear all data._ 
```C++
void astrea::trace::PositionCache::clear () 
```




<hr>



### function get\_index 

_Convert platform ID to internal index._ 
```C++
std::size_t astrea::trace::PositionCache::get_index (
    std::size_t platformId
) const
```





**Parameters:**


* `platformId` Unique ID of the platform 



**Returns:**

std::size\_t Index of the platform in the cache 





        

<hr>



### function get\_platform\_id 

_Get platform ID from internal index._ 
```C++
std::size_t astrea::trace::PositionCache::get_platform_id (
    std::size_t platformIdx
) const
```





**Parameters:**


* `platformIdx` Index of the platform in the cache 



**Returns:**

std::size\_t Unique ID of the platform 





        

<hr>



### function get\_position\_by\_id 

_Get position by platform ID and time index._ 
```C++
const EcefRadiusVec & astrea::trace::PositionCache::get_position_by_id (
    std::size_t platformId,
    std::size_t timeIdx
) const
```





**Parameters:**


* `platformId` Unique ID of the platform 
* `timeIdx` Index of the timestep 



**Returns:**

const EcefRadiusVec& Cached ECI position vector 





        

<hr>



### function get\_position\_by\_index 

_Get position by platform index and time index (faster)_ 
```C++
const EcefRadiusVec & astrea::trace::PositionCache::get_position_by_index (
    std::size_t platformIdx,
    std::size_t timeIdx
) const
```





**Parameters:**


* `platformIdx` Index of the platform in the cache 
* `timeIdx` Index of the timestep 



**Returns:**

const EcefRadiusVec& Cached ECI position vector 





        

<hr>



### function n\_platforms 

_Get number of platforms._ 
```C++
std::size_t astrea::trace::PositionCache::n_platforms () const
```





**Returns:**

std::size\_t Number of platforms in the cache 





        

<hr>



### function n\_timesteps 

_Get number of timesteps._ 
```C++
std::size_t astrea::trace::PositionCache::n_timesteps () const
```





**Returns:**

std::size\_t Number of timesteps cached per platform 





        

<hr>



### function reserve 

_Reserve space for platforms and timesteps._ 
```C++
void astrea::trace::PositionCache::reserve (
    std::size_t nPlatforms
) 
```





**Parameters:**


* `nPlatforms` Number of platforms to cache 




        

<hr>



### function set\_position 

_Set position for a platform at a specific timestep._ 
```C++
void astrea::trace::PositionCache::set_position (
    std::size_t platformIdx,
    std::size_t timeIdx,
    const EcefRadiusVec & position
) 
```





**Parameters:**


* `platformIdx` Index of the platform in the cache 
* `timeIdx` Index of the timestep 
* `position` ECI position vector to cache 




        

<hr>



### function ~PositionCache 

```C++
astrea::trace::PositionCache::~PositionCache () = default
```




<hr>

------------------------------
The documentation for this class was generated from the following file `astrea/trace/trace/analysis/PositionCache.hpp`

