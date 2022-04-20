#pragma once

#include "Drawable.h"
#include "Line.h"

class Rectangle : public Drawable {
    std::vector<Dot> draw(Dot dot1, Dot dot2) override;
};
