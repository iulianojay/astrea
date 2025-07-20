#pragma once

#include <filesystem>
#include <variant>

#include <cpr/cpr.h>
#include <nlohmann/json.hpp>

#include <astro/time/Date.hpp>

#include <snapshot/types/typedefs.hpp>

namespace waveguide {
namespace snapshot {

// WARNING: Do NOT use this for automated scripts. I have NOT setup a check to make sure we're
// within the automated script limits and you could get your SpaceTrack account banned.
class SpaceTrackClient {
  public:
    enum class Controller : EnumType {
        BASIC_SPACE_DATA, // Public
        // EXPANDED_SPACE_DATA, // USSPACECOM SSA Sharing Agreements
        // FILE_SHARE,          // Permission Controlled
        // COMBINED_OPS_DATA,   // Permission Controlled
        PUBLIC_FILES // Public
    };

    enum class Action : EnumType {
        QUERY,
        MODEL_DEF,
    };

    enum class SpaceDataClass : EnumType {
        ANNOUNCEMENT,
        BOX_SCORE,
        CDM_PUBLIC,
        DECAY,
        GP,
        GP_HISTORY,
        LAUNCH_SITE,
        SATCAT,
        SATCAT_CHANGE,
        SATCAT_DEBUT,
        TIP
    };

    enum class PublicFilesClass : EnumType { DIRS, DOWNLOAD, FILES, LOAD_PUBLIC_DATA };

    using RequestClass = std::variant<SpaceDataClass, PublicFilesClass>;

    SpaceTrackClient()  = default;
    ~SpaceTrackClient() = default;

    void login(const std::string& username, const std::string& password);
    nlohmann::json query(
        const std::string& username,
        const std::string& password,
        const Controller& controller                                      = Controller::BASIC_SPACE_DATA,
        const Action& action                                              = Action::QUERY,
        const RequestClass& requestClass                                  = SpaceDataClass::GP,
        const std::vector<std::pair<std::string, std::string>> predicates = {}
    );

    nlohmann::json retrieve_all(const std::string& username, const std::string& password);

  private:
    const cpr::Url _base = "https://www.space-track.org";

    // Login
    const cpr::Url _loginUrl = _base + "/ajaxauth/login";
    cpr::Cookies _loginCookies;

    // Query limits
    bool valid_cookies() const;
    void check_query_history(const std::string& username) const;

    std::string controller_to_string(const Controller& controller) const;
    std::string action_to_string(const Action& action) const;
    std::string class_to_string(const RequestClass& requestClass) const;
    std::string class_to_string(const SpaceDataClass& requestClass) const;
    std::string class_to_string(const PublicFilesClass& requestClass) const;

    cpr::Url build_query_url(
        const Controller& controller,
        const Action& action,
        const RequestClass& requestClass,
        const std::vector<std::pair<std::string, std::string>> predicates
    ) const;

    nlohmann::json query_impl(const std::string& username, const std::string& password, cpr::Url queryUrl);
};

} // namespace snapshot
} // namespace waveguide