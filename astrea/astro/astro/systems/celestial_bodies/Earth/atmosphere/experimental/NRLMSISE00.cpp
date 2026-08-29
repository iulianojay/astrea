/**
 * @file Nrlmsise00.hpp
 * @author Jay Iuliano (iuliano.jay@gmail.com)
 * @brief Header file for the Nrlmsise00 class.
 * @date 2026-05-01
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
 */
#include <astro/systems/celestial_bodies/Earth/atmosphere/Nrlmsise00.hpp>

#include <mp-units/math.h>
#include <mp-units/systems/hep.h>
#include <mp-units/systems/si.h>

using namespace mp_units;
using mp_units::hep::unit_symbols::u; // atomic mass unit
using mp_units::si::unit_symbols::cm;
using mp_units::si::unit_symbols::d;
using mp_units::si::unit_symbols::deg;
using mp_units::si::unit_symbols::h;
using mp_units::si::unit_symbols::J;
using mp_units::si::unit_symbols::K;
using mp_units::si::unit_symbols::kg;
using mp_units::si::unit_symbols::km;
using mp_units::si::unit_symbols::m;
using mp_units::si::unit_symbols::mol;
using mp_units::si::unit_symbols::rad;
using mp_units::si::unit_symbols::s;

using NumberDensity = quantity<one / pow<3>(m)>;
using AtomicMass    = quantity<u>;

/*
Note: Who the fuck wrote the original code for this model? Why do you hate code maintainers?
*/

