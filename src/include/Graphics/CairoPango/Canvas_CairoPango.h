/*
#pragma once

#include <cairo/cairo.h>
#include <X11/Xlib.h>
#include <X11/extensions/Xrender.h>

#include "Graphics/Canvas.h"

namespace Graphics {
    class Canvas_CairoPango : public Canvas {
        private:
            std::string Font = "Sans Normal 9";

            PangoLayout *layout = nullptr;

            cairo_surface_t* CS;
            cairo_t* CR;
        public:
            Canvas_CairoPango(Display* display, Window window, Screen* screen, XRenderPictFormat* pictformat);

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
