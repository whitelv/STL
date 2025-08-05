
#include "graph.h"

int main()
{
    Graph<int> g;
    g.add_edge(0);
    g.add_edge(1);
    g.add_edge(2);
    g.add_edge(3);
    g.add_edge(4);

    g.add_vertex(0, 2, 1);
    g.add_vertex(0, 1, 1);
    g.add_vertex(1, 2, 1);
    g.add_vertex(2, 4, 1);
    g.add_vertex(2, 3, 1);
    g.add_vertex(0, 4, 1);

    g.display_adjacency_list();



    g.dijkstra(0);

    std::cout << std::endl;
}

// std::cout << "[" << edges[front].id << ", " << edges[front].value << "], " << std::flush;