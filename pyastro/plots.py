import matplotlib.pyplot as plt
import pandas as pd
from typing import List, Tuple


def plot_coes(title: str, infile: str, outfile: str) -> None:

    columns = [
        'sma (km)',
        'ecc',
        'inc (deg)',
        'raan (deg)',
        'w (deg)',
        'theta (deg)'
    ]

    titles = [
        "Semimajor Axis\n(km)",
        "Eccentricity",
        "Inclination\n(deg)",
        "Right Ascension\n(deg)",
        "Arg. Perigee\n(deg)",
        "True Anomaly\n(deg)"
    ]

    limits = [
        None,
        None,
        None,
        None,
        None,
        [0, 360]
    ]

    plot_element_set(title, infile, outfile, columns, titles, limits)


def plot_cartesian(title: str, infile: str, outfile: str) -> None:

    columns = [
        'x (km)',
        'y (km)',
        'z (km)',
        'vx (km/s)',
        'vy (km/s)',
        'vz (km/s)'
    ]

    titles = [
        "X Position\n(km)",
        "Y Position\n(km)",
        "Z Position\n(km)",
        "X Veclocity\n(km/s)",
        "Y Veclocity\n(km/s)",
        "Z Veclocity\n(km/s)"
    ]

    limits = [None]*6

    plot_element_set(title, infile, outfile, columns, titles, limits)


def plot_element_set(title: str, infile: str, outfile: str, columns: List[str], titles: List[str], limits: List[Tuple[float, float]]) -> None:

    df = pd.read_csv(infile,index_col=False)
    
    t = df['time (min)'].to_numpy()
    data = [df[col].to_numpy() for col in columns]

    fig, axes = plt.subplots(nrows=6, ncols=1, figsize=(10, 8), sharex=True)
    fig.suptitle(title)

    for ax, vals, axTitle, axLimits in zip(axes, data, titles, limits):
        ax.plot(t, vals)
        ax.grid(True)
        ax.tick_params('x', labelsize=False)
        if axTitle is not None:
            ax.set_ylabel(axTitle)
        if axLimits is not None:
            ax.set_ylim(axLimits)

    plt.xlim(t[0], t[-1])
    fig.tight_layout()

    fig.savefig(outfile)


if __name__=='__main__':

    title = 'Cowells Method Test'
    infile = './bin/results/cowells_test/main.csv'
    outfile = './bin/results/cowells_test/main.png'

    try:
        plot_coes(title, infile, outfile)
    except:
        plot_cartesian(title, infile, outfile)