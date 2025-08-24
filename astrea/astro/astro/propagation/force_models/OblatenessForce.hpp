/**
 * @file OblatenessForce.hpp
 * @author Jay Iuliano (iuliano.jay@gmail.com)
 * @brief Header file for the OblatenessForce class, which computes the gravitational force due to the oblateness of a celestial body.
 * @version 0.1
 * @date 2025-08-02
 *
 * @copyright Copyright (c) 2025
 *
 */
#pragma once

#include <astro/element_sets/OrbitalElements.hpp>
#include <astro/element_sets/orbital_elements/Cartesian.hpp>
#include <astro/platforms/Vehicle.hpp>
#include <astro/propagation/force_models/Force.hpp>
#include <astro/propagation/force_models/ForceModel.hpp>
#include <astro/systems/AstrodynamicsSystem.hpp>
#include <astro/types/typedefs.hpp>
#include <units/units.hpp>

namespace astrea {
namespace astro {

/**
 * @brief Class to compute the gravitational force due to the oblateness of a celestial body.
 *
 */
class OblatenessForce : public Force {
  public:
    /**
     * @brief Default constructor for OblatenessForce.
     */
    OblatenessForce(const AstrodynamicsSystem& sys, const std::size_t& N = 2, const std::size_t& M = 0);

    /**
     * @brief Default destructor for OblatenessForce.
     */
    ~OblatenessForce() = default;

    /**
     * @brief Computes the gravitational force due to the oblateness of a celestial body.
     *
     * @param date Date of the computation
     * @param state Cartesian state vector of the vehicle
     * @param vehicle Vehicle object representing the spacecraft
     * @param sys Astrodynamics system containing celestial body data
     * @return AccelerationVector<ECI> The computed acceleration vector due to oblateness.
     */
    AccelerationVector<ECI>
        compute_force(const Date& date, const Cartesian& state, const Vehicle& vehicle, const AstrodynamicsSystem& sys) const override;

    /**
     * @brief Sets the oblateness coefficients for the celestial body.
     * @param N Degree of the spherical harmonics
     * @param M Order of the spherical harmonics
     * @param sys Astrodynamics system containing celestial body data
     */
    void set_oblateness_coefficients(const std::size_t& N, const std::size_t& M, const AstrodynamicsSystem& sys);

  private:
    mutable std::vector<std::vector<Unitless>> P{};                       // !< Legendre polynomial coefficients
    mutable std::vector<std::vector<Unitless>> normalizingCoefficients{}; //!< Normalizing coefficients for the Legendre polynomials
    mutable std::vector<std::vector<Unitless>> C{}; //!< Cosine coefficients for the spherical harmonics
    mutable std::vector<std::vector<Unitless>> S{}; //!< Sine coefficients for the spherical harmonics

    const std::size_t N;                  //!< Degree of the spherical harmonics
    const std::size_t M;                  //!< Order of the spherical harmonics
    const CelestialBodyUniquePtr& center; //!< Pointer to the celestial body for which the oblateness force is computed

    /**
     * @brief Computes the Legendre polynomial coefficients for the oblateness force.
     * @param x Value at which to evaluate the Legendre polynomial
     */
    void assign_legendre(const Unitless& x) const;

    /**
     * @brief Sets the size of the vectors used for storing oblateness coefficients.
     * @param N Degree of the spherical harmonics
     * @param M Order of the spherical harmonics
     */
    void size_vectors(const std::size_t& N, const std::size_t& M);

    /**
     * @brief Ingests the Legendre coefficient file to populate the coefficients.
     * @param N Degree of the spherical harmonics
     * @param M Order of the spherical harmonics
     */
    void ingest_legendre_coefficient_file(const std::size_t& N, const std::size_t& M);
};

} // namespace astro
} // namespace astrea