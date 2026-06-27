

# Class astrea::trace::PolygonalFieldOfView



[**ClassList**](annotated.md) **>** [**astrea**](namespaceastrea.md) **>** [**trace**](namespaceastrea_1_1trace.md) **>** [**PolygonalFieldOfView**](classastrea_1_1trace_1_1PolygonalFieldOfView.md)



_Polygonal field of view implementation._ [More...](#detailed-description)

* `#include <PolygonalFieldOfView.hpp>`



Inherits the following classes: [astrea::trace::FieldOfView](classastrea_1_1trace_1_1FieldOfView.md)






















































## Public Functions

| Type | Name |
| ---: | :--- |
|   | [**PolygonalFieldOfView**](#function-polygonalfieldofview-13) (const Angle & halfConeAngle=std::numbers::pi/4.0 \*mp\_units::angular::unit\_symbols::rad, const int & nPoints=72) <br>_Constructor for_ [_**PolygonalFieldOfView**_](classastrea_1_1trace_1_1PolygonalFieldOfView.md) _._ |
|   | [**PolygonalFieldOfView**](#function-polygonalfieldofview-23) (const Angle & halfConeWidth, const Angle & halfConeHeight, const int & nPoints=72) <br>_Constructor for_ [_**PolygonalFieldOfView**_](classastrea_1_1trace_1_1PolygonalFieldOfView.md) _with specified half-cone width and height._ |
|   | [**PolygonalFieldOfView**](#function-polygonalfieldofview-33) (const gtl::flat\_hash\_map&lt; Angle, Angle &gt; & points) <br>_Constructor for_ [_**PolygonalFieldOfView**_](classastrea_1_1trace_1_1PolygonalFieldOfView.md) _with a set of points._ |
| virtual bool | [**contains**](#function-contains) (const astro::CartesianVector&lt; Distance, astro::frames::earth::icrf &gt; & boresight, const astro::CartesianVector&lt; Distance, astro::frames::earth::icrf &gt; & target) const<br>_Checks if a target is within the polygonal field of view._  |
| virtual Angle | [**max\_half\_angle**](#function-max_half_angle) () override const<br>_Returns the maximum off-boresight half-angle for this field of view._  |
|   | [**~PolygonalFieldOfView**](#function-polygonalfieldofview) () = default<br>_Default destructor for_ [_**PolygonalFieldOfView**_](classastrea_1_1trace_1_1PolygonalFieldOfView.md) _._ |


## Public Functions inherited from astrea::trace::FieldOfView

See [astrea::trace::FieldOfView](classastrea_1_1trace_1_1FieldOfView.md)

| Type | Name |
| ---: | :--- |
|   | [**FieldOfView**](classastrea_1_1trace_1_1FieldOfView.md#function-fieldofview) () = default<br>_Default constructor for_ [_**FieldOfView**_](classastrea_1_1trace_1_1FieldOfView.md) _._ |
| virtual bool | [**contains**](classastrea_1_1trace_1_1FieldOfView.md#function-contains) (const astro::CartesianVector&lt; Distance, astro::frames::earth::icrf &gt; & boresight, const astro::CartesianVector&lt; Distance, astro::frames::earth::icrf &gt; & target) const = 0<br>_Checks if a target is within the field of view._  |
| virtual Angle | [**max\_half\_angle**](classastrea_1_1trace_1_1FieldOfView.md#function-max_half_angle) () const<br>_Returns the maximum off-boresight half-angle for this field of view._  |
|   | [**~FieldOfView**](classastrea_1_1trace_1_1FieldOfView.md#function-fieldofview) () = default<br>_Virtual destructor for_ [_**FieldOfView**_](classastrea_1_1trace_1_1FieldOfView.md) _._ |






















































## Detailed Description


This class represents a polygonal field of view defined by a set of points. 


    
## Public Functions Documentation




### function PolygonalFieldOfView [1/3]

_Constructor for_ [_**PolygonalFieldOfView**_](classastrea_1_1trace_1_1PolygonalFieldOfView.md) _._
```C++
astrea::trace::PolygonalFieldOfView::PolygonalFieldOfView (
    const Angle & halfConeAngle=std::numbers::pi/4.0 *mp_units::angular::unit_symbols::rad,
    const int & nPoints=72
) 
```





**Parameters:**


* `halfConeAngle` The half-cone angle defining the field of view. 
* `nPoints` The number of points defining the polygon. 




        

<hr>



### function PolygonalFieldOfView [2/3]

_Constructor for_ [_**PolygonalFieldOfView**_](classastrea_1_1trace_1_1PolygonalFieldOfView.md) _with specified half-cone width and height._
```C++
astrea::trace::PolygonalFieldOfView::PolygonalFieldOfView (
    const Angle & halfConeWidth,
    const Angle & halfConeHeight,
    const int & nPoints=72
) 
```





**Parameters:**


* `halfConeWidth` The half-cone width angle. 
* `halfConeHeight` The half-cone height angle. 
* `nPoints` The number of points defining the polygon. 




        

<hr>



### function PolygonalFieldOfView [3/3]

_Constructor for_ [_**PolygonalFieldOfView**_](classastrea_1_1trace_1_1PolygonalFieldOfView.md) _with a set of points._
```C++
inline astrea::trace::PolygonalFieldOfView::PolygonalFieldOfView (
    const gtl::flat_hash_map< Angle, Angle > & points
) 
```





**Parameters:**


* `points` A map of angles defining the polygonal field of view. 




        

<hr>



### function contains 

_Checks if a target is within the polygonal field of view._ 
```C++
virtual bool astrea::trace::PolygonalFieldOfView::contains (
    const astro::CartesianVector< Distance, astro::frames::earth::icrf > & boresight,
    const astro::CartesianVector< Distance, astro::frames::earth::icrf > & target
) const
```





**Parameters:**


* `boresight` The boresight vector of the sensor. 
* `target` The target vector to check. 



**Returns:**

true If the target is within the polygonal field of view. 




**Returns:**

false If the target is outside the polygonal field of view. 





        
Implements [*astrea::trace::FieldOfView::contains*](classastrea_1_1trace_1_1FieldOfView.md#function-contains)


<hr>



### function max\_half\_angle 

_Returns the maximum off-boresight half-angle for this field of view._ 
```C++
inline virtual Angle astrea::trace::PolygonalFieldOfView::max_half_angle () override const
```



Used for spatial index culling to determine the maximum sensor footprint radius. The default returns π/2 rad, a conservative bound covering the full hemisphere.




**Returns:**

Angle Maximum off-boresight half-angle. 





        
Implements [*astrea::trace::FieldOfView::max\_half\_angle*](classastrea_1_1trace_1_1FieldOfView.md#function-max_half_angle)


<hr>



### function ~PolygonalFieldOfView 

_Default destructor for_ [_**PolygonalFieldOfView**_](classastrea_1_1trace_1_1PolygonalFieldOfView.md) _._
```C++
astrea::trace::PolygonalFieldOfView::~PolygonalFieldOfView () = default
```




<hr>

------------------------------
The documentation for this class was generated from the following file `astrea/trace/trace/platforms/sensors/fov/PolygonalFieldOfView.hpp`

