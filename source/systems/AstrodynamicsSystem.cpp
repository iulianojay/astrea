#include "AstrodynamicsSystem.hpp"

using namespace solar_system;

void AstrodynamicsSystem::create_all_bodies() {
    for (const auto body: allBodies) {
        bodyFactory.create(body);
    }
};


void AstrodynamicsSystem::propagate_bodies(double endTime) {

    // Ask factory to propagate
    bodyFactory.propagate_bodies(endTime);

    // Assign properties from central body
    GravitationalBody center = bodyFactory.get(centralBody);

    // Get radius vector from central body
    size_t sizeOfDateArray = centralBody.lengthOfJulianDate();
    double** radiusSunToCenter = new double*[sizeOfDateArray];
    for (int ii = 0; ii < sizeOfDateArray; ++ii) {
        radiusSunToCenter[ii] = new double[3];
        for (int jj = 0; jj < 3; ++jj) {
            radiusSunToCenter[ii][jj] = centralBody.radiusSunToBody()[ii][jj];
        }
    }

    // Create arrays for n body calcs
    double* nBodyGravitationalParameter = new double[allBodies.size()];
    double** radiusSunToNbody = new double*[sizeOfDateArray];
    for (int ii = 0; ii < sizeOfDateArray; ++ii) {
        radiusSunToNbody[ii] = new double[3*allBodies.size()]{};
    }

    for (const auto body: allBodies) {

        // Populate arrays
        const GravitationalBody& ithBody = bodyFactory.get(body);
        for (int jj = 0; jj < sizeOfDateArray; ++jj) {
            radiusSunToNbody[jj][ii*3] = ithBody.radiusSunToBody()[jj][0];
            radiusSunToNbody[jj][ii*3+1] = ithBody.radiusSunToBody()[jj][1];
            radiusSunToNbody[jj][ii*3+2] = ithBody.radiusSunToBody()[jj][2];
        }
    }
}