

# Struct astrea::astro::detail::AxisBase



[**ClassList**](annotated.md) **>** [**astrea**](namespaceastrea.md) **>** [**astro**](namespaceastrea_1_1astro.md) **>** [**detail**](namespaceastrea_1_1astro_1_1detail.md) **>** [**AxisBase**](structastrea_1_1astro_1_1detail_1_1AxisBase.md)










Inherited by the following classes: [astrea::astro::Axis&lt; \_name\_ &gt;](structastrea_1_1astro_1_1Axis_3_01__name___01_4.md),  [astrea::astro::Axis&lt; \_name\_, \_parent\_ &gt;](structastrea_1_1astro_1_1Axis_3_01__name___00_01__parent___01_4.md)



























































## Friends Documentation





### friend equivalent 

_Checks if two frames are equivalent, considering their parent frames and any fixed offsets (spatial or angular)._ 
```C++
template<IsAxis Lhs, IsAxis Rhs>
inline consteval bool astrea::astro::detail::AxisBase::equivalent (
    Lhs lhs,
    Rhs rhs
) 
```





**Template parameters:**


* `Lhs` The type of the left-hand side frame. 
* `Rhs` The type of the right-hand side frame. 



**Parameters:**


* `lhs` The left-hand side frame instance. 
* `rhs` The right-hand side frame instance. 



**Returns:**

true if both frames are equivalent, false otherwise. 





        

<hr>



### friend operator== 

```C++
template<IsAxis Lhs, IsAxis Rhs>
inline consteval bool astrea::astro::detail::AxisBase::operator== (
    Lhs,
    Rhs
) 
```




<hr>

------------------------------
The documentation for this class was generated from the following file `astrea/astro/astro/frames/framework/Axis.hpp`

