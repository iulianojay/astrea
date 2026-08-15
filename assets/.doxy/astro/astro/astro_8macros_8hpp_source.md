

# File astro.macros.hpp

[**File List**](files.md) **>** [**astrea**](dir_b5324400686b7cece921533bb760c87a.md) **>** [**astro**](dir_1d4dcf10fc541574a93624f5c09a3d6f.md) **>** [**astro**](dir_84db6e3c60e44147f5214c05dc45afc2.md) **>** [**astro.macros.hpp**](astro_8macros_8hpp.md)

[Go to the documentation of this file](astro_8macros_8hpp.md)


```C++

#pragma once

#ifndef _ASTRO_ROOT_

#define _ASTRO_ROOT_
static_assert(false, "_ASTRO_ROOT_ environment variable not set or passed to compiler.");

#endif // _ASTRO_ROOT_

#ifdef _ASTRO_ROOT_

#define _ASTRO_GRAV_DATA_ROOT_ _ASTRO_ROOT_ "/data/gravity_models"

#endif // _ASTRO_ROOT_
```


