import matplotlib.pyplot as plt
import pandas as pd
import numpy as np
from typing import List, Tuple


def plot_keplerian(title: str, infile: str, outfile: str) -> None:

    columns = [
        'sma (km)',
        'ecc',
        'inc (rad)',
        'raan (rad)',
        'w (rad)',
        'theta (rad)'
    ]

    titles = [
        "Semimajor Axis\n(km)",
        "Eccentricity",
        "Inclination\n(rad)",
        "Right Ascension\n(rad)",
        "Arg. Perigee\n(rad)",
        "True Anomaly\n(rad)"
    ]

    limits = [
        None,
        [0, 1],
        [0, np.pi],
        [0, 2*np.pi],
        [0, 2*np.pi],
        [0, 2*np.pi]
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
    data[-1] = [x % (2*np.pi) for x in data[-1]]

    fig, axes = plt.subplots(nrows=6, ncols=1, figsize=(10, 8), sharex=True)
    fig.suptitle(title)

    for ax, vals, axTitle, axLimits in zip(axes, data, titles, limits):
        ax.plot(t, vals)
        ax.grid(True)
        if axTitle is not None:
            ax.set_ylabel(axTitle)
        if axLimits is not None:
            ax.set_ylim(axLimits)

    plt.xlim(t[0], t[-1])
    plt.xlabel("Time (minutes)")
    fig.tight_layout()

    fig.savefig(outfile)


if __name__=='__main__':

    # test = 'two_body'
    # title = 'Two-Body Test'
    # test = 'j2mean'
    # title = 'J2 Mean VoP Test'
    # test = 'cowells'
    # title = 'Cowells Method Test'
    test = 'coes'
    title = 'KEPLERIANs VoP Test'
    infile = './bin/results/' + test + '/main.csv'
    outfile = './bin/results/' + test + '/main.png'

    try:
        plot_keplerian(title, infile, outfile)
    except:
        plot_cartesian(title, infile, outfile)