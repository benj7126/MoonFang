#include "ApplicationWindow.h"

#include <cstdio>
#include <iostream>
#include <memory>
#include <stdexcept>
#include <string>
#include <array>

unsigned long _RGB(int r, int g, int b) { return b + (g << 8) + (r << 16); }

ApplicationWindow::ApplicationWindow(){
    display = XOpenDisplay(NULL);
    if (display == NULL) {
        fprintf(stderr, "Cannot open display\n");
        exit(1);
    }

    s = DefaultScreen(display);

    int w = DisplayWidth(display, s);
    int h = DisplayHeight(display, s);

    window = XCreateSimpleWindow(display, RootWindow(display, s), w-300, 0, 200, 20, 1, BlackPixel(display, s), WhitePixel(display, s));

    XSelectInput(display, window, ExposureMask | KeyPressMask);
    XMapWindow(display, window);

    char Name[] = "RT_GUI";
    XClassHint ch = {Name, Name};

    XSetClassHint(display, window, &ch);

    // Handle the close window event to stop WM from forcefully crashing
    // program.
    DeleteWindowMessage = XInternAtom(display, "WM_DELETE_WINDOW", False);
    XSetWMProtocols(display, window, &DeleteWindowMessage, 1);

}

void ApplicationWindow::Start(){
    XEvent Event;

    bool KeepRunning = true;
    while (KeepRunning) {
        XNextEvent(display, &Event);

        if(Event.type == ClientMessage) {
            if((Atom)Event.xclient.data.l[0] == DeleteWindowMessage) {
                KeepRunning = false;
            }
        }

        XFlush(display);
    }

    XCloseDisplay(display);
}
