

# Class astrea::astro::Thruster



[**ClassList**](annotated.md) **>** [**astrea**](namespaceastrea.md) **>** [**astro**](namespaceastrea_1_1astro.md) **>** [**Thruster**](classastrea_1_1astro_1_1Thruster.md)



[_**Thruster**_](classastrea_1_1astro_1_1Thruster.md) _class representing a thruster on a platform._[More...](#detailed-description)

* `#include <Thruster.hpp>`



Inherits the following classes: [astrea::astro::Payload](classastrea_1_1astro_1_1Payload.md)






















































## Public Functions

| Type | Name |
| ---: | :--- |
|   | [**Thruster**](#function-thruster) ([**const**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) [**Parent\_T**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) & parent, [**const**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) [**ThrusterParameters**](classastrea_1_1astro_1_1ThrusterParameters.md) & parameters) <br>_Constructor for_ [_**Thruster**_](classastrea_1_1astro_1_1Thruster.md) _._ |
| virtual std::size\_t | [**get\_id**](#function-get_id) () const<br>_Get the ID of the sensor._  |
|  [**Velocity**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) | [**get\_impulsive\_delta\_v**](#function-get_impulsive_delta_v) () const<br>_Get the impulsive delta-v provided by the thruster._  |
|  [**Force**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) | [**get\_thrust**](#function-get_thrust) () const<br>_Get the thrust of the thruster for a given state._  |
|  [**bool**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) | [**is\_on**](#function-is_on) () const<br>_Check if the thruster is on._  |
|  [**void**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) | [**switch\_off**](#function-switch_off) () <br>_Switch the thruster off._  |
|  [**void**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) | [**switch\_on**](#function-switch_on) () <br>_Switch the thruster on._  |
| virtual  | [**~Thruster**](#function-thruster) () = default<br>_Default destructor for_ [_**Thruster**_](classastrea_1_1astro_1_1Thruster.md) _._ |


## Public Functions inherited from astrea::astro::Payload

See [astrea::astro::Payload](classastrea_1_1astro_1_1Payload.md)

| Type | Name |
| ---: | :--- |
| virtual std::size\_t | [**get\_id**](classastrea_1_1astro_1_1Payload.md#function-get_id) () const = 0<br>_Get the ID of the payload._  |
|  std::string | [**get\_name**](classastrea_1_1astro_1_1Payload.md#function-get_name) () const<br>_Get the name of the payload._  |
|  [**const**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) PayloadParameters\_T & | [**get\_parameters**](classastrea_1_1astro_1_1Payload.md#function-get_parameters-12) () const<br>_Get the payload parameters of the payload._  |
|  PayloadParameters\_T & | [**get\_parameters**](classastrea_1_1astro_1_1Payload.md#function-get_parameters-22) () <br>_Get the payload parameters of the payload._  |
|  [**const**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) [**PayloadPlatform**](classastrea_1_1astro_1_1PayloadPlatform.md)&lt; [**Payload\_T**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) &gt; \*[**const**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) | [**get\_parent**](classastrea_1_1astro_1_1Payload.md#function-get_parent) () const<br>_Get the parent platform of the payload._  |
|  [**CartesianVector**](structastrea_1_1astro_1_1CartesianVector.md)&lt; [**Distance**](classastrea_1_1astro_1_1DirectionCosineMatrix.md), frames::primary &gt; | [**get\_position**](classastrea_1_1astro_1_1Payload.md#function-get_position) ([**const**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) [**Date**](classastrea_1_1astro_1_1Date.md) & date) const<br>_Get the position of the payload in the primary frame._  |
|  [**CartesianVector**](structastrea_1_1astro_1_1CartesianVector.md)&lt; [**Velocity**](classastrea_1_1astro_1_1DirectionCosineMatrix.md), frames::primary &gt; | [**get\_velocity**](classastrea_1_1astro_1_1Payload.md#function-get_velocity) ([**const**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) [**Date**](classastrea_1_1astro_1_1Date.md) & date) const<br>_Get the velocity of the payload in the primary frame. Assumes all payloads are fixed to their platform._  |
















## Protected Attributes inherited from astrea::astro::Payload

See [astrea::astro::Payload](classastrea_1_1astro_1_1Payload.md)

| Type | Name |
| ---: | :--- |
|  std::size\_t | [**\_id**](classastrea_1_1astro_1_1Payload.md#variable-_id)  <br>_Unique identifier for the payload._  |
|  PayloadParameters\_T | [**\_parameters**](classastrea_1_1astro_1_1Payload.md#variable-_parameters)  <br>[_**Payload**_](classastrea_1_1astro_1_1Payload.md) _parameters._ |
|  [**const**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) [**PayloadPlatform**](classastrea_1_1astro_1_1PayloadPlatform.md)&lt; [**Payload\_T**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) &gt; \* | [**\_parent**](classastrea_1_1astro_1_1Payload.md#variable-_parent)  <br>_Parent platform._  |
































## Protected Functions inherited from astrea::astro::Payload

See [astrea::astro::Payload](classastrea_1_1astro_1_1Payload.md)

| Type | Name |
| ---: | :--- |
|   | [**Payload**](classastrea_1_1astro_1_1Payload.md#function-payload) ([**const**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) [**Parent\_T**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) & parent, [**const**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) PayloadParameters\_T & parameters) <br>_Constructs a_ [_**Payload**_](classastrea_1_1astro_1_1Payload.md) _from a FieldOfView object._ |
|  [**void**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) | [**set\_parent**](classastrea_1_1astro_1_1Payload.md#function-set_parent) ([**const**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) [**Parent\_T**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) & parent) <br>_Set the parent platform of the payload._  |
| virtual  | [**~Payload**](classastrea_1_1astro_1_1Payload.md#function-payload) () = default<br>_Default destructor for_ [_**Payload**_](classastrea_1_1astro_1_1Payload.md) _._ |






## Detailed Description


This class inherits from AccessObject and provides functionality for thrusters, including field of view and access management. 


    
## Public Functions Documentation




### function Thruster 

_Constructor for_ [_**Thruster**_](classastrea_1_1astro_1_1Thruster.md) _._
```C++
template<typename  Parent_T>
inline astrea::astro::Thruster::Thruster (
    const  Parent_T & parent,
    const  ThrusterParameters & parameters
) 
```





**Parameters:**


* `parent` Parent frame reference. 
* `parameters` [**Thruster**](classastrea_1_1astro_1_1Thruster.md) parameters. 




        

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



### function get\_thrust 

_Get the thrust of the thruster for a given state._ 
```C++
Force astrea::astro::Thruster::get_thrust () const
```





**Parameters:**


* `state` The state of the vehicle for which to get the thrust. 



**Returns:**

Force The thrust of the thruster. 





        

<hr>



### function is\_on 

_Check if the thruster is on._ 
```C++
bool astrea::astro::Thruster::is_on () const
```





**Returns:**

true if the thruster is on, false otherwise. 





        

<hr>



### function switch\_off 

_Switch the thruster off._ 
```C++
void astrea::astro::Thruster::switch_off () 
```




<hr>



### function switch\_on 

_Switch the thruster on._ 
```C++
void astrea::astro::Thruster::switch_on () 
```




<hr>



### function ~Thruster 

_Default destructor for_ [_**Thruster**_](classastrea_1_1astro_1_1Thruster.md) _._
```C++
virtual astrea::astro::Thruster::~Thruster () = default
```




<hr>

------------------------------
The documentation for this class was generated from the following file `astrea/astro/astro/platforms/thrusters/Thruster.hpp`

