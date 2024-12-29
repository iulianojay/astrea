#pragma once

#include <functional>
#include <memory>
#include <unordered_map>

#include <astro/propagation/force_models/Force.hpp>


class ForceModel {
  private:
  public:
    ForceModel()  = default;
    ~ForceModel() = default;

    template <typename T, typename... Args>
    const std::unique_ptr<Force>& add(Args&&... args)
    {
        std::string name = typeid(T).name();
        if (forces.count(name) == 0) { forces.emplace(name, std::make_unique<T>(std::forward<Args>(args)...)); }
        return forces.at(name);
    }

    AccelerationVector
        compute_forces(const double& julianDate, const OrbitalElements& state, const Vehicle& vehicle, const AstrodynamicsSystem& sys) const
    {
        AccelerationVector sum{ 0.0, 0.0, 0.0 };
        for (const auto& [name, force] : forces) {
            const auto result = force->compute_force(julianDate, state, vehicle, sys);
            for (size_t ii = 0; ii < 3; ++ii) {
                sum[ii] += result[ii];
            }
        }
        return sum;
    }

    const std::unique_ptr<Force>& at(const std::string& name) const { return forces.at(name); }

    template <typename T>
    const std::unique_ptr<Force>& get() const
    {
        std::string name = typeid(T).name();
        return forces.at(name);
    }

  private:
    std::unordered_map<std::string, std::unique_ptr<Force>> forces;
};