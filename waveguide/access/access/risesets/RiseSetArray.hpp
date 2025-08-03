/**
 * @file RiseSetArray.hpp
 * @author Jay Iuliano (iuliano.jay@gmail.com)
 * @brief Contains the RiseSetArray class, which represents an array of rise and set times.
 * @version 0.1
 * @date 2025-08-03
 *
 * @copyright Copyright (c) 2025
 *
 */
#pragma once

#include <vector>

#include <mp-units/format.h>
#include <mp-units/ostream.h>

#include <units/units.hpp>

#include <access/risesets/riseset_utils.hpp>

namespace waveguide {
namespace accesslib {

/**
 * @brief Enumeration of statistical measures for RiseSetArray.
 */
enum class Stat {
    MIN,  //<! Minimum value
    MEAN, //<! Mean value
    MAX   //<! Maximum value
};

/**
 * @brief Represents an array of rise and set times.
 *
 * This class provides functionality to manage and manipulate an array of rise and set times,
 * including operations like addition, subtraction, intersection, and union of rise/set pairs.
 */
class RiseSetArray {

    friend std::ostream& operator<<(std::ostream& os, const RiseSetArray& risesets);

  public:
    /**
     * @brief Default constructor for RiseSetArray.
     *
     * Initializes an empty RiseSetArray.
     */
    RiseSetArray() = default;

    /**
     * @brief Destructor for RiseSetArray.
     */
    ~RiseSetArray() = default;

    /**
     * @brief Constructs a RiseSetArray from a vector of Time objects.
     *
     * @param risesets A vector of Time objects representing rise and set times.
     */
    RiseSetArray(const std::vector<Time>& risesets);

    /**
     * @brief Copy constructor for RiseSetArray.
     *
     * @param other The other RiseSetArray to copy from.
     */
    RiseSetArray(const RiseSetArray& other);

    /**
     * @brief Move constructor for RiseSetArray.
     *
     * @param other The other RiseSetArray to move from.
     */
    RiseSetArray(RiseSetArray&& other) noexcept;

    /**
     * @brief Move assignment operator for RiseSetArray.
     *
     * @param other The other RiseSetArray to move from.
     * @return RiseSetArray& Reference to this RiseSetArray after the move.
     */
    RiseSetArray& operator=(RiseSetArray&& other) noexcept;

    /**
     * @brief Copy assignment operator for RiseSetArray.
     *
     * @param other The other RiseSetArray to copy from.
     * @return RiseSetArray& Reference to this RiseSetArray after the copy.
     */
    RiseSetArray& operator=(const RiseSetArray& other);

    /**
     * @brief Appends a rise and set time to the array.
     *
     * @param rise The rise time to append.
     * @param set The set time to append.
     * @throws std::invalid_argument If the rise time is not before the set time.
     * @throws std::invalid_argument If the rise and set times are not in chronological order.
     * @throws std::invalid_argument If the rise and set times are not valid.
     */
    void append(const Time& rise, const Time& set);

    /**
     * @brief Prepends a rise and set time to the array.
     *
     * @param rise The rise time to prepend.
     * @param set The set time to prepend.
     * @throws std::invalid_argument If the rise time is not before the set time.
     * @throws std::invalid_argument If the rise and set times are not in chronological order.
     * @throws std::invalid_argument If the rise and set times are not valid.
     */
    void prepend(const Time& rise, const Time& set);

    /**
     * @brief Inserts a rise and set time at the end of the array.
     *
     * @param rise The rise time to insert.
     * @param set The set time to insert.
     * @throws std::invalid_argument If the rise time is not before the set time.
     * @throws std::invalid_argument If the rise and set times are not in chronological order.
     * @throws std::invalid_argument If the rise and set times are not valid.
     */
    void insert(const Time& rise, const Time& set);

    /**
     * @brief Returns the number of rise/set pairs in the array.
     *
     * @return std::size_t The number of rise/set pairs.
     */
    std::size_t size() const;

    /**
     * @brief Returns a reference to the rise/set pair at the specified index.
     *
     * @param ind The index of the rise/set pair to access.
     * @return Time& A reference to the rise/set pair at the specified index.
     */
    Time& operator[](const std::size_t& ind); // TODO: Should this be allowed? Makes it possible to generate bad rise/set pairs

    /**
     * @brief Returns a const reference to the rise/set pair at the specified index.
     *
     * @param ind The index of the rise/set pair to access.
     * @return const Time& A const reference to the rise/set pair at the specified index.
     */
    const Time& operator[](const std::size_t& ind) const;

    /**
     * @brief Equality operator to compare two RiseSetArray objects.
     *
     * @param other The other RiseSetArray to compare against.
     * @return true If the two RiseSetArray objects are equal.
     * @return false If the two RiseSetArray objects are not equal.
     */
    bool operator==(const RiseSetArray& other) const;

