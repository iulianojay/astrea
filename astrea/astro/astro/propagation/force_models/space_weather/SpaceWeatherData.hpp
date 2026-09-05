/**
 * @file SpaceWeatherData.hpp
 * @author Jay Iuliano (iuliano.jay@gmail.com)
 * @brief Header file for the SpaceWeatherData struct, which stores space weather data.
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

#include <cstdint>
#include <vector>

#include <units/units.hpp>

#include <astro/time/Date.hpp>

namespace astrea {
namespace astro {
namespace space_weather {

// Enum for measurement types
enum class MeasurementType : std::uint8_t {
    OBSERVED          = 0,
    DAILY_PREDICTED   = 1,
    MONTHLY_PREDICTED = 2,
    MONTHLY_FIT       = 3,
};

struct SolarFluxData {
    SolarFlux nominal;              //<! Nominal 10.7 cm Solar Radio Flux
    SolarFlux centered81DayAverage; //!< Centered 81-day Average of the 10.7 cm Solar Radio Flux
    SolarFlux last81DayAverage;     //!< Last 81-day Average of the 10.7 cm Solar Radio Flux
};

// Build a struct for each line of the EOP data: https://celestrak.org/SpaceData/SpaceWx-format.php
struct SpaceWeatherParameters {
    MeasurementType measurement;
    Date date;         // Date of the measurement(s)
    std::uint8_t bsrn; //!< Bartels Solar Rotation Number. A sequence of 27-day intervals counted continuously from 1832 Feb 8.
    std::uint8_t nd;            //!< Number of Day within the Bartels 27-day cycle (01-27).
    std::array<Unitless, 8> kp; //!< Planetary 3-hour Range Index with each index corresponding to the ith 3-hour interval of the day (00-03, 03-06, 06-09, 09-12, 12-15, 15-18, 18-21, 21-24).
    Unitless sumKp;             //!< Daily Sum of the 8 Kp indices
    std::array<Unitless, 8> ap; //!< Planetary Equivalent Amplitude with each index corresponding to the ith 3-hour interval of the day (00-03, 03-06, 06-09, 09-12, 12-15, 15-18, 18-21, 21-24).
    Unitless avgAp;             //!< Daily Average of the 8 Ap indices
    Unitless cp;                //!< Cp or Planetary Daily Character Figure. A qualitative estimate of overall level of
                 //!< magnetic activity for the day determined from the sum of the 8 Ap indices. Cp ranges, in steps of one-tenth, from 0 (quiet) to 2.5 (highly disturbed).
    std::uint8_t c9; //!< C9. A conversion of the 0-to-2.5 range of the Cp index to one digit between 0 and 9
    unsigned isn; //!< International Sunspot Number. Records contain the Zurich number through 1980 Dec 31 and the International Brussels number thereafter.
    SolarFluxData f107Obs; //!< Observed 10.7 cm Solar Radio Flux
    SolarFluxData f107Adj; //!< Adjusted 10.7 cm Solar Radio Flux adjusted to 1 AU
};

struct SpaceWeatherData {

    SpaceWeatherData()  = default;
    ~SpaceWeatherData() = default;

    void clear() { _data.clear(); }

    void push_back(const SpaceWeatherParameters& row) { _data.push_back(row); }

    void push_back(SpaceWeatherParameters&& row) { _data.push_back(std::move(row)); }

    void emplace_back(const SpaceWeatherParameters& row) { _data.emplace_back(row); }

    void emplace_back(SpaceWeatherParameters&& row) { _data.emplace_back(std::move(row)); }

    [[nodiscard]] std::size_t size() const { return _data.size(); }

    [[nodiscard]] const std::vector<SpaceWeatherParameters>& data() const { return _data; }

  private:
    std::vector<SpaceWeatherParameters> _data;
};

} // namespace space_weather
} // namespace astro
} // namespace astrea