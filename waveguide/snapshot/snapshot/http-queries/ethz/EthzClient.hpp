#pragma once

#include <cpr/cpr.h>
#include <nlohmann/json.hpp>

#include <astro/time/Date.hpp>

namespace waveguide {
namespace snapshot {

class EthzClient {
  public:
    EthzClient() :
        _minStartDate("2023-03-10 00:00:00.0"){};
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
} // namespace waveguide