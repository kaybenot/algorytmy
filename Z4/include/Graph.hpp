#pragma once
#include <string>
#include <fstream>
#include <vector>
#include <stdexcept>
#include <sstream>
#include <iostream>
#include <limits>

enum class Color
{
    WHITE,
    GRAY,
    BLACK
};

class Edge;

class Node
{
private:
public:
    std::string index;
    std::vector<Edge> edges;
    unsigned int distance = UINT_MAX;
    std::string out_num;
};

class Edge
{
private:
public:
    int weight;
    std::string target;
};

class Graph
{
private:
    Node* root = nullptr;
    std::vector<Node> all_nodes;

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

    void recursive(Edge& e, unsigned int distance, std::string out_num)
    {
        Node* n = get_node(e.target);
        if(n->distance < distance + e.weight)
            return;
        n->distance = distance + e.weight;
        n->out_num = out_num;
        for(Edge& ed : n->edges)
            recursive(ed, distance + e.weight, n->index);
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

            Edge e;
            e.target = target;
            e.weight = weight;

            for(Node& n : all_nodes)
            {
                if(n.index == node)
                    n.edges.push_back(e);
            }
        }
        f.close();
    }

    Graph BFS(std::string index)
    {
        if(!contains_node(index))
            return Graph();

        for(Node &n : all_nodes)
            n.distance = UINT_MAX;
        
        Graph gr;
        for(Node n : all_nodes)
            gr.all_nodes.push_back(n);

        gr.root = get_node(index);
        gr.root->distance = 0;
        unsigned int distance = 0;
        for(Edge& e : gr.root->edges)
            gr.recursive(e, distance, gr.root->index);
        return gr;
    }

    std::vector<Node> get_path(std::string end)
    {
        std::vector<Node> out;
        Node* n = get_node(end);
        if(n->distance == UINT_MAX)
            return out;
        while(n->index != root->index)
        {
            out.push_back(*n);
            n = get_node(n->out_num);
        }
        return out;
    }

    int get_hops(std::string end)
    {
        if(end == root->index)
            return 0;
        Node* n = get_node(end);
        if(n == nullptr)
            return -1;
        if(n->distance == UINT_MAX)
            return -1;
        return n->distance;
    }
};
