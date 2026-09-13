/**
 * @file definitions/definitions.hpp
 * @author Jay Iuliano (iuliano.jay@gmail.com)
 * @brief Umbrella header for all concrete frame definitions.
 *
 * Includes all body-centred inertial frames, body-fixed frames, DCM
 * specializations, and dynamic (computed) frame tags.  Also pulls in
 * transformations so callers get the full in_frame machinery.
 *
 * Depends on: frames/framework, astro/systems
 *
 * @copyright Copyright (c) 2025-2026 Jay Iuliano
 *
 * The GNU Lesser General Public License (LGPL)
 *
 * This file is part of Astrea.
 */
#pragma once

#include <astro/frames/definitions/body_centered_inertial_frames.hpp>
#include <astro/frames/definitions/body_fixed_frames.hpp>
#include <astro/frames/definitions/defined_rotations.hpp>
#include <astro/frames/definitions/defined_rotations_earth.hpp>
#include <astro/frames/definitions/dynamic_frames.hpp>
#include <astro/frames/definitions/synodic_frames.hpp>
#include <astro/frames/definitions/transformations.hpp>
