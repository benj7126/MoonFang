#pragma once

#include <memory>
#include <string>
#include <vector>

#include "Color.h"
#include "Cursor.h"

#include "Graphics/CoreXFTDraw.h"

class MFChar{
public:
    unsigned int foregroundColor = 0;
    unsigned int backgroundColor = 0;
    bool useBackground = false;

    XftChar32 value = ' ';

    MFChar(XftChar32 chars);
    MFChar();
};
