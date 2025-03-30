#pragma once

#ifndef SWIG
#include <memory>
#endif

#include <access/platforms/fov/FieldOfView.hpp>
#include <access/time/AccessArray.hpp>

#include <astro/state/State.hpp>
#include <astro/types/typedefs.hpp>

class Sensor {

  public:
    Sensor(FieldOfView* fov) :
        fov(fov)
    {
    }
    ~Sensor() = default;

    const size_t& get_id() { return id; }

    virtual const bool contains(const BasisArray& sensor2target) const
    {
        return fov->contains(boresight, sensor2target);
    }

    void add_access(const size_t& receiverId, const RiseSetArray& access) { accesses[id, receiverId] = access; }

  private:
    size_t id;
    int parentId;
    BasisArray attachmentPoint;
    BasisArray boresight;
    FieldOfView* fov;
    AccessArray accesses;

    void generate_id_hash();
};


#ifdef SWIG

%template(SensorVector) std::vector<Sensor>;

#endif