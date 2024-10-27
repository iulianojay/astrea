#include "riseset_utils.hpp"

#include <vector>
#include <limits>

#include "Time.hpp"
#include "RiseSetArray.hpp"

RiseSetArray riseset_union(const RiseSetArray& a, const RiseSetArray& b) {

    // If one is empty, union is the other
    if (a.size() == 0) {
        return b;
    }
    else if (b.size() == 0) {
        return a;
    }

    // Setup
    size_t aIdx = 0;
    size_t bIdx = 0;
    size_t cIdx = 0;

    const size_t lenA = a.size();
    const size_t lenB = b.size();

    // Max size and fill with trash values
    std::vector<Time> c;
    c.resize(lenA + lenB, std::numeric_limits<int>::max());

    // Loop and insert
    while (aIdx < lenA || bIdx < lenB) {

        // Compare values
        double diff;
        if (aIdx >= lenA) {
            diff = 1;
        }
        else if (bIdx >= lenB) {
            diff = -1;
        }
        else {
            diff = a[aIdx] - b[bIdx];
        }

        // a > b
        if (diff < 0) {
            if (!(bIdx & 1)) {
                c[cIdx] = a[aIdx];
                ++cIdx;
            }
            ++aIdx;
        }
        // b > a
        else if (diff > 0) {
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
    const size_t lenC = (a[0] == b[0]) ? cIdx + 1 : cIdx;

    // Remove duplicates
    auto temp_c = c;
    cIdx = 0;
    for (size_t ii = 0; ii < lenC - 1; ii += 2) {
        if (temp_c[ii] == temp_c[ii+1]) {
            c[cIdx] = temp_c[ii];
            c[cIdx+1] = temp_c[ii+1];
            cIdx += 2;
        }
    }
    c.resize(cIdx);

    return RiseSetArray(c);
}

RiseSetArray riseset_intersection(const RiseSetArray& a, const RiseSetArray& b) {

    // If one is empty, intersection is empty
    if (a.size() == 0 || b.size() == 0) {
        return RiseSetArray();
    }

    // Setup
    size_t aIdx = 0;
    size_t bIdx = 0;
    size_t cIdx = 0;

    const size_t lenA = a.size();
    const size_t lenB = b.size();

    // Max size
    std::vector<Time> c;
    c.resize(lenA + lenB);

    // Loop and insert
    while (aIdx < lenA && bIdx < lenB) {

        // Left and right interval bounds
        const double left  = (a[aIdx]   < b[bIdx])   ? b[bIdx]   : a[aIdx];
        const double right = (a[aIdx+1] > b[bIdx+1]) ? b[bIdx+1] : a[aIdx+1];

        // Only store if it's valid
        if (left < right) {
            c[cIdx] = left;
            c[cIdx+1] = right;
            cIdx += 2;
        }

        // Increment
        if (a[aIdx+1] <= b[bIdx+1]) {
            aIdx += 2;
        }
        else {
            bIdx += 2;
        }
    }
    c.resize(cIdx);

    return RiseSetArray(c);
}