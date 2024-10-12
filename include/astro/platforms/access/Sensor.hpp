#pragma once

#include "FieldOfView.hpp"
#include "Access.hpp"

class Sensor {

public:

    Sensor(const FieldOfView& fov) : fov(fov) {}
    ~Sensor() = default;

    const bool contains(const basis_array& target) const {
        return fov.contains(target);
    }

private:

    size_t id;
    int parentId;
    FieldOfView fov;
    AccessArray accesses;

    void generate_id_hash();

};