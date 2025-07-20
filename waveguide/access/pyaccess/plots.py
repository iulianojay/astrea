import matplotlib.pyplot as plt
import pandas as pd
import numpy as np
from typing import List, Tuple


def plot_access_bars(title: str, results: str, outfile: str, target: str = None, colors: dict = None) -> None:
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
    fig.set_figheight(15)
    fig.set_figwidth(20)

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
        risesets = []
        for ii in range(2, row.values.size, 2):
            # Correct typing and convert from seconds
            rise = float(row.values[ii])
            set = float(row.values[ii+1])
            if not np.isnan(rise) and not np.isnan(set):
                risesets.append((rise / 3600, set/ 3600))
            else: 
                break

        # Plot
        ax.broken_barh(risesets, (-0.2 + iPlot*1.0, 0.4), color=color)
        iPlot += 1

    # Cleanup
    ax.set_xlim(0, 24)
    ax.set_xticks(range(0, 25, 2))
    ax.invert_yaxis()
    ax.set_yticks(range(len(labels)), labels=labels)
    ax.set_xlabel("Rise - Set Times (hrs)")
    ax.set_title(title)
    ax.grid()

    # Save
    fig.savefig(outfile, bbox_inches='tight')


def plot_number_of_accesses(title: str, results: str, outfile: str, target: str = None) -> None:
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
            # Correct typing and convert from seconds
            rise = float(row.values[ii])
            set = float(row.values[ii+1])
            if not np.isnan(rise) and not np.isnan(set):
                risesets.append((rise / 3600, set/ 3600))
            else: 
                break
        accesses[(sender, receiver)] = risesets

    # Loop over rows
    times = [x/60.0 for x in range(0, 1440)]
    nAccesses = []
    for t in times:
        count = 0
        for pair, risesets in accesses.items():
            sender, receiver = pair
            for rise, set in risesets:
                if rise <= t and set >= t:
                    count += 1
        nAccesses.append(count)

    # Plot
    fig, ax = plt.subplots()
    ax.plot(times, nAccesses)

    ax.set_xlim(0, 24)
    ax.set_ylim(0, 500)
    ax.set_xticks(range(0, 25, 2))
    ax.set_xlabel("Time (hrs)")
    ax.set_title(title)
    ax.grid()

    # Save
    fig.savefig(outfile, bbox_inches='tight')


if __name__=='__main__':

    results = '/home/jay/projects/waveguide/waveguide/access/access/drivers/results/revisit.csv' 
    # outfile = '/home/jay/projects/waveguide/waveguide/access/access/drivers/results/revisit.png' 
    outfile = '/home/jay/projects/waveguide/waveguide/access/access/drivers/results/access_count.png' 
    target = "Washington DC"
    # target = "NUVIEW ALPHA"
    colors = None
    # plot_access_bars("Test Access Analysis", results, outfile, target, colors)
    plot_number_of_accesses("Test Access Analysis", results, outfile, target)