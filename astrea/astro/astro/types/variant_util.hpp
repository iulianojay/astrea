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


} // namespace astro
} // namespace astrea