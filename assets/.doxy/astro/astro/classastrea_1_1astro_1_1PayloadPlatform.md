

# Class astrea::astro::PayloadPlatform

**template &lt;[**class**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) [**Payload\_T**](classastrea_1_1astro_1_1DirectionCosineMatrix.md)&gt;**



[**ClassList**](annotated.md) **>** [**astrea**](namespaceastrea.md) **>** [**astro**](namespaceastrea_1_1astro.md) **>** [**PayloadPlatform**](classastrea_1_1astro_1_1PayloadPlatform.md)



_The_ [_**PayloadPlatform**_](classastrea_1_1astro_1_1PayloadPlatform.md) _class represents a platform that can have payloads attached to it. It provides methods to attach payloads and retrieve the list of attached payloads._

* `#include <PayloadPlatform.hpp>`





































## Public Functions

| Type | Name |
| ---: | :--- |
|  [**void**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) | [**attach\_payload**](#function-attach_payload) ([**const**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) [**PayloadParameters\_T**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) & parameters) <br>_Attaches a single payload to the platform._  |
|  [**void**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) | [**attach\_payloads**](#function-attach_payloads) ([**const**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) std::vector&lt; [**PayloadParameters\_T**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) &gt; & parameterPack) <br>_Attaches multiple payloads to the platform._  |
| virtual std::size\_t | [**get\_id**](#function-get_id) () const = 0<br>_Get the ID of the payload._  |
| virtual [**Mass**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) | [**get\_mass**](#function-get_mass) () const<br>_Get the mass of the platform._  |
|  std::vector&lt; [**Payload\_T**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) &gt; & | [**get\_payloads**](#function-get_payloads-12) () <br>_Retrieves the list of payloads attached to the platform._  |
|  [**const**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) std::vector&lt; [**Payload\_T**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) &gt; & | [**get\_payloads**](#function-get_payloads-22) () const<br>_Retrieves the list of payloads attached to the platform (const version)._  |
| virtual [**RadiusVector**](namespaceastrea_1_1astro.md#typedef-radiusvector)&lt; frames::primary &gt; | [**get\_position**](#function-get_position) ([**const**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) [**Date**](classastrea_1_1astro_1_1Date.md) & date) const = 0<br>_Get the position of the platform._  |
| virtual [**VelocityVector**](namespaceastrea_1_1astro.md#typedef-velocityvector)&lt; frames::primary &gt; | [**get\_velocity**](#function-get_velocity) ([**const**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) [**Date**](classastrea_1_1astro_1_1Date.md) & date) const = 0<br>_Get the velocity of the platform._  |








## Protected Attributes

| Type | Name |
| ---: | :--- |
|  std::vector&lt; [**Payload\_T**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) &gt; | [**\_payloads**](#variable-_payloads)  <br> |
















## Protected Functions

| Type | Name |
| ---: | :--- |
|   | [**PayloadPlatform**](#function-payloadplatform-13) () = default<br>_Default constructor for_ [_**PayloadPlatform**_](classastrea_1_1astro_1_1PayloadPlatform.md) _._ |
|   | [**PayloadPlatform**](#function-payloadplatform-23) ([**const**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) [**PayloadPlatform**](classastrea_1_1astro_1_1PayloadPlatform.md) & other) <br>_Copy constructor for_ [_**PayloadPlatform**_](classastrea_1_1astro_1_1PayloadPlatform.md) _._ |
|   | [**PayloadPlatform**](#function-payloadplatform-33) ([**PayloadPlatform**](classastrea_1_1astro_1_1PayloadPlatform.md) && other) noexcept<br>_Move constructor for_ [_**PayloadPlatform**_](classastrea_1_1astro_1_1PayloadPlatform.md) _._ |
|  [**PayloadPlatform**](classastrea_1_1astro_1_1PayloadPlatform.md) & | [**operator=**](#function-operator) ([**const**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) [**PayloadPlatform**](classastrea_1_1astro_1_1PayloadPlatform.md) & other) <br>_Copy assignment operator for_ [_**PayloadPlatform**_](classastrea_1_1astro_1_1PayloadPlatform.md) _._ |
|  [**PayloadPlatform**](classastrea_1_1astro_1_1PayloadPlatform.md) & | [**operator=**](#function-operator_1) ([**PayloadPlatform**](classastrea_1_1astro_1_1PayloadPlatform.md) && other) noexcept<br>_Move assignment operator for_ [_**PayloadPlatform**_](classastrea_1_1astro_1_1PayloadPlatform.md) _._ |
|  [**void**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) | [**reset\_payload\_parentage**](#function-reset_payload_parentage) () <br>_Resets the parentage of all payloads attached to the platform to this._  |
| virtual  | [**~PayloadPlatform**](#function-payloadplatform) () = default<br>_Default destructor for_ [_**PayloadPlatform**_](classastrea_1_1astro_1_1PayloadPlatform.md) _._ |




## Public Functions Documentation




### function attach\_payload 

_Attaches a single payload to the platform._ 
```C++
inline void astrea::astro::PayloadPlatform::attach_payload (
    const  PayloadParameters_T & parameters
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



### function get\_position 

_Get the position of the platform._ 
```C++
virtual RadiusVector < frames::primary > astrea::astro::PayloadPlatform::get_position (
    const  Date & date
) const = 0
```





**Parameters:**


* `date` The date for which to get the position. 



**Returns:**

[**RadiusVector&lt;frames::primary&gt;**](namespaceastrea_1_1astro.md#typedef-radiusvector) Position of the platform. 





        

<hr>



### function get\_velocity 

_Get the velocity of the platform._ 
```C++
virtual VelocityVector < frames::primary > astrea::astro::PayloadPlatform::get_velocity (
    const  Date & date
) const = 0
```





**Parameters:**


* `date` The date for which to get the velocity. 



**Returns:**

[**VelocityVector&lt;frames::primary&gt;**](namespaceastrea_1_1astro.md#typedef-velocityvector) Velocity of the platform. 





        

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

