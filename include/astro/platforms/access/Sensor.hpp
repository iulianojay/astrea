#pragma once

#include <memory>

#include "AccessArray.hpp"
#include "FieldOfView.hpp"
#include "typedefs.hpp"

class Sensor {

public:

    Sensor(FieldOfView* fov) : fov(fov) {}
    ~Sensor() = default;

    virtual const bool contains(const basis_array& target) const {
        return fov->contains(boresight, target);
    }

private:

    size_t id;
    int parentId;
    basis_array boresight;
    FieldOfView* fov;
    AccessArray accesses;

    void generate_id_hash();

};