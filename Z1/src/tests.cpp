#include <Set.hpp>
#include <string>

int isTwoSet(int argc, char* argv[])
{
    for(int i = 2; i < argc; i++)
        if(std::string(argv[i]) == ",")
            return i;
    return -1;
}

int main(int argc, char* argv[])
{
    std::string type = std::string(argv[1]);
    int twoSet = isTwoSet(argc, argv);
    if(type == "integer")
    {
        if(twoSet != -1)
        {
            Set<int> set1;
            Set<int> set2;
            for(int i = 2; i < twoSet; i++)
                set1.insert(atoi(argv[i]));
            for(int i = twoSet + 1; i < argc; i++)
                set2.insert(atoi(argv[i]));
            std::cout << "Difference = " << set1.difference(set2) << std::endl;
            std::cout << "Intersection = " << set1.intersection(set2) << std::endl;
            std::cout << "Union = " << set1.uni(set2) << std::endl;
            set1.popAll(set2);
            std::cout << "PopAll = " << set1 << std::endl;
        }
        else
        {
            Set<int> set;
            for(int i = 2; i < argc; i++)
                set.insert(atoi(argv[i]));
            std::cout << set;
        }
    }
    else if(type == "string")
    {
        if(twoSet != -1)
        {
            Set<std::string> set1;
            Set<std::string> set2;
            for(int i = 2; i < twoSet; i++)
                set1.insert(std::string(argv[i]));
            for(int i = twoSet + 1; i < argc; i++)
                set2.insert(std::string(argv[i]));
            std::cout << "Difference = " << set1.difference(set2) << std::endl;
            std::cout << "Intersection = " << set1.intersection(set2) << std::endl;
            std::cout << "Union = " << set1.uni(set2) << std::endl;
            set1.popAll(set2);
            std::cout << "PopAll = " << set1 << std::endl;
        }
        else
        {
            Set<std::string> set;
            for(int i = 2; i < argc; i++)
                set.insert(std::string(argv[i]));
            std::cout << set;
        }
    }
    else
        std::cout << "Obslugiwane typy to jedynie: integer, string" << std::endl;
    return 0;
}
