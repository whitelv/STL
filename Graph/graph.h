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

    void add_vertex(const T &value)
    {
        vertices.push_back(create_new_vertex(value));
        adjacency_list.resize(vertices.size());
    }

    void add_edge(size_t from_id, size_t to_id, size_t weight)
    {
        if (from_id == to_id)
        {
            throw std::invalid_argument("Error: vertex to itself");
        }

        if (from_id >= vertices.size() || to_id >= vertices.size())
        {
            throw std::out_of_range("Error: No such edge id");
        }

        if (check_for_edge(from_id, to_id))
        {
            throw std::invalid_argument("Error: Vertex between from_id & to_id exists");
        }

        adjacency_list[from_id].push_front(create_new_edge(to_id, weight));
        adjacency_list[to_id].push_front(create_new_edge(from_id, weight));
    }

    bool check_for_edge(size_t from_id, size_t to_id)
    {
        if (from_id == to_id)
        {
            throw std::invalid_argument("Error: vertex to itself");
        }
        if (from_id >= vertices.size() || to_id >= vertices.size())
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
        if (id >= vertices.size())
        {
            throw std::out_of_range("Error: No such edge id");
        }
        std::queue<size_t> q;
        std::vector<bool> visited(vertices.size(), false);

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
            callback(vertices[front].value);
            q.pop();
        }
    }

    std::vector<std::pair<size_t, size_t>> find_bridges()
    {
        if (vertices.empty())
        {
            throw std::invalid_argument("Error: No Vertices");
        }
        std::stack<size_t> s;
        std::vector<bool> visited(vertices.size(), false);
        std::vector<size_t> time_in(vertices.size(), 0);
        std::vector<size_t> f_up(vertices.size(), 0);
        std::vector<size_t> parents(vertices.size(), 0);
        std::vector<std::pair<size_t, size_t>> brigdes;
        size_t time = 0;

        s.push(0);
        visited[0] = true;
        time_in[0] = time++;
        f_up[0] = time_in[0];

        while (!s.empty())
        {
            auto top = s.top();
            auto begin = adjacency_list[top].begin();
            auto end = adjacency_list[top].end();

            while (begin != end)
            {
                if (begin->to_id == parents[top])
                {
                    begin++;
                    continue;
                }
                if (visited[begin->to_id] == true)
                {
                    f_up[top] = std::min(f_up[top], time_in[begin->to_id]);
                    begin++;
                    continue;
                }
                auto next = begin->to_id;
                s.push(next);
                visited[next] = true;
                time_in[next] = time++;
                f_up[next] = time_in[next];
                parents[next] = top;
                break;
            }
            if (begin == end)
            {
                begin = adjacency_list[top].begin();
                end = adjacency_list[top].end();
                while (begin != end)
                {
                    if (f_up[begin->to_id] > time_in[top])
                    {
                        brigdes.push_back({top, begin->to_id});
                    }
                    begin++;
                }
                s.pop();
                if (!s.empty())
                {
                    f_up[s.top()] = std::min(f_up[s.top()], f_up[top]);
                }
            }
        }
        return brigdes;
    }

    template <typename Callback>
    void DFS(size_t id, Callback callback)
    {
        if (id >= vertices.size())
        {
            throw std::out_of_range("Error: No such edge id");
        }

        std::stack<size_t> s;
        std::vector<bool> visited(vertices.size(), false);

        s.push(id);
        visited[id] = true;
        callback(vertices[id].value);

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
                    callback(vertices[next].value);
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

    std::vector<size_t> dijkstra(size_t id)
    {
        size_t times = 0;
        if (id >= vertices.size())
        {
            throw std::out_of_range("Error: No such edge id");
        }

        std::vector<bool> visited(vertices.size(), false);
        std::vector<size_t> distance(vertices.size(), std::numeric_limits<size_t>::max());
        Heap<PathLength> heap;

        visited[id] = true;
        distance[id] = 0;
        heap.insert(PathLength(id, distance[id]));

        while (!heap.empty())
        {
            auto min = *heap.get_min();
            auto begin = adjacency_list[min.id].begin();
            auto end = adjacency_list[min.id].end();

            while (begin != end)
            {
                if (visited[begin->to_id] != true)
                {
                    auto dist = min.length + begin->weight;
                    if (dist < distance[begin->to_id])
                    {
                        distance[begin->to_id] = dist;
                        heap.insert(PathLength(begin->to_id, distance[begin->to_id]));
                    }
                }
                begin++;
            }
            visited[min.id] = true;
            heap.removeMin();
        }
        return distance;
    }

    std::vector<T> get_vertices_values() const
    {
        std::vector<T> values;
        for (size_t i = 0; i < vertices.size(); i++)
        {
            values.push_back(vertices[i].value);
        }
        return values;
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

    Edge create_new_vertex(const T &value)
    {
        return Edge{vertices.size(), value};
    }

    Vertex create_new_edge(size_t to_id, size_t weight)
    {
        return Vertex{to_id, weight};
    }

public:
    std::vector<std::forward_list<Vertex>> adjacency_list;
    std::vector<Edge> vertices;
};