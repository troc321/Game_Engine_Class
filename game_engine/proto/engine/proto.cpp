#include "proto.h"

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <iostream>

#include "utils.h"

using namespace sf;


PyObject *pmod_game = NULL;

Clock clock_update;
double elapsed = 0.0;

void post_update(void) {
    elapsed = clock_update.getElapsedTime().asSeconds();
    clock_update.restart();
}

int start_engine(char *python_file) {
    PyObject *pName, *pfn_init, *pfn_update, *pfn_draw;

    // make sure game file exists
    {
        FILE *file = fopen(python_file, "r");
        if(file) {
            // file exists!
            fclose(file);
        } else {
            // file does not exist :(
            fprintf(stderr, "Proto Error: Game file \"%s\" does not exist\n", python_file);
            return -1;
        }
    }

    // set up Python
    wchar_t *program = Py_DecodeLocale("proto", NULL);
    Py_SetProgramName(program);                                     // optional but recommended
    PyMem_RawFree(program);
    // add proto module so that games can access features / functionality of engine
    // NOTE: any additional modules should be added here _before_ Py_Initialize
    PyImport_AppendInittab("proto", PyInit_proto_main);             // add proto module
    Py_Initialize();
    PyRun_SimpleString("import os, sys");
    PyRun_SimpleString("sys.path.insert(0, \".\")");    // set up path
    if(has_path(python_file)) {
        char str_chdir[1000];
        sprintf(str_chdir, "os.chdir(os.path.dirname('%s'))", python_file);
        PyRun_SimpleString(str_chdir);
    }

    // load game as module
    remove_py_extension(python_file);
    remove_path(python_file);
    pName = PyUnicode_DecodeFSDefault(python_file);                 // error checking of pName left out
    pmod_game = PyImport_Import(pName);                             // import module
    Py_DECREF(pName);                                               // no longer need pName
    if (pmod_game == NULL) {                                        // could not load module
        PyErr_Print();
        fprintf(stderr, "Failed to load \"%s\"\n", python_file);
        Py_FinalizeEx();
        return 1;
    }

    // get functions: _init, _update, _draw  (could be null)
    pfn_init = get_py_function("_init");
    pfn_update = get_py_function("_update");
    pfn_draw = get_py_function("_draw");
    //printf("fns: %p %p %p\n", pfn_init, pfn_update, pfn_draw);

    // set up SFML
    create_window(640, 480, "Proto Game Engine");

    // call game's _init (if exists)
    call_py_function(pfn_init);

    while(window->isOpen()) {
        Event event;
        while(window->pollEvent(event)) {
            if(event.type == Event::Closed) window->close();
        }

        call_py_function(pfn_update);   // call game's _update (if exists)
        post_update();

        window->clear();
        call_py_function(pfn_draw);     // call game's _draw (if exists)
        window->display();
    }

    // shutdown SFML
    clear_all_audio();
    clear_all_music();

    // tear down Python and exit
    Py_XDECREF(pfn_init);
    Py_DECREF(pmod_game);
    if (Py_FinalizeEx() < 0) {
        return 120;
    }
    return 0;
}

PyObject* close_window(PyObject *self, PyObject *args) {
    window->close();
    return PyLong_FromLong(1);
}

PyObject* proto_deltatime(PyObject *self, PyObject *args) {
    return PyFloat_FromDouble(elapsed);
}

PyObject* proto_tupleswap(PyObject *self, PyObject *args) {
    PyObject* arg_tuple = NULL;

    // get tuple argument
    if (!PyArg_ParseTuple(args, "O", &arg_tuple)) {
        // can fail if arg passed is not right type
        return PyLong_FromLong(-1);
    }
    if(!PyTuple_Check(arg_tuple)) {
        PyErr_SetString(PyExc_TypeError, "expected tuple");
        return NULL; // Py_RETURN_NONE;
    }

    // get longs out of tuple
    long arg_tuple_0 = PyLong_AsLong(PyTuple_GetItem(arg_tuple, 0));
    long arg_tuple_1 = PyLong_AsLong(PyTuple_GetItem(arg_tuple, 1));

    // do the swap
    long ret_tuple_0 = arg_tuple_1;
    long ret_tuple_1 = arg_tuple_0;

    // create and return new tuple
    PyObject *ret = PyTuple_New(2);
    PyTuple_SetItem(ret, 0, PyLong_FromLong(ret_tuple_0));
    PyTuple_SetItem(ret, 1, PyLong_FromLong(ret_tuple_1));
    return ret;
}


