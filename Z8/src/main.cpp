#include <Graph.hpp>

int main(int argc, char* argv[])
{
    Graph g;

    if(argc < 2)
    {
        std::cout << "./my_program [csv]" << std::endl;
        return 1;
    }

    std::string path(argv[1]);
    try {
        g.read_graph(path);
    } catch (std::exception& e)
    {
        std::cerr << e.what() << std::endl;
        return 1;
    }
    g.floyd_warshall();
    for(int i = 2; i < argc; i++)
    {
        std::string p(argv[i]);
        std::vector<std::string> seglist;
        std::stringstream seg(p);
        std::string segment;
        while(std::getline(seg, segment, ','))
            seglist.push_back(segment);

        int node = std::atoi(seglist.at(0).c_str());
        int target = std::atoi(seglist.at(1).c_str());

        std::cout << g.gl(node, target) << ' ';
    }
    std::cout << std::endl;

    return 0;
}
