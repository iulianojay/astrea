#pragma once

#include <memory>

#include <access/platforms/fov/FieldOfView.hpp>
#include <access/time/AccessArray.hpp>

#include <astro/types/typedefs.hpp>

namespace accesslib {

class Sensor {

  public:
    Sensor() = default;
    template <typename FieldOfView_T>
    Sensor(const FieldOfView_T& fov) :
        _fov(std::make_shared<FieldOfView_T>(fov))
    {
    }
    ~Sensor() = default;

    const std::size_t& get_id() { return _id; }

    virtual const bool contains(const astro::RadiusVector& sensor2target) const
    {
        return _fov->contains(_boresight, sensor2target);
    }

    virtual const bool contains(const astro::RadiusVector& boresight, const astro::RadiusVector& sensor2target) const
    {
        return _fov->contains(boresight, sensor2target);
    }

    void add_access(const std::size_t& receiverId, const RiseSetArray& access) { _accesses[_id, receiverId] = access; }

  private:
    std::size_t _id;
    int _parentId;
    astro::RadiusVector _attachmentPoint;
    astro::RadiusVector _boresight;
    std::shared_ptr<FieldOfView> _fov;
    AccessArray _accesses;

    void generate_id_hash();
};

} // namespace accesslib