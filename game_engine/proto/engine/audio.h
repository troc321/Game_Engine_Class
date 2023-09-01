#pragma once

#include <Python.h>
#include <SFML/Audio.hpp>

extern std::vector<sf::SoundBuffer *> audio_buffers;
extern std::vector<sf::Sound *> audios;

void clear_all_audio(void);

// load audio function
PyDoc_STRVAR(proto_audio_load_doc,
    ".. function:: load(filename)\n"
    "\n"
    "    Loads an audio file.\n"
    "\n"
    "   :param filename: Filename of audio file to load.\n"
    "   :type x: str\n"
    "   :return: Handle as number; -1 if fail.\n"
    "   :rtypet: int\n"
    );
PyObject* proto_audio_load(PyObject *self, PyObject *args);

// play audio function
PyDoc_STRVAR(proto_audio_play_doc,
    ".. function:: play(handle)\n"
    "\n"
    "    Plays audio using given handle.\n"
    "\n"
    "   :param handle: Handle of audio to play.\n"
    "   :type x: int\n"
    "   :return: True if success; False otherwise.\n"
    "   :rtypet: bool\n"
    );
PyObject* proto_audio_play(PyObject *self, PyObject *args);


static PyMethodDef ProtoAudioMethods[] = {
    {"load", proto_audio_load, METH_VARARGS, proto_audio_load_doc},
    {"play", proto_audio_play, METH_VARARGS, proto_audio_play_doc},
    {NULL, NULL, 0, NULL}       // indicates end of list
};

// see: https://docs.python.org/3/c-api/module.html#c.PyModuleDef
static PyModuleDef ProtoAudioModule = {
    PyModuleDef_HEAD_INIT,      // m_base
    "proto.audio",              // m_name
    NULL,                       // m_doc
    -1,                         // m_size
    ProtoAudioMethods,          // m_methods
    NULL,                       // m_reload
    NULL,                       // m_traverse
    NULL,                       // m_clear
    NULL                        // m_free
};

PyMODINIT_FUNC PyInit_proto_audio(void);
