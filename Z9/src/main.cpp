#include <Graph.hpp>

int main(int argc, char* argv[])
{
    Graph g;

    if(argc < 3)
    {
        std::cout << "./my_program [csv] [out]" << std::endl;
        return 1;
    }

    std::string path(argv[1]);
    std::string path_out(argv[2]);
    try {
        g.read_graph(path);
    } catch (std::exception& e)
    {
        std::cerr << e.what() << std::endl;
        return 1;
    }
    g.kruskal();
    g.save_graph(path_out);

    return 0;
}
