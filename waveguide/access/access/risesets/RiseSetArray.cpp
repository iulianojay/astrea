#include <access/risesets/RiseSetArray.hpp>

#include <stdexcept>

namespace waveguide {
namespace accesslib {

RiseSetArray::RiseSetArray(const std::vector<Time>& risesets)
{
    validate_risesets(risesets);
    _risesets = risesets;
}


RiseSetArray::RiseSetArray(const RiseSetArray& other) :
    _risesets(other._risesets)
{
}

RiseSetArray::RiseSetArray(RiseSetArray&& other) noexcept :
    _risesets(std::move(other._risesets))
{
}

RiseSetArray& RiseSetArray::operator=(RiseSetArray&& other) noexcept
{
    if (this != &other) { _risesets = std::move(other._risesets); }
    return *this;
}

bool RiseSetArray::operator==(const RiseSetArray& other) const
{
    if (this == &other) { return true; }
    return _risesets == other._risesets;
}

RiseSetArray& RiseSetArray::operator=(const RiseSetArray& other) { return *this = RiseSetArray(other); }

RiseSetArray RiseSetArray::operator|(const RiseSetArray& other) const { return riseset_union(*this, other); }

RiseSetArray RiseSetArray::operator&(const RiseSetArray& other) const { return riseset_intersection(*this, other); }

RiseSetArray RiseSetArray::operator-(const RiseSetArray& other) const { return riseset_difference(*this, other); }

RiseSetArray& RiseSetArray::operator-=(const RiseSetArray& other)
{
    *this = riseset_difference(*this, other);
    return *this;
}

void RiseSetArray::validate_risesets(const std::vector<Time>& risesets) const
{
    if (risesets.size() % 2) {
        throw std::runtime_error("RiseSetArrays must be constructed from an even-sized list of values.");
    }

    for (std::size_t ii = 1; ii < risesets.size(); ++ii) {
        validate_riseset(risesets[ii - 1], risesets[ii]);
    }
}

void RiseSetArray::validate_riseset(const Time& rise, const Time& set) const
{
    if (set < rise) { throw std::runtime_error("RiseSetArrays must be constructed from a list of ascending values."); }
    else if (set == rise) {
        throw std::runtime_error("RiseSetArrays must be constructed from a list of unique values.");
    }
}

void RiseSetArray::append(const Time& rise, const Time& set)
{
    if (size() > 0 && rise < _risesets.back()) {
        insert(rise, set);
        return;
    }
    validate_riseset(rise, set);

    _risesets.push_back(rise);
    _risesets.push_back(set);
}

void RiseSetArray::prepend(const Time& rise, const Time& set)
{
    if (set > _risesets[0]) {
        insert(rise, set);
        return;
    }
    validate_riseset(rise, set);

    _risesets.insert(_risesets.begin(), rise);
    _risesets.insert(_risesets.begin(), set);
}

void RiseSetArray::insert(const Time& rise, const Time& set)
{
    validate_riseset(rise, set);

    *this = (*this) | RiseSetArray({ rise, set });
}

std::vector<std::string> RiseSetArray::to_string_vector() const
{
    std::vector<std::string> retval;
    retval.reserve(_risesets.size());
    for (const auto t : _risesets) {
        retval.push_back(to_formatted_string(t));
    }
    return retval;
}


Time RiseSetArray::gap(const Stat& stat) const
{
    Time retval = 0.0 * mp_units::si::unit_symbols::s;

    // No gaps
    if (_risesets.size() <= 2) { return retval; }

    for (std::size_t ii = 1; ii < _risesets.size() - 1; ii += 2) {
        const Time gap = _risesets[ii + 1] - _risesets[ii];

        switch (stat) {
            case (Stat::MIN): {
                if (gap < retval) { retval = gap; }
                break;
            }
            case (Stat::MAX): {
                if (gap > retval) { retval = gap; }
                break;
            }
            case (Stat::MEAN): {
                retval += gap;
                break;
            }
            default: throw std::runtime_error("Unknown gap statistic requested.");
        }
    }
    if (stat == Stat::MEAN) {
        const std::size_t nGaps = _risesets.size() / 2 - 1;
        retval /= nGaps;
    }
    return retval;
}


Time RiseSetArray::access_time(const Stat& stat) const
{
    Time retval = 0.0 * mp_units::si::unit_symbols::s;

    // Empty
    if (_risesets.size() < 2) { return retval; }

    for (std::size_t ii = 0; ii < _risesets.size(); ii += 2) {
        const Time accessTime = _risesets[ii + 1] - _risesets[ii];

        switch (stat) {
            case (Stat::MIN): {
                if (accessTime < retval) { retval = accessTime; }
                break;
            }
            case (Stat::MAX): {
                if (accessTime > retval) { retval = accessTime; }
                break;
            }
            case (Stat::MEAN): {
                retval += accessTime;
                break;
            }
            default: throw std::runtime_error("Unknown access time statistic requested.");
        }
    }
    if (stat == Stat::MEAN) {
        const std::size_t nAccess = _risesets.size() / 2;
        retval /= nAccess;
    }
    return retval;
}


std::ostream& operator<<(std::ostream& os, const RiseSetArray& risesets)
{
    const auto& values = risesets._risesets;
    os << "[" << values[0];
    for (std::size_t ii = 1; ii < values.size(); ++ii) {
        os << ", " << values[ii];
    }
    os << "]";
    return os;
}

} // namespace accesslib
} // namespace waveguide