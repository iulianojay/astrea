/**
 * @file riseset_utils.hpp
 * @author Jay Iuliano (iuliano.jay@gmail.com)
 * @brief Utility functions for manipulating RiseSetArray objects.
 * @version 0.1
 * @date 2025-08-03
 *
 * @copyright Copyright (c) 2025
 *
 */
#pragma once

namespace astrea {
namespace accesslib {

class RiseSetArray;

/**
 * @brief Union of two RiseSetArray objects.
 *
 * @param a The first RiseSetArray.
 * @param b The second RiseSetArray.
 * @return RiseSetArray The union of the two RiseSetArray objects.
 */
RiseSetArray riseset_union(const RiseSetArray& a, const RiseSetArray& b);

/**
 * @brief Intersection of two RiseSetArray objects.
 *
 * @param a The first RiseSetArray.
 * @param b The second RiseSetArray.
 * @return RiseSetArray The intersection of the two RiseSetArray objects.
 */
RiseSetArray riseset_intersection(const RiseSetArray& a, const RiseSetArray& b);

/**
 * @brief Difference of two RiseSetArray objects.
 *
 * @param a The first RiseSetArray.
 * @param b The second RiseSetArray.
 * @return RiseSetArray The difference of the two RiseSetArray objects.
 */
RiseSetArray riseset_difference(const RiseSetArray& a, const RiseSetArray& b);

} // namespace accesslib
} // namespace astrea