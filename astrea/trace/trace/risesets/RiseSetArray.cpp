/*
 * The GNU Lesser General Public License (LGPL)
 *
 * Copyright (c) 2025 Jay Iuliano
 *
 * This file is part of Astrea.
 * Astrea is free software: you can redistribute it and/or modify it under the terms of the GNU Lesser General Public License
 * as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
 * Astrea is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty
 * of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU Lesser General Public License for more details. You should
 * have received a copy of the GNU General Public License along with Astrea. If not, see <https://www.gnu.org/licenses/>.
 */

#include <trace/risesets/RiseSetArray.hpp>

#include <stdexcept>

#include <mp-units/systems/si.h>

using mp_units::one;
using mp_units::si::unit_symbols::s;

namespace astrea {
namespace trace {

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

RiseSetArray::iterator RiseSetArray::begin() { return _risesets.begin(); }

RiseSetArray::iterator RiseSetArray::end() { return _risesets.end(); }

RiseSetArray::const_iterator RiseSetArray::begin() const { return _risesets.begin(); }

RiseSetArray::const_iterator RiseSetArray::end() const { return _risesets.end(); }

RiseSetArray::const_iterator RiseSetArray::cbegin() const { return _risesets.cbegin(); }

RiseSetArray::const_iterator RiseSetArray::cend() const { return _risesets.cend(); }

RiseSetArray& RiseSetArray::operator=(const RiseSetArray& other) { return *this = RiseSetArray(other); }

RiseSetArray RiseSetArray::operator|(const RiseSetArray& other) const { return riseset_union(*this, other); }

RiseSetArray& RiseSetArray::operator|=(const RiseSetArray& other) { return *this = riseset_union(*this, other); }

RiseSetArray RiseSetArray::operator&(const RiseSetArray& other) const { return riseset_intersection(*this, other); }

RiseSetArray& RiseSetArray::operator&=(const RiseSetArray& other) { return *this = riseset_intersection(*this, other); }

RiseSetArray RiseSetArray::operator-(const RiseSetArray& other) const { return riseset_difference(*this, other); }

RiseSetArray& RiseSetArray::operator-=(const RiseSetArray& other)
{
    *this = riseset_difference(*this, other);
    return *this;
}

Time& RiseSetArray::operator[](const std::size_t& ind) { return _risesets[ind]; }
const Time& RiseSetArray::operator[](const std::size_t& ind) const { return _risesets[ind]; }

std::size_t RiseSetArray::size() const { return _risesets.size(); }

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
    if (!_risesets.empty() && rise < _risesets.back()) {
        insert(rise, set);
        return;
    }
    validate_riseset(rise, set);

    _risesets.push_back(rise);
    _risesets.push_back(set);
}

void RiseSetArray::prepend(const Time& rise, const Time& set)
{
    if (!_risesets.empty() && set > _risesets[0]) {
        insert(rise, set);
        return;
    }
    validate_riseset(rise, set);

    _risesets.insert(_risesets.begin(), set);
    _risesets.insert(_risesets.begin(), rise);
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


Time RiseSetArray::gap(const Stat& stat, const Unitless percentile) const
{
    return calculate_statistic(stat, percentile, RisesetMetric::GAP);
}


Time RiseSetArray::access_time(const Stat& stat, const Unitless percentile) const
{
    return calculate_statistic(stat, percentile, RisesetMetric::ACCESS_TIME);
}


Time RiseSetArray::calculate_statistic(const Stat& stat, const Unitless& percentile, const RisesetMetric metric) const
{

    Time retval = 0.0 * mp_units::si::unit_symbols::s;

    // Empty
    if (_risesets.size() < 2) { return retval; }

    // Gap measures space between accesses so we can just shift the starting index
    // This value also happens to represent the difference in number of each metric type so we use it to shift
    // the array sizes for each accordingly
    std::size_t startIdx = metric == RisesetMetric::GAP ? 1 : 0;

    // Percentile calcs
    if (stat == Stat::PCT) {
        if (percentile < 0 || percentile > 1) { throw std::runtime_error("Percentile must be between 0 and 1."); }

        const double nMetricIntervals = static_cast<double>(_risesets.size() / 2 - startIdx);
        const std::size_t index = static_cast<std::size_t>(std::ceil(percentile.numerical_value_in(one) * nMetricIntervals)) - 1;

        std::vector<Time> metricTimes; // TODO: Update this so the vector is built in sorted order
        metricTimes.reserve(nMetricIntervals);
        for (std::size_t ii = startIdx; ii < _risesets.size() - 1; ii += 2) {
            metricTimes.push_back(_risesets[ii + 1] - _risesets[ii]);
        }
        std::sort(metricTimes.begin(), metricTimes.end());

        return metricTimes[index];
    }

    // Non-percentile calcs
    for (std::size_t ii = startIdx; ii < _risesets.size(); ii += 2) {
        const Time metricTime = _risesets[ii + 1] - _risesets[ii];

        if (ii == startIdx) {
            retval = metricTime;
            continue;
        }
        switch (stat) {
            case (Stat::MIN): {
                if (metricTime < retval) { retval = metricTime; }
                break;
            }
            case (Stat::MAX): {
                if (metricTime > retval) { retval = metricTime; }
                break;
            }
            case (Stat::MEAN): {
                retval += metricTime;
                break;
            }
            default: throw std::runtime_error("Unknown access time statistic requested.");
        }
    }
    if (stat == Stat::MEAN) {
        const std::size_t nMetricIntervals = _risesets.size() / 2 - startIdx;
        retval /= nMetricIntervals;
    }
    return retval;
}


std::string RiseSetArray::to_formatted_string(Time t) const
{
    std::ostringstream out;
    out.precision(1);
    out << std::fixed << t.force_numerical_value_in(mp_units::si::unit_symbols::s);
    return std::move(out).str();
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

} // namespace trace
} // namespace astrea