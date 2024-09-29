#include "RiseSetArray.hpp"

#include <stdexcept>

RiseSetArray::RiseSetArray(const std::vector<Time>& _risesets) {
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

    risesets = _risesets;
}

RiseSetArray RiseSetArray::make_union(const RiseSetArray& first, const RiseSetArray& second) const {

}

RiseSetArray RiseSetArray::make_intersection(const RiseSetArray& first, const RiseSetArray& second) const {

}