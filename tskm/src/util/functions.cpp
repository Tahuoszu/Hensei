/**
 *
 * @file    functions.cpp
 * @brief	
 * @author  Henri NG
 * @version 0.1
 * @date    08/04/2014
 *
 */

#include "functions.h"

string intToString(int num)
{
    string str;
    std::ostringstream convert;
    convert << num;
    str = convert.str();
    return str;
}

int duration(int x, int y)
{
    return y - x + 1;
}

int randomNumber(int range)
{
    int r = (rand() % range + 1);
    return r;
}
