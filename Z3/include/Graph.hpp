#pragma once
#include <string>
#include <fstream>
#include <vector>
#include <stdexcept>
#include <sstream>
#include <iostream>

class Edge
{
private:
public:
    int weight;
    int number;
};

class Node
{
private:
public:
    int number;
    std::vector<Edge> edges;
};

class Graph
{
private:
    std::vector<Node> list;
    std::vector<Node> all_nodes;

    bool contains_node(int i)
    {
        for(Node n : list)
        {
            if(n.number == i)
                return true;
        }
        return false;
    }

    bool contains_node_all(int i)
    {
        for(Node n : all_nodes)
        {
            if(n.number == i)
                return true;
        }
        return false;
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

            int node = std::atoi(seglist.at(0).c_str());
            int target = std::atoi(seglist.at(1).c_str());
            int weight = std::atoi(seglist.at(2).c_str());

            Edge e;
            e.number = target;
            e.weight = weight;

            if(!contains_node_all(node))
            {
                Node n;
                n.number = node;
                all_nodes.push_back(n);
            }
            if(!contains_node_all(target))
            {
                Node n;
                n.number = target;
                all_nodes.push_back(n);
            }
            for(Node& n : all_nodes)
            {
                if(n.number == node)
                    n.edges.push_back(e);
                if(n.number == target)
                {
                    Edge ed;
                    ed.number = node;
                    ed.weight = weight;
                    n.edges.push_back(ed);
                }
            }
            
            if(!contains_node(node))
            {
                Node n;
                n.number = node;
                list.push_back(n);
            }
            for(Node& n : list)
            {
                if(n.number == node)
                    n.edges.push_back(e);
            }
        }
        f.close();
    }

    void to_dot(std::string filename)
    {
        std::ofstream f(filename);
        f << "digraph {\n";
        for(Node n : list)
        {
            for(Edge e : n.edges)
                f << "  " << n.number << " -> " << e.number << "[label=\"" << e.weight << "\"];\n";
        }
        f << "}\n";
        f.close();
    }

    void is_complete()
    {
        bool complete = true;

        size_t edges = 0;
        for(Node n : list)
            edges += n.edges.size();

        if(edges != all_nodes.size() * (all_nodes.size() - 1) / 2)
            complete = false;

        for(Node n : all_nodes)
        {
            if(n.edges.size() != all_nodes.size() - 1)
                complete = false;
        }

        if(complete)
            std::cout << "graph is complete" << std::endl;
        else
            std::cout << "graph is not complete" << std::endl;
    }
};
