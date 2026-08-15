

# Class astrea::astro::Constellation::sat\_iterator



[**ClassList**](annotated.md) **>** [**astrea**](namespaceastrea.md) **>** [**astro**](namespaceastrea_1_1astro.md) **>** [**Constellation**](classastrea_1_1astro_1_1Constellation.md) **>** [**sat\_iterator**](classastrea_1_1astro_1_1Constellation_1_1sat__iterator.md)



_Iterator class for iterating over all_ [_**Spacecraft**_](classastrea_1_1astro_1_1Spacecraft.md) _in the_[_**Constellation**_](classastrea_1_1astro_1_1Constellation.md) _._

* `#include <Constellation.hpp>`





































## Public Functions

| Type | Name |
| ---: | :--- |
|  bool | [**operator!=**](#function-operator) (const [**sat\_iterator**](classastrea_1_1astro_1_1Constellation_1_1sat__iterator.md) & other) const<br>_Inequality operator for the_ [_**sat\_iterator**_](classastrea_1_1astro_1_1Constellation_1_1sat__iterator.md) _._ |
|  Spacecraft\_T | [**operator\***](#function-operator_1) () <br>_Dereference operator for the_ [_**sat\_iterator**_](classastrea_1_1astro_1_1Constellation_1_1sat__iterator.md) _._ |
|  [**sat\_iterator**](classastrea_1_1astro_1_1Constellation_1_1sat__iterator.md) & | [**operator++**](#function-operator_2) () <br>_Pre-increment operator for the_ [_**sat\_iterator**_](classastrea_1_1astro_1_1Constellation_1_1sat__iterator.md) _._ |
|  [**sat\_iterator**](classastrea_1_1astro_1_1Constellation_1_1sat__iterator.md) | [**operator++**](#function-operator_3) (int) <br>_Post-increment operator for the_ [_**sat\_iterator**_](classastrea_1_1astro_1_1Constellation_1_1sat__iterator.md) _._ |
|  [**sat\_iterator**](classastrea_1_1astro_1_1Constellation_1_1sat__iterator.md) & | [**operator--**](#function-operator-) () <br>_Pre-decrement operator for the_ [_**sat\_iterator**_](classastrea_1_1astro_1_1Constellation_1_1sat__iterator.md) _._ |
|  [**sat\_iterator**](classastrea_1_1astro_1_1Constellation_1_1sat__iterator.md) | [**operator--**](#function-operator-_1) (int) <br>_Post-decrement operator for the_ [_**sat\_iterator**_](classastrea_1_1astro_1_1Constellation_1_1sat__iterator.md) _._ |
|  bool | [**operator&lt;**](#function-operator_4) (const [**sat\_iterator**](classastrea_1_1astro_1_1Constellation_1_1sat__iterator.md) & other) const<br>_Less than operator for the_ [_**sat\_iterator**_](classastrea_1_1astro_1_1Constellation_1_1sat__iterator.md) _._ |
|  bool | [**operator&lt;=**](#function-operator_5) (const [**sat\_iterator**](classastrea_1_1astro_1_1Constellation_1_1sat__iterator.md) & other) const<br>_Less than or equal to operator for the_ [_**sat\_iterator**_](classastrea_1_1astro_1_1Constellation_1_1sat__iterator.md) _._ |
|  bool | [**operator==**](#function-operator_6) (const [**sat\_iterator**](classastrea_1_1astro_1_1Constellation_1_1sat__iterator.md) & other) const<br>_Equality operator for the_ [_**sat\_iterator**_](classastrea_1_1astro_1_1Constellation_1_1sat__iterator.md) _._ |
|  bool | [**operator&gt;**](#function-operator_7) (const [**sat\_iterator**](classastrea_1_1astro_1_1Constellation_1_1sat__iterator.md) & other) const<br>_Greater than operator for the_ [_**sat\_iterator**_](classastrea_1_1astro_1_1Constellation_1_1sat__iterator.md) _._ |
|  bool | [**operator&gt;=**](#function-operator_8) (const [**sat\_iterator**](classastrea_1_1astro_1_1Constellation_1_1sat__iterator.md) & other) const<br>_Greater than or equal to operator for the_ [_**sat\_iterator**_](classastrea_1_1astro_1_1Constellation_1_1sat__iterator.md) _._ |
|   | [**sat\_iterator**](#function-sat_iterator) (std::vector&lt; [**Shell**](classastrea_1_1astro_1_1Shell.md)&lt; Spacecraft\_T &gt; &gt;[**::iterator**](classastrea_1_1astro_1_1Constellation.md#typedef-iterator) \_iterShell, [**Shell**](classastrea_1_1astro_1_1Shell.md)&lt; Spacecraft\_T &gt;::sat\_iterator \_iterSat) <br>_Construct a_ [_**sat\_iterator**_](classastrea_1_1astro_1_1Constellation_1_1sat__iterator.md) _from a_[_**Shell**_](classastrea_1_1astro_1_1Shell.md) _iterator and a_[_**Spacecraft**_](classastrea_1_1astro_1_1Spacecraft.md) _iterator._ |




























## Public Functions Documentation




### function operator!= 

_Inequality operator for the_ [_**sat\_iterator**_](classastrea_1_1astro_1_1Constellation_1_1sat__iterator.md) _._
```C++
inline bool astrea::astro::Constellation::sat_iterator::operator!= (
    const sat_iterator & other
) const
```





**Parameters:**


* `other` The other [**sat\_iterator**](classastrea_1_1astro_1_1Constellation_1_1sat__iterator.md) to compare with. 



**Returns:**

true if both iterators do not point to the same [**Spacecraft**](classastrea_1_1astro_1_1Spacecraft.md), false otherwise. 





        

<hr>



### function operator\* 

_Dereference operator for the_ [_**sat\_iterator**_](classastrea_1_1astro_1_1Constellation_1_1sat__iterator.md) _._
```C++
inline Spacecraft_T astrea::astro::Constellation::sat_iterator::operator* () 
```





**Returns:**

Spacecraft\_T& A reference to the [**Spacecraft**](classastrea_1_1astro_1_1Spacecraft.md) pointed to by the iterator. 





        

<hr>



### function operator++ 

_Pre-increment operator for the_ [_**sat\_iterator**_](classastrea_1_1astro_1_1Constellation_1_1sat__iterator.md) _._
```C++
inline sat_iterator & astrea::astro::Constellation::sat_iterator::operator++ () 
```





**Returns:**

[**sat\_iterator**](classastrea_1_1astro_1_1Constellation_1_1sat__iterator.md)& A reference to the incremented iterator. 





        

<hr>



### function operator++ 

_Post-increment operator for the_ [_**sat\_iterator**_](classastrea_1_1astro_1_1Constellation_1_1sat__iterator.md) _._
```C++
inline sat_iterator astrea::astro::Constellation::sat_iterator::operator++ (
    int
) 
```





**Returns:**

[**sat\_iterator**](classastrea_1_1astro_1_1Constellation_1_1sat__iterator.md) A copy of the iterator before incrementing. 





        

<hr>



### function operator-- 

_Pre-decrement operator for the_ [_**sat\_iterator**_](classastrea_1_1astro_1_1Constellation_1_1sat__iterator.md) _._
```C++
inline sat_iterator & astrea::astro::Constellation::sat_iterator::operator-- () 
```





**Returns:**

[**sat\_iterator**](classastrea_1_1astro_1_1Constellation_1_1sat__iterator.md)& A reference to the decremented iterator. 





        

<hr>



### function operator-- 

_Post-decrement operator for the_ [_**sat\_iterator**_](classastrea_1_1astro_1_1Constellation_1_1sat__iterator.md) _._
```C++
inline sat_iterator astrea::astro::Constellation::sat_iterator::operator-- (
    int
) 
```





**Returns:**

[**sat\_iterator**](classastrea_1_1astro_1_1Constellation_1_1sat__iterator.md) A copy of the iterator before decrementing. 





        

<hr>



### function operator&lt; 

_Less than operator for the_ [_**sat\_iterator**_](classastrea_1_1astro_1_1Constellation_1_1sat__iterator.md) _._
```C++
inline bool astrea::astro::Constellation::sat_iterator::operator< (
    const sat_iterator & other
) const
```





**Parameters:**


* `other` The other [**sat\_iterator**](classastrea_1_1astro_1_1Constellation_1_1sat__iterator.md) to compare with. 



**Returns:**

true if this iterator is less than the other, false otherwise. 




**Returns:**

false if this iterator is greater than or equal to the other. 





        

<hr>



### function operator&lt;= 

_Less than or equal to operator for the_ [_**sat\_iterator**_](classastrea_1_1astro_1_1Constellation_1_1sat__iterator.md) _._
```C++
inline bool astrea::astro::Constellation::sat_iterator::operator<= (
    const sat_iterator & other
) const
```





**Parameters:**


* `other` The other [**sat\_iterator**](classastrea_1_1astro_1_1Constellation_1_1sat__iterator.md) to compare with. 



**Returns:**

true if this iterator is less than or equal to the other, false otherwise. 




**Returns:**

false if this iterator is greater than the other. 





        

<hr>



### function operator== 

_Equality operator for the_ [_**sat\_iterator**_](classastrea_1_1astro_1_1Constellation_1_1sat__iterator.md) _._
```C++
inline bool astrea::astro::Constellation::sat_iterator::operator== (
    const sat_iterator & other
) const
```





**Parameters:**


* `other` The other [**sat\_iterator**](classastrea_1_1astro_1_1Constellation_1_1sat__iterator.md) to compare with. 



**Returns:**

true if both iterators point to the same [**Spacecraft**](classastrea_1_1astro_1_1Spacecraft.md), false otherwise. 





        

<hr>



### function operator&gt; 

_Greater than operator for the_ [_**sat\_iterator**_](classastrea_1_1astro_1_1Constellation_1_1sat__iterator.md) _._
```C++
inline bool astrea::astro::Constellation::sat_iterator::operator> (
    const sat_iterator & other
) const
```





**Parameters:**


* `other` The other [**sat\_iterator**](classastrea_1_1astro_1_1Constellation_1_1sat__iterator.md) to compare with. 



**Returns:**

true if this iterator is greater than the other, false otherwise. 




**Returns:**

false if this iterator is less than or equal to the other. 





        

<hr>



### function operator&gt;= 

_Greater than or equal to operator for the_ [_**sat\_iterator**_](classastrea_1_1astro_1_1Constellation_1_1sat__iterator.md) _._
```C++
inline bool astrea::astro::Constellation::sat_iterator::operator>= (
    const sat_iterator & other
) const
```





**Parameters:**


* `other` The other [**sat\_iterator**](classastrea_1_1astro_1_1Constellation_1_1sat__iterator.md) to compare with. 



**Returns:**

true if this iterator is greater than or equal to the other, false otherwise. 




**Returns:**

false if this iterator is less than the other. 





        

<hr>



### function sat\_iterator 

_Construct a_ [_**sat\_iterator**_](classastrea_1_1astro_1_1Constellation_1_1sat__iterator.md) _from a_[_**Shell**_](classastrea_1_1astro_1_1Shell.md) _iterator and a_[_**Spacecraft**_](classastrea_1_1astro_1_1Spacecraft.md) _iterator._
```C++
inline astrea::astro::Constellation::sat_iterator::sat_iterator (
    std::vector< Shell < Spacecraft_T > > ::iterator _iterShell,
    Shell < Spacecraft_T >::sat_iterator _iterSat
) 
```





**Parameters:**


* `_iterShell` The iterator for the Shells in the [**Constellation**](classastrea_1_1astro_1_1Constellation.md). 
* `_iterSat` The iterator for the [**Spacecraft**](classastrea_1_1astro_1_1Spacecraft.md) within the current [**Shell**](classastrea_1_1astro_1_1Shell.md). 




        

<hr>

------------------------------
The documentation for this class was generated from the following file `astrea/astro/astro/platforms/space/Constellation.hpp`

