#include <snapshot/utilities/string_util.hpp>

#include <algorithm>

namespace waveguide {
namespace snapshot {

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

} // namespace snapshot
} // namespace waveguide