#pragma once

#include <memory>

#include "AccessArray.hpp"
#include "FieldOfView.hpp"
#include "State.hpp"
#include "typedefs.hpp"

class Sensor {

public:

    Sensor(FieldOfView* fov) : fov(fov) {}
    ~Sensor() = default;

    const size_t& get_id() { return id; }

    virtual const bool contains(const basis_array& sensor2target) const {
        return fov->contains(boresight, sensor2target);
    }

    void add_access(const size_t& receiverId, const RiseSetArray& access) {
        accesses[id, receiverId] = access;
    }

private:

    size_t id;
    int parentId;
    basis_array attachmentPoint;
    basis_array boresight;
    FieldOfView* fov;
    AccessArray accesses;

    void generate_id_hash();

};