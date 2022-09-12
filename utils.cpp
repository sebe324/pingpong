#include "utils.h"
Utils::isPositive(float number){
if(number>=0) return 1;
else return -1;
}
Utils::clamp(int minimum, int value, int maximum){
    if(value<=minimum) return minimum;
    else if(value>=maximum) return maximum;
    else return value;
}
