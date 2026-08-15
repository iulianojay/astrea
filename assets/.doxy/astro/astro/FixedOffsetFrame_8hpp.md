

# File FixedOffsetFrame.hpp



[**FileList**](files.md) **>** [**astrea**](dir_b5324400686b7cece921533bb760c87a.md) **>** [**astro**](dir_1d4dcf10fc541574a93624f5c09a3d6f.md) **>** [**astro**](dir_84db6e3c60e44147f5214c05dc45afc2.md) **>** [**frames**](dir_45ba6462728f0c3fdeb841915d341ea3.md) **>** [**framework**](dir_aa3952657448f7008c08b8ed45c303ac.md) **>** [**FixedOffsetFrame.hpp**](FixedOffsetFrame_8hpp.md)

[Go to the source code of this file](FixedOffsetFrame_8hpp_source.md)

_Definition for a FixedOffsetFrame in astrea._ [More...](#detailed-description)

* `#include <type_traits>`
* `#include <mp-units/core.h>`
* `#include <mp-units/framework/symbol_text.h>`
* `#include <units/units.hpp>`
* `#include <utilities/string_util.hpp>`
* `#include <astro/frames/framework/CartesianVector.hpp>`
* `#include <astro/frames/framework/Frame.hpp>`
* `#include <astro/frames/framework/frame_concepts.hpp>`
* `#include <astro/types/enums.hpp>`













## Namespaces

| Type | Name |
| ---: | :--- |
| namespace | [**astrea**](namespaceastrea.md) <br> |
| namespace | [**astro**](namespaceastrea_1_1astro.md) <br> |
| namespace | [**detail**](namespaceastrea_1_1astro_1_1detail.md) <br> |


## Classes

| Type | Name |
| ---: | :--- |
| struct | [**FixedOffsetAxis**](structastrea_1_1astro_1_1FixedOffsetAxis.md) &lt;\_parent\_, \_phi\_, \_theta\_, \_psi\_, \_sequence\_&gt;<br> |
| struct | [**Misalignment**](structastrea_1_1astro_1_1FixedOffsetAxis_1_1Misalignment.md) <br> |
| struct | [**FixedOffsetFrame&lt; \_name\_, \_parent\_, \_phi\_, \_theta\_, \_psi\_, \_sequence\_, Args... &gt;**](structastrea_1_1astro_1_1FixedOffsetFrame_3_01__name___00_01__parent___00_01__phi___00_01__theta96154ff31cb8eb7d055f0d1372ec2a1e.md) &lt;\_name\_, \_parent\_, \_phi\_, \_theta\_, \_psi\_, \_sequence\_, Args&gt;<br>_Specialization of_ [_**FixedOffsetFrame**_](structastrea_1_1astro_1_1FixedOffsetFrame.md) _for an angular offset with no spatial misalignment that lets the name be specified._ |
| struct | [**FixedOffsetFrame&lt; \_name\_, \_parent\_, \_x\_, \_y\_, \_z\_, Args... &gt;**](structastrea_1_1astro_1_1FixedOffsetFrame_3_01__name___00_01__parent___00_01__x___00_01__y___00_01__z___00_01Args_8_8_8_01_4.md) &lt;\_name\_, \_parent\_, \_x\_, \_y\_, \_z\_, Args&gt;<br>_Specialization of_ [_**FixedOffsetFrame**_](structastrea_1_1astro_1_1FixedOffsetFrame.md) _for a spatial offset with no angular misalignment that lets the name be specified._ |
| struct | [**FixedOffsetFrame&lt; \_name\_, \_parent\_, \_x\_, \_y\_, \_z\_, \_phi\_, \_theta\_, \_psi\_, \_sequence\_, Args... &gt;**](structastrea_1_1astro_1_1FixedOffsetFrame_3_01__name___00_01__parent___00_01__x___00_01__y___00_682f817510ea200b9f1d77fc37d45a92.md) &lt;\_name\_, \_parent\_, \_x\_, \_y\_, \_z\_, \_phi\_, \_theta\_, \_psi\_, \_sequence\_, Args&gt;<br>_Specialization of_ [_**FixedOffsetFrame**_](structastrea_1_1astro_1_1FixedOffsetFrame.md) _for a combined spatial and angular offset that lets the name be specified._ |
| struct | [**FixedOffsetFrame&lt; \_parent\_, \_phi\_, \_theta\_, \_psi\_, \_sequence\_, Args... &gt;**](structastrea_1_1astro_1_1FixedOffsetFrame_3_01__parent___00_01__phi___00_01__theta___00_01__psi_9e091a834f5483531831878cbc7beda5.md) &lt;\_parent\_, \_phi\_, \_theta\_, \_psi\_, \_sequence\_, Args&gt;<br>_Specialization of_ [_**FixedOffsetFrame**_](structastrea_1_1astro_1_1FixedOffsetFrame.md) _for a pure angular offset (no spatial offset)._ |
| struct | [**FixedOffsetFrame&lt; \_parent\_, \_x\_, \_y\_, \_z\_, Args... &gt;**](structastrea_1_1astro_1_1FixedOffsetFrame_3_01__parent___00_01__x___00_01__y___00_01__z___00_01Args_8_8_8_01_4.md) &lt;\_parent\_, \_x\_, \_y\_, \_z\_, Args&gt;<br>_Specialization of_ [_**FixedOffsetFrame**_](structastrea_1_1astro_1_1FixedOffsetFrame.md) _for a pure spatial offset (no angular misalignment)._ |
| struct | [**FixedOffsetFrame&lt; \_parent\_, \_x\_, \_y\_, \_z\_, \_phi\_, \_theta\_, \_psi\_, \_sequence\_, Args... &gt;**](structastrea_1_1astro_1_1FixedOffsetFrame_3_01__parent___00_01__x___00_01__y___00_01__z___00_01_3721297a9a90e06cc0beab0e7a99da8d.md) &lt;\_parent\_, \_x\_, \_y\_, \_z\_, \_phi\_, \_theta\_, \_psi\_, \_sequence\_, Args&gt;<br>_Specialization of_ [_**FixedOffsetFrame**_](structastrea_1_1astro_1_1FixedOffsetFrame.md) _for a combined spatial and angular offset._ |
| struct | [**FixedOffsetOrigin**](structastrea_1_1astro_1_1FixedOffsetOrigin.md) &lt;\_parent\_, \_x\_, \_y\_, \_z\_&gt;<br> |
| struct | [**Offset**](structastrea_1_1astro_1_1FixedOffsetOrigin_1_1Offset.md) <br> |


















































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
The documentation for this class was generated from the following file `astrea/astro/astro/frames/framework/FixedOffsetFrame.hpp`

