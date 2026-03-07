

# Class astrea::trace::AccessArray



[**ClassList**](annotated.md) **>** [**astrea**](namespaceastrea.md) **>** [**trace**](namespaceastrea_1_1trace.md) **>** [**AccessArray**](classastrea_1_1trace_1_1AccessArray.md)



_Represents a collection of access times indexed by sender and receiver IDs. This class provides methods to manipulate and query access times for different sender-receiver pairs._ 

* `#include <AccessArray.hpp>`

















## Public Types

| Type | Name |
| ---: | :--- |
| typedef gtl::btree\_map&lt; [**IdPair**](structastrea_1_1trace_1_1IdPair.md), [**RiseSetArray**](classastrea_1_1trace_1_1RiseSetArray.md) &gt;::[**const\_iterator**](classastrea_1_1trace_1_1AccessArray.md#typedef-const_iterator) | [**const\_iterator**](#typedef-const_iterator)  <br>_Const iterator type for_ [_**AccessArray**_](classastrea_1_1trace_1_1AccessArray.md) _._ |
| typedef gtl::btree\_map&lt; [**IdPair**](structastrea_1_1trace_1_1IdPair.md), [**RiseSetArray**](classastrea_1_1trace_1_1RiseSetArray.md) &gt;::[**iterator**](classastrea_1_1trace_1_1AccessArray.md#typedef-iterator) | [**iterator**](#typedef-iterator)  <br>_Iterator type for_ [_**AccessArray**_](classastrea_1_1trace_1_1AccessArray.md) _._ |




















## Public Functions

| Type | Name |
| ---: | :--- |
|   | [**AccessArray**](#function-accessarray) () = default<br>_Default constructor for_ [_**AccessArray**_](classastrea_1_1trace_1_1AccessArray.md) _. Initializes an empty_[_**AccessArray**_](classastrea_1_1trace_1_1AccessArray.md) _._ |
|  const [**RiseSetArray**](classastrea_1_1trace_1_1RiseSetArray.md) & | [**at**](#function-at) (const std::size\_t & senderId, const std::size\_t & receiverId) const<br>_Accesses the_ [_**RiseSetArray**_](classastrea_1_1trace_1_1RiseSetArray.md) _for a given_[_**IdPair**_](structastrea_1_1trace_1_1IdPair.md) _._ |
|  [**iterator**](classastrea_1_1trace_1_1AccessArray.md#typedef-iterator) | [**begin**](#function-begin-12) () <br>_Returns an iterator to the beginning of the_ [_**AccessArray**_](classastrea_1_1trace_1_1AccessArray.md) _._ |
|  [**const\_iterator**](classastrea_1_1trace_1_1AccessArray.md#typedef-const_iterator) | [**begin**](#function-begin-22) () const<br>_Returns a const iterator to the beginning of the_ [_**AccessArray**_](classastrea_1_1trace_1_1AccessArray.md) _._ |
|  [**const\_iterator**](classastrea_1_1trace_1_1AccessArray.md#typedef-const_iterator) | [**cbegin**](#function-cbegin) () const<br>_Returns a const iterator to the beginning of the_ [_**AccessArray**_](classastrea_1_1trace_1_1AccessArray.md) _._ |
|  [**const\_iterator**](classastrea_1_1trace_1_1AccessArray.md#typedef-const_iterator) | [**cend**](#function-cend) () const<br>_Returns a const iterator to the end of the_ [_**AccessArray**_](classastrea_1_1trace_1_1AccessArray.md) _._ |
|  bool | [**contains**](#function-contains) (const [**IdPair**](structastrea_1_1trace_1_1IdPair.md) & idPair) const<br>_Checks if the_ [_**AccessArray**_](classastrea_1_1trace_1_1AccessArray.md) _contains a_[_**RiseSetArray**_](classastrea_1_1trace_1_1RiseSetArray.md) _for the specified_[_**IdPair**_](structastrea_1_1trace_1_1IdPair.md) _._ |
|  [**iterator**](classastrea_1_1trace_1_1AccessArray.md#typedef-iterator) | [**end**](#function-end-12) () <br>_Returns an iterator to the end of the_ [_**AccessArray**_](classastrea_1_1trace_1_1AccessArray.md) _._ |
|  [**const\_iterator**](classastrea_1_1trace_1_1AccessArray.md#typedef-const_iterator) | [**end**](#function-end-22) () const<br>_Returns a const iterator to the end of the_ [_**AccessArray**_](classastrea_1_1trace_1_1AccessArray.md) _._ |
|  void | [**erase**](#function-erase) (const std::size\_t & senderId, const std::size\_t & receiverId) <br>_Erases the_ [_**RiseSetArray**_](classastrea_1_1trace_1_1RiseSetArray.md) _for a given sender and receiver ID._ |
|  [**RiseSetArray**](classastrea_1_1trace_1_1RiseSetArray.md) | [**get\_all\_accesses\_from\_sender**](#function-get_all_accesses_from_sender) (const std::size\_t & senderId) const<br>_Retrieves the_ [_**RiseSetArray**_](classastrea_1_1trace_1_1RiseSetArray.md) _for all accesses from a specific sender._ |
|  [**RiseSetArray**](classastrea_1_1trace_1_1RiseSetArray.md) | [**get\_all\_accesses\_to\_receiver**](#function-get_all_accesses_to_receiver) (const std::size\_t & receiverId) const<br>_Retrieves the_ [_**RiseSetArray**_](classastrea_1_1trace_1_1RiseSetArray.md) _for all accesses to a specific receiver._ |
|  [**AccessArray**](classastrea_1_1trace_1_1AccessArray.md) | [**operator&**](#function-operator) (const [**AccessArray**](classastrea_1_1trace_1_1AccessArray.md) & other) const<br>_Const intersection operator for_ [_**AccessArray**_](classastrea_1_1trace_1_1AccessArray.md) _._ |
|  [**AccessArray**](classastrea_1_1trace_1_1AccessArray.md) & | [**operator&=**](#function-operator_1) (const [**AccessArray**](classastrea_1_1trace_1_1AccessArray.md) & other) <br>_Intersection operator for_ [_**AccessArray**_](classastrea_1_1trace_1_1AccessArray.md) _._ |
|  bool | [**operator==**](#function-operator_2) (const [**AccessArray**](classastrea_1_1trace_1_1AccessArray.md) & other) const<br>_Equality operator for_ [_**AccessArray**_](classastrea_1_1trace_1_1AccessArray.md) _._ |
|  [**RiseSetArray**](classastrea_1_1trace_1_1RiseSetArray.md) & | [**operator[]**](#function-operator_3) (const std::size\_t & senderId, const std::size\_t & receiverId) <br>_Accesses the_ [_**RiseSetArray**_](classastrea_1_1trace_1_1RiseSetArray.md) _for a given sender and receiver ID._ |
|  [**AccessArray**](classastrea_1_1trace_1_1AccessArray.md) | [**operator\|**](#function-operator_4) (const [**AccessArray**](classastrea_1_1trace_1_1AccessArray.md) & other) const<br>_Const union operator for_ [_**AccessArray**_](classastrea_1_1trace_1_1AccessArray.md) _._ |
|  [**AccessArray**](classastrea_1_1trace_1_1AccessArray.md) & | [**operator\|=**](#function-operator_5) (const [**AccessArray**](classastrea_1_1trace_1_1AccessArray.md) & other) <br>_Union operator for_ [_**AccessArray**_](classastrea_1_1trace_1_1AccessArray.md) _._ |
|  std::size\_t | [**size**](#function-size) () const<br>_Returns the number of RiseSetArrays in the_ [_**AccessArray**_](classastrea_1_1trace_1_1AccessArray.md) _._ |
|   | [**~AccessArray**](#function-accessarray) () = default<br>_Default destructor for_ [_**AccessArray**_](classastrea_1_1trace_1_1AccessArray.md) _._ |




























## Public Types Documentation




### typedef const\_iterator 

_Const iterator type for_ [_**AccessArray**_](classastrea_1_1trace_1_1AccessArray.md) _._
```C++
using astrea::trace::AccessArray::const_iterator =  gtl::btree_map<IdPair, RiseSetArray>::const_iterator;
```




<hr>



### typedef iterator 

_Iterator type for_ [_**AccessArray**_](classastrea_1_1trace_1_1AccessArray.md) _._
```C++
using astrea::trace::AccessArray::iterator =  gtl::btree_map<IdPair, RiseSetArray>::iterator;
```




<hr>
## Public Functions Documentation




### function AccessArray 

_Default constructor for_ [_**AccessArray**_](classastrea_1_1trace_1_1AccessArray.md) _. Initializes an empty_[_**AccessArray**_](classastrea_1_1trace_1_1AccessArray.md) _._
```C++
astrea::trace::AccessArray::AccessArray () = default
```




<hr>



### function at 

_Accesses the_ [_**RiseSetArray**_](classastrea_1_1trace_1_1RiseSetArray.md) _for a given_[_**IdPair**_](structastrea_1_1trace_1_1IdPair.md) _._
```C++
const RiseSetArray & astrea::trace::AccessArray::at (
    const std::size_t & senderId,
    const std::size_t & receiverId
) const
```





**Parameters:**


* `senderId` The ID of the sender. 
* `receiverId` The ID of the receiver. 



**Returns:**

[**RiseSetArray**](classastrea_1_1trace_1_1RiseSetArray.md)& The [**RiseSetArray**](classastrea_1_1trace_1_1RiseSetArray.md) for the specified sender and receiver. 





        

<hr>



### function begin [1/2]

_Returns an iterator to the beginning of the_ [_**AccessArray**_](classastrea_1_1trace_1_1AccessArray.md) _._
```C++
inline iterator astrea::trace::AccessArray::begin () 
```





**Returns:**

iterator An iterator to the beginning. 





        

<hr>



### function begin [2/2]

_Returns a const iterator to the beginning of the_ [_**AccessArray**_](classastrea_1_1trace_1_1AccessArray.md) _._
```C++
inline const_iterator astrea::trace::AccessArray::begin () const
```





**Returns:**

const\_iterator A const iterator to the beginning. 





        

<hr>



### function cbegin 

_Returns a const iterator to the beginning of the_ [_**AccessArray**_](classastrea_1_1trace_1_1AccessArray.md) _._
```C++
inline const_iterator astrea::trace::AccessArray::cbegin () const
```





**Returns:**

const\_iterator A const iterator to the beginning. 





        

<hr>



### function cend 

_Returns a const iterator to the end of the_ [_**AccessArray**_](classastrea_1_1trace_1_1AccessArray.md) _._
```C++
inline const_iterator astrea::trace::AccessArray::cend () const
```





**Returns:**

const\_iterator A const iterator to the end. 





        

<hr>



### function contains 

_Checks if the_ [_**AccessArray**_](classastrea_1_1trace_1_1AccessArray.md) _contains a_[_**RiseSetArray**_](classastrea_1_1trace_1_1RiseSetArray.md) _for the specified_[_**IdPair**_](structastrea_1_1trace_1_1IdPair.md) _._
```C++
bool astrea::trace::AccessArray::contains (
    const IdPair & idPair
) const
```





**Parameters:**


* `idPair` The [**IdPair**](structastrea_1_1trace_1_1IdPair.md) to check. 



**Returns:**

true if the [**AccessArray**](classastrea_1_1trace_1_1AccessArray.md) contains the [**IdPair**](structastrea_1_1trace_1_1IdPair.md), false otherwise. 





        

<hr>



### function end [1/2]

_Returns an iterator to the end of the_ [_**AccessArray**_](classastrea_1_1trace_1_1AccessArray.md) _._
```C++
inline iterator astrea::trace::AccessArray::end () 
```





**Returns:**

iterator An iterator to the end. 





        

<hr>



### function end [2/2]

_Returns a const iterator to the end of the_ [_**AccessArray**_](classastrea_1_1trace_1_1AccessArray.md) _._
```C++
inline const_iterator astrea::trace::AccessArray::end () const
```





**Returns:**

const\_iterator A const iterator to the end. 





        

<hr>



### function erase 

_Erases the_ [_**RiseSetArray**_](classastrea_1_1trace_1_1RiseSetArray.md) _for a given sender and receiver ID._
```C++
void astrea::trace::AccessArray::erase (
    const std::size_t & senderId,
    const std::size_t & receiverId
) 
```





**Parameters:**


* `senderId` The ID of the sender. 
* `receiverId` The ID of the receiver. 




        

<hr>



### function get\_all\_accesses\_from\_sender 

_Retrieves the_ [_**RiseSetArray**_](classastrea_1_1trace_1_1RiseSetArray.md) _for all accesses from a specific sender._
```C++
RiseSetArray astrea::trace::AccessArray::get_all_accesses_from_sender (
    const std::size_t & senderId
) const
```





**Parameters:**


* `senderId` The ID of the sender. 



**Returns:**

[**RiseSetArray**](classastrea_1_1trace_1_1RiseSetArray.md) The [**RiseSetArray**](classastrea_1_1trace_1_1RiseSetArray.md) containing all accesses from the specified sender. 





        

<hr>



### function get\_all\_accesses\_to\_receiver 

_Retrieves the_ [_**RiseSetArray**_](classastrea_1_1trace_1_1RiseSetArray.md) _for all accesses to a specific receiver._
```C++
RiseSetArray astrea::trace::AccessArray::get_all_accesses_to_receiver (
    const std::size_t & receiverId
) const
```





**Parameters:**


* `receiverId` The ID of the receiver. 



**Returns:**

[**RiseSetArray**](classastrea_1_1trace_1_1RiseSetArray.md) The [**RiseSetArray**](classastrea_1_1trace_1_1RiseSetArray.md) containing all accesses to the specified receiver. 





        

<hr>



### function operator& 

_Const intersection operator for_ [_**AccessArray**_](classastrea_1_1trace_1_1AccessArray.md) _._
```C++
AccessArray astrea::trace::AccessArray::operator& (
    const AccessArray & other
) const
```





**Parameters:**


* `other` The [**AccessArray**](classastrea_1_1trace_1_1AccessArray.md) to intersect with. 



**Returns:**

[**AccessArray**](classastrea_1_1trace_1_1AccessArray.md) The resulting [**AccessArray**](classastrea_1_1trace_1_1AccessArray.md) after the intersection operation. 





        

<hr>



### function operator&= 

_Intersection operator for_ [_**AccessArray**_](classastrea_1_1trace_1_1AccessArray.md) _._
```C++
AccessArray & astrea::trace::AccessArray::operator&= (
    const AccessArray & other
) 
```





**Parameters:**


* `other` The [**AccessArray**](classastrea_1_1trace_1_1AccessArray.md) to intersect with. 




        

<hr>



### function operator== 

_Equality operator for_ [_**AccessArray**_](classastrea_1_1trace_1_1AccessArray.md) _._
```C++
bool astrea::trace::AccessArray::operator== (
    const AccessArray & other
) const
```





**Parameters:**


* `other` The [**AccessArray**](classastrea_1_1trace_1_1AccessArray.md) to compare with. 



**Returns:**

true if the AccessArrays are equal, false otherwise. 





        

<hr>



### function operator[] 

_Accesses the_ [_**RiseSetArray**_](classastrea_1_1trace_1_1RiseSetArray.md) _for a given sender and receiver ID._
```C++
RiseSetArray & astrea::trace::AccessArray::operator[] (
    const std::size_t & senderId,
    const std::size_t & receiverId
) 
```





**Parameters:**


* `senderId` The ID of the sender. 
* `receiverId` The ID of the receiver. 



**Returns:**

[**RiseSetArray**](classastrea_1_1trace_1_1RiseSetArray.md)& The [**RiseSetArray**](classastrea_1_1trace_1_1RiseSetArray.md) for the specified sender and receiver. 





        

<hr>



### function operator\| 

_Const union operator for_ [_**AccessArray**_](classastrea_1_1trace_1_1AccessArray.md) _._
```C++
AccessArray astrea::trace::AccessArray::operator| (
    const AccessArray & other
) const
```





**Parameters:**


* `other` The [**AccessArray**](classastrea_1_1trace_1_1AccessArray.md) to union with. 



**Returns:**

[**AccessArray**](classastrea_1_1trace_1_1AccessArray.md) The resulting [**AccessArray**](classastrea_1_1trace_1_1AccessArray.md) after the union operation. 





        

<hr>



### function operator\|= 

_Union operator for_ [_**AccessArray**_](classastrea_1_1trace_1_1AccessArray.md) _._
```C++
AccessArray & astrea::trace::AccessArray::operator|= (
    const AccessArray & other
) 
```





**Parameters:**


* `other` The [**AccessArray**](classastrea_1_1trace_1_1AccessArray.md) to union with. 




        

<hr>



### function size 

_Returns the number of RiseSetArrays in the_ [_**AccessArray**_](classastrea_1_1trace_1_1AccessArray.md) _._
```C++
std::size_t astrea::trace::AccessArray::size () const
```





**Returns:**

std::size\_t The number of RiseSetArrays. 





        

<hr>



### function ~AccessArray 

_Default destructor for_ [_**AccessArray**_](classastrea_1_1trace_1_1AccessArray.md) _._
```C++
astrea::trace::AccessArray::~AccessArray () = default
```




<hr>

------------------------------
The documentation for this class was generated from the following file `astrea/trace/trace/risesets/AccessArray.hpp`

