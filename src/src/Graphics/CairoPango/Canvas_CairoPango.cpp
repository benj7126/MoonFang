#include "Graphics/Canvas.h"
#include "Graphics/CairoPango/Canvas_CairoPango.h"
#include <cairo/cairo-xlib-xrender.h>
#include <cairo/cairo-xlib.h>
#include <pango/pangocairo.h>
#include <X11/Xlib.h>
#include <X11/extensions/Xrender.h>

namespace Graphics {
    Canvas_CairoPango::Canvas_CairoPango(Display* display, Window window, Screen* screen, XRenderPictFormat* pictformat) {
        CS = cairo_xlib_surface_create_with_xrender_format(display, window, screen, pictformat, 100, 100);
        CR = cairo_create(CS);
    }

    void Canvas_CairoPango::SetColor(double r, double g, double b) {
        cairo_set_source_rgb(CR, r, g, b);
    }

    void Canvas_CairoPango::SetFont(std::string Font) {
        this->Font = Font;
    }

    DrawTextRet Canvas_CairoPango::DrawText(int x, int y, std::string Text) {
        cairo_move_to(CR, x, y);

        PangoLayout *layout = pango_cairo_create_layout(CR);
        PangoFontDescription *desc = pango_font_description_from_string(Font.c_str());
        pango_layout_set_font_description(layout, desc);
        pango_font_description_free(desc);

        pango_layout_set_text(layout, Text.c_str(), 1);
        pango_cairo_update_layout(CR, layout);
        pango_cairo_show_layout(CR, layout);


        // Get info for return.
        int tW, tH;
        pango_layout_get_size (layout, &tW, &tH);

        double tWD, tHD;
        tWD = ((double)tW / PANGO_SCALE);
        tHD = ((double)tW / PANGO_SCALE);

        return {tWD,tHD};
    }

    void Canvas_CairoPango::SetSize(int width, int height) {
        cairo_xlib_surface_set_size(CS, width, height);
    }
}
