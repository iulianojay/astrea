import os
import matplotlib.pyplot as plt
import matplotlib.dates as mdates
import matplotlib.colors as mcolors
import pandas as pd
import numpy as np
import datetime
from typing import List, Any

def ingest_riseset_csv(infile: str) -> pd.DataFrame:
    # Loop the data lines
    with open(infile, 'r') as temp_f:
        # get n of columns in each line
        col_count = [ len(l.split(",")) for l in temp_f.readlines() ]
    
    # Generate column names  (names will be 0, 1, 2, ..., maximum columns - 1)
    column_names = [i for i in range(0, max(col_count))]

    # Read results
    return pd.read_csv(infile, index_col=False, header=None, names=column_names, low_memory=False)


def get_midnight_of_today() -> datetime.datetime:
    now = datetime.datetime.now()
    return now.replace(hour = 0, minute = 0, second = 0, microsecond = 0)


def get_risesets_from_row(row: pd.Series) -> List[Any]:
    risesets = []
    for ii in range(2, row.values.size, 2):
        # Correct typing and convert from seconds
        rise = float(row.values[ii])
        set = float(row.values[ii+1])
        if not np.isnan(rise) and not np.isnan(set):
            risesets.append((rise / 3600, set / 3600))
        else: 
            break
    return risesets


def get_non_interfering_riseset_times(risesets: List[float], interference: List[float]) -> List[float]:

    # TODO: THIS IS NOT GENERALIZED AND WILL USUALLY BE WRONG
    times = [risesets[0][0]]
    for rise, set in interference[0]:
        times.append(rise)
        times.append(set)
    times.append(risesets[0][1])
        
    return [(times[ii], times[ii+1]) for ii in range(0, len(times), 2)]


def plot_access_bars(results: str, outfile: str, main: str, target: str = None, colors: dict = None) -> None:

    # Read results
    df = ingest_riseset_csv(results)

    # Get time of day
    midnight = get_midnight_of_today()
    timeTicks = mdates.drange(midnight, midnight + datetime.timedelta(days=1, hours=2), datetime.timedelta(hours=2))

    # Setup plot
    fig, ax = plt.subplots()

    # Loop over rows
    labels = []
    usedPairs = []
    iPlot = 0
    interferingRisesets = []
    for index, row in df.iterrows():
        if index == 0: 
            continue

        sender = row[0]
        receiver = row[1]

        if target is not None and sender != target and receiver != target:
            continue

        # Set plot color
        color = 'tab:red'
        if colors is not None:
            if sender in colors.keys():
                color = colors[sender]
            if receiver in colors.keys():
                color = colors[sender]

        # Avoid plotting same pairs twice - TODO: Update this for one-way analysis
        if (sender, receiver) in usedPairs or (receiver, sender) in usedPairs:
            continue

        # Store labels
        usedPairs.append((sender, receiver))
        labels.append(f'{sender} \u21D4 {receiver}') # TODO: use unicode single-direction arrow for one-way analysis

        # Store risesets
        risesets = get_risesets_from_row(row)
        if sender == main or receiver == main:
            mainRisesets = risesets
        else:
            interferingRisesets.append(risesets)

        # Plot
        risesetBars = [
            (midnight + datetime.timedelta(hours=rise), datetime.timedelta(hours=set-rise)) 
            for rise, set in risesets
        ]
        ax.broken_barh(risesetBars, (-0.2 + iPlot*1.0, 0.4), color=color)
        iPlot += 1
    
    # Plot interference bar
    nonInterferedRisesets = get_non_interfering_riseset_times(mainRisesets, interferingRisesets)
    risesetBars = [
        (midnight + datetime.timedelta(hours=rise), datetime.timedelta(hours=set-rise - 0.075)) 
        for rise, set in nonInterferedRisesets
    ]
    ax.broken_barh(risesetBars, (-0.2 + iPlot*1.0, 0.4), color='tab:green')
    labels.append(f'{main} \u21D4 {target}\n(no interference)')

    # Cleanup
    ax.xaxis_date()
    ax.xaxis.set_major_formatter(mdates.DateFormatter('%H:%M'))
    fig.autofmt_xdate()

    ax.set_xlim(risesetBars[0][0], risesetBars[-1][0] + risesetBars[-1][1])
    ax.set_xticks(timeTicks)
    ax.set_xlabel("Rise - Set Times")

    ax.invert_yaxis()
    ax.set_yticks(range(len(labels)), labels=labels, ma='center')
    
    ax.set_title(f"Access Times to {target}")
    ax.grid()

    # Save
    fig.savefig(outfile, bbox_inches='tight')


def plot_number_of_accesses(results: str, outfile: str, target: str = None, plotInterference:bool = False) -> None:

    # Read results
    df = ingest_riseset_csv(results)
    
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

        accesses[(sender, receiver)] = get_risesets_from_row(row)

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

    # Get time of day
    midnight = get_midnight_of_today()
    timesHours = [midnight + datetime.timedelta(hours=t) for t in times]
    timeTicks = mdates.drange(midnight, midnight + datetime.timedelta(days=1, hours=2), datetime.timedelta(hours=2))

    # Plot
    fig, ax = plt.subplots()
    ax.bar(timesHours, nAccesses, width = (timesHours[1] - timesHours[0]))

    ax.xaxis_date()
    ax.xaxis.set_major_formatter(mdates.DateFormatter('%H:%M'))
    fig.autofmt_xdate()

    limit = int(np.ceil(np.max(nAccesses)*1.1))

    ax.set_xlim(timesHours[0], timesHours[-1])
    ax.set_xticks(timeTicks)
    ax.set_ylim(0, limit)
    ax.set_yticks(range(0, limit))
    ax.set_xlabel("Time of Day")
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
    main = "ARCTURUS"
    colors = {main: 'tab:blue'}

    plot_access_bars(results, accessOutfile, main, target, colors)
    plot_number_of_accesses(results, countOutfile, target)
    plot_number_of_accesses(results, interfereOutfile, target, True)