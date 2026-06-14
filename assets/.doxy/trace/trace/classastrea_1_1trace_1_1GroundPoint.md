

# Class astrea::trace::GroundPoint

**template &lt;astro::IsCelestialBody auto \_body\_&gt;**



[**ClassList**](annotated.md) **>** [**astrea**](namespaceastrea.md) **>** [**trace**](namespaceastrea_1_1trace.md) **>** [**GroundPoint**](classastrea_1_1trace_1_1GroundPoint.md)



_Represents a point on the surface of a celestial body with latitude, longitude, and altitude._ [More...](#detailed-description)

* `#include <GroundPoint.hpp>`



Inherits the following classes: [astrea::trace::AccessObject](classastrea_1_1trace_1_1AccessObject.md)


Inherited by the following classes: [astrea::trace::GroundStation](classastrea_1_1trace_1_1GroundStation.md)
























## Public Static Attributes

| Type | Name |
| ---: | :--- |
|  constexpr auto | [**body**](#variable-body)   = `\_body\_`<br>_The celestial body this ground point resides on._  |




























## Public Functions

| Type | Name |
| ---: | :--- |
|   | [**GroundPoint**](#function-groundpoint) (const Angle & latitude=0.0 \*mp\_units::angular::unit\_symbols::deg, const Angle & longitude=0.0 \*mp\_units::angular::unit\_symbols::deg, const Distance & altitude=0.0 \*mp\_units::si::unit\_symbols::km) <br>_Constructs a_ [_**GroundPoint**_](classastrea_1_1trace_1_1GroundPoint.md) _with specified latitude, longitude, and altitude._ |
|  const Distance & | [**get\_altitude**](#function-get_altitude) () const<br>_Returns the altitude of the ground point above the surface._  |
| virtual std::size\_t | [**get\_id**](#function-get_id) () override const<br>_Returns the unique identifier for this ground point._  |
|  const Angle & | [**get\_latitude**](#function-get_latitude) () const<br>_Returns the latitude of the ground point._  |
|  const astro::Geodetic&lt; \_body\_ &gt; & | [**get\_lla**](#function-get_lla) () const<br>_Returns the geodetic coordinates of the ground point._  |
|  const Angle & | [**get\_longitude**](#function-get_longitude) () const<br>_Returns the longitude of the ground point._  |
|  std::string | [**get\_name**](#function-get_name) () const<br>_Returns a human-readable name for the ground point._  |
|  auto | [**get\_position**](#function-get_position-12) () const<br>_Returns the position in the body-fixed frame._  |
|  auto | [**get\_position**](#function-get_position-22) (const astro::Date & date) const<br>_Returns the inertial position at the given date._  |
|  auto | [**get\_velocity**](#function-get_velocity) (const astro::Date & date) const<br>_Returns the inertial velocity at the given date, computed from the body's rotation rate._  |
|  bool | [**operator==**](#function-operator) (const [**GroundPoint**](classastrea_1_1trace_1_1GroundPoint.md) & other) const<br>_Equality operator — compares geodetic coordinates._  |
| virtual  | [**~GroundPoint**](#function-groundpoint) () = default<br> |


## Public Functions inherited from astrea::trace::AccessObject

See [astrea::trace::AccessObject](classastrea_1_1trace_1_1AccessObject.md)

| Type | Name |
| ---: | :--- |
|  void | [**add\_access**](classastrea_1_1trace_1_1AccessObject.md#function-add_access) (const std::size\_t & receiverId, const [**RiseSetArray**](classastrea_1_1trace_1_1RiseSetArray.md) & access) <br>_Adds access times for a specific receiver._  |
|  void | [**drop\_access**](classastrea_1_1trace_1_1AccessObject.md#function-drop_access) (const std::size\_t & receiverId, const [**RiseSetArray**](classastrea_1_1trace_1_1RiseSetArray.md) & access) <br>_Drops access times for a specific receiver._  |
|  [**AccessArray**](classastrea_1_1trace_1_1AccessArray.md) & | [**get\_accesses**](classastrea_1_1trace_1_1AccessObject.md#function-get_accesses-12) () <br>_Gets the access times for this object._  |
|  const [**AccessArray**](classastrea_1_1trace_1_1AccessArray.md) & | [**get\_accesses**](classastrea_1_1trace_1_1AccessObject.md#function-get_accesses-22) () const<br>_Gets the access times for this object (const version)._  |
| virtual std::size\_t | [**get\_id**](classastrea_1_1trace_1_1AccessObject.md#function-get_id) () const = 0<br>_Pure virtual function to get the ID of the object._  |














## Protected Attributes

| Type | Name |
| ---: | :--- |
|  std::size\_t | [**\_id**](#variable-_id)  <br>_Unique identifier, generated at construction._  |
|  astro::Geodetic&lt; \_body\_ &gt; | [**\_lla**](#variable-_lla)  <br>_Geodetic coordinates of the ground point._  |


































## Protected Functions inherited from astrea::trace::AccessObject

See [astrea::trace::AccessObject](classastrea_1_1trace_1_1AccessObject.md)

| Type | Name |
| ---: | :--- |
|   | [**AccessObject**](classastrea_1_1trace_1_1AccessObject.md#function-accessobject) () = default<br>_Default constructor._  |
| virtual  | [**~AccessObject**](classastrea_1_1trace_1_1AccessObject.md#function-accessobject) () = default<br>_Default destructor._  |






## Detailed Description




**Template parameters:**


* `_body_` The celestial body NTTP this ground point resides on. 




    
## Public Static Attributes Documentation




### variable body 

_The celestial body this ground point resides on._ 
```C++
constexpr auto astrea::trace::GroundPoint< _body_ >::body;
```




<hr>
## Public Functions Documentation




### function GroundPoint 

_Constructs a_ [_**GroundPoint**_](classastrea_1_1trace_1_1GroundPoint.md) _with specified latitude, longitude, and altitude._
```C++
inline astrea::trace::GroundPoint::GroundPoint (
    const Angle & latitude=0.0 *mp_units::angular::unit_symbols::deg,
    const Angle & longitude=0.0 *mp_units::angular::unit_symbols::deg,
    const Distance & altitude=0.0 *mp_units::si::unit_symbols::km
) 
```





**Parameters:**


* `latitude` The latitude of the ground point (default is 0 degrees). 
* `longitude` The longitude of the ground point (default is 0 degrees). 
* `altitude` The altitude of the ground point above the surface (default is 0 km). 




        

<hr>



### function get\_altitude 

_Returns the altitude of the ground point above the surface._ 
```C++
inline const Distance & astrea::trace::GroundPoint::get_altitude () const
```




<hr>



### function get\_id 

_Returns the unique identifier for this ground point._ 
```C++
inline virtual std::size_t astrea::trace::GroundPoint::get_id () override const
```



Implements [*astrea::trace::AccessObject::get\_id*](classastrea_1_1trace_1_1AccessObject.md#function-get_id)


<hr>



### function get\_latitude 

_Returns the latitude of the ground point._ 
```C++
inline const Angle & astrea::trace::GroundPoint::get_latitude () const
```




<hr>



### function get\_lla 

_Returns the geodetic coordinates of the ground point._ 
```C++
inline const astro::Geodetic< _body_ > & astrea::trace::GroundPoint::get_lla () const
```




<hr>



### function get\_longitude 

_Returns the longitude of the ground point._ 
```C++
inline const Angle & astrea::trace::GroundPoint::get_longitude () const
```




<hr>



### function get\_name 

_Returns a human-readable name for the ground point._ 
```C++
inline std::string astrea::trace::GroundPoint::get_name () const
```




<hr>



### function get\_position [1/2]

_Returns the position in the body-fixed frame._ 
```C++
inline auto astrea::trace::GroundPoint::get_position () const
```




<hr>



### function get\_position [2/2]

_Returns the inertial position at the given date._ 
```C++
inline auto astrea::trace::GroundPoint::get_position (
    const astro::Date & date
) const
```




<hr>



### function get\_velocity 

_Returns the inertial velocity at the given date, computed from the body's rotation rate._ 
```C++
inline auto astrea::trace::GroundPoint::get_velocity (
    const astro::Date & date
) const
```




<hr>



### function operator== 

_Equality operator — compares geodetic coordinates._ 
```C++
inline bool astrea::trace::GroundPoint::operator== (
    const GroundPoint & other
) const
```




<hr>



### function ~GroundPoint 

```C++
virtual astrea::trace::GroundPoint::~GroundPoint () = default
```




<hr>
## Protected Attributes Documentation




### variable \_id 

_Unique identifier, generated at construction._ 
```C++
std::size_t astrea::trace::GroundPoint< _body_ >::_id;
```




<hr>



### variable \_lla 

_Geodetic coordinates of the ground point._ 
```C++
astro::Geodetic<_body_> astrea::trace::GroundPoint< _body_ >::_lla;
```




<hr>

------------------------------
The documentation for this class was generated from the following file `astrea/trace/trace/platforms/ground/GroundPoint.hpp`

