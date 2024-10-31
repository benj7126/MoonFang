#include "Terminal.h"

#include "Graphics/CoreXFTDraw.h"
#include <iostream>

#include <X11/Xft/Xft.h>
#include <X11/Xlib.h>

#include <cmath>

#include "MFChar.h"

// https://www.x.org/wiki/guide/fonts/

void Terminal::PressChar(std::string inpString, int keysym, int status) {
    // need to do some char conversion... from keysum to

    // std::cout << keysym << std::endl;
    switch(keysym) {
        case XK_Up:
            inpString = "\e[A";
            // std::cout << "test" << std::endl;
            break;
        case XK_Down:
            inpString = "\e[B";
            break;
        case XK_Right:
            inpString = "\e[C"; // does it not send this back..? TODO fix...
            break;
        case XK_Left:
            inpString = "\e[D";
            break;
    }
    
    for (char c : inpString) {
        pt.SendPTChars(&c, 1);
    }

    /* curString += inpString; */
    /* if (keysym == 65293) {// enter */
    /*     lines.push_back(curString); */
    /*     curString = ""; */
    /* } */
}

void Terminal::ChangeSize(int w, int h){
    int oldW = charactersPerLine;

    float midW = (float)w / CV->font->max_advance_width;
    float midH = (float)h / CV->font->height;

    // std::cout << midH << " - " << lineCount << std::endl;

    charactersPerLine = midW + 1;
    
    // lines = (MFChar**)realloc(lines, sizeof(void*) * lineCount);

    for (int i = 0; i < lineCount; i++) {
        int InitStart = oldW;

        /* -- i wont add or remove lines
        if (i >= oldH) {
            InitStart = 0;
            lines[i] = nullptr;
        }
        */

        /*
        std::cout << charactersPerLine << " - " << i << " - " << (sizeof(MFChar) * charactersPerLine) << std::endl;
        std::cout << lines[i] << std::endl;
        std::cout << lines[i]->value << std::endl;
        */
        delete linesPointer[i];
        linesPointer[i] = (MFChar*)realloc(NULL, sizeof(MFChar) * charactersPerLine);
        // std::cout << "did realloc" << std::endl;
        for (int c = InitStart; c < charactersPerLine; c++){
            linesPointer[i][c] = MFChar{};
        }

        delete linesBufferPointer[i];
        linesBufferPointer[i] = (MFChar*)realloc(NULL, sizeof(MFChar) * charactersPerLine);
        // std::cout << "did realloc" << std::endl;
        for (int c = InitStart; c < charactersPerLine; c++){
            linesBufferPointer[i][c] = MFChar{};
        }
    }

    MFCursor::cursor -> widthLimit = charactersPerLine;
    pt.ChangeSize(charactersPerLine, (int)midH);
}

void Terminal::ClearFromLineToLine(int start, int end){
    for (int i = start; i < end; i++){
        for (int c = 0; c < charactersPerLine; c++){
            lines[i][c] = {};
        }
    }

    int y = start * CV->font->height + 12; // + 5;
    int x = 0; //5;

    if (MFCursor::cursor -> useBackground)
        CV->DrawTextRect(x, y, MFCursor::cursor -> backgroundColor, charactersPerLine, start - end);
    else
        CV->ClearTextRect(x, y, charactersPerLine, start - end);
}

void Terminal::DeleteInLineFromCharToChar(int line, int start, int end){
    if (end > charactersPerLine)
        end = charactersPerLine;

    for (int c = start; c < end; c++){
        lines[line][c] = {};
    }

    for (int c = end; c < charactersPerLine; c++){
        lines[line][c + (start-end)] = lines[line][c];
    }

    int y = line * CV->font->height + 12; // + 5;
    int x = start * CV->font->max_advance_width; // + 5;

    if (MFCursor::cursor -> useBackground)
        CV->DrawTextRect(x, y, MFCursor::cursor -> backgroundColor, start - end);
    else
        CV->ClearTextRect(x, y, start - end);
}

