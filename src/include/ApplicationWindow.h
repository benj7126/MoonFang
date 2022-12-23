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

class ApplicationWindow {
private:
    Display *display;
    Window window;
    XEvent event;
    int s;

    XIM im;
    XIC ic;

    Terminal t;

public:
    ApplicationWindow();
    void Start();
};
