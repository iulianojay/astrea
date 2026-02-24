import argparse
import os
import matplotlib.pyplot as plt
import matplotlib.dates as mdates
import matplotlib.colors as mcolors
import pandas as pd
import numpy as np
import datetime
from typing import List, Any
from risesets import riseset_difference
from mpl_toolkits.basemap import Basemap
from scipy.interpolate import griddata
from matplotlib.colors import Normalize as norm

ASTREA_ROOT = os.getenv("ASTREA_ROOT")



def ingest_riseset_csv(infile: str) -> pd.DataFrame:
    # Loop the data lines
    with open(infile, "r") as temp_f:
        # get n of columns in each line
        col_count = [len(l.split(",")) for l in temp_f.readlines()]

    # Generate column names  (names will be 0, 1, 2, ..., maximum columns - 1)
    column_names = [i for i in range(0, max(col_count))]

    # Read results
    return pd.read_csv(
        infile, index_col=False, header=None, names=column_names, low_memory=False
    )


def get_midnight_of_today() -> datetime.datetime:
    now = datetime.datetime.now()
    return now.replace(hour=0, minute=0, second=0, microsecond=0)


def get_risesets_from_row(row: pd.Series) -> List[Any]:
    risesets = []
    for ii in range(2, row.values.size, 2):
        # Correct typing and convert from seconds
        rise = float(row.values[ii])
        set = float(row.values[ii + 1])
        if not np.isnan(rise) and not np.isnan(set):
            risesets.append((rise / 3600, set / 3600))
        else:
            break
    return risesets


def get_non_interfering_riseset_times(
    risesets: List[float], interference: List[float]
) -> List[float]:

    # TODO: THIS IS NOT GENERALIZED AND WILL USUALLY BE WRONG
    times = [risesets[0][0]]
    for rise, set in interference[0]:
        times.append(rise)
        times.append(set)
    times.append(risesets[0][1])

    return [(times[ii], times[ii + 1]) for ii in range(0, len(times), 2)]


def plot_trace_bars(
    results: str, outfile: str, main: str, target: str = None, colors: dict = None
) -> None:

    # Read results
    df = ingest_riseset_csv(results)

    # Get time of day
    midnight = get_midnight_of_today()
    timeTicks = mdates.drange(
        midnight,
        midnight + datetime.timedelta(days=1, hours=2),
        datetime.timedelta(hours=2),
    )

    # Setup plot
    fig, ax = plt.subplots()

    # Loop over rows
    labels = []
    usedPairs = []
    iPlot = 0
    mainRisesets = []
    interferingRisesets = []
    for index, row in df.iterrows():
        if index == 0:
            continue

        sender = row[0]
        receiver = row[1]

        if target is not None and sender != target and receiver != target:
            continue

        # Set plot color
        color = "tab:red"
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
        labels.append(
            f"{sender} \u21d4 {receiver}"
        )  # TODO: use unicode single-direction arrow for one-way analysis

        # Store risesets
        risesets = get_risesets_from_row(row)
        if sender == main or receiver == main:
            mainRisesets = risesets
        else:
            interferingRisesets.append(risesets)

        # Plot
        risesetBars = [
            (
                midnight + datetime.timedelta(hours=rise),
                datetime.timedelta(hours=set - rise),
            )
            for rise, set in risesets
        ]
        ax.broken_barh(risesetBars, (-0.2 + iPlot * 1.0, 0.4), color=color)
        iPlot += 1

    if len(mainRisesets) == 0:
        print(f"Warning: No risesets found for {main}. Plot will be empty.")
        return

    # Plot interference bar
    nonInterferedRisesets = get_non_interfering_riseset_times(
        mainRisesets, interferingRisesets
    )
    risesetBars = [
        (
            midnight + datetime.timedelta(hours=rise),
            datetime.timedelta(hours=set - rise - 0.075),
        )
        for rise, set in nonInterferedRisesets
    ]
    ax.broken_barh(risesetBars, (-0.2 + iPlot * 1.0, 0.4), color="tab:green")
    labels.append(f"{main} \u21d4 {target}\n(no interference)")

    # Cleanup
    ax.xaxis_date()
    ax.xaxis.set_major_formatter(mdates.DateFormatter("%H:%M"))
    fig.autofmt_xdate()

    ax.set_xlim(risesetBars[0][0], risesetBars[-1][0] + risesetBars[-1][1])
    ax.set_xticks(timeTicks)
    ax.set_xlabel("Rise - Set Times")

    ax.invert_yaxis()
    ax.set_yticks(range(len(labels)), labels=labels, ma="center")

    ax.set_title(f"Trace Times to {target}")
    ax.grid()

    # Save
    fig.savefig(outfile, bbox_inches="tight")


