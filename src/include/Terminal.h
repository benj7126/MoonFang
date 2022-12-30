#pragma once

#include "PT.h"
#include "Token.h"

#include <string>
#include <array>
#include <memory>

#include <cairo/cairo-xlib-xrender.h>
#include <cairo/cairo-xlib.h>
#include <X11/extensions/Xrender.h>

#include "Graphics/Canvas.h"

class Terminal{
private:
    PT pt;

    Token token;

    int cursorX = 0;
    int cursorY = 0;

    std::array<std::string, 100> lines;
    int lineOffset = 0;

    int x = 0;
    int y = 0;
    int width = 0;
    int height = 0;

    int scroll = 0; // the amount of lines scrolled down
    int deletedLines = 0;
   
public:
    void PressChar(std::string inpString, int keysym, int status);
    void Draw(std::shared_ptr<Graphics::Canvas> CV);
    bool SetTermProperties(int _x, int _y, int _width, int _height);
    bool Update();

};
