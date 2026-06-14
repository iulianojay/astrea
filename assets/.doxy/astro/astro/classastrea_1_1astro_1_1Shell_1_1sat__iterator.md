

# Class astrea::astro::Shell::sat\_iterator



[**ClassList**](annotated.md) **>** [**astrea**](namespaceastrea.md) **>** [**astro**](namespaceastrea_1_1astro.md) **>** [**Shell**](classastrea_1_1astro_1_1Shell.md) **>** [**sat\_iterator**](classastrea_1_1astro_1_1Shell_1_1sat__iterator.md)



_Iterator for iterating over all_ [_**Spacecraft**_](classastrea_1_1astro_1_1Spacecraft.md) _in the_[_**Shell**_](classastrea_1_1astro_1_1Shell.md) _._

* `#include <Shell.hpp>`

















## Public Types

| Type | Name |
| ---: | :--- |
| typedef [**Plane**](classastrea_1_1astro_1_1Plane.md)&lt; [**Spacecraft\_T**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) &gt;[**::iterator**](classastrea_1_1astro_1_1Shell.md#typedef-iterator) | [**difference\_type**](#typedef-difference_type)  <br> |
| typedef std::forward\_iterator\_tag | [**iterator\_category**](#typedef-iterator_category)  <br> |
| typedef [**const**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) [**Plane**](classastrea_1_1astro_1_1Plane.md)&lt; [**Spacecraft\_T**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) &gt;[**::iterator**](classastrea_1_1astro_1_1Shell.md#typedef-iterator) \* | [**pointer**](#typedef-pointer)  <br> |
| typedef [**const**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) [**Plane**](classastrea_1_1astro_1_1Plane.md)&lt; [**Spacecraft\_T**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) &gt;[**::iterator**](classastrea_1_1astro_1_1Shell.md#typedef-iterator) & | [**reference**](#typedef-reference)  <br> |
| typedef [**Plane**](classastrea_1_1astro_1_1Plane.md)&lt; [**Spacecraft\_T**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) &gt;[**::iterator**](classastrea_1_1astro_1_1Shell.md#typedef-iterator) | [**value\_type**](#typedef-value_type)  <br> |




















## Public Functions

| Type | Name |
| ---: | :--- |
|  [**bool**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) | [**operator!=**](#function-operator) ([**const**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) [**sat\_iterator**](classastrea_1_1astro_1_1Shell_1_1sat__iterator.md) & other) const<br>_Inequality operator for the_ [_**sat\_iterator**_](classastrea_1_1astro_1_1Shell_1_1sat__iterator.md) _._ |
|  [**Spacecraft\_T**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) | [**operator\***](#function-operator_1) () <br>_Dereference operator for the_ [_**sat\_iterator**_](classastrea_1_1astro_1_1Shell_1_1sat__iterator.md) _._ |
|  [**sat\_iterator**](classastrea_1_1astro_1_1Shell_1_1sat__iterator.md) & | [**operator++**](#function-operator_2) () <br>_Increment operator for the_ [_**sat\_iterator**_](classastrea_1_1astro_1_1Shell_1_1sat__iterator.md) _._ |
|  [**sat\_iterator**](classastrea_1_1astro_1_1Shell_1_1sat__iterator.md) | [**operator++**](#function-operator_3) ([**int**](classastrea_1_1astro_1_1DirectionCosineMatrix.md)) <br>_Post-increment operator for the_ [_**sat\_iterator**_](classastrea_1_1astro_1_1Shell_1_1sat__iterator.md) _._ |
|  [**sat\_iterator**](classastrea_1_1astro_1_1Shell_1_1sat__iterator.md) & | [**operator--**](#function-operator-) () <br>_Decrement operator for the_ [_**sat\_iterator**_](classastrea_1_1astro_1_1Shell_1_1sat__iterator.md) _._ |
|  [**sat\_iterator**](classastrea_1_1astro_1_1Shell_1_1sat__iterator.md) | [**operator--**](#function-operator-_1) ([**int**](classastrea_1_1astro_1_1DirectionCosineMatrix.md)) <br>_Post-decrement operator for the_ [_**sat\_iterator**_](classastrea_1_1astro_1_1Shell_1_1sat__iterator.md) _._ |
|  [**bool**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) | [**operator&lt;**](#function-operator_4) ([**const**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) [**sat\_iterator**](classastrea_1_1astro_1_1Shell_1_1sat__iterator.md) & other) const<br>_Less than operator for the_ [_**sat\_iterator**_](classastrea_1_1astro_1_1Shell_1_1sat__iterator.md) _._ |
|  [**bool**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) | [**operator&lt;=**](#function-operator_5) ([**const**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) [**sat\_iterator**](classastrea_1_1astro_1_1Shell_1_1sat__iterator.md) & other) const<br>_Less than or equal to operator for the_ [_**sat\_iterator**_](classastrea_1_1astro_1_1Shell_1_1sat__iterator.md) _._ |
|  [**bool**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) | [**operator==**](#function-operator_6) ([**const**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) [**sat\_iterator**](classastrea_1_1astro_1_1Shell_1_1sat__iterator.md) & other) const<br>_Comparison operators for the_ [_**sat\_iterator**_](classastrea_1_1astro_1_1Shell_1_1sat__iterator.md) _._ |
|  [**bool**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) | [**operator&gt;**](#function-operator_7) ([**const**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) [**sat\_iterator**](classastrea_1_1astro_1_1Shell_1_1sat__iterator.md) & other) const<br>_Greater than operator for the_ [_**sat\_iterator**_](classastrea_1_1astro_1_1Shell_1_1sat__iterator.md) _._ |
|  [**bool**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) | [**operator&gt;=**](#function-operator_8) ([**const**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) [**sat\_iterator**](classastrea_1_1astro_1_1Shell_1_1sat__iterator.md) & other) const<br>_Greater than or equal to operator for the_ [_**sat\_iterator**_](classastrea_1_1astro_1_1Shell_1_1sat__iterator.md) _._ |
|   | [**sat\_iterator**](#function-sat_iterator) (std::vector&lt; [**Plane**](classastrea_1_1astro_1_1Plane.md)&lt; [**Spacecraft\_T**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) &gt; &gt;[**::iterator**](classastrea_1_1astro_1_1Shell.md#typedef-iterator) \_iterPlane, [**Plane**](classastrea_1_1astro_1_1Plane.md)&lt; [**Spacecraft\_T**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) &gt;[**::iterator**](classastrea_1_1astro_1_1Shell.md#typedef-iterator) \_iterSat) <br>_Default constructor for_ [_**sat\_iterator**_](classastrea_1_1astro_1_1Shell_1_1sat__iterator.md) _. Initializes the iterator to the beginning of the first plane's spacecraft._ |




























## Public Types Documentation




### typedef difference\_type 

```C++
using astrea::astro::Shell< Spacecraft_T >::sat_iterator::difference_type =  Plane<Spacecraft_T>::iterator;
```




<hr>



### typedef iterator\_category 

```C++
using astrea::astro::Shell< Spacecraft_T >::sat_iterator::iterator_category =  std::forward_iterator_tag;
```




<hr>



### typedef pointer 

```C++
using astrea::astro::Shell< Spacecraft_T >::sat_iterator::pointer =  const Plane<Spacecraft_T>::iterator*;
```




<hr>



### typedef reference 

```C++
using astrea::astro::Shell< Spacecraft_T >::sat_iterator::reference =  const Plane<Spacecraft_T>::iterator&;
```




<hr>



### typedef value\_type 

```C++
using astrea::astro::Shell< Spacecraft_T >::sat_iterator::value_type =  Plane<Spacecraft_T>::iterator;
```




<hr>
## Public Functions Documentation




### function operator!= 

_Inequality operator for the_ [_**sat\_iterator**_](classastrea_1_1astro_1_1Shell_1_1sat__iterator.md) _._
```C++
inline bool astrea::astro::Shell::sat_iterator::operator!= (
    const  sat_iterator & other
) const
```





**Parameters:**


* `other` The other iterator to compare against. 



**Returns:**

bool True if the iterators are not equal, false otherwise. 





        

<hr>



### function operator\* 

_Dereference operator for the_ [_**sat\_iterator**_](classastrea_1_1astro_1_1Shell_1_1sat__iterator.md) _._
```C++
inline Spacecraft_T astrea::astro::Shell::sat_iterator::operator* () 
```





**Returns:**

Spacecraft\_T& A reference to the spacecraft at the current iterator position. 





        

<hr>



### function operator++ 

_Increment operator for the_ [_**sat\_iterator**_](classastrea_1_1astro_1_1Shell_1_1sat__iterator.md) _._
```C++
inline sat_iterator & astrea::astro::Shell::sat_iterator::operator++ () 
```





**Returns:**

[**sat\_iterator**](classastrea_1_1astro_1_1Shell_1_1sat__iterator.md)& A reference to the incremented iterator. 





        

<hr>



### function operator++ 

_Post-increment operator for the_ [_**sat\_iterator**_](classastrea_1_1astro_1_1Shell_1_1sat__iterator.md) _._
```C++
inline sat_iterator astrea::astro::Shell::sat_iterator::operator++ (
    int
) 
```





**Returns:**

[**sat\_iterator**](classastrea_1_1astro_1_1Shell_1_1sat__iterator.md) A copy of the iterator before incrementing. 





        

<hr>



### function operator-- 

_Decrement operator for the_ [_**sat\_iterator**_](classastrea_1_1astro_1_1Shell_1_1sat__iterator.md) _._
```C++
inline sat_iterator & astrea::astro::Shell::sat_iterator::operator-- () 
```





**Returns:**

[**sat\_iterator**](classastrea_1_1astro_1_1Shell_1_1sat__iterator.md)& A reference to the decremented iterator. 





        

<hr>



### function operator-- 

_Post-decrement operator for the_ [_**sat\_iterator**_](classastrea_1_1astro_1_1Shell_1_1sat__iterator.md) _._
```C++
inline sat_iterator astrea::astro::Shell::sat_iterator::operator-- (
    int
) 
```





**Returns:**

[**sat\_iterator**](classastrea_1_1astro_1_1Shell_1_1sat__iterator.md) A copy of the iterator before decrementing. 





        

<hr>



### function operator&lt; 

_Less than operator for the_ [_**sat\_iterator**_](classastrea_1_1astro_1_1Shell_1_1sat__iterator.md) _._
```C++
inline bool astrea::astro::Shell::sat_iterator::operator< (
    const  sat_iterator & other
) const
```





**Parameters:**


* `other` The other iterator to compare against. 



**Returns:**

true if this iterator is less than the other, false otherwise. 




**Returns:**

false if this iterator is not less than the other. 





        

<hr>



### function operator&lt;= 

_Less than or equal to operator for the_ [_**sat\_iterator**_](classastrea_1_1astro_1_1Shell_1_1sat__iterator.md) _._
```C++
inline bool astrea::astro::Shell::sat_iterator::operator<= (
    const  sat_iterator & other
) const
```





**Parameters:**


* `other` The other iterator to compare against. 



**Returns:**

true if this iterator is less than or equal to the other, false otherwise. 




**Returns:**

false if this iterator is not less than or equal to the other. 





        

<hr>



### function operator== 

_Comparison operators for the_ [_**sat\_iterator**_](classastrea_1_1astro_1_1Shell_1_1sat__iterator.md) _._
```C++
inline bool astrea::astro::Shell::sat_iterator::operator== (
    const  sat_iterator & other
) const
```





**Parameters:**


* `other` The other iterator to compare against. 



**Returns:**

bool True if the iterators are equal, false otherwise. 





        

<hr>



### function operator&gt; 

_Greater than operator for the_ [_**sat\_iterator**_](classastrea_1_1astro_1_1Shell_1_1sat__iterator.md) _._
```C++
inline bool astrea::astro::Shell::sat_iterator::operator> (
    const  sat_iterator & other
) const
```





**Parameters:**


* `other` The other iterator to compare against. 



**Returns:**

true if this iterator is greater than the other, false otherwise. 




**Returns:**

false if this iterator is not greater than the other. 





        

<hr>



### function operator&gt;= 

_Greater than or equal to operator for the_ [_**sat\_iterator**_](classastrea_1_1astro_1_1Shell_1_1sat__iterator.md) _._
```C++
inline bool astrea::astro::Shell::sat_iterator::operator>= (
    const  sat_iterator & other
) const
```





**Parameters:**


* `other` The other iterator to compare against. 



**Returns:**

true if this iterator is greater than or equal to the other, false otherwise. 




**Returns:**

false if this iterator is not greater than or equal to the other. 





        

<hr>



### function sat\_iterator 

_Default constructor for_ [_**sat\_iterator**_](classastrea_1_1astro_1_1Shell_1_1sat__iterator.md) _. Initializes the iterator to the beginning of the first plane's spacecraft._
```C++
inline astrea::astro::Shell::sat_iterator::sat_iterator (
    std::vector< Plane < Spacecraft_T > > ::iterator _iterPlane,
    Plane < Spacecraft_T > ::iterator _iterSat
) 
```




<hr>

------------------------------
The documentation for this class was generated from the following file `astrea/astro/astro/platforms/space/Shell.hpp`

