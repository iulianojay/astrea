The original fortran programs for reading ascii versions of the
JPL planetary ephemeris files had a fixed maximum number of 400
for the number of ephemeris constants used in the integration
and listed in the header.xxx file for the ephemeris.

DE430 uses 572 ephemeris constants, which exceeds the prior
maximum number allowed.

In this directory, there are two header files included.

Use header.430_229 if using an old program with 400 maximum
ephemeris constants. The header.430_229 file includes a list
of only 229 ephemeris constants, omitting the mass parameters
for 343 individual asteroids modeled in the de430 integration.
Using this header will only omit the asteroid mass parameters
from the binary ephemeris file; position and velocity information
will be unaffected.

Use header.430_572 if using a program that allows more than 400
ephemeris constants.

***********************************************************

Also, this set of files does not include information on TT-TDB
which was integrated as part of the de430 development.
The TT-TDB information is available in ascii format in the
directory de430t.