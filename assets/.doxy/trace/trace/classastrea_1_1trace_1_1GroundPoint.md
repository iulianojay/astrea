

# Class astrea::trace::GroundPoint



[**ClassList**](annotated.md) **>** [**astrea**](namespaceastrea.md) **>** [**trace**](namespaceastrea_1_1trace.md) **>** [**GroundPoint**](classastrea_1_1trace_1_1GroundPoint.md)



_Represents a point on the ground with latitude, longitude, and altitude._ [More...](#detailed-description)

* `#include <GroundPoint.hpp>`



Inherits the following classes: [astrea::trace::AccessObject](classastrea_1_1trace_1_1AccessObject.md),  astro::FrameReference


Inherited by the following classes: [astrea::trace::GroundStation](classastrea_1_1trace_1_1GroundStation.md)




















































## Public Functions

| Type | Name |
| ---: | :--- |
|   | [**GroundPoint**](#function-groundpoint) (const astro::CelestialBody \* parent=nullptr, const Angle & latitutde=0.0 \*mp\_units::angular::unit\_symbols::deg, const Angle & longitude=0.0 \*mp\_units::angular::unit\_symbols::deg, const Distance & altitude=0.0 \*mp\_units::si::unit\_symbols::km) <br>_Constructs a_ [_**GroundPoint**_](classastrea_1_1trace_1_1GroundPoint.md) _with specified latitude, longitude, and altitude._ |
|  const Distance & | [**get\_altitude**](#function-get_altitude) () const<br>_Gets the altitude of the ground point above sea level._  |
| virtual std::size\_t | [**get\_id**](#function-get_id) () const<br>_Get the unique identifier for the ground station._  |
|  astro::CartesianVector&lt; Distance, astro::frames::earth::icrf &gt; | [**get\_inertial\_position**](#function-get_inertial_position) (const astro::Date & date) const<br>_Get the position of the frame in Earth-Centered Inertial coordinates._  |
|  astro::CartesianVector&lt; Velocity, astro::frames::earth::icrf &gt; | [**get\_inertial\_velocity**](#function-get_inertial_velocity) (const astro::Date & date) const<br>_Get the velocity of the frame in Earth-Centered Inertial coordinates._  |
|  const Angle & | [**get\_latitude**](#function-get_latitude) () const<br>_Gets the latitude of the ground point._  |
|  const astro::Geodetic & | [**get\_lla**](#function-get_lla) () const<br>_Gets the geodetic coordinates of the ground point._  |
|  const Angle & | [**get\_longitude**](#function-get_longitude) () const<br>_Gets the longitude of the ground point._  |
|  std::string | [**get\_name**](#function-get_name) () const<br> |
|  const astro::CelestialBody \* | [**get\_parent**](#function-get_parent) () const<br>_Gets the parent celestial body of the ground point._  |
|  astro::CartesianVector&lt; Distance, astro::frames::earth::earth\_fixed &gt; | [**get\_position**](#function-get_position) () const<br>_Get the position of the frame in Earth-Centered-Earth-Fixed (ECEF) coordinates._  |
|  bool | [**operator==**](#function-operator) (const [**GroundPoint**](classastrea_1_1trace_1_1GroundPoint.md) & other) const<br>_Equality operator for comparing two_ [_**GroundPoint**_](classastrea_1_1trace_1_1GroundPoint.md) _objects._ |
| virtual  | [**~GroundPoint**](#function-groundpoint) () = default<br>_Destructor for the_ [_**GroundPoint**_](classastrea_1_1trace_1_1GroundPoint.md) _class._ |


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
|  std::size\_t | [**\_id**](#variable-_id)  <br>_Unique identifier for the ground station, generated from its properties._  |
|  astro::Geodetic | [**\_lla**](#variable-_lla)  <br>_Geodetic coordinates of the ground point._  |
|  const astro::CelestialBody \* | [**\_parent**](#variable-_parent)  <br>_Pointer to the parent celestial body._  |
































## Protected Functions

| Type | Name |
| ---: | :--- |
|  std::size\_t | [**generate\_id**](#function-generate_id) () <br>_Generates a unique identifier for the ground station based on its properties. This method is called in the constructor to ensure that each ground station has a unique ID._  |


## Protected Functions inherited from astrea::trace::AccessObject

See [astrea::trace::AccessObject](classastrea_1_1trace_1_1AccessObject.md)

| Type | Name |
| ---: | :--- |
|   | [**AccessObject**](classastrea_1_1trace_1_1AccessObject.md#function-accessobject) () = default<br>_Default constructor._  |
| virtual  | [**~AccessObject**](classastrea_1_1trace_1_1AccessObject.md#function-accessobject) () = default<br>_Default destructor._  |






## Detailed Description


This class is used to define a ground point in terms of its geographic coordinates and altitude above sea level. It can be extended to include additional properties or methods as needed for specific applications. 


    
## Public Functions Documentation




### function GroundPoint 

_Constructs a_ [_**GroundPoint**_](classastrea_1_1trace_1_1GroundPoint.md) _with specified latitude, longitude, and altitude._
```C++
astrea::trace::GroundPoint::GroundPoint (
    const astro::CelestialBody * parent=nullptr,
    const Angle & latitutde=0.0 *mp_units::angular::unit_symbols::deg,
    const Angle & longitude=0.0 *mp_units::angular::unit_symbols::deg,
    const Distance & altitude=0.0 *mp_units::si::unit_symbols::km
) 
```





**Parameters:**


* `latitutde` The latitude of the ground point (default is 0 degrees). 
* `longitude` The longitude of the ground point (default is 0 degrees). 
* `altitude` The altitude of the ground point above sea level (default is 0 kilometers). 




        

<hr>



### function get\_altitude 

_Gets the altitude of the ground point above sea level._ 
```C++
const Distance & astrea::trace::GroundPoint::get_altitude () const
```





**Returns:**

Distance The altitude of the ground point. 





        

<hr>



### function get\_id 

_Get the unique identifier for the ground station._ 
```C++
virtual std::size_t astrea::trace::GroundPoint::get_id () const
```





**Returns:**

std::size\_t The unique identifier for the ground station. 





        
Implements [*astrea::trace::AccessObject::get\_id*](classastrea_1_1trace_1_1AccessObject.md#function-get_id)


<hr>



### function get\_inertial\_position 

_Get the position of the frame in Earth-Centered Inertial coordinates._ 
```C++
astro::CartesianVector< Distance, astro::frames::earth::icrf > astrea::trace::GroundPoint::get_inertial_position (
    const astro::Date & date
) const
```





**Parameters:**


* `date` The date for which to get the position. 



**Returns:**

CartesianVector&lt;Distance, frames::earth::icrf&gt; 





        

<hr>



### function get\_inertial\_velocity 

_Get the velocity of the frame in Earth-Centered Inertial coordinates._ 
```C++
astro::CartesianVector< Velocity, astro::frames::earth::icrf > astrea::trace::GroundPoint::get_inertial_velocity (
    const astro::Date & date
) const
```





**Parameters:**


* `date` The date for which to get the velocity. 



**Returns:**

CartesianVector&lt;Velocity, frames::earth::icrf&gt; 





        

<hr>



### function get\_latitude 

_Gets the latitude of the ground point._ 
```C++
const Angle & astrea::trace::GroundPoint::get_latitude () const
```





**Returns:**

Angle The latitude of the ground point. 





        

<hr>



### function get\_lla 

_Gets the geodetic coordinates of the ground point._ 
```C++
const astro::Geodetic & astrea::trace::GroundPoint::get_lla () const
```





**Returns:**

const Geodetic& The geodetic coordinates (latitude, longitude, altitude) of the ground point. 





        

<hr>



### function get\_longitude 

_Gets the longitude of the ground point._ 
```C++
const Angle & astrea::trace::GroundPoint::get_longitude () const
```





**Returns:**

Angle The longitude of the ground point. 





        

<hr>



### function get\_name 

```C++
std::string astrea::trace::GroundPoint::get_name () const
```




<hr>



### function get\_parent 

_Gets the parent celestial body of the ground point._ 
```C++
const astro::CelestialBody * astrea::trace::GroundPoint::get_parent () const
```





**Returns:**

const CelestialBody\* Pointer to the parent celestial body. 





        

<hr>



### function get\_position 

_Get the position of the frame in Earth-Centered-Earth-Fixed (ECEF) coordinates._ 
```C++
astro::CartesianVector< Distance, astro::frames::earth::earth_fixed > astrea::trace::GroundPoint::get_position () const
```





**Parameters:**


* `date` The date for which to get the position. 



**Returns:**

CartesianVector&lt;Distance, frames::earth::earth\_fixed&gt; 





        

<hr>



### function operator== 

_Equality operator for comparing two_ [_**GroundPoint**_](classastrea_1_1trace_1_1GroundPoint.md) _objects._
```C++
bool astrea::trace::GroundPoint::operator== (
    const GroundPoint & other
) const
```





**Parameters:**


* `other` The other [**GroundPoint**](classastrea_1_1trace_1_1GroundPoint.md) to compare with. 



**Returns:**

true if the two [**GroundPoint**](classastrea_1_1trace_1_1GroundPoint.md) objects are equal, false otherwise. 





        

<hr>



### function ~GroundPoint 

_Destructor for the_ [_**GroundPoint**_](classastrea_1_1trace_1_1GroundPoint.md) _class._
```C++
virtual astrea::trace::GroundPoint::~GroundPoint () = default
```




<hr>
## Protected Attributes Documentation




### variable \_id 

_Unique identifier for the ground station, generated from its properties._ 
```C++
std::size_t astrea::trace::GroundPoint::_id;
```




<hr>



### variable \_lla 

_Geodetic coordinates of the ground point._ 
```C++
astro::Geodetic astrea::trace::GroundPoint::_lla;
```




<hr>



### variable \_parent 

_Pointer to the parent celestial body._ 
```C++
const astro::CelestialBody* astrea::trace::GroundPoint::_parent;
```




<hr>
## Protected Functions Documentation




### function generate\_id 

_Generates a unique identifier for the ground station based on its properties. This method is called in the constructor to ensure that each ground station has a unique ID._ 
```C++
std::size_t astrea::trace::GroundPoint::generate_id () 
```




<hr>

------------------------------
The documentation for this class was generated from the following file `astrea/trace/trace/platforms/ground/GroundPoint.hpp`

