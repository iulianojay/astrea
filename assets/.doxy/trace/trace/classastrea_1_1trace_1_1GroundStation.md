

# Class astrea::trace::GroundStation

**template &lt;astro::IsCelestialBody auto \_body\_&gt;**



[**ClassList**](annotated.md) **>** [**astrea**](namespaceastrea.md) **>** [**trace**](namespaceastrea_1_1trace.md) **>** [**GroundStation**](classastrea_1_1trace_1_1GroundStation.md)



_Ground station on the surface of a celestial body, with sensors._ [More...](#detailed-description)

* `#include <GroundStation.hpp>`



Inherits the following classes: [astrea::trace::GroundPoint](classastrea_1_1trace_1_1GroundPoint.md),  SensorPlatform


































## Public Static Attributes inherited from astrea::trace::GroundPoint

See [astrea::trace::GroundPoint](classastrea_1_1trace_1_1GroundPoint.md)

| Type | Name |
| ---: | :--- |
|  constexpr auto | [**body**](classastrea_1_1trace_1_1GroundPoint.md#variable-body)   = `\_body\_`<br>_The celestial body this ground point resides on._  |








































## Public Functions

| Type | Name |
| ---: | :--- |
|   | [**GroundStation**](#function-groundstation) (const Angle & latitude, const Angle & longitude, const Distance & altitude=0.0 \*mp\_units::si::unit\_symbols::km, const std::string name="Unnamed", const std::vector&lt; [**SensorParameters**](classastrea_1_1trace_1_1SensorParameters.md) &gt; & sensors={}) <br>_Constructs a_ [_**GroundStation**_](classastrea_1_1trace_1_1GroundStation.md) _._ |
| virtual std::size\_t | [**get\_id**](#function-get_id) () override const<br>_Gets the unique identifier for this ground station._  |
|  std::string | [**get\_name**](#function-get_name) () const<br>_Gets the human-readable name of the ground station._  |
|  auto | [**get\_position**](#function-get_position-12) () const<br>_Gets the position of the ground station in the body-fixed frame._  |
|  astro::RadiusVector&lt; astro::frames::primary &gt; | [**get\_position**](#function-get_position-22) (const astro::Date & date) const<br>_Gets the inertial position of the spacecraft at a specific date._  |
|  astro::VelocityVector&lt; astro::frames::primary &gt; | [**get\_velocity**](#function-get_velocity) (const astro::Date & date) const<br>_Gets the inertial velocity of the spacecraft at a specific date._  |
|   | [**~GroundStation**](#function-groundstation) () = default<br>_Default destructor for_ [_**GroundStation**_](classastrea_1_1trace_1_1GroundStation.md) _._ |


## Public Functions inherited from astrea::trace::GroundPoint

See [astrea::trace::GroundPoint](classastrea_1_1trace_1_1GroundPoint.md)

| Type | Name |
| ---: | :--- |
|   | [**GroundPoint**](classastrea_1_1trace_1_1GroundPoint.md#function-groundpoint) (const Angle & latitude=0.0 \*mp\_units::si::unit\_symbols::deg, const Angle & longitude=0.0 \*mp\_units::si::unit\_symbols::deg, const Distance & altitude=0.0 \*mp\_units::si::unit\_symbols::km) <br>_Constructs a_ [_**GroundPoint**_](classastrea_1_1trace_1_1GroundPoint.md) _with specified latitude, longitude, and altitude._ |
|  const Distance & | [**get\_altitude**](classastrea_1_1trace_1_1GroundPoint.md#function-get_altitude) () const<br>_Returns the altitude of the ground point above the surface._  |
| virtual std::size\_t | [**get\_id**](classastrea_1_1trace_1_1GroundPoint.md#function-get_id) () override const<br>_Returns the unique identifier for this ground point._  |
|  const Angle & | [**get\_latitude**](classastrea_1_1trace_1_1GroundPoint.md#function-get_latitude) () const<br>_Returns the latitude of the ground point._  |
|  const astro::Geodetic&lt; \_body\_ &gt; & | [**get\_lla**](classastrea_1_1trace_1_1GroundPoint.md#function-get_lla) () const<br>_Returns the geodetic coordinates of the ground point._  |
|  const Angle & | [**get\_longitude**](classastrea_1_1trace_1_1GroundPoint.md#function-get_longitude) () const<br>_Returns the longitude of the ground point._  |
|  std::string | [**get\_name**](classastrea_1_1trace_1_1GroundPoint.md#function-get_name) () const<br>_Returns a human-readable name for the ground point._  |
|  auto | [**get\_position**](classastrea_1_1trace_1_1GroundPoint.md#function-get_position-12) () const<br>_Returns the position in the body-fixed frame._  |
|  auto | [**get\_position**](classastrea_1_1trace_1_1GroundPoint.md#function-get_position-22) (const astro::Date & date) const<br>_Returns the inertial position at the given date._  |
|  auto | [**get\_velocity**](classastrea_1_1trace_1_1GroundPoint.md#function-get_velocity) (const astro::Date & date) const<br>_Returns the inertial velocity at the given date, computed from the body's rotation rate._  |
|  bool | [**operator==**](classastrea_1_1trace_1_1GroundPoint.md#function-operator) (const [**GroundPoint**](classastrea_1_1trace_1_1GroundPoint.md) & other) const<br>_Equality operator — compares geodetic coordinates._  |
| virtual  | [**~GroundPoint**](classastrea_1_1trace_1_1GroundPoint.md#function-groundpoint) () = default<br> |


## Public Functions inherited from astrea::trace::AccessObject

See [astrea::trace::AccessObject](classastrea_1_1trace_1_1AccessObject.md)

| Type | Name |
| ---: | :--- |
|  void | [**add\_access**](classastrea_1_1trace_1_1AccessObject.md#function-add_access) (const std::size\_t & receiverId, const [**RiseSetArray**](classastrea_1_1trace_1_1RiseSetArray.md) & access) <br>_Adds access times for a specific receiver._  |
|  void | [**drop\_access**](classastrea_1_1trace_1_1AccessObject.md#function-drop_access) (const std::size\_t & receiverId, const [**RiseSetArray**](classastrea_1_1trace_1_1RiseSetArray.md) & access) <br>_Drops access times for a specific receiver._  |
|  [**AccessArray**](classastrea_1_1trace_1_1AccessArray.md) & | [**get\_accesses**](classastrea_1_1trace_1_1AccessObject.md#function-get_accesses-12) () <br>_Gets the access times for this object._  |
|  const [**AccessArray**](classastrea_1_1trace_1_1AccessArray.md) & | [**get\_accesses**](classastrea_1_1trace_1_1AccessObject.md#function-get_accesses-22) () const<br>_Gets the access times for this object (const version)._  |
| virtual std::size\_t | [**get\_id**](classastrea_1_1trace_1_1AccessObject.md#function-get_id) () const = 0<br>_Pure virtual function to get the ID of the object._  |






















## Protected Attributes inherited from astrea::trace::GroundPoint

See [astrea::trace::GroundPoint](classastrea_1_1trace_1_1GroundPoint.md)

| Type | Name |
| ---: | :--- |
|  std::size\_t | [**\_id**](classastrea_1_1trace_1_1GroundPoint.md#variable-_id)  <br>_Unique identifier, generated at construction._  |
|  astro::Geodetic&lt; \_body\_ &gt; | [**\_lla**](classastrea_1_1trace_1_1GroundPoint.md#variable-_lla)  <br>_Geodetic coordinates of the ground point._  |


















































## Protected Functions inherited from astrea::trace::AccessObject

See [astrea::trace::AccessObject](classastrea_1_1trace_1_1AccessObject.md)

| Type | Name |
| ---: | :--- |
|   | [**AccessObject**](classastrea_1_1trace_1_1AccessObject.md#function-accessobject) () = default<br>_Default constructor._  |
| virtual  | [**~AccessObject**](classastrea_1_1trace_1_1AccessObject.md#function-accessobject) () = default<br>_Default destructor._  |








## Detailed Description




**Template parameters:**


* `_body_` The celestial body NTTP this station resides on. 




    
## Public Functions Documentation




### function GroundStation 

_Constructs a_ [_**GroundStation**_](classastrea_1_1trace_1_1GroundStation.md) _._
```C++
inline astrea::trace::GroundStation::GroundStation (
    const Angle & latitude,
    const Angle & longitude,
    const Distance & altitude=0.0 *mp_units::si::unit_symbols::km,
    const std::string name="Unnamed",
    const std::vector< SensorParameters > & sensors={}
) 
```





**Parameters:**


* `latitude` Geodetic latitude. 
* `longitude` Longitude. 
* `altitude` Altitude above the surface (default 0 km). 
* `name` Human-readable name (default "Unnamed"). 
* `sensors` [**Sensor**](classastrea_1_1trace_1_1Sensor.md) parameters to attach (default none). 




        

<hr>



### function get\_id 

_Gets the unique identifier for this ground station._ 
```C++
inline virtual std::size_t astrea::trace::GroundStation::get_id () override const
```





**Returns:**

std::size\_t The unique identifier for this ground station. 





        
Implements [*astrea::trace::GroundPoint::get\_id*](classastrea_1_1trace_1_1GroundPoint.md#function-get_id)


<hr>



### function get\_name 

_Gets the human-readable name of the ground station._ 
```C++
inline std::string astrea::trace::GroundStation::get_name () const
```





**Returns:**

std::string The name of the ground station. 





        

<hr>



### function get\_position [1/2]

_Gets the position of the ground station in the body-fixed frame._ 
```C++
inline auto astrea::trace::GroundStation::get_position () const
```





**Returns:**

astro::RadiusVector&lt;astro::frames::Geodetic&lt;_body_&gt;::_fixed\_frame_&gt; The position of the ground station in the body-fixed frame. 





        

<hr>



### function get\_position [2/2]

_Gets the inertial position of the spacecraft at a specific date._ 
```C++
inline astro::RadiusVector< astro::frames::primary > astrea::trace::GroundStation::get_position (
    const astro::Date & date
) const
```





**Parameters:**


* `date` The date at which to retrieve the position. 



**Returns:**

astro::RadiusVector&lt;astro::frames::primary&gt; The inertial position of the spacecraft. 





        

<hr>



### function get\_velocity 

_Gets the inertial velocity of the spacecraft at a specific date._ 
```C++
inline astro::VelocityVector< astro::frames::primary > astrea::trace::GroundStation::get_velocity (
    const astro::Date & date
) const
```





**Parameters:**


* `date` The date at which to retrieve the velocity. 



**Returns:**

astro::VelocityVector&lt;astro::frames::primary&gt; The inertial velocity of the spacecraft. 





        

<hr>



### function ~GroundStation 

_Default destructor for_ [_**GroundStation**_](classastrea_1_1trace_1_1GroundStation.md) _._
```C++
astrea::trace::GroundStation::~GroundStation () = default
```




<hr>

------------------------------
The documentation for this class was generated from the following file `astrea/trace/trace/platforms/ground/GroundStation.hpp`