void Terminal::ClearInLineFromCharToChar(int line, int start, int end){
    if (end > charactersPerLine)
        end = charactersPerLine;

    for (int c = start; c < end; c++){
        lines[line][c] = {};
    }

    int y = line * CV->font->height + 12; // + 5;
    int x = start * CV->font->max_advance_width; // + 5;

    if (MFCursor::cursor -> useBackground)
        CV -> DrawTextRect(x, y, MFCursor::cursor -> backgroundColor, start - end);
    else
        CV->ClearTextRect(x, y, start - end);
}

void Terminal::DrawSingleCharacterAt(MFChar nChar, int gridX, int gridY){
    int x = CV->font->max_advance_width * gridX; // + 5;
    int y = CV->font->height * gridY + 12; // + 5;

    if (nChar.useBackground)
        CV->DrawTextRect(x, y, nChar.backgroundColor);
    else
        CV->ClearTextRect(x, y);

    CV->DrawText(x, y, &nChar.value, 1, nChar.foregroundColor);
}

void Terminal::DrawSingleCharacterWithCursorAt(MFChar nChar, int gridX, int gridY){
    int x = CV->font->max_advance_width * gridX; // + 5;
    int y = CV->font->height * gridY + 12; // + 5;

    if (nChar.useBackground)
        CV->DrawTextRect(x, y, nChar.backgroundColor);
    else
        CV->ClearTextRect(x, y);
    
    CV->DrawTextRect(x, y, 15);

    CV->DrawText(x, y, &nChar.value, 1, nChar.backgroundColor);
}

void Terminal::FixLineOffset(){
    int y = MFCursor::getY();
    int vy = MFCursor::getVisualY();
    int diff = y - lineOffset;

    if (diff > 5){
    }

}

void Terminal::Draw() {
    int y = 12; // + 5; // + CV->font->height * (line-1);
    for (int lineNr = 0; lineNr < lineCount; lineNr++) {
        MFChar* line = lines[lineNr];
        int x = 0; //5;

        int size   = 0;
        int color  = line[0].backgroundColor;
        bool useBG = line[0].useBackground;

        // Draw BG
        for (int i = 0; i < charactersPerLine; i++) {
            MFChar c = line[i];
            if (c.useBackground != useBG) {
                if (useBG)
                    CV->DrawTextRect(x, y, color, size);

                x += size * CV->font->max_advance_width;
                size  = 0;
                useBG = c.useBackground;
                color = c.backgroundColor;
            } else if (c.backgroundColor != color) {
                if (useBG)
                    CV->DrawTextRect(x, y, color, size);

                x += size * CV->font->max_advance_width;
                size  = 0;
                color = c.backgroundColor;
            }
            size++;
        }
        if (useBG)
            CV->DrawTextRect(x, y, color, size);

        x = 0;
        color = line[0].foregroundColor;

        XftChar32* text = (XftChar32*)malloc(sizeof(XftChar32) * charactersPerLine);
        size = 0;

        bool blank = true;

        // Draw Text
        for (int i = 0; i < charactersPerLine; i++) {
            MFChar c = line[i];

            if (c.foregroundColor != color) {
                if (!blank)
                    CV->DrawText(x, y, text, size, color);

                blank = true;
                color = c.foregroundColor;
                x += CV->font->max_advance_width * size;
                size = 0;
            }

            if (c.value != ' ')
                blank = false;

            text[size] = c.value;
            size++;
        }
        if (!blank)
            CV->DrawText(x, y, text, size, color);

        y += CV->font->height;
    }

    //}

    // scuffed cursor (for now)
    // CV->DrawText(x, y, "█");
    // pango cant handle it ....

    MFChar c = lines[MFCursor::getInternalY()][MFCursor::getX()];
    DrawSingleCharacterWithCursorAt(c, MFCursor::getX(), MFCursor::getVisualY());
}

