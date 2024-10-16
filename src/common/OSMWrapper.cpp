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

std::vector<int> OSMWrapper::callRequest(double minLon, double maxLon, double minLat, double maxLat) {
    PyObject* min_lon = PyFloat_FromDouble(minLon);
    PyObject* max_lon = PyFloat_FromDouble(maxLon);
    PyObject* min_lat= PyFloat_FromDouble(minLat);
    PyObject* max_lat = PyFloat_FromDouble(maxLat);

    PyObject* bbox = PyTuple_New(4);

    PyTuple_SetItem(bbox, 0, min_lon);
    PyTuple_SetItem(bbox, 1, max_lon);
    PyTuple_SetItem(bbox, 2, min_lat);
    PyTuple_SetItem(bbox, 3, max_lat);


    PyObject* req = PyObject_CallObject(requestFunction, bbox);
    if (req) {
        std::vector<int> result;

        Py_ssize_t size = PyList_Size(req);

        for (int i = 0; i < size; i++) {
            PyObject* item = PyList_GetItem(req, i);

            result.push_back(static_cast<int>(PyLong_AsLong(item)));
            std::cout << result[result.size() - 1] << std::endl;
        }

        return result;

        Py_DECREF(req);
    }
    else {
        PyErr_Print();
        std::cerr << "Request Function call failed!" << std::endl;
    }

    Py_DECREF(min_lon);
    Py_DECREF(max_lon);
    Py_DECREF(min_lat);
    Py_DECREF(max_lat);


    return {-1};
}


std::vector<int> OSMWrapper::getRoadData(double minLon, double maxLon, double minLat, double maxLat) {
    return callRequest(minLon, maxLon, minLat,maxLat);
}