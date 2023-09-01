#pragma once

#include <Python.h>
#include <SFML/Graphics.hpp>

extern std::vector<sf::Texture *> textures;
extern std::vector<sf::Sprite *> sprites;
extern sf::RenderWindow *window;

// load sprite function
PyDoc_STRVAR(proto_load_texture_sprite_doc,
    ".. function:: loadTex(texture)\n"
    "\n"
    " Loads a texture from a file.\n"
    "\n"
    "   :param texture: File name of desired texture.\n"
    "   :type texture: str\n"
    );

PyObject* proto_load_texture_sprite(PyObject *self, PyObject *args);

// draw sprite function
PyDoc_STRVAR(proto_get_size_sprite_doc,
    ".. function:: getSize(handle)\n"
    "\n"
    "  Gets a size from a given texture. \n"
    "\n"
    "   :param handle: The index of the texture desired for the sprite.\n"
    "   :type handle: int\n"
    "   :return: length.\n"
    "   :rtypet: int\n"
    "   :return: width.\n"
    "   :rtypet: int\n"
    );

PyObject* proto_get_size_sprite(PyObject *self, PyObject *args);

PyDoc_STRVAR(proto_load_sprite_doc,
    ".. function:: load(texture)\n"
    "\n"
    "  Loads a sprite with a given texture, position (x,y), length, width, and optionally color.\n"
    "\n"
    "   :param texture: File name of desired texture.\n"
    "   :type texture: str\n"
    "   :param x: X coordinate of top left corner of sprite rect.\n"
    "   :type x: float\n"
    "   :param y: Y coordinate of top left corner of sprite rect.\n"
    "   :type y: float\n"
    "   :param l: Length of sprite rect.\n"
    "   :type l: float\n"
    "   :param w: Width of sprite rect.\n"
    "   :type w: float\n"
    "   :param r: Red value of sprite.\n"
    "   :type r: float\n"
    "   :param g: Blue value of sprite.\n"
    "   :type g: float\n"
    "   :param b: Green value of sprite.\n"
    "   :type b: float\n"
    "   :return: handle of sprite.\n"
    "   :rtypet: int\n"
    );

PyObject* proto_load_sprite(PyObject *self, PyObject *args);

PyDoc_STRVAR(proto_move_sprite_doc,
    ".. function:: move(handle, x, y)\n"
    "\n"
    "  Changes the position of a given sprite. \n"
    "\n"
    "   :param handle: The index of the sprite to draw.\n"
    "   :type handle: int\n"
    "   :param x: The x position of the top left corner of the sprite.\n"
    "   :type x: float\n"
    "   :param y: The y position of the top left corner of the sprite.\n"
    "   :type y: float\n"
    );

PyObject* proto_move_sprite(PyObject *self, PyObject *args);

// draw sprite function
PyDoc_STRVAR(proto_draw_sprite_doc,
    ".. function:: draw(handle)\n"
    "\n"
    "  Draws a given sprite. \n"
    "\n"
    "   :param handle: The index of the sprite to draw.\n"
    "   :type handle: int\n"
    );

PyObject* proto_draw_sprite(PyObject *self, PyObject *args);

static PyMethodDef ProtoSpriteMethods[] = {
    {"loadTex", proto_load_texture_sprite, METH_VARARGS, proto_load_texture_sprite_doc},
    {"getSize", proto_get_size_sprite, METH_VARARGS, proto_get_size_sprite_doc},
    {"load", proto_load_sprite, METH_VARARGS, proto_load_sprite_doc},
    {"move", proto_move_sprite, METH_VARARGS, proto_move_sprite_doc},
    {"draw", proto_draw_sprite, METH_VARARGS, proto_draw_sprite_doc},
    {NULL, NULL, 0, NULL}       // indicates end of list
};

// see: https://docs.python.org/3/c-api/module.html#c.PyModuleDef
static PyModuleDef ProtoSpriteModule = {
    PyModuleDef_HEAD_INIT,      // m_base
    "proto.sprite",             // m_name
    NULL,                       // m_doc
    -1,                         // m_size
    ProtoSpriteMethods,         // m_methods
    NULL,                       // m_reload
    NULL,                       // m_traverse
    NULL,                       // m_clear
    NULL                        // m_free
};

PyMODINIT_FUNC PyInit_proto_sprite(void);
