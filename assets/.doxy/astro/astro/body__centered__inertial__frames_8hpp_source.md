

# File body\_centered\_inertial\_frames.hpp

[**File List**](files.md) **>** [**astrea**](dir_b5324400686b7cece921533bb760c87a.md) **>** [**astro**](dir_1d4dcf10fc541574a93624f5c09a3d6f.md) **>** [**astro**](dir_84db6e3c60e44147f5214c05dc45afc2.md) **>** [**frames**](dir_45ba6462728f0c3fdeb841915d341ea3.md) **>** [**instances**](dir_a85615e9ad779999123e94bfb15c8545.md) **>** [**body\_centered\_inertial\_frames.hpp**](body__centered__inertial__frames_8hpp.md)

[Go to the documentation of this file](body__centered__inertial__frames_8hpp.md)


```C++

#pragma once

#include <astro/astro.fwd.hpp>

namespace astrea {
namespace astro {
namespace frames {

namespace sun {
using icrf  = InertialFrame<CelestialBodyId::SUN, FrameAxis::ICRF>;
using j2000 = InertialFrame<CelestialBodyId::SUN, FrameAxis::J2000>;
} // namespace sun

namespace mercury {
using icrf  = InertialFrame<CelestialBodyId::MERCURY, FrameAxis::ICRF>;
using j2000 = InertialFrame<CelestialBodyId::MERCURY, FrameAxis::J2000>;
} // namespace mercury

namespace venus {
using icrf  = InertialFrame<CelestialBodyId::VENUS, FrameAxis::ICRF>;
using j2000 = InertialFrame<CelestialBodyId::VENUS, FrameAxis::J2000>;
} // namespace venus

namespace earth {
using icrf  = InertialFrame<CelestialBodyId::EARTH, FrameAxis::ICRF>;  // GCRF frame, sometimes ECI
using j2000 = InertialFrame<CelestialBodyId::EARTH, FrameAxis::J2000>; // EME2000 frame, sometimes ECI
} // namespace earth

namespace moon {
using icrf  = InertialFrame<CelestialBodyId::MOON, FrameAxis::ICRF>;
using j2000 = InertialFrame<CelestialBodyId::MOON, FrameAxis::J2000>;
} // namespace moon

namespace mars {
using icrf  = InertialFrame<CelestialBodyId::MARS, FrameAxis::ICRF>;
using j2000 = InertialFrame<CelestialBodyId::MARS, FrameAxis::J2000>;
} // namespace mars

namespace phobos {
using icrf  = InertialFrame<CelestialBodyId::PHOBOS, FrameAxis::ICRF>;
using j2000 = InertialFrame<CelestialBodyId::PHOBOS, FrameAxis::J2000>;
} // namespace phobos

namespace deimos {
using icrf  = InertialFrame<CelestialBodyId::DEIMOS, FrameAxis::ICRF>;
using j2000 = InertialFrame<CelestialBodyId::DEIMOS, FrameAxis::J2000>;
} // namespace deimos

namespace jupiter {
using icrf  = InertialFrame<CelestialBodyId::JUPITER, FrameAxis::ICRF>;
using j2000 = InertialFrame<CelestialBodyId::JUPITER, FrameAxis::J2000>;
} // namespace jupiter

namespace ganymede {
using icrf  = InertialFrame<CelestialBodyId::GANYMEDE, FrameAxis::ICRF>;
using j2000 = InertialFrame<CelestialBodyId::GANYMEDE, FrameAxis::J2000>;
} // namespace ganymede

namespace callisto {
using icrf  = InertialFrame<CelestialBodyId::CALLISTO, FrameAxis::ICRF>;
using j2000 = InertialFrame<CelestialBodyId::CALLISTO, FrameAxis::J2000>;
} // namespace callisto

namespace io {
using icrf  = InertialFrame<CelestialBodyId::IO, FrameAxis::ICRF>;
using j2000 = InertialFrame<CelestialBodyId::IO, FrameAxis::J2000>;
} // namespace io

namespace europa {
using icrf  = InertialFrame<CelestialBodyId::EUROPA, FrameAxis::ICRF>;
using j2000 = InertialFrame<CelestialBodyId::EUROPA, FrameAxis::J2000>;
} // namespace europa

namespace saturn {
using icrf  = InertialFrame<CelestialBodyId::SATURN, FrameAxis::ICRF>;
using j2000 = InertialFrame<CelestialBodyId::SATURN, FrameAxis::J2000>;
} // namespace saturn

namespace titan {
using icrf  = InertialFrame<CelestialBodyId::TITAN, FrameAxis::ICRF>;
using j2000 = InertialFrame<CelestialBodyId::TITAN, FrameAxis::J2000>;
} // namespace titan

namespace rhea {
using icrf  = InertialFrame<CelestialBodyId::RHEA, FrameAxis::ICRF>;
using j2000 = InertialFrame<CelestialBodyId::RHEA, FrameAxis::J2000>;
} // namespace rhea

namespace iapetus {
using icrf  = InertialFrame<CelestialBodyId::IAPETUS, FrameAxis::ICRF>;
using j2000 = InertialFrame<CelestialBodyId::IAPETUS, FrameAxis::J2000>;
} // namespace iapetus

namespace uranus {
using icrf  = InertialFrame<CelestialBodyId::URANUS, FrameAxis::ICRF>;
using j2000 = InertialFrame<CelestialBodyId::URANUS, FrameAxis::J2000>;
} // namespace uranus

namespace titania {
using icrf  = InertialFrame<CelestialBodyId::TITANIA, FrameAxis::ICRF>;
using j2000 = InertialFrame<CelestialBodyId::TITANIA, FrameAxis::J2000>;
} // namespace titania

namespace oberon {
using icrf  = InertialFrame<CelestialBodyId::OBERON, FrameAxis::ICRF>;
using j2000 = InertialFrame<CelestialBodyId::OBERON, FrameAxis::J2000>;
} // namespace oberon

namespace neptune {
using icrf  = InertialFrame<CelestialBodyId::NEPTUNE, FrameAxis::ICRF>;
using j2000 = InertialFrame<CelestialBodyId::NEPTUNE, FrameAxis::J2000>;
} // namespace neptune

namespace triton {
using icrf  = InertialFrame<CelestialBodyId::TRITON, FrameAxis::ICRF>;
using j2000 = InertialFrame<CelestialBodyId::TRITON, FrameAxis::J2000>;
} // namespace triton

namespace solar_system_barycenter {
using icrf  = InertialFrame<CelestialBodyId::SOLAR_SYSTEM_BARYCENTER, FrameAxis::ICRF>; // Generally, the ICRF frame
using j2000 = InertialFrame<CelestialBodyId::SOLAR_SYSTEM_BARYCENTER, FrameAxis::J2000>;
} // namespace solar_system_barycenter

namespace mercury_barycenter {
using icrf  = InertialFrame<CelestialBodyId::MERCURY_BARYCENTER, FrameAxis::ICRF>;
using j2000 = InertialFrame<CelestialBodyId::MERCURY_BARYCENTER, FrameAxis::J2000>;
} // namespace mercury_barycenter

namespace venus_barycenter {
using icrf  = InertialFrame<CelestialBodyId::VENUS_BARYCENTER, FrameAxis::ICRF>;
using j2000 = InertialFrame<CelestialBodyId::VENUS_BARYCENTER, FrameAxis::J2000>;
} // namespace venus_barycenter

namespace earth_barycenter {
using icrf  = InertialFrame<CelestialBodyId::EARTH_BARYCENTER, FrameAxis::ICRF>;
using j2000 = InertialFrame<CelestialBodyId::EARTH_BARYCENTER, FrameAxis::J2000>;
} // namespace earth_barycenter

namespace mars_barycenter {
using icrf  = InertialFrame<CelestialBodyId::MARS_BARYCENTER, FrameAxis::ICRF>;
using j2000 = InertialFrame<CelestialBodyId::MARS_BARYCENTER, FrameAxis::J2000>;
} // namespace mars_barycenter

namespace jupiter_barycenter {
using icrf  = InertialFrame<CelestialBodyId::JUPITER_BARYCENTER, FrameAxis::ICRF>;
using j2000 = InertialFrame<CelestialBodyId::JUPITER_BARYCENTER, FrameAxis::J2000>;
} // namespace jupiter_barycenter

namespace saturn_barycenter {
using icrf  = InertialFrame<CelestialBodyId::SATURN_BARYCENTER, FrameAxis::ICRF>;
using j2000 = InertialFrame<CelestialBodyId::SATURN_BARYCENTER, FrameAxis::J2000>;
} // namespace saturn_barycenter

namespace uranus_barycenter {
using icrf  = InertialFrame<CelestialBodyId::URANUS_BARYCENTER, FrameAxis::ICRF>;
using j2000 = InertialFrame<CelestialBodyId::URANUS_BARYCENTER, FrameAxis::J2000>;
} // namespace uranus_barycenter

namespace neptune_barycenter {
using icrf  = InertialFrame<CelestialBodyId::NEPTUNE_BARYCENTER, FrameAxis::ICRF>;
using j2000 = InertialFrame<CelestialBodyId::NEPTUNE_BARYCENTER, FrameAxis::J2000>;
} // namespace neptune_barycenter

} // namespace frames
} // namespace astro
} // namespace astrea
```


