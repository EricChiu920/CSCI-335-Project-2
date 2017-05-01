#include "chiu2.h"

std::vector<city> greedy(std::vector<city> cities, double &total_distance)
{
	std::vector<eucl_distance> distances;
	eucl_distance a_distance;
	//double total_distance = 0;

	for (int i = 0; i < cities.size(); i++) //calculate distances between every city and every other city
	{
		for (int j = i+1; j < cities.size(); j++)
		{
			a_distance.distance = sqrt(pow(cities.at(i).x - cities.at(j).x, 2.0) + pow(cities.at(i).y - cities.at(j).y, 2.0));
			a_distance.a = i;
			a_distance.b = j;
			distances.push_back(a_distance);
		}
	}
	std::sort(distances.begin(), distances.end(), compareDistance);

	int i = 0;
	int j = 0;

	while (j < cities.size() && i < distances.size())
	{
		//Don't add a edge if either of the cities already have two edges connected.
		if ((cities.at(distances.at(i).a).edge_count < 2) && (cities.at(distances.at(i).b).edge_count < 2))
		{
			//If you are trying to add a edge to two cities that both have exactly one edge there is a chance
			//to create a cycle so we need to check if that happens.
			if (cities.at(distances.at(i).a).edge_count == 1 && cities.at(distances.at(i).b).edge_count == 1)
			{
				if (!is_cycle(cities, distances.at(i)) || (j == cities.size() - 1)) //However we allow a cycle if it is the last city.
				{
					total_distance += distances.at(i).distance;
					add_edge(cities, distances, i, j);
				}
				else
				{
					i++;
				}
			}
			else
			{
				total_distance += distances.at(i).distance;
				add_edge(cities, distances, i, j);
			}
		}//end check for cycles
		else
		{
			i++;
		}
	}//end while

	return cities;
}

void add_edge(std::vector<city> &cities, std::vector <eucl_distance> &distances, int &i, int &j)
{
	if (cities.at(distances.at(i).a).edge_count == 0) //Update city A
	{
		cities.at(distances.at(i).a).edge1 = distances.at(i).b;
	}
	else
	{
		cities.at(distances.at(i).a).edge2 = distances.at(i).b;
	}

	if (cities.at(distances.at(i).b).edge_count == 0) //Update city B
	{
		cities.at(distances.at(i).b).edge1 = distances.at(i).a;
	}
	else
	{
		cities.at(distances.at(i).b).edge2 = distances.at(i).a;
	}

	cities.at(distances.at(i).a).edge_count++;
	cities.at(distances.at(i).b).edge_count++;
	i++;
	j++;
}

bool is_cycle(std::vector<city> cities, eucl_distance edge)
{
	int previous;
	int next;
	cities.at(edge.a).edge2 = edge.b;
	cities.at(edge.b).edge2 = edge.a;

	previous = edge.a;
	next = cities.at(edge.a).edge1;

	while (1)
	{
		if (cities.at(next).edge2 == edge.b)
		{
			return true;
		}
		if (cities.at(next).edge2 == -1)
		{
			return false;
		}

		if (cities.at(next).edge1 != previous)
		{
			previous = next;
			next = cities.at(previous).edge1;
		}
		else
		{
			previous = next;
			next = cities.at(previous).edge2;
		}
	}
}