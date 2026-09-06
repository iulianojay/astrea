

# File ForceModel.hpp

[**File List**](files.md) **>** [**astrea**](dir_b5324400686b7cece921533bb760c87a.md) **>** [**astro**](dir_1d4dcf10fc541574a93624f5c09a3d6f.md) **>** [**astro**](dir_84db6e3c60e44147f5214c05dc45afc2.md) **>** [**propagation**](dir_55ae0edd352c6621ebfa1115f28a0fff.md) **>** [**force\_models**](dir_0ce51a85166db93c377c5b7f000b236c.md) **>** [**ForceModel.hpp**](ForceModel_8hpp.md)

[Go to the documentation of this file](ForceModel_8hpp.md)


```C++

#pragma once

#include <functional>
#include <memory>
#include <string>
#include <unordered_map>
#include <utility>

#include <units/units.hpp>

#include <astro/astro.fwd.hpp>
#include <astro/propagation/force_models/PerturbingForce.hpp>
#include <astro/propagation/force_models/space_weather/SpaceWeatherProvider.hpp>

namespace astrea {
namespace astro {

class ForceModel {
  public:
    ForceModel();

    explicit ForceModel(std::shared_ptr<const SpaceWeatherData> data);

    explicit ForceModel(SpaceWeatherProvider provider);

    explicit ForceModel(SpaceWeatherData data);

    template <typename... Args>
    explicit ForceModel(std::in_place_t, Args&&... args) :
        _spaceWeatherProvider(std::make_shared<SpaceWeatherProvider>(std::in_place, std::forward<Args>(args)...))
    {
    }

    ~ForceModel() = default;

    ForceModel(const ForceModel& other);

    ForceModel(ForceModel&&) noexcept = default;

    ForceModel& operator=(const ForceModel& other);

    ForceModel& operator=(ForceModel&&) noexcept = default;

    std::size_t size() const { return forces.size(); }

    template <typename T, typename... Args>
    const std::unique_ptr<PerturbingForce>& add(Args&&... args)
    {
        static const std::string name = typeid(T).name();
        if (forces.count(name) == 0) {
            auto force = std::make_unique<T>(std::forward<Args>(args)...);
            force->bind_space_weather_provider(_spaceWeatherProvider);
            forces.emplace(name, std::move(force));
        }
        return forces.at(name);
    }

    template <template <auto...> class Pert, auto... Params, typename... Args>
    const std::unique_ptr<PerturbingForce>& add(Args&&... args)
    {
        using T                       = Pert<Params...>;
        static const std::string name = typeid(T).name();
        if (forces.count(name) == 0) {
            auto force = std::make_unique<T>(std::forward<Args>(args)...);
            force->bind_space_weather_provider(_spaceWeatherProvider);
            forces.emplace(name, std::move(force));
        }
        return forces.at(name);
    }

    [[nodiscard]] const std::shared_ptr<const SpaceWeatherProvider>& space_weather_provider() const noexcept
    {
        return _spaceWeatherProvider;
    }

    Perturbation compute_perturbations(const State& state, const Vehicle& vehicle) const;

    const std::unique_ptr<PerturbingForce>& at(const std::string& name) const;

    template <typename T>
    const std::unique_ptr<PerturbingForce>& get() const
    {
        static const std::string name = typeid(T).name();
        return forces.at(name);
    }

    void set_space_weather_provider(std::shared_ptr<const SpaceWeatherProvider> provider);

    void set_space_weather_provider(SpaceWeatherProvider provider);

    void set_space_weather_provider(SpaceWeatherData data);

  private:
    std::shared_ptr<const SpaceWeatherProvider> _spaceWeatherProvider;
    std::unordered_map<std::string, std::unique_ptr<PerturbingForce>> forces; 
};

} // namespace astro
} // namespace astrea
```


