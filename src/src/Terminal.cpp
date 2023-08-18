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

        CV->MoveTo(x, y);

        int LargestCharHeight = 7;

        std::vector<MFChar> &line = lines[lineIDX];

        for (MFChar c : line) {
            c.Draw(CV, x, y);
            x += 7;
        }

        if (lineIDX < line.size() - 1) {
            x = 5;
            y += LargestCharHeight * 2;
        }
    }

    // scuffed cursor (for now)
    // CV->DrawText(x, y, "█");
    // pango cant handle it .... 
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
            MFC.x = 0;
            MFC.y += 1;
            return true;
        }

        token.AddChar(inp);
        if (token.IsEnded()) {
            if (token.type == UTF8_T) {
                // std::cout << "utf8; " << token.curSaveValue << std::endl;
                /*
                if (MFC.BracketedPasteMode){
                    lines[MFC.y].push_back(MFChar{"[", MFC});
                    MFC.x += 1;
                }
                */

                lines[MFC.y].push_back(MFChar{token.curSaveValue, MFC});

                /*
                if (MFC.BracketedPasteMode){
                    lines[MFC.y].push_back(MFChar{"[", MFC});
                    MFC.x += 1;
                }
                */

                MFC.x += 1;
            } else {
                // std::cout << "found token of type " << token.type << std::endl;
            }

            token.Clear();

            changedTerm = true;
        }
    }
}
