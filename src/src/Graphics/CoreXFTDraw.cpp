#include "Graphics/CoreXFTDraw.h"
#include "Graphics/XFTColors.h"

#include <X11/Xft/Xft.h>
#include <X11/Xlib.h>

#include <cassert>
#include <iostream>

namespace Graphics {
    CoreXFTDraw* CoreXFTDraw::theCV = nullptr;

    CoreXFTDraw::CoreXFTDraw(Display* display, Drawable window, Drawable buffer, Visual* visual, Colormap colormap, int screen, GC gc) : display{display}, window{window}, buffer{buffer}, gc{gc} {
        theCV = this;

        XFTColors::Setup(display, visual, colormap);

        blank = {};
        XRenderColor colorValue {0, 0, 0, 0};
        XftColorAllocValue(display, visual, colormap, &colorValue, &blank);

        drawWindow = XftDrawCreate(display, window, visual, colormap);
        drawBuff = XftDrawCreate(display, buffer, visual, colormap);
        font = XftFontOpenName(display, screen, "Hack:pixelsize=13:antialias=true:autohint=true");
    }

    void CoreXFTDraw::ClearTextRect(int x, int y, int width, int height){
        if (drawToWindow)
            XClearArea(display, window, x, y - font->height + 4, font->max_advance_width * width, font->height * height, 0);
        else
            XftDrawRect(drawBuff, &blank, x, y - font->height + 4, font->max_advance_width * width, font->height * height);
    }

    void CoreXFTDraw::DrawTextRect(int x, int y, unsigned int color, int width, int height){

        if (XFTColors::GetColor(color)->color.alpha == 0){
            XClearArea(display, drawToWindow ? window : buffer, x, y - font->height + 4, font->max_advance_width * width, font->height * height, 0);
            return;
        }

        XftDrawRect(drawToWindow ? drawWindow : drawBuff, XFTColors::GetColor(color), x, y - font->height + 4, font->max_advance_width * width, font->height);
    }

    void CoreXFTDraw::DrawText(int x, int y, XftChar32* text, int chars, unsigned int color){ // need to change from string to the glyph thingys, i think.
        if (XFTColors::GetColor(color)->color.alpha == 0)
            return;

        XftDrawString32(drawToWindow ? drawWindow : drawBuff, XFTColors::GetColor(color), font, x, y, text, chars);
    }
}

