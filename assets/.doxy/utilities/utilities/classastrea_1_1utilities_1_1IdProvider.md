

# Class astrea::utilities::IdProvider



[**ClassList**](annotated.md) **>** [**astrea**](namespaceastrea.md) **>** [**utilities**](namespaceastrea_1_1utilities.md) **>** [**IdProvider**](classastrea_1_1utilities_1_1IdProvider.md)










































## Public Functions

| Type | Name |
| ---: | :--- |
|   | [**IdProvider**](#function-idprovider) () = delete<br>_Deleted constructor to prevent instantiation of_ [_**IdProvider**_](classastrea_1_1utilities_1_1IdProvider.md) _._ |


## Public Static Functions

| Type | Name |
| ---: | :--- |
|  std::size\_t | [**get\_next\_id**](#function-get_next_id) () <br>_Get the next unique ID._  |


























## Public Functions Documentation




### function IdProvider 

_Deleted constructor to prevent instantiation of_ [_**IdProvider**_](classastrea_1_1utilities_1_1IdProvider.md) _._
```C++
astrea::utilities::IdProvider::IdProvider () = delete
```




<hr>
## Public Static Functions Documentation




### function get\_next\_id 

_Get the next unique ID._ 
```C++
template<mp_units::symbol_text name>
static inline std::size_t astrea::utilities::IdProvider::get_next_id () 
```





**Template parameters:**


* `name` A string literal representing the type of ID being generated (e.g., "Spacecraft", "Plane", etc.). 



**Returns:**

std::size\_t The next unique ID. 





        

<hr>

------------------------------
The documentation for this class was generated from the following file `astrea/utilities/utilities/IdProvider.hpp`

