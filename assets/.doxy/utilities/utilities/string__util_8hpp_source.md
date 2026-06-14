

# File string\_util.hpp

[**File List**](files.md) **>** [**astrea**](dir_b5324400686b7cece921533bb760c87a.md) **>** [**utilities**](dir_bc3eec91113c7b4aa38cf4b314cc4587.md) **>** [**utilities**](dir_e80a6df966dae334846d11eed150d587.md) **>** [**string\_util.hpp**](string__util_8hpp.md)

[Go to the documentation of this file](string__util_8hpp.md)


```C++

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

std::string trim(const std::string& str, const std::string& whitespace = " \t");

std::string replace_all(std::string const& original, std::string const& before, std::string const& after);

template <typename T>
std::string get_body_type_name()
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

std::vector<std::string> split(std::string s, const std::string& delimiter);

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

template <double_wrapper N, typename char_type = char>
constexpr f_to_string_t<N, char_type> f_to_string;

} // namespace utilities
} // namespace astrea
```


