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

    std::size_t size() const;

    // Element access
    Time& operator[](const std::size_t& ind); // TODO: Should this be allowed? Makes it possible to generate bad rise/set pairs
    const Time& operator[](const std::size_t& ind) const;

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
    using iterator       = std::vector<Time>::iterator;
    using const_iterator = std::vector<Time>::const_iterator;

    iterator begin();
    iterator end();
    const_iterator begin() const;
    const_iterator end() const;
    const_iterator cbegin() const;
    const_iterator cend() const;

    std::vector<std::string> to_string_vector() const;

  private:
    std::vector<Time> _risesets;

    void validate_riseset(const Time& rise, const Time& set) const;
    void validate_risesets(const std::vector<Time>& risesets) const;

    std::string to_formatted_string(Time t) const;
};

} // namespace accesslib
} // namespace waveguide