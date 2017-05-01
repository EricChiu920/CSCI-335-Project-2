#include "chiu4.h"

std::vector<city> iterative_improvement(std::vector<city> cities, double &total_distance)
{
	double prev_distance;
	double new_distance;
	int a;
	int b;
	int c;

	a = 0;
	b = cities.at(a).edge2;
	c = a;

	for (int i = 0; i < cities.size() - 2; i++)
	{
		prev_distance = sqrt(pow(cities.at(0).x - cities.at(cities.at(0).edge2).x, 2.0) + pow(cities.at(0).y - cities.at(cities.at(0).edge2).y, 2.0));

		//move two edges away from first edge
		for (int i = 0; i < 2; i++)
		{
			a = b;
			if (cities.at(b).edge1 != c)
			{
				b = cities.at(b).edge1;
			}
			else
			{
				b = cities.at(b).edge2;
			}
			c = a;
		}
		prev_distance += sqrt(pow(cities.at(a).x - cities.at(b).x, 2.0) + pow(cities.at(a).y - cities.at(b).y, 2.0));

		new_distance = sqrt(pow(cities.at(0).x - cities.at(b).x, 2.0) + pow(cities.at(0).y - cities.at(b).y, 2.0));
		new_distance += sqrt(pow(cities.at(cities.at(0).edge2).x - cities.at(a).x, 2.0) + pow(cities.at(cities.at(0).edge2).y - cities.at(a).y, 2.0));

		if (new_distance < prev_distance)
		{
			total_distance -= prev_distance;
			total_distance += new_distance;

			c = cities.at(0).edge2;

			cities.at(0).edge2 = b;
			if (cities.at(b).edge1 == a)
			{
				cities.at(b).edge1 = 0;
			}
			else
			{
				cities.at(b).edge2 = 0;
			}

			cities.at(c).edge2 = a;
			if (cities.at(a).edge1 == b)
			{
				cities.at(a).edge1 = c;
			}
			else
			{
				cities.at(b).edge2 = c;
			}
			break;
		}
	}

	return cities;
}