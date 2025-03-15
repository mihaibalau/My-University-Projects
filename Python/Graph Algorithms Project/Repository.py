from Domain import Vertex


class Graph:
    def __init__(self, number_of_vertices, number_of_edges):
        self.__list_of_vertices = {}
        self.__number_of_edges = number_of_edges
        self.__number_of_vertices = number_of_vertices
        self.__vertices_cost = {}

    def load_from_text_file(self, file_name):
        first_line = True
        file_input = open(file_name, "rt")
        self.__list_of_vertices = {}
        self.__vertices_cost = {}
        non_isolated_vertices = 0
        number_of_edges_bidirectional = 0
        for current_read_line in file_input:
            if first_line:
                current_read_line = current_read_line.split(" ")
                self.__number_of_vertices = int(current_read_line[0])
                current_read_line[1] = current_read_line[1].replace("\n", "")
                self.__number_of_edges = int(current_read_line[1])
                first_line = False
            else:
                current_read_line = current_read_line.split(" ")
                vertex_out = int(current_read_line[0])
                vertex_in = int(current_read_line[1])
                make_pair = (vertex_out, vertex_in)
                make_pair2 = (vertex_in, vertex_out)
                if vertex_in != -1:
                    current_read_line[2] = current_read_line[2].replace("\n", "")
                    cost = int(current_read_line[2])
                    self.__vertices_cost[make_pair] = cost
                    self.__vertices_cost[make_pair2] = cost
                    if vertex_in not in self.__list_of_vertices:
                        self.__list_of_vertices[vertex_in] = Vertex()
                        non_isolated_vertices += 1
                    if vertex_out not in self.__list_of_vertices:
                        self.__list_of_vertices[vertex_out] = Vertex()
                        non_isolated_vertices += 1
                    number_of_edges_bidirectional += self.__list_of_vertices[vertex_out].add_an_outbound_edge_without_raise(vertex_in)
                    self.__list_of_vertices[vertex_out].add_an_inbound_edge_without_raise(vertex_in)
                    self.__list_of_vertices[vertex_in].add_an_outbound_edge_without_raise(vertex_out)
                    number_of_edges_bidirectional += self.__list_of_vertices[vertex_in].add_an_inbound_edge_without_raise(vertex_out)
                else:
                    if vertex_out not in self.__list_of_vertices:
                        self.__list_of_vertices[vertex_out] = Vertex()
                        non_isolated_vertices += 1
        starting_vertex = 0
        while non_isolated_vertices < self.__number_of_vertices:
            if starting_vertex not in self.__list_of_vertices:
                self.__list_of_vertices[starting_vertex] = Vertex()
                non_isolated_vertices += 1
            starting_vertex += 1

        self.__number_of_edges = number_of_edges_bidirectional
        file_input.close()

    def save_to_file(self, file_name):
        file_output = open(file_name, "wt")
        file_output.write(str(len(self.__list_of_vertices)) + " " + str(self.__number_of_edges) + "\n")
        list_of_vertices = list(self.__list_of_vertices.keys())
        list_of_vertices = sorted(list_of_vertices)
        for index in list_of_vertices:
            printed_list = self.__list_of_vertices[index].get_the_outbound_edges()
            if len(printed_list) == 0:
                file_output.write(str(index) + " -1\n")
            else:
                for each_element in printed_list:
                    make_pair = (index, each_element)
                    file_output.write(str(index) + " " + str(each_element) + " " + str(self.__vertices_cost[make_pair]) + "\n")

    def print_the_memory_tool(self):
        print(str(len(self.__list_of_vertices)) + " " + str(self.__number_of_edges))
        list_of_vertices = list(self.__list_of_vertices.keys())
        list_of_vertices = sorted(list_of_vertices)
        for index in list_of_vertices:
            printed_list = self.__list_of_vertices[index].get_the_outbound_edges()
            for each_element in printed_list:
                make_pair = (index, each_element)
                print(str(index) + " " + str(each_element) + " " + str(self.__vertices_cost[make_pair]))
        for index in self.__vertices_cost:
            print(str(index) + " " + str(self.__vertices_cost[index]))

    def get_the_number_of_vertices(self):
        return self.__number_of_vertices

    def get_the_set_of_vertices(self):
        return list(self.__list_of_vertices.keys())

    def add_a_new_vertex_in_repository(self, new_vertex_number):
        if new_vertex_number in self.__list_of_vertices:
            return False
        self.__list_of_vertices[new_vertex_number] = Vertex()
        self.__number_of_vertices += 1
        return True

    def remove_a_vertex_from_repository(self, removed_vertex_number):
        if removed_vertex_number in self.__list_of_vertices:
            del self.__list_of_vertices[removed_vertex_number]
            for index in self.__list_of_vertices:
                self.__list_of_vertices[index].remove_a_vertex_from_an_index(removed_vertex_number)
            self.__number_of_vertices -= 1
            list_of_popped_indexes = []
            for index in self.__vertices_cost:
                if removed_vertex_number in index:
                    list_of_popped_indexes.append(index)
            for index in list_of_popped_indexes:
                self.__vertices_cost.pop(index)
            self.__number_of_edges -= len(list_of_popped_indexes)
            return True
        else:
            return False

    def add_a_new_edge_between_to_vertices(self, vertex_out, vertex_in, cost):
        if vertex_out not in self.__list_of_vertices:
            raise ValueError("The imputed vertex out doesn't exist in current repository!")
        if vertex_in not in self.__list_of_vertices:
            raise ValueError("The imputed vertex in doesn't exist in current repository!")
        if self.__list_of_vertices[vertex_out].check_if_exist_an_edge_bidirectional:
            make_pair = (vertex_out, vertex_in)
            make_pair2 = (vertex_in, vertex_out)
            self.__vertices_cost[make_pair] = cost
            self.__vertices_cost[make_pair2] = cost
            self.__number_of_edges += self.__list_of_vertices[vertex_out].add_an_outbound_edge_without_raise(vertex_in)
            self.__list_of_vertices[vertex_out].add_an_inbound_edge_without_raise(vertex_in)
            self.__list_of_vertices[vertex_in].add_an_outbound_edge_without_raise(vertex_out)
            self.__number_of_edges += self.__list_of_vertices[vertex_in].add_an_inbound_edge_without_raise(vertex_out)
        else:
            raise ValueError("This bidirectional edge already exist!")

    def remove_a_new_edge_between_to_vertices(self, vertex_out, vertex_in):
        if vertex_out not in self.__list_of_vertices:
            raise ValueError("The imputed vertex out doesn't exist in current repository!")
        if vertex_in not in self.__list_of_vertices:
            raise ValueError("The imputed vertex in doesn't exist in current repository!")
        if not self.__list_of_vertices[vertex_out].check_if_exist_an_edge_bidirectional:
            self.__list_of_vertices[vertex_out].remove_an_outbound_edge_without_raise(vertex_in)
            self.__list_of_vertices[vertex_out].remove_an_inbound_edge_without_raise(vertex_in)
            self.__list_of_vertices[vertex_in].remove_an_inbound_edge_without_raise(vertex_out)
            self.__list_of_vertices[vertex_in].remove_an_outbound_edge_without_raise(vertex_out)
            self.__number_of_edges -= 2
            make_pair = (vertex_out, vertex_in)
            make_pair2 = (vertex_in, vertex_out)
            self.__vertices_cost.pop(make_pair)
            self.__vertices_cost.pop(make_pair2)
        else:
            raise ValueError("This bidirectional edge doesn't exist!")

    def create_if_not_exist_vertices_for_an_edge(self, vertex_out, vertex_in):
        if vertex_out not in self.__list_of_vertices:
            self.__list_of_vertices[vertex_out] = Vertex()
            self.__number_of_vertices += 1
        if vertex_in not in self.__list_of_vertices:
            self.__list_of_vertices[vertex_in] = Vertex()
            self.__number_of_vertices += 1

    def check_if_exist_edge_between_to_vertices(self, vertex_out, vertex_in):
        if vertex_out not in self.__list_of_vertices:
            raise ValueError("The imputed vertex out doesn't exist in current repository!")
        if vertex_in not in self.__list_of_vertices:
            raise ValueError("The imputed vertex in doesn't exist in current repository!")
        return self.__list_of_vertices[vertex_out].check_if_exist_edge_between_to_vertices(vertex_in)

    def get_the_in_and_out_degree_for_a_vertex(self, vertex):
        if vertex not in self.__list_of_vertices:
            raise ValueError("The imputed vertex doesn't exist in current repository!")
        return self.__list_of_vertices[vertex].get_the_number_of_inbound_edges(), self.__list_of_vertices[vertex].get_the_number_of_outbound_edges()

    def iterate_the_outbound_edges_of_a_vertex(self, vertex):
        if vertex not in self.__list_of_vertices:
            raise ValueError("The imputed vertex doesn't exist in current repository!")
        return self.__list_of_vertices[vertex].get_the_outbound_edges()

    def iterate_the_inbound_edges_of_a_vertex(self, vertex):
        if vertex not in self.__list_of_vertices:
            raise ValueError("The imputed vertex doesn't exist in current repository!")
        return self.__list_of_vertices[vertex].get_the_inbound_edges()

    def modify_the_cost_of_an_edge(self, vertex_out, vertex_in, new_cost):
        if vertex_out not in self.__list_of_vertices:
            raise ValueError("The imputed vertex out doesn't exist in current repository!")
        if vertex_in not in self.__list_of_vertices:
            raise ValueError("The imputed vertex in doesn't exist in current repository!")
        make_pair = (vertex_out, vertex_in)
        make_pair2 = (vertex_in, vertex_out)
        if make_pair not in self.__vertices_cost:
            raise ValueError("Doesn't exist an edge between imputed vertices!")
        self.__vertices_cost[make_pair] = new_cost
        self.__vertices_cost[make_pair2] = new_cost

    def get_the_vertices_cost(self, vertex_out, vertex_in):
        pair = (vertex_out, vertex_in)
        return self.__vertices_cost[pair]