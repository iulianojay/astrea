# Adapted from https://github.com/mschmit6/jpl_ephemeris.git

from enum import IntEnum
import numpy as np
import os
import argparse

ASTREA_ROOT = os.getenv("ASTREA_ROOT")

def parse_header_file(headerFile):
    """
    Pull the table out of the DE header file, which is located between the tags "GROUP   1050" and "GROUP   1070"
    
    Returns:
        ndarray: Numpy array containing the header table 
        float: Earth/Moon mass ratio

    """

    def parse_group_1040(linesGroup1040):
        """
        Simply identify the index in the block for EMRAT
        """
        linesGroup1040 = linesGroup1040[2:]

        splitBlock = []
        for line in linesGroup1040:
            if line.strip() == "":
                continue
            else:
                splitBlock.extend(line.strip().split())

        # Now identify index of EMRAT
        for ind, val in enumerate(splitBlock):
            if val == "EMRAT":
                return ind

        return None

    def parse_group_1041(linesGroup1041, emratIdx):
        """
        Return the Earth/Moon mass ratio
        """
        linesGroup1041 = linesGroup1041[2:]

        splitBlock = []
        for line in linesGroup1041:
            if line.strip() == "":
                continue
            else:
                splitBlock.extend(line.strip().split())

        return float(splitBlock[emratIdx].replace("D", "e"))
        
    def parse_group_1050(lines_group_1050):
        # Put the header lines into a numpy array
        jplEphemHeader = []
        for line in lines_group_1050:
            if line.strip() == "":
                continue
            else:
                jplEphemHeader.append(list(map(int, line.strip().split())))
        return jplEphemHeader

    with open(headerFile, 'r') as fID:
        lines = fID.readlines()

    # Parse the file into groupes
    group = None
    groupLines = {'1040': [], '1041': [], '1050': []}

    # Discard the lines until we get to the line containing "GROUP   1050"
    for line in lines:
        if "GROUP" in line:
            group = line.split()[1].strip()
            continue
        elif group is None:
            continue
        else:
            if group == "1040":
                groupLines['1040'].append(line)
            elif group == "1041":
                groupLines['1041'].append(line)
            elif group == "1050":
                groupLines['1050'].append(line)

    emratIdx = parse_group_1040(groupLines['1040'])
    if emratIdx is None:
        raise Exception("Failed to parse out the EMRAT value from header file")
    emratio = parse_group_1041(groupLines['1041'], emratIdx)
    jplEphemHeader = parse_group_1050(groupLines['1050'])
    return emratio, np.asarray(jplEphemHeader)

class CelestialBodies(IntEnum):
    """
    Celestial bodies in the order that they appear in the JPL ephemeris header. An example table is shown below

    GROUP   1050

        Me   V    EMB   Mars  Jup   Sat   Ura   Nep   Plu   Moon   Sun
        3   171   231   309   342   366   387   405   423   441   753   819   899  1019  1019
        14   10    13    11     8     7     6     6     6    13    11    10    10     0     0
        4     2     2     1     1     1     1     1     1     8     2     4     4     0     0

    """
    Mercury = 0,        # Mercury from SSB
    Venus = 1,          # Venus from SSB
    EMB = 2,            # EMB from SSB
    Mars = 3,           # Mars from SSB
    Jupiter = 4,        # Jupiter from SSB
    Saturn = 5,         # Saturn from SSB
    Uranus = 6,         # Uranus from SSB
    Neptune = 7,        # Neptune from SSB
    Moon = 8,           # Moon geocentric position
    Sun = 9,            # Sun from SSB
    EarthFromEMB = 10   # Earth from EMB


