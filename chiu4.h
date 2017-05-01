#ifndef CHIU4_H
#define CHIU4_h

#include <vector>
#include <math.h> //pow
#include "chiu1.h"

//Take a finished tour and try to improve it by taking two edges away and seeing if another
//combinations of those four cities result in a shorter tour to improve it.
std::vector<city> iterative_improvement(std::vector<city> cities, double &total_distance);

#endif