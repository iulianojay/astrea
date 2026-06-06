/**
 * @file framework/framework.hpp
 * @author Jay Iuliano (iuliano.jay@gmail.com)
 * @brief Umbrella header for the frames framework layer.
 *
 * Includes all abstract frame building blocks: type definitions, concepts,
 * registry, and utility helpers.  Does NOT include any concrete frame
 * instances or DCM specialisations — see frames/definitions/definitions.hpp
 * for those.
 *
 * @copyright Copyright (c) 2025 Jay Iuliano
 *
 * The GNU Lesser General Public License (LGPL)
 *
 * This file is part of Astrea.
 */
#pragma once

#include <astro/frames/definitions/frame_registry.hpp>
#include <astro/frames/definitions/primary_frame.hpp>
#include <astro/frames/framework/Axis.hpp>
#include <astro/frames/framework/BodyFixedFrame.hpp>
#include <astro/frames/framework/CartesianVector.hpp>
#include <astro/frames/framework/DirectionCosineMatrix.hpp>
#include <astro/frames/framework/DynamicFrame.hpp>
#include <astro/frames/framework/FixedOffsetFrame.hpp>
#include <astro/frames/framework/Frame.hpp>
#include <astro/frames/framework/Origin.hpp>
#include <astro/frames/framework/SynodicFrame.hpp>
#include <astro/frames/framework/frame_concepts.hpp>
#include <astro/frames/framework/frame_utilities.hpp>
