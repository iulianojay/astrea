/**
 * @file AccessObject.hpp
 * @author Jay Iuliano (iuliano.jay@gmail.com)
 * @brief AccessObject class for managing access rights.
 * @version 0.1
 * @date 2025-08-03
 *
 * @copyright Copyright (c) 2025
 *
 */
#pragma once

#include <memory>

#include <access/risesets/AccessArray.hpp>

#include <astro/types/typedefs.hpp>

namespace waveguide {
namespace accesslib {

/**
 * @brief Base class for objects that can visually access other objects.
 */
class AccessObject {

  protected:
    /**
     * @brief Default constructor.
     */
    AccessObject() = default;

    /**
     * @brief Default destructor.
     */
    virtual ~AccessObject() = default;

  public:
    /**
     * @brief Adds access times for a specific receiver.
     *
     * @param receiverId The ID of the receiver.
     * @param access The RiseSetArray representing the access times.
     */
    void add_access(const std::size_t& receiverId, const RiseSetArray& access)
    {
        if (_accesses.contains({ get_id(), receiverId })) {
            _accesses[get_id(), receiverId] = (_accesses[get_id(), receiverId] | access);
        }
        else {
            _accesses[get_id(), receiverId] = access;
        }
    }

    /**
     * @brief Drops access times for a specific receiver.
     *
     * @param receiverId The ID of the receiver.
     * @param access The RiseSetArray representing the access times.
     */
    void drop_access(const std::size_t& receiverId, const RiseSetArray& access)
    {
        _accesses.erase(get_id(), receiverId);
    }

    /**
     * @brief Gets the access times for this object.
     *
     * @return AccessArray& A reference to the AccessArray containing access times.
     */
    AccessArray& get_accesses() { return _accesses; }

    /**
     * @brief Gets the access times for this object (const version).
     *
     * @return const AccessArray& A const reference to the AccessArray containing access times.
     */
    const AccessArray& get_accesses() const { return _accesses; }

    /**
     * @brief Pure virtual function to get the ID of the object.
     *
     * @return std::size_t The ID of the object.
     */
    virtual std::size_t get_id() const = 0;

  private:
    AccessArray _accesses; //<! Access times for this object, indexed by sender and receiver IDs.
};

} // namespace accesslib
} // namespace waveguide