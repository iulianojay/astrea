

# File IdProvider.hpp

[**File List**](files.md) **>** [**astrea**](dir_b5324400686b7cece921533bb760c87a.md) **>** [**utilities**](dir_bc3eec91113c7b4aa38cf4b314cc4587.md) **>** [**utilities**](dir_e80a6df966dae334846d11eed150d587.md) **>** [**IdProvider.hpp**](IdProvider_8hpp.md)

[Go to the documentation of this file](IdProvider_8hpp.md)


```C++

#pragma once

#include <atomic>

#include <mp-units/framework/symbol_text.h>

namespace astrea {
namespace utilities {

class IdProvider {
  public:
    IdProvider() = delete;

    template <mp_units::symbol_text name>
    static std::size_t get_next_id()
    {
        static std::atomic<std::size_t> _idCounter{ 0 };
        return _idCounter++;
    }
};

} // namespace utilities
} // namespace astrea
```


