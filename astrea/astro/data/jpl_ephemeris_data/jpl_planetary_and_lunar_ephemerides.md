*******************************************************************************

JPL PLANETARY AND LUNAR EPHEMERIDES : Export Information  [21 December 2020]

*******************************************************************************

INTRODUCTION

JPL planetary ephemerides are generally created to support spacecraft missions
to the planets. Selected ephemerides are recommended for more general use.

The latest JPL ephemeris with fully consistent treatment of planetary and 
lunar laser ranging data is DE440 (Park et al., 2021). The dynamical model
for DE440 includes a frictional damping between the fluid core and the
elastic mantle. This damping term is not suitable for extrapolation more
than several centuries into the past. In order to cover a longer time span,
the ephemeris DE441 was integrated without the lunar core/mantle damping term.
The positions of the planets for DE441 agree with the positions on DE440 to 
within one meter over the time covered by DE440. For the Moon DE441 differs
from DE440 mainly in the estimated tidal damping term causing a difference
in along-track position of the Moon of ~10 meters 100 years from the present
and growing quadratically for times more thna 100 years from present. 

The JPL planetary ephemerides are saved as files of Chebyshev polynomials fit 
to the Cartesian positions and velocities of the planets, Sun, and Moon, 
typically in 32-day intervals. The positions are integrated in astronomical 
units (au), but with polynomials stored in units of kilometers. The integration
time units are days of barycentric dynamical time (TDB). In DE440, similar
to DE430, the astronomical units has been fixed to the value 149597870.700 km
as adopted by the International Astronomical Union in 2012.

Most JPL planetary ephemeris files include Chebyshev polynomials fit to 
the lunar libration angles, which are integrated along with the planetary 
positions. Many ephemeris files also a fit to the 1980 IAU nutation series. 
While the 1980 IAU nutation series is not current, it is maintained in the 
files for backward compatibility.


ACCESSING THE JPL PLANETARY EPHEMERIDES
------------------------------------------

For users who need positions of planets at a few specific times, 
JPL's interactive website and telnet service, "Horizons", provides a wide 
variety of astronomical information including planetary positions from the 
planetary ephemeris DE441, at web site  http://ssd.jpl.nasa.gov/?horizons .


For users who need the capability of looking up the positions of planets at many
times or as needed for other computations, the recommended means of reading the
ephemerides is through use of the SPICE software toolkit, 
http://naif.jpl.nasa.gov/ .
The SPICE software is supported in several languages (including C, Fortran, 
and Matlab) on multiple platforms and compilers. The SPICE software reads JPL 
planetary ephemerides in a machine-independent binary format (kernels) which 
are available from the SPICE web site and from
https://ssd.jpl.nasa.gov/ftp/eph/planets/bsp/ .


The JPL planetary ephemerides are also available in an ASCII format which are 
converted by the user to machine-dependent binary files for reading. 
The ASCII files are created in blocks of 20 or more years. Later ephemerides 
tend to be stored in longer blocks. When converted into binary format, 
the files can be merged to span a longer time if desired. 
The ASCII files are available from 
https://ssd.jpl.nasa.gov/ftp/eph/planets/ascii/ .
The ascii file format is briefly described in the file
https://ssd.jpl.nasa.gov/ftp/eph/planets/ascii/ascii_format.txt .

The machine-dependent binary files differ mainly in the binary representation
of numbers. The 'little-endian' representation is used by Intel x86, IA64 or 
Alpha based processors (and their clones). Some binary ephemeris files are 
available in this format from https://ssd.jpl.nasa.gov/ftp/eph/planets/Linux/ . 
The 'big endian' representation is used by PowerPC and SPARC processors. 
Some binary files in this format are available from 
https://ssd.jpl.nasa.gov/ftp/eph/planets/SunOS/ .

