

# Class astrea::trace::AntennaParameters



[**ClassList**](annotated.md) **>** [**astrea**](namespaceastrea.md) **>** [**trace**](namespaceastrea_1_1trace.md) **>** [**AntennaParameters**](classastrea_1_1trace_1_1AntennaParameters.md)



_Class for storing and managing antenna parameters._ 

* `#include <Antenna.hpp>`



Inherits the following classes: [astrea::trace::SensorParameters](classastrea_1_1trace_1_1SensorParameters.md)






















































## Public Functions

| Type | Name |
| ---: | :--- |
|   | [**AntennaParameters**](#function-antennaparameters) (const [**FieldOfView**](classastrea_1_1trace_1_1FieldOfView.md) \* fov, const Length & diameter, const Unitless & efficiency, const Frequency & frequency, const Power & power, const astro::CartesianVector&lt; Distance, astro::frames::dynamic::ric &gt; & boresight=astro::NADIR\_RIC, const astro::CartesianVector&lt; Distance, astro::frames::dynamic::ric &gt; & attachmentPoint=astro::CENTER, const Frequency & noiseBandwidth=0.0 \*mp\_units::si::unit\_symbols::GHz, const Gain & transmitLoss=1.0 \*mp\_units::one, const Gain & receiverLoss=1.0 \*mp\_units::one, const [**PatternApproximation**](namespaceastrea_1_1trace.md#enum-patternapproximation) & pattern=PatternApproximation::BESSEL) <br>_Construct a new_ [_**Antenna**_](classastrea_1_1trace_1_1Antenna.md) _Parameters object._ |
|  Length | [**get\_diameter**](#function-get_diameter) () const<br>_Get the diameter of the antenna._  |
|  Unitless | [**get\_efficiency**](#function-get_efficiency) () const<br>_Get the efficiency of the antenna._  |
|  Power | [**get\_eirp**](#function-get_eirp) () const<br>_Get the equivalent isotropic radiated power (EIRP) of the antenna._  |
|  Frequency | [**get\_frequency**](#function-get_frequency) () const<br>_Get the frequency of the antenna._  |
|  Gain | [**get\_gain**](#function-get_gain) () const<br>_Get the gain of the antenna._  |
|  Frequency | [**get\_noise\_bandwidth**](#function-get_noise_bandwidth) () const<br>_Get the noise bandwidth of the antenna._  |
|  [**PatternApproximation**](namespaceastrea_1_1trace.md#enum-patternapproximation) | [**get\_pattern**](#function-get_pattern) () const<br>_Get the pattern approximation method of the antenna._  |
|  Power | [**get\_power**](#function-get_power) () const<br>_Get the power of the antenna._  |
|  Gain | [**get\_receiver\_loss**](#function-get_receiver_loss) () const<br>_Get the receiver loss of the antenna._  |
|  Temperature | [**get\_system\_noise\_temperature**](#function-get_system_noise_temperature) () const<br>_Get the system noise temperature of the antenna._  |
|  Gain | [**get\_transmit\_loss**](#function-get_transmit_loss) () const<br>_Get the transmit loss of the antenna._  |
|  Length | [**get\_wavelength**](#function-get_wavelength) () const<br>_Get the wavelength of the antenna._  |
|  void | [**set\_diameter**](#function-set_diameter) (const Length & diameter) <br>_Set the diameter of the antenna._  |
|  void | [**set\_efficiency**](#function-set_efficiency) (const Unitless & efficiency) <br>_Set the efficiency of the antenna._  |
|  void | [**set\_frequency**](#function-set_frequency) (const Frequency & frequency) <br>_Set the frequency of the antenna._  |
|  void | [**set\_noise\_bandwidth**](#function-set_noise_bandwidth) (const Frequency & noiseBandwidth) <br>_Set the noise bandwidth of the antenna._  |
|  void | [**set\_pattern**](#function-set_pattern) (const [**PatternApproximation**](namespaceastrea_1_1trace.md#enum-patternapproximation) & pattern) <br>_Set the pattern approximation method of the antenna._  |
|  void | [**set\_power**](#function-set_power) (const Power & power) <br>_Set the power of the antenna._  |
|  void | [**set\_receiver\_loss**](#function-set_receiver_loss) (const Gain & receiverLoss) <br>_Set the receiver loss of the antenna._  |
|  void | [**set\_transmit\_loss**](#function-set_transmit_loss) (const Gain & transmitLoss) <br>_Set the transmit loss of the antenna._  |
|   | [**~AntennaParameters**](#function-antennaparameters) () = default<br>_Default constructor for_ [_**AntennaParameters**_](classastrea_1_1trace_1_1AntennaParameters.md) _._ |


## Public Functions inherited from astrea::trace::SensorParameters

See [astrea::trace::SensorParameters](classastrea_1_1trace_1_1SensorParameters.md)

| Type | Name |
| ---: | :--- |
|   | [**SensorParameters**](classastrea_1_1trace_1_1SensorParameters.md#function-sensorparameters) (const [**FieldOfView**](classastrea_1_1trace_1_1FieldOfView.md) \* fov=nullptr, const astro::CartesianVector&lt; Distance, astro::frames::dynamic::ric &gt; & boresight=astro::NADIR\_RIC, const astro::CartesianVector&lt; Distance, astro::frames::dynamic::ric &gt; & attachmentPoint=astro::CENTER) <br>_Constructor for_ [_**SensorParameters**_](classastrea_1_1trace_1_1SensorParameters.md) _._ |
|  const [**FieldOfView**](classastrea_1_1trace_1_1FieldOfView.md) \* | [**get\_fov**](classastrea_1_1trace_1_1SensorParameters.md#function-get_fov) () const<br>_Get the field of view of the sensor._  |
|  void | [**set\_fov**](classastrea_1_1trace_1_1SensorParameters.md#function-set_fov) ([**FieldOfView**](classastrea_1_1trace_1_1FieldOfView.md) \* fov) <br>_Set the field of view of the sensor._  |
| virtual  | [**~SensorParameters**](classastrea_1_1trace_1_1SensorParameters.md#function-sensorparameters) () = default<br>_Default destructor for_ [_**SensorParameters**_](classastrea_1_1trace_1_1SensorParameters.md) _._ |
















## Protected Attributes inherited from astrea::trace::SensorParameters

See [astrea::trace::SensorParameters](classastrea_1_1trace_1_1SensorParameters.md)

| Type | Name |
| ---: | :--- |
|  const [**FieldOfView**](classastrea_1_1trace_1_1FieldOfView.md) \* | [**\_fov**](classastrea_1_1trace_1_1SensorParameters.md#variable-_fov)  <br>_Field of view of the sensor, defining its coverage area._  |






































## Public Functions Documentation




### function AntennaParameters 

_Construct a new_ [_**Antenna**_](classastrea_1_1trace_1_1Antenna.md) _Parameters object._
```C++
inline astrea::trace::AntennaParameters::AntennaParameters (
    const FieldOfView * fov,
    const Length & diameter,
    const Unitless & efficiency,
    const Frequency & frequency,
    const Power & power,
    const astro::CartesianVector< Distance, astro::frames::dynamic::ric > & boresight=astro::NADIR_RIC,
    const astro::CartesianVector< Distance, astro::frames::dynamic::ric > & attachmentPoint=astro::CENTER,
    const Frequency & noiseBandwidth=0.0 *mp_units::si::unit_symbols::GHz,
    const Gain & transmitLoss=1.0 *mp_units::one,
    const Gain & receiverLoss=1.0 *mp_units::one,
    const PatternApproximation & pattern=PatternApproximation::BESSEL
) 
```





**Parameters:**


* `fov` Field of View for the antenna. 
* `diameter` Reflector diameter. 
* `efficiency` Aperture illumination efficiency. 
* `frequency` Carrier frequency. 
* `power` Transmit power. 
* `boresight` Boresight direction in RIC coordinates (default is Nadir). 
* `attachmentPoint` Attachment point in RIC coordinates (default is Center). 
* `noiseBandwidth` Equivalent noise bandwidth (default is 0.0, ideal). 
* `transmitLoss` Transmit loss (default is 1.0, ideal). 
* `receiverLoss` Receiver loss (default is 1.0, ideal). 
* `pattern` Pattern approximation method (default is Bessel). 




        

<hr>



### function get\_diameter 

_Get the diameter of the antenna._ 
```C++
inline Length astrea::trace::AntennaParameters::get_diameter () const
```





**Returns:**

Length Diameter of the antenna. 





        

<hr>



### function get\_efficiency 

_Get the efficiency of the antenna._ 
```C++
inline Unitless astrea::trace::AntennaParameters::get_efficiency () const
```





**Returns:**

Unitless Efficiency of the antenna. 





        

<hr>



### function get\_eirp 

_Get the equivalent isotropic radiated power (EIRP) of the antenna._ 
```C++
inline Power astrea::trace::AntennaParameters::get_eirp () const
```





**Returns:**

Power EIRP of the antenna. 





        

<hr>



### function get\_frequency 

_Get the frequency of the antenna._ 
```C++
inline Frequency astrea::trace::AntennaParameters::get_frequency () const
```





**Returns:**

Frequency Frequency of the antenna. 





        

<hr>



### function get\_gain 

_Get the gain of the antenna._ 
```C++
inline Gain astrea::trace::AntennaParameters::get_gain () const
```





**Returns:**

Gain Gain of the antenna. 





        

<hr>



### function get\_noise\_bandwidth 

_Get the noise bandwidth of the antenna._ 
```C++
inline Frequency astrea::trace::AntennaParameters::get_noise_bandwidth () const
```





**Returns:**

Frequency Noise bandwidth of the antenna. 





        

<hr>



### function get\_pattern 

_Get the pattern approximation method of the antenna._ 
```C++
inline PatternApproximation astrea::trace::AntennaParameters::get_pattern () const
```





**Returns:**

PatternApproximation Pattern approximation method of the antenna. 





        

<hr>



### function get\_power 

_Get the power of the antenna._ 
```C++
inline Power astrea::trace::AntennaParameters::get_power () const
```





**Returns:**

Power Power of the antenna. 





        

<hr>



### function get\_receiver\_loss 

_Get the receiver loss of the antenna._ 
```C++
inline Gain astrea::trace::AntennaParameters::get_receiver_loss () const
```





**Returns:**

Gain Receiver loss of the antenna. 





        

<hr>



### function get\_system\_noise\_temperature 

_Get the system noise temperature of the antenna._ 
```C++
inline Temperature astrea::trace::AntennaParameters::get_system_noise_temperature () const
```





**Returns:**

Temperature System noise temperature of the antenna. 





        

<hr>



### function get\_transmit\_loss 

_Get the transmit loss of the antenna._ 
```C++
inline Gain astrea::trace::AntennaParameters::get_transmit_loss () const
```





**Returns:**

Gain Transmit loss of the antenna. 





        

<hr>



### function get\_wavelength 

_Get the wavelength of the antenna._ 
```C++
inline Length astrea::trace::AntennaParameters::get_wavelength () const
```





**Returns:**

Length Wavelength of the antenna. 





        

<hr>



### function set\_diameter 

_Set the diameter of the antenna._ 
```C++
inline void astrea::trace::AntennaParameters::set_diameter (
    const Length & diameter
) 
```





**Parameters:**


* `diameter` Length Diameter of the antenna. 




        

<hr>



### function set\_efficiency 

_Set the efficiency of the antenna._ 
```C++
inline void astrea::trace::AntennaParameters::set_efficiency (
    const Unitless & efficiency
) 
```





**Parameters:**


* `efficiency` Unitless Efficiency of the antenna. 




        

<hr>



### function set\_frequency 

_Set the frequency of the antenna._ 
```C++
inline void astrea::trace::AntennaParameters::set_frequency (
    const Frequency & frequency
) 
```





**Parameters:**


* `frequency` Frequency Frequency of the antenna. 




        

<hr>



### function set\_noise\_bandwidth 

_Set the noise bandwidth of the antenna._ 
```C++
inline void astrea::trace::AntennaParameters::set_noise_bandwidth (
    const Frequency & noiseBandwidth
) 
```





**Parameters:**


* `noiseBandwidth` Frequency Noise bandwidth of the antenna. 




        

<hr>



### function set\_pattern 

_Set the pattern approximation method of the antenna._ 
```C++
inline void astrea::trace::AntennaParameters::set_pattern (
    const PatternApproximation & pattern
) 
```





**Parameters:**


* `pattern` PatternApproximation Pattern approximation method of the antenna. 




        

<hr>



### function set\_power 

_Set the power of the antenna._ 
```C++
inline void astrea::trace::AntennaParameters::set_power (
    const Power & power
) 
```





**Parameters:**


* `power` Power Power of the antenna. 




        

<hr>



### function set\_receiver\_loss 

_Set the receiver loss of the antenna._ 
```C++
inline void astrea::trace::AntennaParameters::set_receiver_loss (
    const Gain & receiverLoss
) 
```





**Parameters:**


* `receiverLoss` Gain Receiver loss of the antenna. 




        

<hr>



### function set\_transmit\_loss 

_Set the transmit loss of the antenna._ 
```C++
inline void astrea::trace::AntennaParameters::set_transmit_loss (
    const Gain & transmitLoss
) 
```





**Parameters:**


* `transmitLoss` Gain Transmit loss of the antenna. 




        

<hr>



### function ~AntennaParameters 

_Default constructor for_ [_**AntennaParameters**_](classastrea_1_1trace_1_1AntennaParameters.md) _._
```C++
astrea::trace::AntennaParameters::~AntennaParameters () = default
```




<hr>

------------------------------
The documentation for this class was generated from the following file `astrea/trace/trace/platforms/sensors/Antenna.hpp`

