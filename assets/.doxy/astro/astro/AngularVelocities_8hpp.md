

# File AngularVelocities.hpp



[**FileList**](files.md) **>** [**astrea**](dir_b5324400686b7cece921533bb760c87a.md) **>** [**astro**](dir_1d4dcf10fc541574a93624f5c09a3d6f.md) **>** [**astro**](dir_84db6e3c60e44147f5214c05dc45afc2.md) **>** [**state**](dir_cf1a4d8122645f8636e977da512a043c.md) **>** [**attitude**](dir_d187d1a6cf435d7a067093cc1f3d7926.md) **>** [**AngularVelocities.hpp**](AngularVelocities_8hpp.md)

[Go to the source code of this file](AngularVelocities_8hpp_source.md)

_Class representing angular sequence velocities for attitude transformations between state/frames._ [More...](#detailed-description)

* `#include <units/units.hpp>`
* `#include <astro/astro.fwd.hpp>`
* `#include <astro/frames/definitions/dynamic_frames/tags.hpp>`
* `#include <astro/frames/framework/CartesianVector.hpp>`
* `#include <astro/frames/framework/DirectionCosineMatrix.hpp>`
* `#include <astro/frames/framework/frame_concepts.hpp>`
* `#include <astro/platforms/InertiaTensor.hpp>`
* `#include <astro/state/attitude/EulerAngles.hpp>`
* `#include <astro/types/enums.hpp>`
* `#include <astro/utilities/conversions.hpp>`













## Namespaces

| Type | Name |
| ---: | :--- |
| namespace | [**astrea**](namespaceastrea.md) <br> |
| namespace | [**astro**](namespaceastrea_1_1astro.md) <br> |


## Classes

| Type | Name |
| ---: | :--- |
| class | [**AngularAccelerations**](classastrea_1_1astro_1_1AngularAccelerations.md) &lt;\_in\_frame\_, \_ref\_frame\_&gt;<br>_Class representing the angular sequence acceleration, which is the time derivative of the angular sequence velocity._  |
| class | [**AngularVelocities**](classastrea_1_1astro_1_1AngularVelocities.md) &lt;\_in\_frame\_, \_ref\_frame\_&gt;<br>_Class representing a sequence of angular velocities (either Euler or Tait-Bryan) for attitude transformations between frames._  |


















































## Detailed Description




**Author:**

Jay Iuliano ([iuliano.jay@gmail.com](mailto:iuliano.jay@gmail.com)) 




**Date:**

2026-03-22




**Copyright:**

Copyright (c) 2025-2026 Jay Iuliano


The GNU Lesser General Public License (LGPL)


This file is part of Astrea. Astrea is free software: you can redistribute it and/or modify it under the terms of the GNU Lesser General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version. Astrea is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU Lesser General Public License for more details. You should have received a copy of the GNU General Public License along with Astrea. If not, see [https://www.gnu.org/licenses/](https://www.gnu.org/licenses/). 


    

------------------------------
The documentation for this class was generated from the following file `astrea/astro/astro/state/attitude/AngularVelocities.hpp`

