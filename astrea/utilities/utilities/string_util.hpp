/**
 * @file string_util.hpp
 * @author Jay Iuliano (iuliano.jay@gmail.com)
 * @brief String utility functions for the snapshot module
 * @version 0.1
 * @date 2025-08-03
 *
 * @copyright Copyright (c) 2025
 *
 */
#pragma once

#include <cstdlib>
#include <cxxabi.h>
#include <string>

namespace astrea {
namespace utilities {

/**
 * @brief Trims whitespace from both ends of a string.
 *
 * @param str The string to trim.
 * @param whitespace The characters to trim (default is space and tab).
 * @return A trimmed string.
 */
std::string trim(const std::string& str, const std::string& whitespace = " \t");

/**
 * @brief Replaces all occurrences of a substring with another substring in a string.
 *
 * @param original The original string.
 * @param before The substring to be replaced.
 * @param after The substring to replace with.
 * @return A new string with all occurrences replaced.
 */
std::string replace_all(std::string const& original, std::string const& before, std::string const& after);

template <typename T>
std::string get_type_name()
{
    static int status;
    static const std::string fullName = abi::__cxa_demangle(typeid(T).name(), NULL, NULL, &status);
    static const std::string name     = fullName.substr(fullName.find_last_of("::") + 1);
    return name;
}

} // namespace utilities
} // namespace astrea