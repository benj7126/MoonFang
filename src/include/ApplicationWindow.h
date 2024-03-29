#pragma once

#include "Terminal.h"

#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <stdio.h>
#include <stdlib.h>
#include <chrono>
#include <thread>
#include <string.h>
#include <vector>
#include <memory>

#include "Graphics/Canvas.h"

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

    Terminal t;
    Atom DeleteWindowMessage;

    std::shared_ptr<Graphics::Canvas> CV;

    ApplicationWindow();
    void Start();

    static ApplicationWindow W;
};
