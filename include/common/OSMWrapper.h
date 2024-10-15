#pragma once

#include <Python.h>

class OSMWrapper {
private:
    PyObject* apiModule;

    PyObject* requestFunction;

	void callRequest(double min_lon, double max_lon, double min_lat, double max_lat);

public:
	int init();

	void getRoadData();
};