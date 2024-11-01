#include "ApplicationWindow.h"

#include <array>
#include <cstdio>
#include <iostream>
#include <memory>
#include <stdexcept>
#include <string>

#include "Terminal.h"

#include "Graphics/CoreXFTDraw.h"

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

    int screen = DefaultScreen(display);

    XSetWindowAttributes attr;
    attr.colormap         = XCreateColormap(display, RootWindow(display, screen), vinfo.visual, AllocNone);
    attr.border_pixel     = 0;
    attr.background_pixel = 0;

    window = XCreateWindow(display, RootWindow(display, screen), 0, 0, 300, 200, 0, vinfo.depth, InputOutput, vinfo.visual, CWColormap | CWBorderPixel | CWBackPixel, &attr);
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
    buffer = XCreatePixmap(display, window, 1920, 1080, vinfo.depth); // width and height to be changed so that it handles automatically
    CV     = {display, window, buffer, vinfo.visual, attr.colormap, screen, gc};

    //pt = {ConnectionNumber(display)};
}

void ApplicationWindow::Start() {
    bool redraw = false;
    bool KeepRunning = true;
    XWindowAttributes attr;
    
    Terminal::term.CV = &CV;

    std::cout << "test" << std::endl;

    // XGetWindowAttributes(display, window, &attr);
    // XClearArea(display, window, 0, 0, attr.width, attr.height, false);
    while (KeepRunning) {
        // std::cout << (char)Terminal::term.lines[0][0].value << std::endl;
        XGetWindowAttributes(display, window, &attr);
        if (Terminal::term.SetTermProperties(attr.x, attr.y, attr.width, attr.height)) {
            redraw = true;
        }

        XGetWindowAttributes(display, window, &attr);

        if (Terminal::term.Update())
            redraw = true;

        XGetWindowAttributes(display, window, &attr);

        while (XPending(display)) {
            XNextEvent(display, &event);
            if (XFilterEvent(&event, window)) {
                continue;
            }

            switch (event.type) {
                case Expose: {
                    redraw = true; // TODO: make it draw only area within event.xexpose.width, event.xexpose.height
                    break;
                }
                case ConfigureNotify: {
                    Terminal::term.ChangeSize(event.xconfigure.width, event.xconfigure.height);
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
                    Terminal::term.PressChar(conv, keysym, (int) status);
                    break;
                }

                case ClientMessage:
                    if ((Atom) event.xclient.data.l[0] == DeleteWindowMessage) {
                        KeepRunning = false;
                    }
                    break;
            }
        }

        XGetWindowAttributes(display, window, &attr);

        if (redraw || true) {
            CV.UseBuffer();
            XFillRectangle(display, buffer, gc, 0, 0, attr.width, attr.height);
            Terminal::term.Draw();
            XCopyArea(display, buffer, window, gc, 0, 0, attr.width, attr.height, 0, 0); // for redrawing whole screen?
            CV.UseWindow();

            redraw = false;


            // CV->EndDraw();
            // XCopyArea(display, buffer, window, gc, 0, 0, attr.width, attr.height, 0, 0); // for redrawing whole screen?
            // XClearArea(display, buffer, 0, 0, attr.width, attr.height, false);
            // XFillRectangle(display, buffer, gc, 0, 0, attr.width, attr.height);
        // } else {
        }

        //std::cout << charBuffer->size() << std::endl;
        //XDrawString(display, window, DefaultGC(display, s), 50, 50, t.str.c_str(), t.str.size());
    }

    XCloseDisplay(display);
}
