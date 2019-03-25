from matplotlib import pyplot as plt
import numpy as np

data = np.fromfile('phaseSum.bin')

beta = []
F = []
error = []

for n, entry in enumerate(data):
    stage = n % 3
    if stage == 0:
        beta.append(entry)
    elif stage == 1:
        F.append(entry)
    elif stage == 2:
        error.append(entry)

beta = np.array(beta)
F = np.array(F)
error = np.array(error)

error = np.divide(error, F)
F = - np.log(F)
F = np.divide(F, beta)
error = np.divide(error, beta)

plt.rcParams.update({'font.size': 15})
fig = plt.figure()
yMax = max(F)
yMin = min(F)
xMin = min(beta)
xMax = max(beta)
ax = fig.subplots(subplot_kw=dict(aspect='auto', autoscale_on=False, xlim=(xMin, xMax), ylim=(yMin, yMax)))
ax.grid()

ax.errorbar(beta, F, error, fmt='-o', lw=1, ms=2)

ax.set_ylabel(r'$F$')
ax.set_xlabel(r'$\beta$')

plt.show()
