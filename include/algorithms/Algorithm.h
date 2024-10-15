#pragma once

#include <vector>
#include <unordered_map>
#include <unordered_set>

class Algorithm {
	std::unordered_set<int> visited;
	std::vector<int> toVisit;
public:
	virtual ~Algorithm() {};

	virtual void run();
};