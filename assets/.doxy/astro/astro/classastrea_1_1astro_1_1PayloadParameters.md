

# Class astrea::astro::PayloadParameters



[**ClassList**](annotated.md) **>** [**astrea**](namespaceastrea.md) **>** [**astro**](namespaceastrea_1_1astro.md) **>** [**PayloadParameters**](classastrea_1_1astro_1_1PayloadParameters.md)



_Class for storing and managing payload parameters._ 

* `#include <Payload.hpp>`





Inherited by the following classes: [astrea::astro::ThrusterParameters](classastrea_1_1astro_1_1ThrusterParameters.md)
































## Public Functions

| Type | Name |
| ---: | :--- |
|  [**astro::RadiusVector**](namespaceastrea_1_1astro.md#typedef-radiusvector)&lt; [**astro::frames::dynamic::ric**](classastrea_1_1astro_1_1frames_1_1RadialInTrackCrossTrack.md) &gt; | [**get\_attachment\_point**](#function-get_attachment_point) () const<br>_Get the attachment point of the payload._  |
|  [**astro::RadiusVector**](namespaceastrea_1_1astro.md#typedef-radiusvector)&lt; [**astro::frames::dynamic::ric**](classastrea_1_1astro_1_1frames_1_1RadialInTrackCrossTrack.md) &gt; | [**get\_boresight**](#function-get_boresight) () const<br>_Get the boresight direction of the payload._  |
|  void | [**set\_attachment\_point**](#function-set_attachment_point) (const [**astro::RadiusVector**](namespaceastrea_1_1astro.md#typedef-radiusvector)&lt; [**astro::frames::dynamic::ric**](classastrea_1_1astro_1_1frames_1_1RadialInTrackCrossTrack.md) &gt; & attachmentPoint) <br>_Set the attachment point of the payload._  |
|  void | [**set\_boresight**](#function-set_boresight) (const [**astro::RadiusVector**](namespaceastrea_1_1astro.md#typedef-radiusvector)&lt; [**astro::frames::dynamic::ric**](classastrea_1_1astro_1_1frames_1_1RadialInTrackCrossTrack.md) &gt; & boresight) <br>_Set the boresight direction of the payload._  |








## Protected Attributes

| Type | Name |
| ---: | :--- |
|  [**astro::RadiusVector**](namespaceastrea_1_1astro.md#typedef-radiusvector)&lt; [**astro::frames::dynamic::ric**](classastrea_1_1astro_1_1frames_1_1RadialInTrackCrossTrack.md) &gt; | [**\_attachmentPoint**](#variable-_attachmentpoint)  <br>_Attachment point of the payload on the platform._  |
|  [**astro::RadiusVector**](namespaceastrea_1_1astro.md#typedef-radiusvector)&lt; [**astro::frames::dynamic::ric**](classastrea_1_1astro_1_1frames_1_1RadialInTrackCrossTrack.md) &gt; | [**\_boresight**](#variable-_boresight)  <br>_Boresight vector of the payload, indicating the direction it is pointing._  |
















## Protected Functions

| Type | Name |
| ---: | :--- |
|   | [**PayloadParameters**](#function-payloadparameters) (const [**astro::RadiusVector**](namespaceastrea_1_1astro.md#typedef-radiusvector)&lt; [**astro::frames::dynamic::ric**](classastrea_1_1astro_1_1frames_1_1RadialInTrackCrossTrack.md) &gt; & boresight=NADIR\_RIC, const [**astro::RadiusVector**](namespaceastrea_1_1astro.md#typedef-radiusvector)&lt; [**astro::frames::dynamic::ric**](classastrea_1_1astro_1_1frames_1_1RadialInTrackCrossTrack.md) &gt; & attachmentPoint=CENTER) <br>_Constructor for_ [_**PayloadParameters**_](classastrea_1_1astro_1_1PayloadParameters.md) _._ |
| virtual  | [**~PayloadParameters**](#function-payloadparameters) () = default<br>_Default destructor for_ [_**PayloadParameters**_](classastrea_1_1astro_1_1PayloadParameters.md) _._ |




## Public Functions Documentation




### function get\_attachment\_point 

_Get the attachment point of the payload._ 
```C++
inline astro::RadiusVector < astro::frames::dynamic::ric > astrea::astro::PayloadParameters::get_attachment_point () const
```





**Returns:**

astro::RadiusVector&lt;astro::frames::dynamic::ric&gt;Attachment point of the payload. 





        

<hr>



### function get\_boresight 

_Get the boresight direction of the payload._ 
```C++
inline astro::RadiusVector < astro::frames::dynamic::ric > astrea::astro::PayloadParameters::get_boresight () const
```





**Returns:**

astro::RadiusVector&lt;astro::frames::dynamic::ric&gt;Boresight direction of the payload. 





        

<hr>



### function set\_attachment\_point 

_Set the attachment point of the payload._ 
```C++
inline void astrea::astro::PayloadParameters::set_attachment_point (
    const astro::RadiusVector < astro::frames::dynamic::ric > & attachmentPoint
) 
```





**Parameters:**


* `attachmentPoint` astro::RadiusVector&lt;astro::frames::dynamic::ric&gt;Attachment point of the payload. 




        

<hr>



### function set\_boresight 

_Set the boresight direction of the payload._ 
```C++
inline void astrea::astro::PayloadParameters::set_boresight (
    const astro::RadiusVector < astro::frames::dynamic::ric > & boresight
) 
```





**Parameters:**


* `boresight` astro::RadiusVector&lt;astro::frames::dynamic::ric&gt;Boresight direction of the payload. 




        

<hr>
## Protected Attributes Documentation




### variable \_attachmentPoint 

_Attachment point of the payload on the platform._ 
```C++
astro::RadiusVector<astro::frames::dynamic::ric> astrea::astro::PayloadParameters::_attachmentPoint;
```




<hr>



### variable \_boresight 

_Boresight vector of the payload, indicating the direction it is pointing._ 
```C++
astro::RadiusVector<astro::frames::dynamic::ric> astrea::astro::PayloadParameters::_boresight;
```




<hr>
## Protected Functions Documentation




### function PayloadParameters 

_Constructor for_ [_**PayloadParameters**_](classastrea_1_1astro_1_1PayloadParameters.md) _._
```C++
inline astrea::astro::PayloadParameters::PayloadParameters (
    const astro::RadiusVector < astro::frames::dynamic::ric > & boresight=NADIR_RIC,
    const astro::RadiusVector < astro::frames::dynamic::ric > & attachmentPoint=CENTER
) 
```





**Parameters:**


* `boresight` Boresight direction in RIC coordinates (default is Nadir). 
* `attachmentPoint` Attachment point in RIC coordinates (default is Center). 




        

<hr>



### function ~PayloadParameters 

_Default destructor for_ [_**PayloadParameters**_](classastrea_1_1astro_1_1PayloadParameters.md) _._
```C++
virtual astrea::astro::PayloadParameters::~PayloadParameters () = default
```




<hr>

------------------------------
The documentation for this class was generated from the following file `astrea/astro/astro/platforms/Payload.hpp`