    /**
     * @brief Difference operator to subtract one RiseSetArray from another.
     *
     * @param other The RiseSetArray to subtract from this one.
     * @return RiseSetArray A new RiseSetArray containing the result of the subtraction.
     */
    RiseSetArray operator-(const RiseSetArray& other) const;

    /**
     * @brief In-place difference operator to subtract one RiseSetArray from another.
     *
     * @param other The RiseSetArray to subtract from this one.
     * @return RiseSetArray& Reference to this RiseSetArray after the subtraction.
     */
    RiseSetArray& operator-=(const RiseSetArray& other);

    /**
     * @brief Union operator to combine two RiseSetArray objects.
     *
     * @param other The other RiseSetArray to combine with this one.
     * @return RiseSetArray A new RiseSetArray containing the union of the two.
     */
    RiseSetArray operator|(const RiseSetArray& other) const;

    /**
     * @brief In-place union operator to combine two RiseSetArray objects.
     *
     * @param other The other RiseSetArray to combine with this one.
     * @return RiseSetArray& Reference to this RiseSetArray after the union.
     */
    RiseSetArray& operator|=(const RiseSetArray& other);

    /**
     * @brief Intersection operator to find common rise/set pairs between two RiseSetArray objects.
     *
     * @param other The other RiseSetArray to intersect with this one.
     * @return RiseSetArray A new RiseSetArray containing the intersection of the two.
     */
    RiseSetArray operator&(const RiseSetArray& other) const;

    /**
     * @brief In-place intersection operator to find common rise/set pairs between two RiseSetArray objects.
     *
     * @param other The other RiseSetArray to intersect with this one.
     * @return RiseSetArray& Reference to this RiseSetArray after the intersection.
     */
    RiseSetArray& operator&=(const RiseSetArray& other);

    /**
     * @brief Calculates the gap between rise and set times.
     *
     * @param stat The statistical measure to calculate (MIN, MEAN, MAX).
     * @return Time The calculated gap based on the specified statistic.
     */
    Time gap(const Stat& stat = Stat::MEAN) const;

    /**
     * @brief Calculates the access time based on rise and set times.
     *
     * @param stat The statistical measure to calculate (MIN, MEAN, MAX).
     * @return Time The calculated access time based on the specified statistic.
     */
    Time access_time(const Stat& stat = Stat::MEAN) const;

    /**
     * @brief Iterator type for the RiseSetArray.
     */
    using iterator = std::vector<Time>::iterator;

    /**
     * @brief Constant iterator type for the RiseSetArray.
     */
    using const_iterator = std::vector<Time>::const_iterator;

    /**
     * @brief Returns an iterator to the beginning of the RiseSetArray.
     *
     * @return iterator An iterator to the beginning of the RiseSetArray.
     */
    iterator begin();

    /**
     * @brief Returns an iterator to the end of the RiseSetArray.
     *
     * @return iterator An iterator to the end of the RiseSetArray.
     */
    iterator end();

    /**
     * @brief Returns a constant iterator to the beginning of the RiseSetArray.
     *
     * @return const_iterator A constant iterator to the beginning of the RiseSetArray.
     */
    const_iterator begin() const;

    /**
     * @brief Returns a constant iterator to the end of the RiseSetArray.
     *
     * @return const_iterator A constant iterator to the end of the RiseSetArray.
     */
    const_iterator end() const;

    /**
     * @brief Returns a constant iterator to the beginning of the RiseSetArray.
     *
     * @return const_iterator A constant iterator to the beginning of the RiseSetArray.
     */
    const_iterator cbegin() const;

    /**
     * @brief Returns a constant iterator to the end of the RiseSetArray.
     *
     * @return const_iterator A constant iterator to the end of the RiseSetArray.
     */
    const_iterator cend() const;

    /**
     * @brief Converts the RiseSetArray to a vector of formatted strings.
     *
     * @return std::vector<std::string> A vector of formatted strings representing the rise and set times.
     */
    std::vector<std::string> to_string_vector() const;

  private:
    std::vector<Time> _risesets; //!< Vector to store rise and set times

    /**
     * @brief Validates a rise/set pair.
     *
     * @param rise The rise time to validate.
     * @param set The set time to validate.
     * @throws std::invalid_argument If the rise time is not before the set time.
     * @throws std::invalid_argument If the rise and set times are not in chronological order.
     * @throws std::invalid_argument If the rise and set times are not valid.
     */
    void validate_riseset(const Time& rise, const Time& set) const;

    /**
     * @brief Validates a vector of rise/set pairs.
     *
     * @param risesets The vector of Time objects to validate.
     * @throws std::invalid_argument If the rise and set times are not in chronological order.
     * @throws std::invalid_argument If the rise and set times are not valid.
     */
    void validate_risesets(const std::vector<Time>& risesets) const;

    /**
     * @brief Converts a Time object to a formatted string.
     *
     * @param t The Time object to convert.
     * @return std::string A formatted string representation of the Time object.
     */
    std::string to_formatted_string(Time t) const;
};

} // namespace accesslib
} // namespace waveguide