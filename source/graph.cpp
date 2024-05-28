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

std::vector<int> Graph::generateUniqueNumbers(int n, int k)
{
    // Check if the range is smaller than the number of required unique numbers
    if (k > n + 1)
    {
        std::cout << "Error: Number of unique numbers required exceeds the range.\n";
        return std::vector<int>();
    }

    // Create a vector to hold the generated numbers
    std::vector<int> numbers(n + 1);
    for (int i = 0; i <= n; ++i)
    {
        numbers[i] = i;
    }

    // Shuffle the vector
    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(numbers.begin(), numbers.end(), g);

    // Take first k elements
    std::vector<int> result(numbers.begin(), numbers.begin() + k);

    return result;
}

std::vector<int> Graph::generateShuffledVector(int n) {
    // Create a vector with values from 0 to n-1
    std::vector<int> vec(n);
    for (int i = 0; i < n; ++i) 
    {
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
    this->matrix = createMatrix(nNodes, nNodes);

    if (inputMode == HAMILTON)
    {
        std::vector<int> hamiltonPath = this->generateShuffledVector(nNodes);
        for (int i=0; i<nNodes-1; i++)
        {
            if(hamiltonPath[i] > hamiltonPath[i+1])
                this->matrix[hamiltonPath[i+1]][hamiltonPath[i]] = 1;
            else
                this->matrix[hamiltonPath[i]][hamiltonPath[i+1]] = 1;
        }
        if (hamiltonPath[nNodes-1] > hamiltonPath[0])
            this->matrix[hamiltonPath[0]][hamiltonPath[nNodes-1]] = 1;
        else
            this->matrix[hamiltonPath[nNodes-1]][hamiltonPath[0]] = 1;

        int nNodesInUpperTriangle = nNodes * (nNodes - 1) / 2 - nNodes;
        int nNodesToFill = nNodesInUpperTriangle * saturation / 100;

        if (nNodesToFill <= 0)
            return true;

        std::vector<int> indexes = this->generateUniqueNumbers(nNodesInUpperTriangle - 1, nNodesToFill);

        for (int i = 0; i < indexes.size(); i++)
        {
            int nHamiltonNodesFilled = 0;
            for (int r=0; r<nNodes; r++)
            {
                for (int c=0; c<nNodes; c++)
                {
                    if (this->matrix[r][r + 1 + c] == 1)
                        nHamiltonNodesFilled++;
                }
            }

            indexes[i] += nHamiltonNodesFilled;

            for (int j = 0; j < nNodes - 1; j++)
            {
                if (indexes[i] + 1 < nNodes - 1 - j)
                {
                    this->matrix[j][j + 2 + indexes[i]] = 1;
                    break;
                }
                else
                {
                    indexes[i] -= (nNodes - 1 - j);
                }
            }
        }
    }
    else if (inputMode == NON_HAMILTON)
    {
        int nNodesInUpperTriangle = nNodes * (nNodes - 1) / 2;
        int nNodesToFill = nNodesInUpperTriangle * saturation / 100;

        if (nNodesToFill <= 0)
            return true;

        std::vector<int> indexes = this->generateUniqueNumbers(nNodesInUpperTriangle - 1, nNodesToFill);

        for (int i = 0; i < indexes.size(); i++)
        {
            for (int j = 0; j < nNodes - 1; j++)
            {
                if (indexes[i] + 1 < nNodes - 1 - j)
                {
                    this->matrix[j][j + 2 + indexes[i]] = 1;
                    break;
                }
                else
                {
                    indexes[i] -= (nNodes - 1 - j);
                }
            }
        }
    }

    this->generateList();

    return true;
}

void Graph::generateList()
{
    for (int r = 0; r < this->matrix.size(); r++)
    {
        std::vector<int> row;

        for (int c = 0; c < matrix.size(); c++)
        {
            if (matrix[r][c] == 1)
            {
                row.push_back(c + 1);
            }
        }

        list.push_back(row);
    }
}

void Graph::print(std::string type)
{
    if (type == "matrix")
        this->printMatrix();
    else if (type == "list")
        this->printList();
}

void Graph::printMatrix()
{
    int spacesBefore = countDigits(matrix.size());

    // title bar
    for (int i=0; i<spacesBefore; i++)
        std::cout << " ";
    std::cout << " |";
    for (int i = 1; i <= matrix.size(); i++)
        std::cout << " " << i;

    // separator
    std::cout << std::endl;
    for (int i=0; i<spacesBefore; i++)
        std::cout << "-"; 
    std::cout << "-+-";
    for (int i = 1; i <= matrix.size(); i++)
        std::cout << "--";

    // values
    std::cout << "\n";
    for (int i = 0; i < matrix.size(); i++)
    {
        std::cout << i + 1;
        for (int j=0; j<spacesBefore-countDigits(i + 1); j++)
            std::cout << " ";
        std::cout << " |";

        for (int j = 0; j < matrix.size(); j++)
        {
            for (int s = 0; s < countDigits(j + 1); s++)
            {
                std::cout << " ";
            }
            std::cout << matrix[i][j];
        }
        std::cout << "\n";
    }
}

void Graph::printList()
{
    for (int i = 0; i < this->list.size(); i++)
    {
        std::cout << i + 1 << ">";
        for (int j = 0; j < list[i].size(); j++)
        {
            std::cout << " " << list[i][j];
        }
        std::cout << "\n";
    }
}

void Graph::findEulerCicle()
{

}

void Graph::findHamiltonCicle()
{

}
