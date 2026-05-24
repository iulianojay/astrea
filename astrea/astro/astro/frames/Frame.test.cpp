/*
 * The GNU Lesser General Public License (LGPL)
 *
 * Copyright (c) 2025 Jay Iuliano
 *
 * This file is part of Astrea.
 * Astrea is free software: you can redistribute it and/or modify it under the terms of the GNU Lesser General Public License
 * as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
 * Astrea is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty
 * of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU Lesser General Public License for more details. You should
 * have received a copy of the GNU General Public License along with Astrea. If not, see <https://www.gnu.org/licenses/>.
 */

#include <gtest/gtest.h>

#include <type_traits>

#include <astro/frames/Frame.hpp>
#include <astro/frames/frame_concepts.hpp>
#include <astro/frames/frames.hpp>

using namespace astrea::astro;

// Origin checks: origin member is a typed struct value — compare types.
static_assert(frames::earth::icrf.origin == planets::Earth);
static_assert(frames::earth::earth_fixed.origin == planets::Earth);
static_assert(frames::mars::icrf.origin == planets::Mars);
static_assert(frames::sun::icrf.origin == planets::Sun);

// Axis checks: axis member is a typed struct value — compare types.
static_assert(frames::earth::icrf.axis == axes::icrf);
static_assert(frames::earth::j2000.axis == axes::j2000);
static_assert(IsFixedRotatingFrame<frames::earth::earth_fixed>);

// Parent checks: parent member is a constexpr value — compare decltype.
static_assert(frames::earth::earth_fixed.parent == frames::earth::icrf);
static_assert(!IsDerivedFrame<frames::earth::icrf>);
static_assert(!IsDerivedFrame<frames::earth::j2000>);
static_assert(IsDerivedFrame<frames::earth::earth_fixed>);

static_assert(IsFrame<frames::earth::icrf>);
static_assert(IsFrame<frames::earth::j2000>);
static_assert(IsFrame<frames::earth::earth_fixed>);
static_assert(IsFrame<frames::mars::icrf>);
static_assert(!IsFrame<int>);

static_assert(IsInertialFrame<frames::earth::icrf>);
static_assert(IsInertialFrame<frames::earth::j2000>);
static_assert(IsInertialFrame<frames::mars::icrf>);
static_assert(!IsInertialFrame<frames::earth::earth_fixed>);

static_assert(IsFixedRotatingFrame<frames::earth::earth_fixed>);
static_assert(!IsFixedRotatingFrame<frames::earth::icrf>);
static_assert(!IsFixedRotatingFrame<frames::earth::j2000>);

static_assert(IsStaticFrame<frames::earth::icrf>);
static_assert(IsStaticFrame<frames::earth::j2000>);
static_assert(IsStaticFrame<frames::earth::earth_fixed>);

static_assert(frames::earth::icrf.origin == frames::earth::j2000.origin);
static_assert(frames::earth::icrf.origin == frames::earth::earth_fixed.origin);
static_assert(frames::earth::icrf.origin != frames::mars::icrf.origin);
static_assert(frames::earth::icrf.origin != frames::sun::icrf.origin);

static_assert(frames::earth::icrf.axis == frames::mars::icrf.axis);
static_assert(frames::earth::j2000.axis == frames::mars::j2000.axis);
static_assert(frames::earth::icrf.axis != frames::earth::j2000.axis);
static_assert(frames::earth::icrf.axis != frames::earth::earth_fixed.axis);

static_assert(frames::earth::icrf == frames::earth::icrf);
static_assert(frames::mars::icrf == frames::mars::icrf);
static_assert(frames::earth::icrf != frames::earth::j2000);
static_assert(frames::earth::icrf != frames::mars::icrf);
static_assert(frames::earth::icrf != frames::earth::earth_fixed);
