#pragma once

#include <map>
#include <tuple>

#include "astro/element_sets/OrbitalElements.hpp"
#include "astro/types/typedefs.hpp"
#include "astro/types/tuple_hash.hpp"
#include "astro/systems/AstrodynamicsSystem.hpp"
#include "astro/propagation/force_models/Force.hpp"
#include "astro/propagation/force_models/ForceModel.hpp"

class AtmosphericForce : public Force {
public:

    AtmosphericForce() = default;
    ~AtmosphericForce() = default;

    basis_array compute_force(const double& julianDate, const OrbitalElements& state, const Vehicle& vehicle, const AstrodynamicsSystem& sys) const override;

private:

    const OrbitalElements find_accel_drag_and_lift(const double& julianDate, const OrbitalElements& state, const Vehicle& vehicle, const AstrodynamicsSystem& sys) const;
    const double find_atmospheric_density(const double& julianDate, const OrbitalElements& state, const CelestialBodyUniquePtr& center) const;

    static const std::map<double, double> venutianAtmosphere;
    static const std::map<double, std::tuple<double, double, double>> earthAtmosphere;
    static const std::map<double, double> martianAtmosphere;
    static const std::map<double, double> titanicAtmosphere;
};