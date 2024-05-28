#pragma once

#include <vector>
#include <string>

class Graph
{
public:
    // VARIABLES
    int nodesNumber = 0;
    std::vector<std::vector<int>> matrix;
    std::vector<std::vector<int>> list;

    // METHODS
    std::vector<std::vector<int>> createMatrix(int rows, int cols);
    bool checkNums(std::string s);
    bool generate(int inputMode);
    void print();
    void findEulerCicle();
    void findHamiltonCicle();
};
