from enum import IntEnum
import numpy
import os

#---------------------------------------------------------------------------------------------------------------------------
#---------------------------------------------------------------------------------------------------------------------------

#--------------------------------------
# Utility Functions
#--------------------------------------

def parse_header_file(header_file):
    """
    Pull the table out of the DE header file, which is located between the tags "GROUP   1050" and "GROUP   1070"
    
    Returns:
        ndarray: Numpy array containing the header table 
        float: Earth/Moon mass ratio

    """

    def parse_group_1040(lines_group_1040):
        """
        Simply identify the index in the block for EMRAT
        """
        lines_group_1040 = lines_group_1040[2:]

        split_block = []
        for line in lines_group_1040:
            if line.strip() == "":
                continue
            else:
                split_block.extend(line.strip().split())

        # Now identify index of EMRAT
        for ind, val in enumerate(split_block):
            if val == "EMRAT":
                return ind

        return None

    def parse_group_1041(lines_group_1041, emrat_ind):
        """
        Return the Earth/Moon mass ratio
        """
        lines_group_1041 = lines_group_1041[2:]

        split_block = []
        for line in lines_group_1041:
            if line.strip() == "":
                continue
            else:
                split_block.extend(line.strip().split())

        return float(split_block[emrat_ind].replace("D", "e"))
        
    def parse_group_1050(lines_group_1050):
        # Put the header lines into a numpy array
        jpl_ephem_header = []
        for line in lines_group_1050:
            if line.strip() == "":
                continue
            else:
                jpl_ephem_header.append(list(map(int, line.strip().split())))
        return jpl_ephem_header

    with open(header_file, 'r') as fID:
        lines = fID.readlines()

    # Parse the file into groupes
    group = None
    group_lines = {'1040': [], '1041': [], '1050': []}

    # Discard the lines until we get to the line containing "GROUP   1050"
    for line in lines:
        if "GROUP" in line:
            group = line.split()[1].strip()
            continue
        elif group is None:
            continue
        else:
            if group == "1040":
                group_lines['1040'].append(line)
            elif group == "1041":
                group_lines['1041'].append(line)
            elif group == "1050":
                group_lines['1050'].append(line)

    emrat_ind = parse_group_1040(group_lines['1040'])
    if emrat_ind is None:
        raise Exception("Failed to parse out the EMRAT value from header file")
    emratio = parse_group_1041(group_lines['1041'], emrat_ind)
    jpl_ephem_header = parse_group_1050(group_lines['1050'])
    return emratio, numpy.asarray(jpl_ephem_header)

#---------------------------------------------------------------------------------------------------------------------------

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
    Pluto = 8,          # Pluto from SSB
    Moon = 9,           # Moon geocentric position
    Sun = 10,           # Sun from SSB
    EarthFromEMB = 11   # Earth from EMB

#---------------------------------------------------------------------------------------------------------------------------

def get_table_parameters(celestial_body: CelestialBodies, jpl_ephem_header: numpy.ndarray):
    """
    Get start index, end index, and number of polynomials for each Celestial Body

    Arguments:
        celestial_body (CelestialBodies): Enum value representing the celestial body
        jpl_ephem_header (numpy.ndarray): Numpy array containing the header table 

    Returns:
        tuple: Tuple containing the following values
            - **start_ind** `(int)`: Index in the JPL ephemeris file at which the celestial body's polynomial coefficients start
            - **stop_ind** `(int)`: Index in the JPL ephemeris file at which the celestial body's polynomial coefficients stop
            - **coeff_per_poly** `(int)`: Number of coefficients per polynomial
            - **num_poly** `(int)`: Number of polynomials required to model the body over the 32 day period
            - **days_per_poly** `(int)`: Number of days each polynomial represents

    """
    # Get integer value for the CelestialBody
    cb_ind = celestial_body.value

    # Extract table information. Note that start/stop index you subtract 1 since Python is 0 based
    start_ind = jpl_ephem_header[0, cb_ind] - 1
    stop_ind = jpl_ephem_header[0, cb_ind + 1] - 1
    coeff_per_poly = jpl_ephem_header[1, cb_ind]
    num_poly = jpl_ephem_header[2, cb_ind]
    days_per_poly = 32.0 / num_poly

    return start_ind, stop_ind, coeff_per_poly, num_poly, days_per_poly

#---------------------------------------------------------------------------------------------------------------------------

