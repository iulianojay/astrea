

# Struct astrea::astro::detail::EventInnerBase



[**ClassList**](annotated.md) **>** [**astrea**](namespaceastrea.md) **>** [**astro**](namespaceastrea_1_1astro.md) **>** [**detail**](namespaceastrea_1_1astro_1_1detail.md) **>** [**EventInnerBase**](structastrea_1_1astro_1_1detail_1_1EventInnerBase.md)



_Pure virtual base class for_ [_**Event**_](classastrea_1_1astro_1_1Event.md) _inner implementations._

* `#include <Event.hpp>`





Inherited by the following classes: [astrea::astro::detail::EventInner](structastrea_1_1astro_1_1detail_1_1EventInner.md)
































## Public Functions

| Type | Name |
| ---: | :--- |
| virtual std::unique\_ptr&lt; [**EventInnerBase**](structastrea_1_1astro_1_1detail_1_1EventInnerBase.md) &gt; | [**clone**](#function-clone) () const = 0<br>_Clones the_ [_**Event**_](classastrea_1_1astro_1_1Event.md) _inner implementation._ |
| virtual std::string | [**get\_name**](#function-get_name) () const = 0<br>_Gets the name of the_ [_**Event**_](classastrea_1_1astro_1_1Event.md) _._ |
| virtual [**const**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) [**void**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) \* | [**get\_ptr**](#function-get_ptr-12) () const = 0<br>_Gets a pointer to the internal_ [_**Event**_](classastrea_1_1astro_1_1Event.md) _instance._ |
| virtual [**void**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) \* | [**get\_ptr**](#function-get_ptr-22) () = 0<br>_Gets a pointer to the internal_ [_**Event**_](classastrea_1_1astro_1_1Event.md) _instance._ |
| virtual [**bool**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) | [**is\_terminal**](#function-is_terminal) () const = 0<br>_Checks if the_ [_**Event**_](classastrea_1_1astro_1_1Event.md) _is a terminal_[_**Event**_](classastrea_1_1astro_1_1Event.md) _._ |
| virtual [**Unitless**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) | [**measure\_event**](#function-measure_event) ([**const**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) [**Time**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) & time, [**const**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) [**State**](classastrea_1_1astro_1_1State.md) & state, [**const**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) [**Vehicle**](classastrea_1_1astro_1_1Vehicle.md) & vehicle) const = 0<br>_Detects if the_ [_**Event**_](classastrea_1_1astro_1_1Event.md) _is triggered by a_[_**Vehicle**_](classastrea_1_1astro_1_1Vehicle.md) _._ |
| virtual [**void**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) | [**trigger\_action**](#function-trigger_action) ([**const**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) [**Time**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) & time, [**State**](classastrea_1_1astro_1_1State.md) & state, [**Vehicle**](classastrea_1_1astro_1_1Vehicle.md) & vehicle) const = 0<br>_Triggers the_ [_**Event**_](classastrea_1_1astro_1_1Event.md) _for a_[_**Vehicle**_](classastrea_1_1astro_1_1Vehicle.md) _._ |
| virtual [**const**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) std::type\_info & | [**type**](#function-type) () const = 0<br>_Gets the type information of the internal vehicle instance._  |
| virtual  | [**~EventInnerBase**](#function-eventinnerbase) () <br>_Destructor for_ [_**EventInnerBase**_](structastrea_1_1astro_1_1detail_1_1EventInnerBase.md) _._ |




























## Public Functions Documentation




### function clone 

_Clones the_ [_**Event**_](classastrea_1_1astro_1_1Event.md) _inner implementation._
```C++
virtual std::unique_ptr< EventInnerBase > astrea::astro::detail::EventInnerBase::clone () const = 0
```





**Returns:**

std::unique\_ptr&lt;EventInnerBase&gt; A unique pointer to the cloned [**Event**](classastrea_1_1astro_1_1Event.md) inner implementation. 





        

<hr>



### function get\_name 

_Gets the name of the_ [_**Event**_](classastrea_1_1astro_1_1Event.md) _._
```C++
virtual std::string astrea::astro::detail::EventInnerBase::get_name () const = 0
```





**Returns:**

std::string The name of the [**Event**](classastrea_1_1astro_1_1Event.md). 





        

<hr>



### function get\_ptr [1/2]

_Gets a pointer to the internal_ [_**Event**_](classastrea_1_1astro_1_1Event.md) _instance._
```C++
virtual const  void * astrea::astro::detail::EventInnerBase::get_ptr () const = 0
```





**Returns:**

const void\* A pointer to the internal [**Event**](classastrea_1_1astro_1_1Event.md) instance. 





        

<hr>



### function get\_ptr [2/2]

_Gets a pointer to the internal_ [_**Event**_](classastrea_1_1astro_1_1Event.md) _instance._
```C++
virtual void * astrea::astro::detail::EventInnerBase::get_ptr () = 0
```





**Returns:**

void\* A pointer to the internal [**Event**](classastrea_1_1astro_1_1Event.md) instance. 





        

<hr>



### function is\_terminal 

_Checks if the_ [_**Event**_](classastrea_1_1astro_1_1Event.md) _is a terminal_[_**Event**_](classastrea_1_1astro_1_1Event.md) _._
```C++
virtual bool astrea::astro::detail::EventInnerBase::is_terminal () const = 0
```





**Returns:**

true If the [**Event**](classastrea_1_1astro_1_1Event.md) is a terminal [**Event**](classastrea_1_1astro_1_1Event.md). 




**Returns:**

false If the [**Event**](classastrea_1_1astro_1_1Event.md) is not a terminal [**Event**](classastrea_1_1astro_1_1Event.md). 





        

<hr>



### function measure\_event 

_Detects if the_ [_**Event**_](classastrea_1_1astro_1_1Event.md) _is triggered by a_[_**Vehicle**_](classastrea_1_1astro_1_1Vehicle.md) _._
```C++
virtual Unitless astrea::astro::detail::EventInnerBase::measure_event (
    const  Time & time,
    const  State & state,
    const  Vehicle & vehicle
) const = 0
```





**Parameters:**


* `time` The current time in the integration. 
* `state` The current state of the vehicle. 
* `vehicle` The [**Vehicle**](classastrea_1_1astro_1_1Vehicle.md) to check. 



**Returns:**

true If the [**Event**](classastrea_1_1astro_1_1Event.md) is triggered by the [**Vehicle**](classastrea_1_1astro_1_1Vehicle.md). 




**Returns:**

false If the [**Event**](classastrea_1_1astro_1_1Event.md) is not triggered by the [**Vehicle**](classastrea_1_1astro_1_1Vehicle.md). 





        

<hr>



### function trigger\_action 

_Triggers the_ [_**Event**_](classastrea_1_1astro_1_1Event.md) _for a_[_**Vehicle**_](classastrea_1_1astro_1_1Vehicle.md) _._
```C++
virtual void astrea::astro::detail::EventInnerBase::trigger_action (
    const  Time & time,
    State & state,
    Vehicle & vehicle
) const = 0
```





**Parameters:**


* `time` The current time in the integration. 
* `state` The current state of the vehicle. 
* `vehicle` The [**Vehicle**](classastrea_1_1astro_1_1Vehicle.md) to trigger the [**Event**](classastrea_1_1astro_1_1Event.md) for. 



**Returns:**

[**Vehicle**](classastrea_1_1astro_1_1Vehicle.md) The [**Vehicle**](classastrea_1_1astro_1_1Vehicle.md) after the [**Event**](classastrea_1_1astro_1_1Event.md) has been triggered. 





        

<hr>



### function type 

_Gets the type information of the internal vehicle instance._ 
```C++
virtual const std::type_info & astrea::astro::detail::EventInnerBase::type () const = 0
```





**Returns:**

const std::type\_info& The type information of the internal vehicle instance. 





        

<hr>



### function ~EventInnerBase 

_Destructor for_ [_**EventInnerBase**_](structastrea_1_1astro_1_1detail_1_1EventInnerBase.md) _._
```C++
inline virtual astrea::astro::detail::EventInnerBase::~EventInnerBase () 
```




<hr>

------------------------------
The documentation for this class was generated from the following file `astrea/astro/astro/propagation/event_detection/Event.hpp`

