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

class Vertex
{
public:
    std::string index;

    bool operator==(const Vertex& r)
    {
        return index == r.index;
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

public:
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
            if(!std::count(vertices.begin(), vertices.end(), n))
                vertices.push_back(n);
            if(!std::count(vertices.begin(), vertices.end(), t))
                vertices.push_back(t);
            if(!std::count(edges.begin(), edges.end(), e))
                edges.push_back(e);
        }
        f.close();
    }

    void save_graph(std::string filename)
    {
        std::ofstream out(filename);
        for(auto& el : kruskal_edges)
            out << el.n1 << ',' << el.n2 << ',' << el.weight << std::endl;
        out.close();
    }

    void kruskal()
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
            auto it = std::min_element(edges.begin(), edges.end());
            Edge& min_edge = *it;
            Vertex n1(min_edge.n1);
            Vertex n2(min_edge.n2);
            Set<Vertex>* s1 = get_set(n1, p);
            Set<Vertex>* s2 = get_set(n2, p);

            if(s1 == s2)
            {
                edges.erase(it);
                continue;
            }
            *s1 = s1->uni(*s2);
            p.erase(p.begin() + set_index(*s2, p));
            kruskal_edges.push_back(min_edge);
            edges.erase(it);
        }
    }
};
