#pragma once

#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <queue>

#include "Node.h"
#include "../algorithms/Algorithm.h"

class Map {
public: 
	std::vector<Node*> vertices;
	std::unordered_map<long long, Node*> vertMap;
	std::queue<Node*> updatedNodes;

	std::vector<int> SCREEN_SIZE;
	std::vector<double> MAP_SIZE;

	std::vector<double> center;


	Algorithm algorithm;

	Map();
	Map(std::vector<Node*> _vertices, std::vector<int> _SCREEN_SIZE, std::vector<double> _MAP_SIZE, std::vector<double> _center);

	void connect(long long id1, long long id2);

	void runAlgorithm();

	void drawMap();

	std::vector<double> calculateMapCoordinates(int x, int y);

	std::vector<int> calculateScreenCoordinates(double x, double y);


	void setCenterX(double centerX);
	void setCenterY(double centerY);
};