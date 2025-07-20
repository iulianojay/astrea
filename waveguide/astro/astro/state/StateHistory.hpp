#pragma once

#include <map>

#include <astro/state/State.hpp>
#include <astro/types/typedefs.hpp>

namespace waveguide {
namespace astro {

class StateHistory {
  public:
    StateHistory() = default;
    StateHistory(const std::size_t& objectId) :
        _objectId(objectId)
    {
    }
    ~StateHistory() = default;

    State& operator[](const Time& time);
    const State& at(const Time& time) const;

    void insert(const Time& time, const State& state);
    std::size_t size() const;
    void clear();

    const State& first() const { return _states.begin()->second; }
    const State& last() const { return _states.rbegin()->second; }

    void set_object_id(const std::size_t& objectId) { _objectId = objectId; }
    std::size_t get_object_id() const { return _objectId; }

    const State& get_closest_state(const Time& time) const;
    const State& get_state_at(const Time& time);

    using iterator       = std::map<Time, State>::iterator;
    using const_iterator = std::map<Time, State>::const_iterator;

    iterator begin() { return _states.begin(); }
    iterator end() { return _states.end(); }
    const_iterator begin() const { return _states.begin(); }
    const_iterator end() const { return _states.end(); }
    const_iterator cbegin() const { return _states.cbegin(); }
    const_iterator cend() const { return _states.cend(); }

  private:
    std::map<Time, State> _states;
    std::size_t _objectId;
};

} // namespace astro
} // namespace waveguide