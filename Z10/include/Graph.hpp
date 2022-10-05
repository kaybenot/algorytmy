#pragma once
#include "Set.hpp"
#include <string>
#include <fstream>
#include <vector>
#include <stdexcept>
#include <sstream>
#include <iostream>
#include <algorithm>
#include <map>
#include <climits>
#include <exception>
#include <set>

class Vertex
{
public:
    std::string index;
    int rank = 0;
    Vertex* p = this;

    bool operator==(const Vertex& r)
    {
        return index == r.index;
    }

    bool operator!=(const Vertex& r)
    {
        return index != r.index;
    }

    bool operator<(const Vertex& r) const noexcept
    {
        return this->index < r.index;
    }

    Vertex(std::string i)
    {
        index = i;
    }

    Vertex() {}
};

class Edge
{
public:
    std::string n1;
    std::string n2;
    float weight;

    bool operator==(const Edge& r)
    {
        if(n1 != r.n1 || n2 != r.n2 || weight != r.weight)
            return false;
        return true;
    }

    bool operator<(const Edge& r)
    {
        return weight < r.weight;
    }
};

class Graph
{
private:
    std::vector<Vertex> vertices;
    std::set<Vertex> added_vertices;
    std::vector<Edge> edges;
    std::vector<Edge> kruskal_edges;

    Set<Vertex>* get_set(Vertex& v, std::vector<Set<Vertex>>& arr)
    {
        for(Set<Vertex>& s : arr)
        {
            if(s.isMember(v))
                return &s;
        }
        return nullptr;
    }

    size_t set_index(Set<Vertex>& s, std::vector<Set<Vertex>> arr)
    {
        for(size_t i = 0; i < arr.size(); i++)
        {
            if(s == arr.at(i))
                return i;
        }
        return 0;
    }

    void LINK(Vertex& x, Vertex& y)
    {
        if(x.rank > y.rank)
            y.p = &x;
        else
            x.p = &y;
        if(x.rank == y.rank)
            y.rank++;
    }

    Vertex* FIND_SET(Vertex& x)
    {
        if(x != *x.p)
            x.p = FIND_SET(*x.p);
        return x.p;
    }

    void UNION(Vertex& x, Vertex& y)
    {
        LINK(*FIND_SET(x), *FIND_SET(y));
    }

    Vertex* get_vert(std::string& v_name)
    {
        for(Vertex& u : vertices)
            if(v_name == u.index)
                return &u;
        return nullptr;
    }

public:
    float min_w = 0;

    void copy_contents(Graph& g2)
    {
        for(Vertex& v : g2.vertices)
            vertices.push_back(v);
        for(Edge& e : g2.edges)
            edges.push_back(e);
    }

    void read_graph(std::string filename)
    {
        std::ifstream f(filename);
        if(!f.good())
            throw std::runtime_error("Could not read file");
        
        std::string line;
        while(std::getline(f, line))
        {
            std::vector<std::string> seglist;
            std::stringstream seg(line);
            std::string segment;
            while(std::getline(seg, segment, ','))
                seglist.push_back(segment);

            std::string node = seglist.at(0);
            std::string target = seglist.at(1);
            float weight = std::atof(seglist.at(2).c_str());
            Vertex n;
            n.index = node;
            Vertex t;
            t.index = target;
            Edge e;
            e.n1 = node;
            e.n2 = target;
            e.weight =  weight;
            if(!added_vertices.count(n))
            {
                vertices.push_back(n);
                added_vertices.insert(n);
            }
            if(!added_vertices.count(t))
            {
                vertices.push_back(t);
                added_vertices.insert(t);
            }
            edges.push_back(e);
        }
        std::sort(edges.begin(), edges.end());
        f.close();
    }

    float kruskal()
    {
        std::vector<Set<Vertex>> p;
        
        for(Vertex& v : vertices)
        {
            Set<Vertex> s;
            s.insert(v);
            p.push_back(s);
        }

        while (p.size() > 1)
        {
            Edge& min_edge = edges.at(0);
            Vertex n1(min_edge.n1);
            Vertex n2(min_edge.n2);
            Set<Vertex>* s1 = get_set(n1, p);
            Set<Vertex>* s2 = get_set(n2, p);

            if(s1 == s2)
            {
                edges.erase(edges.begin());
                continue;
            }
            *s1 = s1->uni(*s2);
            min_w += min_edge.weight;
            p.erase(p.begin() + set_index(*s2, p));
            kruskal_edges.push_back(min_edge);
            edges.erase(edges.begin());
        }
        return min_w;
    }

    float kruskal2()
    {
        for(Vertex& v : vertices)
        {
            v.p = &v;
        }
        size_t zbiory = vertices.size();
        while (zbiory > 1)
        {
            Edge& min_edge = edges.at(0);
            Vertex* s1 = get_vert(min_edge.n1);
            Vertex* s2 = get_vert(min_edge.n2);

            if(*FIND_SET(*s1) == *FIND_SET(*s2))
            {
                edges.erase(edges.begin());
                continue;
            }

            UNION(*s1, *s2);
            zbiory--;
            min_w += min_edge.weight;
            kruskal_edges.push_back(min_edge);
            edges.erase(edges.begin());
        }
        return min_w;
    }
};