namespace astrea {
namespace astro {
namespace planets {

/** NRLMSISE-00 data: temperature pt[150]. */
static const std::array<Temperature, 150> PT = {
    mp_units::point<K>(9.86573e-1),  mp_units::point<K>(1.62228e-2),  mp_units::point<K>(1.55270e-2),
    mp_units::point<K>(-1.04323e-1), mp_units::point<K>(-3.75801e-3), mp_units::point<K>(-1.18538e-3),
    mp_units::point<K>(-1.24043e-1), mp_units::point<K>(4.56820e-3),  mp_units::point<K>(8.76018e-3),
    mp_units::point<K>(-1.36235e-1), mp_units::point<K>(-3.52427e-2), mp_units::point<K>(8.84181e-3),
    mp_units::point<K>(-5.92127e-3), mp_units::point<K>(-8.61650),    mp_units::point<K>(0.0),
    mp_units::point<K>(1.28492e-2),  mp_units::point<K>(0.0),         mp_units::point<K>(1.30096e2),
    mp_units::point<K>(1.04567e-2),  mp_units::point<K>(1.65686e-3),  mp_units::point<K>(-5.53887e-6),
    mp_units::point<K>(2.97810e-3),  mp_units::point<K>(0.0),         mp_units::point<K>(5.13122e-3),
    mp_units::point<K>(8.66784e-2),  mp_units::point<K>(1.58727e-1),  mp_units::point<K>(0.0),
    mp_units::point<K>(0.0),         mp_units::point<K>(0.0),         mp_units::point<K>(-7.27026e-6),
    mp_units::point<K>(0.0),         mp_units::point<K>(6.74494),     mp_units::point<K>(4.93933e-3),
    mp_units::point<K>(2.21656e-3),  mp_units::point<K>(2.50802e-3),  mp_units::point<K>(0.0),
    mp_units::point<K>(0.0),         mp_units::point<K>(-2.08841e-2), mp_units::point<K>(-1.79873),
    mp_units::point<K>(1.45103e-3),  mp_units::point<K>(2.81769e-4),  mp_units::point<K>(-1.44703e-3),
    mp_units::point<K>(-5.16394e-5), mp_units::point<K>(8.47001e-2),  mp_units::point<K>(1.70147e-1),
    mp_units::point<K>(5.72562e-3),  mp_units::point<K>(5.07493e-5),  mp_units::point<K>(4.36148e-3),
    mp_units::point<K>(1.17863e-4),  mp_units::point<K>(4.74364e-3),  mp_units::point<K>(6.61278e-3),
    mp_units::point<K>(4.34292e-5),  mp_units::point<K>(1.44373e-3),  mp_units::point<K>(2.41470e-5),
    mp_units::point<K>(2.84426e-3),  mp_units::point<K>(8.56560e-4),  mp_units::point<K>(2.04028e-3),
    mp_units::point<K>(0.0),         mp_units::point<K>(-3.15994e3),  mp_units::point<K>(-2.46423e-3),
    mp_units::point<K>(1.13843e-3),  mp_units::point<K>(4.20512e-4),  mp_units::point<K>(0.0),
    mp_units::point<K>(-9.77214e1),  mp_units::point<K>(6.77794e-3),  mp_units::point<K>(5.27499e-3),
    mp_units::point<K>(1.14936e-3),  mp_units::point<K>(0.0),         mp_units::point<K>(-6.61311e-3),
    mp_units::point<K>(-1.84255e-2), mp_units::point<K>(-1.96259e-2), mp_units::point<K>(2.98618e4),
    mp_units::point<K>(0.0),         mp_units::point<K>(0.0),         mp_units::point<K>(0.0),
    mp_units::point<K>(6.44574e2),   mp_units::point<K>(8.84668e-4),  mp_units::point<K>(5.05066e-4),
    mp_units::point<K>(0.0),         mp_units::point<K>(4.02881e3),   mp_units::point<K>(-1.89503e-3),
    mp_units::point<K>(0.0),         mp_units::point<K>(0.0),         mp_units::point<K>(8.21407e-4),
    mp_units::point<K>(2.06780e-3),  mp_units::point<K>(0.0),         mp_units::point<K>(0.0),
    mp_units::point<K>(0.0),         mp_units::point<K>(0.0),         mp_units::point<K>(0.0),
    mp_units::point<K>(-1.20410e-2), mp_units::point<K>(-3.63963e-3), mp_units::point<K>(9.92070e-5),
    mp_units::point<K>(-1.15284e-4), mp_units::point<K>(-6.33059e-5), mp_units::point<K>(-6.05545e-1),
    mp_units::point<K>(8.34218e-3),  mp_units::point<K>(-9.13036e1),  mp_units::point<K>(3.71042e-4),
    mp_units::point<K>(0.0),         mp_units::point<K>(4.19000e-4),  mp_units::point<K>(2.70928e-3),
    mp_units::point<K>(3.31507e-3),  mp_units::point<K>(-4.44508e-3), mp_units::point<K>(-4.96334e-3),
    mp_units::point<K>(-1.60449e-3), mp_units::point<K>(3.95119e-3),  mp_units::point<K>(2.48924e-3),
    mp_units::point<K>(5.09815e-4),  mp_units::point<K>(4.05302e-3),  mp_units::point<K>(2.24076e-3),
    mp_units::point<K>(0.0),         mp_units::point<K>(6.84256e-3),  mp_units::point<K>(4.66354e-4),
    mp_units::point<K>(0.0),         mp_units::point<K>(-3.68328e-4), mp_units::point<K>(0.0),
    mp_units::point<K>(0.0),         mp_units::point<K>(-1.4687e2),   mp_units::point<K>(0.0),
    mp_units::point<K>(0.0),         mp_units::point<K>(1.09501e-3),  mp_units::point<K>(4.65156e-4),
    mp_units::point<K>(5.62583e-4),  mp_units::point<K>(3.21596),     mp_units::point<K>(6.43168e-4),
    mp_units::point<K>(3.14860e-3),  mp_units::point<K>(3.40738e-3),  mp_units::point<K>(1.78481e-3),
    mp_units::point<K>(9.62532e-4),  mp_units::point<K>(5.58171e-4),  mp_units::point<K>(3.43731),
    mp_units::point<K>(-2.33195e-1), mp_units::point<K>(5.10289e-4),  mp_units::point<K>(0.0),
    mp_units::point<K>(0.0),         mp_units::point<K>(-9.25347e4),  mp_units::point<K>(0.0),
    mp_units::point<K>(-1.99639e-3), mp_units::point<K>(0.0),         mp_units::point<K>(0.0),
    mp_units::point<K>(0.0),         mp_units::point<K>(0.0),         mp_units::point<K>(0.0),
    mp_units::point<K>(0.0),         mp_units::point<K>(0.0),         mp_units::point<K>(0.0),
    mp_units::point<K>(0.0),         mp_units::point<K>(0.0),         mp_units::point<K>(0.0)
};

/** NRLMSISE-00 data: density pd[9][150]. */
static const std::array<std::array<NumberDensity, 150>, 9> PD = {
    // HE DENSITY
    { 1.09979 * one / pow<3>(m),     -4.88060e-2 * one / pow<3>(m), -1.97501e-1 * one / pow<3>(m),
      -9.10280e-2 * one / pow<3>(m), -6.96558e-3 * one / pow<3>(m), 2.42136e-2 * one / pow<3>(m),
      3.91333e-1 * one / pow<3>(m),  -7.20068e-3 * one / pow<3>(m), -3.22718e-2 * one / pow<3>(m),
      1.41508 * one / pow<3>(m),     1.68194e-1 * one / pow<3>(m),  1.85282e-2 * one / pow<3>(m),
      1.09384e-1 * one / pow<3>(m),  -7.24282 * one / pow<3>(m),    0.0 * one / pow<3>(m),
      2.96377e-1 * one / pow<3>(m),  -4.97210e-2 * one / pow<3>(m), 1.04114e2 * one / pow<3>(m),
      -8.61108e-2 * one / pow<3>(m), -7.29177e-4 * one / pow<3>(m), 1.48998e-6 * one / pow<3>(m),
      1.08629e-3 * one / pow<3>(m),  0.0 * one / pow<3>(m),         0.0 * one / pow<3>(m),
      8.31090e-2 * one / pow<3>(m),  1.12818e-1 * one / pow<3>(m),  -5.75005e-2 * one / pow<3>(m),
      -1.29919e-2 * one / pow<3>(m), -1.78849e-2 * one / pow<3>(m), -2.86343e-6 * one / pow<3>(m),
      0.0 * one / pow<3>(m),         -1.51187e2 * one / pow<3>(m),  -6.65902e-3 * one / pow<3>(m),
      0.0 * one / pow<3>(m),         -2.02069e-3 * one / pow<3>(m), 0.0 * one / pow<3>(m),
      0.0 * one / pow<3>(m),         4.32264e-2 * one / pow<3>(m),  -2.80444e1 * one / pow<3>(m),
      -3.26789e-3 * one / pow<3>(m), 2.47461e-3 * one / pow<3>(m),  0.0 * one / pow<3>(m),
      0.0 * one / pow<3>(m),         9.82100e-2 * one / pow<3>(m),  1.22714e-1 * one / pow<3>(m),
      -3.96450e-2 * one / pow<3>(m), 0.0 * one / pow<3>(m),         -2.76489e-3 * one / pow<3>(m),
      0.0 * one / pow<3>(m),         1.87723e-3 * one / pow<3>(m),  -8.09813e-3 * one / pow<3>(m),
      4.34428e-5 * one / pow<3>(m),  -7.70932e-3 * one / pow<3>(m), 0.0 * one / pow<3>(m),
      -2.28894e-3 * one / pow<3>(m), -5.69070e-3 * one / pow<3>(m), -5.22193e-3 * one / pow<3>(m),
      6.00692e-3 * one / pow<3>(m),  -7.80434e3 * one / pow<3>(m),  -3.48336e-3 * one / pow<3>(m),
      -6.38362e-3 * one / pow<3>(m), -1.82190e-3 * one / pow<3>(m), 0.0 * one / pow<3>(m),
      -7.58976e1 * one / pow<3>(m),  -2.17875e-2 * one / pow<3>(m), -1.72524e-2 * one / pow<3>(m),
      -9.06287e-3 * one / pow<3>(m), 0.0 * one / pow<3>(m),         2.44725e-2 * one / pow<3>(m),
      8.66040e-2 * one / pow<3>(m),  1.05712e-1 * one / pow<3>(m),  3.02543e4 * one / pow<3>(m),
      0.0 * one / pow<3>(m),         0.0 * one / pow<3>(m),         0.0 * one / pow<3>(m),
      -6.01364e3 * one / pow<3>(m),  -5.64668e-3 * one / pow<3>(m), -2.54157e-3 * one / pow<3>(m),
      0.0 * one / pow<3>(m),         3.15611e2 * one / pow<3>(m),   -5.69158e-3 * one / pow<3>(m),
      0.0 * one / pow<3>(m),         0.0 * one / pow<3>(m),         -4.47216e-3 * one / pow<3>(m),
      -4.49523e-3 * one / pow<3>(m), 4.64428e-3 * one / pow<3>(m),  0.0 * one / pow<3>(m),
      0.0 * one / pow<3>(m),         0.0 * one / pow<3>(m),         0.0 * one / pow<3>(m),
      4.51236e-2 * one / pow<3>(m),  2.46520e-2 * one / pow<3>(m),  6.17794e-3 * one / pow<3>(m),
      0.0 * one / pow<3>(m),         0.0 * one / pow<3>(m),         -3.62944e-1 * one / pow<3>(m),
      -4.80022e-2 * one / pow<3>(m), -7.5723e1 * one / pow<3>(m),   -1.99656e-3 * one / pow<3>(m),
      0.0 * one / pow<3>(m),         -5.18780e-3 * one / pow<3>(m), -1.73990e-2 * one / pow<3>(m),
      -9.03485e-3 * one / pow<3>(m), 7.48465e-3 * one / pow<3>(m),  1.53267e-2 * one / pow<3>(m),
      1.06296e-2 * one / pow<3>(m),  1.18655e-2 * one / pow<3>(m),  2.55569e-3 * one / pow<3>(m),
      1.69020e-3 * one / pow<3>(m),  3.51936e-2 * one / pow<3>(m),  -1.81242e-2 * one / pow<3>(m),
      0.0 * one / pow<3>(m),         -1.00529e-1 * one / pow<3>(m), -5.10574e-3 * one / pow<3>(m),
      0.0 * one / pow<3>(m),         2.10228e-3 * one / pow<3>(m),  0.0 * one / pow<3>(m),
      0.0 * one / pow<3>(m),         -1.73255e2 * one / pow<3>(m),  5.07833e-1 * one / pow<3>(m),
      -2.41408e-1 * one / pow<3>(m), 8.75414e-3 * one / pow<3>(m),  2.77527e-3 * one / pow<3>(m),
      -8.90353e-5 * one / pow<3>(m), -5.25148 * one / pow<3>(m),    -5.83899e-3 * one / pow<3>(m),
      -2.09122e-2 * one / pow<3>(m), -9.63530e-3 * one / pow<3>(m), 9.77164e-3 * one / pow<3>(m),
      4.07051e-3 * one / pow<3>(m),  2.53555e-4 * one / pow<3>(m),  -5.52875 * one / pow<3>(m),
      -3.55993e-1 * one / pow<3>(m), -2.49231e-3 * one / pow<3>(m), 0.0 * one / pow<3>(m),
      0.0 * one / pow<3>(m),         2.86026e1 * one / pow<3>(m),   0.0 * one / pow<3>(m),
      3.42722e-4 * one / pow<3>(m),  0.0 * one / pow<3>(m),         0.0 * one / pow<3>(m),
      0.0 * one / pow<3>(m),         0.0 * one / pow<3>(m),         0.0 * one / pow<3>(m),
      0.0 * one / pow<3>(m),         0.0 * one / pow<3>(m),         0.0 * one / pow<3>(m),
      0.0 * one / pow<3>(m),         0.0 * one / pow<3>(m),         0.0 * one / pow<3>(m) },
    // O DENSITY
    { 1.02315 * one / pow<3>(m),     -1.59710e-1 * one / pow<3>(m), -1.06630e-1 * one / pow<3>(m),
      -1.77074e-2 * one / pow<3>(m), -4.42726e-3 * one / pow<3>(m), 3.44803e-2 * one / pow<3>(m),
      4.45613e-2 * one / pow<3>(m),  -3.33751e-2 * one / pow<3>(m), -5.73598e-2 * one / pow<3>(m),
      3.50360e-1 * one / pow<3>(m),  6.33053e-2 * one / pow<3>(m),  2.16221e-2 * one / pow<3>(m),
      5.42577e-2 * one / pow<3>(m),  -5.74193 * one / pow<3>(m),    0.0 * one / pow<3>(m),
      1.90891e-1 * one / pow<3>(m),  -1.39194e-2 * one / pow<3>(m), 1.01102e2 * one / pow<3>(m),
      8.16363e-2 * one / pow<3>(m),  1.33717e-4 * one / pow<3>(m),  6.54403e-6 * one / pow<3>(m),
      3.10295e-3 * one / pow<3>(m),  0.0 * one / pow<3>(m),         0.0 * one / pow<3>(m),
      5.38205e-2 * one / pow<3>(m),  1.23910e-1 * one / pow<3>(m),  -1.39831e-2 * one / pow<3>(m),
      0.0 * one / pow<3>(m),         0.0 * one / pow<3>(m),         -3.95915e-6 * one / pow<3>(m),
      0.0 * one / pow<3>(m),         -7.14651e-1 * one / pow<3>(m), -5.01027e-3 * one / pow<3>(m),
      0.0 * one / pow<3>(m),         -3.24756e-3 * one / pow<3>(m), 0.0 * one / pow<3>(m),
      0.0 * one / pow<3>(m),         4.42173e-2 * one / pow<3>(m),  -1.31598e1 * one / pow<3>(m),
      -3.15626e-3 * one / pow<3>(m), 1.24574e-3 * one / pow<3>(m),  -1.47626e-3 * one / pow<3>(m),
      -1.55461e-3 * one / pow<3>(m), 6.40682e-2 * one / pow<3>(m),  1.34898e-1 * one / pow<3>(m),
      -2.42415e-2 * one / pow<3>(m), 0.0 * one / pow<3>(m),         0.0 * one / pow<3>(m),
      0.0 * one / pow<3>(m),         6.13666e-4 * one / pow<3>(m),  -5.40373e-3 * one / pow<3>(m),
      2.61635e-5 * one / pow<3>(m),  -3.33012e-3 * one / pow<3>(m), 0.0 * one / pow<3>(m),
      -3.08101e-3 * one / pow<3>(m), -2.42679e-3 * one / pow<3>(m), -3.36086e-3 * one / pow<3>(m),
      0.0 * one / pow<3>(m),         -1.18979e3 * one / pow<3>(m),  -5.04738e-2 * one / pow<3>(m),
      -2.61547e-3 * one / pow<3>(m), -1.03132e-3 * one / pow<3>(m), 1.91583e-4 * one / pow<3>(m),
      -8.38132e1 * one / pow<3>(m),  -1.40517e-2 * one / pow<3>(m), -1.14167e-2 * one / pow<3>(m),
      -4.08012e-3 * one / pow<3>(m), 1.73522e-4 * one / pow<3>(m),  -1.39644e-2 * one / pow<3>(m),
      -6.64128e-2 * one / pow<3>(m), -6.85152e-2 * one / pow<3>(m), -1.34414e4 * one / pow<3>(m),
      0.0 * one / pow<3>(m),         0.0 * one / pow<3>(m),         0.0 * one / pow<3>(m),
      6.07916e2 * one / pow<3>(m),   -4.12220e-3 * one / pow<3>(m), -2.20996e-3 * one / pow<3>(m),
      0.0 * one / pow<3>(m),         1.70277e3 * one / pow<3>(m),   -4.63015e-3 * one / pow<3>(m),
      0.0 * one / pow<3>(m),         0.0 * one / pow<3>(m),         -2.25360e-3 * one / pow<3>(m),
      -2.96204e-3 * one / pow<3>(m), 0.0 * one / pow<3>(m),         0.0 * one / pow<3>(m),
      0.0 * one / pow<3>(m),         0.0 * one / pow<3>(m),         0.0 * one / pow<3>(m),
      3.92786e-2 * one / pow<3>(m),  1.31186e-2 * one / pow<3>(m),  -1.78086e-3 * one / pow<3>(m),
      0.0 * one / pow<3>(m),         0.0 * one / pow<3>(m),         -3.90083e-1 * one / pow<3>(m),
      -2.84741e-2 * one / pow<3>(m), -7.784e1 * one / pow<3>(m),    -1.02601e-3 * one / pow<3>(m),
      0.0 * one / pow<3>(m),         -7.26485e-4 * one / pow<3>(m), -5.42181e-3 * one / pow<3>(m),
      -5.59305e-3 * one / pow<3>(m), 1.22825e-2 * one / pow<3>(m),  1.23868e-2 * one / pow<3>(m),
      6.68835e-3 * one / pow<3>(m),  -1.03303e-2 * one / pow<3>(m), -9.51903e-3 * one / pow<3>(m),
      2.70021e-4 * one / pow<3>(m),  -2.57084e-2 * one / pow<3>(m), -1.32430e-2 * one / pow<3>(m),
      0.0 * one / pow<3>(m),         -3.81000e-2 * one / pow<3>(m), -3.16810e-3 * one / pow<3>(m),
      0.0 * one / pow<3>(m),         0.0 * one / pow<3>(m),         0.0 * one / pow<3>(m),
      0.0 * one / pow<3>(m),         0.0 * one / pow<3>(m),         0.0 * one / pow<3>(m),
      0.0 * one / pow<3>(m),         -9.05762e-4 * one / pow<3>(m), -2.14590e-3 * one / pow<3>(m),
      -1.17824e-3 * one / pow<3>(m), 3.66732 * one / pow<3>(m),     -3.79729e-4 * one / pow<3>(m),
      -6.13966e-3 * one / pow<3>(m), -5.09082e-3 * one / pow<3>(m), -1.96332e-3 * one / pow<3>(m),
      -3.08280e-3 * one / pow<3>(m), -9.75222e-4 * one / pow<3>(m), 4.03315 * one / pow<3>(m),
      -2.52710e-1 * one / pow<3>(m), 0.0 * one / pow<3>(m),         0.0 * one / pow<3>(m),
      0.0 * one / pow<3>(m),         0.0 * one / pow<3>(m),         0.0 * one / pow<3>(m),
      0.0 * one / pow<3>(m),         0.0 * one / pow<3>(m),         0.0 * one / pow<3>(m),
      0.0 * one / pow<3>(m),         0.0 * one / pow<3>(m),         0.0 * one / pow<3>(m),
      0.0 * one / pow<3>(m),         0.0 * one / pow<3>(m),         0.0 * one / pow<3>(m),
      0.0 * one / pow<3>(m),         0.0 * one / pow<3>(m),         0.0 * one / pow<3>(m) },
    // N2 DENSITY
    { 1.16112 * one / pow<3>(m),     0.0 * one / pow<3>(m),        0.0 * one / pow<3>(m),
      3.33725e-2 * one / pow<3>(m),  0.0 * one / pow<3>(m),        3.48637e-2 * one / pow<3>(m),
      -5.44368e-3 * one / pow<3>(m), 0.0 * one / pow<3>(m),        -6.73940e-2 * one / pow<3>(m),
      1.74754e-1 * one / pow<3>(m),  0.0 * one / pow<3>(m),        0.0 * one / pow<3>(m),
      0.0 * one / pow<3>(m),         1.74712e2 * one / pow<3>(m),  0.0 * one / pow<3>(m),
      1.26733e-1 * one / pow<3>(m),  0.0 * one / pow<3>(m),        1.03154e2 * one / pow<3>(m),
      5.52075e-2 * one / pow<3>(m),  0.0 * one / pow<3>(m),        0.0 * one / pow<3>(m),
      8.13525e-4 * one / pow<3>(m),  0.0 * one / pow<3>(m),        0.0 * one / pow<3>(m),
      8.66784e-2 * one / pow<3>(m),  1.58727e-1 * one / pow<3>(m), 0.0 * one / pow<3>(m),
      0.0 * one / pow<3>(m),         0.0 * one / pow<3>(m),        0.0 * one / pow<3>(m),
      0.0 * one / pow<3>(m),         -2.50482e1 * one / pow<3>(m), 0.0 * one / pow<3>(m),
      0.0 * one / pow<3>(m),         0.0 * one / pow<3>(m),        0.0 * one / pow<3>(m),
      0.0 * one / pow<3>(m),         0.0 * one / pow<3>(m),        0.0 * one / pow<3>(m),
      -2.48894e-3 * one / pow<3>(m), 6.16053e-4 * one / pow<3>(m), -5.79716e-4 * one / pow<3>(m),
      2.95482e-3 * one / pow<3>(m),  8.47001e-2 * one / pow<3>(m), 1.70147e-1 * one / pow<3>(m),
      0.0 * one / pow<3>(m),         0.0 * one / pow<3>(m),        0.0 * one / pow<3>(m),
      0.0 * one / pow<3>(m),         0.0 * one / pow<3>(m),        0.0 * one / pow<3>(m),
      2.47425e-5 * one / pow<3>(m),  0.0 * one / pow<3>(m),        0.0 * one / pow<3>(m),
      0.0 * one / pow<3>(m),         0.0 * one / pow<3>(m),        0.0 * one / pow<3>(m),
      0.0 * one / pow<3>(m),         0.0 * one / pow<3>(m),        0.0 * one / pow<3>(m),
      0.0 * one / pow<3>(m),         0.0 * one / pow<3>(m),        0.0 * one / pow<3>(m),
      0.0 * one / pow<3>(m),         0.0 * one / pow<3>(m),        0.0 * one / pow<3>(m),
      0.0 * one / pow<3>(m),         0.0 * one / pow<3>(m),        0.0 * one / pow<3>(m),
      0.0 * one / pow<3>(m),         0.0 * one / pow<3>(m),        0.0 * one / pow<3>(m),
      0.0 * one / pow<3>(m),         0.0 * one / pow<3>(m),        0.0 * one / pow<3>(m),
      0.0 * one / pow<3>(m),         0.0 * one / pow<3>(m),        0.0 * one / pow<3>(m),
      0.0 * one / pow<3>(m),         0.0 * one / pow<3>(m),        0.0 * one / pow<3>(m),
      0.0 * one / pow<3>(m),         0.0 * one / pow<3>(m),        0.0 * one / pow<3>(m),
      0.0 * one / pow<3>(m),         0.0 * one / pow<3>(m),        0.0 * one / pow<3>(m),
      0.0 * one / pow<3>(m),         0.0 * one / pow<3>(m),        0.0 * one / pow<3>(m),
      0.0 * one / pow<3>(m),         0.0 * one / pow<3>(m),        0.0 * one / pow<3>(m),
      0.0 * one / pow<3>(m),         0.0 * one / pow<3>(m),        0.0 * one / pow<3>(m),
      0.0 * one / pow<3>(m),         0.0 * one / pow<3>(m),        0.0 * one / pow<3>(m),
      0.0 * one / pow<3>(m),         0.0 * one / pow<3>(m),        0.0 * one / pow<3>(m),
      0.0 * one / pow<3>(m),         0.0 * one / pow<3>(m),        0.0 * one / pow<3>(m),
      0.0 * one / pow<3>(m),         0.0 * one / pow<3>(m),        0.0 * one / pow<3>(m),
      0.0 * one / pow<3>(m),         0.0 * one / pow<3>(m),        0.0 * one / pow<3>(m),
      0.0 * one / pow<3>(m),         0.0 * one / pow<3>(m),        0.0 * one / pow<3>(m),
      0.0 * one / pow<3>(m),         0.0 * one / pow<3>(m),        0.0 * one / pow<3>(m),
      0.0 * one / pow<3>(m),         0.0 * one / pow<3>(m),        0.0 * one / pow<3>(m),
      0.0 * one / pow<3>(m),         0.0 * one / pow<3>(m),        0.0 * one / pow<3>(m),
      0.0 * one / pow<3>(m),         0.0 * one / pow<3>(m),        0.0 * one / pow<3>(m),
      0.0 * one / pow<3>(m),         0.0 * one / pow<3>(m),        0.0 * one / pow<3>(m),
      0.0 * one / pow<3>(m),         0.0 * one / pow<3>(m),        0.0 * one / pow<3>(m),
      0.0 * one / pow<3>(m),         0.0 * one / pow<3>(m),        0.0 * one / pow<3>(m),
      0.0 * one / pow<3>(m),         0.0 * one / pow<3>(m),        0.0 * one / pow<3>(m),
      0.0 * one / pow<3>(m),         0.0 * one / pow<3>(m),        0.0 * one / pow<3>(m),
      0.0 * one / pow<3>(m),         0.0 * one / pow<3>(m),        0.0 * one / pow<3>(m),
      0.0 * one / pow<3>(m),         0.0 * one / pow<3>(m),        0.0 * one / pow<3>(m),
      0.0 * one / pow<3>(m),         0.0 * one / pow<3>(m),        0.0 * one / pow<3>(m) },
    // TOTAL MASS
    { 9.44846e-1 * one / pow<3>(m),  0.0 * one / pow<3>(m),        0.0 * one / pow<3>(m),
      -3.08617e-2 * one / pow<3>(m), 0.0 * one / pow<3>(m),        -2.44019e-2 * one / pow<3>(m),
      6.48607e-3 * one / pow<3>(m),  0.0 * one / pow<3>(m),        3.08181e-2 * one / pow<3>(m),
      4.59392e-2 * one / pow<3>(m),  0.0 * one / pow<3>(m),        0.0 * one / pow<3>(m),
      0.0 * one / pow<3>(m),         1.74712e2 * one / pow<3>(m),  0.0 * one / pow<3>(m),
      2.13260e-2 * one / pow<3>(m),  0.0 * one / pow<3>(m),        -3.56958e2 * one / pow<3>(m),
      0.0 * one / pow<3>(m),         1.82278e-4 * one / pow<3>(m), 0.0 * one / pow<3>(m),
      3.07472e-4 * one / pow<3>(m),  0.0 * one / pow<3>(m),        0.0 * one / pow<3>(m),
      8.66784e-2 * one / pow<3>(m),  1.58727e-1 * one / pow<3>(m), 0.0 * one / pow<3>(m),
      0.0 * one / pow<3>(m),         0.0 * one / pow<3>(m),        0.0 * one / pow<3>(m),
      0.0 * one / pow<3>(m),         0.0 * one / pow<3>(m),        3.83054e-3 * one / pow<3>(m),
      0.0 * one / pow<3>(m),         0.0 * one / pow<3>(m),        -1.93065e-3 * one / pow<3>(m),
      -1.45090e-3 * one / pow<3>(m), 0.0 * one / pow<3>(m),        0.0 * one / pow<3>(m),
      0.0 * one / pow<3>(m),         0.0 * one / pow<3>(m),        -1.23493e-3 * one / pow<3>(m),
      1.36736e-3 * one / pow<3>(m),  8.47001e-2 * one / pow<3>(m), 1.70147e-1 * one / pow<3>(m),
      3.71469e-3 * one / pow<3>(m),  0.0 * one / pow<3>(m),        0.0 * one / pow<3>(m),
      0.0 * one / pow<3>(m),         0.0 * one / pow<3>(m),        5.10250e-3 * one / pow<3>(m),
      2.47425e-5 * one / pow<3>(m),  0.0 * one / pow<3>(m),        0.0 * one / pow<3>(m),
      0.0 * one / pow<3>(m),         0.0 * one / pow<3>(m),        0.0 * one / pow<3>(m),
      0.0 * one / pow<3>(m),         0.0 * one / pow<3>(m),        0.0 * one / pow<3>(m),
      0.0 * one / pow<3>(m),         0.0 * one / pow<3>(m),        0.0 * one / pow<3>(m),
      0.0 * one / pow<3>(m),         0.0 * one / pow<3>(m),        0.0 * one / pow<3>(m),
      0.0 * one / pow<3>(m),         0.0 * one / pow<3>(m),        0.0 * one / pow<3>(m),
      0.0 * one / pow<3>(m),         0.0 * one / pow<3>(m),        0.0 * one / pow<3>(m),
      0.0 * one / pow<3>(m),         0.0 * one / pow<3>(m),        0.0 * one / pow<3>(m),
      0.0 * one / pow<3>(m),         0.0 * one / pow<3>(m),        0.0 * one / pow<3>(m),
      0.0 * one / pow<3>(m),         0.0 * one / pow<3>(m),        0.0 * one / pow<3>(m),
      0.0 * one / pow<3>(m),         0.0 * one / pow<3>(m),        0.0 * one / pow<3>(m),
      0.0 * one / pow<3>(m),         0.0 * one / pow<3>(m),        0.0 * one / pow<3>(m),
      0.0 * one / pow<3>(m),         0.0 * one / pow<3>(m),        0.0 * one / pow<3>(m),
      0.0 * one / pow<3>(m),         0.0 * one / pow<3>(m),        0.0 * one / pow<3>(m),
      0.0 * one / pow<3>(m),         0.0 * one / pow<3>(m),        0.0 * one / pow<3>(m),
      3.68756e-3 * one / pow<3>(m),  0.0 * one / pow<3>(m),        0.0 * one / pow<3>(m),
      0.0 * one / pow<3>(m),         0.0 * one / pow<3>(m),        0.0 * one / pow<3>(m),
      0.0 * one / pow<3>(m),         0.0 * one / pow<3>(m),        0.0 * one / pow<3>(m),
      0.0 * one / pow<3>(m),         0.0 * one / pow<3>(m),        0.0 * one / pow<3>(m),
      0.0 * one / pow<3>(m),         0.0 * one / pow<3>(m),        0.0 * one / pow<3>(m),
      0.0 * one / pow<3>(m),         0.0 * one / pow<3>(m),        0.0 * one / pow<3>(m),
      0.0 * one / pow<3>(m),         0.0 * one / pow<3>(m),        0.0 * one / pow<3>(m),
      0.0 * one / pow<3>(m),         0.0 * one / pow<3>(m),        0.0 * one / pow<3>(m),
      0.0 * one / pow<3>(m),         0.0 * one / pow<3>(m),        0.0 * one / pow<3>(m),
      0.0 * one / pow<3>(m),         0.0 * one / pow<3>(m),        0.0 * one / pow<3>(m),
      0.0 * one / pow<3>(m),         0.0 * one / pow<3>(m),        0.0 * one / pow<3>(m),
      0.0 * one / pow<3>(m),         0.0 * one / pow<3>(m),        0.0 * one / pow<3>(m),
      0.0 * one / pow<3>(m),         0.0 * one / pow<3>(m),        0.0 * one / pow<3>(m),
      0.0 * one / pow<3>(m),         0.0 * one / pow<3>(m),        0.0 * one / pow<3>(m),
      0.0 * one / pow<3>(m),         0.0 * one / pow<3>(m),        0.0 * one / pow<3>(m),
      0.0 * one / pow<3>(m),         0.0 * one / pow<3>(m),        0.0 * one / pow<3>(m),
      0.0 * one / pow<3>(m),         0.0 * one / pow<3>(m),        0.0 * one / pow<3>(m),
      0.0 * one / pow<3>(m),         0.0 * one / pow<3>(m),        0.0 * one / pow<3>(m) },
    // O2 DENSITY
    { 1.35580 * one / pow<3>(m),     1.44816e-1 * one / pow<3>(m),  0.0 * one / pow<3>(m),
      6.07767e-2 * one / pow<3>(m),  0.0 * one / pow<3>(m),         2.94777e-2 * one / pow<3>(m),
      7.46900e-2 * one / pow<3>(m),  0.0 * one / pow<3>(m),         -9.23822e-2 * one / pow<3>(m),
      8.57342e-2 * one / pow<3>(m),  0.0 * one / pow<3>(m),         0.0 * one / pow<3>(m),
      0.0 * one / pow<3>(m),         2.38636e1 * one / pow<3>(m),   0.0 * one / pow<3>(m),
      7.71653e-2 * one / pow<3>(m),  0.0 * one / pow<3>(m),         8.18751e1 * one / pow<3>(m),
      1.87736e-2 * one / pow<3>(m),  0.0 * one / pow<3>(m),         0.0 * one / pow<3>(m),
      1.49667e-2 * one / pow<3>(m),  0.0 * one / pow<3>(m),         0.0 * one / pow<3>(m),
      8.66784e-2 * one / pow<3>(m),  1.58727e-1 * one / pow<3>(m),  0.0 * one / pow<3>(m),
      0.0 * one / pow<3>(m),         0.0 * one / pow<3>(m),         0.0 * one / pow<3>(m),
      0.0 * one / pow<3>(m),         -3.67874e2 * one / pow<3>(m),  5.48158e-3 * one / pow<3>(m),
      0.0 * one / pow<3>(m),         0.0 * one / pow<3>(m),         0.0 * one / pow<3>(m),
      0.0 * one / pow<3>(m),         0.0 * one / pow<3>(m),         0.0 * one / pow<3>(m),
      0.0 * one / pow<3>(m),         0.0 * one / pow<3>(m),         0.0 * one / pow<3>(m),
      0.0 * one / pow<3>(m),         8.47001e-2 * one / pow<3>(m),  1.70147e-1 * one / pow<3>(m),
      1.22631e-2 * one / pow<3>(m),  0.0 * one / pow<3>(m),         0.0 * one / pow<3>(m),
      0.0 * one / pow<3>(m),         0.0 * one / pow<3>(m),         8.17187e-3 * one / pow<3>(m),
      3.71617e-5 * one / pow<3>(m),  0.0 * one / pow<3>(m),         0.0 * one / pow<3>(m),
      0.0 * one / pow<3>(m),         0.0 * one / pow<3>(m),         0.0 * one / pow<3>(m),
      0.0 * one / pow<3>(m),         0.0 * one / pow<3>(m),         0.0 * one / pow<3>(m),
      0.0 * one / pow<3>(m),         0.0 * one / pow<3>(m),         0.0 * one / pow<3>(m),
      0.0 * one / pow<3>(m),         -2.10826e-3 * one / pow<3>(m), -3.13640e-3 * one / pow<3>(m),
      0.0 * one / pow<3>(m),         0.0 * one / pow<3>(m),         0.0 * one / pow<3>(m),
      0.0 * one / pow<3>(m),         0.0 * one / pow<3>(m),         0.0 * one / pow<3>(m),
      0.0 * one / pow<3>(m),         0.0 * one / pow<3>(m),         0.0 * one / pow<3>(m),
      0.0 * one / pow<3>(m),         0.0 * one / pow<3>(m),         0.0 * one / pow<3>(m),
      0.0 * one / pow<3>(m),         0.0 * one / pow<3>(m),         0.0 * one / pow<3>(m),
      0.0 * one / pow<3>(m),         0.0 * one / pow<3>(m),         0.0 * one / pow<3>(m),
      0.0 * one / pow<3>(m),         0.0 * one / pow<3>(m),         0.0 * one / pow<3>(m),
      0.0 * one / pow<3>(m),         0.0 * one / pow<3>(m),         0.0 * one / pow<3>(m),
      -7.35742e-2 * one / pow<3>(m), -5.00266e-2 * one / pow<3>(m), 0.0 * one / pow<3>(m),
      0.0 * one / pow<3>(m),         0.0 * one / pow<3>(m),         0.0 * one / pow<3>(m),
      1.94965e-2 * one / pow<3>(m),  0.0 * one / pow<3>(m),         0.0 * one / pow<3>(m),
      0.0 * one / pow<3>(m),         0.0 * one / pow<3>(m),         0.0 * one / pow<3>(m),
      0.0 * one / pow<3>(m),         0.0 * one / pow<3>(m),         0.0 * one / pow<3>(m),
      0.0 * one / pow<3>(m),         0.0 * one / pow<3>(m),         0.0 * one / pow<3>(m),
      0.0 * one / pow<3>(m),         0.0 * one / pow<3>(m),         0.0 * one / pow<3>(m),
      0.0 * one / pow<3>(m),         0.0 * one / pow<3>(m),         0.0 * one / pow<3>(m),
      0.0 * one / pow<3>(m),         0.0 * one / pow<3>(m),         0.0 * one / pow<3>(m),
      0.0 * one / pow<3>(m),         0.0 * one / pow<3>(m),         0.0 * one / pow<3>(m),
      0.0 * one / pow<3>(m),         0.0 * one / pow<3>(m),         0.0 * one / pow<3>(m),
      0.0 * one / pow<3>(m),         0.0 * one / pow<3>(m),         0.0 * one / pow<3>(m),
      0.0 * one / pow<3>(m),         0.0 * one / pow<3>(m),         0.0 * one / pow<3>(m),
      0.0 * one / pow<3>(m),         0.0 * one / pow<3>(m),         0.0 * one / pow<3>(m),
      0.0 * one / pow<3>(m),         0.0 * one / pow<3>(m),         0.0 * one / pow<3>(m),
      0.0 * one / pow<3>(m),         0.0 * one / pow<3>(m),         0.0 * one / pow<3>(m),
      0.0 * one / pow<3>(m),         0.0 * one / pow<3>(m),         0.0 * one / pow<3>(m),
      0.0 * one / pow<3>(m),         0.0 * one / pow<3>(m),         0.0 * one / pow<3>(m),
      0.0 * one / pow<3>(m),         0.0 * one / pow<3>(m),         0.0 * one / pow<3>(m),
      0.0 * one / pow<3>(m),         0.0 * one / pow<3>(m),         0.0 * one / pow<3>(m) },
    // AR DENSITY
    { 1.04761 * one / pow<3>(m),     2.00165e-1 * one / pow<3>(m),  2.37697e-1 * one / pow<3>(m),
      3.68552e-2 * one / pow<3>(m),  0.0 * one / pow<3>(m),         3.57202e-2 * one / pow<3>(m),
      -2.14075e-1 * one / pow<3>(m), 0.0 * one / pow<3>(m),         -1.08018e-1 * one / pow<3>(m),
      -3.73981e-1 * one / pow<3>(m), 0.0 * one / pow<3>(m),         3.10022e-2 * one / pow<3>(m),
      -1.16305e-3 * one / pow<3>(m), -2.07596e1 * one / pow<3>(m),  0.0 * one / pow<3>(m),
      8.64502e-2 * one / pow<3>(m),  0.0 * one / pow<3>(m),         9.74908e1 * one / pow<3>(m),
      5.16707e-2 * one / pow<3>(m),  0.0 * one / pow<3>(m),         0.0 * one / pow<3>(m),
      0.0 * one / pow<3>(m),         0.0 * one / pow<3>(m),         0.0 * one / pow<3>(m),
      8.66784e-2 * one / pow<3>(m),  1.58727e-1 * one / pow<3>(m),  0.0 * one / pow<3>(m),
      0.0 * one / pow<3>(m),         0.0 * one / pow<3>(m),         0.0 * one / pow<3>(m),
      0.0 * one / pow<3>(m),         3.46193e2 * one / pow<3>(m),   1.34297e-2 * one / pow<3>(m),
      0.0 * one / pow<3>(m),         0.0 * one / pow<3>(m),         0.0 * one / pow<3>(m),
      0.0 * one / pow<3>(m),         0.0 * one / pow<3>(m),         0.0 * one / pow<3>(m),
      -3.48509e-3 * one / pow<3>(m), -1.54689e-4 * one / pow<3>(m), 0.0 * one / pow<3>(m),
      0.0 * one / pow<3>(m),         8.47001e-2 * one / pow<3>(m),  1.70147e-1 * one / pow<3>(m),
      1.47753e-2 * one / pow<3>(m),  0.0 * one / pow<3>(m),         0.0 * one / pow<3>(m),
      0.0 * one / pow<3>(m),         0.0 * one / pow<3>(m),         1.89320e-2 * one / pow<3>(m),
      3.68181e-5 * one / pow<3>(m),  1.32570e-2 * one / pow<3>(m),  0.0 * one / pow<3>(m),
      0.0 * one / pow<3>(m),         3.59719e-3 * one / pow<3>(m),  7.44328e-3 * one / pow<3>(m),
      -1.00023e-3 * one / pow<3>(m), -6.50528e3 * one / pow<3>(m),  0.0 * one / pow<3>(m),
      1.03485e-2 * one / pow<3>(m),  -1.00983e-3 * one / pow<3>(m), -4.06916e-3 * one / pow<3>(m),
      -6.60864e1 * one / pow<3>(m),  -1.71533e-2 * one / pow<3>(m), 1.10605e-2 * one / pow<3>(m),
      1.20300e-2 * one / pow<3>(m),  -5.20034e-3 * one / pow<3>(m), 0.0 * one / pow<3>(m),
      0.0 * one / pow<3>(m),         0.0 * one / pow<3>(m),         0.0 * one / pow<3>(m),
      0.0 * one / pow<3>(m),         0.0 * one / pow<3>(m),         0.0 * one / pow<3>(m),
      -2.62769e3 * one / pow<3>(m),  7.13755e-3 * one / pow<3>(m),  4.17999e-3 * one / pow<3>(m),
      0.0 * one / pow<3>(m),         1.2591e4 * one / pow<3>(m),    0.0 * one / pow<3>(m),
      0.0 * one / pow<3>(m),         0.0 * one / pow<3>(m),         -2.23595e-3 * one / pow<3>(m),
      4.60217e-3 * one / pow<3>(m),  5.71794e-3 * one / pow<3>(m),  0.0 * one / pow<3>(m),
      0.0 * one / pow<3>(m),         0.0 * one / pow<3>(m),         0.0 * one / pow<3>(m),
      -3.18353e-2 * one / pow<3>(m), -2.35526e-2 * one / pow<3>(m), -1.36189e-2 * one / pow<3>(m),
      0.0 * one / pow<3>(m),         0.0 * one / pow<3>(m),         0.0 * one / pow<3>(m),
      2.03522e-2 * one / pow<3>(m),  -6.67837e1 * one / pow<3>(m),  -1.09724e-3 * one / pow<3>(m),
      0.0 * one / pow<3>(m),         -1.38821e-2 * one / pow<3>(m), 1.60468e-2 * one / pow<3>(m),
      0.0 * one / pow<3>(m),         0.0 * one / pow<3>(m),         0.0 * one / pow<3>(m),
      0.0 * one / pow<3>(m),         0.0 * one / pow<3>(m),         0.0 * one / pow<3>(m),
      0.0 * one / pow<3>(m),         1.51574e-2 * one / pow<3>(m),  -5.44470e-4 * one / pow<3>(m),
      0.0 * one / pow<3>(m),         7.28224e-2 * one / pow<3>(m),  6.59413e-2 * one / pow<3>(m),
      0.0 * one / pow<3>(m),         -5.15692e-3 * one / pow<3>(m), 0.0 * one / pow<3>(m),
      0.0 * one / pow<3>(m),         -3.70367e3 * one / pow<3>(m),  0.0 * one / pow<3>(m),
      0.0 * one / pow<3>(m),         1.36131e-2 * one / pow<3>(m),  5.38153e-3 * one / pow<3>(m),
      0.0 * one / pow<3>(m),         4.76285 * one / pow<3>(m),     -1.75677e-2 * one / pow<3>(m),
      2.26301e-2 * one / pow<3>(m),  0.0 * one / pow<3>(m),         1.76631e-2 * one / pow<3>(m),
      4.77162e-3 * one / pow<3>(m),  0.0 * one / pow<3>(m),         5.39354 * one / pow<3>(m),
      0.0 * one / pow<3>(m),         -7.51710e-3 * one / pow<3>(m), 0.0 * one / pow<3>(m),
      0.0 * one / pow<3>(m),         -8.82736e1 * one / pow<3>(m),  0.0 * one / pow<3>(m),
      0.0 * one / pow<3>(m),         0.0 * one / pow<3>(m),         0.0 * one / pow<3>(m),
      0.0 * one / pow<3>(m),         0.0 * one / pow<3>(m),         0.0 * one / pow<3>(m),
      0.0 * one / pow<3>(m),         0.0 * one / pow<3>(m),         0.0 * one / pow<3>(m),
      0.0 * one / pow<3>(m),         0.0 * one / pow<3>(m),         0.0 * one / pow<3>(m) },
    // H DENSITY
    { 1.26376 * one / pow<3>(m),     -2.14304e-1 * one / pow<3>(m), -1.49984e-1 * one / pow<3>(m),
      2.30404e-1 * one / pow<3>(m),  2.98237e-2 * one / pow<3>(m),  2.68673e-2 * one / pow<3>(m),
      2.96228e-1 * one / pow<3>(m),  2.21900e-2 * one / pow<3>(m),  -2.07655e-2 * one / pow<3>(m),
      4.52506e-1 * one / pow<3>(m),  1.20105e-1 * one / pow<3>(m),  3.24420e-2 * one / pow<3>(m),
      4.24816e-2 * one / pow<3>(m),  -9.14313 * one / pow<3>(m),    0.0 * one / pow<3>(m),
      2.47178e-2 * one / pow<3>(m),  -2.88229e-2 * one / pow<3>(m), 8.12805e1 * one / pow<3>(m),
      5.10380e-2 * one / pow<3>(m),  -5.80611e-3 * one / pow<3>(m), 2.51236e-5 * one / pow<3>(m),
      -1.24083e-2 * one / pow<3>(m), 0.0 * one / pow<3>(m),         0.0 * one / pow<3>(m),
      8.66784e-2 * one / pow<3>(m),  1.58727e-1 * one / pow<3>(m),  -3.48190e-2 * one / pow<3>(m),
      0.0 * one / pow<3>(m),         0.0 * one / pow<3>(m),         2.89885e-5 * one / pow<3>(m),
      0.0 * one / pow<3>(m),         1.53595e2 * one / pow<3>(m),   -1.68604e-2 * one / pow<3>(m),
      0.0 * one / pow<3>(m),         1.01015e-2 * one / pow<3>(m),  0.0 * one / pow<3>(m),
      0.0 * one / pow<3>(m),         0.0 * one / pow<3>(m),         0.0 * one / pow<3>(m),
      2.84552e-4 * one / pow<3>(m),  -1.22181e-3 * one / pow<3>(m), 0.0 * one / pow<3>(m),
      0.0 * one / pow<3>(m),         8.47001e-2 * one / pow<3>(m),  1.70147e-1 * one / pow<3>(m),
      -1.04927e-2 * one / pow<3>(m), 0.0 * one / pow<3>(m),         0.0 * one / pow<3>(m),
      0.0 * one / pow<3>(m),         -5.91313e-3 * one / pow<3>(m), -2.30501e-2 * one / pow<3>(m),
      3.14758e-5 * one / pow<3>(m),  0.0 * one / pow<3>(m),         0.0 * one / pow<3>(m),
      1.26956e-2 * one / pow<3>(m),  8.35489e-3 * one / pow<3>(m),  3.10513e-4 * one / pow<3>(m),
      0.0 * one / pow<3>(m),         3.42119e3 * one / pow<3>(m),   -2.45017e-3 * one / pow<3>(m),
      -4.27154e-4 * one / pow<3>(m), 5.45152e-4 * one / pow<3>(m),  1.89896e-3 * one / pow<3>(m),
      2.89121e1 * one / pow<3>(m),   -6.49973e-3 * one / pow<3>(m), -1.93855e-2 * one / pow<3>(m),
      -1.48492e-2 * one / pow<3>(m), 0.0 * one / pow<3>(m),         -5.10576e-2 * one / pow<3>(m),
      7.87306e-2 * one / pow<3>(m),  9.51981e-2 * one / pow<3>(m),  -1.49422e4 * one / pow<3>(m),
      0.0 * one / pow<3>(m),         0.0 * one / pow<3>(m),         0.0 * one / pow<3>(m),
      2.65503e2 * one / pow<3>(m),   0.0 * one / pow<3>(m),         0.0 * one / pow<3>(m),
      0.0 * one / pow<3>(m),         0.0 * one / pow<3>(m),         0.0 * one / pow<3>(m),
      0.0 * one / pow<3>(m),         0.0 * one / pow<3>(m),         6.37110e-3 * one / pow<3>(m),
      3.24789e-4 * one / pow<3>(m),  0.0 * one / pow<3>(m),         0.0 * one / pow<3>(m),
      0.0 * one / pow<3>(m),         0.0 * one / pow<3>(m),         0.0 * one / pow<3>(m),
      6.14274e-2 * one / pow<3>(m),  1.00376e-2 * one / pow<3>(m),  -8.41083e-4 * one / pow<3>(m),
      0.0 * one / pow<3>(m),         0.0 * one / pow<3>(m),         0.0 * one / pow<3>(m),
      -1.27099e-2 * one / pow<3>(m), 0.0 * one / pow<3>(m),         0.0 * one / pow<3>(m),
      0.0 * one / pow<3>(m),         -3.94077e-3 * one / pow<3>(m), -1.28601e-2 * one / pow<3>(m),
      -7.97616e-3 * one / pow<3>(m), 0.0 * one / pow<3>(m),         0.0 * one / pow<3>(m),
      0.0 * one / pow<3>(m),         0.0 * one / pow<3>(m),         0.0 * one / pow<3>(m),
      0.0 * one / pow<3>(m),         0.0 * one / pow<3>(m),         0.0 * one / pow<3>(m),
      0.0 * one / pow<3>(m),         0.0 * one / pow<3>(m),         0.0 * one / pow<3>(m),
      0.0 * one / pow<3>(m),         0.0 * one / pow<3>(m),         0.0 * one / pow<3>(m),
      0.0 * one / pow<3>(m),         0.0 * one / pow<3>(m),         0.0 * one / pow<3>(m),
      0.0 * one / pow<3>(m),         -6.71465e-3 * one / pow<3>(m), -1.69799e-3 * one / pow<3>(m),
      1.93772e-3 * one / pow<3>(m),  3.81140 * one / pow<3>(m),     -7.79290e-3 * one / pow<3>(m),
      -1.82589e-2 * one / pow<3>(m), -1.25860e-2 * one / pow<3>(m), -1.04311e-2 * one / pow<3>(m),
      -3.02465e-3 * one / pow<3>(m), 2.43063e-3 * one / pow<3>(m),  3.63237 * one / pow<3>(m),
      0.0 * one / pow<3>(m),         0.0 * one / pow<3>(m),         0.0 * one / pow<3>(m),
      0.0 * one / pow<3>(m),         0.0 * one / pow<3>(m),         0.0 * one / pow<3>(m),
      0.0 * one / pow<3>(m),         0.0 * one / pow<3>(m),         0.0 * one / pow<3>(m),
      0.0 * one / pow<3>(m),         0.0 * one / pow<3>(m),         0.0 * one / pow<3>(m),
      0.0 * one / pow<3>(m),         0.0 * one / pow<3>(m),         0.0 * one / pow<3>(m),
      0.0 * one / pow<3>(m),         0.0 * one / pow<3>(m),         0.0 * one / pow<3>(m) },
    // N DENSITY
    { 7.09557e1 * one / pow<3>(m),   -3.26740e-1 * one / pow<3>(m), 0.0 * one / pow<3>(m),
      -5.16829e-1 * one / pow<3>(m), -1.71664e-3 * one / pow<3>(m), 9.09310e-2 * one / pow<3>(m),
      -6.71500e-1 * one / pow<3>(m), -1.47771e-1 * one / pow<3>(m), -9.27471e-2 * one / pow<3>(m),
      -2.30862e-1 * one / pow<3>(m), -1.56410e-1 * one / pow<3>(m), 1.34455e-2 * one / pow<3>(m),
      -1.19717e-1 * one / pow<3>(m), 2.52151 * one / pow<3>(m),     0.0 * one / pow<3>(m),
      -2.41582e-1 * one / pow<3>(m), 5.92939e-2 * one / pow<3>(m),  4.39756 * one / pow<3>(m),
      9.15280e-2 * one / pow<3>(m),  4.41292e-3 * one / pow<3>(m),  0.0 * one / pow<3>(m),
      8.66807e-3 * one / pow<3>(m),  0.0 * one / pow<3>(m),         0.0 * one / pow<3>(m),
      8.66784e-2 * one / pow<3>(m),  1.58727e-1 * one / pow<3>(m),  9.74701e-2 * one / pow<3>(m),
      0.0 * one / pow<3>(m),         0.0 * one / pow<3>(m),         0.0 * one / pow<3>(m),
      0.0 * one / pow<3>(m),         6.70217e1 * one / pow<3>(m),   -1.31660e-3 * one / pow<3>(m),
      0.0 * one / pow<3>(m),         -1.65317e-2 * one / pow<3>(m), 0.0 * one / pow<3>(m),
      0.0 * one / pow<3>(m),         8.50247e-2 * one / pow<3>(m),  2.77428e1 * one / pow<3>(m),
      4.98658e-3 * one / pow<3>(m),  6.15115e-3 * one / pow<3>(m),  9.50156e-3 * one / pow<3>(m),
      -2.12723e-2 * one / pow<3>(m), 8.47001e-2 * one / pow<3>(m),  1.70147e-1 * one / pow<3>(m),
      -2.38645e-2 * one / pow<3>(m), 0.0 * one / pow<3>(m),         0.0 * one / pow<3>(m),
      0.0 * one / pow<3>(m),         1.37380e-3 * one / pow<3>(m),  -8.41918e-3 * one / pow<3>(m),
      2.80145e-5 * one / pow<3>(m),  7.12383e-3 * one / pow<3>(m),  0.0 * one / pow<3>(m),
      -1.66209e-2 * one / pow<3>(m), 1.03533e-4 * one / pow<3>(m),  -1.68898e-2 * one / pow<3>(m),
      0.0 * one / pow<3>(m),         3.64526e3 * one / pow<3>(m),   0.0 * one / pow<3>(m),
      6.54077e-3 * one / pow<3>(m),  3.69130e-4 * one / pow<3>(m),  9.94419e-4 * one / pow<3>(m),
      8.42803e1 * one / pow<3>(m),   -1.16124e-2 * one / pow<3>(m), -7.74414e-3 * one / pow<3>(m),
      -1.68844e-3 * one / pow<3>(m), 1.42809e-3 * one / pow<3>(m),  -1.92955e-3 * one / pow<3>(m),
      1.17225e-1 * one / pow<3>(m),  -2.41512e-2 * one / pow<3>(m), 1.50521e4 * one / pow<3>(m),
      0.0 * one / pow<3>(m),         0.0 * one / pow<3>(m),         0.0 * one / pow<3>(m),
      1.60261e3 * one / pow<3>(m),   0.0 * one / pow<3>(m),         0.0 * one / pow<3>(m),
      0.0 * one / pow<3>(m),         0.0 * one / pow<3>(m),         0.0 * one / pow<3>(m),
      0.0 * one / pow<3>(m),         0.0 * one / pow<3>(m),         -3.54403e-4 * one / pow<3>(m),
      -1.87270e-2 * one / pow<3>(m), 0.0 * one / pow<3>(m),         0.0 * one / pow<3>(m),
      0.0 * one / pow<3>(m),         0.0 * one / pow<3>(m),         0.0 * one / pow<3>(m),
      2.76439e-2 * one / pow<3>(m),  6.43207e-3 * one / pow<3>(m),  -3.54300e-2 * one / pow<3>(m),
      0.0 * one / pow<3>(m),         0.0 * one / pow<3>(m),         0.0 * one / pow<3>(m),
      -2.80221e-2 * one / pow<3>(m), 8.11228e1 * one / pow<3>(m),   -6.75255e-4 * one / pow<3>(m),
      0.0 * one / pow<3>(m),         -1.05162e-2 * one / pow<3>(m), -3.48292e-3 * one / pow<3>(m),
      -6.97321e-3 * one / pow<3>(m), 0.0 * one / pow<3>(m),         0.0 * one / pow<3>(m),
      0.0 * one / pow<3>(m),         0.0 * one / pow<3>(m),         0.0 * one / pow<3>(m),
      0.0 * one / pow<3>(m),         0.0 * one / pow<3>(m),         0.0 * one / pow<3>(m),
      0.0 * one / pow<3>(m),         0.0 * one / pow<3>(m),         0.0 * one / pow<3>(m),
      0.0 * one / pow<3>(m),         0.0 * one / pow<3>(m),         0.0 * one / pow<3>(m),
      0.0 * one / pow<3>(m),         0.0 * one / pow<3>(m),         0.0 * one / pow<3>(m),
      0.0 * one / pow<3>(m),         -1.45546e-3 * one / pow<3>(m), -1.31970e-2 * one / pow<3>(m),
      -3.57751e-3 * one / pow<3>(m), -1.09021 * one / pow<3>(m),    -1.50181e-2 * one / pow<3>(m),
      -7.12841e-3 * one / pow<3>(m), -6.64590e-3 * one / pow<3>(m), -3.52610e-3 * one / pow<3>(m),
      -1.87773e-2 * one / pow<3>(m), -2.22432e-3 * one / pow<3>(m), -3.93895e-1 * one / pow<3>(m),
      0.0 * one / pow<3>(m),         0.0 * one / pow<3>(m),         0.0 * one / pow<3>(m),
      0.0 * one / pow<3>(m),         0.0 * one / pow<3>(m),         0.0 * one / pow<3>(m),
      0.0 * one / pow<3>(m),         0.0 * one / pow<3>(m),         0.0 * one / pow<3>(m),
      0.0 * one / pow<3>(m),         0.0 * one / pow<3>(m),         0.0 * one / pow<3>(m),
      0.0 * one / pow<3>(m),         0.0 * one / pow<3>(m),         0.0 * one / pow<3>(m),
      0.0 * one / pow<3>(m),         0.0 * one / pow<3>(m),         0.0 * one / pow<3>(m) },
    // HOT O DENSITY
    { 6.04050e-2 * one / pow<3>(m),  1.57034 * one / pow<3>(m),    2.99387e-2 * one / pow<3>(m),
      0.0 * one / pow<3>(m),         0.0 * one / pow<3>(m),        0.0 * one / pow<3>(m),
      0.0 * one / pow<3>(m),         0.0 * one / pow<3>(m),        0.0 * one / pow<3>(m),
      -1.51018 * one / pow<3>(m),    0.0 * one / pow<3>(m),        0.0 * one / pow<3>(m),
      0.0 * one / pow<3>(m),         -8.61650 * one / pow<3>(m),   1.26454e-2 * one / pow<3>(m),
      0.0 * one / pow<3>(m),         0.0 * one / pow<3>(m),        0.0 * one / pow<3>(m),
      0.0 * one / pow<3>(m),         0.0 * one / pow<3>(m),        0.0 * one / pow<3>(m),
      5.50878e-3 * one / pow<3>(m),  0.0 * one / pow<3>(m),        0.0 * one / pow<3>(m),
      8.66784e-2 * one / pow<3>(m),  1.58727e-1 * one / pow<3>(m), 0.0 * one / pow<3>(m),
      0.0 * one / pow<3>(m),         0.0 * one / pow<3>(m),        0.0 * one / pow<3>(m),
      0.0 * one / pow<3>(m),         0.0 * one / pow<3>(m),        6.23881e-2 * one / pow<3>(m),
      0.0 * one / pow<3>(m),         0.0 * one / pow<3>(m),        0.0 * one / pow<3>(m),
      0.0 * one / pow<3>(m),         0.0 * one / pow<3>(m),        0.0 * one / pow<3>(m),
      0.0 * one / pow<3>(m),         0.0 * one / pow<3>(m),        0.0 * one / pow<3>(m),
      0.0 * one / pow<3>(m),         8.47001e-2 * one / pow<3>(m), 1.70147e-1 * one / pow<3>(m),
      -9.45934e-2 * one / pow<3>(m), 0.0 * one / pow<3>(m),        0.0 * one / pow<3>(m),
      0.0 * one / pow<3>(m),         0.0 * one / pow<3>(m),        0.0 * one / pow<3>(m),
      0.0 * one / pow<3>(m),         0.0 * one / pow<3>(m),        0.0 * one / pow<3>(m),
      0.0 * one / pow<3>(m),         0.0 * one / pow<3>(m),        0.0 * one / pow<3>(m),
      0.0 * one / pow<3>(m),         0.0 * one / pow<3>(m),        0.0 * one / pow<3>(m),
      0.0 * one / pow<3>(m),         0.0 * one / pow<3>(m),        0.0 * one / pow<3>(m),
      0.0 * one / pow<3>(m),         0.0 * one / pow<3>(m),        0.0 * one / pow<3>(m),
      0.0 * one / pow<3>(m),         0.0 * one / pow<3>(m),        0.0 * one / pow<3>(m),
      0.0 * one / pow<3>(m),         0.0 * one / pow<3>(m),        0.0 * one / pow<3>(m),
      0.0 * one / pow<3>(m),         0.0 * one / pow<3>(m),        0.0 * one / pow<3>(m),
      0.0 * one / pow<3>(m),         0.0 * one / pow<3>(m),        0.0 * one / pow<3>(m),
      0.0 * one / pow<3>(m),         0.0 * one / pow<3>(m),        0.0 * one / pow<3>(m),
      0.0 * one / pow<3>(m),         0.0 * one / pow<3>(m),        0.0 * one / pow<3>(m),
      0.0 * one / pow<3>(m),         0.0 * one / pow<3>(m),        0.0 * one / pow<3>(m),
      0.0 * one / pow<3>(m),         0.0 * one / pow<3>(m),        0.0 * one / pow<3>(m),
      0.0 * one / pow<3>(m),         0.0 * one / pow<3>(m),        0.0 * one / pow<3>(m),
      0.0 * one / pow<3>(m),         0.0 * one / pow<3>(m),        0.0 * one / pow<3>(m),
      0.0 * one / pow<3>(m),         0.0 * one / pow<3>(m),        0.0 * one / pow<3>(m),
      0.0 * one / pow<3>(m),         0.0 * one / pow<3>(m),        0.0 * one / pow<3>(m),
      0.0 * one / pow<3>(m),         0.0 * one / pow<3>(m),        0.0 * one / pow<3>(m),
      0.0 * one / pow<3>(m),         0.0 * one / pow<3>(m),        0.0 * one / pow<3>(m),
      0.0 * one / pow<3>(m),         0.0 * one / pow<3>(m),        0.0 * one / pow<3>(m),
      0.0 * one / pow<3>(m),         0.0 * one / pow<3>(m),        0.0 * one / pow<3>(m),
      0.0 * one / pow<3>(m),         0.0 * one / pow<3>(m),        0.0 * one / pow<3>(m),
      0.0 * one / pow<3>(m),         0.0 * one / pow<3>(m),        0.0 * one / pow<3>(m),
      0.0 * one / pow<3>(m),         0.0 * one / pow<3>(m),        0.0 * one / pow<3>(m),
      0.0 * one / pow<3>(m),         0.0 * one / pow<3>(m),        0.0 * one / pow<3>(m),
      0.0 * one / pow<3>(m),         0.0 * one / pow<3>(m),        0.0 * one / pow<3>(m),
      0.0 * one / pow<3>(m),         0.0 * one / pow<3>(m),        0.0 * one / pow<3>(m),
      0.0 * one / pow<3>(m),         0.0 * one / pow<3>(m),        0.0 * one / pow<3>(m),
      0.0 * one / pow<3>(m),         0.0 * one / pow<3>(m),        0.0 * one / pow<3>(m),
      0.0 * one / pow<3>(m),         0.0 * one / pow<3>(m),        0.0 * one / pow<3>(m),
      0.0 * one / pow<3>(m),         0.0 * one / pow<3>(m),        0.0 * one / pow<3>(m),
      0.0 * one / pow<3>(m),         0.0 * one / pow<3>(m),        0.0 * one / pow<3>(m),
      0.0 * one / pow<3>(m),         0.0 * one / pow<3>(m),        0.0 * one / pow<3>(m) }
};

/** NRLMSISE-00 data: ps[150]. */
static const quantity[] PS = {
    9.56827e-1, 6.20637e-2, 3.18433e-2,  0.0,         0.0,        3.94900e-2, 0.0, 0.0, -9.24882e-3, -7.94023e-3,
    0.0,        0.0,        0.0,         1.74712e2,   0.0,        0.0,        0.0, 0.0, 0.0,         0.0,
    0.0,        2.74677e-3, 0.0,         1.54951e-2,  8.66784e-2, 1.58727e-1, 0.0, 0.0, 0.0,         0.0,
    0.0,        0.0,        0.0,         -6.99007e-4, 0.0,        0.0,        0.0, 0.0, 0.0,         0.0,
    0.0,        1.24362e-2, -5.28756e-3, 8.47001e-2,  1.70147e-1, 0.0,        0.0, 0.0, 0.0,         0.0,
    0.0,        2.47425e-5, 0.0,         0.0,         0.0,        0.0,        0.0, 0.0, 0.0,         0.0,
    0.0,        0.0,        0.0,         0.0,         0.0,        0.0,        0.0, 0.0, 0.0,         0.0,
    0.0,        0.0,        0.0,         0.0,         0.0,        0.0,        0.0, 0.0, 0.0,         0.0,
    0.0,        0.0,        0.0,         0.0,         0.0,        0.0,        0.0, 0.0, 0.0,         0.0,
    0.0,        0.0,        0.0,         0.0,         0.0,        0.0,        0.0, 0.0, 0.0,         0.0,
    0.0,        0.0,        0.0,         0.0,         0.0,        0.0,        0.0, 0.0, 0.0,         0.0,
    0.0,        0.0,        0.0,         0.0,         0.0,        0.0,        0.0, 0.0, 0.0,         0.0,
    0.0,        0.0,        0.0,         0.0,         0.0,        0.0,        0.0, 0.0, 0.0,         0.0,
    0.0,        0.0,        0.0,         0.0,         0.0,        0.0,        0.0, 0.0, 0.0,         0.0,
    0.0,        0.0,        0.0,         0.0,         0.0,        0.0,        0.0, 0.0, 0.0,         0.0
};

/** NRLMSISE-00 data: TURBO pdl[2][25]. */
static const quantity[][] PDL = {
    { 1.09930, 3.90631, 3.07165, 9.86161e-1, 1.63536e1, 4.63830, 1.0, 0.0, 0.0, 0.0,     0.0,        0.0,       0.0,
      0.0,     0.0,     0.0,     0.0,        0.0,       0.0,     0.0, 0.0, 0.0, 1.28840, 3.10302e-2, 1.18339e-1 },
    { 1.0,        7.00000e-1, 1.15020,   3.44689,    1.28840, 1.0,         1.08738,   1.22947,     1.10016,
      7.34129e-1, 1.15241,    2.22784,   7.95046e-1, 4.01612, 4.47749,     1.23435e2, -7.60535e-2, 1.68986e-6,
      7.44294e-1, 1.03604,    1.72783e2, 1.15020,    3.44689, -7.46230e-1, 9.49154e-1 }
};

/** NRLMSISE-00 data: LOWER BOUNDARY ptm[10]. */
struct BatesProfileParams {
    Temperature Tinf;
    Temperature Tlb0;
    Temperature TN12;
    quantity<K / km> S0;
    Temperature TN14;
    Distance Zlb;
    Temperature TN11;
    Temperature TN13;
    quantity<K / km> Tgrad;
};
static const BatesProfileParams PTM = { mp_units::point<K>(1.0413e3), mp_units::point<K>(3.86e2),
                                        mp_units::point<K>(1.95e2),   mp_units::delta<K / km>(1.66728e1),
                                        mp_units::point<K>(2.13e2),   1.2e2 * km,
                                        mp_units::point<K>(2.4e2),    mp_units::point<K>(1.87e2),
                                        mp_units::delta<K / km>(-2.0) };

/// Mean molecular mass of the well-mixed lower atmosphere (amu), corresponding to SpeciesModelData[N2][4] in the Fortran source.
static const AtomicMass XMM = 28.9500 * u;

/// Per-species empirical parameters for NRLMSISE-00 diffusive and mixed-region density calculations.
struct SpeciesModelParams {
    NumberDensity nRef; ///< cm⁻³: reference number density at lower boundary
    Unitless mixRatio;  ///< dimensionless: mixing ratio / density correction factor
    Distance zh;        ///< turbopause altitude
    Unitless c3;        ///< species-specific: zhm scale height (N2) or rc correction ratio (O, O2, H, N)
    Distance za;        ///< primary ccor correction centre altitude (N2: unused, set to 0)
    Distance ha;        ///< primary ccor correction scale height
    Distance zb;        ///< secondary ccor correction centre altitude
    Distance hb;        ///< secondary ccor correction scale height
    Unitless c9;        ///< anomalous O only: secondary thermal reference parameter
};

enum Species {
    HELIUM             = 0,
    ATOMIC_OXYGEN      = 1,
    MOLECULAR_NITROGEN = 2,
    MOLECULAR_OXYGEN   = 3,
    ARGON              = 4,
    TOTAL_MASS         = 5,
    HYDROGEN           = 6,
    ATOMIC_NITROGEN    = 7,
    ANOMALOUS_OXYGEN   = 8
};

/** NRLMSISE-00 data: pdm[8][10]. */
static const std::unordered_map<Species, SpeciesModelParams> SpeciesModelData = { {
    { HELIUM, { 2.456e7 * pow<-3>(cm), 6.71072e-6 * one, 1.0e2 * km, 0.0 * one, 1.1e2 * km, 1.0e1 * km, 0.0 * km, 0.0 * km, 0.0 * one } },
    { ATOMIC_OXYGEN,
      { 8.594e+10 * pow<-3>(cm), 1.0 * one, 1.05e2 * km, -8.0 * one, 1.1e2 * km, 1.0e1 * km, 9.0e1 * km, 2.0 * km, 0.0 * one } },
    { MOLECULAR_NITROGEN,
      { 2.81e+11 * pow<-3>(cm), 0.0 * one, 1.05e2 * km, 2.8e1 * one, 0.0 * km, 0.0 * km, 0.0 * km, 0.0 * km, 0.0 * one } },
    { MOLECULAR_OXYGEN,
      { 3.3e+10 * pow<-3>(cm), 2.68270e-1 * one, 1.05e2 * km, 1.0 * one, 1.1e2 * km, 1.0e1 * km, 1.1e2 * km, -1.0e1 * km, 0.0 * one } },
    { ARGON, { 1.33e9 * pow<-3>(cm), 1.19615e-2 * one, 1.05e2 * km, 0.0 * one, 1.1e2 * km, 1.0e1 * km, 0.0 * km, 0.0 * km, 0.0 * one } },
    { HYDROGEN, { 1.761e5 * pow<-3>(cm), 1.0 * one, 9.5e1 * km, -8.0 * one, 1.1e2 * km, 1.0e1 * km, 9.0e1 * km, 2.0 * km, 0.0 * one } },
    { ATOMIC_NITROGEN,
      { 1.0e7 * pow<-3>(cm), 1.0 * one, 1.05e2 * km, -8.0 * one, 1.1e2 * km, 1.0e1 * km, 9.0e1 * km, 2.0 * km, 0.0 * one } },
    { ANOMALOUS_OXYGEN,
      { 1.0e6 * pow<-3>(cm), 1.0 * one, 1.05e2 * km, -8.0 * one, 5.5e2 * km, 7.6e1 * km, 9.0e1 * km, 2.0 * km, 4.0e3 * one } },
} };

/** NRLMSISE-00 data: ptl[4][100]. */
static const quantity[][] PTL = {
    // TN1(2)
    { 1.00858,     4.56011e-2,  -2.22972e-2, -5.44388e-2, 5.23136e-4,  -1.88849e-2, 5.23707e-2, -9.43646e-3,
      6.31707e-3,  -7.80460e-2, -4.88430e-2, 0.0,         0.0,         -7.60250,    0.0,        -1.44635e-2,
      -1.76843e-2, -1.21517e2,  2.85647e-2,  0.0,         0.0,         6.31792e-4,  0.0,        5.77197e-3,
      8.66784e-2,  1.58727e-1,  0.0,         0.0,         0.0,         0.0,         0.0,        -8.90272e3,
      3.30611e-3,  3.02172e-3,  0.0,         -2.13673e-3, -3.20910e-4, 0.0,         0.0,        2.76034e-3,
      2.82487e-3,  -2.97592e-4, -4.21534e-3, 8.47001e-2,  1.70147e-1,  8.96456e-3,  0.0,        -1.08596e-2,
      0.0,         0.0,         5.57917e-3,  0.0,         0.0,         0.0,         0.0,        0.0,
      0.0,         0.0,         0.0,         0.0,         0.0,         0.0,         0.0,        0.0,
      0.0,         0.0,         0.0,         0.0,         0.0,         0.0,         0.0,        0.0,
      0.0,         0.0,         0.0,         0.0,         0.0,         0.0,         0.0,        0.0,
      0.0,         0.0,         0.0,         0.0,         0.0,         0.0,         0.0,        0.0,
      0.0,         0.0,         0.0,         0.0,         0.0,         0.0,         0.0,        0.0,
      9.65405e-3,  0.0,         0.0,         2.0 },
    // TN1(3)
    { 9.39664e-1,  8.56514e-2, -6.79989e-3, 2.65929e-2,  -4.74283e-3, 1.21855e-2, -2.14905e-2, 6.49651e-3,  -2.05477e-2,
      -4.24952e-2, 0.0,        0.0,         0.0,         1.19148e1,   0.0,        1.18777e-2,  -7.28230e-2, -8.15965e1,
      1.73887e-2,  0.0,        0.0,         0.0,         -1.44691e-2, 2.80259e-4, 8.66784e-2,  1.58727e-1,  0.0,
      0.0,         0.0,        0.0,         0.0,         2.16584e2,   3.18713e-3, 7.37479e-3,  0.0,         -2.55018e-3,
      -3.92806e-3, 0.0,        0.0,         -2.89757e-3, -1.33549e-3, 1.02661e-3, 3.53775e-4,  8.47001e-2,  1.70147e-1,
      -9.17497e-3, 0.0,        0.0,         0.0,         0.0,         3.56082e-3, 0.0,         0.0,         0.0,
      0.0,         0.0,        0.0,         0.0,         0.0,         0.0,        0.0,         0.0,         0.0,
      0.0,         0.0,        0.0,         0.0,         0.0,         0.0,        0.0,         0.0,         0.0,
      0.0,         0.0,        0.0,         0.0,         0.0,         0.0,        0.0,         0.0,         0.0,
      0.0,         0.0,        0.0,         0.0,         0.0,         0.0,        0.0,         0.0,         0.0,
      0.0,         0.0,        0.0,         0.0,         0.0,         0.0,        -1.00902e-2, 0.0,         0.0,
      2.0 },
    // TN1(4)
    { 9.85982e-1,  -4.55435e-2, 1.21106e-2,  2.04127e-2,  -2.40836e-3, 1.11383e-2, -4.51926e-2, 1.35074e-2,
      -6.54139e-3, 1.15275e-1,  1.28247e-1,  0.0,         0.0,         -5.30705,   0.0,         -3.79332e-2,
      -6.24741e-2, 7.71062e-1,  2.96315e-2,  0.0,         0.0,         0.0,        6.81051e-3,  -4.34767e-3,
      8.66784e-2,  1.58727e-1,  0.0,         0.0,         0.0,         0.0,        0.0,         1.07003e1,
      -2.76907e-3, 4.32474e-4,  0.0,         1.31497e-3,  -6.47517e-4, 0.0,        -2.20621e1,  -1.10804e-3,
      -8.09338e-4, 4.18184e-4,  4.29650e-3,  8.47001e-2,  1.70147e-1,  0.0,        0.0,         0.0,
      0.0,         0.0,         -4.04337e-3, 0.0,         0.0,         0.0,        0.0,         0.0,
      0.0,         0.0,         0.0,         0.0,         0.0,         0.0,        0.0,         0.0,
      -9.52550e-4, 8.56253e-4,  4.33114e-4,  0.0,         0.0,         0.0,        0.0,         0.0,
      0.0,         0.0,         1.21223e-3,  2.38694e-4,  9.15245e-4,  1.28385e-3, 8.67668e-4,  -5.61425e-6,
      1.04445,     3.41112e1,   0.0,         -8.40704e-1, -2.39639e2,  7.06668e-1, -2.05873e1,  -3.63696e-1,
      2.39245e1,   0.0,         -1.06657e-3, -7.67292e-4, 1.54534e-4,  0.0,        0.0,         0.0,
      0.0,         0.0,         0.0,         2.0 },
    // TN1(5) TN2(1)
    { 1.00320,     3.83501e-2,  -2.38983e-3, 2.83950e-3,  4.20956e-3,  5.86619e-4,  2.19054e-2,  -1.00946e-2,
      -3.50259e-3, 4.17392e-2,  -8.44404e-3, 0.0,         0.0,         4.96949,     0.0,         -7.06478e-3,
      -1.46494e-2, 3.13258e1,   -1.86493e-3, 0.0,         -1.67499e-2, 0.0,         0.0,         5.12686e-4,
      8.66784e-2,  1.58727e-1,  -4.64167e-3, 0.0,         0.0,         0.0,         4.37353e-3,  -1.99069e2,
      0.0,         -5.34884e-3, 0.0,         1.62458e-3,  2.93016e-3,  2.67926e-3,  5.90449e2,   0.0,
      0.0,         -1.17266e-3, -3.58890e-4, 8.47001e-2,  1.70147e-1,  0.0,         0.0,         1.38673e-2,
      0.0,         0.0,         0.0,         0.0,         0.0,         0.0,         0.0,         0.0,
      0.0,         0.0,         0.0,         0.0,         0.0,         0.0,         0.0,         0.0,
      1.60571e-3,  6.28078e-4,  5.05469e-5,  0.0,         0.0,         0.0,         0.0,         0.0,
      0.0,         0.0,         -1.57829e-3, -4.00855e-4, 5.04077e-5,  -1.39001e-3, -2.33406e-3, -4.81197e-4,
      1.46758,     6.20332,     0.0,         3.66476e-1,  -6.1976e1,   3.09198e-1,  -1.98999e1,  0.0,
      -3.29933e2,  0.0,         -1.10080e-3, -9.39310e-5, 1.39638e-4,  0.0,         0.0,         0.0,
      0.0,         0.0,         0.0,         2.0 }
};

/** NRLMSISE-00 data: pma[10][100]. */
static const quantity[][] PMA = {
    // TN2(2)
    { 9.81637e-1,  -1.41317e-3, 3.87323e-2,  0.0,        0.0,        0.0,         0.0,         0.0,
      0.0,         -3.58707e-2, -8.63658e-3, 0.0,        0.0,        -2.02226,    0.0,         -8.69424e-3,
      -1.91397e-2, 8.76779e1,   4.52188e-3,  0.0,        2.23760e-2, 0.0,         0.0,         0.0,
      0.0,         0.0,         -7.07572e-3, 0.0,        0.0,        0.0,         -4.11210e-3, 3.5006e1,
      0.0,         0.0,         0.0,         0.0,        0.0,        -8.36657e-3, 1.61347e1,   0.0,
      0.0,         0.0,         0.0,         0.0,        0.0,        0.0,         0.0,         -1.45130e-2,
      0.0,         0.0,         0.0,         0.0,        0.0,        0.0,         0.0,         0.0,
      0.0,         0.0,         0.0,         0.0,        0.0,        0.0,         0.0,         0.0,
      1.24152e-3,  6.43365e-4,  0.0,         0.0,        0.0,        0.0,         0.0,         0.0,
      0.0,         0.0,         1.33255e-3,  2.42657e-3, 1.60666e-3, -1.85728e-3, -1.46874e-3, -4.79163e-6,
      1.22464,     3.5351e1,    0.0,         4.49223e-1, -4.77466e1, 4.70681e-1,  8.41861,     -2.88198e-1,
      1.67854e2,   0.0,         7.11493e-4,  6.05601e-4, 0.0,        0.0,         0.0,         0.0,
      0.0,         0.0,         0.0,         2.0 },
    // TN2(3)
    { 1.00422,     -7.11212e-3, 5.24480e-3,  0.0,        0.0,        0.0,         0.0,         0.0,        0.0,
      -5.28914e-2, -2.41301e-2, 0.0,         0.0,        -2.12219e1, -1.03830e-2, -3.28077e-3, 1.65727e-2, 1.68564,
      -6.68154e-3, 0.0,         1.45155e-2,  0.0,        8.42365e-3, 0.0,         0.0,         0.0,        -4.34645e-3,
      0.0,         0.0,         2.16780e-2,  0.0,        -1.38459e2, 0.0,         0.0,         0.0,        0.0,
      0.0,         7.04573e-3,  -4.73204e1,  0.0,        0.0,        0.0,         0.0,         0.0,        0.0,
      0.0,         0.0,         1.08767e-2,  0.0,        0.0,        0.0,         0.0,         0.0,        0.0,
      0.0,         0.0,         0.0,         0.0,        0.0,        -8.08279e-3, 0.0,         0.0,        0.0,
      0.0,         5.21769e-4,  -2.27387e-4, 0.0,        0.0,        0.0,         0.0,         0.0,        0.0,
      0.0,         0.0,         3.26769e-3,  3.16901e-3, 4.60316e-4, -1.01431e-4, 1.02131e-3,  9.96601e-4, 1.25707,
      2.50114e1,   0.0,         4.24472e-1,  -2.77655e1, 3.44625e-1, 2.75412e1,   0.0,         7.94251e2,  0.0,
      2.45835e-3,  1.38871e-3,  0.0,         0.0,        0.0,        0.0,         0.0,         0.0,        0.0,
      2.0 },
    // TN2(4) TN3(1)
    { 1.01890,     -2.46603e-2, 1.00078e-2,  0.0,         0.0,         0.0,         0.0,        0.0,        0.0,
      -6.70977e-2, -4.02286e-2, 0.0,         0.0,         -2.29466e1,  -7.47019e-3, 2.26580e-3, 2.63931e-2, 3.72625e1,
      -6.39041e-3, 0.0,         9.58383e-3,  0.0,         0.0,         0.0,         0.0,        0.0,        -1.85291e-3,
      0.0,         0.0,         0.0,         0.0,         1.39717e2,   0.0,         0.0,        0.0,        0.0,
      0.0,         9.19771e-3,  -3.69121e2,  0.0,         0.0,         0.0,         0.0,        0.0,        0.0,
      0.0,         0.0,         -1.57067e-2, 0.0,         0.0,         0.0,         0.0,        0.0,        0.0,
      0.0,         0.0,         0.0,         0.0,         0.0,         -7.07265e-3, 0.0,        0.0,        0.0,
      0.0,         -2.92953e-3, -2.77739e-3, -4.40092e-4, 0.0,         0.0,         0.0,        0.0,        0.0,
      0.0,         0.0,         2.47280e-3,  2.95035e-4,  -1.81246e-3, 2.81945e-3,  4.27296e-3, 9.78863e-4, 1.40545,
      -6.19173,    0.0,         0.0,         -7.93632e1,  4.44643e-1,  -4.03085e2,  0.0,        1.15603e1,  0.0,
      2.25068e-3,  8.48557e-4,  -2.98493e-4, 0.0,         0.0,         0.0,         0.0,        0.0,        0.0,
      2.0 },
    // TN3(2)
    { 9.75801e-1,  3.80680e-2,  -3.05198e-2, 0.0,         0.0,         0.0,         0.0,         0.0,
      0.0,         3.85575e-2,  5.04057e-2,  0.0,         0.0,         -1.76046e2,  1.44594e-2,  -1.48297e-3,
      -3.68560e-3, 3.02185e1,   -3.23338e-3, 0.0,         1.53569e-2,  0.0,         -1.15558e-2, 0.0,
      0.0,         0.0,         4.89620e-3,  0.0,         0.0,         -1.00616e-2, -8.21324e-3, -1.57757e2,
      0.0,         0.0,         0.0,         0.0,         0.0,         6.63564e-3,  4.5841e1,    0.0,
      0.0,         0.0,         0.0,         0.0,         0.0,         0.0,         0.0,         -2.51280e-2,
      0.0,         0.0,         0.0,         0.0,         0.0,         0.0,         0.0,         0.0,
      0.0,         0.0,         0.0,         9.91215e-3,  0.0,         0.0,         0.0,         0.0,
      -8.73148e-4, -1.29648e-3, -7.32026e-5, 0.0,         0.0,         0.0,         0.0,         0.0,
      0.0,         0.0,         -4.68110e-3, -4.66003e-3, -1.31567e-3, -7.39390e-4, 6.32499e-4,  -4.65588e-4,
      -1.29785,    -1.57139e2,  0.0,         2.58350e-1,  -3.69453e1,  4.10672e-1,  9.78196,     -1.52064e-1,
      -3.85084e3,  0.0,         -8.52706e-4, -1.40945e-3, -7.26786e-4, 0.0,         0.0,         0.0,
      0.0,         0.0,         0.0,         2.0 },
    // TN3(3)
    { 9.60722e-1,  7.03757e-2,  -3.00266e-2, 0.0,         0.0,         0.0,         0.0,        0.0,         0.0,
      2.22671e-2,  4.10423e-2,  0.0,         0.0,         -1.6307e2,   1.06073e-2,  5.40747e-4, 7.79481e-3,  1.44908e2,
      1.51484e-4,  0.0,         1.97547e-2,  0.0,         -1.41844e-2, 0.0,         0.0,        0.0,         5.77884e-3,
      0.0,         0.0,         9.74319e-3,  0.0,         -2.88015e3,  0.0,         0.0,        0.0,         0.0,
      0.0,         -4.44902e-3, -2.9276e1,   0.0,         0.0,         0.0,         0.0,        0.0,         0.0,
      0.0,         0.0,         2.34419e-2,  0.0,         0.0,         0.0,         0.0,        0.0,         0.0,
      0.0,         0.0,         0.0,         0.0,         0.0,         5.36685e-3,  0.0,        0.0,         0.0,
      0.0,         -4.65325e-4, -5.50628e-4, 3.31465e-4,  0.0,         0.0,         0.0,        0.0,         0.0,
      0.0,         0.0,         -2.06179e-3, -3.08575e-3, -7.93589e-4, -1.08629e-4, 5.95511e-4, -9.05050e-4, 1.18997,
      4.15924e1,   0.0,         -4.72064e-1, -9.4715e2,   3.98723e-1,  1.98304e1,   0.0,        3.73219e3,   0.0,
      -1.50040e-3, -1.14933e-3, -1.56769e-4, 0.0,         0.0,         0.0,         0.0,        0.0,         0.0,
      2.0 },
    // TN3(4)
    { 1.03123,     -7.05124e-2, 8.71615e-3,  0.0,         0.0,         0.0,        0.0,         0.0,         0.0,
      -3.82621e-2, -9.80975e-3, 0.0,         0.0,         2.89286e1,   9.57341e-3, 0.0,         0.0,         8.66153e1,
      7.91938e-4,  0.0,         0.0,         0.0,         4.68917e-3,  0.0,        0.0,         0.0,         7.86638e-3,
      0.0,         0.0,         9.90827e-3,  0.0,         6.55573e1,   0.0,        0.0,         0.0,         0.0,
      0.0,         0.0,         -4.002e1,    0.0,         0.0,         0.0,        0.0,         0.0,         0.0,
      0.0,         0.0,         7.07457e-3,  0.0,         0.0,         0.0,        0.0,         0.0,         0.0,
      0.0,         0.0,         0.0,         0.0,         0.0,         5.72268e-3, 0.0,         0.0,         0.0,
      0.0,         -2.04970e-4, 1.21560e-3,  -8.05579e-6, 0.0,         0.0,        0.0,         0.0,         0.0,
      0.0,         0.0,         -2.49941e-3, -4.57256e-4, -1.59311e-4, 2.96481e-4, -1.77318e-3, -6.37918e-4, 1.02395,
      1.28172e1,   0.0,         1.49903e-1,  -2.63818e1,  0.0,         4.70628e1,  -2.22139e-1, 4.82292e-2,  0.0,
      -8.67075e-4, -5.86479e-4, 5.32462e-4,  0.0,         0.0,         0.0,        0.0,         0.0,         0.0,
      2.0 },
    // TN3(5) SURFACE TEMP TSL
    { 1.00828,     -9.10404e-2, -2.26549e-2, 0.0,        0.0,        0.0,        0.0,         0.0,         0.0,
      -2.32420e-2, -9.08925e-3, 0.0,         0.0,        3.36105e1,  0.0,        0.0,         0.0,         -1.24957e1,
      -5.87939e-3, 0.0,         0.0,         0.0,        0.0,        0.0,        0.0,         0.0,         0.0,
      0.0,         0.0,         0.0,         0.0,        2.79765e1,  0.0,        0.0,         0.0,         0.0,
      0.0,         0.0,         2.01237e3,   0.0,        0.0,        0.0,        0.0,         0.0,         0.0,
      0.0,         0.0,         -1.75553e-2, 0.0,        0.0,        0.0,        0.0,         0.0,         0.0,
      0.0,         0.0,         0.0,         0.0,        0.0,        0.0,        0.0,         0.0,         0.0,
      0.0,         3.29699e-3,  1.26659e-3,  2.68402e-4, 0.0,        0.0,        0.0,         0.0,         0.0,
      0.0,         0.0,         1.17894e-3,  1.48746e-3, 1.06478e-4, 1.34743e-4, -2.20939e-3, -6.23523e-4, 6.36539e-1,
      1.13621e1,   0.0,         -3.93777e-1, 2.38687e3,  0.0,        6.61865e2,  -1.21434e-1, 9.27608,     0.0,
      1.68478e-4,  1.24892e-3,  1.71345e-3,  0.0,        0.0,        0.0,        0.0,         0.0,         0.0,
      2.0 },
    // TGN3(2) SURFACE GRAD TSLG
    { 1.57293, -6.78400e-1, 6.47500e-1,  0.0, 0.0, 0.0,       0.0, 0.0,       0.0, -7.62974e-2, -3.60423e-1, 0.0,
      0.0,     1.28358e2,   0.0,         0.0, 0.0, 4.68038e1, 0.0, 0.0,       0.0, 0.0,         0.0,         0.0,
      0.0,     0.0,         -1.67898e-1, 0.0, 0.0, 0.0,       0.0, 2.90994e4, 0.0, 0.0,         0.0,         0.0,
      0.0,     0.0,         3.15706e1,   0.0, 0.0, 0.0,       0.0, 0.0,       0.0, 0.0,         0.0,         0.0,
      0.0,     0.0,         0.0,         0.0, 0.0, 0.0,       0.0, 0.0,       0.0, 0.0,         0.0,         0.0,
      0.0,     0.0,         0.0,         0.0, 0.0, 0.0,       0.0, 0.0,       0.0, 0.0,         0.0,         0.0,
      0.0,     0.0,         0.0,         0.0, 0.0, 0.0,       0.0, 0.0,       0.0, 0.0,         0.0,         0.0,
      0.0,     0.0,         0.0,         0.0, 0.0, 0.0,       0.0, 0.0,       0.0, 0.0,         0.0,         0.0,
      0.0,     0.0,         0.0,         2.0 },
    // TGN2(1) TGN1(2)
    { 8.60028e-1, 3.77052e-1, 0.0, 0.0,        0.0,         0.0,        0.0,        0.0,        0.0,         -1.17570,
      0.0,        0.0,        0.0, 7.77757e-3, 0.0,         0.0,        0.0,        1.01024e2,  0.0,         0.0,
      0.0,        0.0,        0.0, 0.0,        0.0,         0.0,        0.0,        0.0,        0.0,         0.0,
      0.0,        6.54251e2,  0.0, 0.0,        0.0,         0.0,        0.0,        0.0,        0.0,         0.0,
      0.0,        0.0,        0.0, 0.0,        0.0,         0.0,        0.0,        0.0,        0.0,         0.0,
      0.0,        0.0,        0.0, 0.0,        0.0,         0.0,        0.0,        0.0,        0.0,         0.0,
      0.0,        0.0,        0.0, 0.0,        0.0,         0.0,        0.0,        0.0,        0.0,         0.0,
      0.0,        0.0,        0.0, 0.0,        -1.56959e-2, 1.91001e-2, 3.15971e-2, 1.00982e-2, -6.71565e-3, 2.57693e-3,
      1.38692,    2.82132e-1, 0.0, 0.0,        3.81511e2,   0.0,        0.0,        0.0,        0.0,         0.0,
      0.0,        0.0,        0.0, 0.0,        0.0,         0.0,        0.0,        0.0,        0.0,         2.0 },
    // TGN3(1) TGN2(2)
    { 1.06029,    -5.25231e-2, 3.73034e-1,  0.0,        0.0,        0.0,         0.0,         0.0,         0.0,
      3.31072e-2, -3.88409e-1, 0.0,         0.0,        -1.65295e2, -2.13801e-1, -4.38916e-2, -3.22716e-1, -8.82393e1,
      1.18458e-1, 0.0,         -4.35863e-1, 0.0,        0.0,        0.0,         0.0,         0.0,         -1.19782e-1,
      0.0,        0.0,         0.0,         0.0,        2.62229e1,  0.0,         0.0,         0.0,         0.0,
      0.0,        0.0,         -5.37443e1,  0.0,        0.0,        0.0,         0.0,         0.0,         0.0,
      0.0,        0.0,         -4.55788e-1, 0.0,        0.0,        0.0,         0.0,         0.0,         0.0,
      0.0,        0.0,         0.0,         0.0,        0.0,        0.0,         0.0,         0.0,         0.0,
      0.0,        3.84009e-2,  3.96733e-2,  0.0,        0.0,        0.0,         0.0,         0.0,         0.0,
      0.0,        0.0,         5.05494e-2,  7.39617e-2, 1.92200e-2, -8.46151e-3, -1.34244e-2, 1.96338e-2,  1.50421,
      1.88368e1,  0.0,         0.0,         -5.13114e1, 0.0,        0.0,         0.0,         0.0,         0.0,
      5.11923e-2, 3.61225e-2,  0.0,         0.0,        0.0,        0.0,         0.0,         0.0,         0.0,
      2.0 }
};

// Constants

enum TemperatureType { EXOSPHERIC = 0, ALTITUDE = 1 };

// EARTH GEOPHYSICAL CONSTANTS

/** Reference latitude (°). */
static const Angle LAT_REF = 45.0 * deg;

/** Reference gravity on Earth surface at reference latitude (cm/s2). */
static const Acceleration G_REF = 980.616 * cm / (s * s);

// CHEMICAL CONSTANTS

/** Gas constant (inverse of). */
static const auto R_GAS = 831.4 * J / (mol * K);

/** Hydrogen atomic mass. */
static const AtomicMass H_MASS = 1.0 * u;

/** Helium atomic mass. */
static const AtomicMass HE_MASS = 4.0 * u;

/** Nitrogen atomic mass. */
static const AtomicMass N_MASS = 14.0 * u;

/** N2 molecular mass. */
static const AtomicMass N2_MASS = 2.0 * N_MASS;

/** Oxygen atomic mass. */
static const AtomicMass O_MASS = 16.0 * u;

/** O2 molecular mass. */
static const AtomicMass O2_MASS = 2.0 * O_MASS;

/** Argon atomic mass. */
static const AtomicMass AR_MASS = 40.0 * u;

// NRL MSISE 2000 SPECIFIC CONSTANTS

/** Reference average flux. */
static const SolarFlux FLUX_REF = 150.0;

/** Array of altitudes #1. */
static const std::array<Distance, 5> ZN1 = { 123.435 * km, 110.0 * km, 100.0 * km, 90.0 * km, 72.5 * km };

/** Array of altitudes #2. */
static const std::array<Distance, 4> ZN2 = { 72.5 * km, 55.0 * km, 45.0 * km, 32.5 * km };

/** Array of altitudes #3. */
static const std::array<Distance, 5> ZN3 = { 32.5 * km, 20.0 * km, 15.0 * km, 10.0 * km, 0.0 * km };

/** Mix altitude (km). */
static const Distance ZMIX = 62.5 * km;

/**  NRLMSISE-00 data: MIDDLE ATMOSPHERE AVERAGES pavgm[10]. */
static const std::array<quantity, 10> PAVGM = { 2.61e2, 2.64e2,   2.29e2,   2.17e2, 2.17e2,
                                                2.23e2, 2.8676e2, -2.93940, 2.50,   0.0 };

/** NRLMSISE-00 minimum temperature, used in many cases in density computation. */
static const Temperature MIN_TEMP = 50.0 * K;

/** Switches for main effects. */
enum Option {
    F107_EFFECT_ON_MEAN                               = 0,
    INDEPENDENT_OF_TIME                               = 1,
    SYMMETRICAL_ANNUAL                                = 2,
    SYMMETRICAL_SEMIANNUAL                            = 3,
    ASYMMETRICAL_ANNUAL                               = 4,
    ASYMMETRICAL_SEMIANNUAL                           = 5,
    DIURNAL                                           = 6,
    SEMIDIURNAL                                       = 7,
    DAILY_AP                                          = 8,
    ALL_UT_LONGITUDINAL_EFFECTS                       = 9,
    LONGITUDINAL_EFFECTS                              = 10,
    UT_AND_MIXED_UT_LONGITUDINAL_EFFECTS              = 11,
    MIXED_AP_UT_LONGITUDINAL_EFFECTS                  = 12,
    TERDIURNAL                                        = 13,
    DEPARTURES_FROM_DIFFUSIVE_EQUILIBRIUM             = 14,
    ALL_EXOSPHERIC_TEMPERATURE_VARIATIONS             = 15,
    ALL_VARIATIONS_FROM_120KM_TEMPERATURE_TLB         = 16,
    ALL_LOWER_THERMOSPHERE_TEMPERATURE_TN1_VARIATIONS = 17,
    ALL_120KM_GRADIENT_S_VARIATIONS                   = 18,
    ALL_UPPER_STRATOSPHERE_TEMPERATURE_TN2_VARIATIONS = 19,
    ALL_VARIATIONS_FROM_120KM_VALUES_ZLB              = 20,
    ALL_LOWER_MESOSPHERE_TEMPERATURE_TN3_VARIATIONS   = 21,
    TURBOPAUSE_SCALE_HEIGHT_VARIATIONS                = 22
};

struct Switch {
    bool mainEffect  = true;
    bool crossEffect = true;
    bool fullAp      = true;
};

std::unordered_map<Option, Switch> options{ { F107_EFFECT_ON_MEAN, Switch() },
                                            { INDEPENDENT_OF_TIME, Switch() },
                                            { SYMMETRICAL_ANNUAL, Switch() },
                                            { SYMMETRICAL_SEMIANNUAL, Switch() },
                                            { ASYMMETRICAL_ANNUAL, Switch() },
                                            { ASYMMETRICAL_SEMIANNUAL, Switch() },
                                            { DIURNAL, Switch() },
                                            { SEMIDIURNAL, Switch() },
                                            { DAILY_AP, Switch() },
                                            { ALL_UT_LONGITUDINAL_EFFECTS, Switch() },
                                            { LONGITUDINAL_EFFECTS, Switch() },
                                            { UT_AND_MIXED_UT_LONGITUDINAL_EFFECTS, Switch() },
                                            { MIXED_AP_UT_LONGITUDINAL_EFFECTS, Switch() },
                                            { TERDIURNAL, Switch() },
                                            { DEPARTURES_FROM_DIFFUSIVE_EQUILIBRIUM, Switch() },
                                            { ALL_EXOSPHERIC_TEMPERATURE_VARIATIONS, Switch() },
                                            { ALL_VARIATIONS_FROM_120KM_TEMPERATURE_TLB, Switch() },
                                            { ALL_LOWER_THERMOSPHERE_TEMPERATURE_TN1_VARIATIONS, Switch() },
                                            { ALL_120KM_GRADIENT_S_VARIATIONS, Switch() },
                                            { ALL_UPPER_STRATOSPHERE_TEMPERATURE_TN2_VARIATIONS, Switch() },
                                            { ALL_VARIATIONS_FROM_120KM_VALUES_ZLB, Switch() },
                                            { ALL_LOWER_MESOSPHERE_TEMPERATURE_TN3_VARIATIONS, Switch() },
                                            { TURBOPAUSE_SCALE_HEIGHT_VARIATIONS, Switch() } };


Density find_atmospheric_density(const State& state)
{
    // check if data are available :
    const Date& date = state.get_epoch();
    if (date < inputParams.getMinDate() || date > inputParams.getMaxDate()) {
        throw std::out_of_range("Date is out of range for NRLMSISE-00 model: " + date.toString());
    }

    // compute day number in current year and the seconds within the day
    const int doy  = date.day_of_year();
    const Time sec = date.seconds_in_local_day();

    // compute geodetic position
    const auto& rEcef          = state.get_position_in_frame<frames::earth::earth_fixed>();
    const auto [lat, lon, alt] = convert_body_fixed_to_geodetic(rEcef);

    // compute local solar time
    const Time lst = calculate_local_solar_time(state);

    // get solar activity data and compute
    const Output output(
        doy, sec, lat, lon, lst, inputParams.get_average_flux(date), inputParams.get_daily_flux(date), inputParams.get_ap(date)
    );
    output.gtd7d(alt);

    // return the local density
    return output.get_density(TOTAL_MASS);
}

Time calculate_local_solar_time(const State& state)
{
    const Date& date     = state.get_epoch();
    const auto& position = state.get_position();

    const RadiusVector<frames::solar_system_barycenter::icrf> sun2Earth = get_position_at(date);
    const Direction<frames::earth::icrf> sunDirection = -sun2Earth.direction().force_frame_conversion<frames::earth::icrf>();

    const Angle lst =
        std::numbers::pi * rad + atan2(
                                     sunDirection.get_x() * position.get_y() - sunDirection.get_y() * position.get_x(),
                                     sunDirection.get_x() * position.get_x() + sunDirection.get_y() * position.get_y()
                                 );
    return lst * 12.0 / std::numbers::pi * h / rad;
}


/**
 * This class is a placeholder for the computed densities and temperatures.
 * <p>
 * Densities are provided as an array d such as:
 * <ul>
 * <li>d[0] = He number density (1/m³)</li>
 * <li>d[1] = O number density (1/m³)</li>
 * <li>d[2] = N2 number density (1/m³)</li>
 * <li>d[3] = O2 number density (1/m³)</li>
 * <li>d[4] = Ar number density (1/m³)</li>
 * <li>d[5] = total mass density (kg/m³) (*)</li>
 * <li>d[6] = H number density (1/m³)</li>
 * <li>d[7] = N number density (1/m³)</li>
 * <li>d[8] = anomalous oxygen number density (1/m³)
 * </ul>
 * Total mass density, d[5], is NOT the same for methods gtd7 and gtd7d:
 * <ul>
 * <li>For gtd7: d[5] is the sum of the mass densities of the species
 * He, O, N2, O2, Ar, H and N but does NOT include anomalous oxygen.</li>
 * <li>For gtd7d: d[5] is the "effective total mass density for drag" and is the sum
 * of the mass densities of all species in this model, INCLUDING anomalous oxygen.</li>
 * </ul>
 * O, H, and N are set to zero below 72.5 km.
 * </p>
 * <p>
 * Temperatures are provided as an array t such as:
 * <ul>
 * <li>t[0] = exospheric temperature (K)</li>
 * <li>t[1] = temperature at altitude (K)</li>
 * </ul>
 * t[0] is set to global average for altitudes below 120 km.<br>
 * The 120 km gradient is left at global average value for altitudes below 72 km.
 * </p>
 */
class Output {

