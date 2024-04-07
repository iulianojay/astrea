#pragma once

#include <frozen/unordered_map.h>
#include <frozen/string.h>

class ElementSet
{
public:
    enum Values : uint8_t {
        COE,
        CARTESIAN
    };

    // Constructors
    ElementSet() = default;
    constexpr ElementSet(Values x) : value(x) {}
    constexpr ElementSet(frozen::string xStr) : value(fromString.at(xStr)) {}

    // Assignment
    constexpr const ElementSet operator=(const ElementSet& x) { return ElementSet(value); }

    // Allow switch and comparisons.
    constexpr operator Values() const { return value; }

    // Prevent usage: if(ElementSet)
    explicit operator bool() const = delete;

    // Utilities
    constexpr frozen::string to_string() const { return toString.at(value); }

private:
    Values value;
    frozen::unordered_map<Values, frozen::string, 2> toString = {
        {COE,       "COE"},
        {CARTESIAN, "CARTESIAN"}
    };
    frozen::unordered_map<frozen::string, Values, 2> fromString = {
        {"COE",       COE},
        {"CARTESIAN", CARTESIAN}
    };
};