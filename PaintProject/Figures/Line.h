#pragma once
#include "Drawable.h"

class Line : public Drawable {
    std::vector<Dot> Draw(Dot dot1, Dot dot2) override;
};