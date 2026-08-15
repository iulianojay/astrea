

# Struct astrea::astro::detail::EventInner

**template &lt;typename T&gt;**



[**ClassList**](annotated.md) **>** [**astrea**](namespaceastrea.md) **>** [**astro**](namespaceastrea_1_1astro.md) **>** [**detail**](namespaceastrea_1_1astro_1_1detail.md) **>** [**EventInner**](structastrea_1_1astro_1_1detail_1_1EventInner.md)



_A template class for_ [_**Event**_](classastrea_1_1astro_1_1Event.md) _inner implementations._[More...](#detailed-description)

* `#include <Event.hpp>`



Inherits the following classes: [astrea::astro::detail::EventInnerBase](structastrea_1_1astro_1_1detail_1_1EventInnerBase.md)






















## Public Attributes

| Type | Name |
| ---: | :--- |
|  T | [**\_value**](#variable-_value)  <br>_The value of the_ [_**Event**_](classastrea_1_1astro_1_1Event.md) _inner implementation, which is the user-defined_[_**Event**_](classastrea_1_1astro_1_1Event.md) _type._ |
































## Public Functions

| Type | Name |
| ---: | :--- |
|   | [**EventInner**](#function-eventinner-15) () = default<br>_Default constructor for_ [_**EventInner**_](structastrea_1_1astro_1_1detail_1_1EventInner.md) _._ |
|   | [**EventInner**](#function-eventinner-25) (const [**EventInner**](structastrea_1_1astro_1_1detail_1_1EventInner.md) &) = delete<br>_Deleted copy assignment operator._  |
|   | [**EventInner**](#function-eventinner-35) ([**EventInner**](structastrea_1_1astro_1_1detail_1_1EventInner.md) &&) = delete<br>_Deleted move assignment operator._  |
|   | [**EventInner**](#function-eventinner-45) (const T & x) <br>_Constructs a_ [_**EventInner**_](structastrea_1_1astro_1_1detail_1_1EventInner.md) _with a given value._ |
|   | [**EventInner**](#function-eventinner-55) (T && x) <br>_Constructs a_ [_**EventInner**_](structastrea_1_1astro_1_1detail_1_1EventInner.md) _with a given value._ |
| virtual std::unique\_ptr&lt; [**EventInnerBase**](structastrea_1_1astro_1_1detail_1_1EventInnerBase.md) &gt; | [**clone**](#function-clone) () const<br>_Clones the_ [_**Event**_](classastrea_1_1astro_1_1Event.md) _inner implementation._ |
| virtual std::string | [**get\_name**](#function-get_name) () override const<br>_Gets the name of the_ [_**Event**_](classastrea_1_1astro_1_1Event.md) _._ |
| virtual const void \* | [**get\_ptr**](#function-get_ptr-12) () const<br>_Gets a pointer to the internal_ [_**Event**_](classastrea_1_1astro_1_1Event.md) _instance._ |
| virtual void \* | [**get\_ptr**](#function-get_ptr-22) () <br>_Gets a pointer to the internal_ [_**Event**_](classastrea_1_1astro_1_1Event.md) _instance._ |
| virtual bool | [**is\_terminal**](#function-is_terminal) () override const<br>_Checks if the_ [_**Event**_](classastrea_1_1astro_1_1Event.md) _is a terminal_[_**Event**_](classastrea_1_1astro_1_1Event.md) _._ |
| virtual Unitless | [**measure\_event**](#function-measure_event) (const Time & time, const [**State**](classastrea_1_1astro_1_1State.md) & state, const [**Vehicle**](classastrea_1_1astro_1_1Vehicle.md) & vehicle) override const<br>_Detects if the_ [_**Event**_](classastrea_1_1astro_1_1Event.md) _is triggered by a_[_**Vehicle**_](classastrea_1_1astro_1_1Vehicle.md) _._ |
|  [**EventInner**](structastrea_1_1astro_1_1detail_1_1EventInner.md) & | [**operator=**](#function-operator) (const [**EventInner**](structastrea_1_1astro_1_1detail_1_1EventInner.md) &) = delete<br>_Deleted copy assignment operator._  |
|  [**EventInner**](structastrea_1_1astro_1_1detail_1_1EventInner.md) & | [**operator=**](#function-operator_1) ([**EventInner**](structastrea_1_1astro_1_1detail_1_1EventInner.md) &&) = delete<br>_Deleted move assignment operator._  |
| virtual void | [**trigger\_action**](#function-trigger_action) (const Time & time, [**State**](classastrea_1_1astro_1_1State.md) & state, [**Vehicle**](classastrea_1_1astro_1_1Vehicle.md) & vehicle) override const<br>_Triggers the_ [_**Event**_](classastrea_1_1astro_1_1Event.md) _for a_[_**Vehicle**_](classastrea_1_1astro_1_1Vehicle.md) _._ |
|  void | [**trigger\_action\_impl**](#function-trigger_action_impl-12) (const U & value, const Time & time, [**State**](classastrea_1_1astro_1_1State.md) & state, [**Vehicle**](classastrea_1_1astro_1_1Vehicle.md) & vehicle) const<br>_Implementation of the trigger\_action function for an_ [_**Event**_](classastrea_1_1astro_1_1Event.md) _with a trigger._ |
|  void | [**trigger\_action\_impl**](#function-trigger_action_impl-22) (const U & value, const Time & time, [**State**](classastrea_1_1astro_1_1State.md) & state, [**Vehicle**](classastrea_1_1astro_1_1Vehicle.md) & vehicle) const<br>_Implementation of the trigger\_action function for an_ [_**Event**_](classastrea_1_1astro_1_1Event.md) _without a trigger. Does nothing._ |
| virtual const std::type\_info & | [**type**](#function-type) () const<br>_Gets the type information of the internal vehicle instance._  |


## Public Functions inherited from astrea::astro::detail::EventInnerBase

See [astrea::astro::detail::EventInnerBase](structastrea_1_1astro_1_1detail_1_1EventInnerBase.md)

| Type | Name |
| ---: | :--- |
| virtual std::unique\_ptr&lt; [**EventInnerBase**](structastrea_1_1astro_1_1detail_1_1EventInnerBase.md) &gt; | [**clone**](structastrea_1_1astro_1_1detail_1_1EventInnerBase.md#function-clone) () const = 0<br>_Clones the_ [_**Event**_](classastrea_1_1astro_1_1Event.md) _inner implementation._ |
| virtual std::string | [**get\_name**](structastrea_1_1astro_1_1detail_1_1EventInnerBase.md#function-get_name) () const = 0<br>_Gets the name of the_ [_**Event**_](classastrea_1_1astro_1_1Event.md) _._ |
| virtual const void \* | [**get\_ptr**](structastrea_1_1astro_1_1detail_1_1EventInnerBase.md#function-get_ptr-12) () const = 0<br>_Gets a pointer to the internal_ [_**Event**_](classastrea_1_1astro_1_1Event.md) _instance._ |
| virtual void \* | [**get\_ptr**](structastrea_1_1astro_1_1detail_1_1EventInnerBase.md#function-get_ptr-22) () = 0<br>_Gets a pointer to the internal_ [_**Event**_](classastrea_1_1astro_1_1Event.md) _instance._ |
| virtual bool | [**is\_terminal**](structastrea_1_1astro_1_1detail_1_1EventInnerBase.md#function-is_terminal) () const = 0<br>_Checks if the_ [_**Event**_](classastrea_1_1astro_1_1Event.md) _is a terminal_[_**Event**_](classastrea_1_1astro_1_1Event.md) _._ |
| virtual Unitless | [**measure\_event**](structastrea_1_1astro_1_1detail_1_1EventInnerBase.md#function-measure_event) (const Time & time, const [**State**](classastrea_1_1astro_1_1State.md) & state, const [**Vehicle**](classastrea_1_1astro_1_1Vehicle.md) & vehicle) const = 0<br>_Detects if the_ [_**Event**_](classastrea_1_1astro_1_1Event.md) _is triggered by a_[_**Vehicle**_](classastrea_1_1astro_1_1Vehicle.md) _._ |
| virtual void | [**trigger\_action**](structastrea_1_1astro_1_1detail_1_1EventInnerBase.md#function-trigger_action) (const Time & time, [**State**](classastrea_1_1astro_1_1State.md) & state, [**Vehicle**](classastrea_1_1astro_1_1Vehicle.md) & vehicle) const = 0<br>_Triggers the_ [_**Event**_](classastrea_1_1astro_1_1Event.md) _for a_[_**Vehicle**_](classastrea_1_1astro_1_1Vehicle.md) _._ |
| virtual const std::type\_info & | [**type**](structastrea_1_1astro_1_1detail_1_1EventInnerBase.md#function-type) () const = 0<br>_Gets the type information of the internal vehicle instance._  |
| virtual  | [**~EventInnerBase**](structastrea_1_1astro_1_1detail_1_1EventInnerBase.md#function-eventinnerbase) () <br>_Destructor for_ [_**EventInnerBase**_](structastrea_1_1astro_1_1detail_1_1EventInnerBase.md) _._ |






















































## Detailed Description




**Template parameters:**


* `T` The type of the [**Event**](classastrea_1_1astro_1_1Event.md) implementation. 




    
## Public Attributes Documentation




### variable \_value 

_The value of the_ [_**Event**_](classastrea_1_1astro_1_1Event.md) _inner implementation, which is the user-defined_[_**Event**_](classastrea_1_1astro_1_1Event.md) _type._
```C++
T astrea::astro::detail::EventInner< T >::_value;
```




<hr>
## Public Functions Documentation




### function EventInner [1/5]

_Default constructor for_ [_**EventInner**_](structastrea_1_1astro_1_1detail_1_1EventInner.md) _._
```C++
astrea::astro::detail::EventInner::EventInner () = default
```




<hr>



### function EventInner [2/5]

_Deleted copy assignment operator._ 
```C++
astrea::astro::detail::EventInner::EventInner (
    const EventInner &
) = delete
```




<hr>



### function EventInner [3/5]

_Deleted move assignment operator._ 
```C++
astrea::astro::detail::EventInner::EventInner (
    EventInner &&
) = delete
```




<hr>



### function EventInner [4/5]

_Constructs a_ [_**EventInner**_](structastrea_1_1astro_1_1detail_1_1EventInner.md) _with a given value._
```C++
inline explicit astrea::astro::detail::EventInner::EventInner (
    const T & x
) 
```





**Parameters:**


* `x` The value to initialize the [**Event**](classastrea_1_1astro_1_1Event.md) inner implementation. 




        

<hr>



### function EventInner [5/5]

_Constructs a_ [_**EventInner**_](structastrea_1_1astro_1_1detail_1_1EventInner.md) _with a given value._
```C++
inline explicit astrea::astro::detail::EventInner::EventInner (
    T && x
) 
```





**Parameters:**


* `x` The value to initialize the [**Event**](classastrea_1_1astro_1_1Event.md) inner implementation. 




        

<hr>



### function clone 

_Clones the_ [_**Event**_](classastrea_1_1astro_1_1Event.md) _inner implementation._
```C++
inline virtual std::unique_ptr< EventInnerBase > astrea::astro::detail::EventInner::clone () const
```





**Returns:**

std::unique\_ptr&lt;EventInnerBase&gt; A unique pointer to the cloned [**Event**](classastrea_1_1astro_1_1Event.md) inner implementation. 





        
Implements [*astrea::astro::detail::EventInnerBase::clone*](structastrea_1_1astro_1_1detail_1_1EventInnerBase.md#function-clone)


<hr>



### function get\_name 

_Gets the name of the_ [_**Event**_](classastrea_1_1astro_1_1Event.md) _._
```C++
inline virtual std::string astrea::astro::detail::EventInner::get_name () override const
```





**Returns:**

std::string The name of the [**Event**](classastrea_1_1astro_1_1Event.md). 





        
Implements [*astrea::astro::detail::EventInnerBase::get\_name*](structastrea_1_1astro_1_1detail_1_1EventInnerBase.md#function-get_name)


<hr>



### function get\_ptr [1/2]

_Gets a pointer to the internal_ [_**Event**_](classastrea_1_1astro_1_1Event.md) _instance._
```C++
inline virtual const void * astrea::astro::detail::EventInner::get_ptr () const
```





**Returns:**

const void\* A pointer to the internal [**Event**](classastrea_1_1astro_1_1Event.md) instance. 





        
Implements [*astrea::astro::detail::EventInnerBase::get\_ptr*](structastrea_1_1astro_1_1detail_1_1EventInnerBase.md#function-get_ptr-12)


<hr>



### function get\_ptr [2/2]

_Gets a pointer to the internal_ [_**Event**_](classastrea_1_1astro_1_1Event.md) _instance._
```C++
inline virtual void * astrea::astro::detail::EventInner::get_ptr () 
```





**Returns:**

void\* A pointer to the internal [**Event**](classastrea_1_1astro_1_1Event.md) instance. 





        
Implements [*astrea::astro::detail::EventInnerBase::get\_ptr*](structastrea_1_1astro_1_1detail_1_1EventInnerBase.md#function-get_ptr-22)


<hr>



### function is\_terminal 

_Checks if the_ [_**Event**_](classastrea_1_1astro_1_1Event.md) _is a terminal_[_**Event**_](classastrea_1_1astro_1_1Event.md) _._
```C++
inline virtual bool astrea::astro::detail::EventInner::is_terminal () override const
```





**Returns:**

true If the [**Event**](classastrea_1_1astro_1_1Event.md) is a terminal [**Event**](classastrea_1_1astro_1_1Event.md). 




**Returns:**

false If the [**Event**](classastrea_1_1astro_1_1Event.md) is not a terminal [**Event**](classastrea_1_1astro_1_1Event.md). 





        
Implements [*astrea::astro::detail::EventInnerBase::is\_terminal*](structastrea_1_1astro_1_1detail_1_1EventInnerBase.md#function-is_terminal)


<hr>



### function measure\_event 

_Detects if the_ [_**Event**_](classastrea_1_1astro_1_1Event.md) _is triggered by a_[_**Vehicle**_](classastrea_1_1astro_1_1Vehicle.md) _._
```C++
inline virtual Unitless astrea::astro::detail::EventInner::measure_event (
    const Time & time,
    const State & state,
    const Vehicle & vehicle
) override const
```





**Parameters:**


* `time` The current time in the integration. 
* `state` The current state of the vehicle. 
* `vehicle` The [**Vehicle**](classastrea_1_1astro_1_1Vehicle.md) to check. 



**Returns:**

true If the [**Event**](classastrea_1_1astro_1_1Event.md) is triggered by the [**Vehicle**](classastrea_1_1astro_1_1Vehicle.md). 




**Returns:**

false If the [**Event**](classastrea_1_1astro_1_1Event.md) is not triggered by the [**Vehicle**](classastrea_1_1astro_1_1Vehicle.md). 





        
Implements [*astrea::astro::detail::EventInnerBase::measure\_event*](structastrea_1_1astro_1_1detail_1_1EventInnerBase.md#function-measure_event)


<hr>



### function operator= 

_Deleted copy assignment operator._ 
```C++
EventInner & astrea::astro::detail::EventInner::operator= (
    const EventInner &
) = delete
```




<hr>



### function operator= 

_Deleted move assignment operator._ 
```C++
EventInner & astrea::astro::detail::EventInner::operator= (
    EventInner &&
) = delete
```




<hr>



### function trigger\_action 

_Triggers the_ [_**Event**_](classastrea_1_1astro_1_1Event.md) _for a_[_**Vehicle**_](classastrea_1_1astro_1_1Vehicle.md) _._
```C++
inline virtual void astrea::astro::detail::EventInner::trigger_action (
    const Time & time,
    State & state,
    Vehicle & vehicle
) override const
```





**Parameters:**


* `time` The current time in the integration. 
* `state` The current state of the vehicle. 
* `vehicle` The [**Vehicle**](classastrea_1_1astro_1_1Vehicle.md) to trigger the [**Event**](classastrea_1_1astro_1_1Event.md) for. 



**Returns:**

[**Vehicle**](classastrea_1_1astro_1_1Vehicle.md) The [**Vehicle**](classastrea_1_1astro_1_1Vehicle.md) after the [**Event**](classastrea_1_1astro_1_1Event.md) has been triggered. 





        
Implements [*astrea::astro::detail::EventInnerBase::trigger\_action*](structastrea_1_1astro_1_1detail_1_1EventInnerBase.md#function-trigger_action)


<hr>



### function trigger\_action\_impl [1/2]

_Implementation of the trigger\_action function for an_ [_**Event**_](classastrea_1_1astro_1_1Event.md) _with a trigger._
```C++
template<typename U>
inline void astrea::astro::detail::EventInner::trigger_action_impl (
    const U & value,
    const Time & time,
    State & state,
    Vehicle & vehicle
) const
```





**Template parameters:**


* `U` The type of the [**Event**](classastrea_1_1astro_1_1Event.md) implementation. 



**Parameters:**


* `value` The [**Event**](classastrea_1_1astro_1_1Event.md) implementation instance. 
* `time` The current time in the integration. 
* `state` The current state of the vehicle. 
* `vehicle` The [**Vehicle**](classastrea_1_1astro_1_1Vehicle.md) to trigger the [**Event**](classastrea_1_1astro_1_1Event.md) for. 



**Returns:**

[**Vehicle**](classastrea_1_1astro_1_1Vehicle.md) The [**Vehicle**](classastrea_1_1astro_1_1Vehicle.md) after the [**Event**](classastrea_1_1astro_1_1Event.md) has been triggered. 





        

<hr>



### function trigger\_action\_impl [2/2]

_Implementation of the trigger\_action function for an_ [_**Event**_](classastrea_1_1astro_1_1Event.md) _without a trigger. Does nothing._
```C++
template<typename U>
inline void astrea::astro::detail::EventInner::trigger_action_impl (
    const U & value,
    const Time & time,
    State & state,
    Vehicle & vehicle
) const
```





**Template parameters:**


* `U` The type of the [**Event**](classastrea_1_1astro_1_1Event.md) implementation. 



**Parameters:**


* `value` The [**Event**](classastrea_1_1astro_1_1Event.md) implementation instance. 
* `time` The current time in the integration. 
* `state` The current state of the vehicle. 
* `vehicle` The [**Vehicle**](classastrea_1_1astro_1_1Vehicle.md) to trigger the [**Event**](classastrea_1_1astro_1_1Event.md) for. 



**Returns:**

[**Vehicle**](classastrea_1_1astro_1_1Vehicle.md) The [**Vehicle**](classastrea_1_1astro_1_1Vehicle.md) after the [**Event**](classastrea_1_1astro_1_1Event.md) has been triggered. 





        

<hr>



### function type 

_Gets the type information of the internal vehicle instance._ 
```C++
inline virtual const std::type_info & astrea::astro::detail::EventInner::type () const
```





**Returns:**

const std::type\_info& The type information of the internal vehicle instance. 





        
Implements [*astrea::astro::detail::EventInnerBase::type*](structastrea_1_1astro_1_1detail_1_1EventInnerBase.md#function-type)


<hr>

------------------------------
The documentation for this class was generated from the following file `astrea/astro/astro/propagation/event_detection/Event.hpp`

