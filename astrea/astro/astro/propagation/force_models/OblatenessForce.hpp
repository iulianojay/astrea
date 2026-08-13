/**
 * @file OblatenessForce.hpp
 * @author Jay Iuliano (iuliano.jay@gmail.com)
 * @brief Header file for the OblatenessForce class, which computes the gravitational force due to the oblateness of a celestial _body_.
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
#include <vector>

#include <units/units.hpp>

#include <astro/astro.fwd.hpp>
#include <astro/propagation/force_models/LegendreCache.hpp>
#include <astro/propagation/force_models/PerturbingForce.hpp>

namespace astrea {
namespace astro {

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
     * @brief Computes the gravitational force using Montenbruck & Gill (2000) V and W recurrence relations.
     *
     * This method implements the algorithm from "Satellite Orbits: Models, Methods and Applications"
     * by O. Montenbruck and E. Gill (Springer, 2000), which uses V and W auxiliary functions
     * with recurrence relations for more efficient and numerically stable computation.
     *
     * @param state Cartesian<frames::primary> state vector of the vehicle
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