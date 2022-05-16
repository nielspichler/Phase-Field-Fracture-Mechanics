import numpy as np


class Node:
    def __init__(self, x,y, n):
        self.x = x
        self.y = y
        self.number = n

    def set_twin(self, n):
        self.twin_nb = n

    def write_node(self, f):

        line = '$node ' + str(self.number+1) + " " + str(self.x) + " " + str(self.y) + "\n"

        f.write(line)

class Element:
    def __init__(self, n1,n2, n3, n4):
        self.n1 = n1
        self.n2 = n2
        self.n3 = n3
        self.n4 = n4

        self.E = 210
        self.nu = 0.3
        self.g = 0.005

    def set_E(self, E):
        self.E = E
    def set_nu(self, nu):
        self.nu = nu
    def set_g(self, g):
        self.g = g

    def write_element(self, f, number):

        line = '$element ' + str(number) + " " + str(self.n1+1) \
               + " " + str(self.n2+1)\
               + " " + str(self.n3+1)\
               + " " + str(self.n4+1) \
               + " 1 " + str(self.E)\
               + " " + str(self.nu)\
               + " " + str(self.g)+ "\n"

        f.write(line)


class BC:
    def __init__(self, edge, direction, amplitude):

        self.edge = edge
        self.direction = direction
        self.amplitude = amplitude

    def get_nodes(self, node_list, lx, ly):

        self.bcd_list = []

        if self.edge == 0:      # edge 0, bottom edge
            for n in node_list:
                if n.y == 0:
                    self.bcd_list.append(n.number)

        if self.edge == 1:      # edge 1, right edge
            for n in node_list:
                if n.x == lx:
                    self.bcd_list.append(n.number)

        if self.edge == 2:      # edge 2, top edge
            for n in node_list:
                if n.y == ly:
                    self.bcd_list.append(n.number)

        if self.edge == 3:      # edge 3, right edge
            for n in node_list:
                if n.x == 0:
                    self.bcd_list.append(n.number)

    def write_bcd(self, f):

        for node in self.bcd_list:

            line = "$bcd 0 " + str(node+1)\
                   + " " + str(self.direction+1)\
                   + " " + str(self.amplitude) + "\n"

            f.write(line)