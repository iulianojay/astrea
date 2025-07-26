#pragma once

#include <vector>

#include <mp-units/format.h>
#include <mp-units/ostream.h>

#include <units/units.hpp>

#include <access/risesets/riseset_utils.hpp>

namespace waveguide {
namespace accesslib {

enum class Stat { MIN, MEAN, MAX };

class RiseSetArray {

    friend std::ostream& operator<<(std::ostream& os, const RiseSetArray& risesets);

  public:
    RiseSetArray()  = default;
    ~RiseSetArray() = default;

    RiseSetArray(const std::vector<Time>& risesets);

    // Copy constructor
    RiseSetArray(const RiseSetArray&);

    // Move constructor
    RiseSetArray(RiseSetArray&&) noexcept;

    // Move assignment operator
    RiseSetArray& operator=(RiseSetArray&&) noexcept;

    // Copy assignment operator
    RiseSetArray& operator=(const RiseSetArray&);

    // Utilities
    void append(const Time& rise, const Time& set);
    void prepend(const Time& rise, const Time& set);
    void insert(const Time& rise, const Time& set);

    std::size_t size() const { return _risesets.size(); }

    // Element access
    Time& operator[](const std::size_t& ind) { return _risesets[ind]; }
    const Time& operator[](const std::size_t& ind) const { return _risesets[ind]; }

    // Equality
    bool operator==(const RiseSetArray& other) const;

    // Difference
    RiseSetArray operator-(const RiseSetArray& other) const;
    RiseSetArray& operator-=(const RiseSetArray& other);

    // Union
    RiseSetArray operator|(const RiseSetArray& other) const;

    // Intersection
    RiseSetArray operator&(const RiseSetArray& other) const;

    // Calcs
    Time gap(const Stat& stat = Stat::MEAN) const;
    Time access_time(const Stat& stat = Stat::MEAN) const;

    // Iterators
    using const_iterator = std::vector<Time>::const_iterator;

    const_iterator begin() const { return _risesets.begin(); }
    const_iterator end() const { return _risesets.end(); }
    const_iterator cbegin() const { return _risesets.cbegin(); }
    const_iterator cend() const { return _risesets.cend(); }

    std::vector<std::string> to_string_vector() const;

  private:
    std::vector<Time> _risesets;

    void validate_riseset(const Time& rise, const Time& set) const;
    void validate_risesets(const std::vector<Time>& risesets) const;

    std::string to_formatted_string(Time t) const
    {
        std::ostringstream out;
        out.precision(1);
        out << std::fixed << t.force_numerical_value_in(mp_units::si::unit_symbols::s);
        return std::move(out).str();
    }
};

} // namespace accesslib
} // namespace waveguide