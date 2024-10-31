/*
#include "Graphics/Canvas.h"
#include "Graphics/CairoPango/Canvas_CairoPango.h"
#include <cairo/cairo-xlib-xrender.h>
#include <cairo/cairo-xlib.h>
#include <X11/Xlib.h>
#include <X11/extensions/Xrender.h>

#include <cassert>
#include <iostream>

namespace Graphics {
    void Canvas_CairoPango::StartDraw(){
        layout = pango_cairo_create_layout(CR);
        assert(layout != NULL && "Assert is null");
    }

    void Canvas_CairoPango::EndDraw(){
        //cairo_move_to(CR, 0, 0);
    }

    Canvas_CairoPango::Canvas_CairoPango(Display* display, Window window, Screen* screen, XRenderPictFormat* pictformat) {
        CS = cairo_xlib_surface_create_with_xrender_format(display, window, screen, pictformat, 100, 100);
        CR = cairo_create(CS);
    }

    void Canvas_CairoPango::SetColor(double r, double g, double b) {
        cairo_set_source_rgb(CR, r, g, b);
    }
    
    void Canvas_CairoPango::SetColor(Color C){
        cairo_set_source_rgb(CR, C.R/255.0, C.G/255.0, C.B/255.0);
    }

    void Canvas_CairoPango::SetFont(std::string Font) {
        this->Font = Font;
    }

    TextData Canvas_CairoPango::GetTextData(int x, int y, std::string Text) {
        static int tW = 0;
        static int tH = 0;

        PangoFontDescription *desc = pango_font_description_from_string(Font.c_str());
        pango_layout_set_font_description(layout, desc);
        pango_font_description_free(desc);

        pango_layout_set_text(layout, Text.c_str(), 1);

        pango_cairo_update_layout(CR, layout);

        // Get info for return. v(values)v pending
        if (tW == 0)
        {
            pango_cairo_update_layout(CR, layout);
            pango_layout_get_size (layout, &tW, &tH);
        }

        double tWD, tHD;
        tWD = ((double)tW / PANGO_SCALE);
        tHD = ((double)tH / PANGO_SCALE);

        // std::cout << Text << " | " << tWD << " "<<x<<" " << tHD << " "<<y<<" " << std::endl;

        return {tWD,tHD, x, y};
    }

    void Canvas_CairoPango::DrawText(TextData TD){
        cairo_move_to(CR, TD.x, TD.y);
        pango_cairo_show_layout(CR, layout);
    }

    void Canvas_CairoPango::DrawTextRect(TextData TD){
        cairo_rectangle(CR, TD.x, TD.y, TD.BWidth, TD.BHeight);
        cairo_fill(CR);
    }

    void Canvas_CairoPango::SetSize(int width, int height) {
        cairo_xlib_surface_set_size(CS, width, height);
    }

    void Canvas_CairoPango::MoveTo(int x, int y){
        cairo_move_to(CR, x, y);
    }
}
*/
