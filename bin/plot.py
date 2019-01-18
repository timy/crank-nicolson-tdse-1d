import numpy as np
import matplotlib.pyplot as plt
import matplotlib.animation as animation

base_dir = 'res_re' # 'res_im' for imaginary time propagation for TISE
t = np.loadtxt(base_dir+'/time_0.dat')
x = np.loadtxt(base_dir+'/grid_0.dat')
pot = np.loadtxt(base_dir+'/pot_0.dat')
# may change the index of the followings for excited state with TISE
wf = np.loadtxt(base_dir+'/norm_0.dat')
energy = np.loadtxt(base_dir+'/energy_0.dat')
nt = len(t)

bTISE = False;
if len(np.shape(pot)) == 1:
    bTISE = True

# rescale the whole data into the region [0, 1] along y-axis
pot_min, pot_max = np.amin(pot), np.amax(pot)
wf_min, wf_max = np.amin(wf), np.amax(wf)

pot = (pot - pot_min) / (pot_max - pot_min)
if bTISE == False:
    wf = (wf - wf_min) / (wf_max - wf_min)
    expect_x = np.loadtxt(base_dir+'/x_0.dat')

# move the wave packet to the position corresponding to
# the actual energy of the system
for i in xrange(nt):
    wf[i] += (energy[i] - pot_min) / (pot_max - pot_min)

# start the animation, prepare the axes and lines
fig = plt.figure ()
ax = plt.axes (xlim=(x[0], x[-1]), ylim=(0, 1))
line_wf, = ax.plot (x, wf[0], 'k')
if bTISE == True:
    line_pot, = ax.plot (x, pot, 'r')
else:
    line_pot, = ax.plot (x, pot[0], 'r')

# indicate the potential energy on the other axis
ax_pot = ax.twinx()
ax_pot.set_ylim([pot_min, pot_max])

# time indicator
text_time = ax.text(0.5*x[-1], 0.9, '')
text_x = ax.text(0.5*x[-1], 0.8, '')

def init_ani():
    line_wf.set_data(x, wf[0])
    line_pot.set_data(x, pot[0])
    text_time.set_text('')
    text_x.set_text('')
    return line_wf, line_pot, text_time, text_x

def run (i):
    line_wf.set_data (x, wf[i])
    if bTISE is True:
        line_pot.set_data (x, pot)
    else:
        line_pot.set_data (x, pot[i])
    text_time.set_text (r'$t=%5.1f$ a.u.' % t[i])
    text_x.set_text (r'$x=%5.2f$ a.u.' % expect_x[i])
    return line_wf, line_pot, text_time, text_x,

ani = animation.FuncAnimation (fig, run, frames=nt, init_func=init_ani,
                               interval=200, blit=True)

# uncomment this if video is desired
# ani.save('res/prop.mp4')

plt.show()
