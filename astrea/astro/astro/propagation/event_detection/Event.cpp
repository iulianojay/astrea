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