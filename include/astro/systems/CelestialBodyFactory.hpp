#pragma once

#ifndef SWIG
    #include <string>
    #include <unordered_map>
#endif

#include "astro/systems/CelestialBody.hpp"
#include "astro/time/Date.hpp"

using CelestialBodyUniquePtr = std::unique_ptr<CelestialBody>;

class CelestialBodyFactory {
public:

    CelestialBodyFactory() = default;
    ~CelestialBodyFactory() = default;

    const CelestialBodyUniquePtr& create(const std::string& name);
    const CelestialBodyUniquePtr& get(const std::string& name) const;
    const CelestialBodyUniquePtr& get_or_create(const std::string& name);

    const size_t number_of_bodies() const { return bodies.size(); }
    void propagate_bodies(const Date& epoch, const Time& endTime);

    const std::string& get_root() const { return root; }

private:

    std::unordered_map<std::string, CelestialBodyUniquePtr> bodies;
    std::string root;

    void find_root();

    const std::unordered_map<std::string, std::string> buildFiles = {
        {"Sun",      "./data/planetary/Sun/Sun.json"},
        {"Mercury",  "./data/planetary/Mercury/Mercury.json"},
        {"Venus",    "./data/planetary/Venus/Venus.json"},
        {"Earth",    "./data/planetary/Earth/Earth.json"},
        {"Moon",     "./data/planetary/Earth/Moon.json"},
        {"Mars",     "./data/planetary/Mars/Mars.json"},
        {"Phobos",   "./data/planetary/Mars/Phobos.json"},
        {"Deimos",   "./data/planetary/Mars/Deimos.json"},
        {"Jupiter",  "./data/planetary/Jupiter/Jupiter.json"},
        {"Ganymede", "./data/planetary/Jupiter/Ganymede.json"},
        {"Callisto", "./data/planetary/Jupiter/Callisto.json"},
        {"Io",       "./data/planetary/Jupiter/Io.json"},
        {"Europa",   "./data/planetary/Jupiter/Europa.json"},
        {"Saturn",   "./data/planetary/Saturn/Saturn.json"},
        {"Titan",    "./data/planetary/Saturn/Titan.json"},
        {"Rhea",     "./data/planetary/Saturn/Rhea.json"},
        {"Iapetus",  "./data/planetary/Saturn/Iapetus.json"},
        {"Uranus",   "./data/planetary/Uranus/Uranus.json"},
        {"Titania",  "./data/planetary/Uranus/Titania.json"},
        {"Oberon",   "./data/planetary/Uranus/Oberon.json"},
        {"Neptune",  "./data/planetary/Neptune/Neptune.json"},
        {"Triton",   "./data/planetary/Neptune/Triton.json"}
    };
};