def jd_to_mjdj2k(jd: float) -> float:
    """
    Convert Julian Date to Modified Julian Date from the J2000 Epoch

    """
    return jd - 2451545.0

#---------------------------------------------------------------------------------------------------------------------------

def read_in_blocks(file_names: list):
    """
    Read in blocks from multiple files, and concactinate them into a set of blocks

    Arguments:
        file_names (list[str]): List of filenames to parse

    Returns:
        list[list]: Each block from the files, as a list of floating point values

    """

    # Type check to make sure that it is a list being passed in
    if isinstance(file_names, str):
        file_names = [file_names]

    # read all lines from the file
    lines = []
    for file in file_names:
        with open(file, 'r') as fID:
            new_lines = fID.readlines()
            lines += new_lines


    # Split each line up into corresponding "blocks"
    block_lines = []
    cur_block = ""

    for line in lines:
        split_line = line.strip().split()

        # Check for the header line
        if len(split_line) == 2:
            if split_line[1] == "1018":
                if len(cur_block) > 0:
                    block_lines.append(cur_block)
                cur_block = ""
        else:
            cur_block += line

    # Append the last block
    block_lines.append(cur_block)

    # Split each block up into a list of floating point values
    float_lines = [convert_to_float(line.split()) for line in block_lines]

    return float_lines

#---------------------------------------------------------------------------------------------------------------------------

def write_to_file(file_name: str, num_entries, days_per_poly, x_coeff_str, y_coeff_str, z_coeff_str, body):
    """
    Format and write x, y, z position coefficients to file

    """

    with open("{}".format(file_name), 'w') as fID:

        # Write number of days per poly at the top
        fID.write("static constexpr double days_per_poly_ = {};\n".format(days_per_poly))

        # Write the x coefficients to file
        fID.write("std::array<std::array<double, {}>, {}> {}::x_interp_ ".format(num_entries, len(x_coeff_str), body) + "{\n")

        for x in x_coeff_str:
            fID.write('    std::array<double, {}>'.format(num_entries) + "{" + "{}".format(x) + "},\n")

        fID.write("};")

        fID.write("\n\n//--------------------------------------------------------------------------------------------------------------------------\n\n");

        # Write the y coefficients to file
        fID.write("std::array<std::array<double, {}>, {}> {}::y_interp_ ".format(num_entries, len(x_coeff_str), body) + "{\n")

        for y in y_coeff_str:
            fID.write('    std::array<double, {}>'.format(num_entries) + "{" + "{}".format(y) + "},\n")

        fID.write("};")

        fID.write("\n\n//--------------------------------------------------------------------------------------------------------------------------\n\n");

        # Write the z coefficients to file
        fID.write("std::array<std::array<double, {}>, {}> {}::z_interp_ ".format(num_entries, len(x_coeff_str), body) + "{\n");

        for z in z_coeff_str:
            fID.write('    std::array<double, {}>'.format(num_entries) + "{" + "{}".format(z) + "},\n");

        fID.write("};")

    return

#---------------------------------------------------------------------------------------------------------------------------

def convert_to_float(words):
    """
    Convert values from strings to floating point values

    Arguments:
        words (list[str]): List of string values to be converted to floating points

    Returns:
        list[str]: Corresponding list of floating point values

    """

    float_vals = []

    for word in words:
        if "D" in word:
            word = word.replace("D", "e")

        float_vals.append(float(word))

    return float_vals

#---------------------------------------------------------------------------------------------------------------------------

def duplicate_start_date(start_mjdj2k_vals, cur_mjd_start):
    """
    Function to prevent duplicate start dates when multiple files are used
    
    """
    for mj2jdk_val in start_mjdj2k_vals:
        if cur_mjd_start == mj2jdk_val:
            return True

    return False

#---------------------------------------------------------------------------------------------------------------------------

