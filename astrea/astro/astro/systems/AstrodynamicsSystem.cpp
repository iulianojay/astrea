/*
 * The GNU Lesser General Public License (LGPL)
 *
 * Copyright (c) 2025 Jay Iuliano
 *
 * This file is part of Astrea.
 * Astrea is free software: you can redistribute it and/or modify it under the terms of the GNU Lesser General Public License
 * as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
 * Astrea is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty
 * of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU Lesser General Public License for more details. You should
 * have received a copy of the GNU General Public License along with Astrea. If not, see <https://www.gnu.org/licenses/>.
 */

#include <astro/systems/AstrodynamicsSystem.hpp>

#include <astro/frames/CartesianVector.hpp>
#include <astro/frames/frames.hpp>

namespace astrea {
namespace astro {

AstrodynamicsSystem::AstrodynamicsSystem(const CelestialBodyId& centralBody, const std::unordered_set<CelestialBodyId>& secondaryBodies) :
    _centerType(SystemCenter::CENTRAL_BODY),
    _centralBody(centralBody)
{
    add_body(centralBody);
    for (const auto& body : secondaryBodies) {
        add_body(body);
    }
}
AstrodynamicsSystem::AstrodynamicsSystem(const AstrodynamicsSystem& other)
{
    _centerType  = other._centerType;
    _centralBody = other._centralBody;
    for (const auto& [id, body] : other._bodies) {
        add_body(id);
    }
}

AstrodynamicsSystem& AstrodynamicsSystem::operator=(const AstrodynamicsSystem& other)
{
    return *this = std::move(AstrodynamicsSystem(other));
}

const SystemCenter& AstrodynamicsSystem::get_center_type() const { return _centerType; }

const CelestialBodyId& AstrodynamicsSystem::get_central_body_id() const { return _centralBody; }

const CelestialBodyUniquePtr& AstrodynamicsSystem::get_central_body() const
{
    switch (_centerType) {
        case SystemCenter::CENTRAL_BODY: return get_body(_centralBody);
        case SystemCenter::BARYCENTER:
        default: throw std::runtime_error("Barycenteric systems have no central body.");
    }
}

const CelestialBodyUniquePtr& AstrodynamicsSystem::get_body(const CelestialBodyId& id) const { return _bodies.at(id); }

const CelestialBodyUniquePtr& AstrodynamicsSystem::add_body(const CelestialBodyId& id)
{
    if (_bodies.count(id) == 0) {
        _bodies.emplace(id, create_impl(id));
        _root = find_common_ancestor({ std::from_range, std::views::keys(_bodies) });
    }
    return get_body(id);
}

CelestialBodyUniquePtr AstrodynamicsSystem::create_body(const CelestialBodyId& id) const { return create_impl(id); }

const gtl::flat_hash_map<CelestialBodyId, CelestialBodyUniquePtr>& AstrodynamicsSystem::get_all_bodies() const
{
    return _bodies;
}

const CelestialBodyId& AstrodynamicsSystem::get_system_root() const { return _root; }

GravParam AstrodynamicsSystem::get_mu() const
{
    switch (_centerType) {
        case SystemCenter::CENTRAL_BODY: return get_central_body()->get_mu();
        case SystemCenter::BARYCENTER: throw std::runtime_error("Barycenteric systems have not been implemented yet.");
        default: throw std::runtime_error("AstrodynamicsSystem::get_mu: Unknown system center type.");
    }
}

const std::size_t AstrodynamicsSystem::size() const { return _bodies.size(); }

void AstrodynamicsSystem::clear() { return _bodies.clear(); }

RadiusVector<frames::solar_system_barycenter::icrf>
    AstrodynamicsSystem::get_relative_position(const Date& date, const CelestialBodyId id1, const CelestialBodyId id2) const
{
    // If one is the parent of the other, easy
    const auto parent1 = create_body(id1)->get_parent();
    const auto parent2 = create_body(id2)->get_parent();

    if (parent1 == id2) { return create_body(id1)->get_position_at(date); }
    if (parent2 == id1) { return -create_body(id2)->get_position_at(date); }

    // Find the position using the root but it's fine to represent in ssb since it's just a relative position vector
    const CelestialBodyId root = find_common_ancestor({ id1, id2 });

    const RadiusVector<frames::solar_system_barycenter::icrf> pos1 = get_position_relative_to_ancestor(date, id1, root);
    const RadiusVector<frames::solar_system_barycenter::icrf> pos2 = get_position_relative_to_ancestor(date, id2, root);

    return pos1 - pos2;
}

VelocityVector<frames::solar_system_barycenter::icrf>
    AstrodynamicsSystem::get_relative_velocity(const Date& date, const CelestialBodyId id1, const CelestialBodyId id2) const
{
    // If one is the parent of the other, easy
    const auto parent1 = create_body(id1)->get_parent();
    const auto parent2 = create_body(id2)->get_parent();

    if (parent1 == id2) { return create_body(id1)->get_velocity_at(date); }
    if (parent2 == id1) { return -create_body(id2)->get_velocity_at(date); }

    // Find the position using the root but it's fine to represent in ssb since it's just a relative position vector
    const CelestialBodyId root = find_common_ancestor({ id1, id2 });

    const VelocityVector<frames::solar_system_barycenter::icrf> vel1 = get_velocity_relative_to_ancestor(date, id1, root);
    const VelocityVector<frames::solar_system_barycenter::icrf> vel2 = get_velocity_relative_to_ancestor(date, id2, root);

    return vel1 - vel2;
}

RadiusVector<frames::solar_system_barycenter::icrf>
    AstrodynamicsSystem::get_position_relative_to_ancestor(const Date& date, const CelestialBodyId id, const CelestialBodyId ancestor) const
{
    auto object = id;
    auto parent = create_body(object)->get_parent();

    RadiusVector<frames::solar_system_barycenter::icrf> pos = create_body(object)->get_position_at(date);
    while (parent != ancestor) {
        object = parent;
        parent = create_body(parent)->get_parent();
        pos += create_body(object)->get_position_at(date);
    }
    return pos;
}


CartesianVector<Velocity, frames::solar_system_barycenter::icrf>
    AstrodynamicsSystem::get_velocity_relative_to_ancestor(const Date& date, const CelestialBodyId id, const CelestialBodyId ancestor) const
{
    auto object = id;
    auto parent = create_body(object)->get_parent();

    CartesianVector<Velocity, frames::solar_system_barycenter::icrf> vel = create_body(object)->get_velocity_at(date);
    while (parent != ancestor) {
        object = parent;
        parent = create_body(parent)->get_parent();
        vel += create_body(object)->get_velocity_at(date);
    }
    return vel;
}

CelestialBodyId AstrodynamicsSystem::find_common_ancestor(const std::unordered_set<CelestialBodyId>& bodies) const
{
    // If there's only one body, it is the root
    if (bodies.size() == 1) { return *(bodies.begin()); }

    // Count total planets
    CelestialBodyId ancestor;
    std::size_t planetCount = 0;
    for (const auto& id : bodies) {
        const auto& body = create_body(id);
        if (body->get_type() == CelestialBodyType::PLANET) {
            planetCount++;
            ancestor = id;
        }
    }

    if (planetCount == 1) {
        // Check if other bodies are children of only planet -
        // assumes the common ancestor cannot be a satellite
        for (const auto& id : bodies) {
            CelestialBodyId parentId = id;
            while (parentId != CelestialBodyId::SUN && parentId != ancestor) {
                // Don't add parent to active bodies if it's not already there
                parentId = create_body(parentId)->get_parent();
            }

            // If any object not in same planetary system, the common ancestor must be the Sun
            if (parentId == CelestialBodyId::SUN) {
                ancestor = CelestialBodyId::SUN;
                break;
            }
        }
    }
    else {
        // The only common ancestor for multiple planets is the Sun
        ancestor = CelestialBodyId::SUN;
    }

    return ancestor;
}

CelestialBodyUniquePtr AstrodynamicsSystem::create_impl(const CelestialBodyId& id) const
{
    using namespace planetary_bodies;
    switch (id) {
        case (CelestialBodyId::SUN): {
            return std::make_unique<Sun>();
        }
        case (CelestialBodyId::MERCURY): {
            return std::make_unique<Mercury>();
        }
        case (CelestialBodyId::VENUS): {
            return std::make_unique<Venus>();
        }
        case (CelestialBodyId::EARTH): {
            return std::make_unique<Earth>();
        }
        case (CelestialBodyId::MOON): {
            return std::make_unique<Moon>();
        }
        case (CelestialBodyId::MARS): {
            return std::make_unique<Mars>();
        }
        case (CelestialBodyId::PHOBOS): {
            return std::make_unique<Phobos>();
        }
        case (CelestialBodyId::DEIMOS): {
            return std::make_unique<Deimos>();
        }
        case (CelestialBodyId::JUPITER): {
            return std::make_unique<Jupiter>();
        }
        case (CelestialBodyId::GANYMEDE): {
            return std::make_unique<Ganymede>();
        }
        case (CelestialBodyId::CALLISTO): {
            return std::make_unique<Callisto>();
        }
        case (CelestialBodyId::IO): {
            return std::make_unique<Io>();
        }
        case (CelestialBodyId::EUROPA): {
            return std::make_unique<Europa>();
        }
        case (CelestialBodyId::SATURN): {
            return std::make_unique<Saturn>();
        }
        case (CelestialBodyId::TITAN): {
            return std::make_unique<Titan>();
        }
        case (CelestialBodyId::RHEA): {
            return std::make_unique<Rhea>();
        }
        case (CelestialBodyId::IAPETUS): {
            return std::make_unique<Iapetus>();
        }
        case (CelestialBodyId::URANUS): {
            return std::make_unique<Uranus>();
        }
        case (CelestialBodyId::TITANIA): {
            return std::make_unique<Titania>();
        }
        case (CelestialBodyId::OBERON): {
            return std::make_unique<Oberon>();
        }
        case (CelestialBodyId::NEPTUNE): {
            return std::make_unique<Neptune>();
        }
        case (CelestialBodyId::TRITON): {
            return std::make_unique<Triton>();
        }
        default: throw std::runtime_error("Error: Celestial body not implemented in factory.");
    }
}

} // namespace astro
} // namespace astrea