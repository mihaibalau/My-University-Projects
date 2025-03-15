import random

from Repository import Graph


class GraphsServices:

    def __init__(self, main_repository, backup_repository):
        self.__main_repository = main_repository
        self.__backup_repository = backup_repository

    def create_a_random_graph(self, number_of_vertices, number_of_edges):
        self.__main_repository = Graph(number_of_vertices, number_of_edges)
        count = 0
        while count < number_of_edges:
            vertex_out = random.randint(0, number_of_vertices-1)
            vertex_in = random.randint(0, number_of_vertices-1)
            cost = random.randint(1, 100)
            self.__main_repository.create_if_not_exist_vertices_for_an_edge(int(vertex_out), int(vertex_in))
            if not self.__main_repository.check_if_exist_edge_between_to_vertices(vertex_out, vertex_in):
                self.__main_repository.add_a_new_edge_between_to_vertices(vertex_out, vertex_in, cost)
                count = count + 1

    def add_a_new_vertex(self, vertex_number):
        vertex_number = int(vertex_number)
        if not self.__main_repository.add_a_new_vertex_in_repository(vertex_number):
            raise ValueError("This vertex already exist in the current repository!")

    def remove_a_vertex(self, vertex_number):
        vertex_number = int(vertex_number)
        if not self.__main_repository.remove_a_vertex_from_repository(vertex_number):
            raise ValueError("This vertex number doesn't exist in the current repository!")

    def add_a_new_edge(self, vertex_out, vertex_in, cost):
        vertex_out = int(vertex_out)
        vertex_in = int(vertex_in)
        cost = int(cost)
        self.__main_repository.add_a_new_edge_between_to_vertices(vertex_out, vertex_in, cost)

    def remove_an_edge(self, vertex_out, vertex_in):
        vertex_out = int(vertex_out)
        vertex_in = int(vertex_in)
        self.__main_repository.remove_a_new_edge_between_to_vertices(vertex_out, vertex_in)

    def load_the_graph_from_text_file(self, file_name):
        self.__main_repository.load_from_text_file(file_name)

    def print_the_graph_in_text_file(self, file_name):
        self.__main_repository.save_to_file(file_name)

    def get_the_number_of_vertices(self):
        return self.__main_repository.get_the_number_of_vertices()

    def get_the_set_of_vertices(self):
        return self.__main_repository.get_the_set_of_vertices()

    def check_if_exist_edge_between_to_vertices(self, vertex_out, vertex_in):
        vertex_out = int(vertex_out)
        vertex_in = int(vertex_in)
        return self.__main_repository.check_if_exist_edge_between_to_vertices(vertex_out, vertex_in)

    def get_the_in_and_out_degree_for_a_vertex(self, vertex):
        vertex = int(vertex)
        return self.__main_repository.get_the_in_and_out_degree_for_a_vertex(vertex)

    def iterate_the_outbound_edges_of_a_vertex(self, vertex):
        vertex = int(vertex)
        return self.__main_repository.iterate_the_outbound_edges_of_a_vertex(vertex)

    def iterate_the_inbound_edges_of_a_vertex(self, vertex):
        vertex = int(vertex)
        return self.__main_repository.iterate_the_inbound_edges_of_a_vertex(vertex)

    def modify_the_cost_of_an_edge(self, vertex_out, vertex_in, new_cost):
        vertex_out = int(vertex_out)
        vertex_in = int(vertex_in)
        new_cost = int(new_cost)
        self.__main_repository.modify_the_cost_of_an_edge(vertex_out, vertex_in, new_cost)

    def make_a_backup_of_current_graph(self):
        self.__backup_repository = self.__main_repository

    def restore_the_backup_to_current_graph(self):
        if self.__main_repository.get_the_number_of_vertices() == 0:
            raise ValueError("No backup available!")
        else:
            self.__main_repository = self.__backup_repository

    def DFS(self, current_vertex, visited, returned_subgraph):
        available_outs = self.__main_repository.iterate_the_outbound_edges_of_a_vertex(current_vertex)
        returned_subgraph.append(current_vertex)
        for vertex in available_outs:
            if vertex not in visited:
                visited.append(vertex)
                self.DFS(vertex, visited, returned_subgraph)

    def get_the_connected_components_dfs(self):
        returned_list = []
        visited = []
        available_vertices = self.get_the_set_of_vertices()
        for current_vertex in available_vertices:
            if current_vertex not in visited:
                visited.append(current_vertex)
                subgraph = []
                self.DFS(current_vertex, visited, subgraph)
                returned_list.append(subgraph)
        return returned_list

    def get_the_cost_between_two_vertices(self, source, destinaiton):
        import queue
        infinity = 999999
        q = queue.Queue()
        d = {}
        last_k_value = {}

        vertices = self.__main_repository.get_the_set_of_vertices()
        for current_vertex in vertices:
            pair_value = (current_vertex, 0)
            last_k_value[current_vertex] = 0
            d[pair_value] = infinity

        pair_value = (source, 0)
        d[pair_value] = 0

        q.put(source)
        while not q.empty():
            current_vertex = q.get()
            neighborhoods = self.__main_repository.iterate_the_outbound_edges_of_a_vertex(current_vertex)
            for current_nh in neighborhoods:
                cost = self.__main_repository.get_the_vertices_cost(current_vertex, current_nh)
                pair_value = (current_nh, last_k_value[current_nh])
                pair_value2 = (current_vertex, last_k_value[current_vertex])
                if d[pair_value] > d[pair_value2] + cost:
                    last_k_value[current_nh] += 1
                    pair_value3 = (current_nh, last_k_value[current_nh])
                    d[pair_value3] = d[pair_value2] + cost
                    if current_nh == source:
                        raise ValueError("Negative cost cycle accessible found from starting vertex!")
                    q.put(current_nh)

        pair_value = (destinaiton, last_k_value[destinaiton])
        if d[pair_value] == infinity:
            raise ValueError("This destination is unreachable from imputed starting point!")
        else:
            return d[pair_value]
