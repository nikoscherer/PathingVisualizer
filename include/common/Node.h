#pragma once

#include <unordered_set>

class Node {
public:
	long long id;

	double x;
	double y;

	std::unordered_set<long long> neighbors;

	Node(long long _id, double _x, double _y, std::unordered_set<long long> _neighbors);
};