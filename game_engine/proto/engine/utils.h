#pragma once

#include <Python.h>

void remove_py_extension(char *filename);
void remove_path(char *filename);
bool has_path(char *filename);

PyObject * get_py_function(const char *fnname);
void call_py_function(PyObject *pfn);
