#ifndef MATH_CONST_H
#define MATH_CONST_H 

// Constants
static const double PI = 3.14159265358979323846264338;

// Conversions
static const double RAD_TO_DEG = 180.0/PI;
static const double DEG_TO_RAD = PI/180.0;

static const double DAY_TO_SEC = 86400.0;
static const double SEC_TO_DAY = 1.0/86400.0;

static const double YEAR_TO_DAY = 365.25;
static const double DAY_TO_YEAR = 1.0/365.25;

static const double YEAR_TO_SEC = 31556926.0;
static const double SEC_TO_YEAR = 1.0/31556926.0;

static const double KM_TO_M = 1000.0;
static const double M_TO_KM = 0.001;

static const double KM_TO_AU = 1.0/1.49597871e8;
static const double AU_TO_KM = 1.49597871e8;

#endif//MATH_CONST_H