Fortran programs for converting the ASCII files and for merging and reading
the binary files are available from 
https://ssd.jpl.nasa.gov/ftp/eph/planets/fortran/ . 
These Fortran programs generally require some tailoring by the user. 
Instructions for using these programs are available for downloading from 
https://ssd.jpl.nasa.gov/ftp/eph/planets/fortran/userguide.txt . 
Other programs for reading these formats have been developed independently by 
outside programmers, and not suported directly by JPL, are listed at 
https://ssd.jpl.nasa.gov/ftp/eph/planets/other_readers.txt .


AVAILABLE EPHEMERIDES
---------------------

DE102 : Created September 1981; includes nutations but not librations.
        Referred to the dynamical equator and equinox of 1950.
        Covers JED 1206160.5 (-1410 APR 16) to JED 2817872.5 (3002 DEC 22).

DE200 : Created September 1981; includes nutations but not librations.
        Referred to the dynamical equator and equinox of 2000.
        Covers JED 2305424.5 (1599 DEC 09)  to  JED 2513360.5 (2169 MAR 31).
        This ephemeris was used for  the Astronomical Almanac from 1984 to 2003.
        (See Standish, 1982 and Standish, 1990).

DE202 : Created October 1987; includes nutations and librations.
        Referred to the dynamical equator and equinox of 2000.
        Covers JED 2414992.5 (1899 DEC 04) to  JED 2469808.5 (2050 JAN 02).

DE403 : Created May 1993; includes nutations and librations.
        Referred to the International Celestial Reference Frame.
        Covers JED 2305200.5 (1599 APR 29) to  JED 2524400.5 (2199 JUN 22).
        Fit to planetary and lunar laser ranging data.
        (See Folkner et al. 1994).

DE405 : Created May 1997; includes both nutations and librations.
        Referred to the International Celestial Reference Frame.
        Covers JED 2305424.50  (1599 DEC 09)  to  JED 2525008.50  (2201 FEB 20)

DE406 : Created May 1997; includes neither nutations nor librations.
        Referred to the International Celestial Reference Frame.
        Spans JED 0625360.5 (-3000 FEB 23) to 2816912.50 (+3000 MAY 06)

        This is the same integration as DE405, with the accuracy of the 
        interpolating polynomials has been lessened to reduce file size
        for the longer time span covered by the file.

DE410 : Created April 2003; includes nutations and librations.
        Referred to the International Celestial Reference Frame.
        Covers JED 2415056.5 (1900 FEB 06) to JED 2458832.5 (2019 DEC 15).
        Ephemeris used for Mars Exploration Rover navigation.

DE413 : Created November 2004; includes nutations and librations.
        Referred to the International Celestial Reference Frame.
        Covers JED 2414992.5, (1899 DEC 04) to JED 2469872.5 (2050 MAR 07).

        Created to update the orbit of Pluto to aid in planning
        for an occultation of a relatively bright star by Charon on 11 July 2005.

DE414 : Created May 2005; includes nutations and librations.
        Covers JED 2414992.5, (1899 DEC 04) to JED 2469872.5 (2050 MAR 07).

        Fit to ranging data from MGS and Odyssey through 2003.
        (See Konopliv et al., 2006.)

DE418 : Created August 2007; includes nutations and librations.
        Covers JED 2414864.5 (1899 JUL 29) to JED 2470192.5 (2051 JAN 21)

DE421 : Created Feb 2008; includes nutations and librations.
        Referred to the International Celestial Reference Frame.
        Covers JED 2414864.5 (1899 JUL 29) to JED 2471184.5 (2053 OCT 09)

        Fit to planetary and lunar laser ranging data.
        (See Folkner et al., 2009)

DE422 : Created September 2009; includes nutations and librations.
        Referred to the International Celestial Reference Frame.
        Covers JED 625648.5, (-3000 DEC 07) to JED 2816816.5, (3000 JAN 30).

        Intended for the MESSENGER mission to Mercury.
        Extended integration time to serve as successor to DE406.
        Fit to ranging data from MGS and Odyssey through 2003.
        (See Konopliv et al., 2010.)

