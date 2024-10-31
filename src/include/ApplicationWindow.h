#pragma once

#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <stdio.h>
#include <stdlib.h>
#include <chrono>
#include <thread>
#include <string.h>
#include <vector>
#include <memory>

#include "Graphics/CoreXFTDraw.h"

class ApplicationWindow {
public:
    Display *display;
    Window window;
    XEvent event;
    int s;

    Pixmap buffer;
    GC gc;

    XIM im;
    XIC ic;

    Atom DeleteWindowMessage;

    Graphics::CoreXFTDraw CV;

    ApplicationWindow();
    void Start();

    static ApplicationWindow W;
};
