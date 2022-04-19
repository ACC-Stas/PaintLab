#pragma once
#include <iostream>
#include <string>

struct Colour {
    double r;
    double g;
    double b;
};

class Dot {
public:
    Dot();
    Dot(int, int, Colour);
    ~Dot();

    int getX();
    int getY();
    Colour getColor();


    void setPosition(int, int);
    void setColour(Colour);

private:
    int newX;
    int newY;
    Colour colour_;
};
