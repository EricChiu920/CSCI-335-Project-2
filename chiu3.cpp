#include "chiu3.h"

std::vector<city> nearest_insertion(std::vector<city> cities)
{
	std::vector<std::vector<double>> adjacency_matrix(cities.size(), std::vector<double>(cities.size()));
	std::vector<double> list_of_shortest_distance(cities.size(), std::numeric_limits<double>::max());
	double total_distance = 0;
	double min;
	int subtour_size = 0;
	int city1;
	int city2;


	//START CREATE STARTING SUBTOUR
	//START CREATE STARTING SUBTOUR

	//Make a adjacency matrix of distances
	for (int i = 0; i < cities.size(); i++)
	{
		for (int j = 0; j < cities.size(); j++)
		{
			adjacency_matrix.at(i).at(j) = sqrt(pow(cities.at(i).x - cities.at(j).x, 2.0) + pow(cities.at(i).y - cities.at(j).y, 2.0));
		}
	}

	//set min to first distance in adjacency matrix
	min = adjacency_matrix.at(0).at(1);
	city1 = 0;
	city2 = 1;

	//Find the minimum distance in adjacency matrix
	for (int i = 0; i < cities.size(); i++)
	{
		for (int j = i + 1; j < cities.size(); j++)
		{
			if ((adjacency_matrix.at(i).at(j) > 0) && (adjacency_matrix.at(i).at(j) < min))
			{
				min = adjacency_matrix.at(i).at(j);
				city1 = i;
				city2 = j;
			}
		}
	}

	total_distance += adjacency_matrix.at(city1).at(city2) * 2;

	//Make a list of shortest distances from every city not in the subtour to any city in our subtour
	for (int i = 0; i < cities.size(); i++)
	{
		if (adjacency_matrix.at(i).at(city1) < adjacency_matrix.at(i).at(city2))
		{
			list_of_shortest_distance.at(i) = adjacency_matrix.at(i).at(city1);
		}
		else
		{
			list_of_shortest_distance.at(i) = adjacency_matrix.at(i).at(city2);
		}
	}

	//Updates edges of starting subtour
	cities.at(city1).edge1 = city2;
	cities.at(city1).edge2 = city2;
	cities.at(city2).edge1 = city1;
	cities.at(city2).edge2 = city1;
	list_of_shortest_distance.at(city1) = std::numeric_limits<double>::max();
	list_of_shortest_distance.at(city2) = std::numeric_limits<double>::max();
	subtour_size += 2;

	//END CREATE STARTING SUBTOUR
	//END CREATE STARTING SUBTOUR

	//Add cities to our subtour until it becomes a complete tour.
	for(; subtour_size < cities.size(); subtour_size++)
	{
		add_edge(cities, find_min_distance(list_of_shortest_distance, adjacency_matrix), subtour_size, adjacency_matrix, total_distance);
	}

	std::cout << "The total distance is: " << total_distance << std::endl;

	return cities;
}

void add_edge(std::vector<city> &cities, int a, int size, std::vector<std::vector<double>> adjacency_matrix, double &total_distance)
{
	int city1;
	int city2;

	//Find first edge at subtour
	for (int i = 0; i < cities.size(); i++)
	{
		if (cities.at(i).edge1 != -1)
		{
			city1 = i;
			city2 = cities.at(i).edge1;
			break;
		}
	}

	int previous = city1;
	int min_position1 = city1;
	int min_position2 = city2;
	
	//Find the edge the city should be added between.
	double min = adjacency_matrix.at(city1).at(a) + adjacency_matrix.at(city2).at(a) - adjacency_matrix.at(city1).at(city2);


	for (int i = 1; i < size; i++)
	{
		//Go to next edge.
		city1 = city2;
		if (cities.at(city2).edge1 != previous)
		{
			city2 = cities.at(city2).edge1;
		}
		else
		{
			city2 = cities.at(city2).edge2;
		}
		previous = city1;

		//Find shortest edge to insert city
		if ((adjacency_matrix.at(city1).at(a) + adjacency_matrix.at(city2).at(a) - adjacency_matrix.at(city1).at(city2)) < min)
		{
			min = adjacency_matrix.at(city1).at(a) + adjacency_matrix.at(city2).at(a) - adjacency_matrix.at(city1).at(city2);
			min_position1 = city1;
			min_position2 = city2;
		}
	}

	//Update edges
	cities.at(a).edge1 = city1;
	cities.at(a).edge2 = city2;
	if (cities.at(city1).edge1 == city2)
	{
		cities.at(city1).edge1 = a;
	}
	else
	{
		cities.at(city1).edge2 = a;
	}
	if (cities.at(city2).edge1 == city1)
	{
		cities.at(city2).edge1 = a;
	}
	else
	{
		cities.at(city2).edge2 = a;
	}

	total_distance += adjacency_matrix.at(city1).at(a) + adjacency_matrix.at(city2).at(a) - adjacency_matrix.at(city1).at(city2);
}

int find_min_distance(std::vector<double> &list, std::vector<std::vector<double>> adjacency_matrix)
{
	double min = list.at(0);
	int position = 0;

	for (int i = 1; i < list.size(); i++)
	{
		if (list.at(i) < min)
		{
			min = list.at(i);
			position = i;
		}
	}

	//Remove city from the list.
	list.at(position) = std::numeric_limits<double>::max();

	//Update list to see if other cities are closer to the city to be
	//added than the other cities already in the subtour.
	for (int i = 0; i < list.size(); i++)
	{
		//Don't update city if it's a city in the subtour
		if (list.at(i) != std::numeric_limits<double>::max())
		{
			//Update shortest distance if it's shorter than before.
			if (adjacency_matrix.at(i).at(position) < list.at(i))
			{
				list.at(i) = adjacency_matrix.at(i).at(position);
			}
		}
	}

	return position;
}