def plot_number_of_accesses(
    results: str, outfile: str, target: str = None, plotInterference: bool = False
) -> None:

    # Read results
    df = ingest_riseset_csv(results)

    # Get _accesses
    _accesses = {}
    for index, row in df.iterrows():
        if index == 0:
            continue

        sender = row[0]
        receiver = row[1]

        if target is not None and sender != target and receiver != target:
            continue

        # Avoid plotting same pairs twice - TODO: Update this for one-way analysis
        if (sender, receiver) in _accesses.keys() or (
            receiver,
            sender,
        ) in _accesses.keys():
            continue

        _accesses[(sender, receiver)] = get_risesets_from_row(row)

    # Loop over rows
    times = [x / 60.0 for x in range(0, 1440)]  # hours
    n_accesses = []
    for t in times:
        count = 0
        for pair, risesets in _accesses.items():
            sender, receiver = pair
            for rise, set in risesets:
                if rise <= t and set >= t:
                    count += 1
        if plotInterference and count > 0:
            count -= 1
        n_accesses.append(count)

    # Get time of day
    midnight = get_midnight_of_today()
    timesHours = [midnight + datetime.timedelta(hours=t) for t in times]
    timeTicks = mdates.drange(
        midnight,
        midnight + datetime.timedelta(days=1, hours=2),
        datetime.timedelta(hours=2),
    )

    # Plot
    fig, ax = plt.subplots()
    ax.bar(timesHours, n_accesses, width=(timesHours[1] - timesHours[0]))

    ax.xaxis_date()
    ax.xaxis.set_major_formatter(mdates.DateFormatter("%H:%M"))
    fig.autofmt_xdate()

    limit = int(np.ceil(np.max(n_accesses) * 1.1))

    ax.set_xlim(timesHours[0], timesHours[-1])
    ax.set_xticks(timeTicks)
    ax.set_ylim(0, limit)
    ax.set_yticks(range(0, limit))
    ax.set_xlabel("Time of Day")
    if plotInterference:
        ax.set_ylabel(f"Number of Interference Sources")
        ax.set_title(f"Number of Possible Interference Events Tracing {target}")
    else:
        ax.set_ylabel(f"Number of Accesses")
        ax.set_title(f"Number of Simultaneous Accesses to {target}")
    ax.grid()

    # Save
    fig.savefig(outfile, bbox_inches="tight")



