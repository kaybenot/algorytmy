#include <vector>

class Vertex
{
public:
    int index = -1;
    std::vector<int> children;
    bool visited = false;
};

class Graph
{
private:
    size_t size;
    std::vector<Vertex> vertices;

    void DFS(Vertex& v)
    {
        if(v.visited)
            return;
        v.visited = true;
        for(int u : v.children)
            DFS(vertices.at(u));
    }
    
public:
    void add_edge(int from, int to)
    {
        vertices.at(from - 1).children.push_back(to - 1);
        vertices.at(to - 1).children.push_back(from - 1);
    }

    int count()
    {
        int ret = 0;
        for(int i = 0; i < size; i++)
        {
            Vertex& v = vertices.at(i);
            if(v.visited)
                continue;
            DFS(v);
            ret++;
        }

        return ret;
    }

    Graph(size_t size)
    {
        this->size = size;
        for(int i = 0; i < size; i++)
        {
            Vertex v;
            v.index = i;
            vertices.push_back(v);
        }
    }
};
