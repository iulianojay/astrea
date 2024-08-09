import matplotlib.pyplot as plt
import numpy as np
import pandas as pd

data = pd.read_csv('./bin/results/main.csv',index_col=False)

t = data['time (min)'].to_numpy()
sma = data['sma (km)'].to_numpy()
ecc = data['ecc'].to_numpy()
inc = data['inc (deg)'].to_numpy()
raan = data['raan (deg)'].to_numpy()
w = data['w (deg)'].to_numpy()
theta = data['theta (deg)'].to_numpy()

fig = plt.gcf()

ax1 = plt.subplot(611)
plt.plot(t, sma)
plt.tick_params('x', labelsize=6)

# share x only
ax2 = plt.subplot(612, sharex=ax1)
plt.plot(t, ecc)
plt.tick_params('x', labelbottom=False)

# share x only
ax3 = plt.subplot(613, sharex=ax1)
plt.plot(t, inc)
plt.tick_params('x', labelbottom=False)

# share x only
ax4 = plt.subplot(614, sharex=ax1)
plt.plot(t, raan)
plt.tick_params('x', labelbottom=False)

# share x only
ax5 = plt.subplot(615, sharex=ax1)
plt.plot(t, w)
plt.tick_params('x', labelbottom=False)

# share x only
ax6 = plt.subplot(616, sharex=ax1)
plt.plot(t, theta)
plt.tick_params('x', labelbottom=False)

fig.savefig('./bin/results/main.png')