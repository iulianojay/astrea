#pragma once

#include <vector>

#include <access/platforms/ground/GroundStation.hpp>

namespace waveguide {
namespace accesslib {

class GroundArchitecture {
  public:
    GroundArchitecture(const std::vector<GroundStation>& groundStations) :
        _groundStations(groundStations)
    {
    }
    ~GroundArchitecture() = default;

    using iterator       = std::vector<GroundStation>::iterator;
    using const_iterator = std::vector<GroundStation>::const_iterator;

    iterator begin() { return _groundStations.begin(); }
    iterator end() { return _groundStations.end(); }
    const_iterator begin() const { return _groundStations.begin(); }
    const_iterator end() const { return _groundStations.end(); }
    const_iterator cbegin() const { return _groundStations.begin(); }
    const_iterator cend() const { return _groundStations.end(); }

  private:
    std::vector<GroundStation> _groundStations;
};

} // namespace accesslib
} // namespace waveguide