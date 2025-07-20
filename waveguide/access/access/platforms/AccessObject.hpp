#pragma once

#include <memory>

#include <access/time/AccessArray.hpp>

#include <astro/types/typedefs.hpp>

namespace waveguide {
namespace accesslib {

class AccessObject {

  protected:
    AccessObject()          = default;
    virtual ~AccessObject() = default;

  public:
    void add_access(const std::size_t& receiverId, const RiseSetArray& access)
    {
        _accesses[get_id(), receiverId] = (_accesses[get_id(), receiverId] | access);
    }
    void drop_access(const std::size_t& receiverId, const RiseSetArray& access)
    {
        _accesses.erase(get_id(), receiverId);
    }

    AccessArray& get_accesses() { return _accesses; }
    const AccessArray& get_accesses() const { return _accesses; }

    virtual std::size_t get_id() const = 0;

  private:
    AccessArray _accesses;
};

} // namespace accesslib
} // namespace waveguide