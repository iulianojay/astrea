

# Struct astrea::astro::FixedOffsetAxis

**template &lt;IsAxis [**auto**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) \_parent\_, [**Angle**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) \_phi\_, [**Angle**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) \_theta\_, [**Angle**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) \_psi\_, [**RotationSequence**](namespaceastrea_1_1astro.md#enum-rotationsequence) \_sequence\_&gt;**



[**ClassList**](annotated.md) **>** [**astrea**](namespaceastrea.md) **>** [**astro**](namespaceastrea_1_1astro.md) **>** [**FixedOffsetAxis**](structastrea_1_1astro_1_1FixedOffsetAxis.md)








Inherits the following classes: [astrea::astro::Axis](structastrea_1_1astro_1_1Axis.md)












## Classes

| Type | Name |
| ---: | :--- |
| struct | [**Misalignment**](structastrea_1_1astro_1_1FixedOffsetAxis_1_1Misalignment.md) <br> |














## Public Static Attributes

| Type | Name |
| ---: | :--- |
|  [**constexpr**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) [**Misalignment**](structastrea_1_1astro_1_1FixedOffsetAxis_1_1Misalignment.md) | [**misalignment**](#variable-misalignment)   = `{ [**\_phi\_**](classastrea_1_1astro_1_1DirectionCosineMatrix.md), [**\_theta\_**](classastrea_1_1astro_1_1DirectionCosineMatrix.md), [**\_psi\_**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) }`<br>_The fixed angular offset from the parent frame to this frame._  |
|  [**constexpr**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) [**auto**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) | [**sequence**](#variable-sequence)   = `[**\_sequence\_**](classastrea_1_1astro_1_1DirectionCosineMatrix.md)`<br>_The rotation sequence for the angular offset._  |




















































































## Public Static Attributes Documentation




### variable misalignment 

_The fixed angular offset from the parent frame to this frame._ 
```C++
constexpr Misalignment astrea::astro::FixedOffsetAxis< _parent_, _phi_, _theta_, _psi_, _sequence_ >::misalignment;
```




<hr>



### variable sequence 

_The rotation sequence for the angular offset._ 
```C++
constexpr auto astrea::astro::FixedOffsetAxis< _parent_, _phi_, _theta_, _psi_, _sequence_ >::sequence;
```




<hr>

------------------------------
The documentation for this class was generated from the following file `astrea/astro/astro/frames/framework/FixedOffsetFrame.hpp`