    /** Day of year (from 1 to 365 or 366). */
    const int doy;

    /** Seconds in day (UT scale). */
    const Time sec;

    /** Geodetic latitude (°). */
    const Angle lat;

    /** Geodetic longitude (°). */
    const Angle lon;

    /** Local apparent solar time (hours). */
    const Time hl;

    /** 81 day average of F10.7 flux (centered on day). */
    const SolarFlux f107a;

    /** Daily F10.7 flux for previous day. */
    const SolarFlux f107;

    /** Array containing:
     *  <ul>
     *  <li>0: daily Ap</li>
     *  <li>1: 3 hr ap index for current time</li>
     *  <li>2: 3 hr ap index for 3 hrs before current time</li>
     *  <li>3: 3 hr ap index for 6 hrs before current time</li>
     *  <li>4: 3 hr ap index for FOR 9 hrs before current time</li>
     *  <li>5: average of eight 3 hr ap indices from 12 to 33 hrs prior to current time</li>
     *  <li>6: average of eight 3 hr ap indices from 36 to 57 hrs prior to current time</li>
     *  </ul>. */
    const std::array<Unitless, 7> ap;

    /** Gravity at latitude (cm/s2). */
    Acceleration glat;

    /** Effective Earth radius at latitude (km). */
    Distance rlat;

