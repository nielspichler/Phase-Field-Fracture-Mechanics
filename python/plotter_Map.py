import numpy as np
import pandas as pd
import sys
from matplotlib import pyplot as plt
from matplotlib import cm

if __name__ == '__main__':

    if len(sys.argv) < 3:
        sys.exit('Missing argument! usage: ./plotter_Map.py dir sim_name step_number ... ')

    odir = str(sys.argv[1])
    sim_name = str(sys.argv[2])
    
    frames = []
    
    for i in range(len(sys.argv)-3):
        frames.append(int(sys.argv[3+i])+2)

    # own results

    cmap = "jet"
    levels = 30

    data_d = pd.read_csv("../examples/"+ odir +"/output_"+sim_name+"Phase.dat", sep = " ")
    data_s1 = pd.read_csv("../examples/"+ odir +"/output_"+sim_name+"F1.dat", sep = " ")
    data_s2 = pd.read_csv("../examples/"+ odir +"/output_"+sim_name+"F2.dat", sep = " ")
    data_u1 = pd.read_csv("../examples/"+ odir +"/output_"+sim_name+"u1.dat", sep = " ")
    data_u2 = pd.read_csv("../examples/"+ odir +"/output_"+sim_name+"u2.dat", sep = " ")
    data_h = pd.read_csv("../examples/"+ odir +"/output_"+sim_name+"H.dat", sep = " ")
    
    
    x = data_d.values[0,:]
    y = data_d.values[1,:]
    

    fig, ax = plt.subplots(nrows = len(frames), ncols = 5, figsize = (17,8,), constrained_layout = True)
    i=0
    
    for f in frames: 

        im_1 = ax[i,0].tricontourf(x,y,data_d.values[f,:], cmap = cmap,  alpha = 0.5, levels = levels)
        for c in im_1.collections:
            c.set_edgecolor("face")
            c.set_linewidth(0.01)
        im_1 = ax[i,0].scatter(x,y,c = data_d.values[f,:],s=2, cmap = cmap)#, vmin = 0, vmax = 1,
        
        im_2 = ax[i,1].tricontourf(x,y,data_u2.values[f,:], cmap = cmap, alpha = 0.5, levels = levels)
        for c in im_2.collections:
            c.set_edgecolor("face")
            c.set_linewidth(0.01)                
        im_2 = ax[i,1].scatter(x,y,c = data_u2.values[f,:],s=2, cmap = cmap)#, vmin = 0, vmax = 0.2,
        
        im_3 = ax[i,2].tricontourf(x,y,data_u1.values[f,:], cmap = cmap, alpha = 0.5, levels = levels)
        for c in im_3.collections:
            c.set_edgecolor("face")
            c.set_linewidth(0.01)        
        im_3 = ax[i, 2].scatter(x, y, c=data_u1.values[f, :], s=2, cmap=cmap)  # , vmin = 0, vmax = 0.2,


        nodal_disp = np.sqrt(data_u1.values[f,:]**2 + data_u2.values[f,:]**2)
        im_4 = ax[i,3].tricontourf(x,y,nodal_disp, cmap = cmap, alpha = 0.3, levels = levels)
        for c in im_4.collections:
            c.set_edgecolor("face")
            c.set_linewidth(0.01)
        im_4 = ax[i, 3].scatter(x, y, c=nodal_disp, s=2, cmap=cmap)  # , vmin = 0, vmax = 0.2,
        ax[i,3].quiver(x,y, data_u1.values[f,:], data_u2.values[f,:], nodal_disp, cmap = cmap)
        
                
        nodal_forces = np.sqrt(data_s1.values[f,:].astype(np.float)**2 + data_s2.values[f,:].astype(np.float)**2)
        im_5 = ax[i,4].tricontourf(x,y,nodal_forces, cmap = cmap, alpha = 0.3, levels = levels)
        for c in im_5.collections:
            c.set_edgecolor("face")
            c.set_linewidth(0.01)
        im_5 = ax[i, 4].scatter(x, y, c=nodal_forces, s=2, cmap=cmap)  # , vmin = 0, vmax = 0.2,
        ax[i,4].quiver(x,y, data_s1.values[f,:].astype(np.float), data_s2.values[f,:].astype(np.float), nodal_forces, cmap = cmap)


        ax[i, 0].set_title('Damage, step: ' + str(f-2))
        ax[i, 1].set_title('U2, step: ' + str(f-2))
        ax[i, 2].set_title('U1, step: ' + str(f - 2))
        ax[i, 3].set_title('Disp resultant, step: ' + str(f - 2))
        ax[i, 4].set_title('RF resultant, step: ' + str(f - 2))
        
        fig.colorbar(im_1, ax=ax[i,0])
        fig.colorbar(im_2, ax=ax[i,1])
        fig.colorbar(im_3, ax=ax[i, 2])
        fig.colorbar(im_4, ax=ax[i, 3])
        fig.colorbar(im_5, ax=ax[i, 4])

        #print(data_u2.values[f,:])
        #print(f)

        i=i+1
    
    plt.show()
