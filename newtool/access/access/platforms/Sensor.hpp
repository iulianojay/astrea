#pragma once

#include <memory>

#include <access/platforms/fov/FieldOfView.hpp>
#include <access/time/AccessArray.hpp>

#include <astro/types/typedefs.hpp>

namespace accesslib {

class Sensor {

  public:
    Sensor(FieldOfView* fov) :
        fov(fov)
    {
    }
    ~Sensor() = default;

    const std::size_t& get_id() { return id; }

    virtual const bool contains(const astro::RadiusVector& sensor2target) const
    {
        return fov->contains(boresight, sensor2target);
    }

    void add_access(const std::size_t& receiverId, const RiseSetArray& access) { accesses[id, receiverId] = access; }

  private:
    std::size_t id;
    int parentId;
    astro::RadiusVector attachmentPoint;
    astro::RadiusVector boresight;
    FieldOfView* fov;
    AccessArray accesses;

    void generate_id_hash();
};

} // namespace accesslib