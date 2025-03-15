
class Vertex:
    def __init__(self):
        self.__outbound_edges = []
        self.__inbound_edges = []

    def check_if_exist_an_edge_bidirectional(self, end):
        if end in self.__outbound_edges:
            return 1
        return 0

    def add_an_outbound_edge_without_raise(self, end):
        if end in self.__outbound_edges:
            return 0
        self.__outbound_edges.append(end)
        return 1

    def add_an_outbound_edge(self, end):
        if end in self.__outbound_edges:
            raise ValueError("This edge already exist!")
        self.__outbound_edges.append(end)

    def remove_an_outbound_edge_without_raise(self, end):
        if end in self.__outbound_edges:
            self.__outbound_edges.remove(end)
            return 1
        return 0

    def remove_an_outbound_edge(self, end):
        if end in self.__outbound_edges:
            self.__outbound_edges.remove(end)
        else:
            raise ValueError("This edge doesn't exist!")

    def add_an_inbound_edge_without_raise(self, end):
        if end in self.__inbound_edges:
            return 0
        self.__inbound_edges.append(end)
        return 1

    def add_an_inbound_edge(self, end):
        if end in self.__inbound_edges:
            raise ValueError("This edge already exist!")
        self.__inbound_edges.append(end)

    def remove_an_inbound_edge_without_raise(self, end):
        if end in self.__inbound_edges:
            self.__inbound_edges.remove(end)
            return 1
        return 0

    def remove_an_inbound_edge(self, end):
        if end in self.__inbound_edges:
            self.__inbound_edges.remove(end)
        else:
            raise ValueError("This edge doesn't exist!")

    def get_the_number_of_outbound_edges(self):
        return len(self.__outbound_edges)

    def get_the_number_of_inbound_edges(self):
        return len(self.__inbound_edges)

    def get_the_outbound_edges(self):
        return self.__outbound_edges

    def get_the_inbound_edges(self):
        return self.__inbound_edges

    def check_if_exist_edge_between_to_vertices(self, vertex_in):
        if vertex_in in self.__outbound_edges:
            return True
        else:
            return False

    def remove_a_vertex_from_an_index(self, vertex):
        if vertex in self.__inbound_edges:
            self.__inbound_edges.remove(vertex)
        if vertex in self.__outbound_edges:
            self.__outbound_edges.remove(vertex)