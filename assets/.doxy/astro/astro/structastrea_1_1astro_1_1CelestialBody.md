

# Struct astrea::astro::CelestialBody

**template &lt;mp\_units::symbol\_text \_name\_, IsOrigin [**auto**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) \_parent\_&gt;**



[**ClassList**](annotated.md) **>** [**astrea**](namespaceastrea.md) **>** [**astro**](namespaceastrea_1_1astro.md) **>** [**CelestialBody**](structastrea_1_1astro_1_1CelestialBody.md)



[_**CelestialBody**_](structastrea_1_1astro_1_1CelestialBody.md) _class represents a celestial body in an astrodynamics system._

* `#include <CelestialBody.hpp>`



Inherits the following classes: [astrea::astro::Origin&lt; \_name\_, \_parent\_ &gt;](structastrea_1_1astro_1_1Origin_3_01__name___00_01__parent___01_4.md),  [astrea::astro::detail::CelestialBodyBase](structastrea_1_1astro_1_1detail_1_1CelestialBodyBase.md)






































## Public Static Attributes

| Type | Name |
| ---: | :--- |
|  [**constexpr**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) [**GeocentricAxes**](structastrea_1_1astro_1_1GeocentricAxes.md)&lt; [**\_name\_**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) &gt; | [**geocentric\_axes**](#variable-geocentric_axes)   = `{}`<br> |
|  [**constexpr**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) [**ReferenceAxes**](structastrea_1_1astro_1_1ReferenceAxes.md)&lt; [**\_name\_**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) &gt; | [**reference\_axes**](#variable-reference_axes)   = `{}`<br> |


## Public Static Attributes inherited from astrea::astro::Origin< _name_, _parent_ >

See [astrea::astro::Origin&lt; \_name\_, \_parent\_ &gt;](structastrea_1_1astro_1_1Origin_3_01__name___00_01__parent___01_4.md)

| Type | Name |
| ---: | :--- |
|  [**constexpr**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) [**auto**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) | [**name**](structastrea_1_1astro_1_1Origin_3_01__name___00_01__parent___01_4.md#variable-name)   = `[**\_name\_**](classastrea_1_1astro_1_1DirectionCosineMatrix.md)`<br>_The name of the origin._  |
|  [**constexpr**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) [**auto**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) | [**parent**](structastrea_1_1astro_1_1Origin_3_01__name___00_01__parent___01_4.md#variable-parent)   = `[**\_parent\_**](classastrea_1_1astro_1_1DirectionCosineMatrix.md)`<br>_The parent origin of this origin, if any._  |






































































































































































## Public Static Attributes Documentation




### variable geocentric\_axes 

```C++
constexpr GeocentricAxes<_name_> astrea::astro::CelestialBody< _name_, _parent_ >::geocentric_axes;
```




<hr>



### variable reference\_axes 

```C++
constexpr ReferenceAxes<_name_> astrea::astro::CelestialBody< _name_, _parent_ >::reference_axes;
```




<hr>

------------------------------
The documentation for this class was generated from the following file `astrea/astro/astro/systems/CelestialBody.hpp`

