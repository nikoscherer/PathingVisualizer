#pragma once

#include <Python.h>

#include "Node.h"

class OSMWrapper {
private:
    PyObject* apiHandler;

    PyObject* requestFunction;
	PyObject* initFunction;

	std::vector<Node> callRequest(double minLon, double maxLon, double minLat, double maxLat, std::string type);

public:
	int init();

	std::vector<Node> getRoadData(double lon, double lat, std::vector<double> bbox, std::string type);
};