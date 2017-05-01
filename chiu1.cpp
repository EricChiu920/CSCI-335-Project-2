//Created by: Eric Chiu
//For CSCI 335 Project 2.
//TSP approximations using greedy algorithms.

#include "chiu1.h"
#include "chiu2.h"
#include "chiu3.h"
#include "chiu4.h"

int main(int argc, char* argv[])
{
	std::ifstream country_txt(argv[1]);
	std::ofstream greedy_txt;// ("chiu1.txt");
	std::ofstream iterative_txt("chiu2.txt");
	std::ofstream insertion_txt("chiu3.txt");
	std::string line; //Hold a getline
	std::string wanted_line; //Line I wanted to search for.
	std::string temp; //Hold a string
	double num;
	double total_distance = 0;

	greedy_txt.open("chiu1.txt");

	std::vector<city> cities;
	city a_city;

	if (!country_txt.is_open()) //Check if file can be opened.
	{
		std::cerr << "Error opening file.\n";
		return -1;
	}

	wanted_line = "locations in"; //Search for amount of cities in which country.
	while (std::getline(country_txt, line))
	{
		if (line.find(wanted_line) != std::string::npos)
		{
			line = line.substr(9);
			std::cout << "Performing TSP approximation algorithms on: " << line << std::endl << std::endl;
			break;
		}
	}

	wanted_line = "NODE_COORD_SECTION"; //Find coordinates
	while (std::getline(country_txt, line))
	{
		if (line.find(wanted_line) != std::string::npos)
		{
			while (country_txt.eof() != 1)
			{
				country_txt >> temp;
				if (is_interger(temp)) //Check if next line is another city or not
				{
					country_txt >> num;
					a_city.x = num;
					country_txt >> num;
					a_city.y = num;
					cities.push_back(a_city);
				}
			}
		}
	}

	greedy_txt << "TSP approximation order of greedy algorithm." << std::endl;
	std::cout << "Running a greedy algorithms takes takes all the edges of shortest distance first.\n";
	auto start = std::chrono::steady_clock::now(); //Start timing the runtime of the method
	print_cycle(greedy(cities, total_distance), greedy_txt);
	std::cout << "The total distance is: " << total_distance << std::endl;
	auto end = std::chrono::steady_clock::now(); //End timing
	auto diff = end - start; //Store time
	std::cout << " Runtime of this TSP approximation algorithm: " << std::chrono::duration <double, std::milli>(diff).count() << "ms\n\n"; //Print runtime

	total_distance = 0;

	iterative_txt << "TSP approximation order of iterative improvement algorithm." << std::endl;
	std::cout << "Running iterative_improvement greedy algorithm\n";
	start = std::chrono::steady_clock::now(); //Start timing the runtime of the method
	print_cycle(iterative_improvement(greedy(cities, total_distance), total_distance), iterative_txt);
	std::cout << "The total distance is: " << total_distance << std::endl;
	end = std::chrono::steady_clock::now(); //End timing
	diff = end - start; //Store time
	std::cout << " Runtime of this TSP approximation algorithm: " << std::chrono::duration <double, std::milli>(diff).count() << "ms\n\n"; //Print runtime

	insertion_txt << "TSP approximation order of nearest insertion algorithm." << std::endl;
	std::cout << "Running nearest insertion greedy algorithm\n";
	start = std::chrono::steady_clock::now(); //Start timing the runtime of the method
	print_cycle(nearest_insertion(cities), insertion_txt);
	end = std::chrono::steady_clock::now(); //End timing
	diff = end - start; //Store time
	std::cout << " Runtime of this TSP approximation algorithm: " << std::chrono::duration <double, std::milli>(diff).count() << "ms\n"; //Print runtime

	country_txt.close();

	return 0;
}

bool is_interger(const std::string s)
{
	return (s.find_first_not_of("0123456789") == std::string::npos);
}

bool compareDistance(eucl_distance a, eucl_distance b)
{
	return (a.distance < b.distance);
}

void print_cycle(std::vector<city> cities, std::ofstream &myfile)
{
	int previous = 0;
	int next = 0;

	std::cout << "The TSP approximation order is written to chiu.txt" << std::endl;

	for (int i = 0; i < cities.size() + 1; i++)
	{
		if (cities.at(next).edge1 != previous)
		{
			myfile << cities.at(next).edge1 + 1 << std::endl;
			previous = next;
			next = cities.at(previous).edge1;
		}
		else
		{
			myfile << cities.at(next).edge2 + 1 << std::endl;
			previous = next;
			next = cities.at(previous).edge2;
		}
	}

	myfile.close();
}