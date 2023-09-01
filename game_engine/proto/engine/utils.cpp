#include "utils.h"

#include "proto.h"

void remove_py_extension(char *filename) {
    int l = strlen(filename);
    if(l < 3) return;
    if(filename[l-3] == '.' && filename[l-2] == 'p' && filename[l-1] == 'y') {
        filename[l-3] = '\0';
    }
}
void remove_path(char *filename) {
    int l = strlen(filename);
    int idx;
    for(idx = l-1; idx >= 0; idx--) {
        if(filename[idx] == '/') break;
    }
    if(idx < 0) return;
    idx++;
    for(int i = 0; idx + i <= l; i++) {
        filename[i] = filename[idx + i];
    }
}
bool has_path(char *filename) {
    for(int i = 0; i < strlen(filename); i++) {
        if(filename[i] == '/') return true;
    }
    return false;
}

PyObject * get_py_function(const char *fnname) {
    if(!PyObject_HasAttrString(pmod_game, fnname)) return NULL;
    PyObject *pfn = PyObject_GetAttrString(pmod_game, fnname);
    if(!pfn) return NULL;
    if(!PyCallable_Check(pfn)) {
        Py_DECREF(pfn);
        return NULL;
    }
    return pfn;
}

void call_py_function(PyObject *pfn) {
    PyObject *pArgs, *pValue;
    if(!pfn) return;
    pArgs = PyTuple_New(0);
    pValue = PyObject_CallObject(pfn, pArgs);
    Py_DECREF(pArgs);
    if (pValue != NULL) {
        //printf("Result of call: %ld\n", PyLong_AsLong(pValue)); fflush(stdout);
        Py_DECREF(pValue);
    } else {
        // an error occurred while calling function
        PyErr_Print();
    }
}

