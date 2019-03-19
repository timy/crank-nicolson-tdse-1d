import numpy as np
import matplotlib.pyplot as plt

base_dir = 'res_re'
t = np.loadtxt(base_dir+'/time_0.dat')
f = np.loadtxt(base_dir+'/field_0.dat')

plt.plot(t, f)
plt.show()
