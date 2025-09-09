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
    if (json.contains(key)) {
        if (json[key].empty() || json[key].is_null()) { return std::nullopt; }
        else {
            std::string retval;
            std::getline(std::stringstream(clean_entry(json[key])), retval);
            return retval;
        }
    }
    throw std::runtime_error("Key " + key + " not found.");
}

} // namespace utilities
} // namespace astrea