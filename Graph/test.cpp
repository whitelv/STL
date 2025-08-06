#include <gtest/gtest.h>
#include "graph.h"

TEST(GraphModule, testAddNoVertex)
{
    Graph<int> graph;
    std::vector<int> result;
    std::vector<int> test = graph.get_vertices_values();
    EXPECT_EQ(test, result);
}

TEST(GraphModule, testAddVertex)
{
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
    EXPECT_EQ(test, result);
}

TEST(GraphModule, testAddCycleEdgeThrow){
    Graph<int> graph;
    graph.add_vertex(0);
    EXPECT_THROW(graph.add_edge(0,0,1), std::invalid_argument);
}
