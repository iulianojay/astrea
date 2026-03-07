

# Class astrea::astro::CartesianVector

**template &lt;class Value\_T, class Frame\_T&gt;**



[**ClassList**](annotated.md) **>** [**astrea**](namespaceastrea.md) **>** [**astro**](namespaceastrea_1_1astro.md) **>** [**CartesianVector**](classastrea_1_1astro_1_1CartesianVector.md)



_Class representing a 3D vector in_ [_**Cartesian**_](classastrea_1_1astro_1_1Cartesian.md) _coordinates._[More...](#detailed-description)

* `#include <CartesianVector.hpp>`





































## Public Functions

| Type | Name |
| ---: | :--- |
|   | [**CartesianVector**](#function-cartesianvector-13) (const Value\_T & x=Value\_T(), const Value\_T & y=Value\_T(), const Value\_T & z=Value\_T()) <br>_Default constructor for_ [_**CartesianVector**_](classastrea_1_1astro_1_1CartesianVector.md) _._ |
|   | [**CartesianVector**](#function-cartesianvector-23) (const [**CartesianVector**](classastrea_1_1astro_1_1CartesianVector.md)&lt; Value\_T, Frame\_U &gt; & other) = delete<br> |
|   | [**CartesianVector**](#function-cartesianvector-33) ([**CartesianVector**](classastrea_1_1astro_1_1CartesianVector.md)&lt; Value\_T, Frame\_U &gt; && other) = delete<br> |
|  [**CartesianVector**](classastrea_1_1astro_1_1CartesianVector.md)&lt; Value\_T, Frame\_U &gt; | [**force\_frame\_conversion**](#function-force_frame_conversion) () const<br>_Copy constructor for_ [_**CartesianVector**_](classastrea_1_1astro_1_1CartesianVector.md) _that implicitly converts the frame._ |
|  [**CartesianVector**](classastrea_1_1astro_1_1CartesianVector.md)&lt; Value\_T, Frame\_T &gt; | [**operator=**](#function-operator) (const [**CartesianVector**](classastrea_1_1astro_1_1CartesianVector.md)&lt; Value\_T, Frame\_U &gt; & other) = delete<br> |
|  [**CartesianVector**](classastrea_1_1astro_1_1CartesianVector.md)&lt; Value\_T, Frame\_T &gt; | [**operator=**](#function-operator_1) ([**CartesianVector**](classastrea_1_1astro_1_1CartesianVector.md)&lt; Value\_T, Frame\_U &gt; && other) = delete<br> |
|  bool | [**operator==**](#function-operator_2) (const [**CartesianVector**](classastrea_1_1astro_1_1CartesianVector.md)&lt; Value\_U, Frame\_T &gt; & other) const<br>_Equality operator for_ [_**CartesianVector**_](classastrea_1_1astro_1_1CartesianVector.md) _._ |
|  Value\_T & | [**operator[]**](#function-operator_3) (size\_t index) <br>_Access operator for vector components._  |
|  const Value\_T & | [**operator[]**](#function-operator_4) (size\_t index) const<br>_Const access operator for vector components._  |
|   | [**requires**](#function-requires) (!std::is\_same&lt; Frame\_T, Frame\_U &gt;::value) <br>_Inequality operator for_ [_**CartesianVector**_](classastrea_1_1astro_1_1CartesianVector.md) _in a different frame. Always false._ |




























## Detailed Description


This class encapsulates a vector with three components (x, y, z) and provides various operations such as addition, subtraction, scalar multiplication, and dot/cross products.




**Template parameters:**


* `T` The type of the vector components (e.g., Distance, Velocity). 




    
## Public Functions Documentation




### function CartesianVector [1/3]

_Default constructor for_ [_**CartesianVector**_](classastrea_1_1astro_1_1CartesianVector.md) _._
```C++
inline astrea::astro::CartesianVector::CartesianVector (
    const Value_T & x=Value_T(),
    const Value_T & y=Value_T(),
    const Value_T & z=Value_T()
) 
```



Initializes the vector components to zero. 

**Parameters:**


* `x` The x component of the vector (default is 0). 
* `y` The y component of the vector (default is 0). 
* `z` The z component of the vector (default is 0). 




        

<hr>



### function CartesianVector [2/3]

```C++
template<typename Frame_U>
astrea::astro::CartesianVector::CartesianVector (
    const CartesianVector < Value_T, Frame_U > & other
) = delete
```




<hr>



### function CartesianVector [3/3]

```C++
template<typename Frame_U>
astrea::astro::CartesianVector::CartesianVector (
    CartesianVector < Value_T, Frame_U > && other
) = delete
```




<hr>



### function force\_frame\_conversion 

_Copy constructor for_ [_**CartesianVector**_](classastrea_1_1astro_1_1CartesianVector.md) _that implicitly converts the frame._
```C++
template<typename Frame_U>
inline CartesianVector < Value_T, Frame_U > astrea::astro::CartesianVector::force_frame_conversion () const
```





**Parameters:**


* `other` The other [**CartesianVector**](classastrea_1_1astro_1_1CartesianVector.md) to copy from. 




        

<hr>



### function operator= 

```C++
template<typename Frame_U>
CartesianVector < Value_T, Frame_T > astrea::astro::CartesianVector::operator= (
    const CartesianVector < Value_T, Frame_U > & other
) = delete
```




<hr>



### function operator= 

```C++
template<typename Frame_U>
CartesianVector < Value_T, Frame_T > astrea::astro::CartesianVector::operator= (
    CartesianVector < Value_T, Frame_U > && other
) = delete
```




<hr>



### function operator== 

_Equality operator for_ [_**CartesianVector**_](classastrea_1_1astro_1_1CartesianVector.md) _._
```C++
template<typename Value_U>
inline bool astrea::astro::CartesianVector::operator== (
    const CartesianVector < Value_U, Frame_T > & other
) const
```





**Parameters:**


* `other` The other [**CartesianVector**](classastrea_1_1astro_1_1CartesianVector.md) to compare with. 



**Returns:**

true If the two vectors are equal. 




**Returns:**

false If the two vectors are not equal. 





        

<hr>



### function operator[] 

_Access operator for vector components._ 
```C++
inline Value_T & astrea::astro::CartesianVector::operator[] (
    size_t index
) 
```





**Parameters:**


* `index` The index of the component to access (0 for x, 1 for y, 2 for z). 



**Returns:**

Value\_T& Reference to the component at the specified index. 





        

<hr>



### function operator[] 

_Const access operator for vector components._ 
```C++
inline const Value_T & astrea::astro::CartesianVector::operator[] (
    size_t index
) const
```





**Parameters:**


* `index` The index of the component to access (0 for x, 1 for y, 2 for z). 



**Returns:**

const Value\_T& Reference to the component at the specified index. 





        

<hr>



### function requires 

_Inequality operator for_ [_**CartesianVector**_](classastrea_1_1astro_1_1CartesianVector.md) _in a different frame. Always false._
```C++
template<typename Frame_U>
astrea::astro::CartesianVector::requires (
    !std::is_same< Frame_T, Frame_U >::value
) 
```





**Parameters:**


* `other` The other [**CartesianVector**](classastrea_1_1astro_1_1CartesianVector.md) to compare with. 



**Returns:**

true If the two vectors are not equal. 




**Returns:**

false If the two vectors are equal. Array to hold the x, y, and z components of the vector. 





        

<hr>

------------------------------
The documentation for this class was generated from the following file `astrea/astro/astro/frames/CartesianVector.hpp`