def get_table_parameters(celestialBody: CelestialBodies, jplEphemHeader: np.ndarray):
    """
    Get start index, end index, and number of polynomials for each Celestial Body

    Arguments:
        celestialBody (CelestialBodies): Enum value representing the celestial body
        jplEphemHeader (np.ndarray): Numpy array containing the header table 

    Returns:
        tuple: Tuple containing the following values
            - **startIdx** `(int)`: Index in the JPL ephemeris file at which the celestial body's polynomial coefficients start
            - **stopIdx** `(int)`: Index in the JPL ephemeris file at which the celestial body's polynomial coefficients stop
            - **coeff_per_poly** `(int)`: Number of coefficients per polynomial
            - **nPoly** `(int)`: Number of polynomials required to model the body over the 32 day period
            - **daysPerPoly** `(int)`: Number of days each polynomial represents

    """
    # Get integer value for the CelestialBody
    cbIdx = celestialBody.value

    # Extract table information. Note that start/stop index you subtract 1 since Python is 0 based
    startIdx = jplEphemHeader[0, cbIdx] - 1
    stopIdx = jplEphemHeader[0, cbIdx + 1] - 1
    coeffPerPoly = jplEphemHeader[1, cbIdx]
    nPoly = jplEphemHeader[2, cbIdx]
    daysPerPoly = 32.0 / nPoly

    return startIdx, stopIdx, coeffPerPoly, nPoly, daysPerPoly


def jd_to_mjdj2k(jd: float) -> float:
    """
    Convert Julian Date to Modified Julian Date from the J2000 Epoch

    """
    return jd - 2451545.0


def read_in_blocks(files: list):
    """
    Read in blocks from multiple files, and concactinate them into a set of blocks

    Arguments:
        files (list[str]): List of filenames to parse

    Returns:
        list[list]: Each block from the files, as a list of floating point values

    """

    # Type check to make sure that it is a list being passed in
    if isinstance(files, str):
        files = [files]

    # read all lines from the file
    lines = []
    for file in files:
        with open(file, 'r') as fID:
            newLines = fID.readlines()
            lines += newLines


    # Split each line up into corresponding "blocks"
    blockLines = []
    curBlock = ""

    for line in lines:
        splitLine = line.strip().split()

        # Check for the header line
        if len(splitLine) == 2:
            if splitLine[1] == "1018":
                if len(curBlock) > 0:
                    blockLines.append(curBlock)
                curBlock = ""
        else:
            curBlock += line

    # Append the last block
    blockLines.append(curBlock)

    # Split each block up into a list of floating point values
    floatLines = [convert_to_float(line.split()) for line in blockLines]

    return floatLines



