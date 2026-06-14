

# File enums.hpp

[**File List**](files.md) **>** [**astrea**](dir_b5324400686b7cece921533bb760c87a.md) **>** [**astro**](dir_1d4dcf10fc541574a93624f5c09a3d6f.md) **>** [**astro**](dir_84db6e3c60e44147f5214c05dc45afc2.md) **>** [**types**](dir_81b398d2ba04cf47420d9ac22d356bcf.md) **>** [**enums.hpp**](enums_8hpp.md)

[Go to the documentation of this file](enums_8hpp.md)


```C++

#pragma once

#include <stdint.h>

namespace astrea {
namespace astro {

using EnumType = uint32_t;

enum class CelestialBodyType : EnumType { UNSET, STAR, PLANET, MOON };

enum class SystemCenter : EnumType { CENTRAL_BODY, BARYCENTER };

enum class FrameAxis : EnumType {
    UNSET,
    ICRF,
    J2000,
    FIXED_ROTATING,
    LVLH,
    RIC,
    VNB,
    ENU
};

enum class RotationSequence {
    // Traditional Euler Sequences
    ZXZ,
    XYX,
    YZY,
    ZYZ,
    XZX,
    YXY,
    // Tait-Bryan Sequences
    XYZ,
    YZX,
    ZXY,
    XZY,
    ZYX,
    YXZ
};

enum class RotationType { EXTRINSIC, INTRINSIC };

} // namespace astro
} // namespace astrea
```


