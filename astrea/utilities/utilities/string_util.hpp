/**
 * @file string_util.hpp
 * @author Jay Iuliano (iuliano.jay@gmail.com)
 * @brief String utility functions for the snapshot module
 * @date 2025-08-03
 *
 * @copyright Copyright (c) 2025-2026 Jay Iuliano
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
#if defined(_MSC_VER)
#include <dbghelp.h>
#include <windows.h>
#pragma comment(lib, "dbghelp.lib")
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
#if defined(_MSC_VER)
    static const std::string name(1024);
    // if alloc was OK then set 0 first char and use UnDecorateSymbolName
    ::UnDecorateSymbolName(typeid(T).name(), name, 1024, 0);
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

/**
 * Credit to https://github.com/tcsullivan/constexpr-to-string/tree/master for the following implementation of `f_to_string`
 */
struct double_wrapper {
    long long int whole = 0;
    long long int frac  = 0;

    constexpr double_wrapper(double v, int prec = 5)
    {
        whole = static_cast<long long int>(v);
        v -= whole;
        for (int i = 0; i < prec; i++)
            v *= 10;
        frac = static_cast<long long int>(v);
    }
};

/**
 * @struct f_to_string_t
 * @brief Provides the ability to convert a floating-point number to a string at compile-time.
 * @tparam N Number to convert
 */
template <double_wrapper N, typename char_type>
class f_to_string_t {
    char_type buf[([]() constexpr noexcept {
        unsigned int len = 2;
        if (N.whole <= 0) len++;
        for (auto n = N.whole; n; len++, n /= 10)
            ;
        if (N.frac == 0 || (N.whole == 0 && N.frac < 0)) len++;
        for (auto n = N.frac; n; len++, n /= 10)
            ;
        return len;
    }())] = {};

  public:
    /**
     * Constructs the object, filling `buf` with the string representation of N.
     */
    constexpr f_to_string_t() noexcept
    {
        auto append = [](auto V, auto& ptr) {
            if (V != 0) {
                for (auto n = V; n; n /= 10)
                    *--ptr = (V < 0 ? -1 : 1) * (n % 10) + '0';
            }
            else {
                *--ptr = '0';
            }
        };

        auto ptr = end();
        *--ptr   = '\0';
        append(N.frac, ptr);
        *--ptr = '.';
        append(N.whole, ptr);
        if (N.frac < 0 || N.whole < 0) *--ptr = '-';
    }

    // Support implicit casting to `char *` or `const char *`.
    constexpr operator char_type*() noexcept { return buf; }
    constexpr operator const char_type*() const noexcept { return buf; }

    constexpr auto size() const noexcept { return sizeof(buf) / sizeof(buf[0]); }
    // Element access
    constexpr auto data() noexcept { return buf; }
    constexpr auto data() const noexcept { return buf; }
    constexpr auto& operator[](unsigned int i) noexcept { return buf[i]; }
    constexpr const auto& operator[](unsigned int i) const noexcept { return buf[i]; }
    constexpr auto& front() noexcept { return buf[0]; }
    constexpr const auto& front() const noexcept { return buf[0]; }
    constexpr auto& back() noexcept { return buf[size() - 1]; }
    constexpr const auto& back() const noexcept { return buf[size() - 1]; }
    // Iterators
    constexpr auto begin() noexcept { return buf; }
    constexpr auto begin() const noexcept { return buf; }
    constexpr auto end() noexcept { return buf + size(); }
    constexpr auto end() const noexcept { return buf + size(); }
};

/**
 * Simplifies use of `f_to_string_t` from `f_to_string_t<N>()` to `f_to_string<N>`.
 */
template <double_wrapper N, typename char_type = char>
constexpr f_to_string_t<N, char_type> f_to_string;

} // namespace utilities
} // namespace astrea