#ifndef UTILS_H
#define UTILS_H

#include <sstream>

class Utils{
    public:
static int clamp(int minimum, int value, int maximum);
static int isPositive(float number); //if a number is positive or 0 returns 1, else returns -1
static int toHexInt(std::string str);
static int toInt(std::string str);
};
#endif
