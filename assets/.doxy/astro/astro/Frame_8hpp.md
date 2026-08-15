

# File Frame.hpp



[**FileList**](files.md) **>** [**astrea**](dir_b5324400686b7cece921533bb760c87a.md) **>** [**astro**](dir_1d4dcf10fc541574a93624f5c09a3d6f.md) **>** [**astro**](dir_84db6e3c60e44147f5214c05dc45afc2.md) **>** [**frames**](dir_45ba6462728f0c3fdeb841915d341ea3.md) **>** [**framework**](dir_aa3952657448f7008c08b8ed45c303ac.md) **>** [**Frame.hpp**](Frame_8hpp.md)

[Go to the source code of this file](Frame_8hpp_source.md)

_Definition for a Frame in astrea._ [More...](#detailed-description)

* `#include <type_traits>`
* `#include <mp-units/framework/symbol_text.h>`
* `#include <units/units.hpp>`
* `#include <astro/frames/framework/Axis.hpp>`
* `#include <astro/frames/framework/Origin.hpp>`
* `#include <astro/frames/framework/frame_concepts.hpp>`













## Namespaces

| Type | Name |
| ---: | :--- |
| namespace | [**astrea**](namespaceastrea.md) <br> |
| namespace | [**astro**](namespaceastrea_1_1astro.md) <br> |
| namespace | [**detail**](namespaceastrea_1_1astro_1_1detail.md) <br> |


## Classes

| Type | Name |
| ---: | :--- |
| struct | [**Frame&lt; \_name\_, \_origin\_, \_axis\_ &gt;**](structastrea_1_1astro_1_1Frame_3_01__name___00_01__origin___00_01__axis___01_4.md) &lt;\_name\_, \_origin\_, \_axis\_&gt;<br>[_**Frame**_](structastrea_1_1astro_1_1Frame.md) _with name, origin, and axis (no parent)._ |
| struct | [**Frame&lt; \_name\_, \_origin\_, \_axis\_, \_parent\_ &gt;**](structastrea_1_1astro_1_1Frame_3_01__name___00_01__origin___00_01__axis___00_01__parent___01_4.md) &lt;\_name\_, \_origin\_, \_axis\_, \_parent\_&gt;<br>[_**Frame**_](structastrea_1_1astro_1_1Frame.md) _with name, origin, axis, and parent._ |
| struct | [**FrameBase**](structastrea_1_1astro_1_1detail_1_1FrameBase.md) <br>_Empty base class for all frames in astrea. This allows us to use std::derived\_from to check if a type is a frame._  |


















































## Detailed Description




**Author:**

Jay Iuliano ([iuliano.jay@gmail.com](mailto:iuliano.jay@gmail.com)) 




**Date:**

2025-10-02




**Copyright:**

Copyright (c) 2025-2026 Jay Iuliano


The GNU Lesser General Public License (LGPL)


This file is part of Astrea. Astrea is free software: you can redistribute it and/or modify it under the terms of the GNU Lesser General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version. Astrea is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU Lesser General Public License for more details. You should have received a copy of the GNU General Public License along with Astrea. If not, see [https://www.gnu.org/licenses/](https://www.gnu.org/licenses/). 


    

------------------------------
The documentation for this class was generated from the following file `astrea/astro/astro/frames/framework/Frame.hpp`

