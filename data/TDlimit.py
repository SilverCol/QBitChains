from matplotlib import pyplot as plt
import numpy as np

beta = []
E = []
names = []
N = []

for i in range(11):
    try:
        data = np.fromfile('phaseSum' + str(2*i) + '.bin')
    except:
        continue

    N.append(2*i)
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
last = []
for n in range(len(E)):
    E[n] = np.gradient(E[n], beta[n])
    E[n] /= N[n]
    last.append(E[n][-1])

plt.rcParams.update({'font.size': 15})
fig = plt.figure()
yMax = np.amax(last) + .05
yMin = np.amin(last)
xMin = np.amin(N)
xMax = np.amax(N)
ax = fig.subplots(subplot_kw=dict(aspect='auto', autoscale_on=False, xlim=(xMin, xMax), ylim=(yMin, yMax)))
ax.grid()

ax.plot(N, last, '-o', lw=1, ms=2)

ax.set_ylabel(r'$\frac{1}{N}\langle H \rangle$')
ax.set_xlabel(r'$N$')

plt.show()
