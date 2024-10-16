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
	std::unordered_map<int, Node*> vertMap;
	std::queue<Node*> updatedNodes;

	std::vector<int> SCREEN_SIZE;
	std::vector<double> MAP_SIZE;

	std::vector<double> center;


	Algorithm algorithm;

	Map();
	Map(std::vector<Node*> _vertices, std::vector<int> _SCREEN_SIZE, std::vector<double> _MAP_SIZE, std::vector<double> _center);

	void connect(int id1, int id2);

	void runAlgorithm();

	void drawMap();

	std::vector<double> calculateMapCoordinates(int x, int y);

	std::vector<int> calculateScreenCoordinates(double x, double y);


	void setCenterX(double centerX);
	void setCenterY(double centerY);
};