import os
import matplotlib.pyplot as plt
import pandas as pd
import numpy as np


def plot_access_bars(results: str, outfile: str, target: str = None, colors: dict = None) -> None:
    # Loop the data lines
    with open(results, 'r') as temp_f:
        # get n of columns in each line
        col_count = [ len(l.split(",")) for l in temp_f.readlines() ]
    
    # Generate column names  (names will be 0, 1, 2, ..., maximum columns - 1)
    column_names = [i for i in range(0, max(col_count))]

    # Read results
    df = pd.read_csv(results, index_col=False, header=None, names=column_names, low_memory=False)
    
    # Setup plot
    fig, ax = plt.subplots()

    # Loop over rows
    labels = []
    usedPairs = []
    iPlot = 0
    for index, row in df.iterrows():
        if index == 0: 
            continue

        sender = row[0]
        receiver = row[1]

        if target is not None and sender != target and receiver != target:
            continue
        color = 'r'
        if colors is not None:
            if sender in colors.keys():
                color = colors[sender]
            if receiver in colors.keys():
                color = colors[sender]

        # Avoid plotting same pairs twice - TODO: Update this for one-way analysis
        if (sender, receiver) in usedPairs or (receiver, sender) in usedPairs:
            continue
        else:
            usedPairs.append((sender, receiver))

        # Store labels
        labels.append(f'{sender} \u21D4 {receiver}') # TODO: use unicode single-direction arrow for one-way analysis

        # Loop over riseset times
        risesetBars = []
        for ii in range(2, row.values.size, 2):
            # Correct typing and convert from seconds
            rise = float(row.values[ii])
            set = float(row.values[ii+1])
            if not np.isnan(rise) and not np.isnan(set):
                risesetBars.append((rise / 3600, (set - rise)/ 3600))
            else: 
                break

        # Plot
        ax.broken_barh(risesetBars, (-0.2 + iPlot*1.0, 0.4), color=color)
        iPlot += 1

    # Cleanup
    ax.set_xlim(0, 24)
    ax.set_xticks(range(0, 25, 2))
    ax.invert_yaxis()
    ax.set_yticks(range(len(labels)), labels=labels)
    ax.set_xlabel("Rise - Set Times (hrs)")
    ax.set_title(f"Access Time to {target}")
    ax.grid()

    # Save
    fig.savefig(outfile, bbox_inches='tight')


def plot_number_of_accesses(results: str, outfile: str, target: str = None, plotInterference:bool = False) -> None:
    # Loop the data lines
    with open(results, 'r') as temp_f:
        # get n of columns in each line
        col_count = [ len(l.split(",")) for l in temp_f.readlines() ]
    
    # Generate column names  (names will be 0, 1, 2, ..., maximum columns - 1)
    column_names = [i for i in range(0, max(col_count))]

    # Read results
    df = pd.read_csv(results, index_col=False, header=None, names=column_names, low_memory=False)
    
    # Get accesses
    accesses = {}
    for index, row in df.iterrows():
        if index == 0: 
            continue

        sender = row[0]
        receiver = row[1]

        if target is not None and sender != target and receiver != target:
            continue

        # Avoid plotting same pairs twice - TODO: Update this for one-way analysis
        if (sender, receiver) in accesses.keys() or (receiver, sender) in accesses.keys():
            continue

        # Loop over riseset times
        risesets = []
        for ii in range(2, row.values.size, 2):
            # Correct typing and convert from seconds to hours
            rise = float(row.values[ii])
            set = float(row.values[ii+1])
            if not np.isnan(rise) and not np.isnan(set):
                risesets.append((rise / 3600.0, set / 3600.0)) # hours
            else: 
                break
        accesses[(sender, receiver)] = risesets

    # Loop over rows
    times = [x/60.0 for x in range(0, 1440)] # hours
    nAccesses = []
    for t in times:
        count = 0
        for pair, risesets in accesses.items():
            sender, receiver = pair
            for rise, set in risesets:
                if rise <= t and set >= t:
                    count += 1
        if plotInterference and count > 0:
            count -= 1
        nAccesses.append(count)

    # Plot
    fig, ax = plt.subplots()

    ax.bar(times, nAccesses)

    limit = int(np.ceil(np.max(nAccesses)*1.1))

    ax.set_xlim(0, 24)
    ax.set_xticks(range(0, 25, 2))
    ax.set_ylim(0, limit)
    ax.set_yticks(range(0, limit))
    ax.set_xlabel("Time (hrs)")
    if plotInterference:
        ax.set_ylabel(f"Number of Interference Sources")
        ax.set_title(f"Number of Possible Interference Events Accessing {target}")
    else:
        ax.set_ylabel(f"Number Accesses")
        ax.set_title(f"Number of Simultaneous Accesses to {target}")
    ax.grid()

    # Save
    fig.savefig(outfile, bbox_inches='tight')


if __name__=='__main__':

    base = '/home/jay/projects/waveguide/waveguide/access/access/drivers/results/'

    results = os.path.join(base, 'revisit.csv') 
    accessOutfile = os.path.join(base, 'revisit.png')
    countOutfile = os.path.join(base, 'access_count.png')
    interfereOutfile = os.path.join(base, 'interference_count.png')
    target = "Washington DC"
    colors = {"ARCTURUS": "b"}
    plot_access_bars(results, accessOutfile, target, colors)
    plot_number_of_accesses(results, countOutfile, target)
    plot_number_of_accesses(results, interfereOutfile, target, True)