/*
 * The GNU Lesser General Public License (LGPL)
 *
 * Copyright (c) 2025 Jay Iuliano
 *
 * This file is part of Astrea.
 * Astrea is free software: you can redistribute it and/or modify it under the terms of the GNU Lesser General Public License
 * as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
 * Astrea is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty
 * of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU Lesser General Public License for more details. You should
 * have received a copy of the GNU General Public License along with Astrea. If not, see <https://www.gnu.org/licenses/>.
 */

#include <fstream>
#include <iostream>
#include <string>

#include <nlohmann/json.hpp>

#include <trace/analysis/analysis.hpp>
#include <trace/trace.hpp>

using namespace astrea;
using namespace trace;

int main(int argc, char* argv[])
{
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " <config.json>\n";
        return 1;
    }

    const std::string path = argv[1];
    std::ifstream f(path);
    if (!f) {
        std::cerr << "Error: cannot open config file: " << path << "\n";
        return 1;
    }

    TraceConfig config;
    try {
        config = TraceConfig(nlohmann::json::parse(f));
    }
    catch (const std::exception& e) {
        std::cerr << "Error: JSON parse error in " << path << ": " << e.what() << "\n";
        return 1;
    }

    const auto result = run_trace_analysis(config);

    return 0;
}
