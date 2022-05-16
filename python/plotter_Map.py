import numpy as np
import pandas as pd
import sys
from matplotlib import pyplot as plt
from matplotlib import cm

if __name__ == '__main__':

    if len(sys.argv) != 3:
        sys.exit('Missing argument! usage: ./plotter_Map.py dir sim_name')

    odir = str(sys.argv[1])
    sim_name = str(sys.argv[2])

    # own results


    data_d = pd.read_csv("../examples/"+ odir +"/output_"+sim_name+"Phase.dat", sep = " ")
    data_s1 = pd.read_csv("../examples/"+ odir +"/output_"+sim_name+"F1.dat", sep = " ")
    data_s2 = pd.read_csv("../examples/"+ odir +"/output_"+sim_name+"F2.dat", sep = " ")
    data_u1 = pd.read_csv("../examples/"+ odir +"/output_"+sim_name+"u1.dat", sep = " ")
    data_u2 = pd.read_csv("../examples/"+ odir +"/output_"+sim_name+"u2.dat", sep = " ")
    data_h = pd.read_csv("../examples/"+ odir +"/output_"+sim_name+"H.dat", sep = " ")
    
    
    x = data_d.values[0,:]
    y = data_d.values[1,:]
    
    #print(x)
    #print(y)
    #print(data_d.values[2,:])
    
    d_start_idx = 2
    d_finish_idx = len(data_d.values[:,0])-1
    d_mid = int((d_start_idx+d_finish_idx)/15)
    
    frames = [d_start_idx,d_mid, d_finish_idx]
    
    # Numerical solution

    fig, ax = plt.subplots(nrows = len(frames), ncols = 2, figsize = (8,10.8,), constrained_layout = True)
    i=0
    

    for f in frames: 
        #im_1 = ax[i,0].pcolormesh(x.reshape(3,3),y.reshape(3,3),data_d.values[f,:].reshape(3,3), cmap = "coolwarm", vmin = 0, vmax = 1, shading = "gouraud", alpha = 0.5)
        #im_2 = ax[i,1].pcolormesh(x.reshape(3,3),y.reshape(3,3),data_u2.values[f,:].reshape(3,3), cmap = "coolwarm", vmin = 0, vmax = 0.2, shading = "gouraud", alpha = 0.5)

        ax[i,0].scatter(x,y,c = data_d.values[f,:],s=50, cmap = "coolwarm", vmin = 0, vmax = 1, )
        ax[i,1].scatter(x,y,c = data_u2.values[f,:],s=50, cmap = "coolwarm", vmin = 0, vmax = 0.2,)
        
        ax[i,0].set_title('Damage, step: ' + str(f-1))
        ax[i,1].set_title('U2, step: ' + str(f-1))
        
        #fig.colorbar(im_1, ax=ax[i,0])
        #fig.colorbar(im_2, ax=ax[i,1])

        #print(data_u2.values[f,:])
        #print(f)

        i=i+1
    
    plt.show()
