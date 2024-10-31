#pragma once

#include <X11/Xlib.h>
#include <X11/Xft/Xft.h>

#include <unordered_map>
#include <vector>

#include <iostream>

namespace Graphics {
    class XFTColors {
    private:
        static const std::vector<XRenderColor> renderColors;
        static std::vector<XftColor> colors;
        static std::unordered_map<int, unsigned int> colorMap;

        static Display* display;
        static Visual* visual;
        static Colormap cmap;

    public:
        static void Setup(Display* d, Visual* v, Colormap c){
            display = d;
            visual = v;
            cmap = c;

            for (XRenderColor c : renderColors){
                colors.push_back({});

                XftColorAllocValue(display, visual, cmap, &c, &colors.back());
            }
        }

        static unsigned int GetColor(unsigned char r, unsigned char g, unsigned char b, unsigned char a){
            unsigned int mapIndex = (((((r << 8) | g) << 8) | b) << 8) | a;

            if (colorMap.count(mapIndex)){
                return colorMap.at(mapIndex);
            }

            colors.push_back({});

            XRenderColor colorValue {(unsigned short)(r * 257), (unsigned short)(g * 257), (unsigned short)(b * 257), (unsigned short)(a * 257)};
            XftColorAllocValue(display, visual, cmap, &colorValue, &colors.back());

            colorMap.insert({mapIndex, colors.size()-1});

            return colors.size()-1;
        }

        static XftColor* GetColor(int color){
            if (colors.size() < color)
                return &(colors[0]);

            return &(colors[color]);
        }
    };
}
