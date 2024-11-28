#include "Plane.hpp"


Plane::Plane(std::vector<Spacecraft> _satellites) {
    satellites = _satellites;

    // Grab first element set as plane set
    elements = satellites[0].states[0].elements;

    // Assume Earth-system for now. TODO: Fix this
    AstrodynamicsSystem sys;
    elements.convert(ElementSet::KEPLERIAN, sys);
    elements[5] = 0.0;

    // Check if other satellites are actually in-plane
    strict = true;
    for (const auto& sat: satellites) {
        OrbitalElements satElements = sat.states[0].elements;
        satElements.convert(ElementSet::KEPLERIAN, sys);
        if (!elements.nearly_equal(satElements, true)) {
            strict = false;
            break;
        }
    }

    generate_id_hash();
}


const size_t Plane::size() const {
    return satellites.size();
}


void Plane::add_spacecraft(const Spacecraft& spacecraft) {
    satellites.push_back(spacecraft);
}


const std::vector<Spacecraft>& Plane::get_all_spacecraft() const {
    return satellites;
}


const Spacecraft& Plane::get_spacecraft(const size_t& spacecraftId) const {
    for (const auto& sat: satellites) {
        if (sat.id == spacecraftId) {
            return sat;
        }
    }
    throw std::runtime_error("No spacecraft found with matching id: " + std::to_string(spacecraftId) + "\n");
}


void Plane::generate_id_hash() {
    id = std::hash<size_t>()(satellites[0].id);
    for (size_t ii = 1; ii < satellites.size(); ii++) {
        id ^= std::hash<size_t>()(satellites[ii].id);
    }
}


void Plane::propagate(EquationsOfMotion& eom, Integrator& integrator, const Interval& interval) {
    for (auto& sat : satellites) {
        integrator.propagate(interval, eom, sat);
    }
}