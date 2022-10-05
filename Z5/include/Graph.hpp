#pragma once
#include <string>
#include <fstream>
#include <vector>
#include <stdexcept>
#include <sstream>
#include <iostream>
#include <algorithm>

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
    int d = -1;
    int f = -1;
    Color color = Color::WHITE;
    Node* parent = nullptr;
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
    int time;
    std::vector<std::string> list;

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

    void DFS_Visit(Node& node)
    {
        time++;
        node.d = time;
        node.color = Color::GRAY;
        for(Edge& e : node.edges)
        {
            Node* adj = get_node(e.target);
            if(adj->color == Color::WHITE)
            {
                adj->parent = &node;
                DFS_Visit(*adj);
            }
        }
        node.color = Color::BLACK;
        time++;
        node.f = time;
        list.insert(list.begin(), node.index);
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
        std::sort(all_nodes.begin(), all_nodes.end(), 
            [](const Node& l, const Node& r) -> bool
            {
                return l.index < r.index;
            });
    }

    std::vector<std::string>& DFS()
    {
        time = 0;
        for(Node& n : all_nodes)
        {
            if(n.color == Color::WHITE)
                DFS_Visit(n);
        }
        return list;
    }
};
