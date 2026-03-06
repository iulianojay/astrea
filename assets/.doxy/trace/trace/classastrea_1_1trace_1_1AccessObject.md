

# Class astrea::trace::AccessObject



[**ClassList**](annotated.md) **>** [**astrea**](namespaceastrea.md) **>** [**trace**](namespaceastrea_1_1trace.md) **>** [**AccessObject**](classastrea_1_1trace_1_1AccessObject.md)



_Base class for objects that can visually access other objects._ 

* `#include <AccessObject.hpp>`





Inherited by the following classes: [astrea::trace::GroundPoint](classastrea_1_1trace_1_1GroundPoint.md),  [astrea::trace::Sensor](classastrea_1_1trace_1_1Sensor.md),  [astrea::trace::Viewer](classastrea_1_1trace_1_1Viewer.md)
































## Public Functions

| Type | Name |
| ---: | :--- |
|  void | [**add\_access**](#function-add_access) (const std::size\_t & receiverId, const [**RiseSetArray**](classastrea_1_1trace_1_1RiseSetArray.md) & access) <br>_Adds access times for a specific receiver._  |
|  void | [**drop\_access**](#function-drop_access) (const std::size\_t & receiverId, const [**RiseSetArray**](classastrea_1_1trace_1_1RiseSetArray.md) & access) <br>_Drops access times for a specific receiver._  |
|  [**AccessArray**](classastrea_1_1trace_1_1AccessArray.md) & | [**get\_accesses**](#function-get_accesses-12) () <br>_Gets the access times for this object._  |
|  const [**AccessArray**](classastrea_1_1trace_1_1AccessArray.md) & | [**get\_accesses**](#function-get_accesses-22) () const<br>_Gets the access times for this object (const version)._  |
| virtual std::size\_t | [**get\_id**](#function-get_id) () const = 0<br>_Pure virtual function to get the ID of the object._  |
























## Protected Functions

| Type | Name |
| ---: | :--- |
|   | [**AccessObject**](#function-accessobject) () = default<br>_Default constructor._  |
| virtual  | [**~AccessObject**](#function-accessobject) () = default<br>_Default destructor._  |




## Public Functions Documentation




### function add\_access 

_Adds access times for a specific receiver._ 
```C++
inline void astrea::trace::AccessObject::add_access (
    const std::size_t & receiverId,
    const RiseSetArray & access
) 
```





**Parameters:**


* `receiverId` The ID of the receiver. 
* `access` The [**RiseSetArray**](classastrea_1_1trace_1_1RiseSetArray.md) representing the access times. 




        

<hr>



### function drop\_access 

_Drops access times for a specific receiver._ 
```C++
inline void astrea::trace::AccessObject::drop_access (
    const std::size_t & receiverId,
    const RiseSetArray & access
) 
```





**Parameters:**


* `receiverId` The ID of the receiver. 
* `access` The [**RiseSetArray**](classastrea_1_1trace_1_1RiseSetArray.md) representing the access times. 




        

<hr>



### function get\_accesses [1/2]

_Gets the access times for this object._ 
```C++
inline AccessArray & astrea::trace::AccessObject::get_accesses () 
```





**Returns:**

[**AccessArray**](classastrea_1_1trace_1_1AccessArray.md)& A reference to the [**AccessArray**](classastrea_1_1trace_1_1AccessArray.md) containing access times. 





        

<hr>



### function get\_accesses [2/2]

_Gets the access times for this object (const version)._ 
```C++
inline const AccessArray & astrea::trace::AccessObject::get_accesses () const
```





**Returns:**

const [**AccessArray**](classastrea_1_1trace_1_1AccessArray.md)& A const reference to the [**AccessArray**](classastrea_1_1trace_1_1AccessArray.md) containing access times. 





        

<hr>



### function get\_id 

_Pure virtual function to get the ID of the object._ 
```C++
virtual std::size_t astrea::trace::AccessObject::get_id () const = 0
```





**Returns:**

std::size\_t The ID of the object. 





        

<hr>
## Protected Functions Documentation




### function AccessObject 

_Default constructor._ 
```C++
astrea::trace::AccessObject::AccessObject () = default
```




<hr>



### function ~AccessObject 

_Default destructor._ 
```C++
virtual astrea::trace::AccessObject::~AccessObject () = default
```




<hr>

------------------------------
The documentation for this class was generated from the following file `astrea/trace/trace/platforms/AccessObject.hpp`

