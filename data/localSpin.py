from matplotlib import pyplot as plt
import numpy as np

time = []
S = []
error = []

for i in range(11):
    try:
        data = np.fromfile('localSpin' + str(2*i) + '.bin')
    except:
        continue

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

for n, s in enumerate(S):
    ax.plot(time[n], s, '-o', lw=1, ms=2)

ax.set_ylabel(r'$\langle S_j(t) S_j(0) \rangle$')
ax.set_xlabel(r'$t$')

plt.show()
