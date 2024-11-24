#pragma once

#include "astro/element_sets/OrbitalElements.hpp"
#include "astro/types/typedefs.hpp"
#include "astro/platforms/space/Spacecraft.hpp"
#include "astro/systems/AstrodynamicsSystem.hpp"
#include "astro/propagation/force_models/Force.hpp"
#include "astro/propagation/force_models/ForceModel.hpp"

class OblatenessForce : public Force {
public:
    OblatenessForce(const AstrodynamicsSystem& sys, const size_t& N = 2, const size_t& M = 0);
    ~OblatenessForce() = default;

    basis_array compute_force(const double& julianDate, const OrbitalElements& state, const Spacecraft& vehicle, const AstrodynamicsSystem& sys) const override;
    void set_oblateness_coefficients(const size_t& N, const size_t& M, const AstrodynamicsSystem& sys);

private:

    mutable std::vector<std::vector<double>> P{};
    mutable std::vector<std::vector<double>> C{};
    mutable std::vector<std::vector<double>> S{};

    std::vector<std::vector<double>> alpha;
    std::vector<std::vector<double>> beta;
    std::vector<std::vector<double>> gamma;
    std::vector<std::vector<double>> Pbase;

    const size_t N;
    const size_t M;
    const GravitationalBody& center;

    void assign_legendre(const double& latitude) const;
};
