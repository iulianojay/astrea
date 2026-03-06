

# Class astrea::astro::Event



[**ClassList**](annotated.md) **>** [**astrea**](namespaceastrea.md) **>** [**astro**](namespaceastrea_1_1astro.md) **>** [**Event**](classastrea_1_1astro_1_1Event.md)



_A class representing a_ [_**Event**_](classastrea_1_1astro_1_1Event.md) _in the astrea astro platform. This class serves as a base for user-defined Events and provides a common interface._

* `#include <Event.hpp>`





































## Public Functions

| Type | Name |
| ---: | :--- |
|   | [**Event**](#function-event-14) () <br>_Default constructor for_ [_**Event**_](classastrea_1_1astro_1_1Event.md) _._ |
|   | [**Event**](#function-event-24) ([**T**](classastrea_1_1astro_1_1CartesianVector.md) && x) <br>_Constructs a_ [_**Event**_](classastrea_1_1astro_1_1Event.md) _with a user-defined type._ |
|   | [**Event**](#function-event-34) ([**const**](classastrea_1_1astro_1_1CartesianVector.md) [**Event**](classastrea_1_1astro_1_1Event.md) & other) <br>_Copy constructor for_ [_**Event**_](classastrea_1_1astro_1_1Event.md) _._ |
|   | [**Event**](#function-event-44) ([**Event**](classastrea_1_1astro_1_1Event.md) && other) noexcept<br>_Move constructor for_ [_**Event**_](classastrea_1_1astro_1_1Event.md) _._ |
|  [**const**](classastrea_1_1astro_1_1CartesianVector.md) [**T**](classastrea_1_1astro_1_1CartesianVector.md) \* | [**extract**](#function-extract) () noexcept const<br>_Extracts the user-defined_ [_**Event**_](classastrea_1_1astro_1_1Event.md) _from the_[_**Event**_](classastrea_1_1astro_1_1Event.md) _instance._ |
|  std::string | [**get\_name**](#function-get_name) () const<br>_Gets the name of the_ [_**Event**_](classastrea_1_1astro_1_1Event.md) _._ |
|  [**const**](classastrea_1_1astro_1_1CartesianVector.md) [**void**](classastrea_1_1astro_1_1CartesianVector.md) \* | [**get\_ptr**](#function-get_ptr-12) () const<br>_Gets a pointer to the internal_ [_**Event**_](classastrea_1_1astro_1_1Event.md) _instance._ |
|  [**void**](classastrea_1_1astro_1_1CartesianVector.md) \* | [**get\_ptr**](#function-get_ptr-22) () <br>_Gets a pointer to the internal_ [_**Event**_](classastrea_1_1astro_1_1Event.md) _instance._ |
|  [**bool**](classastrea_1_1astro_1_1CartesianVector.md) | [**is\_terminal**](#function-is_terminal) () const<br>_Checks if the_ [_**Event**_](classastrea_1_1astro_1_1Event.md) _is a terminal_[_**Event**_](classastrea_1_1astro_1_1Event.md) _._ |
|  [**Unitless**](classastrea_1_1astro_1_1CartesianVector.md) | [**measure\_event**](#function-measure_event) ([**const**](classastrea_1_1astro_1_1CartesianVector.md) [**Time**](classastrea_1_1astro_1_1CartesianVector.md) & time, [**const**](classastrea_1_1astro_1_1CartesianVector.md) [**State**](classastrea_1_1astro_1_1State.md) & state, [**const**](classastrea_1_1astro_1_1CartesianVector.md) [**Vehicle**](classastrea_1_1astro_1_1Vehicle.md) & vehicle) const<br>_Detects if the_ [_**Event**_](classastrea_1_1astro_1_1Event.md) _is triggered by a_[_**Vehicle**_](classastrea_1_1astro_1_1Vehicle.md) _._ |
|  [**Event**](classastrea_1_1astro_1_1Event.md) & | [**operator=**](#function-operator) ([**Event**](classastrea_1_1astro_1_1Event.md) && other) noexcept<br>_Copy assignment operator for_ [_**Event**_](classastrea_1_1astro_1_1Event.md) _._ |
|  [**Event**](classastrea_1_1astro_1_1Event.md) & | [**operator=**](#function-operator_1) ([**const**](classastrea_1_1astro_1_1CartesianVector.md) [**Event**](classastrea_1_1astro_1_1Event.md) & other) <br>_Move assignment operator for_ [_**Event**_](classastrea_1_1astro_1_1Event.md) _._ |
|  [**Event**](classastrea_1_1astro_1_1Event.md) & | [**operator=**](#function-operator_2) ([**T**](classastrea_1_1astro_1_1CartesianVector.md) && x) <br>_Generic assignment operator for_ [_**Event**_](classastrea_1_1astro_1_1Event.md) _._ |
|  [**void**](classastrea_1_1astro_1_1CartesianVector.md) | [**trigger\_action**](#function-trigger_action) ([**const**](classastrea_1_1astro_1_1CartesianVector.md) [**Time**](classastrea_1_1astro_1_1CartesianVector.md) & time, [**State**](classastrea_1_1astro_1_1State.md) & state, [**Vehicle**](classastrea_1_1astro_1_1Vehicle.md) & vehicle) const<br>_Triggers the_ [_**Event**_](classastrea_1_1astro_1_1Event.md) _for a_[_**Vehicle**_](classastrea_1_1astro_1_1Vehicle.md) _._ |




























## Public Functions Documentation




### function Event [1/4]

_Default constructor for_ [_**Event**_](classastrea_1_1astro_1_1Event.md) _._
```C++
astrea::astro::Event::Event () 
```




<hr>



### function Event [2/4]

_Constructs a_ [_**Event**_](classastrea_1_1astro_1_1Event.md) _with a user-defined type._
```C++
template<typename  T>
inline explicit astrea::astro::Event::Event (
    T && x
) 
```





**Template parameters:**


* `T` The type of the user-defined [**Event**](classastrea_1_1astro_1_1Event.md). 



**Parameters:**


* `x` The user-defined [**Event**](classastrea_1_1astro_1_1Event.md) instance to initialize the [**Event**](classastrea_1_1astro_1_1Event.md). 




        

<hr>



### function Event [3/4]

_Copy constructor for_ [_**Event**_](classastrea_1_1astro_1_1Event.md) _._
```C++
astrea::astro::Event::Event (
    const  Event & other
) 
```





**Parameters:**


* `other` The [**Event**](classastrea_1_1astro_1_1Event.md) instance to copy from. 




        

<hr>



### function Event [4/4]

_Move constructor for_ [_**Event**_](classastrea_1_1astro_1_1Event.md) _._
```C++
astrea::astro::Event::Event (
    Event && other
) noexcept
```





**Parameters:**


* `other` The [**Event**](classastrea_1_1astro_1_1Event.md) instance to move from. 




        

<hr>



### function extract 

_Extracts the user-defined_ [_**Event**_](classastrea_1_1astro_1_1Event.md) _from the_[_**Event**_](classastrea_1_1astro_1_1Event.md) _instance._
```C++
template<typename  T>
inline const  T * astrea::astro::Event::extract () noexcept const
```





**Template parameters:**


* `T` The type of the user-defined [**Event**](classastrea_1_1astro_1_1Event.md) to extract. 



**Returns:**

const T\* A pointer to the user-defined [**Event**](classastrea_1_1astro_1_1Event.md) if it matches the type, otherwise nullptr. 





        

<hr>



### function get\_name 

_Gets the name of the_ [_**Event**_](classastrea_1_1astro_1_1Event.md) _._
```C++
inline std::string astrea::astro::Event::get_name () const
```





**Returns:**

std::string The name of the [**Event**](classastrea_1_1astro_1_1Event.md). 





        

<hr>



### function get\_ptr [1/2]

_Gets a pointer to the internal_ [_**Event**_](classastrea_1_1astro_1_1Event.md) _instance._
```C++
const  void * astrea::astro::Event::get_ptr () const
```





**Returns:**

const void\* A pointer to the internal [**Event**](classastrea_1_1astro_1_1Event.md) instance. 





        

<hr>



### function get\_ptr [2/2]

_Gets a pointer to the internal_ [_**Event**_](classastrea_1_1astro_1_1Event.md) _instance._
```C++
void * astrea::astro::Event::get_ptr () 
```





**Returns:**

void\* A pointer to the internal [**Event**](classastrea_1_1astro_1_1Event.md) instance. 





        

<hr>



### function is\_terminal 

_Checks if the_ [_**Event**_](classastrea_1_1astro_1_1Event.md) _is a terminal_[_**Event**_](classastrea_1_1astro_1_1Event.md) _._
```C++
inline bool astrea::astro::Event::is_terminal () const
```





**Returns:**

true If the [**Event**](classastrea_1_1astro_1_1Event.md) is a terminal [**Event**](classastrea_1_1astro_1_1Event.md). 




**Returns:**

false If the [**Event**](classastrea_1_1astro_1_1Event.md) is not a terminal [**Event**](classastrea_1_1astro_1_1Event.md). 





        

<hr>



### function measure\_event 

_Detects if the_ [_**Event**_](classastrea_1_1astro_1_1Event.md) _is triggered by a_[_**Vehicle**_](classastrea_1_1astro_1_1Vehicle.md) _._
```C++
inline Unitless astrea::astro::Event::measure_event (
    const  Time & time,
    const  State & state,
    const  Vehicle & vehicle
) const
```





**Parameters:**


* `vehicle` The [**Vehicle**](classastrea_1_1astro_1_1Vehicle.md) to check. 



**Returns:**

true If the [**Event**](classastrea_1_1astro_1_1Event.md) is triggered by the [**Vehicle**](classastrea_1_1astro_1_1Vehicle.md). 




**Returns:**

false If the [**Event**](classastrea_1_1astro_1_1Event.md) is not triggered by the [**Vehicle**](classastrea_1_1astro_1_1Vehicle.md). 





        

<hr>



### function operator= 

_Copy assignment operator for_ [_**Event**_](classastrea_1_1astro_1_1Event.md) _._
```C++
Event & astrea::astro::Event::operator= (
    Event && other
) noexcept
```





**Returns:**

[**Event**](classastrea_1_1astro_1_1Event.md)& A reference to the current [**Event**](classastrea_1_1astro_1_1Event.md) instance. 





        

<hr>



### function operator= 

_Move assignment operator for_ [_**Event**_](classastrea_1_1astro_1_1Event.md) _._
```C++
Event & astrea::astro::Event::operator= (
    const  Event & other
) 
```





**Parameters:**


* `other` The [**Event**](classastrea_1_1astro_1_1Event.md) instance to move from. 



**Returns:**

[**Event**](classastrea_1_1astro_1_1Event.md)& A reference to the current [**Event**](classastrea_1_1astro_1_1Event.md) instance. 





        

<hr>



### function operator= 

_Generic assignment operator for_ [_**Event**_](classastrea_1_1astro_1_1Event.md) _._
```C++
template<typename  T>
inline Event & astrea::astro::Event::operator= (
    T && x
) 
```





**Template parameters:**


* `T` The type of the user-defined [**Event**](classastrea_1_1astro_1_1Event.md). 



**Parameters:**


* `x` The user-defined [**Event**](classastrea_1_1astro_1_1Event.md) instance to assign to the [**Event**](classastrea_1_1astro_1_1Event.md). 



**Returns:**

[**Event**](classastrea_1_1astro_1_1Event.md)& A reference to the current [**Event**](classastrea_1_1astro_1_1Event.md) instance. 





        

<hr>



### function trigger\_action 

_Triggers the_ [_**Event**_](classastrea_1_1astro_1_1Event.md) _for a_[_**Vehicle**_](classastrea_1_1astro_1_1Vehicle.md) _._
```C++
inline void astrea::astro::Event::trigger_action (
    const  Time & time,
    State & state,
    Vehicle & vehicle
) const
```





**Parameters:**


* `time` The current time in the integration. 
* `state` The current state of the vehicle. 
* `vehicle` The [**Vehicle**](classastrea_1_1astro_1_1Vehicle.md) to trigger the [**Event**](classastrea_1_1astro_1_1Event.md) for. 



**Returns:**

[**Vehicle**](classastrea_1_1astro_1_1Vehicle.md) The [**Vehicle**](classastrea_1_1astro_1_1Vehicle.md) after the [**Event**](classastrea_1_1astro_1_1Event.md) has been triggered. 





        

<hr>

------------------------------
The documentation for this class was generated from the following file `astrea/astro/astro/propagation/event_detection/Event.hpp`

