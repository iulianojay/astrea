/**
 * @file AccessArray.hpp
 * @author Jay Iuliano (iuliano.jay@gmail.com)
 * @brief Contains the AccessArray class, which is a collection of RiseSetArrays indexed by sender and receiver IDs, and
 * provides methods for manipulating and querying access times.
 * @date 2025-08-03
 *
 * @copyright Copyright (c) 2025 Jay Iuliano
 *
 * The GNU Lesser General Public License (LGPL)
 *
 * This file is part of Astrea.
 * Astrea is free software: you can redistribute it and/or modify it under the terms of the GNU Lesser General Public License
 * as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
 * Astrea is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty
 * of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU Lesser General Public License for more details. You should
 * have received a copy of the GNU General Public License along with Astrea. If not, see <https://www.gnu.org/licenses/>.
 *
 */
#pragma once

#include <cstdint>
#include <functional>

namespace astrea {
namespace trace {

/**
 * @brief Represents a pair of IDs for sender and receiver.
 */
struct IdPair {
    std::size_t sender;   //!<< The ID of the sender.
    std::size_t receiver; //!< The ID of the receiver.

    /**
     * @brief Default constructor for IdPair.
     */
    IdPair() = default;

    /**
     * @brief Constructs an IdPair with specified sender and receiver IDs.
     * @param sender The ID of the sender.
     * @param receiver The ID of the receiver.
     */
    IdPair(std::size_t sender, std::size_t receiver) :
        sender(sender),
        receiver(receiver)
    {
    }

    /**
     * @brief Copy constructor for IdPair.
     * @param other The IdPair to copy from.
     */
    IdPair(const IdPair& other) :
        sender(other.sender),
        receiver(other.receiver)
    {
    }

    /**
     * @brief Default destructor for IdPair.
     */
    ~IdPair() = default;

    /**
     * @brief Equality operator for IdPair.
     * @param other The IdPair to compare with.
     * @return True if both sender and receiver IDs are equal, false otherwise.
     */
    bool operator==(const IdPair& other) const { return (sender == other.sender && receiver == other.receiver); }
};

} // namespace trace
} // namespace astrea

/**
 * @brief Specialization of std::hash for IdPair to allow it to be used as a key in hash-based containers.
 */
template <>
struct std::hash<astrea::trace::IdPair> {
    /**
     * @brief Computes a hash value for an IdPair.
     * @param k The IdPair to hash.
     * @return A hash value for the IdPair.
     */
    std::size_t operator()(const astrea::trace::IdPair& k) const
    {
        return (std::hash<std::size_t>()(k.sender)) ^ (std::hash<std::size_t>()(k.receiver));
    }
};

/**
 * @brief Specialization of std::less for IdPair to allow it to be used in ordered containers.
 */
template <>
struct std::less<astrea::trace::IdPair> {
    /**
     * @brief Compares two IdPairs for ordering.
     * @param lhs The first IdPair to compare.
     * @param rhs The second IdPair to compare.
     * @return True if lhs is less than rhs, false otherwise.
     */
    bool operator()(const astrea::trace::IdPair& lhs, const astrea::trace::IdPair& rhs) const
    {
        if (lhs.sender == rhs.sender) { return lhs.receiver < rhs.receiver; }
        else {
            return lhs.sender < rhs.sender;
        }
    };
};