    /** N2 mixed density at alt. */
    NumberDensity n2MixedNumberDensity;

    /** Legendre polynomials. */
    const std::array<std::array<Unitless, 8>, 4> legendrePolynomials;

    /** Cosinus of local solar time. */
    const Unitless ctloc;
    /** Sinus of local solar time. */
    const Unitless stloc;
    /** Square of ctloc. */
    const Unitless c2tloc;
    /** Square of stloc. */
    const Unitless s2tloc;
    /** Cube of ctloc. */
    const Unitless c3tloc;
    /** Cube of stloc. */
    const Unitless s3tloc;

    /** Magnetic activity based on daily ap. */
    quantity apdf;

    /** Magnetic activity based on daily ap. */
    quantity apt;

    /** Temperature at nodes for ZN1 scale. */
    const std::array<Temperature, ZN1.size()> mesoTn1;

    /** Temperature at nodes for ZN2 scale. */
    const std::array<Temperature, ZN2.size()> mesoTn2;

    /** Temperature at nodes for ZN3 scale. */
    const std::array<Temperature, ZN3.size()> mesoTn3;

    /** Temperature gradients at end nodes for ZN1 scale. */
    const std::array<Temperature, 2> mesoTgn1;

    /** Temperature gradients at end nodes for ZN2 scale. */
    const std::array<Temperature, 2> mesoTgn2;

