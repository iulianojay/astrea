#pragma once

#include <astro/element_sets/OrbitalElements.hpp>
#include <astro/element_sets/orbital_elements/Cartesian.hpp>
#include <astro/platforms/Vehicle.hpp>
#include <astro/propagation/force_models/Force.hpp>
#include <astro/propagation/force_models/ForceModel.hpp>
#include <astro/systems/AstrodynamicsSystem.hpp>
#include <astro/types/typedefs.hpp>
#include <astro/units/units.hpp>

namespace astro {

class OblatenessForce : public Force {
  public:
    OblatenessForce(const AstrodynamicsSystem& sys, const size_t& N = 2, const size_t& M = 0);
    ~OblatenessForce() = default;

    AccelerationVector
        compute_force(const Date& date, const Cartesian& state, const Vehicle& vehicle, const AstrodynamicsSystem& sys) const override;
    void set_oblateness_coefficients(const size_t& N, const size_t& M, const AstrodynamicsSystem& sys);

  private:
    mutable std::vector<std::vector<Unitless>> P{};
    mutable std::vector<std::vector<Unitless>> C{};
    mutable std::vector<std::vector<Unitless>> S{};

    std::vector<std::vector<Unitless>> alpha;
    std::vector<std::vector<Unitless>> beta;
    std::vector<std::vector<Unitless>> gamma;
    std::vector<std::vector<Unitless>> Pbase;

    const size_t N;
    const size_t M;
    const CelestialBodyUniquePtr& center;

    void assign_legendre(const Angle& latitude) const;
    void size_vectors(const size_t& N, const size_t& M);
    void ingest_legendre_coefficient_file(const size_t& N, const size_t& M);
};

} // namespace astro