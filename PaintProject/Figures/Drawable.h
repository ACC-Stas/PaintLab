#pragma once

#include "Dot.h"
#include <vector>

class Drawable {
public:
    virtual std::vector<Dot> Draw(Dot dot1, Dot dot2) = 0;
};