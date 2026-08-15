

# Struct astrea::astro::DcmInterface

**template &lt;typename Value\_T, IsFrame auto \_in\_frame\_, IsFrame auto \_out\_frame\_&gt;**



[**ClassList**](annotated.md) **>** [**astrea**](namespaceastrea.md) **>** [**astro**](namespaceastrea_1_1astro.md) **>** [**DcmInterface**](structastrea_1_1astro_1_1DcmInterface.md)



_Class representing a 3x3 matrix, used for matrices and their rates/accelerations._ [More...](#detailed-description)

* `#include <DcmInterface.hpp>`























## Public Static Attributes

| Type | Name |
| ---: | :--- |
|  constexpr auto | [**in\_frame**](#variable-in_frame)   = `\_in\_frame\_`<br>_The input frame of the matrix._  |
|  constexpr auto | [**out\_frame**](#variable-out_frame)   = `\_out\_frame\_`<br>_The output frame of the matrix._  |














## Public Functions

| Type | Name |
| ---: | :--- |
|  constexpr | [**DcmInterface**](#function-dcminterface-25) (const std::array&lt; Value\_T, 9 &gt; & matrix) <br>_Constructor for_ [_**DcmInterface**_](structastrea_1_1astro_1_1DcmInterface.md) _from an array of values._ |
|  constexpr | [**DcmInterface**](#function-dcminterface-35) (const std::array&lt; Value\_T, 3 &gt; & row1, const std::array&lt; Value\_T, 3 &gt; & row2, const std::array&lt; Value\_T, 3 &gt; & row3) <br>_Constructor for_ [_**DcmInterface**_](structastrea_1_1astro_1_1DcmInterface.md) _from three rows represented as arrays._ |
|  constexpr | [**DcmInterface**](#function-dcminterface-45) (const [**DcmInterface**](structastrea_1_1astro_1_1DcmInterface.md)&lt; Value\_U, in\_frame\_u, out\_frame\_u &gt; & matrix) <br> |
|  constexpr | [**DcmInterface**](#function-dcminterface-55) ([**DcmInterface**](structastrea_1_1astro_1_1DcmInterface.md)&lt; Value\_U, in\_frame\_u, out\_frame\_u &gt; && matrix) <br> |
|  constexpr std::array&lt; Value\_T, 9 &gt; | [**data**](#function-data) () const<br>_Get the underlying data of the matrix as an array._  |
|  constexpr Value\_T | [**determinant**](#function-determinant) () const<br>_Get the determinant of the matrix._  |
|  constexpr void | [**normalize**](#function-normalize) () <br>_Normalizes the matrix to ensure it represents a valid rotation._  |
|  constexpr [**DcmInterface**](structastrea_1_1astro_1_1DcmInterface.md)&lt; decltype(Value\_T{} \*Value\_U{}), [**in\_frame**](structastrea_1_1astro_1_1DcmInterface.md#variable-in_frame), [**out\_frame**](structastrea_1_1astro_1_1DcmInterface.md#variable-out_frame) &gt; | [**operator\***](#function-operator) (const [**DcmInterface**](structastrea_1_1astro_1_1DcmInterface.md)&lt; Value\_U, in\_frame\_u, out\_frame\_u &gt; & other) const<br>_Compose two direction matrices (matrix multiplication)._  |
|  constexpr [**DcmInterface**](structastrea_1_1astro_1_1DcmInterface.md)&lt; decltype(Value\_T{} \*Value\_U{}), [**in\_frame**](structastrea_1_1astro_1_1DcmInterface.md#variable-in_frame), out\_frame\_u &gt; | [**operator\***](#function-operator_1) (const [**DcmInterface**](structastrea_1_1astro_1_1DcmInterface.md)&lt; Value\_U, in\_frame\_u, out\_frame\_u &gt; & other) const<br>_Compose two direction matrices (matrix multiplication)._  |
|  constexpr [**CartesianVector**](structastrea_1_1astro_1_1CartesianVector.md)&lt; decltype(Value\_T{} \*Value\_U{}), [**out\_frame**](structastrea_1_1astro_1_1DcmInterface.md#variable-out_frame) &gt; | [**operator\***](#function-operator_2) (const [**CartesianVector**](structastrea_1_1astro_1_1CartesianVector.md)&lt; Value\_U, in\_frame\_u &gt; & vec) const<br>_Multiply this matrix by a_ [_**Cartesian**_](classastrea_1_1astro_1_1Cartesian.md) _vector._ |
|  constexpr [**DcmInterface**](structastrea_1_1astro_1_1DcmInterface.md)&lt; decltype(Value\_T{} \*Value\_U{}), [**in\_frame**](structastrea_1_1astro_1_1DcmInterface.md#variable-in_frame), [**out\_frame**](structastrea_1_1astro_1_1DcmInterface.md#variable-out_frame) &gt; | [**operator\***](#function-operator_3) (const Value\_U & scalar) const<br>_Multiply the matrix by a scalar value (element-wise multiplication)._  |
|  constexpr [**DcmInterface**](structastrea_1_1astro_1_1DcmInterface.md) | [**operator+**](#function-operator_4) (const [**DcmInterface**](structastrea_1_1astro_1_1DcmInterface.md)&lt; Value\_U, in\_frame\_u, out\_frame\_u &gt; & other) const<br>_Add two matrices together (element-wise addition)._  |
|  constexpr [**DcmInterface**](structastrea_1_1astro_1_1DcmInterface.md) | [**operator-**](#function-operator-) () const<br>_Negate the matrix (element-wise negation)._  |
|  constexpr [**DcmInterface**](structastrea_1_1astro_1_1DcmInterface.md) | [**operator-**](#function-operator-_1) (const [**DcmInterface**](structastrea_1_1astro_1_1DcmInterface.md)&lt; Value\_U, in\_frame\_u, out\_frame\_u &gt; & other) const<br>_Subtract another matrix from this one (element-wise subtraction)._  |
|  constexpr Value\_T & | [**operator[]**](#function-operator_5) (std::size\_t row, std::size\_t col) <br>_Access operator for the elements of the matrix._  |
|  constexpr const Value\_T & | [**operator[]**](#function-operator_6) (std::size\_t row, std::size\_t col) const<br>_Const access operator for the elements of the matrix._  |
|  constexpr [**CartesianVector**](structastrea_1_1astro_1_1CartesianVector.md)&lt; Value\_T, \_in\_frame\_ &gt; | [**row**](#function-row) (const std::size\_t & idx) const<br>_Get a specific row of the matrix as a_ [_**Cartesian**_](classastrea_1_1astro_1_1Cartesian.md) _vector._ |
|  constexpr Value\_T | [**trace**](#function-trace) () const<br>_Get the trace of the matrix (the sum of the diagonal elements)._  |
|  constexpr [**DcmInterface**](structastrea_1_1astro_1_1DcmInterface.md)&lt; Value\_T, \_out\_frame\_, \_in\_frame\_ &gt; | [**transpose**](#function-transpose) () const<br>_Transposes the matrix, effectively inverting the transformation._  |








## Protected Attributes

| Type | Name |
| ---: | :--- |
|  std::array&lt; Value\_T, 9 &gt; | [**\_data**](#variable-_data)  <br>_3x3 matrix to hold the direction cosines._  |
















## Protected Functions

| Type | Name |
| ---: | :--- |
|  std::array&lt; decltype(Value\_T{} \*Value\_U{}), 9 &gt; | [**\_multiply**](#function-_multiply) (const std::array&lt; Value\_U, 9 &gt; & other) const<br> |
|  constexpr void | [**\_normalize**](#function-_normalize) (const Unitless & scale) <br>_Normalizes the matrix by scaling all elements by the given factor._  |


## Protected Static Functions

| Type | Name |
| ---: | :--- |
|  constexpr [**DcmInterface**](structastrea_1_1astro_1_1DcmInterface.md) | [**identity**](#function-identity) () <br>_Creates an identity matrix (no rotation)._  |
|  constexpr [**DcmInterface**](structastrea_1_1astro_1_1DcmInterface.md) | [**zero**](#function-zero) () <br>_Creates a zero matrix (invalid rotation)._  |


## Detailed Description




**Note:**

I didn't generalize this matrix definition and I'm not going to 





    
## Public Static Attributes Documentation




### variable in\_frame 

_The input frame of the matrix._ 
```C++
constexpr auto astrea::astro::DcmInterface< Value_T, _in_frame_, _out_frame_ >::in_frame;
```




<hr>



### variable out\_frame 

_The output frame of the matrix._ 
```C++
constexpr auto astrea::astro::DcmInterface< Value_T, _in_frame_, _out_frame_ >::out_frame;
```




<hr>
## Public Functions Documentation




### function DcmInterface [2/5]

_Constructor for_ [_**DcmInterface**_](structastrea_1_1astro_1_1DcmInterface.md) _from an array of values._
```C++
inline constexpr astrea::astro::DcmInterface::DcmInterface (
    const std::array< Value_T, 9 > & matrix
) 
```





**Parameters:**


* `matrix` An array containing the nine elements of the matrix in row-major order. 




        

<hr>



### function DcmInterface [3/5]

_Constructor for_ [_**DcmInterface**_](structastrea_1_1astro_1_1DcmInterface.md) _from three rows represented as arrays._
```C++
inline constexpr astrea::astro::DcmInterface::DcmInterface (
    const std::array< Value_T, 3 > & row1,
    const std::array< Value_T, 3 > & row2,
    const std::array< Value_T, 3 > & row3
) 
```





**Parameters:**


* `row1` An array containing the three elements of the first row of the matrix. 
* `row2` An array containing the three elements of the second row of the matrix. 
* `row3` An array containing the three elements of the third row of the matrix. 




        

<hr>



### function DcmInterface [4/5]

```C++
template<typename Value_U, auto in_frame_u, auto out_frame_u>
inline constexpr astrea::astro::DcmInterface::DcmInterface (
    const DcmInterface < Value_U, in_frame_u, out_frame_u > & matrix
) 
```




<hr>



### function DcmInterface [5/5]

```C++
template<typename Value_U, auto in_frame_u, auto out_frame_u>
inline constexpr astrea::astro::DcmInterface::DcmInterface (
    DcmInterface < Value_U, in_frame_u, out_frame_u > && matrix
) 
```




<hr>



### function data 

_Get the underlying data of the matrix as an array._ 
```C++
inline constexpr std::array< Value_T, 9 > astrea::astro::DcmInterface::data () const
```





**Returns:**

std::array&lt;Value\_T, 9&gt; The elements of the matrix in row-major order. 





        

<hr>



### function determinant 

_Get the determinant of the matrix._ 
```C++
inline constexpr Value_T astrea::astro::DcmInterface::determinant () const
```





**Returns:**

Value\_T The determinant of the matrix. 





        

<hr>



### function normalize 

_Normalizes the matrix to ensure it represents a valid rotation._ 
```C++
inline constexpr void astrea::astro::DcmInterface::normalize () 
```



This method scales the elements of the matrix so that the determinant is 1, which is a requirement for a valid rotation matrix. If the determinant is zero, an exception is thrown since the matrix cannot be normalized. Uses a linear approximation when the determinant is close to 1 for numerical efficiency. 


        

<hr>



### function operator\* 

_Compose two direction matrices (matrix multiplication)._ 
```C++
template<typename Value_U, auto in_frame_u, auto out_frame_u>
inline constexpr DcmInterface < decltype(Value_T{} *Value_U{}), in_frame , out_frame > astrea::astro::DcmInterface::operator* (
    const DcmInterface < Value_U, in_frame_u, out_frame_u > & other
) const
```



Note: This overload is identically-framed matrices so the output frame is the same as the input frame.




**Template parameters:**


* `_newout_frame` The output frame of the right-hand-side matrix. 



**Parameters:**


* `other` The right-hand-side matrix to compose with. 



**Returns:**

[**DcmInterface**](structastrea_1_1astro_1_1DcmInterface.md) The composed matrix. 





        

<hr>



### function operator\* 

_Compose two direction matrices (matrix multiplication)._ 
```C++
template<typename Value_U, auto in_frame_u, auto out_frame_u>
inline constexpr DcmInterface < decltype(Value_T{} *Value_U{}), in_frame , out_frame_u > astrea::astro::DcmInterface::operator* (
    const DcmInterface < Value_U, in_frame_u, out_frame_u > & other
) const
```



Note: This overload is for stacked rotations where mat\_1^2 \* mat\_2^3 -&gt; mat\_1^3




**Template parameters:**


* `_newout_frame` The output frame of the right-hand-side matrix. 



**Parameters:**


* `other` The right-hand-side matrix to compose with. 



**Returns:**

[**DcmInterface**](structastrea_1_1astro_1_1DcmInterface.md) The composed matrix. 





        

<hr>



### function operator\* 

_Multiply this matrix by a_ [_**Cartesian**_](classastrea_1_1astro_1_1Cartesian.md) _vector._
```C++
template<typename Value_U, auto in_frame_u>
inline constexpr CartesianVector < decltype(Value_T{} *Value_U{}), out_frame > astrea::astro::DcmInterface::operator* (
    const CartesianVector < Value_U, in_frame_u > & vec
) const
```





**Template parameters:**


* `Value_U` The type of the elements in the [**Cartesian**](classastrea_1_1astro_1_1Cartesian.md) vector. 
* `in_frame_u` The input frame of the [**Cartesian**](classastrea_1_1astro_1_1Cartesian.md) vector. 



**Parameters:**


* `vec` The [**Cartesian**](classastrea_1_1astro_1_1Cartesian.md) vector to multiply the matrix by. 



**Returns:**

[**CartesianVector**](structastrea_1_1astro_1_1CartesianVector.md) The resulting vector from the multiplication. 





        

<hr>



### function operator\* 

_Multiply the matrix by a scalar value (element-wise multiplication)._ 
```C++
template<typename Value_U>
inline constexpr DcmInterface < decltype(Value_T{} *Value_U{}), in_frame , out_frame > astrea::astro::DcmInterface::operator* (
    const Value_U & scalar
) const
```





**Parameters:**


* `scalar` The scalar value to multiply the matrix by. 



**Returns:**

[**DcmInterface**](structastrea_1_1astro_1_1DcmInterface.md) The resulting matrix from the scalar multiplication. 





        

<hr>



### function operator+ 

_Add two matrices together (element-wise addition)._ 
```C++
template<typename Value_U, auto in_frame_u, auto out_frame_u>
inline constexpr DcmInterface astrea::astro::DcmInterface::operator+ (
    const DcmInterface < Value_U, in_frame_u, out_frame_u > & other
) const
```





**Parameters:**


* `other` The matrix to add to this one. 



**Returns:**

[**DcmInterface**](structastrea_1_1astro_1_1DcmInterface.md) The resulting matrix from the addition. 





        

<hr>



### function operator- 

_Negate the matrix (element-wise negation)._ 
```C++
inline constexpr DcmInterface astrea::astro::DcmInterface::operator- () const
```





**Returns:**

[**DcmInterface**](structastrea_1_1astro_1_1DcmInterface.md) The resulting negated matrix. 





        

<hr>



### function operator- 

_Subtract another matrix from this one (element-wise subtraction)._ 
```C++
template<typename Value_U, auto in_frame_u, auto out_frame_u>
inline constexpr DcmInterface astrea::astro::DcmInterface::operator- (
    const DcmInterface < Value_U, in_frame_u, out_frame_u > & other
) const
```





**Parameters:**


* `other` The matrix to subtract from this one. 



**Returns:**

[**DcmInterface**](structastrea_1_1astro_1_1DcmInterface.md) The resulting matrix from the subtraction. 





        

<hr>



### function operator[] 

_Access operator for the elements of the matrix._ 
```C++
inline constexpr Value_T & astrea::astro::DcmInterface::operator[] (
    std::size_t row,
    std::size_t col
) 
```





**Parameters:**


* `row` The row index (0, 1, or 2). 
* `col` The column index (0, 1, or 2). 



**Returns:**

Value\_T& Reference to the element at the specified row and column. 





        

<hr>



### function operator[] 

_Const access operator for the elements of the matrix._ 
```C++
inline constexpr const Value_T & astrea::astro::DcmInterface::operator[] (
    std::size_t row,
    std::size_t col
) const
```





**Parameters:**


* `row` The row index (0, 1, or 2). 
* `col` The column index (0, 1, or 2). 



**Returns:**

const Value\_T& Reference to the element at the specified row and column. 





        

<hr>



### function row 

_Get a specific row of the matrix as a_ [_**Cartesian**_](classastrea_1_1astro_1_1Cartesian.md) _vector._
```C++
inline constexpr CartesianVector < Value_T, _in_frame_ > astrea::astro::DcmInterface::row (
    const std::size_t & idx
) const
```





**Parameters:**


* `idx` The index of the row to retrieve (0, 1, or 2). 



**Returns:**

const [**CartesianVector**](structastrea_1_1astro_1_1CartesianVector.md)&lt;Value\_T, _in\_frame_&gt;& The requested row as a [**Cartesian**](classastrea_1_1astro_1_1Cartesian.md) vector. 





        

<hr>



### function trace 

_Get the trace of the matrix (the sum of the diagonal elements)._ 
```C++
inline constexpr Value_T astrea::astro::DcmInterface::trace () const
```





**Returns:**

Value\_T The trace of the matrix. 





        

<hr>



### function transpose 

_Transposes the matrix, effectively inverting the transformation._ 
```C++
inline constexpr DcmInterface < Value_T, _out_frame_, _in_frame_ > astrea::astro::DcmInterface::transpose () const
```





**Returns:**

[**DcmInterface**](structastrea_1_1astro_1_1DcmInterface.md) The transposed matrix. 





        

<hr>
## Protected Attributes Documentation




### variable \_data 

_3x3 matrix to hold the direction cosines._ 
```C++
std::array<Value_T, 9> astrea::astro::DcmInterface< Value_T, _in_frame_, _out_frame_ >::_data;
```




<hr>
## Protected Functions Documentation




### function \_multiply 

```C++
template<typename Value_U>
inline std::array< decltype(Value_T{} *Value_U{}), 9 > astrea::astro::DcmInterface::_multiply (
    const std::array< Value_U, 9 > & other
) const
```




<hr>



### function \_normalize 

_Normalizes the matrix by scaling all elements by the given factor._ 
```C++
inline constexpr void astrea::astro::DcmInterface::_normalize (
    const Unitless & scale
) 
```





**Parameters:**


* `scale` The factor to scale the matrix elements by to achieve normalization. 




        

<hr>
## Protected Static Functions Documentation




### function identity 

_Creates an identity matrix (no rotation)._ 
```C++
static inline constexpr DcmInterface astrea::astro::DcmInterface::identity () 
```





**Returns:**

[**DcmInterface**](structastrea_1_1astro_1_1DcmInterface.md) The identity matrix. 





        

<hr>



### function zero 

_Creates a zero matrix (invalid rotation)._ 
```C++
static inline constexpr DcmInterface astrea::astro::DcmInterface::zero () 
```





**Returns:**

[**DcmInterface**](structastrea_1_1astro_1_1DcmInterface.md) The zero matrix. 





        

<hr>## Friends Documentation





### friend DcmInterface [1/5]

```C++
template<typename Value_U, IsFrame auto in_frame_u, IsFrame auto out_frame_u>
struct astrea::astro::DcmInterface::DcmInterface (
    DcmInterface
) 
```




<hr>



### friend operator&lt;&lt; 

```C++
inline std::ostream & astrea::astro::DcmInterface::operator<< (
    std::ostream & os,
    const DcmInterface & matrix
) 
```




<hr>

------------------------------
The documentation for this class was generated from the following file `astrea/astro/astro/frames/framework/DcmInterface.hpp`

