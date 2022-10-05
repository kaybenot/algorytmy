#include <Graph.hpp>

int main(int argc, char* argv[])
{
    Graph g;

    if(argc < 2)
    {
        std::cout << "./my_program [dot]" << std::endl;
        return 1;
    }

    std::string path(argv[1]);
    std::string start(argv[2]);

    g.read_graph(path);
    bool bf = g.bellman_ford(start);

    if(bf)
        std::cout << "TRUE" << std::endl;
    else
        std::cout << "FALSE" << std::endl;
    
    for(auto i : g.poprzednik)
        std::cout << '(' << i.first << ',' << i.second << ") ";
    std::cout << std::endl;

    for(auto i : g.dlugosc)
    {
        if(i.second == INT_MAX)
            std::cout << '(' << i.first << ',' << "inf" << ") ";
        else
            std::cout << '(' << i.first << ',' << i.second << ") ";
    }
    std::cout << std::endl;

    return 0;
}
