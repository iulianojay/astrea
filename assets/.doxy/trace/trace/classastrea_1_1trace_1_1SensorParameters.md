

# Class astrea::trace::SensorParameters



[**ClassList**](annotated.md) **>** [**astrea**](namespaceastrea.md) **>** [**trace**](namespaceastrea_1_1trace.md) **>** [**SensorParameters**](classastrea_1_1trace_1_1SensorParameters.md)



_Class for storing and managing sensor parameters._ 

* `#include <Sensor.hpp>`



Inherits the following classes: astro::PayloadParameters


Inherited by the following classes: [astrea::trace::AntennaParameters](classastrea_1_1trace_1_1AntennaParameters.md)
































## Public Functions

| Type | Name |
| ---: | :--- |
|   | [**SensorParameters**](#function-sensorparameters) (const [**FieldOfView**](classastrea_1_1trace_1_1FieldOfView.md) \* fov=nullptr, const astro::CartesianVector&lt; Distance, astro::frames::dynamic::ric &gt; & boresight=astro::NADIR\_RIC, const astro::CartesianVector&lt; Distance, astro::frames::dynamic::ric &gt; & attachmentPoint=astro::CENTER) <br>_Constructor for_ [_**SensorParameters**_](classastrea_1_1trace_1_1SensorParameters.md) _._ |
|  const [**FieldOfView**](classastrea_1_1trace_1_1FieldOfView.md) \* | [**get\_fov**](#function-get_fov) () const<br>_Get the field of view of the sensor._  |
|  void | [**set\_fov**](#function-set_fov) ([**FieldOfView**](classastrea_1_1trace_1_1FieldOfView.md) \* fov) <br>_Set the field of view of the sensor._  |
| virtual  | [**~SensorParameters**](#function-sensorparameters) () = default<br>_Default destructor for_ [_**SensorParameters**_](classastrea_1_1trace_1_1SensorParameters.md) _._ |








## Protected Attributes

| Type | Name |
| ---: | :--- |
|  const [**FieldOfView**](classastrea_1_1trace_1_1FieldOfView.md) \* | [**\_fov**](#variable-_fov)  <br>_Field of view of the sensor, defining its coverage area._  |




















## Public Functions Documentation




### function SensorParameters 

_Constructor for_ [_**SensorParameters**_](classastrea_1_1trace_1_1SensorParameters.md) _._
```C++
inline astrea::trace::SensorParameters::SensorParameters (
    const FieldOfView * fov=nullptr,
    const astro::CartesianVector< Distance, astro::frames::dynamic::ric > & boresight=astro::NADIR_RIC,
    const astro::CartesianVector< Distance, astro::frames::dynamic::ric > & attachmentPoint=astro::CENTER
) 
```





**Parameters:**


* `fov` Field of View for the sensor. 
* `boresight` Boresight direction in RIC coordinates (default is Nadir). 
* `attachmentPoint` Attachment point in RIC coordinates (default is Center). 




        

<hr>



### function get\_fov 

_Get the field of view of the sensor._ 
```C++
inline const FieldOfView * astrea::trace::SensorParameters::get_fov () const
```





**Returns:**

FieldOfView\* Pointer to the field of view object. 





        

<hr>



### function set\_fov 

_Set the field of view of the sensor._ 
```C++
inline void astrea::trace::SensorParameters::set_fov (
    FieldOfView * fov
) 
```





**Parameters:**


* `fov` FieldOfView\* Pointer to the field of view object. 




        

<hr>



### function ~SensorParameters 

_Default destructor for_ [_**SensorParameters**_](classastrea_1_1trace_1_1SensorParameters.md) _._
```C++
virtual astrea::trace::SensorParameters::~SensorParameters () = default
```




<hr>
## Protected Attributes Documentation




### variable \_fov 

_Field of view of the sensor, defining its coverage area._ 
```C++
const FieldOfView* astrea::trace::SensorParameters::_fov;
```




<hr>

------------------------------
The documentation for this class was generated from the following file `astrea/trace/trace/platforms/sensors/Sensor.hpp`