DE423 : Created February 2010; includes nutations and librations.
        Referred to the International Celestial Reference Frame version 2.0.
        Covers JED 2378480.5, (1799 DEC 16) to JED  2524624.5, (2200 FEB 02).

        Intended for the MESSENGER mission to Mercury.

DE430 : Created April 2013; includes librations and 1980 nutation.
        Referred to the International Celestial Reference Frame version 2.0.
        Covers JED 2287184.5, (1549 DEC 21) to JED 2688976.5, (2650 JAN 25).

DE431 : Created April 2013; includes librations and 1980 nutation.
        Referred to the International Celestial Reference Frame  version 2.0.
        Covers JED -3100015.5, (-13200 AUG 15) to JED 8000016.5,(17191 MAR 15).

        DE430 and DE431 are documented in the following document:
        http://ipnpr.jpl.nasa.gov/progress_report/42-196/196C.pdf

DE432 : Created April 2014; includes librations but no nutations.
        Referred to the International Celestial Reference Frame  version 2.0.
        Covers JED 2287184.5, (1549 DEC 21) to JED 2688976.5, (2650 JAN 25).

        DE432 is a minor update to DE430, and is intended primarily to
        aid the New Horizons project targeting of Pluto.

DE440 : Created June 2020; compared to DE430, about 7 years of new data have
        beend added.
        Referred to the International Celestial Reference Frame version 3.0.
        Covers JED 2287184.5, (1549 DEC 31) to JED 2688976.5, (2650 JAN 25).

DE441 : Created June 2020; compared to DE431, about 7 years of new data have 
        been added.
        Referred to the International Celestial Reference Frame version 3.0.
        Covers JED -3100015.5, (-13200 AUG 15) to JED 8000016.50, (17191 MAR 15).

        DE440 and DE441 are documented in the following document:
        https://doi.org/10.3847/1538-3881/abd414
        (NOTE: this paper has been accepted for publication in December, 2020;
         this link will become available sometime in January)

REFERENCES
----------

 Park et al., The JPL Planetary and Lunar Ephemerides DE440 and DE441, 2021
  https://doi.org/10.3847/1538-3881/abd414
        (NOTE: this paper has been accepted for publication in December, 2020;
         this link will become available sometime in January)

 Folkner et al., JPL Interplanetary Network Progress Report 42-196, 2014
  http://ipnpr.jpl.nasa.gov/progress_report/42-196/196C.pdf

 Konopliv et al., Icarus v. 211, pp. 401-428, 2011.

 Folkner et al., JPL Interplanetary Network Progress Report 24-178, 2009
   http://ipnpr.jpl.nasa.gov/progress_report/42-178/178C.pdf

 Konopliv et al., Icarus v. 182, pp. 23-26, 2006.

 Standish, E.M.: 1998, "JPL Planetary and Lunar Ephemerides,
   DE405/LE405",JPL IOM  312.F-98-048. 

 Standish, E.M., Newhall, X X, Williams, J.G. and Folkner, W.F.: 1995, 
   "JPL Planetary and Lunar Ephemerides, DE403/LE403", JPL IOM 314.10-127.

 Folkner et al., Astronomy and Astrophysics v. 287, pp. 279-289, 1994.

 Standish, E.M.: 1990, "The Observational Basis for JPL's DE200, the 
   planetary ephemeris of the Astronomical Almanac", Astronomy & Astrophysics,
   vol. 233, pp. 252-271.

 Newhall, X X, Standish, E.M. and Williams, J.G.: 1983, "DE102: a numerically 
   integrated ephemeris of the Moon and planets spanning forty-four centuries",
   Astronomy & Astrophysics, vol. 125, pp. 150-167.

 Standish, E.M.: 1982, "Orientation of the JPL Ephemerides, DE200/LE200, to 
   the Dynamical Equinox of J2000", Astronomy & Astrophysics, vol. 114, 
   pp. 297-302.

ASSISTANCE
----------

Questions may be addressed to;

Ryan Park; JPL m/s 301-121; Pasadena, CA  91109
e-mail: ryan.s.park@jpl.nasa.gov                 