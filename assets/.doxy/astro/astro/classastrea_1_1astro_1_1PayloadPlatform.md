

# Class astrea::astro::PayloadPlatform

**template &lt;[**class**](classastrea_1_1astro_1_1CartesianVector.md) [**Payload\_T**](classastrea_1_1astro_1_1CartesianVector.md)&gt;**



[**ClassList**](annotated.md) **>** [**astrea**](namespaceastrea.md) **>** [**astro**](namespaceastrea_1_1astro.md) **>** [**PayloadPlatform**](classastrea_1_1astro_1_1PayloadPlatform.md)



_The_ [_**PayloadPlatform**_](classastrea_1_1astro_1_1PayloadPlatform.md) _class represents a platform that can have payloads attached to it. It provides methods to attach payloads and retrieve the list of attached payloads._

* `#include <PayloadPlatform.hpp>`



Inherits the following classes: [astrea::astro::FrameReference](classastrea_1_1astro_1_1FrameReference.md)






















































## Public Functions

| Type | Name |
| ---: | :--- |
|  [**void**](classastrea_1_1astro_1_1CartesianVector.md) | [**attach\_payload**](#function-attach_payload) ([**const**](classastrea_1_1astro_1_1CartesianVector.md) PayloadParameters\_T & parameters) <br>_Attaches a single payload to the platform._  |
|  [**void**](classastrea_1_1astro_1_1CartesianVector.md) | [**attach\_payloads**](#function-attach_payloads) ([**const**](classastrea_1_1astro_1_1CartesianVector.md) std::vector&lt; PayloadParameters\_T &gt; & parameterPack) <br>_Attaches multiple payloads to the platform._  |
| virtual std::size\_t | [**get\_id**](#function-get_id) () const = 0<br>_Get the ID of the payload._  |
| virtual [**Mass**](classastrea_1_1astro_1_1CartesianVector.md) | [**get\_mass**](#function-get_mass) () const<br>_Get the mass of the platform._  |
|  std::vector&lt; [**Payload\_T**](classastrea_1_1astro_1_1CartesianVector.md) &gt; & | [**get\_payloads**](#function-get_payloads-12) () <br>_Retrieves the list of payloads attached to the platform._  |
|  [**const**](classastrea_1_1astro_1_1CartesianVector.md) std::vector&lt; [**Payload\_T**](classastrea_1_1astro_1_1CartesianVector.md) &gt; & | [**get\_payloads**](#function-get_payloads-22) () const<br>_Retrieves the list of payloads attached to the platform (const version)._  |


## Public Functions inherited from astrea::astro::FrameReference

See [astrea::astro::FrameReference](classastrea_1_1astro_1_1FrameReference.md)

| Type | Name |
| ---: | :--- |
|   | [**FrameReference**](classastrea_1_1astro_1_1FrameReference.md#function-framereference) () = default<br>_Default constructor for_ [_**FrameReference**_](classastrea_1_1astro_1_1FrameReference.md) _._ |
| virtual [**CartesianVector**](classastrea_1_1astro_1_1CartesianVector.md)&lt; [**Acceleration**](classastrea_1_1astro_1_1CartesianVector.md), [**frames::earth::icrf**](structastrea_1_1astro_1_1InertialFrame.md) &gt; | [**get\_inertial\_acceleration**](classastrea_1_1astro_1_1FrameReference.md#function-get_inertial_acceleration) ([**const**](classastrea_1_1astro_1_1CartesianVector.md) [**Date**](classastrea_1_1astro_1_1Date.md) & date) const<br>_Get the acceleration of the frame in Earth-Centered Inertial coordinates._  |
| virtual [**CartesianVector**](classastrea_1_1astro_1_1CartesianVector.md)&lt; [**Distance**](classastrea_1_1astro_1_1CartesianVector.md), [**frames::earth::icrf**](structastrea_1_1astro_1_1InertialFrame.md) &gt; | [**get\_inertial\_position**](classastrea_1_1astro_1_1FrameReference.md#function-get_inertial_position) ([**const**](classastrea_1_1astro_1_1CartesianVector.md) [**Date**](classastrea_1_1astro_1_1Date.md) & date) const = 0<br>_Get the position of the frame in Earth-Centered Inertial coordinates._  |
| virtual [**CartesianVector**](classastrea_1_1astro_1_1CartesianVector.md)&lt; [**Velocity**](classastrea_1_1astro_1_1CartesianVector.md), [**frames::earth::icrf**](structastrea_1_1astro_1_1InertialFrame.md) &gt; | [**get\_inertial\_velocity**](classastrea_1_1astro_1_1FrameReference.md#function-get_inertial_velocity) ([**const**](classastrea_1_1astro_1_1CartesianVector.md) [**Date**](classastrea_1_1astro_1_1Date.md) & date) const = 0<br>_Get the velocity of the frame in Earth-Centered Inertial coordinates._  |
| virtual std::string | [**get\_name**](classastrea_1_1astro_1_1FrameReference.md#function-get_name) () const = 0<br>_Get the name of the frame reference._  |
| virtual  | [**~FrameReference**](classastrea_1_1astro_1_1FrameReference.md#function-framereference) () = default<br>_Default destructor for_ [_**FrameReference**_](classastrea_1_1astro_1_1FrameReference.md) _._ |














## Protected Attributes

| Type | Name |
| ---: | :--- |
|  std::vector&lt; [**Payload\_T**](classastrea_1_1astro_1_1CartesianVector.md) &gt; | [**\_payloads**](#variable-_payloads)  <br> |
































## Protected Functions

| Type | Name |
| ---: | :--- |
|   | [**PayloadPlatform**](#function-payloadplatform-13) () = default<br>_Default constructor for_ [_**PayloadPlatform**_](classastrea_1_1astro_1_1PayloadPlatform.md) _._ |
|   | [**PayloadPlatform**](#function-payloadplatform-23) ([**const**](classastrea_1_1astro_1_1CartesianVector.md) [**PayloadPlatform**](classastrea_1_1astro_1_1PayloadPlatform.md) & other) <br>_Copy constructor for_ [_**PayloadPlatform**_](classastrea_1_1astro_1_1PayloadPlatform.md) _._ |
|   | [**PayloadPlatform**](#function-payloadplatform-33) ([**PayloadPlatform**](classastrea_1_1astro_1_1PayloadPlatform.md) && other) noexcept<br>_Move constructor for_ [_**PayloadPlatform**_](classastrea_1_1astro_1_1PayloadPlatform.md) _._ |
|  [**PayloadPlatform**](classastrea_1_1astro_1_1PayloadPlatform.md) & | [**operator=**](#function-operator) ([**const**](classastrea_1_1astro_1_1CartesianVector.md) [**PayloadPlatform**](classastrea_1_1astro_1_1PayloadPlatform.md) & other) <br>_Copy assignment operator for_ [_**PayloadPlatform**_](classastrea_1_1astro_1_1PayloadPlatform.md) _._ |
|  [**PayloadPlatform**](classastrea_1_1astro_1_1PayloadPlatform.md) & | [**operator=**](#function-operator_1) ([**PayloadPlatform**](classastrea_1_1astro_1_1PayloadPlatform.md) && other) noexcept<br>_Move assignment operator for_ [_**PayloadPlatform**_](classastrea_1_1astro_1_1PayloadPlatform.md) _._ |
|  [**void**](classastrea_1_1astro_1_1CartesianVector.md) | [**reset\_payload\_parentage**](#function-reset_payload_parentage) () <br>_Resets the parentage of all payloads attached to the platform to this._  |
| virtual  | [**~PayloadPlatform**](#function-payloadplatform) () = default<br>_Default destructor for_ [_**PayloadPlatform**_](classastrea_1_1astro_1_1PayloadPlatform.md) _._ |








## Public Functions Documentation




### function attach\_payload 

_Attaches a single payload to the platform._ 
```C++
inline void astrea::astro::PayloadPlatform::attach_payload (
    const PayloadParameters_T & parameters
) 
```





**Parameters:**


* `parameters` The payload parameters to attach. 




        

<hr>



### function attach\_payloads 

_Attaches multiple payloads to the platform._ 
```C++
inline void astrea::astro::PayloadPlatform::attach_payloads (
    const std::vector< PayloadParameters_T > & parameterPack
) 
```





**Parameters:**


* `parameterPack` Vector of payload parameters to attach. 




        

<hr>



### function get\_id 

_Get the ID of the payload._ 
```C++
virtual std::size_t astrea::astro::PayloadPlatform::get_id () const = 0
```





**Returns:**

std::size\_t ID of the payload. 





        

<hr>



### function get\_mass 

_Get the mass of the platform._ 
```C++
inline virtual Mass astrea::astro::PayloadPlatform::get_mass () const
```





**Returns:**

Mass The mass of the platform. 





        

<hr>



### function get\_payloads [1/2]

_Retrieves the list of payloads attached to the platform._ 
```C++
inline std::vector< Payload_T > & astrea::astro::PayloadPlatform::get_payloads () 
```





**Returns:**

A vector of payloads attached to the platform. 





        

<hr>



### function get\_payloads [2/2]

_Retrieves the list of payloads attached to the platform (const version)._ 
```C++
inline const std::vector< Payload_T > & astrea::astro::PayloadPlatform::get_payloads () const
```





**Returns:**

A const vector of payloads attached to the platform. 





        

<hr>
## Protected Attributes Documentation




### variable \_payloads 

```C++
std::vector<Payload_T> astrea::astro::PayloadPlatform< Payload_T >::_payloads;
```




<hr>
## Protected Functions Documentation




### function PayloadPlatform [1/3]

_Default constructor for_ [_**PayloadPlatform**_](classastrea_1_1astro_1_1PayloadPlatform.md) _._
```C++
astrea::astro::PayloadPlatform::PayloadPlatform () = default
```




<hr>



### function PayloadPlatform [2/3]

_Copy constructor for_ [_**PayloadPlatform**_](classastrea_1_1astro_1_1PayloadPlatform.md) _._
```C++
inline astrea::astro::PayloadPlatform::PayloadPlatform (
    const  PayloadPlatform & other
) 
```





**Parameters:**


* `other` The other [**PayloadPlatform**](classastrea_1_1astro_1_1PayloadPlatform.md) to copy from. 




        

<hr>



### function PayloadPlatform [3/3]

_Move constructor for_ [_**PayloadPlatform**_](classastrea_1_1astro_1_1PayloadPlatform.md) _._
```C++
inline astrea::astro::PayloadPlatform::PayloadPlatform (
    PayloadPlatform && other
) noexcept
```





**Parameters:**


* `other` The other [**PayloadPlatform**](classastrea_1_1astro_1_1PayloadPlatform.md) to move from. 




        

<hr>



### function operator= 

_Copy assignment operator for_ [_**PayloadPlatform**_](classastrea_1_1astro_1_1PayloadPlatform.md) _._
```C++
inline PayloadPlatform & astrea::astro::PayloadPlatform::operator= (
    const  PayloadPlatform & other
) 
```





**Parameters:**


* `other` The other [**PayloadPlatform**](classastrea_1_1astro_1_1PayloadPlatform.md) to copy from. 



**Returns:**

[**PayloadPlatform**](classastrea_1_1astro_1_1PayloadPlatform.md)& Reference to this [**PayloadPlatform**](classastrea_1_1astro_1_1PayloadPlatform.md). 





        

<hr>



### function operator= 

_Move assignment operator for_ [_**PayloadPlatform**_](classastrea_1_1astro_1_1PayloadPlatform.md) _._
```C++
inline PayloadPlatform & astrea::astro::PayloadPlatform::operator= (
    PayloadPlatform && other
) noexcept
```





**Parameters:**


* `other` The other [**PayloadPlatform**](classastrea_1_1astro_1_1PayloadPlatform.md) to move from. 



**Returns:**

[**PayloadPlatform**](classastrea_1_1astro_1_1PayloadPlatform.md)& Reference to this [**PayloadPlatform**](classastrea_1_1astro_1_1PayloadPlatform.md). 





        

<hr>



### function reset\_payload\_parentage 

_Resets the parentage of all payloads attached to the platform to this._ 
```C++
inline void astrea::astro::PayloadPlatform::reset_payload_parentage () 
```




<hr>



### function ~PayloadPlatform 

_Default destructor for_ [_**PayloadPlatform**_](classastrea_1_1astro_1_1PayloadPlatform.md) _._
```C++
virtual astrea::astro::PayloadPlatform::~PayloadPlatform () = default
```




<hr>

------------------------------
The documentation for this class was generated from the following file `astrea/astro/astro/platforms/PayloadPlatform.hpp`

