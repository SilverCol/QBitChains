from matplotlib import pyplot as plt
import numpy as np

data = np.fromfile('freeEnergy.bin')

beta = []
E = []
error = []

for n, entry in enumerate(data):
    stage = n % 3
    if stage == 0:
        beta.append(entry)
        print('beta: ' + str(entry))
    elif stage == 1:
        E.append(entry)
        print('E: ' + str(entry))
    elif stage == 2:
        error.append(entry)
        print('dE: ' + str(entry))

plt.rcParams.update({'font.size': 15})
fig = plt.figure()
yMax = max(E)
yMin = min(E)
xMin = min(beta)
xMax = max(beta)
ax = fig.subplots(subplot_kw=dict(aspect='auto', autoscale_on=False, xlim=(xMin, xMax), ylim=(yMin, yMax)))
ax.grid()

ax.plot(beta, E, '-', lw=2)

ax.set_ylabel(r'$F$')
ax.set_xlabel(r'$\beta$')

plt.show()
