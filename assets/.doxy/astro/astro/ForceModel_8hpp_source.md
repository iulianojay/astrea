

# File ForceModel.hpp

[**File List**](files.md) **>** [**astrea**](dir_b5324400686b7cece921533bb760c87a.md) **>** [**astro**](dir_1d4dcf10fc541574a93624f5c09a3d6f.md) **>** [**astro**](dir_84db6e3c60e44147f5214c05dc45afc2.md) **>** [**propagation**](dir_55ae0edd352c6621ebfa1115f28a0fff.md) **>** [**force\_models**](dir_0ce51a85166db93c377c5b7f000b236c.md) **>** [**ForceModel.hpp**](ForceModel_8hpp.md)

[Go to the documentation of this file](ForceModel_8hpp.md)


```C++

#pragma once

#include <functional>
#include <memory>
#include <string>
#include <unordered_map>

#include <units/units.hpp>

#include <astro/astro.fwd.hpp>
#include <astro/propagation/force_models/PerturbingForce.hpp>

namespace astrea {
namespace astro {

class ForceModel {
  public:
    ForceModel() = default;

    ~ForceModel() = default;

    std::size_t size() const { return forces.size(); }

    template <typename T, typename... Args>
    const std::unique_ptr<PerturbingForce>& add(Args&&... args)
    {
        static const std::string name = typeid(T).name();
        if (forces.count(name) == 0) { forces.emplace(name, std::make_unique<T>(std::forward<Args>(args)...)); }
        return forces.at(name);
    }

    template <template <auto...> class Pert, auto... Params, typename... Args>
    const std::unique_ptr<PerturbingForce>& add(Args&&... args)
    {
        using T                       = Pert<Params...>;
        static const std::string name = typeid(T).name();
        if (forces.count(name) == 0) { forces.emplace(name, std::make_unique<T>(std::forward<Args>(args)...)); }
        return forces.at(name);
    }

    Perturbation compute_perturbations(const State& state, const Vehicle& vehicle) const;

    const std::unique_ptr<PerturbingForce>& at(const std::string& name) const;

    template <typename T>
    const std::unique_ptr<PerturbingForce>& get() const
    {
        static const std::string name = typeid(T).name();
        return forces.at(name);
    }

  private:
    std::unordered_map<std::string, std::unique_ptr<PerturbingForce>> forces; 
};

} // namespace astro
} // namespace astrea
```


