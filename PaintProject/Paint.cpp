#include "Paint.h"
#include <vector>
#include <list>
#include "Figures/Dot.h"
#include "Drawer.h"

#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/freeglut.h>

void Paint::start(int argc, char **argv) {
    drawer.setLineColour({1, 0, 0});
    drawer.setMainColour({0, 0, 0});
    is_second = false;
    is_random = false;
    window_w = 1920;
    window_h = 1080;

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);
    glutInitWindowSize(window_w, window_h);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Paint");
    callbackInit();
    init();
    createOurMenu();
    glutMainLoop();
}

void Paint::callbackInit() {
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutMouseFunc(mouse);
    glutPassiveMotionFunc(passiveMouse);
    glutMotionFunc(motion);
    glutTimerFunc(17, FPS, 0);
}

void Paint::passiveMouse(int x, int y) {
    y = window_h - y;

    temp_dots.clear();

    if (drawer.isOneClickable() || !is_second) {
        return;
    }
    Dot tmp = Dot{tmp_x, tmp_y, Colour{0, 0, 0}};
    Dot current = Dot(x, y, Colour{0, 0, 0});
    auto points = drawer.draw(tmp, current);
    temp_dots.insert(temp_dots.end(), points.begin(), points.end());
}

void Paint::FPS(int val) {
    glutPostRedisplay();
    glutTimerFunc(0, FPS, 0);
}

void Paint::init() {
    /* background color */
    glClearColor(1.0, 1.0, 1.0, 1.0);
    glColor3f(1.0, 1.0, 1.0);

    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(0.0, window_w, 0.0, window_h);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void Paint::createOurMenu() {
    int colourMenu = glutCreateMenu(processColourMenu);
    glutAddMenuEntry("Red", 1);
    glutAddMenuEntry("Green", 2);
    glutAddMenuEntry("Blue", 3);
    glutAddMenuEntry("Purple", 4);
    glutAddMenuEntry("Yellow", 5);
    glutAddMenuEntry("Random", 6);

    int colourMenuMain = glutCreateMenu(processColourMain);
    glutAddMenuEntry("Red", 1);
    glutAddMenuEntry("Green", 2);
    glutAddMenuEntry("Blue", 3);
    glutAddMenuEntry("Purple", 4);
    glutAddMenuEntry("Yellow", 5);
    glutAddMenuEntry("Random", 6);

    int sizeMenuBrush = glutCreateMenu(processBrushSizeMenu);
    glutAddMenuEntry("4px", 4);
    glutAddMenuEntry("8px", 8);
    glutAddMenuEntry("12px", 12);
    glutAddMenuEntry("16px", 16);

    int shapeMenu = glutCreateMenu(processShapeMenu);
    glutAddMenuEntry("Point", 1);
    glutAddMenuEntry("Line", 2);
    glutAddMenuEntry("Rectangle", 3);
    glutAddMenuEntry("Ellipse", 4);
    glutAddSubMenu("Airbrush", sizeMenuBrush);
    glutAddMenuEntry("Poly line", 5);

    int eraserSizeMenu = glutCreateMenu(processEraserSizeMenu);
    glutAddMenuEntry("Small", 2);
    glutAddMenuEntry("Medium", 6);
    glutAddMenuEntry("Large", 10);

    int sizeMenu = glutCreateMenu(processSizeMenu);
    glutAddMenuEntry("4px", 4);
    glutAddMenuEntry("8px", 8);
    glutAddMenuEntry("12px", 12);
    glutAddMenuEntry("16px", 16);
    glutAddMenuEntry("20px", 20);

    int main_id = glutCreateMenu(processMainMenu);
    glutAddSubMenu("Line Colour", colourMenu);
    glutAddSubMenu("Inner Colour", colourMenuMain);
    glutAddSubMenu("Shapes", shapeMenu);
    glutAddSubMenu("Size", sizeMenu);
    glutAddSubMenu("Eraser", eraserSizeMenu);
    glutAddMenuEntry("Undo", 2);
    glutAddMenuEntry("Redo", 3);
    glutAddMenuEntry("Clear", 1);
    glutAddMenuEntry("Quit", 0);
    glutAttachMenu(GLUT_RIGHT_BUTTON);
}

void Paint::processEraserSizeMenu(int value) {
    glutSetCursor(GLUT_CURSOR_RIGHT_ARROW);
    drawer.setLineWidth(value);
    drawer.setLineColour(Colour{1, 1, 1});
}

void Paint::processShapeMenu(int value) {
    is_polyline = false;
    if (value == 5) {
        is_polyline = true;
        value = 2;
    }

    drawer.setDrawer(DrawerNames(value));
}

void Paint::processColourMenu(int value) {
    is_second = false;
    is_random = false;

    switch (value) {
        case 1: // red
            drawer.setLineColour(Colour{1, 0, 0});
            break;
        case 2: // green
            drawer.setLineColour(Colour{0, 1, 0});
            break;
        case 3: // blue
            drawer.setLineColour(Colour{0, 0, 1});
            break;
        case 4: // purple
            drawer.setLineColour(Colour{0.5, 0, 0.5});
            break;
        case 5: // yellow
            drawer.setLineColour(Colour{1.0, 1.0, 0});
            break;
        case 6: // random
            is_random = true;
            break;
        default:
            break;
    }
}

void Paint::processBrushSizeMenu(int value) {
    drawer.setDrawer(DrawerNames::brush);
    drawer.setLineWidth(value);
}

void Paint::processMainMenu(int value) {
    switch (value) {
        case 0:
            quit();
            break;
        case 1:
            clear();
            break;
        case 2:
            undo();
            break;
        case 3:
            redo();
            break;
        default:
            break;
    }
}

void Paint::reshape(int w, int h) {
    window_w = w;
    window_h = h;
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, w, 0, h);

    glMatrixMode(GL_MODELVIEW);
    glViewport(0, 0, w, h);
}