PyObject* proto_collide_rects(PyObject *self, PyObject *args) {
    float x1, y1, w1, h1, x2, y2, w2, h2;
    // see https://docs.python.org/3/c-api/arg.html
    if (!PyArg_ParseTuple(args, "ffffffff", &x1, &y1, &w1, &h1, &x2, &y2, &w2, &h2)) {
        // can fail if arg passed is not right type
        return PyBool_FromLong(0);
    }

    long collide;
    if ((x1 < x2 + w2) && (x1 + w1 > x2) && (y1 < y2 + h2) && (h1 + y1 > y2)) {
        collide = 1;
    } else {
        collide = 0;
    }

    return PyLong_FromLong(collide);
}

PyObject* proto_collide_circles(PyObject *self, PyObject *args) {
    float x1, y1, r1, x2, y2, r2;
    // see https://docs.python.org/3/c-api/arg.html
    if (!PyArg_ParseTuple(args, "ffffff", &x1, &y1, &r1, &x2, &y2, &r2)) {
        // can fail if arg passed is not right type
        return PyBool_FromLong(0);
    }

    long collide;
    collide = 1;
    if (sqrt(pow((x1-x2), 2) + pow((y1-y2), 2)) <= (r1 + r2)) {
        collide = 1;
    } else {
        collide = 0;
    }

    return PyLong_FromLong(collide);
}

PyObject* proto_keyPressed(PyObject *self, PyObject *args) {

    int key;


    if (!PyArg_ParseTuple(args, "i", &key)) {
        // can fail if arg passed is not right type
        return PyBool_FromLong(0);
    }

    if(sf::Keyboard::isKeyPressed((Keyboard::Key)key)){
        return PyBool_FromLong(1);
    }

    return PyLong_FromLong(0);  // return `True` to indicate "success"
}

PyMODINIT_FUNC PyInit_proto_main(void) {
    PyObject *mod;
    PyObject *submodule;
    PyObject *sys_modules = PyImport_GetModuleDict();

    mod = PyModule_Create(&ProtoMainModule);

    // add draw submodule
    PyModule_AddObject(mod, "draw", (submodule = PyInit_proto_draw()));
    PyDict_SetItem(sys_modules, PyModule_GetNameObject(submodule), submodule);

    // add audio submodule
    PyModule_AddObject(mod, "audio", (submodule = PyInit_proto_audio()));
    PyDict_SetItem(sys_modules, PyModule_GetNameObject(submodule), submodule);

    // add music submodule
    PyModule_AddObject(mod, "music", (submodule = PyInit_proto_music()));
    PyDict_SetItem(sys_modules, PyModule_GetNameObject(submodule), submodule);

    // add sprite submodule
    PyModule_AddObject(mod, "sprite", (submodule = PyInit_proto_sprite()));
    PyDict_SetItem(sys_modules, PyModule_GetNameObject(submodule), submodule);

    //add keyboard presses
    PyModule_AddIntConstant(mod, "K_Left",   Keyboard::Left);
    PyModule_AddIntConstant(mod, "K_Right",   Keyboard::Right);
    PyModule_AddIntConstant(mod, "K_Down",   Keyboard::Down);
    PyModule_AddIntConstant(mod, "K_Up",   Keyboard::Up);
    PyModule_AddIntConstant(mod, "K_A",   Keyboard::A);
    PyModule_AddIntConstant(mod, "K_S",   Keyboard::S);
    PyModule_AddIntConstant(mod, "K_D",   Keyboard::D);
    PyModule_AddIntConstant(mod, "K_F",   Keyboard::F);
    PyModule_AddIntConstant(mod, "K_W",   Keyboard::W);
    PyModule_AddIntConstant(mod, "K_Space",   Keyboard::Space);
    PyModule_AddIntConstant(mod, "K_Escape",   Keyboard::Escape);
    PyModule_AddIntConstant(mod, "K_LShift",   Keyboard::LShift);
    PyModule_AddIntConstant(mod, "K_Tab",   Keyboard::Tab);


    return mod;
}