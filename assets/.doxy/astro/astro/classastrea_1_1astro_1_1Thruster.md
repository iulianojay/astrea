

# Class astrea::astro::Thruster



[**ClassList**](annotated.md) **>** [**astrea**](namespaceastrea.md) **>** [**astro**](namespaceastrea_1_1astro.md) **>** [**Thruster**](classastrea_1_1astro_1_1Thruster.md)



[_**Thruster**_](classastrea_1_1astro_1_1Thruster.md) _class representing a thruster on a platform._[More...](#detailed-description)

* `#include <Thruster.hpp>`



Inherits the following classes: [astrea::astro::Payload](classastrea_1_1astro_1_1Payload.md)






















## Public Attributes

| Type | Name |
| ---: | :--- |
|  const [**ThrusterParameters**](classastrea_1_1astro_1_1ThrusterParameters.md) & | [**parameters**](#variable-parameters)  <br> |
































## Public Functions

| Type | Name |
| ---: | :--- |
|  const [**ThrusterParameters**](classastrea_1_1astro_1_1ThrusterParameters.md) | [**ThrusterParameters**](#function-thrusterparameters) (parent, parameters) <br> |
| virtual std::size\_t | [**get\_id**](#function-get_id) () const<br>_Get the ID of the sensor._  |
|  Velocity | [**get\_impulsive\_delta\_v**](#function-get_impulsive_delta_v) () const<br>_Get the impulsive delta-v provided by the thruster._  |
|   | [**requires**](#function-requires) (std::is\_base\_of\_v&lt; [**FrameReference**](classastrea_1_1astro_1_1FrameReference.md), Parent\_T &gt;) const<br>_Constructor for_ [_**Thruster**_](classastrea_1_1astro_1_1Thruster.md) _._ |
| virtual  | [**~Thruster**](#function-thruster) () = default<br>_Default destructor for_ [_**Thruster**_](classastrea_1_1astro_1_1Thruster.md) _._ |


## Public Functions inherited from astrea::astro::Payload

See [astrea::astro::Payload](classastrea_1_1astro_1_1Payload.md)

| Type | Name |
| ---: | :--- |
|  std::size\_t | [**generate\_id**](classastrea_1_1astro_1_1Payload.md#function-generate_id) () const<br>_Generate a hash for the payload ID._  |
| virtual std::size\_t | [**get\_id**](classastrea_1_1astro_1_1Payload.md#function-get_id) () const = 0<br>_Get the ID of the payload._  |
|  PayloadParameters\_T | [**get\_parameters**](classastrea_1_1astro_1_1Payload.md#function-get_parameters) () const<br>_Get the payload parameters of the payload._  |
|  const [**PayloadPlatform**](classastrea_1_1astro_1_1PayloadPlatform.md)&lt; Payload\_T &gt; \*const | [**get\_parent**](classastrea_1_1astro_1_1Payload.md#function-get_parent) () const<br>_Get the parent platform of the payload._  |
















## Protected Attributes inherited from astrea::astro::Payload

See [astrea::astro::Payload](classastrea_1_1astro_1_1Payload.md)

| Type | Name |
| ---: | :--- |
|  std::size\_t | [**\_id**](classastrea_1_1astro_1_1Payload.md#variable-_id-12)  <br>_Unique identifier for the payload._  |
|  PayloadParameters\_T | [**\_parameters**](classastrea_1_1astro_1_1Payload.md#variable-_parameters-12)  <br>[_**Payload**_](classastrea_1_1astro_1_1Payload.md) _parameters._ |
|  const [**PayloadPlatform**](classastrea_1_1astro_1_1PayloadPlatform.md)&lt; Payload\_T &gt; \* | [**\_parent**](classastrea_1_1astro_1_1Payload.md#variable-_parent)  <br>_Parent platform._  |
|  const PayloadParameters\_T & | [**parameters**](classastrea_1_1astro_1_1Payload.md#variable-parameters)  <br> |
































## Protected Functions inherited from astrea::astro::Payload

See [astrea::astro::Payload](classastrea_1_1astro_1_1Payload.md)

| Type | Name |
| ---: | :--- |
|  const PayloadParameters\_T | [**\_id**](classastrea_1_1astro_1_1Payload.md#function-_id-22) ([**generate\_id**](classastrea_1_1astro_1_1Payload.md#function-generate_id)()) <br> |
|  const PayloadParameters\_T | [**\_parameters**](classastrea_1_1astro_1_1Payload.md#function-_parameters-22) (parameters) <br> |
|   | [**requires**](classastrea_1_1astro_1_1Payload.md#function-requires-12) (std::is\_base\_of\_v&lt; [**PayloadPlatform**](classastrea_1_1astro_1_1PayloadPlatform.md)&lt; Payload\_T &gt;, Parent\_T &gt;) const<br>_Constructs a_ [_**Payload**_](classastrea_1_1astro_1_1Payload.md) _from a FieldOfView object._ |
|   | [**requires**](classastrea_1_1astro_1_1Payload.md#function-requires-22) (std::is\_base\_of\_v&lt; [**PayloadPlatform**](classastrea_1_1astro_1_1PayloadPlatform.md)&lt; Payload\_T &gt;, Parent\_T &gt;) const<br>_Set the parent platform of the payload._  |
| virtual  | [**~Payload**](classastrea_1_1astro_1_1Payload.md#function-payload) () = default<br>_Default destructor for_ [_**Payload**_](classastrea_1_1astro_1_1Payload.md) _._ |






## Detailed Description


This class inherits from AccessObject and provides functionality for thrusters, including field of view and access management. 


    
## Public Attributes Documentation




### variable parameters 

```C++
const ThrusterParameters& astrea::astro::Thruster::parameters;
```




<hr>
## Public Functions Documentation




### function ThrusterParameters 

```C++
inline const ThrusterParameters astrea::astro::Thruster::ThrusterParameters (
    parent,
    parameters
) 
```




<hr>



### function get\_id 

_Get the ID of the sensor._ 
```C++
virtual std::size_t astrea::astro::Thruster::get_id () const
```





**Returns:**

std::size\_t ID of the sensor. 





        
Implements [*astrea::astro::Payload::get\_id*](classastrea_1_1astro_1_1Payload.md#function-get_id)


<hr>



### function get\_impulsive\_delta\_v 

_Get the impulsive delta-v provided by the thruster._ 
```C++
Velocity astrea::astro::Thruster::get_impulsive_delta_v () const
```





**Returns:**

Velocity The impulsive delta-v. 





        

<hr>



### function requires 

_Constructor for_ [_**Thruster**_](classastrea_1_1astro_1_1Thruster.md) _._
```C++
template<typename Parent_T>
astrea::astro::Thruster::requires (
    std::is_base_of_v< FrameReference , Parent_T >
) const
```





**Parameters:**


* `parent` Parent frame reference. 
* `parameters` [**Thruster**](classastrea_1_1astro_1_1Thruster.md) parameters. 




        

<hr>



### function ~Thruster 

_Default destructor for_ [_**Thruster**_](classastrea_1_1astro_1_1Thruster.md) _._
```C++
virtual astrea::astro::Thruster::~Thruster () = default
```




<hr>

------------------------------
The documentation for this class was generated from the following file `astrea/astro/astro/platforms/thrusters/Thruster.hpp`

