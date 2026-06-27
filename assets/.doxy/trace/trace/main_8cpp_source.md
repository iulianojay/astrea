

# File main.cpp

[**File List**](files.md) **>** [**astrea**](dir_b5324400686b7cece921533bb760c87a.md) **>** [**trace**](dir_e30098dbada9bbfb44888190c04e2af0.md) **>** [**trace**](dir_f04035ba8afac2675c737f654641e7b5.md) **>** [**drivers**](dir_ede4f445fc3b272c23592e211659caf8.md) **>** [**main.cpp**](main_8cpp.md)

[Go to the documentation of this file](main_8cpp.md)


```C++
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
        std::cerr << "[trace] Usage: " << argv[0] << " <config.json>\n";
        return 1;
    }

    const std::string path = argv[1];
    std::ifstream f(path);
    if (!f) {
        std::cerr << "[trace] Error: cannot open config file: " << path << "\n";
        return 1;
    }

    TraceConfig config;
    try {
        config = TraceConfig(nlohmann::json::parse(f));
    }
    catch (const std::exception& e) {
        std::cerr << "[trace] Error: JSON parse error in " << path << ": " << e.what() << "\n";
        return 1;
    }

    const auto result = run_trace_analysis(config);

    return 0;
}
```


