#pragma once

#include "Drawable.h"

class RadialBrush : Drawable {
    std::vector<Dot> draw(Dot dot1, Dot dot2) override;
};
