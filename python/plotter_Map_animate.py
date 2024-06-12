import numpy as np
import pandas as pd
import sys
from matplotlib import pyplot as plt
from matplotlib import cm
from matplotlib.animation import FuncAnimation
from matplotlib.tri import Triangulation

if __name__ == '__main__':

    if len(sys.argv) < 3:
        sys.exit('Missing argument! usage: ./plotter_Map.py dir sim_name variable ... ')

    odir = str(sys.argv[1])
    sim_name = str(sys.argv[2])
    var = str(sys.argv[3])

    if var not in ['Phase', 'U1', 'U2']:
        sys.exit('variable can only be Phase, U1 or U2')

    fig, ax = plt.subplots(constrained_layout = True)

    # own results

    cmap = "Oranges"
    levels = 30
    alpha = 1

    data_d = pd.read_csv("../examples/"+ odir +"/output_"+sim_name+"Phase.dat", sep = " ")
    data_u1 = pd.read_csv("../examples/"+ odir +"/output_"+sim_name+"u1.dat", sep = " ")
    data_u2 = pd.read_csv("../examples/"+ odir +"/output_"+sim_name+"u2.dat", sep = " ")

    if var == 'Phase':
        data = data_d
        vmax = data.values[2:,:].max().max()
        vmin = data.values[2:, :].min().min()
    elif var == 'U1':
        data = data_u1
        vmax = data.values[2:,:].max().max()
        vmin = data.values[2:, :].min().min()

    elif var == 'U2':
        data = data_u2
        vmax = data.values[2:,:].max().max()
        vmin = data.values[2:, :].min().min()

    else:
        print('We should not be there... Phase will be plotted')
        data = data_d
        vmin = 0
        vmax = 1

    
    x = data_d.values[0,:] # initial coord
    y = data_d.values[1,:] # initial coord

    triangulation = Triangulation(x, y)

    # to properly set the bounds of the colorbar, we need to plota contourf that ranges from the min to the max value

    contour = ax.tricontourf(triangulation,
                             #data.values[-1,:],
                             np.linspace(vmin, vmax, len(data.values[-1,:])),
                             cmap = cmap,
                             alpha = alpha,
                             levels = levels,
                             vmin=vmin,
                             vmax = vmax)


    # Add a colorbar
    cbar = fig.colorbar(contour, ax=ax)
    cbar.set_label(var)

    ax.set_title('Map of %s'%var)


    def init():
        global contour
        for c in contour.collections:
            c.remove()
        contour = ax.tricontourf(triangulation,
                                 data.values[2,:],
                                 cmap = cmap,
                                 alpha = alpha,
                                 levels = levels,
                                 vmin=vmin,
                                 vmax = vmax)
        return contour.collections


    # Update function: this is called sequentially
    def update(frame):
        global contour

        # Remove the old contour plots
        for c in contour.collections:
            c.remove()

        # Create new contour plots
        contour = ax.tricontourf(triangulation,
                                 data.values[frame,:],
                                 cmap = cmap,
                                 alpha = alpha,
                                 levels = levels,
                                 vmin=vmin,
                                 vmax=vmax)
        return contour.collections


    ani = FuncAnimation(fig, update, frames=data.values.shape[0]-2, init_func=init, blit=True)
    #ani.save('tricontourf_animation.mp4', writer='ffmpeg')
    
    plt.show()
