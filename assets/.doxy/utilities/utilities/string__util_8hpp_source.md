

# File string\_util.hpp

[**File List**](files.md) **>** [**astrea**](dir_b5324400686b7cece921533bb760c87a.md) **>** [**utilities**](dir_bc3eec91113c7b4aa38cf4b314cc4587.md) **>** [**utilities**](dir_e80a6df966dae334846d11eed150d587.md) **>** [**string\_util.hpp**](string__util_8hpp.md)

[Go to the documentation of this file](string__util_8hpp.md)


```C++

#pragma once

#include <algorithm>
#include <cstdlib>
#include <cstring>
#include <cxxabi.h>
#include <iostream>
#include <memory>
#include <optional>
#include <string>
#include <type_traits>
#include <vector>

namespace astrea {
namespace utilities {

std::string trim(const std::string& str, const std::string& whitespace = " \t");

std::string replace_all(std::string const& original, std::string const& before, std::string const& after);

template <typename T>
std::string get_type_name()
{
    static int status;
    static const std::string fullName = abi::__cxa_demangle(typeid(T).name(), NULL, NULL, &status);
    static const std::string name     = fullName.substr(fullName.find_last_of("::") + 1);
    return name;
}

std::vector<std::string> split(std::string s, const std::string& delimiter);

} // namespace utilities
} // namespace astrea
```


