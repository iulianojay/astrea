/**
 * @file AccessArray.hpp
 * @author Jay Iuliano (iuliano.jay@gmail.com)
 * @brief Contains the AccessArray class, which is a collection of RiseSetArrays indexed by sender and receiver IDs, and
 * provides methods for manipulating and querying access times.
 * @version 0.1
 * @date 2025-08-03
 *
 * @copyright Copyright (c) 2025
 *
 */
#pragma once

#include <parallel_hashmap/btree.h>

#include <access/risesets/RiseSetArray.hpp>

namespace waveguide {
namespace accesslib {

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

} // namespace accesslib
} // namespace waveguide

/**
 * @brief Specialization of std::hash for IdPair to allow it to be used as a key in hash-based containers.
 */
template <>
struct std::hash<waveguide::accesslib::IdPair> {
    /**
     * @brief Computes a hash value for an IdPair.
     * @param k The IdPair to hash.
     * @return A hash value for the IdPair.
     */
    std::size_t operator()(const waveguide::accesslib::IdPair& k) const
    {
        return (std::hash<std::size_t>()(k.sender)) ^ (std::hash<std::size_t>()(k.receiver));
    }
};

/**
 * @brief Specialization of std::less for IdPair to allow it to be used in ordered containers.
 */
template <>
struct std::less<waveguide::accesslib::IdPair> {
    /**
     * @brief Compares two IdPairs for ordering.
     * @param lhs The first IdPair to compare.
     * @param rhs The second IdPair to compare.
     * @return True if lhs is less than rhs, false otherwise.
     */
    bool operator()(const waveguide::accesslib::IdPair& lhs, const waveguide::accesslib::IdPair& rhs) const
    {
        if (lhs.sender == rhs.sender) { return lhs.receiver < rhs.receiver; }
        else {
            return lhs.sender < rhs.sender;
        }
    };
};

namespace waveguide {
namespace accesslib {

/**
 * @brief Represents a collection of access times indexed by sender and receiver IDs.
 * This class provides methods to manipulate and query access times for different sender-receiver pairs.
 */
class AccessArray {

    friend std::ostream& operator<<(std::ostream& os, const AccessArray& accessArray);

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
     * @brief Union operator for AccessArray.
     *
     * @param other The AccessArray to union with.
     */
    void operator|(const AccessArray& other);

    /**
     * @brief Intersection operator for AccessArray.
     *
     * @param other The AccessArray to intersect with.
     */
    void operator&(const AccessArray& other);

    /**
     * @brief Iterator type for AccessArray.
     */
    using iterator = phmap::btree_map<IdPair, RiseSetArray>::iterator;

    /**
     * @brief Const iterator type for AccessArray.
     */
    using const_iterator = phmap::btree_map<IdPair, RiseSetArray>::const_iterator;

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
    phmap::btree_map<IdPair, RiseSetArray> _accesses; //!< A map that associates IdPairs with their corresponding RiseSetArrays.
};

} // namespace accesslib
} // namespace waveguide