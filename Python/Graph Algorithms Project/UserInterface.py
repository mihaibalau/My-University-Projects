
class GraphsUI:

    def __init__(self, available_services):
        self.__available_services = available_services

    def create_a_random_graph(self):
        number_of_vertices = input("Enter the number of vertices: ")
        number_of_edges = input("Enter the number of edges: ")
        self.__available_services.create_a_random_graph(int(number_of_vertices), int(number_of_edges))

    def modify_the_current_graph(self):
        print("  Options:")
        print("1. Add a new vertex")
        print("2. Remove a vertex")
        print("3. Add an new edge")
        print("4. Remove an edge")
        imputed_option = input("Your option is: ")
        if imputed_option == '1':
            new_vertex_number = input("Enter the number for the new vertex: ")
            self.__available_services.add_a_new_vertex(new_vertex_number)
        elif imputed_option == '2':
            removed_vertex_number = input("Enter which vertex you want to be deleted: ")
            self.__available_services.remove_a_vertex(removed_vertex_number)
        elif imputed_option == '3':
            vertex_out = input("Enter the vertex out for the new edge: ")
            vertex_in = input("Enter the vertex in for the new edge: ")
            cost = input("Enter the cost for the new edge: ")
            self.__available_services.add_a_new_edge(vertex_out, vertex_in, cost)
        elif imputed_option == '4':
            vertex_out = input("Enter the vertex out for the removed edge: ")
            vertex_in = input("Enter the vertex in for the removed edge: ")
            self.__available_services.remove_an_edge(vertex_out, vertex_in)
        else:
            raise ValueError("Invalid option!")

    def check_if_exist_edge_between_to_vertices(self):
        vertex_out = input("Enter the vertex out: ")
        vertex_in = input("Enter the vertex in: ")
        if self.__available_services.check_if_exist_edge_between_to_vertices(vertex_out, vertex_in):
            print("Exist edge between", vertex_out, "and", vertex_in, "!")
        else:
            print("Doesn't exist edge between", vertex_out, "and", vertex_in, "!")

    def get_the_in_and_out_degree_for_a_vertex(self):
        vertex = input("Enter the vertex: ")
        in_degree, out_degree = self.__available_services.get_the_in_and_out_degree_for_a_vertex(vertex)
        print("The in degree is", in_degree, "and the out degree is", out_degree, "for the vertex", vertex, "!")

    def iterate_the_outbound_edges_of_a_vertex(self):
        vertex = input("Enter the vertex: ")
        outbound_edges = self.__available_services.iterate_the_outbound_edges_of_a_vertex(vertex)
        print("The outbound edges for vertex", vertex, "are:", outbound_edges)

    def iterate_the_inbound_edges_of_a_vertex(self):
        vertex = input("Enter the vertex: ")
        inbound_edges = self.__available_services.iterate_the_inbound_edges_of_a_vertex(vertex)
        print("The inbound edges for vertex", vertex, "are:", inbound_edges)

    def modify_the_information_of_an_edge(self):
        vertex_out = input("Enter the vertex out: ")
        vertex_in = input("Enter the vertex in: ")
        new_cost = input("Enter the new cost for this edge: ")
        self.__available_services.modify_the_cost_of_an_edge(vertex_out, vertex_in, new_cost)

    def find_the_connected_components_dfs(self):
        print("  ~ The connected components are: ")
        printed_list = self.__available_services.get_the_connected_components_dfs()
        for index in printed_list:
            print(list(index))

    def the_cost_between_to_vertices(self):
        vertex_out = input("The starting vertex is: ")
        vertex_in = input("The destination vertex is: ")
        print("The cost between", vertex_out, "and", vertex_in, "is:", self.__available_services.get_the_cost_between_two_vertices(int(vertex_out), int(vertex_in)))

    @staticmethod
    def print_menu():
        print("  ~  Practical work - Balau Mihai  ~")
        print(" ")
        print("1. Create a random graph")
        print("2. Modify the current graph")
        print("3. Read the graph from a text file")
        print("4. Write the graph in a text file")
        print("5. Show the number of vertices")
        print("6. Iterate the set of vertices")
        print("7. Check if exist edge between to vertices")
        print("8. Get the in and out degree for a vertex")
        print("9. Iterate the outbound edges of a vertex")
        print("10. Iterate the inbound edges of a vertex")
        print("11. Modify the information for an edge")
        print("12. Make a backup of the current graph")
        print("13. Restore the backup to current graph")
        print("14. Finds the connected components using a depth-first traversal")
        print("15. The cost between to vertices with negative values and cycles")
        print("0. Exit")
        print("")

    def run_code(self):
        while True:
            try:
                self.print_menu()
                imputed_option = input("Enter the option: ")
                imputed_option = int(imputed_option)
                if imputed_option == 1:
                    self.create_a_random_graph()
                    print("\n ~ Operation was made successfully!")
                elif imputed_option == 2:
                    self.modify_the_current_graph()
                    print("\n ~ Operation was made successfully!")
                elif imputed_option == 3:
                    file_name = input("Enter the file name from where you want to load the graph: ")
                    self.__available_services.load_the_graph_from_text_file(file_name)
                    print("\n ~ Operation was made successfully!")
                elif imputed_option == 4:
                    file_name = input("Enter the file name where you want to print the graph: ")
                    self.__available_services.print_the_graph_in_text_file(file_name)
                    print("\n ~ Operation was made successfully!")
                elif imputed_option == 5:
                    print("The number of graph's vertices are:", self.__available_services.get_the_number_of_vertices())
                    print("\n ~ Operation was made successfully!")
                elif imputed_option == 6:
                    print("THe set of vertices are:", self.__available_services.get_the_set_of_vertices())
                elif imputed_option == 7:
                    self.check_if_exist_edge_between_to_vertices()
                    print("\n ~ Operation was made successfully!")
                elif imputed_option == 8:
                    self.get_the_in_and_out_degree_for_a_vertex()
                    print("\n ~ Operation was made successfully!")
                elif imputed_option == 9:
                    self.iterate_the_outbound_edges_of_a_vertex()
                    print("\n ~ Operation was made successfully!")
                elif imputed_option == 10:
                    self.iterate_the_inbound_edges_of_a_vertex()
                    print("\n ~ Operation was made successfully!")
                elif imputed_option == 11:
                    self.modify_the_information_of_an_edge()
                    print("\n ~ Operation was made successfully!")
                elif imputed_option == 12:
                    self.__available_services.make_a_backup_of_current_graph()
                    print("\n ~ Operation was made successfully!")
                elif imputed_option == 13:
                    self.__available_services.restore_the_backup_to_current_graph()
                    print("\n ~ Operation was made successfully!")
                elif imputed_option == 14:
                    self.find_the_connected_components_dfs()
                    print("\n ~ Operation was made successfully!")
                elif imputed_option == 15:
                    self.the_cost_between_to_vertices()
                    print("\n ~ Operation was made successfully!")
                elif imputed_option == 0:
                    print("\n ~ Have a good day! \n")
                    return
                else:
                    raise ValueError("Invalid option!")
            except ValueError as error_message:
                print("Error:", error_message)
