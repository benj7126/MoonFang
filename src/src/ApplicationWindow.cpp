#include "ApplicationWindow.h"

#include <array>
#include <cairo/cairo-xlib.h>
#include <cstdio>
#include <iostream>
#include <memory>
#include <stdexcept>
#include <string>

#include "Graphics/CairoPango/Canvas_CairoPango.h"

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

    XSelectInput(display, window, ExposureMask | ButtonPressMask | StructureNotifyMask | KeyPressMask | KeyReleaseMask);
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
    gc     = XCreateGC(display, window, 0, NULL);
    buffer = XCreatePixmap(display, window, 10000, 10000, vinfo.depth);
    CV     = std::make_shared<Graphics::Canvas_CairoPango>(display, buffer, WinAttr.screen, XRenderFindStandardFormat(display, PictStandardARGB32));

    //pt = {ConnectionNumber(display)};
}

void ApplicationWindow::Start() {
    bool reDraw      = true;
    bool KeepRunning = true;
    XWindowAttributes attr;
    while (KeepRunning) {
        XGetWindowAttributes(display, window, &attr);
        if (t.SetTermProperties(attr.x, attr.y, attr.width, attr.height)) {
            reDraw = true;
        }

        if (t.Update())
            reDraw = true;

        while (XPending(display)) {
            XNextEvent(display, &event);
            if (XFilterEvent(&event, window)) {
                continue;
            }

            switch (event.type) {
                case Expose: {
                    CV->SetSize(event.xexpose.width, event.xexpose.height);
                    break;
                }
                case KeyPress: {
                    int count     = 0;
                    KeySym keysym = 0;
                    char buf[20];
                    Status status = 0;
                    count         = Xutf8LookupString(ic, (XKeyPressedEvent *) &event, buf, 20, &keysym, &status);

                    /*
                    printf("count: %d\n", count);
                    if (status == XBufferOverflow)
                        printf("BufferOverflow\n");

                    if (count)
                        printf("buffer: %.*s\n", count, buf);

                    if (status == XLookupKeySym || status == XLookupBoth) {
                        printf("status: %d\n", status);
                    }
                    printf("pressed KEY: %d\n", (int) keysym);
                    */

                    std::string conv = std::string{buf, (size_t) count};
                    if (count > 0 && conv != "" && status == 4)
                        t.PressChar(conv, (int) keysym, (int) status);

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
            t.Draw(CV);
            XCopyArea(display, buffer, window, gc, 0, 0, attr.width, attr.height, 0, 0);
            //XClearArea(display, buffer, 0, 0, attr.width, attr.height, false);
            XFillRectangle(display, buffer, gc, 0, 0, attr.width, attr.height);
        }

        //std::cout << charBuffer->size() << std::endl;
        //XDrawString(display, window, DefaultGC(display, s), 50, 50, t.str.c_str(), t.str.size());

        //std::this_thread::sleep_for(std::chrono::milliseconds(10));
        reDraw = false;
    }

    XCloseDisplay(display);
}
