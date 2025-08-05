
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
    g.add_edge(8);
    g.add_edge(9);
    g.add_edge(10);
    g.add_edge(11);
    g.add_edge(12);
    g.add_edge(13);
    g.add_edge(14);
    g.add_edge(15);
    g.add_edge(16);
    g.add_edge(17);

    g.add_vertex(0, 2, 9);
    g.add_vertex(0, 4, 6);
    g.add_vertex(0, 14, 3);

    g.add_vertex(1, 4, 4);

    
    g.add_vertex(2, 5, 9);
    g.add_vertex(2, 6, 4);

    g.add_vertex(3, 6, 5);

    
    g.add_vertex(4, 5, 1);
    g.add_vertex(4, 7, 9);

   
    g.add_vertex(5, 6, 9);
    g.add_vertex(5, 8, 9);

  
    g.add_vertex(6, 9, 7);
    g.add_vertex(6, 10, 7);

    
    g.add_vertex(7, 8, 2);
    g.add_vertex(7, 11, 6);

    
    g.add_vertex(8, 9, 2);
    g.add_vertex(8, 11, 2);
    g.add_vertex(8, 12, 6);

   
    g.add_vertex(9, 10, 1);

    
    g.add_vertex(10, 13, 8);
    g.add_vertex(10, 17, 2);

   
    g.add_vertex(11, 12, 9);
    g.add_vertex(11, 15, 3);

    
    g.add_vertex(12, 13, 7);
    g.add_vertex(12, 15, 5);
    g.add_vertex(12, 16, 3);

    
    g.add_vertex(13, 16, 2);
    g.add_vertex(13, 17, 7);

    
    g.add_vertex(14, 15, 7);


    std::vector<size_t> v = g.dijkstra(0);
    std::cout << std::endl;
}
// std::cout << "[" << edges[front].id << ", " << edges[front].value << "], " << std::flush;