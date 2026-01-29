/**
 * @file OblatenessForce.hpp
 * @author Jay Iuliano (iuliano.jay@gmail.com)
 * @brief Header file for the OblatenessForce class, which computes the gravitational force due to the oblateness of a celestial body.
 * @date 2025-08-02
 *
 * @copyright Copyright (c) 2025 Jay Iuliano
 *
 * The GNU Lesser General Public License (LGPL)
 *
 * This file is part of Astrea.
 * Astrea is free software: you can redistribute it and/or modify it under the terms of the GNU Lesser General Public License
 * as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
 * Astrea is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty
 * of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU Lesser General Public License for more details. You should
 * have received a copy of the GNU General Public License along with Astrea. If not, see <https://www.gnu.org/licenses/>.
 *
 */
#pragma once

#include <array>
#include <memory>
#include <vector>

#include <units/units.hpp>

#include <astro/astro.fwd.hpp>
#include <astro/propagation/force_models/Force.hpp>

namespace astrea {
namespace astro {

class LegendreCache {
  public:
    /**
     * @brief Default constructor for LegendreCache.
     */
    LegendreCache() = default;

    /**
     * @brief Default destructor for LegendreCache.
     */
    ~LegendreCache() = default;

    /**
     * @brief Builds the cache for Legendre polynomials and coefficients.
     *
     * @param sys Astrodynamics system containing celestial body data
     * @param degree Degree of the spherical harmonics
     * @param order Order of the spherical harmonics
     */
    LegendreCache(const AstrodynamicsSystem& sys, const std::size_t& degree, const std::size_t& order);

    /**
     * @brief Gets the cosine coefficient for given n and m.
     *
     * @param n Degree of the polynomial
     * @param m Order of the polynomial
     * @return Unitless The value of the cosine coefficient Cnm
     */
    Unitless get_cosine_coefficient(const std::size_t& n, const std::size_t& m) const;

    /**
     * @brief Gets the sine coefficient for given n and m.
     *
     * @param n Degree of the polynomial
     * @param m Order of the polynomial
     * @return Unitless The value of the sine coefficient Snm
     */
    Unitless get_sine_coefficient(const std::size_t& n, const std::size_t& m) const;

    /**
     * @brief Computes the Legendre polynomial coefficients for the oblateness force.
     *
     * @param x Value at which to evaluate the Legendre polynomial
     * @param degree Degree of the spherical harmonics
     * @param order Order of the spherical harmonics
     */
    std::vector<std::vector<Unitless>>
        get_legendre_coefficients(const std::size_t& degree, const std::size_t& order, const Unitless& x) const;

  private:
    std::vector<std::vector<Unitless>> _normalizingCoefficients{}; //!< Normalizing coefficients for the Legendre polynomials
    std::vector<std::vector<Unitless>> _C{};                       //!< Cosine coefficients for the spherical harmonics
    std::vector<std::vector<Unitless>> _S{};                       //!< Sine coefficients for the spherical harmonics

    /**
     * @brief Sets the size of the vectors used for storing oblateness coefficients.
     *
     * @param degree Degree of the spherical harmonics
     * @param order Order of the spherical harmonics
     */
    void size_vectors(const std::size_t& degree, const std::size_t& order);

    /**
     * @brief Ingests the Legendre coefficient file to populate the coefficients.
     *
     * @param sys Astrodynamics system containing celestial body data
     * @param degree Degree of the spherical harmonics
     * @param order Order of the spherical harmonics
     */
    void ingest_legendre_coefficient_file(const AstrodynamicsSystem& sys, const std::size_t& degree, const std::size_t& order);
};

/**
 * @brief Class to compute the gravitational force due to the oblateness of a celestial body.
 *
 */
class OblatenessForce : public Force {
  public:
    /**
     * @brief Default destructor for OblatenessForce.
     */
    ~OblatenessForce() = default;

    /**
     * @brief Constructor for OblatenessForce.
     * @param sys Astrodynamics system containing celestial body data
     * @param N Degree of the spherical harmonics (default is 2)
     * @param M Order of the spherical harmonics (default is 0)
     * @param findExactLegendre Whether to find exact Legendre values (default is false)
     * @param useFastLegendre Whether to use fast lookup for Legendre polynomials without interpolation (default is true)
     */
    OblatenessForce(const AstrodynamicsSystem& sys, const std::size_t& N = 2, const std::size_t& M = 0);

    /**
     * @brief Computes the gravitational force due to the oblateness of a celestial body.
     *
     * @param date Date of the computation
     * @param state Cartesian state vector of the vehicle
     * @param vehicle Vehicle object representing the spacecraft
     * @param sys Astrodynamics system containing celestial body data
     * @return AccelerationVector<frames::earth::icrf> The computed acceleration vector due to oblateness.
     */
    CartesianVector<Acceleration, frames::earth::icrf>
        compute_force(const Date& date, const Cartesian& state, const Vehicle& vehicle, const AstrodynamicsSystem& sys) const override;

  private:
    const std::size_t _degree;          //!< Degree of the spherical harmonics
    const std::size_t _order;           //!< Order of the spherical harmonics
    const AstrodynamicsSystem* _sys;    //!< Pointer to the astrodynamics system
    const LegendreCache _legendreCache; //!< Cache for Legendre polynomials and coefficients
};

} // namespace astro
} // namespace astrea