def write_to_file(outPath: str, relPath: str, className: str, nEntries : int, daysPerPoly: float, xCoeffStr: list, yCoeffStr: list, zCoeffStr: list):
    """
    Format and write x, y, z position coefficients to file
    """

    # Common strings
    warningString = "//!!!!!!! WARNING: Autogenerated file, do not edit !!!!!!!\n"
    subTypeString = f"std::array<double, {nEntries}>"
    typeString = f"const std::array<{subTypeString}, {len(xCoeffStr)}>"

    # Build output directory if it doesn't exist
    outDir = os.path.join(outPath, relPath)
    os.makedirs(outDir, exist_ok=True)

    # Write header file
    header = f"{relPath}/{className}.hpp"
    headerfile = os.path.join(outPath, header)
    if (os.path.exists(headerfile)):
        print(f" -- {headerfile} already exists, skipping rebuild...")
        return
    with open(headerfile, 'w+') as fID:

        fID.write(warningString)

        fID.write(f"#pragma once\n\n")
        fID.write(f"#include <array>\n")
        fID.write(f"#include <units/units.hpp>\n")
        fID.write(f"#include <astro/time/Date.hpp>\n\n")
        fID.write(f"#include <astro/systems/planetary_bodies/JplEphemerisTable.hpp>\n\n")
        fID.write(f"namespace astrea {{\n")
        fID.write(f"namespace astro {{\n")
        fID.write(f"namespace planetary_bodies {{\n\n")
        fID.write(f"struct {className} : public JplEphemerisTable {{\n")

        # Write number of days per poly at the top
        fID.write(f"static constexpr Time TIME_PER_COEFFICIENT = {daysPerPoly} * mp_units::non_si::day;\n")

        # Write the x coefficients to file
        fID.write(f"static {typeString} X_INTERP;\n")
        fID.write(f"static {typeString} Y_INTERP;\n")
        fID.write(f"static {typeString} Z_INTERP;\n")

        fID.write("};\n\n")
        fID.write(f"}} // namespace astrea \n")
        fID.write(f"}} // namespace astro \n")
        fID.write(f"}} // namespace planetary_bodies \n\n")

    # Write source file
    sourcefile = os.path.join(outPath, f"{relPath}/{className}.cpp")
    with open(sourcefile, 'w+') as fID:
        fID.write(warningString)

        fID.write(f"#include <ephemerides/{header}>\n\n")
        fID.write(f"namespace astrea {{\n")
        fID.write(f"namespace astro {{\n")
        fID.write(f"namespace planetary_bodies {{\n\n")

        # Write the x coefficients to file
        fID.write(f"{typeString} {className}::X_INTERP {{\n")
        for x in xCoeffStr:
            fID.write(f"\t{subTypeString} {{{x}}},\n")
        fID.write("};\n\n")
        fID.write("//-------------------------------------------------\n")
        fID.write("//-------------------------------------------------\n\n")

        # Write the y coefficients to file
        fID.write(f"{typeString} {className}::Y_INTERP {{\n")
        for y in yCoeffStr:
            fID.write(f"\t{subTypeString} {{{y}}},\n")
        fID.write("};\n\n")
        fID.write("//-------------------------------------------------\n")
        fID.write("//-------------------------------------------------\n\n")

        # Write the z coefficients to file
        fID.write(f"{typeString} {className}::Z_INTERP {{\n")
        for z in zCoeffStr:
            fID.write(f"\t{subTypeString} {{{z}}},\n")
        fID.write("};\n\n")
        fID.write("//-------------------------------------------------\n")
        fID.write("//-------------------------------------------------\n\n")

        fID.write(f"}} // namespace astrea \n")
        fID.write(f"}} // namespace astro \n")
        fID.write(f"}} // namespace planetary_bodies \n\n")

    return


def convert_to_float(words):
    """
    Convert values from strings to floating point values

    Arguments:
        words (list[str]): List of string values to be converted to floating points

    Returns:
        list[str]: Corresponding list of floating point values

    """
    return [float(word.replace("D", "e")) if "D" in word else float(word) for word in words ]


def duplicate_start_date(startMjdVals, curMjdStart):
    """
    Function to prevent duplicate start dates when multiple files are used
    
    """
    for mjd in startMjdVals:
        if curMjdStart == mjd:
            return True

    return False


