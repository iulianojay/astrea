/**
 * @file EquinoctialStm.hpp
 * @author Jay Iuliano (iuliano.jay@gmail.com)
 * @brief This file defines the EquinoctialStm class and its associated methods.
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

namespace astrea {
namespace astro {

template <IsFrame auto _frame_>
class EquinoctialStm {
  public:
    static constexpr auto frame = _frame_; //!< The reference frame of the Equinoctial STM.

    /**
     * @brief Default constructor for EquinoctialStm.
     */
    EquinoctialStm() = default;

    /**
     * @brief Default destructor for EquinoctialStm.
     */
    ~EquinoctialStm() = default;

  private:
    /**
     * f(s) = [f0(s), f1(s), ..., fn(s)] where fi is the ith component of the equations of motion
     *
     * df/ds = |df0/ds0, df0/ds1, ..., df0/dsn| where dfi/ds is the partial derivative of the ith component with respect to the state vector
     *         |df1/ds0, df1/ds1, ..., df1/dsn|
     *         | ...                          |
     *         |dfn/ds0, dfn/ds1, ..., dfn/dsn|
     *
     * Equinoctial:
     * df/ds = |dsdot/ds, dsdot/df, dsdot/dg, dsdot/dh, dsdot/dk, dsdot/dL|
     *         |dfdot/ds, dfdot/df, dfdot/dg, dfdot/dh, dfdot/dk, dfdot/dL|
     *         |dgdot/ds, dgdot/df, dgdot/dg, dgdot/dh, dgdot/dk, dgdot/dL|
     *         |dhdot/ds, dhdot/df, dhdot/dg, dhdot/dh, dhdot/dk, dhdot/dL|
     *         |dkdot/ds, dkdot/df, dkdot/dg, dkdot/dh, dkdot/dk, dkdot/dL|
     *         |dLdot/ds, dLdot/df, dLdot/dg, dLdot/dh, dLdot/dk, dLdot/dL|
     */
    quantity<one / s> _dsdotds; //!< Partial derivative of the semilatus rectum rate with respect to the semilatus rectum
    quantity<km / s> _dsdotdf;  //!< Partial derivative of the semilatus rectum rate with respect to the f component
    quantity<km / s> _dsdotdg;  //!< Partial derivative of the semilatus rectum rate with respect to the g component
    quantity<km / s> _dsdotdh;  //!< Partial derivative of the semilatus rectum rate with respect to the h component
    quantity<km / s> _dsdotdk;  //!< Partial derivative of the semilatus rectum rate with respect to the k component
    quantity<km / (rad * s)> _dsdotdL; //!< Partial derivative of the semilatus rectum rate with respect to the mean longitude

    quantity<one / (km * s)> _dfdotds; //!< Partial derivative of the f component rate with respect to the semilatus rectum
    quantity<one / s> _dfdotdf;        //!< Partial derivative of the f component rate with respect to the f component
    quantity<one / s> _dfdotdg;        //!< Partial derivative of the f component rate with respect to the g component
    quantity<one / s> _dfdotdh;        //!< Partial derivative of the f component rate with respect to the h component
    quantity<one / s> _dfdotdk;        //!< Partial derivative of the f component rate with respect to the k component
    quantity<one / (rad * s)> _dfdotdL; //!< Partial derivative of the f component rate with respect to the mean longitude

    quantity<rad / (km * s)> _dgdotds; //!< Partial derivative of the g component rate with respect to the semilatus rectum
    quantity<one / s> _dgdotdf;        //!< Partial derivative of the g component rate with respect to the f component
    quantity<one / s> _dgdotdg;        //!< Partial derivative of the g component rate with respect to the g component
    quantity<one / s> _dgdotdh;        //!< Partial derivative of the g component rate with respect to the h component
    quantity<one / s> _dgdotdk;        //!< Partial derivative of the g component rate with respect to the k component
    quantity<one / (rad * s)> _dgdotdL; //!< Partial derivative of the g component rate with respect to the mean longitude

    quantity<rad / (km * s)> _dhdotds; //!< Partial derivative of the h component rate with respect to the semilatus rectum
    quantity<one / s> _dhdotdf;        //!< Partial derivative of the h component rate with respect to the f component
    quantity<one / s> _dhdotdg;        //!< Partial derivative of the h component rate with respect to the g component
    quantity<one / s> _dhdotdh;        //!< Partial derivative of the h component rate with respect to the h component
    quantity<one / s> _dhdotdk;        //!< Partial derivative of the h component rate with respect to the k component
    quantity<one / (rad * s)> _dhdotdL; //!< Partial derivative of the h component rate with respect to the mean longitude

    quantity<rad / (km * s)> _dkdotds; //!< Partial derivative of the k component rate with respect to the semilatus rectum
    quantity<one / s> _dkdotdf;        //!< Partial derivative of the k component rate with respect to the f component
    quantity<one / s> _dkdotdg;        //!< Partial derivative of the k component rate with respect to the g component
    quantity<one / s> _dkdotdh;        //!< Partial derivative of the k component rate with respect to the h component
    quantity<one / s> _dkdotdk;        //!< Partial derivative of the k component rate with respect to the k component
    quantity<one / (rad * s)> _dkdotdL; //!< Partial derivative of the k component rate with respect to the mean longitude

    quantity<rad / (km * s)> _dLdotds; //!< Partial derivative of the mean longitude rate with respect to the semilatus rectum
    quantity<rad / s> _dLdotdf; //!< Partial derivative of the mean longitude rate with respect to the f component
    quantity<rad / s> _dLdotdg; //!< Partial derivative of the mean longitude rate with respect to the g component
    quantity<rad / s> _dLdotdh; //!< Partial derivative of the mean longitude rate with respect to the h component
    quantity<rad / s> _dLdotdk; //!< Partial derivative of the mean longitude rate with respect to the k component
    quantity<one / s> _dLdotdL; //!< Partial derivative of the mean longitude rate with respect to the mean longitude
};

} // namespace astro
} // namespace astrea