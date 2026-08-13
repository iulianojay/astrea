/**
 * @file LegendreCache.hpp
 * @author Jay Iuliano (iuliano.jay@gmail.com)
 * @brief Header file for the LegendreCache class, which caches Legendre polynomial coefficients for a given celestial _body_, degree, and order.
 * @date 2025-08-02
 *
 * @copyright Copyright (c) 2025-2026 Jay Iuliano
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

#include <units/units.hpp>

#include <astro/astro.fwd.hpp>

namespace astrea {
namespace astro {

/**
 * @brief Class to cache Legendre polynomial coefficients for a given celestial _body_, degree, and order.
 *
 * @tparam _body_ The celestial _body_ for which the Legendre coefficients are cached
 * @tparam _degree_ The maximum degree of the spherical harmonics
 * @tparam _order_ The maximum order of the spherical harmonics
 */
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

  private:
    std::array<std::array<Unitless, _order_ + 1>, _degree_ + 1> _C{}; //!< Cosine coefficients for the spherical harmonics
    std::array<std::array<Unitless, _order_ + 1>, _degree_ + 1> _S{}; //!< Sine coefficients for the spherical harmonics
};

} // namespace astro
} // namespace astrea

#include <astro/propagation/force_models/LegendreCache.ipp>