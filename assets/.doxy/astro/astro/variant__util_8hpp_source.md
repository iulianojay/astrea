

# File variant\_util.hpp

[**File List**](files.md) **>** [**astrea**](dir_b5324400686b7cece921533bb760c87a.md) **>** [**astro**](dir_1d4dcf10fc541574a93624f5c09a3d6f.md) **>** [**astro**](dir_84db6e3c60e44147f5214c05dc45afc2.md) **>** [**types**](dir_81b398d2ba04cf47420d9ac22d356bcf.md) **>** [**variant\_util.hpp**](variant__util_8hpp.md)

[Go to the documentation of this file](variant__util_8hpp.md)


```C++

#pragma once

#include <variant>

namespace astrea {
namespace astro {


template <typename VariantType, typename T, std::size_t index = 0>
constexpr std::size_t get_variant_index()
{
    static_assert(std::variant_size_v<VariantType> > index, "Type not found in variant");
    if constexpr (index == std::variant_size_v<VariantType>) { return index; }
    else if constexpr (std::is_same_v<std::variant_alternative_t<index, VariantType>, T>) {
        return index;
    }
    else {
        return get_variant_index<VariantType, T, index + 1>();
    }
}

template <typename VariantType, typename T, std::size_t index = 0>
constexpr bool variant_contains()
{
    if constexpr (index == std::variant_size_v<VariantType>) { return false; }
    else if constexpr (std::is_same_v<std::variant_alternative_t<index, VariantType>, T>) {
        return true;
    }
    else {
        return variant_contains<VariantType, T, index + 1>();
    }
}


} // namespace astro
} // namespace astrea
```


