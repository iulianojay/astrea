

# File EthzClient.hpp

[**File List**](files.md) **>** [**astrea**](dir_b5324400686b7cece921533bb760c87a.md) **>** [**snapshot**](dir_ad01b7a66bf2103e1e551598d7ba094a.md) **>** [**snapshot**](dir_d7d302d432d8a6ab561803ec6eec1eed.md) **>** [**http-queries**](dir_e3fe50636e6aa25df3bf26a0e7917672.md) **>** [**ethz**](dir_31d12700b25e15af9e5493b70ce27e08.md) **>** [**EthzClient.hpp**](EthzClient_8hpp.md)

[Go to the documentation of this file](EthzClient_8hpp.md)


```C++

#pragma once

#include <string>

#include <cpr/cpr.h>
#include <nlohmann/json.hpp>

#include <astro/time/Date.hpp>

namespace astrea {
namespace snapshot {

class EthzClient {
  public:
    EthzClient() :
        _minStartDate("2023-03-10 00:00:00.0") {};

    ~EthzClient() = default;

    nlohmann::json query(const astro::Date& startDate, const astro::Date& endDate, const std::string& name, const bool& includeFrequencyData = false);

    nlohmann::json query(const astro::Date& startDate, const astro::Date& endDate, const unsigned& noradId, const bool& includeFrequencyData = false);

  private:
    const cpr::Url _base               = "https://satdb.ethz.ch/api"; 
    const cpr::Url _satDataUrl         = _base + "/satellitedata";    
    const cpr::Url _satUrl             = _base + "/satellite";        
    const cpr::Url _frequencySourceUrl = _base + "/frequencysource";  
    const cpr::Url _frequencyUrl       = _base + "/frequency";        
    const cpr::Authentication _auth    = { "user", "pass", cpr::AuthMode::BASIC }; 

    const astro::Date _minStartDate; 

    nlohmann::json query_impl(
        const astro::Date& startDate,
        const astro::Date& endDate,
        const std::string& name          = "",
        const unsigned& noradId          = 0,
        const bool& includeFrequencyData = false
    );

    void clean_result(nlohmann::json& result);
};

} // namespace snapshot
} // namespace astrea
```


