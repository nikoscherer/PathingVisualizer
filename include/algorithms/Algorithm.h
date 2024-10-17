#pragma once

#include <vector>
#include <unordered_map>
#include <unordered_set>

class Algorithm {

public:
	std::unordered_set<long long> visited;
	std::vector<long long> toVisit;

	virtual ~Algorithm() {};
};