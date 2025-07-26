#pragma once

#include <memory>
#include <unordered_set>
#include <vector>

#include <astro/systems/Barycenter.hpp>
#include <astro/systems/CelestialBody.hpp>
#include <astro/systems/CelestialBodyFactory.hpp>
#include <astro/time/Date.hpp>
#include <astro/types/typedefs.hpp>


namespace waveguide {
namespace astro {

class AstrodynamicsSystem {
  public:
    AstrodynamicsSystem(std::string centralBody = "Earth", std::unordered_set<std::string> allBodies = { "Earth", "Moon" }, Date epoch = J2000) :
        centralBody(centralBody),
        allBodies(allBodies),
        epoch(epoch)
    {
        create_all_bodies();
    };
    ~AstrodynamicsSystem() {}

    // Remove copy asignment/construction
    AstrodynamicsSystem(const AstrodynamicsSystem&)           = delete;
    AstrodynamicsSystem operator=(const AstrodynamicsSystem&) = delete;

    static AstrodynamicsSystem DEFAULT() { return AstrodynamicsSystem(); }

    const std::string& center() const { return centralBody; }
    const CelestialBodyUniquePtr& get_center() const { return bodyFactory.get(centralBody); }
    const CelestialBodyUniquePtr& get(const std::string& name) const { return bodyFactory.get(name); }
    const CelestialBodyUniquePtr& get_or_create(const std::string& name)
    {
        return bodyFactory.get_or_create(name, *this);
    }

    const std::unordered_set<std::string>& all_bodies() const { return allBodies; }
    const auto& get_all_bodies() const { return bodyFactory.get_all_bodies(); }

    // RadiusVector get_radius_to_center(CelestialBody target, double date); //TODO: Implement

    using iterator       = std::unordered_map<std::string, CelestialBodyUniquePtr>::iterator;
    using const_iterator = std::unordered_map<std::string, CelestialBodyUniquePtr>::const_iterator;
    auto begin() const { return bodyFactory.begin(); }
    auto end() const { return bodyFactory.end(); }

  private:
    const std::string centralBody;
    const std::unordered_set<std::string> allBodies;

    Date epoch;
    CelestialBodyFactory bodyFactory;

    void create_all_bodies();
};

} // namespace astro
} // namespace waveguide