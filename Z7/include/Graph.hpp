#pragma once
#include <string>
#include <fstream>
#include <vector>
#include <stdexcept>
#include <sstream>
#include <iostream>
#include <algorithm>
#include <map>
#include <climits>

class Edge;

class Node
{
private:
public:
    std::string index;
    std::vector<Edge*> edges;
    Node* parent = nullptr;
    int d = INT_MAX;
};

class Edge
{
private:
public:
    std::string start;
    std::string target;
    int weight;
};

class Graph
{
private:
    std::vector<Node> all_nodes;
    std::vector<Edge*> all_edges;
    int time = 0;
    int silne = 0;

    Node* get_node(std::string index)
    {
        for(Node& n : all_nodes)
        {
            if(n.index == index)
                return &n;
        }
        return nullptr;
    }

    bool contains_node(std::string i)
    {
        for(Node& n : all_nodes)
        {
            if(n.index == i)
                return true;
        }
        return false;
    }

    int w(Node* u, std::string v)
    {
        for(Edge* e : u->edges)
        {
            if(e->target == v)
                return e->weight;
        }
        return 0;
    }

    void relax(std::string u, std::string v)
    {
        Node* nu = get_node(u);
        Node* nv = get_node(v);
        int ww = w(nu, v);
        if(nu->d == INT_MAX)
            return;
        if(nv->d > nu->d + ww)
        {
            nv->d = nu->d + ww;
            nv->parent = nu;
        }
    }

public:
    std::map<std::string, int> dlugosc;
    std::map<std::string, std::string> poprzednik;

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
            int weight = std::atoi(seglist.at(2).c_str());

            if(!contains_node(node))
            {
                Node n;
                n.index = node;
                all_nodes.push_back(n);
            }
            if(!contains_node(target))
            {
                Node n;
                n.index = target;
                all_nodes.push_back(n);
            }

            Edge* e = new Edge();
            e->target = target;
            e->start = node;
            e->weight = weight;
            all_edges.push_back(e);

            for(Node& n : all_nodes)
            {
                if(n.index == node)
                    n.edges.push_back(e);
            }
        }
        f.close();
    }

    bool bellman_ford(std::string start_node)
    {
        bool ret = true;
        Node* n = get_node(start_node);
        if(!n)
            return false;
        n->d = 0;
        for(size_t i = 0; i < all_nodes.size(); i++)
        {
            for(Edge* e : all_edges)
                relax(e->start, e->target);
        }
        for(Edge* e : all_edges)
        {
            Node* u = get_node(e->start);
            Node* v = get_node(e->target);
            if(u->d == INT_MAX)
                continue;
            if(v->d > u->d + w(u, e->target))
                ret = false;
        }

        for(Node& n : all_nodes)
        {
            dlugosc.insert({n.index, n.d});
            if(n.parent == nullptr)
                poprzednik.insert({n.index, "NULL"});
            else
                poprzednik.insert({n.index, n.parent->index});
        }

        return ret;
    }
};
