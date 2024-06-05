#include <iostream>
#include <vector>
#include <string>
#include <random>
#include <stack>
#include <queue>
#include <set>
#include "graph.h"
#include "actions.h"

std::string stringToLowercase(std::string text)
{
    for (auto &x : text)
    {
        x = tolower(x);
    }

    return text;
}

bool textValidation(std::string *numbers)
{
    // Performs preprocessing data such as removing spaces
    std::string newNumbers;
    int lastIndex = -1;
    for (int i = 0; i < numbers->size(); i++)
    {
        if ((*numbers)[i] == ' ')
        {
            if (lastIndex != -1)
            {
                if (newNumbers[lastIndex] != ' ')
                {
                    newNumbers += ' ';
                    lastIndex += 1;
                }
            }
        }
        else if ((*numbers)[i] >= '0' && (*numbers)[i] <= '9')
        {
            newNumbers += (*numbers)[i];
            lastIndex += 1;
        }
        else
        {
            return false;
        }
    }
    *numbers = newNumbers;
    return true;
}

int strToInt(std::string numberString)
{
    int numberInt = 0;
    for (int i = 0; i < numberString.length(); i++)
    {
        numberInt *= 10;
        numberInt += numberString[i] - '0';
    }
    return numberInt;
}

void convertNodes(std::vector<int> *ids, std::string numbers)
{
    int currentNumber = 0;
    bool anyNode = false;
    for (int i = 0; i < numbers.size(); i++)
    {
        if (numbers[i] == ' ')
        {
            ids->push_back(currentNumber);
            currentNumber = 0;
        }
        else if (numbers[i] >= '0' && numbers[i] <= '9')
        {
            anyNode = true;
            currentNumber = currentNumber * 10 + (numbers[i] - '0');
        }
    }

    if (anyNode)
        ids->push_back(currentNumber);
}

bool isValidValues(std::vector<int> &ids, int nNodes)
{
    for (int i = 0; i < ids.size(); i++)
    {
        if (ids[i] > nNodes)
            return false;
    }
    return true;
}

int countDigits(int number)
{
    int nDigits = 0;
    while (number > 0)
    {
        nDigits++;
        number /= 10;
    }
    return nDigits;
}