    /** Temperature gradients at end nodes for ZN3 scale. */
    const std::array<Temperature, 2> mesoTgn3;

    /** Densities. */
    const std::array<NumberDensity, 9> densities;

    /** Temperatures. */
    const std::array<Temperature, 2> temperatures;

    /** Simple constructor.
     *  @param doy day of year (from 1 to 365 or 366)
     *  @param sec seconds in day (UT scale)
     *  @param lat geodetic latitude (°)
     *  @param lon geodetic longitude (°)
     *  @param hl local apparent solar time (hours)
     *  @param f107a 81 day average of F10.7 flux (centered on day)
     *  @param f107 daily F10.7 flux for previous day
     *  @param ap array containing:
     *  <ul>
     *  <li>0: daily Ap</li>
     *  <li>1: 3 hr ap index for current time</li>
     *  <li>2: 3 hr ap index for 3 hrs before current time</li>
     *  <li>3: 3 hr ap index for 6 hrs before current time</li>
     *  <li>4: 3 hr ap index for FOR 9 hrs before current time</li>
     *  <li>5: average of eight 3 hr ap indices from 12 to 33 hrs prior to current time</li>
     *  <li>6: average of eight 3 hr ap indices from 36 to 57 hrs prior to current time</li>
     *  </ul>
     */
    Output(
        const int doy,
        const Time sec,
        const Angle lat,
        const Angle lon,
        const Time hl,
        const SolarFlux f107a,
        const SolarFlux f107,
        const std::array<Unitless, 7>& ap
    ) :
        doy(doy),
        sec(sec),
        lat(lat),
        lon(lon),
        hl(hl),
        f107a(f107a),
        f107(f107),
        ap(ap)
    {
        // Calculates latitude variable gravity and effective radius
        const Angle xlat  = (!options[INDEPENDENT_OF_TIME].mainEffect) ? LAT_REF : lat;
        const Unitless c2 = cos(2.0 * xlat * rad);
        glat              = G_REF * (1.0 - 0.0026373 * c2);
        rlat              = 2.0 * glat * cm / (s * s) / (3.085462e-6 + 2.27e-9 * c2 * 1.0e-5 * km);

        // Calculate legendre polynomials (lat already in radians)
        const Unitless sinLat = sin(lat); // Orekit has c = sin(lat) and s = cos(lat). Is this an error?
        const Unitless cosLat = cos(lat); // I've kept the equations below consistent with Orekit but they might be inverted.

        legendrePolynomials[0][1] = sinLat;
        legendrePolynomials[0][2] = (3.0 * sinLat * legendrePolynomials[0][1] - 1.0) / 2.0;
        legendrePolynomials[0][3] = (5.0 * sinLat * legendrePolynomials[0][2] - 2.0 * legendrePolynomials[0][1]) / 3.0;
        legendrePolynomials[0][4] = (7.0 * sinLat * legendrePolynomials[0][3] - 3.0 * legendrePolynomials[0][2]) / 4.0;
        legendrePolynomials[0][5] = (9.0 * sinLat * legendrePolynomials[0][4] - 4.0 * legendrePolynomials[0][3]) / 5.0;
        legendrePolynomials[0][6] = (11.0 * sinLat * legendrePolynomials[0][5] - 5.0 * legendrePolynomials[0][4]) / 6.0;

        legendrePolynomials[1][1] = cosLat;
        legendrePolynomials[1][2] = 3.0 * sinLat * legendrePolynomials[1][1];
        legendrePolynomials[1][3] = (5.0 * sinLat * legendrePolynomials[1][2] - 3.0 * legendrePolynomials[1][1]) / 2.0;
        legendrePolynomials[1][4] = (7.0 * sinLat * legendrePolynomials[1][3] - 4.0 * legendrePolynomials[1][2]) / 3.0;
        legendrePolynomials[1][5] = (9.0 * sinLat * legendrePolynomials[1][4] - 5.0 * legendrePolynomials[1][3]) / 4.0;
        legendrePolynomials[1][6] = (11.0 * sinLat * legendrePolynomials[1][5] - 6.0 * legendrePolynomials[1][4]) / 5.0;

        legendrePolynomials[2][2] = 3.0 * cosLat * legendrePolynomials[1][1];
        legendrePolynomials[2][3] = 5.0 * sinLat * legendrePolynomials[2][2];
        legendrePolynomials[2][4] = (7.0 * sinLat * legendrePolynomials[2][3] - 5.0 * legendrePolynomials[2][2]) / 2.0;
        legendrePolynomials[2][5] = (9.0 * sinLat * legendrePolynomials[2][4] - 6.0 * legendrePolynomials[2][3]) / 3.0;
        legendrePolynomials[2][6] = (11.0 * sinLat * legendrePolynomials[2][5] - 7.0 * legendrePolynomials[2][4]) / 4.0;
        legendrePolynomials[2][7] = (13.0 * sinLat * legendrePolynomials[2][6] - 8.0 * legendrePolynomials[2][5]) / 5.0;

        legendrePolynomials[3][3] = 5.0 * cosLat * legendrePolynomials[2][2];
        legendrePolynomials[3][4] = 7.0 * sinLat * legendrePolynomials[3][3];
        legendrePolynomials[3][5] = (9.0 * sinLat * legendrePolynomials[3][4] - 7.0 * legendrePolynomials[3][3]) / 2.0;
        legendrePolynomials[3][6] = (11.0 * sinLat * legendrePolynomials[3][5] - 8.0 * legendrePolynomials[3][4]) / 3.0;

        // Calculate additional data
        if (options[DIURNAL].mainEffect || options[SEMIDIURNAL].mainEffect || options[TERDIURNAL].mainEffect) {
            const Angle tloc = HOUR_TO_RAD * hl;
            stloc            = sin(tloc);
            ctloc            = cos(tloc);
            s2tloc           = sin(2.0 * tloc);
            c2tloc           = cos(2.0 * tloc);
            s3tloc           = sin(3.0 * tloc);
            c3tloc           = cos(3.0 * tloc);
        }
        else {
            stloc  = 0.0 * one;
            ctloc  = 0.0 * one;
            s2tloc = 0.0 * one;
            c2tloc = 0.0 * one;
            s3tloc = 0.0 * one;
            c3tloc = 0.0 * one;
        }
    }

