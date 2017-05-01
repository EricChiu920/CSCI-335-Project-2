#ifndef CHIU1_H
#define CHIU1_H

#include <iostream> //std::cout
#include <fstream> //std::ifstream std::ofstream
#include <string>
#include <vector>
#include <algorithm> //std::sort
#include <chrono> //timing

//City node. Has the amount of edges it connects to, what cities it connects to, and the coordiantes
struct city
{
	int edge1 = -1;
	int edge2 = -1;
	int edge_count = 0;
	double x = 0;
	double y = 0;
};
extern city globalCity; //Allow chiu2.h to include this header

//Distance Node to hold the distance between two cities and what two cities this distance is for.
struct eucl_distance
{
	double distance = 0;
	int a;
	int b;
};
extern eucl_distance globalEucl_distance;



//Takes a string as a parameter
//Returns 1 if string only contains numbers, 0 otherwise.
bool is_interger(const std::string string);

//Allows std::sort compare distance from eucl_distance struct
bool compareDistance(eucl_distance a, eucl_distance b);

//Prints the finished tsp cycle
void print_cycle(std::vector<city> cities, std::ofstream &myfile);

#endif // !CHIU1_H
