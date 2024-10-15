#include <filesystem>
#include <Python.h>
#include <iostream>

#include "../../include/common/OSMWrapper.h"

int OSMWrapper::init() {
    Py_Initialize();

    // Set python path
    std::filesystem::path executePath = std::filesystem::current_path();
    PyRun_SimpleString(("import sys; sys.path.append(r'" + executePath.string() + "/python/')").c_str());

    apiModule = PyImport_ImportModule("apihandler");
    if (!apiModule) {
        PyErr_Print();
        std::cerr << "Failed to load the API handler!" << std::endl;
        return 1;
    }

    // Get the function from the module
    requestFunction = PyObject_GetAttrString(apiModule, "request");
    if (!requestFunction) {
        PyErr_Print();
        std::cerr << "Failed to get request function!" << std::endl;
        return 1;
    }

    return 0;
}

void OSMWrapper::callRequest(double min_lon, double max_lon, double min_lat, double max_lat) {
    PyObject* min_lon = PyFloat_FromDouble(min_lon);
    PyObject* max_lon = PyFloat_FromDouble(max_lon);
    PyObject* min_lat= PyFloat_FromDouble(min_lat);
    PyObject* max_lat = PyFloat_FromDouble(max_lat);

    PyObject* req = PyObject_CallObject(requestFunction, nullptr);
    if (req) {
        Py_DECREF(req);
    }
    else {
        PyErr_Print();
        std::cerr << "Request Function call failed!" << std::endl;
    }
}


void OSMWrapper::getRoadData() {
    callRequest();
}