#include <iostream>
#include <vector>
#include <algorithm>
#include <chrono>
#include <random>

#include "graph.h"
#include "actions.h"

#define PLACEHOLDER 0
#define HAMILTON 1
#define NON_HAMILTON 2

std::vector<std::vector<int>> Graph::createMatrix(int rows, int cols)
{
    return std::vector<std::vector<int>>(rows, std::vector<int>(cols));
}

std::vector<int> generateShuffledVector(int n) {
    // Create a vector with values from 0 to n-1
    std::vector<int> vec(n);
    for(int i = 0; i < n; ++i) {
        vec[i] = i;
    }

    // Obtain a random number generator based on a random device
    std::random_device rd;
    std::mt19937 g(rd());

    // Shuffle the vector using the random number generator
    std::shuffle(vec.begin(), vec.end(), g);

    return vec;
}


bool Graph::checkNums(std::string s)
{
    bool isAll = true;

    for (auto c : s)
    {
        if (!(c >= '0' && c <= '9'))
        {
            isAll = false;
        }
    }
    return isAll;
}

bool Graph::generate(int inputMode)
{
    // read number of nodes in graph
    std::string nNodesStr;
    int nNodes = 0;
    std::cout << "     nodes> ";
    std::getline(std::cin, nNodesStr);
    if (!checkNums(nNodesStr))
        return false;
    nNodes = strToInt(nNodesStr);
    this->nodesNumber = nNodes;

    // read saturation
    std::string saturationStr;
    int saturation = 0;
    std::cout << "saturation> ";
    std::getline(std::cin, saturationStr);
    if (!checkNums(saturationStr))
        return false;
    saturation = strToInt(saturationStr);

    // check if saturation is in correct range
    if (saturation < 0 || saturation > 100)
    {
        std::cout << "Saturation must be between 0 and 100.\n";
        return false;
    }

    // create graph
    // do some magic
}

void Graph::print()
{

}

void Graph::findEulerCicle()
{

}

void Graph::findHamiltonCicle()
{

}
