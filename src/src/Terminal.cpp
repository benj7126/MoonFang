#include "Terminal.h"

#include <iostream>


void Terminal::PressChar(std::string inpString, int keysym, int status) {
    curString += inpString;
    if (keysym == 65293) {// enter
        lines.push_back(curString);
        curString = "";
    }
}

void Terminal::Draw(cairo_t *CR) {
    cairo_select_font_face(CR, "Sans", CAIRO_FONT_SLANT_NORMAL, CAIRO_FONT_WEIGHT_NORMAL);
    cairo_set_font_size(CR, 12.0);

    cairo_font_options_t *font_options = cairo_font_options_create();

    cairo_set_source_rgb(CR, 0.8, 0.8, 0.8);

    double x = 5;
    double y = 12 + 5;
    for (int lineIDX = 0; lineIDX <= lines.size(); lineIDX++) {
        std::string &line = (lineIDX == lines.size() ? curString : lines[lineIDX]);
        cairo_move_to(CR, x, y);

        for (char c : line) {
            cairo_show_text(CR, &c);
            cairo_get_current_point(CR, &x, &y);
            if (x >= width-12) {
                x = 5;
                y += 20;
                cairo_move_to(CR, x, y);
            }
        }

        x = 5;
        y += 20;
    }
}

bool Terminal::SetTermProperties(int _x, int _y, int _width, int _height) {
    bool changed = false;

    changed = x != _x || y != _y || width != _width || height != _height;

    x      = _x;
    y      = _y;
    width  = _width;
    height = _height;

    return changed;
}
