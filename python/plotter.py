import numpy as np
import pandas as pd
from matplotlib import pyplot as plt


if __name__ == '__main__':

    data = pd.read_csv("../build/examples/output/output_sim1Phase.dat", sep = " ")

    fig, ax = plt.subplots()
    
    # Analytical solution (see paper)
    c22 = 210. * (1-0.3)/((1+0.3)*(1-2*0.3))
    gc = 0.005
    lc = 0.1
    eps = np.linspace(0,0.1, data.shape[0]-2) # computes the applied strain for each timestep
    
    d =  eps**2*c22/(gc/lc + eps**2*c22)
    
    ax.plot(eps, d, '-k', label = "analytical solution")

    for i in ["Node_0", "Node_1", "Node_2", "Node_3",]:
        ax.plot(eps, data[i][2:], '.', markerfacecolor = None, alpha = 0.2, label = i)

    ax.set_xlabel("strain")
    ax.set_ylabel("damage variable")
    ax.legend()
    ax.grid()

    plt.show()
