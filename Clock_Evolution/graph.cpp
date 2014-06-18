/*From github user Chocti
  An implimentation of Dijkstras algorithm in C++
  */

#include <unordered_map>
#include <vector>
#include <limits>
#include <algorithm>
#include <iostream>
#include "stdfax.h"

class Graph
{
	std::unordered_map<char, const std::unordered_map<char,int>> vertices;

public:
	void add_vertex(char name, const std::unordered_map<char,int>& edges)
	{
		vertices.insert(std::unordered_map<char, const std::unordered_map<char,int>>::value_type(name,edges));
	}

	std::vector<char> shortest_path(char start, char finish)
	{
		std::unordered_map<char,int> distances;
		std::unordered_map<char,char> previous;
		std::vector<char> nodes;
		std::vector<char> path;

		auto comparator = [&] (char left, char right)
		{
			return distances[left] > distances[right];
		};

		for(auto& vertex : vertices)
		{
			if(vertex.first == start)
				distances[vertex.first] = 0;
			else
				distances[vertex.first] = std::numeric_limits<int>::max();

			nodes.push_back(vertex.first);
			push_heap(begin(nodes),end(nodes),comparator);
		}

		while(!nodes.empty())
		{
			pop_heap(begin(nodes),end(nodes),comparator);
			char smallest = nodes.back();
			nodes.pop_back();

			if(smallest == finish)
			{
				while(previous.find(smallest) != end(previous))
				{
					path.push_back(smallest);
					smallest = previous[smallest];
				}
				break;
			}
			if(distances[smallest] == std::numeric_limits<int>::max())
				break;

			for(auto& neighbor : vertices[smallest])
			{
				int alt = distances[smallest]+neighbor.second;
				if(alt < distances[neighbor.first])
				{
					distances[neighbor.first] = alt;
					previous[neighbor.first] = smallest;
					make_heap(begin(nodes),end(nodes),comparator);
				}
			}
		}
		return path;
	}
};

/*Example use
int main()
{
	Graph g;
	 g.add_vertex('A', {{'B', 7}, {'C', 8}});
    g.add_vertex('B', {{'A', 7}, {'F', 2}});
    g.add_vertex('C', {{'A', 8}, {'F', 6}, {'G', 4}});
    g.add_vertex('D', {{'F', 8}});
    g.add_vertex('E', {{'H', 1}});
    g.add_vertex('F', {{'B', 2}, {'C', 6}, {'D', 8}, {'G', 9}, {'H', 3}});
    g.add_vertex('G', {{'C', 4}, {'F', 9}});
    g.add_vertex('H', {{'E', 1}, {'F', 3}});
    
    for (char vertex : g.shortest_path('A', 'H'))
    {
        cout << vertex << endl;
    }
    
    return 0;
}
