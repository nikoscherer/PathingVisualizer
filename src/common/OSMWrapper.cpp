#include <filesystem>
#include <Python.h>
#include <iostream>
#include <unordered_set>

#include "../../include/common/OSMWrapper.h"
#include "../../include/common/Node.h"

int OSMWrapper::init() {
    Py_Initialize();

    // Set python path
    std::filesystem::path executePath = std::filesystem::current_path();
    PyRun_SimpleString(("import sys; sys.path.append(r'" + executePath.string() + "\\python')").c_str());

    // get apihandler
    apiHandler = PyImport_ImportModule("apihandler");
    if (!apiHandler) {
        PyErr_Print();
        std::cerr << "Failed to load the API handler!" << std::endl;
        return 1;
    }

    requestFunction = PyObject_GetAttrString(apiHandler, "request");
    if (!requestFunction) {
        PyErr_Print();
        std::cerr << "Failed to get request function!" << std::endl;
        return 1;
    }

    // Get the function from apihandler
    initFunction = PyObject_GetAttrString(apiHandler, "init");
    if (!requestFunction) {
        PyErr_Print();
        std::cerr << "Failed to get request function!" << std::endl;
        return 1;
    }

    PyObject_CallObject(initFunction, nullptr);

    return 0;
}

std::vector<Node> OSMWrapper::callRequest(double minLon, double maxLon, double minLat, double maxLat, std::string type) {
    PyObject* min_lon = PyFloat_FromDouble(minLon);
    PyObject* max_lon = PyFloat_FromDouble(maxLon);
    PyObject* min_lat= PyFloat_FromDouble(minLat);
    PyObject* max_lat = PyFloat_FromDouble(maxLat);

    PyObject* ways = PyUnicode_FromString(type.c_str());

    PyObject* args = PyTuple_New(4);

    PyTuple_SetItem(args, 0, min_lon);
    PyTuple_SetItem(args, 1, max_lon);
    PyTuple_SetItem(args, 2, min_lat);
    PyTuple_SetItem(args, 3, max_lat);
    PyTuple_SetItem(args, 4, ways);


    PyObject* req = PyObject_CallObject(requestFunction, args);

    if (req) {
        std::vector<Node> result;

        Py_ssize_t size = PyList_Size(req);

        for (int i = 0; i < size; i++) {
            PyObject* item = PyList_GetItem(req, i);

            long long id = static_cast<long long>(PyLong_AsLongLong(PyTuple_GetItem(item, 0)));
            double lon = static_cast<double>(PyFloat_AsDouble(PyTuple_GetItem(item, 1)));
            double lat = static_cast<double>(PyFloat_AsDouble(PyTuple_GetItem(item, 2)));
            std::unordered_set<long long> neighbors;

            PyObject* n = PyTuple_GetItem(item, 3);
            Py_ssize_t neighborSize = PyList_Size(n);

            for (int j = 0; j < neighborSize; j++) {
                long long val = PyLong_AsLongLong(PyList_GetItem(n, j));
                neighbors.insert(val);
            }

            result.push_back(Node(id, lon, lat, neighbors));
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

    return { };
}


std::vector<Node> OSMWrapper::getRoadData(double lon, double lat, std::vector<double> bbox. std::string type) {
    return callRequest(lon - bbox[0], lon + bbox[0], lat - bbox[1], lat + bbox[1], type);
}