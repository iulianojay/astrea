

# File GroundArchitecture.hpp

[**File List**](files.md) **>** [**astrea**](dir_b5324400686b7cece921533bb760c87a.md) **>** [**trace**](dir_e30098dbada9bbfb44888190c04e2af0.md) **>** [**trace**](dir_f04035ba8afac2675c737f654641e7b5.md) **>** [**platforms**](dir_4dbda61db413396ce1d3b920f98dbf93.md) **>** [**ground**](dir_f1cb7431ef00eaab1d7c5caeb9788760.md) **>** [**GroundArchitecture.hpp**](GroundArchitecture_8hpp.md)

[Go to the documentation of this file](GroundArchitecture_8hpp.md)


```C++

#pragma once

#include <vector>

#include <astro/systems/system_concepts.hpp>

#include <trace/platforms/ground/GroundStation.hpp>

namespace astrea {
namespace trace {

template <astro::IsCelestialBody auto _body_>
class GroundArchitecture {
    using Station = GroundStation<_body_>;

  public:
    GroundArchitecture(const std::vector<Station>& groundStations) :
        _groundStations(groundStations)
    {
    }

    ~GroundArchitecture() = default;

    Station& operator[](const std::size_t& idx) { return _groundStations[idx]; }

    const Station& operator[](const std::size_t& idx) const { return _groundStations[idx]; }

    std::size_t size() const { return _groundStations.size(); }

    using iterator = typename std::vector<Station>::iterator;

    using const_iterator = typename std::vector<Station>::const_iterator;

    iterator begin() { return _groundStations.begin(); }

    iterator end() { return _groundStations.end(); }

    const_iterator begin() const { return _groundStations.begin(); }

    const_iterator end() const { return _groundStations.end(); }

    const_iterator cbegin() const { return _groundStations.begin(); }

    const_iterator cend() const { return _groundStations.end(); }

  private:
    std::vector<Station> _groundStations; 
};

} // namespace trace
} // namespace astrea
```


