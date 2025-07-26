#pragma once

namespace waveguide {
namespace accesslib {

class RiseSetArray;

RiseSetArray riseset_union(const RiseSetArray& a, const RiseSetArray& b);
RiseSetArray riseset_intersection(const RiseSetArray& a, const RiseSetArray& b);
RiseSetArray riseset_difference(const RiseSetArray& a, const RiseSetArray& b);

} // namespace accesslib
} // namespace waveguide