    /** Calculate temperatures and densities not including anomalous oxygen.
     *  <p>
     *  This method is the thermospheric portion of NRLMSISE-00 for alt > 72.5 km.
     *  </p>
     *  <p>NOTES ON INPUT VARIABLES:<br>
     *  Seconds, Local Time, and Longitude are used independently in the
     *  model and are not of equal importance for every situation.<br>
     *  For the most physically realistic calculation these three
     *  variables should be consistent (lst=sec/3600 + lon/15).<br>
     *  The Equation of Time departures from the above formula
     *  for apparent local time can be included if available but
     *  are of minor importance.<br><br>
     *
     *  f107 and f107A values used to generate the model correspond
     *  to the 10.7 cm radio flux at the actual distance of the Earth
     *  from the Sun rather than the radio flux at 1 AU. The following
     *  site provides both classes of values:<br>
     *  ftp://ftp.ngdc.noaa.gov/STP/SOLAR_DATA/SOLAR_RADIO/FLUX/<br><br>
     *
     *  f107, f107A, and ap effects are neither large nor well established below 80 km
     *  and these parameters should be set to 150., 150., and 4. respectively.
     *  </p>
     *  @param alt altitude (km)
     */
    void gts7(const Distance alt)
    {

        // Thermal diffusion coefficients for species
        const std::array<Unitless, 9> thermalDiffusionCoefficients = { -0.38, 0.0, 0.0, 0.0, 0.17, 0.0, -0.38, 0.0, 0.0 };

        // Altitude limits for net density computation for species
        const std::array<Distance, 8> altl = { 200.0 * km, 300.0 * km, 160.0 * km, 250.0 * km,
                                               240.0 * km, 450.0 * km, 320.0 * km, 450.0 * km };

        /**** Exospheric temperature ****/
        const Temperature tempInf = PTM.Tinf * PT[0];

        // Tinf variations not important below ZA or ZN[0]
        if (alt > ZN1[0]) { tempInf *= 1.0 + options[ALL_EXOSPHERIC_TEMPERATURE_VARIATIONS].mainEffect * globe7(PT); }
        set_temperature(EXOSPHERIC, tempInf);

        // Gradient variations not important below ZN[4]
        quantity g0 = PTM.S0 * PS[0];
        if (alt > ZN1[4]) { g0 *= 1.0 + options[ALL_120KM_GRADIENT_S_VARIATIONS].mainEffect * globe7(PS); }

        // Temperature at lower boundary
        const Temperature tempLowerBound =
            PTM.Tlb0 * PD[3][0] * (1.0 + options[ALL_VARIATIONS_FROM_120KM_TEMPERATURE_TLB].mainEffect * globe7(PD[3]));

        // Slope
        const quantity s = g0 / (tempInf - tempLowerBound);

        // Lower thermosphere temp variations not significant for density above 300 km
        mesoTn1[1]  = PTM.TN11 * PTL[0][0];
        mesoTn1[2]  = PTM.TN12 * PTL[1][0];
        mesoTn1[3]  = PTM.TN13 * PTL[2][0];
        mesoTn1[4]  = PTM.TN14 * PTL[3][0];
        mesoTgn1[1] = PTM.Tgrad * PMA[8][0];
        if (alt < 300.0) {
            const quantity r = PTM.TN14 * PTL[3][0];
            mesoTn1[1] /= 1.0 - options[ALL_LOWER_THERMOSPHERE_TEMPERATURE_TN1_VARIATIONS].mainEffect * glob7s(PTL[0]);
            mesoTn1[2] /= 1.0 - options[ALL_LOWER_THERMOSPHERE_TEMPERATURE_TN1_VARIATIONS].mainEffect * glob7s(PTL[1]);
            mesoTn1[3] /= 1.0 - options[ALL_LOWER_THERMOSPHERE_TEMPERATURE_TN1_VARIATIONS].mainEffect * glob7s(PTL[2]);
            mesoTn1[4] /= 1.0 - options[ALL_LOWER_THERMOSPHERE_TEMPERATURE_TN1_VARIATIONS].mainEffect *
                                    options[ALL_UPPER_STRATOSPHERE_TEMPERATURE_TN2_VARIATIONS].mainEffect * glob7s(PTL[3]);
            mesoTgn1[1] *= 1.0 + options[ALL_LOWER_THERMOSPHERE_TEMPERATURE_TN1_VARIATIONS].mainEffect *
                                     options[ALL_UPPER_STRATOSPHERE_TEMPERATURE_TN2_VARIATIONS].mainEffect * glob7s(PMA[8]);
            mesoTgn1[1] *= mesoTn1[4] * mesoTn1[4] / (r * r);
        }

        /**** Temperature at altitude ****/
        set_temperature(ALTITUDE, calculate_density_temperature_profile_new(alt, 1.0, tempInf, tempLowerBound, 0.0, 0.0, PTM.Zlb, s));

        /**** N2 density ****/
        /*   Density variation factor at Zlb */
        const quantity g28 = options[ALL_VARIATIONS_FROM_120KM_VALUES_ZLB].mainEffect * globe7(PD[2]);
        /* Diffusive density at Zlb */
        const quantity db28 = SpeciesModelData[MOLECULAR_NITROGEN].nRef * exp(g28) * PD[2][0];
        /* Diffusive density at Alt */
        quantity diffusiveDensity = calculate_density_temperature_profile_new(
            alt, db28, tempInf, tempLowerBound, N2_MASS, thermalDiffusionCoefficients[2], PTM.Zlb, s
        );
        set_density(MOLECULAR_NITROGEN, diffusiveDensity);
        // Variation of turbopause height
        const quantity zhf = PDL[1][24] * (1.0 + options[ASYMMETRICAL_ANNUAL] * PDL[0][24].mainEffect * sin(lat * rad) *
                                                     cos(DAY_TO_RAD * rad / d) * (doy - PT[13]));
        /* Turbopause */
        const quantity zh28  = SpeciesModelData[MOLECULAR_NITROGEN].zh * zhf;
        const quantity zhm28 = SpeciesModelData[MOLECULAR_NITROGEN].c3 * PDL[1][5];
        /* Mixed density at Zlb */
        const quantity b28 = calculate_density_temperature_profile_new(
            zh28, db28, tempInf, tempLowerBound, N2_MASS - XMM, thermalDiffusionCoefficients[2] - 1.0, PTM.Zlb, s
        );
        if (options[DEPARTURES_FROM_DIFFUSIVE_EQUILIBRIUM].mainEffect && alt <= altl[2]) {
            /*  Mixed density at Alt */
            n2MixedNumberDensity = calculate_density_temperature_profile_new(
                alt, b28, tempInf, tempLowerBound, XMM, thermalDiffusionCoefficients[2], PTM.Zlb, s
            );
            /*  Net density at Alt */
            set_density(MOLECULAR_NITROGEN, calculate_turbopause_correction(diffusiveDensity, n2MixedNumberDensity, zhm28, XMM, N2_MASS));
        }

        /**** He density ****/
        /*   Density variation factor at Zlb */
        const quantity g4 = options[ALL_VARIATIONS_FROM_120KM_VALUES_ZLB].mainEffect * globe7(PD[0]);
        /*  Diffusive density at Zlb */
        const quantity db04 = SpeciesModelData[HELIUM].nRef * exp(g4) * PD[0][0];
        /*  Diffusive density at Alt */
        diffusiveDensity = calculate_density_temperature_profile_new(
            alt, db04, tempInf, tempLowerBound, HE_MASS, thermalDiffusionCoefficients[0], PTM.Zlb, s
        );
        set_density(HELIUM, diffusiveDensity);
        if (options[DEPARTURES_FROM_DIFFUSIVE_EQUILIBRIUM].mainEffect && alt < altl[0]) {
            /*  Turbopause */
            const quantity zh04 = SpeciesModelData[HELIUM].zh;
            /*  Mixed density at Zlb */
            const quantity b04 = calculate_density_temperature_profile_new(
                zh04, db04, tempInf, tempLowerBound, HE_MASS - XMM, thermalDiffusionCoefficients[0] - 1., PTM.Zlb, s
            );
            /*  Mixed density at Alt */
            const quantity dm04 =
                calculate_density_temperature_profile_new(alt, b04, tempInf, tempLowerBound, XMM, 0., PTM.Zlb, s);
            const quantity zhm04 = zhm28;
            /*  Net density at Alt */
            diffusiveDensity = calculate_turbopause_correction(diffusiveDensity, dm04, zhm04, XMM, HE_MASS);
            /*  Correction to specified mixing ratio at ground */
            const quantity rl   = log(b28 * SpeciesModelData[HELIUM].mixRatio / b04);
            const quantity zc04 = SpeciesModelData[HELIUM].za * PDL[1][0];
            const quantity hc04 = SpeciesModelData[HELIUM].ha * PDL[1][1];
            /*  Net density corrected at Alt */
            set_density(HELIUM, diffusiveDensity * calculate_dissociation_correction(alt, rl, hc04, zc04));
        }

        /**** O density ****/
        /* Density variation factor at Zlb */
        const quantity g16 = options[ALL_VARIATIONS_FROM_120KM_VALUES_ZLB].mainEffect * globe7(PD[1]);
        /* Diffusive density at Zlb */
        const quantity db16 = SpeciesModelData[ATOMIC_OXYGEN].nRef * exp(g16) * PD[1][0];
        /* Diffusive density at Alt */
        diffusiveDensity = calculate_density_temperature_profile_new(
            alt, db16, tempInf, tempLowerBound, O_MASS, thermalDiffusionCoefficients[1], PTM.Zlb, s
        );
        set_density(ATOMIC_OXYGEN, diffusiveDensity);
        if (options[DEPARTURES_FROM_DIFFUSIVE_EQUILIBRIUM].mainEffect && alt < altl[1]) {
            /* Turbopause */
            const quantity zh16 = SpeciesModelData[ATOMIC_OXYGEN].zh;
            /* Mixed density at Zlb */
            const quantity b16 = calculate_density_temperature_profile_new(
                zh16, db16, tempInf, tempLowerBound, O_MASS - XMM, thermalDiffusionCoefficients[1] - 1.0, PTM.Zlb, s
            );
            /* Mixed density at Alt */
            const quantity dm16 =
                calculate_density_temperature_profile_new(alt, b16, tempInf, tempLowerBound, XMM, 0., PTM.Zlb, s);
            const quantity zhm16 = zhm28;
            /* Net density at Alt */
            diffusiveDensity  = calculate_turbopause_correction(diffusiveDensity, dm16, zhm16, XMM, O_MASS);
            const quantity rl = SpeciesModelData[ATOMIC_OXYGEN].mixRatio * PDL[1][16] *
                                (1.0 + options[F107_EFFECT_ON_MEAN].mainEffect * PDL[0][23] * (f107a - FLUX_REF));
            const quantity hc16  = SpeciesModelData[ATOMIC_OXYGEN].ha * PDL[1][3];
            const quantity zc16  = SpeciesModelData[ATOMIC_OXYGEN].za * PDL[1][2];
            const quantity hc216 = SpeciesModelData[ATOMIC_OXYGEN].ha * PDL[1][4];
            diffusiveDensity *= calculate_oxygen_dissociation_correction(alt, rl, hc16, zc16, hc216);
            /* Chemistry correction */
            const quantity hcc16 = SpeciesModelData[ATOMIC_OXYGEN].hb * PDL[1][13];
            const quantity zcc16 = SpeciesModelData[ATOMIC_OXYGEN].zb * PDL[1][12];
            const quantity rc16  = SpeciesModelData[ATOMIC_OXYGEN].c3 * PDL[1][14];
            /* Net density corrected at Alt */
            set_density(ATOMIC_OXYGEN, diffusiveDensity * calculate_dissociation_correction(alt, rc16, hcc16, zcc16));
        }

        /**** O2 density ****/
        /* Density variation factor at Zlb */
        const quantity g32 = options[ALL_VARIATIONS_FROM_120KM_VALUES_ZLB].mainEffect * globe7(PD[4]);
        /* Diffusive density at Zlb */
        const quantity db32 = SpeciesModelData[MOLECULAR_OXYGEN].nRef * exp(g32) * PD[4][0];
        /* Diffusive density at Alt */
        diffusiveDensity = calculate_density_temperature_profile_new(
            alt, db32, tempInf, tempLowerBound, O2_MASS, thermalDiffusionCoefficients[3], PTM.Zlb, s
        );
        set_density(MOLECULAR_OXYGEN, diffusiveDensity);
        if (options[DEPARTURES_FROM_DIFFUSIVE_EQUILIBRIUM].mainEffect) {
            if (alt <= altl[3]) {
                /* Turbopause */
                const quantity zh32 = SpeciesModelData[MOLECULAR_OXYGEN].zh;
                /* Mixed density at Zlb */
                const quantity b32 = calculate_density_temperature_profile_new(
                    zh32, db32, tempInf, tempLowerBound, O2_MASS - XMM, thermalDiffusionCoefficients[3] - 1., PTM.Zlb, s
                );
                /* Mixed density at Alt */
                const quantity dm32 =
                    calculate_density_temperature_profile_new(alt, b32, tempInf, tempLowerBound, XMM, 0., PTM.Zlb, s);
                const quantity zhm32 = zhm28;
                /* Net density at Alt */
                diffusiveDensity = calculate_turbopause_correction(diffusiveDensity, dm32, zhm32, XMM, O2_MASS);
                /* Correction to specified mixing ratio at ground */
                const quantity rl   = log(b28 * SpeciesModelData[MOLECULAR_OXYGEN].mixRatio / b32);
                const quantity hc32 = SpeciesModelData[MOLECULAR_OXYGEN].ha * PDL[1][7];
                const quantity zc32 = SpeciesModelData[MOLECULAR_OXYGEN].za * PDL[1][6];
                diffusiveDensity *= calculate_dissociation_correction(alt, rl, hc32, zc32);
            }
            /* Correction for general departure from diffusive equilibrium above Zlb */
            const quantity hcc32  = SpeciesModelData[MOLECULAR_OXYGEN].hb * PDL[1][22];
            const quantity hcc232 = SpeciesModelData[MOLECULAR_OXYGEN].hb * PDL[0][22];
            const quantity zcc32  = SpeciesModelData[MOLECULAR_OXYGEN].zb * PDL[1][21];
            const quantity rc32   = SpeciesModelData[MOLECULAR_OXYGEN].c3 * PDL[1][23] *
                                  (1. + options[F107_EFFECT_ON_MEAN].mainEffect * PDL[0][23] * (f107a - FLUX_REF));
            /* Net density corrected at Alt */
            set_density(MOLECULAR_OXYGEN, diffusiveDensity * calculate_oxygen_dissociation_correction(alt, rc32, hcc32, zcc32, hcc232));
        }

        /**** Ar density ****/
        /* Density variation factor at Zlb */
        const quantity g40 = options[ALL_VARIATIONS_FROM_120KM_VALUES_ZLB].mainEffect * globe7(PD[5]);
        /* Diffusive density at Zlb */
        const quantity db40 = SpeciesModelData[ARGON].nRef * exp(g40) * PD[5][0];
        /* Diffusive density at Alt */
        diffusiveDensity = calculate_density_temperature_profile_new(
            alt, db40, tempInf, tempLowerBound, AR_MASS, thermalDiffusionCoefficients[4], PTM.Zlb, s
        );
        set_density(ARGON, diffusiveDensity);
        if (options[DEPARTURES_FROM_DIFFUSIVE_EQUILIBRIUM].mainEffect && alt <= altl[4]) {
            /* Turbopause */
            const quantity zh40 = SpeciesModelData[ARGON].zh;
            /* Mixed density at Zlb */
            const quantity b40 = calculate_density_temperature_profile_new(
                zh40, db40, tempInf, tempLowerBound, AR_MASS - XMM, thermalDiffusionCoefficients[4] - 1., PTM.Zlb, s
            );
            /* Mixed density at Alt */
            const quantity dm40 =
                calculate_density_temperature_profile_new(alt, b40, tempInf, tempLowerBound, XMM, 0., PTM.Zlb, s);
            const quantity zhm40 = zhm28;
            /* Net density at Alt */
            diffusiveDensity = calculate_turbopause_correction(diffusiveDensity, dm40, zhm40, XMM, AR_MASS);
            /* Correction to specified mixing ratio at ground */
            const quantity rl   = log(b28 * SpeciesModelData[ARGON].mixRatio / b40);
            const quantity hc40 = SpeciesModelData[ARGON].ha * PDL[1][9];
            const quantity zc40 = SpeciesModelData[ARGON].za * PDL[1][8];
            /* Net density corrected at Alt */
            set_density(ARGON, diffusiveDensity * calculate_dissociation_correction(alt, rl, hc40, zc40));
        }

        /**** H density ****/
        /* Density variation factor at Zlb */
        const quantity g1 = options[ALL_VARIATIONS_FROM_120KM_VALUES_ZLB].mainEffect * globe7(PD[6]);
        /* Diffusive density at Zlb */
        const quantity db01 = SpeciesModelData[HYDROGEN].nRef * exp(g1) * PD[6][0];
        /* Diffusive density at Alt */
        diffusiveDensity = calculate_density_temperature_profile_new(
            alt, db01, tempInf, tempLowerBound, H_MASS, thermalDiffusionCoefficients[6], PTM.Zlb, s
        );
        set_density(HYDROGEN, diffusiveDensity);
        if (options[DEPARTURES_FROM_DIFFUSIVE_EQUILIBRIUM].mainEffect && alt <= altl[6]) {
            /* Turbopause */
            const quantity zh01 = SpeciesModelData[HYDROGEN].zh;
            /* Mixed density at Zlb */
            const quantity b01 = calculate_density_temperature_profile_new(
                zh01, db01, tempInf, tempLowerBound, H_MASS - XMM, thermalDiffusionCoefficients[6] - 1., PTM.Zlb, s
            );
            /* Mixed density at Alt */
            const quantity dm01 =
                calculate_density_temperature_profile_new(alt, b01, tempInf, tempLowerBound, XMM, 0., PTM.Zlb, s);
            const quantity zhm01 = zhm28;
            /* Net density at Alt */
            diffusiveDensity = calculate_turbopause_correction(diffusiveDensity, dm01, zhm01, XMM, H_MASS);
            /* Correction to specified mixing ratio at ground */
            const quantity rl   = log(b28 * SpeciesModelData[HYDROGEN].mixRatio * sqrt(PDL[1][17] * PDL[1][17]) / b01);
            const quantity hc01 = SpeciesModelData[HYDROGEN].ha * PDL[1][11];
            const quantity zc01 = SpeciesModelData[HYDROGEN].za * PDL[1][10];
            diffusiveDensity *= calculate_dissociation_correction(alt, rl, hc01, zc01);
            /* Chemistry correction */
            const quantity hcc01 = SpeciesModelData[HYDROGEN].hb * PDL[1][19];
            const quantity zcc01 = SpeciesModelData[HYDROGEN].zb * PDL[1][18];
            const quantity rc01  = SpeciesModelData[HYDROGEN].c3 * PDL[1][20];
            /* Net density corrected at Alt */
            set_density(HYDROGEN, diffusiveDensity * calculate_dissociation_correction(alt, rc01, hcc01, zcc01));
        }

        /**** N density ****/
        /* Density variation factor at Zlb */
        const quantity g14 = options[ALL_VARIATIONS_FROM_120KM_VALUES_ZLB].mainEffect * globe7(PD[7]);
        /* Diffusive density at Zlb */
        const quantity db14 = SpeciesModelData[ATOMIC_NITROGEN].nRef * exp(g14) * PD[7][0];
        /* Diffusive density at Alt */
        diffusiveDensity = calculate_density_temperature_profile_new(
            alt, db14, tempInf, tempLowerBound, N_MASS, thermalDiffusionCoefficients[7], PTM.Zlb, s
        );
        set_density(ATOMIC_NITROGEN, diffusiveDensity);
        if (options[DEPARTURES_FROM_DIFFUSIVE_EQUILIBRIUM].mainEffect && alt <= altl[7]) {
            /* Turbopause */
            const quantity zh14 = SpeciesModelData[ATOMIC_NITROGEN].zh;
            /* Mixed density at Zlb */
            const quantity b14 = calculate_density_temperature_profile_new(
                zh14, db14, tempInf, tempLowerBound, N_MASS - XMM, thermalDiffusionCoefficients[7] - 1., PTM.Zlb, s
            );
            /* Mixed density at Alt */
            const quantity dm14 =
                calculate_density_temperature_profile_new(alt, b14, tempInf, tempLowerBound, XMM, 0., PTM.Zlb, s);
            const quantity zhm14 = zhm28;
            /* Net density at Alt */
            diffusiveDensity = calculate_turbopause_correction(diffusiveDensity, dm14, zhm14, XMM, N_MASS);
            /* Correction to specified mixing ratio at ground */
            const quantity rl   = log(b28 * SpeciesModelData[ATOMIC_NITROGEN].mixRatio * PDL[0][2] / b14);
            const quantity hc14 = SpeciesModelData[ATOMIC_NITROGEN].ha * PDL[0][1];
            const quantity zc14 = SpeciesModelData[ATOMIC_NITROGEN].za * PDL[0][0];
            diffusiveDensity *= calculate_dissociation_correction(alt, rl, hc14, zc14);
            /* Chemistry correction */
            const quantity hcc14 = SpeciesModelData[ATOMIC_NITROGEN].hb * PDL[0][4];
            const quantity zcc14 = SpeciesModelData[ATOMIC_NITROGEN].zb * PDL[0][3];
            const quantity rc14  = SpeciesModelData[ATOMIC_NITROGEN].c3 * PDL[0][5];
            /* Net density corrected at Alt */
            set_density(ATOMIC_NITROGEN, diffusiveDensity * calculate_dissociation_correction(alt, rc14, hcc14, zcc14));
        }

        /**** Anomalous O density ****/
        const quantity g16h  = options[ALL_VARIATIONS_FROM_120KM_VALUES_ZLB].mainEffect * globe7(PD[8]);
        const quantity db16h = SpeciesModelData[ANOMALOUS_OXYGEN].nRef * exp(g16h) * PD[8][0];
        const quantity tho   = SpeciesModelData[ANOMALOUS_OXYGEN].c9 * PDL[0][6];
        diffusiveDensity =
            calculate_density_temperature_profile_new(alt, db16h, tho, tho, O_MASS, thermalDiffusionCoefficients[8], PTM.Zlb, s);
        const quantity zsht = SpeciesModelData[ANOMALOUS_OXYGEN].ha;
        const quantity zmho = SpeciesModelData[ANOMALOUS_OXYGEN].za;
        const quantity zsho = calculate_scale_height(zmho, O_MASS, tho);
        diffusiveDensity *= exp(-zsht / zsho * (exp((zmho - alt) / zsht) - 1.));
        set_density(ANOMALOUS_OXYGEN, diffusiveDensity);

        // Convert densities from cm-3 to m-3
        for (int i = 0; i < 9; i++) {
            set_density(i, get_density(i) * 1.0e6);
        }

        /**** Total mass density ****/
        const quantity tmd = HE_MASS * get_density(HELIUM) + O_MASS * get_density(ATOMIC_OXYGEN) +
                             N2_MASS * get_density(MOLECULAR_NITROGEN) + O2_MASS * get_density(MOLECULAR_OXYGEN) +
                             AR_MASS * get_density(ARGON) + H_MASS * get_density(HYDROGEN) + N_MASS * get_density(ATOMIC_NITROGEN);
        set_density(TOTAL_MASS, tmd);
    }

