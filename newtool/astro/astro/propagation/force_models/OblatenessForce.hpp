#pragma once

#include <astro/element_sets/OrbitalElements.hpp>
#include <astro/element_sets/orbital_elements/Cartesian.hpp>
#include <astro/platforms/Vehicle.hpp>
#include <astro/propagation/force_models/Force.hpp>
#include <astro/propagation/force_models/ForceModel.hpp>
#include <astro/systems/AstrodynamicsSystem.hpp>
#include <astro/types/typedefs.hpp>

class OblatenessForce : public Force {
  public:
    OblatenessForce(const AstrodynamicsSystem& sys, const size_t& N = 2, const size_t& M = 0);
    ~OblatenessForce() = default;

    AccelerationVector compute_force(
        const mp_units::quantity<mp_units::non_si::day>& julianDate,
        const Cartesian& state,
        const Vehicle& vehicle,
        const AstrodynamicsSystem& sys
    ) const override;
    void set_oblateness_coefficients(const size_t& N, const size_t& M, const AstrodynamicsSystem& sys);

  private:
    using Altitude = mp_units::quantity<mp_units::si::unit_symbols::km>;
    using Unitless = mp_units::quantity<mp_units::one>;

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

    void assign_legendre(const Altitude& latitude) const;
    void size_vectors(const size_t& N, const size_t& M);
    void ingest_legendre_coefficient_file(const size_t& N, const size_t& M);
};
