/*
#pragma once

#include <string>
#include <pango/pangocairo.h>

#include "Color.h"

namespace Graphics {

    struct TextData {
        double BWidth;
        double BHeight;

        int x;
        int y;
    };

    class Canvas {
        public:
            virtual void StartDraw() = 0;
            virtual void EndDraw() = 0;
            virtual void SetColor(double r, double g, double b) = 0;
            virtual void SetColor(Color C) = 0;

            virtual void SetFont(std::string Font) = 0;
            virtual TextData GetTextData(int x, int y, std::string Text) = 0;
            virtual void DrawText(TextData TD) = 0;
            virtual void DrawTextRect(TextData TD) = 0;

            virtual void SetSize(int width, int height) = 0;

            virtual void MoveTo(int x, int y) = 0;
    };
}
*/
