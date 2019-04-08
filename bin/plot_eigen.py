import numpy as np
import matplotlib.pyplot as plt
import matplotlib.animation as animation

ns = 9
base_dir = 'res_im' # 'res_im' for imaginary time propagation for TISE
t = np.loadtxt(base_dir+'/time_0.dat')
x = np.loadtxt(base_dir+'/grid_0.dat')
pot = np.loadtxt(base_dir+'/pot_0.dat')


wf = np.loadtxt(base_dir+'/norm_0.dat')
energy = np.loadtxt(base_dir+'/energy_0.dat')
nt = t.size

plt.plot(pot)
for i in xrange(ns):
    wf = np.loadtxt(base_dir+'/norm_%d.dat' % i)
    energy = np.loadtxt(base_dir+'/energy_%d.dat' % i)
    plt.plot(wf+energy)

# plt.plot(wf)
plt.show()
