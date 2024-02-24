#include "GravitationalBody.hpp"

// Constructors 
GravitationalBody::GravitationalBody() {
    assign_properties("Earth");

    double jdTemp = J2000;
    set_dates(&jdTemp, 1);
}

GravitationalBody::GravitationalBody(std::string inputName) {
    assign_properties(inputName);

    double jdTemp = J2000;
    set_dates(&jdTemp, 1);
}

// Destructor
GravitationalBody::~GravitationalBody() {

    if (_lengthJulianDate > 1) {
        for (int ii = 0; ii < _lengthJulianDate; ++ii) {
            delete[] _radiusParentToBody[ii];
            delete[] _velocityParentToBody[ii];
            delete[] _radiusSunToBody[ii];
            delete[] _velocitySunToBody[ii];
        }
        delete[] _julianDate;
    }
    else {
        delete _julianDate;
    }

    delete[] _radiusParentToBody;
    delete[] _velocityParentToBody;
    delete[] _radiusSunToBody;
    delete[] _velocitySunToBody;
}

// Separate function to assign values so the class isn"t created twice
void GravitationalBody::assign_properties(std::string inputName) {

    _name = _nameMap.at(inputName);

    // Identify object 
    _planetId = _idMap.at(_name).first;
    _moonId = _idMap.at(_name).second;

    // Assign body class and parent
    _type = _typeMap.at(_name);
    _parent = _parentMap.at(_name);

    // Assign physical properties
    // Assign all properties from the astronomical_constants header
    _gravitationalParameter = gravitataionalParameter [_moonId][_planetId];
    _mass                   = mass [_moonId][_planetId];
    _equitorialRadius       = equatorialRadius [_moonId][_planetId];
    _polarRadius            = polarRadius [_moonId][_planetId];
    _crashRadius            = crashRadius [_moonId][_planetId];
    _sphereOfInfluence      = sphereOfInfluence [_moonId][_planetId];

    _j2 = j2Oblateness[_moonId][_planetId];
    _j3 = j3Oblateness[_moonId][_planetId];

    _axialTilt      = axisTilt[_moonId][_planetId];
    _rotationRate   = rotationalRate[_moonId][_planetId];
    _siderealPeroid = siderealPeriod[_moonId][_planetId];

    // Assign orbital properties
    _semimajorAxis      = semimajorAxis[_moonId][_planetId];
    _eccentricity       = eccentricity[_moonId][_planetId];
    _inclination        = inclination[_moonId][_planetId];
    _rightAscension     = rightAscension[_moonId][_planetId];
    _argumentOfPerigee  = argumentOfPerigee[_moonId][_planetId];
    _trueLatitude       = trueLatitude[_moonId][_planetId];

    if (_moonId == 0) {
        _semimajorAxisRate      = semimajorAxisRate[_moonId][_planetId];
        _eccentricityRate       = eccentricityRate[_moonId][_planetId];
        _inclinationRate        = inclinationRate[_moonId][_planetId];
        _rightAscensionRate     = rightAscensionRate[_moonId][_planetId];
        _argumentOfPerigeeRate  = argumentOfPerigeeRate[_moonId][_planetId];
        _trueLatitudeRate       = trueLatitudeRate[_moonId][_planetId];
    }
    else {
        _semimajorAxisRate = 0.0;
        _eccentricityRate = 0.0;
        _inclinationRate = 0.0;
        _rightAscensionRate = 0.0;
        _argumentOfPerigeeRate = 0.0;
        _trueLatitudeRate = 0.0;
    }
}

void GravitationalBody::set_dates(double* inputJulianDate, int inputLengthJulianDate) {
    // Assign julian date 
    _lengthJulianDate = inputLengthJulianDate;
    _julianDate = new double[_lengthJulianDate];

    // Create appropriately sized arrays
    _radiusParentToBody   = new double*[_lengthJulianDate];
    _velocityParentToBody = new double*[_lengthJulianDate];
    _radiusSunToBody      = new double*[_lengthJulianDate];
    _velocitySunToBody    = new double*[_lengthJulianDate];
    for (int ii = 0; ii < _lengthJulianDate; ++ii) {
        _julianDate[ii] = inputJulianDate[ii];

        _radiusParentToBody[ii]   = new double[3];
        _velocityParentToBody[ii] = new double[3];
        _radiusSunToBody[ii]      = new double[3];
        _velocitySunToBody[ii]    = new double[3];
    }

    // Find State Values
    find_radius_to_parent();
    find_radius_to_sun();
}

