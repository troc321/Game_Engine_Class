#include "sprite.h"

using namespace std;
using namespace sf;

vector<Texture*> textures;
vector<Sprite*> sprites;

#define f_to_uint8(vf)  ((Uint8) clamp(255.0f * (vf), 0.0f, 255.0f))

PyObject* proto_load_texture_sprite(PyObject *self, PyObject *args) {
    const char* filename = NULL;
    

    // see https://docs.python.org/3/c-api/arg.html
    if (!PyArg_ParseTuple(args, "s", &filename)) {
        // can fail if arg passed is not right type
        return PyLong_FromLong(0);
    }

    Texture *texture = new Texture();
    if(!texture->loadFromFile(filename)) {
        delete texture;
        return PyLong_FromLong(-1);
    }
    textures.push_back(texture);
    return PyLong_FromLong(textures.size() - 1);
}

PyObject* proto_get_size_sprite(PyObject *self, PyObject *args) {
    int handle;
    

    // see https://docs.python.org/3/c-api/arg.html
    if (!PyArg_ParseTuple(args, "i", &handle)) {
        // can fail if arg passed is not right type
        return PyLong_FromLong(0);
    }

    if(handle < 0 || handle >= textures.size()) {
        // handle out of range
        return PyBool_FromLong(0);
    }

    Vector2u *size = new Vector2u(textures[handle]->getSize());
    int length = int(size->x);
    int width = int(size->y);

    // create and return new tuple
    PyObject *ret = PyTuple_New(2);
    PyTuple_SetItem(ret, 0, PyLong_FromLong(length));
    PyTuple_SetItem(ret, 1, PyLong_FromLong(width));
    return ret;
}

PyObject* proto_load_sprite(PyObject *self, PyObject *args) {
    int handle;
    float x, y, l=0, w=0, r=1.f, g=1.f, b=1.f;

    if(!window) {
        // no window to draw in!
        return PyBool_FromLong(0);
    }

    // see https://docs.python.org/3/c-api/arg.html
    if (!PyArg_ParseTuple(args, "iff|fffff", &handle, &x, &y, &l, &w, &r, &g, &b)){
        // can fail if arg passed is not right type
        return PyBool_FromLong(0);
    }

    if(handle < 0 || handle >= textures.size()) {
        // handle out of range
        return PyBool_FromLong(0);
    }

    Sprite *sprite = new Sprite();
    sprite->setTexture(*textures[handle]);
    sprite->setPosition(Vector2f(x,y));
    if (l>0 && w>0) {
        sprite->setTextureRect(IntRect(x,y,l,w));
    }
    Color color(f_to_uint8(r), f_to_uint8(g), f_to_uint8(b));
    sprite->setColor(color);
    sprites.push_back(sprite);

    return PyBool_FromLong(sprites.size()-1);  // return handle of new sprite
}

PyObject* proto_move_sprite(PyObject *self, PyObject *args) {
    int handle; float x,y;

    // see https://docs.python.org/3/c-api/arg.html
    if (!PyArg_ParseTuple(args, "iff", &handle, &x, &y)) {
        // can fail if arg passed is not right type
        return PyBool_FromLong(0);
    }

    if(handle < 0 || handle >= sprites.size()) {
        // handle out of range
        return PyBool_FromLong(0);
    }
    sprites[handle]->setPosition(x,y);

    return PyBool_FromLong(1);  // return `True` to indicate "success"
}

PyObject* proto_draw_sprite(PyObject *self, PyObject *args) {
    int handle;
    

    // see https://docs.python.org/3/c-api/arg.html
    if (!PyArg_ParseTuple(args, "i", &handle)) {
        // can fail if arg passed is not right type
        return PyLong_FromLong(0);
    }

    if(handle < 0 || handle >= sprites.size()) {
        // handle out of range
        return PyBool_FromLong(0);
    }

    window->draw(*sprites[handle]);
    //returns True if successful
    return PyBool_FromLong(1);
}

PyMODINIT_FUNC PyInit_proto_sprite(void) {
    // printf("FOOBAR\n");
    return PyModule_Create(&ProtoSpriteModule);
}
