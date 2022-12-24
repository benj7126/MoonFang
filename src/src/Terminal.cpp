#include "Terminal.h"

#include <iostream>
#include <pango/pangocairo.h>


void Terminal::PressChar(std::string inpString, int keysym, int status) {
    curString += inpString;
    if (keysym == 65293) {// enter
        lines.push_back(curString);
        curString = "";
    }
}

void Terminal::Draw(cairo_t *CR) {
    cairo_set_source_rgb(CR, 0.8, 0.8, 0.8);

    PangoLayout *layout = pango_cairo_create_layout(CR);
    PangoFontDescription *desc = pango_font_description_from_string("Hack Normal 9");
    pango_layout_set_font_description(layout, desc);
    pango_font_description_free(desc);

    double x = 5;
    double y = 12 + 5;
    for (int lineIDX = 0; lineIDX <= lines.size(); lineIDX++) {
        std::string &line = (lineIDX == lines.size() ? curString : lines[lineIDX]);
        cairo_move_to(CR, x, y);

        for (char c : line) {
            pango_layout_set_text(layout, &c, 1);
            pango_cairo_update_layout(CR, layout);
            pango_cairo_show_layout(CR, layout);

            int charW, charH;
            pango_layout_get_size (layout, &charW, &charH);

            cairo_get_current_point(CR, &x, &y);
            x += ((double)charW/PANGO_SCALE);
            cairo_move_to(CR, x, y);
            if (x >= width-12) {
                x = 5;
                y += 20;
                cairo_move_to(CR, x, y);
            }
        }

        x = 5;
        y += 20;
    }

    g_object_unref(layout);
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
