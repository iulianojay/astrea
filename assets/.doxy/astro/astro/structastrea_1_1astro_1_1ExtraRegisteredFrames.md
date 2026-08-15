

# Struct astrea::astro::ExtraRegisteredFrames

**template &lt;typename&gt;**



[**ClassList**](annotated.md) **>** [**astrea**](namespaceastrea.md) **>** [**astro**](namespaceastrea_1_1astro.md) **>** [**ExtraRegisteredFrames**](structastrea_1_1astro_1_1ExtraRegisteredFrames.md)



_Trait that users specialize to register additional_ [_**Cartesian**_](classastrea_1_1astro_1_1Cartesian.md) _frames._[More...](#detailed-description)

* `#include <frame_registry.fwd.hpp>`

















## Public Types

| Type | Name |
| ---: | :--- |
| typedef std::tuple&lt;&gt; | [**type**](#typedef-type)  <br> |
















































## Detailed Description


Include this header, provide a specialization, then include [**frame\_registry.hpp**](frame__registry_8hpp.md). The frame types used in the specialization must already be declared before this point.



```C++
#include <astro/frames/definitions/body_centered_inertial_frames.hpp>
#include <astro/frames/definitions/frame_registry.fwd.hpp>

namespace astrea::astro {
  template <>
  struct ExtraRegisteredFrames<> {
      using type = std::tuple<std::decay_t<decltype(frames::moon::icrf)>,
                              std::decay_t<decltype(frames::mars::icrf)>>;
  };
}

#include <astro/frames/definitions/frame_registry.hpp>
// ... all other astrea headers
```



The primary template (empty list) is the default — do not modify it. 


    
## Public Types Documentation




### typedef type 

```C++
using astrea::astro::ExtraRegisteredFrames< typename >::type =  std::tuple<>;
```




<hr>

------------------------------
The documentation for this class was generated from the following file `astrea/astro/astro/frames/definitions/frame_registry.fwd.hpp`

