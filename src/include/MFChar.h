#pragma once

#include <string>
#include <memory>

#include "Color.h"
#include "Cursor.h"

#include "Graphics/Canvas.h"

class MFChar{
private:
    Color foregroundColor;
    Color backgroundColor;

    std::string text;

public:
    MFChar(std::string chars, MFCursor &cursor);
    void Draw(std::shared_ptr<Graphics::Canvas> CV, int x, int y);
};
