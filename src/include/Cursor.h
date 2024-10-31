#pragma once

#include "Color.h"
#include <X11/Xlib.h>
#include <X11/Xft/Xft.h>

#include <algorithm>

#include <iostream>

class MFCursor{
private:
    int x = 0;
    int y = 0;

    int lastX = 0;
    int lastY = 0;

    int sx = 0;
    int sy = 0;

    // int lowestY = 0;
    static MFCursor* cursorPointer;
    static MFCursor* cursorBufferPointer;

public:
    int widthLimit = 0;

    static MFCursor* cursor;
    const unsigned int defaultForegroundColor = 15; // need to set from file or something i think..?
    const unsigned int defaultBackgroundColor = 0;

    static void SetCursorBuffer(bool active){
        if (active)
            cursor = cursorPointer;
        else
            cursor = cursorBufferPointer;
    }

    static void savePosition(){
        cursor -> sx = cursor -> x;
        cursor -> sy = cursor -> y;
    }

    static void loadPosition(){
        cursor -> x = cursor -> sx;
        cursor -> y = cursor -> sy;
    }

    static bool doReDraw(){
        int sx = cursor -> x;
        int sy = cursor -> y;

        cursor -> x = std::min(std::max(cursor -> x, 0), cursor -> widthLimit);
        cursor -> y = std::max(cursor -> y, 0);

        return cursor -> x != cursor -> lastX || cursor -> y != cursor -> lastY || cursor -> x != sx || cursor -> y != sy;
    }
    static void didRedraw(){
        cursor -> lastX = cursor -> x;
        cursor -> lastY = cursor -> y;
    }
    static void move(int dx, int dy){
        cursor -> x += dx;
        cursor -> y += dy;
    }
    static void setX(int nx){
        cursor -> x = nx;
    }
    static void setY(int ny){
        cursor -> y = ny;
    }
    static void set(int nx, int ny){
        cursor -> x = nx;
        cursor -> y = ny;
    }
    static int getX() {
        cursor -> x = std::min(std::max(cursor -> x, 0), cursor -> widthLimit);
        return cursor -> x;
    }
    static int getY(){
        cursor -> y = std::max(cursor -> y, 0);
        return cursor -> y;
    }
    static int getVisualY(){
        return getY(); // cursor -> y < 5 ? cursor -> y : 5;
    }
    static int getInternalY(){
        return getY(); // % 5;
    }
    static int getLX() {
        // cursor -> lastX = std::min(std::max(cursor -> lastX, 0), cursor -> widthLimit);
        return cursor -> lastX;
    }
    static int getLY(){
        cursor -> lastY = std::max(cursor -> lastY, 0);
        return cursor -> lastY;
    }
    static int getLVisualY(){
        return getLY(); // cursor.lastY < 5 ? cursor.lastY : 5;
    }
    static int getLInternalY(){
        return getLY(); // % 5;
    }

    static void FixLimits(){
        // cursor.x = std::min(std::max(cursor.x, 0), cursor.widthLimit);
        // cursor.y = std::max(cursor.y, 0);

        // cursor.lastX = std::min(std::max(cursor.lastX, 0), cursor.widthLimit);
        // cursor.lastY = std::max(cursor.lastY, 0);
        
        /*
        std::cout << cursor.y << " - " << cursor.lowestY << std::endl;
        if (cursor.y - cursor.lowestY > 5){
            int diff = (cursor.y - cursor.lowestY) - 5;
            std::cout << "overLimit - " << diff << std::endl;

            for (int i = 0; i < diff; i++){
                int clearL = (cursor.y - i) % 5;
                std::cout << "clear: " << clearL << std::endl;
                // (*MFCharArr::theCharList)[clearL] = {}
            }

            cursor.lowestY = cursor.y - 5;
        }
        */
    }

    unsigned int foregroundColor = 15;
    unsigned int backgroundColor = 0;
    bool useBackground = false;

    bool BracketedPasteMode = false;
};
