/**
 * @file state/frames.hpp
 * @author Jay Iuliano (iuliano.jay@gmail.com)
 * @brief Header file for frame instances in the astro namespace
 * @version 0.1
 * @date 2025-08-05
 *
 * @copyright Copyright (c) 2025
 *
 */
#pragma once

#include <astro/frames/typedefs.hpp>

// static state/frames
#include <astro/frames/instances/EarthCenteredEarthFixed.hpp>
#include <astro/frames/instances/body_centered_inertial_frames.hpp>

// dynamic state/frames
#include <astro/frames/instances/LocalHorizontalLocalVertical.hpp>
#include <astro/frames/instances/RadialInTrackCrossTrack.hpp>
#include <astro/frames/instances/VelocityNormalBinormal.hpp>