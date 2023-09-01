#pragma once

#include <Python.h>

#include "draw.h"
#include "audio.h"
#include "music.h"
#include "sprite.h"

extern PyObject *pmod_game;

void post_update(void);
int start_engine(char *python_file);
PyObject* close_window(PyObject *self, PyObject *args);

PyDoc_STRVAR(close_window_doc,
    ".. function:: close_window()\n"
    "Closes sfml window and returns 1"
    );

// get delta time function
PyDoc_STRVAR(proto_deltatime_doc,
    ".. function:: deltatime()\n"
    "\n"
    "  Returns time (in seconds) since last update.\n"
    "\n"
    "   :return: Time (in seconds).\n"
    "   :rtypet: float\n"
    );
PyObject* proto_deltatime(PyObject *self, PyObject *args);

// tuple example function
PyDoc_STRVAR(proto_tupleswap_doc, "Simple function to work with tuples.  Note: assumes exactly two longs in tuple!");
PyObject* proto_tupleswap(PyObject *self, PyObject *args);

// rect collision function
PyDoc_STRVAR(proto_collide_rects_doc,
    ".. function:: collide_rects()\n"
    "\n"
    "  Returns 1 if the two rects overlap, 0 if they don't.\n"
    "\n"
    "   :return: 0 or 1.\n"
    "   :rtypet: int\n"
    );
PyObject* proto_collide_rects(PyObject *self, PyObject *args);

// check key presses
PyDoc_STRVAR(proto_keyPressed_doc,
    
    ".. function:: keyPressed()\n"
    "register whether a key is pressed, triggers code even if key is held. AKA 'Real Time Input'");


PyObject* proto_keyPressed(PyObject *self, PyObject *args);

// circle collision function
PyDoc_STRVAR(proto_collide_circles_doc,
    ".. function:: collide_circles()\n"
    "\n"
    "  Returns 1 if the two circles overlap, 0 if they don't.\n"
    "\n"
    "   :return: 0 or 1.\n"
    "   :rtypet: int\n"
    );
PyObject* proto_collide_circles(PyObject *self, PyObject *args);

static PyMethodDef ProtoMainMethods[] = {
    // {py name, cpp funct name, CONST, for documentation above}
    {"close_window", close_window, METH_VARARGS, close_window_doc},
    {"deltatime", proto_deltatime, METH_VARARGS, proto_deltatime_doc},
    {"collide_rects", proto_collide_rects, METH_VARARGS, proto_collide_rects_doc},
    {"collide_circles", proto_collide_circles, METH_VARARGS, proto_collide_circles_doc},
    {"tupleswap", proto_tupleswap, METH_VARARGS, proto_tupleswap_doc},
    {"keyPressed", proto_keyPressed, METH_VARARGS, proto_keyPressed_doc},
    {NULL, NULL, 0, NULL} // indicates end of list
};

// see: https://docs.python.org/3/c-api/module.html#c.PyModuleDef
static PyModuleDef ProtoMainModule = {
    PyModuleDef_HEAD_INIT,      // m_base
    "proto",                    // m_name
    NULL,                       // m_doc
    -1,                         // m_size
    ProtoMainMethods,           // m_methods
    NULL,                       // m_reload
    NULL,                       // m_traverse
    NULL,                       // m_clear
    NULL                        // m_free
};

PyMODINIT_FUNC PyInit_proto_main(void);
