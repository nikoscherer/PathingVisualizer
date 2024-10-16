#pragma once

#include <vector>
#include <unordered_map>
#include <unordered_set>

class Algorithm {

public:
	std::unordered_set<int> visited;
	std::vector<int> toVisit;

	virtual ~Algorithm() {};
};