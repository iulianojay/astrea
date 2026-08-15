

# Class astrea::trace::CircularFieldOfView



[**ClassList**](annotated.md) **>** [**astrea**](namespaceastrea.md) **>** [**trace**](namespaceastrea_1_1trace.md) **>** [**CircularFieldOfView**](classastrea_1_1trace_1_1CircularFieldOfView.md)



_Circular field of view implementation._ [More...](#detailed-description)

* `#include <CircularFieldOfView.hpp>`



Inherits the following classes: [astrea::trace::FieldOfView](classastrea_1_1trace_1_1FieldOfView.md)






















































## Public Functions

| Type | Name |
| ---: | :--- |
|   | [**CircularFieldOfView**](#function-circularfieldofview) (const Angle & halfConeAngle=std::numbers::pi/4.0 \*mp\_units::si::unit\_symbols::rad) <br>_Constructor for_ [_**CircularFieldOfView**_](classastrea_1_1trace_1_1CircularFieldOfView.md) _._ |
| virtual bool | [**contains**](#function-contains) (const astro::CartesianVector&lt; Distance, astro::frames::earth::icrf &gt; & boresight, const astro::CartesianVector&lt; Distance, astro::frames::earth::icrf &gt; & target) const<br>_Checks if a target is within the circular field of view._  |
| virtual Angle | [**max\_half\_angle**](#function-max_half_angle) () override const<br>_Returns the maximum off-boresight half-angle for this field of view._  |
|   | [**~CircularFieldOfView**](#function-circularfieldofview) () = default<br>_Default destructor for_ [_**CircularFieldOfView**_](classastrea_1_1trace_1_1CircularFieldOfView.md) _._ |


## Public Functions inherited from astrea::trace::FieldOfView

See [astrea::trace::FieldOfView](classastrea_1_1trace_1_1FieldOfView.md)

| Type | Name |
| ---: | :--- |
|   | [**FieldOfView**](classastrea_1_1trace_1_1FieldOfView.md#function-fieldofview) () = default<br>_Default constructor for_ [_**FieldOfView**_](classastrea_1_1trace_1_1FieldOfView.md) _._ |
| virtual bool | [**contains**](classastrea_1_1trace_1_1FieldOfView.md#function-contains) (const astro::CartesianVector&lt; Distance, astro::frames::earth::icrf &gt; & boresight, const astro::CartesianVector&lt; Distance, astro::frames::earth::icrf &gt; & target) const = 0<br>_Checks if a target is within the field of view._  |
| virtual Angle | [**max\_half\_angle**](classastrea_1_1trace_1_1FieldOfView.md#function-max_half_angle) () const<br>_Returns the maximum off-boresight half-angle for this field of view._  |
|   | [**~FieldOfView**](classastrea_1_1trace_1_1FieldOfView.md#function-fieldofview) () = default<br>_Virtual destructor for_ [_**FieldOfView**_](classastrea_1_1trace_1_1FieldOfView.md) _._ |






















































## Detailed Description


This class represents a circular field of view defined by a half-cone angle. 


    
## Public Functions Documentation




### function CircularFieldOfView 

_Constructor for_ [_**CircularFieldOfView**_](classastrea_1_1trace_1_1CircularFieldOfView.md) _._
```C++
astrea::trace::CircularFieldOfView::CircularFieldOfView (
    const Angle & halfConeAngle=std::numbers::pi/4.0 *mp_units::si::unit_symbols::rad
) 
```





**Parameters:**


* `halfConeAngle` The half-cone angle defining the field of view. 




        

<hr>



### function contains 

_Checks if a target is within the circular field of view._ 
```C++
virtual bool astrea::trace::CircularFieldOfView::contains (
    const astro::CartesianVector< Distance, astro::frames::earth::icrf > & boresight,
    const astro::CartesianVector< Distance, astro::frames::earth::icrf > & target
) const
```





**Parameters:**


* `boresight` The boresight vector of the sensor. 
* `target` The target vector to check. 



**Returns:**

true If the target is within the circular field of view. 




**Returns:**

false If the target is outside the circular field of view. 





        
Implements [*astrea::trace::FieldOfView::contains*](classastrea_1_1trace_1_1FieldOfView.md#function-contains)


<hr>



### function max\_half\_angle 

_Returns the maximum off-boresight half-angle for this field of view._ 
```C++
inline virtual Angle astrea::trace::CircularFieldOfView::max_half_angle () override const
```



Used for spatial index culling to determine the maximum sensor footprint radius. The default returns π/2 rad, a conservative bound covering the full hemisphere.




**Returns:**

Angle Maximum off-boresight half-angle. 





        
Implements [*astrea::trace::FieldOfView::max\_half\_angle*](classastrea_1_1trace_1_1FieldOfView.md#function-max_half_angle)


<hr>



### function ~CircularFieldOfView 

_Default destructor for_ [_**CircularFieldOfView**_](classastrea_1_1trace_1_1CircularFieldOfView.md) _._
```C++
astrea::trace::CircularFieldOfView::~CircularFieldOfView () = default
```




<hr>

------------------------------
The documentation for this class was generated from the following file `astrea/trace/trace/platforms/sensors/fov/CircularFieldOfView.hpp`

