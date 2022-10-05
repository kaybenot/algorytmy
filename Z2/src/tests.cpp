#include <PriorityQueue.hpp>
#include <iostream>
#include <string>
#include <sstream>

int main(int argc, char* argv[])
{
    PriorityQueue<std::string> pq(20);

    for(int i = 1; i < argc; i++)
    {
        std::string arg(argv[i]);
        arg.erase(0, 1);
        arg.erase(arg.size() - 1);
        std::string val = arg.substr(0, arg.find(','));
        arg.erase(0, arg.find(',') + 1);
        std::string prioritys = arg;
        int priority;
        std::stringstream(prioritys) >> priority;
        Element<std::string> el(val, priority);
        pq.InsertElement(el);
    }

    for(int i = 1; i < argc; i++)
        std::cout << pq.Pop().val() << ' ';
    std::cout << std::endl;

    return 0;
}
