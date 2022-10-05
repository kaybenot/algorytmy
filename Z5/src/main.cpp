#include <Graph.hpp>
#include <cstdlib>

std::string remove_extension(const std::string& filename) {
    size_t lastdot = filename.find_last_of(".");
    if (lastdot == std::string::npos) return filename;
    return filename.substr(0, lastdot); 
}

int main(int argc, char* argv[])
{
    Graph g;

    if(argc < 2)
    {
        std::cout << "./program [csv]" << std::endl;
        return 1;
    }

    std::string path(argv[1]);

    g.read_graph(path);
    std::vector<std::string> list = g.DFS();

    for(std::string& s : list)
        std::cout << s << ' ';

    return 0;
}
