#pragma once

#include <iostream>
#include <string>

namespace waveguide {
namespace utilities {

class ProgressBar {
  public:
    ProgressBar(const std::size_t maxRecords, const std::string& title = "Progress", const std::size_t& frequency = 10, const std::size_t& barWidth = 50) :
        _iRecord(0),
        _maxRecords(maxRecords),
        _title(title),
        _frequency(frequency),
        _barWidth(barWidth)
    {
    }
    ~ProgressBar() = default;

    inline void reset() { _iRecord = 0; }

    inline void operator()()
    {
        // Progress bar
        if (_iRecord % _frequency == 0) {
            std::cout << _title << ": [";
            const double progress = static_cast<double>(_iRecord) / static_cast<double>(_maxRecords);
            const std::size_t pos = _barWidth * progress;
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
    std::string _title;
    std::size_t _iRecord;
    std::size_t _barWidth;
    std::size_t _maxRecords;
    std::size_t _frequency;
};

} // namespace utilities
} // namespace waveguide