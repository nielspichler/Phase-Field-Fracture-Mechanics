import numpy as np
from mesh_parts import *


if __name__ == '__main__':

    ####################################################################################################################################
    #                Mofdify the parameters from here....

    lx = 1 # length of the domain
    ly = 1 # height of the domain

    x_disc = 21 # nb nodes in x direction
    y_disc = 21 # nb nodes in y direction

    crack = [0,0.5,0.5,0.5] # x start, y start, x finish, y finish (needs to coincide with nodes), origin is in the lower left corner

    lc = 0.1 # length scale parameter
    steps = 1000 # number of steps
    
    E = 210.0 # E modulus in Kn/mm²
    G = 2.7e-3 # Critical ERR in kN/mm
    nu = 0.3 # poisson ratio
    
    damage = 1 # option to activate or deactivate the damage

    file_name = "input_20x20_crack_damage.inp" # name of the input file to be writter Take care this will append to the file

    # Boundary conditions definitions, (0)lower edge, (1)right edge, (2)top edge, (3)left edge
    
    bc_1 = BC(0, 0, 0) # edge, direction, amplitude (final)
    bc_2 = BC(0, 1, 0)
    bc_3 = BC(1, 0, 0)
    bc_4 = BC(2, 1, 0.05)
    bc_5 = BC(2, 0, 0)
    bc_6 = BC(3, 0, 0)

    # easily put or remove BCs
    BC_list = [bc_1, bc_2, bc_4, bc_5,]# bc_3,

    # end of the parameters definition 
    
    #                ... to here.
    ####################################################################################################################################


    nb_nodes = x_disc*y_disc
    nb_el = (x_disc-1) * (y_disc)

    x = np.linspace(0, lx, x_disc)
    y = np.linspace(0, ly, y_disc)

    el_size_x = x[1]
    el_size_y = y[1]

    xv, yv = np.meshgrid(x,y)

    node_list = []
    node_number = 0
    for i in range(y_disc):

        for j in range(x_disc):

            n = Node(xv[i,j], yv[i,j],node_number)
            node_list.append(n)
            node_number+=1

    element_list = []

    for i in range(y_disc-1):

        for j in range(x_disc-1):

            e = Element(i*x_disc+j,i*x_disc+j+1, (i+1)*x_disc+j+1, (i+1)*x_disc+j)
            e.set_E(E)
            e.set_g(G)
            e.set_nu(nu)
            element_list.append(e)

    nodes_to_duplicate = []

    for n in node_list:
        if (crack[0]-el_size_x/2<=n.x<crack[2] and crack[1]-el_size_y/2<=n.y<=crack[3]+el_size_y/2):
            nodes_to_duplicate.append(n)

    for n_dupl in nodes_to_duplicate:
        n_dupl.set_twin(node_number)
        n = Node(n_dupl.x, n_dupl.y, node_number)
        node_list.append(n)
        node_number += 1

    for e in element_list:
        for n in nodes_to_duplicate:
            if e.n1 == n.number:
                e.n1 = n.twin_nb
            if e.n2 == n.number:
                e.n2 = n.twin_nb


    f = open(file_name, 'a')

    f.write("$dimensions 2\n$lc " + str(lc) + "\n$steps " + str(steps) + "\n$damage " + str(damage) + "\n")

    f.write("$nodes " + str(node_number) + "\n")
    for n in node_list:
        n.write_node(f)

    f.write("$elements " + str(len(element_list)) + "\n$elementtype 1 4\n")
    i=1
    for e in element_list:
        e.write_element(f, i)
        i+=1


    for BC in BC_list:
        BC.get_nodes(node_list, lx, ly)
        BC.write_bcd(f)
