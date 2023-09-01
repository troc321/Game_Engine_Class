#pragma once

#include <Python.h>
#include <SFML/Graphics.hpp>

extern sf::RenderWindow *window;

void create_window(int width, int height, const char *title);

PyDoc_STRVAR(proto_set_window_framerate_doc,
    ".. function:: limiter(fps)\n"
    "\n"
    "  Limits the window's frames per second.\n"
    "\n"
    "   :param fps: The desired frames per second.\n"
    "   :type fps: int\n"
    "   :return: True if succeeded; False otherwise.\n"
    "   :rtypet: bool\n"
    );

PyObject* proto_set_window_framerate(PyObject *self, PyObject *args);

// draw circle function
PyDoc_STRVAR(proto_draw_circle_doc,
    ".. function:: circle(x, y, r, red, green, blue)\n"
    "\n"
    "  Draws a circle centered at given position (x,y) with given radius (r) and optional color (r,g,b).\n"
    "\n"
    "   :param x: X coordinate of circle center.\n"
    "   :type x: float\n"
    "   :param y: Y coordinate of circle center.\n"
    "   :type y: float\n"
    "   :param r: Radius of circle.\n"
    "   :type r: float\n"
    "   :param red: Red component of color (optional).\n"
    "   :type red: float\n"
    "   :param green: Green component of color (optional).\n"
    "   :type green: float\n"
    "   :param blue: Blue component of color (optional).\n"
    "   :type blue: float\n"
    "   :return: True if succeeded; False otherwise.\n"
    "   :rtypet: bool\n"
    );
PyObject* proto_draw_circle(PyObject *self, PyObject *args);
PyObject* proto_draw_perma_circle(PyObject *self, PyObject *args);
PyObject* proto_draw_perma_rect(PyObject *self, PyObject *args);

PyObject* proto_circle_create(PyObject *self, PyObject *args);
PyObject* proto_move_circle(PyObject *self, PyObject *args);
PyObject* proto_move_rect(PyObject *self, PyObject *args);


// draw rect function
PyDoc_STRVAR(proto_draw_rect_doc,
    ".. function:: rect(x, y, w, h, red, green, blue)\n"
    "\n"
    "  Draws a rect centered at given position (x,y) with given width and height (w,h) and optional color (r,g,b).\n"
    "\n"
    "   etc..."
    );
PyObject* proto_draw_rect(PyObject *self, PyObject *args);
PyObject* proto_rect_create(PyObject *self, PyObject *args);

// draw text function
PyDoc_STRVAR(proto_draw_text_doc,
    ".. function:: text(str, x, y, size, red, green, blue)\n"
    "\n"
    "  Draws a str with top left corner at given position (x,y) with given font size. Optional: color (r,g,b), which are floats between 0.0 and 1.0.\n"
    );
PyObject* proto_draw_text(PyObject *self, PyObject *args);

// draw line function
PyDoc_STRVAR(proto_draw_line_doc,
    ".. function:: line(x1, y1, x2, y2, optional: red, green, blue)\n"
    "\n"
    "  Draws a line between two vertices (points). Optional: color (r,g,b), which are floats between 0.0 and 1.0.\n"
    );
PyObject* proto_draw_line(PyObject *self, PyObject *args);
PyDoc_STRVAR(proto_get_windowW_doc, "Gets game window width");
PyObject* get_window_width(PyObject *self, PyObject *args);

PyDoc_STRVAR(proto_get_windowH_doc, "Gets game window height");
PyObject* get_window_height(PyObject *self, PyObject *args);

static PyMethodDef ProtoDrawMethods[] = {
    {"limiter", proto_set_window_framerate, METH_VARARGS, proto_set_window_framerate_doc},
    {"circle", proto_draw_circle, METH_VARARGS, proto_draw_circle_doc},
    {"drawPermaCircle", proto_draw_perma_circle, METH_VARARGS, proto_draw_circle_doc},
    {"drawPermaRect", proto_draw_perma_rect, METH_VARARGS, proto_draw_circle_doc},
    {"createCircle", proto_circle_create, METH_VARARGS, proto_draw_circle_doc},
    {"createRect", proto_rect_create, METH_VARARGS, proto_draw_circle_doc},
    {"moveCircle", proto_move_circle, METH_VARARGS, proto_draw_circle_doc},
    {"rect", proto_draw_rect, METH_VARARGS, proto_draw_rect_doc},
    {"text", proto_draw_text, METH_VARARGS, proto_draw_text_doc},
    {"line", proto_draw_line, METH_VARARGS, proto_draw_line_doc},
    {"getWindowWidth", get_window_width, METH_VARARGS, proto_get_windowW_doc},
    {"getWindowHeight", get_window_height, METH_VARARGS, proto_get_windowH_doc},
    {"moveRect", proto_move_rect, METH_VARARGS, proto_draw_rect_doc},
    {NULL, NULL, 0, NULL}       // indicates end of list
};




// see: https://docs.python.org/3/c-api/module.html#c.PyModuleDef
static PyModuleDef ProtoDrawModule = {
    PyModuleDef_HEAD_INIT,      // m_base
    "proto.draw",               // m_name
    NULL,                       // m_doc
    -1,                         // m_size
    ProtoDrawMethods,           // m_methods
    NULL,                       // m_reload
    NULL,                       // m_traverse
    NULL,                       // m_clear
    NULL                        // m_free
};

PyMODINIT_FUNC PyInit_proto_draw(void);
