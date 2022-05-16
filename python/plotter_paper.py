import numpy as np
import pandas as pd
from matplotlib import pyplot as plt


if __name__ == '__main__':

    # own results

    sim_name = "sim_paper"

    data_d = pd.read_csv("../build/examples/output/output_"+sim_name+"Phase.dat", sep = " ")
    data_s1 = pd.read_csv("../build/examples/output/output_"+sim_name+"F1.dat", sep = " ")
    data_s2 = pd.read_csv("../build/examples/output/output_"+sim_name+"F2.dat", sep = " ")
    data_u1 = pd.read_csv("../build/examples/output/output_"+sim_name+"u1.dat", sep = " ")
    data_u2 = pd.read_csv("../build/examples/output/output_"+sim_name+"u2.dat", sep = " ")
    data_h = pd.read_csv("../build/examples/output/output_"+sim_name+"H.dat", sep = " ")
    
    # Abaqus implementation
    
    data_ABQ = pd.read_csv("abaqus_results.csv", sep = ";")    

    fig, ax = plt.subplots(nrows=1, ncols=3, figsize = (16.8,4.8), constrained_layout = True)
    

    # ABAQUS plot
    
    ax[0].plot(data_ABQ['_U:U2 PI: ELEM-1N: 3'][:], data_ABQ['_SDV15 PI: ELEM-1E: 3 N: 3'][:], marker = 'x', markersize = 5, alpha = 0.5, label = "ABAQUS node 3",)

    ax[1].plot(data_ABQ['_U:U2 PI: ELEM-1N: 3'][:], data_ABQ['_RF:RF2 PI: ELEM-1 N: 3'][:], marker = 'x', markersize = 5,alpha = 0.5, label = "ABAQUS node 3 Rf2")

    ax[2].plot(data_ABQ['_U:U2 PI: ELEM-1N: 3'][:], data_ABQ['_SDV16 PI: ELEM-1E: 3 N: 3'][:], marker = 'x', markersize = 5,alpha = 0.5, label = "ABAQUS node 3")

    # Numerical solution

    for i in ["Node_0", "Node_1", "Node_2", "Node_3",]: # ["Node_0", "Node_1", "Node_2", "Node_3",]
        ax[0].plot(data_u2["Node_2"][2:], data_d[i][2:], '.', markerfacecolor = None, alpha = 0.5, label = i)
        #ax[1].plot(data_u2["Node_2"][2:], data_s1[i][2:], '.', markerfacecolor = None, alpha = 0.5, label = i+"_dir1")
        ax[1].plot(data_u2["Node_2"][2:], data_s2[i][2:], '.', markerfacecolor = None, alpha = 0.5, label = i+"_dir2")

    ax[2].plot(data_u2["Node_2"][2:], data_h["element_0"][:], '.', markerfacecolor = None, alpha = 0.5, label = "history_variable")

    # Analytical solution (see paper)
    c22 = 210. * (1-0.3)/((1+0.3)*(1-2*0.3))
    gc = 0.005
    lc = 0.1
    eps = np.linspace(0,0.1, data_d.shape[0]-2) # computes the applied strain for each timestep
    
    d =  eps**2*c22/(gc/lc + eps**2*c22)
    
    sig_y = c22 * eps * (1-d)**2    
    
    ax[0].plot(eps, d, '-k', label = "analytical solution")
    ax[1].plot(eps, sig_y/2, '-k', label = "analytical solution (half of elemental stress)")


    ax[0].set_xlabel("strain")
    ax[0].set_ylabel("damage variable")
    ax[0].legend()
    ax[0].grid()
    
    ax[1].set_xlabel("strain")
    ax[1].set_ylabel("Reaction force")
    ax[1].legend()
    ax[1].grid()
    
    ax[2].set_xlabel("strain")
    ax[2].set_ylabel("History variable")
    ax[2].legend()
    ax[2].grid()
    
    
    plt.show()
