#pragma once

#include <vector>

#include <mp-units/format.h>
#include <mp-units/ostream.h>

#include <astro/types/typedefs.hpp>

#include <access/time/riseset_utils.hpp>

namespace accesslib {

class RiseSetArray {

    friend std::ostream& operator<<(std::ostream& os, const RiseSetArray& risesets);

  public:
    RiseSetArray()  = default;
    ~RiseSetArray() = default;

    RiseSetArray(const std::vector<astro::Time>& risesets);

    // Copy constructor
    RiseSetArray(const RiseSetArray&);

    // Move constructor
    RiseSetArray(RiseSetArray&&) noexcept;

    // Move assignment operator
    RiseSetArray& operator=(RiseSetArray&&) noexcept;

    // Copy assignment operator
    RiseSetArray& operator=(const RiseSetArray&);

    // Utilities
    void append(const astro::Time& rise, const astro::Time& set);
    void prepend(const astro::Time& rise, const astro::Time& set);
    void insert(const astro::Time& rise, const astro::Time& set);

    std::size_t size() const { return _risesets.size(); }

    // Element access
    const astro::Time& operator[](const std::size_t& ind) const { return _risesets[ind]; }

    // Union
    RiseSetArray operator|(const RiseSetArray& other) const { return riseset_union(*this, other); }

    // Intersection
    RiseSetArray operator&(const RiseSetArray& other) const { return riseset_intersection(*this, other); }

    using const_iterator = std::vector<astro::Time>::const_iterator;

    const_iterator begin() const { return _risesets.begin(); }
    const_iterator end() const { return _risesets.end(); }
    const_iterator cbegin() const { return _risesets.cbegin(); }
    const_iterator cend() const { return _risesets.cend(); }

    std::vector<std::string> to_string_vector() const
    {
        std::vector<std::string> retval;
        retval.reserve(_risesets.size());
        for (const auto t : _risesets) {
            retval.push_back(to_formatted_string(t));
        }
        return retval;
    }

  private:
    std::vector<astro::Time> _risesets;

    void validate_riseset(const astro::Time& rise, const astro::Time& set) const;
    void validate_risesets(const std::vector<astro::Time>& risesets) const;

    std::string to_formatted_string(astro::Time t) const
    {
        return std::to_string(t.force_numerical_value_in(mp_units::si::unit_symbols::s));
    }
};

} // namespace accesslib