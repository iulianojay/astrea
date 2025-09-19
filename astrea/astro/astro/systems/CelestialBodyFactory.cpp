#include <astro/systems/CelestialBodyFactory.hpp>

#include <astro/systems/planetary_bodies/planetary_bodies.hpp>

namespace astrea {
namespace astro {

const CelestialBodyUniquePtr& CelestialBodyFactory::create(const PlanetaryBody& id, const AstrodynamicsSystem& system)
{
    using namespace planetary_bodies;
    if (_bodies.count(id) == 0) {
        switch (id) {
            case (PlanetaryBody::SUN): {
                _bodies.emplace(id, std::make_unique<Sun>(system));
                break;
            }
            case (PlanetaryBody::MERCURY): {
                _bodies.emplace(id, std::make_unique<Mercury>(system));
                break;
            }
            case (PlanetaryBody::VENUS): {
                _bodies.emplace(id, std::make_unique<Venus>(system));
                break;
            }
            case (PlanetaryBody::EARTH): {
                _bodies.emplace(id, std::make_unique<Earth>(system));
                break;
            }
            case (PlanetaryBody::MOON): {
                _bodies.emplace(id, std::make_unique<Moon>(system));
                break;
            }
            case (PlanetaryBody::MARS): {
                _bodies.emplace(id, std::make_unique<Mars>(system));
                break;
            }
            case (PlanetaryBody::PHOBOS): {
                _bodies.emplace(id, std::make_unique<Phobos>(system));
                break;
            }
            case (PlanetaryBody::DEIMOS): {
                _bodies.emplace(id, std::make_unique<Deimos>(system));
                break;
            }
            case (PlanetaryBody::JUPITER): {
                _bodies.emplace(id, std::make_unique<Jupiter>(system));
                break;
            }
            case (PlanetaryBody::GANYMEDE): {
                _bodies.emplace(id, std::make_unique<Ganymede>(system));
                break;
            }
            case (PlanetaryBody::CALLISTO): {
                _bodies.emplace(id, std::make_unique<Callisto>(system));
                break;
            }
            case (PlanetaryBody::IO): {
                _bodies.emplace(id, std::make_unique<Io>(system));
                break;
            }
            case (PlanetaryBody::EUROPA): {
                _bodies.emplace(id, std::make_unique<Europa>(system));
                break;
            }
            case (PlanetaryBody::SATURN): {
                _bodies.emplace(id, std::make_unique<Saturn>(system));
                break;
            }
            case (PlanetaryBody::TITAN): {
                _bodies.emplace(id, std::make_unique<Titan>(system));
                break;
            }
            case (PlanetaryBody::RHEA): {
                _bodies.emplace(id, std::make_unique<Rhea>(system));
                break;
            }
            case (PlanetaryBody::IAPETUS): {
                _bodies.emplace(id, std::make_unique<Iapetus>(system));
                break;
            }
            case (PlanetaryBody::URANUS): {
                _bodies.emplace(id, std::make_unique<Uranus>(system));
                break;
            }
            case (PlanetaryBody::TITANIA): {
                _bodies.emplace(id, std::make_unique<Titania>(system));
                break;
            }
            case (PlanetaryBody::OBERON): {
                _bodies.emplace(id, std::make_unique<Oberon>(system));
                break;
            }
            case (PlanetaryBody::NEPTUNE): {
                _bodies.emplace(id, std::make_unique<Neptune>(system));
                break;
            }
            case (PlanetaryBody::TRITON): {
                _bodies.emplace(id, std::make_unique<Triton>(system));
                break;
            }
            default: throw std::runtime_error("Error: Celestial body not implemented in factory.");
        }
    }
    return get(id);
}

const CelestialBodyUniquePtr& CelestialBodyFactory::get(const PlanetaryBody& id) const
{
    if (_bodies.count(id) > 0) { return _bodies.at(id); }
    throw std::out_of_range("Input gravitational body not found.");
}

const CelestialBodyUniquePtr& CelestialBodyFactory::get_or_create(const PlanetaryBody& id, const AstrodynamicsSystem& system)
{
    if (_bodies.count(id) == 0) { create(id, system); }
    return _bodies.at(id);
}


// void CelestialBodyFactory::propagate_bodies(const Date& epoch, const Time& endTime)
// {
//     // Propagate everything except the Sun
//     for (auto& [name, body] : _bodies) {
//         if (name != "Sun") {
//             // Get parent mu
//             const std::string parent = body->get_parent();
//             const auto parentMu      = get_or_create(parent)->get_mu();

//             // Propagate
//             body->propagate(epoch, endTime, parentMu);
//         }
//     }
// }


} // namespace astro
} // namespace astrea