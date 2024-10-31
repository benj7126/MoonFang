#pragma once

#include <X11/Xlib.h>
#include <X11/Xft/Xft.h>

#include "Color.h"

#include <string>

namespace Graphics {
    class CoreXFTDraw {
        private:
            XftDraw* drawBuff;
            XftDraw* drawWindow;

            Display* display;

            XftColor blank;

            GC gc;

            Drawable window;
            Drawable buffer;
            bool drawToWindow = true; // it cant draw to buffer for some reason...
            // int Color = 0;
            
        public:
            static CoreXFTDraw* theCV;
            XftFont* font; // why this pointin so much?

            CoreXFTDraw() = default;
            CoreXFTDraw(Display* display, Drawable window, Drawable buffer, Visual* visual, Colormap colormap, int screen, GC gc);

            void UseWindow() {drawToWindow = true; };
            void UseBuffer() {drawToWindow = false; };

            void DrawTextRect(int x, int y, unsigned int color, int width = 1, int height = 1);
            void ClearTextRect(int x, int y, int width = 1, int height = 1);
            void DrawText(int x, int y, XftChar32* text, int chars, unsigned int color);

            /*
            void SetColor(unsigned int x);
            void StartDraw();
            void EndDraw();

            void SetColor(Color C);

            void SetFont(std::string Font) = 0;
            TextData GetTextData(int x, int y, std::string Text);

            void SetSize(int width, int height);

            void MoveTo(int x, int y);
            */
    };
}
