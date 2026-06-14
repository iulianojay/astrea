

# File defined\_rotations\_earth.hpp



[**FileList**](files.md) **>** [**astrea**](dir_b5324400686b7cece921533bb760c87a.md) **>** [**astro**](dir_1d4dcf10fc541574a93624f5c09a3d6f.md) **>** [**astro**](dir_84db6e3c60e44147f5214c05dc45afc2.md) **>** [**frames**](dir_45ba6462728f0c3fdeb841915d341ea3.md) **>** [**definitions**](dir_0fbce91be2e6463cb25c5b2d70c0c29c.md) **>** [**defined\_rotations\_earth.hpp**](defined__rotations__earth_8hpp.md)

[Go to the source code of this file](defined__rotations__earth_8hpp_source.md)

_Earth-specific DCM explicit specialisations._ [More...](#detailed-description)

* `#include <type_traits>`
* `#include <mp-units/systems/angular/math.h>`
* `#include <astro/frames/definitions/body_centered_inertial_frames.hpp>`
* `#include <astro/frames/definitions/body_fixed_frames.hpp>`
* `#include <astro/frames/definitions/defined_rotations.hpp>`
* `#include <astro/systems/celestial_bodies.hpp>`
* `#include <astro/systems/system_utilities.hpp>`
* `#include <astro/time/Date.hpp>`













## Namespaces

| Type | Name |
| ---: | :--- |
| namespace | [**astrea**](namespaceastrea.md) <br> |
| namespace | [**astro**](namespaceastrea_1_1astro.md) <br> |




















































## Detailed Description




**Author:**

Jay Iuliano ([iuliano.jay@gmail.com](mailto:iuliano.jay@gmail.com)) 


This file is intentionally separate from [**defined\_rotations.hpp**](defined__rotations_8hpp.md) so that the generic templates in [**defined\_rotations.hpp**](defined__rotations_8hpp.md) can be included mid-way through the include graph (e.g. via [**dynamic\_frames.hpp**](dynamic__frames_8hpp.md)) without pulling in frames::earth::\*, which are only complete once [**body\_centered\_inertial\_frames.hpp**](body__centered__inertial__frames_8hpp.md) and [**body\_fixed\_frames.hpp**](body__fixed__frames_8hpp.md) have both finished.


frames.hpp includes this file AFTER its two frame-instance headers, so by the time these specialisations are compiled all earth frame types are complete.




**Copyright:**

Copyright (c) 2025 Jay Iuliano


The GNU Lesser General Public License (LGPL)


This file is part of Astrea. 


    

------------------------------
The documentation for this class was generated from the following file `astrea/astro/astro/frames/definitions/defined_rotations_earth.hpp`

