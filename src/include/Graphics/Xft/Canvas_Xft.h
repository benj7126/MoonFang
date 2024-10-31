/*
#pragma once

#include <X11/Xlib.h>
#include <X11/Xft/Xft.h>

#include "Graphics/Canvas.h"

namespace Graphics {
    class Canvas_Xft : public Canvas {
        private:
            XftGlyphFontSpec *specbuf;

        public:
            Canvas_Xft(Display* display, Window window, Screen* screen, XRenderPictFormat* pictformat);

            void StartDraw() override;
            void EndDraw() override;

            void SetColor(double r, double g, double b) override;
            void SetColor(Color C) override;

            void SetFont(std::string Font) override;
            TextData GetTextData(int x, int y, std::string Text) override;
            void DrawText(TextData TD) override;
            void DrawTextRect(TextData TD) override;

            void SetSize(int width, int height) override;

            void MoveTo(int x, int y) override;
    };
}
*/
