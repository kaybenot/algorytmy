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
    Node* parent = nullptr;
    Color color = Color::WHITE;
    int d = -1;
    int f = -1;
};

class Edge
{
private:
public:
    std::string start;
    std::string target;
};

class Graph
{
private:
    std::vector<Node> all_nodes;
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
    }

    void DFS()
    {
        silne = 0;
        for(Node& n : all_nodes)
        {
            n.color = Color::WHITE;
            n.parent = nullptr;
        }
        time = 0;
        for(Node& n : all_nodes)
        {
            if(n.color == Color::WHITE)
            {
                DFS_Visit(n);
                silne++;
            }
        }
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
            if((line == "digraph {") || (line == "}") || line == "")
                continue;

            std::string delimiter = "->";

            size_t pos = 0;
            std::string token;

            // Left
            std::string left;
            pos = line.find(delimiter);
            token = line.substr(0, pos);
            token.erase(std::remove_if(token.begin(), token.end(), std::isspace), token.end());
            left = token;
            line.erase(0, pos + delimiter.length());

            // Right
            std::string right;
            line.erase(std::remove_if(line.begin(), line.end(), std::isspace), line.end());
            line.pop_back();
            right = line;

            std::string node = left;
            std::string target = right;

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

            for(Node& n : all_nodes)
            {
                if(n.index == node)
                    n.edges.push_back(e);
            }
        }
        f.close();
        /*std::sort(all_nodes.begin(), all_nodes.end(), 
            [](const Node& l, const Node& r) -> bool
            {
                return l.index < r.index;
            });*/
    }

    void SilneSpojne()
    {
        DFS();
        std::vector<Edge> edges;
        for(Node& n : all_nodes)
        {
            for(Edge& e : n.edges)
            {
                e.start = e.target;
                e.target = n.index;
                edges.push_back(e);
            }
            n.edges.clear();
        }
        for(Node& n : all_nodes)
            for(Edge& e : edges)
                if(e.start == n.index)
                    n.edges.push_back(e);
        std::sort(all_nodes.begin(), all_nodes.end(), 
            [](const Node& l, const Node& r) -> bool
            {
                return l.f > r.f;
            });
        DFS();
        std::cout << silne << std::endl;
    }
};
