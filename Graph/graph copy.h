#pragma once
#include <vector>
#include <unordered_map>
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
        size_t from_id;
        size_t to_id;
        size_t weight;
    };

    // constructor utilities
    struct ConstructorUtility
    {
        size_t from_id;
        T from_value;
        size_t to_id;
        T to_value;
        size_t weight;
    };

    void constructor_vertex_utility(size_t id, const T &value)
    {
        if (!adjacency_list.count(id))
        {
            add_vertex(id, value);
        }
        if (adjacency_list.count(id) && vertices[id] != value)
        {
            throw std::invalid_argument("Error: same key - diffirent values");
        }
    }

    // dijkstra utilities
    struct PathLength
    {
        size_t id;
        size_t length;
    };

    friend bool
    operator<(const PathLength &p1, const PathLength &p2)
    {
        return p1.length < p2.length;
    }

    // constructors
    Graph() {}
    Graph(std::initializer_list<ConstructorUtility> ilist)
    {
        auto begin = ilist.begin();

        while (begin != ilist.end())
        {
            constructor_vertex_utility(begin->from_id, begin->from_value);
            constructor_vertex_utility(begin->to_id, begin->to_value);
            add_edge(begin->from_id, begin->to_id, begin->weight);
            begin++;
        }
        return;
    }

    // modifiers
public:
    void add_vertex(size_t id, const T &value)
    {
        if (vertices.count(id))
        {
            throw std::invalid_argument("Error: such vertex exists already");
        }
        vertices.insert(std::pair<size_t, T>(id, value));
        adjacency_list.insert(std::pair<size_t, std::forward_list<Edge>>(id, std::forward_list<Edge>{}));
    }

    void add_edge(size_t from_id, size_t to_id, size_t weight)
    {
        if (from_id == to_id)
        {
            throw std::invalid_argument("Error: edge to itself");
        }

        if (!vertices.count(from_id) || !vertices.count(to_id))
        {
            throw std::out_of_range("Error: No such vertex id");
        }

        if (check_for_edge(from_id, to_id))
        {
            throw std::invalid_argument("Error: Edge between from_id & to_id exists");
        }
        adjacency_list[from_id].push_front(create_new_edge(from_id, to_id, weight));
        adjacency_list[to_id].push_front(create_new_edge(to_id, from_id, weight));
    }

    void erase_edge(size_t from_id, size_t to_id)
    {
        if (from_id == to_id)
        {
            throw std::invalid_argument("Error: edge to itself");
        }
        if (!vertices.count(from_id) || !vertices.count(to_id))
        {
            throw std::out_of_range("Error: No such vertex id");
        }
        if (!check_for_edge(from_id, to_id))
        {
            throw std::invalid_argument("Error: Edge between from_id & to_id doesnt exist");
        }

        erase_edge_utility(from_id, to_id);
        erase_edge_utility(to_id, from_id);
    }

    void erase_vertex(size_t id)
    {
        if (!vertices.count(id))
        {
            throw std::invalid_argument("Error: such vertex doesnt exist yet");
        }
        auto begin = adjacency_list[id].begin();
        while (begin != adjacency_list[id].end())
        {
            erase_edge_utility(begin->to_id, id);
            begin++;
        }
        vertices.erase(id);
        adjacency_list.erase(id);
    }

    // observers
public:
    bool check_for_edge(size_t from_id, size_t to_id)
    {
        if (from_id == to_id)
        {
            throw std::invalid_argument("Error: vertex to itself");
        }
        if (!vertices.count(from_id) || !vertices.count(to_id))
        {
            throw std::out_of_range("Error: No such vertex id");
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
        if (!vertices.count(id))
        {
            throw std::out_of_range("Error: No such vertex id");
        }
        std::queue<size_t> q;
        std::unordered_map<size_t, bool> visited;

        q.push(id);
        visited[id] = true;

        while (!q.empty())
        {
            auto front = q.front();
            auto begin = adjacency_list[front].begin();
            auto end = adjacency_list[front].end();

            while (begin != end)
            {
                if (!visited.count(begin->to_id))
                {
                    q.push(begin->to_id);
                    visited[begin->to_id] = true;
                }
                begin++;
            }
            callback(vertices[front]);
            q.pop();
        }
        return;
    }

    template <typename Callback>
    void DFS(size_t id, Callback callback)
    {
        if (!vertices.count(id))
        {
            throw std::out_of_range("Error: No such vertex id");
        }

        std::stack<size_t> s;
        std::unordered_map<size_t, bool> visited;

        s.push(id);
        visited[id] = true;
        callback(vertices[id]);

        while (!s.empty())
        {
            auto top = s.top();
            auto begin = adjacency_list[top].begin();
            auto end = adjacency_list[top].end();
            while (begin != end)
            {
                if (!visited.count(begin->to_id))
                {
                    auto next = begin->to_id;
                    s.push(next);
                    visited[next] = true;
                    callback(vertices[next]);
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

    std::vector<std::pair<size_t, size_t>> find_bridges()
    {
        if (vertices.empty())
        {
            throw std::out_of_range("Error: No Vertices");
        }
        std::stack<size_t> s;
        std::unordered_map<size_t, bool> visited;
        std::unordered_map<size_t, size_t> time_in;
        std::unordered_map<size_t, size_t> f_up;
        std::unordered_map<size_t, size_t> parents;
        std::vector<std::pair<size_t, size_t>> brigdes;
        size_t time = 0;

        size_t start_index = vertices.begin()->second;
        s.push(start_index);
        visited[start_index] = true;
        time_in[start_index] = time++;
        f_up[start_index] = time_in[start_index];
        parents[start_index] = 0;

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
                if (visited.count(begin->to_id))
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

    std::unordered_map<size_t, size_t> dijkstra(size_t id)
    {
        if (!vertices.count(id))
        {
            throw std::out_of_range("Error: No such edge id");
        }

        std::unordered_map<size_t, bool> visited;
        std::unordered_map<size_t, size_t> distance;
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
                if (!visited.count(begin->to_id))
                {
                    auto dist = min.length + begin->weight;
                    if (!distance.count(begin->to_id) || dist < distance[begin->to_id])
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

    std::unordered_map<size_t, T> get_vertices_map() const
    {
        return vertices;
    }

    void display_adjacency_list() const
    {
        auto begin = vertices.begin();
        while (begin != vertices.end())
        {
            std::cout << begin->first << ": ";
            auto begin_list = adjacency_list.at(begin->first).begin();
            auto end_list = adjacency_list.at(begin->first).end();

            while (begin_list != end_list)
            {
                std::cout << "[" << begin_list->to_id << ", " << begin_list->weight << "], ";
                begin_list++;
            }
            std::cout << std::endl;
            begin++;
        }
    }

    // utilities
private:
    Edge create_new_edge(size_t from_id, size_t to_id, size_t weight)
    {
        return Edge{from_id, to_id, weight};
    }

    void erase_edge_utility(size_t from_id, size_t to_id)
    {
        auto before_begin_from = adjacency_list[from_id].before_begin();
        auto begin_from = adjacency_list[from_id].begin();

        while (begin_from != adjacency_list[from_id].end() && begin_from->to_id != to_id)
        {
            before_begin_from++;
            begin_from++;
        }
        adjacency_list[from_id].erase_after(before_begin_from);
    }

public:
    std::unordered_map<size_t, std::forward_list<Edge>> adjacency_list;
    std::unordered_map<size_t, T> vertices;
};