#pragma once

#include "Color.h"

struct MFCursor{
    int x = 0;
    int y = 0;
    Color foregroundColor{255, 255, 255};
    Color backgroundColor{255, 255, 255};

    bool BracketedPasteMode = false;
};
