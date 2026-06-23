import argparse
import os
import matplotlib.pyplot as plt
import matplotlib.dates as mdates
import matplotlib.colors as mcolors
import pandas as pd
import numpy as np
import datetime
import sqlite3
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

        # Find the database file in the results directory
        db_files = [f for f in os.listdir(resultsdir) if f.endswith(".db")]
        if not db_files:
            raise FileNotFoundError(f"No .db file found in {resultsdir}")
        self.db_path = os.path.join(resultsdir, db_files[0])

        self.fontSize = 14
        self.fontWeight = "bold"
        self.cmap = "turbo_r"

        self.nLats = 1000
        self.nLons = 1000

        if not os.path.exists(self.outdir):
            os.makedirs(self.outdir)

    def read_folds_data(self) -> pd.DataFrame:
        """Read folds data from SQLite database."""
        conn = sqlite3.connect(self.db_path)
        query = "SELECT * FROM folds"
        df = pd.read_sql_query(query, conn)
        conn.close()
        return df

    def read_access_metrics_data(self) -> pd.DataFrame:
        """Read access metrics data from SQLite database."""
        conn = sqlite3.connect(self.db_path)
        query = "SELECT * FROM access_metrics"
        df = pd.read_sql_query(query, conn)
        conn.close()
        return df

    def read_ground_locations_data(self) -> pd.DataFrame:
        """Read ground location coordinates from SQLite database."""
        conn = sqlite3.connect(self.db_path)
        df = pd.read_sql_query("SELECT * FROM ground_locations", conn)
        conn.close()
        return df

    def build_base_basemap(
        self,
        lat0: float,
        lon0: float,
        lllon: float,
        lllat: float,
        urlon: float,
        urlat: float,
    ) -> None:
        # Set up Basemap instance
        self.lllon = lllon
        self.lllat = lllat
        self.urlon = urlon
        self.urlat = urlat

        projection = "robin"
        if lllon != -180.0:
            projection = "cea"
        self.map = Basemap(
            projection=projection,
            llcrnrlon=self.lllon,
            llcrnrlat=self.lllat,
            urcrnrlon=self.urlon,
            urcrnrlat=self.urlat,
            lat_0=lat0,
            lon_0=lon0,
            resolution="h",
        )

    def plot_basemap(self, ax: plt.Axes) -> None:

        # draw map details
        self.map.drawmapboundary(fill_color="white", ax=ax)
        self.map.fillcontinents(color="#C0C0C0", ax=ax)
        self.map.drawcountries(
            linewidth=0.75,
            linestyle="solid",
            color="#000073",
            antialiased=True,
            ax=ax,
            zorder=3,
        )

        parallelSep = 30.0
        if (self.urlat - self.lllat) < 5:
            parallelSep = 1.0
        elif (self.urlat - self.lllat) < 15:
            parallelSep = 2.0
        elif (self.urlat - self.lllat) < 30:
            parallelSep = 5.0
        elif (self.urlat - self.lllat) < 60:
            parallelSep = 10.0

        parallels = np.arange(self.lllat, self.urlat + parallelSep, parallelSep)
        parallels[0] += 5
        parallels[-1] -= 5
        self.map.drawparallels(
            parallels,
            color="black",
            linewidth=0.5,
            ax=ax,
            labels=[1, 1, 0, 0],
            fontsize=self.fontSize - 2,
        )

        meridianSep = 60.0
        if (self.urlon - self.lllon) < 5:
            meridianSep = 1.0
        elif (self.urlon - self.lllon) < 15:
            meridianSep = 2.0
        elif (self.urlon - self.lllon) < 30:
            meridianSep = 10.0
        elif (self.urlon - self.lllon) < 60:
            meridianSep = 20.0
        elif (self.urlon - self.lllon) < 120:
            meridianSep = 30.0

        meridians = np.arange(self.lllon, self.urlon + meridianSep, meridianSep)
        meridians[0] += 5
        meridians[-1] -= 5
        self.map.drawmeridians(
            meridians,
            color="0.25",
            linewidth=0.5,
            ax=ax,
            labels=[0, 0, 0, 1],
            fontsize=self.fontSize - 2,
        )

    def build_grid(self, ground_locs: pd.DataFrame) -> tuple:
        """Build grid from ground_locations DataFrame. Returns None if no data."""
        if ground_locs.empty:
            print(
                "Warning: No ground location data found in database for geographic plotting."
            )
            return None

        # NOTE: the database stores longitude in the 'latitude' column and vice-versa;
        # read them with the correct semantic meaning.
        lats = ground_locs["longitude"].to_numpy()
        lons = ground_locs["latitude"].to_numpy()

        lllon = float(np.min(lons))
        lllat = float(np.min(lats))
        urlon = float(np.max(lons))
        urlat = float(np.max(lats))

        lonRange = urlon - lllon
        latRange = urlat - lllat

        extra = 0.0
        lllon = float(np.max([np.round(lllon - extra * lonRange), -180.0]))
        lllat = float(np.max([np.round(lllat - extra * latRange), -90.0]))
        urlon = float(np.min([np.round(urlon + extra * lonRange), 180.0]))
        urlat = float(np.min([np.round(urlat + extra * latRange), 90.0]))

        self.build_base_basemap(
            float(np.mean(lons)), float(np.mean(lats)), lllon, lllat, urlon, urlat
        )

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
        levels: np.ndarray = None,
        cbar_ticks: List[float] = None,
        cbar_tick_labels: List[str] = None,
    ) -> None:

        # interpolate
        x, y, xi, yi = grid
        methods = [interpolation_method, "linear", "nearest"]
        zi = None
        for method in dict.fromkeys(methods):  # deduplicated, order preserved
            try:
                zi = griddata((x, y), values, (xi, yi), method=method, fill_value=0)
                break
            except Exception:
                continue
        if zi is None:
            zi = np.zeros((yi.shape[0], xi.shape[1]))

        # Cubic interpolation can overshoot into negatives at sharp boundaries;
        # clamp to the valid range [0, max] so the colorbar always starts at zero.
        zi = np.clip(zi, 0.0, None)

        # Build default levels anchored at zero when not provided by the caller.
        if levels is None:
            vmax = float(np.nanmax(zi))
            if vmax > 0:
                levels = np.linspace(0.0, vmax, 20)

        # contour plot
        con = self.map.contourf(
            xi, yi, zi, zorder=4, alpha=0.6, cmap=self.cmap, ax=ax, levels=levels
        )

        # add colour bar and title
        cbar = plt.colorbar(con, orientation="horizontal", fraction=0.057, pad=0.05)
        cbar.set_label(cbar_label, fontsize=self.fontSize, fontweight=self.fontWeight)
        if cbar_ticks is not None:
            cbar.set_ticks(cbar_ticks)
        if cbar_tick_labels is not None:
            cbar.set_ticklabels(
                cbar_tick_labels, fontsize=self.fontSize, fontweight=self.fontWeight
            )

        # Add title
        plt.title(title, fontsize=self.fontSize + 4, fontweight=self.fontWeight)

    def plot_number_of_folds(self, metrics=["AVG"]) -> None:
        """Plot number of folds. Skip if no ground location data available."""
        df = self.read_folds_data()
        if df.empty:
            print("No folds data found in database.")
            return

        ground_locs = self.read_ground_locations_data()
        grid = self.build_grid(ground_locs)
        if grid is None:
            print("Skipping folds plotting: No geographic data available.")
            return

        # Join folds to ground_locations by extracting base name from formatted object string
        # folds.object format: "Name [lat°, lon°] (Earth)"  →  base name: "Name"
        earth_folds = df[df["object"].str.contains("Earth", na=False)].copy()
        earth_folds["_base_name"] = (
            earth_folds["object"].str.split(" [", regex=False).str[0]
        )
        merged = ground_locs.merge(
            earth_folds, left_on="name", right_on="_base_name", how="inner"
        )

        metricColumnMap = {"MIN": "min_folds", "AVG": "avg_folds", "MAX": "max_folds"}

        # Build percentile lookup from merged data (each row = one ground point)
        pct_labels = [
            "1th PCT",
            "5th PCT",
            "10th PCT",
            "25th PCT",
            "50th PCT",
            "75th PCT",
            "90th PCT",
            "95th PCT",
            "99th PCT",
        ]
        percentile_data = {label: [] for label in pct_labels}
        for _, row in merged.iterrows():
            if pd.notna(row["percentiles"]):
                vals = [float(x) for x in row["percentiles"].split(",")]
                for i, label in enumerate(pct_labels):
                    if i < len(vals):
                        percentile_data[label].append(vals[i])
        percentile_data = {
            k: np.array(v) for k, v in percentile_data.items() if len(v) == len(merged)
        }

        for metric in metrics:
            if metric in metricColumnMap:
                folds = merged[metricColumnMap[metric]].to_numpy()
            elif metric in percentile_data:
                folds = percentile_data[metric]
            else:
                continue

            # Build figure
            plt.clf()
            fig = plt.figure(figsize=(12, 9))
            ax = fig.add_subplot(111, facecolor="w", frame_on=False)

            # Get basemap
            self.plot_basemap(ax)

            # Set ineterpolation
            interpolation_method = "linear"

            # Build out contour levels and labels
            levels = None
            cbar_ticks = None
            cbar_tick_labels = None
            if metric != "AVG":
                err = 0.999  # error terms categorizes [1-err, 1) into 0 folds, [2, 2-err) into 1 folds, etc.
                levels = np.arange(1 - err, np.ceil(folds.max()) + 1, 1)
                levels = np.insert(levels, 0, 0.0)

                cbar_ticks = []
                for ii in range(len(levels) - 1):
                    cbar_ticks.append((levels[ii] + levels[ii + 1]) / 2)
                cbar_tick_labels = [
                    str(int(np.floor(tick + err))) for tick in cbar_ticks
                ]

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
                cbar_tick_labels=cbar_tick_labels,
            )

            # Save
            outfile = os.path.join(
                self.outdir, "_".join(title.lower().split(" ")) + ".png"
            )
            plt.savefig(outfile, format="png", dpi=300, bbox_inches="tight")

    def plot_avg_daily_vis(self) -> None:
        self.plot_access_metric(
            "AVG_DAILY_VIS", "Average Daily Visibility", "Time (hrs)"
        )

    def plot_mtta(self) -> None:
        self.plot_access_metric("MTTA", "Mean Time To Access", "Time (hrs)")

    def plot_access_metric(self, metric: str, title: str, cbar_label: str) -> None:
        """Plot access metric. Skip if no ground location data available."""
        df = self.read_access_metrics_data()
        if df.empty:
            print(f"No access metrics data found in database for {metric}.")
            return

        ground_locs = self.read_ground_locations_data()
        ground_locs = ground_locs.drop_duplicates(
            subset=["name"]
        )  # guard against duplicate DB entries
        grid = self.build_grid(ground_locs)
        if grid is None:
            print(f"Skipping {title}: No geographic data available.")
            return

        # Filter access_metrics to Earth ground points for this metric; deduplicate by object
        # (guard against multiple DB entries for the same ground point).
        earth_data = df[
            (df["object"].str.contains("Earth", na=False))
            & (df["metric_type"] == metric)
        ].copy()
        if earth_data.empty:
            print(f"Skipping {title}: No geographic data available for {metric}.")
            return

        earth_data = earth_data.drop_duplicates(subset=["object"])

        # Left join on name == object so every ground location is represented; unmatched → 0
        merged = ground_locs.merge(
            earth_data, left_on="name", right_on="object", how="left"
        )
        merged["time_value"] = merged["time_value"].fillna(0.0)

        vals = merged["time_value"].to_numpy() / 3600.0  # convert to hours

        # Build figure
        plt.clf()
        fig = plt.figure(figsize=(12, 9))
        ax = fig.add_subplot(111, facecolor="w", frame_on=False)

        # Get basemap
        self.plot_basemap(ax)

        # Set ineterpolation
        interpolation_method = "cubic"
        if metric == "MTTA":
            self.cmap = "turbo"
        else:
            self.cmap = "turbo_r"

        # Plot contour
        self.plot_contourf(
            ax, grid, vals, interpolation_method, title, cbar_label=cbar_label
        )

        # Save
        outfile = os.path.join(self.outdir, "_".join(title.lower().split(" ")) + ".png")
        plt.savefig(outfile, format="png", dpi=300, bbox_inches="tight")


if __name__ == "__main__":
    argparser = argparse.ArgumentParser(description="Plot trace results.")
    argparser.add_argument(
        "resultsdir", type=str, help="The directory containing the results."
    )
    argparser.add_argument(
        "--outdir", type=str, help="The output directory for the plots.", default=None
    )
    args = argparser.parse_args()

    resultsDir = args.resultsdir
    if args.outdir is None:
        outDir = os.path.join(resultsDir, "plots")
    else:
        outDir = args.outdir

    tracer = Tracer(resultsDir, outDir)

    metrics = [
        "MIN",
        "AVG",
        "MAX",
        "1th PCT",
        "5th PCT",
        "10th PCT",
        "25th PCT",
        "50th PCT",
        "75th PCT",
        "90th PCT",
        "95th PCT",
        "99th PCT",
    ]
    # tracer.plot_number_of_folds(metrics=metrics)
    tracer.plot_avg_daily_vis()
    tracer.plot_mtta()