// Find position of body relative to parent and relative to the sun
void GravitationalBody::find_radius_to_parent() {

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
	double referenceJulianDate{};
	double parentMu{};
	switch (_type) {
        case GC:
            referenceJulianDate = 2451545;  // Jan 1, 2000 00:00:00
            parentMu = DBL_MAX;
        case (Star || Planet):
            referenceJulianDate = 2451545;  // Jan 1, 2000 00:00:00
            parentMu = gravitataionalParameter[0][0];
            break;
        case Satellite:
            switch (_parent) {
                case Earth:
                    referenceJulianDate = 2451545.5; // Jan 1, 2000 12:00:00
                    break;
                case Mars:
                    referenceJulianDate = 2433282.5; // Jan 1, 1950 00:00:00
                    break;
                case Jupiter:
                    referenceJulianDate = 2450465;   // Jan 16, 1997 00:00:00
                    break;
                case Saturn:
                    referenceJulianDate = 2451545.5; // Jan 1, 2000 12:00:00
                    break;
                case Uranus:
                    referenceJulianDate = 2444240;   // Jan 1, 1980 00:00:00
                    break;
                case Neptune:
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

	// Variables for loop
	double t{};

	double at{};
	double ecct{};
	double inct{};
	double raant{};
	double wt{};
	double Lt{};

	double ht{};
	double Met{};
	double thetat{};

	double ecct_2{};
	double ecct_3{};
	double ecct_4{};
	double ecct_5{};

	double ct{};
	double st{};
	double ci{};
	double si{};
	double cr{};
	double sr{};
	double cw{};
	double sw{};

	double coes2perir{};
	double coes2periv{};

	double xPerifocal{};
	double yPerifocal{};
	double vxPerifocal{};
	double vyPerifocal{};

	double DCM_xx{};
	double DCM_xy{};
	double DCM_yx{};
	double DCM_yy{};
	double DCM_zx{};
	double DCM_zy{};

	const double pi = 3.141592653575;
    const double rad2deg = 180.0/pi;
    const double deg2rad = pi/180.0;

	// Fruit loop
    for (int ii = 0; ii < _lengthJulianDate; ++ii) {
        // Time since reference date
        t = (_julianDate[ii] - referenceJulianDate)/36525; // Julian Centuries

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
        ecct_2 = pow(ecct, 2); ecct_3 = pow(ecct, 3);
        ecct_4 = pow(ecct, 4); ecct_5 = pow(ecct, 5);

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
        _radiusParentToBody[ii][0] = DCM_xx*xPerifocal  + DCM_xy*yPerifocal;
        _radiusParentToBody[ii][1] = DCM_yx*xPerifocal  + DCM_yy*yPerifocal;
        _radiusParentToBody[ii][2] = DCM_zx*xPerifocal  + DCM_zy*yPerifocal;

        _velocityParentToBody[ii][0] = DCM_xx*vxPerifocal + DCM_xy*vyPerifocal;
        _velocityParentToBody[ii][1] = DCM_yx*vxPerifocal + DCM_yy*vyPerifocal;
        _velocityParentToBody[ii][2] = DCM_zx*vxPerifocal + DCM_zy*vyPerifocal;
    }
}

void GravitationalBody::find_radius_to_sun() {

	switch (_type) {
		case Star:
			for (int ii = 0; ii < _lengthJulianDate; ++ii) {
                _radiusSunToBody[ii][0] = 0.0;
                _radiusSunToBody[ii][1] = 0.0;
                _radiusSunToBody[ii][2] = 0.0;

                _velocitySunToBody[ii][0] = 0.0;
                _velocitySunToBody[ii][1] = 0.0;
                _velocitySunToBody[ii][2] = 0.0;
			}
            break;

		case Planet:
			for (int ii = 0; ii < _lengthJulianDate; ++ii) {
                for (int jj = 0; jj < 3; ++jj) {
				    _radiusSunToBody[ii][jj] = _radiusParentToBody[ii][jj];
				    _velocitySunToBody[ii][jj] = _velocityParentToBody[ii][jj];
                }
			}
            break;
            
		case Satellite:
			// Construct parent body
			GravitationalBody *parentBody = new GravitationalBody(_mapName.at(_parent));
            parentBody->set_dates(_julianDate, _lengthJulianDate);

			// Find state relative to sun
			for (int ii = 0; ii < _lengthJulianDate; ++ii) {
                for (int jj = 0; jj < 3; ++jj) {
                    _radiusSunToBody[ii][jj] = parentBody->radiusParentToBody()[ii][jj] + _radiusParentToBody[ii][jj];
                    _velocitySunToBody[ii][jj] = parentBody->velocityParentToBody()[ii][jj] + _velocityParentToBody[ii][jj];
                }
			}

			// Destroy parent body
			delete parentBody;
            break;
	}
}

