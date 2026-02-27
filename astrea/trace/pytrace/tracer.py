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


class Tracer:

    def __init__(self, resultsdir: str, outdir: str):
        self.resultsdir = resultsdir
        self.outdir = outdir

        self.fontSize = 14
        self.fontWeight = 'bold'
        self.cmap = 'turbo_r'

        self.nLats = 1000
        self.nLons = 1000

        # Set up Basemap instance
        self.lllon = -180
        self.lllat = -90
        self.urlon = 180
        self.urlat = 90
        self.map = Basemap(
            projection = 'robin',
            llcrnrlon = self.lllon,
            llcrnrlat = self.lllat,
            urcrnrlon = self.urlon,
            urcrnrlat = self.urlat,
            lat_0 = 0,
            lon_0 = 0,
            resolution='h'
        )

        if not os.path.exists(self.outdir):
            os.makedirs(self.outdir)


    def ingest_csv(self, infile: str) -> pd.DataFrame:
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


    def plot_basemap(self, ax: plt.Axes) -> None:
        # draw map details
        self.map.drawmapboundary(fill_color='white', ax=ax)
        self.map.fillcontinents(color='#C0C0C0', ax=ax)
        self.map.drawcountries(
            linewidth=.75,
            linestyle='solid',
            color='#000073',
            antialiased=True,
            ax=ax,
            zorder=3
        )

        parallelSep = 30.0
        parallels = np.arange(self.lllat, self.urlat + parallelSep, parallelSep)
        parallels[0] += 5
        parallels[-1] -= 5
        self.map.drawparallels(
            parallels,
            color = 'black',
            linewidth = 0.5,
            ax=ax,
            labels=[1,1,0,0],
            fontsize=self.fontSize-2
        )

        meridianSep = 60.0
        meridians = np.arange(self.lllon, self.urlon + meridianSep, meridianSep)
        meridians[0] += 5
        meridians[-1] -= 5
        self.map.drawmeridians(
            meridians,
            color = '0.25',
            linewidth = 0.5,
            ax=ax,
            labels=[0,0,0,1],
            fontsize=self.fontSize-2
        )

    def build_grid(self, df: pd.DataFrame) -> tuple:

        lats = np.array([])
        lons = np.array([])
        for row in df.itertuples():
            obj = row[1]
            if "(Earth)" not in obj:
                continue

            lat, lon = obj.replace('°','').split('[')[1].split(']')[0].split(",")
            lats = np.append(lats, float(lat))
            lons = np.append(lons, float(lon))

        # transform lon / lat coordinates to map projection
        x, y = self.map(*(lons, lats))

        # grid data
        xi = np.linspace(x.min(), x.max(), self.nLons)
        yi = np.linspace(y.min(), y.max(), self.nLats)
        xi, yi = np.meshgrid(xi, yi)

        return x, y, xi, yi

    def plot_contourf(
            self,
            ax: plt.Axes,
            grid: tuple,
            values: np.ndarray,
            interpolation_method,
            title: str,
            cbar_label: str,
            levels: np.ndarray=None,
            cbar_ticks: List[float]=None,
            cbar_tick_labels: List[str]=None
        ) -> None:

        # interpolate
        x, y, xi, yi = grid
        zi = griddata(
            (x, y),
            values,
            (xi, yi),
            method=interpolation_method,
            fill_value=0
        )

        # contour plot
        con = self.map.contourf(xi, yi, zi, zorder=4, alpha=0.6, cmap=self.cmap, ax=ax, levels=levels)

        # add colour bar and title
        cbar = plt.colorbar(con, orientation='horizontal', fraction=.057, pad=0.05)
        cbar.set_label(cbar_label, fontsize=self.fontSize, fontweight=self.fontWeight)
        if cbar_ticks is not None:
            cbar.set_ticks(cbar_ticks)
        if cbar_tick_labels is not None:
            cbar.set_ticklabels(cbar_tick_labels, fontsize=self.fontSize, fontweight=self.fontWeight)

        # Add title
        plt.title(title, fontsize=self.fontSize + 4, fontweight=self.fontWeight)


    def plot_number_of_folds(self, metrics=['AVG']) -> None:

        # Read results
        foldsFile = os.path.join(self.resultsdir, "n_folds.csv")
        df = self.ingest_csv(foldsFile)
        grid = self.build_grid(df)

        metricIndexMap = { # boy this is stupid
            'MIN': 2,
            'AVG': 3,
            'MAX': 4,
            '1th PCT' : 5,
            '5th PCT': 6,
            '10th PCT': 7,
            '25th PCT': 8,
            '50th PCT': 9,
            '75th PCT': 10,
            '90th PCT': 11,
            '95th PCT': 12,
            '99th PCT': 13
        }

        for metric in metrics:
            metricIndex = metricIndexMap[metric]

            folds = np.array([])
            for row in df.itertuples():
                if "(Earth)" not in row[1]:
                    continue
                folds = np.append(folds, float(row[metricIndex]))

            # Build figure
            plt.clf()
            fig = plt.figure(figsize=(12, 9))
            ax = fig.add_subplot(111, facecolor='w', frame_on=False)

            # Get basemap
            self.plot_basemap(ax)

            # Set ineterpolation
            interpolation_method = 'linear'

            # Build out contour levels and labels
            levels = None
            cbar_ticks = None
            cbar_tick_labels = None
            if metric != 'AVG':
                err = 0.999 # error terms categorizes [1-err, 1) into 0 folds, [2, 2-err) into 1 folds, etc.
                levels = np.arange(1 - err, np.ceil(folds.max()) + 1, 1)
                levels = np.insert(levels, 0, 0.)

                cbar_ticks = []
                for ii in range(len(levels) - 1):
                    cbar_ticks.append((levels[ii] + levels[ii + 1]) / 2)
                cbar_tick_labels = [str(int(np.floor(tick + err))) for tick in cbar_ticks]

            # Plot contour
            title = metric + " Folds of Coverage"
            cbar_label = "Folds"
            self.plot_contourf(
                ax,
                grid,
                folds,
                interpolation_method,
                title,
                cbar_label=cbar_label,
                levels=levels,
                cbar_ticks=cbar_ticks,
                cbar_tick_labels=cbar_tick_labels
            )

            # Save
            outfile = os.path.join(self.outdir, "_".join(title.lower().split(" ")) + ".png")
            plt.savefig(outfile, format="png", dpi=300, bbox_inches="tight")


    def plot_avg_daily_vis(self) -> None:
        self.plot_access_metric('AVG_DAILY_VIS', "Average Daily Visibility", "Time (hrs)")


    def plot_mtta(self) -> None:
        self.plot_access_metric('MTTA', "Mean Time To Access", "Time (hrs)")


    def plot_access_metric(self, metric: str, title:str, cbar_label: str) -> None:

        # Read results
        accessFile = os.path.join(self.resultsdir, "access_metrics.csv")
        df = pd.read_csv(accessFile)

        grid = self.build_grid(df)
        vals = df[[col for col in df.columns if metric in col][0]].to_numpy() / 3600.0 # convert to hours

        # Build figure
        plt.clf()
        fig = plt.figure(figsize=(12, 9))
        ax = fig.add_subplot(111, facecolor='w', frame_on=False)

        # Get basemap
        self.plot_basemap(ax)

        # Set ineterpolation
        interpolation_method = 'cubic'
        if metric == 'MTTA':
            self.cmap = 'turbo'
        else:
            self.cmap = 'turbo_r'

        # Plot contour
        self.plot_contourf(
            ax,
            grid,
            vals,
            interpolation_method,
            title,
            cbar_label=cbar_label
        )

        # Save
        outfile = os.path.join(self.outdir, "_".join(title.lower().split(" ")) + ".png")
        plt.savefig(outfile, format="png", dpi=300, bbox_inches="tight")


if __name__ == "__main__":

    argparser = argparse.ArgumentParser(description="Plot trace results.")
    argparser.add_argument("resultsdir", type=str, help="The directory containing the results.")
    argparser.add_argument("--outdir", type=str, help="The output directory for the plots.",
                           default=None)
    args = argparser.parse_args()

    resultsDir = args.resultsdir
    if (args.outdir is None):
        outDir = os.path.join(resultsDir, 'plots')
    else:
        outDir = args.outdir

    tracer = Tracer(resultsDir, outDir)

    metrics = [
        'MIN',
        'AVG',
        'MAX',
        # '1th PCT',
        # '5th PCT',
        # '10th PCT',
        # '25th PCT',
        # '50th PCT',
        # '75th PCT',
        # '90th PCT',
        # '95th PCT',
        # '99th PCT'
    ]
    tracer.plot_number_of_folds(metrics=metrics)
    tracer.plot_avg_daily_vis()
    tracer.plot_mtta()
