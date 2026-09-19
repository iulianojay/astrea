/*
 * The GNU Lesser General Public License (LGPL)
 *
 * Copyright (c) 2025-2026 Jay Iuliano
 *
 * This file is part of Astrea.
 * Astrea is free software: you can redistribute it and/or modify it under the terms of the GNU Lesser General Public License
 * as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
 * Astrea is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty
 * of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU Lesser General Public License for more details. You should
 * have received a copy of the GNU General Public License along with Astrea. If not, see <https://www.gnu.org/licenses/>.
 */

#include <astro/propagation/event_detection/Event.hpp>

#include <astro/propagation/event_detection/events/NullEvent.hpp>

namespace astrea {
namespace astro {

Event::Event() :
    Event(NullEvent())
{
}

Event::Event(const Event& other) :
    _ptr(other._ptr ? other._ptr->clone() : nullptr)
{
}

Event::Event(Event&& other) noexcept :
    _ptr(std::move(other._ptr))
{
}

Event& Event::operator=(Event&& other) noexcept
{
    if (this != &other) { _ptr = std::move(other._ptr); }
    return *this;
}

Event& Event::operator=(const Event& other) { return *this = Event(other); }

const void* Event::get_ptr() const { return ptr()->get_ptr(); }

void* Event::get_ptr() { return ptr()->get_ptr(); }

} // namespace astro
} // namespace astrea