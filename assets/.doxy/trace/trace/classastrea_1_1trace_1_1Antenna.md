

# Class astrea::trace::Antenna



[**ClassList**](annotated.md) **>** [**astrea**](namespaceastrea.md) **>** [**trace**](namespaceastrea_1_1trace.md) **>** [**Antenna**](classastrea_1_1trace_1_1Antenna.md)



_Represents an antenna with properties such as diameter, efficiency, frequency, and power._ [More...](#detailed-description)

* `#include <Antenna.hpp>`



Inherits the following classes: [astrea::trace::Sensor](classastrea_1_1trace_1_1Sensor.md)




























## Public Attributes inherited from astrea::trace::Sensor

See [astrea::trace::Sensor](classastrea_1_1trace_1_1Sensor.md)

| Type | Name |
| ---: | :--- |
|  const [**SensorParameters**](classastrea_1_1trace_1_1SensorParameters.md) & | [**parameters**](classastrea_1_1trace_1_1Sensor.md#variable-parameters)  <br> |














































## Public Functions

| Type | Name |
| ---: | :--- |
|   | [**Antenna**](#function-antenna) (const T & parent, const [**AntennaParameters**](classastrea_1_1trace_1_1AntennaParameters.md) & antennaParameters) <br>_Construct a new_ [_**Antenna**_](classastrea_1_1trace_1_1Antenna.md) _object._ |
|  Gain | [**atmospheric\_loss**](#function-atmospheric_loss) () const<br>_Calculate the atmospheric loss for the antenna._  |
|  CNR | [**carrier\_to\_noise\_density**](#function-carrier_to_noise_density) (const [**Antenna**](classastrea_1_1trace_1_1Antenna.md) & receiver, const Distance & range, const Angle & offsetAngle) const<br>_Calculate the carrier-to-noise density (CND) for the antenna._  |
|  CNR | [**carrier\_to\_noise\_ratio**](#function-carrier_to_noise_ratio) (const [**Antenna**](classastrea_1_1trace_1_1Antenna.md) & receiver, const Distance & range, const Angle & offsetAngle) const<br>_Calculate the carrier-to-noise ratio (CNR) for the antenna._  |
|  Gain | [**free\_space\_loss**](#function-free_space_loss) (const Distance & range) const<br>_Calculate the free space loss for the antenna._  |
|  Gain | [**gain**](#function-gain) () const<br>_Get antenna gain._  |
|  Gain | [**mispointing\_loss**](#function-mispointing_loss) (const [**Antenna**](classastrea_1_1trace_1_1Antenna.md) & receiver, const Angle & offsetAngle) const<br>_Calculate the mispointing loss for the antenna._  |
|  Gain | [**polarization\_loss**](#function-polarization_loss) (const [**Antenna**](classastrea_1_1trace_1_1Antenna.md) & receiver) const<br>_Calculate the polarization loss for the antenna._  |
|  Gain | [**receiver\_loss**](#function-receiver_loss) () const<br>_Get the receiver loss._  |
|  Power | [**recieved\_power**](#function-recieved_power) (const [**Antenna**](classastrea_1_1trace_1_1Antenna.md) & receiver, const Distance & range, const Angle & offsetAngle) const<br>_Calculate the received power at the receiver._  |
|  void | [**set\_pattern\_approximation**](#function-set_pattern_approximation) (const [**PatternApproximation**](namespaceastrea_1_1trace.md#enum-patternapproximation) & pattern) <br>_Set the pattern approximation method._  |
|  Gain | [**system\_loss**](#function-system_loss) (const [**Antenna**](classastrea_1_1trace_1_1Antenna.md) & receiver, const Angle & offsetAngle) const<br>_Calculate the system loss for the antenna._  |
|  Temperature | [**system\_noise\_temperature**](#function-system_noise_temperature) () const<br>_Get the system noise temperature._  |
|  Gain | [**transmit\_loss**](#function-transmit_loss) () const<br>_Get the transmit loss._  |


## Public Functions inherited from astrea::trace::Sensor

See [astrea::trace::Sensor](classastrea_1_1trace_1_1Sensor.md)

| Type | Name |
| ---: | :--- |
|  const [**SensorParameters**](classastrea_1_1trace_1_1SensorParameters.md) | [**Payload**](classastrea_1_1trace_1_1Sensor.md#function-payload) (parent, parameters) <br> |
|  bool | [**contains**](classastrea_1_1trace_1_1Sensor.md#function-contains) (const astro::RadiusVector&lt; astro::frames::earth::icrf &gt; & sensor2target, const astro::Date & date) const<br>_Check if the sensor can see a target given the boresight vector._  |
| virtual std::size\_t | [**get\_id**](classastrea_1_1trace_1_1Sensor.md#function-get_id) () const<br>_Get the ID of the sensor._  |
|   | [**requires**](classastrea_1_1trace_1_1Sensor.md#function-requires) (std::is\_base\_of\_v&lt; astro::FrameReference, Parent\_T &gt;) const<br>_Constructs a_ [_**Sensor**_](classastrea_1_1trace_1_1Sensor.md) _from a_[_**FieldOfView**_](classastrea_1_1trace_1_1FieldOfView.md) _object._ |
| virtual  | [**~Sensor**](classastrea_1_1trace_1_1Sensor.md#function-sensor) () = default<br>_Default destructor for_ [_**Sensor**_](classastrea_1_1trace_1_1Sensor.md) _._ |


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


The [**Antenna**](classastrea_1_1trace_1_1Antenna.md) class provides methods to calculate signal strength, losses, and other antenna-related properties. 


    
## Public Functions Documentation




### function Antenna 

_Construct a new_ [_**Antenna**_](classastrea_1_1trace_1_1Antenna.md) _object._
```C++
template<typename T>
inline astrea::trace::Antenna::Antenna (
    const T & parent,
    const AntennaParameters & antennaParameters
) 
```




<hr>



### function atmospheric\_loss 

_Calculate the atmospheric loss for the antenna._ 
```C++
Gain astrea::trace::Antenna::atmospheric_loss () const
```





**Returns:**

Gain The calculated atmospheric loss. 





        

<hr>



### function carrier\_to\_noise\_density 

_Calculate the carrier-to-noise density (CND) for the antenna._ 
```C++
CNR astrea::trace::Antenna::carrier_to_noise_density (
    const Antenna & receiver,
    const Distance & range,
    const Angle & offsetAngle
) const
```





**Parameters:**


* `receiver` [**Antenna**](classastrea_1_1trace_1_1Antenna.md) object representing the receiver. 
* `range` Distance to the receiver. 
* `offsetAngle` Angle offset from the boresight. 



**Returns:**

CNR The calculated carrier-to-noise density. 





        

<hr>



### function carrier\_to\_noise\_ratio 

_Calculate the carrier-to-noise ratio (CNR) for the antenna._ 
```C++
CNR astrea::trace::Antenna::carrier_to_noise_ratio (
    const Antenna & receiver,
    const Distance & range,
    const Angle & offsetAngle
) const
```





**Parameters:**


* `receiver` [**Antenna**](classastrea_1_1trace_1_1Antenna.md) object representing the receiver. 
* `range` Distance to the receiver. 
* `offsetAngle` Angle offset from the boresight. 



**Returns:**

CNR The calculated carrier-to-noise ratio. 





        

<hr>



### function free\_space\_loss 

_Calculate the free space loss for the antenna._ 
```C++
Gain astrea::trace::Antenna::free_space_loss (
    const Distance & range
) const
```





**Parameters:**


* `range` Distance to the receiver. 



**Returns:**

Gain The calculated free space loss. 





        

<hr>



### function gain 

_Get antenna gain._ 
```C++
Gain astrea::trace::Antenna::gain () const
```





**Returns:**

Gain The gain of the antenna. 





        

<hr>



### function mispointing\_loss 

_Calculate the mispointing loss for the antenna._ 
```C++
Gain astrea::trace::Antenna::mispointing_loss (
    const Antenna & receiver,
    const Angle & offsetAngle
) const
```





**Parameters:**


* `receiver` [**Antenna**](classastrea_1_1trace_1_1Antenna.md) object representing the receiver. 
* `offsetAngle` Angle offset from the boresight. 



**Returns:**

Gain The calculated mispointing loss. 





        

<hr>



### function polarization\_loss 

_Calculate the polarization loss for the antenna._ 
```C++
Gain astrea::trace::Antenna::polarization_loss (
    const Antenna & receiver
) const
```





**Parameters:**


* `receiver` [**Antenna**](classastrea_1_1trace_1_1Antenna.md) object representing the receiver. 



**Returns:**

Gain The calculated polarization loss. 





        

<hr>



### function receiver\_loss 

_Get the receiver loss._ 
```C++
Gain astrea::trace::Antenna::receiver_loss () const
```





**Returns:**

Gain The receiver loss. 





        

<hr>



### function recieved\_power 

_Calculate the received power at the receiver._ 
```C++
Power astrea::trace::Antenna::recieved_power (
    const Antenna & receiver,
    const Distance & range,
    const Angle & offsetAngle
) const
```





**Parameters:**


* `receiver` [**Antenna**](classastrea_1_1trace_1_1Antenna.md) object representing the receiver. 
* `range` Distance to the receiver. 
* `offsetAngle` Angle offset from the boresight. 



**Returns:**

Power The calculated received power. 





        

<hr>



### function set\_pattern\_approximation 

_Set the pattern approximation method._ 
```C++
void astrea::trace::Antenna::set_pattern_approximation (
    const PatternApproximation & pattern
) 
```





**Parameters:**


* `pattern` Pattern approximation method to set. 




        

<hr>



### function system\_loss 

_Calculate the system loss for the antenna._ 
```C++
Gain astrea::trace::Antenna::system_loss (
    const Antenna & receiver,
    const Angle & offsetAngle
) const
```





**Parameters:**


* `receiver` [**Antenna**](classastrea_1_1trace_1_1Antenna.md) object representing the receiver. 
* `offsetAngle` Angle offset from the boresight. 



**Returns:**

Gain The calculated system loss. 





        

<hr>



### function system\_noise\_temperature 

_Get the system noise temperature._ 
```C++
Temperature astrea::trace::Antenna::system_noise_temperature () const
```





**Returns:**

Temperature The system noise temperature. 





        

<hr>



### function transmit\_loss 

_Get the transmit loss._ 
```C++
Gain astrea::trace::Antenna::transmit_loss () const
```





**Returns:**

Gain The transmit loss. 





        

<hr>

------------------------------
The documentation for this class was generated from the following file `astrea/trace/trace/platforms/sensors/Antenna.hpp`

