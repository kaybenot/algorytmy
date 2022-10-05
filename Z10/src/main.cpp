#include <Graph.hpp>
#include <chrono>

int main(int argc, char* argv[])
{
    Graph orginal;
    Graph forest;

    if(argc < 2)
    {
        std::cout << "./my_program [csv]" << std::endl;
        return 1;
    }

    std::string path(argv[1]);
    try {
        orginal.read_graph(path);
        forest.copy_contents(orginal);
    } catch (std::exception& e)
    {
        std::cerr << e.what() << std::endl;
        return 1;
    }
    auto start_org = std::chrono::high_resolution_clock::now();
    float org_w = orginal.kruskal();
    auto end_org = std::chrono::high_resolution_clock::now();

    auto start_w = std::chrono::high_resolution_clock::now();
    float for_w = forest.kruskal2();
    auto end_w = std::chrono::high_resolution_clock::now();

    std::cout << "ORGINAL: " << std::chrono::duration<double>(end_org - start_org).count() << ", WEIGHT: " << org_w << std::endl;
    std::cout << "FOREST: " << std::chrono::duration<double>(end_w - start_w).count() << ", WEIGHT: " << for_w << std::endl;

    return 0;
}
