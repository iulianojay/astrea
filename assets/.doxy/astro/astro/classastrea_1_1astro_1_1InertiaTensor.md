

# Class astrea::astro::InertiaTensor

**template &lt;IsFrame auto \_frame\_&gt;**



[**ClassList**](annotated.md) **>** [**astrea**](namespaceastrea.md) **>** [**astro**](namespaceastrea_1_1astro.md) **>** [**InertiaTensor**](classastrea_1_1astro_1_1InertiaTensor.md)



_A class representing an inertia matrix in the astrea astro platform._ [More...](#detailed-description)

* `#include <InertiaTensor.hpp>`





































## Public Functions

| Type | Name |
| ---: | :--- |
|  constexpr | [**InertiaTensor**](#function-inertiatensor-14) () <br>_Default constructor for an inertia tensor._  |
|   | [**InertiaTensor**](#function-inertiatensor-24) (const MomentOfInertia & Ixx, const MomentOfInertia & Ixy, const MomentOfInertia & Ixz, const MomentOfInertia & Iyx, const MomentOfInertia & Iyy, const MomentOfInertia & Iyz, const MomentOfInertia & Izx, const MomentOfInertia & Izy, const MomentOfInertia & Izz) <br>_Constructs an inertia tensor with the specified moments of inertia._  |
|   | [**InertiaTensor**](#function-inertiatensor-34) (const MomentOfInertia & Ixx, const MomentOfInertia & Iyy, const MomentOfInertia & Izz) <br>_Constructs a diagonal inertia tensor with the specified moments of inertia along the principal axes._  |
|   | [**InertiaTensor**](#function-inertiatensor-44) (const MomentOfInertia & Iii) <br>_Constructs a spherical inertia tensor with the specified moment of inertia about any axis._  |
|  auto | [**determinant**](#function-determinant) () const<br>_Computes the determinant of the inertia tensor._  |
|  [**CartesianVector**](structastrea_1_1astro_1_1CartesianVector.md)&lt; decltype(Value\_U{}/MomentOfInertia{}), \_frame\_ &gt; | [**inverse\_multiply**](#function-inverse_multiply) (const [**CartesianVector**](structastrea_1_1astro_1_1CartesianVector.md)&lt; Value\_U, \_frame\_ &gt; & vec) const<br>_Multiplies the inertia tensor by a_ [_**CartesianVector**_](structastrea_1_1astro_1_1CartesianVector.md) _, effectively applying the inertia tensor to the vector._ |
|  MomentOfInertia & | [**operator[]**](#function-operator) (size\_t i, size\_t j) <br>_Accesses the inertia tensor element at the specified row and column._  |
|  const MomentOfInertia & | [**operator[]**](#function-operator_1) (size\_t i, size\_t j) const<br>_Accesses the inertia tensor element at the specified row and column (const version)._  |
|   | [**~InertiaTensor**](#function-inertiatensor) () = default<br>_Default destructor for an inertia tensor._  |




























## Detailed Description




**Template parameters:**


* `_frame_` The frame in which the inertia tensor is defined. Defaults to `frames::dynamic::body`. 




    
## Public Functions Documentation




### function InertiaTensor [1/4]

_Default constructor for an inertia tensor._ 
```C++
inline constexpr astrea::astro::InertiaTensor::InertiaTensor () 
```




<hr>



### function InertiaTensor [2/4]

_Constructs an inertia tensor with the specified moments of inertia._ 
```C++
inline astrea::astro::InertiaTensor::InertiaTensor (
    const MomentOfInertia & Ixx,
    const MomentOfInertia & Ixy,
    const MomentOfInertia & Ixz,
    const MomentOfInertia & Iyx,
    const MomentOfInertia & Iyy,
    const MomentOfInertia & Iyz,
    const MomentOfInertia & Izx,
    const MomentOfInertia & Izy,
    const MomentOfInertia & Izz
) 
```





**Parameters:**


* `Ixx` Moment of inertia about the x-axis. 
* `Ixy` Product of inertia about the x and y axes. 
* `Ixz` Product of inertia about the x and z axes. 
* `Iyy` Moment of inertia about the y-axis. 
* `Iyz` Product of inertia about the y and z axes. 
* `Izz` Moment of inertia about the z-axis. 




        

<hr>



### function InertiaTensor [3/4]

_Constructs a diagonal inertia tensor with the specified moments of inertia along the principal axes._ 
```C++
inline astrea::astro::InertiaTensor::InertiaTensor (
    const MomentOfInertia & Ixx,
    const MomentOfInertia & Iyy,
    const MomentOfInertia & Izz
) 
```





**Parameters:**


* `Ixx` Moment of inertia about the x-axis. 
* `Iyy` Moment of inertia about the y-axis. 
* `Izz` Moment of inertia about the z-axis. 




        

<hr>



### function InertiaTensor [4/4]

_Constructs a spherical inertia tensor with the specified moment of inertia about any axis._ 
```C++
inline astrea::astro::InertiaTensor::InertiaTensor (
    const MomentOfInertia & Iii
) 
```





**Parameters:**


* `Iii` Moment of inertia about any axis (for a sphere, all moments of inertia are equal). 




        

<hr>



### function determinant 

_Computes the determinant of the inertia tensor._ 
```C++
inline auto astrea::astro::InertiaTensor::determinant () const
```





**Returns:**

auto The determinant of the inertia tensor. 





        

<hr>



### function inverse\_multiply 

_Multiplies the inertia tensor by a_ [_**CartesianVector**_](structastrea_1_1astro_1_1CartesianVector.md) _, effectively applying the inertia tensor to the vector._
```C++
template<typename Value_U>
inline CartesianVector < decltype(Value_U{}/MomentOfInertia{}), _frame_ > astrea::astro::InertiaTensor::inverse_multiply (
    const CartesianVector < Value_U, _frame_ > & vec
) const
```




<hr>



### function operator[] 

_Accesses the inertia tensor element at the specified row and column._ 
```C++
inline MomentOfInertia & astrea::astro::InertiaTensor::operator[] (
    size_t i,
    size_t j
) 
```




<hr>



### function operator[] 

_Accesses the inertia tensor element at the specified row and column (const version)._ 
```C++
inline const MomentOfInertia & astrea::astro::InertiaTensor::operator[] (
    size_t i,
    size_t j
) const
```




<hr>



### function ~InertiaTensor 

_Default destructor for an inertia tensor._ 
```C++
astrea::astro::InertiaTensor::~InertiaTensor () = default
```




<hr>

------------------------------
The documentation for this class was generated from the following file `astrea/astro/astro/platforms/InertiaTensor.hpp`

