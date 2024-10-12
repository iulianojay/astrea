# include "Constellation.hpp"

static const int DEFAULT_SHELL_ID = -1;

Constellation::Constellation(std::vector<Shell> _shells) {
    shells = _shells;
    generate_id_hash();
}


Constellation::Constellation(std::vector<Plane> planes) {
    Shell noShell(planes);
    noShell.name = "DEFAULT";
    noShell.id = DEFAULT_SHELL_ID;

    shells.push_back(noShell);

    generate_id_hash();
}


Constellation::Constellation(std::vector<Spacecraft> satellites) {
    Plane noPlane(satellites);
    Shell noShell(std::vector<Plane>{noPlane});
    noShell.name = "DEFAULT";

    shells.push_back(noShell);

    generate_id_hash();
}


const size_t Constellation::size() const {
    size_t size;
    for (const auto& shell: shells) {
        size += shells.size();
    }
    return size;
}


const size_t Constellation::n_shells() const {
    return shells.size();
}


const size_t Constellation::n_planes() const {
    size_t nPlane;
    for (const auto& shell: shells) {
        nPlane += shell.n_planes();
    }
    return nPlane;
}


void Constellation::add_shell(const Shell& shell) {
    shells.push_back(shell);
}


void Constellation::add_plane(const Plane& plane, const int& shellId) {
    for (auto& shell : shells) {
        if (shell.id == shellId) {
            shell.add_plane(plane);
        }
    }
    throw std::runtime_error("No shell found with matching id: " + std::to_string(shellId) + "\n");
}


void Constellation::add_plane(const Plane& plane) {
    for (auto& shell : shells) {
        if (shell.id == DEFAULT_SHELL_ID) {
            shell.add_plane(plane);
            return;
        }
    }

    Shell noShell(std::vector<Plane>{plane});
    noShell.name = "DEFAULT";
    noShell.id = DEFAULT_SHELL_ID;

    shells.push_back(noShell);
}


void Constellation::add_spacecraft(const Spacecraft& spacecraft, const int& planeId) {
    for (auto& shell : shells) {
        for (auto& plane : shell.planes) {
            if (plane.id == planeId) {
                plane.add_spacecraft(spacecraft);
            }
        }
    }
    throw std::runtime_error("No plane found with matching id: " + std::to_string(planeId) + "\n");
}


void Constellation::add_spacecraft(const Spacecraft& spacecraft) {
    for (auto& shell : shells) {
        if (shell.id == DEFAULT_SHELL_ID) {
            shell.add_spacecraft(spacecraft);
            return;
        }
    }

    Shell noShell(std::vector<Plane>{std::vector<Spacecraft>{spacecraft}});
    noShell.name = "DEFAULT";
    noShell.id = DEFAULT_SHELL_ID;

    shells.push_back(noShell);
}


const std::vector<Shell>& Constellation::get_all_shells() const {
    return shells;
}


const std::vector<Plane> Constellation::get_all_planes() const {
    std::vector<Plane> allPlanes;
    for (auto& shell : shells) {
        const auto& shellPlanes = shell.get_all_planes();
        allPlanes.insert(allPlanes.end(), shellPlanes.begin(), shellPlanes.end());
    }
    return allPlanes;
}


const std::vector<Spacecraft> Constellation::get_all_spacecraft() const {
    std::vector<Spacecraft> allSpacecraft;
    for (auto& shell : shells) {
        const auto shellSpacecraft = shell.get_all_spacecraft();
        allSpacecraft.insert(allSpacecraft.end(), shellSpacecraft.begin(), shellSpacecraft.end());
    }
    return allSpacecraft;
}


const Shell& Constellation::get_shell(const int& shellId) const {
    for (const auto& shell: shells) {
        if (shell.id == shellId) {
            return shell;
        }
    }
    throw std::runtime_error("No shell found with matching id: " + std::to_string(shellId) + "\n");
}


const Plane& Constellation::get_plane(const int& planeId) const {
    for (const auto& shell: shells) {
        for (const auto& plane: shell.planes) {
            if (plane.id == planeId) {
                return plane;
            }
        }
    }
    throw std::runtime_error("No plane found with matching id: " + std::to_string(planeId) + "\n");
}


const Spacecraft& Constellation::get_spacecraft(const int& spacecraftId) const {
    for (const auto& shell: shells) {
        for (const auto& plane: shell.planes) {
            for (const auto& sat: plane.satellites) {
                if (sat.id == spacecraftId) {
                    return sat;
                }
            }
        }
    }
    throw std::runtime_error("No spacecraft found with matching id: " + std::to_string(spacecraftId) + "\n");
}


void Constellation::generate_id_hash() {
    id = std::hash<size_t>()(shells[0].id);
    for (int ii = 1; ii < shells.size(); ii++) {
        id ^= std::hash<size_t>()(shells[ii].id);
    }
}


void Constellation::propagate(const Interval& interval) {
    EquationsOfMotion eom;
    Integrator integrator;
    propagate(eom, integrator, interval);
}


void Constellation::propagate(const AstrodynamicsSystem& sys, const Interval& interval) {
    EquationsOfMotion eom(sys);
    propagate(eom, interval);
}


void Constellation::propagate(EquationsOfMotion& eom, const Interval& interval) {
    Integrator integrator;
    propagate(eom, integrator, interval);
}


void Constellation::propagate(Integrator& integrator, const Interval& interval) {
    EquationsOfMotion eom;
    propagate(eom, integrator, interval);
}



void Constellation::propagate(EquationsOfMotion& eom, Integrator& integrator, const Interval& interval) {
    for (auto& shell : shells) {
        shell.propagate(eom, integrator, interval);
    }
}

