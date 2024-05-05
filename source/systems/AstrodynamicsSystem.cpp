#include "AstrodynamicsSystem.hpp"

using namespace solar_system;

void AstrodynamicsSystem::create_all_bodies() {
    for (const auto body: allBodies) {
        bodyFactory.create(body);
    }
};


void AstrodynamicsSystem::propagate_bodies(double propTime) {

    // Ask factory to propagate
    bodyFactory.propagate_bodies(epoch, propTime);

    // Assign properties from central body
    GravitationalBody center = bodyFactory.get(centralBody);

    // Get radius vector from central body
    size_t sizeOfDateArray = center.nDays();
    double** radiusParentToCenter = new double*[sizeOfDateArray];
    for (int ii = 0; ii < sizeOfDateArray; ++ii) {
        radiusParentToCenter[ii] = new double[3];
        for (int jj = 0; jj < 3; ++jj) {
            radiusParentToCenter[ii][jj] = center.radiusParentToBody()[ii][jj];
        }
    }

    // Create arrays for n body calcs
    double* nBodyGravitationalParameter = new double[allBodies.size()];
    double** radiusParentToNbody = new double*[sizeOfDateArray];
    for (int ii = 0; ii < sizeOfDateArray; ++ii) {
        radiusParentToNbody[ii] = new double[3*allBodies.size()]{};
    }

    int ii = 0;
    for (const auto body: allBodies) {

        // Populate arrays
        GravitationalBody ithBody = bodyFactory.get(body);
        for (int jj = 0; jj < sizeOfDateArray; ++jj) {
            radiusParentToNbody[jj][ii*3] = ithBody.radiusParentToBody()[jj][0];
            radiusParentToNbody[jj][ii*3+1] = ithBody.radiusParentToBody()[jj][1];
            radiusParentToNbody[jj][ii*3+2] = ithBody.radiusParentToBody()[jj][2];
        }
        ii++;
    }
}