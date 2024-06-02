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
        if (!std::strcmp(argv[1], "-hamilton") || !std::strcmp(argv[1], "-h"))
            inputMode = HAMILTON;
        else if (!std::strcmp(argv[1], "-non-hamilton") || !std::strcmp(argv[1], "-nh"))
            inputMode = NON_HAMILTON;
        else if (!std::strcmp(argv[1], "-help"))
        {
            std::cout << "-h for hamilton graph\n-nh for non-hamilton graph" << std::endl;
            return 1;
        }
        else
        {
            std::cout << "You incorrect specify the input mode.\n"
                      << "Available modes are:\n"
                      << "\t-hamiltion\n"
                      << "\t-non-hamilton\n";
            return 1;
        }
    }
    else
    {
        std::cout << "You did not specify the input mode.\n"
                  << "Available modes are:\n"
                  << "\t-hamiltion\n"
                  << "\t-non-hamilton\n";
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
            graph.print("list");
        }
        else if (option == "print list" || option == "printlist" || option == "print-list")
        {
            graph.print("list");
        }
        else if (option == "print matrix" || option == "printmatrix" || option == "print-matrix")
        {
            graph.print("matrix");
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
                      << "Find euler      Find Euler cicle in graph and print it" << std::endl
                      << "Find hamilton   Find Hamilton cicle in graph and print it" << std::endl
                      << "Exit            Exits the program" << std::endl;
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
