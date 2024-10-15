#include <vector>
#include <unordered_map>
#include <unordered_set>

#include "../../include/common/Map.h"

#include <iostream>

Map::Map() {

}
Map::Map(std::vector<Node*> _vertices, std::vector<int> _SCREEN_SIZE, std::vector<double> _MAP_SIZE, std::vector<double> _center)
	: SCREEN_SIZE(_SCREEN_SIZE), MAP_SIZE(_MAP_SIZE), center(_center) {

	for (Node* vertex : _vertices) {
		vertex->x = vertex->x - center[0];
		vertex->y = vertex->y - center[1];

		vertices.push_back(vertex);
		vertMap[vertex->id] = vertex;
	}
}

void Map::setCenterX(double centerX) {
	for (Node* vertex : vertices) {
		vertex->x = vertex->x + center[0] - centerX;
	}
	center[0] = centerX;
}

void Map::setCenterY(double centerY) {
	for (Node* vertex : vertices) {
		vertex->y = vertex->y + center[1] - centerY;
	}
	center[1] = centerY;
}

void Map::connect(int id1, int id2) {
	Node* vert1 = vertMap[id1];
	Node* vert2 = vertMap[id2];
	
	if (!vert1->neighbors.count(id2)) {
		vert1->neighbors.insert(id2);
		vert2->neighbors.insert(id1);
	}

}

void Map::runAlgorithm() {

}

void Map::drawMap() {

}

std::vector<double> Map::calculateMapCoordinates(int x, int y) {
	return {
		(((double) x / SCREEN_SIZE[0]) - 0.5) * (2 * MAP_SIZE[0]),
		-(((double) y / SCREEN_SIZE[1]) - 0.5) * (2 * MAP_SIZE[1])
	};
}

std::vector<int> Map::calculateScreenCoordinates(double x, double y) {
	return {
		int (((x) / (2 * MAP_SIZE[0]) + 0.5) * SCREEN_SIZE[0]),
		int (SCREEN_SIZE[1] + ((-y / (2 * MAP_SIZE[1]) - 0.5) * SCREEN_SIZE[1]))
	};
}