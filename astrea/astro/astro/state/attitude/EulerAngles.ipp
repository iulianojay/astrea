/**
 * @file EulerAngles.ipp
 * @author Jay Iuliano (iuliano.jay@gmail.com)
 * @brief Class representing a sequence of angles (either Euler or Tait-Bryan) for attitude transformations between state/frames.
 * @date 2026-03-22
 *
 * @copyright Copyright (c) 2025-2026 Jay Iuliano
 *
 * The GNU Lesser General Public License (LGPL)
 *
 * This file is part of Astrea.
 * Astrea is free software: you can redistribute it and/or modify it under the terms of the GNU Lesser General Public License
 * as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
 * Astrea is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty
 * of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU Lesser General Public License for more details. You should
 * have received a copy of the GNU General Public License along with Astrea. If not, see <https://www.gnu.org/licenses/>.
 *
 */
#pragma once

#include <astro/state/attitude/Quaternion.hpp>

namespace astrea {
namespace astro {

template <RotationSequence sequence, RotationType rotation_type, IsFrame auto _in_frame_, IsFrame auto _out_frame_>
template <RotationSequence sequence_u, RotationType rotation_type_u>
    requires(!IsCompatibleEulerAngles<sequence, rotation_type, _in_frame_, _out_frame_, sequence_u, rotation_type_u, _in_frame_, _out_frame_>)
EulerAngles<sequence, rotation_type, _in_frame_, _out_frame_>::EulerAngles(const EulerAngles<sequence_u, rotation_type_u, _in_frame_, _out_frame_>& other)
{
    *this = Quaternion<_in_frame_, _out_frame_>(other).template to_euler_angles<sequence, rotation_type>();
}

} // namespace astro
} // namespace astrea