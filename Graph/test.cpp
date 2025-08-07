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

TEST(GraphModule, testAddCycleEdgeThrow)
{
    Graph<int> graph;
    graph.add_vertex(0);
    EXPECT_THROW(graph.add_edge(0, 0, 1), std::invalid_argument);
}

TEST(GraphModule, testAddEdgeToNonExistentVertexThrow)
{
    Graph<int> graph;
    graph.add_vertex(0);
    EXPECT_THROW(graph.add_edge(0, 1, 1), std::out_of_range);
}

TEST(GraphModule, testAddDuplicateEdgeThrow)
{
    Graph<int> graph;
    graph.add_vertex(0);
    graph.add_vertex(1);
    graph.add_edge(0, 1, 1);
    EXPECT_THROW(graph.add_edge(0, 1, 1), std::invalid_argument);
}

TEST(GraphModule, testAddEdge)
{
    Graph<int> graph;
    graph.add_vertex(0);
    graph.add_vertex(1);
    graph.add_vertex(2);
    graph.add_edge(0, 1, 1);
    graph.add_edge(1, 2, 1);
    std::vector<size_t> test;
    std::vector<size_t> result = {0, 1, 2};
    graph.DFS(0, [&test](const auto &value)
              { test.push_back(value); });
    EXPECT_EQ(test, result);
}

TEST(GraphModule, testCheckForCycleEdgeThrow)
{
    Graph<int> graph;
    graph.add_vertex(0);
    EXPECT_THROW(graph.check_for_edge(0, 0), std::invalid_argument);
}

TEST(GraphModule, testtCheckForEdgeToNonExistentVertexThrow)
{
    Graph<int> graph;
    graph.add_vertex(0);
    EXPECT_THROW(graph.check_for_edge(0, 1), std::out_of_range);
}

TEST(GraphModule, testtCheckForVertexTrue)
{
    Graph<int> graph;
    graph.add_vertex(0);
    graph.add_vertex(1);
    graph.add_edge(0, 1, 1);
    EXPECT_TRUE(graph.check_for_edge(0, 1));
}

TEST(GraphModule, testtCheckForVertexFalse)
{
    Graph<int> graph;
    graph.add_vertex(0);
    graph.add_vertex(1);
    EXPECT_FALSE(graph.check_for_edge(0, 1));
}

TEST(GraphModule, testtDFSfromNonExistentVertexThrow)
{
    Graph<int> graph;
    graph.add_vertex(0);
    graph.add_vertex(1);
    graph.add_edge(0, 1, 1);
    EXPECT_THROW(graph.DFS(2, [](const auto &a) {}), std::out_of_range);
}

TEST(GraphModule, testtDFSfromExistentVertexThrow)
{
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
    EXPECT_EQ(test, result);
}


TEST(GraphModule, testBFSfromNonExistentVertexThrow)
{
    Graph<int> graph;
    graph.add_vertex(0);
    graph.add_vertex(1);
    graph.add_edge(0, 1, 1);
    EXPECT_THROW(graph.BFS(2, [](const auto &a) {}), std::out_of_range);
}

TEST(GraphModule, testtBFSfromExistentVertexThrow)
{
    Graph<int> graph;
    for (size_t i = 0; i < 5; i++)
    {
        graph.add_vertex(i);
    }

    graph.add_edge(0, 1, 1);
    graph.add_edge(0, 2, 1);
    graph.add_edge(2, 3, 1);
    graph.add_edge(2, 4, 1);
    std::vector<size_t> test;
    std::vector<size_t> result = {0,2,1,4,3};
    graph.BFS(0, [&test](const auto &value)
              { test.push_back(value); });
    EXPECT_EQ(test, result);
}