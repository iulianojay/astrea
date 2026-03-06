

# File StateHistory.hpp

[**File List**](files.md) **>** [**astrea**](dir_b5324400686b7cece921533bb760c87a.md) **>** [**astro**](dir_1d4dcf10fc541574a93624f5c09a3d6f.md) **>** [**astro**](dir_84db6e3c60e44147f5214c05dc45afc2.md) **>** [**state**](dir_cf1a4d8122645f8636e977da512a043c.md) **>** [**StateHistory.hpp**](StateHistory_8hpp.md)

[Go to the documentation of this file](StateHistory_8hpp.md)


```C++

#pragma once

#include <gtl/btree.hpp>

#include <astro/state/State.hpp>
#include <astro/types/typedefs.hpp>

namespace astrea {
namespace astro {

class StateHistory {

    using StateMap      = gtl::btree_map<Date, State>;
    using EventTimesMap = gtl::btree_map<std::string, std::vector<Date>>;

  public:
    StateHistory() = default;

    StateHistory(const std::size_t& objectId) :
        _objectId(objectId)
    {
    }

    ~StateHistory() = default;

    State& operator[](const Date& date);

    const State& at(const Date& date) const;

    void insert(const State& state);

    std::size_t size() const;

    void clear();

    const Date& epoch() const { return _states.begin()->first; }

    const State& first() const { return _states.begin()->second; }

    const State& last() const { return _states.rbegin()->second; }

    void set_object_id(const std::size_t& objectId) { _objectId = objectId; }

    std::size_t get_object_id() const { return _objectId; }

    const State& get_closest_state(const Date& date) const;

    State get_state_at(const Date& date) const;

    void set_event_times(const EventTimesMap& eventTimes) { _eventTimes = eventTimes; }

    const EventTimesMap& get_event_times() const { return _eventTimes; }

    EventTimesMap& get_event_times() { return _eventTimes; }

    using iterator = StateMap::iterator;

    using const_iterator = StateMap::const_iterator;

    iterator begin() { return _states.begin(); }

    iterator end() { return _states.end(); }

    const_iterator begin() const { return _states.begin(); }

    const_iterator end() const { return _states.end(); }

    const_iterator cbegin() const { return _states.cbegin(); }

    const_iterator cend() const { return _states.cend(); }

  private:
    StateMap _states;          
    EventTimesMap _eventTimes; 
    std::size_t _objectId = 0; 
};

} // namespace astro
} // namespace astrea
```


