#pragma once

#include <iostream>
#include <optional>
#include <string>

#include <nlohmann/json.hpp>

namespace astrea {
namespace utilities {

/**
 * @brief Cleans a JSON entry by removing quotes and returning it as a string.
 *
 * @param entry The JSON entry to clean.
 * @return A cleaned string without quotes.
 */
std::string clean_entry(const nlohmann::json& entry);

/**
 * @brief Extracts a value of type T from a JSON object using the specified key.
 *
 * @tparam T The type of the value to extract.
 * @param json The JSON object to extract from.
 * @param key The key to look for in the JSON object.
 * @return The extracted value of type T.
 * @throws std::runtime_error if the key is not found or if the value is null.
 */
template <typename T>
T extract_from_json(const nlohmann::json& json, const std::string& key)
{
    if (json.contains(key)) {
        if (json[key].empty() || json[key].is_null()) { throw std::runtime_error("Null value not allowed."); }
        else {
            T retval;
            std::stringstream(clean_entry(json[key])) >> retval;
            return retval;
        }
    }
    throw std::runtime_error("Key " + key + " not found.");
}

/**
 * @brief Extracts an optional value of type T from a JSON object using the specified key.
 *
 * @tparam T The type of the value to extract.
 * @param json The JSON object to extract from.
 * @param key The key to look for in the JSON object.
 * @return An std::optional containing the extracted value, or std::nullopt if the key is not found or the value is null.
 * @throws std::runtime_error if the key is not found.
 */
template <typename T>
std::optional<T> extract_optional_from_json(const nlohmann::json& json, const std::string& key)
{
    if (json.contains(key)) {
        if (json[key].empty() || json[key].is_null()) { return std::nullopt; }
        else {
            T retval;
            const std::string output = clean_entry(json[key]);
            std::stringstream(output) >> retval;
            return retval;
        }
    }
    throw std::runtime_error("Key " + key + " not found.");
}

/**
 * @brief Extracts a string value from a JSON object using the specified key.
 *
 * @param json The JSON object to extract from.
 * @param key The key to look for in the JSON object.
 * @return The extracted string value.
 * @throws std::runtime_error if the key is not found or if the value is null.
 */
std::string extract_string_from_json(const nlohmann::json& json, const std::string& key);

/**
 * @brief Extracts an optional string value from a JSON object using the specified key.
 *
 * @param json The JSON object to extract from.
 * @param key The key to look for in the JSON object.
 * @return An std::optional containing the extracted string value, or std::nullopt if the key is not found or the value is null.
 * @throws std::runtime_error if the key is not found.
 */
std::optional<std::string> extract_optional_string_from_json(const nlohmann::json& json, const std::string& key);

} // namespace utilities
} // namespace astrea