def generate_ephemeris_file(line_blocks: list, em_ratio: float, mjdj2k_0: float, mjdj2k_f: float, 
                            celestial_body: CelestialBodies, jpl_ephem_header: numpy.ndarray):
    """
    Extract the Chebyshev coefficients for the specified liens, given an initial and final MJD from the J2000 Epoch

    Arguments:
        line_blocks (list[list]): List of floating point values representing each block
        em_ratio (float): Earth/Moon mass ratio
        mjdj2k_0 (float): Initial value of MJD from the J2000 Epoch
        mjdj2k_f (float): Final value of MJD from the J2000 Epoch
        celestial_body (CelestialBodies): Celestial body to extract
        jpl_ephem_header (numpy.ndarray): Numpy array containing the header table 

    Returns:
        (list, list, list): String representation of Chebyshev interpolants for x, y, z values of position

    """

    if celestial_body == CelestialBodies.EarthFromEMB:
        # Have to do extra work to compute the position of Earth relative to EMB
        generate_earth_relative_to_barycenter_file(line_blocks, em_ratio, mjdj2k_0, mjdj2k_f, jpl_ephem_header)

    else:
        # Get table parameters for the body
        START_IND, END_IND, NUM_COEFF, NUM_POLY, DAYS_PER_POLY = get_table_parameters(celestial_body, jpl_ephem_header)

        x_chebyshev_str = []
        y_chebyshev_str = []
        z_chebyshev_str = []
        start_mjdj2k_vals = []
        
        for block in line_blocks:

            # First, pull out start/stop jd and convert to MJD_J2k
            mjdj2k_start = jd_to_mjdj2k(block[0])
            mjdj2k_stop  = jd_to_mjdj2k(block[1])

            # Skip a block if it isn't contained within the start/stop window
            if mjdj2k_stop < mjdj2k_0 or mjdj2k_start > mjdj2k_f:
                continue

            # Get the chebyshev coefficients for the moon
            coeff = block[START_IND:END_IND]

            # Process coefficients for Each polynomial
            cur_ind = 0
            for k in range(NUM_POLY):
                # Set the start/stop MJD values
                cur_mjd_start = mjdj2k_start + DAYS_PER_POLY * k
                cur_mjd_stop = cur_mjd_start + DAYS_PER_POLY

                # Prevent duplicate start dates
                if duplicate_start_date(start_mjdj2k_vals, cur_mjd_start):
                    continue
                start_mjdj2k_vals.append(cur_mjd_start)

                # Extract x coefficients
                x_coeff = coeff[cur_ind:(cur_ind + NUM_COEFF)]
                x_coeff_str = "{},{},{}".format(cur_mjd_start, cur_mjd_stop, ','.join([str("{0:0.15e}".format(val)) for val in x_coeff]))
                x_chebyshev_str.append(x_coeff_str)

                # Extract y coefficients
                cur_ind += NUM_COEFF
                y_coeff = coeff[cur_ind:(cur_ind + NUM_COEFF)]
                y_coeff_str = "{},{},{}".format(cur_mjd_start, cur_mjd_stop, ','.join([str("{0:0.15e}".format(val)) for val in y_coeff]))
                y_chebyshev_str.append(y_coeff_str)

                # Extract z coefficients
                cur_ind += NUM_COEFF
                z_coeff = coeff[cur_ind:(cur_ind + NUM_COEFF)]
                z_coeff_str = "{},{},{}".format(cur_mjd_start, cur_mjd_stop, ','.join([str("{0:0.15e}".format(val)) for val in z_coeff]))
                z_chebyshev_str.append(z_coeff_str)

                # Add NUM_COEFF so the next X value starts off properly
                cur_ind += NUM_COEFF

            # Set the previous stop value so that we don't allow overlap between tables
            prev_mjdj2k_stop = int(mjdj2k_stop)


        if celestial_body != CelestialBodies.Moon:
            write_to_file("{}_position.txt".format(celestial_body.name), NUM_COEFF + 2, DAYS_PER_POLY, x_chebyshev_str,
                        y_chebyshev_str, z_chebyshev_str, "{}FromSSBGCRFTable".format(celestial_body.name))
        else:
            write_to_file("{}_position.txt".format(celestial_body.name), NUM_COEFF + 2, DAYS_PER_POLY, x_chebyshev_str,
                        y_chebyshev_str, z_chebyshev_str, "{}GCRFTable".format(celestial_body.name))

        return x_chebyshev_str, y_chebyshev_str, z_chebyshev_str

#---------------------------------------------------------------------------------------------------------------------------

