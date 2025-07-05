#include <access/time/RiseSetArray.hpp>

#include <stdexcept>

using astro::Time;

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

RiseSetArray& RiseSetArray::operator=(const RiseSetArray& other) { return *this = RiseSetArray(other); }

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
    if (rise < _risesets[size() - 1]) {
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

} // namespace accesslib