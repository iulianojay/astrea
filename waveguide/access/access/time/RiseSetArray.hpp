#pragma once

#include <vector>

#include <access/time/riseset_utils.hpp>
#include <astro/types/typedefs.hpp>

namespace accesslib {

class RiseSetArray {

  public:
    RiseSetArray() = default;
    RiseSetArray(const std::vector<astro::Time>& risesets);
    RiseSetArray(const RiseSetArray& other);
    ~RiseSetArray() = default;

    void append(const astro::Time& rise, const astro::Time& set);
    void prepend(const astro::Time& rise, const astro::Time& set);
    void insert(const astro::Time& rise, const astro::Time& set);

    const std::size_t size() const { return risesets.size(); }

    // Element access
    const astro::Time& operator[](const std::size_t& ind) const { return risesets[ind]; }

    // Union
    RiseSetArray operator|(const RiseSetArray& other) const { return riseset_union(*this, other); }

    // Intersection
    RiseSetArray operator&(const RiseSetArray& other) const { return riseset_intersection(*this, other); }

  private:
    std::vector<astro::Time> risesets;

    void validate_riseset(const astro::Time& rise, const astro::Time& set) const;
    void validate_risesets(const std::vector<astro::Time>& risesets) const;
};

} // namespace accesslib