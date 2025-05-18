#pragma once

#include <filesystem>

#include <cpr/cpr.h>
#include <nlohmann/json.hpp>

#include <astro/time/Date.hpp>

namespace snapshot {

class SpaceTrackClient {
  public:
    SpaceTrackClient()  = default;
    ~SpaceTrackClient() = default;

    void login(const std::string& username, const std::string& password);
    nlohmann::json query(const std::string& username, const std::string& password);

  private:
    const cpr::Url _base = "https://www.space-track.org/";

    // Login
    const cpr::Url _loginUrl = _base + "/ajaxauth/login";
    cpr::Cookies _loginCookies;

    // Query limits
    bool valid_cookies() const;
    void check_query_history(const std::string& username) const;

    nlohmann::json query_impl(const std::string& username, const std::string& password);
    void clean_result(nlohmann::json& result);
};

} // namespace snapshot