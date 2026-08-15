

# Struct astrea::astro::SynodicAxis

**template &lt;IsCelestialBody auto \_primary\_, IsCelestialBody auto \_secondary\_&gt;**



[**ClassList**](annotated.md) **>** [**astrea**](namespaceastrea.md) **>** [**astro**](namespaceastrea_1_1astro.md) **>** [**SynodicAxis**](structastrea_1_1astro_1_1SynodicAxis.md)



[_**Axis**_](structastrea_1_1astro_1_1Axis.md) _defined by the line connecting two celestial bodies and the plane of motion of the secondary around the primary._[More...](#detailed-description)

* `#include <SynodicFrame.hpp>`



Inherits the following classes: [astrea::astro::Axis](structastrea_1_1astro_1_1Axis.md)


























## Public Static Attributes

| Type | Name |
| ---: | :--- |
|  constexpr auto | [**primary**](#variable-primary)   = `\_primary\_`<br> |
|  constexpr auto | [**secondary**](#variable-secondary)   = `\_secondary\_`<br> |




















































































## Detailed Description


The x-axis points from the primary to the secondary, the z-axis is normal to the plane of motion of the secondary around the primary, and the y-axis is normal to both, pointing in the direction of motion of the secondary around the primary. 


    
## Public Static Attributes Documentation




### variable primary 

```C++
constexpr auto astrea::astro::SynodicAxis< _primary_, _secondary_ >::primary;
```




<hr>



### variable secondary 

```C++
constexpr auto astrea::astro::SynodicAxis< _primary_, _secondary_ >::secondary;
```




<hr>

------------------------------
The documentation for this class was generated from the following file `astrea/astro/astro/frames/framework/SynodicFrame.hpp`

