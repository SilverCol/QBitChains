from matplotlib import pyplot as plt
import numpy as np

beta = []
F = []
error = []
names = []

for i in range(11):
    try:
        data = np.fromfile('phaseSum' + str(2*i) + '.bin')
    except:
        continue

    names.append(r'$N = ' + str(2*i) + r'$')
    b = []
    f = []
    df = []

    for n, entry in enumerate(data):
        stage = n % 3
        if stage == 0:
            b.append(entry)
        elif stage == 1:
            f.append(entry)
        elif stage == 2:
            df.append(entry)
    beta.append(b)
    F.append(f)
    error.append(df)

error = np.divide(error, F)
F = - np.log(F)
F = np.divide(F, beta)
error = np.divide(error, beta)

plt.rcParams.update({'font.size': 15})
fig = plt.figure()
yMax = np.amax(F) + 3
yMin = np.amin(F)
xMin = np.amin(beta)
xMax = np.amax(beta)
ax = fig.subplots(subplot_kw=dict(aspect='auto', autoscale_on=False, xlim=(xMin, xMax), ylim=(yMin, yMax)))
ax.grid()

plots = []
for n, f in enumerate(F):
    temp = ax.errorbar(beta[n], f, error[n], fmt='-o', lw=1, ms=2)[0]
    plots.append(temp)

ax.set_ylabel(r'$F$')
ax.set_xlabel(r'$\beta$')
ax.legend(tuple(plots), tuple(names), ncol=5)

plt.show()
