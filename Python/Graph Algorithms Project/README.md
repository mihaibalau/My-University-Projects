# Graph algorithms

Console application for directed graphs with a cost on each edge, from the graphs course. The code is split the same way as the other Python labs: `Domain.py` holds a vertex and its inbound and outbound neighbours, `Repository.py` stores the graph, `Services.py` does the work, `UserInterface.py` is the menu.

From the menu I can build a random graph, add or remove vertices and edges, change a cost, and save or load a text file. There is also a backup copy of the current graph, so a change can be undone.

Two algorithms sit on top of that:

- connected components, by depth-first search: each unvisited vertex starts a new component
- lowest cost between two vertices, including negative costs. The search keeps a distance for each vertex and relaxes outbound edges. If the start vertex is reached again on a cheaper walk, it reports a negative cycle. If the target stays at infinity, it is unreachable

`graph1k.txt`, `graph10k.txt` and `graph100k.txt` are sample graphs.

Technologies: Python.
