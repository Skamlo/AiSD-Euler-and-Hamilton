#include <iostream>
#include <vector>
#include <algorithm>
#include <chrono>
#include <random>
#include <queue>
#include <stack>

#include "graph.h"
#include "actions.h"

#define PLACEHOLDER 0
#define HAMILTON 1
#define NON_HAMILTON 2

std::vector<std::vector<int>> Graph::createMatrix(int rows, int cols)
{
    return std::vector<std::vector<int>>(rows, std::vector<int>(cols));
}

std::vector<int> Graph::generateShuffledVector(int n)
{
    std::vector<int> vec(n, 0);
    for (int i = 0; i < n; i++)
        vec[i] = i;

    // Initialize random number generator
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::mt19937 g(seed);

    // Shuffle the vector
    shuffle(vec.begin(), vec.end(), g);

    return vec;
}

std::vector<int> Graph::generateUniqueNumbers(int n, int k)
{
    if (k > n || n <= 0 || k <= 0)
    {
        std::cout << "Error: Number of unique numbers required exceeds the range.\n";
        return std::vector<int>();
    }

    std::vector<int> vec = generateShuffledVector(n);

    std::vector<int> outputVector(k, 9);
    for (int i = 0; i < k; i++)
        outputVector[i] = vec[i];

    return outputVector;
}

bool Graph::checkIfNums(std::string s)
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
    if (!checkIfNums(nNodesStr))
        return false;
    nNodes = strToInt(nNodesStr);
    this->nodesNumber = nNodes;

    // read saturation
    std::string saturationStr;
    int saturation = 0;
    std::cout << "saturation> ";
    std::getline(std::cin, saturationStr);
    if (!checkIfNums(saturationStr))
        return false;
    saturation = strToInt(saturationStr);
    this->saturationForBenchmark = saturation;
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
        for (int i = 0; i < nNodes - 1; i++)
        {
            if (hamiltonPath[i] > hamiltonPath[i + 1])
                this->matrix[hamiltonPath[i + 1]][hamiltonPath[i]] = 1;
            else
                this->matrix[hamiltonPath[i]][hamiltonPath[i + 1]] = 1;
        }
        if (hamiltonPath[nNodes - 1] > hamiltonPath[0])
            this->matrix[hamiltonPath[0]][hamiltonPath[nNodes - 1]] = 1;
        else
            this->matrix[hamiltonPath[nNodes - 1]][hamiltonPath[0]] = 1;

        int nNodesInUpperTriangle = nNodes * (nNodes - 1) / 2;
        int nNodesToFill = nNodesInUpperTriangle * saturation / 100;
        nNodesToFill -= nNodes;

        if (nNodesToFill <= 0)
            return true;

        std::vector<int> indexes = this->generateUniqueNumbers(nNodesInUpperTriangle - nNodes, nNodesToFill);

        for (int i = 0; i < indexes.size(); i++)
        {
            int nOnes = 0;
            int nCells = 0;
            bool flag = true;
            for (int row = 0; row < nNodes - 1; row++)
            {
                if (!flag)
                    break;

                for (int col = row + 1; col < nNodes; col++)
                {
                    if (this->matrix[row][col] == 1)
                    {
                        nOnes++;
                    }
                    if (this->matrix[row][col] == 0)
                    {
                        nCells++;
                    }
                    if (nCells > indexes[i])
                    {
                        flag = false;
                        break;
                    }
                }
            }
            indexes[i] += nOnes;
        }

        for (int index : indexes)
        {
            int yPos = 0;
            int xPos = 0;
            int tracker = 0;
            for (int i = nNodes - 1; i > 0; i--)
            {
                if (tracker + i > index)
                {
                    xPos = yPos + index - tracker + 1;
                    break;
                }
                else
                {
                    yPos++;
                    tracker += i;
                }
            }

            this->matrix[yPos][xPos] = 1;
        }
    }
    else if (inputMode == NON_HAMILTON)
    {
        int nNodesInUpperTriangle = nNodes * (nNodes - 1) / 2;
        int nNodesToFill = nNodesInUpperTriangle * saturation / 100;

        if (nNodesToFill <= 0)
            return true;

        std::vector<int> indexes = this->generateUniqueNumbers(nNodesInUpperTriangle, nNodesToFill);

        for (int index : indexes)
        {
            int yPos = 0;
            int xPos = 0;
            int tracker = 0;
            for (int i = nNodes - 1; i > 0; i--)
            {
                if (tracker + i > index)
                {
                    xPos = yPos + index - tracker + 1;
                    break;
                }
                else
                {
                    yPos++;
                    tracker += i;
                }
            }

            this->matrix[yPos][xPos] = 1;
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

        for (int c = 0; c < this->matrix.size(); c++)
        {
            if (this->matrix[r][c] == 1 || this->matrix[c][r] == 1)
            {
                row.push_back(c + 1);
            }
        }

        this->list.push_back(row);
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
    int spacesBefore = countDigits(this->matrix.size());

    // title bar
    for (int i = 0; i < spacesBefore; i++)
        std::cout << " ";
    std::cout << " |";
    for (int i = 1; i <= this->matrix.size(); i++)
        std::cout << " " << i;

    // separator
    std::cout << std::endl;
    for (int i = 0; i < spacesBefore; i++)
        std::cout << "-";
    std::cout << "-+-";
    for (int i = 1; i <= this->matrix.size(); i++)
        std::cout << "--";

    // values
    std::cout << "\n";
    for (int i = 0; i < this->matrix.size(); i++)
    {
        std::cout << i + 1;
        for (int j = 0; j < spacesBefore - countDigits(i + 1); j++)
            std::cout << " ";
        std::cout << " |";

        for (int j = 0; j < this->matrix.size(); j++)
        {
            for (int s = 0; s < countDigits(j + 1); s++)
            {
                std::cout << " ";
            }
            std::cout << this->matrix[i][j];
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

// HAMILTON CYCLE
bool Graph::findHamiltonCicle()
{
    matrix = this->matrix;
    for (int row = 0; row < matrix.size() - 1; row++)
    {
        for (int col = row + 1; col < matrix.size(); col++)
        {
            if (matrix[row][col] == 1)
                matrix[col][row] = 1;
        }
    }

    std::vector<int> path(matrix.size(), -1);
    path[0] = 0;

    if (this->hamiltonCycleUtil(matrix, path, 1))
    {
        std::cout << "Hamilton cycle: ";
        for (int node : path)
            std::cout << node << " ";
        std::cout << path[0] << std::endl;
        return true;
    }
    else
    {
        std::cout << "Solution does not exist\n";
        return false;
    }
}

bool Graph::hamiltonCycleUtil(std::vector<std::vector<int>> &matrix, std::vector<int> &path, int pos)
{
    if (pos == matrix.size())
    {
        if (matrix[path[pos - 1]][path[0]] == 1)
            return true;
        else
            return false;
    }

    for (int node = 1; node < matrix.size(); node++)
    {
        if (this->isSafeHamilton(node, matrix, path, pos))
        {
            path[pos] = node;

            if (this->hamiltonCycleUtil(matrix, path, pos + 1))
                return true;

            path[pos] = -1;
        }
    }

    return false;
}

bool Graph::isSafeHamilton(int node, std::vector<std::vector<int>> &matrix, std::vector<int> &path, int pos)
{
    if (matrix[path[pos - 1]][node] == 0)
        return false;

    for (int i = 0; i < pos; i++)
        if (path[i] == node)
            return false;

    return true;
}

// EULER CYCLE
void Graph::findEulerCicle()
{
}