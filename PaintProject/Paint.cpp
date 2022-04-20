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
    isSecond = false;
    isRandom = false;
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

    tempDots.clear();

    if (drawer.isOneClickable() || !isSecond) {
        return;
    }
    Dot tmp = Dot{tmpx, tmpy, Colour{0, 0, 0}};
    Dot current = Dot(x, y, Colour{0, 0, 0});
    auto points = drawer.draw(tmp, current);
    tempDots.insert(tempDots.end(), points.begin(), points.end());
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
    glutAddSubMenu("Colour", colourMenu);
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
    drawer.setDrawer(DrawerNames(value));
}

void Paint::processColourMenu(int value) {
    isSecond = false;
    isRandom = false;

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
            isRandom = true;
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

    if (isRandom) {
        srand(time(NULL));

        float red = float(rand()) / float(RAND_MAX);
        float green = float(rand()) / float(RAND_MAX);
        float blue = float(rand()) / float(RAND_MAX);

        drawer.setLineColour(Colour{red, green, blue});
    }

    if (undoHistory.size() > 20) {
        undoHistory.pop_front();
    }

    if (drawer.isOneClickable()) {
        undoHistory.push_back(dots.size());
        auto points = drawer.draw(Dot(x, y, Colour{0, 0, 0}), Dot(x, y, Colour{0, 0, 0}));
        dots.insert(dots.end(), points.begin(), points.end());

        return;
    }

    if (!isSecond) {
        tmpx = x;
        tmpy = y;
        isSecond = true;
    } else {
        if (undoHistory.back() != dots.size()) {
            undoHistory.push_back(dots.size());
        }

        auto points = drawer.draw(Dot(tmpx, tmpy, Colour{0, 0, 0}), Dot(x, y, Colour{0, 0, 0}));
        dots.insert(dots.end(), points.begin(), points.end());

        isSecond = false;
    }
}

void Paint::redo() {
    if (redoHistory.size() <= 1) {
        return;
    }
    undoHistory.push_back(redoHistory.back());
    redoHistory.pop_back();
    int numRemove = redoHistory.back() - dots.size();
    for (int i = 0; i < numRemove; i++) {
        dots.push_back(redoDots.back());
        redoDots.pop_back();
    }

}

void Paint::undo() {
    if (undoHistory.empty()) {
        return;
    }

    if (undoHistory.back() != dots.size() && redoHistory.back() != dots.size()) {
        redoHistory.push_back(dots.size());
    }
    int numRemove = dots.size() - undoHistory.back();
    for (int i = 0; i < numRemove; i++) {
        redoDots.push_back(dots.back());
        dots.pop_back();
    }
    redoHistory.push_back(undoHistory.back());
    undoHistory.pop_back();
}

void Paint::quit() {
    exit(0);
}

void Paint::clear() {
    dots.clear();
    undoHistory.clear();
    redoDots.clear();
    redoHistory.clear();
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

    for (auto &dot: tempDots) {
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


int Paint::tmpx, Paint::tmpy; // store the first point when shape is line, rectangle or circle
bool Paint::isSecond;
bool Paint::isRandom;
float Paint::window_w;
float Paint::window_h;

std::vector<Dot> Paint::dots;        // store all the points until clear
std::list<int> Paint::undoHistory; // record for undo, maximum 20 shapes in history
std::list<int> Paint::redoHistory; // record for redo, maximum 20 shapes in history
std::vector<Dot> Paint::redoDots;  // store the dots after undo temporaly
std::vector<Dot> Paint::tempDots;

Drawer Paint::drawer;