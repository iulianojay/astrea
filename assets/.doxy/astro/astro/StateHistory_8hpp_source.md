

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

    using EventTimesMap = gtl::btree_map<std::string, std::vector<Date>>;

  public:
    StateHistory() = default;

    StateHistory(const std::size_t& objectId) :
        _objectId(objectId)
    {
    }

    ~StateHistory() = default;

    void insert(const State& state);

    void insert(const StateHistory& stateHistory);

    void fast_append(const State& state) { _states.push_back(state); }

    void fast_prepend(const State& state) { _states.insert(_states.begin(), state); }

    std::size_t size() const;

    bool empty() const;

    void clear();

    const Date& epoch() const { return _states.front().get_epoch(); }

    State& first() { return _states.front(); }

    const State& first() const { return _states.front(); }

    State& last() { return _states.back(); }

    const State& last() const { return _states.back(); }

    void set_object_id(const std::size_t& objectId) { _objectId = objectId; }

    std::size_t get_object_id() const { return _objectId; }

    const State& get_closest_state(const Date& date) const;

    State get_state_at(const Date& date, const bool allowApproximation = true) const;

    void set_event_times(const EventTimesMap& eventTimes) { _eventTimes = eventTimes; }

    const EventTimesMap& get_event_times() const { return _eventTimes; }

    EventTimesMap& get_event_times() { return _eventTimes; }

    using iterator = std::vector<State>::iterator;

    using const_iterator = std::vector<State>::const_iterator;

    iterator begin() { return _states.begin(); }

    iterator end() { return _states.end(); }

    const_iterator begin() const { return _states.begin(); }

    const_iterator end() const { return _states.end(); }

    const_iterator cbegin() const { return _states.cbegin(); }

    const_iterator cend() const { return _states.cend(); }

    void sort();

    template <IsOrbitalElements T>
    void convert_to_set()
    {
        for (auto& state : _states) {
            state.convert_to_set<T>();
        }
    }

  private:
    std::vector<State> _states; 
    EventTimesMap _eventTimes;  
    std::size_t _objectId = 0;  
};

} // namespace astro
} // namespace astrea
```


