

# Struct astrea::astro::CelestialBodyTypePack

**template &lt;typename...&gt;**



[**ClassList**](annotated.md) **>** [**astrea**](namespaceastrea.md) **>** [**astro**](namespaceastrea_1_1astro.md) **>** [**CelestialBodyTypePack**](structastrea_1_1astro_1_1CelestialBodyTypePack.md)



_Type-list used to attach member bodies to a_ [_**Barycenter**_](structastrea_1_1astro_1_1Barycenter.md) _._[More...](#detailed-description)

* `#include <Barycenter.hpp>`

































































## Detailed Description


Types in the list may be incomplete (forward-declared) at the point where the [**Barycenter**](structastrea_1_1astro_1_1Barycenter.md) is instantiated, which avoids circular inclusion between [**Barycenter.hpp**](Barycenter_8hpp.md) and the individual planet headers. Because CelestialBodyTypePack&lt;&gt; has no data members it is a structural type and can therefore be passed as a non-type template parameter. 


    

------------------------------
The documentation for this class was generated from the following file `astrea/astro/astro/systems/Barycenter.hpp`

