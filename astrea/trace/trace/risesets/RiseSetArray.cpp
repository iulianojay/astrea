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

#include <limits>
#include <stdexcept>

#include <mp-units/math.h>
#include <mp-units/systems/iau.h>
#include <mp-units/systems/si.h>

using namespace mp_units;
using mp_units::non_si::day;
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


Time RiseSetArray::gap(const StatType& stat, const Unitless percentile) const
{
    return calculate_statistic(stat, percentile, RiseSetMetric::GAP);
}


std::vector<Time> RiseSetArray::get_gap_times() const
{
    std::vector<Time> gaps;
    gaps.reserve(_risesets.size() / 2 - 1);
    for (std::size_t ii = 1; ii < _risesets.size() - 1; ii += 2) {
        gaps.push_back(_risesets[ii + 1] - _risesets[ii]);
    }
    return gaps;
}


Time RiseSetArray::access_time(const StatType& stat, const Unitless percentile) const
{
    return calculate_statistic(stat, percentile, RiseSetMetric::ACCESS_TIME);
}


std::vector<Time> RiseSetArray::get_access_times() const
{
    std::vector<Time> accesses;
    accesses.reserve(_risesets.size() / 2);
    for (std::size_t ii = 0; ii < _risesets.size() - 1; ii += 2) {
        accesses.push_back(_risesets[ii + 1] - _risesets[ii]);
    }
    return accesses;
}


Time RiseSetArray::average_daily_vis_time() const
{
    // good luck parsing this jumbled mess
    Time avgDailyVisTime       = 0.0 * s;
    std::size_t ii             = 0;
    unsigned iDay              = 0;
    bool accessCrossesMidnight = false;
    while (ii < _risesets.size() - 1) {
        Time dailyVisTime = 0.0 * s;
        for (; ii < _risesets.size() - 1; ii += 2) {
            Time start = _risesets[ii];
            if (accessCrossesMidnight) {
                start                 = Time(days(iDay - 1));
                accessCrossesMidnight = false;
            }
            Time end = _risesets[ii + 1];
            if (end > Time(days(iDay))) {
                end                   = Time(days(iDay));
                accessCrossesMidnight = true;
            }
            dailyVisTime += end - start;
            if (accessCrossesMidnight) { break; }
        }
        avgDailyVisTime += dailyVisTime;
        ++iDay;
    }
    return avgDailyVisTime / (iDay - 1);
}


Time RiseSetArray::mean_time_to_access() const
{
    quantity mtta = 0.0 * s * s;
    for (const auto& gap : get_gap_times()) {
        mtta += gap * gap;
    }
    return sqrt(mtta) * 0.5;
}


Time RiseSetArray::calculate_statistic(const StatType& stat, const Unitless& percentile, const RiseSetMetric metric) const
{
    // TODO: Is this a good default value? Is it necessarily meaningless or should it be negative or error?
    Time retval = 0.0 * s;

    // Gap measures space between accesses so we can just shift the starting index
    // This value also happens to represent the difference in number of each metric type so we use it to shift
    // the array sizes for each accordingly
    std::size_t idxOffset = metric == RiseSetMetric::GAP ? 1 : 0;

    // Empty or not enough risesets for any gap
    if (_risesets.size() < 2 + idxOffset) { return retval; }

    // Percentile calcs
    if (stat == StatType::PCT) {
        if (percentile < 0 * one || percentile > 1 * one) {
            throw std::runtime_error("Percentile must be between 0 and 1.");
        }

        const double nMetricIntervals = static_cast<double>(_risesets.size() / 2 - idxOffset);
        const std::size_t index = static_cast<std::size_t>(std::ceil(percentile.numerical_value_in(one) * nMetricIntervals)) - 1;

        std::vector<Time> durations; // TODO: Update this so the vector is built in sorted order
        durations.reserve(nMetricIntervals);
        for (std::size_t ii = idxOffset; ii < _risesets.size() - 1; ii += 2) {
            durations.push_back(_risesets[ii + 1] - _risesets[ii]);
        }
        std::sort(durations.begin(), durations.end());

        return durations[index];
    }

    // Non-percentile calcs
    if (stat == StatType::MIN) { retval = std::numeric_limits<double>::max() * s; }
    for (std::size_t ii = idxOffset; ii < _risesets.size() - 1; ii += 2) {
        const Time duration = _risesets[ii + 1] - _risesets[ii];

        if (ii == idxOffset) {
            retval = duration;
            continue;
        }
        switch (stat) {
            case (StatType::MIN): {
                if (duration < retval) { retval = duration; }
                break;
            }
            case (StatType::MAX): {
                if (duration > retval) { retval = duration; }
                break;
            }
            case (StatType::AVG): {
                retval += duration;
                break;
            }
            default: throw std::runtime_error("Unknown access time statistic requested.");
        }
    }
    if (stat == StatType::AVG) {
        const std::size_t nMetricIntervals = _risesets.size() / 2 - idxOffset;
        retval /= nMetricIntervals;
    }
    return retval;
}


bool RiseSetArray::has_access(const Time& time) const
{
    const auto lower = std::lower_bound(_risesets.begin(), _risesets.end(), time);
    return (std::distance(_risesets.begin(), lower) % 2);
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