void Paint::motion(int x, int y) {
    y = window_h - y;

    if (!drawer.isOneClickable()) {
        return;
    }

    Dot dot = {x, y, Colour{0, 0, 0}};
    auto points = drawer.draw(dot, dot);
    dots.insert(dots.end(), points.begin(), points.end());
}

void Paint::mouse(int bin, int state, int x, int y) {
    if (bin != GLUT_LEFT_BUTTON || state != GLUT_DOWN) {
        return;
    }

    y = window_h - y;

    if (is_random) {
        srand(time(NULL));

        float red = float(rand()) / float(RAND_MAX);
        float green = float(rand()) / float(RAND_MAX);
        float blue = float(rand()) / float(RAND_MAX);

        drawer.setLineColour(Colour{red, green, blue});
    }

    if (drawer.isOneClickable()) {
        undo_history.push_back(dots.size());
        auto points = drawer.draw(Dot(x, y, Colour{0, 0, 0}), Dot(x, y, Colour{0, 0, 0}));
        dots.insert(dots.end(), points.begin(), points.end());

        return;
    }

    if (!is_second) {
        tmp_x = x;
        tmp_y = y;
        is_second = true;

        return;
    }

    undo_history.push_back(dots.size());
    auto points = drawer.draw(Dot(tmp_x, tmp_y, Colour{0, 0, 0}), Dot(x, y, Colour{0, 0, 0}));
    dots.insert(dots.end(), points.begin(), points.end());

    if (is_polyline) {
        tmp_x = x;
        tmp_y = y;
    } else {
        is_second = false;
    }
}

void Paint::redo() {
    if (redo_history.size() <= 1) {
        return;
    }
    undo_history.push_back(redo_history.back());
    redo_history.pop_back();
    int numRemove = redo_history.back() - dots.size();
    for (int i = 0; i < numRemove; i++) {
        dots.push_back(redo_dots.back());
        redo_dots.pop_back();
    }

}

void Paint::undo() {
    if (undo_history.empty()) {
        return;
    }

    if (undo_history.back() != dots.size() && redo_history.back() != dots.size()) {
        redo_history.push_back(dots.size());
    }
    int numRemove = dots.size() - undo_history.back();
    for (int i = 0; i < numRemove; i++) {
        redo_dots.push_back(dots.back());
        dots.pop_back();
    }
    redo_history.push_back(undo_history.back());
    undo_history.pop_back();
}

void Paint::quit() {
    exit(0);
}

void Paint::clear() {
    dots.clear();
    undo_history.clear();
    redo_dots.clear();
    redo_history.clear();
    glClear(GL_COLOR_BUFFER_BIT);
    glutSwapBuffers();
}

void Paint::display() {
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    glPointSize(3);
    glBegin(GL_POINTS);
    for (auto &dot: dots) {
        Colour colour = dot.getColor();
        glColor3f(colour.r, colour.g, colour.b);
        glVertex2i(dot.getX(), dot.getY());
    }

    for (auto &dot: temp_dots) {
        Colour colour = dot.getColor();
        glColor3f(colour.r, colour.g, colour.b);
        glVertex2i(dot.getX(), dot.getY());
    }
    glEnd();
    glutSwapBuffers();
}

void Paint::processSizeMenu(int value) {
    drawer.setLineWidth(value);
}

void Paint::processColourMain(int value) {
    is_second = false;
    is_random = false;

    switch (value) {
        case 1: // red
            drawer.setMainColour(Colour{1, 0, 0});
            break;
        case 2: // green
            drawer.setMainColour(Colour{0, 1, 0});
            break;
        case 3: // blue
            drawer.setMainColour(Colour{0, 0, 1});
            break;
        case 4: // purple
            drawer.setMainColour(Colour{0.5, 0, 0.5});
            break;
        case 5: // yellow
            drawer.setMainColour(Colour{1.0, 1.0, 0});
            break;
        case 6: // random
            is_random = true;
            break;
        default:
            break;
    }
}

int Paint::tmp_x, Paint::tmp_y; // store the first point when shape is line, rectangle or circle
bool Paint::is_second;
bool Paint::is_random;
bool Paint::is_polyline;
float Paint::window_w;
float Paint::window_h;

std::vector<Dot> Paint::dots;        // store all the points until clear
std::list<int> Paint::undo_history; // record for undo, maximum 20 shapes in history
std::list<int> Paint::redo_history; // record for redo, maximum 20 shapes in history
std::vector<Dot> Paint::redo_dots;  // store the dots after undo temporaly
std::vector<Dot> Paint::temp_dots;

std::unordered_map<int, Dot> Paint::matrix;

Drawer Paint::drawer;