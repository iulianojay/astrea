import matplotlib.pyplot as plt
import pandas as pd
import numpy as np
from typing import List, Tuple


def plot_access_results(title: str, results: str, outfile: str) -> None:
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

        senderId = row[0]
        receiverId = row[1]

        if (senderId != "DIRECTV_32729" and receiverId != "DIRECTV_32729"):
            continue

        # Avoid plotting same pairs twice - TODO: Update this for one-way analysis
        if (senderId, receiverId) in usedPairs or (receiverId, senderId) in usedPairs:
            continue
        else:
            usedPairs.append((senderId, receiverId))

        # Store labels
        labels.append(f'{senderId} \u21D4 {receiverId}') # TODO: use unicode single-direction arrow for one-way analysis

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
        ax.broken_barh(risesets, (-0.2 + iPlot*1.0, 0.4))
        iPlot += 1

    # Cleanup
    ax.set_xlim(0, 24)
    ax.set_xticks(range(0, 26, 2))
    ax.invert_yaxis()
    ax.set_yticks(range(len(labels)), labels=labels)
    ax.set_xlabel("Rise - Set Times (hrs)")
    ax.set_title(title)
    ax.grid()

    # Save
    fig.savefig(outfile, bbox_inches='tight')


if __name__=='__main__':

    results = '/home/jay/projects/waveguide/waveguide/access/access/drivers/results/revisit.csv' 
    outfile = '/home/jay/projects/waveguide/waveguide/access/access/drivers/results/revisit.png' 
    plot_access_results("Test Access Analysis", results, outfile)