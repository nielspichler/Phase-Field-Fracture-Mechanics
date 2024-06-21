import numpy as np
import pandas as pd
import sys
from matplotlib import pyplot as plt
from matplotlib import cm

if __name__ == '__main__':

    if len(sys.argv) < 3:
        sys.exit('Missing argument! usage: ./lD_curve-square_domain.py dir sim_name ')
    
    odir = str(sys.argv[1])
    sim_name = str(sys.argv[2])

    # own results

    cmap = "jet"
    levels = 30

    data_s1 = pd.read_csv("../examples/" + odir + "/output_" + sim_name + "F1.dat", sep=" ")
    data_s2 = pd.read_csv("../examples/" + odir + "/output_" + sim_name + "F2.dat", sep=" ")

    data_u1 = pd.read_csv("../examples/"+ odir +"/output_"+sim_name+"u1.dat", sep = " ")
    data_u2 = pd.read_csv("../examples/"+ odir +"/output_"+sim_name+"u2.dat", sep = " ")

    x = data_s1.values[0, :]
    y = data_s1.values[1, :]

    # find domain boundaries asusming it's a rectangular domain

    x_min = np.min(x)
    x_max = np.max(x)

    y_min = np.min(y)
    y_max = np.max(y)

    bottom_edge_nodal_index = np.where(y == y_min)[0]
    top_edge_nodal_index = np.where(y == y_max)[0]
    left_edge_nodal_index = np.where(x == x_min)[0]
    right_edge_nodal_index = np.where(x == x_max)[0]

    Rx_bottom = np.sum(data_s1.values[2:, bottom_edge_nodal_index], axis=1).flatten()
    Rx_top= np.sum(data_s1.values[2:, top_edge_nodal_index], axis=1).flatten()
    Ry_top = np.sum(data_s2.values[2:, top_edge_nodal_index], axis=1).flatten()
    Ry_bottom = np.sum(data_s2.values[2:, bottom_edge_nodal_index], axis=1).flatten()

    Rx_left = np.sum(data_s1.values[2:, left_edge_nodal_index], axis=1).flatten()
    Rx_right = np.sum(data_s1.values[2:, right_edge_nodal_index], axis=1).flatten()
    Ry_left = np.sum(data_s2.values[2:, left_edge_nodal_index], axis=1).flatten()
    Ry_right = np.sum(data_s2.values[2:, right_edge_nodal_index], axis=1).flatten()

    # get the displacement of the edges assuming the domain is a square and the displacement is the same for all nodes on the edge

    u1_bottom = data_u1.values[2:, bottom_edge_nodal_index[0]]
    u1_top = data_u1.values[2:, top_edge_nodal_index[0]]
    u2_bottom = data_u2.values[2:, bottom_edge_nodal_index[0]]
    u2_top = data_u2.values[2:, top_edge_nodal_index[0]]

    u1_left = data_u1.values[2:, left_edge_nodal_index[0]]
    u1_right = data_u1.values[2:, right_edge_nodal_index[0]]
    u2_left = data_u2.values[2:, left_edge_nodal_index[0]]
    u2_right = data_u2.values[2:, right_edge_nodal_index[0]]


    # plot the load-displacement curves

    fig, ax = plt.subplots(nrows=1, ncols=2, figsize=(16.8, 4.8), constrained_layout=True)

    ax[0].plot(u1_top, Rx_top, label = 'Rx_top')
    ax[0].plot(u1_bottom, Rx_bottom, label = 'Rx_bottom')
    ax[0].plot(u1_left, Rx_left, label = 'Rx_left')
    ax[0].plot(u1_right, Rx_right, label = 'Rx_right')

    ax[1].plot(u2_top, Ry_top, label = 'Ry_top')
    ax[1].plot(u2_bottom, Ry_bottom, label = 'Ry_bottom')
    ax[1].plot(u2_left, Ry_left, label = 'Ry_left')
    ax[1].plot(u2_right, Ry_right, label = 'Ry_right')

    ax[0].set_title('Rx')
    ax[0].set_xlabel("u1")
    ax[0].set_ylabel("reaction force")
    ax[0].legend()
    ax[0].grid()

    ax[1].set_title('Ry')
    ax[1].set_xlabel("u2")
    ax[1].set_ylabel("reaction force")
    ax[1].legend()
    ax[1].grid()

    plt.show()



