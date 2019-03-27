from matplotlib import pyplot as plt
import numpy as np

time = []
S = []
error = []
names = []

for i in range(4, 11):
    try:
        data = np.fromfile('localSpin' + str(2*i) + '.bin')
    except:
        continue

    names.append(r'$N = ' + str(2*i) + r'$')
    t = []
    s = []
    ds = []

    for n, entry in enumerate(data):
        stage = n % 3
        if stage == 0:
            t.append(entry)
        elif stage == 1:
            s.append(entry)
        elif stage == 2:
            ds.append(entry)
    time.append(t)
    S.append(s)
    error.append(ds)

plt.rcParams.update({'font.size': 15})
fig = plt.figure()
yMax = np.amax(S)
yMin = np.amin(S)
xMin = np.amin(time)
xMax = np.amax(time)
ax = fig.subplots(subplot_kw=dict(aspect='auto', autoscale_on=False, xlim=(xMin, xMax), ylim=(yMin, yMax)))
ax.grid()
ax.set_yscale('log')
#ax.set_xscale('log')

plots = []
for n, s in enumerate(S):
    temp = ax.plot(time[n], s, '-o', lw=1, ms=2)[0]
    plots.append(temp)

ax.set_ylabel(r'$\langle S_j(t) S_j(0) \rangle$')
ax.set_xlabel(r'$t$')
ax.legend(tuple(plots), tuple(names))

plt.show()
