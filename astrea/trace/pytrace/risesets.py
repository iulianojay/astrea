from typing import List


def convert_to_flat_list(risesets: List[float]) -> List[float]:
    """
    Convert a list of (rise, set) tuples to a flat list [rise1, set1, rise2, set2, ...]
    """
    flat_list = []
    for rise, set in risesets:
        flat_list.append(rise)
        flat_list.append(set)
    return flat_list


def convert_to_tuple_list(risesets: List[float]) -> List[float]:
    """
    Convert a flat list [rise1, set1, rise2, set2, ...] to a list of (rise, set) tuples
    """
    tuple_list = []
    for ii in range(0, len(risesets), 2):
        tuple_list.append((risesets[ii], risesets[ii + 1]))
    return tuple_list


def riseset_difference(a0: List[float], b0: List[float]) -> List[float]:
    """
    Compute the difference between two riseset arrays a - b. Hastly converted from C++ with
    no real thought given to making it more "pythonic".
    """
    # c = a - b

    # Check for empty arrays
    if len(a0) == 0 or len(b0) == 0:
        return a0

    a0 = convert_to_flat_list(a0)
    b0 = convert_to_flat_list(b0)

    # Setup
    aIdx = 0
    bIdx = 0
    cIdx = 0

    lenA = len(a0)
    lenB = len(b0)
    a = a0
    b = b0

    # Max size
    c = [0.0] * (lenA + lenB)

    # Loop and insert
    while aIdx < lenA:
        """
        1)
        a:      |-----|
        b:   |------------|

        2)
        a:   |------------|
        b:      |-----|

        3)
        a:   |------|
        b:      |-----|

            3.5)
            a:   |------|
            b:             |-----|

        4)
        a:      |-----|
        b:   |------|

            4.5)
            a:             |-----|
            b:   |------|
        """

        # TODO: There's gotta be a way to optimize this
        if bIdx == lenB:
            # Done with b, store everything else
            c[cIdx] = a[aIdx]
            c[cIdx + 1] = a[aIdx + 1]
            cIdx += 2
            aIdx += 2

        elif a[aIdx] >= b[bIdx] and a[aIdx + 1] <= b[bIdx + 1]:
            # Case 1: b envelopes a

            # truncate b
            b[bIdx] = a[aIdx + 1]

            # Move to next a riseset
            aIdx += 2

        elif a[aIdx] < b[bIdx] and a[aIdx + 1] > b[bIdx + 1]:
            # Case 2: a envelopes b

            # Store a rise to b rise
            c[cIdx] = a[aIdx]
            c[cIdx + 1] = b[bIdx]
            cIdx += 2

            # truncate a
            a[aIdx] = b[bIdx + 1]

            # Move to next b riseset
            bIdx += 2

        elif a[aIdx] < b[bIdx] and a[aIdx + 1] <= b[bIdx + 1]:
            # Case 3: a starts, b ends

            c[cIdx] = a[aIdx]
            if b[bIdx] > a[aIdx + 1]:  # Case 3.5: b completely after a
                c[cIdx + 1] = a[aIdx + 1]

            else:
                # Store a rise to b rise
                c[cIdx + 1] = b[bIdx]

                # truncate b
                b[bIdx] = a[aIdx + 1]

            # Increment
            cIdx += 2
            aIdx += 2

        elif a[aIdx] >= b[bIdx] and a[aIdx + 1] > b[bIdx + 1]:
            # Case 4: b starts, a ends

            if a[aIdx] > b[bIdx + 1]:
                # Case 4.5: a completely after b
                pass

            else:
                # truncate a
                a[aIdx] = b[bIdx + 1]

            # Move to next b riseset
            bIdx += 2

    c = c[:cIdx]

    return convert_to_tuple_list(c)
