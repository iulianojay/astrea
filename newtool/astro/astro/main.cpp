#include <stdio.h>
#include <iostream>
#include <fstream>
#include <filesystem>

// #include <arrow/api.h>
// #include <arrow/csv/api.h>
// #include <arrow/io/api.h>
// #include <arrow/ipc/api.h>
// #include <parquet/arrow/reader.h>
// #include <parquet/arrow/writer.h>

#include <iostream>

#include <astro/astro.hpp>

int main() {

    // Setup system
    AstrodynamicsSystem sys("Earth", {"Earth", "Moon", "Sun", "Jupiter"});

    const OrbitalElements state({10000.0, 0.0, 45.0, 0.0, 0.0, 0.0}, ElementSet::KEPLERIAN);
    // const OrbitalElements cartesianState = conversions::convert(state, ElementSet::KEPLERIAN, ElementSet::CARTESIAN, sys);

    // Build constellation
    const int T = 1;
    const int P = 1;
    const double F = 1.0;
    Constellation walkerBall(10000.0, 45.0, T, P, F);

    // int count = 0; //TODO: Fix this. Comparitor doesn't work and iterates past end, for some reason
    // for (auto satIter = walkerBall.sat_begin(); satIter < walkerBall.sat_end(); ++satIter) {
    //     if (count == 100) {
    //         std::cout << "stop";
    //     }
    //     std::cout << "sat(" << count << ") id = " << (*satIter).get_id() << std::endl;
    //     ++count;
    // }

    // Build Force Model
    ForceModel forces;
    forces.add<AtmosphericForce>();
    forces.add<OblatenessForce>(sys, 10, 10);
    forces.add<NBodyForce>();

    // Build EoMs
    // std::string propagator = "two_body";
    // TwoBody eom(sys);
    std::string propagator = "j2mean";
    J2MeanVop eom(sys);
    // std::string propagator = "cowells";
    // CowellsMethod eom(sys, forces);
    // std::string propagator = "coes";
    // KeplerianVop eom(sys, forces, false);

    // Setup integrator
    Integrator integrator;
    integrator.set_abs_tol(1.0e-10);
    integrator.set_rel_tol(1.0e-10);

    // Propagate
    auto start = std::chrono::steady_clock::now();

    Interval propInterval{seconds(0), years(1)};
    walkerBall.propagate(eom, integrator, propInterval);

    auto end = std::chrono::steady_clock::now();
    auto diff = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start);

    std::cout << "Func Evals: " << integrator.n_func_evals() << std::endl;
    std::cout << "Propagation Time: " << diff.count()/1e9 << " (s)" << std::endl;

    // Access
    // start = std::chrono::steady_clock::now();

    // Time accessResolution = minutes(5);
    // find_accesses(walkerBall, accessResolution, &sys);

    // end = std::chrono::steady_clock::now();
    // diff = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start);

    // std::cout << "Access Analysis Time: " << diff.count()/1e9 << " (s)" << std::endl;

    // Check propagation
    // std::cout << "\n\n" << "Walker: [" << T << ", " << P << ", " << F << "]" << std::endl;
    // for (auto& shell : walkerBall) {
    //     std::cout << "Shell: " << shell.get_id() << std::endl;
    //     for (auto& plane : shell) {
    //         std::cout << "\tPlane: " << plane.get_id() << std::endl;
    //         for (auto& sat : plane) {
    //             std::cout << "\t\tSat: " << sat.get_id() << std::endl;
    //             std::cout << "\t\tstate0 = " << sat.get_initial_state() << std::endl;
    //             std::cout << "\t\tstatef = " << sat.get_final_state() << std::endl << std::endl;
    //         }
    //     }
    // }

    // Send to file
    std::ofstream outfile;
    std::filesystem::create_directories("./bin/results/" + propagator + "/");
    outfile.open("./bin/results/" + propagator +"/main.csv");
    outfile << "time (min),sma (km),ecc,inc (rad),raan (rad),w (rad),theta (rad)\n";
    auto vehicle = walkerBall.get_all_spacecraft()[0];
    for (auto& state: vehicle.get_states()) {
        outfile << state.time.count<minutes>() << ",";
        state.elements.convert(ElementSet::KEPLERIAN, sys);
        for (const auto& x: state.elements) {
            outfile << x << ",";
        }
        outfile << "\n";
    }
    outfile.close();

    return 1;
}

// #include <unordered_map>
// #include <functional>
// #include <string>
// #include <memory>
// #include <array>
// #include <iostream>

// class Force {
// public:
//     Force() = default;
//     virtual ~Force() = default;

//     virtual std::array<double, 3> compute_force(...) const = 0;
// };

// class DerivedForceA : public Force {
// public:
//     DerivedForceA() = default;
//     ~DerivedForceA() = default;

//     std::array<double, 3> compute_force(...) const override {
//         std::array<double, 3> someArray{0.0, 0.0, 0.0};
//         return someArray;
//     }
// };

// class DerivedForceB : public Force {
// public:
//     DerivedForceB() = default;
//     ~DerivedForceB() = default;

//     std::array<double, 3> compute_force(...) const override {
//         std::array<double, 3> someArray{1.0, 1.0, 1.0};
//         return someArray;
//     }

//     void set_coefficients(size_t n) {
//         std::cout << "Size Before: " << _data.size() << std::endl;
//         _data.resize(n);
//         std::cout << "Size After: " << _data.size() << std::endl;
//     }

// private:

//     mutable std::vector<std::vector<double>> _data{};
// };

// std::unique_ptr<Force> build_a() { return std::make_unique<DerivedForceA>(); }
// std::unique_ptr<Force> build_b() { return std::make_unique<DerivedForceB>(); }

// class ForceFactory {
// private:

//     using BuilderFunc = std::function<std::unique_ptr<Force>()>;

//     const std::unordered_map<std::string, BuilderFunc> builders = {
//         {"DerivedForceA",  build_a},
//         {"DerivedForceB",  build_b}
//     };

//     std::unordered_map<std::string, std::unique_ptr<Force>> forces;

// public:
//     // Build call for pre-defined, derived Forces
//     const std::unique_ptr<Force>& build(const std::string& force) {
//         if (forces.count(force) == 0) {
//             forces[force] = builders.at(force)();
//         }
//         return forces[force];
//     }

//     void set_b_coefficients(size_t n) {
//         auto& baseRef = forces.at("DerivedForceB");
//         auto* basePtr = baseRef.get();
//         auto* derived = dynamic_cast< DerivedForceB* >(basePtr);
//         derived->set_coefficients(n);
//     }

//     std::unique_ptr<Force>& operator[](const std::string& force) {
//         return forces[force];
//     }

//     const std::unique_ptr<Force>& at(const std::string& force) const {
//         return forces.at(force);
//     }
// };


// int main() {

//     ForceFactory allForces;
//     allForces.build("DerivedForceA");
//     allForces.build("DerivedForceB");

//     for (int ii = 0; ii < 5; ++ii) {
//         allForces.set_b_coefficients(ii);
//     }

//     for (int ii = 5; ii < 10; ++ii) {
//         auto& baseRef = allForces.at("DerivedForceB");
//         auto* basePtr = baseRef.get();
//         auto* derived = dynamic_cast< DerivedForceB* >(basePtr);
//         derived->set_coefficients(ii);
//     }

//     return 0;
// }