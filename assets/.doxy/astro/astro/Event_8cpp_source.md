

# File Event.cpp

[**File List**](files.md) **>** [**astrea**](dir_b5324400686b7cece921533bb760c87a.md) **>** [**astro**](dir_1d4dcf10fc541574a93624f5c09a3d6f.md) **>** [**astro**](dir_84db6e3c60e44147f5214c05dc45afc2.md) **>** [**propagation**](dir_55ae0edd352c6621ebfa1115f28a0fff.md) **>** [**event\_detection**](dir_283e5a6c8e70b5075f630fb83b6454d7.md) **>** [**Event.cpp**](Event_8cpp.md)

[Go to the documentation of this file](Event_8cpp.md)


```C++
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
```


