
#include "graph.h"
int main()
{
    Graph<int> g;
    g.add_edge(0);
    g.add_edge(1);
    g.add_edge(2);
    g.add_edge(3);
    g.add_edge(4);
    g.add_edge(5);
    g.add_edge(6);
    g.add_edge(7);

    g.add_vertex(0, 2, 1);
    g.add_vertex(0, 1, 1);
    g.add_vertex(1, 3, 1);
    g.add_vertex(3, 4, 1);
    g.add_vertex(3, 2, 1);
    g.add_vertex(4, 6, 1);
    g.add_vertex(4, 5, 1);
    g.add_vertex(5, 6, 1);
    g.add_vertex(6, 7, 1);

    g.display_adjacency_list();
    
    g.find_bridges();

}