bool Terminal::SetTermProperties(int _x, int _y, int _width, int _height) {
    if (!(x != _x || y != _y || width != _width || height != _height))
        return false;

    x      = _x;
    y      = _y;
    width  = _width;
    height = _height;

    return true;
}


#include <unistd.h>
bool Terminal::Update() {
    // the while loop might be a bad idea...
    // idk...
    bool changedTerm = false;
    while (true) {
        char inp = pt.GetPTInput();

        if (pt.ignore) {
            pt.ignore = false;
            break;
        }

        // std::cout << inp << " - " << (int)inp << " - stuff" << std::endl;

        if (inp == '\r') continue;
        //if ((int)inp == 7) continue;

        if (inp == '\n') {
            MFCursor::set(0, MFCursor::getY()+1);
            // FixLineOffset(CV);
            continue;
        }
        
        if ((int)inp == 8){
            MFCursor::move(-1, 0);
            continue;
        }

        if (inp == '\t') {
            MFCursor::setX((int)(std::ceil((float)MFCursor::getX() / 4)) * 4);
            continue;
        }

        token.AddChar(inp);
        if (token.IsEnded()) {
            // std::cout << "found token with " << (int)token.curSaveValue[0] << std::endl;

            if (token.type == UTF8_T){ // && !((int)token.curSaveValue.c_str()[0] < 32)) {
                // std::cout << token.curSaveValue.size() << " -s" << std::endl;
                const char* chars = token.curSaveValue.c_str();
                XftChar32 c = (XftChar32)(chars[0] << 24) | (chars[1] << 16) | (chars[2] << 8) | chars[3];

                if (c >= 32) {
                    MFChar nChar = {c};
                    lines[MFCursor::getInternalY()][MFCursor::getX()] = nChar;
                    DrawSingleCharacterAt(nChar, MFCursor::getX(), MFCursor::getVisualY());
                    MFCursor::move(1, 0);
                }


            } else {
                // std::cout << "found token of type " << token.type << std::endl;

                // utf8 dose not warrant a term change
            }

            if (token.Clear())
                changedTerm = true;

            // FixLineOffset(CV); // movement CSI things ^^

            /*
            if (MFCursor::Cursor.doReDraw()){
                MFChar c = lines[MFCursor::Cursor.lastY].chars[MFCursor::Cursor.lastX];
                DrawSingleCharacterAt(CV, c, MFCursor::Cursor.lastX, MFCursor::Cursor.lastY);

                c = lines[MFCursor::Cursor.y].chars[MFCursor::Cursor.x];
                DrawSingleCharacterWithCursorAt(CV, c, MFCursor::Cursor.x, MFCursor::Cursor.y, MFCursor::Cursor.x, MFCursor::Cursor.y);

                // last line
                int x = CV->font->max_advance_width * MFCursor::Cursor.x + 5;
                int y = CV->font->height * MFCursor::Cursor.y + 5 + 12;

                CV->DrawTextRect(x, y, 1, 15);

                MFCursor::Cursor.didRedraw();
            }
            */

            // usleep(1000000); break;
        }
    }

    if (MFCursor::doReDraw()){
        MFChar c = lines[MFCursor::getLInternalY()][MFCursor::getLX()];
        DrawSingleCharacterAt(c, MFCursor::getLX(), MFCursor::getLVisualY());

        // std::cout << MFCursor::getInternalY() << " - " << MFCursor::getX() << ": " << lines[MFCursor::getInternalY()][MFCursor::getX()].value << std::endl;

        c = lines[MFCursor::getInternalY()][MFCursor::getX()];
        DrawSingleCharacterWithCursorAt(c, MFCursor::getX(), MFCursor::getVisualY());

        // last line
        /*
        int x = CV->font->max_advance_width * MFCursor::getX() + 5;
        int y = CV->font->height * MFCursor::getY() + 5 + 12;

        CV->DrawTextRect(x, y, 1, 15);
        */

        MFCursor::didRedraw();
    }
    
    return changedTerm;
}
