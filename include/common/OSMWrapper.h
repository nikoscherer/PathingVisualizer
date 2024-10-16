#pragma once

#include <Python.h>

class OSMWrapper {
private:
    PyObject* apiModule;

    PyObject* requestFunction;

	std::vector<int> callRequest(double minLon, double maxLon, double minLat, double maxLat);

public:
	int init();

	std::vector<int> getRoadData(double minLon, double maxLon, double minLat, double maxLat);
};