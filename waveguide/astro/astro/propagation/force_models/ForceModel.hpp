#pragma once

#include <functional>
#include <memory>
#include <unordered_map>

#include <astro/propagation/force_models/Force.hpp>
#include <units/units.hpp>

namespace waveguide {
namespace astro {

class ForceModel {
  private:
  public:
    ForceModel()  = default;
    ~ForceModel() = default;

    template <typename T, typename... Args>
    const std::unique_ptr<Force>& add(Args&&... args)
    {
        static const std::string name = typeid(T).name();
        if (forces.count(name) == 0) { forces.emplace(name, std::make_unique<T>(std::forward<Args>(args)...)); }
        return forces.at(name);
    }

    AccelerationVector
        compute_forces(const Date& date, const Cartesian& state, const Vehicle& vehicle, const AstrodynamicsSystem& sys) const;

    const std::unique_ptr<Force>& at(const std::string& name) const;

    template <typename T>
    const std::unique_ptr<Force>& get() const
    {
        static const std::string name = typeid(T).name();
        return forces.at(name);
    }

  private:
    std::unordered_map<std::string, std::unique_ptr<Force>> forces;
};

} // namespace astro
} // namespace waveguide