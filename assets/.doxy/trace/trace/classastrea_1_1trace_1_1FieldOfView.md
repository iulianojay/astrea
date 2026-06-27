

# Class astrea::trace::FieldOfView



[**ClassList**](annotated.md) **>** [**astrea**](namespaceastrea.md) **>** [**trace**](namespaceastrea_1_1trace.md) **>** [**FieldOfView**](classastrea_1_1trace_1_1FieldOfView.md)



_Base class for Field of View (FoV) representations._ [More...](#detailed-description)

* `#include <FieldOfView.hpp>`





Inherited by the following classes: [astrea::trace::CircularFieldOfView](classastrea_1_1trace_1_1CircularFieldOfView.md),  [astrea::trace::PolygonalFieldOfView](classastrea_1_1trace_1_1PolygonalFieldOfView.md)
































## Public Functions

| Type | Name |
| ---: | :--- |
|   | [**FieldOfView**](#function-fieldofview) () = default<br>_Default constructor for_ [_**FieldOfView**_](classastrea_1_1trace_1_1FieldOfView.md) _._ |
| virtual bool | [**contains**](#function-contains) (const astro::CartesianVector&lt; Distance, astro::frames::earth::icrf &gt; & boresight, const astro::CartesianVector&lt; Distance, astro::frames::earth::icrf &gt; & target) const = 0<br>_Checks if a target is within the field of view._  |
| virtual Angle | [**max\_half\_angle**](#function-max_half_angle) () const<br>_Returns the maximum off-boresight half-angle for this field of view._  |
|   | [**~FieldOfView**](#function-fieldofview) () = default<br>_Virtual destructor for_ [_**FieldOfView**_](classastrea_1_1trace_1_1FieldOfView.md) _._ |




























## Detailed Description


This class defines the interface for different types of fields of view. 


    
## Public Functions Documentation




### function FieldOfView 

_Default constructor for_ [_**FieldOfView**_](classastrea_1_1trace_1_1FieldOfView.md) _._
```C++
astrea::trace::FieldOfView::FieldOfView () = default
```




<hr>



### function contains 

_Checks if a target is within the field of view._ 
```C++
virtual bool astrea::trace::FieldOfView::contains (
    const astro::CartesianVector< Distance, astro::frames::earth::icrf > & boresight,
    const astro::CartesianVector< Distance, astro::frames::earth::icrf > & target
) const = 0
```





**Parameters:**


* `boresight` The boresight vector of the sensor. 
* `target` The target vector to check. 



**Returns:**

true If the target is within the field of view. 




**Returns:**

false If the target is outside the field of view. 





        

<hr>



### function max\_half\_angle 

_Returns the maximum off-boresight half-angle for this field of view._ 
```C++
inline virtual Angle astrea::trace::FieldOfView::max_half_angle () const
```



Used for spatial index culling to determine the maximum sensor footprint radius. The default returns π/2 rad, a conservative bound covering the full hemisphere.




**Returns:**

Angle Maximum off-boresight half-angle. 





        

<hr>



### function ~FieldOfView 

_Virtual destructor for_ [_**FieldOfView**_](classastrea_1_1trace_1_1FieldOfView.md) _._
```C++
astrea::trace::FieldOfView::~FieldOfView () = default
```



Ensures proper cleanup of derived classes. 


        

<hr>

------------------------------
The documentation for this class was generated from the following file `astrea/trace/trace/platforms/sensors/fov/FieldOfView.hpp`