def generate_ephemeris_file(lineBlocks: list, em_ratio: float, mjd0: float, mjdF: float, celestialBody: CelestialBodies, jplEphemHeader: np.ndarray, outPath: str):
    """
    Extract the Chebyshev coefficients for the specified liens, given an initial and final MJD from the J2000 Epoch

    Arguments:
        lineBlocks (list[list]): List of floating point values representing each block
        em_ratio (float): Earth/Moon mass ratio
        mjd0 (float): Initial value of MJD from the J2000 Epoch
        mjdF (float): Final value of MJD from the J2000 Epoch
        celestialBody (CelestialBodies): Celestial body to extract
        jplEphemHeader (np.ndarray): Numpy array containing the header table 

    Returns:
        (list, list, list): String representation of Chebyshev interpolants for x, y, z values of position

    """

    if celestialBody == CelestialBodies.EarthFromEMB:
        # Have to do extra work to compute the position of Earth relative to EMB
        generate_earth_relative_to_barycenter_file(lineBlocks, em_ratio, mjd0, mjdF, jplEphemHeader, outPath)

    else:
        # Get table parameters for the body
        START_IND, END_IND, NUM_COEFF, NUM_POLY, DAYS_PER_POLY = get_table_parameters(celestialBody, jplEphemHeader)

        xChebyshevStr = []
        yChebyshevStr = []
        zChebyshevStr = []
        startMjdVals = []
        
        for block in lineBlocks:

            # First, pull out start/stop jd and convert to MJD_J2k
            mjdStart = jd_to_mjdj2k(block[0])
            mjdStop  = jd_to_mjdj2k(block[1])

            # Skip a block if it isn't contained within the start/stop window
            if mjdStop < mjd0 or mjdStart > mjdF:
                continue

            # Get the chebyshev coefficients for the moon
            coeff = block[START_IND:END_IND]

            # Process coefficients for Each polynomial
            idx = 0
            for k in range(NUM_POLY):
                # Set the start/stop MJD values
                curMjdStart = mjdStart + DAYS_PER_POLY * k
                curMjdStop = curMjdStart + DAYS_PER_POLY

                # Prevent duplicate start dates
                if duplicate_start_date(startMjdVals, curMjdStart):
                    continue
                startMjdVals.append(curMjdStart)

                # Extract x coefficients
                xCoeffStr = format_coefficients_string(curMjdStart, curMjdStop, coeff[idx:(idx + NUM_COEFF)])
                xChebyshevStr.append(xCoeffStr)

                # Extract y coefficients
                idx += NUM_COEFF
                yCoeffStr = format_coefficients_string(curMjdStart, curMjdStop, coeff[idx:(idx + NUM_COEFF)])
                yChebyshevStr.append(yCoeffStr)

                # Extract z coefficients
                idx += NUM_COEFF
                zCoeffStr = format_coefficients_string(curMjdStart, curMjdStop, coeff[idx:(idx + NUM_COEFF)])
                zChebyshevStr.append(zCoeffStr)

                # Add NUM_COEFF so the next X value starts off properly
                idx += NUM_COEFF

        # Write to file
        name = celestialBody.name
        if (celestialBody != CelestialBodies.EMB and celestialBody != CelestialBodies.Moon):
            # relPath = f"astro/systems/planetary_bodies/{name}"
            relPath = f"{name}"
        else:
            # relPath = "astro/systems/planetary_bodies/Earth"
            relPath = "Earth"

        if celestialBody != CelestialBodies.Moon:
            write_to_file(outPath, relPath, f"{name}EphemerisTable", NUM_COEFF + 2, DAYS_PER_POLY, xChebyshevStr, yChebyshevStr, zChebyshevStr)
        elif celestialBody == CelestialBodies.EMB:
            write_to_file(outPath, relPath, f"EmbEphemerisTable", NUM_COEFF + 2, DAYS_PER_POLY, xChebyshevStr, yChebyshevStr, zChebyshevStr)
        else:
            write_to_file(outPath, relPath, f"{name}GcrfTable", NUM_COEFF + 2, DAYS_PER_POLY, xChebyshevStr, yChebyshevStr, zChebyshevStr)

        return xChebyshevStr, yChebyshevStr, zChebyshevStr


