#pragma once

#include <string>

namespace snapshot {

std::string trim(const std::string& str, const std::string& whitespace = " \t");
std::string replace_all(std::string const& original, std::string const& before, std::string const& after);

} // namespace snapshot