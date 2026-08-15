

# Struct astrea::astro::DirectionCosineMatrix

**template &lt;IsFrame auto \_in\_frame\_, IsFrame auto \_out\_frame\_&gt;**



[**ClassList**](annotated.md) **>** [**astrea**](namespaceastrea.md) **>** [**astro**](namespaceastrea_1_1astro.md) **>** [**DirectionCosineMatrix**](classastrea_1_1astro_1_1DirectionCosineMatrix.md)



_Class representing a direction cosine matrix (DCM) for transforming vectors between state/frames._ [More...](#detailed-description)

* `#include <DirectionCosineMatrix.hpp>`



Inherits the following classes: [astrea::astro::DcmInterface](structastrea_1_1astro_1_1DcmInterface.md)




























## Public Static Attributes inherited from astrea::astro::DcmInterface

See [astrea::astro::DcmInterface](structastrea_1_1astro_1_1DcmInterface.md)

| Type | Name |
| ---: | :--- |
|  constexpr auto | [**in\_frame**](structastrea_1_1astro_1_1DcmInterface.md#variable-in_frame)   = `\_in\_frame\_`<br>_The input frame of the matrix._  |
|  constexpr auto | [**out\_frame**](structastrea_1_1astro_1_1DcmInterface.md#variable-out_frame)   = `\_out\_frame\_`<br>_The output frame of the matrix._  |


























## Public Functions

| Type | Name |
| ---: | :--- |
|  constexpr | [**DirectionCosineMatrix**](#function-directioncosinematrix-15) (const std::array&lt; Unitless, 9 &gt; & matrix) <br>_Constructor for_ [_**DirectionCosineMatrix**_](classastrea_1_1astro_1_1DirectionCosineMatrix.md) _from an array of CartesianVectors._ |
|  constexpr | [**DirectionCosineMatrix**](#function-directioncosinematrix-25) (const std::array&lt; Unitless, 3 &gt; & row1, const std::array&lt; Unitless, 3 &gt; & row2, const std::array&lt; Unitless, 3 &gt; & row3) <br>_Constructor for_ [_**DirectionCosineMatrix**_](classastrea_1_1astro_1_1DirectionCosineMatrix.md) _from an array of CartesianVectors._ |
|  constexpr | [**DirectionCosineMatrix**](#function-directioncosinematrix-35) (const [**DcmInterface**](structastrea_1_1astro_1_1DcmInterface.md)&lt; Unitless, \_in\_frame\_, \_out\_frame\_ &gt; & matrix) <br> |
|  constexpr | [**DirectionCosineMatrix**](#function-directioncosinematrix-45) (const [**DirectionCosineMatrix**](classastrea_1_1astro_1_1DirectionCosineMatrix.md)&lt; in\_frame\_u, out\_frame\_u &gt; & other) <br> |
|  constexpr | [**DirectionCosineMatrix**](#function-directioncosinematrix-55) ([**DirectionCosineMatrix**](classastrea_1_1astro_1_1DirectionCosineMatrix.md)&lt; in\_frame\_u, out\_frame\_u &gt; && other) <br> |
|  constexpr [**DirectionCosineMatrix**](classastrea_1_1astro_1_1DirectionCosineMatrix.md)&lt; \_out\_frame\_, \_in\_frame\_ &gt; | [**transpose**](#function-transpose) () const<br> |


## Public Functions inherited from astrea::astro::DcmInterface

See [astrea::astro::DcmInterface](structastrea_1_1astro_1_1DcmInterface.md)

| Type | Name |
| ---: | :--- |
|  constexpr | [**DcmInterface**](structastrea_1_1astro_1_1DcmInterface.md#function-dcminterface-25) (const std::array&lt; Value\_T, 9 &gt; & matrix) <br>_Constructor for_ [_**DcmInterface**_](structastrea_1_1astro_1_1DcmInterface.md) _from an array of values._ |
|  constexpr | [**DcmInterface**](structastrea_1_1astro_1_1DcmInterface.md#function-dcminterface-35) (const std::array&lt; Value\_T, 3 &gt; & row1, const std::array&lt; Value\_T, 3 &gt; & row2, const std::array&lt; Value\_T, 3 &gt; & row3) <br>_Constructor for_ [_**DcmInterface**_](structastrea_1_1astro_1_1DcmInterface.md) _from three rows represented as arrays._ |
|  constexpr | [**DcmInterface**](structastrea_1_1astro_1_1DcmInterface.md#function-dcminterface-45) (const [**DcmInterface**](structastrea_1_1astro_1_1DcmInterface.md)&lt; Value\_U, in\_frame\_u, out\_frame\_u &gt; & matrix) <br> |
|  constexpr | [**DcmInterface**](structastrea_1_1astro_1_1DcmInterface.md#function-dcminterface-55) ([**DcmInterface**](structastrea_1_1astro_1_1DcmInterface.md)&lt; Value\_U, in\_frame\_u, out\_frame\_u &gt; && matrix) <br> |
|  constexpr std::array&lt; Value\_T, 9 &gt; | [**data**](structastrea_1_1astro_1_1DcmInterface.md#function-data) () const<br>_Get the underlying data of the matrix as an array._  |
|  constexpr Value\_T | [**determinant**](structastrea_1_1astro_1_1DcmInterface.md#function-determinant) () const<br>_Get the determinant of the matrix._  |
|  constexpr void | [**normalize**](structastrea_1_1astro_1_1DcmInterface.md#function-normalize) () <br>_Normalizes the matrix to ensure it represents a valid rotation._  |
|  constexpr [**DcmInterface**](structastrea_1_1astro_1_1DcmInterface.md)&lt; decltype(Value\_T{} \*Value\_U{}), [**in\_frame**](structastrea_1_1astro_1_1DcmInterface.md#variable-in_frame), [**out\_frame**](structastrea_1_1astro_1_1DcmInterface.md#variable-out_frame) &gt; | [**operator\***](structastrea_1_1astro_1_1DcmInterface.md#function-operator) (const [**DcmInterface**](structastrea_1_1astro_1_1DcmInterface.md)&lt; Value\_U, in\_frame\_u, out\_frame\_u &gt; & other) const<br>_Compose two direction matrices (matrix multiplication)._  |
|  constexpr [**DcmInterface**](structastrea_1_1astro_1_1DcmInterface.md)&lt; decltype(Value\_T{} \*Value\_U{}), [**in\_frame**](structastrea_1_1astro_1_1DcmInterface.md#variable-in_frame), out\_frame\_u &gt; | [**operator\***](structastrea_1_1astro_1_1DcmInterface.md#function-operator_1) (const [**DcmInterface**](structastrea_1_1astro_1_1DcmInterface.md)&lt; Value\_U, in\_frame\_u, out\_frame\_u &gt; & other) const<br>_Compose two direction matrices (matrix multiplication)._  |
|  constexpr [**CartesianVector**](structastrea_1_1astro_1_1CartesianVector.md)&lt; decltype(Value\_T{} \*Value\_U{}), [**out\_frame**](structastrea_1_1astro_1_1DcmInterface.md#variable-out_frame) &gt; | [**operator\***](structastrea_1_1astro_1_1DcmInterface.md#function-operator_2) (const [**CartesianVector**](structastrea_1_1astro_1_1CartesianVector.md)&lt; Value\_U, in\_frame\_u &gt; & vec) const<br>_Multiply this matrix by a_ [_**Cartesian**_](classastrea_1_1astro_1_1Cartesian.md) _vector._ |
|  constexpr [**DcmInterface**](structastrea_1_1astro_1_1DcmInterface.md)&lt; decltype(Value\_T{} \*Value\_U{}), [**in\_frame**](structastrea_1_1astro_1_1DcmInterface.md#variable-in_frame), [**out\_frame**](structastrea_1_1astro_1_1DcmInterface.md#variable-out_frame) &gt; | [**operator\***](structastrea_1_1astro_1_1DcmInterface.md#function-operator_3) (const Value\_U & scalar) const<br>_Multiply the matrix by a scalar value (element-wise multiplication)._  |
|  constexpr [**DcmInterface**](structastrea_1_1astro_1_1DcmInterface.md) | [**operator+**](structastrea_1_1astro_1_1DcmInterface.md#function-operator_4) (const [**DcmInterface**](structastrea_1_1astro_1_1DcmInterface.md)&lt; Value\_U, in\_frame\_u, out\_frame\_u &gt; & other) const<br>_Add two matrices together (element-wise addition)._  |
|  constexpr [**DcmInterface**](structastrea_1_1astro_1_1DcmInterface.md) | [**operator-**](structastrea_1_1astro_1_1DcmInterface.md#function-operator-) () const<br>_Negate the matrix (element-wise negation)._  |
|  constexpr [**DcmInterface**](structastrea_1_1astro_1_1DcmInterface.md) | [**operator-**](structastrea_1_1astro_1_1DcmInterface.md#function-operator-_1) (const [**DcmInterface**](structastrea_1_1astro_1_1DcmInterface.md)&lt; Value\_U, in\_frame\_u, out\_frame\_u &gt; & other) const<br>_Subtract another matrix from this one (element-wise subtraction)._  |
|  constexpr Value\_T & | [**operator[]**](structastrea_1_1astro_1_1DcmInterface.md#function-operator_5) (std::size\_t row, std::size\_t col) <br>_Access operator for the elements of the matrix._  |
|  constexpr const Value\_T & | [**operator[]**](structastrea_1_1astro_1_1DcmInterface.md#function-operator_6) (std::size\_t row, std::size\_t col) const<br>_Const access operator for the elements of the matrix._  |
|  constexpr [**CartesianVector**](structastrea_1_1astro_1_1CartesianVector.md)&lt; Value\_T, \_in\_frame\_ &gt; | [**row**](structastrea_1_1astro_1_1DcmInterface.md#function-row) (const std::size\_t & idx) const<br>_Get a specific row of the matrix as a_ [_**Cartesian**_](classastrea_1_1astro_1_1Cartesian.md) _vector._ |
|  constexpr Value\_T | [**trace**](structastrea_1_1astro_1_1DcmInterface.md#function-trace) () const<br>_Get the trace of the matrix (the sum of the diagonal elements)._  |
|  constexpr [**DcmInterface**](structastrea_1_1astro_1_1DcmInterface.md)&lt; Value\_T, \_out\_frame\_, \_in\_frame\_ &gt; | [**transpose**](structastrea_1_1astro_1_1DcmInterface.md#function-transpose) () const<br>_Transposes the matrix, effectively inverting the transformation._  |


## Public Static Functions

| Type | Name |
| ---: | :--- |
|  constexpr [**DirectionCosineMatrix**](classastrea_1_1astro_1_1DirectionCosineMatrix.md)&lt; \_in\_frame\_, \_out\_frame\_ &gt; | [**X**](#function-x) (const Angle & theta) <br>_Creates a direction cosine matrix for a rotation around the X-axis._  |
|  constexpr [**DirectionCosineMatrix**](classastrea_1_1astro_1_1DirectionCosineMatrix.md)&lt; \_in\_frame\_, \_out\_frame\_ &gt; | [**XYX**](#function-xyx) (const Angle & alpha, const Angle & beta, const Angle & gamma) <br>_Creates a direction cosine matrix for a rotation around the X-axis, the Y-axis, and the X-axis again._  |
|  constexpr [**DirectionCosineMatrix**](classastrea_1_1astro_1_1DirectionCosineMatrix.md)&lt; \_in\_frame\_, \_out\_frame\_ &gt; | [**XYZ**](#function-xyz) (const Angle & alpha, const Angle & beta, const Angle & gamma) <br>_Creates a direction cosine matrix for a rotation around the X-axis, then Y-axis, then Z-axis._  |
|  constexpr [**DirectionCosineMatrix**](classastrea_1_1astro_1_1DirectionCosineMatrix.md)&lt; \_in\_frame\_, \_out\_frame\_ &gt; | [**XZX**](#function-xzx) (const Angle & alpha, const Angle & beta, const Angle & gamma) <br>_Creates a direction cosine matrix for a rotation around the X-axis, the Z-axis, and the X-axis again._  |
|  constexpr [**DirectionCosineMatrix**](classastrea_1_1astro_1_1DirectionCosineMatrix.md)&lt; \_in\_frame\_, \_out\_frame\_ &gt; | [**XZY**](#function-xzy) (const Angle & alpha, const Angle & beta, const Angle & gamma) <br>_Creates a direction cosine matrix for a rotation around the X-axis, then Z-axis, then Y-axis._  |
|  constexpr [**DirectionCosineMatrix**](classastrea_1_1astro_1_1DirectionCosineMatrix.md)&lt; \_in\_frame\_, \_out\_frame\_ &gt; | [**Y**](#function-y) (const Angle & theta) <br>_Creates a direction cosine matrix for a rotation around the Y-axis._  |
|  constexpr [**DirectionCosineMatrix**](classastrea_1_1astro_1_1DirectionCosineMatrix.md)&lt; \_in\_frame\_, \_out\_frame\_ &gt; | [**YXY**](#function-yxy) (const Angle & alpha, const Angle & beta, const Angle & gamma) <br>_Creates a direction cosine matrix for a rotation around the Y-axis, the X-axis, and the Y-axis again._  |
|  constexpr [**DirectionCosineMatrix**](classastrea_1_1astro_1_1DirectionCosineMatrix.md)&lt; \_in\_frame\_, \_out\_frame\_ &gt; | [**YXZ**](#function-yxz) (const Angle & alpha, const Angle & beta, const Angle & gamma) <br>_Creates a direction cosine matrix for a rotation around the Y-axis, then X-axis, then Z-axis._  |
|  constexpr [**DirectionCosineMatrix**](classastrea_1_1astro_1_1DirectionCosineMatrix.md)&lt; \_in\_frame\_, \_out\_frame\_ &gt; | [**YZX**](#function-yzx) (const Angle & alpha, const Angle & beta, const Angle & gamma) <br>_Creates a direction cosine matrix for a rotation around the Y-axis, then Z-axis, then X-axis._  |
|  constexpr [**DirectionCosineMatrix**](classastrea_1_1astro_1_1DirectionCosineMatrix.md)&lt; \_in\_frame\_, \_out\_frame\_ &gt; | [**YZY**](#function-yzy) (const Angle & alpha, const Angle & beta, const Angle & gamma) <br>_Creates a direction cosine matrix for a rotation around the Y-axis, the Z-axis, and the Y-axis again._  |
|  constexpr [**DirectionCosineMatrix**](classastrea_1_1astro_1_1DirectionCosineMatrix.md)&lt; \_in\_frame\_, \_out\_frame\_ &gt; | [**Z**](#function-z) (const Angle & theta) <br>_Creates a direction cosine matrix for a rotation around the Z-axis._  |
|  constexpr [**DirectionCosineMatrix**](classastrea_1_1astro_1_1DirectionCosineMatrix.md)&lt; \_in\_frame\_, \_out\_frame\_ &gt; | [**ZXY**](#function-zxy) (const Angle & alpha, const Angle & beta, const Angle & gamma) <br>_Creates a direction cosine matrix for a rotation around the Z-axis, then X-axis, then Y-axis._  |
|  constexpr [**DirectionCosineMatrix**](classastrea_1_1astro_1_1DirectionCosineMatrix.md)&lt; \_in\_frame\_, \_out\_frame\_ &gt; | [**ZXZ**](#function-zxz) (const Angle & alpha, const Angle & beta, const Angle & gamma) <br>_Creates a direction cosine matrix for a rotation around the Z-axis, the X-axis, and the Z-axis again._  |
|  constexpr [**DirectionCosineMatrix**](classastrea_1_1astro_1_1DirectionCosineMatrix.md)&lt; \_in\_frame\_, \_out\_frame\_ &gt; | [**ZYX**](#function-zyx) (const Angle & alpha, const Angle & beta, const Angle & gamma) <br>_Creates a direction cosine matrix for a rotation around the Z-axis, then Y-axis, then X-axis._  |
|  constexpr [**DirectionCosineMatrix**](classastrea_1_1astro_1_1DirectionCosineMatrix.md)&lt; \_in\_frame\_, \_out\_frame\_ &gt; | [**ZYZ**](#function-zyz) (const Angle & alpha, const Angle & beta, const Angle & gamma) <br>_Creates a direction cosine matrix for a rotation around the Z-axis, the Y-axis, and the Z-axis again._  |
|  constexpr [**DirectionCosineMatrix**](classastrea_1_1astro_1_1DirectionCosineMatrix.md)&lt; \_in\_frame\_, \_out\_frame\_ &gt; | [**from\_euler\_angles**](#function-from_euler_angles) (const Angle & alpha, const Angle & beta, const Angle & gamma) <br>_Creates a direction cosine matrix from Euler angles based on a specified rotation sequence._  |
|  constexpr [**DirectionCosineMatrix**](classastrea_1_1astro_1_1DirectionCosineMatrix.md)&lt; \_in\_frame\_, \_out\_frame\_ &gt; | [**from\_vectors**](#function-from_vectors) (const [**CartesianVector**](structastrea_1_1astro_1_1CartesianVector.md)&lt; Unitless, \_in\_frame\_ &gt; & x, const [**CartesianVector**](structastrea_1_1astro_1_1CartesianVector.md)&lt; Unitless, \_in\_frame\_ &gt; & y, const [**CartesianVector**](structastrea_1_1astro_1_1CartesianVector.md)&lt; Unitless, \_in\_frame\_ &gt; & z) <br>_Creates a direction cosine matrix from three orthonormal vectors._  |
|  constexpr [**DirectionCosineMatrix**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) | [**identity**](#function-identity) () <br> |
|  constexpr [**DirectionCosineMatrix**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) | [**zero**](#function-zero) () <br> |














## Protected Attributes inherited from astrea::astro::DcmInterface

See [astrea::astro::DcmInterface](structastrea_1_1astro_1_1DcmInterface.md)

| Type | Name |
| ---: | :--- |
|  std::array&lt; Value\_T, 9 &gt; | [**\_data**](structastrea_1_1astro_1_1DcmInterface.md#variable-_data)  <br>_3x3 matrix to hold the direction cosines._  |
































## Protected Functions inherited from astrea::astro::DcmInterface

See [astrea::astro::DcmInterface](structastrea_1_1astro_1_1DcmInterface.md)

| Type | Name |
| ---: | :--- |
|  std::array&lt; decltype(Value\_T{} \*Value\_U{}), 9 &gt; | [**\_multiply**](structastrea_1_1astro_1_1DcmInterface.md#function-_multiply) (const std::array&lt; Value\_U, 9 &gt; & other) const<br> |
|  constexpr void | [**\_normalize**](structastrea_1_1astro_1_1DcmInterface.md#function-_normalize) (const Unitless & scale) <br>_Normalizes the matrix by scaling all elements by the given factor._  |




## Protected Static Functions inherited from astrea::astro::DcmInterface

See [astrea::astro::DcmInterface](structastrea_1_1astro_1_1DcmInterface.md)

| Type | Name |
| ---: | :--- |
|  constexpr [**DcmInterface**](structastrea_1_1astro_1_1DcmInterface.md) | [**identity**](structastrea_1_1astro_1_1DcmInterface.md#function-identity) () <br>_Creates an identity matrix (no rotation)._  |
|  constexpr [**DcmInterface**](structastrea_1_1astro_1_1DcmInterface.md) | [**zero**](structastrea_1_1astro_1_1DcmInterface.md#function-zero) () <br>_Creates a zero matrix (invalid rotation)._  |


## Detailed Description


This class provides methods to create DCMs for various rotations and to apply them to vectors.




**Template parameters:**


* `_out_frame_` The frame type to which the DCM applies. 




    
## Public Functions Documentation




### function DirectionCosineMatrix [1/5]

_Constructor for_ [_**DirectionCosineMatrix**_](classastrea_1_1astro_1_1DirectionCosineMatrix.md) _from an array of CartesianVectors._
```C++
inline constexpr astrea::astro::DirectionCosineMatrix::DirectionCosineMatrix (
    const std::array< Unitless, 9 > & matrix
) 
```





**Parameters:**


* `matrix` An array containing the three rows of the DCM, each represented as a [**CartesianVector**](structastrea_1_1astro_1_1CartesianVector.md). 




        

<hr>



### function DirectionCosineMatrix [2/5]

_Constructor for_ [_**DirectionCosineMatrix**_](classastrea_1_1astro_1_1DirectionCosineMatrix.md) _from an array of CartesianVectors._
```C++
inline constexpr astrea::astro::DirectionCosineMatrix::DirectionCosineMatrix (
    const std::array< Unitless, 3 > & row1,
    const std::array< Unitless, 3 > & row2,
    const std::array< Unitless, 3 > & row3
) 
```





**Parameters:**


* `row1` An array containing the three elements of the first row of the DCM. 
* `row2` An array containing the three elements of the second row of the DCM. 
* `row3` An array containing the three elements of the third row of the DCM. 




        

<hr>



### function DirectionCosineMatrix [3/5]

```C++
inline constexpr astrea::astro::DirectionCosineMatrix::DirectionCosineMatrix (
    const DcmInterface < Unitless, _in_frame_, _out_frame_ > & matrix
) 
```




<hr>



### function DirectionCosineMatrix [4/5]

```C++
template<IsFrame auto in_frame_u, IsFrame auto out_frame_u>
inline constexpr astrea::astro::DirectionCosineMatrix::DirectionCosineMatrix (
    const DirectionCosineMatrix < in_frame_u, out_frame_u > & other
) 
```




<hr>



### function DirectionCosineMatrix [5/5]

```C++
template<IsFrame auto in_frame_u, IsFrame auto out_frame_u>
inline constexpr astrea::astro::DirectionCosineMatrix::DirectionCosineMatrix (
    DirectionCosineMatrix < in_frame_u, out_frame_u > && other
) 
```




<hr>



### function transpose 

```C++
inline constexpr DirectionCosineMatrix < _out_frame_, _in_frame_ > astrea::astro::DirectionCosineMatrix::transpose () const
```




<hr>
## Public Static Functions Documentation




### function X 

_Creates a direction cosine matrix for a rotation around the X-axis._ 
```C++
static inline constexpr DirectionCosineMatrix < _in_frame_, _out_frame_ > astrea::astro::DirectionCosineMatrix::X (
    const Angle & theta
) 
```





**Parameters:**


* `theta` The angle of rotation around the X-axis. 



**Returns:**

[**DirectionCosineMatrix**](classastrea_1_1astro_1_1DirectionCosineMatrix.md)&lt;_out\_frame_&gt; The resulting direction cosine matrix. 





        

<hr>



### function XYX 

_Creates a direction cosine matrix for a rotation around the X-axis, the Y-axis, and the X-axis again._ 
```C++
static inline constexpr DirectionCosineMatrix < _in_frame_, _out_frame_ > astrea::astro::DirectionCosineMatrix::XYX (
    const Angle & alpha,
    const Angle & beta,
    const Angle & gamma
) 
```





**Parameters:**


* `alpha` The angle of rotation around the X-axis. 
* `beta` The angle of rotation around the Y-axis. 
* `gamma` The angle of rotation around the X-axis. 



**Returns:**

[**DirectionCosineMatrix**](classastrea_1_1astro_1_1DirectionCosineMatrix.md)&lt;_out\_frame_&gt; The resulting direction cosine matrix. 





        

<hr>



### function XYZ 

_Creates a direction cosine matrix for a rotation around the X-axis, then Y-axis, then Z-axis._ 
```C++
static inline constexpr DirectionCosineMatrix < _in_frame_, _out_frame_ > astrea::astro::DirectionCosineMatrix::XYZ (
    const Angle & alpha,
    const Angle & beta,
    const Angle & gamma
) 
```





**Parameters:**


* `alpha` The angle of rotation around the X-axis. 
* `beta` The angle of rotation around the Y-axis. 
* `gamma` The angle of rotation around the Z-axis. 



**Returns:**

[**DirectionCosineMatrix**](classastrea_1_1astro_1_1DirectionCosineMatrix.md)&lt;_out\_frame_&gt; The resulting direction cosine matrix. 





        

<hr>



### function XZX 

_Creates a direction cosine matrix for a rotation around the X-axis, the Z-axis, and the X-axis again._ 
```C++
static inline constexpr DirectionCosineMatrix < _in_frame_, _out_frame_ > astrea::astro::DirectionCosineMatrix::XZX (
    const Angle & alpha,
    const Angle & beta,
    const Angle & gamma
) 
```





**Parameters:**


* `alpha` The angle of rotation around the X-axis. 
* `beta` The angle of rotation around the Z-axis. 
* `gamma` The angle of rotation around the X-axis. 



**Returns:**

[**DirectionCosineMatrix**](classastrea_1_1astro_1_1DirectionCosineMatrix.md)&lt;_out\_frame_&gt; The resulting direction cosine matrix. 





        

<hr>



### function XZY 

_Creates a direction cosine matrix for a rotation around the X-axis, then Z-axis, then Y-axis._ 
```C++
static inline constexpr DirectionCosineMatrix < _in_frame_, _out_frame_ > astrea::astro::DirectionCosineMatrix::XZY (
    const Angle & alpha,
    const Angle & beta,
    const Angle & gamma
) 
```





**Parameters:**


* `alpha` The angle of rotation around the X-axis. 
* `beta` The angle of rotation around the Z-axis. 
* `gamma` The angle of rotation around the Y-axis. 



**Returns:**

[**DirectionCosineMatrix**](classastrea_1_1astro_1_1DirectionCosineMatrix.md)&lt;_out\_frame_&gt; The resulting direction cosine matrix. 





        

<hr>



### function Y 

_Creates a direction cosine matrix for a rotation around the Y-axis._ 
```C++
static inline constexpr DirectionCosineMatrix < _in_frame_, _out_frame_ > astrea::astro::DirectionCosineMatrix::Y (
    const Angle & theta
) 
```





**Parameters:**


* `theta` The angle of rotation around the Y-axis. 



**Returns:**

[**DirectionCosineMatrix**](classastrea_1_1astro_1_1DirectionCosineMatrix.md)&lt;_out\_frame_&gt; The resulting direction cosine matrix. 





        

<hr>



### function YXY 

_Creates a direction cosine matrix for a rotation around the Y-axis, the X-axis, and the Y-axis again._ 
```C++
static inline constexpr DirectionCosineMatrix < _in_frame_, _out_frame_ > astrea::astro::DirectionCosineMatrix::YXY (
    const Angle & alpha,
    const Angle & beta,
    const Angle & gamma
) 
```





**Parameters:**


* `alpha` The angle of rotation around the Y-axis. 
* `beta` The angle of rotation around the X-axis. 
* `gamma` The angle of rotation around the Y-axis. 



**Returns:**

[**DirectionCosineMatrix**](classastrea_1_1astro_1_1DirectionCosineMatrix.md)&lt;_out\_frame_&gt; The resulting direction cosine matrix. 





        

<hr>



### function YXZ 

_Creates a direction cosine matrix for a rotation around the Y-axis, then X-axis, then Z-axis._ 
```C++
static inline constexpr DirectionCosineMatrix < _in_frame_, _out_frame_ > astrea::astro::DirectionCosineMatrix::YXZ (
    const Angle & alpha,
    const Angle & beta,
    const Angle & gamma
) 
```





**Parameters:**


* `alpha` The angle of rotation around the Y-axis. 
* `beta` The angle of rotation around the X-axis. 
* `gamma` The angle of rotation around the Z-axis. 



**Returns:**

[**DirectionCosineMatrix**](classastrea_1_1astro_1_1DirectionCosineMatrix.md)&lt;_out\_frame_&gt; The resulting direction cosine matrix. 





        

<hr>



### function YZX 

_Creates a direction cosine matrix for a rotation around the Y-axis, then Z-axis, then X-axis._ 
```C++
static inline constexpr DirectionCosineMatrix < _in_frame_, _out_frame_ > astrea::astro::DirectionCosineMatrix::YZX (
    const Angle & alpha,
    const Angle & beta,
    const Angle & gamma
) 
```





**Parameters:**


* `alpha` The angle of rotation around the Y-axis. 
* `beta` The angle of rotation around the Z-axis. 
* `gamma` The angle of rotation around the X-axis. 



**Returns:**

[**DirectionCosineMatrix**](classastrea_1_1astro_1_1DirectionCosineMatrix.md)&lt;_out\_frame_&gt; The resulting direction cosine matrix. 





        

<hr>



### function YZY 

_Creates a direction cosine matrix for a rotation around the Y-axis, the Z-axis, and the Y-axis again._ 
```C++
static inline constexpr DirectionCosineMatrix < _in_frame_, _out_frame_ > astrea::astro::DirectionCosineMatrix::YZY (
    const Angle & alpha,
    const Angle & beta,
    const Angle & gamma
) 
```





**Parameters:**


* `alpha` The angle of rotation around the Y-axis. 
* `beta` The angle of rotation around the Z-axis. 
* `gamma` The angle of rotation around the Y-axis. 



**Returns:**

[**DirectionCosineMatrix**](classastrea_1_1astro_1_1DirectionCosineMatrix.md)&lt;_out\_frame_&gt; The resulting direction cosine matrix. 





        

<hr>



### function Z 

_Creates a direction cosine matrix for a rotation around the Z-axis._ 
```C++
static inline constexpr DirectionCosineMatrix < _in_frame_, _out_frame_ > astrea::astro::DirectionCosineMatrix::Z (
    const Angle & theta
) 
```





**Parameters:**


* `theta` The angle of rotation around the Z-axis. 



**Returns:**

[**DirectionCosineMatrix**](classastrea_1_1astro_1_1DirectionCosineMatrix.md)&lt;_out\_frame_&gt; The resulting direction cosine matrix. 





        

<hr>



### function ZXY 

_Creates a direction cosine matrix for a rotation around the Z-axis, then X-axis, then Y-axis._ 
```C++
static inline constexpr DirectionCosineMatrix < _in_frame_, _out_frame_ > astrea::astro::DirectionCosineMatrix::ZXY (
    const Angle & alpha,
    const Angle & beta,
    const Angle & gamma
) 
```





**Parameters:**


* `alpha` The angle of rotation around the Z-axis. 
* `beta` The angle of rotation around the X-axis. 
* `gamma` The angle of rotation around the Y-axis. 



**Returns:**

[**DirectionCosineMatrix**](classastrea_1_1astro_1_1DirectionCosineMatrix.md)&lt;_out\_frame_&gt; The resulting direction cosine matrix. 





        

<hr>



### function ZXZ 

_Creates a direction cosine matrix for a rotation around the Z-axis, the X-axis, and the Z-axis again._ 
```C++
static inline constexpr DirectionCosineMatrix < _in_frame_, _out_frame_ > astrea::astro::DirectionCosineMatrix::ZXZ (
    const Angle & alpha,
    const Angle & beta,
    const Angle & gamma
) 
```





**Parameters:**


* `alpha` The angle of rotation around the Z-axis. 
* `beta` The angle of rotation around the X-axis. 
* `gamma` The angle of rotation around the Z-axis. 



**Returns:**

[**DirectionCosineMatrix**](classastrea_1_1astro_1_1DirectionCosineMatrix.md)&lt;_out\_frame_&gt; The resulting direction cosine matrix. 





        

<hr>



### function ZYX 

_Creates a direction cosine matrix for a rotation around the Z-axis, then Y-axis, then X-axis._ 
```C++
static inline constexpr DirectionCosineMatrix < _in_frame_, _out_frame_ > astrea::astro::DirectionCosineMatrix::ZYX (
    const Angle & alpha,
    const Angle & beta,
    const Angle & gamma
) 
```





**Parameters:**


* `alpha` The angle of rotation around the Z-axis. 
* `beta` The angle of rotation around the Y-axis. 
* `gamma` The angle of rotation around the X-axis. 



**Returns:**

[**DirectionCosineMatrix**](classastrea_1_1astro_1_1DirectionCosineMatrix.md)&lt;_out\_frame_&gt; The resulting direction cosine matrix. 





        

<hr>



### function ZYZ 

_Creates a direction cosine matrix for a rotation around the Z-axis, the Y-axis, and the Z-axis again._ 
```C++
static inline constexpr DirectionCosineMatrix < _in_frame_, _out_frame_ > astrea::astro::DirectionCosineMatrix::ZYZ (
    const Angle & alpha,
    const Angle & beta,
    const Angle & gamma
) 
```





**Parameters:**


* `alpha` The angle of rotation around the Z-axis. 
* `beta` The angle of rotation around the Y-axis. 
* `gamma` The angle of rotation around the Z-axis. 



**Returns:**

[**DirectionCosineMatrix**](classastrea_1_1astro_1_1DirectionCosineMatrix.md)&lt;_out\_frame_&gt; The resulting direction cosine matrix. 





        

<hr>



### function from\_euler\_angles 

_Creates a direction cosine matrix from Euler angles based on a specified rotation sequence._ 
```C++
template<RotationSequence sequence>
static inline constexpr DirectionCosineMatrix < _in_frame_, _out_frame_ > astrea::astro::DirectionCosineMatrix::from_euler_angles (
    const Angle & alpha,
    const Angle & beta,
    const Angle & gamma
) 
```





**Template parameters:**


* `sequence` The rotation sequence to use for the Euler angles (e.g., XYZ, ZYX, etc.). 



**Parameters:**


* `alpha` The first Euler angle (rotation around the first axis in the sequence). 
* `beta` The second Euler angle (rotation around the second axis in the sequence). 
* `gamma` The third Euler angle (rotation around the third axis in the sequence). 



**Returns:**

[**DirectionCosineMatrix**](classastrea_1_1astro_1_1DirectionCosineMatrix.md)&lt;_out\_frame_&gt; The resulting direction cosine matrix. 





        

<hr>



### function from\_vectors 

_Creates a direction cosine matrix from three orthonormal vectors._ 
```C++
static inline constexpr DirectionCosineMatrix < _in_frame_, _out_frame_ > astrea::astro::DirectionCosineMatrix::from_vectors (
    const CartesianVector < Unitless, _in_frame_ > & x,
    const CartesianVector < Unitless, _in_frame_ > & y,
    const CartesianVector < Unitless, _in_frame_ > & z
) 
```





**Parameters:**


* `x` The unit vector in the X direction. 
* `y` The unit vector in the Y direction. 
* `z` The unit vector in the Z direction. 



**Returns:**

[**DirectionCosineMatrix**](classastrea_1_1astro_1_1DirectionCosineMatrix.md)&lt;_out\_frame_&gt; The resulting direction cosine matrix. 





        

<hr>



### function identity 

```C++
static inline constexpr DirectionCosineMatrix astrea::astro::DirectionCosineMatrix::identity () 
```




<hr>



### function zero 

```C++
static inline constexpr DirectionCosineMatrix astrea::astro::DirectionCosineMatrix::zero () 
```




<hr>

------------------------------
The documentation for this class was generated from the following file `astrea/astro/astro/frames/framework/DirectionCosineMatrix.hpp`

