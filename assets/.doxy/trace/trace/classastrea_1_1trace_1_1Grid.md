

# Class astrea::trace::Grid

**template &lt;astro::IsCelestialBody auto \_body\_&gt;**



[**ClassList**](annotated.md) **>** [**astrea**](namespaceastrea.md) **>** [**trace**](namespaceastrea_1_1trace.md) **>** [**Grid**](classastrea_1_1trace_1_1Grid.md)



_Class representing a grid of ground points on the surface of a celestial body._ [More...](#detailed-description)

* `#include <Grid.hpp>`

















## Public Types

| Type | Name |
| ---: | :--- |
| typedef typename std::vector&lt; Point &gt;::const\_iterator | [**const\_iterator**](#typedef-const_iterator)  <br>_Constant iterator type for the_ [_**Grid**_](classastrea_1_1trace_1_1Grid.md) _class._ |
| typedef typename std::vector&lt; Point &gt;::iterator | [**iterator**](#typedef-iterator)  <br>_Iterator type for the_ [_**Grid**_](classastrea_1_1trace_1_1Grid.md) _class._ |




















## Public Functions

| Type | Name |
| ---: | :--- |
|   | [**Grid**](#function-grid-13) () = default<br>_Default constructor for the_ [_**Grid**_](classastrea_1_1trace_1_1Grid.md) _class._ |
|   | [**Grid**](#function-grid-23) (const std::vector&lt; Point &gt; & groundPoints) <br>_Construct a_ [_**Grid**_](classastrea_1_1trace_1_1Grid.md) _from an explicit vector of ground points._ |
|   | [**Grid**](#function-grid-33) (const [**LatLon**](namespaceastrea_1_1trace.md#typedef-latlon) & corner1, const [**LatLon**](namespaceastrea_1_1trace.md#typedef-latlon) & corner4, const [**GridType**](namespaceastrea_1_1trace.md#enum-gridtype) & gridType, const Angle & spacing=5.0 \*mp\_units::angular::unit\_symbols::deg, const Unitless & weight=0.0 \*mp\_units::one) <br>_Construct a_ [_**Grid**_](classastrea_1_1trace_1_1Grid.md) _from corner points and a grid type._ |
|  [**iterator**](classastrea_1_1trace_1_1Grid.md#typedef-iterator) | [**begin**](#function-begin-12) () <br>_Returns an iterator to the beginning of the ground points in the grid._  |
|  [**const\_iterator**](classastrea_1_1trace_1_1Grid.md#typedef-const_iterator) | [**begin**](#function-begin-22) () const<br>_Returns a constant iterator to the beginning of the ground points in the grid._  |
|  [**const\_iterator**](classastrea_1_1trace_1_1Grid.md#typedef-const_iterator) | [**cbegin**](#function-cbegin) () const<br>_Returns a constant iterator to the beginning of the ground points in the grid._  |
|  [**const\_iterator**](classastrea_1_1trace_1_1Grid.md#typedef-const_iterator) | [**cend**](#function-cend) () const<br>_Returns a constant iterator to the end of the ground points in the grid._  |
|  [**iterator**](classastrea_1_1trace_1_1Grid.md#typedef-iterator) | [**end**](#function-end-12) () <br>_Returns an iterator to the end of the ground points in the grid._  |
|  [**const\_iterator**](classastrea_1_1trace_1_1Grid.md#typedef-const_iterator) | [**end**](#function-end-22) () const<br>_Returns a constant iterator to the end of the ground points in the grid._  |
|  [**GridType**](namespaceastrea_1_1trace.md#enum-gridtype) | [**get\_grid\_type**](#function-get_grid_type) () const<br>_Get the type of grid._  |
|  Point & | [**operator[]**](#function-operator) (std::size\_t index) <br>_Access a ground point in the grid by index._  |
|  const Point & | [**operator[]**](#function-operator_1) (std::size\_t index) const<br>_Access a ground point in the grid by index (constant version)._  |
|  std::size\_t | [**size**](#function-size) () const<br>_Get the number of ground points in the grid._  |
| virtual  | [**~Grid**](#function-grid) () = default<br>_Default destructor for the_ [_**Grid**_](classastrea_1_1trace_1_1Grid.md) _class._ |




























## Detailed Description


The [**Grid**](classastrea_1_1trace_1_1Grid.md) class manages a collection of ground points, allowing for various grid configurations such as uniform, equal area, and weighted grids. It provides methods to iterate over the ground stations and access their properties.




**Template parameters:**


* `_body_` The celestial body NTTP this grid resides on. 




    
## Public Types Documentation




### typedef const\_iterator 

_Constant iterator type for the_ [_**Grid**_](classastrea_1_1trace_1_1Grid.md) _class._
```C++
using astrea::trace::Grid< _body_ >::const_iterator =  typename std::vector<Point>::const_iterator;
```




<hr>



### typedef iterator 

_Iterator type for the_ [_**Grid**_](classastrea_1_1trace_1_1Grid.md) _class._
```C++
using astrea::trace::Grid< _body_ >::iterator =  typename std::vector<Point>::iterator;
```




<hr>
## Public Functions Documentation




### function Grid [1/3]

_Default constructor for the_ [_**Grid**_](classastrea_1_1trace_1_1Grid.md) _class._
```C++
astrea::trace::Grid::Grid () = default
```



Initializes an empty grid with no ground points. 


        

<hr>



### function Grid [2/3]

_Construct a_ [_**Grid**_](classastrea_1_1trace_1_1Grid.md) _from an explicit vector of ground points._
```C++
inline astrea::trace::Grid::Grid (
    const std::vector< Point > & groundPoints
) 
```





**Parameters:**


* `groundPoints` Vector of [**GroundPoint**](classastrea_1_1trace_1_1GroundPoint.md) objects representing the grid. 




        

<hr>



### function Grid [3/3]

_Construct a_ [_**Grid**_](classastrea_1_1trace_1_1Grid.md) _from corner points and a grid type._
```C++
inline astrea::trace::Grid::Grid (
    const LatLon & corner1,
    const LatLon & corner4,
    const GridType & gridType,
    const Angle & spacing=5.0 *mp_units::angular::unit_symbols::deg,
    const Unitless & weight=0.0 *mp_units::one
) 
```





**Parameters:**


* `corner1` First corner (latitude, longitude). 
* `corner4` Fourth corner (latitude, longitude). 
* `gridType` [**Grid**](classastrea_1_1trace_1_1Grid.md) generation algorithm. 
* `spacing` Angular spacing between points (default 5 deg). 
* `weight` Weighting factor (default 0). 




        

<hr>



### function begin [1/2]

_Returns an iterator to the beginning of the ground points in the grid._ 
```C++
inline iterator astrea::trace::Grid::begin () 
```





**Returns:**

An iterator to the first ground point. 





        

<hr>



### function begin [2/2]

_Returns a constant iterator to the beginning of the ground points in the grid._ 
```C++
inline const_iterator astrea::trace::Grid::begin () const
```





**Returns:**

A constant iterator to the first ground point. 





        

<hr>



### function cbegin 

_Returns a constant iterator to the beginning of the ground points in the grid._ 
```C++
inline const_iterator astrea::trace::Grid::cbegin () const
```





**Returns:**

A constant iterator to the first ground point. 





        

<hr>



### function cend 

_Returns a constant iterator to the end of the ground points in the grid._ 
```C++
inline const_iterator astrea::trace::Grid::cend () const
```





**Returns:**

A constant iterator to one past the last ground point. 





        

<hr>



### function end [1/2]

_Returns an iterator to the end of the ground points in the grid._ 
```C++
inline iterator astrea::trace::Grid::end () 
```





**Returns:**

An iterator to one past the last ground point. 





        

<hr>



### function end [2/2]

_Returns a constant iterator to the end of the ground points in the grid._ 
```C++
inline const_iterator astrea::trace::Grid::end () const
```





**Returns:**

A constant iterator to one past the last ground point. 





        

<hr>



### function get\_grid\_type 

_Get the type of grid._ 
```C++
inline GridType astrea::trace::Grid::get_grid_type () const
```





**Returns:**

GridType The type of grid (uniform, equal area, etc.). 





        

<hr>



### function operator[] 

_Access a ground point in the grid by index._ 
```C++
inline Point & astrea::trace::Grid::operator[] (
    std::size_t index
) 
```





**Parameters:**


* `index` Index of the ground point to access. 



**Returns:**

Reference to the Point at the specified index. 





        

<hr>



### function operator[] 

_Access a ground point in the grid by index (constant version)._ 
```C++
inline const Point & astrea::trace::Grid::operator[] (
    std::size_t index
) const
```





**Parameters:**


* `index` Index of the ground point to access. 



**Returns:**

Constant reference to the Point at the specified index. 





        

<hr>



### function size 

_Get the number of ground points in the grid._ 
```C++
inline std::size_t astrea::trace::Grid::size () const
```





**Returns:**

std::size\_t The number of ground points in the grid. 





        

<hr>



### function ~Grid 

_Default destructor for the_ [_**Grid**_](classastrea_1_1trace_1_1Grid.md) _class._
```C++
virtual astrea::trace::Grid::~Grid () = default
```




<hr>

------------------------------
The documentation for this class was generated from the following file `astrea/trace/trace/platforms/ground/Grid.hpp`

