

# File EventDetector.hpp

[**File List**](files.md) **>** [**astrea**](dir_b5324400686b7cece921533bb760c87a.md) **>** [**astro**](dir_1d4dcf10fc541574a93624f5c09a3d6f.md) **>** [**astro**](dir_84db6e3c60e44147f5214c05dc45afc2.md) **>** [**propagation**](dir_55ae0edd352c6621ebfa1115f28a0fff.md) **>** [**event\_detection**](dir_283e5a6c8e70b5075f630fb83b6454d7.md) **>** [**EventDetector.hpp**](EventDetector_8hpp.md)

[Go to the documentation of this file](EventDetector_8hpp.md)


```C++

#pragma once

#include <set>
#include <vector>

#include <gtl/btree.hpp>

#include <units/units.hpp>

#include <astro/propagation/event_detection/Event.hpp>

namespace astrea {
namespace astro {

class EventDetector {

    struct EventTracker {
        Event event;                   
        bool firstMeasurement;         
        Time previousTime;             
        Unitless previousValue;        
        std::set<Time> detectionTimes; 
    };

  public:
    EventDetector() = default;

    EventDetector(const std::vector<Event>& events);

    ~EventDetector() = default;

    void add_event(const Event& event);

    void add_events(const std::vector<Event>& events);

    void clear_events();

    std::vector<Event> get_events() const;

    bool detect_events(const Time& time, State& state, Vehicle& vehicle);

    gtl::btree_map<std::string, std::vector<Date>> get_event_times(const Date& epoch) const;

  private:
    std::vector<EventTracker> _eventTrackers; 

    bool detect_event(const Time& time, const Unitless& value, EventTracker& tracker) const;
};

} // namespace astro
} // namespace astrea
```


