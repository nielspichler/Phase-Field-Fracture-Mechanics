import numpy as np
import pandas as pd
from matplotlib import pyplot as plt
from matplotlib import cm

if __name__ == '__main__':

    # own results

    sim_name = 'sim_4el'

    data_d = pd.read_csv("../build/examples/output/output_"+sim_name+"Phase.dat", sep = " ")
    data_s1 = pd.read_csv("../build/examples/output/output_"+sim_name+"F1.dat", sep = " ")
    data_s2 = pd.read_csv("../build/examples/output/output_"+sim_name+"F2.dat", sep = " ")
    data_u1 = pd.read_csv("../build/examples/output/output_"+sim_name+"u1.dat", sep = " ")
    data_u2 = pd.read_csv("../build/examples/output/output_"+sim_name+"u2.dat", sep = " ")
    data_h = pd.read_csv("../build/examples/output/output_"+sim_name+"H.dat", sep = " ")
    
    
    x = data_d.values[0,:]
    y = data_d.values[1,:]
    
    #print(x)
    #print(y)
    #print(data_d.values[2,:])
    
    d_start_idx = 2
    d_finish_idx = len(data_d.values[:1])
    d_mid = int((d_start_idx+d_finish_idx)/4)
    
    frames = [d_start_idx,d_mid, d_finish_idx]
    
    # Numerical solution

    fig, ax = plt.subplots(nrows = len(frames), ncols = 2, figsize = (9,16.8,), constrained_layout = True)
    i=0
    

    for f in frames: 
    	ax[i,0].scatter(x,y,s=200, c=data_d.values[f,:], cmap = "coolwarm", vmin = 0, vmax = 1)
    	ax[i,1].scatter(x,y,s=200, c=data_u2.values[f,:], cmap = "coolwarm", vmin = 0, vmax = 0.2)
    	i=i+1

    
    plt.show()
