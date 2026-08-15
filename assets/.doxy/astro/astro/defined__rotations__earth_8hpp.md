

# File defined\_rotations\_earth.hpp



[**FileList**](files.md) **>** [**astrea**](dir_b5324400686b7cece921533bb760c87a.md) **>** [**astro**](dir_1d4dcf10fc541574a93624f5c09a3d6f.md) **>** [**astro**](dir_84db6e3c60e44147f5214c05dc45afc2.md) **>** [**frames**](dir_45ba6462728f0c3fdeb841915d341ea3.md) **>** [**definitions**](dir_0fbce91be2e6463cb25c5b2d70c0c29c.md) **>** [**defined\_rotations\_earth.hpp**](defined__rotations__earth_8hpp.md)

[Go to the source code of this file](defined__rotations__earth_8hpp_source.md)

_Earth-specific DCM explicit specialisations._ [More...](#detailed-description)

* `#include <mp-units/systems/si/math.h>`
* `#include <math/trig.hpp>`
* `#include <units/units.hpp>`
* `#include <astro/eop/EarthOrientationParameters.hpp>`
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








## Public Attributes

| Type | Name |
| ---: | :--- |
|  mp\_units::quantity&lt; mp\_units::si::arcminute &gt; | [**a0**](#variable-a0)  <br> |
|  mp\_units::quantity&lt; mp\_units::si::arcsecond &gt; | [**a1**](#variable-a1)  <br> |
|  mp\_units::quantity&lt; mp\_units::si::arcminute &gt; | [**b0**](#variable-b0)  <br> |
|  mp\_units::quantity&lt; mp\_units::si::arcsecond &gt; | [**b1**](#variable-b1)  <br> |
|  std::array&lt; int8\_t, 5 &gt; | [**k**](#variable-k)  <br> |
|  Time | [**period**](#variable-period)  <br> |












































## Detailed Description




**Author:**

Jay Iuliano ([iuliano.jay@gmail.com](mailto:iuliano.jay@gmail.com)) 


This file is intentionally separate from [**defined\_rotations.hpp**](defined__rotations_8hpp.md) so that the generic templates in [**defined\_rotations.hpp**](defined__rotations_8hpp.md) can be included mid-way through the include graph (e.g. via dynamic/tags.hpp) without pulling in frames::earth::\*, which are only complete once [**body\_centered\_inertial\_frames.hpp**](body__centered__inertial__frames_8hpp.md) and [**body\_fixed\_frames.hpp**](body__fixed__frames_8hpp.md) have both finished.


frames.hpp includes this file AFTER its two frame-instance headers, so by the time these specialisations are compiled all earth frame types are complete.




**Copyright:**

Copyright (c) 2025-2026 Jay Iuliano


The GNU Lesser General Public License (LGPL)


This file is part of Astrea. 


    
## Public Attributes Documentation




### variable a0 

```C++
mp_units::quantity<mp_units::si::arcminute> a0;
```




<hr>



### variable a1 

```C++
mp_units::quantity<mp_units::si::arcsecond> a1;
```




<hr>



### variable b0 

```C++
mp_units::quantity<mp_units::si::arcminute> b0;
```




<hr>



### variable b1 

```C++
mp_units::quantity<mp_units::si::arcsecond> b1;
```




<hr>



### variable k 

```C++
std::array<int8_t, 5> k;
```




<hr>



### variable period 

```C++
Time period;
```




<hr>

------------------------------
The documentation for this class was generated from the following file `astrea/astro/astro/frames/definitions/defined_rotations_earth.hpp`

