

# Class astrea::trace::GroundStation



[**ClassList**](annotated.md) **>** [**astrea**](namespaceastrea.md) **>** [**trace**](namespaceastrea_1_1trace.md) **>** [**GroundStation**](classastrea_1_1trace_1_1GroundStation.md)



_Ground station class for managing ground-based access. This class inherits from_ [_**GroundPoint**_](classastrea_1_1trace_1_1GroundPoint.md) _,_[_**AccessObject**_](classastrea_1_1trace_1_1AccessObject.md) _, and SensorPlatform. It represents a ground station with a specific latitude, longitude, altitude, and a collection of sensors. It also provides methods to manage access and sensor functionalities._

* `#include <GroundStation.hpp>`



Inherits the following classes: [astrea::trace::GroundPoint](classastrea_1_1trace_1_1GroundPoint.md),  SensorPlatform










































































## Public Functions

| Type | Name |
| ---: | :--- |
|   | [**GroundStation**](#function-groundstation) (const astro::CelestialBody \* parent, const Angle & latitude, const Angle & longitude, const Distance & altitude=0.0 \*mp\_units::si::unit\_symbols::km, const std::string name="Unnammed", const std::vector&lt; [**SensorParameters**](classastrea_1_1trace_1_1SensorParameters.md) &gt; & sensors={}) <br>_Constructs a_ [_**GroundStation**_](classastrea_1_1trace_1_1GroundStation.md) _object with specified latitude, longitude, altitude, sensors, and name._ |
| virtual std::size\_t | [**get\_id**](#function-get_id) () const<br>_Get the ID of the payload._  |
|  astro::CartesianVector&lt; Distance, astro::frames::earth::icrf &gt; | [**get\_inertial\_position**](#function-get_inertial_position) (const astro::Date & date) const<br>_Get the inertial position of the ground station in the ECI frame._  |
|  astro::CartesianVector&lt; Velocity, astro::frames::earth::icrf &gt; | [**get\_inertial\_velocity**](#function-get_inertial_velocity) (const astro::Date & date) const<br>_Get the inertial velocity of the ground station in the ECI frame._  |
|  std::string | [**get\_name**](#function-get_name) () const<br>_Get the name of the ground station._  |
|   | [**~GroundStation**](#function-groundstation) () = default<br>_Default destructor for the_ [_**GroundStation**_](classastrea_1_1trace_1_1GroundStation.md) _class._ |


## Public Functions inherited from astrea::trace::GroundPoint

See [astrea::trace::GroundPoint](classastrea_1_1trace_1_1GroundPoint.md)

| Type | Name |
| ---: | :--- |
|   | [**GroundPoint**](classastrea_1_1trace_1_1GroundPoint.md#function-groundpoint) (const astro::CelestialBody \* parent=nullptr, const Angle & latitutde=0.0 \*mp\_units::angular::unit\_symbols::deg, const Angle & longitude=0.0 \*mp\_units::angular::unit\_symbols::deg, const Distance & altitude=0.0 \*mp\_units::si::unit\_symbols::km) <br>_Constructs a_ [_**GroundPoint**_](classastrea_1_1trace_1_1GroundPoint.md) _with specified latitude, longitude, and altitude._ |
|  const Distance & | [**get\_altitude**](classastrea_1_1trace_1_1GroundPoint.md#function-get_altitude) () const<br>_Gets the altitude of the ground point above sea level._  |
| virtual std::size\_t | [**get\_id**](classastrea_1_1trace_1_1GroundPoint.md#function-get_id) () const<br>_Get the unique identifier for the ground station._  |
|  astro::CartesianVector&lt; Distance, astro::frames::earth::icrf &gt; | [**get\_inertial\_position**](classastrea_1_1trace_1_1GroundPoint.md#function-get_inertial_position) (const astro::Date & date) const<br>_Get the position of the frame in Earth-Centered Inertial coordinates._  |
|  astro::CartesianVector&lt; Velocity, astro::frames::earth::icrf &gt; | [**get\_inertial\_velocity**](classastrea_1_1trace_1_1GroundPoint.md#function-get_inertial_velocity) (const astro::Date & date) const<br>_Get the velocity of the frame in Earth-Centered Inertial coordinates._  |
|  const Angle & | [**get\_latitude**](classastrea_1_1trace_1_1GroundPoint.md#function-get_latitude) () const<br>_Gets the latitude of the ground point._  |
|  const astro::Geodetic & | [**get\_lla**](classastrea_1_1trace_1_1GroundPoint.md#function-get_lla) () const<br>_Gets the geodetic coordinates of the ground point._  |
|  const Angle & | [**get\_longitude**](classastrea_1_1trace_1_1GroundPoint.md#function-get_longitude) () const<br>_Gets the longitude of the ground point._  |
|  std::string | [**get\_name**](classastrea_1_1trace_1_1GroundPoint.md#function-get_name) () const<br> |
|  const astro::CelestialBody \* | [**get\_parent**](classastrea_1_1trace_1_1GroundPoint.md#function-get_parent) () const<br>_Gets the parent celestial body of the ground point._  |
|  astro::CartesianVector&lt; Distance, astro::frames::earth::earth\_fixed &gt; | [**get\_position**](classastrea_1_1trace_1_1GroundPoint.md#function-get_position) () const<br>_Get the position of the frame in Earth-Centered-Earth-Fixed (ECEF) coordinates._  |
|  bool | [**operator==**](classastrea_1_1trace_1_1GroundPoint.md#function-operator) (const [**GroundPoint**](classastrea_1_1trace_1_1GroundPoint.md) & other) const<br>_Equality operator for comparing two_ [_**GroundPoint**_](classastrea_1_1trace_1_1GroundPoint.md) _objects._ |
| virtual  | [**~GroundPoint**](classastrea_1_1trace_1_1GroundPoint.md#function-groundpoint) () = default<br>_Destructor for the_ [_**GroundPoint**_](classastrea_1_1trace_1_1GroundPoint.md) _class._ |


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
|  std::size\_t | [**\_id**](classastrea_1_1trace_1_1GroundPoint.md#variable-_id)  <br>_Unique identifier for the ground station, generated from its properties._  |
|  astro::Geodetic | [**\_lla**](classastrea_1_1trace_1_1GroundPoint.md#variable-_lla)  <br>_Geodetic coordinates of the ground point._  |
|  const astro::CelestialBody \* | [**\_parent**](classastrea_1_1trace_1_1GroundPoint.md#variable-_parent)  <br>_Pointer to the parent celestial body._  |
















































## Protected Functions inherited from astrea::trace::GroundPoint

See [astrea::trace::GroundPoint](classastrea_1_1trace_1_1GroundPoint.md)

| Type | Name |
| ---: | :--- |
|  std::size\_t | [**generate\_id**](classastrea_1_1trace_1_1GroundPoint.md#function-generate_id) () <br>_Generates a unique identifier for the ground station based on its properties. This method is called in the constructor to ensure that each ground station has a unique ID._  |


## Protected Functions inherited from astrea::trace::AccessObject

See [astrea::trace::AccessObject](classastrea_1_1trace_1_1AccessObject.md)

| Type | Name |
| ---: | :--- |
|   | [**AccessObject**](classastrea_1_1trace_1_1AccessObject.md#function-accessobject) () = default<br>_Default constructor._  |
| virtual  | [**~AccessObject**](classastrea_1_1trace_1_1AccessObject.md#function-accessobject) () = default<br>_Default destructor._  |








## Public Functions Documentation




### function GroundStation 

_Constructs a_ [_**GroundStation**_](classastrea_1_1trace_1_1GroundStation.md) _object with specified latitude, longitude, altitude, sensors, and name._
```C++
astrea::trace::GroundStation::GroundStation (
    const astro::CelestialBody * parent,
    const Angle & latitude,
    const Angle & longitude,
    const Distance & altitude=0.0 *mp_units::si::unit_symbols::km,
    const std::string name="Unnammed",
    const std::vector< SensorParameters > & sensors={}
) 
```





**Parameters:**


* `latitude` The latitude of the ground station. 
* `longitude` The longitude of the ground station. 
* `altitude` The altitude of the ground station. 
* `sensors` The sensors associated with the ground station. 
* `name` The name of the ground station. 




        

<hr>



### function get\_id 

_Get the ID of the payload._ 
```C++
virtual std::size_t astrea::trace::GroundStation::get_id () const
```





**Returns:**

std::size\_t ID of the payload. 





        
Implements [*astrea::trace::GroundPoint::get\_id*](classastrea_1_1trace_1_1GroundPoint.md#function-get_id)


<hr>



### function get\_inertial\_position 

_Get the inertial position of the ground station in the ECI frame._ 
```C++
astro::CartesianVector< Distance, astro::frames::earth::icrf > astrea::trace::GroundStation::get_inertial_position (
    const astro::Date & date
) const
```





**Parameters:**


* `date` The date for which to compute the position. 



**Returns:**

RadiusVector&lt;frames::earth::icrf&gt; The inertial position of the ground station. 





        

<hr>



### function get\_inertial\_velocity 

_Get the inertial velocity of the ground station in the ECI frame._ 
```C++
astro::CartesianVector< Velocity, astro::frames::earth::icrf > astrea::trace::GroundStation::get_inertial_velocity (
    const astro::Date & date
) const
```





**Parameters:**


* `date` The date for which to compute the velocity. 



**Returns:**

VelocityVector&lt;frames::earth::icrf&gt; The inertial velocity of the ground station. 





        

<hr>



### function get\_name 

_Get the name of the ground station._ 
```C++
std::string astrea::trace::GroundStation::get_name () const
```





**Returns:**

std::string The name of the ground station. 





        

<hr>



### function ~GroundStation 

_Default destructor for the_ [_**GroundStation**_](classastrea_1_1trace_1_1GroundStation.md) _class._
```C++
astrea::trace::GroundStation::~GroundStation () = default
```




<hr>

------------------------------
The documentation for this class was generated from the following file `astrea/trace/trace/platforms/ground/GroundStation.hpp`

