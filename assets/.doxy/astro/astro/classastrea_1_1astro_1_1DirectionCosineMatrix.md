

# Struct astrea::astro::DirectionCosineMatrix

**template &lt;IsFrame [**auto**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) \_in\_frame\_, IsFrame [**auto**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) \_out\_frame\_&gt;**



[**ClassList**](annotated.md) **>** [**astrea**](namespaceastrea.md) **>** [**astro**](namespaceastrea_1_1astro.md) **>** [**DirectionCosineMatrix**](classastrea_1_1astro_1_1DirectionCosineMatrix.md)



_Class representing a direction cosine matrix (DCM) for transforming vectors between state/frames._ [More...](#detailed-description)

* `#include <DirectionCosineMatrix.hpp>`



Inherits the following classes: [astrea::astro::DcmInterface](structastrea_1_1astro_1_1DcmInterface.md)




























## Public Static Attributes inherited from astrea::astro::DcmInterface

See [astrea::astro::DcmInterface](structastrea_1_1astro_1_1DcmInterface.md)

| Type | Name |
| ---: | :--- |
|  [**constexpr**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) [**auto**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) | [**in\_frame**](structastrea_1_1astro_1_1DcmInterface.md#variable-in_frame)   = `[**\_in\_frame\_**](classastrea_1_1astro_1_1DirectionCosineMatrix.md)`<br>_The input frame of the matrix._  |
|  [**constexpr**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) [**auto**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) | [**out\_frame**](structastrea_1_1astro_1_1DcmInterface.md#variable-out_frame)   = `[**\_out\_frame\_**](classastrea_1_1astro_1_1DirectionCosineMatrix.md)`<br>_The output frame of the matrix._  |


























## Public Functions

| Type | Name |
| ---: | :--- |
|  [**constexpr**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) | [**DirectionCosineMatrix**](#function-directioncosinematrix-13) ([**const**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) std::array&lt; [**Unitless**](classastrea_1_1astro_1_1DirectionCosineMatrix.md), 9 &gt; & matrix) <br>_Constructor for_ [_**DirectionCosineMatrix**_](classastrea_1_1astro_1_1DirectionCosineMatrix.md) _from an array of CartesianVectors._ |
|  [**constexpr**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) | [**DirectionCosineMatrix**](#function-directioncosinematrix-23) ([**const**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) std::array&lt; [**Unitless**](classastrea_1_1astro_1_1DirectionCosineMatrix.md), 3 &gt; & row1, [**const**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) std::array&lt; [**Unitless**](classastrea_1_1astro_1_1DirectionCosineMatrix.md), 3 &gt; & row2, [**const**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) std::array&lt; [**Unitless**](classastrea_1_1astro_1_1DirectionCosineMatrix.md), 3 &gt; & row3) <br>_Constructor for_ [_**DirectionCosineMatrix**_](classastrea_1_1astro_1_1DirectionCosineMatrix.md) _from an array of CartesianVectors._ |
|  [**constexpr**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) | [**DirectionCosineMatrix**](#function-directioncosinematrix-33) ([**const**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) [**DcmInterface**](structastrea_1_1astro_1_1DcmInterface.md)&lt; [**Unitless**](classastrea_1_1astro_1_1DirectionCosineMatrix.md), [**\_in\_frame\_**](classastrea_1_1astro_1_1DirectionCosineMatrix.md), [**\_out\_frame\_**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) &gt; & matrix) <br> |
|  [**constexpr**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) [**DirectionCosineMatrix**](classastrea_1_1astro_1_1DirectionCosineMatrix.md)&lt; [**\_out\_frame\_**](classastrea_1_1astro_1_1DirectionCosineMatrix.md), [**\_in\_frame\_**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) &gt; | [**transpose**](#function-transpose) () const<br> |


## Public Functions inherited from astrea::astro::DcmInterface

See [astrea::astro::DcmInterface](structastrea_1_1astro_1_1DcmInterface.md)

| Type | Name |
| ---: | :--- |
|  [**constexpr**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) | [**DcmInterface**](structastrea_1_1astro_1_1DcmInterface.md#function-dcminterface-14) ([**const**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) std::array&lt; [**Value\_T**](classastrea_1_1astro_1_1DirectionCosineMatrix.md), 9 &gt; & matrix) <br>_Constructor for_ [_**DcmInterface**_](structastrea_1_1astro_1_1DcmInterface.md) _from an array of values._ |
|  [**constexpr**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) | [**DcmInterface**](structastrea_1_1astro_1_1DcmInterface.md#function-dcminterface-24) ([**const**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) std::array&lt; [**Value\_T**](classastrea_1_1astro_1_1DirectionCosineMatrix.md), 3 &gt; & row1, [**const**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) std::array&lt; [**Value\_T**](classastrea_1_1astro_1_1DirectionCosineMatrix.md), 3 &gt; & row2, [**const**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) std::array&lt; [**Value\_T**](classastrea_1_1astro_1_1DirectionCosineMatrix.md), 3 &gt; & row3) <br>_Constructor for_ [_**DcmInterface**_](structastrea_1_1astro_1_1DcmInterface.md) _from three rows represented as arrays._ |
|  [**constexpr**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) | [**DcmInterface**](structastrea_1_1astro_1_1DcmInterface.md#function-dcminterface-34) ([**const**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) [**DcmInterface**](structastrea_1_1astro_1_1DcmInterface.md)&lt; [**Value\_U**](classastrea_1_1astro_1_1DirectionCosineMatrix.md), [**in\_frame\_u**](classastrea_1_1astro_1_1DirectionCosineMatrix.md), [**out\_frame\_u**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) &gt; & matrix) <br> |
|  [**constexpr**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) | [**DcmInterface**](structastrea_1_1astro_1_1DcmInterface.md#function-dcminterface-44) ([**DcmInterface**](structastrea_1_1astro_1_1DcmInterface.md)&lt; [**Value\_U**](classastrea_1_1astro_1_1DirectionCosineMatrix.md), [**in\_frame\_u**](classastrea_1_1astro_1_1DirectionCosineMatrix.md), [**out\_frame\_u**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) &gt; && matrix) <br> |
|  [**constexpr**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) std::array&lt; [**Value\_T**](classastrea_1_1astro_1_1DirectionCosineMatrix.md), 9 &gt; | [**data**](structastrea_1_1astro_1_1DcmInterface.md#function-data) () const<br>_Get the underlying data of the matrix as an array._  |
|  [**constexpr**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) [**Value\_T**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) | [**determinant**](structastrea_1_1astro_1_1DcmInterface.md#function-determinant) () const<br>_Get the determinant of the matrix._  |
|  [**constexpr**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) [**void**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) | [**normalize**](structastrea_1_1astro_1_1DcmInterface.md#function-normalize) () <br>_Normalizes the matrix to ensure it represents a valid rotation._  |
|  [**constexpr**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) [**DcmInterface**](structastrea_1_1astro_1_1DcmInterface.md)&lt; [**decltype**](classastrea_1_1astro_1_1DirectionCosineMatrix.md)([**Value\_T**](classastrea_1_1astro_1_1DirectionCosineMatrix.md){} \*[**Value\_U**](classastrea_1_1astro_1_1DirectionCosineMatrix.md){}), [**in\_frame**](structastrea_1_1astro_1_1DcmInterface.md#variable-in_frame), [**out\_frame**](structastrea_1_1astro_1_1DcmInterface.md#variable-out_frame) &gt; | [**operator\***](structastrea_1_1astro_1_1DcmInterface.md#function-operator) ([**const**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) [**DcmInterface**](structastrea_1_1astro_1_1DcmInterface.md)&lt; [**Value\_U**](classastrea_1_1astro_1_1DirectionCosineMatrix.md), [**in\_frame\_u**](classastrea_1_1astro_1_1DirectionCosineMatrix.md), [**out\_frame\_u**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) &gt; & other) const<br>_Compose two direction matrices (matrix multiplication)._  |
|  [**constexpr**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) [**DcmInterface**](structastrea_1_1astro_1_1DcmInterface.md)&lt; [**decltype**](classastrea_1_1astro_1_1DirectionCosineMatrix.md)([**Value\_T**](classastrea_1_1astro_1_1DirectionCosineMatrix.md){} \*[**Value\_U**](classastrea_1_1astro_1_1DirectionCosineMatrix.md){}), [**in\_frame**](structastrea_1_1astro_1_1DcmInterface.md#variable-in_frame), [**out\_frame\_u**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) &gt; | [**operator\***](structastrea_1_1astro_1_1DcmInterface.md#function-operator_1) ([**const**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) [**DcmInterface**](structastrea_1_1astro_1_1DcmInterface.md)&lt; [**Value\_U**](classastrea_1_1astro_1_1DirectionCosineMatrix.md), [**in\_frame\_u**](classastrea_1_1astro_1_1DirectionCosineMatrix.md), [**out\_frame\_u**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) &gt; & other) const<br>_Compose two direction matrices (matrix multiplication)._  |
|  [**constexpr**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) [**CartesianVector**](structastrea_1_1astro_1_1CartesianVector.md)&lt; [**decltype**](classastrea_1_1astro_1_1DirectionCosineMatrix.md)([**Value\_T**](classastrea_1_1astro_1_1DirectionCosineMatrix.md){} \*[**Value\_U**](classastrea_1_1astro_1_1DirectionCosineMatrix.md){}), [**out\_frame**](structastrea_1_1astro_1_1DcmInterface.md#variable-out_frame) &gt; | [**operator\***](structastrea_1_1astro_1_1DcmInterface.md#function-operator_2) ([**const**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) [**CartesianVector**](structastrea_1_1astro_1_1CartesianVector.md)&lt; [**Value\_U**](classastrea_1_1astro_1_1DirectionCosineMatrix.md), [**in\_frame\_u**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) &gt; & vec) const<br>_Multiply this matrix by a_ [_**Cartesian**_](classastrea_1_1astro_1_1Cartesian.md) _vector._ |
|  [**constexpr**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) [**DcmInterface**](structastrea_1_1astro_1_1DcmInterface.md)&lt; [**decltype**](classastrea_1_1astro_1_1DirectionCosineMatrix.md)([**Value\_T**](classastrea_1_1astro_1_1DirectionCosineMatrix.md){} \*[**Value\_U**](classastrea_1_1astro_1_1DirectionCosineMatrix.md){}), [**in\_frame**](structastrea_1_1astro_1_1DcmInterface.md#variable-in_frame), [**out\_frame**](structastrea_1_1astro_1_1DcmInterface.md#variable-out_frame) &gt; | [**operator\***](structastrea_1_1astro_1_1DcmInterface.md#function-operator_3) ([**const**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) [**Value\_U**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) & scalar) const<br>_Multiply the matrix by a scalar value (element-wise multiplication)._  |
|  [**constexpr**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) [**DcmInterface**](structastrea_1_1astro_1_1DcmInterface.md) | [**operator+**](structastrea_1_1astro_1_1DcmInterface.md#function-operator_4) ([**const**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) [**DcmInterface**](structastrea_1_1astro_1_1DcmInterface.md)&lt; [**Value\_U**](classastrea_1_1astro_1_1DirectionCosineMatrix.md), [**in\_frame\_u**](classastrea_1_1astro_1_1DirectionCosineMatrix.md), [**out\_frame\_u**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) &gt; & other) const<br>_Add two matrices together (element-wise addition)._  |
|  [**constexpr**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) [**DcmInterface**](structastrea_1_1astro_1_1DcmInterface.md) | [**operator-**](structastrea_1_1astro_1_1DcmInterface.md#function-operator-) () const<br>_Negate the matrix (element-wise negation)._  |
|  [**constexpr**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) [**DcmInterface**](structastrea_1_1astro_1_1DcmInterface.md) | [**operator-**](structastrea_1_1astro_1_1DcmInterface.md#function-operator-_1) ([**const**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) [**DcmInterface**](structastrea_1_1astro_1_1DcmInterface.md)&lt; [**Value\_U**](classastrea_1_1astro_1_1DirectionCosineMatrix.md), [**in\_frame\_u**](classastrea_1_1astro_1_1DirectionCosineMatrix.md), [**out\_frame\_u**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) &gt; & other) const<br>_Subtract another matrix from this one (element-wise subtraction)._  |
|  [**constexpr**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) [**Value\_T**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) & | [**operator[]**](structastrea_1_1astro_1_1DcmInterface.md#function-operator_5) (std::size\_t row, std::size\_t col) <br>_Access operator for the elements of the matrix._  |
|  [**constexpr**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) [**const**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) [**Value\_T**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) & | [**operator[]**](structastrea_1_1astro_1_1DcmInterface.md#function-operator_6) (std::size\_t row, std::size\_t col) const<br>_Const access operator for the elements of the matrix._  |
|  [**constexpr**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) [**CartesianVector**](structastrea_1_1astro_1_1CartesianVector.md)&lt; [**Value\_T**](classastrea_1_1astro_1_1DirectionCosineMatrix.md), [**\_in\_frame\_**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) &gt; | [**row**](structastrea_1_1astro_1_1DcmInterface.md#function-row) ([**const**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) std::size\_t & idx) const<br>_Get a specific row of the matrix as a_ [_**Cartesian**_](classastrea_1_1astro_1_1Cartesian.md) _vector._ |
|  [**constexpr**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) [**Value\_T**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) | [**trace**](structastrea_1_1astro_1_1DcmInterface.md#function-trace) () const<br>_Get the trace of the matrix (the sum of the diagonal elements)._  |
|  [**constexpr**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) [**DcmInterface**](structastrea_1_1astro_1_1DcmInterface.md)&lt; [**Value\_T**](classastrea_1_1astro_1_1DirectionCosineMatrix.md), [**\_out\_frame\_**](classastrea_1_1astro_1_1DirectionCosineMatrix.md), [**\_in\_frame\_**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) &gt; | [**transpose**](structastrea_1_1astro_1_1DcmInterface.md#function-transpose) () const<br>_Transposes the matrix, effectively inverting the transformation._  |


## Public Static Functions

| Type | Name |
| ---: | :--- |
|  [**constexpr**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) [**DirectionCosineMatrix**](classastrea_1_1astro_1_1DirectionCosineMatrix.md)&lt; [**\_in\_frame\_**](classastrea_1_1astro_1_1DirectionCosineMatrix.md), [**\_out\_frame\_**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) &gt; | [**X**](#function-x) ([**const**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) [**Angle**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) & theta) <br>_Creates a direction cosine matrix for a rotation around the X-axis._  |
|  [**constexpr**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) [**DirectionCosineMatrix**](classastrea_1_1astro_1_1DirectionCosineMatrix.md)&lt; [**\_in\_frame\_**](classastrea_1_1astro_1_1DirectionCosineMatrix.md), [**\_out\_frame\_**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) &gt; | [**XYX**](#function-xyx) ([**const**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) [**Angle**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) & alpha, [**const**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) [**Angle**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) & beta, [**const**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) [**Angle**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) & gamma) <br>_Creates a direction cosine matrix for a rotation around the X-axis, the Y-axis, and the X-axis again._  |
|  [**constexpr**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) [**DirectionCosineMatrix**](classastrea_1_1astro_1_1DirectionCosineMatrix.md)&lt; [**\_in\_frame\_**](classastrea_1_1astro_1_1DirectionCosineMatrix.md), [**\_out\_frame\_**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) &gt; | [**XYZ**](#function-xyz) ([**const**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) [**Angle**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) & alpha, [**const**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) [**Angle**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) & beta, [**const**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) [**Angle**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) & gamma) <br>_Creates a direction cosine matrix for a rotation around the X-axis, then Y-axis, then Z-axis._  |
|  [**constexpr**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) [**DirectionCosineMatrix**](classastrea_1_1astro_1_1DirectionCosineMatrix.md)&lt; [**\_in\_frame\_**](classastrea_1_1astro_1_1DirectionCosineMatrix.md), [**\_out\_frame\_**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) &gt; | [**XZX**](#function-xzx) ([**const**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) [**Angle**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) & alpha, [**const**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) [**Angle**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) & beta, [**const**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) [**Angle**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) & gamma) <br>_Creates a direction cosine matrix for a rotation around the X-axis, the Z-axis, and the X-axis again._  |
|  [**constexpr**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) [**DirectionCosineMatrix**](classastrea_1_1astro_1_1DirectionCosineMatrix.md)&lt; [**\_in\_frame\_**](classastrea_1_1astro_1_1DirectionCosineMatrix.md), [**\_out\_frame\_**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) &gt; | [**XZY**](#function-xzy) ([**const**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) [**Angle**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) & alpha, [**const**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) [**Angle**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) & beta, [**const**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) [**Angle**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) & gamma) <br>_Creates a direction cosine matrix for a rotation around the X-axis, then Z-axis, then Y-axis._  |
|  [**constexpr**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) [**DirectionCosineMatrix**](classastrea_1_1astro_1_1DirectionCosineMatrix.md)&lt; [**\_in\_frame\_**](classastrea_1_1astro_1_1DirectionCosineMatrix.md), [**\_out\_frame\_**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) &gt; | [**Y**](#function-y) ([**const**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) [**Angle**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) & theta) <br>_Creates a direction cosine matrix for a rotation around the Y-axis._  |
|  [**constexpr**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) [**DirectionCosineMatrix**](classastrea_1_1astro_1_1DirectionCosineMatrix.md)&lt; [**\_in\_frame\_**](classastrea_1_1astro_1_1DirectionCosineMatrix.md), [**\_out\_frame\_**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) &gt; | [**YXY**](#function-yxy) ([**const**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) [**Angle**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) & alpha, [**const**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) [**Angle**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) & beta, [**const**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) [**Angle**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) & gamma) <br>_Creates a direction cosine matrix for a rotation around the Y-axis, the X-axis, and the Y-axis again._  |
|  [**constexpr**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) [**DirectionCosineMatrix**](classastrea_1_1astro_1_1DirectionCosineMatrix.md)&lt; [**\_in\_frame\_**](classastrea_1_1astro_1_1DirectionCosineMatrix.md), [**\_out\_frame\_**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) &gt; | [**YXZ**](#function-yxz) ([**const**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) [**Angle**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) & alpha, [**const**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) [**Angle**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) & beta, [**const**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) [**Angle**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) & gamma) <br>_Creates a direction cosine matrix for a rotation around the Y-axis, then X-axis, then Z-axis._  |
|  [**constexpr**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) [**DirectionCosineMatrix**](classastrea_1_1astro_1_1DirectionCosineMatrix.md)&lt; [**\_in\_frame\_**](classastrea_1_1astro_1_1DirectionCosineMatrix.md), [**\_out\_frame\_**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) &gt; | [**YZX**](#function-yzx) ([**const**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) [**Angle**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) & alpha, [**const**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) [**Angle**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) & beta, [**const**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) [**Angle**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) & gamma) <br>_Creates a direction cosine matrix for a rotation around the Y-axis, then Z-axis, then X-axis._  |
|  [**constexpr**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) [**DirectionCosineMatrix**](classastrea_1_1astro_1_1DirectionCosineMatrix.md)&lt; [**\_in\_frame\_**](classastrea_1_1astro_1_1DirectionCosineMatrix.md), [**\_out\_frame\_**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) &gt; | [**YZY**](#function-yzy) ([**const**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) [**Angle**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) & alpha, [**const**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) [**Angle**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) & beta, [**const**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) [**Angle**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) & gamma) <br>_Creates a direction cosine matrix for a rotation around the Y-axis, the Z-axis, and the Y-axis again._  |
|  [**constexpr**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) [**DirectionCosineMatrix**](classastrea_1_1astro_1_1DirectionCosineMatrix.md)&lt; [**\_in\_frame\_**](classastrea_1_1astro_1_1DirectionCosineMatrix.md), [**\_out\_frame\_**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) &gt; | [**Z**](#function-z) ([**const**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) [**Angle**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) & theta) <br>_Creates a direction cosine matrix for a rotation around the Z-axis._  |
|  [**constexpr**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) [**DirectionCosineMatrix**](classastrea_1_1astro_1_1DirectionCosineMatrix.md)&lt; [**\_in\_frame\_**](classastrea_1_1astro_1_1DirectionCosineMatrix.md), [**\_out\_frame\_**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) &gt; | [**ZXY**](#function-zxy) ([**const**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) [**Angle**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) & alpha, [**const**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) [**Angle**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) & beta, [**const**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) [**Angle**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) & gamma) <br>_Creates a direction cosine matrix for a rotation around the Z-axis, then X-axis, then Y-axis._  |
|  [**constexpr**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) [**DirectionCosineMatrix**](classastrea_1_1astro_1_1DirectionCosineMatrix.md)&lt; [**\_in\_frame\_**](classastrea_1_1astro_1_1DirectionCosineMatrix.md), [**\_out\_frame\_**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) &gt; | [**ZXZ**](#function-zxz) ([**const**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) [**Angle**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) & alpha, [**const**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) [**Angle**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) & beta, [**const**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) [**Angle**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) & gamma) <br>_Creates a direction cosine matrix for a rotation around the Z-axis, the X-axis, and the Z-axis again._  |
|  [**constexpr**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) [**DirectionCosineMatrix**](classastrea_1_1astro_1_1DirectionCosineMatrix.md)&lt; [**\_in\_frame\_**](classastrea_1_1astro_1_1DirectionCosineMatrix.md), [**\_out\_frame\_**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) &gt; | [**ZYX**](#function-zyx) ([**const**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) [**Angle**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) & alpha, [**const**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) [**Angle**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) & beta, [**const**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) [**Angle**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) & gamma) <br>_Creates a direction cosine matrix for a rotation around the Z-axis, then Y-axis, then X-axis._  |
|  [**constexpr**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) [**DirectionCosineMatrix**](classastrea_1_1astro_1_1DirectionCosineMatrix.md)&lt; [**\_in\_frame\_**](classastrea_1_1astro_1_1DirectionCosineMatrix.md), [**\_out\_frame\_**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) &gt; | [**ZYZ**](#function-zyz) ([**const**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) [**Angle**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) & alpha, [**const**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) [**Angle**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) & beta, [**const**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) [**Angle**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) & gamma) <br>_Creates a direction cosine matrix for a rotation around the Z-axis, the Y-axis, and the Z-axis again._  |
|  [**constexpr**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) [**DirectionCosineMatrix**](classastrea_1_1astro_1_1DirectionCosineMatrix.md)&lt; [**\_in\_frame\_**](classastrea_1_1astro_1_1DirectionCosineMatrix.md), [**\_out\_frame\_**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) &gt; | [**from\_euler\_angles**](#function-from_euler_angles) ([**const**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) [**Angle**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) & alpha, [**const**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) [**Angle**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) & beta, [**const**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) [**Angle**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) & gamma) <br>_Creates a direction cosine matrix from Euler angles based on a specified rotation sequence._  |
|  [**constexpr**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) [**DirectionCosineMatrix**](classastrea_1_1astro_1_1DirectionCosineMatrix.md)&lt; [**\_in\_frame\_**](classastrea_1_1astro_1_1DirectionCosineMatrix.md), [**\_out\_frame\_**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) &gt; | [**from\_vectors**](#function-from_vectors) ([**const**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) [**CartesianVector**](structastrea_1_1astro_1_1CartesianVector.md)&lt; [**Unitless**](classastrea_1_1astro_1_1DirectionCosineMatrix.md), [**\_in\_frame\_**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) &gt; & x, [**const**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) [**CartesianVector**](structastrea_1_1astro_1_1CartesianVector.md)&lt; [**Unitless**](classastrea_1_1astro_1_1DirectionCosineMatrix.md), [**\_in\_frame\_**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) &gt; & y, [**const**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) [**CartesianVector**](structastrea_1_1astro_1_1CartesianVector.md)&lt; [**Unitless**](classastrea_1_1astro_1_1DirectionCosineMatrix.md), [**\_in\_frame\_**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) &gt; & z) <br>_Creates a direction cosine matrix from three orthonormal vectors._  |
|  [**constexpr**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) [**DirectionCosineMatrix**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) | [**identity**](#function-identity) () <br> |
|  [**constexpr**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) [**DirectionCosineMatrix**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) | [**zero**](#function-zero) () <br> |














## Protected Attributes inherited from astrea::astro::DcmInterface

See [astrea::astro::DcmInterface](structastrea_1_1astro_1_1DcmInterface.md)

| Type | Name |
| ---: | :--- |
|  std::array&lt; [**Value\_T**](classastrea_1_1astro_1_1DirectionCosineMatrix.md), 9 &gt; | [**\_data**](structastrea_1_1astro_1_1DcmInterface.md#variable-_data)  <br>_3x3 matrix to hold the direction cosines._  |
































## Protected Functions inherited from astrea::astro::DcmInterface

See [astrea::astro::DcmInterface](structastrea_1_1astro_1_1DcmInterface.md)

| Type | Name |
| ---: | :--- |
|  std::array&lt; [**decltype**](classastrea_1_1astro_1_1DirectionCosineMatrix.md)([**Value\_T**](classastrea_1_1astro_1_1DirectionCosineMatrix.md){} \*[**Value\_U**](classastrea_1_1astro_1_1DirectionCosineMatrix.md){}), 9 &gt; | [**\_multiply**](structastrea_1_1astro_1_1DcmInterface.md#function-_multiply) ([**const**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) std::array&lt; [**Value\_U**](classastrea_1_1astro_1_1DirectionCosineMatrix.md), 9 &gt; & other) const<br> |
|  [**constexpr**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) [**void**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) | [**\_normalize**](structastrea_1_1astro_1_1DcmInterface.md#function-_normalize) ([**const**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) [**Unitless**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) & scale) <br>_Normalizes the matrix by scaling all elements by the given factor._  |




## Protected Static Functions inherited from astrea::astro::DcmInterface

See [astrea::astro::DcmInterface](structastrea_1_1astro_1_1DcmInterface.md)

| Type | Name |
| ---: | :--- |
|  [**constexpr**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) [**DcmInterface**](structastrea_1_1astro_1_1DcmInterface.md) | [**identity**](structastrea_1_1astro_1_1DcmInterface.md#function-identity) () <br>_Creates an identity matrix (no rotation)._  |
|  [**constexpr**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) [**DcmInterface**](structastrea_1_1astro_1_1DcmInterface.md) | [**zero**](structastrea_1_1astro_1_1DcmInterface.md#function-zero) () <br>_Creates a zero matrix (invalid rotation)._  |


## Detailed Description


This class provides methods to create DCMs for various rotations and to apply them to vectors.




**Template parameters:**


* `_out_frame_` The frame type to which the DCM applies. 




    
## Public Functions Documentation




### function DirectionCosineMatrix [1/3]

_Constructor for_ [_**DirectionCosineMatrix**_](classastrea_1_1astro_1_1DirectionCosineMatrix.md) _from an array of CartesianVectors._
```C++
inline constexpr astrea::astro::DirectionCosineMatrix::DirectionCosineMatrix (
    const std::array< Unitless , 9 > & matrix
) 
```





**Parameters:**


* `matrix` An array containing the three rows of the DCM, each represented as a [**CartesianVector**](structastrea_1_1astro_1_1CartesianVector.md). 




        

<hr>



### function DirectionCosineMatrix [2/3]

_Constructor for_ [_**DirectionCosineMatrix**_](classastrea_1_1astro_1_1DirectionCosineMatrix.md) _from an array of CartesianVectors._
```C++
inline constexpr astrea::astro::DirectionCosineMatrix::DirectionCosineMatrix (
    const std::array< Unitless , 3 > & row1,
    const std::array< Unitless , 3 > & row2,
    const std::array< Unitless , 3 > & row3
) 
```





**Parameters:**


* `row1` An array containing the three elements of the first row of the DCM. 
* `row2` An array containing the three elements of the second row of the DCM. 
* `row3` An array containing the three elements of the third row of the DCM. 




        

<hr>



### function DirectionCosineMatrix [3/3]

```C++
inline constexpr astrea::astro::DirectionCosineMatrix::DirectionCosineMatrix (
    const  DcmInterface < Unitless , _in_frame_ , _out_frame_ > & matrix
) 
```




<hr>



### function transpose 

```C++
inline constexpr  DirectionCosineMatrix < _out_frame_ , _in_frame_ > astrea::astro::DirectionCosineMatrix::transpose () const
```




<hr>
## Public Static Functions Documentation




### function X 

_Creates a direction cosine matrix for a rotation around the X-axis._ 
```C++
static inline constexpr  DirectionCosineMatrix < _in_frame_ , _out_frame_ > astrea::astro::DirectionCosineMatrix::X (
    const  Angle & theta
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
static inline constexpr  DirectionCosineMatrix < _in_frame_ , _out_frame_ > astrea::astro::DirectionCosineMatrix::XYX (
    const  Angle & alpha,
    const  Angle & beta,
    const  Angle & gamma
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
static inline constexpr  DirectionCosineMatrix < _in_frame_ , _out_frame_ > astrea::astro::DirectionCosineMatrix::XYZ (
    const  Angle & alpha,
    const  Angle & beta,
    const  Angle & gamma
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
static inline constexpr  DirectionCosineMatrix < _in_frame_ , _out_frame_ > astrea::astro::DirectionCosineMatrix::XZX (
    const  Angle & alpha,
    const  Angle & beta,
    const  Angle & gamma
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
static inline constexpr  DirectionCosineMatrix < _in_frame_ , _out_frame_ > astrea::astro::DirectionCosineMatrix::XZY (
    const  Angle & alpha,
    const  Angle & beta,
    const  Angle & gamma
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
static inline constexpr  DirectionCosineMatrix < _in_frame_ , _out_frame_ > astrea::astro::DirectionCosineMatrix::Y (
    const  Angle & theta
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
static inline constexpr  DirectionCosineMatrix < _in_frame_ , _out_frame_ > astrea::astro::DirectionCosineMatrix::YXY (
    const  Angle & alpha,
    const  Angle & beta,
    const  Angle & gamma
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
static inline constexpr  DirectionCosineMatrix < _in_frame_ , _out_frame_ > astrea::astro::DirectionCosineMatrix::YXZ (
    const  Angle & alpha,
    const  Angle & beta,
    const  Angle & gamma
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
static inline constexpr  DirectionCosineMatrix < _in_frame_ , _out_frame_ > astrea::astro::DirectionCosineMatrix::YZX (
    const  Angle & alpha,
    const  Angle & beta,
    const  Angle & gamma
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
static inline constexpr  DirectionCosineMatrix < _in_frame_ , _out_frame_ > astrea::astro::DirectionCosineMatrix::YZY (
    const  Angle & alpha,
    const  Angle & beta,
    const  Angle & gamma
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
static inline constexpr  DirectionCosineMatrix < _in_frame_ , _out_frame_ > astrea::astro::DirectionCosineMatrix::Z (
    const  Angle & theta
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
static inline constexpr  DirectionCosineMatrix < _in_frame_ , _out_frame_ > astrea::astro::DirectionCosineMatrix::ZXY (
    const  Angle & alpha,
    const  Angle & beta,
    const  Angle & gamma
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
static inline constexpr  DirectionCosineMatrix < _in_frame_ , _out_frame_ > astrea::astro::DirectionCosineMatrix::ZXZ (
    const  Angle & alpha,
    const  Angle & beta,
    const  Angle & gamma
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
static inline constexpr  DirectionCosineMatrix < _in_frame_ , _out_frame_ > astrea::astro::DirectionCosineMatrix::ZYX (
    const  Angle & alpha,
    const  Angle & beta,
    const  Angle & gamma
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
static inline constexpr  DirectionCosineMatrix < _in_frame_ , _out_frame_ > astrea::astro::DirectionCosineMatrix::ZYZ (
    const  Angle & alpha,
    const  Angle & beta,
    const  Angle & gamma
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
static inline constexpr  DirectionCosineMatrix < _in_frame_ , _out_frame_ > astrea::astro::DirectionCosineMatrix::from_euler_angles (
    const  Angle & alpha,
    const  Angle & beta,
    const  Angle & gamma
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
static inline constexpr  DirectionCosineMatrix < _in_frame_ , _out_frame_ > astrea::astro::DirectionCosineMatrix::from_vectors (
    const  CartesianVector < Unitless , _in_frame_ > & x,
    const  CartesianVector < Unitless , _in_frame_ > & y,
    const  CartesianVector < Unitless , _in_frame_ > & z
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
static inline constexpr  DirectionCosineMatrix astrea::astro::DirectionCosineMatrix::identity () 
```




<hr>



### function zero 

```C++
static inline constexpr  DirectionCosineMatrix astrea::astro::DirectionCosineMatrix::zero () 
```




<hr>

------------------------------
The documentation for this class was generated from the following file `astrea/astro/astro/frames/framework/DirectionCosineMatrix.hpp`

