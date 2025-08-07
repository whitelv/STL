#include <gtest/gtest.h>
#include "graph.h"

TEST(GraphModule, testDefaultConstructor)
{
    EXPECT_NO_FATAL_FAILURE(Graph<int>());
}

TEST(GraphModule, testParameterConstructor)
{
    Graph<int> graph{{0, 0, 1, 1, 1}, {1, 1, 2, 2, 1}};
    std::vector<size_t> test;
    std::vector<size_t> result = {0, 1, 2};
    graph.BFS(0, [&test](const auto &a)
              { test.push_back(a); });
    EXPECT_EQ(test, result);
}

TEST(GraphModule, testParameterConstructorSameKeyDiffValuesThrow)
{
    EXPECT_THROW(Graph<int>({{0, 0, 1, 1, 1}, {1, 2, 2, 2, 1}}), std::invalid_argument);
}

TEST(GraphModule, testAddNoVertex)
{
    Graph<int> graph;
    std::unordered_map<size_t, int> result;
    std::unordered_map<size_t, int> test = graph.get_vertices_map();
    EXPECT_EQ(test, result);
}

TEST(GraphModule, testAddVertex)
{
    Graph<int> graph;
    graph.add_vertex(0, 0);
    graph.add_vertex(1, 1);
    std::unordered_map<size_t, int> result = {{0, 0}, {1, 1}};
    std::unordered_map<size_t, int> test = graph.get_vertices_map();
    EXPECT_EQ(test, result);
}

TEST(GraphModule, testAddDuplicateVertexThrow)
{
    Graph<int> graph;
    graph.add_vertex(0, 0);
    EXPECT_THROW(graph.add_vertex(0, 0), std::invalid_argument);
}

TEST(GraphModule, testAddCycleEdgeThrow)
{
    Graph<int> graph;
    graph.add_vertex(0, 0);
    EXPECT_THROW(graph.add_edge(0, 0, 1), std::invalid_argument);
}

TEST(GraphModule, testAddEdgeToNonExistentVertexThrow)
{
    Graph<int> graph;
    graph.add_vertex(0, 0);
    EXPECT_THROW(graph.add_edge(0, 1, 1), std::out_of_range);
}

TEST(GraphModule, testAddDuplicateEdgeThrow)
{
    Graph<int> graph;
    graph.add_vertex(0, 0);
    graph.add_vertex(1, 1);
    graph.add_edge(0, 1, 1);
    EXPECT_THROW(graph.add_edge(0, 1, 1), std::invalid_argument);
}

TEST(GraphModule, testAddEdge)
{
    Graph<int> graph;
    graph.add_vertex(0, 0);
    graph.add_vertex(1, 1);
    graph.add_vertex(2, 2);
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
    graph.add_vertex(0, 0);
    EXPECT_THROW(graph.check_for_edge(0, 0), std::invalid_argument);
}

TEST(GraphModule, testtCheckForEdgeToNonExistentVertexThrow)
{
    Graph<int> graph;
    graph.add_vertex(0, 0);
    EXPECT_THROW(graph.check_for_edge(0, 1), std::out_of_range);
}

TEST(GraphModule, testtCheckForVertexTrue)
{
    Graph<int> graph;
    graph.add_vertex(0, 0);
    graph.add_vertex(1, 1);
    graph.add_edge(0, 1, 1);
    EXPECT_TRUE(graph.check_for_edge(0, 1));
}

TEST(GraphModule, testCheckForVertexFalse)
{
    Graph<int> graph;
    graph.add_vertex(0, 0);
    graph.add_vertex(1, 1);
    EXPECT_FALSE(graph.check_for_edge(0, 1));
}

TEST(GraphModule, testtDFSfromNonExistentVertexThrow)
{
    Graph<int> graph;
    graph.add_vertex(0, 0);
    graph.add_vertex(1, 1);
    graph.add_edge(0, 1, 1);
    EXPECT_THROW(graph.DFS(2, [](const auto &a) {}), std::out_of_range);
}

