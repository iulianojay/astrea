

# File PerturbingForce.hpp

[**File List**](files.md) **>** [**astrea**](dir_b5324400686b7cece921533bb760c87a.md) **>** [**astro**](dir_1d4dcf10fc541574a93624f5c09a3d6f.md) **>** [**astro**](dir_84db6e3c60e44147f5214c05dc45afc2.md) **>** [**propagation**](dir_55ae0edd352c6621ebfa1115f28a0fff.md) **>** [**force\_models**](dir_0ce51a85166db93c377c5b7f000b236c.md) **>** [**PerturbingForce.hpp**](PerturbingForce_8hpp.md)

[Go to the documentation of this file](PerturbingForce_8hpp.md)


```C++

#pragma once

#include <memory>

#include <astro/astro.fwd.hpp>
#include <astro/propagation/force_models/Perturbation.hpp>
#include <astro/propagation/force_models/space_weather/SpaceWeatherProvider.hpp>

namespace astrea {
namespace astro {

class PerturbingForce {
  public:
    PerturbingForce() = default;

    virtual ~PerturbingForce() = default;

    virtual Perturbation compute_perturbation(const State& state, const Vehicle& vehicle) const = 0;

    virtual std::unique_ptr<PerturbingForce> clone() const = 0;

    void bind_space_weather_provider(std::shared_ptr<const SpaceWeatherProvider> provider)
    {
        _provider = std::move(provider);
    }

    [[nodiscard]] const std::shared_ptr<const SpaceWeatherProvider>& get_space_weather_provider() const noexcept
    {
        return _provider;
    }

    [[nodiscard]] std::shared_ptr<const SpaceWeatherData> get_space_weather_data() const noexcept
    {
        return _provider ? _provider->data() : nullptr;
    }

  private:
    std::shared_ptr<const SpaceWeatherProvider> _provider;
};

} // namespace astro
} // namespace astrea
```


