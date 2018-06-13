import numpy as np
import matplotlib.pyplot as plt
import matplotlib.animation as animation

t = np.loadtxt('res/time.dat')
x = np.loadtxt('res/grid.dat')
wf = np.loadtxt('res/norm.dat')
pot = np.loadtxt('res/pot.dat')

# for i in xrange(5):
#     plt.plot(x, wf[i*1])

bTISE = False;
if len(np.shape(pot)) == 1:
    bTISE = True

fig = plt.figure()
ax = plt.axes(xlim=(x[0], x[-1]), ylim=(0, 2))
line_wf, = ax.plot([], [], 'k')

ax_pot = ax.twinx()
ax_pot.tick_params('pot', colors='r')
ax_pot.set_ylim([0, 250])
line_pot, = ax_pot.plot([], [], 'r')

text = ax.text(0.5*x[-1], 1.75, '')

def init_ani():
    line_wf.set_data([], [])
    line_pot.set_data([], [])
    return line_wf, line_pot,

def run(i):
    line_wf.set_data(x, wf[i])
    if bTISE is True:
        line_pot.set_data(x, pot)
    else:
        line_pot.set_data(x, pot[i])
    text.set_text('t=%f au' % t[i])
    return line_wf, line_pot, text,

ani = animation.FuncAnimation(fig, run, frames=len(t), init_func=init_ani, interval=20, blit=True)

# # uncomment this if video is desired
# #ani.save('res/prop.mp4')

plt.show()
