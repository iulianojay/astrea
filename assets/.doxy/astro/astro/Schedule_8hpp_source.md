

# File Schedule.hpp

[**File List**](files.md) **>** [**astrea**](dir_b5324400686b7cece921533bb760c87a.md) **>** [**astro**](dir_1d4dcf10fc541574a93624f5c09a3d6f.md) **>** [**astro**](dir_84db6e3c60e44147f5214c05dc45afc2.md) **>** [**propagation**](dir_55ae0edd352c6621ebfa1115f28a0fff.md) **>** [**event\_detection**](dir_283e5a6c8e70b5075f630fb83b6454d7.md) **>** [**Schedule.hpp**](Schedule_8hpp.md)

[Go to the documentation of this file](Schedule_8hpp.md)


```C++

#pragma once

#include <vector>

#include <gtl/btree.hpp>

#include <astro/astro.fwd.hpp>
#include <astro/propagation/event_detection/Event.hpp>
#include <astro/time/Date.hpp>

namespace astrea {
namespace astro {

class Schedule {
  public:
    Schedule() = default;

    void schedule_event(const Date& date, const Event& event);

    void schedule_event(const std::vector<Date>& dates, const Event& event);

    std::vector<Event> get_events_at(const Date& date) const;

    std::vector<Date> get_scheduled_dates() const;

    void clear();

    void remove_events_at(const Date& date);

    void remove_events_between(const Date& startDate, const Date& endDate);

    void trigger_scheduled_events(const Date& date, const Time& time, State& state, Vehicle& vehicle) const;

  private:
    gtl::btree_map<Date, std::vector<std::size_t>> _schedule; 
    gtl::btree_map<std::size_t, Event> _events;               
};

} // namespace astro
} // namespace astrea
```