TEST(GraphModule, testtDFSfromExistentVertexThrow)
{
    Graph<int> graph;
    for (size_t i = 0; i < 5; i++)
    {
        graph.add_vertex(i, i);
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
    graph.add_vertex(0, 0);
    graph.add_vertex(1, 1);
    graph.add_edge(0, 1, 1);
    EXPECT_THROW(graph.BFS(2, [](const auto &a) {}), std::out_of_range);
}

TEST(GraphModule, testtBFSfromExistentVertexThrow)
{
    Graph<int> graph;
    for (size_t i = 0; i < 5; i++)
    {
        graph.add_vertex(i, i);
    }

    graph.add_edge(0, 1, 1);
    graph.add_edge(0, 2, 1);
    graph.add_edge(2, 3, 1);
    graph.add_edge(2, 4, 1);
    std::vector<size_t> test;
    std::vector<size_t> result = {0, 2, 1, 4, 3};
    graph.BFS(0, [&test](const auto &value)
              { test.push_back(value); });
    EXPECT_EQ(test, result);
}

TEST(GraphModule, testDijkstraFromNonExistentVertexThrow)
{
    Graph<int> graph;
    EXPECT_THROW(graph.dijkstra(0), std::out_of_range);
}

TEST(GraphModule, testDijkstraFromExistentVertexOneVertex)
{
    Graph<int> graph;
    graph.add_vertex(0, 0);
    std::unordered_map<size_t, size_t> test = graph.dijkstra(0);
    EXPECT_EQ(test[0], 0);
}

TEST(GraphModule, testDijkstraFromExistentVertexCase1)
{
    Graph<int> graph{
        {0, 0, 1, 1, 10},
        {0, 0, 2, 2, 2},
        {2, 2, 4, 4, 4},
        {4, 4, 1, 1, 1},
        {1, 1, 3, 3, 5},
        {3, 3, 6, 6, 3},
        {4, 4, 6, 6, 8},
        {6, 6, 7, 7, 4},
        {7, 7, 5, 5, 6},
        {5, 5, 2, 2, 12}};
    std::vector<size_t> results = {0, 7, 2, 12, 6, 14, 14, 18};
    std::unordered_map<size_t, size_t> test = graph.dijkstra(0);

    for (size_t i = 0; i < 8; i++)
    {
        EXPECT_EQ(test[i], results[i]);
    }
}

TEST(GraphModule, testDijkstraFromExistentVertexCase2)
{
    Graph<int> graph{
        {0, 0, 2, 2, 6},
        {0, 0, 3, 3, 3},
        {0, 0, 4, 4, 2},
        {1, 1, 6, 6, 1},
        {2, 2, 5, 5, 6},
        {4, 4, 6, 6, 9},
        {4, 4, 7, 7, 5},
        {6, 6, 7, 7, 3},
    };
    std::vector<size_t> results = {3, 14, 9, 0, 5, 15, 13, 10};
    std::unordered_map<size_t, size_t> test = graph.dijkstra(3);

    for (size_t i = 0; i < 8; i++)
    {
        EXPECT_EQ(test[i], results[i]);
    }
}

TEST(GraphModule, testFindBridgesInEmptyGraph)
{
    Graph<int> graph;
    EXPECT_THROW(graph.find_bridges(), std::out_of_range);
}

TEST(GraphModule, testFindBridgesInGraphWithOneVertex)
{
    Graph<int> graph;
    graph.add_vertex(0, 0);
    std::vector<std::pair<size_t, size_t>> results = {};
    auto test = graph.find_bridges();
    EXPECT_EQ(results, test);
}

TEST(GraphModule, testFindBridgesInGraphCase1)
{
    Graph<int> graph{
        {0, 0, 1, 1, 1}, // V0 — V1
        {0, 0, 2, 2, 1}, // V0 — V2
        {1, 1, 3, 3, 1}, // V1 — V3
        {2, 2, 3, 3, 1}, // V2 — V3
        {3, 3, 4, 4, 1}, // V3 — V4
        {4, 4, 5, 5, 1}, // V4 — V5
        {4, 4, 6, 6, 1}, // V4 — V6
        {5, 5, 6, 6, 1}, // V5 — V6
        {6, 6, 7, 7, 1}  // V6 — V7
    };

    std::vector<std::pair<size_t, size_t>> results = {{4, 3}, {7, 6}};
    auto test = graph.find_bridges();

    EXPECT_EQ(results, test);
}


TEST(GraphModule, testFindBridgesInGraphCase2)
{
    Graph<int> graph{
        {0, 0, 1, 1, 1}, // V0 — V1
        {1, 1, 3, 3, 1}, // V1 — V3
        {2, 2, 3, 3, 1}, // V2 — V3
        {3, 3, 4, 4, 1}, // V3 — V4
        {4, 4, 5, 5, 1}, // V4 — V5
        {4, 4, 6, 6, 1}, // V4 — V6
        {6, 6, 7, 7, 1}  // V6 — V7
    };

    std::vector<std::pair<size_t, size_t>> results = {{1,0}, {3,2}, {3,1}, {4,5}, {4,3}, {6,4}, {7,6}};
    auto test = graph.find_bridges();

    EXPECT_EQ(results, test);
}