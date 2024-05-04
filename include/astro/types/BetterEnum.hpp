#pragma once

#include <unordered_map>
#include <string>

template <class T>
class BetterEnum
{
public:
    enum Values : uint8_t {};

    // Constructors
    BetterEnum() = default;
    constexpr BetterEnum(T x) : value(x) {}
    constexpr BetterEnum(std::string xStr) : value(fromString.at(xStr)) {}
    constexpr ~BetterEnum() {}

    // Allow switch and comparisons.
    constexpr operator Values() const { return value; }

    // Prevent usage: if(BetterEnum)
    explicit operator bool() const = delete;

    // Utilities
    constexpr std::string to_string() { return toString.at(value); }

protected:
    // Members
    Values value;
    std::unordered_map<T, std::string> toString;
    std::unordered_map<std::string, T> fromString;
};