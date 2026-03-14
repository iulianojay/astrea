/**
 * @file string_util.hpp
 * @author Jay Iuliano (iuliano.jay@gmail.com)
 * @brief String utility functions for the snapshot module
 * @date 2025-08-03
 *
 * @copyright Copyright (c) 2025 Jay Iuliano
 *
 * The GNU Lesser General Public License (LGPL)
 *
 * This file is part of Astrea.
 * Astrea is free software: you can redistribute it and/or modify it under the terms of the GNU Lesser General Public License
 * as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
 * Astrea is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty
 * of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU Lesser General Public License for more details. You should
 * have received a copy of the GNU General Public License along with Astrea. If not, see <https://www.gnu.org/licenses/>.
 *
 */
#pragma once

#include <algorithm>
#include <cstdlib>
#include <cstring>
#if defined ( _MSC_VER )
#include <windows.h> 
#include <dbghelp.h>
#pragma comment(lib,"dbghelp.lib")     
#else
#include <cxxabi.h>
#endif
#include <iostream>
#include <memory>
#include <optional>
#include <string>
#include <type_traits>
#include <vector>

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

/**
 * @brief Gets the demangled(ish) type name of a given type.
 *
 * @tparam T The type to get the name of.
 * @return The demangled type name as a string.
 */
template <typename T>
std::string get_type_name()
{
    #if defined( _MSC_VER )
    static const std::string name(1024);
    //if alloc was OK then set 0 first char and use UnDecorateSymbolName
    ::UnDecorateSymbolName(typeid(T).name(), name, 1024, 0) ;
    #else
    static int status;
    static const std::string fullName = abi::__cxa_demangle(typeid(T).name(), NULL, NULL, &status);
    static const std::string name     = fullName.substr(fullName.find_last_of("::") + 1);
    #endif
    return name;
}

/**
 * @brief Splits a string into a vector of substrings based on a delimiter.
 *
 * @param s The string to split.
 * @param delimiter The delimiter to split by.
 * @return A vector of substrings.
 *
 * @note Taken from https://stackoverflow.com/questions/14265581/parse-split-a-string-in-c-using-string-delimiter-standard-c
 */
std::vector<std::string> split(std::string s, const std::string& delimiter);

} // namespace utilities
} // namespace astrea