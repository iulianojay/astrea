#include <astro/systems/CelestialBodyFactory.hpp>

#include <filesystem>

namespace astro {

// TODO: Fix this trash
static const std::filesystem::path ROOT = "/home/jay/projects/waveguide";


const CelestialBodyUniquePtr& CelestialBodyFactory::create(const std::string& name, const AstrodynamicsSystem& system)
{
    const auto file = std::filesystem::absolute(ROOT / _buildFiles.at(name)).lexically_normal();
    if (_bodies.count(name) == 0) { _bodies.emplace(name, std::make_unique<CelestialBody>(file, system)); }
    find_root();
    return get(name);
}

const CelestialBodyUniquePtr& CelestialBodyFactory::get(const std::string& name) const
{
    if (_bodies.count(name) > 0) { return _bodies.at(name); }
    throw std::out_of_range("Input gravitational body, " + name + ", not found.");
}

const CelestialBodyUniquePtr& CelestialBodyFactory::get_or_create(const std::string& name, const AstrodynamicsSystem& system)
{
    if (_bodies.count(name) == 0) { create(name, system); }
    return _bodies.at(name);
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


void CelestialBodyFactory::find_root()
{
    // TODO: Move this to the system

    // // Count total planets
    // std::size_t planetCount = 0;
    // for (const auto& [name, body] : _bodies) {
    //     if (body->get_type() == "Planet") {
    //         planetCount++;
    //         _root = name;
    //     }
    // }

    // // Check if other bodies are children of only planet -
    // // assumes the common root cannot be a satellite
    // if (planetCount == 1) {
    //     for (const auto& [name, body] : _bodies) {
    //         std::string parent = name;
    //         while (parent != "Sun" && parent != _root) {
    //             parent = get_or_create(parent)->get_parent();
    //         }

    //         // If any object not in same planetary system, the common root
    //         // must be the Sun
    //         if (parent == "Sun") {
    //             _root = "Sun";
    //             break;
    //         }
    //     }
    // }
    // else {
    //     // The only common root for multiple planets is the Sun
    //     _root = "Sun";
    // }
}

} // namespace astro