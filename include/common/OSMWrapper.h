#pragma once

#include <Python.h>

class OSMWrapper {
private:
    PyObject* apiModule;

    PyObject* requestFunction;

	void callRequest();

public:
	int init();

	void getRoadData();
};