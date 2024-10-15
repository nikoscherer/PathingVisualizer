#include <filesystem>
#include <Python.h>
#include <iostream>

#include "OSMWrapper.h"

int OSMWrapper::init() {
    Py_Initialize();

    // Set python path
    std::filesystem::path executePath = std::filesystem::current_path();
    PyRun_SimpleString(("import sys; sys.path.append(r'" + executePath.string() + "')").c_str());

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

void OSMWrapper::callRequest() {
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