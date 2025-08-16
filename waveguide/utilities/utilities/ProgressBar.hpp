/**
 * @file ProgressBar.hpp
 * @author Jay Iuliano (iuliano.jay@gmail.com)
 * @brief A simple progress bar utility for console applications.
 * @version 0.1
 * @date 2025-08-02
 *
 * @copyright Copyright (c) 2025
 *
 */
#pragma once

#include <iostream>
#include <string>

namespace waveguide {
namespace utilities {

/**
 * @brief A simple console progress bar utility.
 */
class ProgressBar {
  public:
    /**
     * @brief Constructs a ProgressBar instance.
     *
     * @param maxRecords The maximum number of records to process.
     * @param title The title of the progress bar.
     * @param frequency The frequency of updates (in terms of records processed).
     * @param barWidth The width of the progress bar in characters.
     */
    ProgressBar(const std::size_t& maxRecords, const std::string& title = "Progress", const std::size_t& frequency = 0, const std::size_t& barWidth = 50) :
        _iRecord(0),
        _maxRecords(maxRecords),
        _title(title),
        _frequency(frequency == 0 ? static_cast<std::size_t>(std::ceil(static_cast<double>(maxRecords) / 100.0)) : frequency),
        _barWidth(barWidth)
    {
    }

    /**
     * @brief Default destructor for ProgressBar.
     */
    ~ProgressBar() = default;

    /**
     * @brief Resets the progress bar to the initial state.
     */
    inline void reset() { _iRecord = 0; }

    /**
     * @brief Updates the progress bar and prints it to the console.
     *
     * This method should be called periodically to update the progress bar.
     */
    inline void operator()()
    {
        // Progress bar
        if (_iRecord % _frequency == 0 || _iRecord == _maxRecords - 1) {
            std::cout << _title << ": [";
            const double progress = static_cast<double>(_iRecord + 1) / static_cast<double>(_maxRecords);
            const std::size_t pos = static_cast<std::size_t>(static_cast<double>(_barWidth) * progress);
            for (std::size_t ii = 0; ii < _barWidth; ++ii) {
                if (ii < pos)
                    std::cout << "=";
                else if (ii == pos)
                    std::cout << ">";
                else
                    std::cout << " ";
            }
            std::cout << "] " << int(std::round(progress * 100.0)) << " %\r";
            std::cout.flush();
        }
        ++_iRecord;
    }

  private:
    std::size_t _iRecord;          //!< Current record index
    const std::size_t _maxRecords; //!< Maximum number of records to process
    const std::string _title;      //!< Title of the progress bar
    const std::size_t _frequency;  //!< Frequency of updates (in terms of records processed)
    const std::size_t _barWidth;   //!< Width of the progress bar in characters
};

} // namespace utilities
} // namespace waveguide