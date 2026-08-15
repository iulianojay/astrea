

# Struct astrea::astro::detail::FrameBase



[**ClassList**](annotated.md) **>** [**astrea**](namespaceastrea.md) **>** [**astro**](namespaceastrea_1_1astro.md) **>** [**detail**](namespaceastrea_1_1astro_1_1detail.md) **>** [**FrameBase**](structastrea_1_1astro_1_1detail_1_1FrameBase.md)



_Empty base class for all frames in astrea. This allows us to use std::derived\_from to check if a type is a frame._ 

* `#include <Frame.hpp>`





Inherited by the following classes: [astrea::astro::Frame&lt; \_name\_, \_origin\_, \_axis\_ &gt;](structastrea_1_1astro_1_1Frame_3_01__name___00_01__origin___00_01__axis___01_4.md),  [astrea::astro::Frame&lt; \_name\_, \_origin\_, \_axis\_, \_parent\_ &gt;](structastrea_1_1astro_1_1Frame_3_01__name___00_01__origin___00_01__axis___00_01__parent___01_4.md)



























































## Friends Documentation





### friend operator== 

```C++
template<IsFrame Lhs, IsFrame Rhs>
inline consteval bool astrea::astro::detail::FrameBase::operator== (
    Lhs,
    Rhs
) 
```




<hr>

------------------------------
The documentation for this class was generated from the following file `astrea/astro/astro/frames/framework/Frame.hpp`

