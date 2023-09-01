#pragma once

#include <Python.h>
#include <SFML/Audio.hpp>
#include <SFML/System.hpp>

extern std::vector<sf::Music*> songs;

void clear_all_music(void);

// load music function
PyDoc_STRVAR(proto_music_load_doc,"Loads Music.");
PyObject* proto_music_load(PyObject *self, PyObject *args);

// play music function
PyDoc_STRVAR(proto_music_play_doc, "Plays Music.");
PyObject* proto_music_play(PyObject *self, PyObject *args);

//pause (doesn't reset playing position) music function
PyDoc_STRVAR(proto_music_pause_doc, "Pauses Music.");
PyObject* proto_music_pause(PyObject *self, PyObject *args);

//stop (does reset playing position) music function
PyDoc_STRVAR(proto_music_stop_doc, "Stops Music.");
PyObject* proto_music_stop(PyObject *self, PyObject *args);

//gets song's time offset
PyDoc_STRVAR(proto_music_getOffset_doc, "Gets music offset");
PyObject* proto_music_getOffset(PyObject *self, PyObject *args);

//sets song's time offset
PyDoc_STRVAR(proto_music_setOffset_doc, "Sets music offset");
PyObject* proto_music_setOffset(PyObject *self, PyObject *args);

static PyMethodDef ProtoMusicMethods[] = {
    {"load", proto_music_load, METH_VARARGS, proto_music_load_doc},
    {"play", proto_music_play, METH_VARARGS, proto_music_play_doc},
    {"pause", proto_music_pause, METH_VARARGS, proto_music_pause_doc},
    {"stop", proto_music_stop, METH_VARARGS, proto_music_stop_doc},
    {"getOffset", proto_music_getOffset, METH_VARARGS, proto_music_getOffset_doc},
    {"setOffset", proto_music_setOffset, METH_VARARGS, proto_music_setOffset_doc},
    {NULL, NULL, 0, NULL}       // indicates end of list
};

// see: https://docs.python.org/3/c-api/module.html#c.PyModuleDef
static PyModuleDef ProtoMusicModule = {
    PyModuleDef_HEAD_INIT,      // m_base
    "proto.music",              // m_name
    NULL,                       // m_doc
    -1,                         // m_size
    ProtoMusicMethods,          // m_methods
    NULL,                       // m_reload
    NULL,                       // m_traverse
    NULL,                       // m_clear
    NULL                        // m_free
};

PyMODINIT_FUNC PyInit_proto_music(void);
