# include "Shell.hpp"

#include <stdexcept>

#include "astro/element_sets/orbital_elements/Keplerian.hpp"

Shell::Shell(std::vector<Plane> _planes) {
    planes = _planes;
    generate_id_hash();
}


Shell::Shell(std::vector<Spacecraft> satellites) {
    Plane noPlane(satellites);

    planes.push_back(noPlane);

    generate_id_hash();
}

Shell::Shell(const double& semimajor, const double& inclination, const size_t& T, const size_t& P, const double& F,
        const double& anchorRAAN, const double& anchorAnomaly) {

    if (T % P) {
        throw std::runtime_error("The Walker constructor requires the total number planes is a multiple of the total number of of satellites.");
    }

    const size_t satsPerPlane = T/P;
    const double deltaRAAN =  360.0/double(P);
    const double deltaAnomaly =  F*360.0/double(T);

    const double deg2rad = M_PI/180.0;

    planes.resize(P);
    size_t iAnom = 0;
    size_t iPlane = 0;
    for (auto& plane : planes) {
        plane.satellites.resize(satsPerPlane);
        for (auto& sat: plane.satellites) {
            sat = Spacecraft(
                OrbitalElements(Keplerian({
                    semimajor,
                    0.0,
                    inclination*deg2rad,
                    (anchorRAAN + deltaRAAN*iPlane)*deg2rad,
                    0.0,
                    (anchorAnomaly + deltaAnomaly*iAnom)*deg2rad
                })),
                Date("Jan-01-2030 00:00:00.0")
            );
            ++iAnom;
        }
        plane.generate_id_hash();
    }
    generate_id_hash();
}


const size_t Shell::size() const {
    size_t size = 0;
    for (const auto& plane: planes) {
        size += plane.size();
    }
    return size;
}


const size_t Shell::n_planes() const {
    return planes.size();
}


void Shell::add_plane(const Plane& plane) {
    planes.push_back(plane);
}


void Shell::add_spacecraft(const Spacecraft& spacecraft, const size_t& planeId) {
    for (auto& plane : planes) {
        if (plane.id == planeId) {
            plane.add_spacecraft(spacecraft);
        }
    }
    throw std::runtime_error("No plane found with matching id: " + std::to_string(planeId) + "\n");
}

void Shell::add_spacecraft(const Spacecraft& spacecraft) {
    Plane noPlane(std::vector<Spacecraft>{spacecraft});
    planes.push_back(noPlane);
}


const std::vector<Plane>& Shell::get_all_planes() const {
    return planes;
}

const std::vector<Spacecraft> Shell::get_all_spacecraft() const {
    std::vector<Spacecraft> allSpacecraft;
    for (auto& plane : planes) {
        const auto& shellSpacecraft = plane.get_all_spacecraft();
        allSpacecraft.insert(allSpacecraft.end(), shellSpacecraft.begin(), shellSpacecraft.end());
    }
    return allSpacecraft;
}


const Plane& Shell::get_plane(const size_t& planeId) const {
    for (const auto& plane: planes) {
        if (plane.id == planeId) {
            return plane;
        }
    }
    throw std::runtime_error("No plane found with matching id: " + std::to_string(planeId) + "\n");
}


const Spacecraft& Shell::get_spacecraft(const size_t& spacecraftId) const {
    for (const auto& plane: planes) {
        for (const auto& sat: plane.satellites) {
            if (sat.get_id() == spacecraftId) {
                return sat;
            }
        }
    }
    throw std::runtime_error("No spacecraft found with matching id: " + std::to_string(spacecraftId) + "\n");
}


void Shell::generate_id_hash() {
    id = std::hash<size_t>()(planes[0].id);
    for (size_t ii = 1; ii < planes.size(); ii++) {
        id ^= std::hash<size_t>()(planes[ii].id);
    }
}


void Shell::propagate(EquationsOfMotion& eom, Integrator& integrator, const Interval& interval) {
    for (auto& plane : planes) {
        plane.propagate(eom, integrator, interval);
    }
}