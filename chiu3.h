#ifndef CHIU3_H
#define CHIU3_H

#include <iostream>
#include <vector>
#include <limits> //std::numerical_limits<int>::max(); Set a int to its max value.
#include "chiu1.h"

//TSP approximation greedy algorithm using nearest insertion.
std::vector<city> nearest_insertion(std::vector<city> cities);

//Adds a edge to the subtour.
void add_edge(std::vector<city> &cities, int a, int size, std::vector<std::vector<double>> adjacency_matrix, double &total_distance);

//Takes the list of lowest distances for each city.
//Returns the position of the closest city.
int find_min_distance(std::vector<double> &list, std::vector<std::vector<double>> adjacency_matrix);

#endif // !CHIU3_H
