

# File json\_util.cpp

[**File List**](files.md) **>** [**astrea**](dir_b5324400686b7cece921533bb760c87a.md) **>** [**utilities**](dir_bc3eec91113c7b4aa38cf4b314cc4587.md) **>** [**utilities**](dir_e80a6df966dae334846d11eed150d587.md) **>** [**json\_util.cpp**](json__util_8cpp.md)

[Go to the documentation of this file](json__util_8cpp.md)


```C++
/*
 * The GNU Lesser General Public License (LGPL)
 *
 * Copyright (c) 2025-2026 Jay Iuliano
 *
 * This file is part of Astrea.
 * Astrea is free software: you can redistribute it and/or modify it under the terms of the GNU Lesser General Public License
 * as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
 * Astrea is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty
 * of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU Lesser General Public License for more details. You should
 * have received a copy of the GNU General Public License along with Astrea. If not, see <https://www.gnu.org/licenses/>.
 */

#include <utilities/json_util.hpp>

namespace astrea {
namespace utilities {

std::string clean_entry(const nlohmann::json& entry)
{
    std::string entryStr = entry.template get<std::string>();
    entryStr.erase(std::remove(entryStr.begin(), entryStr.end(), '"'), entryStr.end());
    return entryStr;
}

std::string extract_string_from_json(const nlohmann::json& json, const std::string& key)
{
    if (json.contains(key)) {
        if (json[key].empty() || json[key].is_null()) { throw std::runtime_error("Null value not allowed."); }
        else {
            std::string retval;
            std::getline(std::stringstream(clean_entry(json[key])), retval);
            return retval;
        }
    }
    throw std::runtime_error("Key " + key + " not found.");
}

std::optional<std::string> extract_optional_string_from_json(const nlohmann::json& json, const std::string& key)
{
    if (!json.contains(key) || json[key].empty() || json[key].is_null()) { return std::nullopt; }

    std::string retval;
    std::getline(std::stringstream(clean_entry(json[key])), retval);
    return retval;
}

} // namespace utilities
} // namespace astrea
```


