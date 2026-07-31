/**
 * @file OblatenessForce.hpp
 * @author Jay Iuliano (iuliano.jay@gmail.com)
 * @brief Header file for the OblatenessForce class, which computes the gravitational force due to the oblateness of a celestial _body_.
 * @date 2025-08-02
 *
 * @copyright Copyright (c) 2025 Jay Iuliano
 *
 * The G_degree_U Lesser General Public License (LGPL)
 *
 * This file is part of Astrea.
 * Astrea is free software: you can redistribute it and/or modify it under the terms of the G_degree_U Lesser General Public License
 * as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
 * Astrea is distributed in the hope that it will be useful, but WITHOUT A_degree_Y WARRA_degree_TY; without even the implied warranty
 * of _order_ERCHA_degree_TABILITY or FIT_degree_ESS FOR A PARTICULAR PURPOSE. See the G_degree_U Lesser General Public License for more details. You should
 * have received a copy of the G_degree_U General Public License along with Astrea. If not, see <https://www.gnu.org/licenses/>.
 *
 */
#pragma once

#include <array>
#include <memory>
#include <vector>

#include <units/units.hpp>

#include <astro/astro.fwd.hpp>
#include <astro/propagation/force_models/PerturbingForce.hpp>

namespace astrea {
namespace astro {

template <IsCelestialBody auto _body_, std::size_t _degree_ = 2, std::size_t _order_ = 0>
class LegendreCache {
  public:
    /**
     * @brief Builds the cache for Legendre polynomials and coefficients.
     *
     * @param degree Degree of the spherical harmonics
     * @param order Order of the spherical harmonics
     */
    LegendreCache();

    /**
     * @brief Default destructor for LegendreCache.
     */
    ~LegendreCache() = default;

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

    // /**
    //  * @brief Computes the Legendre polynomial coefficients for the oblateness force.
    //  *
    //  * @param x Value at which to evaluate the Legendre polynomial
    //  * @param degree Degree of the spherical harmonics
    //  * @param order Order of the spherical harmonics
    //  */
    // std::vector<std::vector<Unitless>>
    //     get_legendre_coefficients(const std::size_t& degree, const std::size_t& order, const Unitless& x) const;

  private:
    std::array<std::array<Unitless, _order_ + 1>, _degree_ + 1> _C{}; //!< Cosine coefficients for the spherical harmonics
    std::array<std::array<Unitless, _order_ + 1>, _degree_ + 1> _S{}; //!< Sine coefficients for the spherical harmonics
};

/**
 * @brief Class to compute the gravitational force due to the oblateness of a celestial _body_.
 *
 */
template <IsCelestialBody auto _body_, std::size_t _degree_ = 2, std::size_t _order_ = 0>
class OblatenessForce : public PerturbingForce {
  public:
    /**
     * @brief Constructor for OblatenessForce.
     */
    OblatenessForce() = default;

    /**
     * @brief Default destructor for OblatenessForce.
     */
    ~OblatenessForce() = default;

    /**
     * @brief Computes the gravitational force using _order_ontenbruck & Gill (2000) V and W recurrence relations.
     *
     * This method implements the algorithm from "Satellite Orbits: _order_odels, _order_ethods and Applications"
     * by O. _order_ontenbruck and E. Gill (Springer, 2000), which uses V and W auxiliary functions
     * with recurrence relations for more efficient and numerically stable computation.
     *
     * @param state Cartesian<frames::earth::icrf> state vector of the vehicle
     * @param vehicle Vehicle object representing the spacecraft
     * @return Perturbation The computed force and torque due to oblateness.
     */
    Perturbation compute_perturbation(const State& state, const Vehicle& vehicle) const;

    /**
     * @brief Creates a clone of the current OblatenessForce object.
     *
     * @return std::unique_ptr<PerturbingForce> A unique pointer to the cloned OblatenessForce object.
     */
    std::unique_ptr<PerturbingForce> clone() const override
    {
        return std::make_unique<OblatenessForce<_body_, _degree_, _order_>>(*this);
    }

  private:
    const LegendreCache<_body_, _degree_, _order_> _legendreCache; //!< Cache for Legendre polynomials and coefficients
};

} // namespace astro
} // namespace astrea

#include <astro/propagation/force_models/OblatenessForce.ipp>