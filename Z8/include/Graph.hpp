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
#include <exception>

class Matrix
{
private:
    int* arr;

public:
    int rows;

    Matrix(int rows)
    {
        arr = new int[rows * rows];
        for(int i = 0; i < rows * rows; i++)
        {
            if(i % rows == (i / rows))
                arr[i] = 0;
            else
                arr[i] = INT_MAX;
        }
        this->rows = rows;
    }

    inline int get(int x, int y)
    {
        return arr[y * rows + x];
    }

    inline void set(int x, int y, int val)
    {
        arr[y * rows + x] = val;
    }
};

class Graph
{
private:
    Matrix *D;

    int max_size(std::string filename)
    {
        int size = 0;
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
            if(size < node)
                size = node;
            if(size < target)
                size = target;
        }
        f.close();
        return size;
    }

public:
    void read_graph(std::string filename)
    {
        int size = max_size(filename);
        D = new Matrix(size);
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
            D->set(target-1, node-1, weight);
        }
        f.close();
    }

    void floyd_warshall()
    {
        int n = D->rows;
        for(int k = 1; k <= n; k++)
        {
            for(int i = 1; i <= n; i++)
            {
                for(int j = 1; j <= n; j++)
                {
                    int dij = D->get(j-1, i-1);
                    int dik = D->get(k-1, i-1);
                    int dkj = D->get(j-1, k-1);
                    int val = 0;
                    if((dik == INT_MAX) || (dkj == INT_MAX))
                        val = std::min(dij, INT_MAX);
                    else
                         val = std::min(dij, dik + dkj);
                    D->set(j-1, i-1, val);
                }
            }
        }
    }

    int gl(int x, int y)
    {
        return D->get(y-1, x-1);
    }
};
