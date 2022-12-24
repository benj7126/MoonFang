#include "ApplicationWindow.h"

#include <array>
#include <cairo/cairo-xlib.h>
#include <cstdio>
#include <iostream>
#include <memory>
#include <stdexcept>
#include <string>

unsigned long _RGB(int r, int g, int b) { return b + (g << 8) + (r << 16); }

ApplicationWindow::ApplicationWindow() {
    display = XOpenDisplay(NULL);
    if (display == NULL) {
        fprintf(stderr, "Cannot open display\n");
        exit(1);
    }

    s = DefaultScreen(display);

    int w = DisplayWidth(display, s);
    int h = DisplayHeight(display, s);

    XVisualInfo vinfo;
    XMatchVisualInfo(display, DefaultScreen(display), 32, TrueColor, &vinfo);

    XSetWindowAttributes attr;
    attr.colormap         = XCreateColormap(display, DefaultRootWindow(display), vinfo.visual, AllocNone);
    attr.border_pixel     = 0;
    attr.background_pixel = 0;

    window = XCreateWindow(display, DefaultRootWindow(display), 0, 0, 300, 200, 0, vinfo.depth, InputOutput, vinfo.visual, CWColormap | CWBorderPixel | CWBackPixel, &attr);
    //window = XCreateSimpleWindow(display, RootWindow(display, s), 0, 0, 100, 100, 1, BlackPixel(display, s), WhitePixel(display, s));

    XSelectInput(display, window, ExposureMask|ButtonPressMask|StructureNotifyMask|KeyPressMask|KeyReleaseMask);
    XMapWindow(display, window);

    char Name[]   = "MoonFang";
    XClassHint ch = {Name, Name};

    XSetClassHint(display, window, &ch);

    im = XOpenIM(display, NULL, NULL, NULL);
    ic = XCreateIC(im, XNInputStyle, XIMPreeditNothing | XIMStatusNothing, XNClientWindow, window, NULL);

    XSetICFocus(ic);


    DeleteWindowMessage = XInternAtom(display, "WM_DELETE_WINDOW", False);
    XSetWMProtocols(display, window, &DeleteWindowMessage, 1);

    XWindowAttributes WinAttr;
    XGetWindowAttributes(display, window, &WinAttr);
    CS = cairo_xlib_surface_create_with_xrender_format(display, window, WinAttr.screen, XRenderFindStandardFormat(display, PictStandardARGB32), 100, 100);
    CR = cairo_create(CS);
}

std::string convertToString(char *a, int size) {
    int i;
    std::string s = "";
    for (i = 0; i < size; i++) {
        s = s + a[i];
    }
    return s;
}

void ApplicationWindow::Start() {
    bool reDraw      = true;
    bool KeepRunning = true;
    XWindowAttributes attr;
    while (KeepRunning) {
        XGetWindowAttributes(display, window, &attr);
        if (t.SetTermProperties(attr.x, attr.y, attr.width, attr.height))
                reDraw = true;

        while (XPending(display)) {
            XNextEvent(display, &event);
            if (XFilterEvent(&event, window)){
                continue;
            }

            switch (event.type) {
                case Expose: {
                    cairo_xlib_surface_set_size(CS, event.xexpose.width, event.xexpose.height);
                    break;
                }
                case KeyPress: {
                    int count     = 0;
                    KeySym keysym = 0;
                    char buf[20];
                    Status status = 0;
                    count         = Xutf8LookupString(ic, (XKeyPressedEvent *) &event, buf, 20, &keysym, &status);

                    printf("count: %d\n", count);
                    if (status == XBufferOverflow)
                        printf("BufferOverflow\n");

                    if (count)
                        printf("buffer: %.*s\n", count, buf);

                    if (status == XLookupKeySym || status == XLookupBoth) {
                        printf("status: %d\n", status);
                    }
                    printf("pressed KEY: %d\n", (int) keysym);

                    std::string conv = convertToString(buf, count);
                    if (count > 0 && conv != "" && status == 4)
                        t.PressChar(conv, (int)keysym, (int)status);

                    reDraw = true;
                    break;
                }

                case ClientMessage:
                    if ((Atom) event.xclient.data.l[0] == DeleteWindowMessage) {
                        KeepRunning = false;
                    }
                    break;
            }
        }

        if (reDraw) {
            XClearWindow(display, window);
            t.Draw(CR);
        }


        //std::cout << charBuffer->size() << std::endl;
        //XDrawString(display, window, DefaultGC(display, s), 50, 50, t.str.c_str(), t.str.size());

        reDraw = false;
    }

    XCloseDisplay(display);
}
