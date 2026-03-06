

# Class astrea::trace::SpatialIndex



[**ClassList**](annotated.md) **>** [**astrea**](namespaceastrea.md) **>** [**trace**](namespaceastrea_1_1trace.md) **>** [**SpatialIndex**](classastrea_1_1trace_1_1SpatialIndex.md)



_Spatial index for efficient ground point queries._ [More...](#detailed-description)

* `#include <SpatialIndex.hpp>`





































## Public Functions

| Type | Name |
| ---: | :--- |
|   | [**SpatialIndex**](#function-spatialindex) (const Angle & binSize=10.0 \*mp\_units::angular::unit\_symbols::deg) <br>_Construct spatial index with specified bin size._  |
|  void | [**add\_ground\_point**](#function-add_ground_point) (std::size\_t groundPointIdx, const Angle & lat, const Angle & lon) <br>_Add a ground point to the index._  |
|  void | [**clear**](#function-clear) () <br>_Clear all ground points from the index._  |
|  std::vector&lt; std::size\_t &gt; | [**get\_all\_ground\_points**](#function-get_all_ground_points) () const<br>_Get all ground point indices._  |
|  std::unordered\_set&lt; std::size\_t &gt; | [**get\_nearby\_ground\_points**](#function-get_nearby_ground_points) (const Angle & lat, const Angle & lon, const Angle & radius) const<br>_Get ground points within a radius of a lat/lon position._  |




























## Detailed Description


Divides the Earth's surface into geographic bins to quickly find which ground points are near a satellite's subsatellite point 


    
## Public Functions Documentation




### function SpatialIndex 

_Construct spatial index with specified bin size._ 
```C++
astrea::trace::SpatialIndex::SpatialIndex (
    const Angle & binSize=10.0 *mp_units::angular::unit_symbols::deg
) 
```





**Parameters:**


* `binSize` Angular size of each bin (smaller = more bins, finer resolution) 




        

<hr>



### function add\_ground\_point 

_Add a ground point to the index._ 
```C++
void astrea::trace::SpatialIndex::add_ground_point (
    std::size_t groundPointIdx,
    const Angle & lat,
    const Angle & lon
) 
```





**Parameters:**


* `groundPointIdx` Index of the ground point being added (used for lookup) 
* `lat` Latitude of the ground point 
* `lon` Longitude of the ground point 




        

<hr>



### function clear 

_Clear all ground points from the index._ 
```C++
void astrea::trace::SpatialIndex::clear () 
```




<hr>



### function get\_all\_ground\_points 

_Get all ground point indices._ 
```C++
std::vector< std::size_t > astrea::trace::SpatialIndex::get_all_ground_points () const
```





**Returns:**

std::vector&lt;std::size\_t&gt; Vector of all ground point indices in the index 





        

<hr>



### function get\_nearby\_ground\_points 

_Get ground points within a radius of a lat/lon position._ 
```C++
std::unordered_set< std::size_t > astrea::trace::SpatialIndex::get_nearby_ground_points (
    const Angle & lat,
    const Angle & lon,
    const Angle & radius
) const
```





**Parameters:**


* `lat` Latitude of center point 
* `lon` Longitude of center point 
* `radius` Angular radius to search 



**Returns:**

Set of ground point indices within radius 





        

<hr>

------------------------------
The documentation for this class was generated from the following file `astrea/trace/trace/analysis/SpatialIndex.hpp`

