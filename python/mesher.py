import numpy as np
from mesh_parts import *


if __name__ == '__main__':

    lx = 20
    ly = 20

    x_disc = 41 # nb nodes in x dir
    y_disc = 41 # nb nodes in y dir

    crack = [0,10,2,10] # x start, y start, x finish, y finish (needs to coincide with nodes)

    lc = 0.1
    steps = 1000

    file_name = "input_file.inp"

    bc_1 = BC(0, 0, 0) # edge, direction, amplitude
    bc_2 = BC(0, 1, 0)
    bc_3 = BC(1, 0, 0)
    bc_4 = BC(2, 1, 1)
    bc_5 = BC(2, 0, 0)
    bc_6 = BC(3, 0, 0)

    BC_list = [bc_1, bc_2, bc_3, bc_4, bc_5,]

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

            e = Element(i*x_disc+j,i*x_disc+j+1, (i+1)*x_disc+j, (i+1)*x_disc+j+1)
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

    f.write("$dimensions 2\n$lc " + str(lc) + "\n$steps " + str(steps) + "\n")

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
