#pragma once

#include "astro/element_sets/OrbitalElements.hpp"
#include "astro/types/typedefs.hpp"
#include "astro/platforms/space/Spacecraft.hpp"
#include "astro/systems/AstrodynamicsSystem.hpp"
#include "astro/propagation/force_models/Force.hpp"

class OblatenessForce : public Force {
public:
    OblatenessForce() = default;
    ~OblatenessForce() = default;

    basis_array compute_force(const double& julianDate, const OrbitalElements& state, const Spacecraft& vehicle, const AstrodynamicsSystem& sys) const;

private:

    mutable std::vector<std::vector<double>> P{};
    mutable std::vector<std::vector<double>> C{};
    mutable std::vector<std::vector<double>> S{};

    size_t N = 2, M = 0;
    bool NxMOblateness = false;

    void get_oblateness_coefficients(const size_t& N, const size_t& M, const AstrodynamicsSystem& sys);
    void assign_legendre(const double& latitude) const;
};