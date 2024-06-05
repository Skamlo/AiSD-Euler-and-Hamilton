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
    int saturationForBenchmark = 0;

    // METHODS
    std::vector<std::vector<int>> createMatrix(int rows, int cols);
    std::vector<int> generateUniqueNumbers(int n, int k);
    std::vector<int> generateShuffledVector(int n);
    bool checkIfNums(std::string s);
    bool generate(int inputMode);
    void generateList();

    void print(std::string type);
    void printMatrix();
    void printList();

    bool findHamiltonCicle();
    bool hamiltonCycleUtil(std::vector<std::vector<int>> &matrix, std::vector<int> &path, int pos);
    bool isSafeHamilton(int node, std::vector<std::vector<int>> &matrix, std::vector<int> &path, int pos);

    void findEulerCicle();
};
