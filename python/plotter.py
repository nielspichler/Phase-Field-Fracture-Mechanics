import numpy as np
import pandas as pd
from matplotlib import pyplot as plt


if __name__ == '__main__':

    data_d = pd.read_csv("../build/examples/output/output_sim_1Phase.dat", sep = " ")
    data_s1 = pd.read_csv("../build/examples/output/output_sim_1F1.dat", sep = " ")
    data_s2 = pd.read_csv("../build/examples/output/output_sim_1F2.dat", sep = " ")
    data_u1 = pd.read_csv("../build/examples/output/output_sim_1u1.dat", sep = " ")
    data_u2 = pd.read_csv("../build/examples/output/output_sim_1u2.dat", sep = " ")
    data_h = pd.read_csv("../build/examples/output/output_sim_1H.dat", sep = " ")

    fig, ax = plt.subplots(nrows=1, ncols=3, figsize = (16.8,4.8), constrained_layout = True)
    
    # Analytical solution (see paper)
    c22 = 210. * (1-0.3)/((1+0.3)*(1-2*0.3))
    gc = 0.005
    lc = 0.1
    eps = np.linspace(0,0.1, data_d.shape[0]-2) # computes the applied strain for each timestep
    
    d =  eps**2*c22/(gc/lc + eps**2*c22)
    
    sig_y = c22 * eps * (1-d)**2    
    
    ax[0].plot(eps, d, '-k', label = "analytical solution")
    ax[1].plot(eps, sig_y, '-k', label = "analytical solution")

    # Numerical solution

    for i in ["Node_0", "Node_1", "Node_2", "Node_3"]: # ["Node_0", "Node_1", "Node_2", "Node_3",]
        ax[0].plot(data_u2[i][2:], data_d[i][2:], '.', markerfacecolor = None, alpha = 0.2, label = i)
        ax[1].plot(data_u2[i][2:], data_s1[i][2:], '--', markerfacecolor = None, alpha = 0.2, label = i+"_dir1")
        ax[1].plot(data_u2[i][2:], data_s2[i][2:], '.', markerfacecolor = None, alpha = 0.2, label = i+"_dir2")

    ax[2].plot(data_u2["Node_2"][2:], data_h["element_0"][:], markerfacecolor = None, alpha = 0.2, label = "history_variable")

    ax[0].set_xlabel("strain")
    ax[0].set_ylabel("damage variable")
    ax[0].legend()
    ax[0].grid()
    
    ax[1].set_xlabel("strain")
    ax[1].set_ylabel("Rf")
    ax[1].legend()
    ax[1].grid()
    
    
    plt.show()
