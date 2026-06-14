

# File default\_property\_getters.hpp



[**FileList**](files.md) **>** [**astrea**](dir_b5324400686b7cece921533bb760c87a.md) **>** [**astro**](dir_1d4dcf10fc541574a93624f5c09a3d6f.md) **>** [**astro**](dir_84db6e3c60e44147f5214c05dc45afc2.md) **>** [**systems**](dir_a5d35e082abd602943cf6d70fa2a6872.md) **>** [**default\_property\_getters.hpp**](default__property__getters_8hpp.md)

[Go to the source code of this file](default__property__getters_8hpp_source.md)

_Keplerian-approximation fallback implementations for get\_position\_at / get\_velocity\_at._ [More...](#detailed-description)

* `#include <astro/frames/framework/frame_utilities.hpp>`
* `#include <astro/state/orbital_elements/Cartesian.hpp>`
* `#include <astro/state/orbital_elements/Keplerian.hpp>`
* `#include <astro/systems/property_getters.hpp>`













## Namespaces

| Type | Name |
| ---: | :--- |
| namespace | [**astrea**](namespaceastrea.md) <br> |
| namespace | [**astro**](namespaceastrea_1_1astro.md) <br> |




















































## Detailed Description




**Author:**

Jay Iuliano ([iuliano.jay@gmail.com](mailto:iuliano.jay@gmail.com)) 


This header provides:
* get\_keplerian\_elements\_at&lt;_body_&gt; — JPL linear-approximation Keplerian elements.
* get\_position\_at&lt;_body_&gt; (primary template definition) — Keplerian fallback used for bodies that have no Chebyshev ephemeris specialisation (e.g. Phobos, Deimos).
* get\_velocity\_at&lt;_body_&gt; (primary template definition) — same fallback for velocity.




Include order matters: [**CelestialBody.hpp**](CelestialBody_8hpp.md) already declares the primary templates (without a body) for get\_position\_at / get\_velocity\_at. The planet specialisations (e.g. Earth, Jupiter) are compiled when their individual planet headers are included. This file provides the fall-through primary-template body for any remaining bodies.


This file MUST be included AFTER all planet headers (and therefore after all get\_position\_at explicit specialisations) so that the linker can select the correct overload. [**celestial\_bodies.hpp**](celestial__bodies_8hpp.md) includes it automatically at the bottom.




**Date:**

2025-08-02




**Copyright:**

Copyright (c) 2025 Jay Iuliano


The GNU Lesser General Public License (LGPL)


This file is part of Astrea. Astrea is free software: you can redistribute it and/or modify it under the terms of the GNU Lesser General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version. Astrea is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU Lesser General Public License for more details. You should have received a copy of the GNU General Public License along with Astrea. If not, see [https://www.gnu.org/licenses/](https://www.gnu.org/licenses/). 


    

------------------------------
The documentation for this class was generated from the following file `astrea/astro/astro/systems/default_property_getters.hpp`

