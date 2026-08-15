

# Struct astrea::astro::FixedOffsetAxis

**template &lt;IsAxis auto \_parent\_, Angle \_phi\_, Angle \_theta\_, Angle \_psi\_, [**RotationSequence**](namespaceastrea_1_1astro.md#enum-rotationsequence) \_sequence\_&gt;**



[**ClassList**](annotated.md) **>** [**astrea**](namespaceastrea.md) **>** [**astro**](namespaceastrea_1_1astro.md) **>** [**FixedOffsetAxis**](structastrea_1_1astro_1_1FixedOffsetAxis.md)








Inherits the following classes: [astrea::astro::Axis](structastrea_1_1astro_1_1Axis.md)












## Classes

| Type | Name |
| ---: | :--- |
| struct | [**Misalignment**](structastrea_1_1astro_1_1FixedOffsetAxis_1_1Misalignment.md) <br> |














## Public Static Attributes

| Type | Name |
| ---: | :--- |
|  constexpr [**Misalignment**](structastrea_1_1astro_1_1FixedOffsetAxis_1_1Misalignment.md) | [**misalignment**](#variable-misalignment)   = `{ \_phi\_, \_theta\_, \_psi\_ }`<br>_The fixed angular offset from the parent frame to this frame._  |
|  constexpr auto | [**sequence**](#variable-sequence)   = `\_sequence\_`<br>_The rotation sequence for the angular offset._  |




















































































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

