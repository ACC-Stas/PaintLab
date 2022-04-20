#include "Paint.h"
#include <vector>
#include <list>
#include "Figures/Dot.h"
#include "Figures/Drawable.h"
#include "Figures/Line.h"
#include "Figures/Rectangle.h"
#include "Drawer.h"

#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/freeglut.h>
#include <memory>
#include <complex>

void Paint::start(int argc, char **argv) {
    red = 1.0, green = 0.0, blue = 0.0;
    brushSize = 4;
    eraserSize = 1;
    isSecond = false;
    isRandom = false;
    isEraser = false;
    isRadial = false;
    window_w = 500;
    window_h = 500;
    shape = 1; // 1:point, 2:line, 3:rectangle, 4:circle, 5:brush

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
    drawDot(x, y);
}

void Paint::FPS(int val) {
    glutPostRedisplay();
    glutTimerFunc(0, FPS, 0);
}

void Paint::init() {
    /* background color */
    glClearColor(1.0, 1.0, 1.0, 1.0);
    glColor3f(red, green, blue);

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

    int sizeMenu = glutCreateMenu(processBrushSizeMenu);
    glutAddMenuEntry("4px", 4);
    glutAddMenuEntry("8px", 8);
    glutAddMenuEntry("12px", 12);
    glutAddMenuEntry("16px", 16);

    int shapeMenu = glutCreateMenu(processShapeMenu);
    glutAddMenuEntry("Paint", 1);
    glutAddMenuEntry("Line", 2);
    glutAddMenuEntry("Rectangle", 3);
    glutAddMenuEntry("Circle", 4);
    glutAddSubMenu("Airbrush", sizeMenu);

    int eraserSizeMenu = glutCreateMenu(processEraserSizeMenu);
    glutAddMenuEntry("Small", 2);
    glutAddMenuEntry("Medium", 6);
    glutAddMenuEntry("Large", 10);

    int radicalBrushMenu = glutCreateMenu(processRadicalBrushMenu);
    glutAddMenuEntry("True", 1);
    glutAddMenuEntry("False", 2);

    int main_id = glutCreateMenu(processMainMenu);
    glutAddSubMenu("Colour", colourMenu);
    glutAddSubMenu("Shapes", shapeMenu);
    glutAddSubMenu("Radical Paint Brush", radicalBrushMenu);
    glutAddSubMenu("Eraser", eraserSizeMenu);
    glutAddMenuEntry("Undo", 2);
    glutAddMenuEntry("Redo", 3);
    glutAddMenuEntry("Clear", 1);
    glutAddMenuEntry("Quit", 0);
    glutAttachMenu(GLUT_RIGHT_BUTTON);
}

void Paint::processRadicalBrushMenu(int value) {
    isRadial = value == 1;
}

void Paint::processEraserSizeMenu(int value) {
    glutSetCursor(GLUT_CURSOR_RIGHT_ARROW);
    eraserSize = value;
    isEraser = true;
}

void Paint::processShapeMenu(int value) {
    shape = value;
    isEraser = false;
    isSecond = false;
    isRadial = false;

    switch (shape) {
        case 1:
            glutSetCursor(GLUT_CURSOR_RIGHT_ARROW);
            break;
        case 2:
        case 3:
        case 4:
            glutSetCursor(GLUT_CURSOR_CROSSHAIR);
            break;
    }
}

void Paint::processColourMenu(int value) {
    isSecond = false;
    isEraser = false;
    isRandom = false;

    switch (value) {
        case 1: // red
            red = 1.0;
            green = 0.0;
            blue = 0.0;
            break;
        case 2: // green
            red = 0.0;
            green = 1.0;
            blue = 0.0;
            break;
        case 3: // blue
            red = 0.0;
            green = 0.0;
            blue = 1.0;
            break;
        case 4: // purple
            red = 0.5;
            green = 0.0;
            blue = 0.5;
            break;
        case 5: // yellow
            red = 1.0;
            green = 1.0;
            blue = 0.0;
            break;
        case 6: // random
            isRandom = true;
            break;
    }
}

void Paint::processBrushSizeMenu(int value) {
    shape = 5;
    isEraser = false;
    brushSize = value;
    glutSetCursor(GLUT_CURSOR_CROSSHAIR);
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
    if (isEraser)
        erase(x, y);
    else {
        if (shape == 1) {
            if (isRadial)
                drawRadialBrush(x, y);
            else
                drawDot(x, y);
        }
        if (shape == 5)
            drawBrush(x, y);
    }
}

void Paint::mouse(int bin, int state, int x, int y) {
    if (bin == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        if (isRandom) {
            srand(time(NULL));
            red = float(rand()) / float(RAND_MAX);
            green = float(rand()) / float(RAND_MAX);
            blue = float(rand()) / float(RAND_MAX);
        }
        if (isEraser) {
            undoHistory.push_back(dots.size());
            erase(x, y);
        } else {
            if (shape == 1) {
                undoHistory.push_back(dots.size());
                if (isRadial)
                    drawRadialBrush(x, y);
                else
                    drawDot(x, y);
            } else if (shape == 5) {
                undoHistory.push_back(dots.size());
                drawBrush(x, y);
            } else {
                if (!isSecond) {
                    tmpx = x;
                    tmpy = y;
                    isSecond = true;
                } else {
                    if (undoHistory.back() != dots.size())
                        undoHistory.push_back(dots.size());
                    if (shape == 2)
                        drawLine(tmpx, tmpy, x, y);
                    else if (shape == 3)
                        drawRectangle(tmpx, tmpy, x, y);
                    else if (shape == 4)
                        drawCircle(tmpx, tmpy, x, y);
                    isSecond = false;
                }
            }
        }
        if (undoHistory.size() > 20) {
            undoHistory.pop_front();
        }
    }
}

