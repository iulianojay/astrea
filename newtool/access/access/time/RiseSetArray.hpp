#pragma once

#ifndef SWIG
#include <vector>
#endif

#include <access/time/riseset_utils.hpp>
#include <astro/time/Time.hpp>

class RiseSetArray {

  public:
    RiseSetArray() = default;
    RiseSetArray(const std::vector<Time>& risesets);
    RiseSetArray(const RiseSetArray& other);
    ~RiseSetArray() = default;

    void append(const Time& rise, const Time& set);
    void prepend(const Time& rise, const Time& set);
    void insert(const Time& rise, const Time& set);

    const size_t size() const { return risesets.size(); }

    // Element access
    const Time& operator[](const size_t& ind) const { return risesets[ind]; }

    // Union
    RiseSetArray operator|(const RiseSetArray& other) const { return riseset_union(*this, other); }

    // Intersection
    RiseSetArray operator&(const RiseSetArray& other) const { return riseset_intersection(*this, other); }

  private:
    std::vector<Time> risesets;

    void validate_riseset(const Time& rise, const Time& set) const;
    void validate_risesets(const std::vector<Time>& risesets) const;
};