#include "music.h"

using namespace std;
using namespace sf;

vector<Music*> songs;

void clear_all_music(void) {
    for(int i = 0; i < songs.size(); i++) {
        songs[i]->stop();
        while(songs[i]->getStatus() != SoundSource::Status::Stopped) {
            // spin until done
        }
        delete songs[i];
    }
    songs.clear();
}

PyObject* proto_music_load(PyObject *self, PyObject *args) {
    const char* filename = NULL;

    // see https://docs.python.org/3/c-api/arg.html
    if (!PyArg_ParseTuple(args, "s", &filename)) {
        // can fail if arg passed is not right type
        return PyLong_FromLong(-1);
    }

    Music *song = new Music();
    if(!song->openFromFile(filename)) {
        delete song;
        return PyLong_FromLong(-1);
    }
    songs.push_back(song);
    return PyLong_FromLong(songs.size() - 1);
}

PyObject* proto_music_play(PyObject *self, PyObject *args) {
    int handle;

    // see https://docs.python.org/3/c-api/arg.html
    if (!PyArg_ParseTuple(args, "i", &handle)) {
        // can fail if arg passed is not right type
        return PyBool_FromLong(0);
    }

    if(handle < 0 || handle >= songs.size()) {
        // handle out of range
        return PyBool_FromLong(0);
    }

    songs[handle]->play();

    return PyBool_FromLong(1);  // return `True` to indicate "success"
}

PyObject* proto_music_pause(PyObject *self, PyObject *args) {
    int handle;

    // see https://docs.python.org/3/c-api/arg.html
    if (!PyArg_ParseTuple(args, "i", &handle)) {
        // can fail if arg passed is not right type
        return PyBool_FromLong(0);
    }

    if(handle < 0 || handle >= songs.size()) {
        // handle out of range
        return PyBool_FromLong(0);
    }

    songs[handle]->pause();

    return PyBool_FromLong(1);  // return `True` to indicate "success"
}

PyObject* proto_music_stop(PyObject *self, PyObject *args) {
    int handle;

    // see https://docs.python.org/3/c-api/arg.html
    if (!PyArg_ParseTuple(args, "i", &handle)) {
        // can fail if arg passed is not right type
        return PyBool_FromLong(0);
    }

    if(handle < 0 || handle >= songs.size()) {
        // handle out of range
        return PyBool_FromLong(0);
    }

    songs[handle]->stop();

    return PyBool_FromLong(1);  // return `True` to indicate "success"
}

PyObject* proto_music_getOffset(PyObject *self, PyObject *args) {
    int handle;

    // see https://docs.python.org/3/c-api/arg.html
    if (!PyArg_ParseTuple(args, "i", &handle)) {
        // can fail if arg passed is not right type
        return PyBool_FromLong(0);
    }

    if(handle < 0 || handle >= songs.size()) {
        // handle out of range
        return PyBool_FromLong(0);
    }

    /* "float" */ double timeObj = songs[handle]->getPlayingOffset().asSeconds();
    return PyFloat_FromDouble(timeObj);
}

PyObject* proto_music_setOffset(PyObject *self, PyObject *args){
    int handle;
    float timeInSeconds;

    // see https://docs.python.org/3/c-api/arg.html
    if (!PyArg_ParseTuple(args, "if", &handle, &timeInSeconds)) {
        // can fail if arg passed is not right type
        return PyBool_FromLong(0);
    }

    if(handle < 0 || handle >= songs.size()) {
        // handle out of range
        return PyBool_FromLong(0);
    }

    Time timeObj = seconds(timeInSeconds);
    songs[handle]->setPlayingOffset(timeObj);

    return PyBool_FromLong(1);  // return `True` to indicate "success"
}

PyMODINIT_FUNC PyInit_proto_music(void) {
    PyObject * mod;
    mod = PyModule_Create(&ProtoMusicModule);
    PyModule_AddIntConstant(mod, "VOLUME_LOUD",   100);
    PyModule_AddIntConstant(mod, "VOLUME_MEDIUM",  50);
    PyModule_AddIntConstant(mod, "VOLUME_QUIET",   10);
    return mod;
}
