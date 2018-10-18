import numpy as np
import matplotlib.pyplot as plt
import matplotlib.animation as animation

t = np.loadtxt('res/time.dat')
x = np.loadtxt('res/grid.dat')
wf = np.loadtxt('res/norm.dat')
pot = np.loadtxt('res/pot.dat')

bTISE = False;
if len(np.shape(pot)) == 1:
    bTISE = True

# rescale the whole data into the region [0, 1] along y-axis
pot_min, pot_max = np.amin(pot), np.amax(pot)
wf_min, wf_max = np.amin(wf), np.amax(wf)

pot = (pot - pot_min) / (pot_max - pot_min)
wf = (wf - wf_min) / (wf_max - wf_min)

# move the wave packet to the position corresponding to
# the actual energy of the system
val_energy = 208.
y_energy = (val_energy - pot_min) / (pot_max - pot_min)
wf += y_energy

# start the animation, prepare the axes and lines
fig = plt.figure ()
ax = plt.axes (xlim=(x[0], x[-1]), ylim=(0, 1))
line_wf, = ax.plot (x, wf[0], 'k')
line_pot, = ax.plot (x, pot[0], 'r')

# indicate the potential energy on the other axis
ax_pot = ax.twinx()
ax_pot.set_ylim([pot_min, pot_max])

# time indicator
text = ax.text(0.5*x[-1], 0.9, '')

def init_ani():
    line_wf.set_data(x, wf[0])
    line_pot.set_data(x, pot[0])
    text.set_text('')
    return line_wf, line_pot, text

def run (i):
    line_wf.set_data (x, wf[i])
    if bTISE is True:
        line_pot.set_data (x, pot)
    else:
        line_pot.set_data (x, pot[i])
    text.set_text (r'$t=%5.1f$ a.u.' % t[i])
    return line_wf, line_pot, text,

ani = animation.FuncAnimation (fig, run, frames=len(t), init_func=init_ani,
                               interval=200, blit=True)

# uncomment this if video is desired
# ani.save('res/prop.mp4')

plt.show()
