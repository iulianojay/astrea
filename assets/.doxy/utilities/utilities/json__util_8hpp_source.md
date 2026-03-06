

# File json\_util.hpp

[**File List**](files.md) **>** [**astrea**](dir_b5324400686b7cece921533bb760c87a.md) **>** [**utilities**](dir_bc3eec91113c7b4aa38cf4b314cc4587.md) **>** [**utilities**](dir_e80a6df966dae334846d11eed150d587.md) **>** [**json\_util.hpp**](json__util_8hpp.md)

[Go to the documentation of this file](json__util_8hpp.md)


```C++

#pragma once

#include <iostream>
#include <optional>
#include <string>

#include <nlohmann/json.hpp>

namespace astrea {
namespace utilities {

std::string clean_entry(const nlohmann::json& entry);

template <typename T>
T extract_from_json(const nlohmann::json& json, const std::string& key)
{
    if (json.contains(key)) {
        if (json[key].empty() || json[key].is_null()) { throw std::runtime_error("Null value not allowed."); }
        else {
            T retval;
            if (json[key].is_string()) { std::stringstream(clean_entry(json[key])) >> retval; }
            else {
                retval = json[key].get<T>();
            }
            return retval;
        }
    }
    throw std::runtime_error("Key " + key + " not found.");
}

template <typename T>
std::optional<T> extract_optional_from_json(const nlohmann::json& json, const std::string& key)
{
    if (!json.contains(key) || json[key].empty() || json[key].is_null()) { return std::nullopt; }

    T retval;
    if (json[key].is_string()) { std::stringstream(clean_entry(json[key])) >> retval; }
    else {
        retval = json[key].get<T>();
    }
    return retval;
}

std::string extract_string_from_json(const nlohmann::json& json, const std::string& key);

std::optional<std::string> extract_optional_string_from_json(const nlohmann::json& json, const std::string& key);

} // namespace utilities
} // namespace astrea
```


