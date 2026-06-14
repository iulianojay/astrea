

# Class astrea::trace::Sensor



[**ClassList**](annotated.md) **>** [**astrea**](namespaceastrea.md) **>** [**trace**](namespaceastrea_1_1trace.md) **>** [**Sensor**](classastrea_1_1trace_1_1Sensor.md)



[_**Sensor**_](classastrea_1_1trace_1_1Sensor.md) _class representing a sensor on a platform._[More...](#detailed-description)

* `#include <Sensor.hpp>`



Inherits the following classes: [astrea::trace::AccessObject](classastrea_1_1trace_1_1AccessObject.md),  astro::Payload< Sensor, SensorParameters >


Inherited by the following classes: [astrea::trace::Antenna](classastrea_1_1trace_1_1Antenna.md)




















































## Public Functions

| Type | Name |
| ---: | :--- |
|   | [**Sensor**](#function-sensor) (const Parent\_T & parent, const [**SensorParameters**](classastrea_1_1trace_1_1SensorParameters.md) & parameters) <br>_Constructs a_ [_**Sensor**_](classastrea_1_1trace_1_1Sensor.md) _from a_[_**FieldOfView**_](classastrea_1_1trace_1_1FieldOfView.md) _object._ |
|  bool | [**contains**](#function-contains) (const astro::RadiusVector&lt; astro::frames::earth::icrf &gt; & sensor2target, const astro::Date & date) const<br>_Check if the sensor can see a target given the boresight vector._  |
| virtual std::size\_t | [**get\_id**](#function-get_id) () const<br>_Get the ID of the sensor._  |
| virtual  | [**~Sensor**](#function-sensor) () = default<br>_Default destructor for_ [_**Sensor**_](classastrea_1_1trace_1_1Sensor.md) _._ |


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






## Detailed Description


This class inherits from [**AccessObject**](classastrea_1_1trace_1_1AccessObject.md) and provides functionality for sensors, including field of view and access management. 


    
## Public Functions Documentation




### function Sensor 

_Constructs a_ [_**Sensor**_](classastrea_1_1trace_1_1Sensor.md) _from a_[_**FieldOfView**_](classastrea_1_1trace_1_1FieldOfView.md) _object._
```C++
template<typename Parent_T>
inline astrea::trace::Sensor::Sensor (
    const Parent_T & parent,
    const SensorParameters & parameters
) 
```





**Parameters:**


* `parent` The parent platform to which the sensor is attached. 
* `fov` Field of view object defining the sensor's coverage area. 
* `boresight` The boresight vector of the sensor. 
* `attachmentPoint` The point on the platform where the sensor is attached. 




        

<hr>



### function contains 

_Check if the sensor can see a target given the boresight vector._ 
```C++
bool astrea::trace::Sensor::contains (
    const astro::RadiusVector< astro::frames::earth::icrf > & sensor2target,
    const astro::Date & date
) const
```





**Parameters:**


* `sensor2target` Vector from the sensor to the target. 
* `date` The date for which the visibility is checked. 



**Returns:**

true If the target is within the sensor's field of view. 




**Returns:**

false If the target is outside the sensor's field of view. 





        

<hr>



### function get\_id 

_Get the ID of the sensor._ 
```C++
inline virtual std::size_t astrea::trace::Sensor::get_id () const
```





**Returns:**

std::size\_t ID of the sensor. 





        
Implements [*astrea::trace::AccessObject::get\_id*](classastrea_1_1trace_1_1AccessObject.md#function-get_id)


<hr>



### function ~Sensor 

_Default destructor for_ [_**Sensor**_](classastrea_1_1trace_1_1Sensor.md) _._
```C++
virtual astrea::trace::Sensor::~Sensor () = default
```




<hr>

------------------------------
The documentation for this class was generated from the following file `astrea/trace/trace/platforms/sensors/Sensor.hpp`

