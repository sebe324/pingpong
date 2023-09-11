#ifndef UTILS_H
#define UTILS_H

#include <sstream>

namespace Utils{
int clamp(int minimum, int value, int maximum);
int isPositive(float number); //if a number is positive or 0 returns 1, else returns -1
int toHexInt(std::string str);
int toInt(std::string str);
};
#endif
