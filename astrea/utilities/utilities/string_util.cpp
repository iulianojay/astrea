/*
 * Copyright (c) 2025 Jay Iuliano
 *
 * This file is part of Astrea.
 * Astrea is free software: you can redistribute it and/or modify it under the terms of the GNU Lesser General Public License
 * as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
 * Astrea is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty
 * of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU Lesser General Public License for more details. You should
 * have received a copy of the GNU General Public License along with Astrea. If not, see <https://www.gnu.org/licenses/>.
 */

#include <utilities/string_util.hpp>

#include <algorithm>

namespace astrea {
namespace utilities {

std::string trim(const std::string& str, const std::string& whitespace)
{
    const auto strBegin = str.find_first_not_of(whitespace);
    if (strBegin == std::string::npos) return ""; // no content

    const auto strEnd   = str.find_last_not_of(whitespace);
    const auto strRange = strEnd - strBegin + 1;

    return str.substr(strBegin, strRange);
}

std::string replace_all(std::string const& original, std::string const& before, std::string const& after)
{
    std::string retval;
    std::string::const_iterator end     = original.end();
    std::string::const_iterator current = original.begin();
    std::string::const_iterator next    = std::search(current, end, before.begin(), before.end());
    while (next != end) {
        retval.append(current, next);
        retval.append(after);
        current = next + before.size();
        next    = std::search(current, end, before.begin(), before.end());
    }
    retval.append(current, next);
    return retval;
}

} // namespace utilities
} // namespace astrea