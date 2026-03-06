

# Struct astrea::trace::IdPair



[**ClassList**](annotated.md) **>** [**astrea**](namespaceastrea.md) **>** [**trace**](namespaceastrea_1_1trace.md) **>** [**IdPair**](structastrea_1_1trace_1_1IdPair.md)



_Represents a pair of IDs for sender and receiver._ 

* `#include <IdPair.hpp>`





















## Public Attributes

| Type | Name |
| ---: | :--- |
|  std::size\_t | [**receiver**](#variable-receiver)  <br>_The ID of the receiver._  |
|  std::size\_t | [**sender**](#variable-sender)  <br>_&lt; The ID of the sender._  |
















## Public Functions

| Type | Name |
| ---: | :--- |
|   | [**IdPair**](#function-idpair-13) () = default<br>_Default constructor for_ [_**IdPair**_](structastrea_1_1trace_1_1IdPair.md) _._ |
|   | [**IdPair**](#function-idpair-23) (std::size\_t sender, std::size\_t receiver) <br>_Constructs an_ [_**IdPair**_](structastrea_1_1trace_1_1IdPair.md) _with specified sender and receiver IDs._ |
|   | [**IdPair**](#function-idpair-33) (const [**IdPair**](structastrea_1_1trace_1_1IdPair.md) & other) <br>_Copy constructor for_ [_**IdPair**_](structastrea_1_1trace_1_1IdPair.md) _._ |
|  bool | [**operator==**](#function-operator) (const [**IdPair**](structastrea_1_1trace_1_1IdPair.md) & other) const<br>_Equality operator for_ [_**IdPair**_](structastrea_1_1trace_1_1IdPair.md) _._ |
|   | [**~IdPair**](#function-idpair) () = default<br>_Default destructor for_ [_**IdPair**_](structastrea_1_1trace_1_1IdPair.md) _._ |




























## Public Attributes Documentation




### variable receiver 

_The ID of the receiver._ 
```C++
std::size_t astrea::trace::IdPair::receiver;
```




<hr>



### variable sender 

_&lt; The ID of the sender._ 
```C++
std::size_t astrea::trace::IdPair::sender;
```




<hr>
## Public Functions Documentation




### function IdPair [1/3]

_Default constructor for_ [_**IdPair**_](structastrea_1_1trace_1_1IdPair.md) _._
```C++
astrea::trace::IdPair::IdPair () = default
```




<hr>



### function IdPair [2/3]

_Constructs an_ [_**IdPair**_](structastrea_1_1trace_1_1IdPair.md) _with specified sender and receiver IDs._
```C++
inline astrea::trace::IdPair::IdPair (
    std::size_t sender,
    std::size_t receiver
) 
```





**Parameters:**


* `sender` The ID of the sender. 
* `receiver` The ID of the receiver. 




        

<hr>



### function IdPair [3/3]

_Copy constructor for_ [_**IdPair**_](structastrea_1_1trace_1_1IdPair.md) _._
```C++
inline astrea::trace::IdPair::IdPair (
    const IdPair & other
) 
```





**Parameters:**


* `other` The [**IdPair**](structastrea_1_1trace_1_1IdPair.md) to copy from. 




        

<hr>



### function operator== 

_Equality operator for_ [_**IdPair**_](structastrea_1_1trace_1_1IdPair.md) _._
```C++
inline bool astrea::trace::IdPair::operator== (
    const IdPair & other
) const
```





**Parameters:**


* `other` The [**IdPair**](structastrea_1_1trace_1_1IdPair.md) to compare with. 



**Returns:**

True if both sender and receiver IDs are equal, false otherwise. 





        

<hr>



### function ~IdPair 

_Default destructor for_ [_**IdPair**_](structastrea_1_1trace_1_1IdPair.md) _._
```C++
astrea::trace::IdPair::~IdPair () = default
```




<hr>

------------------------------
The documentation for this class was generated from the following file `astrea/trace/trace/types/IdPair.hpp`

