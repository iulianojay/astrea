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
    const std::unique_ptr<Force>& add(Args&&... args);

    AccelerationVector
        compute_forces(const JulianDate& julianDate, const Cartesian& state, const Vehicle& vehicle, const AstrodynamicsSystem& sys) const;

    const std::unique_ptr<Force>& at(const std::string& name) const;

    template <typename T>
    const std::unique_ptr<Force>& get() const;

  private:
    std::unordered_map<std::string, std::unique_ptr<Force>> forces;
};