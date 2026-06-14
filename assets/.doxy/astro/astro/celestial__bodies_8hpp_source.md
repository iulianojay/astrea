

# File celestial\_bodies.hpp

[**File List**](files.md) **>** [**astrea**](dir_b5324400686b7cece921533bb760c87a.md) **>** [**astro**](dir_1d4dcf10fc541574a93624f5c09a3d6f.md) **>** [**astro**](dir_84db6e3c60e44147f5214c05dc45afc2.md) **>** [**systems**](dir_a5d35e082abd602943cf6d70fa2a6872.md) **>** [**celestial\_bodies.hpp**](celestial__bodies_8hpp.md)

[Go to the documentation of this file](celestial__bodies_8hpp.md)


```C++

#pragma once

#include <astro/systems/celestial_bodies/Earth/Earth.hpp>
#include <astro/systems/celestial_bodies/Earth/Moon.hpp>
#include <astro/systems/celestial_bodies/Jupiter/Callisto.hpp>
#include <astro/systems/celestial_bodies/Jupiter/Europa.hpp>
#include <astro/systems/celestial_bodies/Jupiter/Ganymede.hpp>
#include <astro/systems/celestial_bodies/Jupiter/Io.hpp>
#include <astro/systems/celestial_bodies/Jupiter/Jupiter.hpp>
#include <astro/systems/celestial_bodies/Mars/Deimos.hpp>
#include <astro/systems/celestial_bodies/Mars/Mars.hpp>
#include <astro/systems/celestial_bodies/Mars/Phobos.hpp>
#include <astro/systems/celestial_bodies/Mercury/Mercury.hpp>
#include <astro/systems/celestial_bodies/Neptune/Neptune.hpp>
#include <astro/systems/celestial_bodies/Neptune/Triton.hpp>
#include <astro/systems/celestial_bodies/Saturn/Iapetus.hpp>
#include <astro/systems/celestial_bodies/Saturn/Rhea.hpp>
#include <astro/systems/celestial_bodies/Saturn/Saturn.hpp>
#include <astro/systems/celestial_bodies/Saturn/Titan.hpp>
#include <astro/systems/celestial_bodies/Sun/Sun.hpp>
#include <astro/systems/celestial_bodies/Uranus/Oberon.hpp>
#include <astro/systems/celestial_bodies/Uranus/Titania.hpp>
#include <astro/systems/celestial_bodies/Uranus/Uranus.hpp>
#include <astro/systems/celestial_bodies/Venus/Venus.hpp>

// Keplerian-approximation fallback for get_position_at / get_velocity_at.
// Included AFTER all planet specialisations so the fallback primary-template
// definition does not shadow any explicit specialisation.
#include <astro/systems/default_property_getters.hpp>
```