    /** Calculate temperatures and densities not including anomalous oxygen.
     *  <p>NOTES ON INPUT VARIABLES:<br>
     *  Seconds, Local Time, and Longitude are used independently in the
     *  model and are not of equal importance for every situation.<br>
     *  For the most physically realistic calculation these three
     *  variables should be consistent (lst=sec/3600 + lon/15).<br>
     *  The Equation of Time departures from the above formula
     *  for apparent local time can be included if available but
     *  are of minor importance.<br><br>
     *
     *  f107 and f107A values used to generate the model correspond
     *  to the 10.7 cm radio flux at the actual distance of the Earth
     *  from the Sun rather than the radio flux at 1 AU. The following
     *  site provides both classes of values:<br>
     *  ftp://ftp.ngdc.noaa.gov/STP/SOLAR_DATA/SOLAR_RADIO/FLUX/<br><br>
     *
     *  f107, f107A, and ap effects are neither large nor well established below 80 km
     *  and these parameters should be set to 150., 150., and 4. respectively.
     *  </p>
     *  @param alt altitude (km)
     */
    void gtd7(const Distance alt)
    {
        const quantity alt = alt * km;

        // Calculates for thermosphere/mesosphere (above ZN2[0])
        const Distance altt = (alt > ZN2[0]) ? alt : ZN2[0];
        gts7(altt);
        if (alt >= ZN2[0]) { return; }

        // Calculates for lower mesosphere/upper stratosphere (between ZN2[0] and ZN3[0]):
        // Temperature at nodes and gradients at end nodes
        // Inverse temperature a linear function of spherical harmonics
        const quantity r = PMA[2][0] * PAVGM[2];
        mesoTgn2[0]      = mesoTgn1[1];
        mesoTn2[0]       = mesoTn1[4];
        mesoTn2[1]       = PMA[0][0] * PAVGM[0] /
                     (1.0 - options[ALL_UPPER_STRATOSPHERE_TEMPERATURE_TN2_VARIATIONS].mainEffect * glob7s(PMA[0]));
        mesoTn2[2] = PMA[1][0] * PAVGM[1] /
                     (1.0 - options[ALL_UPPER_STRATOSPHERE_TEMPERATURE_TN2_VARIATIONS].mainEffect * glob7s(PMA[1]));
        mesoTn2[3] = PMA[2][0] * PAVGM[2] /
                     (1.0 - options[ALL_UPPER_STRATOSPHERE_TEMPERATURE_TN2_VARIATIONS].mainEffect *
                                options[ALL_LOWER_MESOSPHERE_TEMPERATURE_TN3_VARIATIONS].mainEffect * glob7s(PMA[2]));
        mesoTgn2[1] = PMA[9][0] * PAVGM[8] *
                      (1.0 + options[ALL_UPPER_STRATOSPHERE_TEMPERATURE_TN2_VARIATIONS].mainEffect *
                                 options[ALL_LOWER_MESOSPHERE_TEMPERATURE_TN3_VARIATIONS].mainEffect * glob7s(PMA[9])) *
                      mesoTn2[3] * mesoTn2[3] / (r * r);
        mesoTn3[0] = mesoTn2[3];

        // Calculates for lower stratosphere and troposphere (below ZN3[0])
        // Temperature at nodes and gradients at end nodes
        // Inverse temperature a linear function of spherical harmonics
        if (alt <= ZN3[0]) {
            const quantity q = PMA[6][0] * PAVGM[6];
            mesoTgn3[0]      = mesoTgn2[1];
            mesoTn3[1]       = PMA[3][0] * PAVGM[3] /
                         (1.0 - options[ALL_LOWER_MESOSPHERE_TEMPERATURE_TN3_VARIATIONS].mainEffect * glob7s(PMA[3]));
            mesoTn3[2] = PMA[4][0] * PAVGM[4] /
                         (1.0 - options[ALL_LOWER_MESOSPHERE_TEMPERATURE_TN3_VARIATIONS].mainEffect * glob7s(PMA[4]));
            mesoTn3[3] = PMA[5][0] * PAVGM[5] /
                         (1.0 - options[ALL_LOWER_MESOSPHERE_TEMPERATURE_TN3_VARIATIONS].mainEffect * glob7s(PMA[5]));
            mesoTn3[4] = PMA[6][0] * PAVGM[6] /
                         (1.0 - options[ALL_LOWER_MESOSPHERE_TEMPERATURE_TN3_VARIATIONS].mainEffect * glob7s(PMA[6]));
            mesoTgn3[1] = PMA[7][0] * PAVGM[7] *
                          (1.0 + options[ALL_LOWER_MESOSPHERE_TEMPERATURE_TN3_VARIATIONS].mainEffect * glob7s(PMA[7])) *
                          mesoTn3[4] * mesoTn3[4] / (q * q);
        }

        // Linear transition to full mixing below ZN2[0]
        const quantity dmc  = (alt > ZMIX) ? 1.0 - (ZN2[0] * km) - alt / (ZN2[0] * km) - ZMIX : 0.;
        const quantity dz28 = get_density(MOLECULAR_NITROGEN);

        // N2 density
        const quantity n2MixedNumberDensitym = n2MixedNumberDensity * 1.0e6;
        quantity dmr                         = dz28 / n2MixedNumberDensitym - 1.0;
        quantity dst = calculate_density_temperature_profile(alt, n2MixedNumberDensitym, XMM) * (1.0 + dmr * dmc);
        set_density(MOLECULAR_NITROGEN, dst);

        // HE density
        dmr = get_density(HELIUM) / (dz28 * SpeciesModelData[HELIUM].mixRatio) - 1.0;
        dst = get_density(MOLECULAR_NITROGEN) * SpeciesModelData[HELIUM].mixRatio * (1.0 + dmr * dmc);
        set_density(HELIUM, dst);

        // O density
        set_density(ATOMIC_OXYGEN, 0.);
        set_density(ANOMALOUS_OXYGEN, 0.);

        // O2 density
        dmr = get_density(MOLECULAR_OXYGEN) / (dz28 * SpeciesModelData[MOLECULAR_OXYGEN].mixRatio) - 1.0;
        dst = get_density(MOLECULAR_NITROGEN) * SpeciesModelData[MOLECULAR_OXYGEN].mixRatio * (1.0 + dmr * dmc);
        set_density(MOLECULAR_OXYGEN, dst);

        // AR density
        dmr = get_density(ARGON) / (dz28 * SpeciesModelData[ARGON].mixRatio) - 1.0;
        dst = get_density(MOLECULAR_NITROGEN) * SpeciesModelData[ARGON].mixRatio * (1.0 + dmr * dmc);
        set_density(ARGON, dst);

        // H density
        set_density(HYDROGEN, 0.);

        // N density
        set_density(ATOMIC_NITROGEN, 0.);

        // Total mass density
        const quantity tmd =
            AMU * (HE_MASS * get_density(HELIUM) + O_MASS * get_density(ATOMIC_OXYGEN) +
                   N2_MASS * get_density(MOLECULAR_NITROGEN) + O2_MASS * get_density(MOLECULAR_OXYGEN) +
                   AR_MASS * get_density(ARGON) + H_MASS * get_density(HYDROGEN) + N_MASS * get_density(ATOMIC_NITROGEN));
        set_density(TOTAL_MASS, tmd);

        // Temperature at altitude
        set_temperature(ALTITUDE, calculate_density_temperature_profile(alt, 1.0, 0));
    }

    /** Calculate temperatures and densities including anomalous oxygen.
     *  <p></p>
     *  <p>NOTES ON INPUT VARIABLES:<br>
     *  Seconds, Local Time, and Longitude are used independently in the
     *  model and are not of equal importance for every situation.<br>
     *  For the most physically realistic calculation these three
     *  variables should be consistent (lst=sec/3600 + lon/15).<br>
     *  The Equation of Time departures from the above formula
     *  for apparent local time can be included if available but
     *  are of minor importance.<br>
     *  <br>
     *  f107 and f107A values used to generate the model correspond
     *  to the 10.7 cm radio flux at the actual distance of the Earth
     *  from the Sun rather than the radio flux at 1 AU. The following
     *  site provides both classes of values:<br>
     *  ftp://ftp.ngdc.noaa.gov/STP/SOLAR_DATA/SOLAR_RADIO/FLUX/<br>
     *  <br>
     *  f107, f107A, and ap effects are neither large nor well established below 80 km
     *  and these parameters should be set to 150., 150., and 4. respectively.
     *  </p>
     *  @param alt altitude (km)
     */
    void gtd7d(const Distance& alt)
    {
        // Compute densities and temperatures
        gtd7(alt);

        // Update the total mass density with anomalous oxygen contribution
        const quantity dTot = get_density(TOTAL_MASS) + AMU * O_MASS * get_density(ANOMALOUS_OXYGEN);
        set_density(TOTAL_MASS, dTot);
    }

    /** Set one density.
     * @param index one of the nine elements :
     * <ul>
     * <li>{@link #HELIUM}</li>
     * <li>{@link #ATOMIC_OXYGEN}</li>
     * <li>{@link #MOLECULAR_NITROGEN}</li>
     * <li>{@link #MOLECULAR_OXYGEN}</li>
     * <li>{@link #ARGON}</li>
     * <li>{@link #TOTAL_MASS}</li>
     * <li>{@link #HYDROGEN}</li>
     * <li>{@link #ATOMIC_NITROGEN}</li>
     * <li>{@link #ATOMIC_NITROGEN}</li>
     * </ul>
     * @param d the value of density to set
     */
    void set_density(const int index, const NumberDensity d) { densities[index] = d; }

    /** Set one temperature.
     * @param index one of the two elements :
     * <ul>
     * <li>{@link #EXOSPHERIC}</li>
     * <li>{@link #ALTITUDE}</li>
     * </ul>
     * @param t the value of temperature to set
     */
    void set_temperature(const int index, const Temperature t) { temperatures[index] = t; }

    /** Get one of the stored densities.
     * @param index one of the nine elements :
     * <ul>
     * <li>{@link #HELIUM}</li>
     * <li>{@link #ATOMIC_OXYGEN}</li>
     * <li>{@link #MOLECULAR_NITROGEN}</li>
     * <li>{@link #MOLECULAR_OXYGEN}</li>
     * <li>{@link #ARGON}</li>
     * <li>{@link #TOTAL_MASS}</li>
     * <li>{@link #HYDROGEN}</li>
     * <li>{@link #ATOMIC_NITROGEN}</li>
     * <li>{@link #ATOMIC_NITROGEN}</li>
     * </ul>
     * @return the requested density
     */
    NumberDensity get_density(const int index) { return densities[index]; }

    /** Calculate G(L) function with upper thermosphere parameters.
     *  @param p array of parameters
     *  @return G(L) value
     */
    quantity globe7(const quantity[] p)
    {
        // Extract raw values from typed quantities for use in polynomial expressions
        const quantity[] t      = new quantity[14];
            const quantity cd32 = cos(doy - p[31]));
            const quantity cd18 = cos(2.0 * doy - p[17]));
            const quantity cd14 = cos(doy - p[13]));
            const quantity cd39 = cos(2.0 * doy - p[38]));

            // F10.7 effect
            const quantity df  = f107 - f107a;
            const quantity dfa = f107a - FLUX_REF;
            t[0]               = p[19] * df * (1.0 + p[59] * dfa) + p[20] * df * df + p[21] * dfa + p[29] * dfa * dfa;

            const quantity f1 = 1.0 + (p[47] * dfa + p[19] * df + p[20] * df * df) * options[F107_EFFECT_ON_MEAN].crossEffect;
            const quantity f2 = 1.0 + (p[49] * dfa + p[19] * df + p[20] * df * df) * options[F107_EFFECT_ON_MEAN].crossEffect;

            // Time independent
            t[1] = (p[1] * legendrePolynomials[0][2] + p[2] * legendrePolynomials[0][4] + p[22] * legendrePolynomials[0][6]) +
                   (p[14] * legendrePolynomials[0][2]) * dfa * options[F107_EFFECT_ON_MEAN].crossEffect +
                   p[26] * legendrePolynomials[0][1];

            // Symmetrical annual
            t[2] = p[18] * cd32;

            // Symmetrical semiannual
            t[3] = (p[15] + p[16] * legendrePolynomials[0][2]) * cd18;

            // Asymmetrical annual
            t[4] = f1 * (p[9] * legendrePolynomials[0][1] + p[10] * legendrePolynomials[0][3]) * cd14;

            // Asymmetrical semiannual
            t[5] = p[37] * legendrePolynomials[0][1] * cd39;

            // Diurnal
            if (options[DIURNAL].mainEffect) {
                const quantity t71 = (p[11] * legendrePolynomials[1][2]) * cd14 * options[ASYMMETRICAL_ANNUAL].crossEffect;
                const quantity t72 = (p[12] * legendrePolynomials[1][2]) * cd14 * options[ASYMMETRICAL_ANNUAL].crossEffect;
                t[6] =
                    f2 *
                    ((p[3] * legendrePolynomials[1][1] + p[4] * legendrePolynomials[1][3] + p[27] * legendrePolynomials[1][5] + t71) * ctloc +
                     (p[6] * legendrePolynomials[1][1] + p[7] * legendrePolynomials[1][3] + p[28] * legendrePolynomials[1][5] + t72) * stloc);
            }

            // Semidiurnal
            if (options[SEMIDIURNAL].mainEffect) {
                const quantity t81 = (p[23] * legendrePolynomials[2][3] + p[35] * legendrePolynomials[2][5]) * cd14 *
                                     options[ASYMMETRICAL_ANNUAL].crossEffect;
                const quantity t82 = (p[33] * legendrePolynomials[2][3] + p[36] * legendrePolynomials[2][5]) * cd14 *
                                     options[ASYMMETRICAL_ANNUAL].crossEffect;
                t[7] = f2 * ((p[5] * legendrePolynomials[2][2] + p[41] * legendrePolynomials[2][4] + t81) * c2tloc +
                             (p[8] * legendrePolynomials[2][2] + p[42] * legendrePolynomials[2][4] + t82) * s2tloc);
            }

            // Terdiurnal
            if (options[TERDIURNAL].mainEffect) {
                t[13] = f2 * ((p[39] * legendrePolynomials[3][3] +
                               (p[93] * legendrePolynomials[3][4] + p[46] * legendrePolynomials[3][6]) * cd14 *
                                   options[ASYMMETRICAL_ANNUAL].crossEffect) *
                                  s3tloc +
                              (p[40] * legendrePolynomials[3][3] +
                               (p[94] * legendrePolynomials[3][4] + p[48] * legendrePolynomials[3][6]) * cd14 *
                                   options[ASYMMETRICAL_ANNUAL].crossEffect) *
                                  c3tloc);
            }

            // magnetic activity based on daily ap
            if (options[DAILY_AP].fullAp) {
                if (p[51] != 0) {
                    const quantity exp1 = exp(-10800.0 * abs(p[51]) / (1.0 + p[138] * (LAT_REF * rad) - abs(lat)));
                    const quantity p24  = max(p[24], 1.0e-4);
                    apt                 = sg0(min(exp1, 0.99999), p24, p[25]);
                    t[8] = apt * (p[50] + p[96] * legendrePolynomials[0][2] + p[54] * legendrePolynomials[0][4] +
                                  (p[125] * legendrePolynomials[0][1] + p[126] * legendrePolynomials[0][3] +
                                   p[127] * legendrePolynomials[0][5]) *
                                      cd14 * options[ASYMMETRICAL_ANNUAL].crossEffect +
                                  (p[128] * legendrePolynomials[1][1] + p[129] * legendrePolynomials[1][3] +
                                   p[130] * legendrePolynomials[1][5]) *
                                      options[DIURNAL].crossEffect * cos(hour2rad * (hl - p[131])));
                }
            }
            else {
                const quantity apd = ap[0] - 4.0;
                const quantity p44 = (p[43] < 0.) ? 1.0E-5 : p[43];
                const quantity p45 = p[44];
                apdf               = apd + (p45 - 1.0) * (apd + (exp(-p44 * apd) - 1.0) / p44);
                if (options[DAILY_AP].mainEffect) {
                    t[8] = apdf * (p[32] + p[45] * legendrePolynomials[0][2] + p[34] * legendrePolynomials[0][4] +
                                   (p[100] * legendrePolynomials[0][1] + p[101] * legendrePolynomials[0][3] +
                                    p[102] * legendrePolynomials[0][5]) *
                                       cd14 * options[ASYMMETRICAL_ANNUAL].crossEffect +
                                   (p[121] * legendrePolynomials[1][1] + p[122] * legendrePolynomials[1][3] +
                                    p[123] * legendrePolynomials[1][5]) *
                                       options[DIURNAL].crossEffect * cos(hour2rad * (hl - p[124])));
                }
            }