def generate_earth_relative_to_barycenter_file(line_blocks: list, em_ratio: float, mjdj2k_0: float, mjdj2k_f: float, 
                                               jpl_ephem_header: numpy.ndarray):
    """
    Extract the Chebyshev coefficients for the Earth's position relative to the Earth-Moon-Barycenter

    Arguments:
        line_blocks (list[list]): List of floating point values representing each block
        em_ratio (float): Earth/Moon mass ratio
        mjdj2k_0 (float): Initial value of MJD from the J2000 Epoch
        mjdj2k_f (float): Final value of MJD from the J2000 Epoch
        jpl_ephem_header (numpy.ndarray): Numpy array containing the header table 

    Returns:
        (list, list, list): String representation of Chebyshev interpolants for x, y, z values of position

    """

    # Get the Chebyshev parameters for the Moon, and will adjust
    START_IND, END_IND, NUM_COEFF, NUM_POLY, DAYS_PER_POLY = get_table_parameters(CelestialBodies.Moon, jpl_ephem_header)

    x_chebyshev_str = []
    y_chebyshev_str = []
    z_chebyshev_str = []
    start_mjdj2k_vals = []

    for block in line_blocks:

        # First, pull out start/stop jd and convert to MJD_J2k
        mjdj2k_start = jd_to_mjdj2k(block[0])
        mjdj2k_stop  = jd_to_mjdj2k(block[1])

        # Skip a block if it isn't contained within the start/stop window
        if mjdj2k_stop < mjdj2k_0 or mjdj2k_start > mjdj2k_f:
            continue

        # Get the chebyshev coefficients for the moon
        moon_coeff = block[START_IND:END_IND]

        # Compute the position of moon relative to EM-barycenter
        earth_rel_embary = [-v / (1 + em_ratio) for v in moon_coeff]


        # Process coefficients for Each polynomial
        cur_ind = 0
        for k in range(NUM_POLY):
            # Set the start/stop MJD values
            cur_mjd_start = mjdj2k_start + DAYS_PER_POLY * k
            cur_mjd_stop = cur_mjd_start + DAYS_PER_POLY

            # Prevent duplicate start dates
            if duplicate_start_date(start_mjdj2k_vals, cur_mjd_start):
                continue
            start_mjdj2k_vals.append(cur_mjd_start)

            # Extract x coefficients
            x_coeff = earth_rel_embary[cur_ind:(cur_ind + NUM_COEFF)]
            x_coeff_str = "{},{},{}".format(cur_mjd_start, cur_mjd_stop, ','.join([str("{0:0.15e}".format(val)) for val in x_coeff]))
            x_chebyshev_str.append(x_coeff_str)

            # Extract y coefficients
            cur_ind += NUM_COEFF
            y_coeff = earth_rel_embary[cur_ind:(cur_ind + NUM_COEFF)]
            y_coeff_str = "{},{},{}".format(cur_mjd_start, cur_mjd_stop, ','.join([str("{0:0.15e}".format(val)) for val in y_coeff]))
            y_chebyshev_str.append(y_coeff_str)

            # Extract z coefficients
            cur_ind += NUM_COEFF
            z_coeff = earth_rel_embary[cur_ind:(cur_ind + NUM_COEFF)]
            z_coeff_str = "{},{},{}".format(cur_mjd_start, cur_mjd_stop, ','.join([str("{0:0.15e}".format(val)) for val in z_coeff]))
            z_chebyshev_str.append(z_coeff_str)

            # Add NUM_COEFF so the next X value starts off properly
            cur_ind += NUM_COEFF

    write_to_file("earth_relative_to_emb.txt", NUM_COEFF + 2, DAYS_PER_POLY, x_chebyshev_str,
                  y_chebyshev_str, z_chebyshev_str, "EarthFromEMBGCRFTable")

    return x_chebyshev_str, y_chebyshev_str, z_chebyshev_str

#---------------------------------------------------------------------------------------------------------------------------
#---------------------------------------------------------------------------------------------------------------------------

if __name__ == "__main__":
    # Make output directory
    ephem_number = "430"
    output_dir = "output_files_de_{}".format(ephem_number)
    os.makedirs(output_dir, exist_ok = True)

    # Parse the header table
    emratio, jpl_ephem_header = parse_header_file("de_{}/header.430_572".format(ephem_number))

    # Parse the desired files
    file_names = ["de_{}/ascp1950.430".format(ephem_number), "de_{}/ascp2050.430".format(ephem_number)]
    block_lines = read_in_blocks(file_names)

    # Parse from 2000-1-1T12:00:00 to 2100-1-1T12:00:00, TT
    mjdj2k_0 = 0
    mjdj2k_f = 36525

    # Change to the output directory so we can write files there cleanly 
    os.chdir(output_dir)

    for celestial_body in CelestialBodies:
        generate_ephemeris_file(block_lines, emratio, mjdj2k_0, mjdj2k_f, celestial_body, jpl_ephem_header)
