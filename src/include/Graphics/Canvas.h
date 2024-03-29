#pragma once

#include<string>

#include "Color.h"

namespace Graphics {

    struct DrawTextRet {
        double Width;
        double Height;
    };

    class Canvas {
        public:
            virtual void SetColor(double r, double g, double b) = 0;
            virtual void SetColor(Color C) = 0;

            virtual void SetFont(std::string Font) = 0;
            virtual DrawTextRet DrawText(int x, int y, std::string Text) = 0;

            virtual void SetSize(int width, int height) = 0;

            virtual void MoveTo(int x, int y) = 0;
    };
}
