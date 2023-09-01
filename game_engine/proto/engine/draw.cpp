#include "draw.h"

using namespace std;
using namespace sf;

vector<CircleShape*> circles;
vector<RectangleShape*> rects;

RenderWindow *window = NULL;

#define f_to_uint8(vf)  ((Uint8) clamp(255.0f * (vf), 0.0f, 255.0f))

void create_window(int width, int height, const char *title) {
    window = new RenderWindow(VideoMode(width, height), title);
    // center window on desktop
    VideoMode desktop = VideoMode::getDesktopMode();
    Vector2i position((desktop.width - width) / 2, (desktop.height - height) / 2);
    window->setPosition(position);
}

PyObject* proto_set_window_framerate(PyObject *self, PyObject *args) {
    int fps;

    // see https://docs.python.org/3/c-api/arg.html
    if (!PyArg_ParseTuple(args, "i", &fps)) {
        // can fail if arg passed is not right type
        return PyBool_FromLong(0);
    }

    window->setFramerateLimit(fps);
    return PyBool_FromLong(1);
}

PyObject* get_window_width(PyObject *self, PyObject *args) {
    return PyFloat_FromDouble(window->getSize().x);
}

PyObject* get_window_height(PyObject *self, PyObject *args) {
    return PyFloat_FromDouble(window->getSize().y);
}

PyObject* proto_circle_create(PyObject *self, PyObject *args) {
    float x, y, r, cr=1.f, cg=1.f, cb=1.f;

    // see https://docs.python.org/3/c-api/arg.html
    if (!PyArg_ParseTuple(args, "fff|fff", &x, &y, &r, &cr, &cg, &cb)) {
        // can fail if arg passed is not right type
        return PyBool_FromLong(0);
    }

    CircleShape *buffer = new CircleShape();
    buffer->setRadius(r);
    buffer->setPosition(x, y);
    Color color(f_to_uint8(cr), f_to_uint8(cg), f_to_uint8(cb));
    buffer->setFillColor(color);
    circles.push_back(buffer);
    return PyLong_FromLong(circles.size() - 1);
}
PyObject* proto_rect_create(PyObject *self, PyObject *args) {
    float x, y, w, h, cr=1.f, cg=1.f, cb=1.f;

    // see https://docs.python.org/3/c-api/arg.html
    if (!PyArg_ParseTuple(args, "ffff|fff", &x, &y, &w, &h, &cr, &cg, &cb)) {
        // can fail if arg passed is not right type
        return PyBool_FromLong(0);
    }

    RectangleShape *buffer = new RectangleShape();
    buffer->setOrigin(0.f, 0.f);
    Color color(f_to_uint8(cr), f_to_uint8(cg), f_to_uint8(cb));
    buffer->setFillColor(color);
    buffer->setPosition(x, y);
    buffer->setSize(sf::Vector2f(w, h));
    rects.push_back(buffer);
    return PyLong_FromLong(rects.size() - 1);
}
void drawCircle(float x,float y,float r,float cr,float cg,float cb){
    CircleShape shape_circle(1.0f);
    shape_circle.setOrigin(0.f, 0.f);
    Color color(f_to_uint8(cr), f_to_uint8(cg), f_to_uint8(cb));
    shape_circle.setFillColor(color);
    shape_circle.setPosition(x - r, y - r);
    shape_circle.setRadius(r);
    window->draw(shape_circle);
}
void drawRect(float x,float y, sf::Vector2f size, float cr,float cg,float cb){
    RectangleShape shape_rect(size);
    shape_rect.setOrigin(0.f, 0.f);
    Color color(f_to_uint8(cr), f_to_uint8(cg), f_to_uint8(cb));
    shape_rect.setFillColor(color);
    shape_rect.setPosition(x, y);
    window->draw(shape_rect);
}


PyObject* proto_draw_perma_circle(PyObject *self, PyObject *args) {
    int handle;

    // see https://docs.python.org/3/c-api/arg.html
    if (!PyArg_ParseTuple(args, "i", &handle)) {
        // can fail if arg passed is not right type
        return PyBool_FromLong(0);
    }

    if(handle < 0 || handle >= circles.size()) {
        // handle out of range
        return PyBool_FromLong(0);
    }
    float r=circles[handle]->getRadius();
    float x=circles[handle]->getPosition().x;
    float y=circles[handle]->getPosition().y;
    float cr=circles[handle]->getFillColor().r / 255.0f;
    float cg=circles[handle]->getFillColor().g / 255.0f;
    float cb=circles[handle]->getFillColor().b / 255.0f;
    drawCircle(x,y,r,cr,cg,cb);

    return PyBool_FromLong(1);  // return `True` to indicate "success"
}

PyObject* proto_draw_perma_rect(PyObject *self, PyObject *args) {
    int handle;

    // see https://docs.python.org/3/c-api/arg.html
    if (!PyArg_ParseTuple(args, "i", &handle)) {
        // can fail if arg passed is not right type
        return PyBool_FromLong(0);
    }

    if(handle < 0 || handle >= rects.size()) {
        // handle out of range
        return PyBool_FromLong(0);
    }
    sf::Vector2f size = rects[handle]->getSize(); 
    float x=rects[handle]->getPosition().x;
    float y=rects[handle]->getPosition().y;
    float cr=rects[handle]->getFillColor().r / 255.0f;
    float cg=rects[handle]->getFillColor().g / 255.0f;
    float cb=rects[handle]->getFillColor().b / 255.0f;
    
    drawRect(x,y,size,cr,cg,cb);

    return PyBool_FromLong(1);  // return `True` to indicate "success"
}


