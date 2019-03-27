from matplotlib import pyplot as plt
import numpy as np

beta = []
E = []
names = []

for i in range(11):
    try:
        data = np.fromfile('phaseSum' + str(2*i) + '.bin')
    except:
        continue

    names.append(r'$N = ' + str(2*i) + r'$')
    e = []
    b = []

    for n, entry in enumerate(data):
        stage = n % 3
        if stage == 0:
            b.append(entry)
        elif stage == 1:
            e.append(entry)
    beta.append(b)
    E.append(e)

E = - np.log(E)
for n in range(len(E)):
    E[n] = np.gradient(E[n], beta[n])

plt.rcParams.update({'font.size': 15})
fig = plt.figure()
yMax = np.amax(E) + 2
yMin = np.amin(E)
xMin = np.amin(beta)
xMax = np.amax(beta)
ax = fig.subplots(subplot_kw=dict(aspect='auto', autoscale_on=False, xlim=(xMin, xMax), ylim=(yMin, yMax)))
ax.grid()

plots = []
for n, e in enumerate(E):
    temp = ax.plot(beta[n], e, '-o', lw=1, ms=2)[0]
    plots.append(temp)

ax.set_ylabel(r'$\langle H \rangle$')
ax.set_xlabel(r'$\beta$')
ax.legend(tuple(plots), tuple(names), ncol=5)

plt.show()