void Paint::erase(int x, int y) {
    for (int i = -eraserSize; i <= eraserSize; i++) {
        for (int j = -eraserSize; j <= eraserSize; j++) {
            drawDot(x + i, y + j);
        }
    }
}

void Paint::drawRadialBrush(int x, int y) {
    int xc = glutGet(GLUT_WINDOW_WIDTH) / 2;
    int yc = glutGet(GLUT_WINDOW_HEIGHT) / 2;
    int dx, dy;

    dx = xc - x;
    dy = yc - y;

    drawDot(xc + dx, yc + dy);
    drawDot(xc - dx, yc + dy);
    drawDot(xc + dx, yc - dy);
    drawDot(xc - dx, yc - dy);
    drawDot(xc + dy, yc + dx);
    drawDot(xc - dy, yc + dx);
    drawDot(xc + dy, yc - dx);
    drawDot(xc - dy, yc - dx);
}

void Paint::drawCircle(int x1, int y1, int x2, int y2) {
    int r = sqrt(std::pow(x1 - x2, 2) + std::pow(y1 - y2, 2));
    double d;
    int x, y;

    x = 0;
    y = r;
    d = 1.25 - r;

    while (x <= y) {
        drawDot(x1 + x, y1 + y);
        drawDot(x1 - x, y1 + y);
        drawDot(x1 + x, y1 - y);
        drawDot(x1 - x, y1 - y);
        drawDot(x1 + y, y1 + x);
        drawDot(x1 - y, y1 + x);
        drawDot(x1 + y, y1 - x);
        drawDot(x1 - y, y1 - x);
        x++;
        if (d < 0) {
            d += 2 * x + 3;
        } else {
            y--;
            d += 2 * (x - y) + 5;
        }
    }
}

void Paint::drawRectangle(int x1, int y1, int x2, int y2) {
    std::unique_ptr<Drawable> rectangle = std::make_unique<Rectangle>();
    rectangle->setMainColour(Colour{red, green, blue});
    rectangle->setLineWidth(1);
    rectangle->setLineColour(Colour{red, green, blue});

    y1 = window_h - y1;
    y2 = window_h - y2;
    Dot dot1 = Dot{x1, y1, Colour{red, green, blue}};
    Dot dot2 = Dot{x2, y2, Colour{red, green, blue}};

    auto points = rectangle->draw(dot1, dot2);

    dots.insert(dots.end(), points.begin(), points.end());
}

void Paint::drawLine(int x1, int y1, int x2, int y2) {
    std::unique_ptr<Drawable> drawable = std::make_unique<Line>();
    drawable->setLineColour(Colour{red, green, blue});
    drawable->setLineWidth(1);
    auto points = drawable->draw(Dot(x1, window_h - y1, Colour{red, green, blue}),
                                 Dot(x2, window_h - y2, Colour{red, green, blue}));

    dots.insert(dots.end(), points.begin(), points.end());
}

void Paint::drawBrush(int x, int y) {
    for (int i = 0; i < brushSize; i++) {
        int randX = rand() % (brushSize + 1) - brushSize / 2 + x;
        int randY = rand() % (brushSize + 1) - brushSize / 2 + y;
        drawDot(randX, randY);
    }
}

void Paint::drawDot(int mousex, int mousey) {
    Dot newDot(mousex, window_h - mousey, Colour{isEraser ? 1.0 : red, isEraser ? 1.0 : green, isEraser ? 1.0 : blue});
    dots.push_back(newDot);
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
    std::cout << "Thank you for using this Paint tool! Goodbye!" << std::endl;
    exit(0);
}

void Paint::clear() {
    dots.clear();
    undoHistory.clear();
    redoDots.clear();
    redoHistory.clear();
    glClear(GL_COLOR_BUFFER_BIT);
    glutSwapBuffers();
    time_t rawtime;
    struct tm *timeinfo;
    time(&rawtime);
    timeinfo = localtime(&rawtime);
    std::cout << asctime(timeinfo)
              << "[Info] The window and the history are cleared successfully.\n";
}

void Paint::display() {
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    glPointSize(200);
    glBegin(GL_POINTS);
    for (auto &dot: dots) {
        Colour colour = dot.getColor();
        glColor3f(colour.r, colour.g, colour.b);
        glVertex2i(dot.getX(), dot.getY());
    }
    glEnd();
    glutSwapBuffers();
}

float Paint::red, Paint::green, Paint::blue;
int Paint::tmpx, Paint::tmpy; // store the first point when shape is line, rectangle or circle
int Paint::brushSize;
int Paint::eraserSize;
bool Paint::isSecond;
bool Paint::isRandom;
bool Paint::isEraser;
bool Paint::isRadial;
float Paint::window_w;
float Paint::window_h;
int Paint::shape;

std::vector<Dot> Paint::dots;        // store all the points until clear
std::list<int> Paint::undoHistory; // record for undo, maximum 20 shapes in history
std::list<int> Paint::redoHistory; // record for redo, maximum 20 shapes in history
std::vector<Dot> Paint::redoDots;  // store the dots after undo temporaly

Drawer Paint::drawer;