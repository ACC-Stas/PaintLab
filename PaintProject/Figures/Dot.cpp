#include "Dot.h"


Dot::Dot() {

}

Dot::Dot(int x, int y, Colour colour) {
    x_ = x;
    y_ = y;
    this->colour_ = colour;
}

Dot::~Dot() {

}

int Dot::getX() {
    return x_;
}

int Dot::getY() {
    return y_;
}

void Dot::setPosition(int x, int y) {
    x_ = x;
    y_ = y;
}

void Dot::setColour(Colour colour) {
    this->colour_ = colour;
}

Colour Dot::getColor() {
    return this->colour_;
}
