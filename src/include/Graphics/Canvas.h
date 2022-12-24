#pragma once

#include<string>

namespace Graphics {

    struct DrawTextRet {
        int Width;
        int Height;
    };

    struct GetPosRet {
        double x;
        double y;
    };

    class Canvas {
        public:
            virtual void SetColor(double r, double g, double b) = 0;

            virtual void SetFont(std::string Font) = 0;
            virtual DrawTextRet DrawText(int x, int y, std::string Text) = 0;
            virtual DrawTextRet DrawText(std::string Text) = 0;

            virtual void SetSize(int width, int height) = 0;

            virtual void SetPos(double x, double y) = 0;

            virtual GetPosRet GetPos() = 0;
            virtual void GetPos(double& x, double& y) = 0;
    };
}
