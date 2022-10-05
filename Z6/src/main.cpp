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

    g.read_graph(path);
    g.SilneSpojne();

    return 0;
}
