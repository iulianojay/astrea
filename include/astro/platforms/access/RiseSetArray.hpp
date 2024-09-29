#pragma once

#include <array>
#include <vector>

#include "Time.hpp"

class RiseSetArray {

public:

    RiseSetArray(const std::vector<Time>& risesets);
    ~RiseSetArray();

    const size_t size() const { return risesets.size(); }

    // Element access
    const Time& operator[](const size_t& ind) const {
        return risesets[ind];
    }

    // Union
    RiseSetArray operator||(const RiseSetArray& other) const {
        return make_union(*this, other);
    }

    // Intersection
    RiseSetArray operator&&(const RiseSetArray& other) const {
        return make_intersection(*this, other);
    }

private:

    std::vector<Time> risesets;

    RiseSetArray make_union(const RiseSetArray& first, const RiseSetArray& second) const;
    RiseSetArray make_intersection(const RiseSetArray& first, const RiseSetArray& second) const;

};