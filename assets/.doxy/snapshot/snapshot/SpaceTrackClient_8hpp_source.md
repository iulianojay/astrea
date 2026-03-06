

# File SpaceTrackClient.hpp

[**File List**](files.md) **>** [**astrea**](dir_b5324400686b7cece921533bb760c87a.md) **>** [**snapshot**](dir_ad01b7a66bf2103e1e551598d7ba094a.md) **>** [**snapshot**](dir_d7d302d432d8a6ab561803ec6eec1eed.md) **>** [**http-queries**](dir_e3fe50636e6aa25df3bf26a0e7917672.md) **>** [**spacetrack**](dir_ebf022e0144e875932c7cae0921ab822.md) **>** [**SpaceTrackClient.hpp**](SpaceTrackClient_8hpp.md)

[Go to the documentation of this file](SpaceTrackClient_8hpp.md)


```C++

#pragma once

#include <filesystem>
#include <variant>

#include <cpr/cpr.h>
#include <nlohmann/json.hpp>

#include <astro/time/Date.hpp>

#include <snapshot/types/typedefs.hpp>

namespace astrea {
namespace snapshot {

class SpaceTrackClient {
  public:
    enum class Controller : EnumType {
        BASIC_SPACE_DATA, 
        // EXPANDED_SPACE_DATA, //!< USSPACECOM SSA Sharing Agreements
        // FILE_SHARE,          //!< Permission Controlled
        // COMBINED_OPS_DATA,   //!< Permission Controlled
        PUBLIC_FILES 
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

    enum class PublicFilesClass : EnumType {
        DIRS,            
        DOWNLOAD,        
        FILES,           
        LOAD_PUBLIC_DATA 
    };

    using RequestClass = std::variant<SpaceDataClass, PublicFilesClass>;

    SpaceTrackClient() = default;

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
} // namespace astrea
```


