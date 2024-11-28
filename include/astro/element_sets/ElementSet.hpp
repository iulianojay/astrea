#pragma once

#ifndef SWIG
    #include <cstdint>
    #include <unordered_map>
    #include <string>
#else

%rename(ElementsSet) ElementSet;

#endif

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
    ElementSet(_ENUM_ x) : value(x) {}
    ElementSet(std::string xStr) : value(fromString.at(xStr)) {}

    // Assignment
#ifndef SWIG
    ElementSet& operator=(const ElementSet& x) { 
        value = x.value;
        return *this; 
    }

    // Allow switch and comparisons.
    operator _ENUM_() const { return value; }
#endif

    // Prevent usage: if(ElementSet)
    explicit operator bool() const = delete;

    // Utilities
    std::string to_string() const { return toString.at(value); }
    const char* to_char() const { return toChar.at(value); }

private:
    _ENUM_ value;
    std::unordered_map<_ENUM_, std::string> toString = {
        {COE,       "COE"},
        {CARTESIAN, "CARTESIAN"},
        {MEE,       "MEE"}
    };
    std::unordered_map<_ENUM_, const char*> toChar = {
        {COE,       "COE"},
        {CARTESIAN, "CARTESIAN"},
        {MEE,       "MEE"}
    };
    std::unordered_map<std::string, _ENUM_> fromString = {
        {"COE",       COE},
        {"CARTESIAN", CARTESIAN},
        {"MEE",       MEE}
    };
};

typedef ElementSet::_ENUM_ ElementsSet;