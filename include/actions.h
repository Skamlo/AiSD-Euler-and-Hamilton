#pragma once

#include <vector>
#include <string>
#include "graph.h"

std::string stringToLowercase(std::string text);
bool textValidation(std::string *numbers);
int strToInt(std::string numberString);
void convertNodes(std::vector<int> *ids, std::string numbers);
bool isValidValues(std::vector<int> &ids, int nNodes);
int countDigits(int number);
