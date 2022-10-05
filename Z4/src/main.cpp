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

    if(argc < 4)
    {
        std::cout << "./program [csv] [starting_vertex] [end_vertex1] ..." << std::endl;
        return 1;
    }

    std::string path(argv[1]);
    //std::string path("graph500.csv");

    g.read_graph(path);

    Graph bfs = g.BFS(std::string(argv[2]));
    //Graph bfs = g.BFS(1);
    for(int i = 3; i < argc; i++)
        std::cout << bfs.get_hops(std::string(argv[i])) << " ";

    return 0;
}
