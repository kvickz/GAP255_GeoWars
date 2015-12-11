//StringMerger.cpp

#include "StringMerger.h"

//This is just kind of a hacky solution
std::string StringMerger::StringWithInt(std::string str, int integer)
{
    std::string newString;

    char numStr[21];

    sprintf_s(numStr, "%d", integer);

    newString = str + numStr;
    return newString;
}