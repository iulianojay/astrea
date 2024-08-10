#include "GravitationalBody.hpp"

void GravitationalBody::propagate(Date epoch, double propTime) {
    Date endEpoch = epoch + Time(propTime);
    _propagate(epoch, endEpoch);
}
void GravitationalBody::propagate(Date epoch, Time propTime) {
    Date endEpoch = epoch + propTime;
    _propagate(epoch, endEpoch);
}
void GravitationalBody::propagate(Date epoch, Date endEpoch) {
    _propagate(epoch, endEpoch);
}

void GravitationalBody::_propagate(Date epoch, Date endEpoch) {

    // Find duration 
    _nDays = round(endEpoch.julian_day() - epoch.julian_day());

    // Find State Values
    find_state_relative_to_parent(epoch, endEpoch);
}

// Find position of body relative to parent and relative to the sun
void GravitationalBody::find_state_relative_to_parent(Date epoch, Date endEpoch) {

	// Get reference date
	/*
	phobos/deimos   Epoch: 1950, Jan. 1.00 , TT -> julianDate = 2433282.5
	jupiter         Epoch: 1997, Jan. 16.00, TT -> julianDate = 2450465
	uranus          Epoch: 1980, Jan. 1.0  , TT -> julianDate = 2444240
	moon            Epoch: 2000, Jan. 1.50 , TT -> julianDate = 2451545.5
	saturn          Epoch: 2000, Jan. 1.50 , TT -> julianDate = 2451545.5
	neptune         Epoch: 2000, Jan. 1.50 , TT -> julianDate = 2451545.5

	UTC = TT - 64 seconds
	*/
	int referenceJulianDate;
	double parentMu{};
	switch (_type) {
        case solar_system::GC:
            referenceJulianDate = 2451545;  // Jan 1, 2000 00:00:00
            parentMu = DBL_MAX;
            break;

        case (solar_system::STAR || solar_system::PLANET):
            referenceJulianDate = 2451545;  // Jan 1, 2000 00:00:00
            parentMu = gravitataionalParameter[0][0];
            break;

        case solar_system::SATELLITE:
            switch (_parent) {
                case solar_system::EARTH:
                    referenceJulianDate = 2451545.5; // Jan 1, 2000 12:00:00
                    break;
                case solar_system::MARS:
                    referenceJulianDate = 2433282.5; // Jan 1, 1950 00:00:00
                    break;
                case solar_system::JUPITER:
                    referenceJulianDate = 2450465;   // Jan 16, 1997 00:00:00
                    break;
                case solar_system::SATURN:
                    referenceJulianDate = 2451545.5; // Jan 1, 2000 12:00:00
                    break;
                case solar_system::URANUS:
                    referenceJulianDate = 2444240;   // Jan 1, 1980 00:00:00
                    break;
                case solar_system::NEPTUNE:
                    referenceJulianDate = 2451545.5; // Jan 1, 2000 12:00:00
                    break;
                default:
                    throw std::invalid_argument("Object's parent not found.");
            }
            parentMu = gravitataionalParameter[0][_planetId];
            break;

        default:
            throw std::invalid_argument("Object's type not found.");
	}
    Date refJulianDate = JulianDate(JulianDateClock::duration(referenceJulianDate));

	// Variables for loop
	double t{}, at{}, ecct{}, inct{}, raant{}, wt{}, Lt{}, ht{}, Met{}, thetat{}, 
        ecct_2{}, ecct_3{}, ecct_4{}, ecct_5{}, ct{}, st{}, ci{}, si{}, cr{}, sr{}, cw{}, sw{},
        coes2perir{}, coes2periv{}, xPerifocal{}, yPerifocal{}, vxPerifocal{}, vyPerifocal{},
        DCM_xx{}, DCM_xy{}, DCM_yx{}, DCM_yy{}, DCM_zx{}, DCM_zy{};

	const double pi = 3.141592653575;
    const double rad2deg = 180.0/pi;
    const double deg2rad = pi/180.0;

	// Loop over each day in the epoch range
    for (int ii = 0; ii < _nDays; ++ii) {
        // Time since reference date
        Time jd = epoch.julian_day() + ii;
        t = (jd.count() - refJulianDate.julian_day())/36525; // time in Julian Centuries

        // COEs
        at = _semimajorAxis + _semimajorAxisRate*t;
        ecct = _eccentricity + _eccentricityRate*t;
        inct = _inclination + _inclinationRate*t;
        raant = _rightAscension + _rightAscensionRate*t;
        wt = _argumentOfPerigee + _argumentOfPerigeeRate*t;
        Lt = _trueLatitude + _trueLatitudeRate*t;

        // Calculations
        ht = pow(parentMu*at*(1 - ecct*ecct), 0.5);
        wt = wt - raant;
        Met = (Lt - wt)*deg2rad;

        // This approximation has error on the order of ecc^6. It is
        // assumed to be good for this calc since all these bodies are
        // nearly circular. Solving Kepler"s equations takes a very long
        // time
        ecct_2 = ecct*ecct; 
        ecct_3 = ecct_2*ecct;
        ecct_4 = ecct_3*ecct;
        ecct_5 = ecct_4*ecct;

        thetat = (Met + (2.0*ecct - 0.25*ecct_3 + 5.0/96.0*ecct_5)*sin(Met) + (1.25*ecct_2 - 11.0/24.0*ecct_4)*sin(2.0*Met) +
            (13.0/12.0*ecct_3 - 43.0/64.0*ecct_5)*sin(3.0*Met) + 103.0/96.0*ecct_4*sin(4*Met) + 1097.0/960.0*ecct_5*sin(5*Met))*rad2deg;

        // Store mean and true anomaly
        _meanAnomaly = Met;
        _trueAnomaly = thetat;

        // Calculate once for speed
        ct = cos(thetat*deg2rad); st = sin(thetat*deg2rad);
        cw = cos(wt*deg2rad);     sw = sin(wt*deg2rad);
        cr = cos(raant*deg2rad);  sr = sin(raant*deg2rad);
        ci = cos(inct*deg2rad);   si = sin(inct*deg2rad);

        coes2perir = ht*ht/parentMu/(1 + ecct*ct);
        coes2periv = parentMu/ht;

        // Perifocal frame
        // z_peri is 0 by definition
        xPerifocal = coes2perir*ct;
        yPerifocal = coes2perir*st;

        vxPerifocal = -coes2periv*st;
        vyPerifocal = coes2periv*(ecct + ct);

        // Translate to inertial frame
        /*
         DCM_peri2ECI = | cw sw 0|*|1   0  0|*| cr sr 0|
                        |-sw cw 0| |0  ci si| |-sr cr 0|
                        |  0  0 1| |0 -si ci| |  0  0 1|
        */
        DCM_xx = cw*cr - ci*sw*sr;
        DCM_xy = -sw*cr - ci*cw*sr;
        DCM_yx = cw*sr + ci*sw*cr;
        DCM_yy = -sw*sr + ci*cw*cr;
        DCM_zx = si*sw;
        DCM_zy = si*cw;

        // Find radius and velocity vector
        double bciState[6];
        bciState[0] = DCM_xx*xPerifocal  + DCM_xy*yPerifocal;
        bciState[1] = DCM_yx*xPerifocal  + DCM_yy*yPerifocal;
        bciState[2] = DCM_zx*xPerifocal  + DCM_zy*yPerifocal;

        bciState[3] = DCM_xx*vxPerifocal + DCM_xy*vyPerifocal;
        bciState[4] = DCM_yx*vxPerifocal + DCM_yy*vyPerifocal;
        bciState[5] = DCM_zx*vxPerifocal + DCM_zy*vyPerifocal;

        // Store
        State state(jd, bciState, ElementSet::CARTESIAN);
        _states.push_back(state);
    }
}

