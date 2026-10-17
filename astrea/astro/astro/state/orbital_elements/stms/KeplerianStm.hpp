/**
 * @file KeplerianStm.hpp
 * @author Jay Iuliano (iuliano.jay@gmail.com)
 * @brief This file defines the KeplerianStm class and its associated methods.
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
class KeplerianStm {
  public:
    static constexpr auto frame = _frame_; //!< The reference frame of the Keplerian STM.

    /**
     * @brief Default constructor for KeplerianStm.
     */
    KeplerianStm() = default;

    /**
     * @brief Default destructor for KeplerianStm.
     */
    ~KeplerianStm() = default;

  private:
    /**
     * f(s) = [f0(s), f1(s), ..., fn(s)] where fi is the ith component of the equations of motion
     *
     * df/ds = |df0/ds0, df0/ds1, ..., df0/dsn| where dfi/ds is the partial derivative of the ith component with respect to the state vector
     *         |df1/ds0, df1/ds1, ..., df1/dsn|
     *         | ...                          |
     *         |dfn/ds0, dfn/ds1, ..., dfn/dsn|
     *
     * Keplerian:
     * df/ds = |dadot/da, dadot/de, dadot/di, dadot/dr, dadot/dw, dadot/dM|
     *         |dedot/da, dedot/de, dedot/di, dedot/dr, dedot/dw, dedot/dM|
     *         |didot/da, didot/de, didot/di, didot/dr, didot/dw, didot/dM|
     *         |drdot/da, drdot/de, drdot/di, drdot/dr, drdot/dw, drdot/dM|
     *         |dwdot/da, dwdot/de, dwdot/di, dwdot/dr, dwdot/dw, dwdot/dM|
     *         |dMdot/da, dMdot/de, dMdot/di, dMdot/dr, dMdot/dw, dMdot/dM|
     */
    quantity<one / s> _dadotda; //!< Partial derivative of the semimajor axis rate with respect to the semimajor axis
    quantity<km / s> _dadotde;  //!< Partial derivative of the semimajor axis rate with respect to the eccentricity
    quantity<km / (rad * s)> _dadotdi; //!< Partial derivative of the semimajor axis rate with respect to the inclination
    quantity<km / (rad * s)> _dadotdr; //!< Partial derivative of the semimajor axis rate with respect to the right ascension of the ascending node
    quantity<km / (rad * s)> _dadotdw; //!< Partial derivative of the semimajor axis rate with respect to the argument of perigee
    quantity<km / (rad * s)> _dadotdM; //!< Partial derivative of the semimajor axis rate with respect to the mean anomaly

    quantity<one / (km * s)> _dedotda; //!< Partial derivative of the eccentricity rate with respect to the semimajor axis
    quantity<one / s> _dedotde;        //!< Partial derivative of the eccentricity rate with respect to the eccentricity
    quantity<one / (rad * s)> _dedotdi; //!< Partial derivative of the eccentricity rate with respect to the inclination
    quantity<one / (rad * s)> _dedotdr; //!< Partial derivative of the eccentricity rate with respect to the right ascension of the ascending node
    quantity<one / (rad * s)> _dedotdw; //!< Partial derivative of the eccentricity rate with respect to the argument of perigee
    quantity<one / (rad * s)> _dedotdM; //!< Partial derivative of the eccentricity rate with respect to the mean anomaly

    quantity<rad / (km * s)> _didotda; //!< Partial derivative of the inclination rate with respect to the semimajor axis
    quantity<rad / s> _didotde;        //!< Partial derivative of the inclination rate with respect to the eccentricity
    quantity<one / s> _didotdi;        //!< Partial derivative of the inclination rate with respect to the inclination
    quantity<one / s> _didotdr; //!< Partial derivative of the inclination rate with respect to the right ascension of the ascending node
    quantity<one / s> _didotdw; //!< Partial derivative of the inclination rate with respect to the argument of perigee
    quantity<one / s> _didotdM; //!< Partial derivative of the inclination rate with respect to the mean anomaly

    quantity<rad / (km * s)> _drdotda; //!< Partial derivative of the right ascension of the ascending node rate with respect to the semimajor axis
    quantity<rad / s> _drdotde; //!< Partial derivative of the right ascension of the ascending node rate with respect to the eccentricity
    quantity<one / s> _drdotdi; //!< Partial derivative of the right ascension of the ascending node rate with respect to the inclination
    quantity<one / s> _drdotdr; //!< Partial derivative of the right ascension of the ascending node rate with respect to the right ascension of the ascending node
    quantity<one / s> _drdotdw; //!< Partial derivative of the right ascension of the ascending node rate with respect to the argument of perigee
    quantity<one / s> _drdotdM; //!< Partial derivative of the right ascension of the ascending node rate with respect to the mean anomaly

    quantity<rad / (km * s)> _dwdotda; //!< Partial derivative of the argument of perigee rate with respect to the semimajor axis
    quantity<rad / s> _dwdotde; //!< Partial derivative of the argument of perigee rate with respect to the eccentricity
    quantity<one / s> _dwdotdi; //!< Partial derivative of the argument of perigee rate with respect to the inclination
    quantity<one / s> _dwdotdr; //!< Partial derivative of the argument of perigee rate with respect to the right ascension of the ascending node
    quantity<one / s> _dwdotdw; //!< Partial derivative of the argument of perigee rate with respect to the argument of perigee
    quantity<one / s> _dwdotdM; //!< Partial derivative of the argument of perigee rate with respect to the mean anomaly

    quantity<rad / (km * s)> _dMdotda; //!< Partial derivative of the mean anomaly rate with respect to the semimajor axis
    quantity<rad / s> _dMdotde;        //!< Partial derivative of the mean anomaly rate with respect to the eccentricity
    quantity<one / s> _dMdotdi;        //!< Partial derivative of the mean anomaly rate with respect to the inclination
    quantity<one / s> _dMdotdr; //!< Partial derivative of the mean anomaly rate with respect to the right ascension of the ascending node
    quantity<one / s> _dMdotdw; //!< Partial derivative of the mean anomaly rate with respect to the argument of perigee
    quantity<one / s> _dMdotdM; //!< Partial derivative of the mean anomaly rate with respect to the mean anomaly
};

} // namespace astro
} // namespace astrea