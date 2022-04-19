#include "Dot.h"


Dot::Dot() {

}

Dot::Dot(int x, int y, Colour colour) {
    newX = x;
    newY = y;
    this->colour_ = colour;
}

Dot::~Dot() {

}

int Dot::getX() {
    return newX;
}

int Dot::getY() {
    return newY;
}

void Dot::setPosition(int x, int y) {
    newX = x;
    newY = y;
}

void Dot::setColour(Colour colour) {
    this->colour_ = colour;
}

Colour Dot::getColor() {
    return this->colour_;
}
