#pragma once

#include "Drawable.h"

class Point : public Drawable {
public:
    std::vector<Dot> draw(Dot dot1, Dot dot2 = Dot()) override;
};
