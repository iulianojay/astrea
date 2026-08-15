

# Struct astrea::astro::DirectionCosineMatrixRate

**template &lt;IsFrame auto \_in\_frame\_, IsFrame auto \_out\_frame\_&gt;**



[**ClassList**](annotated.md) **>** [**astrea**](namespaceastrea.md) **>** [**astro**](namespaceastrea_1_1astro.md) **>** [**DirectionCosineMatrixRate**](structastrea_1_1astro_1_1DirectionCosineMatrixRate.md)



_Class representing a direction cosine matrix (DCM) for transforming vectors between state/frames._ [More...](#detailed-description)

* `#include <DirectionCosineMatrixRate.hpp>`



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
|  constexpr | [**DirectionCosineMatrixRate**](#function-directioncosinematrixrate-13) (const std::array&lt; Frequency, 9 &gt; & matrix) <br>_Constructor for_ [_**DirectionCosineMatrixRate**_](structastrea_1_1astro_1_1DirectionCosineMatrixRate.md) _from an array of CartesianVectors._ |
|  constexpr | [**DirectionCosineMatrixRate**](#function-directioncosinematrixrate-23) (const std::array&lt; Frequency, 3 &gt; & row1, const std::array&lt; Frequency, 3 &gt; & row2, const std::array&lt; Frequency, 3 &gt; & row3) <br>_Constructor for_ [_**DirectionCosineMatrixRate**_](structastrea_1_1astro_1_1DirectionCosineMatrixRate.md) _from three rows of CartesianVectors._ |
|  constexpr | [**DirectionCosineMatrixRate**](#function-directioncosinematrixrate-33) (const [**DcmInterface**](structastrea_1_1astro_1_1DcmInterface.md)&lt; Frequency, \_in\_frame\_, \_out\_frame\_ &gt; & matrix) <br>_Constructor for_ [_**DirectionCosineMatrixRate**_](structastrea_1_1astro_1_1DirectionCosineMatrixRate.md) _from a_[_**DcmInterface**_](structastrea_1_1astro_1_1DcmInterface.md) _of Frequency._ |
|  constexpr [**DirectionCosineMatrixRate**](structastrea_1_1astro_1_1DirectionCosineMatrixRate.md)&lt; \_out\_frame\_, \_in\_frame\_ &gt; | [**transpose**](#function-transpose) () const<br> |


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
|  constexpr [**DirectionCosineMatrixRate**](structastrea_1_1astro_1_1DirectionCosineMatrixRate.md)&lt; \_in\_frame\_, \_out\_frame\_ &gt; | [**X**](#function-x) (const Angle & theta, const AngularVelocity & thetaDot) <br>_Creates a direction cosine matrix for a rotation around the X-axis._  |
|  constexpr [**DirectionCosineMatrixRate**](structastrea_1_1astro_1_1DirectionCosineMatrixRate.md)&lt; \_in\_frame\_, \_out\_frame\_ &gt; | [**XYX**](#function-xyx) (const Angle & alpha, const Angle & beta, const Angle & gamma, const AngularVelocity & alphaDot, const AngularVelocity & betaDot, const AngularVelocity & gammaDot) <br>_Creates a direction cosine matrix for a rotation around the X-axis, the Y-axis, and the X-axis again._  |
|  constexpr [**DirectionCosineMatrixRate**](structastrea_1_1astro_1_1DirectionCosineMatrixRate.md)&lt; \_in\_frame\_, \_out\_frame\_ &gt; | [**XYZ**](#function-xyz) (const Angle & alpha, const Angle & beta, const Angle & gamma, const AngularVelocity & alphaDot, const AngularVelocity & betaDot, const AngularVelocity & gammaDot) <br>_Creates a direction cosine matrix for a rotation around the X-axis, then Y-axis, then Z-axis._  |
|  constexpr [**DirectionCosineMatrixRate**](structastrea_1_1astro_1_1DirectionCosineMatrixRate.md)&lt; \_in\_frame\_, \_out\_frame\_ &gt; | [**XZX**](#function-xzx) (const Angle & alpha, const Angle & beta, const Angle & gamma, const AngularVelocity & alphaDot, const AngularVelocity & betaDot, const AngularVelocity & gammaDot) <br>_Creates a direction cosine matrix for a rotation around the X-axis, the Z-axis, and the X-axis again._  |
|  constexpr [**DirectionCosineMatrixRate**](structastrea_1_1astro_1_1DirectionCosineMatrixRate.md)&lt; \_in\_frame\_, \_out\_frame\_ &gt; | [**XZY**](#function-xzy) (const Angle & alpha, const Angle & beta, const Angle & gamma, const AngularVelocity & alphaDot, const AngularVelocity & betaDot, const AngularVelocity & gammaDot) <br>_Creates a direction cosine matrix for a rotation around the X-axis, then Z-axis, then Y-axis._  |
|  constexpr [**DirectionCosineMatrixRate**](structastrea_1_1astro_1_1DirectionCosineMatrixRate.md)&lt; \_in\_frame\_, \_out\_frame\_ &gt; | [**Y**](#function-y) (const Angle & theta, const AngularVelocity & thetaDot) <br>_Creates a direction cosine matrix for a rotation around the Y-axis._  |
|  constexpr [**DirectionCosineMatrixRate**](structastrea_1_1astro_1_1DirectionCosineMatrixRate.md)&lt; \_in\_frame\_, \_out\_frame\_ &gt; | [**YXY**](#function-yxy) (const Angle & alpha, const Angle & beta, const Angle & gamma, const AngularVelocity & alphaDot, const AngularVelocity & betaDot, const AngularVelocity & gammaDot) <br>_Creates a direction cosine matrix for a rotation around the Y-axis, the X-axis, and the Y-axis again._  |
|  constexpr [**DirectionCosineMatrixRate**](structastrea_1_1astro_1_1DirectionCosineMatrixRate.md)&lt; \_in\_frame\_, \_out\_frame\_ &gt; | [**YXZ**](#function-yxz) (const Angle & alpha, const Angle & beta, const Angle & gamma, const AngularVelocity & alphaDot, const AngularVelocity & betaDot, const AngularVelocity & gammaDot) <br>_Creates a direction cosine matrix for a rotation around the Y-axis, then X-axis, then Z-axis._  |
|  constexpr [**DirectionCosineMatrixRate**](structastrea_1_1astro_1_1DirectionCosineMatrixRate.md)&lt; \_in\_frame\_, \_out\_frame\_ &gt; | [**YZX**](#function-yzx) (const Angle & alpha, const Angle & beta, const Angle & gamma, const AngularVelocity & alphaDot, const AngularVelocity & betaDot, const AngularVelocity & gammaDot) <br>_Creates a direction cosine matrix for a rotation around the Y-axis, then Z-axis, then X-axis._  |
|  constexpr [**DirectionCosineMatrixRate**](structastrea_1_1astro_1_1DirectionCosineMatrixRate.md)&lt; \_in\_frame\_, \_out\_frame\_ &gt; | [**YZY**](#function-yzy) (const Angle & alpha, const Angle & beta, const Angle & gamma, const AngularVelocity & alphaDot, const AngularVelocity & betaDot, const AngularVelocity & gammaDot) <br>_Creates a direction cosine matrix for a rotation around the Y-axis, the Z-axis, and the Y-axis again._  |
|  constexpr [**DirectionCosineMatrixRate**](structastrea_1_1astro_1_1DirectionCosineMatrixRate.md)&lt; \_in\_frame\_, \_out\_frame\_ &gt; | [**Z**](#function-z) (const Angle & theta, const AngularVelocity & thetaDot) <br>_Creates a direction cosine matrix for a rotation around the Z-axis._  |
|  constexpr [**DirectionCosineMatrixRate**](structastrea_1_1astro_1_1DirectionCosineMatrixRate.md)&lt; \_in\_frame\_, \_out\_frame\_ &gt; | [**ZXY**](#function-zxy) (const Angle & alpha, const Angle & beta, const Angle & gamma, const AngularVelocity & alphaDot, const AngularVelocity & betaDot, const AngularVelocity & gammaDot) <br>_Creates a direction cosine matrix for a rotation around the Z-axis, then X-axis, then Y-axis._  |
|  constexpr [**DirectionCosineMatrixRate**](structastrea_1_1astro_1_1DirectionCosineMatrixRate.md)&lt; \_in\_frame\_, \_out\_frame\_ &gt; | [**ZXZ**](#function-zxz) (const Angle & alpha, const Angle & beta, const Angle & gamma, const AngularVelocity & alphaDot, const AngularVelocity & betaDot, const AngularVelocity & gammaDot) <br>_Creates a direction cosine matrix for a rotation around the Z-axis, the X-axis, and the Z-axis again._  |
|  constexpr [**DirectionCosineMatrixRate**](structastrea_1_1astro_1_1DirectionCosineMatrixRate.md)&lt; \_in\_frame\_, \_out\_frame\_ &gt; | [**ZYX**](#function-zyx) (const Angle & alpha, const Angle & beta, const Angle & gamma, const AngularVelocity & alphaDot, const AngularVelocity & betaDot, const AngularVelocity & gammaDot) <br>_Creates a direction cosine matrix for a rotation around the Z-axis, then Y-axis, then X-axis._  |
|  constexpr [**DirectionCosineMatrixRate**](structastrea_1_1astro_1_1DirectionCosineMatrixRate.md)&lt; \_in\_frame\_, \_out\_frame\_ &gt; | [**ZYZ**](#function-zyz) (const Angle & alpha, const Angle & beta, const Angle & gamma, const AngularVelocity & alphaDot, const AngularVelocity & betaDot, const AngularVelocity & gammaDot) <br>_Creates a direction cosine matrix for a rotation around the Z-axis, the Y-axis, and the Z-axis again._  |
|  constexpr [**DirectionCosineMatrixRate**](structastrea_1_1astro_1_1DirectionCosineMatrixRate.md)&lt; \_in\_frame\_, \_out\_frame\_ &gt; | [**from\_euler\_angles**](#function-from_euler_angles) (const Angle & alpha, const Angle & beta, const Angle & gamma, const AngularVelocity & alphaDot, const AngularVelocity & betaDot, const AngularVelocity & gammaDot) <br>_Creates a direction cosine matrix from Euler angles based on a specified rotation sequence._  |
|  constexpr [**DirectionCosineMatrixRate**](structastrea_1_1astro_1_1DirectionCosineMatrixRate.md) | [**identity**](#function-identity) () <br> |
|  constexpr [**DirectionCosineMatrixRate**](structastrea_1_1astro_1_1DirectionCosineMatrixRate.md) | [**zero**](#function-zero) () <br> |














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




### function DirectionCosineMatrixRate [1/3]

_Constructor for_ [_**DirectionCosineMatrixRate**_](structastrea_1_1astro_1_1DirectionCosineMatrixRate.md) _from an array of CartesianVectors._
```C++
inline constexpr astrea::astro::DirectionCosineMatrixRate::DirectionCosineMatrixRate (
    const std::array< Frequency, 9 > & matrix
) 
```





**Parameters:**


* `matrix` An array containing the three rows of the DCM rate, each represented as a [**CartesianVector**](structastrea_1_1astro_1_1CartesianVector.md). 




        

<hr>



### function DirectionCosineMatrixRate [2/3]

_Constructor for_ [_**DirectionCosineMatrixRate**_](structastrea_1_1astro_1_1DirectionCosineMatrixRate.md) _from three rows of CartesianVectors._
```C++
inline constexpr astrea::astro::DirectionCosineMatrixRate::DirectionCosineMatrixRate (
    const std::array< Frequency, 3 > & row1,
    const std::array< Frequency, 3 > & row2,
    const std::array< Frequency, 3 > & row3
) 
```





**Parameters:**


* `row1` The first row of the DCM rate. 
* `row2` The second row of the DCM rate. 
* `row3` The third row of the DCM rate. 




        

<hr>



### function DirectionCosineMatrixRate [3/3]

_Constructor for_ [_**DirectionCosineMatrixRate**_](structastrea_1_1astro_1_1DirectionCosineMatrixRate.md) _from a_[_**DcmInterface**_](structastrea_1_1astro_1_1DcmInterface.md) _of Frequency._
```C++
inline constexpr astrea::astro::DirectionCosineMatrixRate::DirectionCosineMatrixRate (
    const DcmInterface < Frequency, _in_frame_, _out_frame_ > & matrix
) 
```





**Parameters:**


* `matrix` A [**DcmInterface**](structastrea_1_1astro_1_1DcmInterface.md) containing the elements of the DCM rate. 




        

<hr>



### function transpose 

```C++
inline constexpr DirectionCosineMatrixRate < _out_frame_, _in_frame_ > astrea::astro::DirectionCosineMatrixRate::transpose () const
```




<hr>
## Public Static Functions Documentation




### function X 

_Creates a direction cosine matrix for a rotation around the X-axis._ 
```C++
static inline constexpr DirectionCosineMatrixRate < _in_frame_, _out_frame_ > astrea::astro::DirectionCosineMatrixRate::X (
    const Angle & theta,
    const AngularVelocity & thetaDot
) 
```





**Parameters:**


* `theta` The angle of rotation around the X-axis. 
* `thetaDot` The rate of change of the angle of rotation around the X-axis. 



**Returns:**

[**DirectionCosineMatrixRate**](structastrea_1_1astro_1_1DirectionCosineMatrixRate.md)&lt;_out\_frame_&gt; The resulting direction cosine matrix. 





        

<hr>



### function XYX 

_Creates a direction cosine matrix for a rotation around the X-axis, the Y-axis, and the X-axis again._ 
```C++
static inline constexpr DirectionCosineMatrixRate < _in_frame_, _out_frame_ > astrea::astro::DirectionCosineMatrixRate::XYX (
    const Angle & alpha,
    const Angle & beta,
    const Angle & gamma,
    const AngularVelocity & alphaDot,
    const AngularVelocity & betaDot,
    const AngularVelocity & gammaDot
) 
```





**Parameters:**


* `alpha` The angle of rotation around the X-axis. 
* `beta` The angle of rotation around the Y-axis. 
* `gamma` The angle of rotation around the X-axis. 
* `alphaDot` The rate of change of the angle of rotation around the X-axis. 
* `betaDot` The rate of change of the angle of rotation around the Y-axis. 
* `gammaDot` The rate of change of the angle of rotation around the X-axis. 



**Returns:**

[**DirectionCosineMatrixRate**](structastrea_1_1astro_1_1DirectionCosineMatrixRate.md)&lt;_out\_frame_&gt; The resulting direction cosine matrix. 





        

<hr>



### function XYZ 

_Creates a direction cosine matrix for a rotation around the X-axis, then Y-axis, then Z-axis._ 
```C++
static inline constexpr DirectionCosineMatrixRate < _in_frame_, _out_frame_ > astrea::astro::DirectionCosineMatrixRate::XYZ (
    const Angle & alpha,
    const Angle & beta,
    const Angle & gamma,
    const AngularVelocity & alphaDot,
    const AngularVelocity & betaDot,
    const AngularVelocity & gammaDot
) 
```





**Parameters:**


* `alpha` The angle of rotation around the X-axis. 
* `beta` The angle of rotation around the Y-axis. 
* `gamma` The angle of rotation around the Z-axis. 
* `alphaDot` The rate of change of the angle of rotation around the X-axis. 
* `betaDot` The rate of change of the angle of rotation around the Y-axis. 
* `gammaDot` The rate of change of the angle of rotation around the Z-axis. 



**Returns:**

[**DirectionCosineMatrixRate**](structastrea_1_1astro_1_1DirectionCosineMatrixRate.md)&lt;_out\_frame_&gt; The resulting direction cosine matrix. 





        

<hr>



### function XZX 

_Creates a direction cosine matrix for a rotation around the X-axis, the Z-axis, and the X-axis again._ 
```C++
static inline constexpr DirectionCosineMatrixRate < _in_frame_, _out_frame_ > astrea::astro::DirectionCosineMatrixRate::XZX (
    const Angle & alpha,
    const Angle & beta,
    const Angle & gamma,
    const AngularVelocity & alphaDot,
    const AngularVelocity & betaDot,
    const AngularVelocity & gammaDot
) 
```





**Parameters:**


* `alpha` The angle of rotation around the X-axis. 
* `beta` The angle of rotation around the Z-axis. 
* `gamma` The angle of rotation around the X-axis. 
* `alphaDot` The rate of change of the angle of rotation around the X-axis. 
* `betaDot` The rate of change of the angle of rotation around the Z-axis. 
* `gammaDot` The rate of change of the angle of rotation around the X-axis. 



**Returns:**

[**DirectionCosineMatrixRate**](structastrea_1_1astro_1_1DirectionCosineMatrixRate.md)&lt;_out\_frame_&gt; The resulting direction cosine matrix. 





        

<hr>



### function XZY 

_Creates a direction cosine matrix for a rotation around the X-axis, then Z-axis, then Y-axis._ 
```C++
static inline constexpr DirectionCosineMatrixRate < _in_frame_, _out_frame_ > astrea::astro::DirectionCosineMatrixRate::XZY (
    const Angle & alpha,
    const Angle & beta,
    const Angle & gamma,
    const AngularVelocity & alphaDot,
    const AngularVelocity & betaDot,
    const AngularVelocity & gammaDot
) 
```





**Parameters:**


* `alpha` The angle of rotation around the X-axis. 
* `beta` The angle of rotation around the Z-axis. 
* `gamma` The angle of rotation around the Y-axis. 
* `alphaDot` The rate of change of the angle of rotation around the X-axis. 
* `betaDot` The rate of change of the angle of rotation around the Z-axis. 
* `gammaDot` The rate of change of the angle of rotation around the Y-axis. 



**Returns:**

[**DirectionCosineMatrixRate**](structastrea_1_1astro_1_1DirectionCosineMatrixRate.md)&lt;_out\_frame_&gt; The resulting direction cosine matrix. 





        

<hr>



### function Y 

_Creates a direction cosine matrix for a rotation around the Y-axis._ 
```C++
static inline constexpr DirectionCosineMatrixRate < _in_frame_, _out_frame_ > astrea::astro::DirectionCosineMatrixRate::Y (
    const Angle & theta,
    const AngularVelocity & thetaDot
) 
```





**Parameters:**


* `theta` The angle of rotation around the Y-axis. 
* `thetaDot` The rate of change of the angle of rotation around the Y-axis. 



**Returns:**

[**DirectionCosineMatrixRate**](structastrea_1_1astro_1_1DirectionCosineMatrixRate.md)&lt;_out\_frame_&gt; The resulting direction cosine matrix. 





        

<hr>



### function YXY 

_Creates a direction cosine matrix for a rotation around the Y-axis, the X-axis, and the Y-axis again._ 
```C++
static inline constexpr DirectionCosineMatrixRate < _in_frame_, _out_frame_ > astrea::astro::DirectionCosineMatrixRate::YXY (
    const Angle & alpha,
    const Angle & beta,
    const Angle & gamma,
    const AngularVelocity & alphaDot,
    const AngularVelocity & betaDot,
    const AngularVelocity & gammaDot
) 
```





**Parameters:**


* `alpha` The angle of rotation around the Y-axis. 
* `beta` The angle of rotation around the X-axis. 
* `gamma` The angle of rotation around the Y-axis. 
* `alphaDot` The rate of change of the angle of rotation around the Y-axis. 
* `betaDot` The rate of change of the angle of rotation around the X-axis. 
* `gammaDot` The rate of change of the angle of rotation around the Y-axis. 



**Returns:**

[**DirectionCosineMatrixRate**](structastrea_1_1astro_1_1DirectionCosineMatrixRate.md)&lt;_out\_frame_&gt; The resulting direction cosine matrix. 





        

<hr>



### function YXZ 

_Creates a direction cosine matrix for a rotation around the Y-axis, then X-axis, then Z-axis._ 
```C++
static inline constexpr DirectionCosineMatrixRate < _in_frame_, _out_frame_ > astrea::astro::DirectionCosineMatrixRate::YXZ (
    const Angle & alpha,
    const Angle & beta,
    const Angle & gamma,
    const AngularVelocity & alphaDot,
    const AngularVelocity & betaDot,
    const AngularVelocity & gammaDot
) 
```





**Parameters:**


* `alpha` The angle of rotation around the Y-axis. 
* `beta` The angle of rotation around the X-axis. 
* `gamma` The angle of rotation around the Z-axis. 
* `alphaDot` The rate of change of the angle of rotation around the Y-axis. 
* `betaDot` The rate of change of the angle of rotation around the X-axis. 
* `gammaDot` The rate of change of the angle of rotation around the Z-axis. 



**Returns:**

[**DirectionCosineMatrixRate**](structastrea_1_1astro_1_1DirectionCosineMatrixRate.md)&lt;_out\_frame_&gt; The resulting direction cosine matrix. 





        

<hr>



### function YZX 

_Creates a direction cosine matrix for a rotation around the Y-axis, then Z-axis, then X-axis._ 
```C++
static inline constexpr DirectionCosineMatrixRate < _in_frame_, _out_frame_ > astrea::astro::DirectionCosineMatrixRate::YZX (
    const Angle & alpha,
    const Angle & beta,
    const Angle & gamma,
    const AngularVelocity & alphaDot,
    const AngularVelocity & betaDot,
    const AngularVelocity & gammaDot
) 
```





**Parameters:**


* `alpha` The angle of rotation around the Y-axis. 
* `beta` The angle of rotation around the Z-axis. 
* `gamma` The angle of rotation around the X-axis. 
* `alphaDot` The rate of change of the angle of rotation around the Y-axis. 
* `betaDot` The rate of change of the angle of rotation around the Z-axis. 
* `gammaDot` The rate of change of the angle of rotation around the X-axis. 



**Returns:**

[**DirectionCosineMatrixRate**](structastrea_1_1astro_1_1DirectionCosineMatrixRate.md)&lt;_out\_frame_&gt; The resulting direction cosine matrix. 





        

<hr>



### function YZY 

_Creates a direction cosine matrix for a rotation around the Y-axis, the Z-axis, and the Y-axis again._ 
```C++
static inline constexpr DirectionCosineMatrixRate < _in_frame_, _out_frame_ > astrea::astro::DirectionCosineMatrixRate::YZY (
    const Angle & alpha,
    const Angle & beta,
    const Angle & gamma,
    const AngularVelocity & alphaDot,
    const AngularVelocity & betaDot,
    const AngularVelocity & gammaDot
) 
```





**Parameters:**


* `alpha` The angle of rotation around the Y-axis. 
* `beta` The angle of rotation around the Z-axis. 
* `gamma` The angle of rotation around the Y-axis. 
* `alphaDot` The rate of change of the angle of rotation around the Y-axis. 
* `betaDot` The rate of change of the angle of rotation around the Z-axis. 
* `gammaDot` The rate of change of the angle of rotation around the Y-axis. 



**Returns:**

[**DirectionCosineMatrixRate**](structastrea_1_1astro_1_1DirectionCosineMatrixRate.md)&lt;_out\_frame_&gt; The resulting direction cosine matrix. 





        

<hr>



### function Z 

_Creates a direction cosine matrix for a rotation around the Z-axis._ 
```C++
static inline constexpr DirectionCosineMatrixRate < _in_frame_, _out_frame_ > astrea::astro::DirectionCosineMatrixRate::Z (
    const Angle & theta,
    const AngularVelocity & thetaDot
) 
```





**Parameters:**


* `theta` The angle of rotation around the Z-axis. 
* `thetaDot` The rate of change of the angle of rotation around the Z-axis. 



**Returns:**

[**DirectionCosineMatrixRate**](structastrea_1_1astro_1_1DirectionCosineMatrixRate.md)&lt;_out\_frame_&gt; The resulting direction cosine matrix. 





        

<hr>



### function ZXY 

_Creates a direction cosine matrix for a rotation around the Z-axis, then X-axis, then Y-axis._ 
```C++
static inline constexpr DirectionCosineMatrixRate < _in_frame_, _out_frame_ > astrea::astro::DirectionCosineMatrixRate::ZXY (
    const Angle & alpha,
    const Angle & beta,
    const Angle & gamma,
    const AngularVelocity & alphaDot,
    const AngularVelocity & betaDot,
    const AngularVelocity & gammaDot
) 
```





**Parameters:**


* `alpha` The angle of rotation around the Z-axis. 
* `beta` The angle of rotation around the X-axis. 
* `gamma` The angle of rotation around the Y-axis. 
* `alphaDot` The rate of change of the angle of rotation around the Z-axis. 
* `betaDot` The rate of change of the angle of rotation around the X-axis. 
* `gammaDot` The rate of change of the angle of rotation around the Y-axis. 



**Returns:**

[**DirectionCosineMatrixRate**](structastrea_1_1astro_1_1DirectionCosineMatrixRate.md)&lt;_out\_frame_&gt; The resulting direction cosine matrix. 





        

<hr>



### function ZXZ 

_Creates a direction cosine matrix for a rotation around the Z-axis, the X-axis, and the Z-axis again._ 
```C++
static inline constexpr DirectionCosineMatrixRate < _in_frame_, _out_frame_ > astrea::astro::DirectionCosineMatrixRate::ZXZ (
    const Angle & alpha,
    const Angle & beta,
    const Angle & gamma,
    const AngularVelocity & alphaDot,
    const AngularVelocity & betaDot,
    const AngularVelocity & gammaDot
) 
```





**Parameters:**


* `alpha` The angle of rotation around the Z-axis. 
* `beta` The angle of rotation around the X-axis. 
* `gamma` The angle of rotation around the Z-axis. 
* `alphaDot` The rate of change of the angle of rotation around the Z-axis. 
* `betaDot` The rate of change of the angle of rotation around the X-axis. 
* `gammaDot` The rate of change of the angle of rotation around the Z-axis. 



**Returns:**

[**DirectionCosineMatrixRate**](structastrea_1_1astro_1_1DirectionCosineMatrixRate.md)&lt;_out\_frame_&gt; The resulting direction cosine matrix. 





        

<hr>



### function ZYX 

_Creates a direction cosine matrix for a rotation around the Z-axis, then Y-axis, then X-axis._ 
```C++
static inline constexpr DirectionCosineMatrixRate < _in_frame_, _out_frame_ > astrea::astro::DirectionCosineMatrixRate::ZYX (
    const Angle & alpha,
    const Angle & beta,
    const Angle & gamma,
    const AngularVelocity & alphaDot,
    const AngularVelocity & betaDot,
    const AngularVelocity & gammaDot
) 
```





**Parameters:**


* `alpha` The angle of rotation around the Z-axis. 
* `beta` The angle of rotation around the Y-axis. 
* `gamma` The angle of rotation around the X-axis. 
* `alphaDot` The rate of change of the angle of rotation around the Z-axis. 
* `betaDot` The rate of change of the angle of rotation around the Y-axis. 
* `gammaDot` The rate of change of the angle of rotation around the X-axis. 



**Returns:**

[**DirectionCosineMatrixRate**](structastrea_1_1astro_1_1DirectionCosineMatrixRate.md)&lt;_out\_frame_&gt; The resulting direction cosine matrix. 





        

<hr>



### function ZYZ 

_Creates a direction cosine matrix for a rotation around the Z-axis, the Y-axis, and the Z-axis again._ 
```C++
static inline constexpr DirectionCosineMatrixRate < _in_frame_, _out_frame_ > astrea::astro::DirectionCosineMatrixRate::ZYZ (
    const Angle & alpha,
    const Angle & beta,
    const Angle & gamma,
    const AngularVelocity & alphaDot,
    const AngularVelocity & betaDot,
    const AngularVelocity & gammaDot
) 
```





**Parameters:**


* `alpha` The angle of rotation around the Z-axis. 
* `beta` The angle of rotation around the Y-axis. 
* `gamma` The angle of rotation around the Z-axis. 
* `alphaDot` The rate of change of the angle of rotation around the Z-axis. 
* `betaDot` The rate of change of the angle of rotation around the Y-axis. 
* `gammaDot` The rate of change of the angle of rotation around the Z-axis. 



**Returns:**

[**DirectionCosineMatrixRate**](structastrea_1_1astro_1_1DirectionCosineMatrixRate.md)&lt;_out\_frame_&gt; The resulting direction cosine matrix. 





        

<hr>



### function from\_euler\_angles 

_Creates a direction cosine matrix from Euler angles based on a specified rotation sequence._ 
```C++
template<RotationSequence sequence>
static inline constexpr DirectionCosineMatrixRate < _in_frame_, _out_frame_ > astrea::astro::DirectionCosineMatrixRate::from_euler_angles (
    const Angle & alpha,
    const Angle & beta,
    const Angle & gamma,
    const AngularVelocity & alphaDot,
    const AngularVelocity & betaDot,
    const AngularVelocity & gammaDot
) 
```





**Template parameters:**


* `sequence` The rotation sequence to use for the Euler angles (e.g., XYZ, ZYX, etc.). 



**Parameters:**


* `alpha` The first Euler angle (rotation around the first axis in the sequence). 
* `beta` The second Euler angle (rotation around the second axis in the sequence). 
* `gamma` The third Euler angle (rotation around the third axis in the sequence). 
* `alphaDot` The rate of change of the first Euler angle. 
* `betaDot` The rate of change of the second Euler angle. 
* `gammaDot` The rate of change of the third Euler angle. 



**Returns:**

[**DirectionCosineMatrixRate**](structastrea_1_1astro_1_1DirectionCosineMatrixRate.md)&lt;_out\_frame_&gt; The resulting direction cosine matrix. 





        

<hr>



### function identity 

```C++
static inline constexpr DirectionCosineMatrixRate astrea::astro::DirectionCosineMatrixRate::identity () 
```




<hr>



### function zero 

```C++
static inline constexpr DirectionCosineMatrixRate astrea::astro::DirectionCosineMatrixRate::zero () 
```




<hr>

------------------------------
The documentation for this class was generated from the following file `astrea/astro/astro/frames/framework/DirectionCosineMatrixRate.hpp`

