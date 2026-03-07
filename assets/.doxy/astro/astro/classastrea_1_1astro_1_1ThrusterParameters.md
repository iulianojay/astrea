

# Class astrea::astro::ThrusterParameters



[**ClassList**](annotated.md) **>** [**astrea**](namespaceastrea.md) **>** [**astro**](namespaceastrea_1_1astro.md) **>** [**ThrusterParameters**](classastrea_1_1astro_1_1ThrusterParameters.md)



_Class for storing and managing thruster parameters._ 

* `#include <Thruster.hpp>`



Inherits the following classes: [astrea::astro::PayloadParameters](classastrea_1_1astro_1_1PayloadParameters.md)






















































## Public Functions

| Type | Name |
| ---: | :--- |
|   | [**ThrusterParameters**](#function-thrusterparameters) (const Thrust & thrust, const [**CartesianVector**](classastrea_1_1astro_1_1CartesianVector.md)&lt; Distance, [**frames::dynamic::ric**](classastrea_1_1astro_1_1frames_1_1RadialInTrackCrossTrack.md) &gt; & boresight=NADIR\_RIC, const [**CartesianVector**](classastrea_1_1astro_1_1CartesianVector.md)&lt; Distance, [**frames::dynamic::ric**](classastrea_1_1astro_1_1frames_1_1RadialInTrackCrossTrack.md) &gt; & attachmentPoint=CENTER) <br>_Constructor for_ [_**ThrusterParameters**_](classastrea_1_1astro_1_1ThrusterParameters.md) _._ |
|  Thrust | [**get\_thrust**](#function-get_thrust) () const<br>_Get the thrust magnitude._  |
| virtual  | [**~ThrusterParameters**](#function-thrusterparameters) () = default<br>_Default destructor for_ [_**ThrusterParameters**_](classastrea_1_1astro_1_1ThrusterParameters.md) _._ |


## Public Functions inherited from astrea::astro::PayloadParameters

See [astrea::astro::PayloadParameters](classastrea_1_1astro_1_1PayloadParameters.md)

| Type | Name |
| ---: | :--- |
|  [**astro::RadiusVector**](namespaceastrea_1_1astro.md#typedef-radiusvector)&lt; [**astro::frames::dynamic::ric**](classastrea_1_1astro_1_1frames_1_1RadialInTrackCrossTrack.md) &gt; | [**get\_attachment\_point**](classastrea_1_1astro_1_1PayloadParameters.md#function-get_attachment_point) () const<br>_Get the attachment point of the payload._  |
|  [**astro::RadiusVector**](namespaceastrea_1_1astro.md#typedef-radiusvector)&lt; [**astro::frames::dynamic::ric**](classastrea_1_1astro_1_1frames_1_1RadialInTrackCrossTrack.md) &gt; | [**get\_boresight**](classastrea_1_1astro_1_1PayloadParameters.md#function-get_boresight) () const<br>_Get the boresight direction of the payload._  |
|  void | [**set\_attachment\_point**](classastrea_1_1astro_1_1PayloadParameters.md#function-set_attachment_point) (const [**astro::RadiusVector**](namespaceastrea_1_1astro.md#typedef-radiusvector)&lt; [**astro::frames::dynamic::ric**](classastrea_1_1astro_1_1frames_1_1RadialInTrackCrossTrack.md) &gt; & attachmentPoint) <br>_Set the attachment point of the payload._  |
|  void | [**set\_boresight**](classastrea_1_1astro_1_1PayloadParameters.md#function-set_boresight) (const [**astro::RadiusVector**](namespaceastrea_1_1astro.md#typedef-radiusvector)&lt; [**astro::frames::dynamic::ric**](classastrea_1_1astro_1_1frames_1_1RadialInTrackCrossTrack.md) &gt; & boresight) <br>_Set the boresight direction of the payload._  |














## Protected Attributes

| Type | Name |
| ---: | :--- |
|  Thrust | [**\_thrust**](#variable-_thrust)  <br>_Thrust magnitude._  |


## Protected Attributes inherited from astrea::astro::PayloadParameters

See [astrea::astro::PayloadParameters](classastrea_1_1astro_1_1PayloadParameters.md)

| Type | Name |
| ---: | :--- |
|  [**astro::RadiusVector**](namespaceastrea_1_1astro.md#typedef-radiusvector)&lt; [**astro::frames::dynamic::ric**](classastrea_1_1astro_1_1frames_1_1RadialInTrackCrossTrack.md) &gt; | [**\_attachmentPoint**](classastrea_1_1astro_1_1PayloadParameters.md#variable-_attachmentpoint)  <br>_Attachment point of the payload on the platform._  |
|  [**astro::RadiusVector**](namespaceastrea_1_1astro.md#typedef-radiusvector)&lt; [**astro::frames::dynamic::ric**](classastrea_1_1astro_1_1frames_1_1RadialInTrackCrossTrack.md) &gt; | [**\_boresight**](classastrea_1_1astro_1_1PayloadParameters.md#variable-_boresight)  <br>_Boresight vector of the payload, indicating the direction it is pointing._  |
































## Protected Functions inherited from astrea::astro::PayloadParameters

See [astrea::astro::PayloadParameters](classastrea_1_1astro_1_1PayloadParameters.md)

| Type | Name |
| ---: | :--- |
|   | [**PayloadParameters**](classastrea_1_1astro_1_1PayloadParameters.md#function-payloadparameters) (const [**astro::RadiusVector**](namespaceastrea_1_1astro.md#typedef-radiusvector)&lt; [**astro::frames::dynamic::ric**](classastrea_1_1astro_1_1frames_1_1RadialInTrackCrossTrack.md) &gt; & boresight=NADIR\_RIC, const [**astro::RadiusVector**](namespaceastrea_1_1astro.md#typedef-radiusvector)&lt; [**astro::frames::dynamic::ric**](classastrea_1_1astro_1_1frames_1_1RadialInTrackCrossTrack.md) &gt; & attachmentPoint=CENTER) <br>_Constructor for_ [_**PayloadParameters**_](classastrea_1_1astro_1_1PayloadParameters.md) _._ |
| virtual  | [**~PayloadParameters**](classastrea_1_1astro_1_1PayloadParameters.md#function-payloadparameters) () = default<br>_Default destructor for_ [_**PayloadParameters**_](classastrea_1_1astro_1_1PayloadParameters.md) _._ |






## Public Functions Documentation




### function ThrusterParameters 

_Constructor for_ [_**ThrusterParameters**_](classastrea_1_1astro_1_1ThrusterParameters.md) _._
```C++
inline astrea::astro::ThrusterParameters::ThrusterParameters (
    const Thrust & thrust,
    const CartesianVector < Distance, frames::dynamic::ric > & boresight=NADIR_RIC,
    const CartesianVector < Distance, frames::dynamic::ric > & attachmentPoint=CENTER
) 
```





**Parameters:**


* `boresight` Boresight direction in RIC coordinates (default is Nadir). 
* `attachmentPoint` Attachment point in RIC coordinates (default is Center). 




        

<hr>



### function get\_thrust 

_Get the thrust magnitude._ 
```C++
inline Thrust astrea::astro::ThrusterParameters::get_thrust () const
```





**Returns:**

Thrust magnitude. 





        

<hr>



### function ~ThrusterParameters 

_Default destructor for_ [_**ThrusterParameters**_](classastrea_1_1astro_1_1ThrusterParameters.md) _._
```C++
virtual astrea::astro::ThrusterParameters::~ThrusterParameters () = default
```




<hr>
## Protected Attributes Documentation




### variable \_thrust 

_Thrust magnitude._ 
```C++
Thrust astrea::astro::ThrusterParameters::_thrust;
```




<hr>

------------------------------
The documentation for this class was generated from the following file `astrea/astro/astro/platforms/thrusters/Thruster.hpp`

