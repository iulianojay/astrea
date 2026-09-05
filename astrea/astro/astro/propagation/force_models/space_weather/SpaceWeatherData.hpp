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
#include <filesystem>
#include <optional>
#include <vector>

#include <units/units.hpp>

#include <astro/time/Date.hpp>

namespace astrea {
namespace astro {

/**
 * @brief Enumeration for the type of space weather measurement.
 */
enum class MeasurementType : std::uint8_t {
    OBSERVED          = 0,
    DAILY_PREDICTED   = 1,
    MONTHLY_PREDICTED = 2,
    MONTHLY_FIT       = 3,
};

/**
 * @brief Struct to hold solar flux data.
 *
 * This struct contains the nominal, centered 81-day average, and last 81-day average of the 10.7 cm Solar Radio Flux.
 */
struct SolarFluxData {
    SolarFlux nominal;              //<! Nominal 10.7 cm Solar Radio Flux
    SolarFlux centered81DayAverage; //!< Centered 81-day Average of the 10.7 cm Solar Radio Flux
    SolarFlux last81DayAverage;     //!< Last 81-day Average of the 10.7 cm Solar Radio Flux
};

/**
 * @brief Struct to hold space weather parameters for a specific date.
 *
 * This struct contains various space weather parameters, including the Bartels Solar Rotation Number, Kp indices,
 * Ap indices, Cp index, International Sunspot Number, and 10.7 cm Solar Radio Flux data.
 *
 * @note Format from https://celestrak.org/SpaceData/SpaceWx-format.php
 */
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

/**
 * @brief Class to hold space weather data read from a file.
 *
 * This class contains a vector of SpaceWeatherParameters and provides methods to access the data.
 */
class SpaceWeatherData {
  public:
    /**
     * @brief Default constructor for SpaceWeatherData.
     */
    SpaceWeatherData() = default;

    /**
     * @brief Construct a SpaceWeatherData object by reading space weather data from a file.
     *
     * @param infile Path to the space weather data file.
     * @param startDate Optional start date for filtering the data. If provided, only data on or after this date will be included.
     * @param endDate Optional end date for filtering the data. If provided, only data on or before this date will be included.
     */
    SpaceWeatherData(const std::filesystem::path& infile, std::optional<Date> startDate = std::nullopt, std::optional<Date> endDate = std::nullopt);

    /**
     * @brief Default destructor for SpaceWeatherData.
     */
    ~SpaceWeatherData() = default;

    /**
     * @brief Returns the number of space weather data entries.
     *
     * @return std::size_t The number of entries in the space weather data.
     */
    [[nodiscard]] std::size_t size() const;

    /**
     * @brief Returns a const reference to the vector of space weather parameters.
     *
     * @return const std::vector<SpaceWeatherParameters>& The vector of space weather parameters.
     */
    [[nodiscard]] const std::vector<SpaceWeatherParameters>& data() const;

    /**
     * @brief Returns the path to the space weather data file.
     *
     * @return const std::filesystem::path& The path to the space weather data file.
     */
    [[nodiscard]] const std::filesystem::path& infile() const noexcept;

    /**
     * @brief Checks if the space weather data is empty.
     *
     * @return true If there are no space weather data entries.
     * @return false If there are space weather data entries.
     */
    [[nodiscard]] bool empty() const noexcept;

    /**
     * @brief Access the space weather parameters at the specified index.
     *
     * @param index Index of the space weather parameters to access.
     * @return const SpaceWeatherParameters& Reference to the space weather parameters at the specified index.
     */
    [[nodiscard]] const SpaceWeatherParameters& operator[](std::size_t index) const;

    /**
     * @brief Access the space weather parameters at the specified index.
     *
     * @param index Index of the space weather parameters to access.
     * @return SpaceWeatherParameters& Reference to the space weather parameters at the specified index.
     */
    [[nodiscard]] SpaceWeatherParameters& operator[](std::size_t index);

    /**
     * @brief Access the space weather parameters at the specified index with bounds checking.
     *
     * @param index Index of the space weather parameters to access.
     * @return const SpaceWeatherParameters& Reference to the space weather parameters at the specified index.
     * @throws std::out_of_range If the index is out of range.
     */
    [[nodiscard]] const SpaceWeatherParameters& at(std::size_t index) const;

    /**
     * @brief Access the space weather parameters at the specified index with bounds checking.
     *
     * @param index Index of the space weather parameters to access.
     * @return SpaceWeatherParameters& Reference to the space weather parameters at the specified index.
     * @throws std::out_of_range If the index is out of range.
     */
    [[nodiscard]] SpaceWeatherParameters& at(std::size_t index);

    /**
     * @brief Access the space weather parameters for the specified date.
     *
     * @param date Date of the space weather parameters to access.
     * @return const SpaceWeatherParameters& Reference to the space weather parameters for the specified date.
     * @throws std::out_of_range If no data exists for the specified date.
     */
    [[nodiscard]] const SpaceWeatherParameters& at(const Date& date) const;

    /**
     * @brief Access the space weather parameters for the specified date.
     *
     * @param date Date of the space weather parameters to access.
     * @return SpaceWeatherParameters& Reference to the space weather parameters for the specified date.
     * @throws std::out_of_range If no data exists for the specified date.
     */
    [[nodiscard]] SpaceWeatherParameters& at(const Date& date);

    /**
     * @brief Access the optional start date for filtering the data.
     *
     * @return const std::optional<Date>& Optional start date.
     */
    [[nodiscard]] const std::optional<Date>& startDate() const noexcept;

    /**
     * @brief Access the optional end date for filtering the data.
     *
     * @return const std::optional<Date>& Optional end date.
     */
    [[nodiscard]] const std::optional<Date>& endDate() const noexcept;

  private:
    std::filesystem::path _infile;
    std::optional<Date> _startDate;
    std::optional<Date> _endDate;
    std::vector<SpaceWeatherParameters> _data;
};

} // namespace astro
} // namespace astrea