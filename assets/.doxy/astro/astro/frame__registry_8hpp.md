

# File frame\_registry.hpp



[**FileList**](files.md) **>** [**astrea**](dir_b5324400686b7cece921533bb760c87a.md) **>** [**astro**](dir_1d4dcf10fc541574a93624f5c09a3d6f.md) **>** [**astro**](dir_84db6e3c60e44147f5214c05dc45afc2.md) **>** [**frames**](dir_45ba6462728f0c3fdeb841915d341ea3.md) **>** [**definitions**](dir_0fbce91be2e6463cb25c5b2d70c0c29c.md) **>** [**frame\_registry.hpp**](frame__registry_8hpp.md)

[Go to the source code of this file](frame__registry_8hpp_source.md)

_Registration point for Cartesian frames used across astrea._ [More...](#detailed-description)

* `#include <tuple>`
* `#include <type_traits>`
* `#include <variant>`
* `#include <astro/frames/definitions/frame_registry.fwd.hpp>`
* `#include <astro/frames/definitions/primary_frame.hpp>`
* `#include <astro/frames/definitions/transformations.hpp>`
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
| struct | [**apply\_nttp\_template&lt; T, std::tuple&lt; Frames... &gt; &gt;**](structastrea_1_1astro_1_1detail_1_1apply__nttp__template_3_01T_00_01std_1_1tuple_3_01Frames_8_8_8_01_4_01_4.md) &lt;T, Frames&gt;<br> |
| struct | [**apply\_template&lt; T, std::tuple&lt; Frames... &gt; &gt;**](structastrea_1_1astro_1_1detail_1_1apply__template_3_01T_00_01std_1_1tuple_3_01Frames_8_8_8_01_4_01_4.md) &lt;T, Frames&gt;<br> |
| struct | [**multi\_tuple\_cat&lt; First, Rest... &gt;**](structastrea_1_1astro_1_1detail_1_1multi__tuple__cat_3_01First_00_01Rest_8_8_8_01_4.md) &lt;[**typename**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) [**First**](classastrea_1_1astro_1_1DirectionCosineMatrix.md), Rest&gt;<br> |
| struct | [**multi\_tuple\_cat&lt; Only &gt;**](structastrea_1_1astro_1_1detail_1_1multi__tuple__cat_3_01Only_01_4.md) &lt;[**typename**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) [**Only**](classastrea_1_1astro_1_1DirectionCosineMatrix.md)&gt;<br> |
| struct | [**multi\_tuple\_cat&lt;&gt;**](structastrea_1_1astro_1_1detail_1_1multi__tuple__cat_3_4.md) &lt;&gt;<br> |
| struct | [**tuple\_cat\_types&lt; std::tuple&lt; As... &gt;, std::tuple&lt; Bs... &gt; &gt;**](structastrea_1_1astro_1_1detail_1_1tuple__cat__types_3_01std_1_1tuple_3_01As_8_8_8_01_4_00_01std8cf8a2c8692dfec60c2615039d60391f.md) &lt;As, Bs&gt;<br> |
| struct | [**tuple\_to\_variant&lt; std::tuple&lt; Ts... &gt;, Extra... &gt;**](structastrea_1_1astro_1_1detail_1_1tuple__to__variant_3_01std_1_1tuple_3_01Ts_8_8_8_01_4_00_01Extra_8_8_8_01_4.md) &lt;Ts, Extra&gt;<br> |


















































## Detailed Description




**Author:**

Jay Iuliano ([iuliano.jay@gmail.com](mailto:iuliano.jay@gmail.com)) 




**Date:**

2025-04-22




**Copyright:**

Copyright (c) 2025 Jay Iuliano


The GNU Lesser General Public License (LGPL)


This file is part of Astrea. Astrea is free software: you can redistribute it and/or modify it under the terms of the GNU Lesser General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version. Astrea is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU Lesser General Public License for more details. You should have received a copy of the GNU General Public License along with Astrea. If not, see [https://www.gnu.org/licenses/](https://www.gnu.org/licenses/). 


    

------------------------------
The documentation for this class was generated from the following file `astrea/astro/astro/frames/definitions/frame_registry.hpp`

