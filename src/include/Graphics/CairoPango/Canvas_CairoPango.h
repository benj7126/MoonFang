#pragma once

#include "Graphics/Canvas.h"
#include <cairo/cairo.h>
#include <X11/Xlib.h>
#include <X11/extensions/Xrender.h>

namespace Graphics {
    class Canvas_CairoPango : public Canvas {
        private:
            std::string Font = "Sans Normal 9";

            cairo_surface_t* CS;
            cairo_t* CR;
        public:
            Canvas_CairoPango(Display* display, Window window, Screen* screen, XRenderPictFormat* pictformat);

            void SetColor(double r, double g, double b);

            void SetFont(std::string Font);
            DrawTextRet DrawText(int x, int y, std::string Text);
            DrawTextRet DrawText(std::string Text);

            void SetSize(int width, int height);

            void SetPos(double x, double y);
            GetPosRet GetPos();
            void GetPos(double& x, double& y);
    };
}
