#pragma once

#include <unordered_set>

class Node {
public:
	int id;

	double x;
	double y;

	std::unordered_set<int> neighbors;

	Node(int _id, double _x, double _y);
};