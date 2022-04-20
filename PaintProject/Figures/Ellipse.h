#pragma once

#include "Drawable.h"

class Ellipse : public Drawable {
public:
    std::vector<Dot> draw(Dot dot1, Dot dot2) override;

};
