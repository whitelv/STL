
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
    for (size_t i = 0; i < 5; i++)
    {
        graph.add_vertex(i);
    }

    graph.add_edge(0, 1, 1);
    graph.add_edge(0, 2, 1);
    graph.add_edge(2, 3, 1);
    graph.add_edge(3, 4, 1);
    std::vector<size_t> test;
    std::vector<size_t> result = {0, 2, 3, 4, 1};
    graph.DFS(0, [&test](const auto &value)
              { test.push_back(value); });
}
