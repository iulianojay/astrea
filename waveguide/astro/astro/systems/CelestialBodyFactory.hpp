#pragma once

#include <string>
#include <unordered_map>
#include <vector>

#include <astro/systems/CelestialBody.hpp>
#include <astro/time/Date.hpp>

namespace astro {

using CelestialBodyUniquePtr = std::unique_ptr<CelestialBody>;

class CelestialBodyFactory {
  public:
    CelestialBodyFactory()  = default;
    ~CelestialBodyFactory() = default;

    const CelestialBodyUniquePtr& create(const std::string& name);
    const CelestialBodyUniquePtr& get(const std::string& name) const;
    const CelestialBodyUniquePtr& get_or_create(const std::string& name);

    const std::size_t size() const { return _bodies.size(); }
    void clear() { return _bodies.clear(); }
    void propagate_bodies(const Date& epoch, const Time& endTime);

    const std::string& get_root() const { return _root; }

    using iterator       = std::unordered_map<std::string, CelestialBodyUniquePtr>::iterator;
    using const_iterator = std::unordered_map<std::string, CelestialBodyUniquePtr>::const_iterator;
    auto begin() const { return _bodies.begin(); }
    auto end() const { return _bodies.end(); }

  private:
    std::unordered_map<std::string, CelestialBodyUniquePtr> _bodies;
    std::string _root;

    void find_root();

    const std::unordered_map<std::string, std::string> _buildFiles = {
        { "Sun", "./data/planetary/Sun/Sun.json" },
        { "Mercury", "./data/planetary/Mercury/Mercury.json" },
        { "Venus", "./data/planetary/Venus/Venus.json" },
        { "Earth", "./data/planetary/Earth/Earth.json" },
        { "Moon", "./data/planetary/Earth/Moon.json" },
        { "Mars", "./data/planetary/Mars/Mars.json" },
        { "Phobos", "./data/planetary/Mars/Phobos.json" },
        { "Deimos", "./data/planetary/Mars/Deimos.json" },
        { "Jupiter", "./data/planetary/Jupiter/Jupiter.json" },
        { "Ganymede", "./data/planetary/Jupiter/Ganymede.json" },
        { "Callisto", "./data/planetary/Jupiter/Callisto.json" },
        { "Io", "./data/planetary/Jupiter/Io.json" },
        { "Europa", "./data/planetary/Jupiter/Europa.json" },
        { "Saturn", "./data/planetary/Saturn/Saturn.json" },
        { "Titan", "./data/planetary/Saturn/Titan.json" },
        { "Rhea", "./data/planetary/Saturn/Rhea.json" },
        { "Iapetus", "./data/planetary/Saturn/Iapetus.json" },
        { "Uranus", "./data/planetary/Uranus/Uranus.json" },
        { "Titania", "./data/planetary/Uranus/Titania.json" },
        { "Oberon", "./data/planetary/Uranus/Oberon.json" },
        { "Neptune", "./data/planetary/Neptune/Neptune.json" },
        { "Triton", "./data/planetary/Neptune/Triton.json" }
    };
};

} // namespace astro