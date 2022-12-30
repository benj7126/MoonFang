#include "Terminal.h"

#include <iostream>
#include <pango/pangocairo.h>

void Terminal::PressChar(std::string inpString, int keysym, int status) {
    // need to do some char conversion... from keysum to
    for (char c : inpString) {
        pt.SendPTChars(&c, 1);
    }

    /* curString += inpString; */
    /* if (keysym == 65293) {// enter */
    /*     lines.push_back(curString); */
    /*     curString = ""; */
    /* } */
}

void Terminal::Draw(std::shared_ptr<Graphics::Canvas> CV) {
    CV->SetFont("Mono Normal 9");
    CV->SetColor(0.8, 0.8, 0.8);

    double x = 5;
    double y = 5;//12 + 5;
    for (int lineIDX = lineOffset; lineIDX < lines.size(); lineIDX++) {
        // Holds the height of the largest char, as given by
        // canvas->DrawText().
        int LargestCharHeight = 7;

        std::string &line = lines[lineIDX];

        for (char c : line) {
            auto TextInfo     = CV->DrawText(x, y, std::string{c});
            LargestCharHeight = LargestCharHeight < TextInfo.Height ? TextInfo.Height : LargestCharHeight;

            x += TextInfo.Width;
            if (x >= width - 12) {
                x = 5;
                y += LargestCharHeight * 2;
            }
        }

        x = 5;
        y += LargestCharHeight * 2;
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

bool Terminal::Update() {
    // the while loop might be a bad idea...
    // idk...
    bool changedTerm = false;
    while (true) {
        char inp = pt.GetPTInput();

        if (pt.ignore) {
            pt.ignore = false;
            return changedTerm;
        }

        if (inp == '\n') {
            cursorY += 1;
            cursorX = 0;
            return true;
        }

        token.AddChar(inp);
        if (token.IsEnded()) {
            if (token.type == UTF8_T){
                //std::cout << "Y; " << cursorY << std::endl;
                lines[cursorY] += inp;
            }

            token.Clear();

            changedTerm = true;
        }
    }
}
