#pragma once

#include "Drawable.h"

class RadialBrush : public Drawable {
public:
    std::vector<Dot> draw(Dot dot1, Dot dot2) override;
};
