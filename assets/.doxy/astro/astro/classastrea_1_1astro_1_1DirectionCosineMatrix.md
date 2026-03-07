

# Class astrea::astro::DirectionCosineMatrix

**template &lt;typename In\_Frame\_T, typename Out\_Frame\_T&gt;**



[**ClassList**](annotated.md) **>** [**astrea**](namespaceastrea.md) **>** [**astro**](namespaceastrea_1_1astro.md) **>** [**DirectionCosineMatrix**](classastrea_1_1astro_1_1DirectionCosineMatrix.md)



_Class representing a direction cosine matrix (DCM) for transforming vectors between state/frames._ [More...](#detailed-description)

* `#include <DirectionCosineMatrix.hpp>`





































## Public Functions

| Type | Name |
| ---: | :--- |
|   | [**DirectionCosineMatrix**](#function-directioncosinematrix) (const std::array&lt; std::array&lt; Unitless, 3 &gt;, 3 &gt; & matrix) <br>_Constructor for_ [_**DirectionCosineMatrix**_](classastrea_1_1astro_1_1DirectionCosineMatrix.md) _from an array of CartesianVectors._ |
|  [**CartesianVector**](classastrea_1_1astro_1_1CartesianVector.md)&lt; Value\_T, Out\_Frame\_T &gt; | [**operator\***](#function-operator) (const [**CartesianVector**](classastrea_1_1astro_1_1CartesianVector.md)&lt; Value\_T, In\_Frame\_T &gt; & vec) const<br>_Apply the direction cosine matrix to a_ [_**CartesianVector**_](classastrea_1_1astro_1_1CartesianVector.md) _._ |
|  [**CartesianVector**](classastrea_1_1astro_1_1CartesianVector.md)&lt; Unitless, In\_Frame\_T &gt; | [**row**](#function-row) (const std::size\_t & idx) const<br>_Get a specific row of the direction cosine matrix._  |
|  [**DirectionCosineMatrix**](classastrea_1_1astro_1_1DirectionCosineMatrix.md)&lt; Out\_Frame\_T, In\_Frame\_T &gt; | [**transpose**](#function-transpose) () const<br> |


## Public Static Functions

| Type | Name |
| ---: | :--- |
|  [**DirectionCosineMatrix**](classastrea_1_1astro_1_1DirectionCosineMatrix.md)&lt; In\_Frame\_T, Out\_Frame\_T &gt; | [**X**](#function-x) (const Angle & theta) <br>_Creates a direction cosine matrix for a rotation around the X-axis._  |
|  [**DirectionCosineMatrix**](classastrea_1_1astro_1_1DirectionCosineMatrix.md)&lt; In\_Frame\_T, Out\_Frame\_T &gt; | [**XZX**](#function-xzx) (const Angle & alpha, const Angle & beta, const Angle & gamma) <br>_Creates a direction cosine matrix for a rotation around the X-axis followed by a rotation around the Z-axis._  |
|  [**DirectionCosineMatrix**](classastrea_1_1astro_1_1DirectionCosineMatrix.md)&lt; In\_Frame\_T, Out\_Frame\_T &gt; | [**Y**](#function-y) (const Angle & theta) <br>_Creates a direction cosine matrix for a rotation around the Y-axis._  |
|  [**DirectionCosineMatrix**](classastrea_1_1astro_1_1DirectionCosineMatrix.md)&lt; In\_Frame\_T, Out\_Frame\_T &gt; | [**Z**](#function-z) (const Angle & theta) <br>_Creates a direction cosine matrix for a rotation around the Z-axis._  |
|  [**DirectionCosineMatrix**](classastrea_1_1astro_1_1DirectionCosineMatrix.md)&lt; In\_Frame\_T, Out\_Frame\_T &gt; | [**from\_vectors**](#function-from_vectors) (const [**CartesianVector**](classastrea_1_1astro_1_1CartesianVector.md)&lt; Unitless, In\_Frame\_T &gt; & x, const [**CartesianVector**](classastrea_1_1astro_1_1CartesianVector.md)&lt; Unitless, In\_Frame\_T &gt; & y, const [**CartesianVector**](classastrea_1_1astro_1_1CartesianVector.md)&lt; Unitless, In\_Frame\_T &gt; & z) <br>_Creates a direction cosine matrix from three orthonormal vectors._  |
|  [**DirectionCosineMatrix**](classastrea_1_1astro_1_1DirectionCosineMatrix.md)&lt; In\_Frame\_T, Out\_Frame\_T &gt; | [**identity**](#function-identity) () <br> |


























## Detailed Description


This class provides methods to create DCMs for various rotations and to apply them to vectors.




**Template parameters:**


* `Out_Frame_T` The frame type to which the DCM applies. 




    
## Public Functions Documentation




### function DirectionCosineMatrix 

_Constructor for_ [_**DirectionCosineMatrix**_](classastrea_1_1astro_1_1DirectionCosineMatrix.md) _from an array of CartesianVectors._
```C++
inline astrea::astro::DirectionCosineMatrix::DirectionCosineMatrix (
    const std::array< std::array< Unitless, 3 >, 3 > & matrix
) 
```





**Parameters:**


* `matrix` An array containing the three rows of the DCM, each represented as a [**CartesianVector**](classastrea_1_1astro_1_1CartesianVector.md). 




        

<hr>



### function operator\* 

_Apply the direction cosine matrix to a_ [_**CartesianVector**_](classastrea_1_1astro_1_1CartesianVector.md) _._
```C++
template<typename Value_T>
inline CartesianVector < Value_T, Out_Frame_T > astrea::astro::DirectionCosineMatrix::operator* (
    const CartesianVector < Value_T, In_Frame_T > & vec
) const
```





**Template parameters:**


* `Value_T` The type of the vector components. 
* `Frame_T` The frame of the [**CartesianVector**](classastrea_1_1astro_1_1CartesianVector.md). 



**Parameters:**


* `vec` The [**CartesianVector**](classastrea_1_1astro_1_1CartesianVector.md) to which the DCM will be applied. 



**Returns:**

CartesianVector&lt;Value\_T, Out\_Frame\_T&gt; The transformed [**CartesianVector**](classastrea_1_1astro_1_1CartesianVector.md) in the output frame. 





        

<hr>



### function row 

_Get a specific row of the direction cosine matrix._ 
```C++
inline CartesianVector < Unitless, In_Frame_T > astrea::astro::DirectionCosineMatrix::row (
    const std::size_t & idx
) const
```





**Parameters:**


* `idx` The index of the row to retrieve (0, 1, or 2). 



**Returns:**

const CartesianVector&lt;Value\_T, In\_Frame\_T&gt;& The requested row as a [**CartesianVector**](classastrea_1_1astro_1_1CartesianVector.md). 





        

<hr>



### function transpose 

```C++
inline DirectionCosineMatrix < Out_Frame_T, In_Frame_T > astrea::astro::DirectionCosineMatrix::transpose () const
```




<hr>
## Public Static Functions Documentation




### function X 

_Creates a direction cosine matrix for a rotation around the X-axis._ 
```C++
static inline DirectionCosineMatrix < In_Frame_T, Out_Frame_T > astrea::astro::DirectionCosineMatrix::X (
    const Angle & theta
) 
```





**Parameters:**


* `theta` The angle of rotation around the X-axis. 



**Returns:**

DirectionCosineMatrix&lt;Out\_Frame\_T&gt; The resulting direction cosine matrix. 





        

<hr>



### function XZX 

_Creates a direction cosine matrix for a rotation around the X-axis followed by a rotation around the Z-axis._ 
```C++
static inline DirectionCosineMatrix < In_Frame_T, Out_Frame_T > astrea::astro::DirectionCosineMatrix::XZX (
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

DirectionCosineMatrix&lt;Out\_Frame\_T&gt; The resulting direction cosine matrix. 





        

<hr>



### function Y 

_Creates a direction cosine matrix for a rotation around the Y-axis._ 
```C++
static inline DirectionCosineMatrix < In_Frame_T, Out_Frame_T > astrea::astro::DirectionCosineMatrix::Y (
    const Angle & theta
) 
```





**Parameters:**


* `theta` The angle of rotation around the Y-axis. 



**Returns:**

DirectionCosineMatrix&lt;Out\_Frame\_T&gt; The resulting direction cosine matrix. 





        

<hr>



### function Z 

_Creates a direction cosine matrix for a rotation around the Z-axis._ 
```C++
static inline DirectionCosineMatrix < In_Frame_T, Out_Frame_T > astrea::astro::DirectionCosineMatrix::Z (
    const Angle & theta
) 
```





**Parameters:**


* `theta` The angle of rotation around the Z-axis. 



**Returns:**

DirectionCosineMatrix&lt;Out\_Frame\_T&gt; The resulting direction cosine matrix. 





        

<hr>



### function from\_vectors 

_Creates a direction cosine matrix from three orthonormal vectors._ 
```C++
static inline DirectionCosineMatrix < In_Frame_T, Out_Frame_T > astrea::astro::DirectionCosineMatrix::from_vectors (
    const CartesianVector < Unitless, In_Frame_T > & x,
    const CartesianVector < Unitless, In_Frame_T > & y,
    const CartesianVector < Unitless, In_Frame_T > & z
) 
```





**Parameters:**


* `x` The unit vector in the X direction. 
* `y` The unit vector in the Y direction. 
* `z` The unit vector in the Z direction. 



**Returns:**

DirectionCosineMatrix&lt;Out\_Frame\_T&gt; The resulting direction cosine matrix. 





        

<hr>



### function identity 

```C++
static inline DirectionCosineMatrix < In_Frame_T, Out_Frame_T > astrea::astro::DirectionCosineMatrix::identity () 
```




<hr>

------------------------------
The documentation for this class was generated from the following file `astrea/astro/astro/frames/types/DirectionCosineMatrix.hpp`

