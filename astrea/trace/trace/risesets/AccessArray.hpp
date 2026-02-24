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

#include <gtl/btree.hpp>

#include <trace/risesets/RiseSetArray.hpp>
#include <trace/types/IdPair.hpp>

namespace astrea {
namespace trace {

/**
 * @brief Represents a collection of access times indexed by sender and receiver IDs.
 * This class provides methods to manipulate and query access times for different sender-receiver pairs.
 */
class AccessArray {

    friend std::ostream& operator<<(std::ostream& os, const AccessArray& accessarray);

  public:
    /**
     * @brief Default constructor for AccessArray.
     * Initializes an empty AccessArray.
     */
    AccessArray() = default;

    /**
     * @brief Default destructor for AccessArray.
     */
    ~AccessArray() = default;

    /**
     * @brief Accesses the RiseSetArray for a given sender and receiver ID.
     *
     * @param senderId The ID of the sender.
     * @param receiverId The ID of the receiver.
     * @return RiseSetArray& The RiseSetArray for the specified sender and receiver.
     */
    RiseSetArray& operator[](const std::size_t& senderId, const std::size_t& receiverId);

    /**
     * @brief Accesses the RiseSetArray for a given IdPair.
     *
     * @param senderId The ID of the sender.
     * @param receiverId The ID of the receiver.
     * @return RiseSetArray& The RiseSetArray for the specified sender and receiver.
     */
    const RiseSetArray& at(const std::size_t& senderId, const std::size_t& receiverId) const;

    /**
     * @brief Checks if the AccessArray contains a RiseSetArray for the specified IdPair.
     *
     * @param idPair The IdPair to check.
     * @return true if the AccessArray contains the IdPair, false otherwise.
     */
    bool contains(const IdPair& idPair) const;

    /**
     * @brief Erases the RiseSetArray for a given sender and receiver ID.
     *
     * @param senderId The ID of the sender.
     * @param receiverId The ID of the receiver.
     */
    void erase(const std::size_t& senderId, const std::size_t& receiverId);

    /**
     * @brief Returns the number of RiseSetArrays in the AccessArray.
     *
     * @return std::size_t The number of RiseSetArrays.
     */
    std::size_t size() const;

    /**
     * @brief Retrieves the RiseSetArray for all accesses to a specific receiver.
     *
     * @param receiverId The ID of the receiver.
     * @return RiseSetArray The RiseSetArray containing all accesses to the specified receiver.
     */
    RiseSetArray get_all_accesses_to_receiver(const std::size_t& receiverId) const;

    /**
     * @brief Retrieves the RiseSetArray for all accesses from a specific sender.
     *
     * @param senderId The ID of the sender.
     * @return RiseSetArray The RiseSetArray containing all accesses from the specified sender.
     */
    RiseSetArray get_all_accesses_from_sender(const std::size_t& senderId) const;

    /**
     * @brief Union operator for AccessArray.
     *
     * @param other The AccessArray to union with.
     */
    AccessArray& operator|(const AccessArray& other);

    /**
     * @brief Const union operator for AccessArray.
     *
     * @param other The AccessArray to union with.
     * @return AccessArray The resulting AccessArray after the union operation.
     */
    AccessArray operator|(const AccessArray& other) const;

    /**
     * @brief Intersection operator for AccessArray.
     *
     * @param other The AccessArray to intersect with.
     */
    AccessArray& operator&(const AccessArray& other);

    /**
     * @brief Const intersection operator for AccessArray.
     *
     * @param other The AccessArray to intersect with.
     * @return AccessArray The resulting AccessArray after the intersection operation.
     */
    AccessArray operator&(const AccessArray& other) const;

    /**
     * @brief Iterator type for AccessArray.
     */
    using iterator = gtl::btree_map<IdPair, RiseSetArray>::iterator;

    /**
     * @brief Const iterator type for AccessArray.
     */
    using const_iterator = gtl::btree_map<IdPair, RiseSetArray>::const_iterator;

    /**
     * @brief Returns an iterator to the beginning of the AccessArray.
     *
     * @return iterator An iterator to the beginning.
     */
    iterator begin() { return _accesses.begin(); }

    /**
     * @brief Returns an iterator to the end of the AccessArray.
     *
     * @return iterator An iterator to the end.
     */
    iterator end() { return _accesses.end(); }

    /**
     * @brief Returns a const iterator to the beginning of the AccessArray.
     *
     * @return const_iterator A const iterator to the beginning.
     */
    const_iterator begin() const { return _accesses.begin(); }

    /**
     * @brief Returns a const iterator to the end of the AccessArray.
     *
     * @return const_iterator A const iterator to the end.
     */
    const_iterator end() const { return _accesses.end(); }

    /**
     * @brief Returns a const iterator to the beginning of the AccessArray.
     *
     * @return const_iterator A const iterator to the beginning.
     */
    const_iterator cbegin() const { return _accesses.cbegin(); }

    /**
     * @brief Returns a const iterator to the end of the AccessArray.
     *
     * @return const_iterator A const iterator to the end.
     */
    const_iterator cend() const { return _accesses.cend(); }

  private:
    gtl::btree_map<IdPair, RiseSetArray> _accesses; //!< A map that associates IdPairs with their corresponding RiseSetArrays.
};

} // namespace trace
} // namespace astrea