            if (options[ALL_UT_LONGITUDINAL_EFFECTS].mainEffect) {
                const quantity lonr = lon;
                const SinCos scLonr = sinCos(lonr);
                // Longitudinal
                if (options[LONGITUDINAL_EFFECTS].mainEffect) {
                    t[10] = (1.0 + p[80] * dfa * options[F107_EFFECT_ON_MEAN].crossEffect) *
                            ((p[64] * legendrePolynomials[1][2] + p[65] * legendrePolynomials[1][4] +
                              p[66] * legendrePolynomials[1][6] + p[103] * legendrePolynomials[1][1] +
                              p[104] * legendrePolynomials[1][3] + p[105] * legendrePolynomials[1][5] +
                              (p[109] * legendrePolynomials[1][1] + p[110] * legendrePolynomials[1][3] +
                               p[111] * legendrePolynomials[1][5]) *
                                  options[ASYMMETRICAL_ANNUAL].crossEffect * cd14) *
                                 scLonr.cos() +
                             (p[90] * legendrePolynomials[1][2] + p[91] * legendrePolynomials[1][4] +
                              p[92] * legendrePolynomials[1][6] + p[106] * legendrePolynomials[1][1] +
                              p[107] * legendrePolynomials[1][3] + p[108] * legendrePolynomials[1][5] +
                              (p[112] * legendrePolynomials[1][1] + p[113] * legendrePolynomials[1][3] +
                               p[114] * legendrePolynomials[1][5]) *
                                  options[ASYMMETRICAL_ANNUAL].crossEffect * cd14) *
                                 scLonr.sin());
                }

                // ut and mixed ut, longitude
                if (options[UT_AND_MIXED_UT_LONGITUDINAL_EFFECTS].mainEffect) {
                    t[11] = (1.0 + p[95] * legendrePolynomials[0][1]) *
                            (1.0 + p[81] * dfa * options[F107_EFFECT_ON_MEAN].crossEffect) *
                            (1.0 + p[119] * legendrePolynomials[0][1] * options[ASYMMETRICAL_ANNUAL].crossEffect * cd14) *
                            (p[68] * legendrePolynomials[0][1] + p[69] * legendrePolynomials[0][3] +
                             p[70] * legendrePolynomials[0][5]) *
                            cos(sec2rad * (sec - p[71]));
                    t[11] += options[LONGITUDINAL_EFFECTS] *
                             (1.0 + p[137].crossEffect * dfa * options[F107_EFFECT_ON_MEAN].crossEffect) *
                             (p[76] * legendrePolynomials[2][3] + p[77] * legendrePolynomials[2][5] +
                              p[78] * legendrePolynomials[2][7]) *
                             cos(sec2rad * (sec - p[79]) + 2.0 * lonr);
                }

                /* ut, longitude magnetic activity */
                if (options[MIXED_AP_UT_LONGITUDINAL_EFFECTS].mainEffect) {
                    if (options[DAILY_AP].fullAp) {
                        if (p[51] != 0.) {
                            t[12] = apt * options[LONGITUDINAL_EFFECTS].crossEffect *
                                        (1. + p[132] * legendrePolynomials[0][1]) *
                                        (p[52] * legendrePolynomials[1][2] + p[98] * legendrePolynomials[1][4] +
                                         p[67] * legendrePolynomials[1][6]) *
                                        cos(lon - p[97] * rad_val) +
                                    apt * options[LONGITUDINAL_EFFECTS].crossEffect *
                                        options[ASYMMETRICAL_ANNUAL].crossEffect * cd14 *
                                        (p[133] * legendrePolynomials[1][1] + p[134] * legendrePolynomials[1][3] +
                                         p[135] * legendrePolynomials[1][5]) *
                                        cos(lon - p[136] * rad_val) +
                                    apt * options[UT_AND_MIXED_UT_LONGITUDINAL_EFFECTS].crossEffect *
                                        (p[55] * legendrePolynomials[0][1] + p[56] * legendrePolynomials[0][3] +
                                         p[57] * legendrePolynomials[0][5]) *
                                        cos(sec2rad * (sec - p[58]));
                        }
                    }
                    else {
                        t[12] = apdf * options[LONGITUDINAL_EFFECTS].crossEffect * (1.0 + p[120] * legendrePolynomials[0][1]) *
                                    ((p[60] * legendrePolynomials[1][2] + p[61] * legendrePolynomials[1][4] +
                                      p[62] * legendrePolynomials[1][6]) *
                                     cos(lon - p[63] * rad_val)) +
                                apdf * options[LONGITUDINAL_EFFECTS].crossEffect * options[ASYMMETRICAL_ANNUAL].crossEffect * cd14 *
                                    (p[115] * legendrePolynomials[1][1] + p[116] * legendrePolynomials[1][3] +
                                     p[117] * legendrePolynomials[1][5]) *
                                    cos(lon - p[118] * rad_val) +
                                apdf * options[UT_AND_MIXED_UT_LONGITUDINAL_EFFECTS].crossEffect *
                                    (p[83] * legendrePolynomials[0][1] + p[84] * legendrePolynomials[0][3] +
                                     p[85] * legendrePolynomials[0][5]) *
                                    cos(sec2rad * (sec - p[75]));
                    }
                }
            }

            // Sum all effects (params not used: 82, 89, 99, 139-149)
            quantity tempInf = p[30];
            for (int i = 0; i < 14; i++) {
                tempInf += abs(sw[i + 1]) * t[i];
            }

            // Return G(L)
            return tempInf;
    }

    /** Calculate G(L) function with lower atmosphere parameters.
     *  @param p array of parameters
     *  @return G(L) value
     */
    quantity glob7s(const quantity[] p)
    {
        const quantity[] t  = new quantity[14];
        const quantity cd32 = cos(doy - p[31]);
        const quantity cd18 = cos(2.0 * doy - p[17]);
        const quantity cd14 = cos(doy - p[13]);
        const quantity cd39 = cos(2.0 * doy - p[38]);

        // F10.7 effect
        t[0] = p[21] * (f107a - FLUX_REF);

        // Time independent
        t[1] = p[1] * legendrePolynomials[0][2] + p[2] * legendrePolynomials[0][4] + p[22] * legendrePolynomials[0][6] +
               p[26] * legendrePolynomials[0][1] + p[14] * legendrePolynomials[0][3] + p[59] * legendrePolynomials[0][5];

        // Symmetrical annual
        t[2] = (p[18] + p[47] * legendrePolynomials[0][2] + p[29] * legendrePolynomials[0][4]) * cd32;

        // Symmetrical semiannual
        t[3] = (p[15] + p[16] * legendrePolynomials[0][2] + p[30] * legendrePolynomials[0][4]) * cd18;

        // Asymmetrical annual
        t[4] = (p[9] * legendrePolynomials[0][1] + p[10] * legendrePolynomials[0][3] + p[20] * legendrePolynomials[0][5]) * cd14;

        // Asymmetrical semiannual
        t[5] = (p[37] * legendrePolynomials[0][1]) * cd39;

        // Diurnal
        if (options[DIURNAL].mainEffect) {
            const quantity t71 = p[11] * legendrePolynomials[1][2] * cd14 * options[ASYMMETRICAL_ANNUAL].crossEffect;
            const quantity t72 = p[12] * legendrePolynomials[1][2] * cd14 * options[ASYMMETRICAL_ANNUAL].crossEffect;
            t[6]               = (p[3] * legendrePolynomials[1][1] + p[4] * legendrePolynomials[1][3] + t71) * ctloc +
                   (p[6] * legendrePolynomials[1][1] + p[7] * legendrePolynomials[1][3] + t72) * stloc;
        }

        // Semidiurnal
        if (options[SEMIDIURNAL].mainEffect) {
            const quantity t81 = (p[23] * legendrePolynomials[2][3] + p[35] * legendrePolynomials[2][5]) * cd14 *
                                 options[ASYMMETRICAL_ANNUAL].crossEffect;
            const quantity t82 = (p[33] * legendrePolynomials[2][3] + p[36] * legendrePolynomials[2][5]) * cd14 *
                                 options[ASYMMETRICAL_ANNUAL].crossEffect;
            t[7] = (p[5] * legendrePolynomials[2][2] + p[41] * legendrePolynomials[2][4] + t81) * c2tloc +
                   (p[8] * legendrePolynomials[2][2] + p[42] * legendrePolynomials[2][4] + t82) * s2tloc;
        }

        // Terdiurnal
        if (options[TERDIURNAL].mainEffect) {
            t[13] = p[39] * legendrePolynomials[3][3] * s3tloc + p[40] * legendrePolynomials[3][3] * c3tloc;
        }

        // Magnetic activity
        if (options[DAILY_AP].mainEffect) {
            t[8] = apdf * (p[32] + p[45] * legendrePolynomials[0][2] * options[INDEPENDENT_OF_TIME].crossEffect);
        }
        else if (options[DAILY_AP].fullAp) {
            t[8] = apt * (p[50] + p[96] * legendrePolynomials[0][2] * options[INDEPENDENT_OF_TIME].crossEffect);
        }

        // Longitudinal
        if (options[ALL_UT_LONGITUDINAL_EFFECTS].mainEffect == 0 && options[LONGITUDINAL_EFFECTS].mainEffect) {
            const quantity lonr = lon * rad;
            const SinCos scLonr = sinCos(lonr);
            t[10] = (1.0 + legendrePolynomials[0][1] * (p[80] * options[ASYMMETRICAL_ANNUAL].crossEffect * cos(doy - p[81])) +
                     p[85] * options[ASYMMETRICAL_SEMIANNUAL].crossEffect * cos(2.0 * doy - p[86])) +
                    p[83] * options[SYMMETRICAL_ANNUAL].crossEffect * cos(doy - p[84]) +
                    p[87] * options[SYMMETRICAL_SEMIANNUAL].crossEffect * cos(2.0 * doy - p[88]) *
                        ((p[64] * legendrePolynomials[1][2] + p[65] * legendrePolynomials[1][4] +
                          p[66] * legendrePolynomials[1][6] + p[74] * legendrePolynomials[1][1] +
                          p[75] * legendrePolynomials[1][3] + p[76] * legendrePolynomials[1][5]) *
                             scLonr.cos() +
                         (p[90] * legendrePolynomials[1][2] + p[91] * legendrePolynomials[1][4] +
                          p[92] * legendrePolynomials[1][6] + p[77] * legendrePolynomials[1][1] +
                          p[78] * legendrePolynomials[1][3] + p[79] * legendrePolynomials[1][5]) *
                             scLonr.sin());
        }

        // Sum all effects
        quantity gl = 0;
        for (int i = 0; i < 14; i++) {
            gl += abs(sw[i + 1]) * t[i];
        }

        // Return G(L)
        return gl;
    }

    /** Implements sg0 function (Eq. A24a).
     * @param ex ex
     * @param p24 abs(p[24])
     * @param p25 p[25]
     * @return sg0
     */
    Unitless sg0(const Unitless& ex, const Unitless& p24, const Unitless& p25)
    {
        const Unitless g01   = g0(ap[1], p24, p25);
        const Unitless g02   = g0(ap[2], p24, p25);
        const Unitless g03   = g0(ap[3], p24, p25);
        const Unitless g04   = g0(ap[4], p24, p25);
        const Unitless g05   = g0(ap[5], p24, p25);
        const Unitless g06   = g0(ap[6], p24, p25);
        const Unitless ex2   = ex * ex;
        const Unitless ex3   = ex * ex2;
        const Unitless ex4   = ex2 * ex2;
        const Unitless ex8   = ex4 * ex4;
        const Unitless ex12  = ex4 * ex8;
        const Unitless g234  = g02 * ex + g03 * ex2 + g04 * ex3;
        const Unitless g56   = g05 * ex4 + g06 * ex12;
        const Unitless ex19  = ex3 * ex4 * ex12;
        const Unitless omex  = 1.0 - ex;
        const Unitless sumex = 1.0 + (1.0 - ex19) / omex * sqrt(ex);
        return (g01 + (g234 + g56 * (1.0 - ex8) / omex)) / sumex;
    }

    /** Implements go function (Eq. A24d).
     * @param apI 3 hrs ap
     * @param p24 abs(p[24])
     * @param p25 p[25]
     * @return go
     */
    Unitless g0(const Unitless& apI, const Unitless& p24, const Unitless& p25)
    {
        const Unitless am4 = apI - 4.0;
        return am4 + (p25 - 1.0) * (am4 + (exp(-p24 * am4) - 1.0) / p24);
    }

    /** Calculates chemistry/dissociation correction for MSIS models.
     * @param alt altitude
     * @param r target ratio
     * @param h1 transition scale length
     * @param zh altitude of 1/2 R
     * @return correction
     */
    Unitless calculate_dissociation_correction(const Distance alt, const Unitless r, const Distance h1, const Distance zh)
    {
        const Unitless e = (alt - zh) / h1;
        if (e > 70.0 * one) { return 1.0 * one; }
        else if (e < -70.0 * one) {
            return exp(r);
        }
        else {
            return exp(r / (1.0 + exp(e)));
        }
    }


    /** Calculates O & O2 chemistry/dissociation correction for MSIS models.
     * @param alt altitude
     * @param r target ratio
     * @param h1 transition scale length
     * @param zh altitude of 1/2 R
     * @param h2 transition scale length
     * @return correction
     */
    Unitless calculate_oxygen_dissociation_correction(const Distance alt, const Unitless r, const Distance h1, const Distance zh, const Distance h2)
    {
        const Unitless e1 = (alt - zh) / h1;
        const Unitless e2 = (alt - zh) / h2;
        if (e1 > 70.0 * one || e2 > 70.0 * one) { return 1.0 * one; }
        else if (e1 < -70.0 * one && e2 < -70.0 * one) {
            return exp(r);
        }
        else {
            const Unitless ex1 = exp(e1);
            const Unitless ex2 = exp(e2);
            return exp(r / (1.0 * one + 0.5 * (ex1 + ex2)));
        }
    }

    /** Calculates scale height.
     * @param alt altitude
     * @param speciesMolecularWeight species molecular weight
     * @param temp temperature
     * @return scale height (km)
     */
    Distance calculate_scale_height(const Distance& alt, const NumberDensity& speciesMolecularWeight, const Temperature& temp)
    {
        // Gravity at altitude
        const Acceleration calculate_gravity_at_altitude = glat / pow<2>(1.0 * one + alt / rlat);
        return R_GAS * temp / (calculate_gravity_at_altitude * speciesMolecularWeight);
    }

    /** Calculates turbopause correction for MSIS models.
     * @param dd diffusive density
     * @param dm full mixed density
     * @param zhm transition scale length
     * @param XMM full mixed molecular weight
     * @param speciesMolecularWeight species molecular weight
     * @return combined density
     */
    Unitless calculate_turbopause_correction(
        const Unitless& diffusiveDensity,
        const Unitless& mixedDensity,
        const Unitless& transitionScaleLength,
        const Unitless& fullMixedMolecularWeight,
        const Unitless& speciesMolecularWeight
    )
    {
        if (!(mixedDensity > 0 && diffusiveDensity > 0)) {
            Unitless ddd = diffusiveDensity;
            if (diffusiveDensity == 0 && mixedDensity == 0) { ddd = 1; }
            if (mixedDensity == 0) { return ddd; }
            if (diffusiveDensity == 0) { return mixedDensity; }
        }

        const Unitless a    = transitionScaleLength / (fullMixedMolecularWeight - speciesMolecularWeight);
        const Unitless ylog = a * log(mixedDensity / diffusiveDensity);
        if (ylog < -10.) { return diffusiveDensity; }
        else if (ylog > 10.) {
            return mixedDensity;
        }
        else {
            return diffusiveDensity * pow(1.0 + exp(ylog), 1.0 / a);
        }
    }

    /** Calculate Temperature and Density Profiles for lower atmosphere.
     * @param alt altitude
     * @param d0 density
     * @param xm mixed density
     * @return temperature or density profile
     */
    quantity calculate_density_temperature_profile(const Distance& alt, const Density& density0, const Unitless& mixedDensity)
    {
        quantity densm = density0;

        // stratosphere/mesosphere temperature
        int mn     = ZN2.size();
        quantity z = (alt > ZN2[mn - 1] * km) ? alt : ZN2[mn - 1];

        quantity z1    = ZN2[0] * km;
        quantity z2    = ZN2[mn - 1] * km;
        quantity t1    = mesoTn2[0];
        quantity t2    = mesoTn2[mn - 1];
        quantity zg    = zeta(z, z1);
        quantity zgdif = zeta(z2, z1);

        /* set up spline nodes */
        quantity[] xs = new quantity[mn];
        quantity[] ys = new quantity[mn];
        for (int k = 0; k < mn; k++) {
            xs[k] = zeta(ZN2[k] * km), z1 / zgdif;
            ys[k] = 1.0 / mesoTn2[k];
        }
        const quantity qSM = (rlat + z2) / (rlat + z1);
        quantity yd1       = -mesoTgn2[0] / (t1 * t1) * zgdif;
        quantity yd2       = -mesoTgn2[1] / (t2 * t2) * zgdif * qSM * qSM;

        /* calculate spline coefficients */
        quantity[] y2out = spline(xs, ys, yd1, yd2);
        quantity x       = zg / zgdif;
        quantity y       = splint(xs, ys, y2out, x);

        /* temperature at altitude */
        quantity tz = 1.0 / y;

        if (mixedDensity != 0.0) {
            /* calculate stratosphere / mesospehere density */
            const quantity glb  = calculate_gravity_at_altitude(z1);
            const quantity gamm = mixedDensity * glb * zgdif / R_GAS;

            /* Integrate temperature profile */
            const quantity yi   = splini(xs, ys, y2out, x);
            const quantity expl = min(MIN_TEMP, gamm * yi);

            /* Density at altitude */
            densm *= (t1 / tz) * exp(-expl);
        }

        if (alt > ZN3[0]) { return (mixedDensity == 0.0) ? tz : densm; }

        // troposhere/stratosphere temperature
        z     = alt;
        mn    = ZN3.size();
        z1    = ZN3[0] * km;
        z2    = ZN3[mn - 1] * km;
        t1    = mesoTn3[0];
        t2    = mesoTn3[mn - 1];
        zg    = zeta(z, z1);
        zgdif = zeta(z2, z1);

        /* set up spline nodes */
        xs = new quantity[mn];
        ys = new quantity[mn];
        for (int k = 0; k < mn; k++) {
            xs[k] = zeta(ZN3[k] * km), z1 / zgdif;
            ys[k] = 1.0 / mesoTn3[k];
        }
        const quantity qTS = (rlat + z2) / (rlat + z1);
        yd1                = -mesoTgn3[0] / (t1 * t1) * zgdif;
        yd2                = -mesoTgn3[1] / (t2 * t2) * zgdif * qTS * qTS;

        /* calculate spline coefficients */
        y2out = spline(xs, ys, yd1, yd2);
        x     = zg / zgdif;
        y     = splint(xs, ys, y2out, x);

        /* temperature at altitude */
        tz = 1.0 / y;

        if (mixedDensity != 0.0) {
            /* calculate tropospheric / stratosphere density */
            const quantity glb   = calculate_gravity_at_altitude(z1);
            const quantity gamm2 = mixedDensity * glb * zgdif / R_GAS;

            /* Integrate temperature profile */
            const quantity yi   = splini(xs, ys, y2out, x);
            const quantity expl = min(MIN_TEMP, gamm2 * yi);

            /* Density at altitude */
            densm *= (t1 / tz) * exp(-expl);
        }

        return (mixedDensity == 0.0) ? tz : densm;
    }

    /** Calculate temperature and density profiles according to new lower thermo polynomial.
     * @param alt altitude
     * @param densityLowerBound density at lower boundary
     * @param tempInf exospheric temperature
     * @param tempLowerBound temperature at lower boundary
     * @param xm species molecular weight
     * @param thermalDiffusionCoefficient thermal diffusion coefficient
     * @param altLowerBound altitude of the lower boundary
     * @param s2 slope
     * @return temperature or density profile
     */
    quantity calculate_density_temperature_profile_new(
        const Distance alt,
        const Density densityLowerBound,
        const Temperature tempInf,
        const Temperature tempLowerBound,
        const MolecularWeight speciesMolecularWeight,
        const Unitless thermalDiffusionCoefficient,
        const Distance altLowerBound,
        const Unitless slope
    )
    {
        /* joining altitudes of Bates and spline */
        const Distance z = (alt > ZN1[0]) ? alt : ZN1[0];

        /* geopotential altitude difference from ZLB */
        const Distance zg2 = zeta(z, altLowerBound);

        /* Bates temperature */
        const Temperature tt = tempInf - (tempInf - tempLowerBound) * exp(-slope * zg2);
        const Temperature ta = tt;
        Temperature tz       = tt;

        static const int mn = ZN1.size();
        const std::array<Unitless, mn> xs;
        const std::array<Unitless, mn> ys;
        Unitless x = 0.0;
        std::array<Unitless, mn> y2out;

        Distance zgdif = 0.0;
        if (alt < ZN1[0]) {
            /* calculate temperature below ZA
             * temperature gradient at ZA from Bates profile */
            const Unitless p      = (rlat + altLowerBound) / (rlat + ZN1[0]);
            const Temperature dta = (tempInf - ta) * slope * p * p;
            mesoTgn1[0]           = dta;
            mesoTn1[0]            = ta;
            z                     = (alt > ZN1[mn - 1]) ? alt : ZN1[mn - 1];

            const Temperature t1 = mesoTn1[0];
            const Temperature t2 = mesoTn1[mn - 1];

            /* geopotental difference from z1 */
            const Distance zg = zeta(z, ZN1[0]);
            zgdif             = zeta(ZN1[mn - 1], ZN1[0]);
            /* set up spline nodes */
            for (int k = 0; k < mn; k++) {
                xs[k] = zeta(ZN1[k], ZN1[0]) / zgdif;
                ys[k] = 1.0 / mesoTn1[k];
            }
            /* end node derivatives */
            const Unitless q   = (rlat + ZN1[mn - 1]) / (rlat + ZN1[0]);
            const Unitless yd1 = -mesoTgn1[0] / (t1 * t1) * zgdif;
            const Unitless yd2 = -mesoTgn1[1] / (t2 * t2) * zgdif * q * q;

            /* calculate spline coefficients */
            y2out            = spline(xs, ys, yd1, yd2);
            x                = zg / zgdif;
            const Distance y = splint(xs, ys, y2out, x);

            /* temperature at altitude */
            tz = 1.0 / y;
        }

        if (speciesMolecularWeight == 0) { return tz; }

        /* calculate density above za */
        quantity glb   = calculate_gravity_at_altitude(altLowerBound);
        quantity gamma = speciesMolecularWeight * glb / (R_GAS * slope * tempInf);
        quantity expl  = (tt <= 0) ? MIN_TEMP : min(MIN_TEMP, exp(-slope * gamma * zg2));
        quantity densu = densityLowerBound * expl * pow(tempLowerBound / tt, 1.0 + thermalDiffusionCoefficient + gamma);

        // Correction for issue 1365 - protection against "densu" being infinite
        if (!std::isfinite(densu)) {
            if (expl < MIN_TEMP) {
                densu = densityLowerBound *
                        exp(log(tempLowerBound / tt) * (1.0 + thermalDiffusionCoefficient + gamma) - slope * gamma * zg2);
            }
            else {
                throw new OrekitException(OrekitMessages.INFINITE_Nrlmsise00_DENSITY);
            }
        }

        /* calculate density below za */
        if (alt < ZN1[0]) {
            glb   = calculate_gravity_at_altitude(ZN1[0]);
            gamma = speciesMolecularWeight * glb * zgdif / R_GAS;
            /* integrate spline temperatures */
            expl = (tz <= 0) ? MIN_TEMP : min(MIN_TEMP, gamma * splini(xs, ys, y2out, x));
            /* correct density at altitude */
            densu *= pow(mesoTn1[0] / tz, 1.0 + thermalDiffusionCoefficient) * exp(-expl);
        }

        /* Return density at altitude */
        return densu;
    }

    /** Calculate gravity at altitude.
     * @param alt altitude (km)
     * @return gravity at altitude (cm/s2)
     */
    Acceleration calculate_gravity_at_altitude(const Distance& alt) { return glat / pow<2>(1.0 + alt / rlat); }

    /** Calculate zeta function.
     * @param zz zz value
     * @param zl zl value
     * @return value of zeta function
     */
    Distance zeta(const Distance& zz, const Distance& zl) { return (zz - zl) * (rlat + zl) / (rlat + zz); }
}

} // namespace planets
} // namespace astro
} // namespace astrea