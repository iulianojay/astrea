

# File ProgressBar.hpp

[**File List**](files.md) **>** [**astrea**](dir_b5324400686b7cece921533bb760c87a.md) **>** [**utilities**](dir_bc3eec91113c7b4aa38cf4b314cc4587.md) **>** [**utilities**](dir_e80a6df966dae334846d11eed150d587.md) **>** [**ProgressBar.hpp**](ProgressBar_8hpp.md)

[Go to the documentation of this file](ProgressBar_8hpp.md)


```C++

#pragma once

#include <cmath>
#include <iostream>
#include <string>

namespace astrea {
namespace utilities {

class ProgressBar {
  public:
    ProgressBar(const std::size_t& maxRecords, const std::string& title = "Progress", const std::size_t& frequency = 0, const std::size_t& barWidth = 50) :
        _iRecord(0),
        _maxRecords(maxRecords),
        _title(title),
        _frequency(frequency == 0 ? static_cast<std::size_t>(std::ceil(static_cast<double>(maxRecords) / 100.0)) : frequency),
        _barWidth(barWidth)
    {
    }

    ~ProgressBar() = default;

    inline void reset() { _iRecord = 0; }

    inline std::size_t get_progress() const { return _iRecord; }

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
    std::size_t _iRecord;          
    const std::size_t _maxRecords; 
    const std::string _title;      
    const std::size_t _frequency;  
    const std::size_t _barWidth;   
};

} // namespace utilities
} // namespace astrea
```