PyObject* proto_draw_circle(PyObject *self, PyObject *args) {
    float x, y, r, cr=1.f, cg=1.f, cb=1.f;

    if(!window) {
        // no window to draw in!
        return PyBool_FromLong(0);
    }

    // see https://docs.python.org/3/c-api/arg.html
    if (!PyArg_ParseTuple(args, "fff|fff", &x, &y, &r, &cr, &cg, &cb)) {
        // can fail if arg passed is not right type
        return PyBool_FromLong(0);
    }

    drawCircle(x,y,r,cr,cg,cb);

    // to return None, uncomment the line below (not `return Py_RETURN_NONE;`!)
    // Py_RETURN_NONE;
    return PyBool_FromLong(1);  // return `True` to indicate "success"
}
PyObject* proto_move_circle(PyObject *self, PyObject *args) {
    int handle; float x,y;

    // see https://docs.python.org/3/c-api/arg.html
    if (!PyArg_ParseTuple(args, "iff", &handle, &x, &y)) {
        // can fail if arg passed is not right type
        return PyBool_FromLong(0);
    }

    if(handle < 0 || handle >= circles.size()) {
        // handle out of range
        return PyBool_FromLong(0);
    }
    circles[handle]->setPosition(x,y);

    return PyBool_FromLong(1);  // return `True` to indicate "success"
}

PyMODINIT_FUNC PyInit_proto_draw(void) {
    return PyModule_Create(&ProtoDrawModule);
}



PyObject* proto_draw_rect(PyObject *self, PyObject *args) {
    float x, y, w, h, cr=1.f, cg=1.f, cb=1.f;

    if(!window) {
        // no window to draw in!
        return PyBool_FromLong(0);
    }

    // see https://docs.python.org/3/c-api/arg.html
    if (!PyArg_ParseTuple(args, "ffff|fff", &x, &y, &w, &h, &cr, &cg, &cb)) {
        // can fail if arg passed is not right type
        return PyBool_FromLong(0);
    }

    RectangleShape shape_rect(sf::Vector2f(w, h));
    shape_rect.setOrigin(0.f, 0.f);
    Color color(f_to_uint8(cr), f_to_uint8(cg), f_to_uint8(cb));
    shape_rect.setFillColor(color);
    shape_rect.setPosition(x, y);
    window->draw(shape_rect);

    return PyBool_FromLong(1);  // return `True` to indicate "success"
}
PyObject* proto_move_rect(PyObject *self, PyObject *args) {
    int handle; float x,y;

    // see https://docs.python.org/3/c-api/arg.html
    if (!PyArg_ParseTuple(args, "iff", &handle, &x, &y)) {
        // can fail if arg passed is not right type
        return PyBool_FromLong(0);
    }

    if(handle < 0 || handle >= circles.size()) {
        // handle out of range
        return PyBool_FromLong(0);
    }
    rects[handle]->setPosition(x,y);

    return PyBool_FromLong(1);  // return `True` to indicate "success"
}

PyObject* proto_draw_text(PyObject *self, PyObject *args) {
    char* str;
    float x, y, size;
    float cr=1.f, cg=1.f, cb=1.f;
    sf::Font font;
    // Use default font, stored in engine/ folder
    if (!font.loadFromFile("../engine/resources/ubuntu.ttf")) {
        return PyBool_FromLong(0);
    }

    if(!window) {
        // no window to draw in!
        return PyBool_FromLong(0);
    }
    // see https://docs.python.org/3/c-api/arg.html
    if (!PyArg_ParseTuple(args, "sfff|fff", &str, &x, &y, &size, &cr, &cg, &cb)) {
        // can fail if arg passed is not right type
        return PyBool_FromLong(0);
    }

    sf::Text text;
    text.setFont(font);
    text.setString(str);
    text.move(x, y);
    text.setCharacterSize(size);
    text.setFillColor(sf::Color(cr*255, cg*255, cb*255));
    window->draw(text);

    return PyBool_FromLong(1);  // return `True` to indicate "success"
}

PyObject* proto_draw_line(PyObject *self, PyObject *args) {
    float x1, y1, x2, y2, cr=1.f, cg=1.f, cb=1.f;

    if(!window) {
        // no window to draw in!
        return PyBool_FromLong(0);
    }
    // see https://docs.python.org/3/c-api/arg.html
    if (!PyArg_ParseTuple(args, "ffff|fff", &x1, &y1, &x2, &y2, &cr, &cg, &cb)) {
        // can fail if arg passed is not right type
        return PyBool_FromLong(0);
    }

    Color color(f_to_uint8(cr), f_to_uint8(cg), f_to_uint8(cb));

    sf::Vertex line[] = {
        sf::Vertex(sf::Vector2f(x1, y1), color),
        sf::Vertex(sf::Vector2f(x2, y2), color)
    };

    window->draw(line, 2, sf::Lines);

    return PyBool_FromLong(1);  // return `True` to indicate "success"
}
