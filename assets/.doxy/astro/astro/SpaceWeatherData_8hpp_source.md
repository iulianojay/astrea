

# File SpaceWeatherData.hpp

[**File List**](files.md) **>** [**astrea**](dir_b5324400686b7cece921533bb760c87a.md) **>** [**astro**](dir_1d4dcf10fc541574a93624f5c09a3d6f.md) **>** [**astro**](dir_84db6e3c60e44147f5214c05dc45afc2.md) **>** [**propagation**](dir_55ae0edd352c6621ebfa1115f28a0fff.md) **>** [**force\_models**](dir_0ce51a85166db93c377c5b7f000b236c.md) **>** [**space\_weather**](dir_ba92a5bb4647772267966b3cef944594.md) **>** [**SpaceWeatherData.hpp**](SpaceWeatherData_8hpp.md)

[Go to the documentation of this file](SpaceWeatherData_8hpp.md)


```C++

#pragma once

#include <cstdint>
#include <filesystem>
#include <optional>
#include <vector>

#include <units/units.hpp>

#include <astro/time/Date.hpp>

namespace astrea {
namespace astro {

enum class MeasurementType : std::uint8_t {
    OBSERVED          = 0,
    DAILY_PREDICTED   = 1,
    MONTHLY_PREDICTED = 2,
    MONTHLY_FIT       = 3,
};

struct SolarFluxData {
    SolarFlux nominal;              //<! Nominal 10.7 cm Solar Radio Flux
    SolarFlux centered81DayAverage; 
    SolarFlux last81DayAverage;     
};

struct SpaceWeatherParameters {
    MeasurementType measurement;
    Date date;         // Date of the measurement(s)
    std::uint8_t bsrn; 
    std::uint8_t nd;            
    std::array<Unitless, 8> kp; 
    Unitless sumKp;             
    std::array<Unitless, 8> ap; 
    Unitless avgAp;             
    Unitless cp;                
    std::uint8_t c9; 
    unsigned isn; 
    SolarFluxData f107Obs; 
    SolarFluxData f107Adj; 
};

class SpaceWeatherData {
  public:
    SpaceWeatherData() = default;

    SpaceWeatherData(const std::filesystem::path& infile, std::optional<Date> startDate = std::nullopt, std::optional<Date> endDate = std::nullopt);

    ~SpaceWeatherData() = default;

    [[nodiscard]] std::size_t size() const;

    [[nodiscard]] const std::vector<SpaceWeatherParameters>& data() const;

    [[nodiscard]] const std::filesystem::path& infile() const noexcept;

    [[nodiscard]] bool empty() const noexcept;

    [[nodiscard]] const SpaceWeatherParameters& operator[](std::size_t index) const;

    [[nodiscard]] SpaceWeatherParameters& operator[](std::size_t index);

    [[nodiscard]] const SpaceWeatherParameters& at(std::size_t index) const;

    [[nodiscard]] SpaceWeatherParameters& at(std::size_t index);

    [[nodiscard]] const SpaceWeatherParameters& at(const Date& date) const;

    [[nodiscard]] SpaceWeatherParameters& at(const Date& date);

    [[nodiscard]] const std::optional<Date>& startDate() const noexcept;

    [[nodiscard]] const std::optional<Date>& endDate() const noexcept;

  private:
    std::filesystem::path _infile;
    std::optional<Date> _startDate;
    std::optional<Date> _endDate;
    std::vector<SpaceWeatherParameters> _data;
};

} // namespace astro
} // namespace astrea
```