def plot_number_of_folds(
    results: str, outfile: str
) -> None:

    fontSize = 14
    fontWeight = 'bold'

    plt.clf()
    fig = plt.figure(figsize=(12, 9))
    ax = fig.add_subplot(111, facecolor='w', frame_on=False)

    # Set up Basemap instance
    lllon = -180
    lllat = -90
    urlon = 180
    urlat = 90
    map = Basemap(
        projection = 'robin',
        llcrnrlon = lllon,
        llcrnrlat = lllat,
        urcrnrlon = urlon,
        urcrnrlat = urlat,
        lat_0 = 0,
        lon_0 = 0,
        resolution='h'
    )

    # draw map details
    map.drawmapboundary(fill_color='white', ax=ax)
    map.fillcontinents(color='#C0C0C0', ax=ax)
    map.drawcountries(
        linewidth=.75,
        linestyle='solid',
        color='#000073',
        antialiased=True,
        ax=ax,
        zorder=3
    )

    parallelSep = 30.0
    parallels = np.arange(lllat, urlat + parallelSep, parallelSep)
    parallels[0] += 5
    parallels[-1] -= 5
    map.drawparallels(
        parallels,
        color = 'black',
        linewidth = 0.5,
        ax=ax,
        labels=[1,1,0,0],
        fontsize=fontSize-2
    )

    meridianSep = 60.0
    meridians = np.arange(lllon, urlon + meridianSep, meridianSep)
    meridians[0] += 5
    meridians[-1] -= 5
    map.drawmeridians(
        meridians,
        color = '0.25',
        linewidth = 0.5,
        ax=ax,
        labels=[0,0,0,1],
        fontsize=fontSize-2
    )

    # Read results
    df = ingest_riseset_csv(results)

    lats = np.array([])
    lons = np.array([])
    folds = np.array([])
    for row in df.itertuples():
        obj = row[1]
        if "(Earth)" not in obj:
            continue

        lat, lon = obj.replace('°','').split('[')[1].split(']')[0].split(",")
        lats = np.append(lats, float(lat))
        lons = np.append(lons, float(lon))
        folds = np.append(folds, float(row[3]))

    # transform lon / lat coordinates to map projection
    x, y = map(*(lons, lats))

    # grid data
    numcols, numrows = 1000, 1000
    xi = np.linspace(x.min(), x.max(), numcols)
    yi = np.linspace(y.min(), y.max(), numrows)
    xi, yi = np.meshgrid(xi, yi)

    # interpolate
    zi = griddata(
        (x, y),
        folds,
        (xi, yi),
        method='cubic'
    )

    # contour plot
    levels = np.arange(0.5, np.ceil(folds.max()) + 1, 1)
    levels = np.insert(levels, 0, 0.)
    cmapName = 'turbo_r'
    con = map.contourf(xi, yi, zi, zorder=4, alpha=0.6, cmap=cmapName, ax=ax, levels=levels)

    # add colour bar and title
    cbar = plt.colorbar(con, orientation='horizontal', fraction=.057, pad=0.05)
    cbar.set_label("Folds", fontsize=fontSize, fontweight=fontWeight)
    cbar_ticks = []
    for ii in range(len(levels) - 1):
        cbar_ticks.append((levels[ii] + levels[ii + 1]) / 2)
    cbar_labels = [str(int(np.floor(tick + 0.5))) for tick in cbar_ticks]
    cbar.set_ticks(cbar_ticks)
    cbar.set_ticklabels(cbar_labels, fontsize=fontSize, fontweight=fontWeight)

    # fig.suptitle("Average Folds of Coverage", fontsize=16, fontweight=fontWeight)
    # fig.savefig(outfile, bbox_inches="tight")
    plt.title("Average Folds of Coverage", fontsize=fontSize + 4, fontweight=fontWeight)
    plt.savefig(outfile, format="png", dpi=300, bbox_inches="tight")


if __name__ == "__main__":

    # argparser = argparse.ArgumentParser(description="Plot trace results.")
    # argparser.add_argument("--outfile", type=str, help="The output file for the plot.",
    #                        default=os.path.join(os.path.dirname(__file__), '..', 'trace','drivers','results', "revisit.csv"))
    # argparser.add_argument("--target", type=str, help="The target ground site.", default="Washington DC")
    # argparser.add_argument("--main", type=str, help="The main satellite to plot.", default="ARCTURUS")
    # args = argparser.parse_args()

    # results = args.outfile
    # base = os.path.dirname(args.outfile)
    # traceOutfile = os.path.join(base, "revisit.png")
    # countOutfile = os.path.join(base, "trace_count.png")
    # interfereOutfile = os.path.join(base, "interference_count.png")
    # foldsOutfile = os.path.join(base, "folds.png")

    # target = args.target
    # main = args.main
    # colors = {main: "tab:blue"}

    # print(f"Reading trace results from {results}. Targeting {target} with main satellite {main}...")

    # plot_trace_bars(results, traceOutfile, main, target, colors)
    # plot_number_of_accesses(results, countOutfile, target)
    # plot_number_of_accesses(results, interfereOutfile, target, True)

    results = os.path.join(os.path.dirname(__file__), '..', 'trace','drivers','results', 'iceye', "n_folds.csv")
    foldsOutfile = os.path.join(os.path.dirname(__file__), '..', 'trace','drivers','results', 'iceye', 'plots', "folds.png")
    plot_number_of_folds(results, foldsOutfile)
