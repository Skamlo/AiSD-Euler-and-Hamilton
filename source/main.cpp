#include <iostream>
#include <vector>
#include <cstring>
#include <string>
#include "graph.h"
#include "actions.h"

#define PLACEHOLDER 0
#define HAMILTON 1
#define NON_HAMILTON 2

int inputMode = PLACEHOLDER;

Graph graph;

int main(int argc, char *argv[])
{
    // input mode
    if (argc >= 2)
    {
        if (!std::strcmp(argv[1], "-hamiltion") || !std::strcmp(argv[1], "-g"))
            inputMode = HAMILTON;
        else if (!std::strcmp(argv[1], "-non-hamilton") || !std::strcmp(argv[1], "-up"))
            inputMode = NON_HAMILTON;
        else
        {
            std::cout << "You incorrect specify the input mode.\n";
            return 1;
        }
    }
    else
    {
        std::cout << "You did not specify the input mode.\n"
                  << std::endl;
        return 1;
    }

    if (!graph.generate(inputMode))
    {
        std::cout << "Graph generation failed.\n";
        return 1;
    }

    while (true)
    {
        std::string option;
        std::cout << "\naction> ";
        std::getline(std::cin, option);
        option = stringToLowercase(option);

        if (option == "print")
        {
            graph.print();
        }
        else if (option == "find euler" || option == "findeuler" || option == "find-euler")
        {
            graph.findEulerCicle();
        }
        else if (option == "find hamilton" || option == "findhamilton" || option == "find-hamilton")
        {
            graph.findHamiltonCicle();
        }
        else if (option == "help")
        {
            std::cout << "Help            Show this message" << std::endl
                      << "Print           Print the graph in a previously specified type" << std::endl
                      << "find euler      Find Euler cicle in graph and print it" << std::endl
                      << "find hamilton   Find Hamilton cicle in graph and print it" << std::endl;
        }
        else if (option == "exit")
        {
            break;
        }
        else
        {
            std::cout << "This command does not exist." << std::endl;
        }
    }

    return 0;
}
