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
    CV->SetFont("Mono Normal 9");
    CV->SetColor(0.8, 0.8, 0.8);

    double x = 5;
    double y = 12 + 5;
    for (int lineIDX = 0; lineIDX <= lines.size(); lineIDX++) {
        // Holds the height of the largest char, as given by
        // canvas->DrawText().
        int LargestCharHeight = 7;

        std::string &line = (lineIDX == lines.size() ? curString : lines[lineIDX]);

        for (char c : line) {
            auto TextInfo = CV->DrawText(x, y, std::string{c});
            LargestCharHeight = LargestCharHeight < TextInfo.Height ? TextInfo.Height : LargestCharHeight;

            x += TextInfo.Width;
            if (x >= width - 12) {
                x = 5;
                y += LargestCharHeight*2;
            }
        }

        x = 5;
        y += LargestCharHeight*2;
    }
}

bool Terminal::SetTermProperties(int _x, int _y, int _width, int _height) {
    bool changed = x != _x || y != _y || width != _width || height != _height;

    x      = _x;
    y      = _y;
    width  = _width;
    height = _height;

    return changed;
}

void Terminal::Update() {
    while (true) {
        char inp = pt.GetPTInput();

        if (pt.ignore){
            pt.ignore = false;
            return;
        }

        token.AddChar(inp);
        if (token.IsEnded()){
            std::cout << token.type << std::endl;
            if (token.type == UTF8_T)
                curString += std::string{inp};
            token.Clear();
        }
    }
}
