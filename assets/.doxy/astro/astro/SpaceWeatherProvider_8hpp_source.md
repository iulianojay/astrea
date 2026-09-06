

# File SpaceWeatherProvider.hpp

[**File List**](files.md) **>** [**astrea**](dir_b5324400686b7cece921533bb760c87a.md) **>** [**astro**](dir_1d4dcf10fc541574a93624f5c09a3d6f.md) **>** [**astro**](dir_84db6e3c60e44147f5214c05dc45afc2.md) **>** [**propagation**](dir_55ae0edd352c6621ebfa1115f28a0fff.md) **>** [**force\_models**](dir_0ce51a85166db93c377c5b7f000b236c.md) **>** [**space\_weather**](dir_ba92a5bb4647772267966b3cef944594.md) **>** [**SpaceWeatherProvider.hpp**](SpaceWeatherProvider_8hpp.md)

[Go to the documentation of this file](SpaceWeatherProvider_8hpp.md)


```C++

#pragma once

#include <memory>
#include <utility>

#include <astro/propagation/force_models/space_weather/SpaceWeatherData.hpp>

namespace astrea {
namespace astro {

class SpaceWeatherProvider {
  public:
    using DataPtr = std::shared_ptr<const SpaceWeatherData>;

    SpaceWeatherProvider() = default;

    explicit SpaceWeatherProvider(DataPtr data) :
        _data(std::move(data))
    {
    }

    explicit SpaceWeatherProvider(SpaceWeatherData data) :
        _data(std::make_shared<const SpaceWeatherData>(std::move(data)))
    {
    }

    template <typename... Args>
    explicit SpaceWeatherProvider(std::in_place_t, Args&&... args) :
        _data(std::make_shared<const SpaceWeatherData>(std::forward<Args>(args)...))
    {
    }

    [[nodiscard]] std::size_t size() const { return _data ? _data->size() : 0; }

    [[nodiscard]] bool empty() const noexcept { return !_data || _data->empty(); }

    [[nodiscard]] const DataPtr& data() const noexcept { return _data; }

  private:
    DataPtr _data; //<! Shared immutable space weather data snapshot
};

} // namespace astro
} // namespace astrea
```


