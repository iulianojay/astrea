

# Struct astrea::trace::GeographicBin



[**ClassList**](annotated.md) **>** [**astrea**](namespaceastrea.md) **>** [**trace**](namespaceastrea_1_1trace.md) **>** [**GeographicBin**](structastrea_1_1trace_1_1GeographicBin.md)



_Geographic bin for spatial partitioning._ 

* `#include <SpatialIndex.hpp>`





















## Public Attributes

| Type | Name |
| ---: | :--- |
|  std::vector&lt; std::size\_t &gt; | [**groundPointIndices**](#variable-groundpointindices)  <br> |
|  Angle | [**latMax**](#variable-latmax)  <br> |
|  Angle | [**latMin**](#variable-latmin)  <br> |
|  Angle | [**lonMax**](#variable-lonmax)  <br> |
|  Angle | [**lonMin**](#variable-lonmin)  <br> |
















## Public Functions

| Type | Name |
| ---: | :--- |
|  bool | [**contains**](#function-contains) (const Angle & lat, const Angle & lon) const<br> |




























## Public Attributes Documentation




### variable groundPointIndices 

```C++
std::vector<std::size_t> astrea::trace::GeographicBin::groundPointIndices;
```




<hr>



### variable latMax 

```C++
Angle astrea::trace::GeographicBin::latMax;
```




<hr>



### variable latMin 

```C++
Angle astrea::trace::GeographicBin::latMin;
```




<hr>



### variable lonMax 

```C++
Angle astrea::trace::GeographicBin::lonMax;
```




<hr>



### variable lonMin 

```C++
Angle astrea::trace::GeographicBin::lonMin;
```




<hr>
## Public Functions Documentation




### function contains 

```C++
inline bool astrea::trace::GeographicBin::contains (
    const Angle & lat,
    const Angle & lon
) const
```




<hr>

------------------------------
The documentation for this class was generated from the following file `astrea/trace/trace/analysis/SpatialIndex.hpp`

