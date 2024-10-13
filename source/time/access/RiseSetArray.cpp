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
        if (_risesets[ii] < _risesets[ii-1]) {
            throw std::runtime_error("RiseSetArrays must be constructed from a list of ascending values.");
        }
        else if (_risesets[ii] == _risesets[ii-1]) {
            throw std::runtime_error("RiseSetArrays must be constructed from a list of unique values.");
        }
    }
}