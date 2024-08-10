#pragma once

#include <frozen/unordered_map.h>
#include <frozen/string.h>

class ElementSet
{
public:
    enum _ENUM_ : uint8_t {
        COE,
        CARTESIAN,
        MEE
    };

    // Constructors
    ElementSet() = default;
    constexpr ElementSet(_ENUM_ x) : value(x) {}
    constexpr ElementSet(frozen::string xStr) : value(fromString.at(xStr)) {}

    // Assignment
    constexpr ElementSet& operator=(const ElementSet& x) { 
        value = x.value;
        return *this; 
    }

    // Allow switch and comparisons.
    constexpr operator _ENUM_() const { return value; }

    // Prevent usage: if(ElementSet)
    explicit operator bool() const = delete;

    // Utilities
    frozen::string to_string() const { return toString.at(value); }
    const char* to_char() const { return toChar.at(value); }

private:
    _ENUM_ value;
    frozen::unordered_map<_ENUM_, frozen::string, 3> toString = {
        {COE,       "COE"},
        {CARTESIAN, "CARTESIAN"},
        {MEE,       "MEE"}
    };
    frozen::unordered_map<_ENUM_, const char*, 3> toChar = {
        {COE,       "COE"},
        {CARTESIAN, "CARTESIAN"},
        {MEE,       "MEE"}
    };
    frozen::unordered_map<frozen::string, _ENUM_, 3> fromString = {
        {"COE",       COE},
        {"CARTESIAN", CARTESIAN},
        {"MEE",       MEE}
    };
};