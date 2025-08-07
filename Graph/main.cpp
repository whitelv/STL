
#include "graph.h"
int main()
{
    Graph<int> graph{
        {0, 0, 1, 1, 10},
        {0, 0, 2, 2, 10},
        {0, 0, 3, 3, 10},
        {1, 1, 2, 2, 10},
        {3, 3, 2, 2, 10},

    };
    graph.erase_vertex(0);
    graph.display_adjacency_list();

    return 0;
}
