import numpy as np
import pandas as pd
from matplotlib import pyplot as plt


if __name__ == '__main__':

    # own results

    sim_name = 'sim_4el_small_steps'

    data_d = pd.read_csv("../build/examples/output/output_"+sim_name+"Phase.dat", sep = " ")
    data_s1 = pd.read_csv("../build/examples/output/output_"+sim_name+"F1.dat", sep = " ")
    data_s2 = pd.read_csv("../build/examples/output/output_"+sim_name+"F2.dat", sep = " ")
    data_u1 = pd.read_csv("../build/examples/output/output_"+sim_name+"u1.dat", sep = " ")
    data_u2 = pd.read_csv("../build/examples/output/output_"+sim_name+"u2.dat", sep = " ")
    data_h = pd.read_csv("../build/examples/output/output_"+sim_name+"H.dat", sep = " ")
    


    fig, ax = plt.subplots(nrows=1, ncols=3, figsize = (16.8,4.8), constrained_layout = True)
    

    # Numerical solution

    for i in data_d.keys():
        disp_norm = np.sqrt(data_u2[i][:]**2 + data_u1[i][2:]**2)
        ax[0].plot(disp_norm, data_d[i][:], '.', markerfacecolor = None, alpha = 0.2, label = i)
        ax[1].plot(disp_norm, data_s1[i][:], '--', markerfacecolor = None, alpha = 0.2, label = i+"_dir1")
        ax[1].plot(disp_norm, data_s2[i][:], '.', markerfacecolor = None, alpha = 0.2, label = i+"_dir2")
       
    for i in data_h.keys():
    	ax[2].plot(data_h[i][:], '.', markerfacecolor = None, alpha = 0.2, label = "h "+i)



    ax[0].set_xlabel("disp (norm)")
    ax[0].set_ylabel("damage variable")
    ax[0].legend()
    ax[0].grid()
    
    ax[1].set_xlabel("disp (norm)")
    ax[1].set_ylabel("Rf")
    ax[1].legend()
    ax[1].grid()
    
    ax[2].set_xlabel("iterations")
    ax[2].set_ylabel("H")
    ax[2].legend()
    ax[2].grid()
    
    
    plt.show()
