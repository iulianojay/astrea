

# Class astrea::trace::Viewer



[**ClassList**](annotated.md) **>** [**astrea**](namespaceastrea.md) **>** [**trace**](namespaceastrea_1_1trace.md) **>** [**Viewer**](classastrea_1_1trace_1_1Viewer.md)



[_**Viewer**_](classastrea_1_1trace_1_1Viewer.md) _class for managing access and sensors on a spacecraft. This class inherits from Spacecraft,_[_**AccessObject**_](classastrea_1_1trace_1_1AccessObject.md) _, and SensorPlatform. It provides functionality to manage sensors and access rights for the spacecraft._

* `#include <Viewer.hpp>`



Inherits the following classes: astro::Spacecraft,  [astrea::trace::AccessObject](classastrea_1_1trace_1_1AccessObject.md),  SensorPlatform






















































## Public Functions

| Type | Name |
| ---: | :--- |
|   | [**Viewer**](#function-viewer-12) () = default<br>_Default constructor for_ [_**Viewer**_](classastrea_1_1trace_1_1Viewer.md) _._ |
|   | [**Viewer**](#function-viewer-22) (const astro::GeneralPerturbations & gp) <br>_Constructor for_ [_**Viewer**_](classastrea_1_1trace_1_1Viewer.md) _with GeneralPerturbations._ |
| virtual std::size\_t | [**get\_id**](#function-get_id) () const<br>_Get the viewer ID._  |
|  Mass | [**get\_mass**](#function-get_mass) () override const<br>_Get the mass of the viewer._  |
|  std::string | [**get\_name**](#function-get_name) () const<br>_Get the name of the viewer._  |
|  astro::RadiusVector&lt; astro::frames::earth::icrf &gt; | [**get\_position**](#function-get_position) (const astro::Date & date) const<br>_Get the inertial position of the viewer._  |
|  astro::VelocityVector&lt; astro::frames::earth::icrf &gt; | [**get\_velocity**](#function-get_velocity) (const astro::Date & date) const<br>_Get the inertial velocity of the viewer._  |
|   | [**~Viewer**](#function-viewer) () = default<br>_Default destructor for_ [_**Viewer**_](classastrea_1_1trace_1_1Viewer.md) _._ |


## Public Functions inherited from astrea::trace::AccessObject

See [astrea::trace::AccessObject](classastrea_1_1trace_1_1AccessObject.md)

| Type | Name |
| ---: | :--- |
|  void | [**add\_access**](classastrea_1_1trace_1_1AccessObject.md#function-add_access) (const std::size\_t & receiverId, const [**RiseSetArray**](classastrea_1_1trace_1_1RiseSetArray.md) & access) <br>_Adds access times for a specific receiver._  |
|  void | [**drop\_access**](classastrea_1_1trace_1_1AccessObject.md#function-drop_access) (const std::size\_t & receiverId, const [**RiseSetArray**](classastrea_1_1trace_1_1RiseSetArray.md) & access) <br>_Drops access times for a specific receiver._  |
|  [**AccessArray**](classastrea_1_1trace_1_1AccessArray.md) & | [**get\_accesses**](classastrea_1_1trace_1_1AccessObject.md#function-get_accesses-12) () <br>_Gets the access times for this object._  |
|  const [**AccessArray**](classastrea_1_1trace_1_1AccessArray.md) & | [**get\_accesses**](classastrea_1_1trace_1_1AccessObject.md#function-get_accesses-22) () const<br>_Gets the access times for this object (const version)._  |
| virtual std::size\_t | [**get\_id**](classastrea_1_1trace_1_1AccessObject.md#function-get_id) () const = 0<br>_Pure virtual function to get the ID of the object._  |
















































## Protected Functions inherited from astrea::trace::AccessObject

See [astrea::trace::AccessObject](classastrea_1_1trace_1_1AccessObject.md)

| Type | Name |
| ---: | :--- |
|   | [**AccessObject**](classastrea_1_1trace_1_1AccessObject.md#function-accessobject) () = default<br>_Default constructor._  |
| virtual  | [**~AccessObject**](classastrea_1_1trace_1_1AccessObject.md#function-accessobject) () = default<br>_Default destructor._  |






## Public Functions Documentation




### function Viewer [1/2]

_Default constructor for_ [_**Viewer**_](classastrea_1_1trace_1_1Viewer.md) _._
```C++
astrea::trace::Viewer::Viewer () = default
```




<hr>



### function Viewer [2/2]

_Constructor for_ [_**Viewer**_](classastrea_1_1trace_1_1Viewer.md) _with GeneralPerturbations._
```C++
inline astrea::trace::Viewer::Viewer (
    const astro::GeneralPerturbations & gp
) 
```





**Parameters:**


* `gp` The GeneralPerturbations object containing spacecraft data. 




        

<hr>



### function get\_id 

_Get the viewer ID._ 
```C++
inline virtual std::size_t astrea::trace::Viewer::get_id () const
```





**Returns:**

std::size\_t The ID of the viewer. 





        
Implements [*astrea::trace::AccessObject::get\_id*](classastrea_1_1trace_1_1AccessObject.md#function-get_id)


<hr>



### function get\_mass 

_Get the mass of the viewer._ 
```C++
inline Mass astrea::trace::Viewer::get_mass () override const
```





**Returns:**

Mass The mass of the viewer. 





        

<hr>



### function get\_name 

_Get the name of the viewer._ 
```C++
inline std::string astrea::trace::Viewer::get_name () const
```





**Returns:**

std::string The name of the viewer. 





        

<hr>



### function get\_position 

_Get the inertial position of the viewer._ 
```C++
inline astro::RadiusVector< astro::frames::earth::icrf > astrea::trace::Viewer::get_position (
    const astro::Date & date
) const
```





**Parameters:**


* `date` The date for which to get the position. 



**Returns:**

astro::RadiusVector&lt;astro::frames::earth::icrf&gt; The inertial position of the viewer. 





        

<hr>



### function get\_velocity 

_Get the inertial velocity of the viewer._ 
```C++
inline astro::VelocityVector< astro::frames::earth::icrf > astrea::trace::Viewer::get_velocity (
    const astro::Date & date
) const
```





**Parameters:**


* `date` The date for which to get the velocity. 



**Returns:**

astro::RadiusVector&lt;astro::frames::earth::icrf&gt; The inertial velocity of the viewer. 





        

<hr>



### function ~Viewer 

_Default destructor for_ [_**Viewer**_](classastrea_1_1trace_1_1Viewer.md) _._
```C++
astrea::trace::Viewer::~Viewer () = default
```




<hr>

------------------------------
The documentation for this class was generated from the following file `astrea/trace/trace/platforms/vehicles/Viewer.hpp`

