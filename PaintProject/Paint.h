#pragma once

#include <vector>
#include <list>
#include "Figures/Dot.h"
#include "Drawer.h"

class Paint {
public:
    static void display();

    static void clear();

    static void quit();

    static void undo();

    static void redo();

    static void drawDot(int mousex, int mousey);

    static void drawBrush(int x, int y);

    static void drawLine(int x1, int y1, int x2, int y2);

    static void drawRectangle(int x1, int y1, int x2, int y2);

    static void drawCircle(int x1, int y1, int x2, int y2);

    static void drawRadialBrush(int x, int y);

    static void erase(int x, int y);

    static void mouse(int bin, int state, int x, int y);

    static void motion(int x, int y);

    static void reshape(int w, int h);

    static void processMainMenu(int value);

    static void processBrushSizeMenu(int value);

    static void processColourMenu(int value);

    static void processShapeMenu(int value);

    static void processEraserSizeMenu(int value);

    static void processRadicalBrushMenu(int value);

    static void createOurMenu();

    static void init();

    static void FPS(int val);

    static void passiveMouse(int x, int y);

    static void callbackInit();

    static void start(int argc, char **argv);


private:
    static float red, green, blue;
    static int tmpx, tmpy; // store the first point when shape is line, rectangle or circle
    static int brushSize;
    static int eraserSize;
    static bool isSecond;
    static bool isRandom;
    static bool isEraser;
    static bool isRadial;
    static float window_w;
    static float window_h;
    static int shape;

    static std::vector<Dot> dots;        // store all the points until clear
    static std::list<int> undoHistory; // record for undo, maximum 20 shapes in history
    static std::list<int> redoHistory; // record for redo, maximum 20 shapes in history
    static std::vector<Dot> redoDots;  // store the dots after undo temporaly

    static Drawer drawer;
};
