import matplotlib.pyplot as plt
import numpy as np
import pandas as pd

def plot_coes(infile: str, outfile: str) -> None

    data = pd.read_csv(infile,index_col=False)

    t = data['time (min)'].to_numpy()
    sma = data['sma (km)'].to_numpy()
    ecc = data['ecc'].to_numpy()
    inc = data['inc (deg)'].to_numpy()
    raan = data['raan (deg)'].to_numpy()
    w = data['w (deg)'].to_numpy()
    theta = data['theta (deg)'].to_numpy()

    fig, (ax1, ax2, ax3, ax4, ax5, ax6) = plt.subplots(nrows=6, ncols=1, figsize=(10, 8), sharex=True)
    fig.suptitle("Cowells Method Test")

    ax1.plot(t, sma)
    ax1.tick_params('x', labelsize=False)
    ax1.set_ylabel("Semimajor Axis\n(km)")
    ax1.grid(True)

    # share x only
    ax2.plot(t, ecc)
    ax2.tick_params('x', labelbottom=False)
    ax2.set_ylabel("Eccentricity")
    ax2.grid(True)

    # share x only
    ax3.plot(t, inc)
    ax3.tick_params('x', labelbottom=False)
    ax3.set_ylabel("Inclination\n(deg)")
    ax3.grid(True)

    # share x only
    ax4.plot(t, raan)
    ax4.tick_params('x', labelbottom=False)
    ax4.set_ylabel("Right Ascension\n(deg)")
    ax4.grid(True)

    # share x only
    ax5.plot(t, w)
    ax5.tick_params('x', labelbottom=False)
    ax5.set_ylabel("Arg. Perigee\n(deg)")
    ax5.grid(True)

    # share x only
    ax6.plot(t, theta)
    ax6.set_ylabel("True Anomaly\n(deg)")
    ax6.grid(True)
    ax6.set_ylim([0, 360])

    plt.xlim(t[0], t[-1])
    fig.tight_layout()

    fig.savefig(outfile)

if __name__=='__main__':

    infile = './bin/results/cowells_test/main.csv'
    outfile = './bin/results/cowells_test/main.png'

    plot_coes(infile, outfile)