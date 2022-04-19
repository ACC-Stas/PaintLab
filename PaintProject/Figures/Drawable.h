#pragma once

#include "Dot.h"

class Drawable {
public:
    virtual void Draw(Dot first, Dot second) = 0;
};