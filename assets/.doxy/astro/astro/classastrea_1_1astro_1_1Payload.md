

# Class astrea::astro::Payload

**template &lt;class Payload\_T, class PayloadParameters\_T&gt;**



[**ClassList**](annotated.md) **>** [**astrea**](namespaceastrea.md) **>** [**astro**](namespaceastrea_1_1astro.md) **>** [**Payload**](classastrea_1_1astro_1_1Payload.md)



[_**Payload**_](classastrea_1_1astro_1_1Payload.md) _class representing a payload on a platform._[More...](#detailed-description)

* `#include <Payload.hpp>`





































## Public Functions

| Type | Name |
| ---: | :--- |
|  std::size\_t | [**generate\_id**](#function-generate_id) () const<br>_Generate a hash for the payload ID._  |
| virtual std::size\_t | [**get\_id**](#function-get_id) () const = 0<br>_Get the ID of the payload._  |
|  PayloadParameters\_T | [**get\_parameters**](#function-get_parameters) () const<br>_Get the payload parameters of the payload._  |
|  const [**PayloadPlatform**](classastrea_1_1astro_1_1PayloadPlatform.md)&lt; Payload\_T &gt; \*const | [**get\_parent**](#function-get_parent) () const<br>_Get the parent platform of the payload._  |








## Protected Attributes

| Type | Name |
| ---: | :--- |
|  std::size\_t | [**\_id**](#variable-_id-12)  <br>_Unique identifier for the payload._  |
|  PayloadParameters\_T | [**\_parameters**](#variable-_parameters-12)  <br>[_**Payload**_](classastrea_1_1astro_1_1Payload.md) _parameters._ |
|  const [**PayloadPlatform**](classastrea_1_1astro_1_1PayloadPlatform.md)&lt; Payload\_T &gt; \* | [**\_parent**](#variable-_parent)  <br>_Parent platform._  |
|  const PayloadParameters\_T & | [**parameters**](#variable-parameters)  <br> |
















## Protected Functions

| Type | Name |
| ---: | :--- |
|  const PayloadParameters\_T | [**\_id**](#function-_id-22) ([**generate\_id**](classastrea_1_1astro_1_1Payload.md#function-generate_id)()) <br> |
|  const PayloadParameters\_T | [**\_parameters**](#function-_parameters-22) (parameters) <br> |
|   | [**requires**](#function-requires-12) (std::is\_base\_of\_v&lt; [**PayloadPlatform**](classastrea_1_1astro_1_1PayloadPlatform.md)&lt; Payload\_T &gt;, Parent\_T &gt;) const<br>_Constructs a_ [_**Payload**_](classastrea_1_1astro_1_1Payload.md) _from a FieldOfView object._ |
|   | [**requires**](#function-requires-22) (std::is\_base\_of\_v&lt; [**PayloadPlatform**](classastrea_1_1astro_1_1PayloadPlatform.md)&lt; Payload\_T &gt;, Parent\_T &gt;) const<br>_Set the parent platform of the payload._  |
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
inline const PayloadPlatform < Payload_T > *const astrea::astro::Payload::get_parent () const
```





**Returns:**

const PayloadPlatform&lt;Payload\_T, PayloadParameters\_T&gt;\* Pointer to the parent platform. 





        

<hr>
## Protected Attributes Documentation




### variable \_id [1/2]

_Unique identifier for the payload._ 
```C++
std::size_t astrea::astro::Payload< Payload_T, PayloadParameters_T >::_id;
```




<hr>



### variable \_parameters [1/2]

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



### variable parameters 

```C++
const PayloadParameters_T& astrea::astro::Payload< Payload_T, PayloadParameters_T >::parameters;
```




<hr>
## Protected Functions Documentation




### function \_id [2/2]

```C++
inline const PayloadParameters_T astrea::astro::Payload::_id (
    generate_id ()
) 
```




<hr>



### function \_parameters [2/2]

```C++
const PayloadParameters_T astrea::astro::Payload::_parameters (
    parameters
) 
```




<hr>



### function requires [1/2]

_Constructs a_ [_**Payload**_](classastrea_1_1astro_1_1Payload.md) _from a FieldOfView object._
```C++
template<typename Parent_T>
astrea::astro::Payload::requires (
    std::is_base_of_v< PayloadPlatform < Payload_T >, Parent_T >
) const
```





**Parameters:**


* `parent` The parent platform to which the payload is attached. 
* `parameters` The parameters for the payload. 




        

<hr>



### function requires [2/2]

_Set the parent platform of the payload._ 
```C++
template<typename Parent_T>
inline astrea::astro::Payload::requires (
    std::is_base_of_v< PayloadPlatform < Payload_T >, Parent_T >
) const
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

