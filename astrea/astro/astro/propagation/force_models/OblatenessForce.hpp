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
     * @param sys Astrodynamics system containing celestial body data
     * @param N Degree of the spherical harmonics
     * @param M Order of the spherical harmonics
     */
    LegendreCache(const AstrodynamicsSystem& sys, const std::size_t& N, const std::size_t& M);

    /**
     * @brief Gets the precomputed Legendre polynomial value for given n, m, and x. Uses interpolation.
     *
     * @param n Degree of the polynomial
     * @param m Order of the polynomial
     * @param x Value at which to evaluate the polynomial
     * @return Unitless The value of the Legendre polynomial Pnm at x
     */
    Unitless get_legendre_polynomial_interp(const std::size_t& n, const std::size_t& m, const Unitless& x) const;

    /**
     * @brief Gets the precomputed Legendre polynomial value for given n, m, and x. Uses fast lookup without interpolation.
     *
     * @param n Degree of the polynomial
     * @param m Order of the polynomial
     * @param x Value at which to evaluate the polynomial
     * @return Unitless The value of the Legendre polynomial Pnm at x
     */
    Unitless get_legendre_polynomial_fast(const std::size_t& n, const std::size_t& m, const Unitless& x) const;

    /**
     * @brief Gets the cosine coefficient for given n and m.
     *
     * @param n Degree of the polynomial
     * @param m Order of the polynomial
     * @return Unitless The value of the cosine coefficient Cnm
     */
    Unitless get_cosine_coefficient(const std::size_t& n, const std::size_t& m) const { return _C[n][m]; }

    /**
     * @brief Gets the sine coefficient for given n and m.
     *
     * @param n Degree of the polynomial
     * @param m Order of the polynomial
     * @return Unitless The value of the sine coefficient Snm
     */
    Unitless get_sine_coefficient(const std::size_t& n, const std::size_t& m) const { return _S[n][m]; }

  private:
    // -1 <= sinLat <= 1
    // Result = (N + 1) * (M * 1) * (2 * granularity) entries
    static constexpr std::size_t _N_POLY = 2000; //!< Number of entries in the Legendre polynomial cache

    std::vector<std::vector<std::array<Unitless, _N_POLY>>> _P{}; // !< Legendre polynomial coefficients
    std::vector<std::vector<Unitless>> _normalizingCoefficients{}; //!< Normalizing coefficients for the Legendre polynomials
    std::vector<std::vector<Unitless>> _C{};                       //!< Cosine coefficients for the spherical harmonics
    std::vector<std::vector<Unitless>> _S{};                       //!< Sine coefficients for the spherical harmonics

    /**
     * @brief Precomputes the Legendre polynomial coefficients for the oblateness force.
     * @param degree Degree of the spherical harmonics
     * @param order Order of the spherical harmonics
     */
    void precompute_legendre(const std::size_t& degree, const std::size_t& order);

    /**
     * @brief Computes the Legendre polynomial coefficients for the oblateness force.
     * @param x Value at which to evaluate the Legendre polynomial
     * @param degree Degree of the spherical harmonics
     * @param order Order of the spherical harmonics
     */
    void assign_legendre(const std::size_t& degree, const std::size_t& order, const Unitless& x);

    /**
     * @brief Gets the index in the precomputed Legendre polynomial array for a given x value.
     * @param x Value at which to evaluate the Legendre polynomial
     * @return std::size_t The index in the precomputed Legendre polynomial array
     */
    std::size_t get_index(const Unitless& x) const;

    /**
     * @brief Sets the size of the vectors used for storing oblateness coefficients.
     * @param degree Degree of the spherical harmonics
     * @param order Order of the spherical harmonics
     */
    void size_vectors(const std::size_t& degree, const std::size_t& order);

    /**
     * @brief Ingests the Legendre coefficient file to populate the coefficients.
     * @param degree Degree of the spherical harmonics
     * @param order Order of the spherical harmonics
     * @param center Pointer to the celestial body for which the coefficients are being ingested
     */
    void ingest_legendre_coefficient_file(const std::size_t& degree, const std::size_t& order, const std::unique_ptr<CelestialBody>& center);
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
     */
    OblatenessForce(const AstrodynamicsSystem& sys, const std::size_t& N = 2, const std::size_t& M = 0, bool useFastLegendre = true);

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
    const std::size_t _degree;                     //!< Degree of the spherical harmonics
    const std::size_t _order;                      //!< Order of the spherical harmonics
    const std::unique_ptr<CelestialBody>& _center; //!< Pointer to the celestial body for which the oblateness force is computed
    const LegendreCache _legendreCache;            //!< Cache for Legendre polynomials and coefficients
    const bool _useFastLegendre; //!< Whether to use fast lookup for Legendre polynomials without interpolation
};

} // namespace astro
} // namespace astrea