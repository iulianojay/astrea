#include "RiseSetArray.hpp"

#include <stdexcept>

RiseSetArray::RiseSetArray(const std::vector<Time>& _risesets) {
    validate_risesets(_risesets);
    risesets = _risesets;
}

RiseSetArray::RiseSetArray(const RiseSetArray& other) {
    // other must already be validated
    risesets = other.risesets;
}

void RiseSetArray::validate_risesets(const std::vector<Time>& _risesets) const {
    if (risesets.size() % 2) {
        throw std::runtime_error("RiseSetArrays must be constructed from an even-sized list of values.");
    }

    for (size_t ii = 1; ii < _risesets.size(); ++ii) {
        validate_riseset(_risesets[ii-1], _risesets[ii]);
    }
}

void RiseSetArray::validate_riseset(const Time& rise, const Time& set) const {
    if (set < rise) {
        throw std::runtime_error("RiseSetArrays must be constructed from a list of ascending values.");
    }
    else if (set == rise) {
        throw std::runtime_error("RiseSetArrays must be constructed from a list of unique values.");
    }
}

void RiseSetArray::append(const Time& rise, const Time& set) {
    if (rise < risesets[size()-1]) {
        insert(rise, set);
        return;
    }
    validate_riseset(rise, set);

    risesets.push_back(rise);
    risesets.push_back(set);
}

void RiseSetArray::prepend(const Time& rise, const Time& set) {
    if (set > risesets[0]) {
        insert(rise, set);
        return;
    }
    validate_riseset(rise, set);

    risesets.insert(risesets.begin(), rise);
    risesets.insert(risesets.begin(), set);
}

void RiseSetArray::insert(const Time& rise, const Time& set) {
    validate_riseset(rise, set);

    *this = (*this) | RiseSetArray({rise, set});
}