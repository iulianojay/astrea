

# Class astrea::astro::Event



[**ClassList**](annotated.md) **>** [**astrea**](namespaceastrea.md) **>** [**astro**](namespaceastrea_1_1astro.md) **>** [**Event**](classastrea_1_1astro_1_1Event.md)



_A class representing a_ [_**Event**_](classastrea_1_1astro_1_1Event.md) _in the astrea astro platform. This class serves as a base for user-defined Events and provides a common interface._

* `#include <Event.hpp>`





































## Public Functions

| Type | Name |
| ---: | :--- |
|   | [**Event**](#function-event-13) () <br>_Default constructor for_ [_**Event**_](classastrea_1_1astro_1_1Event.md) _._ |
|   | [**Event**](#function-event-23) (const [**Event**](classastrea_1_1astro_1_1Event.md) & other) <br>_Copy constructor for_ [_**Event**_](classastrea_1_1astro_1_1Event.md) _._ |
|   | [**Event**](#function-event-33) ([**Event**](classastrea_1_1astro_1_1Event.md) && other) noexcept<br>_Move constructor for_ [_**Event**_](classastrea_1_1astro_1_1Event.md) _._ |
|  void \* | [**get\_ptr**](#function-get_ptr) () <br>_Gets a pointer to the internal_ [_**Event**_](classastrea_1_1astro_1_1Event.md) _instance._ |
|  [**Event**](classastrea_1_1astro_1_1Event.md) & | [**operator=**](#function-operator) ([**Event**](classastrea_1_1astro_1_1Event.md) && other) noexcept<br>_Copy assignment operator for_ [_**Event**_](classastrea_1_1astro_1_1Event.md) _._ |
|  [**Event**](classastrea_1_1astro_1_1Event.md) & | [**operator=**](#function-operator_1) (const [**Event**](classastrea_1_1astro_1_1Event.md) & other) <br>_Move assignment operator for_ [_**Event**_](classastrea_1_1astro_1_1Event.md) _._ |
|   | [**requires**](#function-requires-12) (IsGenericallyConstructableEvent&lt; T &gt;) <br>_Constructs a_ [_**Event**_](classastrea_1_1astro_1_1Event.md) _with a user-defined type._ |
|   | [**requires**](#function-requires-22) (IsGenericallyConstructableEvent&lt; T &gt;) <br>_Generic assignment operator for_ [_**Event**_](classastrea_1_1astro_1_1Event.md) _._ |




























## Public Functions Documentation




### function Event [1/3]

_Default constructor for_ [_**Event**_](classastrea_1_1astro_1_1Event.md) _._
```C++
astrea::astro::Event::Event () 
```




<hr>



### function Event [2/3]

_Copy constructor for_ [_**Event**_](classastrea_1_1astro_1_1Event.md) _._
```C++
astrea::astro::Event::Event (
    const Event & other
) 
```





**Parameters:**


* `other` The [**Event**](classastrea_1_1astro_1_1Event.md) instance to copy from. 




        

<hr>



### function Event [3/3]

_Move constructor for_ [_**Event**_](classastrea_1_1astro_1_1Event.md) _._
```C++
astrea::astro::Event::Event (
    Event && other
) noexcept
```





**Parameters:**


* `other` The [**Event**](classastrea_1_1astro_1_1Event.md) instance to move from. 




        

<hr>



### function get\_ptr 

_Gets a pointer to the internal_ [_**Event**_](classastrea_1_1astro_1_1Event.md) _instance._
```C++
void * astrea::astro::Event::get_ptr () 
```





**Returns:**

void\* A pointer to the internal [**Event**](classastrea_1_1astro_1_1Event.md) instance. 





        

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
    const Event & other
) 
```





**Parameters:**


* `other` The [**Event**](classastrea_1_1astro_1_1Event.md) instance to move from. 



**Returns:**

[**Event**](classastrea_1_1astro_1_1Event.md)& A reference to the current [**Event**](classastrea_1_1astro_1_1Event.md) instance. 





        

<hr>



### function requires [1/2]

_Constructs a_ [_**Event**_](classastrea_1_1astro_1_1Event.md) _with a user-defined type._
```C++
template<typename T>
inline astrea::astro::Event::requires (
    IsGenericallyConstructableEvent< T >
) 
```





**Template parameters:**


* `T` The type of the user-defined [**Event**](classastrea_1_1astro_1_1Event.md). 



**Parameters:**


* `x` The user-defined [**Event**](classastrea_1_1astro_1_1Event.md) instance to initialize the [**Event**](classastrea_1_1astro_1_1Event.md). 




        

<hr>



### function requires [2/2]

_Generic assignment operator for_ [_**Event**_](classastrea_1_1astro_1_1Event.md) _._
```C++
template<typename T>
astrea::astro::Event::requires (
    IsGenericallyConstructableEvent< T >
) 
```





**Template parameters:**


* `T` The type of the user-defined [**Event**](classastrea_1_1astro_1_1Event.md). 



**Parameters:**


* `x` The user-defined [**Event**](classastrea_1_1astro_1_1Event.md) instance to assign to the [**Event**](classastrea_1_1astro_1_1Event.md). 



**Returns:**

[**Event**](classastrea_1_1astro_1_1Event.md)& A reference to the current [**Event**](classastrea_1_1astro_1_1Event.md) instance. 





        

<hr>

------------------------------
The documentation for this class was generated from the following file `astrea/astro/astro/propagation/event_detection/Event.hpp`

