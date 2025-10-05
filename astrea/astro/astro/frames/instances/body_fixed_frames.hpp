/**
 * @file body_fixed_frames.hpp
 * @author Jay Iuliano (iuliano.jay@gmail.com)
 * @brief Header file for body-fixed frames. Just ECEF right now.
 * @version 0.1
 * @date 2025-08-05
 *
 * @copyright Copyright (c) 2025
 *
 */
#pragma once

#include <astro/astro.fwd.hpp>

namespace astrea {
namespace astro {
namespace frames {

namespace earth {

using earth_fixed = BodyFixedFrame<CelestialBodyId::EARTH>;

} // namespace earth

} // namespace frames
} // namespace astro
} // namespace astrea