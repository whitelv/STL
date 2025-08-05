#pragma once
#include <vector>
#include <forward_list>
#include <memory>
#include <queue>
#include <stack>
#include <iostream>
#include <limits>
#include "../Heap -Array/heap.h"

template <typename T>
class Graph
{
public:
    struct Edge
    {
        size_t id;
        T value;
    };

    struct Vertex
    {
        size_t to_id;
        size_t weight;
    };

    struct PathLength
    {
        size_t id;
        size_t length;
    };

    friend bool operator<(const PathLength &p1, const PathLength &p2)
    {
        return p1.length < p2.length;
    }

    std::vector<size_t> dijkstra(size_t id)
    {
        if (id >= edges.size())
        {
            throw std::out_of_range("Error: No such edge id");
        }

        std::vector<bool> visited(edges.size(), false);
        std::vector<size_t> distance(edges.size(), std::numeric_limits<size_t>::max());
        Heap<PathLength> heap;

        visited[id] = true;
        distance[id] = 0;
        heap.insert(PathLength(id, distance[id]));

        std::cout << heap.get_min() << std::endl;
        
        return distance;
    }

    void add_edge(const T &value)
    {
        edges.push_back(create_new_edge(value));
        adjacency_list.resize(edges.size());
    }

    void add_vertex(size_t from_id, size_t to_id, size_t weight)
    {
        if (from_id == to_id)
        {
            throw std::invalid_argument("Error: vertex to itself");
        }

        if (from_id >= edges.size() || to_id >= edges.size())
        {
            throw std::out_of_range("Error: No such edge id");
        }

        if (check_for_vertex(from_id, to_id))
        {
            throw std::out_of_range("Error: Vertex between from_id & to_id exists");
        }

        adjacency_list[from_id].push_front(create_new_vertex(to_id, weight));
        adjacency_list[to_id].push_front(create_new_vertex(from_id, weight));
    }

    bool check_for_vertex(size_t from_id, size_t to_id)
    {
        if (from_id == to_id)
        {
            throw std::invalid_argument("Error: vertex to itself");
        }
        if (from_id >= edges.size() || to_id >= edges.size())
        {
            throw std::out_of_range("Error: No such edge id");
        }

        auto begin = adjacency_list[from_id].begin();
        auto end = adjacency_list[from_id].end();

        while (begin != end)
        {
            if (begin->to_id == to_id)
            {
                return true;
            }

            begin++;
        }
        return false;
    }
    template <typename Callback>
    void BFS(size_t id, Callback callback)
    {
        if (id >= edges.size())
        {
            throw std::out_of_range("Error: No such edge id");
        }
        std::queue<size_t> q;
        std::vector<bool> visited(edges.size(), false);

        q.push(id);
        visited[id] = true;

        while (!q.empty())
        {
            auto front = q.front();
            auto begin = adjacency_list[front].begin();
            auto end = adjacency_list[front].end();

            while (begin != end)
            {
                if (visited[begin->to_id] != true)
                {
                    q.push(begin->to_id);
                    visited[begin->to_id] = true;
                }
                begin++;
            }
            callback(edges[front].value);
            q.pop();
        }
    }

    template <typename Callback>
    void DFS(size_t id, Callback callback)
    {
        if (id >= edges.size())
        {
            throw std::out_of_range("Error: No such edge id");
        }

        std::stack<size_t> s;
        std::vector<bool> visited(edges.size(), false);

        s.push(id);
        visited[id] = true;
        callback(edges[id].value);

        while (!s.empty())
        {
            auto top = s.top();
            auto begin = adjacency_list[top].begin();
            auto end = adjacency_list[top].end();
            while (begin != end)
            {
                if (visited[begin->to_id] != true)
                {
                    auto next = begin->to_id;
                    s.push(next);
                    visited[next] = true;
                    callback(edges[next].value);
                    break;
                }
                begin++;
            }
            if (begin == end)
            {
                s.pop();
            }
        }
    }

    void display_edges() const
    {
        for (size_t i = 0; i < edges.size(); i++)
        {
            std::cout << "[" << edges[i].id << ", " << edges[i].value << "], ";
        }
        std::cout << std::endl;
    }

    void display_adjacency_list() const
    {
        for (size_t i = 0; i < adjacency_list.size(); i++)
        {
            std::cout << i << ": ";

            auto begin = adjacency_list[i].begin();
            auto end = adjacency_list[i].end();

            while (begin != end)
            {
                std::cout << "[" << begin->to_id << ", " << begin->weight << "], ";
                begin++;
            }

            std::cout << std::endl;
        }
    }

    Edge create_new_edge(const T &value)
    {
        return Edge{edges.size(), value};
    }

    Vertex create_new_vertex(size_t to_id, size_t weight)
    {
        return Vertex{to_id, weight};
    }

public:
    std::vector<std::forward_list<Vertex>> adjacency_list;
    std::vector<Edge> edges;
};