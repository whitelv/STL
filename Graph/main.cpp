
#include "graph.h"
int main()
{
    Graph<int> g;
    g.add_vertex(0);
    g.add_vertex(1);
    g.add_vertex(2);
    g.add_vertex(3);
    g.add_vertex(4);
    g.add_vertex(5);
    g.add_vertex(6);
    g.add_vertex(7);

    g.add_edge(0, 1, 1);
    g.add_edge(1, 3, 1);
    g.add_edge(3, 4, 1);
    g.add_edge(3, 2, 1);
    g.add_edge(4, 5, 1);
    g.add_edge(5, 6, 1);
    g.add_edge(6, 7, 1);

    g.display_adjacency_list();

    std::vector<int> v = g.get_vertices_values();

    g.find_bridges();

    Graph<int> graph;
    std::vector<int> result;
    for (size_t i = 0; i < 10; i++)
    {
        if (i % 2)
        {
            graph.add_vertex(i * i);
            result.push_back(i * i);
        }
        else
        {
            graph.add_vertex(i * i * -i);
            result.push_back(i * i * -i);
        }
    }
    std::vector<int> test = graph.get_vertices_values();

}
