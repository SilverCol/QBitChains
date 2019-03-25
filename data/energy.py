from matplotlib import pyplot as plt
import numpy as np

data = np.fromfile('phaseSum.bin')

beta = []
E = []

for n, entry in enumerate(data):
    stage = n % 3
    if stage == 0:
        beta.append(entry)
    elif stage == 1:
        E.append(entry)

beta = np.array(beta)
E = np.array(E)

E = - np.log(E)
E = np.gradient(E, beta)

plt.rcParams.update({'font.size': 15})
fig = plt.figure()
yMax = max(E)
yMin = min(E)
xMin = min(beta)
xMax = max(beta)
ax = fig.subplots(subplot_kw=dict(aspect='auto', autoscale_on=False, xlim=(xMin, xMax), ylim=(yMin, yMax)))
ax.grid()

ax.plot(beta, E, '-o', lw=1, ms=2)

ax.set_ylabel(r'$\langle H \rangle$')
ax.set_xlabel(r'$\beta$')

plt.show()
