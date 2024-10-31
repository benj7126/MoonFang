#pragma once

#include "PT.h"
#include "Token.h"
#include "MFChar.h"

#include <string>
#include <array>
#include <vector>
#include <memory>

#include <X11/extensions/Xrender.h>
#include "Graphics/CoreXFTDraw.h"

#include "Cursor.h"

class Terminal{
public:
    static Terminal term;
    
    Terminal(){
        // get based on screen size
        lineCount = 120;
        charactersPerLine = 0;

        linesPointer = (MFChar**)malloc(sizeof(void*) * lineCount);
        lines = linesPointer;
        for (int i = 0; i < lineCount; i++){
            linesPointer[i] = (MFChar*)malloc(sizeof(MFChar) * charactersPerLine);
            for (int c = 0; c < charactersPerLine; c++){
                linesPointer[i][c] = MFChar{};
            }
        }

        linesBufferPointer = (MFChar**)malloc(sizeof(void*) * lineCount);
        for (int i = 0; i < lineCount; i++){
            linesBufferPointer[i] = (MFChar*)malloc(sizeof(MFChar) * charactersPerLine);
            for (int c = 0; c < charactersPerLine; c++){
                linesBufferPointer[i][c] = MFChar{};
            }
        }
    }

    PT pt;
    Token token;

    Graphics::CoreXFTDraw* CV;

    int lineCount = 0;
    int charactersPerLine = 0;

    MFChar** lines = nullptr;
    MFChar** linesPointer = nullptr;
    MFChar** linesBufferPointer = nullptr;
    int lineOffset = 0;

    int x = 0;
    int y = 0;
    int width = 0;
    int height = 0;

    int scroll = 0; // the amount of lines scrolled down *up?

    void SetBuffer(bool active) {
        if (active)
            lines = linesPointer;
        else{
            lines = linesBufferPointer;
        }
    }
   
    void PressChar(std::string inpString, int keysym, int status);
    void Draw();
    bool SetTermProperties(int _x, int _y, int _width, int _height);
    bool Update();
    void FixLineOffset();

    void ChangeSize(int w, int h);
    
    void ClearFromLineToLine(int start, int end);
    void DeleteInLineFromCharToChar(int line, int start, int end);
    void ClearInLineFromCharToChar(int line, int start, int end);

    void DrawSingleCharacterAt(MFChar nChar, int gridX, int gridY);
    void DrawSingleCharacterWithCursorAt(MFChar nChar, int gridX, int gridY);
};
