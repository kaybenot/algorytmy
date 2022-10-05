#include "Graph.hpp"

#include <iostream>
#include <cstdlib>

int main(int argc, char* argv[])
{
    int n;
    std::cin >> n;
    Graph g(n);
    for(int i = 1; i <= n; i++)
    {
        int key;
        std::cin >> key;
        g.add_edge(i, key);
    }

    std::cout << g.count() << std::endl;

    return 0;
}