def generate_earth_relative_to_barycenter_file(lineBlocks: list, em_ratio: float, mjd0: float, mjdF: float, jplEphemHeader: np.ndarray, outPath: str):
    """
    Extract the Chebyshev coefficients for the Earth's position relative to the Earth-Moon-Barycenter

    Arguments:
        lineBlocks (list[list]): List of floating point values representing each block
        em_ratio (float): Earth/Moon mass ratio
        mjd0 (float): Initial value of MJD from the J2000 Epoch
        mjdF (float): Final value of MJD from the J2000 Epoch
        jplEphemHeader (np.ndarray): Numpy array containing the header table 

    Returns:
        (list, list, list): String representation of Chebyshev interpolants for x, y, z values of position

    """

    # Get the Chebyshev parameters for the Moon, and will adjust
    START_IND, END_IND, NUM_COEFF, NUM_POLY, DAYS_PER_POLY = get_table_parameters(CelestialBodies.Moon, jplEphemHeader)

    xChebyshevStr = []
    yChebyshevStr = []
    zChebyshevStr = []
    startMjdVals = []

    for block in lineBlocks:

        # First, pull out start/stop jd and convert to MJD_J2k
        mjdStart = jd_to_mjdj2k(block[0])
        mjdStop  = jd_to_mjdj2k(block[1])

        # Skip a block if it isn't contained within the start/stop window
        if mjdStop < mjd0 or mjdStart > mjdF:
            continue

        # Get the chebyshev coefficients for the moon
        moonCoeff = block[START_IND:END_IND]

        # Compute the position of moon relative to EM-barycenter
        earth_rel_embary = [-v / (1 + em_ratio) for v in moonCoeff]

        # Process coefficients for Each polynomial
        idx = 0
        for k in range(NUM_POLY):
            # Set the start/stop MJD values
            curMjdStart = mjdStart + DAYS_PER_POLY * k
            curMjdStop = curMjdStart + DAYS_PER_POLY

            # Prevent duplicate start dates
            if duplicate_start_date(startMjdVals, curMjdStart):
                continue
            startMjdVals.append(curMjdStart)

            # Extract x coefficients
            xCoeffStr = format_coefficients_string(curMjdStart, curMjdStop, earth_rel_embary[idx:(idx + NUM_COEFF)])
            xChebyshevStr.append(xCoeffStr)

            # Extract y coefficients
            idx += NUM_COEFF
            yCoeffStr = format_coefficients_string(curMjdStart, curMjdStop, earth_rel_embary[idx:(idx + NUM_COEFF)])
            yChebyshevStr.append(yCoeffStr)

            # Extract z coefficients
            idx += NUM_COEFF
            zCoeffStr = format_coefficients_string(curMjdStart, curMjdStop, earth_rel_embary[idx:(idx + NUM_COEFF)])
            zChebyshevStr.append(zCoeffStr)

            # Add NUM_COEFF so the next X value starts off properly
            idx += NUM_COEFF

    # relPath = "astro/systems/planetary_bodies/Earth"
    relPath = "Earth"
    write_to_file(outPath, relPath, "EarthFromEmbEphemerisTable", NUM_COEFF + 2, DAYS_PER_POLY, xChebyshevStr,
                  yChebyshevStr, zChebyshevStr)

    return xChebyshevStr, yChebyshevStr, zChebyshevStr


def format_coefficients_string(mjdStart: float, mjdStop: float, coeff: list) -> str:
    return "{},{},{}".format(mjdStart, mjdStop, ','.join([str("{0:0.15e}".format(val)) for val in coeff]))


if __name__ == "__main__":
    parser = argparse.ArgumentParser(description="Generate JPL Ephemeris files for Astrea")
    parser.add_argument('--bodies', nargs='+', type=str, default=[body.name for body in CelestialBodies],
                        help='List of celestial bodies to generate ephemeris files for. Default is all bodies.')
    parser.add_argument('-o', '--output_path', type=str, default=os.path.join(ASTREA_ROOT, "astrea/astro/systems/planetary_bodies"))
    args = parser.parse_args()

    # Parse the header table
    ephemNumber = "430"
    base = os.path.join(ASTREA_ROOT, "astrea/astro/data/jpl_ephemeris_data")
    emratio, jplEphemHeader = parse_header_file(f"{base}/de_{ephemNumber}/header.430_572")

    # Parse the desired files
    files = [
        f"{base}/de_{ephemNumber}/ascp1950.430", 
        f"{base}/de_{ephemNumber}/ascp2050.430"
    ]
    blockLines = read_in_blocks(files)

    # Parse from 2000-1-1T12:00:00 to 2100-1-1T12:00:00, TT
    mjd0 = 0
    mjdF = 36525

    bodies = args.bodies[0].split(' ')
    outPath = args.output_path
    for body in bodies:
        try:
            if body == 'Earth':
                celestialBody = CelestialBodies.EMB
                generate_ephemeris_file(blockLines, emratio, mjd0, mjdF, celestialBody, jplEphemHeader, outPath)
                celestialBody = CelestialBodies.EarthFromEMB
            else:
                celestialBody = CelestialBodies[body]
        except KeyError:
            print(f" -- {body} not supported yet, skipping...")
            continue # just ignore invalid body names for now
        generate_ephemeris_file(blockLines, emratio, mjd0, mjdF, celestialBody, jplEphemHeader, outPath)
