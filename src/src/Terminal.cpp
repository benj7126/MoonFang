#include "Terminal.h"

#include <iostream>
#include <pango/pangocairo.h>


void Terminal::PressChar(std::string inpString, int keysym, int status) {
    curString += inpString;
    if (keysym == 65293) {// enter
        lines.push_back(curString);
        curString = "";
    }
}

void Terminal::Draw(std::shared_ptr<Graphics::Canvas> CV) {
    CV->SetColor(0.8, 0.8, 0.8);

    double x = 5;
    double y = 12 + 5;
    for (int lineIDX = 0; lineIDX <= lines.size(); lineIDX++) {
        std::string &line = (lineIDX == lines.size() ? curString : lines[lineIDX]);
        CV->SetPos(x, y);

        for (char c : line) {
            auto TextInfo = CV->DrawText(std::string{c});

            x += ((double) TextInfo.Width / PANGO_SCALE);
            CV->SetPos(x, y);
            if (x >= width - 12) {
                x = 5;
                y += 20;
                CV->SetPos(x, y);
            }
        }

        x = 5;
        y += 20;
    }
}

bool Terminal::SetTermProperties(int _x, int _y, int _width, int _height) {
    bool changed = false;

    changed = x != _x || y != _y || width != _width || height != _height;

    x      = _x;
    y      = _y;
    width  = _width;
    height = _height;

    return changed;
}

void Terminal::Update() {
    while (1) {
        char inp = pt.GetPTInput();

        if (pt.ignore){
            pt.ignore = false;
            return;
        }
    }
}
