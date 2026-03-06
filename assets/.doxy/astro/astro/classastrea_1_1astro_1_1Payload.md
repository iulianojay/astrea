

# Class astrea::astro::Payload

**template &lt;[**class**](classastrea_1_1astro_1_1CartesianVector.md) [**Payload\_T**](classastrea_1_1astro_1_1CartesianVector.md), [**class**](classastrea_1_1astro_1_1CartesianVector.md) PayloadParameters\_T&gt;**



[**ClassList**](annotated.md) **>** [**astrea**](namespaceastrea.md) **>** [**astro**](namespaceastrea_1_1astro.md) **>** [**Payload**](classastrea_1_1astro_1_1Payload.md)



[_**Payload**_](classastrea_1_1astro_1_1Payload.md) _class representing a payload on a platform._[More...](#detailed-description)

* `#include <Payload.hpp>`





































## Public Functions

| Type | Name |
| ---: | :--- |
|  std::size\_t | [**generate\_id**](#function-generate_id) () const<br>_Generate a hash for the payload ID._  |
| virtual std::size\_t | [**get\_id**](#function-get_id) () const = 0<br>_Get the ID of the payload._  |
|  PayloadParameters\_T | [**get\_parameters**](#function-get_parameters) () const<br>_Get the payload parameters of the payload._  |
|  [**const**](classastrea_1_1astro_1_1CartesianVector.md) [**PayloadPlatform**](classastrea_1_1astro_1_1PayloadPlatform.md)&lt; [**Payload\_T**](classastrea_1_1astro_1_1CartesianVector.md) &gt; \*[**const**](classastrea_1_1astro_1_1CartesianVector.md) | [**get\_parent**](#function-get_parent) () const<br>_Get the parent platform of the payload._  |








## Protected Attributes

| Type | Name |
| ---: | :--- |
|  std::size\_t | [**\_id**](#variable-_id)  <br>_Unique identifier for the payload._  |
|  PayloadParameters\_T | [**\_parameters**](#variable-_parameters)  <br>[_**Payload**_](classastrea_1_1astro_1_1Payload.md) _parameters._ |
|  [**const**](classastrea_1_1astro_1_1CartesianVector.md) [**PayloadPlatform**](classastrea_1_1astro_1_1PayloadPlatform.md)&lt; [**Payload\_T**](classastrea_1_1astro_1_1CartesianVector.md) &gt; \* | [**\_parent**](#variable-_parent)  <br>_Parent platform._  |
















## Protected Functions

| Type | Name |
| ---: | :--- |
|   | [**Payload**](#function-payload) ([**const**](classastrea_1_1astro_1_1CartesianVector.md) [**Parent\_T**](classastrea_1_1astro_1_1CartesianVector.md) & parent, [**const**](classastrea_1_1astro_1_1CartesianVector.md) PayloadParameters\_T & parameters) <br>_Constructs a_ [_**Payload**_](classastrea_1_1astro_1_1Payload.md) _from a FieldOfView object._ |
|  [**void**](classastrea_1_1astro_1_1CartesianVector.md) | [**set\_parent**](#function-set_parent) ([**const**](classastrea_1_1astro_1_1CartesianVector.md) [**Parent\_T**](classastrea_1_1astro_1_1CartesianVector.md) & parent) <br>_Set the parent platform of the payload._  |
| virtual  | [**~Payload**](#function-payload) () = default<br>_Default destructor for_ [_**Payload**_](classastrea_1_1astro_1_1Payload.md) _._ |




## Detailed Description


This class inherits from AccessObject and provides functionality for payloads, including field of view and access management. 


    
## Public Functions Documentation




### function generate\_id 

_Generate a hash for the payload ID._ 
```C++
inline std::size_t astrea::astro::Payload::generate_id () const
```




<hr>



### function get\_id 

_Get the ID of the payload._ 
```C++
virtual std::size_t astrea::astro::Payload::get_id () const = 0
```





**Returns:**

std::size\_t ID of the payload. 





        

<hr>



### function get\_parameters 

_Get the payload parameters of the payload._ 
```C++
inline PayloadParameters_T astrea::astro::Payload::get_parameters () const
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

