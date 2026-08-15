

# Class astrea::astro::State



[**ClassList**](annotated.md) **>** [**astrea**](namespaceastrea.md) **>** [**astro**](namespaceastrea_1_1astro.md) **>** [**State**](classastrea_1_1astro_1_1State.md)



_Class representing the state of an astronomical object. This class encapsulates the orbital elements, epoch, and the astrodynamics system that the state belongs to. It also optionally includes the attitude of the object as a quaternion._ 

* `#include <State.hpp>`





































## Public Functions

| Type | Name |
| ---: | :--- |
|   | [**State**](#function-state-14) () = default<br>_Default constructor for_ [_**State**_](classastrea_1_1astro_1_1State.md) _._ |
|   | [**State**](#function-state-24) (const [**OrbitalElements**](classastrea_1_1astro_1_1OrbitalElements.md) & elements, const [**Date**](classastrea_1_1astro_1_1Date.md) & epoch, const std::optional&lt; [**Attitude**](classastrea_1_1astro_1_1Attitude.md) &gt; & attitude=std::nullopt) <br>_Constructs a_ [_**State**_](classastrea_1_1astro_1_1State.md) _with given orbital elements, epoch, and astrodynamics system._ |
|   | [**State**](#function-state-34) ([**Cartesian**](classastrea_1_1astro_1_1Cartesian.md)&lt; frame &gt; elements, const [**Date**](classastrea_1_1astro_1_1Date.md) & epoch, const std::optional&lt; [**Attitude**](classastrea_1_1astro_1_1Attitude.md) &gt; & attitude=std::nullopt) <br>_Constructs a_ [_**State**_](classastrea_1_1astro_1_1State.md) _from a_[_**Cartesian**_](classastrea_1_1astro_1_1Cartesian.md) _in any frame, converting it to the primary frame._ |
|   | [**State**](#function-state-44) (const [**StateHistory**](classastrea_1_1astro_1_1StateHistory.md) & history) <br>_Constructs a_ [_**State**_](classastrea_1_1astro_1_1State.md) _from a_[_**StateHistory**_](classastrea_1_1astro_1_1StateHistory.md) _object._ |
|  void | [**convert\_to\_set**](#function-convert_to_set-14) () <br>_Converts the orbital elements to a different type._  |
|  [**State**](classastrea_1_1astro_1_1State.md) & | [**convert\_to\_set**](#function-convert_to_set-24) (const std::size\_t idx) <br>_Converts the orbital elements to a different type based on index._  |
|  [**State**](classastrea_1_1astro_1_1State.md) | [**convert\_to\_set**](#function-convert_to_set-34) (const std::size\_t idx) const<br>_Converts the state to a different type of orbital elements based on index._  |
|  [**State**](classastrea_1_1astro_1_1State.md) | [**convert\_to\_set**](#function-convert_to_set-44) () const<br>_Converts the state to a different type of orbital elements._  |
|  const std::optional&lt; [**Attitude**](classastrea_1_1astro_1_1Attitude.md) &gt; & | [**get\_attitude**](#function-get_attitude) () const<br>_Get the attitude of the state._  |
|  const [**OrbitalElements**](classastrea_1_1astro_1_1OrbitalElements.md) & | [**get\_elements**](#function-get_elements) () const<br>_Gets the orbital elements of the state._  |
|  const [**Date**](classastrea_1_1astro_1_1Date.md) & | [**get\_epoch**](#function-get_epoch) () const<br>_Gets the epoch of the state._  |
|  GravParam | [**get\_mu**](#function-get_mu) () const<br>_Gets the gravitational parameter (mu) derived from the origin of the current elements' frame._  |
|  [**RadiusVector**](namespaceastrea_1_1astro.md#typedef-radiusvector)&lt; frames::primary &gt; | [**get\_position**](#function-get_position) () const<br>_Gets the position vector from the state._  |
|  [**RadiusVector**](namespaceastrea_1_1astro.md#typedef-radiusvector)&lt; \_frame\_ &gt; | [**get\_position\_in\_frame**](#function-get_position_in_frame) () const<br>_Gets the position vector in a specified frame from the state._  |
|  [**VelocityVector**](namespaceastrea_1_1astro.md#typedef-velocityvector)&lt; frames::primary &gt; | [**get\_velocity**](#function-get_velocity) () const<br>_Gets the velocity vector from the state._  |
|  [**VelocityVector**](namespaceastrea_1_1astro.md#typedef-velocityvector)&lt; \_frame\_ &gt; | [**get\_velocity\_in\_frame**](#function-get_velocity_in_frame) (const [**Date**](classastrea_1_1astro_1_1Date.md) & date) const<br>_Gets the velocity vector in a specified frame from the state._  |
|  T | [**in\_element\_set**](#function-in_element_set) () const<br>_Converts the current orbital elements to a specified type._  |
|  bool | [**operator==**](#function-operator) (const [**State**](classastrea_1_1astro_1_1State.md) & other) const<br>_Checks if two_ [_**State**_](classastrea_1_1astro_1_1State.md) _objects are equal._ |
|  void | [**set\_attitude**](#function-set_attitude) (const [**Attitude**](classastrea_1_1astro_1_1Attitude.md) & attitude) <br>_Sets the attitude of the state._  |
|  void | [**set\_elements**](#function-set_elements) (const T & elements, const bool convertToOriginal=false) <br>_Sets the orbital elements of the state._  |
|  void | [**set\_epoch**](#function-set_epoch) (const [**Date**](classastrea_1_1astro_1_1Date.md) & epoch) <br>_Sets the epoch of the state._  |




























## Public Functions Documentation




### function State [1/4]

_Default constructor for_ [_**State**_](classastrea_1_1astro_1_1State.md) _._
```C++
astrea::astro::State::State () = default
```




<hr>



### function State [2/4]

_Constructs a_ [_**State**_](classastrea_1_1astro_1_1State.md) _with given orbital elements, epoch, and astrodynamics system._
```C++
inline astrea::astro::State::State (
    const OrbitalElements & elements,
    const Date & epoch,
    const std::optional< Attitude > & attitude=std::nullopt
) 
```





**Parameters:**


* `elements` The orbital elements of the state. 
* `epoch` The epoch of the state. 
* `attitude` The attitude of the state, represented as a quaternion. 




        

<hr>



### function State [3/4]

_Constructs a_ [_**State**_](classastrea_1_1astro_1_1State.md) _from a_[_**Cartesian**_](classastrea_1_1astro_1_1Cartesian.md) _in any frame, converting it to the primary frame._
```C++
template<IsFrame auto frame>
inline astrea::astro::State::State (
    Cartesian < frame > elements,
    const Date & epoch,
    const std::optional< Attitude > & attitude=std::nullopt
) 
```





**Parameters:**


* `elements` [**Cartesian**](classastrea_1_1astro_1_1Cartesian.md) elements in an arbitrary inertial frame. 
* `epoch` The epoch of the state. 
* `attitude` The attitude of the state. 




        

<hr>



### function State [4/4]

_Constructs a_ [_**State**_](classastrea_1_1astro_1_1State.md) _from a_[_**StateHistory**_](classastrea_1_1astro_1_1StateHistory.md) _object._
```C++
astrea::astro::State::State (
    const StateHistory & history
) 
```





**Parameters:**


* `history` The [**StateHistory**](classastrea_1_1astro_1_1StateHistory.md) object to construct the [**State**](classastrea_1_1astro_1_1State.md) from.



**Note:**

This only works if the [**StateHistory**](classastrea_1_1astro_1_1StateHistory.md) contains exactly one state. 





        

<hr>



### function convert\_to\_set [1/4]

_Converts the orbital elements to a different type._ 
```C++
template<IsOrbitalElements T>
inline void astrea::astro::State::convert_to_set () 
```





**Template parameters:**


* `T` The type to convert the orbital elements to. 




        

<hr>



### function convert\_to\_set [2/4]

_Converts the orbital elements to a different type based on index._ 
```C++
inline State & astrea::astro::State::convert_to_set (
    const std::size_t idx
) 
```





**Parameters:**


* `idx` The index of the orbital element type to convert to. 




        

<hr>



### function convert\_to\_set [3/4]

_Converts the state to a different type of orbital elements based on index._ 
```C++
inline State astrea::astro::State::convert_to_set (
    const std::size_t idx
) const
```





**Parameters:**


* `idx` The index of the orbital element type to convert to. 



**Returns:**

[**State**](classastrea_1_1astro_1_1State.md) A new [**State**](classastrea_1_1astro_1_1State.md) object with the converted orbital elements. 





        

<hr>



### function convert\_to\_set [4/4]

_Converts the state to a different type of orbital elements._ 
```C++
template<IsOrbitalElements T>
inline State astrea::astro::State::convert_to_set () const
```





**Template parameters:**


* `T` The type to convert the state to. 



**Returns:**

[**State**](classastrea_1_1astro_1_1State.md) A new [**State**](classastrea_1_1astro_1_1State.md) object with the converted orbital elements. 





        

<hr>



### function get\_attitude 

_Get the attitude of the state._ 
```C++
inline const std::optional< Attitude > & astrea::astro::State::get_attitude () const
```





**Returns:**

std::optional&lt;Attitude&gt; The attitude of the state. 





        

<hr>



### function get\_elements 

_Gets the orbital elements of the state._ 
```C++
inline const OrbitalElements & astrea::astro::State::get_elements () const
```





**Returns:**

const [**OrbitalElements**](classastrea_1_1astro_1_1OrbitalElements.md)& Reference to the orbital elements of the state. 





        

<hr>



### function get\_epoch 

_Gets the epoch of the state._ 
```C++
inline const Date & astrea::astro::State::get_epoch () const
```





**Returns:**

const [**Date**](classastrea_1_1astro_1_1Date.md)& Reference to the epoch of the state. 





        

<hr>



### function get\_mu 

_Gets the gravitational parameter (mu) derived from the origin of the current elements' frame._ 
```C++
inline GravParam astrea::astro::State::get_mu () const
```





**Returns:**

GravParam The gravitational parameter of the central body. 





        

<hr>



### function get\_position 

_Gets the position vector from the state._ 
```C++
inline RadiusVector < frames::primary > astrea::astro::State::get_position () const
```





**Returns:**

RadiusVector&lt;frames::primary&gt; The position vector of the state. 





        

<hr>



### function get\_position\_in\_frame 

_Gets the position vector in a specified frame from the state._ 
```C++
template<IsFrame auto _frame_>
inline RadiusVector < _frame_ > astrea::astro::State::get_position_in_frame () const
```





**Template parameters:**


* `_frame_` The frame to get the position vector in. 



**Returns:**

RadiusVector&lt;_frame_&gt; The position vector of the state in the specified frame. 





        

<hr>



### function get\_velocity 

_Gets the velocity vector from the state._ 
```C++
inline VelocityVector < frames::primary > astrea::astro::State::get_velocity () const
```





**Returns:**

VelocityVector&lt;frames::primary&gt; The velocity vector of the state. 





        

<hr>



### function get\_velocity\_in\_frame 

_Gets the velocity vector in a specified frame from the state._ 
```C++
template<IsFrame auto _frame_>
inline VelocityVector < _frame_ > astrea::astro::State::get_velocity_in_frame (
    const Date & date
) const
```





**Template parameters:**


* `_frame_` The frame to get the velocity vector in. 



**Returns:**

VelocityVector&lt;_frame_&gt; The velocity vector of the state in the specified frame. 





        

<hr>



### function in\_element\_set 

_Converts the current orbital elements to a specified type._ 
```C++
template<IsOrbitalElements T>
inline T astrea::astro::State::in_element_set () const
```





**Parameters:**


* `sys` The astrodynamics system to use for the conversion. 



**Returns:**

The converted orbital elements. 





        

<hr>



### function operator== 

_Checks if two_ [_**State**_](classastrea_1_1astro_1_1State.md) _objects are equal._
```C++
bool astrea::astro::State::operator== (
    const State & other
) const
```





**Parameters:**


* `other` The other [**State**](classastrea_1_1astro_1_1State.md) object to compare with. 



**Returns:**

true if the two states are equal (same elements and epoch), 




**Returns:**

false otherwise. 





        

<hr>



### function set\_attitude 

_Sets the attitude of the state._ 
```C++
inline void astrea::astro::State::set_attitude (
    const Attitude & attitude
) 
```





**Parameters:**


* `attitude` The new attitude to set. 




        

<hr>



### function set\_elements 

_Sets the orbital elements of the state._ 
```C++
template<IsOrbitalElements T>
inline void astrea::astro::State::set_elements (
    const T & elements,
    const bool convertToOriginal=false
) 
```





**Parameters:**


* `elements` The new orbital elements to set. 




        

<hr>



### function set\_epoch 

_Sets the epoch of the state._ 
```C++
inline void astrea::astro::State::set_epoch (
    const Date & epoch
) 
```





**Parameters:**


* `epoch` The new epoch to set. 




        

<hr>

------------------------------
The documentation for this class was generated from the following file `astrea/astro/astro/state/State.hpp`

