

# Class astrea::astro::Payload

**template &lt;[**class**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) [**Payload\_T**](classastrea_1_1astro_1_1DirectionCosineMatrix.md), [**class**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) PayloadParameters\_T&gt;**



[**ClassList**](annotated.md) **>** [**astrea**](namespaceastrea.md) **>** [**astro**](namespaceastrea_1_1astro.md) **>** [**Payload**](classastrea_1_1astro_1_1Payload.md)



[_**Payload**_](classastrea_1_1astro_1_1Payload.md) _class representing a payload on a platform._[More...](#detailed-description)

* `#include <Payload.hpp>`





































## Public Functions

| Type | Name |
| ---: | :--- |
| virtual std::size\_t | [**get\_id**](#function-get_id) () const = 0<br>_Get the ID of the payload._  |
|  std::string | [**get\_name**](#function-get_name) () const<br>_Get the name of the payload._  |
|  [**const**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) PayloadParameters\_T & | [**get\_parameters**](#function-get_parameters-12) () const<br>_Get the payload parameters of the payload._  |
|  PayloadParameters\_T & | [**get\_parameters**](#function-get_parameters-22) () <br>_Get the payload parameters of the payload._  |
|  [**const**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) [**PayloadPlatform**](classastrea_1_1astro_1_1PayloadPlatform.md)&lt; [**Payload\_T**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) &gt; \*[**const**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) | [**get\_parent**](#function-get_parent) () const<br>_Get the parent platform of the payload._  |
|  [**CartesianVector**](structastrea_1_1astro_1_1CartesianVector.md)&lt; [**Distance**](classastrea_1_1astro_1_1DirectionCosineMatrix.md), frames::primary &gt; | [**get\_position**](#function-get_position) ([**const**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) [**Date**](classastrea_1_1astro_1_1Date.md) & date) const<br>_Get the position of the payload in the primary frame._  |
|  [**CartesianVector**](structastrea_1_1astro_1_1CartesianVector.md)&lt; [**Velocity**](classastrea_1_1astro_1_1DirectionCosineMatrix.md), frames::primary &gt; | [**get\_velocity**](#function-get_velocity) ([**const**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) [**Date**](classastrea_1_1astro_1_1Date.md) & date) const<br>_Get the velocity of the payload in the primary frame. Assumes all payloads are fixed to their platform._  |








## Protected Attributes

| Type | Name |
| ---: | :--- |
|  std::size\_t | [**\_id**](#variable-_id)  <br>_Unique identifier for the payload._  |
|  PayloadParameters\_T | [**\_parameters**](#variable-_parameters)  <br>[_**Payload**_](classastrea_1_1astro_1_1Payload.md) _parameters._ |
|  [**const**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) [**PayloadPlatform**](classastrea_1_1astro_1_1PayloadPlatform.md)&lt; [**Payload\_T**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) &gt; \* | [**\_parent**](#variable-_parent)  <br>_Parent platform._  |
















## Protected Functions

| Type | Name |
| ---: | :--- |
|   | [**Payload**](#function-payload) ([**const**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) [**Parent\_T**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) & parent, [**const**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) PayloadParameters\_T & parameters) <br>_Constructs a_ [_**Payload**_](classastrea_1_1astro_1_1Payload.md) _from a FieldOfView object._ |
|  [**void**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) | [**set\_parent**](#function-set_parent) ([**const**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) [**Parent\_T**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) & parent) <br>_Set the parent platform of the payload._  |
| virtual  | [**~Payload**](#function-payload) () = default<br>_Default destructor for_ [_**Payload**_](classastrea_1_1astro_1_1Payload.md) _._ |




## Detailed Description


This class inherits from AccessObject and provides functionality for payloads, including field of view and access management. 


    
## Public Functions Documentation




### function get\_id 

_Get the ID of the payload._ 
```C++
virtual std::size_t astrea::astro::Payload::get_id () const = 0
```





**Returns:**

std::size\_t ID of the payload. 





        

<hr>



### function get\_name 

_Get the name of the payload._ 
```C++
inline std::string astrea::astro::Payload::get_name () const
```





**Returns:**

std::string Name of the payload. 





        

<hr>



### function get\_parameters [1/2]

_Get the payload parameters of the payload._ 
```C++
inline const PayloadParameters_T & astrea::astro::Payload::get_parameters () const
```





**Returns:**

PayloadParameters\_T [**Payload**](classastrea_1_1astro_1_1Payload.md) parameters of the payload. 





        

<hr>



### function get\_parameters [2/2]

_Get the payload parameters of the payload._ 
```C++
inline PayloadParameters_T & astrea::astro::Payload::get_parameters () 
```





**Returns:**

PayloadParameters\_T [**Payload**](classastrea_1_1astro_1_1Payload.md) parameters of the payload. 





        

<hr>



### function get\_parent 

_Get the parent platform of the payload._ 
```C++
inline const  PayloadPlatform < Payload_T > * const astrea::astro::Payload::get_parent () const
```





**Returns:**

const PayloadPlatform&lt;Payload\_T, PayloadParameters\_T&gt;\* Pointer to the parent platform. 





        

<hr>



### function get\_position 

_Get the position of the payload in the primary frame._ 
```C++
inline CartesianVector < Distance , frames::primary > astrea::astro::Payload::get_position (
    const  Date & date
) const
```





**Parameters:**


* `date` The date for which to get the position. 



**Returns:**

CartesianVector&lt;Distance, frames::primary&gt; Position of the payload in the primary frame. 





        

<hr>



### function get\_velocity 

_Get the velocity of the payload in the primary frame. Assumes all payloads are fixed to their platform._ 
```C++
inline CartesianVector < Velocity , frames::primary > astrea::astro::Payload::get_velocity (
    const  Date & date
) const
```





**Parameters:**


* `date` The date for which to get the velocity. 



**Returns:**

CartesianVector&lt;Velocity, frames::primary&gt; Velocity of the payload in the primary frame. 





        

<hr>
## Protected Attributes Documentation




### variable \_id 

_Unique identifier for the payload._ 
```C++
std::size_t astrea::astro::Payload< Payload_T, PayloadParameters_T >::_id;
```




<hr>



### variable \_parameters 

[_**Payload**_](classastrea_1_1astro_1_1Payload.md) _parameters._
```C++
PayloadParameters_T astrea::astro::Payload< Payload_T, PayloadParameters_T >::_parameters;
```




<hr>



### variable \_parent 

_Parent platform._ 
```C++
const PayloadPlatform<Payload_T>* astrea::astro::Payload< Payload_T, PayloadParameters_T >::_parent;
```




<hr>
## Protected Functions Documentation




### function Payload 

_Constructs a_ [_**Payload**_](classastrea_1_1astro_1_1Payload.md) _from a FieldOfView object._
```C++
template<typename  Parent_T>
inline astrea::astro::Payload::Payload (
    const  Parent_T & parent,
    const PayloadParameters_T & parameters
) 
```





**Parameters:**


* `parent` The parent platform to which the payload is attached. 
* `parameters` The parameters for the payload. 




        

<hr>



### function set\_parent 

_Set the parent platform of the payload._ 
```C++
template<typename  Parent_T>
inline void astrea::astro::Payload::set_parent (
    const  Parent_T & parent
) 
```





**Template parameters:**


* `T` Type of the parent platform. 



**Parameters:**


* `parent` The parent platform to set. 




        

<hr>



### function ~Payload 

_Default destructor for_ [_**Payload**_](classastrea_1_1astro_1_1Payload.md) _._
```C++
virtual astrea::astro::Payload::~Payload () = default
```




<hr>

------------------------------
The documentation for this class was generated from the following file `astrea/astro/astro/platforms/Payload.hpp`

