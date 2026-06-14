

# Class astrea::astro::StateHistory



[**ClassList**](annotated.md) **>** [**astrea**](namespaceastrea.md) **>** [**astro**](namespaceastrea_1_1astro.md) **>** [**StateHistory**](classastrea_1_1astro_1_1StateHistory.md)



_Class to manage the history of states for an object over date._ [More...](#detailed-description)

* `#include <StateHistory.hpp>`

















## Public Types

| Type | Name |
| ---: | :--- |
| typedef std::vector&lt; [**State**](classastrea_1_1astro_1_1State.md) &gt;::const\_iterator | [**const\_iterator**](#typedef-const_iterator)  <br>_Constant iterator types for iterating over the states in the history._  |
| typedef std::vector&lt; [**State**](classastrea_1_1astro_1_1State.md) &gt;::iterator | [**iterator**](#typedef-iterator)  <br>_Iterator types for iterating over the states in the history._  |




















## Public Functions

| Type | Name |
| ---: | :--- |
|   | [**StateHistory**](#function-statehistory-12) () = default<br>_Default constructor for_ [_**StateHistory**_](classastrea_1_1astro_1_1StateHistory.md) _._ |
|   | [**StateHistory**](#function-statehistory-22) ([**const**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) std::size\_t & objectId) <br>_Constructor that initializes_ [_**StateHistory**_](classastrea_1_1astro_1_1StateHistory.md) _with a specific object ID._ |
|  [**iterator**](classastrea_1_1astro_1_1StateHistory.md#typedef-iterator) | [**begin**](#function-begin-12) () <br>_Returns an iterator to the beginning of the state history._  |
|  [**const\_iterator**](classastrea_1_1astro_1_1StateHistory.md#typedef-const_iterator) | [**begin**](#function-begin-22) () const<br>_Returns a constant iterator to the beginning of the state history._  |
|  [**const\_iterator**](classastrea_1_1astro_1_1StateHistory.md#typedef-const_iterator) | [**cbegin**](#function-cbegin) () const<br>_Returns a constant iterator to the beginning of the state history._  |
|  [**const\_iterator**](classastrea_1_1astro_1_1StateHistory.md#typedef-const_iterator) | [**cend**](#function-cend) () const<br>_Returns a constant iterator to the end of the state history._  |
|  [**void**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) | [**clear**](#function-clear) () <br>_Clears the state history, removing all stored states._  |
|  [**bool**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) | [**empty**](#function-empty) () const<br>_Checks if the state history is empty._  |
|  [**iterator**](classastrea_1_1astro_1_1StateHistory.md#typedef-iterator) | [**end**](#function-end-12) () <br>_Returns an iterator to the end of the state history._  |
|  [**const\_iterator**](classastrea_1_1astro_1_1StateHistory.md#typedef-const_iterator) | [**end**](#function-end-22) () const<br>_Returns a constant iterator to the end of the state history._  |
|  [**const**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) [**Date**](classastrea_1_1astro_1_1Date.md) & | [**epoch**](#function-epoch) () const<br>_Retrieves the epoch (first date) of the state history._  |
|  [**void**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) | [**fast\_append**](#function-fast_append) ([**const**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) [**State**](classastrea_1_1astro_1_1State.md) & state) <br>_Appends a state to the end of the history without sorting._  |
|  [**void**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) | [**fast\_prepend**](#function-fast_prepend) ([**const**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) [**State**](classastrea_1_1astro_1_1State.md) & state) <br>_Prepends a state to the beginning of the history without sorting._  |
|  [**State**](classastrea_1_1astro_1_1State.md) & | [**first**](#function-first-12) () <br>_Retrieves the first and last states in the history._  |
|  [**const**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) [**State**](classastrea_1_1astro_1_1State.md) & | [**first**](#function-first-22) () const<br>_Retrieves the first and last states in the history._  |
|  [**const**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) [**State**](classastrea_1_1astro_1_1State.md) & | [**get\_closest\_state**](#function-get_closest_state) ([**const**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) [**Date**](classastrea_1_1astro_1_1Date.md) & date) const<br>_Retrieves the closest state to a given date._  |
|  [**const**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) EventTimesMap & | [**get\_event\_times**](#function-get_event_times-12) () const<br>_Retrieves the event times recorded during propagation._  |
|  EventTimesMap & | [**get\_event\_times**](#function-get_event_times-22) () <br>_Retrieves the event times recorded during propagation._  |
|  std::size\_t | [**get\_object\_id**](#function-get_object_id) () const<br>_Gets the object ID for this state history._  |
|  [**State**](classastrea_1_1astro_1_1State.md) | [**get\_state\_at**](#function-get_state_at) ([**const**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) [**Date**](classastrea_1_1astro_1_1Date.md) & date, [**const**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) [**bool**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) allowApproximation=[**true**](classastrea_1_1astro_1_1DirectionCosineMatrix.md)) const<br>_Retrieves the state at a specific date._  |
|  [**void**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) | [**insert**](#function-insert-12) ([**const**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) [**State**](classastrea_1_1astro_1_1State.md) & state) <br>_Inserts a state at a specific date into the history._  |
|  [**void**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) | [**insert**](#function-insert-22) ([**const**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) [**StateHistory**](classastrea_1_1astro_1_1StateHistory.md) & stateHistory) <br>_Inserts multiple states from another_ [_**StateHistory**_](classastrea_1_1astro_1_1StateHistory.md) _into this history._ |
|  [**State**](classastrea_1_1astro_1_1State.md) & | [**last**](#function-last-12) () <br>_Retrieves the last state in the history._  |
|  [**const**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) [**State**](classastrea_1_1astro_1_1State.md) & | [**last**](#function-last-22) () const<br>_Retrieves the last state in the history._  |
|  [**void**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) | [**set\_event\_times**](#function-set_event_times) ([**const**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) EventTimesMap & eventTimes) <br>_Sets the event times recorded during propagation._  |
|  [**void**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) | [**set\_object\_id**](#function-set_object_id) ([**const**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) std::size\_t & objectId) <br>_Sets the object ID for this state history._  |
|  std::size\_t | [**size**](#function-size) () const<br>_Get the number of states in the history._  |
|  [**void**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) | [**sort**](#function-sort) () <br>_Sorts the states in the history by date (epoch)._  |
|   | [**~StateHistory**](#function-statehistory) () = default<br>_Destructor for_ [_**StateHistory**_](classastrea_1_1astro_1_1StateHistory.md) _._ |




























## Detailed Description


This class allows storing, retrieving, and managing the states of an object at different dates, providing functionality to access the closest state to a given date and to convert between different orbital elements. 


    
## Public Types Documentation




### typedef const\_iterator 

_Constant iterator types for iterating over the states in the history._ 
```C++
using astrea::astro::StateHistory::const_iterator =  std::vector<State>::const_iterator;
```




<hr>



### typedef iterator 

_Iterator types for iterating over the states in the history._ 
```C++
using astrea::astro::StateHistory::iterator =  std::vector<State>::iterator;
```




<hr>
## Public Functions Documentation




### function StateHistory [1/2]

_Default constructor for_ [_**StateHistory**_](classastrea_1_1astro_1_1StateHistory.md) _._
```C++
astrea::astro::StateHistory::StateHistory () = default
```




<hr>



### function StateHistory [2/2]

_Constructor that initializes_ [_**StateHistory**_](classastrea_1_1astro_1_1StateHistory.md) _with a specific object ID._
```C++
inline astrea::astro::StateHistory::StateHistory (
    const std::size_t & objectId
) 
```





**Parameters:**


* `objectId` The ID of the object for which the state history is maintained. 




        

<hr>



### function begin [1/2]

_Returns an iterator to the beginning of the state history._ 
```C++
inline iterator astrea::astro::StateHistory::begin () 
```





**Returns:**

iterator An iterator to the first state in the history. 





        

<hr>



### function begin [2/2]

_Returns a constant iterator to the beginning of the state history._ 
```C++
inline const_iterator astrea::astro::StateHistory::begin () const
```





**Returns:**

const\_iterator A constant iterator to the first state in the history. 





        

<hr>



### function cbegin 

_Returns a constant iterator to the beginning of the state history._ 
```C++
inline const_iterator astrea::astro::StateHistory::cbegin () const
```





**Returns:**

const\_iterator A constant iterator to the first state in the history. 





        

<hr>



### function cend 

_Returns a constant iterator to the end of the state history._ 
```C++
inline const_iterator astrea::astro::StateHistory::cend () const
```





**Returns:**

const\_iterator A constant iterator to the position after the last state in the history. 





        

<hr>



### function clear 

_Clears the state history, removing all stored states._ 
```C++
void astrea::astro::StateHistory::clear () 
```




<hr>



### function empty 

_Checks if the state history is empty._ 
```C++
bool astrea::astro::StateHistory::empty () const
```





**Returns:**

true if the state history is empty, false otherwise. 





        

<hr>



### function end [1/2]

_Returns an iterator to the end of the state history._ 
```C++
inline iterator astrea::astro::StateHistory::end () 
```





**Returns:**

iterator An iterator to the position after the last state in the history. 





        

<hr>



### function end [2/2]

_Returns a constant iterator to the end of the state history._ 
```C++
inline const_iterator astrea::astro::StateHistory::end () const
```





**Returns:**

const\_iterator A constant iterator to the position after the last state in the history. 





        

<hr>



### function epoch 

_Retrieves the epoch (first date) of the state history._ 
```C++
inline const  Date & astrea::astro::StateHistory::epoch () const
```





**Returns:**

const [**Date**](classastrea_1_1astro_1_1Date.md)& Reference to the epoch of the state history. 





        

<hr>



### function fast\_append 

_Appends a state to the end of the history without sorting._ 
```C++
inline void astrea::astro::StateHistory::fast_append (
    const  State & state
) 
```



This method is faster than [**insert()**](classastrea_1_1astro_1_1StateHistory.md#function-insert-12) but does not maintain sorted order. Use with caution and only when you are sure the states are already sorted.




**Parameters:**


* `state` The state to be appended. 




        

<hr>



### function fast\_prepend 

_Prepends a state to the beginning of the history without sorting._ 
```C++
inline void astrea::astro::StateHistory::fast_prepend (
    const  State & state
) 
```



This method is faster than [**insert()**](classastrea_1_1astro_1_1StateHistory.md#function-insert-12) but does not maintain sorted order. Use with caution and only when you are sure the states are already sorted.




**Parameters:**


* `state` The state to be prepended. 




        

<hr>



### function first [1/2]

_Retrieves the first and last states in the history._ 
```C++
inline State & astrea::astro::StateHistory::first () 
```





**Returns:**

[**State**](classastrea_1_1astro_1_1State.md)& Reference to the first state. 





        

<hr>



### function first [2/2]

_Retrieves the first and last states in the history._ 
```C++
inline const  State & astrea::astro::StateHistory::first () const
```





**Returns:**

const [**State**](classastrea_1_1astro_1_1State.md)& Reference to the first state. 





        

<hr>



### function get\_closest\_state 

_Retrieves the closest state to a given date._ 
```C++
const  State & astrea::astro::StateHistory::get_closest_state (
    const  Date & date
) const
```



This function finds the state that is closest to the specified date, either before or after it, and returns it.




**Parameters:**


* `date` The date for which the closest state is requested. 



**Returns:**

const [**State**](classastrea_1_1astro_1_1State.md)& Reference to the closest state. 





        

<hr>



### function get\_event\_times [1/2]

_Retrieves the event times recorded during propagation._ 
```C++
inline const EventTimesMap & astrea::astro::StateHistory::get_event_times () const
```





**Returns:**

const EventTimesMap& A vector of dates representing the event times. 





        

<hr>



### function get\_event\_times [2/2]

_Retrieves the event times recorded during propagation._ 
```C++
inline EventTimesMap & astrea::astro::StateHistory::get_event_times () 
```





**Returns:**

const EventTimesMap& A vector of dates representing the event times. 





        

<hr>



### function get\_object\_id 

_Gets the object ID for this state history._ 
```C++
inline std::size_t astrea::astro::StateHistory::get_object_id () const
```





**Returns:**

std::size\_t The ID of the object for which this state history is maintained. 





        

<hr>



### function get\_state\_at 

_Retrieves the state at a specific date._ 
```C++
State astrea::astro::StateHistory::get_state_at (
    const  Date & date,
    const  bool allowApproximation=true
) const
```



This function returns the state at the specified date, or the closest state if no exact match is found and allowApproximation is true, otherwise it interpolates to the given time.




**Parameters:**


* `date` The date for which the state is requested. 
* `allowApproximation` Flag indicating whether to allow returning the closest state if an exact match is not found (default is true). 



**Returns:**

[**State**](classastrea_1_1astro_1_1State.md) The state at the specified date.




**Note:**

Allowing the approximation is generally recommended and will only accept times within a second of any stored points without interpolation. 





        

<hr>



### function insert [1/2]

_Inserts a state at a specific date into the history._ 
```C++
void astrea::astro::StateHistory::insert (
    const  State & state
) 
```





**Parameters:**


* `state` The state to be inserted. 




        

<hr>



### function insert [2/2]

_Inserts multiple states from another_ [_**StateHistory**_](classastrea_1_1astro_1_1StateHistory.md) _into this history._
```C++
void astrea::astro::StateHistory::insert (
    const  StateHistory & stateHistory
) 
```





**Parameters:**


* `stateHistory` The [**StateHistory**](classastrea_1_1astro_1_1StateHistory.md) containing the states to be inserted. 




        

<hr>



### function last [1/2]

_Retrieves the last state in the history._ 
```C++
inline State & astrea::astro::StateHistory::last () 
```





**Returns:**

[**State**](classastrea_1_1astro_1_1State.md)& Reference to the last state. 





        

<hr>



### function last [2/2]

_Retrieves the last state in the history._ 
```C++
inline const  State & astrea::astro::StateHistory::last () const
```





**Returns:**

const [**State**](classastrea_1_1astro_1_1State.md)& Reference to the last state. 





        

<hr>



### function set\_event\_times 

_Sets the event times recorded during propagation._ 
```C++
inline void astrea::astro::StateHistory::set_event_times (
    const EventTimesMap & eventTimes
) 
```





**Parameters:**


* `eventTimes` A vector of dates representing the event times. 




        

<hr>



### function set\_object\_id 

_Sets the object ID for this state history._ 
```C++
inline void astrea::astro::StateHistory::set_object_id (
    const std::size_t & objectId
) 
```





**Parameters:**


* `objectId` The ID of the object for which this state history is maintained. 




        

<hr>



### function size 

_Get the number of states in the history._ 
```C++
std::size_t astrea::astro::StateHistory::size () const
```





**Returns:**

std::size\_t The number of states in the history. 





        

<hr>



### function sort 

_Sorts the states in the history by date (epoch)._ 
```C++
void astrea::astro::StateHistory::sort () 
```



This method should typically not be needed since [**insert()**](classastrea_1_1astro_1_1StateHistory.md#function-insert-12) maintains sorted order, but can be useful if states were modified after insertion. 


        

<hr>



### function ~StateHistory 

_Destructor for_ [_**StateHistory**_](classastrea_1_1astro_1_1StateHistory.md) _._
```C++
astrea::astro::StateHistory::~StateHistory () = default
```




<hr>

------------------------------
The documentation for this class was generated from the following file `astrea/astro/astro/state/StateHistory.hpp`

