#include "audio.h"

using namespace std;
using namespace sf;

vector<SoundBuffer*> audio_buffers;
vector<Sound*> audios;

void clear_all_audio(void) {
    for(int i = 0; i < audios.size(); i++) {
        audios[i]->stop();
        while(audios[i]->getStatus() != SoundSource::Status::Stopped) {
            // spin until done
        }
        delete audios[i];
        delete audio_buffers[i];
    }
    audios.clear();
    audio_buffers.clear();
}

PyObject* proto_audio_load(PyObject *self, PyObject *args) {
    const char* filename = NULL;

    // see https://docs.python.org/3/c-api/arg.html
    if (!PyArg_ParseTuple(args, "s", &filename)) {
        // can fail if arg passed is not right type
        return PyLong_FromLong(-1);
    }

    SoundBuffer *buffer = new SoundBuffer();
    if(!buffer->loadFromFile(filename)) {
        delete buffer;
        return PyLong_FromLong(-1);
    }
    Sound *audio = new Sound(*buffer);
    audio_buffers.push_back(buffer);
    audios.push_back(audio);
    return PyLong_FromLong(audios.size() - 1);
}

PyObject* proto_audio_play(PyObject *self, PyObject *args) {
    int handle;

    // see https://docs.python.org/3/c-api/arg.html
    if (!PyArg_ParseTuple(args, "i", &handle)) {
        // can fail if arg passed is not right type
        return PyBool_FromLong(0);
    }

    if(handle < 0 || handle >= audios.size()) {
        // handle out of range
        return PyBool_FromLong(0);
    }

    audios[handle]->play();

    return PyBool_FromLong(1);  // return `True` to indicate "success"
}

PyMODINIT_FUNC PyInit_proto_audio(void) {
    PyObject * mod;
    mod = PyModule_Create(&ProtoAudioModule);
    PyModule_AddIntConstant(mod, "VOLUME_LOUD",   100);
    PyModule_AddIntConstant(mod, "VOLUME_MEDIUM",  50);
    PyModule_AddIntConstant(mod, "VOLUME_QUIET",   10);
    return mod;
}
