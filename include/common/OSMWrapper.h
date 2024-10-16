#pragma once

#include <Python.h>

#include "Node.h"

class OSMWrapper {
private:
    PyObject* apiModule;

    PyObject* requestFunction;

	std::vector<Node> callRequest(double minLon, double maxLon, double minLat, double maxLat);

public:
	int init();

	std::vector<Node> getRoadData(double minLon, double maxLon, double minLat, double maxLat);
};