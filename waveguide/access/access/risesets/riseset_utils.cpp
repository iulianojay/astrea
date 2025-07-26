#include <access/risesets/riseset_utils.hpp>

#include <limits>
#include <vector>

#include <mp-units/systems/si.h>
#include <mp-units/systems/si/chrono.h>

#include <units/units.hpp>

#include <access/risesets/RiseSetArray.hpp>

namespace waveguide {
namespace accesslib {

RiseSetArray riseset_union(const RiseSetArray& a, const RiseSetArray& b)
{
    // If one is empty, union is the other
    if (a.size() == 0) { return b; }
    else if (b.size() == 0) {
        return a;
    }

    // Setup
    std::size_t aIdx = 0;
    std::size_t bIdx = 0;
    std::size_t cIdx = 0;

    const std::size_t lenA = a.size();
    const std::size_t lenB = b.size();

    // Max size
    std::vector<Time> c;
    c.resize(lenA + lenB);

    // Loop and insert
    while (aIdx < lenA || bIdx < lenB) {

        // Compare values
        Time diff;
        if (aIdx >= lenA) { diff = 1 * detail::time_unit; } // unit is arbitrary here
        else if (bIdx >= lenB) {
            diff = -1 * detail::time_unit;
        }
        else {
            diff = a[aIdx] - b[bIdx];
        }

        // a > b
        if (diff < 0 * detail::time_unit) {
            if (!(bIdx & 1)) {
                c[cIdx] = a[aIdx];
                ++cIdx;
            }
            ++aIdx;
        }
        // b > a
        else if (diff > 0 * detail::time_unit) {
            if (!(aIdx & 1)) {
                c[cIdx] = b[bIdx];
                ++cIdx;
            }
            ++bIdx;
        }
        // a = b
        else {
            if ((aIdx & 1) == (bIdx & 1)) {
                c[cIdx] = b[bIdx];
                ++cIdx;
            }
            ++bIdx;
            ++aIdx;
        }
    }

    // Get length
    const std::size_t lenC = (a[0] == b[0]) ? cIdx + 1 : cIdx;
    c.resize(lenC);

    // Remove duplicates
    for (std::size_t ii = lenC - 1; ii > 0; --ii) {
        if (c[ii] == c[ii - 1]) { c.erase(c.begin() + ii); }
    }

    return RiseSetArray(c);
}

RiseSetArray riseset_intersection(const RiseSetArray& a, const RiseSetArray& b)
{
    // If one is empty, intersection is empty
    if (a.size() == 0 || b.size() == 0) { return RiseSetArray(); }

    // Setup
    std::size_t aIdx = 0;
    std::size_t bIdx = 0;
    std::size_t cIdx = 0;

    const std::size_t lenA = a.size();
    const std::size_t lenB = b.size();

    // Max size
    std::vector<Time> c;
    c.resize(lenA + lenB);

    // Loop and insert
    while (aIdx < lenA && bIdx < lenB) {

        // Left and right interval bounds
        const Time left  = (a[aIdx] < b[bIdx]) ? b[bIdx] : a[aIdx];
        const Time right = (a[aIdx + 1] > b[bIdx + 1]) ? b[bIdx + 1] : a[aIdx + 1];

        // Only store if it's valid
        if (left < right) {
            c[cIdx]     = left;
            c[cIdx + 1] = right;
            cIdx += 2;
        }

        // Increment
        if (a[aIdx + 1] <= b[bIdx + 1]) { aIdx += 2; }
        else {
            bIdx += 2;
        }
    }
    c.resize(cIdx);

    return RiseSetArray(c);
}


RiseSetArray riseset_difference(const RiseSetArray& a0, const RiseSetArray& b0)
{
    // c = a - b

    // Check for empty arrays
    if (a0.size() == 0 || b0.size() == 0) { return a0; }

    // Setup
    std::size_t aIdx = 0;
    std::size_t bIdx = 0;
    std::size_t cIdx = 0;

    const std::size_t lenA = a0.size();
    const std::size_t lenB = b0.size();

    RiseSetArray a = a0;
    RiseSetArray b = b0;

    // Max size
    std::vector<Time> c;
    c.resize(lenA + lenB);

    // Loop and insert
    while (aIdx < lenA) {

        /*

        1)
        a:      |-----|
        b:   |------------|

        2)
        a:   |------------|
        b:      |-----|

        3)
        a:   |------|
        b:      |-----|

            3.5)
            a:   |------|
            b:             |-----|

        4)
        a:      |-----|
        b:   |------|

            4.5)
            a:             |-----|
            b:   |------|

        */

        // TODO: There's gotta be a way to optimize this
        if (bIdx == lenB) {
            // Done with b, store everything else
            c[cIdx]     = a[aIdx];
            c[cIdx + 1] = a[aIdx + 1];
            cIdx += 2;
            aIdx += 2;
        }
        else if (a[aIdx] >= b[bIdx] && a[aIdx + 1] <= b[bIdx + 1]) {
            // Case 1: b envelopes a

            // truncate b
            b[bIdx] = a[aIdx + 1];

            // Move to next a riseset
            aIdx += 2;
        }
        else if (a[aIdx] < b[bIdx] && a[aIdx + 1] > b[bIdx + 1]) {
            // Case 2: a envelopes b

            // Store a rise to b rise
            c[cIdx]     = a[aIdx];
            c[cIdx + 1] = b[bIdx];
            cIdx += 2;

            // truncate a
            a[aIdx] = b[bIdx + 1];

            // Move to next b riseset
            bIdx += 2;
        }
        else if (a[aIdx] < b[bIdx] && a[aIdx + 1] <= b[bIdx + 1]) {
            // Case 3: a starts, b ends

            c[cIdx] = a[aIdx];
            if (b[bIdx] > a[aIdx + 1]) { // Case 3.5: b completely after a
                c[cIdx + 1] = a[aIdx + 1];
            }
            else {
                // Store a rise to b rise
                c[cIdx + 1] = b[bIdx];

                // truncate b
                b[bIdx] = a[aIdx + 1];
            }

            // Increment
            cIdx += 2;
            aIdx += 2;
        }
        else if (a[aIdx] >= b[bIdx] && a[aIdx + 1] > b[bIdx + 1]) {
            // Case 4: b starts, a ends

            if (a[aIdx] > b[bIdx + 1]) {
                // Case 4.5: a completely after b
            }
            else {
                // truncate a
                a[aIdx] = b[bIdx + 1];
            }

            // Move to next b riseset
            bIdx += 2;
        }
    }
    c.resize(cIdx);

    return RiseSetArray(c);
}


} // namespace accesslib
} // namespace waveguide