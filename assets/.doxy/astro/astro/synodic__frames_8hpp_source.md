

# File synodic\_frames.hpp

[**File List**](files.md) **>** [**astrea**](dir_b5324400686b7cece921533bb760c87a.md) **>** [**astro**](dir_1d4dcf10fc541574a93624f5c09a3d6f.md) **>** [**astro**](dir_84db6e3c60e44147f5214c05dc45afc2.md) **>** [**frames**](dir_45ba6462728f0c3fdeb841915d341ea3.md) **>** [**definitions**](dir_0fbce91be2e6463cb25c5b2d70c0c29c.md) **>** [**synodic\_frames.hpp**](synodic__frames_8hpp.md)

[Go to the documentation of this file](synodic__frames_8hpp.md)


```C++

#pragma once

#include <astro/frames/framework/SynodicFrame.hpp>
#include <astro/systems/celestial_bodies.hpp>

namespace astrea {
namespace astro {
namespace frames {

namespace mercury_sun_barycenter {
inline constexpr struct mss final
    : SynodicFrame<"Mercury-Sun Synodic Frame", barycenters::MercurySunBarycenter, planets::Mercury, star::Sun> {
} mss;
} // namespace mercury_sun_barycenter

namespace venus_sun_barycenter {
inline constexpr struct vss final
    : SynodicFrame<"Venus-Sun Synodic Frame", barycenters::VenusSunBarycenter, planets::Venus, star::Sun> {
} vss;
} // namespace venus_sun_barycenter

namespace earth_sun_barycenter {
inline constexpr struct ess final
    : SynodicFrame<"Earth-Sun Synodic Frame", barycenters::EarthSunBarycenter, planets::Earth, star::Sun> {
} ess;
} // namespace earth_sun_barycenter

namespace earth_moon_barycenter {
inline constexpr struct ems final
    : SynodicFrame<"Earth-Moon Synodic Frame", barycenters::EarthMoonBarycenter, planets::Earth, moons::Moon> {
} ems;
} // namespace earth_moon_barycenter

namespace mars_sun_barycenter {
inline constexpr struct mss final
    : SynodicFrame<"Mars-Sun Synodic Frame", barycenters::MarsSunBarycenter, planets::Mars, star::Sun> {
} mss;
} // namespace mars_sun_barycenter

namespace jupiter_sun_barycenter {
inline constexpr struct jss final
    : SynodicFrame<"Jupiter-Sun Synodic Frame", barycenters::JupiterSunBarycenter, planets::Jupiter, star::Sun> {
} jss;
} // namespace jupiter_sun_barycenter

namespace saturn_sun_barycenter {
inline constexpr struct sss final
    : SynodicFrame<"Saturn-Sun Synodic Frame", barycenters::SaturnSunBarycenter, planets::Saturn, star::Sun> {
} sss;
} // namespace saturn_sun_barycenter

namespace uranus_sun_barycenter {
inline constexpr struct uss final
    : SynodicFrame<"Uranus-Sun Synodic Frame", barycenters::UranusSunBarycenter, planets::Uranus, star::Sun> {
} uss;
} // namespace uranus_sun_barycenter

namespace neptune_sun_barycenter {
inline constexpr struct nss final
    : SynodicFrame<"Neptune-Sun Synodic Frame", barycenters::NeptuneSunBarycenter, planets::Neptune, star::Sun> {
} nss;
} // namespace neptune_sun_barycenter

} // namespace frames
} // namespace astro
} // namespace astrea
```


