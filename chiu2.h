#ifndef CHIU2_H
#define CHIU2_H

#include <vector>
#include <math.h> //pow
#include "chiu1.h"

//Takes a struct cities that has x and y coordinates as parameter.
//Returns TSP approximation using a greedy algorithm.
//Greedy algorithm takes all the shortest edges it can without making a cycle until the last city
//or having a city connect to more than two other cities.
std::vector<city> greedy(std::vector<city> cities, double &total_distance);

//Update edges connected to cities.
void add_edge(std::vector<city> &cities, std::vector <eucl_distance> &distances, int &i, int &j);

//Check if adding a edge would cause a cycle.
//Returns 1 if cycle 0 if not.
bool is_cycle(std::vector<city> cities, eucl_distance edge);

#endif // !CHIU2_H

